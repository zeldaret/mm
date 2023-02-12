/*
 * File: z_en_slime.c
 * Overlay: ovl_En_Slime
 * Description: Chuchu
 */

#include "z_en_slime.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_200)

#define THIS ((EnSlime*)thisx)

typedef enum EnSlimeEyeTexture {
    /* 0 */ EN_SLIME_EYETEX_OPEN,
    /* 1 */ EN_SLIME_EYETEX_HALF,
    /* 2 */ EN_SLIME_EYETEX_CLOSED,
    /* 3 */ EN_SLIME_EYETEX_HALF2
} EnSlimeEyeTexture;

typedef enum EnSlimeDamageType {
    /* 0 */ ENSLIME_DMGTYPE_NORMAL,
    /* 1 */ ENSLIME_DMGTYPE_STUN,
    /* 3 */ ENSLIME_DMGTYPE_ICEARROW = 3,
    /* 4 */ ENSLIME_DMGTYPE_LIGHT,
    /* 5 */ ENSLIME_DMGTYPE_ELECTRIC,
    /* 14 */ ENSLIME_DMGTYPE_HOOKSHOT = 14,
    /* 15 */ ENSLIME_DMGTYPE_BLUNT = 15,
} EnSlimeDamageType;

void EnSlime_Init(Actor* thisx, PlayState* play);
void EnSlime_Destroy(Actor* thisx, PlayState* play);
void EnSlime_Update(Actor* thisx, PlayState* play);
void EnSlime_Draw(Actor* thisx, PlayState* play);

void EnSlime_InitBehavior(EnSlime* this);
void EnSlime_InitializeIdle(EnSlime* this, PlayState* play);
void EnSlime_ReturnToIdle(EnSlime* this);
void EnSlime_SitIdle(EnSlime* this, PlayState* play);
void EnSlime_ChangeDirectionIdle(EnSlime* this);
void EnSlime_MoveInDirectionIdle(EnSlime* this, PlayState* play);
void EnSlime_ReturnHome(EnSlime* this);
void EnSlime_MoveToHome(EnSlime* this, PlayState* play);
void EnSlime_EngagePlayer(EnSlime* this);
void EnSlime_TurnToPlayer(EnSlime* this, PlayState* play);
void EnSlime_JumpAtPlayer(EnSlime* this);
void EnSlime_UpdateJump(EnSlime* this, PlayState* play);
void EnSlime_FinishJump(EnSlime* this);
void EnSlime_UpdateJumpLanding(EnSlime* this, PlayState* play);
void EnSlime_UpdateBluntHitReaction(EnSlime* this, PlayState* play);
void EnSlime_UpdateDamageReaction(EnSlime* this, PlayState* play);
void EnSlime_InitializeDeath(EnSlime* this);
void EnSlime_Expire(EnSlime* this, PlayState* play);
void EnSlime_SpawnIceBlock(EnSlime* this, PlayState* play);
void EnSlime_SetIceBlockedState(EnSlime* this);
void EnSlime_UpdateIceBlockedState(EnSlime* this, PlayState* play);
void EnSlime_UpdateStunnedState(EnSlime* this, PlayState* play);
void EnSlime_InitIceBlockUnfreeze(EnSlime* this);
void EnSlime_UpdateIceBlockUnfreeze(EnSlime* this, PlayState* play);
void EnSlime_HideDead(EnSlime* this);
void EnSlime_CountdownRespawn(EnSlime* this, PlayState* play);
void EnSlime_BeginRespawn(EnSlime* this);
void EnSlime_UpdateRespawn(EnSlime* this, PlayState* play);

const ActorInit En_Slime_InitVars = {
    ACTOR_EN_SLIME,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_SLIME,
    sizeof(EnSlime),
    (ActorFunc)EnSlime_Init,
    (ActorFunc)EnSlime_Destroy,
    (ActorFunc)EnSlime_Update,
    (ActorFunc)EnSlime_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x00, 0x04 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_HARD,
        BUMP_ON | BUMP_HOOKABLE,
        OCELEM_ON,
    },
    { 22, 35, 0, { 0, 0, 0 } },
};

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(3, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xE),
    /* Goron punch    */ DMG_ENTRY(0, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0x0),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(0, 0xF),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(1, 0x5),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0xF),
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

static CollisionCheckInfoInit sColChkInfoInit = { 1, 22, 35, 60 };

static TexturePtr sEyeTextures[] = {
    gChuchuEyeOpenTex,
    gChuchuEyeHalfTex,
    gChuchuEyeClosedTex,
    gChuchuEyeHalfTex,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(gravity, -2, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 6000, ICHAIN_STOP),
};

static s32 sVirtualAddrInit = false;

static Color_RGBA8 sBubblePrimColor = { 255, 255, 255, 255 };
static Color_RGBA8 sBubbleEnvColor = { 150, 150, 150, 0 };
static Vec3f sBubbleAccel = { 0.0, -0.8, 0.0 };

static Color_RGBA8 sPrimColors[] = {
    { 255, 255, 255, 255 },
    { 255, 255, 0, 255 },
    { 255, 255, 200, 255 },
    { 225, 200, 255, 255 },
};

static Color_RGBA8 sEnvColors[] = {
    { 140, 255, 195, 255 },
    { 50, 255, 0, 255 },
    { 255, 180, 0, 255 },
    { 255, 50, 155, 255 },
};

static Vec3f sLimbPosMultipliers[] = {
    { 2000.0, 2000.0, 0.0 }, { -1500.0, 2500.0, -500.0 }, { -500.0, 1000.0, 2500.0 },
    { 0.0, 4000.0, 0.0 },    { 0.0, 2000.0, -2000.0 },
};

AnimatedMaterial* sSlimeAnimTex;

/**
 * Initialize EnSlime instance.
 */
