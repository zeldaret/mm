/*
 * File: z_en_crow.c
 * Overlay: ovl_En_Crow
 * Description: Guay
 */

#include "z_en_crow.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_1000 | ACTOR_FLAG_4000)

#define THIS ((EnCrow*)thisx)

void EnCrow_Init(Actor* thisx, GlobalContext* globalCtx);
void EnCrow_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnCrow_Update(Actor* thisx, GlobalContext* globalCtx);
void EnCrow_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnCrow_SetupFlyIdle(EnCrow* this);
void EnCrow_FlyIdle(EnCrow* this, GlobalContext* globalCtx);
void EnCrow_SetupDiveAttack(EnCrow* this);
void EnCrow_DiveAttack(EnCrow* this, GlobalContext* globalCtx);
void EnCrow_CheckIfFrozen(EnCrow* this, GlobalContext* globalCtx);
void EnCrow_Damaged(EnCrow* this, GlobalContext* globalCtx);
void EnCrow_SetupDie(EnCrow* this);
void EnCrow_Die(EnCrow* this, GlobalContext* globalCtx);
void EnCrow_SetupRespawn(EnCrow* this);
void EnCrow_TurnAway(EnCrow* this, GlobalContext* globalCtx);
void EnCrow_Respawn(EnCrow* this, GlobalContext* globalCtx);

const ActorInit En_Crow_InitVars = {
    ACTOR_EN_CROW,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_CROW,
    sizeof(EnCrow),
    (ActorFunc)EnCrow_Init,
    (ActorFunc)EnCrow_Destroy,
    (ActorFunc)EnCrow_Update,
    (ActorFunc)EnCrow_Draw,
};

static ColliderJntSphElementInit sJntSphElementsInit[1] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x08 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_HARD,
            BUMP_ON,
            OCELEM_ON,
        },
        { 1, { { 0, 0, 0 }, 20 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_HIT3,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    1,
    sJntSphElementsInit,
};

static CollisionCheckInfoInit sColChkInfoInit = { 1, 15, 30, 30 };

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x5),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};

static s32 D_8099C0CC = 0;

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 3000, ICHAIN_CONTINUE),
    ICHAIN_S8(hintId, 88, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -500, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_STOP),
};

void EnCrow_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnCrow* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gGuaySkel, &gGuayFlyAnim, this->jointTable, this->morphTable,
                       OBJECT_CROW_LIMB_MAX);
    Collider_InitAndSetJntSph(globalCtx, &this->collider, &this->actor, &sJntSphInit, this->colliderItems);
    this->collider.elements->dim.worldSphere.radius = sJntSphInit.elements[0].dim.modelSphere.radius;
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    ActorShape_Init(&this->actor.shape, 2000.0f, ActorShadow_DrawCircle, 20.0f);
    D_8099C0CC = 0;
    if (this->actor.parent != NULL) {
        this->actor.flags &= ~ACTOR_FLAG_1;
    }
    EnCrow_SetupFlyIdle(this);
}

void EnCrow_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnCrow* this = THIS;

    Collider_DestroyJntSph(globalCtx, &this->collider);
}

void EnCrow_SetupFlyIdle(EnCrow* this) {
    this->timer = 100;
    this->collider.base.acFlags |= AC_ON;
    this->actionFunc = EnCrow_FlyIdle;
    this->skelAnime.playSpeed = 1.0f;
}

