#ifndef __CONSOLE_HPP__
#define __CONSOLE_HPP__
#include <irrlicht/irrlicht.h>

enum
{
    CGUI_CONSOLE_CLOSE_BTN = 101,
};

class VengConsole {
public:
    VengConsole(irr::IrrlichtDevice *);
    void Open();
    void Close();
    void Log(char* i);
    void Logf(char* format,...);
private:
    irr::IrrlichtDevice* device;
    irr::gui::IGUIStaticText* glog;
};

extern VengConsole* GlobConsole;

#endif 