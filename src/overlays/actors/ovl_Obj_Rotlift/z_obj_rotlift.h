#ifndef Z_OBJ_ROTLIFT_H
#define Z_OBJ_ROTLIFT_H

#include "global.h"

struct ObjRotlift;

typedef struct ObjRotlift {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x20];
} ObjRotlift; // size = 0x164

extern const ActorInit Obj_Rotlift_InitVars;

#endif // Z_OBJ_ROTLIFT_H
