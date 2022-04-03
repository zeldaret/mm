/*
 * File: z_en_bbfall.c
 * Overlay: ovl_En_Bbfall
 * Description: Red Bubble
 */

#include "z_en_bbfall.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_200)

#define THIS ((EnBbfall*)thisx)

void EnBbfall_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBbfall_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBbfall_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBbfall_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_808BF5E0(EnBbfall* this);
void func_808BF734(EnBbfall* this, GlobalContext* globalCtx);
void func_808BF7A0(EnBbfall* this);
void func_808BF830(EnBbfall* this, GlobalContext* globalCtx);
void func_808BF894(EnBbfall* this);
void func_808BF8DC(EnBbfall* this, GlobalContext* globalCtx);
void func_808BFA18(EnBbfall* this);
void func_808BFA3C(EnBbfall* this, GlobalContext* globalCtx);
void EnBbfall_Down(EnBbfall* this, GlobalContext* globalCtx);
void EnBbfall_Dead(EnBbfall* this, GlobalContext* globalCtx);
void EnBbfall_Damage(EnBbfall* this, GlobalContext* globalCtx);
void EnBbfall_Frozen(EnBbfall* this, GlobalContext* globalCtx);

typedef enum {
    /* -1 */ BBFALL_BODY_PART_DRAW_STATUS_BROKEN = -1,
    /*  0 */ BBFALL_BODY_PART_DRAW_STATUS_ALIVE,
    /*  1 */ BBFALL_BODY_PART_DRAW_STATUS_DEAD,
} EnBbfallBodyPartDrawStatus;

const ActorInit En_Bbfall_InitVars = {
    ACTOR_EN_BBFALL,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_BB,
    sizeof(EnBbfall),
    (ActorFunc)EnBbfall_Init,
    (ActorFunc)EnBbfall_Destroy,
    (ActorFunc)EnBbfall_Update,
    (ActorFunc)EnBbfall_Draw,
};