void EnCrow_FlyIdle(EnCrow* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    f32 dist;
    s32 onInitialAnimFrame;
    s16 yaw;

    SkelAnime_Update(&this->skelAnime);
    onInitialAnimFrame = Animation_OnFrame(&this->skelAnime, 0.0f);
    this->actor.speedXZ = (Rand_ZeroOne() * 1.5f) + 3.0f;

    if ((this->actor.parent != NULL) && (this->actor.parent->home.rot.z == 0)) {
        this->actor.home.pos.x = this->actor.parent->world.pos.x;
        this->actor.home.pos.z = this->actor.parent->world.pos.z;
        dist = Actor_XZDistanceToPoint(&this->actor, &this->actor.parent->world.pos);
    } else {
        dist = 450.0f;
        this->actor.flags |= ACTOR_FLAG_1;
    }

    if (this->actor.bgCheckFlags & 8) {
        this->aimRotY = this->actor.wallYaw;
    } else if (Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos) > 300.0f) {
        this->aimRotY = Actor_YawToPoint(&this->actor, &this->actor.home.pos);
    }

    if ((Math_SmoothStepToS(&this->actor.shape.rot.y, this->aimRotY, 5, 0x300, 0x10) == 0) && onInitialAnimFrame &&
        (Rand_ZeroOne() < 0.1f)) {

        yaw = (Actor_YawToPoint(&this->actor, &this->actor.home.pos) - this->actor.shape.rot.y);
        if (yaw > 0) {
            this->aimRotY += Rand_S16Offset(0x1000, 0x1000);
        } else {
            this->aimRotY -= Rand_S16Offset(0x1000, 0x1000);
        }
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_KAICHO_CRY);
    }

    if ((this->actor.depthInWater > -40.0f) || (this->actor.bgCheckFlags & 1)) {
        this->aimRotX = -0x1000;
    } else if (this->actor.world.pos.y < (this->actor.home.pos.y - 50.0f)) {
        this->aimRotX = -Rand_S16Offset(0x800, 0x800);
    } else if (this->actor.world.pos.y > (this->actor.home.pos.y + 50.0f)) {
        this->aimRotX = Rand_S16Offset(0x800, 0x800);
    }

    if ((Math_SmoothStepToS(&this->actor.shape.rot.x, this->aimRotX, 0xA, 0x100, 8) == 0) && onInitialAnimFrame &&
        (Rand_ZeroOne() < 0.1f)) {
        if (this->actor.home.pos.y < this->actor.world.pos.y) {
            this->aimRotX -= Rand_S16Offset(0x400, 0x400);
        } else {
            this->aimRotX += Rand_S16Offset(0x400, 0x400);
        }

        this->aimRotX = CLAMP(this->aimRotX, -0x1000, 0x1000);
    }

    if (this->actor.bgCheckFlags & 1) {
        Math_ScaledStepToS(&this->actor.shape.rot.x, -0x100, 0x400);
    }

    if (this->timer != 0) {
        this->timer--;
    }
    if ((this->timer == 0) &&
        (((this->actor.xzDistToPlayer < 300.0f) && !(player->stateFlags1 & 0x800000)) || (dist < 300.0f)) &&
        (this->actor.depthInWater < -40.0f) && (Player_GetMask(globalCtx) != PLAYER_MASK_STONE)) {
        if (dist < this->actor.xzDistToPlayer) {
            this->actor.child = this->actor.parent;
        } else {
            this->actor.child = &player->actor;
        }
        EnCrow_SetupDiveAttack(this);
    }
}

void EnCrow_SetupDiveAttack(EnCrow* this) {
    this->timer = 300;
    this->actionFunc = EnCrow_DiveAttack;
    this->actor.speedXZ = 4.0f;
    this->skelAnime.playSpeed = 2.0f;
}

void EnCrow_DiveAttack(EnCrow* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 isFacingActor;
    Vec3f pos;
    s16 pitch;
    s16 pitchTarget;

    SkelAnime_Update(&this->skelAnime);
    if (this->timer != 0) {
        this->timer--;
    }
    isFacingActor = Actor_ActorAIsFacingActorB(&this->actor, this->actor.child, 0x2800);

    if (isFacingActor) {
        if (&player->actor == this->actor.child) {
            pos.y = this->actor.child->world.pos.y + 20.0f;
        } else {
            pos.y = this->actor.child->world.pos.y + 40.0f;
        }
        pos.x = this->actor.child->world.pos.x;
        pos.z = this->actor.child->world.pos.z;
        pitch = Actor_PitchToPoint(&this->actor, &pos);
        pitchTarget = CLAMP(pitch, -0x3000, 0x3000);
        Math_SmoothStepToS(&this->actor.shape.rot.x, pitchTarget, 2, 0x400, 64);
    } else {
        Math_SmoothStepToS(&this->actor.shape.rot.x, -0x800, 2, 0x100, 16);
    }

    if (isFacingActor || (Actor_XZDistanceBetweenActors(&this->actor, this->actor.child) > 80.0f)) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, Actor_YawBetweenActors(&this->actor, this->actor.child), 4, 0xC00,
                           0xC0);
    }
    if (((this->timer == 0) || ((&player->actor != this->actor.child) && (this->actor.child->home.rot.z != 0)) ||
         ((&player->actor == this->actor.child) &&
          ((Player_GetMask(globalCtx) == PLAYER_MASK_STONE) || (player->stateFlags1 & 0x800000))) ||
         ((this->collider.base.atFlags & AT_HIT) || (this->actor.bgCheckFlags & 9))) ||
        (this->actor.depthInWater > -40.0f)) {

        if (this->collider.base.atFlags & AT_HIT) {
            this->collider.base.atFlags &= ~AT_HIT;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_KAICHO_ATTACK);
        }
        EnCrow_SetupFlyIdle(this);
    }
}

