#include "Serialization.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int BlockingMode = 1;

void VengSetBlockingMode(int Mode) {
    BlockingMode = Mode;
}

void VengWriteByte(int Stream, char C) {
    send(Stream,&C,sizeof(char),0);
}

void VengWriteInt(int Stream, int I) {
    send(Stream,&I,sizeof(int),0);
}

void VengWriteString(int Stream, char* S) {
    size_t stringlength = strlen(S)+1;
    send(Stream,&stringlength,sizeof(size_t),0);
    send(Stream,S,stringlength,0);
}

void VengWriteFloat(int Stream, float F) {
    send(Stream,&F,sizeof(float),0);
}

char VengReadByte(int Stream, char* x) {
    int s = 0;
    if(BlockingMode) {
        while(recv(Stream,x,1,0) != -1) {

        }
    } else {
        s = recv(Stream,x,1,0);
    }
    return s;
}

int VengReadInt(int Stream, int* x) {
    int s = 0;
    if(BlockingMode) {
        while(recv(Stream,x,sizeof(int),0) != -1) {

        }
    } else {
        s = recv(Stream,x,sizeof(int),0);
    }
    return s;
}

float VengReadFloat(int Stream, float* x) {
    int s = 0;
    if(BlockingMode) {
        while(recv(Stream,x,sizeof(float),0) != -1) {

        }
    } else {
        s = recv(Stream,x,sizeof(float),0);
    }
    return s;
}

char* VengReadString(int Stream) {
    char* str;
    size_t strleng = 0;
    while(recv(Stream,&strleng,sizeof(size_t),0) != -1) {

    }
    str = (char*)malloc(strleng);
    while(recv(Stream,&str,sizeof(strleng),0) != -1) {

    }
    return str;
}
