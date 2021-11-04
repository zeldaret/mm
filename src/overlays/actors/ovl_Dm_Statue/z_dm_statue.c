/*
 * File: z_dm_statue.c
 * Overlay: ovl_Dm_Statue
 * Description: Elegy of Emptiness - Beam of Light When Creating Statue
 */

#include "z_dm_statue.h"

#define FLAGS 0x04000030

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

extern AnimatedMaterial D_06001788;
extern Gfx D_06000520[];

void DmStatue_Init(Actor* thisx, GlobalContext* globalCtx) {
    DmStatue* this = THIS;

    Actor_SetScale(&this->actor, 10.0f);
}

void DmStatue_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void DmStatue_Update(Actor* thisx, GlobalContext* globalCtx) {
}

void DmStatue_Draw(Actor* thisx, GlobalContext* globalCtx) {
    AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&D_06001788));
    Gfx_DrawDListXlu(globalCtx, D_06000520);
}
