/*
 * File: z_dm_char09.c
 * Overlay: ovl_Dm_Char09
 * Description: Pirates' Fortress cutscene characters
 */

#include "z_dm_char09.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DmChar09*)thisx)

void DmChar09_Init(Actor* thisx, GlobalContext* globalCtx);
void DmChar09_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmChar09_Update(Actor* thisx, GlobalContext* globalCtx);
void DmChar09_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AB1FDC(DmChar09* this, GlobalContext* globalCtx);
void func_80AB2258(DmChar09* this, GlobalContext* globalCtx);
void func_80AB2268(DmChar09* this, GlobalContext* globalCtx);

#if 0
const ActorInit Dm_Char09_InitVars = {
    ACTOR_DM_CHAR09,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_BEE,
    sizeof(DmChar09),
    (ActorFunc)DmChar09_Init,
    (ActorFunc)DmChar09_Destroy,
    (ActorFunc)DmChar09_Update,
    (ActorFunc)DmChar09_Draw,
};

#endif

extern UNK_TYPE D_0600005C;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/func_80AB1E10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/DmChar09_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/DmChar09_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/func_80AB1FA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/func_80AB1FDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/func_80AB2258.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/func_80AB2268.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/func_80AB24BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/DmChar09_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/func_80AB25D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/DmChar09_Draw.s")
