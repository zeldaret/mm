/*
 * File: z_en_firefly.c
 * Overlay: ovl_En_Firefly
 * Description: Keese (Normal, Fire, Ice)
 */

#include "z_en_firefly.h"
#include "overlays/actors/ovl_Obj_Syokudai/z_obj_syokudai.h"
#include "objects/object_firefly/object_firefly.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_1000 | ACTOR_FLAG_4000)

#define THIS ((EnFirefly*)thisx)

void EnFirefly_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFirefly_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFirefly_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFirefly_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnFirefly_FlyIdle(EnFirefly* this, GlobalContext* globalCtx);
void EnFirefly_Fall(EnFirefly* this, GlobalContext* globalCtx);
void EnFirefly_SetupDie(EnFirefly* this);
void EnFirefly_Die(EnFirefly* this, GlobalContext* globalCtx);
void EnFirefly_SetupDiveAttack(EnFirefly* this);
void EnFirefly_DiveAttack(EnFirefly* this, GlobalContext* globalCtx);
void EnFirefly_Rebound(EnFirefly* this, GlobalContext* globalCtx);
void EnFirefly_SetupFlyAway(EnFirefly* this);
void EnFirefly_FlyAway(EnFirefly* this, GlobalContext* globalCtx);
void EnFirefly_Stunned(EnFirefly* this, GlobalContext* globalCtx);
void EnFirefly_SetupPerch(EnFirefly* this);
void EnFirefly_Perch(EnFirefly* this, GlobalContext* globalCtx);
void EnFirefly_SetupDisturbDiveAttack(EnFirefly* this);
void EnFirefly_DisturbDiveAttack(EnFirefly* this, GlobalContext* globalCtx);

typedef enum {
    /* 0 */ KEESE_FIRE,
    /* 3 */ KEESE_NORMAL = 3,
    /* 4 */ KEESE_ICE
} KeeseCurrentType;

typedef enum {
    /* 0 */ KEESE_AURA_NONE,
    /* 1 */ KEESE_AURA_FIRE,
    /* 2 */ KEESE_AURA_ICE
} KeeseAuraType;

const ActorInit En_Firefly_InitVars = {
    ACTOR_EN_FIREFLY,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_FIREFLY,
    sizeof(EnFirefly),
    (ActorFunc)EnFirefly_Init,
    (ActorFunc)EnFirefly_Destroy,
    (ActorFunc)EnFirefly_Update,
    (ActorFunc)EnFirefly_Draw,
};

static ColliderSphereInit sSphereInit = {
    {
        COLTYPE_HIT3,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_SPHERE,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x01, 0x08 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_HARD,
        BUMP_ON,
        OCELEM_ON,
    },
    { 1, { { 0, 1000, 0 }, 15 }, 100 },
};

static CollisionCheckInfoInit sColChkInfoInit = { 1, 10, 10, 10 };

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
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

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 5, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -500, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, 2, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 4000, ICHAIN_STOP),
};

void EnFirefly_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnFirefly* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 25.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &object_firefly_Skel_0018B8, &object_firefly_Anim_00017C,
                   this->jointTable, this->morphTable, 28);
    Collider_InitAndSetSphere(globalCtx, &this->collider, &this->actor, &sSphereInit);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);

    if (this->actor.params & KEESE_INVISIBLE) {
        this->actor.flags |= ACTOR_FLAG_80;
        this->actor.params = KEESE_GET_MAIN_TYPE(thisx);
        this->isInvisible = true;
    }

    if (this->actor.params == KEESE_FIRE_FLY) {
        this->auraType = KEESE_AURA_FIRE;
        this->timer = Rand_S16Offset(20, 60);
        this->actor.shape.rot.x = 0x1554;
        this->actor.hintId = 0x11; // Fire Keese
        this->maxAltitude = this->actor.home.pos.y;
        this->actionFunc = EnFirefly_FlyIdle;
    } else if (this->actor.params == KEESE_ICE_FLY) {
        this->auraType = KEESE_AURA_ICE;
        this->collider.info.toucher.effect = 2; // Freeze
        this->actor.hintId = 0x56;              // Ice Keese
        this->maxAltitude = this->actor.home.pos.y + 100.0f;
        this->actionFunc = EnFirefly_FlyIdle;
    } else {
        this->auraType = KEESE_AURA_NONE;
        this->collider.info.toucher.effect = 0; // Nothing
        this->actor.hintId = 0x12;              // Keese
        this->maxAltitude = this->actor.home.pos.y + 100.0f;
        this->actionFunc = EnFirefly_Perch;
    }

    this->currentType = this->actor.params;
    this->collider.dim.worldSphere.radius = sSphereInit.dim.modelSphere.radius;
}

