#include "ircserv.hpp"
#include <iostream>
#include <arpa/inet.h>

int main(int av, char **arcv)
{
    


    ircserv a;
    // a.port =  8080;
    // int sockfd = a.create_socket();
    // int sockbind = a.bind_socket();
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(a.port);
    address.sin_addr.s_addr = INADDR_ANY;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(sockfd,  (struct sockaddr *)&address, sizeof(address) == -1);    
    std::cout << "port : " << ntohs(address.sin_port) << "\n addtype" << address.sin_family<<"\n" ;
    std::cout  << "ip : " << inet_ntoa(address.sin_addr)<< "\n";

    while (1)
    {
        listen(sockfd, SOMAXCONN);
    
        // std::cout << sockfd;
    }
}