void EnSlime_Init(Actor* thisx, PlayState* play) {
    s32 respawnTimeSeconds;
    s32 i;
    EnSlime* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 38.0f);

    this->iceBlockTimer = 255; // 255 is the value used when the ice block is not in use
    this->eyeTexIndex = EN_SLIME_EYETEX_OPEN;
    this->wobbleRot.y = 0.0f;

    // Sets maximum distance chuchu will move from its home before turning around.
    if (this->actor.shape.rot.x <= 0) {
        this->distLimit = 30000.0f;
    } else {
        this->distLimit = (f32)this->actor.shape.rot.x * 40.0f;
    }

    this->actor.shape.rot.x = 0;
    respawnTimeSeconds = EN_SLIME_GET_RESPAWN_TIME(&this->actor);
    this->actor.shape.rot.z = 0;
    this->actor.params &= 0xFF;
    if (respawnTimeSeconds == 0xFF) {
        respawnTimeSeconds = 0;
    }

    // Upper byte of actorParams at init is # of seconds past 10s to respawn.
    this->respawnTime = (respawnTimeSeconds * 20) + 200;

    // Update addresses of texture assets (if another instance hasn't already)
    if (!sVirtualAddrInit) {
        for (i = 0; i < 4; i++) {
            sEyeTextures[i] = Lib_SegmentedToVirtual(sEyeTextures[i]);
        }
        sSlimeAnimTex = Lib_SegmentedToVirtual(gChuchuSlimeFlowTexAnim);
        sVirtualAddrInit = true;
    }

    // Lower byte of actorParams is the chuchu color type
    // Set hint IDs and drop item icon depending on chuchu color
    if (EN_SLIME_GET_MAIN_TYPE(&this->actor) == EN_SLIME_TYPE_YELLOW) {
        this->dropObjectTex = Lib_SegmentedToVirtual(gDropArrows1Tex);
        this->actor.hintId = TATL_HINT_ID_YELLOW_CHUCHU;
    } else if (EN_SLIME_GET_MAIN_TYPE(&this->actor) == EN_SLIME_TYPE_GREEN) {
        this->dropObjectTex = Lib_SegmentedToVirtual(gDropMagicSmallTex);
        this->actor.hintId = TATL_HINT_ID_GREEN_CHUCHU;
    } else if (EN_SLIME_GET_MAIN_TYPE(&this->actor) == EN_SLIME_TYPE_RED) {
        this->dropObjectTex = Lib_SegmentedToVirtual(gDropRecoveryHeartTex);
        this->actor.hintId = TATL_HINT_ID_RED_CHUCHU;
    } else {
        this->actor.hintId = TATL_HINT_ID_BLUE_CHUCHU;
    }

    // Sets actor scale and initial action func
    EnSlime_InitBehavior(this);
}

/**
 * Destroy EnSlime instance.
 */
void EnSlime_Destroy(Actor* thisx, PlayState* play) {
    EnSlime* this = THIS;
    Collider_DestroyCylinder(play, &this->collider);
}

/**
 * Upon immobilization via ice arrow (for chuchu types outside of blue), initialize
 * ice visual effects before chuchu enters immobile state.
 */
void EnSlime_InitIceStun(EnSlime* this) {
    this->damageEffectType = ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX;
    this->effectScale = 0.4f;
    this->collider.base.colType = COLTYPE_HIT3;
    this->frozenSteamScale = 0.6f;
    this->effectAlpha = 1.0f;
    this->timer = 80;
    this->actor.flags &= ~ACTOR_FLAG_400;
    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0x2000, 80);
}

/**
 * If ice effect was recently activated (ie. non-blue chuchu was frozen by ice arrow),
 * and the particle effect hasn't spawned yet, update the damage effect state and
 * spawn the ice effects.
 */
void EnSlime_UpdateIceEffects(EnSlime* this, PlayState* play) {
    if (this->damageEffectType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
        this->damageEffectType = 0; // So it's not triggered again until InitIceStun has been called again.
        this->collider.base.colType = COLTYPE_NONE;
        this->effectAlpha = 0.0f;
        Actor_SpawnIceEffects(play, &this->actor, this->limbPos, EN_SLIME_LIMBPOS_COUNT, 2, 0.2f, 0.2f);
        this->actor.flags |= ACTOR_FLAG_200;
    }
}

/**
 * If blink animation is in progress, advance to next frame.
 * If eyes are open, randomly (5% chance) initialize new blink cycle.
 */
void EnSlime_UpdateBlink(EnSlime* this) {
    if (this->eyeTexIndex != EN_SLIME_EYETEX_OPEN) {
        if (++this->eyeTexIndex == 4) {
            this->eyeTexIndex = 0;
        }
    } else if (Rand_ZeroOne() < 0.05f) {
        this->eyeTexIndex = EN_SLIME_EYETEX_HALF;
    }
}

/**
 * Set the actor's initial scale and action function.
 */
void EnSlime_InitBehavior(EnSlime* this) {
    this->actor.scale.x = 0.008f;
    this->actor.scale.z = 0.008f;
    this->actor.scale.y = 0.011f;
    this->actionFunc = EnSlime_InitializeIdle;
}

/**
 * Once BGCHECK_CHECK_WALL flag is set, idle action cycle is entered.
 * This function is only called right after the actor is first initialized.
 * It is not set as the action function again.
 */
void EnSlime_InitializeIdle(EnSlime* this, PlayState* play) {
    if (this->actor.bgCheckFlags & BGCHECK_CHECK_WALL) {
        this->actor.flags &= ~ACTOR_FLAG_10;
        EnSlime_ReturnToIdle(this);
    }
}

/**
 * Set or restore idle action state.
 * Sets timer to 25 and cycles to SitIdle action.
 */
void EnSlime_ReturnToIdle(EnSlime* this) {
    this->timer = 25;
    this->actionFunc = EnSlime_SitIdle;
    this->actor.speedXZ = 0.0f;
}

/**
 * Sit idle for one frame, updating rotation and scale to give
 * the actor an amorphous, oozing effect.
 * Chuchu will engage player during idle sit if player is visible and
 * close enough to it.
 */
void EnSlime_SitIdle(EnSlime* this, PlayState* play) {
    f32 sqrtFactor;
    f32 sinFactor;

    this->timer--;
    sqrtFactor = sqrtf(this->timer) * 0.2f;
    EnSlime_UpdateBlink(this);

    sinFactor = ((sin_rad(this->timer * (2.0f * M_PI / 5.0f)) * (0.13f * sqrtFactor)) + 1.0f) * 0.01f;
    this->actor.scale.x = sinFactor;
    this->actor.scale.z = sinFactor;
    if (this->timer < 24) {
        this->actor.scale.y = ((cos_rad(this->timer * (2.0f * M_PI / 5.0f)) * (0.05f * sqrtFactor)) + 1.0f) * 0.01f;
    }

    this->actor.shape.rot.x = randPlusMinusPoint5Scaled(0x200) * sqrtFactor;
    this->actor.shape.rot.z = randPlusMinusPoint5Scaled(0x200) * sqrtFactor;

    // If player is not wearing the stone mask, is within 280 units of the chuchu, and the chuchu
    //   is facing the player, initialize chase/attack cycle.
    if ((Player_GetMask(play) != PLAYER_MASK_STONE) && (this->actor.xzDistToPlayer < 280.0f) &&
        Actor_IsFacingPlayer(&this->actor, 0x5000)) {
        EnSlime_EngagePlayer(this);
    } else if (this->timer == 0) {
        // Done sitting, start moving (remaining idle)
        EnSlime_ChangeDirectionIdle(this);
    }
}

/**
 * Reset the action timer (to 120), then select a new direction for
 * chuchu to move.
 * Set action function to MoveInDirectionIdle
 */
