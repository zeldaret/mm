/*
 * File: z_dm_char02.c
 * Overlay: ovl_Dm_Char02
 * Description: Ocarina of Time (dropped from Skull Kid's hand)
 */

#include "z_dm_char02.h"
#include "objects/object_stk2/object_stk2.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DmChar02*)thisx)

void DmChar02_Init(Actor* thisx, GlobalContext* globalCtx);
void DmChar02_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmChar02_Update(Actor* thisx, GlobalContext* globalCtx);
void DmChar02_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AAB04C(DmChar02* this, GlobalContext* globalCtx);

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

static AnimationInfo sAnimations[4] = {
    { &object_stk2_Anim_00A2BC, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_stk2_Anim_00A4C4, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_stk2_Anim_00A6D4, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_stk2_Anim_00A104, 1.0f, 0.0f, -1.0f, 2, 0.0f },
};

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char02/func_80AAAE30.s")
void DmChar02_ChangeAnimationByInfo(SkelAnime *skelAnime, AnimationInfo *animation, u16 idx) {
    f32 frameCount;

    animation += idx;

    if (animation->frameCount < 0.0f) {
        frameCount = (f32) Animation_GetLastFrame(animation->animation);
    } else {
        frameCount = animation->frameCount;
    }
    Animation_Change(skelAnime, animation->animation, animation->playSpeed, animation->startFrame, frameCount, 
                     animation->mode, animation->morphFrames);
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char02/func_80AAAECC.s")
void func_80AAAECC(Actor *actor, GlobalContext *globalCtx) {
    switch (globalCtx->csCtx.frames) {
    case 0x5F:
        Actor_PlaySfxAtPos(actor, 0x292AU);
        return;
    case 0x65:
    case 0x69:
    case 0x70:
        Actor_PlaySfxAtPos(actor, 0x292BU);
        return;
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char02/func_80AAAF2C.s")
void func_80AAAF2C(DmChar02 *this, GlobalContext *globalCtx) {
    if ((globalCtx->csCtx.state != 0) && (globalCtx->sceneNum == SCENE_OKUJOU) && (globalCtx->csCtx.currentCsIndex == 1)) {
        func_80AAAECC(&this->actor, globalCtx);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char02/DmChar02_Init.s")
void DmChar02_Init(Actor *thisx, GlobalContext *globalCtx) {
    DmChar02 *this = THIS;

    // items[0] is the ocarina
    if (gSaveContext.save.inventory.items[0] == 0xFF) {
        this->unk2E0 = 0;
        this->actor.targetArrowOffset = 3000.0f;
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 24.0f);
        SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gClockTowerOcarinaOfTimeSkel, NULL, NULL, NULL, 0);
        DmChar02_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 0);
        Actor_SetScale(&this->actor, 0.01f);
        this->actionFunc = func_80AAB04C;
        return;
    }
    Actor_MarkForDeath(&this->actor);
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char02/DmChar02_Destroy.s")
void DmChar02_Destroy(Actor *thisx, GlobalContext *globalCtx) {
}

// action func
// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char02/func_80AAB04C.s")
void func_80AAB04C(DmChar02 *this, GlobalContext *globalCtx) {
    u8 sp2F;
    s32 actionIndex;

    sp2F = 1;
    if (Cutscene_CheckActorAction(globalCtx, 0x83U) != 0) {
        actionIndex = Cutscene_GetActorActionIndex(globalCtx, 0x83U);
        if (globalCtx->csCtx.frames == globalCtx->csCtx.actorActions[actionIndex]->startFrame) {
            switch (globalCtx->csCtx.actorActions[actionIndex]->action) {                      /* irregular */
            default:
                this->unk2E0 = 0;
                sp2F = 0;
                break;
            case 1:
                this->unk2E0 = 0;
                break;
            case 2:
                this->unk2E0 = 1;
                break;
            case 4:
                this->unk2E0 = 3;
                break;
            }
            if (sp2F != 0) {
                DmChar02_ChangeAnimationByInfo(&this->skelAnime, &sAnimations[this->unk2E0], 0U);
            }
        }
        Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx, actionIndex);
    }
    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) != 0) {
        if (this->unk2E0 == 1) {
            this->unk2E0++;
            DmChar02_ChangeAnimationByInfo(&this->skelAnime, &sAnimations[this->unk2E0], 0U);
        }
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char02/DmChar02_Update.s")
void DmChar02_Update(Actor *thisx, GlobalContext *globalCtx) {
    DmChar02 *this = THIS;
    SkelAnime_Update(&this->skelAnime);
    this->unk2F0 = this->unk2F0;
    this->actionFunc(this, globalCtx);
    if (Actor_HasParent(&this->actor, globalCtx) == 0) {
        Actor_PickUp(&this->actor, globalCtx, 0x4C, 30.0f, 80.0f);
    } else {
        gSaveContext.save.playerForm = 4;
        Actor_MarkForDeath(&this->actor);
    }
    func_80AAAF2C(this, globalCtx);
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char02/func_80AAB23C.s")
s32 DmChar02_OverrideLimbDraw(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor *thisx) {
    return false;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char02/func_80AAB258.s")
void DmChar02_PostLimbDraw(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3s *rot, Actor *thisx) {

}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char02/func_80AAB270.s")
void DmChar02_TransformLimbDraw(GlobalContext *globalCtx, s32 limbIndex, Actor *thisx) {

}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char02/DmChar02_Draw.s")
void DmChar02_Draw(Actor *thisx, GlobalContext *globalCtx) {
    s32 pad[2];
    DmChar02 *this = THIS;
    s32 sp30 = 0;
    
    if ((globalCtx->csCtx.state == 0) && (this->actor.world.pos.y < 100.0f)) {
        sp30 = 1;
    } else if (Cutscene_CheckActorAction(globalCtx, 0x6B)) {
        switch (globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 0x6B)]->action) {
            case 0x17:
            case 0x1C:
            case 0x26:
                sp30 = 1;
        }
        
    }
    if (sp30) {
        func_8012C28C(globalCtx->state.gfxCtx);
        SkelAnime_DrawTransformFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount, 
                                       DmChar02_OverrideLimbDraw, DmChar02_PostLimbDraw, DmChar02_TransformLimbDraw, &this->actor);
    }
}