static ColliderJntSphElementInit sJntSphElementsInit[3] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x01, 0x08 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_HARD,
            BUMP_ON | BUMP_HOOKABLE,
            OCELEM_ON,
        },
        { 0, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x01, 0x08 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_HARD,
            BUMP_NONE,
            OCELEM_NONE,
        },
        { 0, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x01, 0x08 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_HARD,
            BUMP_NONE,
            OCELEM_NONE,
        },
        { 0, { { 0, 0, 0 }, 20 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_HIT3,
        AT_NONE | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    ARRAY_COUNT(sJntSphElementsInit),
    sJntSphElementsInit,
};

typedef enum {
    /* 0x0 */ EN_BBFALL_DMGEFF_NONE,
    /* 0x1 */ EN_BBFALL_DMGEFF_STUN,
    /* 0x3 */ EN_BBFALL_DMGEFF_ICE_ARROW = 0x3,
    /* 0x4 */ EN_BBFALL_DMGEFF_LIGHT_ARROW,
    /* 0x5 */ EN_BBFALL_DMGEFF_ZORA_MAGIC,
    /* 0xE */ EN_BBFALL_DMGEFF_HOOKSHOT = 0xE,
} EnBbfallDamageEffect;

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, EN_BBFALL_DMGEFF_STUN),
    /* Deku Stick     */ DMG_ENTRY(1, EN_BBFALL_DMGEFF_NONE),
    /* Horse trample  */ DMG_ENTRY(0, EN_BBFALL_DMGEFF_NONE),
    /* Explosives     */ DMG_ENTRY(1, EN_BBFALL_DMGEFF_NONE),
    /* Zora boomerang */ DMG_ENTRY(1, EN_BBFALL_DMGEFF_NONE),
    /* Normal arrow   */ DMG_ENTRY(1, EN_BBFALL_DMGEFF_NONE),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, EN_BBFALL_DMGEFF_NONE),
    /* Hookshot       */ DMG_ENTRY(0, EN_BBFALL_DMGEFF_HOOKSHOT),
    /* Goron punch    */ DMG_ENTRY(1, EN_BBFALL_DMGEFF_NONE),
    /* Sword          */ DMG_ENTRY(1, EN_BBFALL_DMGEFF_NONE),
    /* Goron pound    */ DMG_ENTRY(1, EN_BBFALL_DMGEFF_NONE),
    /* Fire arrow     */ DMG_ENTRY(1, EN_BBFALL_DMGEFF_NONE),
    /* Ice arrow      */ DMG_ENTRY(2, EN_BBFALL_DMGEFF_ICE_ARROW),
    /* Light arrow    */ DMG_ENTRY(2, EN_BBFALL_DMGEFF_LIGHT_ARROW),
    /* Goron spikes   */ DMG_ENTRY(1, EN_BBFALL_DMGEFF_NONE),
    /* Deku spin      */ DMG_ENTRY(1, EN_BBFALL_DMGEFF_NONE),
    /* Deku bubble    */ DMG_ENTRY(1, EN_BBFALL_DMGEFF_NONE),
    /* Deku launch    */ DMG_ENTRY(2, EN_BBFALL_DMGEFF_NONE),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, EN_BBFALL_DMGEFF_STUN),
    /* Zora barrier   */ DMG_ENTRY(0, EN_BBFALL_DMGEFF_ZORA_MAGIC),
    /* Normal shield  */ DMG_ENTRY(0, EN_BBFALL_DMGEFF_NONE),
    /* Light ray      */ DMG_ENTRY(0, EN_BBFALL_DMGEFF_NONE),
    /* Thrown object  */ DMG_ENTRY(1, EN_BBFALL_DMGEFF_NONE),
    /* Zora punch     */ DMG_ENTRY(1, EN_BBFALL_DMGEFF_NONE),
    /* Spin attack    */ DMG_ENTRY(1, EN_BBFALL_DMGEFF_NONE),
    /* Sword beam     */ DMG_ENTRY(0, EN_BBFALL_DMGEFF_NONE),
    /* Normal Roll    */ DMG_ENTRY(0, EN_BBFALL_DMGEFF_NONE),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, EN_BBFALL_DMGEFF_NONE),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, EN_BBFALL_DMGEFF_NONE),
    /* Unblockable    */ DMG_ENTRY(0, EN_BBFALL_DMGEFF_NONE),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, EN_BBFALL_DMGEFF_NONE),
    /* Powder Keg     */ DMG_ENTRY(1, EN_BBFALL_DMGEFF_NONE),
};

static CollisionCheckInfoInit sColChkInfoInit = { 2, 20, 40, 50 };

static InitChainEntry sInitChain[] = {
    ICHAIN_S8(hintId, 36, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 10, ICHAIN_STOP),
};

/**
 * This maps a given limb based on its limbIndex to its appropriate index
 * in the bodyPartsPos/Velocity arrays. An index of -1 indicates that the
 * limb is not part of the bodyParts arrays.
 */
static s8 sLimbIndexToBodyPartsIndex[] = {
    -1, -1, -1, -1, 0, -1, -1, -1, 1, -1, -1, -1, -1, 2, -1, 3,
};

/**
 * The last element of the bodyParts arrays is a duplicate of the cranium
 * limb, which is then offset by a certain amount. There is no display list
 * associated with this, so it is only used for effects.
 */
static Vec3f sDuplicateCraniumBodyPartOffset = { 1000.0f, -700.0f, 0.0f };

void EnBbfall_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnBbfall* this = THIS;
    s32 i;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    SkelAnime_Init(globalCtx, &this->skelAnime, &gBubbleSkel, &gBubbleFlyingAnim, this->jointTable, this->morphTable,
                   BUBBLE_LIMB_MAX);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    Collider_InitAndSetJntSph(globalCtx, &this->collider, &this->actor, &sJntSphInit, this->colliderElements);
    ActorShape_Init(&this->actor.shape, 1500.0f, ActorShadow_DrawCircle, 35.0f);
    this->timer = 0;
    func_808BF5E0(this);
    Actor_SetFocus(&this->actor, 0.0f);
    for (i = 0; i < 3; i++) {
        this->collider.elements[i].dim.worldSphere.radius = this->collider.elements[i].dim.modelSphere.radius;
    }
}

