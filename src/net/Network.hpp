#ifndef __NETWORK_HPP__
#define __NETWORK_HPP__

#include <stdio.h>
#include "Serialization.hpp"

class NetConnection {
public:
    FILE* Strm;
    NetConnection(char* host, int port);
    void Close();
    int SockFd;
};

#endif