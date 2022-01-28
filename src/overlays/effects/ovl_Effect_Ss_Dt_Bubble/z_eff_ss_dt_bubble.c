/*
 * File: z_eff_ss_dt_bubble.c
 * Overlay: ovl_Effect_Ss_Dt_Bubble
 * Description:
 */

#include "z_eff_ss_dt_bubble.h"

#define PARAMS ((EffectSsDtBubbleInitParams*)initParamsx)

s32 EffectSsDtBubble_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsDtBubble_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsDtBubble_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

#if 0
const EffectSsInit Effect_Ss_Dt_Bubble_InitVars = {
    EFFECT_SS_DT_BUBBLE,
    EffectSsDtBubble_Init,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Dt_Bubble/EffectSsDtBubble_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Dt_Bubble/EffectSsDtBubble_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Dt_Bubble/EffectSsDtBubble_Update.s")
