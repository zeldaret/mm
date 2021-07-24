#ifndef Z_OBJ_SPINYROLL_H
#define Z_OBJ_SPINYROLL_H

#include "global.h"

struct ObjSpinyroll;

typedef struct ObjSpinyroll {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x3A0];
} ObjSpinyroll; // size = 0x4E4

extern const ActorInit Obj_Spinyroll_InitVars;

#endif // Z_OBJ_SPINYROLL_H
