/*
 * File: z_en_yb.c
 * Overlay: ovl_En_Yb
 * Description: Kamaro the Dancing Ghost
 */

#include "z_en_yb.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "objects/object_yb/object_yb.h"

#define FLAGS 0x02000019

#define THIS ((EnYb*)thisx)

void EnYb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnYb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnYb_Update(Actor* thisx, GlobalContext* globalCtx);
void EnYb_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnYb_Idle(EnYb* this, GlobalContext* globalCtx);
void EnYb_WaitForMidnight(EnYb* this, GlobalContext* globalCtx);
void EnYb_Leaving(EnYb* this, GlobalContext* globalCtx);
void func_80BFA91C(EnYb* this, GlobalContext* globalCtx);
void func_80BFA9D4(EnYb* this, GlobalContext* globalCtx);
void EnYb_TeachingDanceFinish(EnYb* this, GlobalContext* globalCtx);
void EnYb_TeachingDance(EnYb* this, GlobalContext* globalCtx);
void func_80BFA868(EnYb* this, GlobalContext* globalCtx);

void EnYb_UpdateAnimation(EnYb* this, GlobalContext* globalCtx);
s32 EnYb_CanTalk(EnYb* this, GlobalContext* globalCtx);
void EnYb_FinishTeachingCutscene(EnYb* this);

// custom shadow function
void EnYb_ActorShadowFunc(Actor* actor, Lights* mapper, GlobalContext* globalCtx);

void EnYb_SetAnimation(GlobalContext*, EnYb*, s16, u8, f32);