void EnFirefly_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnFirefly* this = THIS;

    Collider_DestroySphere(globalCtx, &this->collider);
}

void EnFirefly_SpawnIceEffects(EnFirefly* this, GlobalContext* globalCtx) {
    if (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
        this->drawDmgEffAlpha = 0.0f;
        Actor_SpawnIceEffects(globalCtx, &this->actor, &this->limbPos[0], 3, 2, 0.2f, 0.2f);
    }
}

void EnFirefly_Extinguish(EnFirefly* this) {
    this->currentType = KEESE_NORMAL;
    this->collider.info.toucher.effect = 0; // Nothing
    this->auraType = KEESE_AURA_NONE;
    this->actor.hintId = 0x12; // Keese
}

void EnFirefly_Ignite(EnFirefly* this) {
    if (this->actor.params == KEESE_FIRE_FLY) {
        this->currentType = KEESE_FIRE;
        this->collider.info.toucher.effect = 1; // Fire
        this->auraType = KEESE_AURA_FIRE;
        this->actor.hintId = 0x11; // Fire Keese
    }
}

s32 EnFirefly_ReturnToPerch(EnFirefly* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    f32 distFromHome;

    if (this->actor.params != KEESE_NORMAL_PERCH) {
        return false;
    }

    if (Actor_XZDistanceToPoint(&player->actor, &this->actor.home.pos) > 300.0f) {
        distFromHome = Actor_DistanceToPoint(&this->actor, &this->actor.home.pos);

        if (distFromHome < 5.0f) {
            EnFirefly_SetupPerch(this);
        } else {
            if (distFromHome * 0.05f < 1.0f) {
                this->actor.speedXZ *= distFromHome * 0.05f;
            }

            Math_ScaledStepToS(&this->actor.shape.rot.y, Actor_YawToPoint(&this->actor, &this->actor.home.pos), 0x300);
            Math_ScaledStepToS(&this->actor.shape.rot.x,
                               Actor_PitchToPoint(&this->actor, &this->actor.home.pos) + 0x1554, 0x100);
        }

        return true;
    }

    return false;
}

s32 EnFirefly_SeekTorch(EnFirefly* this, GlobalContext* globalCtx) {
    ObjSyokudai* findTorch = (ObjSyokudai*)globalCtx->actorCtx.actorLists[ACTORCAT_PROP].first;
    ObjSyokudai* closestTorch = NULL;
    f32 currentMinDist = 35000.0f;
    f32 currentDist;
    Vec3f flamePos;

    if ((this->actor.params != KEESE_FIRE_FLY) || (this->currentType != KEESE_NORMAL)) {
        return false;
    }

    while (findTorch != NULL) {
        if ((findTorch->actor.id == ACTOR_OBJ_SYOKUDAI) && (findTorch->snuffTimer != OBJ_SYOKUDAI_SNUFF_OUT)) {
            currentDist = Actor_DistanceBetweenActors(&this->actor, &findTorch->actor);
            if (currentDist < currentMinDist) {
                currentMinDist = currentDist;
                closestTorch = findTorch;
            }
        }
        findTorch = (ObjSyokudai*)findTorch->actor.next;
    }

    if (closestTorch != NULL) {
        flamePos.x = closestTorch->actor.world.pos.x;
        flamePos.y = closestTorch->actor.world.pos.y + 52.0f + 30.0f;
        flamePos.z = closestTorch->actor.world.pos.z;

        if (Actor_DistanceToPoint(&this->actor, &flamePos) < 15.0f) {
            EnFirefly_Ignite(this);
        } else {
            Math_ScaledStepToS(&this->actor.shape.rot.y, Actor_YawBetweenActors(&this->actor, &closestTorch->actor),
                               0x300);
            Math_ScaledStepToS(&this->actor.shape.rot.x, Actor_PitchToPoint(&this->actor, &flamePos) + 0x1554, 0x100);
        }

        return true;
    }

    return false;
}

