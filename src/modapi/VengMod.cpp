#include "VengMod.hpp"
#include <dlfcn.h>
#include <irrlicht/irrlicht.h>
#include "../management/Console.hpp"
#include "../management/CVar.hpp"
#include "../management/EtcGlobals.hpp"

VengMod::VengMod(char* name) {
    soHnd = dlopen(glob::GlobalDevice->getFileSystem()->getAbsolutePath(name).c_str(),RTLD_LAZY);
    if(!soHnd) {
        GlobConsole->Logf("ERROR: Could not open mod %s",name);
    }
}

int VengMod::TryDoCommand(char* cmd) {
    int (*ds)(char*) = (int(*)(char*))dlsym(soHnd,"vengEngineFunc_doCmd");
    return ds(cmd);
}

int VengMod::Tick(pev** pVl) {
    return 0;
}