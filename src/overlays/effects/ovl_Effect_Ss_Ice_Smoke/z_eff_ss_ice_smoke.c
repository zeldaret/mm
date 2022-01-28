/*
 * File: z_eff_ss_ice_smoke.c
 * Overlay: ovl_Effect_Ss_Ice_Smoke
 * Description:
 */

#include "z_eff_ss_ice_smoke.h"

#define PARAMS ((EffectSsIceSmokeInitParams*)initParamsx)

s32 EffectSsIceSmoke_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsIceSmoke_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsIceSmoke_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

#if 0
const EffectSsInit Effect_Ss_Ice_Smoke_InitVars = {
    EFFECT_SS_ICE_SMOKE,
    EffectSsIceSmoke_Init,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Ice_Smoke/EffectSsIceSmoke_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Ice_Smoke/EffectSsIceSmoke_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Ice_Smoke/EffectSsIceSmoke_Update.s")
