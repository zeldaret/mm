#ifndef Z64_EFFECT_SS_STICK_H
#define Z64_EFFECT_SS_STICK_H

#include "global.h"

typedef struct {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ s16 yaw;
} EffectSsStickInitParams; // size = 0x10

extern const EffectSsInit Effect_Ss_Stick_InitVars;

#endif
