/*
 * File: z_en_sb.c
 * Overlay: ovl_En_Sb
 * Description: Shellblade
 */

#include "z_en_sb.h"

#define FLAGS 0x00000005

#define THIS ((EnSb*)thisx)

void EnSb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSb_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSb_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnSb_SetupWaitClosed(EnSb* this);
void EnSb_Idle(EnSb* this, GlobalContext* globalCtx);
void EnSb_Open(EnSb* this, GlobalContext* globalCtx);
void EnSb_WaitOpen(EnSb* this, GlobalContext* globalCtx);
void EnSb_TurnAround(EnSb* this, GlobalContext* globalCtx);
void EnSb_Lunge(EnSb* this, GlobalContext* globalCtx);
void EnSb_Bounce(EnSb* this, GlobalContext* globalCtx);
void EnSb_ReturnToIdle(EnSb* this, GlobalContext* globalCtx);

const ActorInit En_Sb_InitVars = {
    ACTOR_EN_SB,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_SB,
    sizeof(EnSb),
    (ActorFunc)EnSb_Init,
    (ActorFunc)EnSb_Destroy,
    (ActorFunc)EnSb_Update,
    (ActorFunc)EnSb_Draw,
};

static ColliderCylinderInitType1 sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x04, 0x08 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 30, 40, 0, { 0, 0, 0 } },
};

static DamageTable sDamageTable = {
    0x00, 0x00, 0x00, 0xF1, 0xF1, 0xF1, 0x00, 0xF1, 0x00, 0x00, 0x00, 0xF1, 0xF1, 0xF1, 0x00, 0x00,
    0xF1, 0x00, 0x00, 0xF1, 0x00, 0x00, 0x00, 0xF1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF1,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_S8(hintId, 39, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, 2, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 30, ICHAIN_STOP),
};

static Vec3f sFlamePosOffsets[] = {
    { 5.0f, 0.0f, 0.0f },
    { -5.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 5.0f },
    { 0.0f, 0.0f, -5.0f },
};

extern FlexSkeletonHeader D_06002BF0;
extern AnimationHeader D_06000194;
extern AnimationHeader D_0600004C;
extern AnimationHeader D_06000124;
extern AnimationHeader D_06002C8C;
extern AnimationHeader D_060000B4;

void EnSb_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnSb* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->actor.colChkInfo.damageTable = &sDamageTable;
    this->actor.colChkInfo.mass = 0xA;
    this->actor.colChkInfo.health = 2;
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06002BF0, &D_06000194, this->limbDrawTable,
                     this->transitionDrawTable, 9);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinderType1(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    this->isDead = false;
    this->actor.colChkInfo.mass = 0x5A;
    this->actor.shape.rot.y = 0;
    this->actor.speedXZ = 0.0f;
    this->actor.gravity = -0.35f;
    this->fireCount = 0;
    this->unk_252 = 0;
    this->actor.velocity.y = -1.0f;
    Actor_SetScale(&this->actor, 0.006f);
    EnSb_SetupWaitClosed(this);
}

void EnSb_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnSb* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnSb_SpawnBubbles(GlobalContext* globalCtx, EnSb* this) {
    s32 bubbleCount;

    if (this->actor.yDistToWater > 0.0f) {
        for (bubbleCount = 0; bubbleCount < 10; bubbleCount++) {
            EffectSsBubble_Spawn(globalCtx, &this->actor.world.pos, 10.0f, 10.0f, 30.0f, 0.25f);
        }
    }
}

void EnSb_SetupWaitClosed(EnSb* this) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_0600004C, 1.0f, 0, SkelAnime_GetFrameCount(&D_0600004C.common), 2, 0.0f);
    this->state = SHELLBLADE_WAIT_CLOSED;
    this->actionFunc = EnSb_Idle;
}

void EnSb_SetupOpen(EnSb* this) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_06000194, 1.0f, 0, SkelAnime_GetFrameCount(&D_06000194.common), 2, 0.0f);
    this->state = SHELLBLADE_OPEN;
    this->actionFunc = EnSb_Open;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_KUSAMUSHI_VIBE);
}

void EnSb_SetupWaitOpen(EnSb* this) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_06002C8C, 1.0f, 0, SkelAnime_GetFrameCount(&D_06002C8C.common), 0, 0.0f);
    this->state = SHELLBLADE_WAIT_OPEN;
    this->actionFunc = EnSb_WaitOpen;
}

void EnSb_SetupLunge(EnSb* this) {
    f32 frameCount = SkelAnime_GetFrameCount(&D_06000124.common);
    f32 playbackSpeed = this->actor.yDistToWater > 0.0f ? 1.0f : 0.0f;

    SkelAnime_ChangeAnim(&this->skelAnime, &D_06000124, playbackSpeed, 0.0f, frameCount, 2, 0);
    this->state = SHELLBLADE_LUNGE;
    this->actionFunc = EnSb_Lunge;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_KUSAMUSHI_VIBE);
}

