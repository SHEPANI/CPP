

#include "ircserv.hpp"
#include "ircserv.hpp"

ircserv::ircserv()
{
    port = 8080;
    ip = 0;
}

int ircserv::create_socket()
{
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(this->port);
    return(socket(AF_INET, SOCK_STREAM, 0));
}

int ircserv::bind_socket(int sockfd)
{
    // bind(sockfd, )
}