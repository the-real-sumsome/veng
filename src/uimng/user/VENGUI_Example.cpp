#include "VENGUI_Example.hpp"

namespace vengui {
    example::example(irr::IrrlichtDevice* device) : IVengUiObject(device) {

    }
    void example::Init() {

    }
    void example::Render() {
        device->getVideoDriver()->draw3DLine(irr::core::vector3df(0,0,0),irr::core::vector3df(100,100,100));
    }
    venguiinfo_t example::GetInfo() {
        venguiinfo_t guiInfo;
        guiInfo.visibility = true;
        return guiInfo;
    }
}