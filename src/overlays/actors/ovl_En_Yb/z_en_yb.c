/*
 * File: z_en_yb.c
 * Overlay: ovl_En_Yb
 * Description: Kamaro the Dancing Ghost
 */

#include "z_en_yb.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((EnYb*)thisx)

void EnYb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnYb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnYb_Update(Actor* thisx, GlobalContext* globalCtx);
void EnYb_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnYb_Idle(EnYb* this, GlobalContext* globalCtx);
void EnYb_TeachingDanceFinish(EnYb* this, GlobalContext* globalCtx);
void EnYb_SetupLeaving(EnYb* this, GlobalContext* globalCtx);

void EnYb_UpdateAnimation(EnYb* this, GlobalContext* globalCtx);
void EnYb_FinishTeachingCutscene(EnYb* this);
void EnYb_Disappear(EnYb* this, GlobalContext* globalCtx);
void EnYb_ReceiveMask(EnYb* this, GlobalContext* globalCtx);
void EnYb_Talk(EnYb* this, GlobalContext* globalCtx);
void EnYb_TeachingDance(EnYb* this, GlobalContext* globalCtx);
void EnYb_WaitForMidnight(EnYb* this, GlobalContext* globalCtx);

void EnYb_ActorShadowFunc(Actor* thisx, Lights* mapper, GlobalContext* globalCtx);
void EnYb_SetAnimation(GlobalContext*, EnYb*, s16, u8, f32);
s32 EnYb_CanTalk(EnYb* this, GlobalContext* globalCtx);

const ActorInit En_Yb_InitVars = {
    ACTOR_EN_YB,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_YB,
    sizeof(EnYb),
    (ActorFunc)EnYb_Init,
    (ActorFunc)EnYb_Destroy,
    (ActorFunc)EnYb_Update,
    (ActorFunc)EnYb_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_ENEMY,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 20, 40, 0, { 0, 0, 0 } },
};

// crashes if I try to mod it in to look at it
//  assumption: draw uses two different skeleton functions, might be incompatible
static AnimationHeader* gYbUnusedAnimations[] = { &object_yb_Anim_000200 };

static LinkAnimationHeader* gLinkAnimations[] = { &gameplay_keep_Linkanim_00DF28, &gameplay_keep_Linkanim_00CF98 };

static Vec3f D_80BFB2E8 = { 0.0f, 0.5f, 0.0f };

static Vec3f D_80BFB2F4 = { 500.0f, -500.0, 0.0f };

static Vec3f D_80BFB300 = { 500.0f, -500.0f, 0.0f };

void EnYb_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnYb* this = THIS;
    s16 tempCutscene;
    s32 i;

    Actor_SetScale(&this->actor, 0.01f);
    ActorShape_Init(&this->actor.shape, 0.0f, EnYb_ActorShadowFunc, 20.0f);

    // @Bug this alignment is because of player animations, but should be using ALIGN16
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gYbSkeleton, &object_yb_Anim_000200,
                       (uintptr_t)this->jointTable & ~0xF, (uintptr_t)this->morphTable & ~0xF, YB_LIMB_MAX);

    Animation_PlayLoop(&this->skelAnime, &object_yb_Anim_000200);

    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->actionFunc = EnYb_Idle;
    this->currentAnimIndex = 3; // gets overwritten to 2 in EnYb_SetAnimation later
    this->actor.terminalVelocity = -9.0f;
    this->actor.gravity = -1.0f;

    EnYb_SetAnimation(globalCtx, this, 2, ANIMMODE_LOOP, 0.0f);

    tempCutscene = this->actor.cutscene;
    for (i = 0; i < ARRAY_COUNT(this->cutscenes); i++) {
        this->cutscenes[i] = tempCutscene;
        if (tempCutscene != -1) {
            this->actor.cutscene = tempCutscene;
            tempCutscene = ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);
        }
    }

    this->cutsceneIndex = -1;
    this->actor.cutscene = this->cutscenes[0];

    // between midnight and morning start spawned
    if (gSaveContext.save.time < CLOCK_TIME(6, 0)) {
        this->alpha = 255;
    } else { // else (night 6pm to midnight): wait to appear
        this->alpha = 0;
        this->actionFunc = EnYb_WaitForMidnight;
        this->actor.flags &= ~ACTOR_FLAG_1;
    }

    // check if already healed
    if (gSaveContext.save.weekEventReg[82] & 4) {
        Actor_MarkForDeath(&this->actor);
    }
}

void EnYb_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnYb* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80BFA2FC(GlobalContext* globalCtx) {
    if (INV_CONTENT(ITEM_MASK_KAMARO) == ITEM_MASK_KAMARO) {
        func_80151BB4(globalCtx, 0x34);
    }
    func_80151BB4(globalCtx, 0xF);
}

