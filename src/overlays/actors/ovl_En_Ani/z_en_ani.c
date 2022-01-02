/*
 * File: z_en_ani.c
 * Overlay: ovl_En_Ani
 * Description: Part-time worker
 */

#include "z_en_ani.h"
#include "objects/object_ani/object_ani.h"

#define FLAGS 0x00000009

#define THIS ((EnAni*)thisx)

void EnAni_Init(Actor* thisx, GlobalContext* globalCtx);
void EnAni_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnAni_Update(Actor* thisx, GlobalContext* globalCtx);
void EnAni_Draw(Actor* thisx, GlobalContext* globalCtx);

// three functions that deal with eye control
void EnAni_DefaultBlink(EnAni* this);
void EnAni_WaitForEyeClose(EnAni* this);
void EnAni_WaitForEyeOpen(EnAni* this);

void EnAni_SetText(EnAni* this, GlobalContext* globalCtx, u16 textId);

void EnAni_TreeHanging(EnAni* this, GlobalContext* globalCtx);
void EnAni_LosingBalance(EnAni* this, GlobalContext* globalCtx);
void EnAni_FallingToGround(EnAni* this, GlobalContext* globalCtx);
void EnAni_WaitingForFootPain(EnAni* this, GlobalContext* globalCtx);
void EnAni_FallingOver(EnAni* this, GlobalContext* globalCtx);
void EnAni_Suffering(EnAni* this, GlobalContext* globalCtx);
void EnAni_Dialogue(EnAni* this, GlobalContext* globalCtx);
void EnAni_IdleStandingUnused(EnAni* this, GlobalContext* globalCtx);

const ActorInit En_Ani_InitVars = {
    ACTOR_EN_ANI,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ANI,
    sizeof(EnAni),
    (ActorFunc)EnAni_Init,
    (ActorFunc)EnAni_Destroy,
    (ActorFunc)EnAni_Update,
    (ActorFunc)EnAni_Draw,
};

// two different colliders, but only one init for both
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
    { 30, 40, 0, { 0, 0, 0 } },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 850, ICHAIN_STOP),
};

static Vec3f D_809686A4 = { 800.0f, 500.0f, 0.0f };

static TexturePtr sEyeTextures[] = { gAniOpenEyeTex, gAniClosingEyeTex, gAniClosedEyeTex };

void EnAni_DefaultBlink(EnAni* this) {
    if (DECR(this->blinkTimer) == 0) {
        this->blinkTimer = Rand_S16Offset(60, 60);
    }
    this->blinkState = this->blinkTimer;
    if (this->blinkState >= 3) {
        this->blinkState = 0;
    }
}

void EnAni_WaitForEyeClose(EnAni* this) {
    if (this->blinkTimer > 0) {
        this->blinkTimer--;
    } else if (this->blinkState < 2) {
        this->blinkState++;
    } else {
        this->blinkFunc = EnAni_WaitForEyeOpen;
        this->blinkTimer = Rand_S16Offset(20, 20);
    }
}

void EnAni_WaitForEyeOpen(EnAni* this) {
    if (this->blinkTimer > 0) {
        this->blinkTimer--;
    } else if (this->blinkState > 0) {
        this->blinkState--;
    } else {
        this->blinkFunc = EnAni_WaitForEyeClose;
        this->blinkTimer = Rand_S16Offset(10, 10);
    }
}

void EnAni_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnAni* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 24.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gAniSkeleton, &gAniStandingNormalAnim, this->jointTable,
                       this->morphTable, ANI_LIMB_COUNT);
    Animation_PlayOnce(&this->skelAnime, &gAniStandingNormalAnim);
    Collider_InitAndSetCylinder(globalCtx, &this->collider1, &this->actor, &sCylinderInit);
    Collider_InitAndSetCylinder(globalCtx, &this->collider2, &this->actor, &sCylinderInit);
    Collider_UpdateCylinder(&this->actor, &this->collider2);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->stateFlags = ANI_STATE_STANDING;
    this->unusedShort = 0;
    this->treeReachTimer = 0;
    this->blinkFunc = EnAni_DefaultBlink;

    if (GET_ANI_TYPE(thisx) == ANI_TYPE_TREE_HANGING) {
        Animation_Change(&this->skelAnime, &gAniTreeHangingAnim, 1.0f, 0.0f,
                         Animation_GetLastFrame(&gAniTreeHangingAnim), 2, 0.0f);
        this->actionFunc = EnAni_TreeHanging;
        this->actor.velocity.y = 0.0f;
        this->actor.minVelocityY = 0.0f;
        this->actor.gravity = 0.0f;
        this->actor.flags |= 0x10;
        this->stateFlags |= ANI_STATE_CLIMBING;
        gSaveContext.eventInf[1] &= (u8)~0x10;

    } else { // ANI_TYPE_UNUSED_STANDING
        // for some reason standing he has a large collider
        // possibly he was meant to be a blocking npc like bomber
        this->collider2.dim.radius = 60;
        this->actionFunc = EnAni_IdleStandingUnused;
        this->actor.velocity.y = -25.0f;
        this->actor.minVelocityY = -25.0f;
        this->actor.gravity = -5.0f;
    }
}

