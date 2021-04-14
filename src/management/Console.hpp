#ifndef __CONSOLE_HPP__
#define __CONSOLE_HPP__
#include <irrlicht/irrlicht.h>

enum VengConsoleBtnEnum {
    VC_SUBMIT_BUTTON = 101,
    VC_EDIT_BOX = 102,
};

enum VengInputMode {
    VIC_UNKNOWN,
    VIC_SKBOX,
    VIC_LDPAK,
    VIC_USER,
};

class VengConsole {
public:
    VengConsole(irr::IrrlichtDevice *);
    void Open();
    void Close();
    void Log(char* i);
    void Logf(char* format,...);
    void PrepFinal();
    void Do(wchar_t* cmd);
    void UpdConsoleBounds();
    irr::gui::IGUIStaticText* glog;
    irr::gui::IGUIButton* enter;
    irr::gui::IGUIEditBox* edit;
    irr::gui::IGUIImage* coollogo;
    irr::video::ITexture* coolimg;
    char* LatestLine;
    bool Visbility;
private:
    irr::IrrlichtDevice* device;
    VengInputMode selMode;
    bool waitingForInput;
    bool noImg;
};

extern VengConsole* GlobConsole;

#endif 