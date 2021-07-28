/*
 * File: z_eff_ss_d_fire.c
 * Overlay: ovl_Effect_Ss_D_Fire
 * Description:
 */

#include "z_eff_ss_d_fire.h"

#define PARAMS ((EffectSsDFireInitParams*)initParamsx)

s32 EffectSsDFire_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsDFire_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsDFire_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

#if 0
const EffectSsInit Effect_Ss_D_Fire_InitVars = {
    EFFECT_SS_D_FIRE,
    EffectSsDFire_Init,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_D_Fire/func_809791B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_D_Fire/EffectSsDFire_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_D_Fire/EffectSsDFire_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_D_Fire/EffectSsDFire_Update.s")
