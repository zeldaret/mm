#ifndef Z_OBJ_GRASS_CARRY_H
#define Z_OBJ_GRASS_CARRY_H

#include "global.h"

struct ObjGrassCarry;
struct ObjGrass;
struct ObjGrassStruct1_1;

typedef void (*ObjGrassCarryActionFunc)(struct ObjGrassCarry*, GlobalContext*);

typedef struct ObjGrassCarry {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderCylinder collider;
    /* 0x0190 */ struct ObjGrass* unk_190;
    /* 0x0194 */ struct ObjGrassStruct1_1* unk_194;
    /* 0x0198 */ s16 unk_198;
    /* 0x019A */ s16 unk_19A;
    /* 0x019C */ ObjGrassCarryActionFunc actionFunc;
} ObjGrassCarry; // size = 0x1A0

extern const ActorInit Obj_Grass_Carry_InitVars;

#endif // Z_OBJ_GRASS_CARRY_H
