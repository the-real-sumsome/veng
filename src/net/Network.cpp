#include "../player/Player.hpp"
#include "Network.hpp"

#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <netdb.h>
#include <time.h>

using namespace irr;

NetConnection::NetConnection(char* host, int port) {
    SockFd = socket(AF_INET,SOCK_NONBLOCK,0);
    if(SockFd < 0) {
        puts("Error: couldnt open socket");
    }
    struct sockaddr_in serv_addr;
    struct hostent *server;
    server = gethostbyname(host);
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memccpy((char *)&serv_addr.sin_addr.s_addr,
        (char *)server->h_addr,
        server->h_length,1);
    serv_addr.sin_port = htons(port);
    inet_pton(AF_INET, host, &serv_addr.sin_addr);
    if (connect(SockFd,(struct sockaddr*)(&serv_addr),sizeof(serv_addr)) < 0)
        puts("Error: couldnt connect");
    int CVersion = 0;
    VengReadInt(SockFd,&CVersion);
    printf("Server version: %i",CVersion);
    if(CVersion != 1) {
        puts("Warning: Version mismatch");
    }
    VengWriteInt(SockFd,1);
    State = 1;
}

void NetConnection::SceneUpdate(irr::IrrlichtDevice* device, void* pev) {
    VengSetBlockingMode(0);
    int cmd;
    int retl = recv(SockFd,&cmd,sizeof(cmd),0);
    if(retl == -1) {
        VengSetBlockingMode(1);
        return;
    }
    VengSetBlockingMode(1);
    irr::video::IVideoDriver* driver = device->getVideoDriver();
    irr::scene::ISceneManager* scene = device->getSceneManager();
    VengPlayer* tpev = (VengPlayer*)pev;
    printf("Doing command %i",cmd);
    time_t now;
    char* reason;
    char* from;
    char* message;
    char* messageglob;
    localtime(&now);
    switch(cmd) {
        case 0: // heartbeat/get time
            VengWriteInt(SockFd,(int)now);
            break;
        case 1: // kick/disconnect
            reason = VengReadString(SockFd);
            printf("Disconnected: %s\n",reason);
            State = 0;
            break;
        case 2: // chat
            from = VengReadString(SockFd);
            message = VengReadString(SockFd);
            printf("Message from %s: %s",message);
            break;
        case 3: // globchat
            messageglob = VengReadString(SockFd);
            printf("Globmessage: %s",messageglob);
            break;
        case 4: // load new skybox
            scene->addSkyBoxSceneNode(
                driver->getTexture(VengReadString(SockFd)),
                driver->getTexture(VengReadString(SockFd)),
                driver->getTexture(VengReadString(SockFd)),
                driver->getTexture(VengReadString(SockFd)),
                driver->getTexture(VengReadString(SockFd)),
                driver->getTexture(VengReadString(SockFd)));
            break;
        case 5: // request player resync
            tpev->SyncNet(*this);
            break;
        default:
            printf("unknown command? %i\n",cmd);
            break;
    }
}