#include "VengUI.hpp"
#include "UIHeaders.hpp"
#include "../management/Console.hpp"

venguiinfo_t IVengUiObject::GetInfo() {
    venguiinfo_t guiInfo;
    guiInfo.visibility = true;
    return guiInfo;
}

IVengUiObject::IVengUiObject(irr::IrrlichtDevice* device) {
    this->device = device;
}

#define PVNG(N) \
    GlobConsole->Logf("Initializing VENGUI, doing: %s\n", #N ); \
    tmp = N; \
    VengUiObjects.push_back( tmp ); \
    tmp->Init()

VengUI::VengUI(irr::IrrlichtDevice* device) : VengUiObjects() {
    this->device = device;
    IVengUiObject* tmp;
    // initialize VengUI objects
    PVNG(new vengui::example(device));
}

void VengUI::Draw() {
    for(int i = 0; i<VengUiObjects.size(); i++) {
        VengUiObjects[i]->Render();
    }
}