/*
 * File: z_eff_ss_g_splash.c
 * Overlay: ovl_Effect_Ss_G_Splash
 * Description:
 */

#include "z_eff_ss_g_splash.h"

#define PARAMS ((EffectSsGSplashInitParams*)initParamsx)

s32 EffectSsGSplash_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsGSplash_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsGSplash_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

#if 0
const EffectSsInit Effect_Ss_G_Splash_InitVars = {
    EFFECT_SS_G_SPLASH,
    EffectSsGSplash_Init,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_G_Splash/EffectSsGSplash_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_G_Splash/EffectSsGSplash_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_G_Splash/EffectSsGSplash_Update.s")
