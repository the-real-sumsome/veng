#ifndef __SERIALIZATION_H__
#define __SERIALIZATION_H__
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

void VengWriteByte(int Stream, char C);

void VengWriteInt(int Stream, int I);

void VengWriteString(int Stream, char* S);

void VengWriteFloat(int Stream, float F);

char VengReadByte(int Stream);

int VengReadInt(int Stream);

float VengReadFloat(int Stream);

char* VengReadString(int Stream);

#ifdef __cplusplus
}
#endif
#endif