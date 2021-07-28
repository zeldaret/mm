#ifndef Z_OBJ_SKATEBLOCK_H
#define Z_OBJ_SKATEBLOCK_H

#include "global.h"

struct ObjSkateblock;

typedef struct ObjSkateblock {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x80];
} ObjSkateblock; // size = 0x1C4

extern const ActorInit Obj_Skateblock_InitVars;

#endif // Z_OBJ_SKATEBLOCK_H
