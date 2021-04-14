#include "Console.hpp"
#include "CVar.hpp"
#include "EtcGlobals.hpp"
#include <stdarg.h>

VengConsole* GlobConsole = 0;

VengConsole::VengConsole(irr::IrrlichtDevice* device) {
    puts("make console");
    this->device = device;
    irr::gui::IGUISkin* skin = device->getGUIEnvironment()->getSkin();    
    irr::core::dimension2du screensize = device->getVideoDriver()->getScreenSize();
    // create the general log stuff
    // this is the text box that shows the consolelog
    glog = device->getGUIEnvironment()->addStaticText(L"Veng console\n",irr::core::recti(0,32,screensize.Width,32+screensize.Height/2),true,true);
    glog->setDrawBackground(true);
    glog->setBackgroundColor(irr::video::SColor(127,255,255,255));
    glog->setVisible(false);
    glog->setDrawBorder(true);
    // this is the Submit button for submitting commands from the Command text bar
    enter = device->getGUIEnvironment()->addButton(irr::core::recti(0,10,100,32),device->getGUIEnvironment()->getRootGUIElement(),VC_SUBMIT_BUTTON,L"Submit",L"Submit prompt and execute");
    // this is the Command text bar which you write commands into, then submit with the Submit button
    edit = device->getGUIEnvironment()->addEditBox(L"help",irr::core::recti(100,10,screensize.Width,32),true,device->getGUIEnvironment()->getRootGUIElement(),VC_EDIT_BOX);
    edit->setVisible(false);
    enter->setVisible(false);
    edit->setToolTipText(L"Command to execute");
    glog->setToolTipText(L"Console log");
    LatestLine = (char*)malloc(1);
    Visbility = false;
}

void VengConsole::PrepFinal() {
    // this finishes preparing since the console loads before filesystem archives (rsc, ../rsc, etc) are actually loaded
    // grab the screensize for doing anchors since we dont store it (see VengConsole::UpdConsoleBounds for more info)
    irr::core::dimension2du screensize = device->getVideoDriver()->getScreenSize();
    // load texture for first time
    coolimg = device->getVideoDriver()->getTexture("tex/veng.png");
    if(!coolimg) {
        // if it doesnt load set noImg to true and never try again
        noImg = true;
    } else {
        // if it does load set the coollogo IGUIImage* thingie to have that image
        irr::core::dimension2du imgSize = coolimg->getSize();
        coollogo = device->getGUIEnvironment()->addImage(irr::core::recti(screensize.Width-imgSize.Width,32,screensize.Width,imgSize.Height+32));
        coollogo->setImage(coolimg);
        coollogo->setVisible(false);
    }
}

// raw log to console
void VengConsole::Log(char* log) {
    // log string
    irr::core::stringw tmp = irr::core::stringw(log);
    free(LatestLine);
    LatestLine = (char*)malloc(strlen(log)+1);
    memcpy(LatestLine,log,strlen(log)+1);
    tmp += glog->getText();
    glog->setText(tmp.c_str());
    printf("CONSOLE: %s",log);
}

// vprintf log to console
void VengConsole::Logf(char* format,...) {
    // log string formatted like vprintf();
    va_list args;
    char* txt = (char*)malloc(255);
    va_start(args,format);
    vsprintf(txt,format,args);
    va_end(args);
    Log(txt);
    free(txt);
}

void VengConsole::UpdConsoleBounds() {
    // this manages updating the console when the screen is resized
    // it removes all previous ui elements and replaces them with new ones
    irr::core::dimension2du screensize = device->getVideoDriver()->getScreenSize();
    irr::core::stringw logA = irr::core::stringw(glog->getText()); // glog->getText() would return nil after we do glog->remove() so we must store a copy of that in logA for when we recreate glog
    glog->remove();
    enter->remove();
    edit->remove();
    coollogo->remove();
    // recreate old ui elements
    glog = device->getGUIEnvironment()->addStaticText(logA.c_str(),irr::core::recti(0,32,screensize.Width,32+screensize.Height/2),true,true);
    enter = device->getGUIEnvironment()->addButton(irr::core::recti(0,10,100,32),device->getGUIEnvironment()->getRootGUIElement(),VC_SUBMIT_BUTTON,L"Submit",L"Submit prompt and execute");
    edit = device->getGUIEnvironment()->addEditBox(L"help",irr::core::recti(100,10,screensize.Width,32),true,device->getGUIEnvironment()->getRootGUIElement(),VC_EDIT_BOX);
    glog->setDrawBackground(true);
    glog->setBackgroundColor(irr::video::SColor(127,255,255,255));    
    glog->setVisible(false);
    edit->setVisible(false);
    glog->setDrawBorder(true);
    enter->setVisible(false);
    // since the fs archives have already been loaded we can do this
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
    // opens the console and brings everything to front
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
    // hides the console
    glog->setVisible(false);
    enter->setVisible(false);
    edit->setVisible(false);
    coollogo->setVisible(false);
    Visbility = false;
}

void VengConsole::Do(wchar_t* cmd) {
    // this is the command parser
    if(!waitingForInput) {
        const char output[256] = {};
        // convert wide characters (16 bit chars) to normal characters (8 bit chars)
        wcstombs((char*)output,cmd,sizeof(output));
        Logf(">%s\n",output);
        // list loaded filesystem archives
        if(strcmp(output,"fspaks")==0) {
            int count = device->getFileSystem()->getFileArchiveCount();
            Logf("%i archives loaded\n",count);
            for(int i = 0; i<count; i++) {
                Logf("archive: %s\n", device->getFileSystem()->getFileArchive(i)->getFileList()->getPath().c_str());
            }
        } else if(strcmp(output,"help")==0) { // list allcommands
            Logf("help\nfspaks\nskbox\nldpak\ncvars\nquit\n");
        } else if(strcmp(output,"skbox")==0) { // create skybox from name
            Logf("enter skybox name\n");
            waitingForInput = true;
            selMode = VIC_SKBOX;
        } else if(strcmp(output,"ldpak")==0) { // load filesystem archive
            Logf("enter pack location\n");
            waitingForInput = true;
            selMode = VIC_LDPAK;
        } else if(strcmp(output,"cvars")==0) { // list cvars, their name, type and pointer
            std::vector<VengManagement::cvar_entry*> cvars = GlobalCVars->Get_Cvars();
            for(int i = 0; i<cvars.size(); i++) {
                if(cvars[i]->ok) {
                    Logf("cvar: %s@%p, type = %i\n",cvars[i]->name->c_str(),cvars[i]->data,cvars[i]->type);
                } else {
                    Logf("cvar not ok?\n");
                }
            }
        } else if(strcmp(output,"quit")==0) { // exit veng
            device->drop();
            exit(0);
        } else {
            if(glob::GlobalMod != 0) {
                glob::GlobalMod->TryDoCommand((char*)output); // try seing what the mod does with it
            } else {
                puts("Unknown command"); // /shrug
            }
        }
    } else {
        // this is when we set input mode on
        // since i dont want to deal with tokenizing the input string we do this
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
            case VIC_USER:
                waitingForInput = glob::GlobalMod->TryDoCommand((char*)output);
                break;
        }
    }
}