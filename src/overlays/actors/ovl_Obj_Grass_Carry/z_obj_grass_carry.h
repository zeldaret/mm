#ifndef Z_OBJ_GRASS_CARRY_H
#define Z_OBJ_GRASS_CARRY_H

#include "global.h"

struct ObjGrassCarry;
struct ObjGrass;
struct ObjGrassStruct1_1;

typedef void (*ObjGrassCarryActionFunc)(struct ObjGrassCarry*, PlayState*);

typedef struct ObjGrassCarry {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider;
    /* 0x190 */ struct ObjGrass* unk_190;
    /* 0x194 */ struct ObjGrassStruct1_1* unk_194;
    /* 0x198 */ s16 unk_198;
    /* 0x19A */ s16 unk_19A;
    /* 0x19C */ ObjGrassCarryActionFunc actionFunc;
} ObjGrassCarry; // size = 0x1A0

extern const ActorInit Obj_Grass_Carry_InitVars;

#endif // Z_OBJ_GRASS_CARRY_H
