/*
 * File: z_dm_zl.c
 * Overlay: ovl_Dm_Zl
 * Description: Child Zelda (Cutscenes)
 */

#include "z_dm_zl.h"
#include "objects/object_zl4/object_zl4.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((DmZl*)thisx)

void DmZl_Init(Actor* thisx, GlobalContext* globalCtx);
void DmZl_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmZl_Update(Actor* thisx, GlobalContext* globalCtx);
void DmZl_Draw(Actor* thisx, GlobalContext* globalCtx);

void DmZl_DoNothing(DmZl* this, GlobalContext* globalCtx);

const ActorInit Dm_Zl_InitVars = {
    ACTOR_DM_ZL,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_ZL4,
    sizeof(DmZl),
    (ActorFunc)DmZl_Init,
    (ActorFunc)DmZl_Destroy,
    (ActorFunc)DmZl_Update,
    (ActorFunc)DmZl_Draw,
};

static AnimationInfo sAnimations[7] = {
    { (AnimationHeader *)0x06015DA0, 1.0f, 0.0f, -1.0f, 0, -10.0f },
    { (AnimationHeader *)0x06015494, 1.0f, 0.0f, -1.0f, 2, -10.0f },
    { (AnimationHeader *)0x06015A4C, 1.0f, 0.0f, -1.0f, 0, -10.0f },
    { (AnimationHeader *)0x06011BB8, 1.0f, 0.0f, -1.0f, 2, -10.0f },
    { (AnimationHeader *)0x060122E0, 1.0f, 0.0f, -1.0f, 0, -10.0f },
    { (AnimationHeader *)0x06012A84, 1.0f, 0.0f, -1.0f, 2, -10.0f },
    { (AnimationHeader *)0x0601303C, 1.0f, 0.0f, -1.0f, 0, -10.0f },
};

static u64* sMouthTextures[4] = {
    gZl4MouthNeutralTex,
    gZl4MouthOpenSmilingTex,
    gZl4MouthFrowningTex,
    gZl4MouthOpenTex,
};

static u64* sEyeTextures[0xA] = {
    gDmZl4EyeOpenLookingUpRightTex,
    gDmZl4EyeOpenHalf2Tex,
    gDmZl4EyeOpenClosedTex,
    gDmZl4EyeWideTex,
    gDmZl4EyeHalf1Tex,
    gDmZl4EyeOpenLookingLeftTex,
    gDmZl4EyeOpenLookingRightTex,
    NULL,
    NULL,
    NULL,
};


void DmZl_ChangeAnimation(SkelAnime *skelAnime, AnimationInfo animation[], u16 index) {
    f32 endFrame;
    animation += index;
    endFrame = (animation->frameCount < 0.0f) ? Animation_GetLastFrame(animation->animation) : animation->frameCount;

    Animation_Change(skelAnime, animation->animation, animation->playSpeed, animation->startFrame, 
          endFrame,
          animation->mode, animation->morphFrames);

}

void DmZl_Init(Actor *thisx, GlobalContext *globalCtx) {
    s32 pad;
    DmZl *this = THIS;

    this->animationIndex = 0;
    this->unused2BA = 0;
    this->actor.targetArrowOffset = 1000.0f;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 24.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gZl4Skeleton, NULL, NULL, NULL, 0);
    DmZl_ChangeAnimation(&this->skelAnime, &sAnimations[this->animationIndex], 0);
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = DmZl_DoNothing;
}

void DmZl_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    DmZl *this = (DmZl *) thisx;
}

void DmZl_DoNothing(DmZl *this, GlobalContext *globalCtx) {
}

