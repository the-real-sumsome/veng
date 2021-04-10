#ifndef __NETWORK_HPP__
#define __NETWORK_HPP__

#include <stdio.h>
#include <irrlicht/irrlicht.h>
#include "Serialization.hpp"

class NetConnection {
public:
    FILE* Strm;
    NetConnection(char* host, int port);
    void SceneUpdate(irr::IrrlichtDevice* device);
    void Close();
    int SockFd;
};

#endif