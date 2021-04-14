#include "VengMod.hpp"
#include <dlfcn.h>
#include <irrlicht/irrlicht.h>
#include "../management/Console.hpp"
#include "../management/CVar.hpp"
#include "../management/EtcGlobals.hpp"

VengMod::VengMod(char* name) {
    soHnd = dlopen(glob::GlobalDevice->getFileSystem()->getAbsolutePath(name).c_str(),RTLD_LAZY);
    if(!soHnd) {
        GlobConsole->Logf("FATAL: Could not open mod %s",name);
    }
}