void EnSlime_ChangeDirectionIdle(EnSlime* this) {
    this->timer = 120;

    /*If actor is more than 120 units from its home, set the new direction to be towards its home.
     * Otherwise, the new direction to move is pretty much random.
     */
    if (Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos) > 120.0f) {
        this->idleRotY = Actor_YawToPoint(&this->actor, &this->actor.home.pos);
    } else if (Rand_ZeroOne() < 0.7f) {
        this->idleRotY = (s32)randPlusMinusPoint5Scaled(0x4000) + this->actor.shape.rot.y;
    }
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = EnSlime_MoveInDirectionIdle;
}

/**
 * While moving idle, update rotation, speed, scale in a sinusoidal fashion to
 * give oozing effect.
 * If actor has hit a wall or is too far from home, turn around.
 * Chuchu will engage player during idle movement if player is visible and
 * close enough to it.
 */
void EnSlime_MoveInDirectionIdle(EnSlime* this, PlayState* play) {
    f32 sinFactor;

    EnSlime_UpdateBlink(this);
    this->timer--;
    Math_ApproachS(&this->actor.shape.rot.y, this->idleRotY, 4, 0x100);

    /* If actor is touching a wall (bgCheckFlag 8?), set target rotation to match wall where it is touching.
     * If actor is more than 120 units from its home, turn around to face home.
     */
    if (this->actor.bgCheckFlags & BGCHECK_CHECK_ONE_FACE) {
        this->idleRotY = this->actor.wallYaw;
    } else if (Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos) > 120.0f) {
        this->idleRotY = Actor_YawToPoint(&this->actor, &this->actor.home.pos);
    }

    // Update actor scale, xz speed, and rotation to provide amorphous effect
    sinFactor = fabsf(sin_rad(this->timer * (M_PI / 24)));
    Math_StepToF(&this->actor.scale.z, ((0.15f * sinFactor) + 1.0f) * 0.01f, 0.0002f);
    Math_StepToF(&this->actor.scale.x, (1.0f - (0.2f * sinFactor)) * 0.01f, 0.0002f);
    Math_StepToF(&this->actor.scale.y, (1.0f - (0.1f * sinFactor)) * 0.01f, 0.0002f);

    this->actor.speedXZ = (0.8f * sinFactor) + 0.2f;
    this->actor.shape.rot.x = 0x800 * sinFactor;
    this->actor.world.rot.y = this->actor.shape.rot.y;

    if (Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos) > this->distLimit) {
        // If actor is too far from home, start return home cycle
        EnSlime_ReturnHome(this);
    } else if ((Player_GetMask(play) != PLAYER_MASK_STONE) && (this->actor.xzDistToPlayer < 280.0f) &&
               (Actor_IsFacingPlayer(&this->actor, 0x5000))) {
        // If player is close enough to chuchu while not wearing the stone mask, and the chuchu is facing player,
        //  initialize attack cycle
        EnSlime_EngagePlayer(this);
    } else if (this->timer == 0) {
        // If move timer runs out, restart idle cycle (sit in place for 25 frames)
        EnSlime_ReturnToIdle(this);
    }
}

/**
 * Reset the action timer (to 24), then set the target y angle to face home.
 * Set action function to MoveToHome.
 */
void EnSlime_ReturnHome(EnSlime* this) {
    this->timer = 24;
    this->idleRotY = Actor_YawToPoint(&this->actor, &this->actor.home.pos);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = EnSlime_MoveToHome;
}

/**
 * While moving towards home point, update rotation, speed, scale
 * in a sinusoidal fashion to give oozing effect.
 * If actor has hit a wall, turn around.
 * Once it is close enough to home point, return to idle cycle.
 * Chuchu will not engage player while the return home cycle is active.
 */
void EnSlime_MoveToHome(EnSlime* this, PlayState* play) {
    f32 sinFactor;

    EnSlime_UpdateBlink(this);
    this->timer--;
    Math_ApproachS(&this->actor.shape.rot.y, this->idleRotY, 4, 0x400);
    if (this->actor.bgCheckFlags & BGCHECK_CHECK_ONE_FACE) {
        // If hit wall, turn around.
        this->idleRotY = this->actor.wallYaw;
    } else {
        this->idleRotY = Actor_YawToPoint(&this->actor, &this->actor.home.pos);
    }

    sinFactor = fabsf(sin_rad(this->timer * (M_PI / 24)));
    Math_StepToF(&this->actor.scale.z, ((0.15f * sinFactor) + 1.0f) * 0.01f, 0.0002f);
    Math_StepToF(&this->actor.scale.x, (1.0f - (0.2f * sinFactor)) * 0.01f, 0.0002f);
    Math_StepToF(&this->actor.scale.y, (1.0f - (0.1f * sinFactor)) * 0.01f, 0.0002f);

    this->actor.speedXZ = (0.8f * sinFactor) + 0.2f;
    this->actor.shape.rot.x = 0x800 * sinFactor;
    this->actor.world.rot.y = this->actor.shape.rot.y;

    // Reset timer
    if (this->timer == 0) {
        this->timer = 24;
    }

    // Only return to idle once actor is close enough to home point.
    if (Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos) < (this->distLimit * 0.8f)) {
        EnSlime_ReturnToIdle(this);
    }
}

/**
 * Initialize or restart the engage/attack player cycle.
 */
void EnSlime_EngagePlayer(EnSlime* this) {
    this->actor.shape.rot.x = 0;
    this->actor.shape.rot.z = 0;
    this->timer = 8;
    this->actionFunc = EnSlime_TurnToPlayer;
    this->actor.speedXZ = 0.0f;
}

/**
 * Update actor angle and ooze effect as chuchu initially
 * turns to face player.
 */
void EnSlime_TurnToPlayer(EnSlime* this, PlayState* play) {
    f32 factorY;
    f32 factorXZ;

    this->timer--;
    EnSlime_UpdateBlink(this);
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 4, 0x1000);
    if (this->timer >= 0) {
        factorY = 8 - this->timer;
        factorXZ = ((factorY * 0.04f) + 1.0f) * 0.01f;
        this->actor.scale.x = factorXZ;
        this->actor.scale.y = (1.0f - (factorY * 0.05f)) * 0.01f;
        this->actor.scale.z = factorXZ;
    }
    if (this->timer < -2) {
        EnSlime_JumpAtPlayer(this);
    }
}

/**
 * Initialize jump toward player. If fewer than 120 units from
 * the player, start a larger attack lunge. Otherwise, hop forward.
 * Set action function to EnSlime_UpdateJump
 */