void EnAni_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnAni* this = THIS;
    Collider_DestroyCylinder(globalCtx, &this->collider1);
    Collider_DestroyCylinder(globalCtx, &this->collider2);
}

void EnAni_SetText(EnAni* this, GlobalContext* globalCtx, u16 textId) {
    s16 diffAngle = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;

    this->actor.textId = textId;
    if ((this->stateFlags & ANI_STATE_SUFFERING) || ABS_ALT(diffAngle) <= 0x4300) {
        if (this->actor.xzDistToPlayer < 100.0f) {
            func_800B8614(&this->actor, globalCtx, 120.0f);
        }
    }
}

/**
 * just stands there staring at you,
 * this is NOT him as a shopkeeper, that is EnOsn using his object
 */
void EnAni_IdleStandingUnused(EnAni* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
}

void EnAni_Dialogue(EnAni* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if (func_80152498(&globalCtx->msgCtx) == 2 && globalCtx->msgCtx.unk11F04 == 0x6DE) {
        this->actionFunc = EnAni_Suffering;
    }
}

/**
 * writhing, waiting for player to talk to us
 */
void EnAni_Suffering(EnAni* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if (func_800B84D0(&this->actor, globalCtx)) {
        this->actionFunc = EnAni_Dialogue;
    } else {
        // telling you not to take his rupees you knocked from the tree
        EnAni_SetText(this, globalCtx, 0x6DE);
    }
}

/**
 * waiting for falling over animation to end
 */
void EnAni_FallingOver(EnAni* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        this->blinkFunc = EnAni_WaitForEyeOpen;
        this->actionFunc = EnAni_Suffering;
        Animation_Change(&this->skelAnime, &gAniHoldingFootPainWrithingAnim, 1.0f, 0.0f,
                         Animation_GetLastFrame(&gAniHoldingFootPainWrithingAnim), 0, 0.0f);
    }
}

/**
 * pause: waiting for landing animation and hammer sfx to end
 */
void EnAni_WaitingForFootPain(EnAni* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        this->actionFunc = EnAni_FallingOver;
        Animation_Change(&this->skelAnime, &gAniFallOverHoldingFootAnim, 1.0f, 0.0f,
                         Animation_GetLastFrame(&gAniFallOverHoldingFootAnim), 2, 0.0f);
    }
}

void EnAni_FallingToGround(EnAni* this, GlobalContext* globalCtx) {
    s32 pad;
    s16 quakeValue;

    // if hit the ground
    if (this->actor.bgCheckFlags & 1) {
        this->actor.flags &= ~0x10;
        this->actionFunc = EnAni_WaitingForFootPain;
        this->actor.velocity.x = 0.0f;
        this->actor.velocity.z = 0.0f;
        // the animation gets cut short, (first 16 frames only) only the landing part is seen
        Animation_Change(&this->skelAnime, &gAniLandingThenStandingUpAnim, 1.0f, 0.0f, 16.0f, 2, 0.0f);
        this->stateFlags |= ANI_STATE_SUFFERING;
        quakeValue = Quake_Add(globalCtx->cameraPtrs[0], 3);
        Quake_SetSpeed(quakeValue, 0x6978);
        Quake_SetQuakeValues(quakeValue, 7, 0, 0, 0);
        Quake_SetCountdown(quakeValue, 0x14);
        Audio_PlayActorSound2(&this->actor, NA_SE_IT_HAMMER_HIT);
    }

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 2000, 0x100);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

