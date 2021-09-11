#ifndef Z64_EFFECT_SS_HITMARK_H
#define Z64_EFFECT_SS_HITMARK_H

#include "global.h"

typedef enum {
    /* 0 */ EFFECT_HITMARK_WHITE,
    /* 1 */ EFFECT_HITMARK_DUST,
    /* 2 */ EFFECT_HITMARK_RED,
    /* 3 */ EFFECT_HITMARK_METAL
} EffectSsHitmarkType;

typedef struct {
    /* 0x00 */ s32 type;
    /* 0x04 */ s16 scale;
    /* 0x08 */ Vec3f pos;
} EffectSsHitMarkInitParams; // size = 0x14

extern const EffectSsInit Effect_Ss_Hitmark_InitVars;

#endif
