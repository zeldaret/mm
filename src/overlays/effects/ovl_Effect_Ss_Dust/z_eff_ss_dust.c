/*
 * File: z_eff_ss_dust.c
 * Overlay: ovl_Effect_Ss_Dust
 * Description:
 */

#include "z_eff_ss_dust.h"

#define PARAMS ((EffectSsDustInitParams*)initParamsx)

s32 EffectSsDust_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void func_809776BC(GlobalContext* globalCtx, u32 index, EffectSs* this);
void func_809777B4(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsDust_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

#if 0
const EffectSsInit Effect_Ss_Dust_InitVars = {
    EFFECT_SS_DUST,
    EffectSsDust_Init,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Dust/EffectSsDust_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Dust/EffectSsDust_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Dust/func_809776BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Dust/func_809777B4.s")
