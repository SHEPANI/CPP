// The struct addrinfo is a fundamental C/C++ data structure used for modern,
//  protocol-independent networking. It is primarily used with the getaddrinfo()
//  function to translate hostnames and service names into socket addresses.
//  Required HeadersTo use addrinfo, you must include the correct headers based on your operating system:
// POSIX (Linux/macOS): #include <netdb.h> and #include <sys/socket.h>.
// Windows (Winsock): #include <ws2tcpip.h> (and ensure you link against ws2_32.lib).
// Structure DefinitionThe typical definition of addrinfo includes the following members:

/*
struct addrinfo {
    int              ai_flags;     // AI_PASSIVE, AI_CANONNAME, etc.
    int              ai_family;    // AF_INET, AF_INET6, AF_UNSPEC
    int              ai_socktype;  // SOCK_STREAM, SOCK_DGRAM
    int              ai_protocol;  // IPPROTO_TCP, IPPROTO_UDP
    socklen_t        ai_addrlen;   // Length of ai_addr
    struct sockaddr *ai_addr;      // Binary socket address (sockaddr_in or sockaddr_in6)
    char            *ai_canonname; // Canonical name for host
    struct addrinfo *ai_next;      // Pointer to the next node in the linked list
};
*/
