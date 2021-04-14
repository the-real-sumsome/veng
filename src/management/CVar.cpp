#include "CVar.hpp"
#include "Console.hpp"
#include <stdio.h>

using namespace VengManagement;

CVars* GlobalCVars = 0;
    
CVars::CVars() {
    entries_Size = 0;
    for(int i = 0; i<255; i++) {
        entries[i] = 0;
    }
    //      type               name     data
    Reg_Var(CV_WSTRING________,"d_window_name",(void*)&L"Veng");
    int DbgMode = 0;
    #ifdef DEBUG
    DbgMode = 1;
    #endif
    Reg_Var(CV_INT____________,"d_window_mode",&DbgMode);
    #ifdef DEBUG
    // internal pointers for debugging
    Reg_Var(CV_UNKNOWN_POINTER,"dbg_internal_pnode",0);
    Reg_Var(CV_UNKNOWN_POINTER,"dbg_internal_pobjc",0);
    Reg_Var(CV_UNKNOWN_POINTER,"dbg_internal_video",0);
    Reg_Var(CV_UNKNOWN_POINTER,"dbg_internal_fs",0);
    Reg_Var(CV_UNKNOWN_POINTER,"dbg_internal_driver",0);
    Reg_Var(CV_UNKNOWN_POINTER,"dbg_internal_scene",0);
    Reg_Var(CV_UNKNOWN_POINTER,"dbg_internal_gui",0);
    #endif
    Reg_Var(CV_UNKNOWN_POINTER,"map_current",0);

    GlobConsole->Logf("%i variables reigstered.\n",entries_Size);
    GlobalCVars = this;
}

void CVars::Reg_Var(CVarType type, std::string name, void* defValue) {
    if(entries_Size == 255) {
        GlobConsole->Log("Maximum entry size reached\n");
        abort();
    }
    GlobConsole->Logf("Registering CVar \"%s\"\t\t\twith data at %p of type %i.\n",name.c_str(),defValue,type);
    cvar_entry* ent = (cvar_entry*)malloc(sizeof(cvar_entry));
    ent->data = defValue;
    std::string* anam = new std::string(name);
    ent->name = anam;
    ent->type = type;
    ent->ok = true;
    entries[entries_Size] = ent;
    entries_Size++; 
}

void* CVars::Get_Cvar(std::string name) {
    for(int i = 0; i<entries_Size; i++) {
        if(entries[i]->ok) {
            if(entries[i]->name->compare(name.c_str()) == 0) {
                return entries[i]->data;
            }
        }
    }
    return (void*)&"UnknownData";
}

std::vector<cvar_entry*> CVars::Get_Cvars() {
    std::vector<cvar_entry*> entriesvector;
    for(int i = 0; i<entries_Size; i++) {
        if(entries[i]->ok) {
            entriesvector.push_back(entries[i]);
        }
    }
    return entriesvector;
}

void CVars::Set_Cvar(std::string name, void* data) {
    for(int i = 0; i<entries_Size; i++) {
        if(entries[i]->ok) {
            if(entries[i]->name->compare(name.c_str()) == 0) {
                entries[i]->data = data;
            }
        }
    }
}