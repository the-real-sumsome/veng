#ifndef __MOD_HPP__
#define __MOD_HPP__

#include <irrlicht/irrlicht.h>
#include <chaiscript/chaiscript.hpp>

using namespace irr;

class VengMod {
public:
    core::stringw modName; 
    core::stringw modRealName; // internal
    VengMod(core::stringw mod);
protected:
    int initMod();
    chaiscript::ChaiScript* chai;
    io::IFileSystem* fs;
};

#endif