void EnFirefly_SetupFlyIdle(EnFirefly* this) {
    this->timer = Rand_S16Offset(70, 100);
    this->actor.speedXZ = (Rand_ZeroOne() * 1.5f) + 1.5f;
    Math_ScaledStepToS(&this->actor.shape.rot.y, Actor_YawToPoint(&this->actor, &this->actor.home.pos), 0x300);
    this->targetPitch = ((this->maxAltitude < this->actor.world.pos.y) ? 0xC00 : -0xC00) + 0x1554;
    this->skelAnime.playSpeed = 1.0f;
    this->actionFunc = EnFirefly_FlyIdle;
}

void EnFirefly_FlyIdle(EnFirefly* this, GlobalContext* globalCtx) {
    s32 isSkelAnimeUpdated;
    f32 rand;

    SkelAnime_Update(&this->skelAnime);
    if (this->timer != 0) {
        this->timer--;
    }

    isSkelAnimeUpdated = Animation_OnFrame(&this->skelAnime, 0.0f);
    this->actor.speedXZ = (Rand_ZeroOne() * 1.5f) + 1.5f;

    if (!EnFirefly_ReturnToPerch(this, globalCtx) && !EnFirefly_SeekTorch(this, globalCtx)) {
        if (isSkelAnimeUpdated) {
            rand = Rand_ZeroOne();

            if (rand < 0.5f) {
                Math_ScaledStepToS(&this->actor.shape.rot.y, Actor_YawToPoint(&this->actor, &this->actor.home.pos),
                                   0x300);
            } else if (rand < 0.8f) {
                this->actor.shape.rot.y += (s16)randPlusMinusPoint5Scaled(1536.0f);
            }

            // Climb if too close to ground
            if (this->actor.world.pos.y < this->actor.floorHeight + 20.0f) {
                this->targetPitch = 0x954;
                // Descend if above maxAltitude
            } else if (this->maxAltitude < this->actor.world.pos.y) {
                this->targetPitch = 0x2154;
                // Otherwise ascend or descend at random, biased towards ascending
            } else if (Rand_ZeroOne() > 0.35f) {
                this->targetPitch = 0x954;
            } else {
                this->targetPitch = 0x2154;
            }
        } else {
            if (this->actor.bgCheckFlags & 1) {
                this->targetPitch = 0x954;
            } else if ((this->actor.bgCheckFlags & 0x10) || (this->maxAltitude < this->actor.world.pos.y)) {
                this->targetPitch = 0x2154;
            }
        }

        Math_ScaledStepToS(&this->actor.shape.rot.x, this->targetPitch, 0x100);
    }

    if (this->actor.bgCheckFlags & 8) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.wallYaw, 2, 0xC00, 0x300);
    }

    if ((this->timer == 0) && (this->actor.xzDistToPlayer < 200.0f) &&
        (Player_GetMask(globalCtx) != PLAYER_MASK_STONE)) {
        EnFirefly_SetupDiveAttack(this);
    }
}

