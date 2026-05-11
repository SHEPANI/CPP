#include <sys/socket.h>
#include <netinet/in.h>


class ircserv
{
    public:
        int port;
        int ip;
    public:
        ircserv(){};
        ~ircserv(){};
        // ircserv(){};
        int create_socket();
        int bind_socket(int sockfd);
};

class sockinfo 
{
    public:
        sa_family_t i ;
};