void EnBbfall_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnBbfall* this = THIS;

    Collider_DestroyJntSph(globalCtx, &this->collider);
}

void EnBbfall_Freeze(EnBbfall* this) {
    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX;
    this->drawDmgEffScale = 0.4f;
    this->drawDmgEffFrozenSteamScale = 0.6f;
    this->timer = 80;
    this->drawDmgEffAlpha = 1.0f;
    this->actor.flags &= ~ACTOR_FLAG_200;
    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 80);
}

void EnBbfall_Thaw(EnBbfall* this, GlobalContext* globalCtx) {
    if (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
        this->drawDmgEffAlpha = 0.0f;
        Actor_SpawnIceEffects(globalCtx, &this->actor, this->bodyPartsPos, ARRAY_COUNT(this->bodyPartsPos), 2, 0.2f,
                              0.15f);
        this->actor.flags |= ACTOR_FLAG_200;
    }
}

s32 func_808BF438(EnBbfall* this, GlobalContext* globalCtx) {
    if (!SurfaceType_IsWallDamage(&globalCtx->colCtx, this->actor.floorPoly, this->actor.floorBgId)) {
        u32 temp_v0 = func_800C99D4(&globalCtx->colCtx, this->actor.floorPoly, this->actor.floorBgId);

        if ((temp_v0 == 2) || (temp_v0 == 3) || (temp_v0 == 9)) {
            return 1;
        }
    }

    return 0;
}

void func_808BF4B4(EnBbfall* this) {
    if (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 5.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_BUBLE_MOUTH);
    }

    func_800B9010(&this->actor, NA_SE_EN_BUBLEFALL_FIRE - SFX_FLAG);
}

/**
 * Checks to see if the Bubble is touching a wall. If it is, and if the
 * Bubble is facing directly "into" the wall, then rotate it away from
 * the wall.
 */
void EnBbfall_CheckForWall(EnBbfall* this) {
    s16 yawDiff;

    if (this->actor.bgCheckFlags & 8) {
        yawDiff = this->actor.shape.rot.y - this->actor.wallYaw;

        if (ABS_ALT(yawDiff) > 0x4000) {
            this->actor.shape.rot.y = ((this->actor.wallYaw * 2) - this->actor.shape.rot.y) - 0x8000;
        }

        this->actor.bgCheckFlags &= ~8;
    }
}

void func_808BF578(EnBbfall* this) {
    this->collider.elements->info.toucher.effect = 1;
    this->collider.elements[1].info.toucherFlags |= 1;
    this->collider.elements[2].info.toucherFlags |= 1;
}

void func_808BF5AC(EnBbfall* this) {
    this->collider.elements[0].info.toucher.effect = 0;
    this->collider.elements[1].info.toucherFlags &= ~1;
    this->collider.elements[2].info.toucherFlags &= ~1;
}

void func_808BF5E0(EnBbfall* this) {
    s32 i;

    Animation_PlayLoop(&this->skelAnime, &gBubbleAttackAnim);
    this->collider.base.atFlags &= ~AT_ON;
    this->collider.base.acFlags &= ~AC_ON;
    this->collider.base.ocFlags1 &= ~OC1_ON;
    this->flameScaleY = 0.8f;
    this->flameScaleX = 1.0f;
    this->unk_24C = -1;
    this->actor.colChkInfo.health = sColChkInfoInit.health;
    this->actor.colorFilterTimer = 0;
    this->unk_24D = 0;
    this->actor.speedXZ = 0.0f;
    this->actor.gravity = 0.0f;
    this->actor.velocity.y = 0.0f;
    Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.home.pos);
    this->actor.world.pos.y -= 90.0f;
    for (i = 0; i < 6; i++) {
        Math_Vec3f_Copy(&this->unk_268[i], &this->actor.world.pos);
        this->unk_268[i].y -= 47.0f;
    }

    this->actor.bgCheckFlags &= ~1;
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->actionFunc = func_808BF734;
}

