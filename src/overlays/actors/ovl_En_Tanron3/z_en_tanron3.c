/*
 * File: z_en_tanron3.c
 * Overlay: ovl_En_Tanron3
 * Description: Small Fish summoned by Gyorg
 */

#include "z_en_tanron3.h"
#include "overlays/actors/ovl_Boss_03/z_boss_03.h"

#define FLAGS 0x00000035

#define THIS ((EnTanron3*)thisx)

void EnTanron3_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTanron3_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTanron3_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTanron3_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnTanron3_SetupAct(EnTanron3* this, GlobalContext* globalCtx);
void EnTanron3_Act(EnTanron3* this, GlobalContext* globalCtx);
void EnTanron3_Kill(EnTanron3* this, GlobalContext* globalCtx);

static Vec3f sZeroVec[] = { 0.0f, 0.0f, 0.0f };

static Boss03* sGyorg = NULL;

const ActorInit En_Tanron3_InitVars = {
    ACTOR_EN_TANRON3,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BOSS03,
    sizeof(EnTanron3),
    (ActorFunc)EnTanron3_Init,
    (ActorFunc)EnTanron3_Destroy,
    (ActorFunc)EnTanron3_Update,
    (ActorFunc)EnTanron3_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT3,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK3,
        { 0xF7CFFFFF, 0x00, 0x02 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 7, 10, -5, { 0, 0, 0 } },
};

// This actor has two colliders (one for AC and one for AT), but uses the same
// ColliderCylinderInit for both of them, leaving this one totally unused.
static ColliderCylinderInit sUnusedCylinderInit = {
    {
        COLTYPE_HIT3,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK3,
        { 0xF7CFFFFF, 0x00, 0x02 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 20, 20, -10, { 0, 0, 0 } },
};

extern FlexSkeletonHeader D_0600DA20;
extern AnimationHeader D_0600DAAC;

void EnTanron3_CreateEffect(GlobalContext* globalCtx, Vec3f* effectPos) {
    UnkTanron3Effect* effectPtr = (UnkTanron3Effect*)globalCtx->specialEffects;
    s16 i;

    for (i = 0; i < 150; i++, effectPtr++) {
        if ((effectPtr->unk_00 == 0) || (effectPtr->unk_00 == 1)) {
            effectPtr->unk_00 = 2;
            effectPtr->unk_04 = *effectPos;
            effectPtr->unk_10 = *sZeroVec;
            effectPtr->unk_1C = *sZeroVec;
            effectPtr->unk_1C.y = -2.0f;
            effectPtr->unk_34.x = 0.1f;
            effectPtr->unk_34.y = 0.0f;
            effectPtr->unk_34.z = Rand_ZeroFloat(M_PI * 2);
            effectPtr->unk_02 = Rand_ZeroFloat(100.0f);
            effectPtr->unk_10.x = randPlusMinusPoint5Scaled(25.0f);
            effectPtr->unk_10.z = randPlusMinusPoint5Scaled(25.0f);
            return;
        }
    }
}

void EnTanron3_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnTanron3* this = THIS;

    this->actor.gravity = -1.0f;
    Collider_InitAndSetCylinder(globalCtx, &this->atCollider, &this->actor, &sCylinderInit);
    Collider_InitAndSetCylinder(globalCtx, &this->acCollider, &this->actor, &sCylinderInit);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &D_0600DA20, &D_0600DAAC, this->jointTable, this->morphTable, 10);
    Actor_SetScale(&this->actor, 0.02f);
    EnTanron3_SetupAct(this, globalCtx);
    this->actor.flags &= ~1;
    this->currentRotationAngle = Rand_ZeroFloat(500000.0f);
    this->waterSurfaceYPos = 430.0f;
    sGyorg = (Boss03*)this->actor.parent;
}

void EnTanron3_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    sGyorg->unk_252--;
}

void EnTanron3_SpawnBubbles(EnTanron3* this, GlobalContext* globalCtx) {
    static Color_RGBA8 sPrimColor = { 100, 55, 55, 255 };
    static Color_RGBA8 sEnvColor = { 50, 10, 10, 255 };
    s32 i;
    Vec3f velocity;
    Vec3f acceleration;

    for (i = 0; i < 20; i++) {
        Matrix_InsertYRotation_f(Rand_ZeroFloat(2 * M_PI), MTXMODE_NEW);
        Matrix_RotateStateAroundXAxis(Rand_ZeroFloat(2 * M_PI));
        Matrix_GetStateTranslationAndScaledZ(Rand_ZeroFloat(3.0f) + 2.0f, &velocity);
        acceleration.x = velocity.x * -0.05f;
        acceleration.y = velocity.y * -0.05f;
        acceleration.z = velocity.z * -0.05f;
        EffectSsDtBubble_SpawnCustomColor(globalCtx, &this->actor.world.pos, &velocity, &acceleration, &sPrimColor,
                                          &sEnvColor, Rand_ZeroFloat(30.0f) + 70.0f, Rand_ZeroFloat(5.0f) + 15.0f, 0);
    }
}

