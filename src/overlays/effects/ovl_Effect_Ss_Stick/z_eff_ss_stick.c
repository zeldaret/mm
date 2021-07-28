/*
 * File: z_eff_ss_stick.c
 * Overlay: ovl_Effect_Ss_Stick
 * Description:
 */

#include "z_eff_ss_stick.h"

#define PARAMS ((EffectSsStickInitParams*)initParamsx)

s32 EffectSsStick_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsStick_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsStick_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

#if 0
const EffectSsInit Effect_Ss_Stick_InitVars = {
    EFFECT_SS_STICK,
    EffectSsStick_Init,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Stick/EffectSsStick_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Stick/EffectSsStick_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Stick/EffectSsStick_Update.s")