void EnSb_SetupBounce(EnSb* this) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_060000B4, 1.0f, 0, SkelAnime_GetFrameCount(&D_060000B4.common), 2, 0.0f);
    this->state = SHELLBLADE_BOUNCE;
    this->actionFunc = EnSb_Bounce;
}

void EnSb_SetupIdle(EnSb* this, s32 changeSpeed) {
    f32 frameCount = SkelAnime_GetFrameCount(&D_0600004C.common);

    if (this->state != SHELLBLADE_WAIT_CLOSED) {
        SkelAnime_ChangeAnim(&this->skelAnime, &D_0600004C, 1.0f, 0, frameCount, 2, 0.0f);
    }
    this->state = SHELLBLADE_WAIT_CLOSED;
    if (changeSpeed) {
        if (this->actor.yDistToWater > 0.0f) {
            this->actor.speedXZ = -5.0f;
            if (this->actor.velocity.y < 0.0f) {
                this->actor.velocity.y = 2.1f;
            }
        } else {
            this->actor.speedXZ = -6.0f;
            if (this->actor.velocity.y < 0.0f) {
                this->actor.velocity.y = 1.4f;
            }
        }
    }
    this->attackTimer = 60;
    this->actionFunc = EnSb_ReturnToIdle;
}

void EnSb_Idle(EnSb* this, GlobalContext* globalCtx) {
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x7D0, 0);
    if (this->actor.xzDistToPlayer <= 240.0f && this->actor.xzDistToPlayer > 0.0f) {
        EnSb_SetupOpen(this);
    }
}

void EnSb_Open(EnSb* this, GlobalContext* globalCtx) {
    f32 currentFrame = this->skelAnime.animCurrentFrame;

    if (SkelAnime_GetFrameCount(&D_06000194.common) <= currentFrame) {
        this->vulnerableTimer = 20;
        EnSb_SetupWaitOpen(this);
    } else {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x7D0, 0);
        if (this->actor.xzDistToPlayer > 240.0f || this->actor.xzDistToPlayer <= 40.0f) {
            this->vulnerableTimer = 0;
            EnSb_SetupWaitClosed(this);
        }
    }
}

void EnSb_WaitOpen(EnSb* this, GlobalContext* globalCtx) {

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x7D0, 0);
    if (this->actor.xzDistToPlayer > 240.0f || this->actor.xzDistToPlayer <= 40.0f) {
        this->vulnerableTimer = 0;
        EnSb_SetupWaitClosed(this);
    }
    if (this->vulnerableTimer > 0) {
        this->vulnerableTimer--;
    } else {
        this->vulnerableTimer = 0;
        this->attackTimer = 0;
        this->yawAngle = this->actor.yawTowardsPlayer;
        this->actionFunc = EnSb_TurnAround;
    }
}

void EnSb_TurnAround(EnSb* this, GlobalContext* globalCtx) {
    s16 invertedYaw = this->yawAngle + 0x8000;

    Math_SmoothStepToS(&this->actor.shape.rot.y, invertedYaw, 1, 0x1F40, 0xA);
    if (this->actor.shape.rot.y == invertedYaw) {
        this->actor.world.rot.y = this->yawAngle;
        if (this->actor.yDistToWater > 0.0f) {
            this->actor.velocity.y = 3.0f;
            this->actor.speedXZ = 5.0f;
            this->actor.gravity = -0.35f;
        } else {
            this->actor.velocity.y = 2.0f;
            this->actor.speedXZ = 6.0f;
            this->actor.gravity = -2.0f;
        }
        EnSb_SpawnBubbles(globalCtx, this);
        this->bounceCounter = 3;
        EnSb_SetupLunge(this);
    }
}

void EnSb_Lunge(EnSb* this, GlobalContext* globalCtx) {
    Math_StepToF(&this->actor.speedXZ, 0.0f, 0.2f);
    if (this->actor.velocity.y <= -0.1f || this->actor.bgCheckFlags & 2) {
        if (!(this->actor.yDistToWater > 0.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_EYEGOLE_ATTACK);
        }
        this->actor.bgCheckFlags &= ~2;
        EnSb_SetupBounce(this);
    }
}

