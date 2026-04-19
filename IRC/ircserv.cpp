

#include "ircserv.hpp"

int ircserv::create_socket()
{
    return(socket(AF_INET, SOCK_STREAM, 0));
}