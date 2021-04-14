#include "VengUI.hpp"
#include "UIHeaders.hpp"
#include "../management/Console.hpp"

venguiinfo_t IVengUiObject::GetInfo() {
    // this returns the venguiinfo_t about a certain VengUI
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
    // PVNG and then do new vengui::NAME OF CLASS(device) or however you construct it, but make sure its a pointer
    PVNG(new vengui::example(device));
}

void VengUI::Draw() {
    // go through each and call its render function
    for(int i = 0; i<VengUiObjects.size(); i++) {
        // render this
        VengUiObjects[i]->Render();
    }
}