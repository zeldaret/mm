/*
 * File: z_eff_ss_g_ripple.c
 * Overlay: ovl_Effect_Ss_G_Ripple
 * Description:
 */

#include "z_eff_ss_g_ripple.h"

#define PARAMS ((EffectSsGRippleInitParams*)initParamsx)

s32 EffectSsGRipple_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsGRipple_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsGRipple_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

#if 0
const EffectSsInit Effect_Ss_G_Ripple_InitVars = {
    EFFECT_SS_G_RIPPLE,
    EffectSsGRipple_Init,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_G_Ripple/EffectSsGRipple_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_G_Ripple/func_80979C38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_G_Ripple/EffectSsGRipple_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_G_Ripple/EffectSsGRipple_Update.s")
