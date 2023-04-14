/*
 * File: z_en_and.c
 * Overlay: ovl_En_And
 * Description: Anju in Wedding Dress
 */

#include "z_en_and.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnAnd*)thisx)

#define EYE_TEXTURES_COUNT 4

void EnAnd_Init(Actor* thisx, PlayState* play);
void EnAnd_Destroy(Actor* thisx, PlayState* play);
void EnAnd_Update(Actor* thisx, PlayState* play);
void EnAnd_Draw(Actor* thisx, PlayState* play);

ActorInit En_And_InitVars = {
    ACTOR_EN_AND,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_AND,
    sizeof(EnAnd),
    (ActorFunc)EnAnd_Init,
    (ActorFunc)EnAnd_Destroy,
    (ActorFunc)EnAnd_Update,
    (ActorFunc)EnAnd_Draw,
};

static AnimationInfoS sAnimationInfo[8] = {
    { &gAndStaticAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gAndIdleAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gAndWalkAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gAndRaiseHeadAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gAndRaisedHeadLoopAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gAndRaiseHandAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gAndRaisedHandLoopAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gAndRaisedHandWalkAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
};

s32 EnAnd_ChangeAnim(EnAnd* this, s32 animIndex) {
    s32 ret = false;

    if (this->animIndex != animIndex) {
        this->animIndex = animIndex;
        ret = SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, animIndex);
    }
    return ret;
}

void EnAnd_Blink(EnAnd* this) {
    if (DECR(this->blinkTimer) == 0) {
        this->eyeTexIndex++;
        if (this->eyeTexIndex >= EYE_TEXTURES_COUNT) {
            this->blinkTimer = Rand_S16Offset(30, 30);
            this->eyeTexIndex = 0;
        }
    }
}

void EnAnd_HandleCsAction(EnAnd* this, PlayState* play) {
    s32 actionAnimations[] = { 0, 1, 2, 3, 5, 7 };
    u16 csAction;
    s32 actionIndex;

    if (play->csCtx.state != CS_STATE_0) {
        if (!this->hasAction) {
            this->action = 0xFF;
            this->hasAction = true;
            this->prevAnimIndex = this->animIndex;
        }
        if (Cutscene_CheckActorAction(play, 0x235)) {
            actionIndex = Cutscene_GetActorActionIndex(play, 0x235);
            csAction = play->csCtx.actorActions[actionIndex]->action;
            if (this->action != (u8)csAction) {
                this->action = csAction;
                EnAnd_ChangeAnim(this, actionAnimations[csAction]);
            }
            switch (this->action) {
                case 3:
                case 4:
                    if ((this->animIndex == 3) || (this->animIndex == 5)) {
                        if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                            EnAnd_ChangeAnim(this, this->animIndex + 1);
                        }
                    }
                    break;
            }
            Cutscene_ActorTranslateAndYaw(&this->actor, play, actionIndex);
        }
    } else if (this->hasAction) {
        this->hasAction = false;
        EnAnd_ChangeAnim(this, this->prevAnimIndex);
    }
}

void EnAnd_Init(Actor* thisx, PlayState* play) {
    EnAnd* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 14.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &gAndSkel, NULL, this->jointTable, this->morphTable,
                       OBJECT_AND_LIMB_MAX);
    this->animIndex = -1;
    EnAnd_ChangeAnim(this, 0);
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->flags |= 8;
    this->actionFunc = EnAnd_HandleCsAction;
}

void EnAnd_Destroy(Actor* thisx, PlayState* play) {
}

void EnAnd_Update(Actor* thisx, PlayState* play) {
    EnAnd* this = THIS;

    this->actionFunc(this, play);
    SkelAnime_Update(&this->skelAnime);
    EnAnd_Blink(this);
}

void EnAnd_TransformLimbDraw(PlayState* play, s32 limbIndex, Actor* thisx) {
    EnAnd* this = THIS;
    s32 stepRot;
    s32 overrideRot;

    stepRot = this->flags & 8 ? false : true;
    overrideRot = this->flags & 2 ? true : false;
    if (!stepRot) {
        overrideRot = false;
    }

    if (limbIndex != OBJECT_AND_LIMB_TORSO) {
        if (limbIndex == OBJECT_AND_LIMB_HEAD) {
            SubS_UpdateLimb(this->headRotZ + this->torsoRotZ + 0x4000,
                            this->headRotY + this->torsoRotY + this->actor.shape.rot.y + 0x4000, &this->headComputedPos,
                            &this->headComputedRot, stepRot, overrideRot);
            Matrix_Pop();
            Matrix_Translate(this->headComputedPos.x, this->headComputedPos.y, this->headComputedPos.z, MTXMODE_NEW);
            Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
            Matrix_RotateYS(this->headComputedRot.y, MTXMODE_APPLY);
            Matrix_RotateXS(this->headComputedRot.x, MTXMODE_APPLY);
            Matrix_RotateZS(this->headComputedRot.z, MTXMODE_APPLY);
            Matrix_Push();
        }
    } else {
        SubS_UpdateLimb(this->torsoRotZ + 0x4000, this->torsoRotY + this->actor.shape.rot.y + 0x4000,
                        &this->torsoComputedPos, &this->torsoComputedRot, stepRot, overrideRot);
        Matrix_Pop();
        Matrix_Translate(this->torsoComputedPos.x, this->torsoComputedPos.y, this->torsoComputedPos.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateYS(this->torsoComputedRot.y, MTXMODE_APPLY);
        Matrix_RotateXS(this->torsoComputedRot.x, MTXMODE_APPLY);
        Matrix_RotateZS(this->torsoComputedRot.z, MTXMODE_APPLY);
        Matrix_Push();
    }
}

void EnAnd_Draw(Actor* thisx, PlayState* play) {
    static TexturePtr sMouthTextures[] = { gAndMouthNeutralTex, gAndMouthSmileTex };
    static TexturePtr sEyeTextures[] = {
        gAndEyeOpenTex,
        gAndEyeClosingTex,
        gAndEyeClosedTex,
        gAndEyeOpeningTex,
    };
    EnAnd* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sEyeTextures[this->eyeTexIndex]));
    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(sMouthTextures[0]));

    SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   this->skelAnime.dListCount, NULL, NULL, EnAnd_TransformLimbDraw, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}