void EnSlime_JumpAtPlayer(EnSlime* this) {
    if (this->actor.xzDistToPlayer > 120.0f) {
        this->actor.velocity.y = 11.0f;
        this->actor.speedXZ = 5.0f;
        this->actor.gravity = -2.0f;
    } else {
        this->actor.velocity.y = 18.0f;
        this->actor.speedXZ = 7.0f;
        this->actor.gravity = -3.5f;
    }
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->timer = 12;
    this->eyeTexIndex = EN_SLIME_EYETEX_OPEN;
    Math_StepToF(&this->actor.scale.x, 0.008f, 0.0025f);
    Math_StepToF(&this->actor.scale.y, 0.011f, 0.0025f);
    this->actor.scale.z = this->actor.scale.x;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_SLIME_JUMP);
    this->actionFunc = EnSlime_UpdateJump;
}

/**
 * Check for collision and whether actor has stopped falling.
 * Update actor scale for slime effect.
 * If collision, knockback actor. If actor has stopped moving
 * in Y direction, initialize landing action.
 */
void EnSlime_UpdateJump(EnSlime* this, PlayState* play) {
    this->timer--;
    if (this->collider.base.atFlags & AT_HIT) {
        if (this->actor.speedXZ > 0.0f) {
            this->actor.speedXZ *= -1.2f;
            this->collider.base.atFlags &= ~AT_HIT;
        }
    }
    Math_StepToF(&this->actor.scale.x, 0.008f, 0.0025f);
    Math_StepToF(&this->actor.scale.y, 0.011f, 0.0025f);
    this->actor.scale.z = this->actor.scale.x;
    if ((this->actor.velocity.y < 0.0f) && (this->actor.bgCheckFlags & BGCHECK_CHECK_WALL)) {
        EnSlime_FinishJump(this);
    }
}

/**
 * Initialize jump landing.
 * Adjust timer and scale, and stop xz movement.
 * Set action function to UpdateJumpLanding
 */
void EnSlime_FinishJump(EnSlime* this) {
    this->timer = 15;
    this->actor.scale.x = 0.0132f;
    this->actor.scale.y = 0.0074399994f;
    this->actor.scale.z = 0.0132f;
    this->actionFunc = EnSlime_UpdateJumpLanding;
    this->actor.speedXZ = 0.0f;
}

/**
 * Update scale/rot for ooze jiggle effect (XZ), update Y scale
 * to make it appear as though chuchu is compressing.
 * If > 12 frames have passed since jump start, check again if player
 * is in range and restart engage/jump cycle if so.
 * If too far from home, initialize return home cycle (takes priority over
 * player engage check).
 * Otherwise, if timer is up, return to idle.
 */
void EnSlime_UpdateJumpLanding(EnSlime* this, PlayState* play) {
    f32 factorScaleY;
    f32 factorRotXZ;
    f32 factorScaleXZ;

    EnSlime_UpdateBlink(this);
    this->timer--;
    factorScaleY = ((this->timer / 5) + 1) * 1.6f;
    factorRotXZ = sqrtf(this->timer) * 0.2f;
    factorScaleXZ = ((cos_rad(this->timer * (2.0f * M_PI / 5.0f)) * (0.05f * factorScaleY)) + 1.0f) * 0.01f;
    this->actor.scale.x = factorScaleXZ;
    this->actor.scale.z = factorScaleXZ;
    if (this->timer < 15) {
        this->actor.scale.y = (1.0f - (sin_rad(this->timer * (2.0f * M_PI / 5.0f)) * (0.04f * factorScaleY))) * 0.01f;
    }
    this->actor.shape.rot.x = randPlusMinusPoint5Scaled(0x200) * factorRotXZ;
    this->actor.shape.rot.z = randPlusMinusPoint5Scaled(0x200) * factorRotXZ;

    if (Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos) > this->distLimit) {
        EnSlime_ReturnHome(this);
    } else if ((Player_GetMask(play) != PLAYER_MASK_STONE) && (this->actor.xzDistToPlayer < 280.0f) &&
               (this->timer < 12)) {
        EnSlime_EngagePlayer(this);
    } else if (this->timer == 0) {
        EnSlime_ReturnToIdle(this);
    }
}

/**
 * Initialize reaction to receiving a blunt hit (such as with Goron Punch etc.)
 * Chuchu does not take damage, but appears slide backwards.
 * Action function set to UpdateBluntHitReaction.
 */
void EnSlime_ReactToBluntHit(EnSlime* this) {
    this->actor.speedXZ = 10.0f;
    if (this->actor.velocity.y > 0.0f) {
        this->actor.velocity.y = 0.0f;
    }
    this->collider.base.acFlags &= ~AC_ON;
    this->timer = 30;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_SLIME_DEFENCE);
    if (this->collider.base.ac != NULL) {
        this->actor.world.rot.y = Actor_YawBetweenActors(&this->actor, this->collider.base.ac) + 0x8000;
    } else {
        this->actor.world.rot.y = this->actor.yawTowardsPlayer + 0x8000;
    }
    this->actionFunc = EnSlime_UpdateBluntHitReaction;
}

/**
 * Update reaction to receiving a blunt hit (such as with Goron Punch etc.)
 * Update XZ speed and jiggle effect
 * AC_ON flag is off until 15 frames of reaction remain.
 * When timer is up, chuchu will choose whether to engage player, return home,
 * or return to idle. If chuchu is too far from home, returning home will
 * take precedence.
 */
void EnSlime_UpdateBluntHitReaction(EnSlime* this, PlayState* play) {
    f32 timerFactor;
    f32 scaleFactor;

    EnSlime_UpdateBlink(this);
    this->timer--;
    Math_StepToF(&this->actor.speedXZ, 0.0f, 1.0f);
    timerFactor = sqrtf(this->timer);
    if (this->timer < 30) {
        scaleFactor = ((cos_rad(this->timer * (2.0f * M_PI / 5.0f)) * (0.08f * timerFactor)) + 1.0f) * 0.01f;
        this->actor.scale.x = scaleFactor;
        this->actor.scale.z = scaleFactor;
    }
    if (this->timer == 15) {
        this->collider.base.acFlags |= AC_ON;
    }
    this->actor.scale.y = ((sin_rad((f32)this->timer * (2.0f * M_PI / 5.0f)) * (0.07f * timerFactor)) + 1.0f) * 0.01f;
    this->actor.shape.rot.x = randPlusMinusPoint5Scaled(0x200) * timerFactor;
    this->actor.shape.rot.z = randPlusMinusPoint5Scaled(0x200) * timerFactor;

    if (this->timer == 0) {
        if (Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos) > this->distLimit) {
            EnSlime_ReturnHome(this);
        } else if ((this->actor.xzDistToPlayer < 280.0f) && (Player_GetMask(play) != PLAYER_MASK_STONE)) {
            EnSlime_EngagePlayer(this);
        } else {
            EnSlime_ReturnToIdle(this);
        }
    }
}