void EnAni_LosingBalance(EnAni* this, GlobalContext* globalCtx) {
    s32 pad;

    if (SkelAnime_Update(&this->skelAnime)) {
        this->actor.minVelocityY = -20.0f;
        this->actor.gravity = -5.0f;
        this->actor.velocity.y = 0.0f;
        this->actor.velocity.z = -4.0f;
        // frame count : 0.0f, only first frame, rest is handled in next action func
        Animation_Change(&this->skelAnime, &gAniLandingThenStandingUpAnim, 0.0f, 0.0f, 0.0f, 2, 5.0f);
        this->actionFunc = EnAni_FallingToGround;
        gSaveContext.eventInf[1] |= 0x10;
    }
}

void EnAni_TreeHanging(EnAni* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->treeReachTimer > 0) {
            this->treeReachTimer--;
            if (this->treeReachTimer > 0) {
                Animation_PlayOnce(&this->skelAnime, &gAniTreeHangingReachAnim);
            } else {
                Animation_PlayOnce(&this->skelAnime, &gAniTreeHangingAnim);
            }
        } else if (Rand_ZeroFloat(1.0f) < 0.4f) {
            Animation_PlayOnce(&this->skelAnime, &gAniTreeHangingReachAnim);
            this->treeReachTimer = 2;
        } else {
            Animation_PlayOnce(&this->skelAnime, &gAniTreeHangingAnim);
        }
    }

    // his bonk detection is based on his tilt, neat
    if (this->actor.home.rot.x != 0) {
        this->stateFlags |= ANI_STATE_FALLING;
        this->actionFunc = EnAni_LosingBalance;
        Animation_Change(&this->skelAnime, &gAniTreeHangLosingBalanceAnim, 1.0f, 0.0f,
                         Animation_GetLastFrame(&gAniTreeHangLosingBalanceAnim), 2, -5.0f);
    }
}

void EnAni_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnAni* this = THIS;
    f32 minVelocity;

    Collider_UpdateCylinder(&this->actor, &this->collider1);
    Collider_UpdateCylinder(&this->actor, &this->collider2);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
    if (!(this->stateFlags & ANI_STATE_UNUSED)) {
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider2.base);
    }

    this->actor.velocity.y += this->actor.gravity;
    minVelocity = this->actor.minVelocityY;
    if (this->actor.velocity.y < minVelocity) {
        this->actor.velocity.y = minVelocity;
    }

    Actor_ApplyMovement(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    this->actionFunc(this, globalCtx);
    if (this->actor.xzDistToPlayer < 100.0f && !(this->stateFlags & ANI_STATE_CLIMBING)) {
        func_800E9250(globalCtx, &this->actor, &this->headRot, &this->unk2E6, this->actor.focus.pos);
        this->unk2E6.x = this->unk2E6.y = this->unk2E6.z = 0;
    } else {
        Math_SmoothStepToS(&this->headRot.x, 0, 6, 6200, 100);
        Math_SmoothStepToS(&this->headRot.y, 0, 6, 6200, 100);
        Math_SmoothStepToS(&this->unk2E6.x, 0, 6, 6200, 100);
        Math_SmoothStepToS(&this->unk2E6.y, 0, 6, 6200, 100);
    }

    this->blinkFunc(this);
    if (this->stateFlags & ANI_STATE_FALLING) {
        if (this->actor.cutscene == -1) {
            this->stateFlags &= ~ANI_STATE_FALLING;
        } else if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
            ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, &this->actor);
            this->actor.cutscene = ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);
            func_800E02AC(Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(this->actor.cutscene)),
                          &this->actor);
        } else {
            ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        }
    }
}

s32 EnAni_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* actor) {
    EnAni* this = (EnAni*)actor;
    if (limbIndex == 15) { // HEAD
        rot->x += this->headRot.y;
        rot->z += this->headRot.x;
    }
    return false;
}

void EnAni_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* actor) {
    if (limbIndex == 15) { // HEAD
        Matrix_MultiplyVector3fByState(&D_809686A4, &actor->focus.pos);
    }
}

void EnAni_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnAni* this = THIS;
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    Matrix_InsertTranslation(0.0f, 0.0f, -1000.0f, 1);
    func_8012C5B0(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(gEyeTextures[this->blinkState]));

    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnAni_OverrideLimbDraw, EnAni_PostLimbDraw, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