void EnFirefly_SetupFall(EnFirefly* this, GlobalContext* globalCtx) {
    this->timer = 40;
    this->actor.velocity.y = 0.0f;
    Animation_Change(&this->skelAnime, &object_firefly_Anim_00017C, 0.0f, 6.0f, 6.0f, 2, 0.0f);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FFLY_DEAD);
    this->actor.flags |= ACTOR_FLAG_10;

    if (this->isInvisible) {
        Actor_SetColorFilter(&this->actor, 0x4000, 255, 0x2000, 40);
    } else {
        Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 40);
    }

    if (this->actor.colChkInfo.damageEffect == 3) {
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX;
        this->drawDmgEffAlpha = 1.0f;
        this->drawDmgEffScale = 0.55f;
        this->drawDmgEffFrozenSteamScale = 0.82500005f;
    } else if (this->actor.colChkInfo.damageEffect == 4) {
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_LIGHT_ORBS;
        this->drawDmgEffAlpha = 4.0f;
        this->drawDmgEffScale = 0.55f;
        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, this->collider.info.bumper.hitPos.x,
                    this->collider.info.bumper.hitPos.y, this->collider.info.bumper.hitPos.z, 0, 0, 0,
                    CLEAR_TAG_SMALL_LIGHT_RAYS);
    } else if (this->actor.colChkInfo.damageEffect == 2) {
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
        this->drawDmgEffAlpha = 4.0f;
        this->drawDmgEffScale = 0.55f;
    }

    if (this->drawDmgEffAlpha > 0.0f) {
        this->auraType = KEESE_AURA_NONE;
    }

    if (this->actor.flags & ACTOR_FLAG_8000) {
        this->actor.speedXZ = 0.0f;
    }

    this->actionFunc = EnFirefly_Fall;
}

// Fall to the ground after being hit
void EnFirefly_Fall(EnFirefly* this, GlobalContext* globalCtx) {
    this->actor.colorFilterTimer = 40;
    Math_StepToF(&this->actor.speedXZ, 0.0f, 0.5f);

    if (!(this->actor.flags & ACTOR_FLAG_8000)) {
        if (this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
            Math_ScaledStepToS(&this->actor.shape.rot.x, 0x6800, 0x200);
            this->actor.shape.rot.y -= 0x300;
        }

        if ((this->actor.bgCheckFlags & 1) || (this->actor.floorHeight == BGCHECK_Y_MIN)) {
            EnFirefly_SpawnIceEffects(this, globalCtx);
            EnFirefly_SetupDie(this);
        }
    }
}

void EnFirefly_SetupDie(EnFirefly* this) {
    this->timer = 15;
    this->actor.speedXZ = 0.0f;
    this->actionFunc = EnFirefly_Die;
}

// Hit the ground or burn up, spawn drops
void EnFirefly_Die(EnFirefly* this, GlobalContext* globalCtx) {
    if (this->timer != 0) {
        this->timer--;
    }

    Math_StepToF(&this->actor.scale.x, 0.0f, 0.00034f);
    this->actor.scale.y = this->actor.scale.z = this->actor.scale.x;

    if (this->timer == 0) {
        Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.world.pos, 0xA0);
        Actor_MarkForDeath(&this->actor);
    }
}

void EnFirefly_SetupDiveAttack(EnFirefly* this) {
    this->timer = Rand_S16Offset(70, 100);
    this->skelAnime.playSpeed = 1.0f;
    this->targetPitch = ((this->actor.playerHeightRel > 0.0f) ? -0xC00 : 0xC00) + 0x1554;
    this->actionFunc = EnFirefly_DiveAttack;
}

