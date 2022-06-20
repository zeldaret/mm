/*
 * File: z_eff_stk.c
 * Overlay: ovl_Eff_Stk
 * Description: Skullkid Effects (calling down moon / cursing Link)
 */

#include "z_eff_stk.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EffStk*)thisx)

void EffStk_Init(Actor* thisx, GlobalContext* globalCtx);
void EffStk_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EffStk_Update(Actor* thisx, GlobalContext* globalCtx);
void EffStk_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Eff_Stk_InitVars = {
    ACTOR_EFF_STK,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_STK2,
    sizeof(EffStk),
    (ActorFunc)EffStk_Init,
    (ActorFunc)EffStk_Destroy,
    (ActorFunc)EffStk_Update,
    (ActorFunc)EffStk_Draw,
};

#endif

extern UNK_TYPE D_06009F60;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Stk/EffStk_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Stk/EffStk_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Stk/func_80BF0DE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Stk/EffStk_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Stk/EffStk_Draw.s")
