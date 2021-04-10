#include "Server.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

void VengServer() {
    puts("Veng server");
}