void EnFirefly_DiveAttack(EnFirefly* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f preyPos;

    SkelAnime_Update(&this->skelAnime);

    if (this->timer != 0) {
        this->timer--;
    }

    Math_StepToF(&this->actor.speedXZ, 4.0f, 0.5f);

    if (this->actor.bgCheckFlags & 8) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.wallYaw, 2, 0xC00, 0x300);
        Math_ScaledStepToS(&this->actor.shape.rot.x, this->targetPitch, 0x100);
    } else if (Actor_IsFacingPlayer(&this->actor, 0x2800)) {
        if (Animation_OnFrame(&this->skelAnime, 4.0f)) {
            this->skelAnime.playSpeed = 0.0f;
            this->skelAnime.curFrame = 4.0f;
        }

        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 0xC00, 0x300);
        preyPos.x = player->actor.world.pos.x;
        preyPos.y = player->actor.world.pos.y + 20.0f;
        preyPos.z = player->actor.world.pos.z;
        Math_SmoothStepToS(&this->actor.shape.rot.x, Actor_PitchToPoint(&this->actor, &preyPos) + 0x1554, 2, 0x400,
                           0x100);
    } else {
        this->skelAnime.playSpeed = 1.5f;
        if (this->actor.xzDistToPlayer > 80.0f) {
            Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 0xC00, 0x300);
        }

        if (this->actor.bgCheckFlags & 1) {
            this->targetPitch = 0x954;
        }

        if ((this->actor.bgCheckFlags & 0x10) || (this->maxAltitude < this->actor.world.pos.y)) {
            this->targetPitch = 0x2154;
        } else {
            this->targetPitch = 0x954;
        }

        Math_ScaledStepToS(&this->actor.shape.rot.x, this->targetPitch, 0x100);
    }

    if ((this->timer == 0) || (Player_GetMask(globalCtx) == PLAYER_MASK_STONE) || (player->stateFlags2 & 0x80) ||
        (player->actor.freezeTimer > 0)) {
        EnFirefly_SetupFlyAway(this);
    }
}

void EnFirefly_SetupRebound(EnFirefly* this) {
    this->actor.world.rot.x = 0x7000;
    this->timer = 18;
    this->skelAnime.playSpeed = 1.0f;
    this->actor.speedXZ = 2.5f;
    this->actionFunc = EnFirefly_Rebound;
}

// Knockback after hitting player
void EnFirefly_Rebound(EnFirefly* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    Math_ScaledStepToS(&this->actor.shape.rot.x, 0, 0x100);
    Math_StepToF(&this->actor.velocity.y, 0.0f, 0.4f);
    if (Math_StepToF(&this->actor.speedXZ, 0.0f, 0.15f)) {
        if (this->timer != 0) {
            this->timer--;
        }

        if (this->timer == 0) {
            EnFirefly_SetupFlyAway(this);
        }
    }
}

void EnFirefly_SetupFlyAway(EnFirefly* this) {
    this->timer = 150;
    this->targetPitch = 0x954;
    this->actionFunc = EnFirefly_FlyAway;
    this->skelAnime.playSpeed = 1.0f;
}

void EnFirefly_FlyAway(EnFirefly* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);

    if (this->timer != 0) {
        this->timer--;
    }

    if (((fabsf(this->actor.world.pos.y - this->maxAltitude) < 10.0f) &&
         (Math_Vec3f_DistXZ(&this->actor.world.pos, &this->actor.home.pos) < 20.0f)) ||
        (this->timer == 0)) {
        EnFirefly_SetupFlyIdle(this);
        return;
    }

    Math_StepToF(&this->actor.speedXZ, 3.0f, 0.3f);

    if (this->actor.bgCheckFlags & 1) {
        this->targetPitch = 0x954;
    } else if ((this->actor.bgCheckFlags & 0x10) || (this->maxAltitude < this->actor.world.pos.y)) {
        this->targetPitch = 0x2154;
    } else {
        this->targetPitch = 0x954;
    }

    if (this->actor.bgCheckFlags & 8) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.wallYaw, 2, 0xC00, 0x300);
    } else {
        Math_ScaledStepToS(&this->actor.shape.rot.y, Actor_YawToPoint(&this->actor, &this->actor.home.pos), 0x300);
    }

    Math_ScaledStepToS(&this->actor.shape.rot.x, this->targetPitch, 0x100);
}

void EnFirefly_SetupStunned(EnFirefly* this) {
    if (this->isInvisible) {
        Actor_SetColorFilter(&this->actor, 0, 255, 0x2000, this->timer);
    } else {
        Actor_SetColorFilter(&this->actor, 0, 255, 0, this->timer);
    }

    if (this->actionFunc != EnFirefly_Stunned) {
        this->actor.velocity.y = 0.0f;
        this->actor.speedXZ = 0.0f;
    }

    this->auraType = KEESE_AURA_NONE;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
    this->actionFunc = EnFirefly_Stunned;
}