/**
 * Custom shadow draw function of type ActorShadowFunc.
 */
void EnYb_ActorShadowFunc(Actor* thisx, Lights* mapper, GlobalContext* globalCtx) {
    Vec3f oldPos;
    EnYb* this = THIS;

    if (this->alpha > 0) {
        if (this->currentAnimIndex == 2) {
            f32 tempScale = (((27.0f - this->shadowPos.y) + this->actor.world.pos.y) * ((1 / 2.25f) * 0.001f)) + 0.01f;
            this->actor.scale.x = tempScale;
        }
        Math_Vec3f_Copy(&oldPos, &this->actor.world.pos);
        Math_Vec3f_Copy(&this->actor.world.pos, &this->shadowPos);
        func_800B4AEC(globalCtx, &this->actor, 50.0f);

        if (oldPos.y < this->actor.floorHeight) {
            this->actor.world.pos.y = this->actor.floorHeight;
        } else {
            this->actor.world.pos.y = oldPos.y;
        }

        ActorShadow_DrawCircle(&this->actor, mapper, globalCtx);
        Math_Vec3f_Copy(&this->actor.world.pos, &oldPos);
        this->actor.scale.x = 0.01f;
    }
}

void EnYb_SetAnimation(GlobalContext* globalCtx, EnYb* this, s16 animIndex, u8 animMode, f32 transitionRate) {
    if (animIndex >= 0 && animIndex < 3) {
        if (animIndex != this->currentAnimIndex || animMode != ANIMMODE_LOOP) {
            if (animIndex > 0) {
                if (animMode == ANIMMODE_LOOP) {
                    LinkAnimation_Change(globalCtx, &this->skelAnime, gLinkAnimations[animIndex - 1], 1.0f, 0.0f,
                                         Animation_GetLastFrame(gLinkAnimations[animIndex - 1]), ANIMMODE_LOOP,
                                         transitionRate);
                } else {
                    // unused case, (only called once with animMode = ANIMMODE_LOOP)
                    LinkAnimation_Change(globalCtx, &this->skelAnime, gLinkAnimations[animIndex - 1], 1.0f, 0.0f,
                                         Animation_GetLastFrame(gLinkAnimations[animIndex - 1]), ANIMMODE_LOOP,
                                         transitionRate);
                }
            } else {
                // unused case, (only called once with animIndex = 2)
                AnimationHeader* animationPtr = gYbUnusedAnimations[animIndex];

                if (1) {}

                Animation_Change(&this->skelAnime, gYbUnusedAnimations[animIndex], 1.0f, 0.0f,
                                 Animation_GetLastFrame(animationPtr), animMode, transitionRate);
            }
            this->currentAnimIndex = animIndex;
        }
    }
}

s32 EnYb_CanTalk(EnYb* this, GlobalContext* globalCtx) {
    if (this->actor.xzDistToPlayer < 100.0f && Player_IsFacingActor(&this->actor, 0x3000, globalCtx) &&
        Actor_IsFacingPlayer(&this->actor, 0x3000)) {
        return true;
    } else {
        return false;
    }
}

void EnYb_UpdateAnimation(EnYb* this, GlobalContext* globalCtx) {
    if (this->currentAnimIndex <= 0) {
        SkelAnime_Update(&this->skelAnime);
    } else {
        LinkAnimation_Update(globalCtx, &this->skelAnime);
    }
}

void EnYb_FinishTeachingCutscene(EnYb* this) {
    if (this->cutsceneIndex != -1) {
        if (ActorCutscene_GetCurrentIndex() == this->cutscenes[this->cutsceneIndex]) {
            ActorCutscene_Stop(this->cutscenes[this->cutsceneIndex]);
        }
        this->cutsceneIndex = -1;
    }
}

void EnYb_ChangeCutscene(EnYb* this, s16 cutsceneId) {
    EnYb_FinishTeachingCutscene(this);
    this->cutsceneIndex = cutsceneId;
}

/**
 * Sets a flag that enables the Kamaro dancing proximity music at night.
 */
void EnYb_EnableProximityMusic(EnYb* this) {
    func_800B9084(&this->actor);
}