void func_808BF734(EnBbfall* this, GlobalContext* globalCtx) {
    if (this->timer != 0) {
        this->timer--;
    } else if ((Player_GetMask(globalCtx) != PLAYER_MASK_STONE) && (this->actor.xyzDistToPlayerSq <= SQ(250.0f))) {
        func_808BF7A0(this);
    }
}

void func_808BF7A0(EnBbfall* this) {
    this->actor.gravity = -1.0f;
    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    this->collider.base.atFlags |= AT_ON;
    this->collider.base.acFlags |= AC_ON;
    this->collider.base.ocFlags1 |= OC1_ON;
    this->actor.velocity.y = 17.0f;
    func_808BF578(this);
    this->actor.flags |= ACTOR_FLAG_1;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_BUBLEFALL_APPEAR);
    this->actionFunc = func_808BF830;
}

void func_808BF830(EnBbfall* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if (this->actor.home.pos.y < this->actor.world.pos.y) {
        func_808BF894(this);
    }

    func_808BF4B4(this);
}

void func_808BF894(EnBbfall* this) {
    this->unk_24C = 0xFF;
    this->unk_24D = 1;
    this->actor.bgCheckFlags &= ~1;
    this->actor.speedXZ = 5.0f;
    this->actor.gravity = -1.0f;
    this->actionFunc = func_808BF8DC;
}

void func_808BF8DC(EnBbfall* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    Math_StepToF(&this->flameScaleY, 0.8f, 0.1f);
    Math_StepToF(&this->flameScaleX, 1.0f, 0.1f);
    EnBbfall_CheckForWall(this);
    if (this->actor.bgCheckFlags & 1) {
        if (func_808BF438(this, globalCtx)) {
            func_808BFA18(this);
        } else {
            this->actor.velocity.y *= -1.2f;
            this->actor.velocity.y = CLAMP(this->actor.velocity.y, 8.0f, 12.0f);
            this->actor.shape.rot.y += (s16)randPlusMinusPoint5Scaled(73728.0f);
        }

        this->actor.bgCheckFlags &= ~1;
    }

    this->actor.world.rot.y = this->actor.shape.rot.y;
    func_808BF4B4(this);
}

void func_808BFA18(EnBbfall* this) {
    this->unk_24D = 0;
    this->collider.base.acFlags &= ~AC_ON;
    this->actionFunc = func_808BFA3C;
}

void func_808BFA3C(EnBbfall* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if (this->actor.world.pos.y < (this->actor.floorHeight - 90.0f)) {
        this->timer = 10;
        func_808BF5E0(this);
    } else {
        func_808BF4B4(this);
    }
}

void EnBbfall_SetupDown(EnBbfall* this) {
    Animation_PlayLoop(&this->skelAnime, &gBubbleFlyingAnim);
    this->collider.base.atFlags |= AT_ON;
    this->timer = 200;
    this->unk_24C = 0;
    this->collider.base.acFlags |= AC_ON;
    this->actor.speedXZ = 2.0f;
    this->flameScaleY = 0.0f;
    this->flameScaleX = 0.0f;
    this->actor.gravity = -2.0f;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_BUBLE_DOWN);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = EnBbfall_Down;
}

