#ifndef __SERIALIZATION_HPP__
#define __SERIALIZATION_HPP__
#include <stdio.h>

namespace VengNet {
    void WriteByte(FILE* Stream, char C);

    void WriteInt(FILE* Stream, int I);

    void WriteString(FILE* Stream, char* S);

    void WriteFloat(FILE* Stream, float F);

    char ReadByte(FILE* Stream);

    int ReadInt(FILE* Stream);

    float ReadFloat(FILE* Stream);

    char* ReadString(FILE* Stream);
}

#endif