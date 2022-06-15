/*
 * File: z_dm_ah.c
 * Overlay: ovl_Dm_Ah
 * Description: Anju's Mother (cutscene)
 */

#include "z_dm_ah.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((DmAh*)thisx)

void DmAh_Init(Actor* thisx, GlobalContext* globalCtx);
void DmAh_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmAh_Update(Actor* thisx, GlobalContext* globalCtx);
void DmAh_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80C1D7FC(DmAh* this, GlobalContext* globalCtx);
void func_80C1D92C(DmAh* this, GlobalContext* globalCtx);

#if 0
const ActorInit Dm_Ah_InitVars = {
    ACTOR_DM_AH,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_AH,
    sizeof(DmAh),
    (ActorFunc)DmAh_Init,
    (ActorFunc)DmAh_Destroy,
    (ActorFunc)DmAh_Update,
    (ActorFunc)DmAh_Draw,
};

#endif

extern UNK_TYPE D_06009E70;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Ah/func_80C1D410.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Ah/func_80C1D458.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Ah/func_80C1D4D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Ah/func_80C1D6E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Ah/func_80C1D78C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Ah/func_80C1D7FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Ah/func_80C1D92C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Ah/DmAh_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Ah/DmAh_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Ah/DmAh_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Ah/func_80C1DAD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Ah/func_80C1DB24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Ah/DmAh_Draw.s")
