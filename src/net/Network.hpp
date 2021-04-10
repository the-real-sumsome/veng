#ifndef __NETWORK_HPP__
#define __NETWORK_HPP__

#include <stdio.h>
#include <irrlicht/irrlicht.h>
#include <asio.hpp>

using asio::ip::tcp;

class NetConnection {
public:
    NetConnection(char* host, char* port);
    void SceneUpdate(irr::IrrlichtDevice* device, void* pev);
    char* GetMOTD();
    void Close();
    int State;
private:
    int Ready;
    tcp::socket* socket;
    char* motd;
    char read_byte();
    char* read_string();
    int read_int();
    int blocking;
};

#endif