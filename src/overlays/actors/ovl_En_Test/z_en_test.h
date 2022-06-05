#ifndef Z_EN_TEST_H
#define Z_EN_TEST_H

#include "global.h"

struct EnTest;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ Vec3f unk_08;
    /* 0x14 */ Vec3f unk_14;
    /* 0x20 */ Vec3f unk_20;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ Vec3s unk_30;
    /* 0x36 */ Vec3s unk_36;
} EnTestStruct; // size = 0x3C

typedef struct EnTest {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkeletonInfo skeletonInfo;
    /* 0x174 */ s32 unk_174;
    /* 0x178 */ Vec3s unk_178[12];
    /* 0x1C0 */ s16 unk_1C0[36];
    /* 0x208 */ u8 unk_208;
    /* 0x209 */ u8 unk_209;
    /* 0x20A */ u8 unk_20A;
    /* 0x20C */ EnTestStruct unk_20C[20];
} EnTest; // size = 0x6BC

extern const ActorInit En_Test_InitVars;

#endif // Z_EN_TEST_H
