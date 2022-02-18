/*
 * File: z_dm_statue.c
 * Overlay: ovl_Dm_Statue
 * Description: Pillars of water in Giant's Chamber
 */

#include "z_dm_statue.h"
#include "objects/object_smtower/object_smtower.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_4000000)

#define THIS ((DmStatue*)thisx)

void DmStatue_Init(Actor* thisx, GlobalContext* globalCtx);
void DmStatue_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmStatue_Update(Actor* thisx, GlobalContext* globalCtx);
void DmStatue_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Dm_Statue_InitVars = {
    ACTOR_DM_STATUE,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_SMTOWER,
    sizeof(DmStatue),
    (ActorFunc)DmStatue_Init,
    (ActorFunc)DmStatue_Destroy,
    (ActorFunc)DmStatue_Update,
    (ActorFunc)DmStatue_Draw,
};

void DmStatue_Init(Actor* thisx, GlobalContext* globalCtx) {
    DmStatue* this = THIS;

    Actor_SetScale(&this->actor, 10.0f);
}

void DmStatue_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void DmStatue_Update(Actor* thisx, GlobalContext* globalCtx) {
}

void DmStatue_Draw(Actor* thisx, GlobalContext* globalCtx) {
    AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(object_smtower_Matanimheader_001788));
    Gfx_DrawDListXlu(globalCtx, object_smtower_DL_000520);
}
