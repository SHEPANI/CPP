# ft_irc — Internet Relay Chat Server

> *"IRC is a protocol defined in RFC 1459."*  
> An early form of online communication enabling real-time text-based interactions between users in chat rooms or private messages.

---

## What is IRC?

**IRC (Internet Relay Chat)** is a real-time, text-based communication protocol. It was built on top of **TCP/IP**, but not designed to be locked to it — it could potentially run on other network types too (Private LAN, Tor, Radio/Mesh, etc.).

---

## What is RFC?

**RFC (Request for Comments)** are the official technical documents that define the standards, protocols, and guidelines that power the internet and networked systems.

RFCs cover things like:
- How data is transmitted (TCP, UDP, IP)
- How emails work (SMTP)
- How the web works (HTTP)
- Security protocols (TLS, SSH)
- And thousands of other technical specs

---

## Core Components of IRC

### 🖥️ Server

The **backbone of IRC** — handles client connections, manages channels, and relays messages. IRC servers connect to each other in a **tree (spanning tree) shape**, where each server acts as a hub for those below it, forming one big organized network.

**A server is responsible for:**

| Role | Description |
|---|---|
| 🔀 Message Routing | Receives messages and forwards them to the right user or server |
| 👤 User Auth & Registration | Registers nicknames, prevents duplicates, requires passwords |
| 🏠 Channel Management | Creates/manages chat rooms, tracks members, enforces rules |
| 🔒 Permission & Mode Control | Manages operator status, user/channel modes |
| 🗺️ Network Tracking | Maintains a map of all connected servers and users |
| 📢 Broadcasting | Sends system messages, join/quit announcements |
| ⚡ Ping / Keepalive | Pings clients regularly; disconnects unresponsive ones |
| 🚫 Enforcing Rules | Kills misbehaving connections, bans IPs/hostnames |

---

### 👤 Clients

A **client** is anything connecting to a server that is **not another server** — basically the user's side of IRC (your chat app or program).

**Client identification:**
- Every client has a **unique nickname** with a max of **9 characters**
- No two users can share the same nickname

**What the server stores about each client:**

| Info | Description |
|---|---|
| 🖥️ Hostname | The real name of the machine the client is running on |
| 👤 Username | The user's name on that machine |
| 🔗 Connected Server | Which server the client is connected to |

---

### 💬 Channels

Public or private **chat rooms** where users communicate.  
Examples: `#general`, `#42network`, `&local`

---

### ⌨️ Commands

Text-based instructions used to interact with the server.  
Examples: `JOIN`, `PRIVMSG`, `NICK`, `KICK`, `TOPIC`, `MODE`

---

## Building the Server

### What is Socket Programming?

A **socket** is an endpoint for communication between two machines over a network. It allows a client and a server to establish a connection and exchange data. Sockets support both:
- **TCP** — reliable, connection-based
- **UDP** — fast, connectionless

### What is an Endpoint?

An **endpoint** is the specific point where communication starts or ends in a network connection.

```
You (endpoint 1) <----connection----> Server (endpoint 2)
```

In networking terms, an endpoint is identified by:

```
IP Address + Port = Endpoint
```

Example:
```
192.168.1.11:8080
```

| Part | Meaning |
|---|---|
| IP Address | Which machine on the network |
| Port | Which specific program/service on that machine |

---

## Resources

- [RFC 1459 — Internet Relay Chat Protocol](https://datatracker.ietf.org/doc/html/rfc1459)
- [RFC 2810 — IRC Architecture](https://datatracker.ietf.org/doc/html/rfc2810)
- [RFC 2811 — IRC Channel Management](https://datatracker.ietf.org/doc/html/rfc2811)
- [RFC 2812 — IRC Client Protocol](https://datatracker.ietf.org/doc/html/rfc2812)
- [RFC 2813 — IRC Server Protocol](https://datatracker.ietf.org/doc/html/rfc2813)