void EnCrow_CheckIfFrozen(EnCrow* this, GlobalContext* globalCtx) {
    if (this->deathMode == 10) {
        this->deathMode = 0;
        this->effectAlpha = 0.0f;
        Actor_SpawnIceEffects(globalCtx, &this->actor, this->bodyPartsPos, 4, 2, 0.2f, 0.2f);
    }
}

void EnCrow_SetupDamaged(EnCrow* this, GlobalContext* globalCtx) {
    f32 scale;

    this->actor.speedXZ *= Math_CosS(this->actor.world.rot.x);
    this->actor.velocity.y = 0.0f;
    Animation_Change(&this->skelAnime, &gGuayFlyAnim, 0.4f, 0.0f, 0.0f, ANIMMODE_LOOP_INTERP, -3.0f);
    this->actor.shape.yOffset = 0.0f;
    this->actor.targetArrowOffset = 0.0f;
    this->actor.bgCheckFlags &= ~1;
    scale = (this->actor.scale.x * 100.0f);
    this->actor.world.pos.y += 20.0f * scale;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_KAICHO_DEAD);

    if (this->actor.colChkInfo.damageEffect == 3) {
        this->deathMode = 10; // Ice arrows
        this->effectAlpha = 1.0f;
        this->effectScale = 0.75f;
        this->steamScale = 0.5f;
    } else if (this->actor.colChkInfo.damageEffect == 4) {
        this->deathMode = 20; // Light Arrows
        this->effectAlpha = 4.0f;
        this->steamScale = 0.5f;
        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, this->collider.elements->info.bumper.hitPos.x,
                    this->collider.elements->info.bumper.hitPos.y, this->collider.elements->info.bumper.hitPos.z, 0, 0,
                    0, CLEAR_TAG_SMALL_LIGHT_RAYS);
    } else if (this->actor.colChkInfo.damageEffect == 2) {
        this->deathMode = 0; // Fire arrows
        this->effectAlpha = 4.0f;
        this->steamScale = 0.5f;
    }

    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 40);
    if (this->actor.flags & ACTOR_FLAG_8000) {
        this->actor.speedXZ = 0.0f;
    }

    this->collider.base.acFlags &= ~AC_ON;
    this->actor.flags |= ACTOR_FLAG_10;

    this->actionFunc = EnCrow_Damaged;
}

void EnCrow_Damaged(EnCrow* this, GlobalContext* globalCtx) {
    Math_StepToF(&this->actor.speedXZ, 0.0f, 0.5f);
    this->actor.colorFilterTimer = 40;

    if (!(this->actor.flags & ACTOR_FLAG_8000)) {
        if (this->deathMode != 10) {
            Math_ScaledStepToS(&this->actor.shape.rot.x, 0x4000, 0x200);
            this->actor.shape.rot.z += 0x1780;
        }
        if ((this->actor.bgCheckFlags & 1) || (this->actor.floorHeight == BGCHECK_Y_MIN)) {
            EnCrow_CheckIfFrozen(this, globalCtx);
            func_800B3030(globalCtx, &this->actor.world.pos, &gZeroVec3f, &gZeroVec3f, this->actor.scale.x * 10000.0f,
                          0, 0);
            SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 11, NA_SE_EN_EXTINCT);

            if (this->actor.parent != NULL) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            EnCrow_SetupDie(this);
        }
    }
}

void EnCrow_SetupDie(EnCrow* this) {
    this->actor.colorFilterTimer = 0;
    this->actionFunc = EnCrow_Die;
}

