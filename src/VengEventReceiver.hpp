#ifndef __INPUT_HPP__
#define __INPUT_HPP__
#include <irrlicht/irrlicht.h>

struct SAppContext
{
    irr::IrrlichtDevice *device;
};

// Veng engine event receiver for irrlicht
class VengEventReceiver : public irr::IEventReceiver
{
public:
    virtual bool OnEvent(const irr::SEvent& event);

    virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;

    VengEventReceiver(SAppContext & context);

private:
    bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
    SAppContext & Context;
};

#endif