void EnFirefly_Stunned(EnFirefly* this, GlobalContext* globalCtx) {
    Math_ScaledStepToS(&this->actor.shape.rot.x, 0x1554, 0x100);
    if ((this->actor.bgCheckFlags & 1) || (this->actor.floorHeight == BGCHECK_Y_MIN)) {
        if (this->timer != 0) {
            this->timer--;
        }

        if (this->timer == 0) {
            if (this->currentType == KEESE_FIRE) {
                this->auraType = KEESE_AURA_FIRE;
            } else if (this->currentType == KEESE_ICE) {
                this->auraType = KEESE_AURA_ICE;
            }

            EnFirefly_SetupFlyIdle(this);
        }
    } else {
        this->actor.colorFilterTimer = 40;

        if (this->drawDmgEffAlpha > 0.0f) {
            this->drawDmgEffAlpha = 2.0f;
        }
    }
}

void EnFirefly_SetupPerch(EnFirefly* this) {
    this->timer = 1;
    this->actionFunc = EnFirefly_Perch;
    this->actor.speedXZ = 0.0f;
}

// When perching, sit on collision and flap at random intervals
void EnFirefly_Perch(EnFirefly* this, GlobalContext* globalCtx) {
    Math_ScaledStepToS(&this->actor.shape.rot.x, 0, 0x100);
    if (this->timer != 0) {
        SkelAnime_Update(&this->skelAnime);
        if (Animation_OnFrame(&this->skelAnime, 6.0f)) {
            this->timer--;
        }
    } else if (Rand_ZeroOne() < 0.02f) {
        this->timer = 1;
    }

    if (this->actor.xzDistToPlayer < 120.0f) {
        EnFirefly_SetupDisturbDiveAttack(this);
    }
}

void EnFirefly_SetupDisturbDiveAttack(EnFirefly* this) {
    this->skelAnime.playSpeed = 3.0f;
    this->actor.shape.rot.x = 0x1554;
    this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    this->timer = 50;
    this->actor.speedXZ = 3.0f;
    this->actionFunc = EnFirefly_DisturbDiveAttack;
}

void EnFirefly_DisturbDiveAttack(EnFirefly* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f preyPos;

    SkelAnime_Update(&this->skelAnime);

    if (this->timer != 0) {
        this->timer--;
    }
    if (this->timer < 40) {
        Math_ScaledStepToS(&this->actor.shape.rot.x, -0xAAC, 0x100);
    } else {
        preyPos.x = player->actor.world.pos.x;
        preyPos.y = player->actor.world.pos.y + 20.0f;
        preyPos.z = player->actor.world.pos.z;
        Math_ScaledStepToS(&this->actor.shape.rot.x, Actor_PitchToPoint(&this->actor, &preyPos) + 0x1554, 0x100);
        Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x300);
    }

    if (this->timer == 0) {
        EnFirefly_SetupFlyIdle(this);
    }
}

void EnFirefly_UpdateDamage(EnFirefly* this, GlobalContext* globalCtx) {
    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        Actor_SetDropFlag(&this->actor, &this->collider.info);

        if (this->actor.colChkInfo.damageEffect == 1) {
            this->timer = 40;
            EnFirefly_SetupStunned(this);
        } else if (this->actor.colChkInfo.damageEffect == 5) {
            this->timer = 40;
            this->drawDmgEffType = ACTOR_DRAW_DMGEFF_ELECTRIC_SPARKS_MEDIUM;
            this->drawDmgEffAlpha = 2.0f;
            this->drawDmgEffScale = 0.55f;
            EnFirefly_SetupStunned(this);
        } else {
            Enemy_StartFinishingBlow(globalCtx, &this->actor);
            this->actor.colChkInfo.health = 0;
            this->actor.flags &= ~ACTOR_FLAG_1;

            // Negate effects of fire on Fire Keese and Ice on Ice Keese
            if (((this->currentType == KEESE_FIRE) && (this->actor.colChkInfo.damageEffect == 2)) ||
                ((this->currentType == KEESE_ICE) && (this->actor.colChkInfo.damageEffect == 3))) {
                this->actor.colChkInfo.damageEffect = 0;
            }

            EnFirefly_SetupFall(this, globalCtx);
        }
    }
}

