#ifndef Z64_EFFECT_SS_EXTRA_H
#define Z64_EFFECT_SS_EXTRA_H

#include "global.h"

typedef enum {
    /* 0 */ EXTRA_SCORE_30,
    /* 1 */ EXTRA_SCORE_60,
    /* 2 */ EXTRA_SCORE_100
} ExtraScoreIdx;

typedef struct {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ Vec3f velocity;
    /* 0x18 */ Vec3f accel;
    /* 0x24 */ s16 scale;
    /* 0x26 */ s16 scoreIdx;
} EffectSsExtraInitParams; // size = 0x28

extern const EffectSsInit Effect_Ss_Extra_InitVars;

#endif
