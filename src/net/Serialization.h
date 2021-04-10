#ifndef __SERIALIZATION_H__
#define __SERIALIZATION_H__
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

void VengSetBlockingMode(int Mode);

void VengWriteByte(int Stream, char C);

void VengWriteInt(int Stream, int I);

void VengWriteString(int Stream, char* S);

void VengWriteFloat(int Stream, float F);

char VengReadByte(int Stream, char* x);

int VengReadInt(int Stream, int* x);

float VengReadFloat(int Stream, float* x);

char* VengReadString(int Stream);

#ifdef __cplusplus
}
#endif
#endif