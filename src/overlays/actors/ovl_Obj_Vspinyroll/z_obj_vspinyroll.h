#ifndef Z_OBJ_VSPINYROLL_H
#define Z_OBJ_VSPINYROLL_H

#include "global.h"

struct ObjVspinyroll;

typedef struct ObjVspinyroll {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x288];
} ObjVspinyroll; // size = 0x3CC

extern const ActorInit Obj_Vspinyroll_InitVars;

#endif // Z_OBJ_VSPINYROLL_H
