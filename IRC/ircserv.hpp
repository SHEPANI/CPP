#include <sys/socket.h>


class ircserv
{
    public:
        ircserv(){};
        ~ircserv(){};
        // ircserv(){};
        int create_socket();
};

class sockinfo 
{
    public:
        sa_family_t
};