/*
 * File: z_dm_char04.c
 * Overlay: ovl_Dm_Char04
 * Description: Unused(?) Tatl and Tael actors
 */

#include "z_dm_char04.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DmChar04*)thisx)

void DmChar04_Init(Actor* thisx, GlobalContext* globalCtx);
void DmChar04_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmChar04_Update(Actor* thisx, GlobalContext* globalCtx);
void DmChar04_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Dm_Char04_InitVars = {
    ACTOR_DM_CHAR04,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(DmChar04),
    (ActorFunc)DmChar04_Init,
    (ActorFunc)DmChar04_Destroy,
    (ActorFunc)DmChar04_Update,
    (ActorFunc)DmChar04_Draw,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char04/func_80AABC40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char04/DmChar04_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char04/DmChar04_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char04/func_80AABE34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char04/DmChar04_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char04/func_80AABF74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char04/DmChar04_Draw.s")