void EnTanron3_SetupAct(EnTanron3* this, GlobalContext* globalCtx) {
    this->actionFunc = EnTanron3_Act;
    Animation_MorphToLoop(&this->skelAnime, &D_0600DAAC, -10.0f);
    this->rotationStep = 0;
    this->rotationScale = 5;
    this->workTimer[TIMER_PICK_DIRECTION_OR_DIE] = 50;
    this->actor.speedXZ = 5.0f;
    this->speedMaxStep = 0.5f;
    this->deviationFromCurrentPos.x = randPlusMinusPoint5Scaled(500.0f);
    this->deviationFromCurrentPos.y = randPlusMinusPoint5Scaled(100.0f);
    this->deviationFromCurrentPos.z = randPlusMinusPoint5Scaled(500.0f);
    Math_Vec3f_Copy(&this->currentPos, &this->actor.world.pos);
    this->timer = Rand_ZeroFloat(100.0f);
}

void EnTanron3_Act(EnTanron3* this, GlobalContext* globalCtx) {
    s32 atanTemp;
    f32 xDistance;
    f32 yDistance;
    f32 zDistance;
    f32 xzDistance;
    f32 extraScaleY = 0.0f;
    Player* player = GET_PLAYER(globalCtx);

    this->skelAnime.curFrame = 4.0f;
    if ((player->actor.bgCheckFlags & 1) && (player->actor.shape.feetPos[0].y >= 438.0f)) {
        // Player is standing on the central platform
        this->isPassive = true;
    } else if (this->isPassive && this->workTimer[TIMER_ATTACK_OR_WAIT] == 0 && !(this->timer & 0x1F)) {
        xDistance = this->currentPos.x - player->actor.world.pos.x;
        zDistance = this->currentPos.z - player->actor.world.pos.z;
        if (sqrtf(SQ(xDistance) + SQ(zDistance)) < 500.0f) {
            this->isPassive = false;
            this->workTimer[TIMER_ATTACK_OR_WAIT] = 150;
        }
    }
    if (this->actor.world.pos.y < this->waterSurfaceYPos) {
        this->isBeached = false;
        switch (this->isPassive) {
            case false:
                this->targetSpeedXZ = 5.0f;
                this->targetRotationStep = 0x1000;
                this->nextRotationAngle = 0x3A98;
                Math_Vec3f_Copy(&this->currentPos, &player->actor.world.pos);
                if (!(this->timer & 0xF)) {
                    if ((Rand_ZeroOne() < 0.5f) && (this->actor.xzDistToPlayer <= 200.0f)) {
                        Audio_PlayActorSound2(&this->actor, NA_SE_EN_PIRANHA_ATTACK);
                    }
                }
                if ((this->workTimer[TIMER_ATTACK_OR_WAIT] == 0) || (player->stateFlags2 & 0x80)) {
                    this->workTimer[TIMER_ATTACK_OR_WAIT] = 150;
                    this->isPassive = true;
                }
                break;
            case true:
                if ((sGyorg->unk_324 != 0) && (!(this->timer & 7))) {
                    this->nextRotationAngle = 0x4E20;
                    this->actor.speedXZ = 6.0f;
                } else {
                    this->nextRotationAngle = 0x1F40;
                }
                this->targetRotationStep = 0x200;
                this->targetSpeedXZ = 2.0f;
                atanTemp = Math_FAtan2F(this->currentPos.z, this->currentPos.x);
                Matrix_RotateY(atanTemp, MTXMODE_NEW);
                Matrix_GetStateTranslationAndScaledZ(700.0f, &this->currentPos);
                this->currentPos.y = 250.0f;
                extraScaleY = 150.0f;
                break;
        }
        if (this->workTimer[TIMER_OUT_OF_WATER] == 0) {
            if ((this->workTimer[TIMER_PICK_DIRECTION_OR_DIE] == 0) && (this->actor.speedXZ > 1.0f)) {
                this->workTimer[TIMER_PICK_DIRECTION_OR_DIE] = Rand_ZeroFloat(20.0f);
                this->deviationFromCurrentPos.x = randPlusMinusPoint5Scaled(100.0f);
                this->deviationFromCurrentPos.y = randPlusMinusPoint5Scaled(50.0f + extraScaleY);
                this->deviationFromCurrentPos.z = randPlusMinusPoint5Scaled(100.0f);
            }
            this->targetPos.y = this->currentPos.y + this->deviationFromCurrentPos.y + 50.0f;
        }
        this->targetPos.x = this->currentPos.x + this->deviationFromCurrentPos.x;
        this->targetPos.z = this->currentPos.z + this->deviationFromCurrentPos.z;
        xDistance = this->targetPos.x - this->actor.world.pos.x;
        yDistance = this->targetPos.y - this->actor.world.pos.y;
        zDistance = this->targetPos.z - this->actor.world.pos.z;
        xzDistance = sqrtf(SQ(xDistance) + SQ(zDistance));
        atanTemp = Math_FAtan2F(xzDistance, -yDistance);
        Math_ApproachS(&this->actor.world.rot.x, atanTemp, this->rotationScale, this->rotationStep);
        atanTemp = Math_FAtan2F(zDistance, xDistance);
        Math_SmoothStepToS(&this->actor.world.rot.y, atanTemp, this->rotationScale, this->rotationStep, 0);
        Math_ApproachS(&this->rotationStep, this->targetRotationStep, 1, 0x100);
        Math_ApproachF(&this->actor.speedXZ, this->targetSpeedXZ, 1.0f, this->speedMaxStep);
        Actor_SetVelocityAndMoveXYRotationReverse(&this->actor);
    } else {
        switch (this->isBeached) {
            case false:
                this->actor.gravity = -1.0f;
                this->targetPos.y = (this->waterSurfaceYPos - 50.0f);
                this->workTimer[TIMER_OUT_OF_WATER] = 25;
                Math_ApproachS(&this->actor.world.rot.x, 0x3000, 5, 0xBD0);
                if (this->actor.bgCheckFlags & 8) {
                    this->actor.speedXZ = 0.0f;
                    if (this->actor.velocity.y > 0.0f) {
                        this->actor.velocity.y = -1.0f;
                    }
                }
                if (this->actor.bgCheckFlags & 1) {
                    this->isBeached = true;
                }
                break;
            case true:
                this->nextRotationAngle = 0x3A98;
                this->actor.gravity = -1.5f;
                if (this->actor.bgCheckFlags & 1) {
                    this->actor.velocity.y = Rand_ZeroFloat(5.0f) + 5.0f;
                    this->actor.speedXZ = Rand_ZeroFloat(2.0f) + 2.0f;
                    if (Rand_ZeroOne() < 0.5f) {
                        this->targetShapeRotation.x =
                            (s16)randPlusMinusPoint5Scaled(500.0f) + this->targetShapeRotation.x + 0x8000;
                    }
                    if (Rand_ZeroOne() < 0.5f) {
                        this->targetShapeRotation.z =
                            (s16)randPlusMinusPoint5Scaled(500.0f) + this->targetShapeRotation.z + 0x8000;
                    }
                    if (Rand_ZeroOne() < 0.5f) {
                        this->targetShapeRotation.y = (s16)Rand_ZeroFloat(0x10000);
                    }
                    this->actor.world.rot.y = Math_FAtan2F(this->actor.world.pos.z, this->actor.world.pos.x) +
                                              (s16)randPlusMinusPoint5Scaled(52768.0f);
                }
                Math_ApproachS(&this->actor.shape.rot.y, this->targetShapeRotation.y, 3, 0x500);
                Math_ApproachS(&this->actor.shape.rot.x, this->targetShapeRotation.x, 3, 0xC00);
                Math_ApproachS(&this->actor.shape.rot.z, this->targetShapeRotation.z, 3, 0xC00);
                if ((Rand_ZeroOne() < 0.5f) & !(this->timer & 3)) {
                    Vec3f effectPos;

                    effectPos.x = randPlusMinusPoint5Scaled(30.0f) + this->actor.world.pos.x;
                    effectPos.y = this->actor.world.pos.y;
                    effectPos.z = randPlusMinusPoint5Scaled(30.0f) + this->actor.world.pos.z;
                    EnTanron3_CreateEffect(globalCtx, &effectPos);
                }
                break;
        }
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    }
    this->currentRotationAngle += this->nextRotationAngle;
    this->trunkRotation = Math_SinS(this->currentRotationAngle) * 5000.0f;
    this->bodyRotation = Math_SinS(this->currentRotationAngle + 0x6978) * 5000.0f;
    this->tailRotation = Math_SinS(this->currentRotationAngle) * 5000.0f;
    if (!this->isBeached) {
        this->actor.shape.rot = this->actor.world.rot;
    }
}

