#include "Server.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include "Serialization.h"

void error(char *msg)
{
    perror(msg);
    exit(1);
}

void VengServer() {
    puts("Veng testing server");
    int sockfd, newsockfd, portno, clilen, n;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    memset(&serv_addr,0,sizeof(sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8364);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");
    puts("listening");
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
acceptloop:
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t*)&clilen);
    if (newsockfd < 0)
        error("ERROR on accept");
    VengSetBlockingMode(1);
    VengWriteInt(newsockfd,1);
    int retVersion;
    VengReadInt(newsockfd,&retVersion);
    if(retVersion != 1) {
        printf("client does not use same version (1 != %i)",retVersion);
    } else {
        printf("client uses same version\n");
    }
    int ready = 0;
    VengReadInt(newsockfd,&ready);
    printf("client ready\n");
    VengWriteInt(newsockfd,1);
    VengWriteString(newsockfd,"Server is closing.");
    printf("sending kill message to %i\n",newsockfd);
    goto acceptloop;
}