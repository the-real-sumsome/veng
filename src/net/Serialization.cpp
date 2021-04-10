#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "Serialization.hpp"

using namespace VengNet;

void WriteByte(FILE* Stream, char C) {
    fwrite(&C,sizeof(char),1,Stream);
}

void WriteInt(FILE* Stream, int I) {
    fwrite(&I,sizeof(int),1,Stream);
}

void WriteString(FILE* Stream, char* S) {
    size_t stringlength = strlen(S);
    fwrite(&stringlength,sizeof(size_t),1,Stream);
    fwrite(S,stringlength,1,Stream);
}

void WriteFloat(FILE* Stream, float F) {
    fwrite(&F,sizeof(float),1,Stream);
}

char ReadByte(FILE* Stream) {
    char x = 0;
    fread(&x,1,1,Stream);
    return x;
}

int ReadInt(FILE* Stream) {
    int x = 0;
    fread(&x,sizeof(int),1,Stream);
    return x;
}

float ReadFloat(FILE* Stream) {
    float x = 0;
    fread(&x,sizeof(float),1,Stream);
    return x;
}

char* ReadString(FILE* Stream) {
    char* str;
    size_t strleng = 0;
    fread(&strleng,sizeof(size_t),1,Stream);
    str = (char*)malloc(strleng);
    fread(&str,strleng,1,Stream);
    return str;
}