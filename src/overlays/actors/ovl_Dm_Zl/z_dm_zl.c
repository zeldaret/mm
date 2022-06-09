/*
 * File: z_dm_zl.c
 * Overlay: ovl_Dm_Zl
 * Description: Child Zelda (Re-learning Song of Time cutscene)
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
    { &gDmZl4FacingAwayHandsOverEmblemLoop, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, -10.0f },
    { &gDmZl4TurningAround2Anim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, -10.0f },
    { &gDmZl4HandsOverEmblemLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, -10.0f },
    { &gDmZl4GivingItemStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, -10.0f },
    { &gDmZl4GivingItemLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, -10.0f },
    { &gDmZl4RaisingOcarinaToPlayAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, -10.0f },
    { &gDmZl4PlayingOcarinaAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, -10.0f },
};

typedef enum {
    ZELDA_ANIM_FACING_AWAY,
    ZELDA_ANIM_TURNING_TOWARD_PLAYER,
    ZELDA_ANIM_FACING_PLAYER,
    ZELDA_ANIM_GIVING_OCARINA_START,
    ZELDA_ANIM_GIVING_OCARINA,
    ZELDA_ANIM_PLAYING_OCARINA_START,
    ZELDA_ANIM_PLAYING_OCARINA,
    ZELDA_ANIM_MAX,
} DmZlAnimations;

static TexturePtr sMouthTextures[4] = {
    gZl4MouthNeutralTex,
    gZl4MouthOpenSmilingTex,
    gZl4MouthFrowningTex,
    gZl4MouthOpenTex,
};

typedef enum {
    ZELDA_MOUTH_NEUTRAL,
    ZELDA_MOUTH_SMILING,
    ZELDA_MOUTH_FROWNING,
    ZELDA_MOUTH_OPEN,
} DmZlMouthTextures;

static TexturePtr sEyeTextures[] = {
    gDmZl4EyeOpenLookingUpRightTex,
    gDmZl4EyeOpenHalf2Tex,
    gDmZl4EyeOpenClosedTex,
    gDmZl4EyeWideTex,
    gDmZl4EyeHalf1Tex,
    gDmZl4EyeOpenLookingLeftTex,
    gDmZl4EyeOpenLookingRightTex,
};

void DmZl_ChangeAnimation(SkelAnime* skelAnime, AnimationInfo animation[], u16 index) {
    f32 endFrame;

    animation += index;
    endFrame = (animation->frameCount < 0.0f) ? Animation_GetLastFrame(animation->animation) : animation->frameCount;

    Animation_Change(skelAnime, animation->animation, animation->playSpeed, animation->startFrame, endFrame,
                     animation->mode, animation->morphFrames);
}

void DmZl_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    DmZl* this = THIS;

    this->animationIndex = 0;
    this->unused2BA = 0;
    this->actor.targetArrowOffset = 1000.0f;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 24.0f);
    // these three set to NULL should mean they are dynamically allocated
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gZl4Skeleton, NULL, NULL, NULL, 0);
    DmZl_ChangeAnimation(&this->skelAnime, &sAnimations[this->animationIndex], ZELDA_ANIM_FACING_AWAY);
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = DmZl_DoNothing;
}

void DmZl_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void DmZl_DoNothing(DmZl* this, GlobalContext* globalCtx) {
}

void DmZl_UpdateCutscene(DmZl* this, GlobalContext* globalCtx) {
    s32 actionIndex;

    if (Cutscene_CheckActorAction(globalCtx, 0x66)) { // currently in cutscene
        actionIndex = Cutscene_GetActorActionIndex(globalCtx, 0x66);
        if (globalCtx->csCtx.frames == globalCtx->csCtx.actorActions[actionIndex]->startFrame) {
            s16 nextAnimationIndex = ZELDA_ANIM_FACING_AWAY;

            switch (globalCtx->csCtx.actorActions[actionIndex]->action) {
                case 2:
                    nextAnimationIndex = ZELDA_ANIM_TURNING_TOWARD_PLAYER;
                    break;
                case 3:
                    nextAnimationIndex = ZELDA_ANIM_GIVING_OCARINA_START;
                    break;
                case 4:
                    nextAnimationIndex = ZELDA_ANIM_PLAYING_OCARINA_START;
                    break;
                case 1:
                default:
                    break;
            }

            if (nextAnimationIndex != this->animationIndex) {
                this->animationIndex = nextAnimationIndex;
                DmZl_ChangeAnimation(&this->skelAnime, &sAnimations[this->animationIndex], ZELDA_ANIM_FACING_AWAY);
            }
        }

        Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx, actionIndex);
    }

    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) != 0) {
        actionIndex = this->animationIndex;
        if ((actionIndex == 1) || (actionIndex == 3) || (actionIndex == 5)) {
            this->animationIndex++;
            DmZl_ChangeAnimation(&this->skelAnime, &sAnimations[this->animationIndex], ZELDA_ANIM_FACING_AWAY);
        }
    }
}

/**
 * Updates the eye blinking and state, and mouth textures.
 *  (Assumption: these modifications are from outside of this actor by a cutscene).
 */
