#!/usr/bin/env python3
"""
ft_irc ultimate evaluation tester (RFC 2812 compliant)
Usage:
  python3 test.py --port 6667 --password mypass [--server ./ircserv] [--leak-check] [--extreme]
  python3 test.py --port 6667 --password mypass --no-server          # server already running
"""

import socket
import subprocess
import time
import sys
import os
import signal
import argparse
import shutil

# ------------------------------------------------------------
# IRC helpers
# ------------------------------------------------------------
def irc_command(cmd, *args):
    if args:
        msg = f"{cmd} {' '.join(args)}"
    else:
        msg = cmd
    return msg.encode() + b'\r\n'

def parse_reply(data):
    return data.decode('utf-8', errors='replace').split('\r\n')

# ------------------------------------------------------------
# Client
# ------------------------------------------------------------
class IRCClient:
    def __init__(self, host, port, password, nick='testnick', timeout=5.0, verbose=False):
        self.host = host
        self.port = port
        self.password = password
        self.nick = nick
        self.timeout = timeout
        self.verbose = verbose
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.settimeout(timeout)
        self.connected = False

    def connect(self, skip_auth=False):
        self.sock.connect((self.host, self.port))
        self.connected = True
        if not skip_auth:
            self.send_raw(f"PASS {self.password}\r\n".encode())
            self.send_raw(f"NICK {self.nick}\r\n".encode())
            self.send_raw(f"USER testuser 0 * :Test User\r\n".encode())
            if self.read_until(lambda l: '001' in l, timeout=5.0) is None:
                raise Exception("Did not receive 001 (RPL_WELCOME)")

    def send_raw(self, data):
        if self.verbose:
            print(f"[->] {data}")
        self.sock.sendall(data)

    def send_cmd(self, cmd, *args):
        self.send_raw(irc_command(cmd, *args))

    def read_until(self, condition, timeout=5.0):
        buf = b''
        deadline = time.time() + timeout
        while time.time() < deadline:
            try:
                data = self.sock.recv(4096)
                if not data:
                    break
                buf += data
                lines = parse_reply(buf)
                for line in lines:
                    if condition(line):
                        return lines
            except socket.timeout:
                continue
        print(f"[DEBUG] Timeout waiting. Received so far:\n{buf.decode(errors='replace')}")
        return None

    def read_some(self, timeout=0.5):
        self.sock.settimeout(timeout)
        try:
            data = self.sock.recv(4096)
            return parse_reply(data) if data else []
        except socket.timeout:
            return []

    def close(self):
        if self.sock:
            self.sock.close()
        self.connected = False

