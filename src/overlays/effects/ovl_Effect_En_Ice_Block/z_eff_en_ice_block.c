/*
 * File: z_eff_en_ice_block.c
 * Overlay: ovl_Effect_En_Ice_Block
 * Description:
 */

#include "z_eff_en_ice_block.h"

#define PARAMS ((EffectEnIceBlockInitParams*)initParamsx)

s32 EffectEnIceBlock_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectEnIceBlock_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectEnIceBlock_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

#if 0
const EffectSsInit Effect_En_Ice_Block_InitVars = {
    EFFECT_EN_ICE_BLOCK,
    EffectEnIceBlock_Init,
};

#endif

extern UNK_TYPE D_06000A38;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_En_Ice_Block/func_80A22D40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_En_Ice_Block/EffectEnIceBlock_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_En_Ice_Block/EffectEnIceBlock_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_En_Ice_Block/EffectEnIceBlock_Update.s")