void EnCrow_Die(EnCrow* this, GlobalContext* globalCtx) {
    f32 stepScale;

    if (this->actor.params != 0) {
        stepScale = 0.006f;
    } else {
        stepScale = 0.002f;
    }
    if (Math_StepToF(&this->actor.scale.x, 0.0f, stepScale) != 0) {
        if (this->actor.params == 0) {
            D_8099C0CC++;
            Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.world.pos, 0x80);
        } else {
            Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.world.pos, 0x90);
        }
        EnCrow_SetupRespawn(this);
    }
    this->actor.scale.z = this->actor.scale.y = this->actor.scale.x;
}

void EnCrow_SetupTurnAway(EnCrow* this) {
    this->timer = 100;
    this->aimRotX = -0x1000;
    this->actor.speedXZ = 3.5f;
    this->aimRotY = this->actor.yawTowardsPlayer + 0x8000;
    this->skelAnime.playSpeed = 2.0f;
    if (this->actor.colChkInfo.damageEffect == 1) {
        Actor_SetColorFilter(&this->actor, 0, 255, 0, 40);
    } else {
        Actor_SetColorFilter(&this->actor, 0, 255, 0, 40);
    }
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
    this->actionFunc = EnCrow_TurnAway;
}

void EnCrow_TurnAway(EnCrow* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);

    if (this->actor.bgCheckFlags & 8) {
        this->aimRotY = this->actor.wallYaw;
    } else {
        this->aimRotY = this->actor.yawTowardsPlayer + 0x8000;
    }

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->aimRotY, 3, 0xC00, 0xC0);
    Math_SmoothStepToS(&this->actor.shape.rot.x, this->aimRotX, 5, 0x100, 0x10);

    if (this->timer != 0) {
        this->timer--;
    }

    if (this->timer == 0) {
        EnCrow_SetupFlyIdle(this);
    }
}

void EnCrow_SetupRespawn(EnCrow* this) {
    if (D_8099C0CC == 10) {
        this->actor.params = 1;
        D_8099C0CC = 0;
        this->collider.elements->dim.worldSphere.radius = sJntSphInit.elements->dim.modelSphere.radius * 0.03f * 100.0f;
    } else {
        this->actor.params = 0;
        this->collider.elements->dim.worldSphere.radius = sJntSphInit.elements->dim.modelSphere.radius;
    }
    Animation_PlayLoop(&this->skelAnime, &gGuayFlyAnim);
    Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.home.pos);
    this->actor.shape.rot.x = 0;
    this->actor.shape.rot.z = 0;
    this->timer = 300;
    this->actor.draw = NULL;
    this->actor.shape.yOffset = 2000.0f;
    this->actor.targetArrowOffset = 2000.0;
    this->effectAlpha = 0.0f;
    this->actionFunc = EnCrow_Respawn;
}

void EnCrow_Respawn(EnCrow* this, GlobalContext* globalCtx) {
    f32 target;

    if (this->timer != 0) {
        this->timer--;
    }
    if (this->timer == 0) {
        SkelAnime_Update(&this->skelAnime);
        this->actor.draw = EnCrow_Draw;
        if (this->actor.params != 0) {
            target = 0.03f;
        } else {
            target = 0.01f;
        }
        if (Math_StepToF(&this->actor.scale.x, target, target * 0.1f)) {
            this->actor.flags |= ACTOR_FLAG_1;
            this->actor.flags &= ~ACTOR_FLAG_10;
            this->actor.colChkInfo.health = 1;
            EnCrow_SetupFlyIdle(this);
        }
        this->actor.scale.z = this->actor.scale.y = this->actor.scale.x;
    }
}

void EnCrow_UpdateDamage(EnCrow* this, GlobalContext* globalCtx) {

    if (this->collider.base.acFlags & AT_HIT) {
        this->collider.base.acFlags &= ~AT_HIT;
        Actor_SetDropFlag(&this->actor, &this->collider.elements->info);

        if (this->actor.colChkInfo.damageEffect == 1) {
            EnCrow_SetupTurnAway(this);

        } else if (this->actor.colChkInfo.damageEffect == 5) {
            this->deathMode = 31; // Stunned via deku nuts or zora barrier
            this->effectAlpha = 2.0f;
            this->steamScale = 0.5f;
            EnCrow_SetupTurnAway(this);

        } else {
            this->actor.colChkInfo.health = 0;
            this->actor.flags &= ~ACTOR_FLAG_1;
            Enemy_StartFinishingBlow(globalCtx, &this->actor);
            EnCrow_SetupDamaged(this, globalCtx);
        }
    }
}

