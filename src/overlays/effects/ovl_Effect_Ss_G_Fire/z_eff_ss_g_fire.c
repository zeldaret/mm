/*
 * File: z_eff_ss_g_fire.c
 * Overlay: ovl_Effect_Ss_G_Fire
 * Description:
 */

#include "z_eff_ss_g_fire.h"

#define PARAMS ((EffectSsGFireInitParams*)initParamsx)

s32 EffectSsGFire_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsGFire_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsGFire_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

#if 0
const EffectSsInit Effect_Ss_G_Fire_InitVars = {
    EFFECT_SS_G_FIRE,
    EffectSsGFire_Init,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_G_Fire/EffectSsGFire_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_G_Fire/EffectSsGFire_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_G_Fire/EffectSsGFire_Update.s")