void EnYb_Disappear(EnYb* this, GlobalContext* globalCtx) {
    s32 pad;
    Vec3f sp60;
    s32 i;

    EnYb_UpdateAnimation(this, globalCtx);
    for (i = 3; i >= 0; i--) {
        sp60.x = randPlusMinusPoint5Scaled(60.0f) + this->actor.world.pos.x;
        sp60.z = randPlusMinusPoint5Scaled(60.0f) + this->actor.world.pos.z;
        sp60.y = randPlusMinusPoint5Scaled(50.0f) + (this->actor.world.pos.y + 20.0f);
        func_800B3030(globalCtx, &sp60, &D_80BFB2E8, &D_80BFB2E8, 100, 0, 2);
    }

    SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 20, NA_SE_EN_EXTINCT);
    if (this->alpha > 10) {
        this->alpha -= 10;
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

void EnYb_SetupLeaving(EnYb* this, GlobalContext* globalCtx) {
    EnYb_UpdateAnimation(this, globalCtx);
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actor.flags &= ~ACTOR_FLAG_10000;
        this->actionFunc = EnYb_Talk;
        // I am counting on you
        Message_StartTextbox(globalCtx, 0x147D, &this->actor);
        func_80BFA2FC(globalCtx);
    } else {
        func_800B8500(&this->actor, globalCtx, 1000.0f, 1000.0f, -1);
    }
    EnYb_EnableProximityMusic(this);
}

void EnYb_ReceiveMask(EnYb* this, GlobalContext* globalCtx) {
    EnYb_UpdateAnimation(this, globalCtx);
    // Player is parent: receiving the Kamaro mask
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        this->actionFunc = EnYb_SetupLeaving;
        this->actor.flags |= ACTOR_FLAG_10000;
        func_800B8500(&this->actor, globalCtx, 1000.0f, 1000.0f, -1);
    } else {
        Actor_PickUp(&this->actor, globalCtx, GI_MASK_KAMARO, 10000.0f, 100.0f);
    }
    EnYb_EnableProximityMusic(this);
}

void EnYb_Talk(EnYb* this, GlobalContext* globalCtx) {
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 0x1000, 0x200);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    EnYb_UpdateAnimation(this, globalCtx);

    if (Message_GetState(&globalCtx->msgCtx) == 5 && Message_ShouldAdvance(globalCtx) != 0) {
        switch (globalCtx->msgCtx.currentTextId) {
            case 0x147D: // I am counting on you
                func_801477B4(globalCtx);
                this->actionFunc = EnYb_Disappear;
                gSaveContext.save.weekEventReg[82] |= 0x4;
                break;
            case 0x147C: // Spread my dance across the world
                if (Player_GetMask(globalCtx) == PLAYER_MASK_KAMARO) {
                    func_801477B4(globalCtx);
                    this->actionFunc = EnYb_Idle;

                } else if (INV_CONTENT(ITEM_MASK_KAMARO) == ITEM_MASK_KAMARO) {
                    func_80151938(globalCtx, 0x147D); // I am counting on you
                    func_80BFA2FC(globalCtx);

                } else {
                    func_801477B4(globalCtx);
                    this->actionFunc = EnYb_ReceiveMask;
                    EnYb_ReceiveMask(this, globalCtx);
                }
                break;
            default:
                func_801477B4(globalCtx);
                this->actionFunc = EnYb_Idle;
                break;
        }
    }
    EnYb_EnableProximityMusic(this);
}

void EnYb_TeachingDanceFinish(EnYb* this, GlobalContext* globalCtx) {
    EnYb_UpdateAnimation(this, globalCtx);
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actionFunc = EnYb_Talk;
        // Spread my dance across the world
        Message_StartTextbox(globalCtx, 0x147C, &this->actor);
        this->actor.flags &= ~ACTOR_FLAG_10000;
    } else {
        func_800B8500(&this->actor, globalCtx, 1000.0f, 1000.0f, -1);
    }
    EnYb_EnableProximityMusic(this);
}

// dancing countdown
void EnYb_TeachingDance(EnYb* this, GlobalContext* globalCtx) {
    EnYb_UpdateAnimation(this, globalCtx);

    if (this->teachingCutsceneTimer > 0) {
        this->teachingCutsceneTimer--;
    } else {
        EnYb_FinishTeachingCutscene(this);
        this->actionFunc = EnYb_TeachingDanceFinish;
        this->actor.flags |= ACTOR_FLAG_10000;
        func_800B8500(&this->actor, globalCtx, 1000.0f, 1000.0f, -1);
    }
    EnYb_EnableProximityMusic(this);
}