void EnYb_Leaving(EnYb* this, GlobalContext* globalCtx);
void func_80BFA868(EnYb* this, GlobalContext* globalCtx);
void func_80BFA91C(EnYb* this, GlobalContext* globalCtx);
void func_80BFA9D4(EnYb* this, GlobalContext* globalCtx);
void EnYb_TeachingDanceFinish(EnYb* this, GlobalContext* globalCtx);
void EnYb_TeachingDance(EnYb* this, GlobalContext* globalCtx);
void EnYb_Idle(EnYb* this, GlobalContext* globalCtx);
void EnYb_WaitForMidnight(EnYb* this, GlobalContext* globalCtx);

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
static AnimationHeader* gYbUnusedAnimations[] = { &gYbUnkAnim };

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

    // I dont know why
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gYbSkeleton, &gYbUnkAnim,
                       (void*)(((s32) & this->limbDrawTbl) & ~0xF), (void*)((s32) & this->transitionDrawTable & ~0xF),
                       ENYB_LIMBCOUNT);

    Animation_PlayLoop(&this->skelAnime, &gYbUnkAnim);

    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->actionFunc = EnYb_Idle;
    this->currentAnimIndex = 3; // gets overwritten in EnYb_SetAnimation...?
    this->actor.minVelocityY = -9.0f;
    this->actor.gravity = -1.0f;

    EnYb_SetAnimation(globalCtx, this, 2, 0, 0.0f);

    tempCutscene = this->actor.cutscene;
    for (i = 0; i < 2; ++i) {
        this->cutscenes[i] = tempCutscene;
        if (tempCutscene != -1) {
            this->actor.cutscene = tempCutscene;
            tempCutscene = ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);
        }
    }

    this->cutsceneIndex = -1;
    this->actor.cutscene = this->cutscenes[0];

    // between midnight and morning
    if (gSaveContext.time < CLOCK_TIME(6, 0)) {
        this->alpha = 255;
    } else {
        this->alpha = 0;
        this->actionFunc = EnYb_WaitForMidnight;
        this->actor.flags &= ~0x1;
    }

    // check if already healed
    if (gSaveContext.weekEventReg[82] & 4) {
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
 * custom shadow draw function of type ActorShadowFunc
 */
void EnYb_ActorShadowFunc(Actor* actor, Lights* mapper, GlobalContext* globalCtx) {
    Vec3f oldPos;
    EnYb* this = (EnYb*)actor;

    if (this->alpha > 0) {
        if (this->currentAnimIndex == 2) {
            // regalloc without temp
            // almost 1/2250.0f, but thats off by 0x1 in rodata
            f32 tempScale = (((27.0f - this->shadowPos.y) + actor->world.pos.y) * 0.00044444448f) + 0.01f;
            actor->scale.x = tempScale;
        }
        Math_Vec3f_Copy(&oldPos, &actor->world.pos);
        Math_Vec3f_Copy(&actor->world.pos, &this->shadowPos);
        func_800B4AEC(globalCtx, actor, 50.0f);

        if (oldPos.y < this->actor.floorHeight) {
            actor->world.pos.y = this->actor.floorHeight;
        } else {
            actor->world.pos.y = oldPos.y;
        }

        func_800B3FC0(actor, mapper, globalCtx);
        Math_Vec3f_Copy(&actor->world.pos, &oldPos);
        actor->scale.x = 0.01f;
    }
}

/**
 * weird animation changing function
 * only gets called from init with static variables though: (globalCtx, this, 2, 0, 0.0f);
 */
void EnYb_SetAnimation(GlobalContext* globalCtx, EnYb* this, s16 animIndex, u8 animMode, f32 transitionRate) {
    if (animIndex >= 0 && animIndex < 3) {
        if (animIndex != this->currentAnimIndex || animMode != 0) {
            if (animIndex > 0) {
                if (animMode == 0) {
                    LinkAnimation_Change(globalCtx, &this->skelAnime, gLinkAnimations[animIndex - 1], 1.0f, 0.0f,
                                         Animation_GetLastFrame(&gLinkAnimations[animIndex - 1]->common), 0,
                                         transitionRate);
                } else {
                    // unused case, called once with animMode = 0
                    LinkAnimation_Change(globalCtx, &this->skelAnime, gLinkAnimations[animIndex - 1], 1.0f, 0.0f,
                                         Animation_GetLastFrame(&gLinkAnimations[animIndex - 1]->common), 0,
                                         transitionRate);
                }
            } else {
                // unused case, called once with animIndex = 2
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
    if (this->actor.xzDistToPlayer < 100.0f && Actor_IsLinkFacingActor(&this->actor, 0x3000, globalCtx) &&
        Actor_IsActorFacingLink(&this->actor, 0x3000)) {
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

// zero is the only input...? only called from Idle?
void EnYb_ChangeCutscene(EnYb* this, s16 cutsceneId) {
    EnYb_FinishTeachingCutscene(this);
    this->cutsceneIndex = cutsceneId;
}

/**
 * sets a flag that enables the kamaro dancing proximity music at night
 */
void EnYb_EnableProximityMusic(EnYb* this) {
    func_800B9084(&this->actor);
}

void EnYb_Leaving(EnYb* this, GlobalContext* globalCtx) {
    s32 pad;
    Vec3f sp60;
    s32 i;

    EnYb_UpdateAnimation(this, globalCtx);
    for (i = 3; i >= 0; i--) {
        sp60.x = randPlusMinusPoint5Scaled(60.0f) + this->actor.world.pos.x;
        sp60.z = randPlusMinusPoint5Scaled(60.0f) + this->actor.world.pos.z;
        sp60.y = randPlusMinusPoint5Scaled(50.0f) + (this->actor.world.pos.y + 20.0f);
        func_800B3030(globalCtx, &sp60, &D_80BFB2E8, &D_80BFB2E8, 0x64, 0, 2);
    }

    Audio_PlaySoundAtPosition(globalCtx, &this->actor.world.pos, 0x14, NA_SE_EN_EXTINCT);
    if (this->alpha > 10) {
        this->alpha -= 10;
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80BFA868(EnYb* this, GlobalContext* globalCtx) {
    EnYb_UpdateAnimation(this, globalCtx);
    if (func_800B84D0(&this->actor, globalCtx)) { // is talking?
        this->actor.flags &= ~0x10000;
        this->actionFunc = func_80BFA9D4;
        // I am counting on you
        func_801518B0(globalCtx, 0x147D, &this->actor);
        func_80BFA2FC(globalCtx);
    } else {
        func_800B8500(&this->actor, globalCtx, 1000.0f, 1000.0f, -1);
    }
    EnYb_EnableProximityMusic(this);
}

void func_80BFA91C(EnYb* this, GlobalContext* globalCtx) {
    EnYb_UpdateAnimation(this, globalCtx);
    // what parent? when would kamaro be spawned by another actor?
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        this->actionFunc = func_80BFA868;
        this->actor.flags |= 0x10000;
        func_800B8500(&this->actor, globalCtx, 1000.0f, 1000.0f, -1);
    } else {
        func_800B8A1C(&this->actor, globalCtx, 0x89, 10000.0f, 100.0f);
    }
    EnYb_EnableProximityMusic(this);
}

void func_80BFA9D4(EnYb* this, GlobalContext* globalCtx) {

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 0x1000, 0x200);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    EnYb_UpdateAnimation(this, globalCtx);

    if (func_80152498(&globalCtx->msgCtx) == 5 && func_80147624(globalCtx) != 0) {
        switch (globalCtx->msgCtx.unk11F04) {
            case 0x147D: // I am counting on you
                func_801477B4(globalCtx);
                this->actionFunc = EnYb_Leaving;
                gSaveContext.weekEventReg[82] |= 0x4;
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
                    this->actionFunc = func_80BFA91C;
                    func_80BFA91C(this, globalCtx);
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
    if (func_800B84D0(&this->actor, globalCtx) != 0) {
        this->actionFunc = func_80BFA9D4;
        // Spread my dance across the world
        func_801518B0(globalCtx, 0x147C, &this->actor);
        this->actor.flags &= ~0x10000;
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
        this->actor.flags |= 0x10000;
        func_800B8500(&this->actor, globalCtx, 1000.0f, 1000.0f, -1);
    }
    EnYb_EnableProximityMusic(this);
}

void EnYb_Idle(EnYb* this, GlobalContext* globalCtx) {
    s32 pad;
    Player* player = GET_PLAYER(globalCtx);

    EnYb_UpdateAnimation(this, globalCtx);
    if (this->actor.xzDistToPlayer < 180.0f && fabsf(this->actor.playerHeightRel) < 50.0f &&
        globalCtx->msgCtx.unk1202A == 3 && globalCtx->msgCtx.unk1202E == 7 &&
        gSaveContext.playerForm == PLAYER_FORM_HUMAN) {
        this->actionFunc = EnYb_TeachingDance;
        this->teachingCutsceneTimer = 200;
        EnYb_ChangeCutscene(this, 0);
    } else if (func_800B84D0(&this->actor, globalCtx)) {
        func_80BFA2FC(globalCtx);
        this->actionFunc = func_80BFA9D4;
        if (Player_GetMask(globalCtx) == PLAYER_MASK_KAMARO) {
            // I have taught you, go use it
            func_801518B0(globalCtx, 0x147C, &this->actor);
        } else {
            // regular talk to him first dialogue
            func_801518B0(globalCtx, 0x147B, &this->actor);
        }
    } else if (EnYb_CanTalk(this, globalCtx)) {
        func_800B8614(&this->actor, globalCtx, 120.0f);
    }

    // ?
    if (this->unkFlag410 & 1) {
        if (!(player->stateFlags2 & 0x8000000)) {
            this->unkFlag410 &= ~1;
        }
    } else if ((player->stateFlags2 & 0x8000000) && this->actor.xzDistToPlayer < 180.0f &&
               fabsf(this->actor.playerHeightRel) < 50.0f) {

        this->unkFlag410 |= 1;
        Audio_PlayActorSound2(&this->actor, NA_SE_SY_TRE_BOX_APPEAR);
    }

    EnYb_EnableProximityMusic(this);
}

void EnYb_WaitForMidnight(EnYb* this, GlobalContext* globalCtx) {
    if (gSaveContext.time < CLOCK_TIME(6, 0)) {
        EnYb_UpdateAnimation(this, globalCtx);
        this->alpha += 5;
        if (this->alpha > 250) {
            this->alpha = 255;
            this->actor.flags |= 1;
            this->actionFunc = EnYb_Idle;
        }
        EnYb_EnableProximityMusic(this);
    }
}

void EnYb_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnYb* this = THIS;

    if ((this->actor.flags & 1) == 1) {
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
    if ((this->actor.flags & 1) == 1) {
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
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

void EnYb_PostLimbDrawOpa(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* actor) {
    EnYb* this = (EnYb*)actor;

    if (limbIndex == 11) {
        Matrix_MultiplyVector3fByState(&D_80BFB2F4, &this->actor.focus.pos);
    }
    if (limbIndex == 3) {
        Matrix_MultiplyVector3fByState(&gZeroVec3f, &this->shadowPos);
    }
}

void EnYb_PostLimbDrawXlu(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* actor, Gfx** gfx) {
    EnYb* this = (EnYb*)actor;

    if (limbIndex == 11) {
        Matrix_MultiplyVector3fByState(&D_80BFB300, &this->actor.focus.pos);
    }
    if (limbIndex == 3) {
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
