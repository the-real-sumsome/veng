#ifndef __SERIALIZATION_HPP__
#define __SERIALIZATION_HPP__
#include <stdio.h>

namespace VengNet {
    void WriteByte(int Stream, char C);

    void WriteInt(int Stream, int I);

    void WriteString(int Stream, char* S);

    void WriteFloat(int Stream, float F);

    char ReadByte(int Stream);

    int ReadInt(int Stream);

    float ReadFloat(int Stream);

    char* ReadString(int Stream);
}

#endif