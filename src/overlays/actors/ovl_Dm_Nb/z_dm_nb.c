/*
 * File: z_dm_nb.c
 * Overlay: ovl_Dm_Nb
 * Description: Anju's Grandma at wedding during the credits
 */

#include "z_dm_nb.h"
#include "objects/object_nb/object_nb.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((DmNb*)thisx)

void DmNb_Init(Actor* thisx, GlobalContext* globalCtx);
void DmNb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmNb_Update(Actor* thisx, GlobalContext* globalCtx);
void DmNb_Draw(Actor* thisx, GlobalContext* globalCtx);

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

void func_80C1DF18(DmNb* this, GlobalContext* globalCtx) {
    s32 sp2C[] = { 0, 0, 0, 0, 0 };
    u16 actionUnk0;
    s32 actionIndex;

    if (globalCtx->csCtx.state != 0) {
        if (this->unk1F8 == 0) {
            this->unk1EC = 0xFF;
            this->unk1F8 = 1;
            this->unk1F4 = this->unk1F0;
        }
        if (Cutscene_CheckActorAction(globalCtx, 562)) {
            actionIndex = Cutscene_GetActorActionIndex(globalCtx, 562);
            actionUnk0 = globalCtx->csCtx.actorActions[actionIndex]->action;
            if (this->unk1EC != (actionUnk0 & 0xFF)) {
                this->unk1EC = actionUnk0;
                func_80C1DED0(this, sp2C[actionUnk0]);
            }
            Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx, actionIndex);
        }
    } else if (this->unk1F8 != 0) {
        this->unk1F8 = 0;
        func_80C1DED0(this, this->unk1F4);
    }
}

void DmNb_Init(Actor* thisx, GlobalContext* globalCtx) {
    DmNb* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_nb_Skel_008C40, NULL, this->jointTable, this->morphTable,
                       8);
    this->unk1F0 = -1;
    func_80C1DED0(this, 0);
    this->actor.flags &= ~ACTOR_FLAG_1;
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = func_80C1DF18;
}

void DmNb_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void DmNb_Update(Actor* thisx, GlobalContext* globalCtx) {
    DmNb* this = THIS;

    this->actionFunc(this, globalCtx);
    SkelAnime_Update(&this->skelAnime);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, 12.0f, 0.0f, 4);
}

void DmNb_TransformLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx) {
}

void DmNb_Draw(Actor* thisx, GlobalContext* globalCtx) {
    DmNb* this = THIS;

    func_8012C5B0(globalCtx->state.gfxCtx);
    SkelAnime_DrawTransformFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   this->skelAnime.dListCount, NULL, NULL, DmNb_TransformLimbDraw, &this->actor);
}
