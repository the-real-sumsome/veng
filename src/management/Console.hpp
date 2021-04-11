#ifndef __CONSOLE_HPP__
#define __CONSOLE_HPP__
#include <irrlicht/irrlicht.h>

enum VengConsoleBtnEnum {
    VC_SUBMIT_BUTTON = 101,
    VC_EDIT_BOX = 102,
};

class VengConsole {
public:
    VengConsole(irr::IrrlichtDevice *);
    void Open();
    void Close();
    void Log(char* i);
    void Logf(char* format,...);
    void Do(wchar_t* cmd);
    irr::gui::IGUIStaticText* glog;
    irr::gui::IGUIButton* enter;
    irr::gui::IGUIEditBox* edit;
    bool Visbility;
private:
    irr::IrrlichtDevice* device;
};

extern VengConsole* GlobConsole;

#endif 