/**
 * Initialize reaction to taking damage.
 * (I am not confident in what the last arg is for, but it seems to be a boolean of some kind).
 * Spawn bubbles & splash, start actor rebuff wobble, push actor, and play sfx.
 * Set action function to UpdateDamageReaction
 */
void EnSlime_ReactToDamage(EnSlime* this, PlayState* play, s32 faceDamageSource) {
    s32 i;
    Vec3f effectVelocity;
    Vec3f effectPos;
    f32 ySin;
    f32 yCos;
    f32 random;

    this->collider.base.acFlags &= ~AC_ON;
    if (this->actor.velocity.y > 0.0f) {
        this->actor.velocity.y = 0.0f;
    }
    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0x2000, 20);
    this->timer = 20;
    this->actor.speedXZ = 10.0f;
    if (faceDamageSource == true) {
        // This function changes actor's world Y rotation - I think it's maybe to face source of damage?
        func_800BE504(&this->actor, &this->collider);
    }

    this->eyeTexIndex = EN_SLIME_EYETEX_OPEN;
    Actor_SetScale(&this->actor, 0.01f);
    this->wobbleRot.x = Rand_ZeroOne() * (M_PI * 2.0f);
    this->wobbleRot.z = Rand_ZeroOne() * (M_PI * 2.0f);
    ySin = Math_SinS(this->actor.world.rot.y) * 10.0f;
    yCos = Math_CosS(this->actor.world.rot.y) * 10.0f;
    effectPos.x = this->actor.world.pos.x + ySin;
    effectPos.y = this->actor.world.pos.y + 20.0f;
    effectPos.z = this->actor.world.pos.z + yCos;
    EffectSsGSplash_Spawn(play, &effectPos, NULL, NULL, 1, 550);

    for (i = 0; i < 10; i++) {
        effectPos.x = randPlusMinusPoint5Scaled(40.0f) + this->actor.world.pos.x + ySin;
        effectPos.y = randPlusMinusPoint5Scaled(10.0f) + this->actor.world.pos.y + 40.0f;
        effectPos.z = randPlusMinusPoint5Scaled(40.0f) + this->actor.world.pos.z + yCos;

        random = Rand_ZeroOne();
        effectVelocity.x = -Math_SinS(this->actor.world.rot.y) * ((random * 3.5f) + 1.0f);
        random = Rand_ZeroOne();
        effectVelocity.z = -Math_CosS(this->actor.world.rot.y) * ((random * 3.5f) + 1.0f);
        effectVelocity.y = (Rand_ZeroOne() * 6.0f) + 2.0f;
        EffectSsDtBubble_SpawnCustomColor(play, &effectPos, &effectVelocity, &sBubbleAccel, &sBubblePrimColor,
                                          &sBubbleEnvColor, Rand_S16Offset(40, 20), 20, 0);
    }

    if (this->actor.colChkInfo.health == 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_SLIME_DEAD);
    } else {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_SLIME_DAMAGE);
    }
    this->actionFunc = EnSlime_UpdateDamageReaction;
}

/**
 * Update reaction to taking damage.
 * Updates the rebuff wobble. Once timer drops to 0, actor initializes death cycle,
 * re-engages player, or returns to idle.
 */
void EnSlime_UpdateDamageReaction(EnSlime* this, PlayState* play) {
    this->timer--;
    Math_StepToF(&this->actor.speedXZ, 0.0f, 1.0f);
    if ((this->timer % 5) == 0) {
        this->wobbleRot.x = Rand_ZeroOne() * (M_PI * 2.0f);
        this->wobbleRot.z = Rand_ZeroOne() * (M_PI * 2.0f);
    }
    if (this->timer == 0) {
        if (this->actor.colChkInfo.health != 0) {
            this->collider.base.acFlags |= AC_ON;
            if ((this->actor.xzDistToPlayer < 280.0f) && (Player_GetMask(play) != PLAYER_MASK_STONE)) {
                EnSlime_EngagePlayer(this);
            } else {
                EnSlime_ReturnToIdle(this);
            }
        } else {
            SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, 40, NA_SE_EN_SLIME_BREAK);
            EnSlime_InitializeDeath(this);
        }
    }
}

/**
 * Initialize death action cycle. Disable AC_ON flag,
 * make actor stop moving, and shrink the actor.
 * Set action function to Expire.
 */
void EnSlime_InitializeDeath(EnSlime* this) {
    this->collider.base.acFlags &= ~AC_ON;
    if (this->actor.velocity.y > 0.0f) {
        this->actor.velocity.y = 0.0f;
    }
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = EnSlime_Expire;
    this->actor.speedXZ = 0.0f;
}

/**
 * Spawn random effects (bubbles, splash) for death sequence.
 * If chuchu is red, green, or yellow, spawn item drop.
 * Shrink actor scale to 0.
 * Call HideDead function for cleanup.
 */
void EnSlime_Expire(EnSlime* this, PlayState* play) {
    s32 i;
    Vec3f velocity;
    Vec3f effectPos;
    f32 random;
    s32 factor;

    if (Math_StepToF(&this->actor.scale.x, 0.0f, 0.002f)) {
        effectPos.x = this->actor.world.pos.x;
        effectPos.y = this->actor.world.pos.y + 20.0f;
        effectPos.z = this->actor.world.pos.z;
        EffectSsGSplash_Spawn(play, &effectPos, NULL, NULL, 1, 800);

        for (i = 0; i < 15; i++) {
            random = Rand_ZeroOne();

            if (Rand_ZeroOne() < 0.5f) {
                factor = -1;
            } else {
                factor = 1;
            }

            velocity.x = factor * ((random * 2.5f) + 2.0f);

            random = Rand_ZeroOne();
            if (Rand_ZeroOne() < 0.5f) {
                factor = -1;
            } else {
                factor = 1;
            }

            velocity.z = factor * ((random * 2.5f) + 2.0f);

            velocity.y = (Rand_ZeroOne() * 6.0f) + 2.0f;
            EffectSsDtBubble_SpawnCustomColor(play, &effectPos, &velocity, &sBubbleAccel, &sBubblePrimColor,
                                              &sBubbleEnvColor, Rand_S16Offset(40, 20), 20, 0);
        }

        if (this->actor.params == EN_SLIME_TYPE_YELLOW) {
            Item_DropCollectible(play, &this->actor.world.pos, ITEM00_ARROWS_10);
        } else if (this->actor.params == EN_SLIME_TYPE_GREEN) {
            Item_DropCollectible(play, &this->actor.world.pos, ITEM00_MAGIC_SMALL);
        } else if (this->actor.params == EN_SLIME_TYPE_RED) {
            Item_DropCollectible(play, &this->actor.world.pos, ITEM00_RECOVERY_HEART);
        }
        EnSlime_HideDead(this);
    }
    this->actor.scale.y = this->actor.scale.x;
    this->actor.scale.z = this->actor.scale.x;
}

