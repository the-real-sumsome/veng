#include "../player/Player.hpp"
#include "Network.hpp"
#include "../management/Console.hpp"

#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <netdb.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

using namespace irr;

#ifndef VERSION
#define VERSION 1
#endif
// so it looks better in my editor

NetConnection::NetConnection(char* host, char* port) {
    asio::io_context io;
    tcp::resolver resolver(io);
    tcp::resolver::results_type endpoints = resolver.resolve(host, port);    
    socket = new tcp::socket(io);
    asio::connect(*socket, endpoints);
    char sVersion = read_byte();
    printf("Server running veng version %c",sVersion);
    if(sVersion != VERSION) {
        printf("Warning: Server version (%i) != client version (%i)",sVersion,VERSION);
    }
    motd = "Unknown";
}

void NetConnection::SceneUpdate(irr::IrrlichtDevice* device, void* pev) {
    if(!socket->available()) {
        return;
    }

    char buffer[1];
    size_t bytesRead = asio::read(*socket, asio::buffer(buffer, 1));

    irr::video::IVideoDriver* driver = device->getVideoDriver();
    irr::scene::ISceneManager* scene = device->getSceneManager();
    VengPlayer* tpev = (VengPlayer*)pev;

    char* message;
    char* from;
    char* reason;
    switch(buffer[0]) {
        case 0x00: // Server Info
            motd = read_string();
            GlobConsole->Logf("MOTD: %s\n",motd);
            break;
        case 0x01: // Server Disconnect
            reason = read_string();
            GlobConsole->Logf("Disconnected: %s\n",reason);
            break;
        case 0x02: // Chat Message
            from = read_string();
            message = read_string();
            GlobConsole->Logf("%s: %s",from,message);
            break;
        case 0x03: // Global Message
            message = read_string();
            GlobConsole->Logf("%s",message);
            break;
    }
}

char* NetConnection::GetMOTD() {
    return motd;
}

char NetConnection::read_byte() {
    char buffer[1];
    asio::read(*socket, asio::buffer(buffer, 1));
    return buffer[0];
}

char* NetConnection::read_string() {
    int size = 0;
    asio::read(*socket, asio::buffer(&size, sizeof(int)));
    char* str = (char*)malloc(size+1);
    asio::read(*socket, asio::buffer(str, size));
    return str;
}

int NetConnection::read_int() {
    int buffer = 0;
    asio::read(*socket, asio::buffer(&buffer, sizeof(int)));
    return buffer;
}