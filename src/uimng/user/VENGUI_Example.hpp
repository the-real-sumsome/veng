#ifndef __VENGUI_EXAMPLE_HPP__
#define __VENGUI_EXAMPLE_HPP__
#include "../VengUI.hpp"

// all user venguis should be in the namspace vengui
// this is vengui::example

namespace vengui {
    class example : public IVengUiObject {
    public:
        example(irr::IrrlichtDevice* device);
        virtual void Init();
        virtual void Render();
        virtual venguiinfo_t GetInfo();
    private:
        irr::video::ITexture* cooltext;
    };
}

#endif