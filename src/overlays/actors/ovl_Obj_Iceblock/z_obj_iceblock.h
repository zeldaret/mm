#ifndef Z_OBJ_ICEBLOCK_H
#define Z_OBJ_ICEBLOCK_H

#include "global.h"

struct ObjIceblock;

typedef struct ObjIceblock {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x174];
} ObjIceblock; // size = 0x2B8

extern const ActorInit Obj_Iceblock_InitVars;

#endif // Z_OBJ_ICEBLOCK_H