void EnTanron3_SetupKill(EnTanron3* this, GlobalContext* globalCtx) {
    f32 xDistance;
    f32 yDistance;
    f32 zDistance;
    Player* player = GET_PLAYER(globalCtx);

    this->actionFunc = EnTanron3_Kill;
    xDistance = this->actor.world.pos.x - player->actor.world.pos.x;
    yDistance = this->actor.world.pos.y - player->actor.world.pos.y + 30.0f;
    zDistance = this->actor.world.pos.z - player->actor.world.pos.z;
    this->actor.world.rot.x = Math_FAtan2F(sqrtf(SQ(xDistance) + SQ(zDistance)), -yDistance);
    this->actor.world.rot.y = Math_FAtan2F(zDistance, xDistance);
    this->workTimer[TIMER_PICK_DIRECTION_OR_DIE] = 6;
    this->actor.speedXZ = 10.0f;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_KONB_MINI_DEAD);
}

void EnTanron3_Kill(EnTanron3* this, GlobalContext* globalCtx) {
    Actor_SetVelocityAndMoveXYRotationReverse(&this->actor);
    if (this->workTimer[TIMER_PICK_DIRECTION_OR_DIE] == 0) {
        EnTanron3_SpawnBubbles(this, globalCtx);
        Actor_MarkForDeath(&this->actor);
        if (Rand_ZeroOne() < 0.3f) {
            Item_DropCollectibleRandom(globalCtx, NULL, &this->actor.world.pos, 0x60);
        }
    }
}

