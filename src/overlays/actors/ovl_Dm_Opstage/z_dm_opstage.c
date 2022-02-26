/*
 * File: z_dm_opstage.c
 * Overlay: ovl_Dm_Opstage
 * Description: Lost Woods cutscene objects
 */

#include "z_dm_opstage.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DmOpstage*)thisx)

void DmOpstage_Init(Actor* thisx, GlobalContext* globalCtx);
void DmOpstage_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmOpstage_Update(Actor* thisx, GlobalContext* globalCtx);
void DmOpstage_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A9FA58(DmOpstage* this, GlobalContext* globalCtx);

void DmOpstage_SetupAction(DmOpstage* this, DmOpstageActionFunc actionFunc);

#if 0
const ActorInit Dm_Opstage_InitVars = {
    ACTOR_DM_OPSTAGE,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_KEIKOKU_DEMO,
    sizeof(DmOpstage),
    (ActorFunc)DmOpstage_Init,
    (ActorFunc)DmOpstage_Destroy,
    (ActorFunc)DmOpstage_Update,
    (ActorFunc)DmOpstage_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A9FD30[] = {
    ICHAIN_F32(uncullZoneScale, 300, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80A9FD30[];

extern UNK_TYPE D_06000978;
extern UNK_TYPE D_06001C98;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Opstage/DmOpstage_SetupAction.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Opstage/DmOpstage_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Opstage/DmOpstage_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Opstage/func_80A9FA58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Opstage/DmOpstage_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Opstage/DmOpstage_Draw.s")
