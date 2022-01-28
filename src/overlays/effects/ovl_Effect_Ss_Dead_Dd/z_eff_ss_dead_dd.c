/*
 * File: z_eff_ss_dead_dd.c
 * Overlay: ovl_Effect_Ss_Dead_Dd
 * Description:
 */

#include "z_eff_ss_dead_dd.h"

#define PARAMS ((EffectSsDeadDdInitParams*)initParamsx)

s32 EffectSsDeadDd_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsDeadDd_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsDeadDd_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

#if 0
const EffectSsInit Effect_Ss_Dead_Dd_InitVars = {
    EFFECT_SS_DEAD_DD,
    EffectSsDeadDd_Init,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Dead_Dd/EffectSsDeadDd_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Dead_Dd/EffectSsDeadDd_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Dead_Dd/EffectSsDeadDd_Update.s")
