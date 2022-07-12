/*
 * File: z_dm_char02.c
 * Overlay: ovl_Dm_Char02
 * Description: Ocarina of Time (dropped from Skull Kid's hand)
 */

#include "z_dm_char02.h"
#include "objects/object_stk2/object_stk2.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DmChar02*)thisx)

void DmChar02_Init(Actor* thisx, PlayState* play);
void DmChar02_Destroy(Actor* thisx, PlayState* play);
void DmChar02_Update(Actor* thisx, PlayState* play);
void DmChar02_Draw(Actor* thisx, PlayState* play);

void func_80AAB04C(DmChar02* this, PlayState* play);

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

static AnimationInfo sAnimations[] = {
    { &object_stk2_Anim_00A2BC, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &object_stk2_Anim_00A4C4, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &object_stk2_Anim_00A6D4, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &object_stk2_Anim_00A104, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
};

void DmChar02_ChangeAnimationByInfo(SkelAnime* skelAnime, AnimationInfo* animInfo, u16 index) {
    f32 frameCount;

    animInfo += index;

    if (animInfo->frameCount < 0.0f) {
        frameCount = Animation_GetLastFrame(animInfo->animation);
    } else {
        frameCount = animInfo->frameCount;
    }
    Animation_Change(skelAnime, animInfo->animation, animInfo->playSpeed, animInfo->startFrame, frameCount,
                     animInfo->mode, animInfo->morphFrames);
}

void func_80AAAECC(Actor* actor, PlayState* play) {
    switch (play->csCtx.frames) {
        case 95:
            Actor_PlaySfxAtPos(actor, NA_SE_EV_OCARINA_BOUND_0);
            return;
        case 101:
        case 105:
        case 112:
            Actor_PlaySfxAtPos(actor, NA_SE_EV_OCARINA_BOUND_1);
            return;
    }
}

void func_80AAAF2C(DmChar02* this, PlayState* play) {
    if ((play->csCtx.state != 0) && (play->sceneNum == SCENE_OKUJOU) && (play->csCtx.currentCsIndex == 1)) {
        func_80AAAECC(&this->actor, play);
    }
}

void DmChar02_Init(Actor* thisx, PlayState* play) {
    DmChar02* this = THIS;

    if (gSaveContext.save.inventory.items[SLOT_OCARINA] == ITEM_NONE) {
        this->animIndex = 0;
        this->actor.targetArrowOffset = 3000.0f;
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 24.0f);
        SkelAnime_InitFlex(play, &this->skelAnime, &gClockTowerOcarinaOfTimeSkel, NULL, NULL, NULL, 0);
        DmChar02_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 0);
        Actor_SetScale(&this->actor, 0.01f);
        this->actionFunc = func_80AAB04C;
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

void DmChar02_Destroy(Actor* thisx, PlayState* play) {
}

void func_80AAB04C(DmChar02* this, PlayState* play) {
    u8 sp2F = true;
    s32 actionIndex;

    if (Cutscene_CheckActorAction(play, 0x83)) {
        actionIndex = Cutscene_GetActorActionIndex(play, 0x83);
        if (play->csCtx.frames == play->csCtx.actorActions[actionIndex]->startFrame) {
            switch (play->csCtx.actorActions[actionIndex]->action) {
                default:
                    this->animIndex = 0;
                    sp2F = false;
                    break;
                case 1:
                    this->animIndex = 0;
                    break;
                case 2:
                    this->animIndex = 1;
                    break;
                case 4:
                    this->animIndex = 3;
                    break;
            }
            if (sp2F) {
                DmChar02_ChangeAnimationByInfo(&this->skelAnime, &sAnimations[this->animIndex], 0);
            }
        }
        Cutscene_ActorTranslateAndYaw(&this->actor, play, actionIndex);
    }
    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        if (this->animIndex == 1) {
            this->animIndex++;
            DmChar02_ChangeAnimationByInfo(&this->skelAnime, &sAnimations[this->animIndex], 0);
        }
    }
}

void DmChar02_Update(Actor* thisx, PlayState* play) {
    DmChar02* this = THIS;

    SkelAnime_Update(&this->skelAnime);
    this->unk2F0 = this->unk2F0;
    this->actionFunc(this, play);
    if (!Actor_HasParent(&this->actor, play)) {
        Actor_PickUp(&this->actor, play, GI_OCARINA, 30.0f, 80.0f);
    } else {
        gSaveContext.save.playerForm = PLAYER_FORM_HUMAN;
        Actor_MarkForDeath(&this->actor);
    }
    func_80AAAF2C(this, play);
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
    s32 sp30 = false;

    if ((play->csCtx.state == 0) && (this->actor.world.pos.y < 100.0f)) {
        sp30 = true;
    } else if (Cutscene_CheckActorAction(play, 0x6B)) {
        switch (play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 0x6B)]->action) {
            case 0x17:
            case 0x1C:
            case 0x26:
                sp30 = true;
        }
    }
    if (sp30) {
        func_8012C28C(play->state.gfxCtx);
        SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                       this->skelAnime.dListCount, DmChar02_OverrideLimbDraw, DmChar02_PostLimbDraw,
                                       DmChar02_TransformLimbDraw, &this->actor);
    }
}
