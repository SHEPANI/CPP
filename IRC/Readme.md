# IRC (Internet Relay Chat)

> "IRC is a protocol defined in RFC 1459."

IRC is the earliest form of online communication,
enabling real-time text-based interactions
between users in chat rooms or private messages.
We built IRC on top of TCP/IP, but we didn't design it in a way that forces it to stay there — it could potentially work on other network types too (Private LAN, Tor, Radio/Mesh).

---

## RFC — Request for Comments

RFCs are the official technical documents that define the standards,
protocols, and guidelines that power the internet and networked systems.

RFCs cover things like:
- How data is transmitted (TCP, UDP, IP)
- How emails work (SMTP)
- How the web works (HTTP)
- Security protocols (TLS, SSH)
- And thousands of other technical specs

---

## IRC Protocol Core Components

### Server

The backbone of IRC, handling client connections, managing channels, and relaying messages. IRC servers connect to each other in a tree shape, where each server acts as a hub for those below it, forming one big organized network:
- Lets clients (users) connect and talk to each other.
- Lets other servers connect to it, building a larger network.

So an IRC server does things like: handling client connections, managing channels, and relaying messages....

**1. Message Routing**
- When you send a message, your client doesn't send it directly to other users
- The server receives it and forwards it to the right place
- If the recipient is on another server, your server passes it along the tree

**2. User Authentication & Registration**
- The server checks and registers your nickname when you connect
- It makes sure no two users have the same nickname on the network
- It can require passwords to connect

**3. Channel Management**
- Servers create and manage chat rooms (channels)
- They track who is inside each channel
- They enforce channel rules like bans, invite-only, password-protected rooms

**4. Permission & Mode Control**
- Servers enforce user modes (are you an operator? are you invisible?)
- They enforce channel modes (is the channel moderated? limited users?)
- They give or remove operator privileges (@ status)

**5. Keeping Track of the Network**
- Each server maintains a map of the whole IRC network
- It knows which servers are connected and which users are where
- If a server disconnects, it updates the rest of the network

**6. Broadcasting Announcements**
- Server sends system messages to users (welcome messages, errors, notices)
- It broadcasts events like "User X has joined" or "Server Y has disconnected"

**7. Enforcing Rules / Killing Connections**
- Servers can kill (forcefully disconnect) misbehaving users
- They can ban IPs or hostnames from connecting
- Operators on the server level can manage the entire network

**8. Ping / Keepalive**
- Servers regularly ping clients to check if they are still connected
- If a client doesn't respond → server drops the connection
- This keeps the network clean from ghost/dead connections

---

### Clients

A client is anything connecting to a server that is not another server — basically, it's the user's side of IRC (your chat app/program).

**How is each client identified?**
Every client has a unique nickname with a max of 9 characters — no two users can have the same one.

**What info does the server store about each client?**
The server must know 3 things about every connected client:
- 🖥️ Host Name — The real name of the machine the client is running on
- 👤 Username — The user's name on that machine
- 🔗 Connected Server — Which server they are connected to

So: A client is any non-server connection, identified by a unique 9-character nickname, and the server tracks their hostname, username, and which server they're on.

---

### Channels

Public or private chat rooms where users can communicate.

---

### Commands

Text-based instructions like `/join`, `/msg`, and `/nick`.

---

## Building the Server

To create a server we need to use socket programming.

**What is Socket Programming?**
A socket is an endpoint for communication between two machines over a network.
In network programming, a socket allows you to establish a connection between a client and a server,
enabling them to send and receive data. Sockets provide the interface for both network
communication protocols (such as TCP and UDP) and local interprocess communication (IPC).

**What is an endpoint?**
An endpoint is a specific point where communication starts or ends in a network connection.

```
You (endpoint 1) <----call----> Friend (endpoint 2)
```

In networking terms, an endpoint is identified by two things:

```
IP Address + Port --> endpoint
```

Example: `192.168.1.1:8080`

- **IP Address** → which machine on the network
- **Port** → which specific program/service on that machine