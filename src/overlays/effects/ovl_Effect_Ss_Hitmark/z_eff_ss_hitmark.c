/*
 * File: z_eff_ss_hitmark.c
 * Overlay: ovl_Effect_Ss_Hitmark
 * Description:
 */

#include "z_eff_ss_hitmark.h"

#define PARAMS ((EffectSsHitmarkInitParams*)initParamsx)

s32 EffectSsHitmark_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsHitmark_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsHitmark_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

#if 0
const EffectSsInit Effect_Ss_Hitmark_InitVars = {
    EFFECT_SS_HITMARK,
    EffectSsHitmark_Init,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Hitmark/EffectSsHitmark_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Hitmark/EffectSsHitmark_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Hitmark/EffectSsHitmark_Update.s")
