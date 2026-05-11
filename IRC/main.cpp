#include "ircserv.hpp"
#include <iostream>

int main(int av, char **arcv)
{
    
    ircserv a;
    // int sockfd = a.create_socket();
    // int sockbind = a.bind_socket();
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(a.port);
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(sockfd,  (struct sockaddr *)&address, sizeof(address) == -1);
    listen(sockfd, SOMAXCONN);

    // std::cout << sockfd;
}