void DmZl_UpdateFace(DmZl* this) {
    if (this->blinkTimer > 0) {
        this->blinkTimer--;
    } else {
        this->blinkTimer = 0;
    }

    if (this->blinkTimer < 3) {
        this->eyeTextureIndex2 = this->blinkTimer;
        this->eyeTextureIndex1 = this->blinkTimer;
    }

    switch (this->nextEyeState) {
        case 0:
            if (this->blinkTimer == 0) {
                this->blinkTimer = Rand_S16Offset(30, 30);
            }
            break;
        case 1:
            if (this->blinkTimer == 0) {
                this->eyeTextureIndex1 = this->eyeTextureIndex2 = 2;
            }
            break;
        case 2:
            if (this->blinkTimer == 0) {
                this->eyeTextureIndex1 = 5;
                this->eyeTextureIndex2 = 6;
            }
            break;
        case 3:
            if (this->blinkTimer == 0) {
                this->eyeTextureIndex1 = 6;
                this->eyeTextureIndex2 = 5;
            }
            break;
        case 4:
            if (this->blinkTimer == 0) {
                this->eyeTextureIndex1 = this->eyeTextureIndex2 = 3;
            }
            break;
        case 5:
            if (this->blinkTimer == 0) {
                this->eyeTextureIndex1 = this->eyeTextureIndex2 = 4;
            }
            break;
        case 6:
            if (this->blinkTimer >= 3) {
                this->blinkTimer = 0;
            }
            break;
    }

    switch (this->nextMouthMouth) {
        default:
            this->mouthTextureIndex = ZELDA_MOUTH_NEUTRAL;
            break;
        case 1:
            this->mouthTextureIndex = ZELDA_MOUTH_SMILING;
            break;
        case 2:
            this->mouthTextureIndex = ZELDA_MOUTH_FROWNING;
            break;
        case 3:
            this->mouthTextureIndex = ZELDA_MOUTH_OPEN;
            break;
    }

    if (this->animationIndex == ZELDA_ANIM_PLAYING_OCARINA) {
        // override blinking: eyes closed while playing ocarina
        this->eyeTextureIndex1 = this->eyeTextureIndex2 = 2;
    }
}

void DmZl_Update(Actor* thisx, GlobalContext* globalCtx) {
    DmZl* this = THIS;

    DmZl_UpdateFace(this);
    SkelAnime_Update(&this->skelAnime);
    DmZl_UpdateCutscene(this, globalCtx);
    this->actionFunc(this, globalCtx);
}

s32 DmZl_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    return false;
}

void DmZl_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    DmZl* this = THIS;

    if (limbIndex == ZL4_LIMB_RIGHT_HAND) {
        if ((this->animationIndex >= ZELDA_ANIM_GIVING_OCARINA_START) && (this->animationIndex < ZELDA_ANIM_MAX)) {
            OPEN_DISPS(globalCtx->state.gfxCtx);

            gSPDisplayList(POLY_OPA_DISP++, gDmZl4OcarinaDL);

            CLOSE_DISPS(globalCtx->state.gfxCtx);
        }
    }
}

void DmZl_Draw(Actor* thisx, GlobalContext* globalCtx) {
    DmZl* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sEyeTextures[this->eyeTextureIndex2]));

    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(sEyeTextures[this->eyeTextureIndex1]));

    gSPSegment(POLY_OPA_DISP++, 0x0A, Lib_SegmentedToVirtual(sMouthTextures[this->mouthTextureIndex]));

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          DmZl_OverrideLimbDraw, DmZl_PostLimbDraw, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