/**
 * Calculate a new "current" position value that is a multiple of 60
 * away from the "home" position.
 * This is for use by blue chuchus frozen into an ice block so that
 * their position is a multiple of the ice block size.
 */
f32 EnSlime_SnapIceBlockPosition(f32 currentPosition, f32 homePosition) {
    s32 dist = currentPosition - homePosition;

    if (dist > 0) {
        dist += 30;
    } else {
        dist -= 30;
    }

    return ((dist / 60) * 60.0f) + homePosition;
}

/**
 * Prepare actor for ice block to spawn around it.
 * The actor will stop moving, have AC_ON cleared, and
 * target position will be snapped to a multiple of the size of
 * an ice block.
 * Set action function to SpawnIceBlock
 */
void EnSlime_InitIceBlock(EnSlime* this) {
    this->collider.base.acFlags &= ~AC_ON;
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->effectAlpha = 0.0f;
    this->actor.speedXZ = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->actor.gravity = 0.0f;
    this->iceBlockSnapPos.x = EnSlime_SnapIceBlockPosition(this->actor.world.pos.x, this->actor.home.pos.x);
    this->iceBlockSnapPos.z = EnSlime_SnapIceBlockPosition(this->actor.world.pos.z, this->actor.home.pos.z);
    Actor_SetColorFilter(&this->actor, 0x8000, 0x80FF, 0x2000, 10);
    this->eyeTexIndex = EN_SLIME_EYETEX_OPEN;
    this->iceBlockTimer = 254;
    this->actionFunc = EnSlime_SpawnIceBlock;
}

/**
 * Attempt to move the chuchu to snapped position and
 * spawn an ice block actor as a child of the chuchu actor.
 * If ice block spawn fails, chuchu returns to idle.
 */
void EnSlime_SpawnIceBlock(EnSlime* this, PlayState* play) {
    s32 stepCheck; // bool

    stepCheck = Math_StepToF(&this->actor.world.pos.x, this->iceBlockSnapPos.x, 10.0f);
    stepCheck &= Math_StepToF(&this->actor.world.pos.z, this->iceBlockSnapPos.z, 10.0f);

    this->actor.colorFilterTimer = 10;
    if (stepCheck) {
        this->actor.child =
            Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_OBJ_ICEBLOCK, this->actor.world.pos.x,
                               this->actor.world.pos.y + 30.0f, this->actor.world.pos.z, 0, 0, 0, 0);
        if (this->actor.child != NULL) {
            this->actor.child->cutscene = this->actor.cutscene;
            EnSlime_SetIceBlockedState(this);
        } else {
            this->actor.colorFilterTimer = 0;
            this->collider.base.acFlags |= AC_ON;
            this->iceBlockTimer = 255;
            this->actor.flags |= ACTOR_FLAG_1;
            this->actor.gravity = -2.0f;
            EnSlime_ReturnToIdle(this);
        }
    }
}

/**
 * Enter state as a chuchu frozen in an ice block.
 * This function is called after ice block spawn is successful.
 * Action function set to UpdateIceBlockedState
 */
void EnSlime_SetIceBlockedState(EnSlime* this) {
    this->actor.flags |= ACTOR_FLAG_10;
    this->actionFunc = EnSlime_UpdateIceBlockedState;
}

/**
 * Decrement the ice block timer, or if it has hit zero, check to
 * see if the ice block child actor link has been broken or if it has
 * shrunk sufficiently.
 * If timer is up and ice block is sufficiently "gone", init unfreeze.
 */
void EnSlime_UpdateIceBlockedState(EnSlime* this, PlayState* play) {
    if (this->iceBlockTimer == 0) {
        // Proceed to next action if ice block link or its update link are broken or the ice block has shrunk
        // sufficiently.
        if ((this->actor.child == NULL) || (this->actor.child->update == NULL) ||
            !(this->actor.child->scale.y >= 0.1f)) {
            EnSlime_InitIceBlockUnfreeze(this);
        }
    } else {
        this->actor.colorFilterTimer = 10;
        if (this->iceBlockTimer - 5 < 0) {
            this->iceBlockTimer = 0;
        } else {
            this->iceBlockTimer -= 5;
        }
    }
}

/**
 * Prepare the actor to behave as if stunned. Set speed to zero,
 * and set action function to UpdateStunnedState.
 */
void EnSlime_EnterStunnedState(EnSlime* this) {
    this->actor.speedXZ = 0.0f;
    func_800BE504(&this->actor, &this->collider);
    if (this->actor.velocity.y > 0.0f) {
        this->actor.velocity.y = 0.0f;
    }
    this->actionFunc = EnSlime_UpdateStunnedState;
}

/**
 * Check the actor's timer to see whether stun has worn off.
 * If so, either react to damage and initialize death, or start
 * idly wobbling in a new direction.
 */
void EnSlime_UpdateStunnedState(EnSlime* this, PlayState* play) {
    this->timer--;
    if (this->timer == 0) {
        EnSlime_UpdateIceEffects(this, play);
        if (this->actor.colChkInfo.health == 0) {
            EnSlime_ReactToDamage(this, play, false);
        } else {
            this->actor.world.rot.y = this->actor.shape.rot.y;
            EnSlime_ChangeDirectionIdle(this);
        }
    }
}

/**
 * Setup ice block unfreeze
 * Set action function to UpdateIceBlockUnfreeze
 */
void EnSlime_InitIceBlockUnfreeze(EnSlime* this) {
    this->actor.colorFilterTimer = 0;
    this->actor.gravity = -2.0f;
    Actor_SetColorFilter(&this->actor, 0x8000, 0x80FF, 0x2000, 10);
    this->actionFunc = EnSlime_UpdateIceBlockUnfreeze;
}

/**
 * Update the actor's ice block timer to match state of ice block.
 * When it reaches the "unset" value (255), return actor to idle.
 */
void EnSlime_UpdateIceBlockUnfreeze(EnSlime* this, PlayState* play) {
    s32 iceBlockTimerAdj;

    this->actor.colorFilterTimer = 10;
    if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
        iceBlockTimerAdj = (0.1f - this->actor.child->scale.y) * 10.0f * 255.0f;
        this->iceBlockTimer = CLAMP(iceBlockTimerAdj, 0, 255);
    } else {
        this->actor.child = NULL;
        iceBlockTimerAdj = this->iceBlockTimer + 10;
        this->iceBlockTimer = CLAMP_MAX(iceBlockTimerAdj, 255);
    }

    if (this->iceBlockTimer == 255) {
        this->collider.base.acFlags |= AC_ON;
        this->actor.flags |= ACTOR_FLAG_1;
        this->actor.flags &= ~ACTOR_FLAG_10;
        EnSlime_ReturnToIdle(this);
    }
}

