/*
 * File: z_dm_nb.c
 * Overlay: ovl_Dm_Nb
 * Description: Anju's Grandma at wedding during the credits
 */

#include "z_dm_nb.h"
#include "objects/object_nb/object_nb.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((DmNb*)thisx)

void DmNb_Init(Actor* thisx, PlayState* play);
void DmNb_Destroy(Actor* thisx, PlayState* play);
void DmNb_Update(Actor* thisx, PlayState* play);
void DmNb_Draw(Actor* thisx, PlayState* play);

const ActorInit Dm_Nb_InitVars = {
    ACTOR_DM_NB,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_NB,
    sizeof(DmNb),
    (ActorFunc)DmNb_Init,
    (ActorFunc)DmNb_Destroy,
    (ActorFunc)DmNb_Update,
    (ActorFunc)DmNb_Draw,
};

static AnimationInfoS D_80C1E200[] = { { &object_nb_Anim_000990, 1.0f, 0, -1, ANIMMODE_LOOP, 0 } };

s32 func_80C1DED0(DmNb* this, s32 arg1) {
    s32 ret = false;

    if (arg1 != this->unk1F0) {
        this->unk1F0 = arg1;
        ret = SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80C1E200, arg1);
    }
    return ret;
}

void func_80C1DF18(DmNb* this, PlayState* play) {
    s32 sp2C[] = { 0, 0, 0, 0, 0 };
    u16 csAction;
    s32 csActionIndex;

    if (play->csCtx.state != 0) {
        if (this->unk1F8 == 0) {
            this->unk1EC = 0xFF;
            this->unk1F8 = 1;
            this->unk1F4 = this->unk1F0;
        }
        if (Cutscene_CheckActorAction(play, 0x232)) {
            csActionIndex = Cutscene_GetActorActionIndex(play, 0x232);
            csAction = play->csCtx.actorActions[csActionIndex]->action;
            if (this->unk1EC != (u8)csAction) {
                this->unk1EC = csAction;
                func_80C1DED0(this, sp2C[csAction]);
            }
            Cutscene_ActorTranslateAndYaw(&this->actor, play, csActionIndex);
        }
    } else if (this->unk1F8 != 0) {
        this->unk1F8 = 0;
        func_80C1DED0(this, this->unk1F4);
    }
}

void DmNb_Init(Actor* thisx, PlayState* play) {
    DmNb* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &object_nb_Skel_008C40, NULL, this->jointTable, this->morphTable, 8);
    this->unk1F0 = -1;
    func_80C1DED0(this, 0);
    this->actor.flags &= ~ACTOR_FLAG_1;
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = func_80C1DF18;
}

void DmNb_Destroy(Actor* thisx, PlayState* play) {
}

void DmNb_Update(Actor* thisx, PlayState* play) {
    DmNb* this = THIS;

    this->actionFunc(this, play);
    SkelAnime_Update(&this->skelAnime);
    Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 12.0f, 0.0f, 4);
}

void DmNb_TransformLimbDraw(PlayState* play, s32 limbIndex, Actor* thisx) {
}

void DmNb_Draw(Actor* thisx, PlayState* play) {
    DmNb* this = THIS;

    func_8012C5B0(play->state.gfxCtx);
    SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   this->skelAnime.dListCount, NULL, NULL, DmNb_TransformLimbDraw, &this->actor);
}
