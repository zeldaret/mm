#ifndef _Z64_EFFECT_SS_SBN_H_
#define _Z64_EFFECT_SS_SBN_H_

#include "global.h"

typedef struct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ CollisionPoly* unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ char unk_14[UNK_SIZE];
} EffectSsSbnInitParams; // size = ?

extern const EffectSsInit Effect_Ss_Sbn_InitVars;

#endif
