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

void func_80C18C50(EnAnd* this, PlayState* play);
void func_80C18ED0(PlayState* play, s32 limbIndex, Actor* thisx);

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

static AnimationInfoS D_80C19180[8] = {
    { &object_and_Anim_0000C8, 1.0f, 0, -1, 0, 0 },
    { &object_and_Anim_0122D0, 1.0f, 0, -1, 0, 0 },
    { &object_and_Anim_00DA58, 1.0f, 0, -1, 0, 0 },
    { &object_and_Anim_00FE64, 1.0f, 0, -1, 2, 0 },
    { &object_and_Anim_01067C, 1.0f, 0, -1, 0, 0 },
    { &object_and_Anim_00EE00, 1.0f, 0, -1, 2, 0 },
    { &object_and_Anim_00F6C4, 1.0f, 0, -1, 0, 0 },
    { &object_and_Anim_011AFC, 1.0f, 0, -1, 2, 0 },
};

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_And/func_80C18B90.s")
s32 func_80C18B90(EnAnd* this, s32 animIndex) { // Change animation
    s32 ret = false;

    if (this->currentAnim != animIndex) {
        this->currentAnim = animIndex;
        ret = SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80C19180, animIndex);
    }
    return ret;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_And/func_80C18BD8.s")
void func_80C18BD8(EnAnd* this) { // Blink
    if (DECR(this->blinkTimer) == 0) {
        this->eyeTexIndex++;
        if (this->eyeTexIndex >= 4) {
            this->blinkTimer = Rand_S16Offset(30, 30);
            this->eyeTexIndex = 0;
        }
    }
}

void func_80C18C50(EnAnd* this, PlayState* play) {
    s32 D_80C19200[] = {
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
        if (!this->unk30C) {
            this->unk18C = 0xFF;
            this->unk30C = true;
            this->unk308 = this->currentAnim;
        }
        if (Cutscene_CheckActorAction(play, 0x235U)) {
            actionIndex = Cutscene_GetActorActionIndex(play, 0x235U);
            csAction = play->csCtx.actorActions[actionIndex]->action;
            if (this->unk18C != (u8)csAction) {
                this->unk18C = csAction;
                func_80C18B90(this, D_80C19200[csAction]);
            }
            switch (this->unk18C) {
                case 3:
                case 4:
                    if ((this->currentAnim == 3) || (this->currentAnim == 5)) {
                        if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                            func_80C18B90(this, this->currentAnim + 1);
                        }
                    }
                    break;
            }
            Cutscene_ActorTranslateAndYaw(&this->actor, play, actionIndex);
        }
    } else if (this->unk30C) {
        this->unk30C = false;
        func_80C18B90(this, this->unk308);
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_And/EnAnd_Init.s")
void EnAnd_Init(Actor* thisx, PlayState* play) {
    EnAnd* this = THIS;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 14.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &object_and_Skel_00B380, NULL, this->jointTable, this->morphTable, 26);
    this->currentAnim = -1;
    func_80C18B90(this, 0);
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.flags &= ~1;
    this->unk2F0 |= 8;
    this->actionFunc = func_80C18C50;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_And/EnAnd_Destroy.s")
void EnAnd_Destroy(Actor* thisx, PlayState* play) {
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_And/EnAnd_Update.s")
void EnAnd_Update(Actor* thisx, PlayState* play) {
    EnAnd* this = THIS;
    this->actionFunc(this, play);
    SkelAnime_Update(&this->skelAnime);
    func_80C18BD8(this);
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_And/func_80C18ED0.s")
void func_80C18ED0(PlayState* play, s32 limbIndex, Actor* thisx) { // TransformLimbDraw
    EnAnd* this = THIS;

    s32 stepRot;
    s32 overrideRot;

    stepRot = this->unk2F0 & 8 ? 0 : 1;
    overrideRot = this->unk2F0 & 2 ? 1 : 0;
    if (!stepRot) {
        overrideRot = 0;
    }

    if (limbIndex != 2) {
        if (limbIndex == 0x12) {
            SubS_UpdateLimb(this->unk2F6 + this->unk2FA + 0x4000, this->unk2F8 + this->unk2FC + this->actor.shape.rot.y + 0x4000, &this->unk194, &this->unk1AC, stepRot, overrideRot);
            Matrix_Pop();
            Matrix_Translate(this->unk194.x, this->unk194.y, this->unk194.z, MTXMODE_NEW);
            Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
            Matrix_RotateYS(this->unk1AC.y, MTXMODE_APPLY);
            Matrix_RotateXS(this->unk1AC.x, MTXMODE_APPLY);
            Matrix_RotateZS(this->unk1AC.z, MTXMODE_APPLY);
            Matrix_Push();
        }
    } else {
        SubS_UpdateLimb(this->unk2FA + 0x4000, this->unk2FC + this->actor.shape.rot.y + 0x4000, &this->unk1A0, &this->unk1B2, stepRot, overrideRot);
        Matrix_Pop();
        Matrix_Translate(this->unk1A0.x, this->unk1A0.y, this->unk1A0.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateYS(this->unk1B2.y, MTXMODE_APPLY);
        Matrix_RotateXS(this->unk1B2.x, MTXMODE_APPLY);
        Matrix_RotateZS(this->unk1B2.z, MTXMODE_APPLY);
        Matrix_Push();
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_And/EnAnd_Draw.s")
void EnAnd_Draw(Actor* thisx, PlayState* play) {
    static void* D_80C19218[2] = { object_and_Tex_009DF0, object_and_Tex_00A1F0 };
    static void* D_80C19220[4] = {
        object_and_Tex_007DF0,
        object_and_Tex_0085F0,
        object_and_Tex_008DF0,
        object_and_Tex_0095F0,
    };

    EnAnd* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80C19220[this->eyeTexIndex]));
    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(D_80C19218[0]));

    SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, (s32) this->skelAnime.dListCount, NULL, NULL, func_80C18ED0, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}
