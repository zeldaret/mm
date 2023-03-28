/*
 * File: z_en_and.c
 * Overlay: ovl_En_And
 * Description: Anju in Wedding Dress
 */

#include "z_en_and.h"
#include "objects/object_and/object_and.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnAnd*)thisx)

void EnAnd_Init(Actor* thisx, PlayState* play);
void EnAnd_Destroy(Actor* thisx, PlayState* play);
void EnAnd_Update(Actor* thisx, PlayState* play);
void EnAnd_Draw(Actor* thisx, PlayState* play);

void EnAnd_HandleCsAction(EnAnd* this, PlayState* play);

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
    { &object_and_Anim_0000C8, 1.0f, 0, -1, 0, 0 },
    { &object_and_Anim_0122D0, 1.0f, 0, -1, 0, 0 },
    { &object_and_Anim_00DA58, 1.0f, 0, -1, 0, 0 },
    { &object_and_Anim_00FE64, 1.0f, 0, -1, 2, 0 },
    { &object_and_Anim_01067C, 1.0f, 0, -1, 0, 0 },
    { &object_and_Anim_00EE00, 1.0f, 0, -1, 2, 0 },
    { &object_and_Anim_00F6C4, 1.0f, 0, -1, 0, 0 },
    { &object_and_Anim_011AFC, 1.0f, 0, -1, 2, 0 },
};

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_And/EnAnd_ChangeAnimation.s")
s32 EnAnd_ChangeAnimation(EnAnd* this, s32 animIndex) {
    s32 ret = false;

    if (this->animIndex != animIndex) {
        this->animIndex = animIndex;
        ret = SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, animIndex);
    }
    return ret;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_And/EnAnd_Blink.s")
void EnAnd_Blink(EnAnd* this) {
    if (DECR(this->blinkTimer) == 0) {
        this->eyeTexIndex++;
        if (this->eyeTexIndex >= 4) {
            this->blinkTimer = Rand_S16Offset(30, 30);
            this->eyeTexIndex = 0;
        }
    }
}

void EnAnd_HandleCsAction(EnAnd* this, PlayState* play) {
    // Action animations
    s32 D_80C19200[] = { // TODO: Rename accordingly? Other similar code has not done so.
        0x00000000,
        0x00000001,
        0x00000002,
        0x00000003,
        0x00000005,
        0x00000007,
    };
    u16 csAction;
    s32 actionIndex;

    if (play->csCtx.state != 0) {
        if (!this->unk30C) { // TODO: prevPlaying?
            this->unk18C = 0xFF; // TODO: prevAction?
            this->unk30C = true;
            this->unk308 = this->animIndex; // TODO: startAnimIndex?
        }
        if (Cutscene_CheckActorAction(play, 0x235U)) {
            actionIndex = Cutscene_GetActorActionIndex(play, 0x235U);
            csAction = play->csCtx.actorActions[actionIndex]->action;
            if (this->unk18C != (u8)csAction) {
                this->unk18C = csAction;
                EnAnd_ChangeAnimation(this, D_80C19200[csAction]);
            }
            switch (this->unk18C) {
                case 3:
                case 4:
                    if ((this->animIndex == 3) || (this->animIndex == 5)) {
                        if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                            EnAnd_ChangeAnimation(this, this->animIndex + 1);
                        }
                    }
                    break;
            }
            Cutscene_ActorTranslateAndYaw(&this->actor, play, actionIndex);
        }
    } else if (this->unk30C) {
        this->unk30C = false;
        EnAnd_ChangeAnimation(this, this->unk308);
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_And/EnAnd_Init.s")
void EnAnd_Init(Actor* thisx, PlayState* play) {
    EnAnd* this = THIS;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 14.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &object_and_Skel_00B380, NULL, this->jointTable, this->morphTable, 26);
    this->animIndex = -1;
    EnAnd_ChangeAnimation(this, 0);
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.flags &= ~1;
    this->unk2F0 |= 8; // TODO: Is there any good name for this?
    this->actionFunc = EnAnd_HandleCsAction;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_And/EnAnd_Destroy.s")
void EnAnd_Destroy(Actor* thisx, PlayState* play) {
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_And/EnAnd_Update.s")
void EnAnd_Update(Actor* thisx, PlayState* play) {
    EnAnd* this = THIS;
    this->actionFunc(this, play);
    SkelAnime_Update(&this->skelAnime);
    EnAnd_Blink(this);
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_And/EnAnd_TransformLimbDraw.s")
void EnAnd_TransformLimbDraw(PlayState* play, s32 limbIndex, Actor* thisx) {
    EnAnd* this = THIS;

    s32 stepRot;
    s32 overrideRot;

    stepRot = this->unk2F0 & 8 ? false : true;
    overrideRot = this->unk2F0 & 2 ? true : false;
    if (!stepRot) {
        overrideRot = false;
    }

    if (limbIndex != 2) {
        if (limbIndex == 18) {
            SubS_UpdateLimb(this->unk2F6 + this->unk2FA + 0x4000, this->unk2F8 + this->unk2FC + this->actor.shape.rot.y + 0x4000, &this->limbPos1, &this->limbRot1, stepRot, overrideRot);
            Matrix_Pop();
            Matrix_Translate(this->limbPos1.x, this->limbPos1.y, this->limbPos1.z, MTXMODE_NEW);
            Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
            Matrix_RotateYS(this->limbRot1.y, MTXMODE_APPLY);
            Matrix_RotateXS(this->limbRot1.x, MTXMODE_APPLY);
            Matrix_RotateZS(this->limbRot1.z, MTXMODE_APPLY);
            Matrix_Push();
        }
    } else {
        SubS_UpdateLimb(this->unk2FA + 0x4000, this->unk2FC + this->actor.shape.rot.y + 0x4000, &this->limbPos2, &this->limbRot2, stepRot, overrideRot);
        Matrix_Pop();
        Matrix_Translate(this->limbPos2.x, this->limbPos2.y, this->limbPos2.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateYS(this->limbRot2.y, MTXMODE_APPLY);
        Matrix_RotateXS(this->limbRot2.x, MTXMODE_APPLY);
        Matrix_RotateZS(this->limbRot2.z, MTXMODE_APPLY);
        Matrix_Push();
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_And/EnAnd_Draw.s")
void EnAnd_Draw(Actor* thisx, PlayState* play) {
    static TexturePtr sMouthTextures[2] = { object_and_Tex_009DF0, object_and_Tex_00A1F0 };
    static TexturePtr sEyeTextures[4] = {
        object_and_Tex_007DF0,
        object_and_Tex_0085F0,
        object_and_Tex_008DF0,
        object_and_Tex_0095F0,
    };

    EnAnd* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sEyeTextures[this->eyeTexIndex]));
    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(sMouthTextures[0]));

    SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, (s32) this->skelAnime.dListCount, NULL, NULL, EnAnd_TransformLimbDraw, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}
