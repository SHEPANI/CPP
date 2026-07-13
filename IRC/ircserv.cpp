

#include "ircserv.hpp"

ircserv::ircserv()
{
    port = 8080;
    this->serverSocketFd = this->create_socket();
    this->bind_socket(this->serverSocketFd);
}

int ircserv::create_socket()
{

    return(socket(AF_INET, SOCK_STREAM, 0));
}

int ircserv::bind_socket(int sockfd)
{
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(this->port);
    // bind(sockfd, )
    return 0;
}

