/*
 * File: z_eff_ss_g_spk.c
 * Overlay: ovl_Effect_Ss_G_Spk
 * Description:
 */

#include "z_eff_ss_g_spk.h"

#define PARAMS ((EffectSsGSpkInitParams*)initParamsx)

s32 EffectSsGSpk_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void func_80978F40(GlobalContext* globalCtx, u32 index, EffectSs* this);
void func_80979068(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsGSpk_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

#if 0
const EffectSsInit Effect_Ss_G_Spk_InitVars = {
    EFFECT_SS_G_SPK,
    EffectSsGSpk_Init,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_G_Spk/EffectSsGSpk_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_G_Spk/EffectSsGSpk_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_G_Spk/func_80978F40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_G_Spk/func_80979068.s")