void EnYb_Idle(EnYb* this, GlobalContext* globalCtx) {
    s32 pad;
    Player* player = GET_PLAYER(globalCtx);

    EnYb_UpdateAnimation(this, globalCtx);
    if (this->actor.xzDistToPlayer < 180.0f && fabsf(this->actor.playerHeightRel) < 50.0f &&
        globalCtx->msgCtx.ocarinaMode == 3 && globalCtx->msgCtx.unk1202E == 7 &&
        gSaveContext.save.playerForm == PLAYER_FORM_HUMAN) {
        this->actionFunc = EnYb_TeachingDance;
        this->teachingCutsceneTimer = 200;
        EnYb_ChangeCutscene(this, 0);
    } else if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        func_80BFA2FC(globalCtx);
        this->actionFunc = EnYb_Talk;
        if (Player_GetMask(globalCtx) == PLAYER_MASK_KAMARO) {
            // I have taught you, go use it
            Message_StartTextbox(globalCtx, 0x147C, &this->actor);
        } else {
            // regular talk to him first dialogue
            Message_StartTextbox(globalCtx, 0x147B, &this->actor);
        }
    } else if (EnYb_CanTalk(this, globalCtx)) {
        func_800B8614(&this->actor, globalCtx, 120.0f);
    }

    if (this->playerOcarinaOut & 1) {
        if (!(player->stateFlags2 & 0x8000000)) {
            this->playerOcarinaOut &= ~1;
        }
    } else if ((player->stateFlags2 & 0x8000000) && this->actor.xzDistToPlayer < 180.0f &&
               fabsf(this->actor.playerHeightRel) < 50.0f) {
        this->playerOcarinaOut |= 1;
        Actor_PlaySfxAtPos(&this->actor, NA_SE_SY_TRE_BOX_APPEAR);
    }

    EnYb_EnableProximityMusic(this);
}

void EnYb_WaitForMidnight(EnYb* this, GlobalContext* globalCtx) {
    if (gSaveContext.save.time < CLOCK_TIME(6, 0)) {
        EnYb_UpdateAnimation(this, globalCtx);
        this->alpha += 5;
        if (this->alpha > 250) {
            this->alpha = 255;
            this->actor.flags |= ACTOR_FLAG_1;
            this->actionFunc = EnYb_Idle;
        }
        EnYb_EnableProximityMusic(this);
    }
}

void EnYb_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnYb* this = THIS;

    if (CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_1)) {
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
    if (CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_1)) {
        Actor_MoveWithGravity(&this->actor);
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 40.0f, 25.0f, 40.0f, 5);
    }

    this->actionFunc(this, globalCtx);

    if (this->cutsceneIndex != -1 && ActorCutscene_GetCurrentIndex() != this->cutscenes[this->cutsceneIndex]) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
            ActorCutscene_SetIntentToPlay(this->cutscenes[this->cutsceneIndex]);
        } else if (ActorCutscene_GetCanPlayNext(this->cutscenes[this->cutsceneIndex])) {
            if (this->cutsceneIndex == 0) {
                ActorCutscene_StartAndSetUnkLinkFields(this->cutscenes[this->cutsceneIndex], &this->actor);
            }
        } else {
            ActorCutscene_SetIntentToPlay(this->cutscenes[this->cutsceneIndex]);
        }
    }
}

void EnYb_PostLimbDrawOpa(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnYb* this = THIS;

    if (limbIndex == YB_LIMB_HEAD) {
        Matrix_MultiplyVector3fByState(&D_80BFB2F4, &this->actor.focus.pos);
    }
    if (limbIndex == YB_LIMB_LEGS_ROOT) {
        Matrix_MultiplyVector3fByState(&gZeroVec3f, &this->shadowPos);
    }
}

void EnYb_PostLimbDrawXlu(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    EnYb* this = THIS;

    if (limbIndex == YB_LIMB_HEAD) {
        Matrix_MultiplyVector3fByState(&D_80BFB300, &this->actor.focus.pos);
    }
    if (limbIndex == YB_LIMB_LEGS_ROOT) {
        Matrix_MultiplyVector3fByState(&gZeroVec3f, &this->shadowPos);
    }
}

void EnYb_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnYb* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    if (this->alpha != 0) {
        if (this->alpha < 255) {
            if (this->alpha > 128) {
                func_8012C2B4(POLY_XLU_DISP++);
                Scene_SetRenderModeXlu(globalCtx, 2, 2);
            } else {
                func_8012C304(POLY_XLU_DISP++);
                Scene_SetRenderModeXlu(globalCtx, 1, 2);
            }
            gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, this->alpha);

            if (1) {}

            POLY_XLU_DISP =
                SkelAnime_DrawFlex(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   this->skelAnime.dListCount, NULL, EnYb_PostLimbDrawXlu, &this->actor, POLY_XLU_DISP);

        } else {
            func_8012C28C(globalCtx->state.gfxCtx);
            Scene_SetRenderModeXlu(globalCtx, 0, 1);
            SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                  this->skelAnime.dListCount, NULL, EnYb_PostLimbDrawOpa, &this->actor);
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
