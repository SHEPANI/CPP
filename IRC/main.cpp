#include "ircserv.hpp"
#include <iostream>

int main(int av, char **arcv)
{
    
    ircserv a;
    int sockfd = a.create_socket();
    std::cout << sockfd;
}