/**
 * Set speed to zero, and make undrawable.
 * Initialize respawn timer.
 * Set action function to CountdownRespawn
 */
void EnSlime_HideDead(EnSlime* this) {
    this->actor.draw = NULL;
    this->actor.flags |= ACTOR_FLAG_10;
    this->effectAlpha = 0.0f;
    this->actor.gravity = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->actor.speedXZ = 0.0f;
    this->collider.base.ocFlags1 &= ~OC1_ON;
    this->timer = this->respawnTime;
    this->actionFunc = EnSlime_CountdownRespawn;
}

/**
 * Decrement the respawn timer, or if it is zero,
 * initialize respawn action cycle.
 */
void EnSlime_CountdownRespawn(EnSlime* this, PlayState* play) {
    if (this->timer == 0) {
        EnSlime_BeginRespawn(this);
    } else {
        this->timer--;
    }
}

/**
 * Re-enable drawing, reset the actor's health and home,
 * and setup and initialize respawn action.
 * Set action function to UpdateRespawn
 */
void EnSlime_BeginRespawn(EnSlime* this) {
    this->actor.draw = EnSlime_Draw;
    this->actor.colChkInfo.health = sColChkInfoInit.health;
    this->iceBlockTimer = 255;
    Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.home.pos);
    this->timer = 0;
    this->actor.colorFilterTimer = 0;
    this->actor.home.rot.y = this->actor.yawTowardsPlayer;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_SLIME_SURFACE);
    this->actionFunc = EnSlime_UpdateRespawn;
    this->actor.gravity = -2.0f;
}

/**
 * Update bubbling back up effect. After 21 frames, OC1_ON is set.
 * After 28 frames, AC_ON is set and actor returns to idle movement.
 */
void EnSlime_UpdateRespawn(EnSlime* this, PlayState* play) {
    f32 rescaleFactor1;
    f32 rescaleFactor2;

    if (++this->timer == 28) {
        this->actor.flags &= ~ACTOR_FLAG_10;
        this->actor.flags |= ACTOR_FLAG_1;
        this->collider.base.acFlags |= AC_ON;
        this->actor.shape.rot.y = this->actor.home.rot.y;
        EnSlime_ChangeDirectionIdle(this);
    } else {
        if (this->timer < 12) {
            rescaleFactor1 = this->timer * 0.0008333333f; // This is about 1/1200, but (1.0f/1200.0f) does not match
            this->respawnScale.x = rescaleFactor1;
            this->respawnScale.z = rescaleFactor1;
            this->respawnScale.y = 2.0f * rescaleFactor1;
            this->respawnRotY = this->timer * (0x4000 / 10.0f);
        } else if (this->timer < 20) {
            rescaleFactor1 = (this->timer - 12) * (1.0f / 1600.0f);
            rescaleFactor2 = 0.01f + rescaleFactor1;
            this->respawnScale.x = rescaleFactor2;
            this->respawnScale.z = rescaleFactor2;
            this->respawnScale.y = 2.0f * (0.01f - rescaleFactor1);
            this->respawnRotY = this->timer * (0x4000 / 10.0f);
        } else if (this->timer < 24) {
            rescaleFactor1 = (this->timer - 20) * 0.0033333332f; // This is about 1/300
            rescaleFactor2 = 0.015f - rescaleFactor1;
            this->respawnScale.x = rescaleFactor2;
            this->respawnScale.z = rescaleFactor2;
            this->respawnScale.y = (2.0f * rescaleFactor1) + 0.01f;
            Actor_SetScale(&this->actor, 1.5f * rescaleFactor1);
            this->respawnRotY = ((23 - this->timer) * 7281.778f) + 10922.667f;
            this->actor.shape.rot.y = (28 - this->timer) * (f32)0x1000;
        } else {
            Actor_SetScale(&this->actor, (((28 - this->timer) * 0.1f) + 1.0f) * 0.01f);
            Math_Vec3f_Copy(&this->respawnScale, &gZeroVec3f);
            this->actor.shape.rot.y = (28 - this->timer) * (f32)0x1000;
        }

        if (this->timer == 21) {
            this->collider.base.ocFlags1 |= OC1_ON;
        }

        this->respawnRotY += this->actor.home.rot.y;
        this->actor.shape.rot.y += this->actor.home.rot.y;
    }
}

/**
 * Check actor AC hit since last update. If hit, initialize appropriate action cycle.
 */
void EnSlime_CheckACHit(EnSlime* this, PlayState* play) {
    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;

        if ((this->damageEffectType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) ||
            !(this->collider.info.acHitInfo->toucher.dmgFlags & 0xDB0B3)) {

            EnSlime_UpdateIceEffects(this, play);
            if ((this->actor.params == EN_SLIME_TYPE_BLUE) &&
                (this->actor.colChkInfo.damageEffect == ENSLIME_DMGTYPE_ICEARROW)) {
                // Blue chuchus take no damage from ice arrows.
                this->actor.colChkInfo.damage = 0;
            }

            if (Actor_ApplyDamage(&this->actor) == 0) {
                Actor_SetDropFlag(&this->actor, &this->collider.info);
                Enemy_StartFinishingBlow(play, &this->actor);
                this->actor.flags &= ~ACTOR_FLAG_1;
            }

            if (this->actor.colChkInfo.damageEffect == ENSLIME_DMGTYPE_BLUNT) {
                EnSlime_ReactToBluntHit(this);
            } else if (this->actor.colChkInfo.damageEffect == ENSLIME_DMGTYPE_STUN) {
                this->timer = 40;
                Actor_SetColorFilter(&this->actor, 0, 255, 0x2000, 40);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
                EnSlime_EnterStunnedState(this);
            } else if (this->actor.colChkInfo.damageEffect != ENSLIME_DMGTYPE_HOOKSHOT) {
                if (this->actor.colChkInfo.damageEffect == ENSLIME_DMGTYPE_ICEARROW) {
                    if (this->actor.params == EN_SLIME_TYPE_BLUE) {
                        EnSlime_InitIceBlock(this);
                    } else {
                        EnSlime_InitIceStun(this);
                        if (this->actor.colChkInfo.health == 0) {
                            this->timer = 3;
                            this->collider.base.acFlags &= ~AC_ON;
                        }
                        EnSlime_EnterStunnedState(this);
                    }
                } else {
                    if (this->actor.colChkInfo.damageEffect == ENSLIME_DMGTYPE_LIGHT) {
                        this->effectAlpha = 4.0f;
                        this->effectScale = 0.4f;
                        this->damageEffectType = ACTOR_DRAW_DMGEFF_LIGHT_ORBS;
                        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, this->collider.info.bumper.hitPos.x,
                                    this->collider.info.bumper.hitPos.y, this->collider.info.bumper.hitPos.z, 0, 0, 0,
                                    4);
                    } else if (this->actor.colChkInfo.damageEffect == ENSLIME_DMGTYPE_ELECTRIC) {
                        this->damageEffectType = ACTOR_DRAW_DMGEFF_ELECTRIC_SPARKS_LARGE;
                        this->effectAlpha = 4.0f;
                        this->effectScale = 0.4f;
                    }
                    EnSlime_ReactToDamage(this, play, true);
                }
            }
        }
    }
}

