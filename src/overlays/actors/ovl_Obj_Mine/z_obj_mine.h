#ifndef Z_OBJ_MINE_H
#define Z_OBJ_MINE_H

#include "global.h"

struct ObjMine;

typedef void (*ObjMineActionFunc)(struct ObjMine*, PlayState*);

#define OBJMINE_GET_LINK_COUNT(thisx) ((thisx)->params & 0x3F)
#define OBJMINE_GET_PATH(thisx) ((thisx)->params & 0xFF)
#define OBJMINE_GET_PATH_SPEED(thisx) (((thisx)->params >> 8) & 7)
#define OBJMINE_GET_TYPE(thisx) (((thisx)->params >> 12) & 3)

#define OBJMINE_SET_PARAM0(pathIndex, pathSpeed, type) ((pathIndex) | ((pathSpeed) << 8))
#define OBJMINE_SET_PARAM12(linkCount, type) ((linkCount) | ((type) << 0xC))

typedef enum {
    /* 0 */ OBJMINE_TYPE_PATH,
    /* 1 */ OBJMINE_TYPE_AIR,
    /* 2 */ OBJMINE_TYPE_WATER
} ObjMineType;

typedef struct {
    /* 0x00 */ Vec3f x;
    /* 0x0C */ Vec3f y;
    /* 0x18 */ Vec3f z;
} ObjMineMtxF3; // size = 0x24

typedef struct {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
} ObjMineAirLink; // size = 0x4

typedef struct {
    /* 0x00 */ ObjMineMtxF3 basis;
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
    /* 0x60 */ ObjMineAirLink links[0x3F];
} ObjMineAirChain; // size = 0x15C

typedef struct {
    /* 0x00 */ ObjMineMtxF3 basis;
    /* 0x24 */ Vec3f unk_24;
    /* 0x30 */ Vec3f unk_30;
    /* 0x3C */ Vec3f unk_3C;
} ObjMineWaterLink; // size = 0x48

typedef struct {
    /* 0x0000 */ f32 unk_00;
    /* 0x0004 */ Vec3f unk_04;
    /* 0x0010 */ f32 unk_10;
    /* 0x0014 */ f32 unk_14;
    /* 0x0018 */ f32 unk_18;
    /* 0x001C */ f32 unk_1C;
    /* 0x0020 */ s16 unk_20;
    /* 0x0024 */ f32 unk_24;
    /* 0x0028 */ f32 unk_28;
    /* 0x002C */ f32 unk_2C;
    /* 0x0030 */ f32 unk_30;
    /* 0x0034 */ f32 unk_34;
    /* 0x0038 */ f32 unk_38;
    /* 0x003C */ f32 unk_3C;
    /* 0x0040 */ s8 unk_40;
    /* 0x0044 */ ObjMineWaterLink links[0x3F];
} ObjMineWaterChain; // size = 0x11FC

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
    /* 0x01A8 */ f32 pathSpeed;
    /* 0x01AC */ s32 waypointCount;
    /* 0x01B0 */ s32 waypointIndex;
    /* 0x01B4 */ Vec3s* waypoints;
    /* 0x01B8 */ union { 
                     ObjMineAirChain air;
                     ObjMineWaterChain water;
                 } chain;
} ObjMine; // size = 0x13B4

#endif // Z_OBJ_MINE_H
