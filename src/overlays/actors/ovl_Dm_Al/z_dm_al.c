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

s32 func_80C1BD90(DmAl* this, s32* animationIndex) {
    s32 ret = 0;

    if (animationIndex != this->animationIndex) {
        this->animationIndex = animationIndex;
        ret = SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfos, animationIndex);
    }
    return ret;
}

void func_80C1BDD8(DmAl* this, PlayState* play) {
    s32 D_80C1C280[] = { 0, 0, 0, 0, 0 };
    u16 action;
    s32 actionIndex;

    if (play->csCtx.state != 0) {
        if (this->unk45C == 0) {
            this->action = 0xFF;
            this->unk45C = 1;
            this->animationIndex2 = this->animationIndex;
        }
        if (Cutscene_CheckActorAction(play, 0x232)) {
            actionIndex = Cutscene_GetActorActionIndex(play, 0x232);
            action = play->csCtx.actorActions[actionIndex]->action;
            if (this->action != (u8)action) {
                this->action = action;
                func_80C1BD90(this, D_80C1C280[action]);
            }
            Cutscene_ActorTranslateAndYaw(&this->actor, play, actionIndex);
        }
    } else if (this->unk45C != 0) {
        this->unk45C = 0;
        func_80C1BD90(this, this->animationIndex2);
    }
}

void DmAl_Init(Actor* thisx, PlayState* play) {
    DmAl* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &gMadameAromaSkel, NULL, this->jointTable, this->morphTable,
                       OBJECT_AL_LIMB_MAX);
    this->animationIndex = -1;
    func_80C1BD90(this, NULL);
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

s32 func_80C1C028(PlayState* play, s32 limbIndex, Gfx** gfx, Vec3f* rot, Vec3s* pos, Actor* thisx) {
    switch (limbIndex) {
        case MADAME_AROMA_SHAWL_MIDDLE_LIMB:
        case MADAME_AROMA_SHAWL_UPPER_LIMB:
        case MADAME_AROMA_SHAWL_LEFT_LOWER_MIDDLE_LIMB:
        case MADAME_AROMA_SHAWL_LEFT_LOWER_LIMB:
        case MADAME_AROMA_SHAWL_RIGHT_LOWER_MIDDLE_LIMB:
        case MADAME_AROMA_SHAWL_RIGHT_LOWER_LIMB:
            *gfx = NULL;
            break;
    }
    return false;
}

void func_80C1C064(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    DmAl* this = THIS;

    switch (limbIndex) {
        case MADAME_AROMA_SHAWL_MIDDLE_LIMB:
            Matrix_Get(&this->unkMtx[0]);
            break;
        case MADAME_AROMA_SHAWL_UPPER_LIMB:
            Matrix_Get(&this->unkMtx[1]);
            break;
        case MADAME_AROMA_SHAWL_LEFT_LOWER_MIDDLE_LIMB:
            Matrix_Get(&this->unkMtx[2]);
            break;
        case MADAME_AROMA_SHAWL_LEFT_LOWER_LIMB:
            Matrix_Get(&this->unkMtx[3]);
            break;
        case MADAME_AROMA_SHAWL_RIGHT_LOWER_MIDDLE_LIMB:
            Matrix_Get(&this->unkMtx[4]);
            break;
        case MADAME_AROMA_SHAWL_RIGHT_LOWER_LIMB:
            Matrix_Get(&this->unkMtx[5]);
            break;
        default:
            break;
    }
}

void func_80C1C11C(PlayState* play, s32 arg0, Actor* thisx) {
}

s32 sDlists[6] = { object_al_DL_006598, object_al_DL_005920, object_al_DL_005878,
                   object_al_DL_0057D0, object_al_DL_005728, object_al_DL_005680 };
s32 D_80C1C2AC = 0;

void DmAl_Draw(Actor* thisx, PlayState* play) {
    u32 i;
    DmAl* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);
    SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   this->skelAnime.dListCount, func_80C1C028, func_80C1C064, func_80C1C11C,
                                   &this->actor);
    for (i = 0; i < ARRAY_COUNT(this->unkMtx); i++) {
        Matrix_Put(&this->unkMtx[i]);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, sDlists[i]);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}
