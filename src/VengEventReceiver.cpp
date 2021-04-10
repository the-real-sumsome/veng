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
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    } else if (event.EventType == irr::EET_GUI_EVENT) 
    {
        s32 id = event.GUIEvent.Caller->getID();
        gui::IGUIEnvironment* env = Context.device->getGUIEnvironment();

    } else if(event.EventType == irr::EET_LOG_TEXT_EVENT) 
    {
        GlobConsole->Logf("[%i]>%s\n",event.LogEvent.Level,event.LogEvent.Text);
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