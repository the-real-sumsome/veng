#ifndef __VENGUI_EXAMPLE_HPP__
#define __VENGUI_EXAMPLE_HPP__
#include "../VengUI.hpp"

namespace vengui {
    class example : public IVengUiObject {
    public:
        example(irr::IrrlichtDevice* device);
        virtual void Init();
        virtual void Render();
        virtual venguiinfo_t GetInfo();
    private:
    
    };
}

#endif