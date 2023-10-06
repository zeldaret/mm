/*
 * File: z_en_fr.c
 * Overlay: ovl_En_Fr
 * Description:
 */

#include "z_en_fr.h"

#define FLAGS (ACTOR_FLAG_40000000)

#define THIS ((EnFr*)thisx)

void EnFr_Init(Actor* thisx, PlayState* play);
void EnFr_Destroy(Actor* thisx, PlayState* play);
void EnFr_Update(Actor* thisx, PlayState* play);

ActorInit En_Fr_InitVars = {
    ACTOR_EN_FR,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnFr),
    (ActorFunc)EnFr_Init,
    (ActorFunc)EnFr_Destroy,
    (ActorFunc)EnFr_Update,
    (ActorFunc)NULL,
};

void EnFr_Init(Actor* thisx, PlayState* play) {
    EnFr* this = THIS;

    if (Flags_GetSwitch(play, ENFR_GET_SWITCH_FLAG(&this->actor))) {
        Actor_Kill(&this->actor);
        return;
    }

    this->actor.targetMode = ENFR_GET_TARGETMODE(&this->actor);
}

void EnFr_Destroy(Actor* thisx, PlayState* play) {
}

void EnFr_Update(Actor* thisx, PlayState* play) {
    EnFr* this = THIS;

    if (Flags_GetSwitch(play, ENFR_GET_SWITCH_FLAG(&this->actor))) {
        Actor_Kill(&this->actor);
        return;
    }

    if (this->actor.xyzDistToPlayerSq < SQ(IREG(29))) {
        this->actor.flags &= ~ACTOR_FLAG_40000000;
    } else {
        this->actor.flags |= ACTOR_FLAG_40000000;
    }
}
