/*
 * File: z_dm_zl.c
 * Overlay: ovl_Dm_Zl
 * Description: Child Zelda (Cutscenes)
 */

#include "z_dm_zl.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((DmZl*)thisx)

void DmZl_Init(Actor* thisx, GlobalContext* globalCtx);
void DmZl_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmZl_Update(Actor* thisx, GlobalContext* globalCtx);
void DmZl_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A382FC(DmZl* this, GlobalContext* globalCtx);

#if 0
const ActorInit Dm_Zl_InitVars = {
    ACTOR_DM_ZL,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_ZL4,
    sizeof(DmZl),
    (ActorFunc)DmZl_Init,
    (ActorFunc)DmZl_Destroy,
    (ActorFunc)DmZl_Update,
    (ActorFunc)DmZl_Draw,
};

#endif

extern UNK_TYPE D_0600DE08;
extern UNK_TYPE D_0600E038;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Zl/func_80A38190.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Zl/DmZl_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Zl/DmZl_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Zl/func_80A382FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Zl/func_80A3830C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Zl/func_80A38468.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Zl/DmZl_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Zl/func_80A3862C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Zl/func_80A38648.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Zl/DmZl_Draw.s")
