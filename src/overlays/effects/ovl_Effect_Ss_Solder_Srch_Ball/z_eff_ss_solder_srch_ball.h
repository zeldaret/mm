#ifndef Z64_EFFECT_SS_SOLDER_SRCH_BALL_H
#define Z64_EFFECT_SS_SOLDER_SRCH_BALL_H

#include "global.h"

typedef struct {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ Vec3f velocity;
    /* 0x18 */ Vec3f accel;
    /* 0x24 */ s16 unused;
    /* 0x28 */ s16* linkDetected;
    /* 0x2C */ s16 drawFlag;
} EffectSsSolderSrchBallInitParams; // size = 0x30

extern const EffectSsInit Effect_Ss_Solder_Srch_Ball_InitVars;

#endif
