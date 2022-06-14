#ifndef Z_EN_WIZ_FIRE_H
#define Z_EN_WIZ_FIRE_H

#include "global.h"

struct EnWizFire;

typedef void (*EnWizFireActionFunc)(struct EnWizFire*, GlobalContext*);

typedef struct {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ UNK_TYPE1 unk02[0x4];
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ UNK_TYPE1 unk0A[0x2];
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ Vec3f unk_10;
    /* 0x1C */ Vec3f unk_1C;
    /* 0x28 */ Vec3f unk_28;
} EnWizFireStruct; // size = 0x34

typedef struct EnWizFire {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnWizFireActionFunc actionFunc;
    /* 0x0148 */ u8 unk_148;
    /* 0x014C */ f32 unk_14C;
    /* 0x0150 */ f32 unk_150;
    /* 0x0154 */ f32 unk_154;
    /* 0x0158 */ f32 unk_158;
    /* 0x015C */ f32 unk_15C;
    /* 0x0160 */ s16 unk_160;
    /* 0x0162 */ s16 unk_162;
    /* 0x0164 */ u8 unk_164;
    /* 0x0166 */ s16 unk_166;
    /* 0x0168 */ s16 unk_168;
    /* 0x016A */ s16 unk_16A;
    /* 0x016C */ s16 unk_16C;
    /* 0x016E */ s16 unk_16E;
    /* 0x0170 */ s16 unk_170;
    /* 0x0172 */ s16 unk_172;
    /* 0x0174 */ s8 unk_174;
    /* 0x0178 */ Vec3f unk_178[10];
    /* 0x01F0 */ f32 unk_1F0;
    /* 0x01F4 */ f32 unk_1F4;
    /* 0x01F8 */ f32 unk_1F8;
    /* 0x01FC */ f32 unk_1FC;
    /* 0x0200 */ f32 unk_200;
    /* 0x0204 */ f32 unk_204;
    /* 0x0208 */ ColliderCylinder collider;
    /* 0x0254 */ EnWizFireStruct unk_254[200];
} EnWizFire; // size = 0x2AF4

extern const ActorInit En_Wiz_Fire_InitVars;

#endif // Z_EN_WIZ_FIRE_H
