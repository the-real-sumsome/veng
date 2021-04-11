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
    glog->setBackgroundColor(irr::video::SColor(127,255,255,255));
    glog->setVisible(false);
    glog->setDrawBorder(true);
    enter = device->getGUIEnvironment()->addButton(irr::core::recti(0,10,100,32),device->getGUIEnvironment()->getRootGUIElement(),VC_SUBMIT_BUTTON,L"Submit",L"Submit prompt and execute");
    edit = device->getGUIEnvironment()->addEditBox(L"help",irr::core::recti(100,10,screensize.Width,32),true,device->getGUIEnvironment()->getRootGUIElement(),VC_EDIT_BOX);
    edit->setVisible(false);
    enter->setVisible(false);
    edit->setToolTipText(L"Command to execute");
    glog->setToolTipText(L"Console log");
    LatestLine = (char*)malloc(1);
    Visbility = false;
}

void VengConsole::PrepFinal() {
    irr::core::dimension2du screensize = device->getVideoDriver()->getScreenSize();
    coolimg = device->getVideoDriver()->getTexture("tex/veng.png");
    if(!coolimg) {
        noImg = true;
    } else {
        irr::core::dimension2du imgSize = coolimg->getSize();
        coollogo = device->getGUIEnvironment()->addImage(irr::core::recti(screensize.Width-imgSize.Width,32,screensize.Width,imgSize.Height+32));
        coollogo->setImage(coolimg);
        coollogo->setVisible(false);
    }
}

void VengConsole::Log(char* log) {
    irr::core::stringw tmp = irr::core::stringw(log);
    free(LatestLine);
    LatestLine = (char*)malloc(strlen(log)+1);
    memcpy(LatestLine,log,strlen(log)+1);
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

void VengConsole::UpdConsoleBounds() {
    irr::core::dimension2du screensize = device->getVideoDriver()->getScreenSize();
    irr::core::stringw logA = irr::core::stringw(glog->getText());
    glog->remove();
    enter->remove();
    edit->remove();
    coollogo->remove();
    glog = device->getGUIEnvironment()->addStaticText(logA.c_str(),irr::core::recti(0,32,screensize.Width,32+screensize.Height/2),true,true);
    enter = device->getGUIEnvironment()->addButton(irr::core::recti(0,10,100,32),device->getGUIEnvironment()->getRootGUIElement(),VC_SUBMIT_BUTTON,L"Submit",L"Submit prompt and execute");
    edit = device->getGUIEnvironment()->addEditBox(L"help",irr::core::recti(100,10,screensize.Width,32),true,device->getGUIEnvironment()->getRootGUIElement(),VC_EDIT_BOX);
    glog->setDrawBackground(true);
    glog->setBackgroundColor(irr::video::SColor(127,255,255,255));    
    glog->setVisible(false);
    edit->setVisible(false);
    glog->setDrawBorder(true);
    enter->setVisible(false);
    if(!noImg) {
        irr::core::dimension2du imgSize = coolimg->getSize();
        coollogo = device->getGUIEnvironment()->addImage(irr::core::recti(screensize.Width-imgSize.Width,32,screensize.Width,imgSize.Height+32));
        coollogo->setImage(coolimg);
        coollogo->setColor(irr::video::SColor(65,255,255,255));
        coollogo->setVisible(false);
    }
    Visbility = false;
}

void VengConsole::Open() {
    glog->setVisible(true);
    enter->setVisible(true);
    edit->setVisible(true);
    coollogo->setVisible(true);
    glog->bringToFront(coollogo);
    device->getGUIEnvironment()->getRootGUIElement()->bringToFront(glog);
    glog->bringToFront(enter);
    glog->bringToFront(edit);
    Visbility = true;
}

void VengConsole::Close() {
    glog->setVisible(false);
    enter->setVisible(false);
    edit->setVisible(false);
    coollogo->setVisible(false);
    Visbility = false;
}

void VengConsole::Do(wchar_t* cmd) {
    if(!waitingForInput) {
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
        } else if(strcmp(output,"skbox")==0) {
            Logf("enter skybox name\n");
            waitingForInput = true;
            selMode = VIC_SKBOX;
        } else if(strcmp(output,"ldpak")==0) {
            Logf("enter pack location\n");
            waitingForInput = true;
            selMode = VIC_LDPAK;
        } else {
            puts("Unknown starting command, going as usual");
        }
    } else {
        const char output[256] = {};
        wcstombs((char*)output,cmd,sizeof(output));
        Logf("?%s\n",output);
        switch(selMode) {
            default:
            case VIC_UNKNOWN:
                Log("try that one again\n");
                waitingForInput = false;
                break;
            case VIC_SKBOX:
                device->getSceneManager()->addSkyBoxSceneNode(
                    device->getVideoDriver()->getTexture("tex/sky/d3.png"),
                    device->getVideoDriver()->getTexture("tex/sky/d2.png"),
                    device->getVideoDriver()->getTexture("tex/sky/d4.png"),
                    device->getVideoDriver()->getTexture("tex/sky/d5.png"),
                    device->getVideoDriver()->getTexture("tex/sky/d0.png"),
                    device->getVideoDriver()->getTexture("tex/sky/d1.png")); // ill make it use the name later
                waitingForInput = false;
                break;
            case VIC_LDPAK:
                device->getFileSystem()->addFileArchive(output);
                Logf("attempted to load pak %s\n",output);
                waitingForInput = false;
                break;
        }
    }
}