/*
 * File: z_eff_ss_sbn.c
 * Overlay: ovl_Effect_Ss_Sbn
 * Description:
 */

#include "z_eff_ss_sbn.h"

#define PARAMS ((EffectSsSbnInitParams*)initParamsx)

s32 EffectSsSbn_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsSbn_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void func_80AC8ECC(GlobalContext* globalCtx, u32 index, EffectSs* this);
void func_80AC9164(GlobalContext* globalCtx, u32 index, EffectSs* this);

#if 0
const EffectSsInit Effect_Ss_Sbn_InitVars = {
    EFFECT_SS_SBN,
    EffectSsSbn_Init,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Sbn/EffectSsSbn_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Sbn/func_80AC8ECC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Sbn/func_80AC9164.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Sbn/EffectSsSbn_Update.s")
