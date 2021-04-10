#include <cstdlib>
#include "VengMod.hpp"

int VengMod::initMod() {
    io::IReadFile* f = fs->createAndOpenFile("chai/mod.ven");
    char* strd = (char*)std::malloc(f->getSize());
    f->read(strd,f->getSize());
    chai->add_global(chaiscript::Boxed_Value("veng1"),"vengversion");
    chai->eval(strd,chaiscript::Exception_Handler(),"mod.ven.log");

    return 0;
}