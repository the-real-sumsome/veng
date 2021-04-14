#ifndef __VENGMOD_HPP__
#define __VENGMOD_HPP__
#include "C_VengMod.h"

class VengMod {
public:
    VengMod(char* name);
    int TryDoCommand(char* cmd);
    int Tick(pev** pvL);
private:
    void *soHnd;
};

#endif