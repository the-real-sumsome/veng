#ifndef __C_VENGMOD_H__
#define __C_VENGMOD_H__
#ifdef __cplusplus

#else
#include <stdbool.h>
#endif

typedef struct {
    float x;
    float y;
    float z;
} vector3df;

typedef enum {
    PEV_NORMAL,
    PEV_GLOBAL,
    PEV_ETC,
} pev_type;

typedef struct {
    int version;
    pev_type type;
} pev_header;

typedef struct {
    // meta values
    pev_header header;

    // positional values
    vector3df origin;
    vector3df rotation;
    vector3df target;
    bool u_target;

    // user values
    int iuser0;
    int iuser1;
    int iuser2;
    int iuser3;
    float fuser0;
    float fuser1;
    float fuser2;
    float fuser3;
    void* puser0;
    void* puser1;
    void* puser2;
    void* puser3;
} pev;

typedef struct {
    pev_header header;

    pev* cameraPev;
} global_pev;


#endif