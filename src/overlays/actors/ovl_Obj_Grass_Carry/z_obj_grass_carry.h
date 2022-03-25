#ifndef Z_OBJ_GRASS_CARRY_H
#define Z_OBJ_GRASS_CARRY_H

#include "global.h"

struct ObjGrassCarry;

typedef void (*ObjGrassCarryActionFunc)(struct ObjGrassCarry*, GlobalContext*);

typedef struct ObjGrassCarry {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x4C];
    /* 0x0190 */ s32 unk_190;
    /* 0x0194 */ char unk_194[0x8];
    /* 0x019C */ ObjGrassCarryActionFunc actionFunc;
} ObjGrassCarry; // size = 0x1A0

extern const ActorInit Obj_Grass_Carry_InitVars;

#endif // Z_OBJ_GRASS_CARRY_H
