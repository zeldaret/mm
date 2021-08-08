/*
 * File: z_eff_ss_en_ice.c
 * Overlay: ovl_Effect_Ss_En_Ice
 * Description:
 */

#include "z_eff_ss_en_ice.h"

#define PARAMS ((EffectSsEnIceInitParams*)initParamsx)

s32 EffectSsEnIce_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void func_8097F62C(GlobalContext* globalCtx, u32 index, EffectSs* this);
void func_8097F7EC(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsEnIce_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

#if 0
const EffectSsInit Effect_Ss_En_Ice_InitVars = {
    EFFECT_SS_EN_ICE,
    EffectSsEnIce_Init,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_En_Ice/EffectSsEnIce_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_En_Ice/EffectSsEnIce_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_En_Ice/func_8097F62C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_En_Ice/func_8097F7EC.s")
