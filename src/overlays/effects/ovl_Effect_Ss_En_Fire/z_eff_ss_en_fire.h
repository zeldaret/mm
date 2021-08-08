#ifndef _Z64_EFFECT_SS_EN_FIRE_H_
#define _Z64_EFFECT_SS_EN_FIRE_H_

#include "global.h"

typedef struct {
    /* 0x00 */ Actor* actor;
    /* 0x04 */ Vec3f pos;
    /* 0x10 */ s16 scale;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 flags;
    /* 0x16 */ s16 bodyPart;
} EffectSsEnFireInitParams; // size = 0x18

extern const EffectSsInit Effect_Ss_En_Fire_InitVars;

#endif
