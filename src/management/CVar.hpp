#ifndef __CVAR_H__
#define __CVAR_H__

#include <iostream>

namespace VengManagement {


    typedef struct {
        std::string* name;
        void* data;
    } cvar_entry;

    class CVars {
    public:
        void* Get_Cvar(std::string name);
        void Set_Cvar(std::string name, void* data);
        CVars();
    private:
        void Reg_Var(std::string name, void* defValue);
        cvar_entry *entries[255];
        int entries_Size;
    };


}

#endif