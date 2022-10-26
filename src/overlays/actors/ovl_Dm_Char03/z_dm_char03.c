/*
 * File: z_dm_char03.c
 * Overlay: ovl_Dm_Char03
 * Description: Deku Mask (cutscene)
 */

#include "z_dm_char03.h"
#include "objects/object_osn/object_osn.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DmChar03*)thisx)

void DmChar03_Init(Actor* thisx, PlayState* play);
void DmChar03_Destroy(Actor* thisx, PlayState* play);
void DmChar03_Update(Actor* thisx, PlayState* play);
void DmChar03_Draw(Actor* thisx, PlayState* play);

void func_80AAB644(DmChar03* this, PlayState* play);
void DmChar03_DoNothing(DmChar03* this, PlayState* play);
void func_80AABA84(PlayState* play, DmChar03* this);

ActorInit Dm_Char03_InitVars = {
    ACTOR_DM_CHAR03,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_OSN,
    sizeof(DmChar03),
    (ActorFunc)DmChar03_Init,
    (ActorFunc)DmChar03_Destroy,
    (ActorFunc)DmChar03_Update,
    (ActorFunc)DmChar03_Draw,
};

AnimationInfo sAnimationInfo[] = {
    { &gDekuMaskFallOverAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
};

void DmChar03_ChangeAnim(SkelAnime* skelAnime, AnimationInfo* animationInfo, u16 animIndex) {
    f32 frame;

    animationInfo += animIndex;

    if (animationInfo->frameCount < 0.0f) {
        frame = Animation_GetLastFrame(animationInfo->animation);
    } else {
        frame = animationInfo->frameCount;
    }
    Animation_Change(skelAnime, animationInfo->animation, animationInfo->playSpeed, animationInfo->startFrame, frame,
                     animationInfo->mode, animationInfo->morphFrames);
}

void DmChar03_Init(Actor* thisx, PlayState* play) {
    DmChar03* this = THIS;

    this->animIndex = 0;
    this->actor.targetArrowOffset = 3000.0f;
    this->unk_18E = false;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 24.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &gDekuMaskSkel, NULL, NULL, NULL, 0);
    DmChar03_ChangeAnim(&this->skelAnime, sAnimationInfo, 0);
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = DmChar03_DoNothing;
}

void DmChar03_Destroy(Actor* thisx, PlayState* play) {
}

void func_80AAB5F8(DmChar03* this, PlayState* play) {
    s32 index = Object_GetIndex(&play->objectCtx, OBJECT_GI_NUTSMASK);

    if (index >= 0) {
        this->objectIndex = index;
        this->actionFunc = func_80AAB644;
    }
}

void func_80AAB644(DmChar03* this, PlayState* play) {
    if (Cutscene_CheckActorAction(play, 0x88)) {
        s32 index = Cutscene_GetActorActionIndex(play, 0x88);

        if (play->csCtx.actorActions[index]->action == 4) {
            this->unk_18E = true;
            this->offset.x = play->csCtx.actorActions[index]->startPos.x;
            this->offset.y = play->csCtx.actorActions[index]->startPos.y;
            this->offset.z = play->csCtx.actorActions[index]->startPos.z;
        }
    }
}

void DmChar03_DoNothing(DmChar03* this, PlayState* play) {
}

void func_80AAB710(DmChar03* this, PlayState* play) {
    u8 shouldChangeAnim = true;

    if (Cutscene_CheckActorAction(play, 0x88)) {
        s32 index = Cutscene_GetActorActionIndex(play, 0x88);

        if (play->csCtx.frames == play->csCtx.actorActions[index]->startFrame) {
            switch (play->csCtx.actorActions[index]->action) {
                case 1:
                    shouldChangeAnim = false;
                    break;
                case 2:
                    this->animIndex = 0;
                    break;
                case 3:
                    this->unk_18E = false;
                    shouldChangeAnim = false;
                    Actor_Kill(&this->actor);
                    break;
                case 4:
                    Item_Give(play, ITEM_MASK_DEKU);
                    shouldChangeAnim = false;
                    this->actionFunc = func_80AAB5F8;
                    break;
                default:
                    shouldChangeAnim = false;
                    break;
            }

            if (shouldChangeAnim) {
                DmChar03_ChangeAnim(&this->skelAnime, &sAnimationInfo[this->animIndex], 0);
            }
        }
        Cutscene_ActorTranslateAndYaw(&this->actor, play, index);
    }
}

void func_80AAB838(DmChar03* this, PlayState* play) {
    if (Animation_OnFrame(&this->skelAnime, 5.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_IT_MASK_BOUND_0);
    } else if ((Animation_OnFrame(&this->skelAnime, 10.0f)) || (Animation_OnFrame(&this->skelAnime, 18.0f)) ||
               (Animation_OnFrame(&this->skelAnime, 30.0f)) || (Animation_OnFrame(&this->skelAnime, 38.0f))) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_IT_MASK_BOUND_1);
    }
}

void DmChar03_Update(Actor* thisx, PlayState* play) {
    DmChar03* this = THIS;

    if (Cutscene_CheckActorAction(play, 0x88) &&
        (play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 0x88)]->action == 2)) {
        SkelAnime_Update(&this->skelAnime);
    }
    this->actionFunc(this, play);
    func_80AAB710(this, play);
    func_80AAB838(this, play);
}

s32 DmChar03_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    return false;
}

void DmChar03_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
}

void DmChar03_TransformLimbDraw(PlayState* play, s32 limbIndex, Actor* thisx) {
}

void DmChar03_Draw(Actor* thisx, PlayState* play) {
    DmChar03* this = THIS;

    if (!this->unk_18E) {
        if ((Cutscene_CheckActorAction(play, 0x88)) &&
            (play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 0x88)]->action != 1)) {
            func_8012C28C(play->state.gfxCtx);
            SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                           this->skelAnime.dListCount, DmChar03_OverrideLimbDraw, DmChar03_PostLimbDraw,
                                           DmChar03_TransformLimbDraw, &this->actor);
        }
    } else {
        func_80AABA84(play, this);
    }
}

void func_80AABA84(PlayState* play, DmChar03* this) {
    s32 pad;

    if (this->actor.objBankIndex == this->objectIndex) {
        Matrix_Translate(this->offset.x, this->offset.y, this->offset.z, MTXMODE_NEW);
        Matrix_RotateZYX(0, (play->gameplayFrames * 0x3E8), 0, MTXMODE_APPLY);
        Matrix_Scale(0.2f, 0.2f, 0.2f, MTXMODE_APPLY);
        GetItem_Draw(play, GID_MASK_DEKU);
    }
    if (Object_IsLoaded(&play->objectCtx, this->objectIndex)) {
        this->actor.objBankIndex = this->objectIndex;
    }
}
