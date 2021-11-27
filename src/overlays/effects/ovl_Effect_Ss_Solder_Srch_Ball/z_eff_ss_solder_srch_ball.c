/*
 * File: z_eff_ss_solder_srch_ball.c
 * Overlay: ovl_Effect_Ss_Solder_Srch_Ball
 * Description:
 */

#include "z_eff_ss_solder_srch_ball.h"

#define PARAMS ((EffectSsSolderSrchBallInitParams*)initParamsx)

s32 EffectSsSolderSrchBall_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsSolderSrchBall_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsSolderSrchBall_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

#if 0
const EffectSsInit Effect_Ss_Solder_Srch_Ball_InitVars = {
    EFFECT_SS_SOLDER_SRCH_BALL,
    EffectSsSolderSrchBall_Init,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Solder_Srch_Ball/EffectSsSolderSrchBall_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Solder_Srch_Ball/EffectSsSolderSrchBall_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Solder_Srch_Ball/EffectSsSolderSrchBall_Update.s")
