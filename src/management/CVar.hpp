#ifndef __CVAR_H__
#define __CVAR_H__

#include <iostream>
#include <vector>

namespace VengManagement {
    enum CVarType {
        CV_UNKNOWN_POINTER,
        CV_STRING_________,
        CV_STDSTRING______,
        CV_WSTRING________,
        CV_INT____________,
        CV_FLOAT__________,
    };

    typedef struct {
        bool ok;
        CVarType type;
        std::string* name;
        void* data;
    } cvar_entry;

    class CVars {
    public:
        void* Get_Cvar(std::string name);
        void Set_Cvar(std::string name, void* data);
        std::vector<cvar_entry*> Get_Cvars();
        CVars();
    private:
        void Reg_Var(CVarType type, std::string name, void* defValue);
        cvar_entry *entries[255];
        int entries_Size;
    };


}

extern VengManagement::CVars* GlobalCVars;

#endif