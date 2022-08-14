/*
 * File: z_eff_ss_bomb2.c
 * Overlay: ovl_Effect_Ss_Bomb2
 * Description:
 */

#include "z_eff_ss_bomb2.h"

#define PARAMS ((EffectSsBomb2InitParams*)initParamsx)

s32 EffectSsBomb2_Init(PlayState* play, u32 index, EffectSs* this, void* initParamsx);
void EffectSsBomb2_Update(PlayState* play, u32 index, EffectSs* this);
void func_80978138(PlayState* play, u32 index, EffectSs* this);
void func_80978304(PlayState* play, u32 index, EffectSs* this);

#if 0
const EffectSsInit Effect_Ss_Bomb2_InitVars = {
    EFFECT_SS_BOMB2,
    EffectSsBomb2_Init,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Bomb2/EffectSsBomb2_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Bomb2/func_80978138.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Bomb2/func_80978304.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Bomb2/EffectSsBomb2_Update.s")
