#include "Serialization.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void VengWriteByte(int Stream, char C) {
    send(Stream,&C,sizeof(char),0);
}

void VengWriteInt(int Stream, int I) {
    send(Stream,&I,sizeof(int),0);
}

void VengWriteString(int Stream, char* S) {
    size_t stringlength = strlen(S);
    send(Stream,&stringlength,sizeof(size_t),0);
    send(Stream,S,stringlength,0);
}

void VengWriteFloat(int Stream, float F) {
    send(Stream,&F,sizeof(float),0);
}

char VengReadByte(int Stream) {
    char x = 0;
    recv(Stream,&x,1,0);
    return x;
}

int VengReadInt(int Stream) {
    int x = 0;
    recv(Stream,&x,sizeof(int),0);
    return x;
}

float VengReadFloat(int Stream) {
    float x = 0;
    recv(Stream,&x,sizeof(float),0);
    return x;
}

char* VengReadString(int Stream) {
    char* str;
    size_t strleng = 0;
    recv(Stream,&strleng,sizeof(size_t),0);
    str = (char*)malloc(strleng);
    recv(Stream,&strleng,sizeof(size_t),0);
    return str;
}
