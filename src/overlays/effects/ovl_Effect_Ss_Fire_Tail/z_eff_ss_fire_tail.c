/*
 * File: z_eff_ss_fire_tail.c
 * Overlay: ovl_Effect_Ss_Fire_Tail
 * Description:
 */

#include "z_eff_ss_fire_tail.h"

#define PARAMS ((EffectSsFireTailInitParams*)initParamsx)

s32 EffectSsFireTail_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsFireTail_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsFireTail_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

#if 0
const EffectSsInit Effect_Ss_Fire_Tail_InitVars = {
    EFFECT_SS_FIRE_TAIL,
    EffectSsFireTail_Init,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Fire_Tail/EffectSsFireTail_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Fire_Tail/EffectSsFireTail_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Fire_Tail/EffectSsFireTail_Update.s")
