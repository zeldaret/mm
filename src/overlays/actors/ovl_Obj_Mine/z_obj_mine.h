#ifndef Z_OBJ_MINE_H
#define Z_OBJ_MINE_H

#include "global.h"

struct ObjMine;

typedef void (*ObjMineActionFunc)(struct ObjMine*, GlobalContext*);

// definitely fake
typedef struct {
    char unk_00[0x8];
    Vec3f unk_08;
    char unk_14[0xC];
    Vec3f unk_20;
    char unk_2C[0x1C];
} NextUnkStruct; // size = 0x48

// maybe fake
typedef struct {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
} ObjMineUnkStruct3;

typedef struct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ Vec3f unk_18;
    ///* 0x24 */ char unk_24[0x3C];
    /* 0x24 */ Vec3f unk_24;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ f32 unk_3C;
    /* 0x40 */ f32 unk_40;
    /* 0x44 */ f32 unk_44;
    /* 0x48 */ f32 unk_48;
    /* 0x4C */ s16 unk_4C;
    /* 0x50 */ f32 unk_50;
    /* 0x54 */ s16 unk_54;
    /* 0x58 */ f32 unk_58;
    /* 0x5C */ f32 unk_5C;
    /* 0x60 */ ObjMineUnkStruct3 unk_60[1];
} ObjMineUnkStruct; // size = ?? 0x44??? 48 array???

// probably fake
typedef struct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0c */ Vec3f unk_0C;
    ///* 0x10 */ f32 unk_10;
    ///* 0x14 */ char unk_14[0x4];
    /* 0x18 */ Vec3f unk_18;
    ///* 0x1C */ char unk_1C[0x4];
    ///* 0x20 */ f32 unk_20;
    /* 0x24 */ Vec3f unk_24;
    /* 0x30 */ Vec3f unk_30;
    /* 0x3C */ Vec3f unk_3C;
} ObjMineUnkStruct2; // size = 0x48???

typedef struct ObjMine {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderJntSph collider;
    /* 0x0164 */ ColliderJntSphElement colliderElements[1];
    /* 0x01A4 */ ObjMineActionFunc actionFunc;
    /* 0x01A8 */ f32 unk_1A8;
    /* 0x01AC */ s32 unk_1AC;
    /* 0x01B0 */ s32 unk_1B0;
    /* 0x01B4 */ Vec3s* unk_1B4;
    /* 0x01B8 */ ObjMineUnkStruct unk_1B8; // array??
    /* 0x021C */ char unk_21C[0x1198];
} ObjMine; // size = 0x13B4

extern const ActorInit Obj_Mine_InitVars;

#endif // Z_OBJ_MINE_H