// weird cutscene func
void func_80A3830C(DmZl *this, GlobalContext *globalCtx) {
    s32 actionIndex;

    if (Cutscene_CheckActorAction(globalCtx, 0x66) != 0) {
        actionIndex = Cutscene_GetActorActionIndex(globalCtx, 0x66);
        if (globalCtx->csCtx.frames == globalCtx->csCtx.actorActions[actionIndex]->startFrame) {
            s16 newUnk2B0 = 0;

            switch (globalCtx->csCtx.actorActions[actionIndex]->action) {
                case 2:
                    newUnk2B0 = 1;
                    break;
                case 3:
                    newUnk2B0 = 3;
                    break;
                case 4:
                    newUnk2B0 = 5;
                    break;
                case 1:
                default:
                    break;
            }

            if (newUnk2B0 != this->animationIndex) {
                this->animationIndex = newUnk2B0;
                DmZl_ChangeAnimation(&this->skelAnime, &sAnimations[this->animationIndex], 0);
            }
        }

        Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx, actionIndex);
    }

    if ((Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) != 0) &&
           (((actionIndex = this->animationIndex) == 1) || (actionIndex == 3) || (actionIndex == 5))) {
        this->animationIndex++;
        DmZl_ChangeAnimation(&this->skelAnime, &sAnimations[this->animationIndex], 0);
    }
}

void DmZl_UpdateFace(DmZl *this) {
    if (this->timer > 0) {
        this->timer--;
    } else {
        this->timer = 0;
    }

    if (this->timer < 3) {
        this->unk2B3 = this->timer;
        this->unk2B2 = this->timer;
    }

    switch (this->unk2B5) {
        case 0:
            if (this->timer == 0) {
                this->timer = Rand_S16Offset(0x1E, 0x1E);
            }
            break;
        case 1:
            if (this->timer == 0) {
                this->unk2B2 = this->unk2B3 = 2;
            }
            break;
        case 2:
            if (this->timer == 0) {
                this->unk2B2 = 5;
                this->unk2B3 = 6;
            }
            break;
        case 3:
            if (this->timer == 0) {
                this->unk2B2 = 6;
                this->unk2B3 = 5;
            }
            break;
        case 4:
            if (this->timer == 0) {
                this->unk2B2 = this->unk2B3 = 3;
            }
            break;
        case 5:
            if (this->timer == 0) {
                this->unk2B2 = this->unk2B3 = 4;
            }
            break;
        case 6:
            if (this->timer >= 3) {
                this->timer = 0;
            }
            break;
    }

    switch (this->unk2B6) {
        default:
            this->mouthTextureIndex = 0;
            break;
        case 1:
            this->mouthTextureIndex = 1;
            break;
        case 2:
            this->mouthTextureIndex = 2;
            break;
        case 3:
            this->mouthTextureIndex = 3;
            break;
    }

    if (this->animationIndex == 6) {
        this->unk2B2 = this->unk2B3 = 2;
    }
}


void DmZl_Update(Actor *thisx, GlobalContext *globalCtx) {
    DmZl *this = THIS;
    DmZl_UpdateFace(this);
    SkelAnime_Update(&this->skelAnime);
    func_80A3830C(this, globalCtx);
    this->actionFunc(this, globalCtx);
}

s32 DmZl_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    return 0;
}

void DmZl_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx){
    DmZl* this = THIS;

    if (limbIndex == 0x10) {
        if ((this->animationIndex >= 3) && (this->animationIndex < 7)) {
            OPEN_DISPS(globalCtx->state.gfxCtx);

            gSPDisplayList(POLY_OPA_DISP++, &gDl4OcarinaDl);

            CLOSE_DISPS(globalCtx->state.gfxCtx);
        }
    }
}


void DmZl_Draw(Actor *thisx, GlobalContext *globalCtx) {
    DmZl *this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sEyeTextures[this->unk2B3]));

    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(sEyeTextures[this->unk2B2]));

    gSPSegment(POLY_OPA_DISP++, 0x0A, Lib_SegmentedToVirtual(sMouthTextures[this->mouthTextureIndex]));

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount, DmZl_OverrideLimbDraw, DmZl_PostLimbDraw, &this->actor);
    CLOSE_DISPS(globalCtx->state.gfxCtx);

}