void EnFirefly_Update(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnFirefly* this = THIS;

    if (this->collider.base.atFlags & AT_HIT) {
        this->collider.base.atFlags &= ~AT_HIT;
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FFLY_ATTACK);

        if (this->currentType != KEESE_NORMAL) {
            EnFirefly_Extinguish(this);
        }

        if (this->actionFunc != EnFirefly_DisturbDiveAttack) {
            EnFirefly_SetupRebound(this);
        }
    }

    EnFirefly_UpdateDamage(this, globalCtx);
    this->actionFunc(this, globalCtx);

    if (!(this->actor.flags & ACTOR_FLAG_8000)) {
        if ((this->actor.colChkInfo.health == 0) || (this->actionFunc == EnFirefly_Stunned)) {
            Actor_MoveWithGravity(&this->actor);
        } else {
            if (this->actionFunc != EnFirefly_Rebound) {
                this->actor.world.rot.x = 0x1554 - this->actor.shape.rot.x;
            }

            Actor_MoveWithoutGravity(&this->actor);
        }
    }

    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 10.0f, 10.0f, 15.0f, 7);
    this->collider.dim.worldSphere.center.x = this->actor.world.pos.x;
    this->collider.dim.worldSphere.center.y = (s32)this->actor.world.pos.y + 10;
    this->collider.dim.worldSphere.center.z = this->actor.world.pos.z;

    if ((this->actionFunc == EnFirefly_DiveAttack) || (this->actionFunc == EnFirefly_DisturbDiveAttack)) {
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }

    if (this->actor.colChkInfo.health != 0) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        this->actor.world.rot.y = this->actor.shape.rot.y;

        if (Animation_OnFrame(&this->skelAnime, 5.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FFLY_FLY);
        }
    }

    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);

    if (this->drawDmgEffAlpha > 0.0f) {
        if (this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
            Math_StepToF(&this->drawDmgEffAlpha, 0.0f, 0.05f);
            this->drawDmgEffScale = (this->drawDmgEffAlpha + 1.0f) * 0.275f;
            this->drawDmgEffScale = CLAMP_MAX(this->drawDmgEffScale, 0.55f);
        } else if (!Math_StepToF(&this->drawDmgEffFrozenSteamScale, 0.55f, 0.01375f)) {
            func_800B9010(&this->actor, NA_SE_EV_ICE_FREEZE - SFX_FLAG);
        }
    }

    this->actor.focus.pos.x =
        10.0f * Math_SinS(this->actor.shape.rot.x) * Math_SinS(this->actor.shape.rot.y) + this->actor.world.pos.x;
    this->actor.focus.pos.y = 10.0f * Math_CosS(this->actor.shape.rot.x) + this->actor.world.pos.y;
    this->actor.focus.pos.z =
        10.0f * Math_SinS(this->actor.shape.rot.x) * Math_CosS(this->actor.shape.rot.y) + this->actor.world.pos.z;
}

s32 EnFirefly_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                               Actor* thisx, Gfx** gfx) {
    EnFirefly* this = THIS;

    if (this->isInvisible && (globalCtx->actorCtx.unk4 != 0x64)) {
        *dList = NULL;
    } else if (limbIndex == 1) {
        pos->y += 2300.0f;
    }
    return false;
}

