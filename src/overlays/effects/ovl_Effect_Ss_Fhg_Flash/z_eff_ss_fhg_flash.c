/*
 * File: z_eff_ss_fhg_flash.c
 * Overlay: ovl_Effect_Ss_Fhg_Flash
 * Description:
 */

#include "z_eff_ss_fhg_flash.h"

#define PARAMS ((EffectSsFhgFlashInitParams*)initParamsx)

s32 EffectSsFhgFlash_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsFhgFlash_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsFhgFlash_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

#if 0
const EffectSsInit Effect_Ss_Fhg_Flash_InitVars = {
    EFFECT_SS_FHG_FLASH,
    EffectSsFhgFlash_Init,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Fhg_Flash/EffectSsFhgFlash_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Fhg_Flash/EffectSsFhgFlash_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Fhg_Flash/EffectSsFhgFlash_Update.s")
