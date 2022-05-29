/*
 * File: z_dm_bal.c
 * Overlay: ovl_Dm_Bal
 * Description: Tingle (cutscene)
 */

#include "z_dm_bal.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((DmBal*)thisx)

void DmBal_Init(Actor* thisx, GlobalContext* globalCtx);
void DmBal_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmBal_Update(Actor* thisx, GlobalContext* globalCtx);
void DmBal_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80C1EAD8(DmBal* this, GlobalContext* globalCtx);

#if 0
const ActorInit Dm_Bal_InitVars = {
    ACTOR_DM_BAL,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BAL,
    sizeof(DmBal),
    (ActorFunc)DmBal_Init,
    (ActorFunc)DmBal_Destroy,
    (ActorFunc)DmBal_Update,
    (ActorFunc)DmBal_Draw,
};

#endif

extern UNK_TYPE D_060005FC;
extern UNK_TYPE D_06001804;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Bal/DmBal_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Bal/DmBal_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Bal/func_80C1EAC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Bal/func_80C1EAD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Bal/func_80C1EAE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Bal/func_80C1EC60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Bal/func_80C1ED0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Bal/func_80C1ED64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Bal/DmBal_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Bal/func_80C1EF80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Bal/func_80C1F060.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Bal/DmBal_Draw.s")
