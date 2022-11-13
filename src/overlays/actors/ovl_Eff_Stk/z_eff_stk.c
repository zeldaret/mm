/*
 * File: z_eff_stk.c
 * Overlay: ovl_Eff_Stk
 * Description: Skullkid Effects (calling down moon / cursing Link)
 */

#include "z_eff_stk.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EffStk*)thisx)

void EffStk_Init(Actor* thisx, PlayState* play);
void EffStk_Destroy(Actor* thisx, PlayState* play);
void EffStk_Update(Actor* thisx, PlayState* play);
void EffStk_Draw(Actor* thisx, PlayState* play);

#if 0
ActorInit Eff_Stk_InitVars = {
    ACTOR_EFF_STK,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_STK2,
    sizeof(EffStk),
    EffStk_Init,
    EffStk_Destroy,
    EffStk_Update,
    EffStk_Draw,
};

#endif

extern UNK_TYPE D_06009F60;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Stk/EffStk_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Stk/EffStk_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Stk/func_80BF0DE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Stk/EffStk_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Stk/EffStk_Draw.s")
