#ifndef _Z_OBJ_GRASS_CARRY_H_
#define _Z_OBJ_GRASS_CARRY_H_

#include <global.h>

struct ObjGrassCarry;

typedef struct ObjGrassCarry {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x5C];
} ObjGrassCarry; // size = 0x1A0

extern const ActorInit Obj_Grass_Carry_InitVars;

#endif