void EnFirefly_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    static Color_RGBA8 fireAuraPrimColor = { 255, 255, 100, 255 };
    static Color_RGBA8 fireAuraEnvColor = { 255, 50, 0, 0 };
    static Color_RGBA8 iceAuraPrimColor = { 100, 200, 255, 255 };
    static Color_RGBA8 iceAuraEnvColor = { 0, 0, 255, 0 };
    static Vec3f auraVelocity = { 0.0f, 0.5f, 0.0f };
    static Vec3f auraAccel = { 0.0f, 0.5f, 0.0f };
    Vec3f auraPos;
    Color_RGBA8* auraPrimColor;
    Color_RGBA8* auraEnvColor;
    s16 auraScaleStep;
    s16 auraLife;
    s32 pad;
    EnFirefly* this = THIS;

    if ((this->currentType != KEESE_FIRE) && (limbIndex == 27)) {
        gSPDisplayList((*gfx)++, object_firefly_DL_001678);
    } else if ((this->unk_2F4 != globalCtx->gameplayFrames) &&
               ((this->auraType == KEESE_AURA_FIRE) || (this->auraType == KEESE_AURA_ICE)) &&
               ((limbIndex == 15) || (limbIndex == 21))) {
        if (this->actionFunc != EnFirefly_Die) {
            Matrix_GetStateTranslation(&auraPos);
            auraPos.x += Rand_ZeroFloat(5.0f);
            auraPos.y += Rand_ZeroFloat(5.0f);
            auraPos.z += Rand_ZeroFloat(5.0f);
            auraScaleStep = -40;
            auraLife = 3;
        } else {
            if (limbIndex == 15) {
                auraPos.x = Math_SinS(9100 * this->timer) * this->timer + this->actor.world.pos.x;
                auraPos.z = Math_CosS(9100 * this->timer) * this->timer + this->actor.world.pos.z;
            } else {
                auraPos.x = this->actor.world.pos.x - Math_SinS(9100 * this->timer) * this->timer;
                auraPos.z = this->actor.world.pos.z - Math_CosS(9100 * this->timer) * this->timer;
            }

            auraPos.y = this->actor.world.pos.y + (15 - this->timer) * 1.5f;
            auraScaleStep = -5;
            auraLife = 10;
        }

        if (this->auraType == KEESE_AURA_FIRE) {
            auraPrimColor = &fireAuraPrimColor;
            auraEnvColor = &fireAuraEnvColor;
        } else {
            auraPrimColor = &iceAuraPrimColor;
            auraEnvColor = &iceAuraEnvColor;
        }

        func_800B0F80(globalCtx, &auraPos, &auraVelocity, &auraAccel, auraPrimColor, auraEnvColor, 250, auraScaleStep,
                      auraLife);
    }

    if (limbIndex == 15) {
        Matrix_GetStateTranslation(&this->limbPos[0]);
    } else if (limbIndex == 21) {
        Matrix_GetStateTranslation(&this->limbPos[1]);
    } else if (limbIndex == 10) {
        Matrix_GetStateTranslation(&this->limbPos[2]);
    }
}

void EnFirefly_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnFirefly* this = THIS;
    Gfx* gfx;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    if (this->isInvisible) {
        gfx = POLY_XLU_DISP;
    } else {
        gfx = POLY_OPA_DISP;
    }

    gSPDisplayList(gfx, &sSetupDL[6 * 25]);

    if (this->currentType == KEESE_FIRE) {
        gDPSetEnvColor(&gfx[1], 0, 0, 0, 0);
    } else {
        gDPSetEnvColor(&gfx[1], 0, 0, 0, 255);
    }

    gfx = SkelAnime_Draw(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, EnFirefly_OverrideLimbDraw,
                         EnFirefly_PostLimbDraw, &this->actor, &gfx[2]);
    if (this->isInvisible) {
        POLY_XLU_DISP = gfx;
    } else {
        POLY_OPA_DISP = gfx;
    }

    Actor_DrawDamageEffects(globalCtx, NULL, this->limbPos, ARRAY_COUNT(this->limbPos),
                            this->drawDmgEffScale * this->actor.scale.y * 200.0f, this->drawDmgEffFrozenSteamScale,
                            this->drawDmgEffAlpha, this->drawDmgEffType);
    this->unk_2F4 = globalCtx->gameplayFrames;

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