void EnBbfall_Down(EnBbfall* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    EnBbfall_CheckForWall(this);

    if (this->actor.bgCheckFlags & 1) {
        if (func_808BF438(this, globalCtx)) {
            func_808BFA18(this);
            return;
        }

        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_EYEGOLE_ATTACK);
        if (this->timer == 0) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_BUBLE_UP);
            func_808BF578(this);
            this->actor.velocity.y = 8.0f;
            func_808BF894(this);
            return;
        }

        if (this->actor.velocity.y < -14.0f) {
            this->actor.velocity.y *= -0.7f;
        } else {
            this->actor.velocity.y = 10.0f;
        }

        this->actor.bgCheckFlags &= ~1;
        Actor_SpawnFloorDustRing(globalCtx, &this->actor, &this->actor.world.pos, 7.0f, 2, 2.0f, 0, 0, 0);
        Math_ScaledStepToS(&this->actor.shape.rot.y, BINANG_ADD(this->actor.yawTowardsPlayer, 0x8000), 0xBB8);
    }

    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (Animation_OnFrame(&this->skelAnime, 5.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_BUBLE_WING);
    }

    if (this->timer > 0) {
        this->timer--;
    }
}

void EnBbfall_SetupDead(EnBbfall* this, GlobalContext* globalCtx) {
    Vec3f* bodyPartVelocity;
    Vec3f posDiff;
    f32 magnitude;
    s32 i;

    func_800BE5CC(&this->actor, &this->collider, 0);
    this->timer = 15;
    this->actor.shape.rot.x += 0x4E20;
    this->actor.speedXZ = 0.0f;
    SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 40, NA_SE_EN_BUBLE_DEAD);
    Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.world.pos, 0x70);
    this->actor.velocity.y = 0.0f;
    this->actor.speedXZ = 0.0f;
    this->bodyPartDrawStatus = BBFALL_BODY_PART_DRAW_STATUS_DEAD;
    this->actor.gravity = -1.5f;

    bodyPartVelocity = &this->bodyPartsVelocity[0];
    for (i = 0; i < ARRAY_COUNT(this->bodyPartsPos); i++, bodyPartVelocity++) {
        Math_Vec3f_Diff(&this->bodyPartsPos[i], &this->actor.world.pos, &posDiff);
        magnitude = Math3D_Vec3fMagnitude(&posDiff);
        if (magnitude > 1.0f) {
            magnitude = 2.5f / magnitude;
        }

        bodyPartVelocity->x = posDiff.x * magnitude;
        bodyPartVelocity->z = posDiff.z * magnitude;
        bodyPartVelocity->y = Rand_ZeroFloat(3.5f) + 10.0f;
    }

    this->actionFunc = EnBbfall_Dead;
}

void EnBbfall_Dead(EnBbfall* this, GlobalContext* globalCtx) {
    s32 i;

    this->timer--;
    Math_SmoothStepToS(&this->actor.world.rot.z, 0x4000, 4, 0x1000, 0x400);

    if (this->timer == 0) {
        for (i = 0; i < ARRAY_COUNT(this->bodyPartsPos); i++) {
            func_800B3030(globalCtx, &this->bodyPartsPos[i], &gZeroVec3f, &gZeroVec3f, 40, 7, 2);
            SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->bodyPartsPos[i], 11, NA_SE_EN_EXTINCT);
        }

        Actor_MarkForDeath(&this->actor);
    } else {
        for (i = 0; i < ARRAY_COUNT(this->bodyPartsPos); i++) {
            Math_Vec3f_Sum(&this->bodyPartsPos[i], &this->bodyPartsVelocity[i], &this->bodyPartsPos[i]);
            this->bodyPartsVelocity[i].y += this->actor.gravity;
        }
    }
}

void EnBbfall_SetupDamage(EnBbfall* this) {
    this->collider.base.acFlags &= ~AC_ON;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_BUBLE_DAMAGE);
    func_800BE5CC(&this->actor, &this->collider, 0);

    if (this->actor.colChkInfo.damageEffect == EN_BBFALL_DMGEFF_ZORA_MAGIC) {
        Actor_SetColorFilter(&this->actor, 0, 255, 0, 40);
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_ELECTRIC_SPARKS_LARGE;
        this->drawDmgEffAlpha = 2.0f;
        this->drawDmgEffScale = 0.4f;
    } else if (this->actor.colChkInfo.damageEffect == EN_BBFALL_DMGEFF_STUN) {
        Actor_SetColorFilter(&this->actor, 0, 255, 0, 20);
        this->actor.speedXZ = 0.0f;
    } else if (this->actor.colChkInfo.damageEffect == EN_BBFALL_DMGEFF_HOOKSHOT) {
        this->actor.speedXZ = 0.0f;
    } else {
        Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 20);
        this->actor.speedXZ = 7.0f;
    }

    this->actionFunc = EnBbfall_Damage;
}