void EnTanron3_CheckCollisions(EnTanron3* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (player->actor.world.pos.y > 350.0f) {
        if (this->atCollider.base.atFlags & AT_HIT) {
            this->atCollider.base.atFlags &= ~AT_HIT;
            func_800B8D50(globalCtx, NULL, 3.0f, Math_FAtan2F(-player->actor.world.pos.z, -player->actor.world.pos.x),
                          5.0f, 0);
        }
    }
    if (this->acCollider.base.acFlags & AC_HIT) {
        this->acCollider.base.acFlags &= ~AC_HIT;
        if (this->deathTimer == 0) {
            this->deathTimer = 15;
            this->fogTimer = 15;
            EnTanron3_SetupKill(this, globalCtx);
            sGyorg->unk_324 = 20;
        }
    }
}

void EnTanron3_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnTanron3* this = THIS;
    s16 i;
    Vec3f splashPos;

    if (KREG(63) == 0) {
        this->timer++;
        for (i = 0; i < TIMER_MAX; i++) {
            if (this->workTimer[i] != 0) {
                this->workTimer[i]--;
            }
        }
        if (this->deathTimer != 0) {
            this->deathTimer--;
        }
        if (this->fogTimer != 0) {
            this->fogTimer--;
        }
        this->actionFunc(this, globalCtx);
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 10.0f, 10.0f, 20.0f, 5);
        if (((this->actor.prevPos.y < this->waterSurfaceYPos) && (this->waterSurfaceYPos <= this->actor.world.pos.y)) ||
            ((this->actor.prevPos.y > this->waterSurfaceYPos) && (this->waterSurfaceYPos >= this->actor.world.pos.y))) {
            splashPos.x = this->actor.world.pos.x;
            splashPos.y = this->waterSurfaceYPos + 10.0f;
            splashPos.z = this->actor.world.pos.z;
            EffectSsGSplash_Spawn(globalCtx, &splashPos, NULL, NULL, 1, 500);
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_OUT_OF_WATER);
        }
    }
    EnTanron3_CheckCollisions(this, globalCtx);
    Collider_UpdateCylinder(&this->actor, &this->atCollider);
    Collider_UpdateCylinder(&this->actor, &this->acCollider);
    CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->atCollider.base);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->acCollider.base);
    if ((s8)sGyorg->actor.colChkInfo.health <= 0 && this->actionFunc != EnTanron3_Kill) {
        EnTanron3_SetupKill(this, globalCtx);
        this->workTimer[TIMER_PICK_DIRECTION_OR_DIE] = 0;
    }
}

s32 EnTanron3_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                               Actor* actor) {
    EnTanron3* this = (EnTanron3*)actor;

    if (limbIndex == 1) {
        rot->y += this->bodyRotation;
    }
    if (limbIndex == 3) {
        rot->y += this->tailRotation;
    }
    if (limbIndex == 4) {
        rot->y += this->trunkRotation;
    }
    return 0;
}

void EnTanron3_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnTanron3* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    if ((this->fogTimer % 2) != 0) {
        POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 255, 900, 1099);
    }
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnTanron3_OverrideLimbDraw, NULL, &this->actor);
    POLY_OPA_DISP = func_801660B8(globalCtx, POLY_OPA_DISP);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
