/*
 * File: z_dm_al.c
 * Overlay: ovl_Dm_Al
 * Description: Madame Aroma (cutscene)
 */

#include "z_dm_al.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((DmAl*)thisx)

void DmAl_Init(Actor* thisx, PlayState* play);
void DmAl_Destroy(Actor* thisx, PlayState* play);
void DmAl_Update(Actor* thisx, PlayState* play);
void DmAl_Draw(Actor* thisx, PlayState* play);

const ActorInit Dm_Al_InitVars = {
    ACTOR_EN_AL,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_AL,
    sizeof(DmAl),
    (ActorFunc)DmAl_Init,
    (ActorFunc)DmAl_Destroy,
    (ActorFunc)DmAl_Update,
    (ActorFunc)DmAl_Draw,
};

static AnimationInfoS sAnimationInfos[] = {
    { &object_al_Anim_00DBE0, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
};

s32 DmAl_ChangeAnimation(DmAl* this, s32 animationIndex) {
    s32 didAnimationChange = false;

    if (animationIndex != this->animationIndex) {
        this->animationIndex = animationIndex;
        didAnimationChange = SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfos, animationIndex);
    }
    return didAnimationChange;
}

void func_80C1BDD8(DmAl* this, PlayState* play) {
    s32 D_80C1C280[] = { 0, 0, 0, 0, 0 };
    u16 csAction;
    s32 actionIndex;

    if (play->csCtx.state != 0) {
        if (!this->unk_45C) {
            this->action = 0xFF;
            this->unk_45C = true;
            this->animationIndex2 = this->animationIndex;
        }
        if (Cutscene_CheckActorAction(play, 0x232)) {
            actionIndex = Cutscene_GetActorActionIndex(play, 0x232);
            csAction = play->csCtx.actorActions[actionIndex]->action;
            if (this->action != (u8)csAction) {
                this->action = csAction;
                DmAl_ChangeAnimation(this, D_80C1C280[csAction]);
            }
            Cutscene_ActorTranslateAndYaw(&this->actor, play, actionIndex);
        }
    } else if (this->unk_45C) {
        this->unk_45C = false;
        DmAl_ChangeAnimation(this, this->animationIndex2);
    }
}

void DmAl_Init(Actor* thisx, PlayState* play) {
    DmAl* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &gMadameAromaSkel, NULL, this->jointTable, this->morphTable,
                       MADAME_AROMA_LIMB_MAX);
    this->animationIndex = -1;
    DmAl_ChangeAnimation(this, MADAME_AROMA_ANIMATION_0);
    this->actor.flags &= ~ACTOR_FLAG_1;
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = func_80C1BDD8;
}

void DmAl_Destroy(Actor* thisx, PlayState* play) {
}

void DmAl_Update(Actor* thisx, PlayState* play) {
    DmAl* this = THIS;

    this->actionFunc(this, play);
    SkelAnime_Update(&this->skelAnime);
    Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 12.0f, 0.0f, 4);
}

s32 DmAl_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* rot, Vec3s* pos, Actor* thisx) {
    switch (limbIndex) {
        case MADAME_AROMA_LIMB_SHAWL_MIDDLE:
        case MADAME_AROMA_LIMB_SHAWL_UPPER:
        case MADAME_AROMA_LIMB_SHAWL_LEFT_LOWER_MIDDLE:
        case MADAME_AROMA_LIMB_SHAWL_LEFT_LOWER:
        case MADAME_AROMA_LIMB_SHAWL_RIGHT_LOWER_MIDDLE:
        case MADAME_AROMA_LIMB_SHAWL_RIGHT_LOWER:
            *dList = NULL;
            break;
    }
    return false;
}

void DmAl_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    DmAl* this = THIS;

    switch (limbIndex) {
        case MADAME_AROMA_LIMB_SHAWL_MIDDLE:
            Matrix_Get(&this->shawlMatrices[0]);
            break;
        case MADAME_AROMA_LIMB_SHAWL_UPPER:
            Matrix_Get(&this->shawlMatrices[1]);
            break;
        case MADAME_AROMA_LIMB_SHAWL_LEFT_LOWER_MIDDLE:
            Matrix_Get(&this->shawlMatrices[2]);
            break;
        case MADAME_AROMA_LIMB_SHAWL_LEFT_LOWER:
            Matrix_Get(&this->shawlMatrices[3]);
            break;
        case MADAME_AROMA_LIMB_SHAWL_RIGHT_LOWER_MIDDLE:
            Matrix_Get(&this->shawlMatrices[4]);
            break;
        case MADAME_AROMA_LIMB_SHAWL_RIGHT_LOWER:
            Matrix_Get(&this->shawlMatrices[5]);
            break;
        default:
            break;
    }
}

void DmAl_TransformLimbDraw(PlayState* play, s32 limbIndex, Actor* thisx) {
}

static Gfx* sDlists[] = {
    gMadameAromaShawlMiddleDL,           gMadameAromaShawlUpperDL,
    gMadameAromaShawlLeftLowerMiddleDL,  gMadameAromaShawlLeftLowerDL,
    gMadameAromaShawlRightLowerMiddleDL, gMadameAromaShawlRightLowerDL,
};

void DmAl_Draw(Actor* thisx, PlayState* play) {
    u32 i;
    DmAl* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);
    SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   this->skelAnime.dListCount, DmAl_OverrideLimbDraw, DmAl_PostLimbDraw,
                                   DmAl_TransformLimbDraw, &this->actor);
    for (i = 0; i < ARRAY_COUNT(this->shawlMatrices); i++) {
        Matrix_Put(&this->shawlMatrices[i]);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, sDlists[i]);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}