void EnSb_Bounce(EnSb* this, GlobalContext* globalCtx) {
    s32 pad;
    f32 currentFrame = currentFrame = this->skelAnime.animCurrentFrame;
    f32 frameCount = frameCount = SkelAnime_GetFrameCount(&D_060000B4.common);

    Math_StepToF(&this->actor.speedXZ, 0.0f, 0.2f);
    if (currentFrame == frameCount) {
        if (this->bounceCounter != 0) {
            this->bounceCounter--;
            this->attackTimer = 1;
            if (this->actor.yDistToWater > 0.0f) {
                this->actor.velocity.y = 3.0f;
                this->actor.speedXZ = 5.0f;
                this->actor.gravity = -0.35f;
            } else {
                this->actor.velocity.y = 2.0f;
                this->actor.speedXZ = 6.0f;
                this->actor.gravity = -2.0f;
            }
            EnSb_SpawnBubbles(globalCtx, this);
            EnSb_SetupLunge(this);
        } else if (this->actor.bgCheckFlags & 1) {
            this->actor.bgCheckFlags &= ~2;
            this->actor.speedXZ = 0.0f;
            this->attackTimer = 1;
            EnSb_SetupWaitClosed(this);
        }
    }
}

void EnSb_ReturnToIdle(EnSb* this, GlobalContext* globalCtx) {
    if (this->attackTimer != 0) {
        this->attackTimer--;
        if (this->actor.bgCheckFlags & 1) {
            this->actor.bgCheckFlags &= ~1;
            this->actor.speedXZ = 0.0f;
        }
    } else if (this->actor.bgCheckFlags & 1) {
        this->actor.bgCheckFlags &= ~1;
        this->actionFunc = EnSb_Idle;
        this->actor.speedXZ = 0.0f;
    }
}

void EnSb_UpdateDamage(EnSb* this, GlobalContext* globalCtx) {
    Vec3f hitPoint;

    if (this->collider.base.acFlags & AC_HIT) {
        s32 hitPlayer = 0;
        this->collider.base.acFlags &= ~AC_HIT;
        if (this->actor.colChkInfo.damageEffect == 0xF) {
            hitPlayer = 0;
            if (this->vulnerableTimer != 0) {
                func_800BE22C(&this->actor);
                func_800BCB70(&this->actor, 0x4000, 0xFF, 0x2000, 80);
                hitPlayer = 1;
            }
        }
        if (hitPlayer) {
            this->unk_252 = 0;
            if ((this->actor.draw != NULL) && (this->isDrawn == false)) {
                this->isDrawn = true;
            }
            this->isDead = true;
            func_800BBA88(globalCtx, &this->actor);
            func_800F0568(globalCtx, &this->actor.world.pos, 0x28, NA_SE_EN_BEE_FLY);
            return;
        }
        hitPoint.x = this->collider.info.bumper.hitPos.x;
        hitPoint.y = this->collider.info.bumper.hitPos.y;
        hitPoint.z = this->collider.info.bumper.hitPos.z;
        CollisionCheck_SpawnShieldParticlesMetal2(globalCtx, &hitPoint);
        return;
    }
    if (this->collider.base.atFlags & AT_HIT) {
        EnSb_SetupIdle(this, 1);
    }
}

void EnSb_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnSb* this = THIS;
    Player* player = PLAYER;

    if (this->isDead) {
        if (this->actor.yDistToWater > 0.0f) {
            this->actor.params = 4;
        } else {
            this->actor.params = 1;
        }
        Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.world.pos, 0x80);
        Actor_MarkForDeath(&this->actor);
    } else {
        Actor_SetHeight(&this->actor, 20.0f);
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
        this->actionFunc(this, globalCtx);
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 25.0f, 20.0f, 5);
        EnSb_UpdateDamage(this, globalCtx);
        if (player->stateFlags1 & 0x8000000) {
            Collider_UpdateCylinder(&this->actor, &this->collider);
            if (this->vulnerableTimer == 0) {
                CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
            }
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }
        SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    }
}

void EnSb_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    s8 phi_a2;
    EnSb* this = THIS;

    if (this->isDrawn != false) {
        if (limbIndex < 7) {
            phi_a2 = (this->actor.yDistToWater > 0) ? 4 : 1;
            func_800BBCEC(thisx, globalCtx, phi_a2, dList);
        }
        if (limbIndex == 6) {
            this->isDrawn = false;
            this->actor.draw = NULL;
        }
    }
}

void EnSb_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnSb* this = THIS;
    Vec3f flamePos;
    Vec3f* offset;
    s16 fireDecr;

    func_800B8050(&this->actor, globalCtx, 1);
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount, NULL,
                     EnSb_PostLimbDraw, &this->actor);
    if (this->fireCount != 0) {
        this->actor.colorFilterTimer++;
        fireDecr = this->fireCount - 1;
        if (!(fireDecr & 1)) {
            offset = &sFlamePosOffsets[fireDecr & 3];
            flamePos.x = randPlusMinusPoint5Scaled(5.0f) + (this->actor.world.pos.x + offset->x);
            flamePos.y = randPlusMinusPoint5Scaled(5.0f) + (this->actor.world.pos.y + offset->y);
            flamePos.z = randPlusMinusPoint5Scaled(5.0f) + (this->actor.world.pos.z + offset->z);
            EffectSsEnFire_SpawnVec3f(globalCtx, &this->actor, &flamePos, 100, 0, 0, -1);
        }
    }
}
