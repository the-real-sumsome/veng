#include "../player/Player.hpp"
#include "Network.hpp"

#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>

using namespace irr;

NetConnection::NetConnection(char* host, int port) {
    SockFd = socket(AF_INET,SOCK_STREAM,0);
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
    if (connect(SockFd,(struct sockaddr*)(&serv_addr),sizeof(serv_addr)) < 0)
        puts("Error: couldnt connect");
    int CVersion = VengReadInt(SockFd);
    printf("Server version: %i",CVersion);
    if(CVersion != 1) {
        puts("Warning: Version mismatch");
    }
    VengWriteInt(SockFd,1);
}

void NetConnection::SceneUpdate(irr::IrrlichtDevice* device, void* pev) {
    int cmd;
    VengPlayer* tpev = (VengPlayer*)pev;
    recv(SockFd,&cmd,sizeof(cmd),MSG_PEEK);
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
            device->getSceneManager()->addSkyBoxSceneNode(
                device->getVideoDriver()->getTexture(VengReadString(SockFd)),
                device->getVideoDriver()->getTexture(VengReadString(SockFd)),
                device->getVideoDriver()->getTexture(VengReadString(SockFd)),
                device->getVideoDriver()->getTexture(VengReadString(SockFd)),
                device->getVideoDriver()->getTexture(VengReadString(SockFd)),
                device->getVideoDriver()->getTexture(VengReadString(SockFd)));
            break;
        case 5: // force player resync
            tpev->SyncNet(*this);
            break;
        default:
            printf("unknown command? %i\n",cmd);
            break;
    }
}