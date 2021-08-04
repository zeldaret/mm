/*
 * File: z_eff_ss_sibuki.c
 * Overlay: ovl_Effect_Ss_Sibuki
 * Description:
 */

#include "z_eff_ss_sibuki.h"

#define PARAMS ((EffectSsSibukiInitParams*)initParamsx)

s32 EffectSsSibuki_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsSibuki_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsSibuki_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

#if 0
const EffectSsInit Effect_Ss_Sibuki_InitVars = {
    EFFECT_SS_SIBUKI,
    EffectSsSibuki_Init,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Sibuki/EffectSsSibuki_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Sibuki/EffectSsSibuki_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Sibuki/EffectSsSibuki_Update.s")