void EnBbfall_Damage(EnBbfall* this, GlobalContext* globalCtx) {
    Math_SmoothStepToF(&this->actor.speedXZ, 0.0f, 1.0f, 0.5f, 0.0f);
    if ((this->actor.bgCheckFlags & 1) && (this->actor.speedXZ < 0.1f)) {
        if (func_808BF438(this, globalCtx)) {
            func_808BFA18(this);
        } else {
            EnBbfall_SetupDown(this);
        }
    }
}

void EnBbfall_SetupFrozen(EnBbfall* this) {
    this->actor.speedXZ = 0.0f;
    if (this->actor.velocity.y > 0.0f) {
        this->actor.velocity.y = 0.0f;
    }

    this->actor.gravity = -2.0f;
    this->actionFunc = EnBbfall_Frozen;
}

void EnBbfall_Frozen(EnBbfall* this, GlobalContext* globalCtx) {
    DECR(this->timer);

    if (this->timer == 0) {
        EnBbfall_Thaw(this, globalCtx);
        if (this->actor.colChkInfo.health == 0) {
            EnBbfall_SetupDead(this, globalCtx);
        } else {
            EnBbfall_SetupDown(this);
        }
    }
}

void EnBbfall_UpdateDamage(EnBbfall* this, GlobalContext* globalCtx) {
    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        this->collider.base.atFlags &= ~(AT_HIT | AT_BOUNCED);
        this->collider.base.atFlags &= ~AT_ON;
        if ((this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) ||
            (!(this->collider.elements[0].info.acHitInfo->toucher.dmgFlags & 0xDB0B3))) {
            Actor_SetDropFlagJntSph(&this->actor, &this->collider);
            this->unk_24C = 0;
            this->flameScaleY = 0.0f;
            this->flameScaleX = 0.0f;
            func_808BF5AC(this);
            EnBbfall_Thaw(this, globalCtx);

            if (Actor_ApplyDamage(&this->actor) == 0) {
                Enemy_StartFinishingBlow(globalCtx, &this->actor);
            }

            if (this->actor.colChkInfo.damageEffect == EN_BBFALL_DMGEFF_ICE_ARROW) {
                EnBbfall_Freeze(this);
                if (this->actor.colChkInfo.health == 0) {
                    this->timer = 3;
                    this->collider.base.acFlags &= ~AC_ON;
                }

                EnBbfall_SetupFrozen(this);
            } else if (this->actor.colChkInfo.health == 0) {
                EnBbfall_SetupDead(this, globalCtx);
            } else {
                EnBbfall_SetupDamage(this);
            }

            if (this->actor.colChkInfo.damageEffect == EN_BBFALL_DMGEFF_LIGHT_ARROW) {
                this->drawDmgEffAlpha = 4.0f;
                this->drawDmgEffScale = 0.4f;
                this->drawDmgEffType = ACTOR_DRAW_DMGEFF_LIGHT_ORBS;
                Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG,
                            this->collider.elements[0].info.bumper.hitPos.x,
                            this->collider.elements[0].info.bumper.hitPos.y,
                            this->collider.elements[0].info.bumper.hitPos.z, 0, 0, 0, CLEAR_TAG_SMALL_LIGHT_RAYS);
            }
        }
    } else {
        if (this->collider.base.atFlags & AT_BOUNCED) {
            this->collider.base.atFlags &= ~(AT_HIT | AT_BOUNCED);
            func_808BF5AC(this);
            if (this->actionFunc != EnBbfall_Down) {
                this->actor.world.rot.y = this->actor.yawTowardsPlayer + 0x8000;
                this->actor.shape.rot.y = this->actor.world.rot.y;
                EnBbfall_SetupDown(this);
            }
        }
    }
}

