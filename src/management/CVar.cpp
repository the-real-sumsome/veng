#include "CVar.hpp"

CVars::CVars() {
    Reg_Var("r_name","Veng");
}

CVars::Reg_Var(std::string name, void* defValue) {
    cvar_entry* ent = (cvar_entry*)malloc(sizeof(cvar_entry));
    ent->data = defValue;
    ent->name = name;
}