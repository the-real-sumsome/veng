#include <irrlicht/irrlicht.h>
#include "VengEventReceiver.hpp"
#include "management/Console.hpp"

using namespace irr;

// This is the one method that we have to implement
bool VengEventReceiver::OnEvent(const SEvent& event)
{
    // Remember whether each key is down or up
    if (event.EventType == irr::EET_KEY_INPUT_EVENT) 
    {
        // set value in the KeyIsDown array if that key is pressed down
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    } else if (event.EventType == irr::EET_GUI_EVENT) 
    {
        // get id of calling object (for example, if the button was clicked and had an id of 101 the button would be the calling object and the id would be 101)
        s32 id = event.GUIEvent.Caller->getID();
        // get the gui environment
        gui::IGUIEnvironment* env = Context.device->getGUIEnvironment();
        wchar_t* consCmd;
        switch(id) {
            case VC_SUBMIT_BUTTON:
                // submit button was clicked
                if(event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
                    consCmd = (wchar_t*)GlobConsole->edit->getText();
                    GlobConsole->Do(consCmd);
                }
                break;
            case VC_EDIT_BOX:
                // ignore
                break;
            case -1:
                // ignore
                break;
            default:
                GlobConsole->Logf("Unknown action from UI object id %i\n",id);
                break;
        }
    } else if(event.EventType == irr::EET_LOG_TEXT_EVENT) 
    {
        // this is logging
        // switch the log type and then print the correct lil thing
        switch(event.LogEvent.Level) { 
            case irr::ELL_ERROR:
                GlobConsole->Logf("Irrlicht: [ERROR]>%s\n",event.LogEvent.Text);
                break;
            case irr::ELL_WARNING:
                GlobConsole->Logf("Irrlicht: [WARN]>%s\n",event.LogEvent.Text);
                break;
            case irr::ELL_INFORMATION:
                GlobConsole->Logf("Irrlicht: [INFO]>%s\n",event.LogEvent.Text);
                break;
            case irr::ELL_DEBUG:
                GlobConsole->Logf("Irrlicht: [DEBG]>%s\n",event.LogEvent.Text);
                break;
            case irr::ELL_NONE:
                GlobConsole->Logf("Irrlicht: [NONE]>%s\n",event.LogEvent.Text);
                break;
            default:
                GlobConsole->Logf("Irrlicht: [??%i]>%s\n",event.LogEvent.Level,event.LogEvent.Text);
                break;
        }
        return true;
    }

    return false;
}

// This is used to check whether a key is being held down
bool VengEventReceiver::IsKeyDown(EKEY_CODE keyCode) const
{
    return KeyIsDown[keyCode];
}

VengEventReceiver::VengEventReceiver(SAppContext & context) : Context(context)
{
    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
        KeyIsDown[i] = false;
}