void EnSlime_Update(Actor* thisx, PlayState* play) {
    EnSlime* this = THIS;
    s32 pad;
    Player* player = GET_PLAYER(play);

    EnSlime_CheckACHit(this, play);
    this->actionFunc(this, play);

    // Note: Does not match if you use this->actor instead of thisx (iirc this is true for the whole function for some
    // reason)
    thisx->shape.shadowAlpha = this->iceBlockTimer;
    if (this->iceBlockTimer == 255) {
        if (thisx->scale.y > 0.0001f) {
            thisx->targetArrowOffset = 60.0f / thisx->scale.y;
        }

        if (this->collider.base.ocFlags1 & OC1_ON) {
            Actor_MoveWithGravity(thisx);
            Actor_UpdateBgCheckInfo(play, thisx, 20.0f, 35.0f, 40.0f, 0x1D);
        }

        Collider_UpdateCylinder(thisx, &this->collider);
        this->collider.dim.radius = sCylinderInit.dim.radius * (100.0f * thisx->scale.z);
        this->collider.dim.height = sCylinderInit.dim.height * (100.0f * thisx->scale.y);

        if (this->actionFunc == EnSlime_UpdateJump) {
            CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.base);
        }

        if (this->collider.base.acFlags & AC_ON) {
            CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
        }

        if (player->stateFlags3 & PLAYER_STATE3_100) {
            this->collider.base.ocFlags1 &= ~OC1_TYPE_PLAYER;
        } else {
            this->collider.base.ocFlags1 |= OC1_TYPE_PLAYER;
        }

        if (this->collider.base.ocFlags1 & OC1_ON) {
            CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
        }

        Actor_SetFocus(thisx, 15.0f);
        if (this->effectAlpha > 0.0f) {
            if (this->damageEffectType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
                Math_StepToF(&this->effectAlpha, 0.0f, 0.05f);
                this->effectScale = (this->effectAlpha + 1.0f) * 0.2f;
                this->effectScale = CLAMP_MAX(this->effectScale, 0.4f);
            } else if (Math_StepToF(&this->frozenSteamScale, 0.4f, 0.01f) == 0) {
                func_800B9010(thisx, NA_SE_EV_ICE_FREEZE - SFX_FLAG);
            }
        }
    }
}

void EnSlime_Draw(Actor* thisx, PlayState* play) {
    s32 i;
    EnSlime* this = THIS;
    Vec3f wobbleScale;
    Color_RGBA8* primColor;
    Color_RGBA8* envColor;
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C28C(play->state.gfxCtx);
    func_8012C2DC(play->state.gfxCtx);
    func_800B8118(&this->actor, play, 0);
    if (this->iceBlockTimer != 255) {
        gSPSegment(POLY_XLU_DISP++, 10, D_801AEFA0);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 170, 255, 255, 255, 255);
        gDPSetEnvColor(POLY_XLU_DISP++, 150, 255, 255, this->iceBlockTimer);
    } else {
        primColor = &sPrimColors[this->actor.params];
        envColor = &sEnvColors[this->actor.params];
        AnimatedMat_Draw(play, sSlimeAnimTex);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 100, primColor->r, primColor->g, primColor->b, primColor->a);
        gDPSetEnvColor(POLY_XLU_DISP++, envColor->r, envColor->g, envColor->b, 255);
    }

    if (this->actionFunc == EnSlime_UpdateDamageReaction) {
        wobbleScale.x = 1.0f - (sin_rad((f32)this->timer * (M_PI / 2.0f)) * 0.3f);
        wobbleScale.y = (sin_rad((f32)this->timer * (M_PI / 2.0f)) * 0.3f) + 1.0f;
        wobbleScale.z = 1.0f - (cos_rad((f32)this->timer * (M_PI / 2.0f)) * 0.3f);

        Matrix_RotateXFApply(this->wobbleRot.x);
        Matrix_RotateZF(this->wobbleRot.z, MTXMODE_APPLY);
        Matrix_Scale(wobbleScale.x, wobbleScale.y, wobbleScale.z, MTXMODE_APPLY);
        Matrix_RotateZF(-this->wobbleRot.z, MTXMODE_APPLY);
        Matrix_RotateXFApply(-this->wobbleRot.x);
    }

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, gChuchuBodyDL);

    if (this->iceBlockTimer == 255) {
        // Ice block is not active
        Scene_SetRenderModeXlu(play, 0, 1);

        gSPSegment(POLY_OPA_DISP++, 9, (u32)sEyeTextures[this->eyeTexIndex]);
        gDPSetEnvColor(POLY_OPA_DISP++, 0, 30, 70, 255);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, gChuchuEyesDL);

    } else {
        Scene_SetRenderModeXlu(play, 1, 2);
        gSPSegment(POLY_XLU_DISP++, 9, (u32)sEyeTextures[this->eyeTexIndex]);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gChuchuEyesDL);
    }

    for (i = 0; i < 5; i++) {
        Matrix_MultVec3f(&sLimbPosMultipliers[i], &this->limbPos[i]);
    }

    if (this->actionFunc == EnSlime_UpdateRespawn) {
        Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
        Matrix_RotateYS(this->respawnRotY, MTXMODE_APPLY);
        Matrix_Scale(this->respawnScale.x, this->respawnScale.y, this->respawnScale.z, MTXMODE_APPLY);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gChuchuPuddleDL);
    }

    if ((this->actor.params != EN_SLIME_TYPE_BLUE) && (this->actor.scale.x > 0.0f)) {
        POLY_OPA_DISP = Play_SetFog(play, POLY_OPA_DISP);
        POLY_OPA_DISP = func_8012C724(POLY_OPA_DISP);

        Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y + (2000.0f * this->actor.scale.y),
                         this->actor.world.pos.z, MTXMODE_NEW);
        Matrix_Scale(0.03f, 0.03f, 0.03f, MTXMODE_APPLY);

        gSPSegment(POLY_OPA_DISP++, 8, (u32)this->dropObjectTex);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, gItemDropDL);
    }

    Actor_DrawDamageEffects(play, &this->actor, this->limbPos, EN_SLIME_LIMBPOS_COUNT, this->effectScale,
                            this->frozenSteamScale, this->effectAlpha, this->damageEffectType);

    CLOSE_DISPS(play->state.gfxCtx);
}
