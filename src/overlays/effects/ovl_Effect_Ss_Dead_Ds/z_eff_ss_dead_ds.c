/*
 * File: z_eff_ss_dead_ds.c
 * Overlay: ovl_Effect_Ss_Dead_Ds
 * Description:
 */

#include "z_eff_ss_dead_ds.h"

#define PARAMS ((EffectSsDeadDsInitParams*)initParamsx)

s32 EffectSsDeadDs_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsDeadDs_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsDeadDs_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

#if 0
const EffectSsInit Effect_Ss_Dead_Ds_InitVars = {
    EFFECT_SS_DEAD_DS,
    EffectSsDeadDs_Init,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Dead_Ds/EffectSsDeadDs_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Dead_Ds/EffectSsDeadDs_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Dead_Ds/EffectSsDeadDs_Update.s")
