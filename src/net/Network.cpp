#include "Network.hpp"

#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

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
    int CVersion = VengNet::ReadInt((FILE*)SockFd);
    printf("Server version: %i",CVersion);
    if(CVersion != 1) {
        puts("Warning: Version mismatch");
    }
    VengNet::WriteInt((FILE*)SockFd,1);
}