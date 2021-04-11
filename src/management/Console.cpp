#include "Console.hpp"
#include <stdarg.h>

VengConsole* GlobConsole = 0;

VengConsole::VengConsole(irr::IrrlichtDevice* device) {
    puts("make console");
    this->device = device;
    irr::gui::IGUISkin* skin = device->getGUIEnvironment()->getSkin();    
    irr::core::dimension2du screensize = device->getVideoDriver()->getScreenSize();
    glog = device->getGUIEnvironment()->addStaticText(L"Veng console\n",irr::core::recti(0,32,screensize.Width,32+screensize.Height/2),true,true);
    glog->setDrawBackground(true);
    glog->setBackgroundColor(irr::video::SColor(255,255,255,255));
    glog->setVisible(false);
    enter = device->getGUIEnvironment()->addButton(irr::core::recti(0,10,100,32),device->getGUIEnvironment()->getRootGUIElement(),VC_SUBMIT_BUTTON,L"Submit",L"Submit prompt and execute");
    edit = device->getGUIEnvironment()->addEditBox(L"help",irr::core::recti(100,10,screensize.Width,32),true,device->getGUIEnvironment()->getRootGUIElement(),VC_EDIT_BOX);
    edit->setVisible(false);
    enter->setVisible(false);
    edit->setToolTipText(L"Command to execute");
    glog->setToolTipText(L"Console log");
    Visbility = false;
}

void VengConsole::Log(char* log) {
    irr::core::stringw tmp = irr::core::stringw(log);
    tmp += glog->getText();
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
    enter->setVisible(true);
    edit->setVisible(true);
    device->getGUIEnvironment()->getRootGUIElement()->bringToFront(glog);
    glog->bringToFront(enter);
    glog->bringToFront(edit);
    Visbility = true;
}

void VengConsole::Close() {
    glog->setVisible(false);
    enter->setVisible(false);
    edit->setVisible(false);
    Visbility = false;
}

void VengConsole::Do(wchar_t* cmd) {
    const char output[256] = {};
    wcstombs((char*)output,cmd,sizeof(output));
    Logf(">%s\n",output);
    if(strcmp(output,"fspaks")==0) {
        int count = device->getFileSystem()->getFileArchiveCount();
        Logf("%i archives loaded\n",count);
        for(int i = 0; i<count; i++) {
            Logf("archive: %s\n", device->getFileSystem()->getFileArchive(i)->getFileList()->getPath().c_str());
        }
    } else if(strcmp(output,"help")==0) {
        Logf("help\nfspaks\n");
    } else {
        puts("Unknown starting command, going as usual");
    }
}