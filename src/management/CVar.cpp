#include "CVar.hpp"
#include <stdio.h>

using namespace VengManagement;

CVars* GlobalCVars;
    
CVars::CVars() {
    entries_Size = 0;
    for(int i = 0; i<255; i++) {
        entries[i] = 0;
    }
    //      name     data
    Reg_Var("d_window_name",(void*)&L"Veng");
    int DbgMode = 0;
    #ifdef DEBUG
    DbgMode = 1;
    #endif
    Reg_Var("d_window_mode",&DbgMode);
    #ifdef DEBUG
    // internal pointers for debugging
    Reg_Var("dbg_internal_pnode",0);
    Reg_Var("dbg_internal_pobjc",0);
    Reg_Var("dbg_internal_video",0);
    Reg_Var("dbg_internal_fs",0);
    Reg_Var("dbg_internal_driver",0);
    Reg_Var("dbg_internal_scene",0);
    Reg_Var("dbg_internal_gui",0);
    #endif

    printf("%i variables reigstered.\n",entries_Size);
}

void CVars::Reg_Var(std::string name, void* defValue) {
    if(entries_Size == 255) {
        puts("Maximum entry size reached");
        abort();
    }
    printf("Registering CVar \"%s\"\t\t\twith data at %p.\n",name.c_str(),defValue);
    cvar_entry* ent = (cvar_entry*)malloc(sizeof(cvar_entry));
    ent->data = defValue;
    ent->name = &name;
    entries[entries_Size] = ent;
    entries_Size++; 
}

void* CVars::Get_Cvar(std::string name) {
    for(int i = 0; i<entries_Size; i++) {
        if(entries[i]->name->compare(name.c_str()) == 0) {
            return entries[i]->data;
        }
    }
    return (void*)&"UnknownData";
}

void CVars::Set_Cvar(std::string name, void* data) {
    for(int i = 0; i<entries_Size; i++) {
        printf("%i\n",i);
        if(entries[i]->name->compare(name.c_str()) == 0) {
            printf("setting %s to %p\n",name.c_str(),data);
            entries[i]->data = data;
        }
    }
}