void EnBbfall_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnBbfall* this = THIS;
    Sphere16* sphere;
    Vec3f sp5C;
    s32 i;
    f32 temp_f0_2;
    s32 pad[2];

    EnBbfall_UpdateDamage(this, globalCtx);
    this->actionFunc(this, globalCtx);
    if (this->actionFunc != EnBbfall_Dead) {
        Actor_MoveWithGravity(&this->actor);
        if (this->unk_24D != 0) {
            Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, 25.0f, 20.0f, 7);
        }

        for (i = 5; i >= 2; i--) {
            Math_Vec3f_Diff(&this->unk_268[i - 2], &this->unk_268[i - 1], &sp5C);
            Math_Vec3f_Scale(&sp5C, (i - 1) * 0.1f);
            Math_Vec3f_Copy(&this->unk_268[i], &this->unk_268[i - 1]);
            Math_Vec3f_Sum(&this->unk_268[i], &sp5C, &this->unk_268[i]);
        }

        Math_Vec3f_Copy(&this->unk_268[1], &this->unk_268[0]);
        Math_Vec3f_Copy(&this->unk_268[0], &this->actor.world.pos);
        this->unk_268[0].y += 15.0f;
        this->unk_268[0].y -= 47.0f * this->flameScaleY;

        for (i = 0, temp_f0_2 = this->flameScaleX; i < 3; i++, temp_f0_2 *= 0.7569f) {
            sphere = &this->collider.elements[i].dim.worldSphere;
            sphere->radius = 30.0f * temp_f0_2;
            sphere->center.x = this->unk_268[2 * i].x;
            sphere->center.y = this->unk_268[2 * i].y + (47.0f * temp_f0_2);
            sphere->center.z = this->unk_268[2 * i].z;
        }

        this->collider.elements[0].dim.worldSphere.radius =
            CLAMP_MIN(this->collider.elements[0].dim.worldSphere.radius, 20);

        Math_Vec3s_ToVec3f(&this->actor.focus.pos, &this->collider.elements->dim.worldSphere.center);

        if (this->collider.base.atFlags & AT_ON) {
            this->actor.flags |= ACTOR_FLAG_1000000;
            CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }

        if (this->collider.base.acFlags & AC_ON) {
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }

        if (this->collider.base.ocFlags1 & OC1_ON) {
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }

        if (this->drawDmgEffAlpha > 0.0f) {
            if (this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
                Math_StepToF(&this->drawDmgEffAlpha, 0.0f, 0.05f);
                this->drawDmgEffScale = (this->drawDmgEffAlpha + 1.0f) * 0.2f;
                this->drawDmgEffScale = CLAMP_MAX(this->drawDmgEffScale, 0.4f);
            } else if (!Math_StepToF(&this->drawDmgEffFrozenSteamScale, 0.4f, 0.01f)) {
                func_800B9010(&this->actor, NA_SE_EV_ICE_FREEZE - SFX_FLAG);
            }
        }
    }
}

s32 EnBbfall_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                              Actor* thisx) {
    EnBbfall* this = THIS;

    if (this->bodyPartDrawStatus == BBFALL_BODY_PART_DRAW_STATUS_BROKEN) {
        this->limbDList = *dList;
        *dList = NULL;
    }

    return false;
}

