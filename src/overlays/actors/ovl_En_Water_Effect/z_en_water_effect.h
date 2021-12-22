#ifndef Z_EN_WATER_EFFECT_H
#define Z_EN_WATER_EFFECT_H

#include "global.h"

struct EnWaterEffect;

typedef struct {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x04 */ Vec3f unk_04;
    /* 0x10 */ Vec3f unk_10;
    /* 0x1C */ Vec3f unk_1C;
    /* 0x28 */ s16 unk_28;
    /* 0x2A */ u8 unk_2A;
    /* 0x2C */ Vec3f unk_2C;
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ s16 unk_3C;
} EnWaterEffectStruct; // size = 0x40

enum {
    /* 0x  1 */ ENWATEREFFECT_1 = 1,
    /* 0x309 */ ENWATEREFFECT_777 = 777,
    /* 0x30A */ ENWATEREFFECT_778,
    /* 0x30B */ ENWATEREFFECT_779,
    /* 0x30C */ ENWATEREFFECT_780,
};

typedef struct EnWaterEffect {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnWaterEffectStruct unk_144[50];
    /* 0xDC4 */ s16 unk_DC4;
    /* 0xDC6 */ s16 unk_DC6;
    /* 0xDC8 */ Vec3f unk_DC8[5];
    /* 0xE04 */ UNK_TYPE1 unk_E04[4];
    /* 0xE04 */ f32 unk_E08[4];
    /* 0xE18 */ f32 unk_E18[4];
    /* 0xE28 */ UNK_TYPE1 unk_E28[4];
    /* 0xE2C */ f32 unk_E2C;
    /* 0xE30 */ f32 unk_E30;
    /* 0xE34 */ f32 unk_E34;
    /* 0xE38 */ f32 unk_E38;
} EnWaterEffect; // size = 0xE3C

extern const ActorInit En_Water_Effect_InitVars;

#endif // Z_EN_WATER_EFFECT_H
