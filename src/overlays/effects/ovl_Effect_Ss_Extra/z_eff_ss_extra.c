/*
 * File: z_eff_ss_extra.c
 * Overlay: ovl_Effect_Ss_Extra
 * Description:
 */

#include "z_eff_ss_extra.h"

#define PARAMS ((EffectSsExtraInitParams*)initParamsx)

s32 EffectSsExtra_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsExtra_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsExtra_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

#if 0
const EffectSsInit Effect_Ss_Extra_InitVars = {
    EFFECT_SS_EXTRA,
    EffectSsExtra_Init,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Extra/EffectSsExtra_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Extra/EffectSsExtra_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Extra/EffectSsExtra_Update.s")
