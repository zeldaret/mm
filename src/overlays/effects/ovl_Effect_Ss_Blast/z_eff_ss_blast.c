/*
 * File: z_eff_ss_blast.c
 * Overlay: ovl_Effect_Ss_Blast
 * Description:
 */

#include "z_eff_ss_blast.h"

#define PARAMS ((EffectSsBlastInitParams*)initParamsx)

s32 EffectSsBlast_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsBlast_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsBlast_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

#if 0
const EffectSsInit Effect_Ss_Blast_InitVars = {
    EFFECT_SS_BLAST,
    EffectSsBlast_Init,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Blast/EffectSsBlast_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Blast/EffectSsBlast_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Blast/EffectSsBlast_Update.s")
