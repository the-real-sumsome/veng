#ifndef __VENGUI_HPP__
#define __VENGUI_HPP__
#include <irrlicht/irrlicht.h>
#include <vector>

typedef struct {
    bool visibility;
} venguiinfo_t;

class IVengUiObject {
public:
    IVengUiObject(irr::IrrlichtDevice* device);
    virtual void Init()=0;
    virtual void Render()=0;
    virtual venguiinfo_t GetInfo();
protected:
    irr::IrrlichtDevice* device;
};

class VengUI {
public:
    VengUI(irr::IrrlichtDevice* device);
    void Draw();
private:
    irr::IrrlichtDevice* device;
    std::vector<IVengUiObject*> VengUiObjects;
};

#endif