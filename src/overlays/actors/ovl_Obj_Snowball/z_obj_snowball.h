#ifndef Z_OBJ_SNOWBALL_H
#define Z_OBJ_SNOWBALL_H

#include "global.h"

struct ObjSnowball;

typedef struct ObjSnowball {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xD0];
} ObjSnowball; // size = 0x214

extern const ActorInit Obj_Snowball_InitVars;

#endif // Z_OBJ_SNOWBALL_H
