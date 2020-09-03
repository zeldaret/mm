#ifndef _Z_OBJ_HARIKO_H_
#define _Z_OBJ_HARIKO_H_

#include <global.h>

struct ObjHariko;

typedef struct ObjHariko {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x14];
} ObjHariko; // size = 0x158

extern const ActorInit Obj_Hariko_InitVars;

#endif
