#include "Console.hpp"
#include <stdarg.h>

VengConsole* GlobConsole = 0;

VengConsole::VengConsole(irr::IrrlichtDevice* device) {
    this->device = device;
    irr::core::dimension2du screensize = device->getVideoDriver()->getScreenSize();
    glog = device->getGUIEnvironment()->addStaticText(L"Veng console\n",irr::core::recti(0,0,screensize.Width,500),true,true);
    glog->setDrawBackground(true);
    glog->setBackgroundColor(irr::video::SColor(255,255,255,255));
    glog->setVisible(false);
}

void VengConsole::Log(char* log) {
    irr::core::stringw tmp = irr::core::stringw(glog->getText());
    tmp += log;
    glog->setText(tmp.c_str());
    printf("CONSOLE: %s",log);
}

void VengConsole::Logf(char* format,...) {
    va_list args;
    char* txt = (char*)malloc(255);
    va_start(args,format);
    vsprintf(txt,format,args);
    va_end(args);
    Log(txt);
    free(txt);
}

void VengConsole::Open() {
    glog->setVisible(true);
    device->getGUIEnvironment()->getRootGUIElement()->bringToFront(glog);
}

void VengConsole::Close() {
    glog->setVisible(false);
}