/*
 * File: z_eff_ss_kirakira.c
 * Overlay: ovl_Effect_Ss_Kirakira
 * Description:
 */

#include "z_eff_ss_kirakira.h"

#define PARAMS ((EffectSsKirakiraInitParams*)initParamsx)

s32 EffectSsKirakira_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void func_80977DB4(GlobalContext* globalCtx, u32 index, EffectSs* this);
void func_80977E6C(GlobalContext* globalCtx, u32 index, EffectSs* this);
void func_80977F28(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsKirakira_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

#if 0
const EffectSsInit Effect_Ss_Kirakira_InitVars = {
    EFFECT_SS_KIRAKIRA,
    EffectSsKirakira_Init,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Kirakira/EffectSsKirakira_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Kirakira/EffectSsKirakira_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Kirakira/func_80977DB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Kirakira/func_80977E6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Kirakira/func_80977F28.s")