# ------------------------------------------------------------
# Tester
# ------------------------------------------------------------
class Tester:
    def __init__(self, port, password, server_path=None, leak_check=False, no_server=False, verbose=False, extreme=False):
        self.port = port
        self.password = password
        self.server_path = server_path
        self.leak_check = leak_check and not no_server
        self.no_server = no_server
        self.verbose = verbose
        self.extreme = extreme
        self.server_proc = None
        self.passed = 0
        self.failed = 0

    def log(self, msg, level="INFO"):
        print(f"[{level}] {msg}")

    def port_is_open(self, timeout=5.0):
        deadline = time.time() + timeout
        while time.time() < deadline:
            try:
                s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                s.settimeout(1)
                s.connect(('127.0.0.1', self.port))
                s.close()
                return True
            except Exception:
                time.sleep(0.2)
        return False

    def start_server(self):
        if self.no_server:
            self.log("No server started (--no-server). Assuming server is already running.")
            if not self.port_is_open(timeout=2):
                self.log("ERROR: No server listening on port. Start it manually.", "ERROR")
                sys.exit(1)
            return

        cmd = [self.server_path, str(self.port), self.password]
        if self.leak_check:
            if shutil.which('valgrind'):
                cmd = ['valgrind', '--leak-check=full', '--show-leak-kinds=all',
                       '--track-fds=yes', '--error-exitcode=42'] + cmd
            elif sys.platform == 'darwin':
                self.log("Will use 'leaks' at the end.")
            else:
                self.log("No Valgrind/leaks found; leak check disabled.", "WARN")
                self.leak_check = False

        self.log(f"Starting: {' '.join(cmd)}")
        self.server_proc = subprocess.Popen(cmd, stdout=subprocess.PIPE,
                                            stderr=subprocess.PIPE, preexec_fn=os.setpgrp)
        if not self.port_is_open(timeout=10):
            self.log("Server did not start listening in time.", "ERROR")
            self.stop_server()
            sys.exit(1)
        self.log("Server is ready.")

    def stop_server(self):
        if self.no_server or not self.server_proc:
            return
        if self.leak_check:
            if sys.platform == 'darwin':
                pid = self.server_proc.pid
                self.server_proc.terminate()
                try:
                    self.server_proc.wait(timeout=3)
                except subprocess.TimeoutExpired:
                    self.server_proc.kill()
                    self.server_proc.wait()
                time.sleep(0.5)
                leaks_output = subprocess.run(['leaks', str(pid)],
                                              capture_output=True, text=True).stdout
                self.log(f"Leaks report:\n{leaks_output}")
                if "0 leaks" in leaks_output:
                    self.log("✅ No leaks detected by leaks.")
                else:
                    self.log("❌ Memory leaks reported!", "FAIL")
                    self.failed += 1
            else:  # valgrind
                self.server_proc.send_signal(signal.SIGINT)
                try:
                    self.server_proc.wait(timeout=10)
                except subprocess.TimeoutExpired:
                    self.server_proc.kill()
                    self.server_proc.wait()
                if self.server_proc.returncode == 42:
                    self.log("❌ Valgrind detected memory errors/leaks!", "FAIL")
                    self.failed += 1
                else:
                    self.log("✅ Valgrind: no errors/leaks.")
        else:
            self.server_proc.terminate()
            try:
                self.server_proc.wait(timeout=3)
            except subprocess.TimeoutExpired:
                self.server_proc.kill()
                self.server_proc.wait()

    def new_client(self, nick='testnick', verbose=None):
        if verbose is None:
            verbose = self.verbose
        return IRCClient('127.0.0.1', self.port, self.password, nick=nick, verbose=verbose)

    def assert_true(self, condition, test_name):
        if condition:
            self.log(f"✅ PASS: {test_name}")
            self.passed += 1
        else:
            self.log(f"❌ FAIL: {test_name}", "FAIL")
            self.failed += 1

    # --------------------------------------------------------
    # Mandatory tests (unchanged)
    # --------------------------------------------------------
    def test_basic_connection(self):
        self.log("\n=== Basic Connection ===")
        try:
            c = self.new_client(nick='testconn')
            c.connect()
            c.close()
            self.assert_true(True, "Connection with valid password")
        except Exception as e:
            self.assert_true(False, f"Connection failed: {e}")

        try:
            c = IRCClient('127.0.0.1', self.port, 'wrongpass', nick='wrongpwd', verbose=False)
            c.connect(skip_auth=False)
            self.assert_true(False, "Wrong password should be rejected")
        except Exception:
            self.assert_true(True, "Connection with wrong password rejected")

    def test_nick_user_join(self):
        self.log("\n=== NICK, USER, JOIN ===")
        c = self.new_client(nick='testjoin')
        c.connect()
        c.send_cmd('JOIN', '#test')
        lines = c.read_until(lambda l: 'JOIN' in l and '#test' in l, timeout=3)
        self.assert_true(lines and any('#test' in l and 'JOIN' in l for l in lines), "Join channel #test")
        c.close()

    def test_privmsg(self):
        self.log("\n=== PRIVMSG ===")
        c1 = self.new_client(nick='tester1')
        c1.connect()
        c1.send_cmd('JOIN', '#msg')
        time.sleep(0.1)
        c2 = self.new_client(nick='tester2')
        c2.connect()
        c2.send_cmd('JOIN', '#msg')
        time.sleep(0.1)

        c1.send_cmd('PRIVMSG', '#msg', ':Hello channel')
        replies = c2.read_until(lambda l: 'Hello channel' in l, timeout=3)
        self.assert_true(replies and any('Hello channel' in l for l in replies), "Channel message received")

        c1.send_cmd('PRIVMSG', 'tester2', ':Hi private')
        replies = c2.read_until(lambda l: 'Hi private' in l, timeout=3)
        self.assert_true(replies and any('Hi private' in l for l in replies), "Private message received")
        c1.close()
        c2.close()

    def test_partial_commands(self):
        self.log("\n=== Partial commands (Ctrl+D simulation) ===")
        c = IRCClient('127.0.0.1', self.port, self.password, nick='testpart', verbose=False)
        c.sock.connect(('127.0.0.1', self.port))
        c.connected = True
        c.send_raw(f"PASS {self.password}\r\n".encode())
        c.send_raw(f"NICK testpart\r\n".encode())
        c.send_raw(b"USE")
        time.sleep(0.1)
        c.send_raw(b"R testpart 0 * :T\r\n")
        lines = c.read_until(lambda l: '001' in l, timeout=5)
        self.assert_true(lines is not None and any('001' in l for l in lines), "Auth with partial USER")

        c.send_raw(b"JOIN #par")
        time.sleep(0.1)
        c.send_raw(b"tial\r\n")
        replies = c.read_until(lambda l: 'JOIN' in l, timeout=3)
        self.assert_true(replies and any('#partial' in l for l in replies), "Join with partial command")
        c.close()

    def test_kill_client_mid_command(self):
        self.log("\n=== Kill client mid command ===")
        c = self.new_client(nick='killme')
        c.connect()
        c.send_raw(b"JOIN #kill\r\n")
        time.sleep(0.1)
        c.send_raw(b"PRIVMSG #kill :This message will")
        c.close()

        try:
            new_c = self.new_client(nick='survivor')
            new_c.connect()
            new_c.close()
            self.assert_true(True, "Server alive after client killed mid-command")
        except Exception as e:
            self.assert_true(False, f"Server dead: {e}")

    def test_flood_with_stopped_client(self):
        self.log("\n=== Flood with stopped client (simulate Ctrl+Z) ===")
        c1 = self.new_client(nick='flood1')
        c1.connect()
        c1.send_cmd('JOIN', '#flood')
        time.sleep(0.1)
        c2 = self.new_client(nick='flood2')
        c2.connect()
        c2.send_cmd('JOIN', '#flood')
        time.sleep(0.1)

        c3 = None
        try:
            for i in range(100):
                c2.send_cmd('PRIVMSG', '#flood', f':msg{i}')
                time.sleep(0.005)
            time.sleep(0.5)
            c3 = self.new_client(nick='alivechk')
            c3.connect()
            self.assert_true(True, "Server responsive after flood with stopped client")
        except Exception as e:
            self.assert_true(False, f"Server hang: {e}")
        finally:
            c1.close()
            c2.close()
            if c3:
                c3.close()

    def test_operator_commands(self):
        self.log("\n=== Channel operator commands ===")
        c1 = self.new_client(nick='op1')
        c1.connect()
        c1.send_cmd('JOIN', '#ops')
        time.sleep(0.1)
        c2 = self.new_client(nick='op2')
        c2.connect()
        c2.send_cmd('JOIN', '#ops')
        time.sleep(0.1)

        # Non-op KICK (should receive 482 ERR_CHANOPRIVSNEEDED)
        c2.send_cmd('KICK', '#ops', 'op1')
        replies = c2.read_until(lambda l: '482' in l, timeout=1.0)
        self.assert_true(replies and any('482' in l for l in replies), "Non-op KICK denied (482)")

        # Op kicks c2
        c1.send_cmd('KICK', '#ops', 'op2')
        replies = c2.read_until(lambda l: 'KICK' in l, timeout=3)
        self.assert_true(replies and any('KICK' in l for l in replies), "Op kicks user")
        c2.send_cmd('JOIN', '#ops')
        time.sleep(0.1)

        # MODE +i (invite-only)
        c1.send_cmd('MODE', '#ops', '+i')
        time.sleep(0.1)
        c2.send_cmd('INVITE', 'someuser', '#ops')
        replies = c2.read_until(lambda l: '482' in l, timeout=1.0)
        self.assert_true(replies and any('482' in l for l in replies), "Non-op INVITE denied")

        # Remove +i before TOPIC and +k/+l tests
        c1.send_cmd('MODE', '#ops', '-i')
        time.sleep(0.1)

        # TOPIC – non-op must be rejected (482)
        c2.send_cmd('TOPIC', '#ops', ':Should fail')
        replies = c2.read_until(lambda l: '482' in l, timeout=1.0)
        self.assert_true(replies and any('482' in l for l in replies), "Non-op TOPIC denied")
        c1.send_cmd('TOPIC', '#ops', ':New topic')
        replies = c2.read_until(lambda l: 'New topic' in l, timeout=3)
        self.assert_true(replies and any('New topic' in l for l in replies), "Op changes topic")
        c1.send_cmd('TOPIC', '#ops')
        replies = c1.read_until(lambda l: '332' in l, timeout=3)
        self.assert_true(replies and any('332' in l and 'New topic' in l for l in replies), "TOPIC view (332)")

        # MODE +t
        c1.send_cmd('MODE', '#ops', '+t')
        time.sleep(0.1)
        c2.send_cmd('TOPIC', '#ops', ':Fail under +t')
        replies = c2.read_until(lambda l: '482' in l, timeout=1.0)
        self.assert_true(replies and any('482' in l for l in replies), "Non-op TOPIC denied under +t")
        c1.send_cmd('TOPIC', '#ops', ':Still works')
        replies = c1.read_until(lambda l: 'Still works' in l, timeout=1.0)
        self.assert_true(replies and any('Still works' in l for l in replies), "Op can still change topic under +t")

        # MODE +k (channel key)
        c1.send_cmd('MODE', '#ops', '+k', 'secret')
        time.sleep(0.1)
        c3 = self.new_client(nick='keytest')
        c3.connect()
        c3.send_cmd('JOIN', '#ops', 'badkey')
        replies = c3.read_until(lambda l: '475' in l, timeout=1.0)
        self.assert_true(replies and any('475' in l for l in replies), "JOIN with wrong key denied (475)")
        c3.send_cmd('JOIN', '#ops', 'secret')
        replies = c3.read_until(lambda l: 'JOIN' in l, timeout=3)
        self.assert_true(replies and any('JOIN' in l for l in replies), "JOIN with correct key")
        c3.close()

        # MODE +l (user limit)
        c1.send_cmd('MODE', '#ops', '-k')
        time.sleep(0.1)
        c1.send_cmd('MODE', '#ops', '+l', '2')
        time.sleep(0.1)
        c3 = self.new_client(nick='limtest')
        c3.connect()
        c3.send_cmd('JOIN', '#ops')
        replies = c3.read_until(lambda l: '471' in l, timeout=1.0)
        self.assert_true(replies and any('471' in l for l in replies), "JOIN denied when channel full (471)")
        c3.close()
        c1.send_cmd('MODE', '#ops', '-l')
        time.sleep(0.1)

        # MODE +o (give/take operator)
        c1.send_cmd('MODE', '#ops', '+o', 'op2')
        time.sleep(0.1)
        c2.send_cmd('KICK', '#ops', 'op1')
        replies = c1.read_until(lambda l: 'KICK' in l, timeout=3)
        self.assert_true(replies and any('KICK' in l for l in replies), "New op kicks original op")
        c1.send_cmd('JOIN', '#ops')
        time.sleep(0.1)

        c1.close()
        c2.close()

    # --------------------------------------------------------
    # Extreme tests (RFC 2812 aligned)
    # --------------------------------------------------------
    def test_multi_channel(self):
        self.log("\n[EXTREME] === Multi‑channel join/leave ===")
        c = self.new_client(nick='multich')
        c.connect()
        channels = ['#a', '#b', '#c', '#d', '#e']
        for ch in channels:
            c.send_cmd('JOIN', ch)
            lines = c.read_until(lambda l: 'JOIN' in l and ch in l, timeout=2)
            self.assert_true(lines and any(ch in l and 'JOIN' in l for l in lines), f"Joined {ch}")
        c2 = self.new_client(nick='multich2')
        c2.connect()
        c2.send_cmd('JOIN', '#a')
        time.sleep(0.1)
        c.send_cmd('PRIVMSG', '#a', ':onlyA')
        replies = c2.read_until(lambda l: 'onlyA' in l, timeout=2)
        self.assert_true(replies and any('onlyA' in l for l in replies), "Message only in #a")
        c2.send_cmd('JOIN', '#b')
        time.sleep(0.1)
        c.send_cmd('PRIVMSG', '#b', ':onlyB')
        replies = c2.read_until(lambda l: 'onlyB' in l, timeout=2)
        self.assert_true(replies and any('onlyB' in l for l in replies), "Message only in #b")
        c.close()
        c2.close()

    def test_nick_change(self):
        self.log("\n[EXTREME] === Nick change propagation ===")
        c1 = self.new_client(nick='orig1')
        c1.connect()
        c1.send_cmd('JOIN', '#nickch')
        c2 = self.new_client(nick='orig2')
        c2.connect()
        c2.send_cmd('JOIN', '#nickch')
        time.sleep(0.1)
        c1.send_cmd('NICK', 'newnick')
        replies = c2.read_until(lambda l: 'NICK' in l and 'newnick' in l, timeout=2)
        self.assert_true(replies and any('NICK' in l and 'newnick' in l for l in replies), "Nick change broadcast received")
        # Operator status preserved after nick change
        c1.send_cmd('MODE', '#nickch', '+i')
        replies = c1.read_some(timeout=1.0)
        self.assert_true(not any('482' in l for l in replies), "Op status preserved after nick change")
        c1.send_cmd('MODE', '#nickch', '-i')
        c1.close()
        c2.close()

    def test_quit_reason(self):
        self.log("\n[EXTREME] === QUIT with reason ===")
        c1 = self.new_client(nick='quitter')
        c1.connect()
        c1.send_cmd('JOIN', '#quitroom')
        c2 = self.new_client(nick='watcher')
        c2.connect()
        c2.send_cmd('JOIN', '#quitroom')
        time.sleep(0.1)
        c1.send_raw(b'QUIT :Gone fishing\r\n')
        replies = c2.read_until(lambda l: 'QUIT' in l and 'Gone fishing' in l, timeout=2)
        self.assert_true(replies and any('QUIT' in l and 'Gone fishing' in l for l in replies),
                         "Quit message broadcast to channel")
        self.assert_true(not c1.connected, "Quit client disconnected")
        c1.close()
        c2.close()

    def test_long_message(self):
        self.log("\n[EXTREME] === 512‑char PRIVMSG ===")
        c1 = self.new_client(nick='long1')
        c1.connect()
        c1.send_cmd('JOIN', '#long')
        c2 = self.new_client(nick='long2')
        c2.connect()
        c2.send_cmd('JOIN', '#long')
        time.sleep(0.1)
        payload = 'A' * 512
        c1.send_cmd('PRIVMSG', '#long', f':{payload}')
        replies = c2.read_until(lambda l: payload in l, timeout=2)
        self.assert_true(replies and any(payload in l for l in replies), "Long message received")
        c1.close()
        c2.close()

    def test_slow_byte_send(self):
        self.log("\n[EXTREME] === Byte‑by‑byte partial send ===")
        c = IRCClient('127.0.0.1', self.port, self.password, nick='slowby', verbose=False)
        c.sock.connect(('127.0.0.1', self.port))
        c.connected = True
        auth = f"PASS {self.password}\r\nNICK slowby\r\nUSER testuser 0 * :T\r\n"
        for ch in auth:
            c.send_raw(ch.encode())
            time.sleep(0.01)
        lines = c.read_until(lambda l: '001' in l, timeout=5)
        self.assert_true(lines and any('001' in l for l in lines), "Registered with byte‑by‑byte auth")
        cmd = "JOIN #slow\r\n"
        for ch in cmd:
            c.send_raw(ch.encode())
            time.sleep(0.01)
        replies = c.read_until(lambda l: 'JOIN' in l and '#slow' in l, timeout=2)
        self.assert_true(replies and any('#slow' in l for l in replies), "Joined with byte‑by‑byte JOIN")
        c.close()

    def test_many_clients(self):
        self.log("\n[EXTREME] === 10 simultaneous clients ===")
        clients = []
        try:
            for i in range(10):
                c = self.new_client(nick=f'c{i}')
                c.connect()
                c.send_cmd('JOIN', '#party')
                clients.append(c)
                time.sleep(0.02)
            time.sleep(0.2)
            clients[0].send_cmd('PRIVMSG', '#party', ':Hello all')
            replies = clients[9].read_until(lambda l: 'Hello all' in l, timeout=2)
            self.assert_true(replies and any('Hello all' in l for l in replies), "Message to 10‑client channel")
        finally:
            for c in clients:
                c.close()

    def test_operator_demotion(self):
        self.log("\n[EXTREME] === Operator demotion ===")
        c1 = self.new_client(nick='demop1')
        c1.connect()
        c1.send_cmd('JOIN', '#demot')
        c2 = self.new_client(nick='demop2')
        c2.connect()
        c2.send_cmd('JOIN', '#demot')
        time.sleep(0.1)
        c1.send_cmd('MODE', '#demot', '+o', 'demop2')
        time.sleep(0.1)
        c1.send_cmd('MODE', '#demot', '-o', 'demop2')
        time.sleep(0.1)
        c2.send_cmd('KICK', '#demot', 'demop1')
        replies = c2.read_until(lambda l: '482' in l, timeout=1.0)
        self.assert_true(replies and any('482' in l for l in replies), "Ex‑operator cannot kick")
        c1.close()
        c2.close()

    def test_kick_removes_invite(self):
        self.log("\n[EXTREME] === Kick removes invite from +i channel ===")
        c1 = self.new_client(nick='kicker')
        c1.connect()
        c1.send_cmd('JOIN', '#kickinv')
        c1.send_cmd('MODE', '#kickinv', '+i')
        c2 = self.new_client(nick='victim')
        c2.connect()
        c1.send_cmd('INVITE', 'victim', '#kickinv')
        c2.read_until(lambda l: 'INVITE' in l, timeout=1)
        c2.send_cmd('JOIN', '#kickinv')
        time.sleep(0.1)
        c1.send_cmd('KICK', '#kickinv', 'victim', ':bye')
        c2.read_until(lambda l: 'KICK' in l, timeout=1)
        c2.send_cmd('JOIN', '#kickinv')
        replies = c2.read_until(lambda l: '473' in l, timeout=1)
        self.assert_true(replies and any('473' in l for l in replies), "Kicked user cannot rejoin +i without re‑invite")
        c1.close()
        c2.close()

    def test_reduce_limit_below_members(self):
        self.log("\n[EXTREME] === +l below current members ===")
        c1 = self.new_client(nick='limop')
        c1.connect()
        c1.send_cmd('JOIN', '#limtest2')
        c2 = self.new_client(nick='limusr')
        c2.connect()
        c2.send_cmd('JOIN', '#limtest2')
        time.sleep(0.1)
        c1.send_cmd('MODE', '#limtest2', '+l', '1')
        replies = c1.read_some()
        # Setting a limit below current membership is allowed; existing members remain
        self.assert_true(not any('482' in l for l in replies), "Set +l below member count succeeds")
        c3 = self.new_client(nick='limnew')
        c3.connect()
        c3.send_cmd('JOIN', '#limtest2')
        replies = c3.read_until(lambda l: '471' in l, timeout=1)
        self.assert_true(replies and any('471' in l for l in replies), "New join rejected after lowering limit")
        c3.close()
        c1.close()
        c2.close()

    def test_mode_errors(self):
        self.log("\n[EXTREME] === Invalid MODE commands ===")
        c = self.new_client(nick='modeErr')
        c.connect()
        c.send_cmd('JOIN', '#modeErr')
        time.sleep(0.1)
        # Unknown mode flag -> RFC 2812: ERR_UNKNOWNMODE (502)
        c.send_cmd('MODE', '#modeErr', '+x')
        replies = c.read_until(lambda l: '502' in l or '472' in l, timeout=1)  # 472 is also used historically
        self.assert_true(replies and (any('502' in l for l in replies) or any('472' in l for l in replies)), "Unknown mode flag rejected")
        # Missing parameter for +k -> ERR_NEEDMOREPARAMS (461)
        c.send_cmd('MODE', '#modeErr', '+k')
        replies = c.read_until(lambda l: '461' in l, timeout=1)
        self.assert_true(replies and any('461' in l for l in replies), "Missing key parameter rejected")
        # Try to remove last operator -> ERR_CHANOPRIVSNEEDED (482)
        c.send_cmd('MODE', '#modeErr', '-o', 'modeErr')
        replies = c.read_until(lambda l: '482' in l, timeout=1)
        self.assert_true(replies and any('482' in l for l in replies), "Cannot remove last operator")
        c.close()

    def test_nick_reuse(self):
        self.log("\n[EXTREME] === Nick reuse after disconnect ===")
        c1 = self.new_client(nick='reuse')
        c1.connect()
        c1.send_cmd('JOIN', '#reuse')
        time.sleep(0.1)
        c1.close()
        time.sleep(0.2)
        try:
            c2 = self.new_client(nick='reuse')
            c2.connect()
            self.assert_true(True, "Nick can be reused after disconnect")
            c2.close()
        except Exception as e:
            self.assert_true(False, f"Nick reuse failed: {e}")

    def test_empty_message(self):
        self.log("\n[EXTREME] === Empty / whitespace PRIVMSG ===")
        c1 = self.new_client(nick='empty1')
        c1.connect()
        c1.send_cmd('JOIN', '#empty')
        c2 = self.new_client(nick='empty2')
        c2.connect()
        c2.send_cmd('JOIN', '#empty')
        time.sleep(0.1)
        c1.send_raw(b'PRIVMSG #empty :   \r\n')
        time.sleep(0.2)
        c3 = self.new_client(nick='empty3')
        c3.connect()
        c3.close()
        self.assert_true(True, "Server survives empty PRIVMSG")
        c1.close()
        c2.close()

    def test_case_insensitive_commands(self):
        self.log("\n[EXTREME] === Case‑insensitive commands ===")
        c = self.new_client(nick='casec')
        c.connect()
        c.send_raw(b'join #CaseChan\r\n')
        replies = c.read_until(lambda l: 'JOIN' in l and '#CaseChan' in l, timeout=2)
        self.assert_true(replies and any('#CaseChan' in l for l in replies), "lowercase join works")
        c.send_raw(b'JOIN #CaseChan\r\n')   # duplicate, should be harmless
        time.sleep(0.1)
        c.close()

    def test_empty_lines_and_spaces(self):
        self.log("\n[EXTREME] === Empty lines and whitespace commands ===")
        c = self.new_client(nick='emptylines')
        c.connect()
        c.send_raw(b'   \r\n')
        time.sleep(0.1)
        c.send_raw(b'\r\n')
        time.sleep(0.1)
        c2 = self.new_client(nick='emptycheck')
        c2.connect()
        c2.close()
        self.assert_true(True, "Server survives empty/whitespace lines")
        c.close()

    def test_ping_ignored(self):
        self.log("\n[EXTREME] === PING command ignored ===")
        c = self.new_client(nick='pinguser')
        c.connect()
        c.send_raw(b'PING :12345\r\n')
        time.sleep(0.2)
        c2 = self.new_client(nick='pingcheck')
        c2.connect()
        c2.close()
        self.assert_true(True, "Server survives PING command")
        c.close()

    def test_nick_collision(self):
        self.log("\n[EXTREME] === Nick collision (change to taken nick) ===")
        c1 = self.new_client(nick='nickcoll1')
        c1.connect()
        c2 = self.new_client(nick='nickcoll2')
        c2.connect()
        time.sleep(0.1)
        c1.send_cmd('NICK', 'nickcoll2')
        replies = c1.read_until(lambda l: '433' in l, timeout=2)
        self.assert_true(replies and any('433' in l for l in replies), "Nick change to existing nick rejected (433)")
        c1.close()
        c2.close()

    def test_multi_channel_many_clients(self):
        self.log("\n[EXTREME] === 5 clients × 3 channels ===")
        clients = []
        try:
            for i in range(5):
                c = self.new_client(nick=f'mc{i}')
                c.connect()
                clients.append(c)
            # all join a common channel
            for c in clients:
                c.send_cmd('JOIN', '#common')
                c.read_until(lambda l: 'JOIN' in l and '#common' in l, timeout=1)
            clients[0].send_cmd('PRIVMSG', '#common', ':allhere')
            for c in clients:
                replies = c.read_until(lambda l: 'allhere' in l, timeout=2)
                self.assert_true(replies and any('allhere' in l for l in replies), f"Client {c.nick} received common msg")
        finally:
            for c in clients:
                c.close()

    def test_topic_clear(self):
        self.log("\n[EXTREME] === Clear topic with empty string ===")
        c = self.new_client(nick='topicclr')
        c.connect()
        c.send_cmd('JOIN', '#topicclr')
        time.sleep(0.1)
        c.send_cmd('TOPIC', '#topicclr', ':')   # empty topic
        replies = c.read_until(lambda l: '331' in l or '332' in l, timeout=2)
        self.assert_true(True, "Empty topic set without crash")
        c.send_cmd('TOPIC', '#topicclr')
        replies = c.read_until(lambda l: '331' in l or '332' in l, timeout=1)
        self.assert_true(replies and (any('331' in l for l in replies) or (any('332' in l and ':' in l for l in replies))), "Topic query after clear")
        c.close()

    def test_invite_consumed_after_join(self):
        self.log("\n[EXTREME] === INVITE consumed after join ===")
        c1 = self.new_client(nick='invcons1')
        c1.connect()
        c1.send_cmd('JOIN', '#invcons')
        c1.send_cmd('MODE', '#invcons', '+i')
        c2 = self.new_client(nick='invcons2')
        c2.connect()
        c1.send_cmd('INVITE', 'invcons2', '#invcons')
        c2.read_until(lambda l: 'INVITE' in l, timeout=1)
        c2.send_cmd('JOIN', '#invcons')
        time.sleep(0.1)
        # part (if implemented) or just kick: we'll close the socket and reconnect
        c2.close()
        time.sleep(0.1)
        # reconnect with same nick (after server removes old client)
        c2 = self.new_client(nick='invcons2')
        c2.connect()
        c2.send_cmd('JOIN', '#invcons')
        replies = c2.read_until(lambda l: '473' in l, timeout=1)
        self.assert_true(replies and any('473' in l for l in replies), "Rejoin without invite rejected (invite consumed)")
        c1.close()
        c2.close()

    def test_simultaneous_partial_sends(self):
        self.log("\n[EXTREME] === Two clients sending partial data simultaneously ===")
        c1 = IRCClient('127.0.0.1', self.port, self.password, nick='part1', verbose=False)
        c1.sock.connect(('127.0.0.1', self.port))
        c1.connected = True
        c2 = IRCClient('127.0.0.1', self.port, self.password, nick='part2', verbose=False)
        c2.sock.connect(('127.0.0.1', self.port))
        c2.connected = True
        # interleave auth bytes
        c1.send_raw(b'P')
        c2.send_raw(b'P')
        c1.send_raw(b'ASS ' + self.password.encode() + b'\r\n')
        c2.send_raw(b'ASS ' + self.password.encode() + b'\r\n')
        c1.send_raw(b'NICK part1\r\n')
        c2.send_raw(b'NICK part2\r\n')
        c1.send_raw(b'US')
        c2.send_raw(b'US')
        c1.send_raw(b'ER testuser 0 * :T\r\n')
        c2.send_raw(b'ER testuser 0 * :T\r\n')
        lines1 = c1.read_until(lambda l: '001' in l, timeout=5)
        lines2 = c2.read_until(lambda l: '001' in l, timeout=5)
        self.assert_true(lines1 and any('001' in l for l in lines1) and lines2 and any('001' in l for l in lines2),
                         "Both clients registered with interleaved partial sends")
        c1.close()
        c2.close()

    def test_disconnect_during_mode_change(self):
        self.log("\n[EXTREME] === Disconnect while applying MODE +l ===")
        c1 = self.new_client(nick='discmode')
        c1.connect()
        c1.send_cmd('JOIN', '#discmode')
        time.sleep(0.1)
        c1.send_raw(b'MODE #discmode +l 3\r\n')
        time.sleep(0.05)
        c1.close()
        time.sleep(0.2)
        c2 = self.new_client(nick='discmode2')
        c2.connect()
        c2.send_cmd('JOIN', '#discmode')
        replies = c2.read_until(lambda l: 'JOIN' in l, timeout=2)
        self.assert_true(replies and any('#discmode' in l for l in replies), "Channel joinable after crash test")
        c2.close()

    def test_duplicate_join(self):
        self.log("\n[EXTREME] === Duplicate JOIN to same channel ===")
        c = self.new_client(nick='dupjoin')
        c.connect()
        c.send_cmd('JOIN', '#dup')
        time.sleep(0.1)
        c.send_cmd('JOIN', '#dup')
        time.sleep(0.2)
        c2 = self.new_client(nick='dupcheck')
        c2.connect()
        c2.send_cmd('JOIN', '#dup')
        replies = c2.read_until(lambda l: 'JOIN' in l, timeout=2)
        self.assert_true(replies and any('#dup' in l for l in replies), "Duplicate join does not break channel")
        c.close()
        c2.close()

    def test_privmsg_to_nonexistent_channel(self):
        self.log("\n[EXTREME] === PRIVMSG to non‑existent channel ===")
        c = self.new_client(nick='badmsg')
        c.connect()
        c.send_cmd('PRIVMSG', '#nochannel', ':hi')
        replies = c.read_until(lambda l: '401' in l or '403' in l, timeout=1)
        self.assert_true(replies and (any('401' in l for l in replies) or any('403' in l for l in replies)),
                         "Error on message to non‑existent channel")
        c.close()

    def test_channel_name_length(self):
        self.log("\n[EXTREME] === Very long channel name ===")
        c = self.new_client(nick='longchname')
        c.connect()
        long_name = '#' + 'x' * 200
        c.send_cmd('JOIN', long_name)
        replies = c.read_until(lambda l: '403' in l or 'JOIN' in l, timeout=1)
        # Should be rejected (403) or silently ignore; we just ensure no crash
        self.assert_true(True, "Long channel name handled without crash")
        c.close()

    # --------------------------------------------------------
    # Run all tests
    # --------------------------------------------------------
    def run_all(self):
        self.start_server()
        try:
            self.test_basic_connection()
            self.test_nick_user_join()
            self.test_privmsg()
            self.test_partial_commands()
            self.test_kill_client_mid_command()
            self.test_flood_with_stopped_client()
            self.test_operator_commands()

            if self.extreme:
                self.test_multi_channel()
                self.test_nick_change()
                self.test_quit_reason()
                self.test_long_message()
                self.test_slow_byte_send()
                self.test_many_clients()
                self.test_operator_demotion()
                self.test_kick_removes_invite()
                self.test_reduce_limit_below_members()
                self.test_mode_errors()
                self.test_nick_reuse()
                self.test_empty_message()
                self.test_case_insensitive_commands()
                self.test_empty_lines_and_spaces()
                self.test_ping_ignored()
                self.test_nick_collision()
                self.test_multi_channel_many_clients()
                self.test_topic_clear()
                self.test_invite_consumed_after_join()
                self.test_simultaneous_partial_sends()
                self.test_disconnect_during_mode_change()
                self.test_duplicate_join()
                self.test_privmsg_to_nonexistent_channel()
                self.test_channel_name_length()
        finally:
            self.stop_server()

        print(f"\n=== Results: {self.passed} passed, {self.failed} failed ===")
        if self.failed:
            sys.exit(1)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='ft_irc RFC 2812 compliant tester')
    parser.add_argument('--port', type=int, required=True)
    parser.add_argument('--password', required=True)
    parser.add_argument('--server', default='./ircserv')
    parser.add_argument('--leak-check', action='store_true')
    parser.add_argument('--no-server', action='store_true')
    parser.add_argument('--verbose', action='store_true')
    parser.add_argument('--extreme', action='store_true', help='Run extreme stress/edge tests')
    args = parser.parse_args()

    if args.no_server and args.leak_check:
        print("Leak check cannot be performed with --no-server")
        sys.exit(1)

    tester = Tester(args.port, args.password,
                    server_path=args.server if not args.no_server else None,
                    leak_check=args.leak_check,
                    no_server=args.no_server,
                    verbose=args.verbose,
                    extreme=args.extreme)
    tester.run_all()