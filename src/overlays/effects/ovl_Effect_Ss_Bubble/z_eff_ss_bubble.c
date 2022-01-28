/*
 * File: z_eff_ss_bubble.c
 * Overlay: ovl_Effect_Ss_Bubble
 * Description:
 */

#include "z_eff_ss_bubble.h"

#define PARAMS ((EffectSsBubbleInitParams*)initParamsx)

s32 EffectSsBubble_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsBubble_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsBubble_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

#if 0
const EffectSsInit Effect_Ss_Bubble_InitVars = {
    EFFECT_SS_BUBBLE,
    EffectSsBubble_Init,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Bubble/EffectSsBubble_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Bubble/EffectSsBubble_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Bubble/EffectSsBubble_Update.s")