void EnBbfall_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    s32 pad;
    EnBbfall* this = THIS;
    MtxF* currentMatrixState;

    if (this->bodyPartDrawStatus == BBFALL_BODY_PART_DRAW_STATUS_ALIVE) {
        if (sLimbIndexToBodyPartsIndex[limbIndex] != -1) {
            if (sLimbIndexToBodyPartsIndex[limbIndex] == 0) {
                Matrix_GetStateTranslationAndScaledX(1000.0f, &this->bodyPartsPos[0]);
            } else if (sLimbIndexToBodyPartsIndex[limbIndex] == 3) {
                Matrix_GetStateTranslationAndScaledX(-1000.0f, &this->bodyPartsPos[3]);
                Matrix_MultiplyVector3fByState(&sDuplicateCraniumBodyPartOffset, &this->bodyPartsPos[4]);
            } else {
                Matrix_GetStateTranslation(&this->bodyPartsPos[sLimbIndexToBodyPartsIndex[limbIndex]]);
            }
        }
    } else if (this->bodyPartDrawStatus > BBFALL_BODY_PART_DRAW_STATUS_ALIVE) {
        if (sLimbIndexToBodyPartsIndex[limbIndex] != -1) {
            Matrix_GetStateTranslation(&this->bodyPartsPos[sLimbIndexToBodyPartsIndex[limbIndex]]);
        }

        if (limbIndex == BUBBLE_LIMB_CRANIUM) {
            this->bodyPartDrawStatus = BBFALL_BODY_PART_DRAW_STATUS_BROKEN;
        }
    } else {
        if (sLimbIndexToBodyPartsIndex[limbIndex] != -1) {
            OPEN_DISPS(globalCtx->state.gfxCtx);

            currentMatrixState = Matrix_GetCurrentState();
            currentMatrixState->mf[3][0] = this->bodyPartsPos[sLimbIndexToBodyPartsIndex[limbIndex]].x;
            currentMatrixState->mf[3][1] = this->bodyPartsPos[sLimbIndexToBodyPartsIndex[limbIndex]].y;
            currentMatrixState->mf[3][2] = this->bodyPartsPos[sLimbIndexToBodyPartsIndex[limbIndex]].z;
            Matrix_InsertZRotation_s(thisx->world.rot.z, MTXMODE_APPLY);
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, this->limbDList);

            CLOSE_DISPS(globalCtx->state.gfxCtx);
        }
    }
}

void EnBbfall_Draw(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnBbfall* this = THIS;
    MtxF* currentMatrixState;
    Gfx* gfx;
    s32 phi_s3;
    Vec3f* ptr;
    s32 i;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gfx = POLY_OPA_DISP;
    gSPDisplayList(&gfx[0], &sSetupDL[6 * 25]);
    POLY_OPA_DISP = &gfx[1];
    SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, EnBbfall_OverrideLimbDraw,
                      EnBbfall_PostLimbDraw, &this->actor);

    if (this->unk_24C > 0) {
        func_8012C2DC(globalCtx->state.gfxCtx);
        Matrix_RotateY(
            ((Camera_GetCamDirYaw(globalCtx->cameraPtrs[globalCtx->activeCamera]) - this->actor.shape.rot.y) + 0x8000),
            MTXMODE_APPLY);
        Matrix_Scale(this->flameScaleX, this->flameScaleY, 1.0f, MTXMODE_APPLY);
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 0, 0, 0);
        currentMatrixState = Matrix_GetCurrentState();

        phi_s3 = this->unk_24C;
        ptr = &this->unk_268[0];

        for (i = 0; i < ARRAY_COUNT(this->unk_268); i++, ptr++) {
            gSPSegment(POLY_XLU_DISP++, 0x08,
                       Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 32, 64, 1, 0,
                                        ((globalCtx->gameplayFrames + (i * 10)) * (-20 + i * 2)) & 0x1FF, 32, 128));
            gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 255, 255, 0, phi_s3);
            currentMatrixState->mf[3][0] = ptr->x;
            currentMatrixState->mf[3][1] = ptr->y;
            currentMatrixState->mf[3][2] = ptr->z;
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, gGameplayKeepDrawFlameDL);

            phi_s3 -= 35;
            if (phi_s3 < 0) {
                break;
            }

            Matrix_Scale(0.87f, 0.87f, 1.0f, MTXMODE_APPLY);
        }
    }

    Actor_DrawDamageEffects(globalCtx, &this->actor, this->bodyPartsPos, ARRAY_COUNT(this->bodyPartsPos),
                            this->drawDmgEffScale, this->drawDmgEffFrozenSteamScale, this->drawDmgEffAlpha,
                            this->drawDmgEffType);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