void EnCrow_Update(Actor* thisx, GlobalContext* globalCtx) {
    f32 pad;
    EnCrow* this = (EnCrow*)thisx;
    f32 height;
    f32 scale;

    EnCrow_UpdateDamage(this, globalCtx);
    this->actionFunc(this, globalCtx);
    scale = this->actor.scale.x * 100.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actor.world.rot.x = -this->actor.shape.rot.x;

    if (this->actionFunc != EnCrow_Respawn) {
        if (this->actor.colChkInfo.health != 0) {
            height = 20.0f * scale;
            Actor_MoveWithoutGravity(&this->actor);
        } else {
            height = 0.0f;
            Actor_MoveWithGravity(&this->actor);
        }
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 12.0f * scale, 25.0f * scale, 50.0f * scale, 7);
    } else {
        height = 0.0f;
    }

    this->collider.elements[0].dim.worldSphere.center.x = this->actor.world.pos.x;
    this->collider.elements[0].dim.worldSphere.center.y = this->actor.world.pos.y + height;
    this->collider.elements[0].dim.worldSphere.center.z = this->actor.world.pos.z;

    if (this->actionFunc == EnCrow_DiveAttack) {
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
    if (this->collider.base.acFlags & AC_ON) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
    if (this->actionFunc != EnCrow_Respawn) {
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }

    Actor_SetFocus(&this->actor, height);

    if ((this->actor.colChkInfo.health != 0) && (Animation_OnFrame(&this->skelAnime, 3.0f))) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_KAICHO_FLUTTER);
    }
    if (this->effectAlpha > 0.0f) {
        if (this->deathMode != 10) {
            Math_StepToF(&this->effectAlpha, 0.0f, 0.05f);
            this->steamScale = (this->effectAlpha + 1.0f) * 0.25f;
            if (this->steamScale > 0.5f) {
                this->steamScale = 0.5f;
            } else {
                this->steamScale = this->steamScale;
            }
        } else if (Math_StepToF(&this->effectScale, 0.5f, 0.0125f) == 0) {
            func_800B9010(&this->actor, NA_SE_EV_ICE_FREEZE - SFX_FLAG);
        }
    }
}

s32 EnCrow_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                            Actor* thisx) {
    EnCrow* this = (EnCrow*)thisx;

    if (this->actor.colChkInfo.health != 0) {
        if (limbIndex == OBJECT_CROW_LIMB_UPPER_TAIL) {
            rot->y += (s16)(0xC00 * sin_rad(this->skelAnime.curFrame * (M_PI / 4)));
        } else if (limbIndex == OBJECT_CROW_LIMB_TAIL) {
            rot->y += (s16)(0x1400 * sin_rad((this->skelAnime.curFrame + 2.5f) * (M_PI / 4)));
        }
    }
    return false;
}

void EnCrow_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnCrow* this = (EnCrow*)thisx;

    if (limbIndex == OBJECT_CROW_LIMB_BODY) {
        Matrix_GetStateTranslationAndScaledX(2500.0f, this->bodyPartsPos);
        return;
    }
    if ((limbIndex == OBJECT_CROW_LIMB_RIGHT_WING_TIP) || (limbIndex == OBJECT_CROW_LIMB_LEFT_WING_TIP) ||
        (limbIndex == OBJECT_CROW_LIMB_TAIL)) {
        Matrix_GetStateTranslation(&this->bodyPartsPos[(limbIndex >> 1) - 1]);
    }
}

void EnCrow_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnCrow* this = (EnCrow*)thisx;

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnCrow_OverrideLimbDraw, EnCrow_PostLimbDraw, &this->actor);
    Actor_DrawDamageEffects(globalCtx, &this->actor, this->bodyPartsPos, ARRAY_COUNT(this->bodyPartsPos),
                            this->actor.scale.x * 100.0f * this->steamScale, this->effectScale, this->effectAlpha,
                            this->deathMode);
}
