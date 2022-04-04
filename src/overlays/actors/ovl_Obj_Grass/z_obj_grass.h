#ifndef Z_OBJ_GRASS_H
#define Z_OBJ_GRASS_H

#include "global.h"
#include "overlays/actors/ovl_Obj_Grass_Carry/z_obj_grass_carry.h"

struct ObjGrass;
struct ObjGrassCarry;

typedef struct ObjGrassStruct1_1 {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s8 unk_0E;
    /* 0x0F */ u8 unk_0F;
    /* 0x10 */ u8 unk_10;
    /* 0x11 */ UNK_TYPE1 unk_11[0x3];
} ObjGrassStruct1_1; // size = 0x14

typedef struct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ ObjGrassStruct1_1 unk_0C[12];
    /* 0xFC */ s16 unk_FC;
    /* 0xFE */ u8 unk_FE;
} ObjGrassStruct1; // size = 0x100

typedef struct {
    /* 0x00 */ ColliderCylinder collider;
    /* 0x4C */ ObjGrassStruct1_1* unk_4C;
} ObjGrassStruct2; // size = 0x50

typedef struct ObjGrass {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ObjGrassStruct1 unk_144[40];
    /* 0x2944 */ s16 unk_2944;
    /* 0x2948 */ ObjGrassStruct2 unk_2948[20];
    /* 0x2F88 */ MtxF unk_2F88[12];
    /* 0x3288 */ s16 unk_3288;
    /* 0x328A */ s16 unk_328A;
    /* 0x328C */ s16 unk_328C;
    /* 0x328E */ s16 unk_328E;
    /* 0x3290 */ s16 unk_3290;
    /* 0x3292 */ s16 unk_3292;
    /* 0x3294 */ ObjGrassStruct1_1* unk_3294;
    /* 0x3298 */ struct ObjGrassCarry* unk_3298[2];
} ObjGrass; // size = 0x32A0

extern const ActorInit Obj_Grass_InitVars;

#endif // Z_OBJ_GRASS_H
