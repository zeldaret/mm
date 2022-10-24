#ifndef Z_OBJ_MINE_H
#define Z_OBJ_MINE_H

#include "global.h"

struct ObjMine;

typedef void (*ObjMineActionFunc)(struct ObjMine*, PlayState*);

#define OBJMINE_GET_PARAM_003F(thisx) ((thisx)->params & 0x3F)
#define OBJMINE_GET_PARAM_00FF(thisx) ((thisx)->params & 0xFF)
#define OBJMINE_GET_PARAM_0700(thisx) ((thisx)->params >> 8 & 7)
#define OBJMINE_GET_PARAM_3000(thisx) ((thisx)->params >> 0xC & 3)

typedef struct {
    Vec3f x;
    Vec3f y;
    Vec3f z;
    // Vec3f w;
} ObjMineMtxF3;

typedef struct {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
} ObjMineUnkStruct3;

typedef struct {
    /* 0x00 */ ObjMineMtxF3 unk_00;
    // /* 0x0C */ Vec3f unk_0C;
    // /* 0x18 */ Vec3f unk_18;
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
    /* 0x60 */ ObjMineUnkStruct3* unk_60;
} ObjMineUnkStruct; // size = ?? 0x44??? 48 array???

// probably fake
typedef struct {
    /* 0x00 */ ObjMineMtxF3 unk_00;
    // /* 0x0c */ Vec3f unk_0C;
    // /* 0x18 */ Vec3f unk_18;
    /* 0x24 */ Vec3f unk_24;
    /* 0x30 */ Vec3f unk_30;
    /* 0x3C */ Vec3f unk_3C;
} ObjMineUnkStruct2; // size = 0x48???

typedef struct {
    f32 unk_00;
    Vec3f unk_04;
    f32 unk_10;
    f32 unk_14;
    f32 unk_18;
    f32 unk_1C;
    s16 unk_20;
    f32 unk_24;
    f32 unk_28;
    f32 unk_2C;
    f32 unk_30;
    f32 unk_34;
    f32 unk_38;
    f32 unk_3C;
    s8 unk_40;
    ObjMineUnkStruct2 unk_44[0x3F];
} ObjMineTestStruct2;

typedef struct ObjMine {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderJntSph collider;
    /* 0x0164 */ ColliderJntSphElement colliderElements[1];
    /* 0x01A4 */ ObjMineActionFunc actionFunc;
    /* 0x01A8 */ f32 unk_1A8;
    /* 0x01AC */ s32 unk_1AC;
    /* 0x01B0 */ s32 unk_1B0;
    /* 0x01B4 */ Vec3s* unk_1B4;
    // ObjMineTestStruct2 chain2;
    union { ObjMineTestStruct2 chain2; ObjMineUnkStruct chain1;};
} ObjMine; // size = 0x13B4

#endif // Z_OBJ_MINE_H
