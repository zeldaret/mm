/*
 * File: z_dm_al.c
 * Overlay: ovl_Dm_Al
 * Description: Madame Aroma (cutscene)
 */

#include "z_dm_al.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY)

#define THIS ((DmAl*)thisx)

void DmAl_Init(Actor* thisx, PlayState* play);
void DmAl_Destroy(Actor* thisx, PlayState* play);
void DmAl_Update(Actor* thisx, PlayState* play);
void DmAl_Draw(Actor* thisx, PlayState* play);

ActorInit Dm_Al_InitVars = {
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

typedef enum {
    /* 0 */ MADAME_AROMA_ANIM_0,
    /* 1 */ MADAME_AROMA_ANIM_1
} DmAlAnimation;

static AnimationInfoS sAnimationInfo[] = {
    { &object_al_Anim_00DBE0, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
};

s32 DmAl_ChangeAnim(DmAl* this, s32 animIndex) {
    s32 didAnimationChange = false;

    if (animIndex != this->animIndex) {
        this->animIndex = animIndex;
        didAnimationChange = SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, animIndex);
    }
    return didAnimationChange;
}

void func_80C1BDD8(DmAl* this, PlayState* play) {
    s32 D_80C1C280[] = { 0, 0, 0, 0, 0 };
    u16 cueId;
    s32 cueChannel;

    if (play->csCtx.state != CS_STATE_IDLE) {
        if (!this->unk_45C) {
            this->cueId = 255;
            this->unk_45C = true;
            this->animIndex2 = this->animIndex;
        }
        if (Cutscene_IsCueInChannel(play, CS_CMD_ACTOR_CUE_562)) {
            cueChannel = Cutscene_GetCueChannel(play, CS_CMD_ACTOR_CUE_562);
            cueId = play->csCtx.actorCues[cueChannel]->id;
            if (this->cueId != (u8)cueId) {
                this->cueId = cueId;
                DmAl_ChangeAnim(this, D_80C1C280[cueId]);
            }
            Cutscene_ActorTranslateAndYaw(&this->actor, play, cueChannel);
        }
    } else if (this->unk_45C) {
        this->unk_45C = false;
        DmAl_ChangeAnim(this, this->animIndex2);
    }
}

void DmAl_Init(Actor* thisx, PlayState* play) {
    DmAl* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &gMadameAromaSkel, NULL, this->jointTable, this->morphTable,
                       MADAME_AROMA_LIMB_MAX);
    this->animIndex = -1;
    DmAl_ChangeAnim(this, MADAME_AROMA_ANIM_0);
    this->actor.flags &= ~ACTOR_FLAG_TARGETABLE;
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = func_80C1BDD8;
}

void DmAl_Destroy(Actor* thisx, PlayState* play) {
}

void DmAl_Update(Actor* thisx, PlayState* play) {
    DmAl* this = THIS;

    this->actionFunc(this, play);
    SkelAnime_Update(&this->skelAnime);
    Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 12.0f, 0.0f, UPDBGCHECKINFO_FLAG_4);
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

    Gfx_SetupDL25_Opa(play->state.gfxCtx);
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
