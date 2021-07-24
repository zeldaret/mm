#ifndef Z_OBJ_SWPRIZE_H
#define Z_OBJ_SWPRIZE_H

#include "global.h"

struct ObjSwprize;

typedef struct ObjSwprize {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x8];
} ObjSwprize; // size = 0x14C

extern const ActorInit Obj_Swprize_InitVars;

#endif // Z_OBJ_SWPRIZE_H
