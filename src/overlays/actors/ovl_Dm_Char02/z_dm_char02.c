/*
 * File: z_dm_char02.c
 * Overlay: ovl_Dm_Char02
 * Description: The Ocarina of Time that for the scenes on the Clock Tower's rooftop.
 */

#include "z_dm_char02.h"
#include "objects/object_stk2/object_stk2.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DmChar02*)thisx)

void DmChar02_Init(Actor* thisx, PlayState* play);
void DmChar02_Destroy(Actor* thisx, PlayState* play);
void DmChar02_Update(Actor* thisx, PlayState* play);
void DmChar02_Draw(Actor* thisx, PlayState* play);

void DmChar02_PerformCutsceneActions(DmChar02* this, PlayState* play);

const ActorInit Dm_Char02_InitVars = {
    ACTOR_DM_CHAR02,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_STK2,
    sizeof(DmChar02),
    (ActorFunc)DmChar02_Init,
    (ActorFunc)DmChar02_Destroy,
    (ActorFunc)DmChar02_Update,
    (ActorFunc)DmChar02_Draw,

};

typedef enum {
    /* 0 */ DMCHAR02_ANIMATION_HIT_GROUND,
    /* 1 */ DMCHAR02_ANIMATION_TURN_AROUND,
    /* 2 */ DMCHAR02_ANIMATION_JUGGLE,
    /* 3 */ DMCHAR02_ANIMATION_FALL,
} DmChar02AnimationIndex;

static AnimationInfo sAnimations[] = {
    { &gClockTowerOcarinaOfTimeHitGroundAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gClockTowerOcarinaOfTimeTurnAroundAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gClockTowerOcarinaOfTimeJuggleAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gClockTowerOcarinaOfTimeFallAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
};

void DmChar02_ChangeAnimation(SkelAnime* skelAnime, AnimationInfo* animation, u16 index) {
    f32 frameCount;

    animation += index;

    if (animation->frameCount < 0.0f) {
        frameCount = Animation_GetLastFrame(animation->animation);
    } else {
        frameCount = animation->frameCount;
    }

    Animation_Change(skelAnime, animation->animation, animation->playSpeed, animation->startFrame, frameCount,
                     animation->mode, animation->morphFrames);
}

void DmChar02_PlaySfxForDroppingOcarinaCutscene(DmChar02* this, PlayState* play) {
    switch (play->csCtx.frames) {
        case 95:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_OCARINA_BOUND_0);
            break;

        case 101:
        case 105:
        case 112:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_OCARINA_BOUND_1);
            break;
    }
}

void DmChar02_PlaySfxForCutscenes(DmChar02* this, PlayState* play) {
    if ((play->csCtx.state != 0) && (play->sceneNum == SCENE_OKUJOU) && (play->csCtx.currentCsIndex == 1)) {
        DmChar02_PlaySfxForDroppingOcarinaCutscene(this, play);
    }
}

void DmChar02_Init(Actor* thisx, PlayState* play) {
    DmChar02* this = THIS;

    if (gSaveContext.save.inventory.items[SLOT_OCARINA] == ITEM_NONE) {
        this->animIndex = DMCHAR02_ANIMATION_HIT_GROUND;
        this->actor.targetArrowOffset = 3000.0f;
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 24.0f);
        SkelAnime_InitFlex(play, &this->skelAnime, &gClockTowerOcarinaOfTimeSkel, NULL, NULL, NULL, 0);
        DmChar02_ChangeAnimation(&this->skelAnime, sAnimations, 0);
        Actor_SetScale(&this->actor, 0.01f);
        this->actionFunc = DmChar02_PerformCutsceneActions;
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

void DmChar02_Destroy(Actor* thisx, PlayState* play) {
}

void DmChar02_PerformCutsceneActions(DmChar02* this, PlayState* play) {
    u8 shouldChangeAnimation = true;
    s32 actionIndex;

    if (Cutscene_CheckActorAction(play, 0x83)) {
        actionIndex = Cutscene_GetActorActionIndex(play, 0x83);
        if (play->csCtx.frames == play->csCtx.actorActions[actionIndex]->startFrame) {
            switch (play->csCtx.actorActions[actionIndex]->action) {
                default:
                    this->animIndex = DMCHAR02_ANIMATION_HIT_GROUND;
                    shouldChangeAnimation = false;
                    break;

                case 1:
                    this->animIndex = DMCHAR02_ANIMATION_HIT_GROUND;
                    break;

                case 2:
                    this->animIndex = DMCHAR02_ANIMATION_TURN_AROUND;
                    break;

                case 4:
                    this->animIndex = DMCHAR02_ANIMATION_FALL;
                    break;
            }

            if (shouldChangeAnimation) {
                DmChar02_ChangeAnimation(&this->skelAnime, &sAnimations[this->animIndex], 0);
            }
        }

        Cutscene_ActorTranslateAndYaw(&this->actor, play, actionIndex);
    }

    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        if (this->animIndex == DMCHAR02_ANIMATION_TURN_AROUND) {
            this->animIndex++;
            DmChar02_ChangeAnimation(&this->skelAnime, &sAnimations[this->animIndex], 0);
        }
    }
}

void DmChar02_Update(Actor* thisx, PlayState* play) {
    DmChar02* this = THIS;

    SkelAnime_Update(&this->skelAnime);
    this->unk_2F0 = this->unk_2F0;
    this->actionFunc(this, play);
    if (!Actor_HasParent(&this->actor, play)) {
        Actor_PickUp(&this->actor, play, GI_OCARINA, 30.0f, 80.0f);
    } else {
        gSaveContext.save.playerForm = PLAYER_FORM_HUMAN;
        Actor_MarkForDeath(&this->actor);
    }

    DmChar02_PlaySfxForCutscenes(this, play);
}

s32 DmChar02_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    return false;
}

void DmChar02_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
}

void DmChar02_TransformLimbDraw(PlayState* play, s32 limbIndex, Actor* thisx) {
}

void DmChar02_Draw(Actor* thisx, PlayState* play) {
    s32 pad[2];
    DmChar02* this = THIS;
    s32 shouldDraw = false;

    if ((play->csCtx.state == 0) && (this->actor.world.pos.y < 100.0f)) {
        shouldDraw = true;
    } else if (Cutscene_CheckActorAction(play, 0x6B)) {
        switch (play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 0x6B)]->action) {
            case 0x17:
            case 0x1C:
            case 0x26:
                shouldDraw = true;
                break;
        }
    }

    if (shouldDraw) {
        func_8012C28C(play->state.gfxCtx);
        SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                       this->skelAnime.dListCount, DmChar02_OverrideLimbDraw, DmChar02_PostLimbDraw,
                                       DmChar02_TransformLimbDraw, &this->actor);
    }
}
