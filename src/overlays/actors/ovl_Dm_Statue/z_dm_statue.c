/*
 * File: z_dm_statue.c
 * Overlay: ovl_Dm_Statue
 * Description: Pillars of water in Giant's Chamber
 */

#include "z_dm_statue.h"
#include "objects/object_smtower/object_smtower.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_CAN_PRESS_SWITCH)

#define THIS ((DmStatue*)thisx)

void DmStatue_Init(Actor* thisx, PlayState* play);
void DmStatue_Destroy(Actor* thisx, PlayState* play);
void DmStatue_Update(Actor* thisx, PlayState* play);
void DmStatue_Draw(Actor* thisx, PlayState* play);

ActorInit Dm_Statue_InitVars = {
    /**/ ACTOR_DM_STATUE,
    /**/ ACTORCAT_ITEMACTION,
    /**/ FLAGS,
    /**/ OBJECT_SMTOWER,
    /**/ sizeof(DmStatue),
    /**/ DmStatue_Init,
    /**/ DmStatue_Destroy,
    /**/ DmStatue_Update,
    /**/ DmStatue_Draw,
};

void DmStatue_Init(Actor* thisx, PlayState* play) {
    DmStatue* this = THIS;

    Actor_SetScale(&this->actor, 10.0f);
}

void DmStatue_Destroy(Actor* thisx, PlayState* play) {
}

void DmStatue_Update(Actor* thisx, PlayState* play) {
}

void DmStatue_Draw(Actor* thisx, PlayState* play) {
    AnimatedMat_Draw(play, Lib_SegmentedToVirtual(object_smtower_Matanimheader_001788));
    Gfx_DrawDListXlu(play, object_smtower_DL_000520);
}
