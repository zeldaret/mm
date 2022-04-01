#ifndef Z_EN_TEST7_H
#define Z_EN_TEST7_H

#include "global.h"

struct EnTest7;

typedef void (*EnTest7ActionFunc)(struct EnTest7*, GlobalContext*);
typedef void (*EnTest7UnkFunc)(struct EnTest7*, GlobalContext*);
typedef void (*EnTest7UnkDrawFunc)(Actor*, GlobalContext*);

#define ENTEST7_GET(thisx) ((thisx)->params)

#define ENTEST7_MINUS1 -1
#define ENTEST7_26 0x26
#define ENTEST7_1C 0x1C

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ s16 unk_10;
} EnTest7Struct; // size >= 0x14

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ Vec3f unk_08;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ Vec3s unk_30;
    /* 0x36 */ s16 unk_36;
    /* 0x38 */ s16 unk_38;
    /* 0x3A */ s16 unk_3A;
} EnTest7Struct2; // size = 0x3C

typedef struct EnTest7 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ s32 unk_144;
    /* 0x0148 */ EnTest7Struct unk_148;
    /* 0x015C */ EnTest7Struct2 unk_15C[100];
    /* 0x18CC */ SkeletonInfo unk_18CC;
    /* 0x18FC */ Vec3s unk_18FC[114];
    /* 0x1BA8 */ s16 unk_1BA8[342];
    /* 0x1E54 */ s32 unk_1E54;
    /* 0x1E58 */ EnTest7UnkFunc unk_1E58;
    /* 0x1E5C */ EnTest7ActionFunc actionFunc;
    /* 0x1E60 */ Vec3f unk_1E60;
    /* 0x1E6C */ Vec3f unk_1E6C;
    /* 0x1E78 */ f32 unk_1E78;
    /* 0x1E7C */ LightNode* lightNode;
    /* 0x1E80 */ LightInfo lightInfo;
    /* 0x1E8E */ s16 unk_1E8E;
    /* 0x1E90 */ f32 unk_1E90;
    /* 0x1E94 */ f32 unk_1E94;
    /* 0x1E98 */ EnTest7UnkDrawFunc unk_1E98;
} EnTest7; // size = 0x1E9C

extern const ActorInit En_Test7_InitVars;

#endif // Z_EN_TEST7_H
