#include "VENGUI_Example.hpp"
#include <random>

namespace vengui {
    example::example(irr::IrrlichtDevice* device) : IVengUiObject(device) {

    }
    void example::Init() {
        cooltext = device->getVideoDriver()->getTexture("font.bmp");
    }
    void example::Render() {
        //device->getVideoDriver()->draw2DImage(cooltext,irr::core::vector2di(std::rand()%1000,std::rand()%100));
    }
    venguiinfo_t example::GetInfo() {
        venguiinfo_t guiInfo;
        guiInfo.visibility = true;
        return guiInfo;
    }
}