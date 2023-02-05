/*
 * File: z_en_slime.c
 * Overlay: ovl_En_Slime
 * Description: Chuchu
 */

#include "z_en_slime.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_200)

#define THIS ((EnSlime*)thisx)

typedef enum EnSlimeDamageType {
    /* 00 */ EnSlime_DmgType_Normal,
    /* 01 */ EnSlime_DmgType_Stun,
    /* 03 */ EnSlime_DmgType_IceArrow = 3,
    /* 04 */ EnSlime_DmgType_Light,
    /* 05 */ EnSlime_DmgType_Electric,
    /* 14 */ EnSlime_DmgType_Hookshot = 14,
    /* 15 */ EnSlime_DmgType_BluntHit = 15,
} EnSlimeDamageType;

void EnSlime_Init(Actor* thisx, PlayState* play);
void EnSlime_Destroy(Actor* thisx, PlayState* play);
void EnSlime_Update(Actor* thisx, PlayState* play);
void EnSlime_Draw(Actor* thisx, PlayState* play);

void func_80A2EFAC(EnSlime* this);
void EnSlime_UpdateIceEffects(EnSlime* this, PlayState* play);
void func_80A2F0A8(EnSlime* this); 

void EnSlime_InitBehavior(EnSlime* this);
void EnSlime_InitializeIdle(EnSlime* this, PlayState* play); //Default action func
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
void func_80A2FD94(EnSlime* this);
void func_80A2FE38(EnSlime* this, PlayState* play);
void EnSlime_ReactToDamage(EnSlime* this, PlayState* play, s32 arg2);
void EnSlime_UpdateDamageReaction(EnSlime* this, PlayState* play); //Action func
void EnSlime_InitializeDeath(EnSlime* this);
void EnSlime_Expire(EnSlime* this, PlayState* play);
f32 func_80A3072C(f32, f32);
void func_80A30778(EnSlime* this);
void func_80A30820(EnSlime* this, PlayState* play);
void func_80A30924(EnSlime* this);
void func_80A309C8(EnSlime* this);
void func_80A30944(EnSlime* this, PlayState* play);
void func_80A30A20(EnSlime* this, PlayState* play);
void func_80A30A90(EnSlime* this);
void func_80A30AE4(EnSlime* this, PlayState* play);
void EnSlime_HideDead(EnSlime* this);
void EnSlime_CountdownRespawn(EnSlime* this, PlayState* play);
void EnSlime_BeginRespawn(EnSlime* this);
void EnSlime_UpdateRespawn(EnSlime* this, PlayState* play); //Action func
void EnSlime_CheckACHit(EnSlime* this, PlayState* play);

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
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
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

static void* D_80A31B44[] = {gChuchuEyeOpenTex, gChuchuEyeHalfTex, gChuchuEyeClosedTex, gChuchuEyeHalfTex};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(gravity, -2, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 6000, ICHAIN_STOP),
};

static s32 sVirtualAddrInit = false;

static Color_RGBA8 sBubblePrimColor = { 0xff, 0xff, 0xff, 0xff }; //80A31B60
static Color_RGBA8 sBubbleEnvColor = { 0x96, 0x96, 0x96, 0x00 }; // 80A31B64
static Vec3f sBubbleAccel = {0.0, -0.8, 0.0}; //80A31B68

//80A31B74
static Color_RGBA8 sPrimColors[] = {
    { 0xff, 0xff, 0xff, 0xff }, 
    { 0xff, 0xff, 0x00, 0xff }, 
    { 0xff, 0xff, 0xc8, 0xff }, 
    { 0xe1, 0xc8, 0xff, 0xff },
};

//80A31B84
static Color_RGBA8 sEnvColors[] = {
    { 0x8c, 0xff, 0xc3, 0xff }, 
    { 0x32, 0xff, 0x00, 0xff }, 
    { 0xff, 0xb4, 0x00, 0xff }, 
    { 0xff, 0x32, 0x9b, 0xff },
};

static Vec3f D_80A31B94[] = {
    { 2000.0, 2000.0, 0.0 },
    { -1500.0, 2500.0, -500.0 },
    { -500.0, 1000.0, 2500.0 },
    { 0.0, 4000.0, 0.0 },    
    { 0.0, 2000.0, -2000.0 },
};

static void* D_80A32200; //.bss

void EnSlime_Init(Actor* thisx, PlayState* play) {
    s32 actorParamsHi;
    s32 i;
    EnSlime* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 38.0f);

    this->alpha = 0xFF;
    this->unk149 = 0;
    this->unk154.y = 0.0f;

    if (this->actor.shape.rot.x <= 0) {
        this->distLimit = 30000.0f;
    } else {
        this->distLimit = (f32)this->actor.shape.rot.x * 40.0f;
    }

    this->actor.shape.rot.x = 0;
    actorParamsHi = (this->actor.params >> 8) & 0xFF;
    this->actor.shape.rot.z = 0;
    this->actor.params = this->actor.params & 0xFF;
    if (actorParamsHi == 0xFF) {
        actorParamsHi = 0;
    }

    //Upper byte of actorParams at init is # of seconds past 10s to respawn.
    this->respawnTime = (actorParamsHi * 20) + 200;

    if (!sVirtualAddrInit) {
        for (i = 0; i < 4; i++) {
            D_80A31B44[i] = Lib_SegmentedToVirtual(D_80A31B44[i]);
        }
        D_80A32200 = Lib_SegmentedToVirtual(gChuchuSlimeFlowTexAnim);
        sVirtualAddrInit = true;
    }

    if (this->actor.params == EN_SLIME_TYPE_YELLOW) {
        this->dropObjectTex = Lib_SegmentedToVirtual(gDropArrows1Tex);
        this->actor.hintId = TATL_HINT_ID_YELLOW_CHUCHU;
    } else if (this->actor.params == EN_SLIME_TYPE_GREEN) {
        this->dropObjectTex = Lib_SegmentedToVirtual(gDropMagicSmallTex);
        this->actor.hintId = TATL_HINT_ID_GREEN_CHUCHU;
    } else if (this->actor.params == EN_SLIME_TYPE_RED) {
        this->dropObjectTex = Lib_SegmentedToVirtual(gDropRecoveryHeartTex);
        this->actor.hintId = TATL_HINT_ID_RED_CHUCHU;
    } else {
        this->actor.hintId = TATL_HINT_ID_BLUE_CHUCHU;
    }

    EnSlime_InitBehavior(this);
}

void EnSlime_Destroy(Actor* thisx, PlayState* play) {
    EnSlime* this = THIS;
    Collider_DestroyCylinder(play, &this->collider);
}

//80A2EFAC - Update func
void func_80A2EFAC(EnSlime* this) {
    this->damageEffectType = ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX;
    this->effectScale = 0.4f;
    this->collider.base.colType = COLTYPE_HIT3;
    this->frozenSteamScale = 0.6f;
    this->effectAlpha = 1.0f;
    this->timer = 0x50;
    this->actor.flags &= ~0x400;
    Actor_SetColorFilter(&this->actor, 0x4000, 0xFF, 0x2000, 0x50);
}

//80A2F028 - Update func
void EnSlime_UpdateIceEffects(EnSlime* this, PlayState* play) {
    if (this->damageEffectType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
        this->damageEffectType = 0;
        this->collider.base.colType = COLTYPE_NONE;
        this->effectAlpha = 0.0f;
        Actor_SpawnIceEffects(play, &this->actor, this->limbPos, EN_SLIME_LIMBPOS_COUNT, 2, 0.2f, 0.2f);
        this->actor.flags |= 0x200;
    }
}

//80A2F0A8 - Called by action funcs
void func_80A2F0A8(EnSlime* this) {
    if (this->unk149 != 0) {
        if (++this->unk149 == 4) {
            this->unk149 = 0;
        }
    } else if (Rand_ZeroOne() < 0.05f) {
        this->unk149 = 1;
    }
}

//80A2F110 - Called at end of init
void EnSlime_InitBehavior(EnSlime* this) {
    this->actor.scale.x = 0.008f;
    this->actor.scale.z = 0.008f;
    this->actor.scale.y = 0.011f;
    this->actionFunc = EnSlime_InitializeIdle;
}

//80A2F140 - Initial action function
void EnSlime_InitializeIdle(EnSlime* this, PlayState* play) {
    if (this->actor.bgCheckFlags & BGCHECK_CHECK_WALL) {
        this->actor.flags &= ~0x10;
        EnSlime_ReturnToIdle(this);
    }
}

//80A2F180 - Called by 80A2F140 (action func). Seems to reset default idle state?
void EnSlime_ReturnToIdle(EnSlime* this) {
    this->timer = 25;
    this->actionFunc = EnSlime_SitIdle;
    this->actor.speedXZ = 0.0f;
}

//80A2F1A4 - Action function set by initial action function. Checks if it notices player.
void EnSlime_SitIdle(EnSlime* this, PlayState* play) {
    f32 sqrtFactor;
    f32 sinFactor;

    this->timer--;
    sqrtFactor = sqrtf((f32)this->timer) * 0.2f;
    func_80A2F0A8(this);

    sinFactor = ((sin_rad(this->timer * 1.2566371f) * (0.13f * sqrtFactor)) + 1.0f) * 0.01f;
    this->actor.scale.x = sinFactor;
    this->actor.scale.z = sinFactor;
    if (this->timer < 24) {
        this->actor.scale.y = ((cos_rad(this->timer * 1.2566371f) * (0.05f * sqrtFactor)) + 1.0f) * 0.01f;
    }

    this->actor.shape.rot.x = randPlusMinusPoint5Scaled(512.0f) * sqrtFactor;
    this->actor.shape.rot.z = randPlusMinusPoint5Scaled(512.0f) * sqrtFactor;
    if ((Player_GetMask(play) != PLAYER_MASK_STONE) && (this->actor.xzDistToPlayer < 280.0f) &&
        Actor_IsFacingPlayer(&this->actor, 0x5000)) {
        EnSlime_EngagePlayer(this);
    } else if (this->timer == 0) {
        EnSlime_ChangeDirectionIdle(this);
    }
}

// 80A2F354 - Called by action func when chuchu is idle and timer is zero
void EnSlime_ChangeDirectionIdle(EnSlime* this) {
    this->timer = 0x78;
    if (Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos) > 120.0f) {
        this->idleRotY = Actor_YawToPoint(&this->actor, &this->actor.home.pos);
    } else if (Rand_ZeroOne() < 0.7f) {
        this->idleRotY = (s32)randPlusMinusPoint5Scaled(16384.0f) + this->actor.shape.rot.y;
    }
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = EnSlime_MoveInDirectionIdle;
}

//80A2F418 - Action function. Set when chuchu is idle and timer is zero
void EnSlime_MoveInDirectionIdle(EnSlime* this, PlayState* play) {
    f32 sinFactor;

    func_80A2F0A8(this);
    this->timer--;
    Math_ApproachS(&this->actor.shape.rot.y, this->idleRotY, 4, 0x100);
    if (this->actor.bgCheckFlags & 8) {
        this->idleRotY = this->actor.wallYaw;
    } else {
        if (Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos) > 120.0f) {
            this->idleRotY = Actor_YawToPoint(&this->actor, &this->actor.home.pos);
        }
    }
    sinFactor = fabsf(sin_rad((f32)this->timer * 0.1308997f));
    Math_StepToF(&this->actor.scale.z, ((0.15f * sinFactor) + 1.0f) * 0.01f, 0.0002f);
    Math_StepToF(&this->actor.scale.x, (1.0f - (0.2f * sinFactor)) * 0.01f, 0.0002f);
    Math_StepToF(&this->actor.scale.y, (1.0f - (0.1f * sinFactor)) * 0.01f, 0.0002f);

    this->actor.speedXZ = (0.8f * sinFactor) + 0.2f;
    this->actor.shape.rot.x = (s16)(2048.0f * sinFactor);
    this->actor.world.rot.y = this->actor.shape.rot.y;

    if (this->distLimit < Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos)) {
        EnSlime_ReturnHome(this);
    } else if ((Player_GetMask(play) != PLAYER_MASK_STONE) && (this->actor.xzDistToPlayer < 280.0f) &&
               (Actor_IsFacingPlayer(&this->actor, 0x5000))) {
        EnSlime_EngagePlayer(this);
    } else if (this->timer == 0) {
        EnSlime_ReturnToIdle(this);
    }
}

//80A2F684 - Called by action func 80A2FBA0
void EnSlime_ReturnHome(EnSlime* this) {
    this->timer = 0x18;
    this->idleRotY = Actor_YawToPoint(&this->actor, &this->actor.home.pos);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = EnSlime_MoveToHome;
}

//EnSlime_MoveToHome - Action func for wobbling home
void EnSlime_MoveToHome(EnSlime* this, PlayState* play) {
    f32 sinFactor;

    func_80A2F0A8(this);
    this->timer--;
    Math_ApproachS(&this->actor.shape.rot.y, this->idleRotY, 4, 0x400);
    if (this->actor.bgCheckFlags & BGCHECK_CHECK_ONE_FACE) {
        this->idleRotY = this->actor.wallYaw;
    } else {
        this->idleRotY = Actor_YawToPoint(&this->actor, &this->actor.home.pos);
    }

    sinFactor = fabsf(sin_rad((f32)this->timer * 0.1308997f));
    Math_StepToF(&this->actor.scale.z, ((0.15f * sinFactor) + 1.0f) * 0.01f, 0.0002f);
    Math_StepToF(&this->actor.scale.x, (1.0f - (0.2f * sinFactor)) * 0.01f, 0.0002f);
    Math_StepToF(&this->actor.scale.y, (1.0f - (0.1f * sinFactor)) * 0.01f, 0.0002f);

    this->actor.speedXZ = (0.8f * sinFactor) + 0.2f;
    this->actor.shape.rot.x = (s16)(s32)(2048.0f * sinFactor);
    this->actor.world.rot.y = this->actor.shape.rot.y;

    if (this->timer == 0) {
        this->timer = 24;
    }
    if (Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos) < (this->distLimit * 0.8f)) {
        EnSlime_ReturnToIdle(this);
    }
}

//80A2F8B4 - Called by action func 80A2F1A4/80A2FBA0 if chuchu decides to engage/continue engaging player on action cycle
void EnSlime_EngagePlayer(EnSlime* this) {
    this->actor.shape.rot.x = 0;
    this->actor.shape.rot.z = 0;
    this->timer = 8;
    this->actionFunc = EnSlime_TurnToPlayer;
    this->actor.speedXZ = 0.0f;
}

//80A2F8E0 - Action function when chuchu is engaged with player
void EnSlime_TurnToPlayer(EnSlime* this, PlayState* play) {
    f32 factorY;
    f32 factorXZ;

    this->timer--;
    func_80A2F0A8(this);
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 4, 0x1000);
    if (this->timer >= 0) {
        factorY = (f32)(8 - this->timer);
        factorXZ = ((factorY * 0.04f) + 1.0f) * 0.01f;
        this->actor.scale.x = factorXZ;
        this->actor.scale.y = (1.0f - (factorY * 0.05f)) * 0.01f;
        this->actor.scale.z = factorXZ;
    }
    if (this->timer < -2) {
        EnSlime_JumpAtPlayer(this);
    }
}

//80A2F9A0 - Called by action func 80A2F8E0
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
    this->unk149 = 0;
    Math_StepToF(&this->actor.scale.x, 0.008f, 0.0025f);
    Math_StepToF(&this->actor.scale.y, 0.011f, 0.0025f);
    this->actor.scale.z = this->actor.scale.x;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_SLIME_JUMP);
    this->actionFunc = EnSlime_UpdateJump;
}

//80A2FA88 - Action function (engaged with player)
void EnSlime_UpdateJump(EnSlime* this, PlayState* play) {
    this->timer--;
    if (this->collider.base.atFlags & AT_HIT) {
        //Knockback if hit?
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

//80A2FB60 - Called by action func 80A2FA88
void EnSlime_FinishJump(EnSlime* this) {
    this->timer = 15;
    this->actor.scale.x = 0.0132f;
    this->actor.scale.y = 0.0074399994f;
    this->actor.scale.z = 0.0132f;
    this->actionFunc = EnSlime_UpdateJumpLanding;
    this->actor.speedXZ = 0.0f;
}

//80A2FBA0 - Action function (engaged with player)
void EnSlime_UpdateJumpLanding(EnSlime* this, PlayState* play) {
    f32 factorScaleY;
    f32 factorRotXZ;
    f32 factorScaleXZ;

    func_80A2F0A8(this);
    this->timer--;
    factorScaleY = ((this->timer / 5) + 1) * 1.6f;
    factorRotXZ = sqrtf(this->timer) * 0.2f;
    factorScaleXZ = ((cos_rad(this->timer * 1.2566371f) * (0.05f * factorScaleY)) + 1.0f) * 0.01f;
    this->actor.scale.x = factorScaleXZ;
    this->actor.scale.z = factorScaleXZ;
    if (this->timer < 15) {
        this->actor.scale.y = (1.0f - (sin_rad((f32)this->timer * 1.2566371f) * (0.04f * factorScaleY))) * 0.01f;
    }
    this->actor.shape.rot.x = (s16)(s32)(randPlusMinusPoint5Scaled(512.0f) * factorRotXZ);
    this->actor.shape.rot.z = (s16)(s32)(randPlusMinusPoint5Scaled(512.0f) * factorRotXZ);
    if (Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos) > this->distLimit) {
        EnSlime_ReturnHome(this);
    } else if ((Player_GetMask(play) != PLAYER_MASK_STONE) && (this->actor.xzDistToPlayer < 280.0f) &&
               (this->timer < 12)) {
        EnSlime_EngagePlayer(this);
    }
    else if (this->timer == 0) {
        EnSlime_ReturnToIdle(this);
    }
}

//80A2FD94 - Update func
void func_80A2FD94(EnSlime* this) {
    this->actor.speedXZ = 10.0f;
    if (this->actor.velocity.y > 0.0f) {
        this->actor.velocity.y = 0.0f;
    }
    this->collider.base.acFlags &= ~1;
    this->timer = 30;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_SLIME_DEFENCE);
    if (this->collider.base.ac != NULL) {
        this->actor.world.rot.y = Actor_YawBetweenActors(&this->actor, this->collider.base.ac) + 0x8000;
    } else {
        this->actor.world.rot.y = this->actor.yawTowardsPlayer + 0x8000;
    }
    this->actionFunc = func_80A2FE38;
}

//80A2FE38 - Action func
void func_80A2FE38(EnSlime* this, PlayState* play) {
    f32 sp24;
    f32 temp_fv1_2;

    func_80A2F0A8(this);
    this->timer--;
    Math_StepToF(&this->actor.speedXZ, 0.0f, 1.0f);
    sp24 = sqrtf(this->timer);
    if (this->timer < 0x1E) {
        temp_fv1_2 = ((cos_rad(this->timer * 1.2566371f) * (0.08f * sp24)) + 1.0f) * 0.01f;
        this->actor.scale.x = temp_fv1_2;
        this->actor.scale.z = temp_fv1_2;
    }
    if (this->timer == 0xF) {
        this->collider.base.acFlags |= 1;
    }
    this->actor.scale.y = ((sin_rad((f32)this->timer * 1.2566371f) * (0.07f * sp24)) + 1.0f) * 0.01f;
    this->actor.shape.rot.x = (s16)(s32)(randPlusMinusPoint5Scaled(512.0f) * sp24);
    this->actor.shape.rot.z = (s16)(s32)(randPlusMinusPoint5Scaled(512.0f) * sp24);
    if (this->timer == 0) {
        if (this->distLimit < Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos)) {
            EnSlime_ReturnHome(this);
        } else if ((this->actor.xzDistToPlayer < 280.0f) && (Player_GetMask(play) != PLAYER_MASK_STONE)) {
            EnSlime_EngagePlayer(this);
        } else
            EnSlime_ReturnToIdle(this);
    }
}

//80A30018 - Action/Update func
void EnSlime_ReactToDamage(EnSlime* this, PlayState* play, s32 arg2) {
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
    Actor_SetColorFilter(&this->actor, 0x4000, 0xFF, 0x2000, 0x14);
    this->timer = 20;
    this->actor.speedXZ = 10.0f;
    if (arg2 == 1) {
        func_800BE504(&this->actor, &this->collider);
    }

    this->unk149 = 0;
    Actor_SetScale(&this->actor, 0.01f);
    this->unk154.x = Rand_ZeroOne() * 6.2831855f;
    this->unk154.z = Rand_ZeroOne() * 6.2831855f;
    ySin = Math_SinS(this->actor.world.rot.y) * 10.0f;
    yCos = Math_CosS(this->actor.world.rot.y) * 10.0f;
    effectPos.x = this->actor.world.pos.x + ySin;
    effectPos.y = this->actor.world.pos.y + 20.0f;
    effectPos.z = this->actor.world.pos.z + yCos;
    EffectSsGSplash_Spawn(play, &effectPos, NULL, NULL, 1, 0x226);

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
                                          &sBubbleEnvColor, Rand_S16Offset(0x28, 0x14), 0x14, 0);
    }

    if (this->actor.colChkInfo.health == 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_SLIME_DEAD);
    } else {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_SLIME_DAMAGE);
    }
    this->actionFunc = EnSlime_UpdateDamageReaction;
}

//80A30344 - Action func, set by 80A30018. Some kind of damage checker. Wobble or slide back on damage reception?
void EnSlime_UpdateDamageReaction(EnSlime* this, PlayState* play) {
    this->timer--;
    Math_StepToF(&this->actor.speedXZ, 0.0f, 1.0f);
    if ((this->timer % 5) == 0) {
        this->unk154.x = Rand_ZeroOne() * 6.2831855f;
        this->unk154.z = Rand_ZeroOne() * 6.2831855f;
    }
    if (this->timer == 0) {
        if (this->actor.colChkInfo.health != 0) {
            this->collider.base.acFlags |= AC_ON;
            if ((this->actor.xzDistToPlayer < 280.0f) && (Player_GetMask(play) != PLAYER_MASK_STONE)) {
                EnSlime_EngagePlayer(this);
            }
            else EnSlime_ReturnToIdle(this);
        } else {
            SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, 0x28U, NA_SE_EN_SLIME_BREAK);
            EnSlime_InitializeDeath(this);
        }
    }
}

//80A30454 - Called by action func 80A30344
void EnSlime_InitializeDeath(EnSlime* this) {
    this->collider.base.acFlags &= ~AC_ON;
    if (this->actor.velocity.y > 0.0f) {
        this->actor.velocity.y = 0.0f;
    }
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = EnSlime_Expire;
    this->actor.speedXZ = 0.0f;
}

//80A304B8 - Action func, set by 80A30454 (probably part of death sequence)
void EnSlime_Expire(EnSlime* this, PlayState* play) {
    s32 i;
    Vec3f velocity;
    Vec3f effectPos;

    f32 random;
    s32 factor;

    if (Math_StepToF(&this->actor.scale.x, 0.0f, 0.002f) != 0) {
        effectPos.x = this->actor.world.pos.x;
        effectPos.y = this->actor.world.pos.y + 20.0f;
        effectPos.z = this->actor.world.pos.z;
        EffectSsGSplash_Spawn(play, &effectPos, NULL, NULL, 1, 0x320);

        for (i = 0; i < 15; i++) {
            random = Rand_ZeroOne();

            if (Rand_ZeroOne() < 0.5f)
                factor = -1;
            else
                factor = 1;
            velocity.x = factor * ((random * 2.5f) + 2.0f);

            random = Rand_ZeroOne();
            if (Rand_ZeroOne() < 0.5f)
                factor = -1;
            else
                factor = 1;
            velocity.z = factor * ((random * 2.5f) + 2.0f);

            velocity.y = (Rand_ZeroOne() * 6.0f) + 2.0f;
            EffectSsDtBubble_SpawnCustomColor(play, &effectPos, &velocity, &sBubbleAccel, &sBubblePrimColor,
                                              &sBubbleEnvColor, Rand_S16Offset(0x28, 0x14), 0x14, 0);
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

//80A3072C - Update func
f32 func_80A3072C(f32 arg0, f32 arg1) {
    s32 temp = (s32)(arg0 - arg1);

    if (temp > 0) {
        temp = temp + 0x1E;
    } else {
        temp = temp - 0x1E;
    }
    return ((f32)(temp / 60) * 60.0f) + arg1;
}

//80A30778 - Update func
void func_80A30778(EnSlime* this) {
    this->collider.base.acFlags &= ~AC_ON;
    this->actor.flags &= ~1;
    this->effectAlpha = 0.0f;
    this->actor.speedXZ = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->actor.gravity = 0.0f;
    this->unk154.x = func_80A3072C(this->actor.world.pos.x, this->actor.home.pos.x);
    this->unk154.z = func_80A3072C(this->actor.world.pos.z, this->actor.home.pos.z);
    Actor_SetColorFilter(&this->actor, 0x8000, 0x80FF, 0x2000, 10);
    this->unk149 = 0;
    this->alpha = 0xFE;
    this->actionFunc = func_80A30820;
}

//80A30820 - action func, set by 80A30778
void func_80A30820(EnSlime* this, PlayState* play) {
    s32 temp;

    temp = Math_StepToF(&this->actor.world.pos.x, this->unk154.x, 10.0f);
    temp &= Math_StepToF(&this->actor.world.pos.z, this->unk154.z, 10.0f);

    this->actor.colorFilterTimer = 0xA;
    if (temp) {
        this->actor.child =
            Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_OBJ_ICEBLOCK, this->actor.world.pos.x,
                                               this->actor.world.pos.y + 30.0f, this->actor.world.pos.z, 0, 0, 0, 0);
        if (this->actor.child != NULL) {
            this->actor.child->cutscene = this->actor.cutscene;
            func_80A30924(this);
        } else {
            this->actor.colorFilterTimer = 0;
            this->collider.base.acFlags |= 1;
            this->alpha = 0xFF;
            this->actor.flags |= 1;
            this->actor.gravity = -2.0f;
            EnSlime_ReturnToIdle(this);
        }
    }
}

//80A30924 - Called by action func 80A30820
void func_80A30924(EnSlime* this) {
    this->actor.flags |= 0x10;
    this->actionFunc = func_80A30944;
}

//80A30944 - Action func, set by 80A30924
void func_80A30944(EnSlime* this, PlayState* play) {
    if (this->alpha == 0) {
        if ((this->actor.child == NULL) || (this->actor.child->update == NULL) ||
            !(this->actor.child->scale.y >= 0.1f)) {
            func_80A30A90(this);
        }
    } else {
        this->actor.colorFilterTimer = 0xA;
        if (this->alpha - 5 < 0) {
            this->alpha = 0;
        } else
            this->alpha -= 5;
    }
}

//80A309C8 - Update func
void func_80A309C8(EnSlime* this) {
    this->actor.speedXZ = 0.0f;
    func_800BE504(&this->actor, &this->collider);
    if (this->actor.velocity.y > 0.0f) {
        this->actor.velocity.y = 0.0f;
    }
    this->actionFunc = func_80A30A20;
}

//80A30A20 - Action func, set by 80A309C8
void func_80A30A20(EnSlime* this, PlayState* play) {
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

//80A30A90 - Called by action func 80A30944
void func_80A30A90(EnSlime* this) {
    this->actor.colorFilterTimer = 0;
    this->actor.gravity = -2.0f;
    Actor_SetColorFilter(&this->actor, 0x8000U, 0x80FFU, 0x2000U, 0xA);
    this->actionFunc = func_80A30AE4;
}

//80A30AE4 - Action func, set by 80A30A90
void func_80A30AE4(EnSlime* this, PlayState* play) {
    s32 temp;

    this->actor.colorFilterTimer = 0xA;
    if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
        temp = (0.1f - this->actor.child->scale.y) * 10.0f * 255.0f;
        this->alpha = (u8)(CLAMP(temp, 0, 0xff));
    } else {
        this->actor.child = NULL;
        temp = this->alpha + 10;
        this->alpha = (u8)(CLAMP_MAX(temp, 0xff));
    }
    if (this->alpha == 0xFF) {
        this->collider.base.acFlags |= 1;
        this->actor.flags |= 1;
        this->actor.flags &= ~0x10;
        EnSlime_ReturnToIdle(this);
    }
}

//80A30BE0 - Called by action func 80A304B8
void EnSlime_HideDead(EnSlime* this) {
    this->actor.draw = NULL;
    this->actor.flags |= 0x10;
    this->effectAlpha = 0.0f;
    this->actor.gravity = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->actor.speedXZ = 0.0f;
    this->collider.base.ocFlags1 &= ~OC1_ON;
    this->timer = this->respawnTime;
    this->actionFunc = EnSlime_CountdownRespawn;
}

//80A30C2C - Action func, set by 80A30BE0
void EnSlime_CountdownRespawn(EnSlime* this, PlayState* play) {
    if (this->timer == 0)
        EnSlime_BeginRespawn(this);
    else
        this->timer--;
}

//80A30C68 - Called by action func 80A30C2C. Respawn?
void EnSlime_BeginRespawn(EnSlime* this) {
    this->actor.draw = EnSlime_Draw;
    this->actor.colChkInfo.health = sColChkInfoInit.health;
    this->alpha = 0xFF;
    Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.home.pos);
    this->timer = 0;
    this->actor.colorFilterTimer = 0;
    this->actor.home.rot.y = this->actor.yawTowardsPlayer;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_SLIME_SURFACE);
    this->actionFunc = EnSlime_UpdateRespawn;
    this->actor.gravity = -2.0f;
}

//80A30CEC - Action func, set by 80A30C68. I think bubbling back up when respawning.
void EnSlime_UpdateRespawn(EnSlime* this, PlayState* play) {
    f32 temp_f0;
    f32 temp_f1;

    if (++this->timer == 0x1C) {
        this->actor.flags &= ~0x10;
        this->actor.flags |= 1;
        this->collider.base.acFlags |= AC_ON;
        this->actor.shape.rot.y = this->actor.home.rot.y;
        EnSlime_ChangeDirectionIdle(this);
    } else {
        if (this->timer < 0xC) {
            temp_f0 = this->timer * 0.0008333333f;
            this->respawnScale.x = temp_f0;
            this->respawnScale.z = temp_f0;
            this->respawnScale.y = 2.0f * temp_f0;
            this->respawnRotY = this->timer * 1638.4f;
        } else if (this->timer < 0x14) {
            temp_f0 = (this->timer - 0xC) * 0.000625f;
            temp_f1 = 0.01f + temp_f0;
            this->respawnScale.x = temp_f1;
            this->respawnScale.z = temp_f1;
            this->respawnScale.y = 2.0f * (0.01f - temp_f0);
            this->respawnRotY = this->timer * 1638.4f;
        } else if (this->timer < 0x18) {
            temp_f0 = (this->timer - 0x14) * 0.0033333332f;
            temp_f1 = 0.015f - temp_f0;
            this->respawnScale.x = temp_f1;
            this->respawnScale.z = temp_f1;
            this->respawnScale.y = (2.0f * temp_f0) + 0.01f;
            Actor_SetScale(&this->actor, 1.5f * temp_f0);
            this->respawnRotY = ((0x17 - this->timer) * 7281.778f) + 10922.667f;
            this->actor.shape.rot.y = (0x1C - this->timer) * 4096.0f;
        } else {
            Actor_SetScale(&this->actor, (((0x1C - this->timer) * 0.1f) + 1.0f) * 0.01f);
            Math_Vec3f_Copy(&this->respawnScale, &gZeroVec3f);
            this->actor.shape.rot.y = ((0x1C - this->timer) * 4096.0f);
        }

        if (this->timer == 0x15) {
            this->collider.base.ocFlags1 |= OC1_ON;
        }

        this->respawnRotY += this->actor.home.rot.y;
        this->actor.shape.rot.y += this->actor.home.rot.y;
    }
}

//80A30F98 - Update function called before action. Checks if AC collider hit occured in last frame, and does updates if so.
void EnSlime_CheckACHit(EnSlime* this, PlayState* play) {
    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        if ((this->damageEffectType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) ||
            !(this->collider.info.acHitInfo->toucher.dmgFlags & 0xDB0B3)) {

            EnSlime_UpdateIceEffects(this, play);
            if ((this->actor.params == EN_SLIME_TYPE_BLUE) &&
                (this->actor.colChkInfo.damageEffect == EnSlime_DmgType_IceArrow)) {
                //Blue immune to this type of damage? Ice arrows? or is that effect 1?
                this->actor.colChkInfo.damage = 0;
            }

            //Actor_ApplyDamage returns remaining health?
            if (Actor_ApplyDamage(&this->actor) == 0) {
                Actor_SetDropFlag(&this->actor, &this->collider.info);
                Enemy_StartFinishingBlow(play, &this->actor);
                this->actor.flags &= ~1;
            }

            if (this->actor.colChkInfo.damageEffect == EnSlime_DmgType_BluntHit) {
                //No idea what damage type this is
                func_80A2FD94(this);
            } else if (this->actor.colChkInfo.damageEffect == EnSlime_DmgType_Stun) {
                //Some kind of ice effect? But not ice arrow?
                this->timer = 40;
                Actor_SetColorFilter(&this->actor, 0, 0xFF, 0x2000, 40);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
                func_80A309C8(this);
            } else if (this->actor.colChkInfo.damageEffect != EnSlime_DmgType_Hookshot) {
                //No idea what damage type this is
                if (this->actor.colChkInfo.damageEffect == EnSlime_DmgType_IceArrow) {
                    if (this->actor.params == EN_SLIME_TYPE_BLUE) {
                        func_80A30778(this); //Okay, this spawns an ice block. Must be ice arrow.
                    } else {
                        func_80A2EFAC(this);
                        if (this->actor.colChkInfo.health == 0) {
                            this->timer = 3;
                            this->collider.base.acFlags &= ~AC_ON;
                        }
                        func_80A309C8(this);
                    }
                } else {
                    if (this->actor.colChkInfo.damageEffect == EnSlime_DmgType_Light) {
                        this->effectAlpha = 4.0f;
                        this->effectScale = 0.4f;
                        this->damageEffectType = ACTOR_DRAW_DMGEFF_LIGHT_ORBS;
                        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, this->collider.info.bumper.hitPos.x,
                                    this->collider.info.bumper.hitPos.y, this->collider.info.bumper.hitPos.z, 0, 0, 0, 4);
                    } else if (this->actor.colChkInfo.damageEffect == EnSlime_DmgType_Electric) {
                        this->damageEffectType = ACTOR_DRAW_DMGEFF_ELECTRIC_SPARKS_LARGE;
                        this->effectAlpha = 4.0f;
                        this->effectScale = 0.4f;
                    }
                    EnSlime_ReactToDamage(this, play, 1);
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

    //Note: Does not match if you use this->actor instead of thisx
    thisx->shape.shadowAlpha = this->alpha;
    if (this->alpha == 0xFF) {
        if (thisx->scale.y > 0.0001f) {
            thisx->targetArrowOffset = 60.0f / thisx->scale.y;
        }

        if (this->collider.base.ocFlags1 & 1) {
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
                func_800B9010(thisx, 0x20B2);
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
    if (this->alpha != 0xFF) {
        gSPSegment(POLY_XLU_DISP++, 0x0A, D_801AEFA0);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0xAA, 0xFF, 0xFF, 0xFF, 0xFF);
        gDPSetEnvColor(POLY_XLU_DISP++, 0x96, 0xFF, 0xFF, this->alpha);
    } else {
        primColor = &sPrimColors[this->actor.params];
        envColor = &sEnvColors[this->actor.params];
        AnimatedMat_Draw(play, (AnimatedMaterial*)D_80A32200);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x64, primColor->r, primColor->g, primColor->b, primColor->a);
        gDPSetEnvColor(POLY_XLU_DISP++, envColor->r, envColor->g, envColor->b, 0xFF);
    }

    if (this->actionFunc == EnSlime_UpdateDamageReaction) {
        wobbleScale.x = 1.0f - (sin_rad((f32)this->timer * 1.5707964f) * 0.3f);
        wobbleScale.y = (sin_rad((f32)this->timer * 1.5707964f) * 0.3f) + 1.0f;
        wobbleScale.z = 1.0f - (cos_rad((f32)this->timer * 1.5707964f) * 0.3f);

        Matrix_RotateXFApply(this->unk154.x);
        Matrix_RotateZF(this->unk154.z, MTXMODE_APPLY);
        Matrix_Scale(wobbleScale.x, wobbleScale.y, wobbleScale.z, MTXMODE_APPLY);
        Matrix_RotateZF(-this->unk154.z, MTXMODE_APPLY);
        Matrix_RotateXFApply(-this->unk154.x);
    }

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, gChuchuBodyDL);

    if (this->alpha == 0xFF) {
        Scene_SetRenderModeXlu(play, 0, 1U);

        gSPSegment(POLY_OPA_DISP++, 0x09, (u32)D_80A31B44[(u8)this->unk149]);
        gDPSetEnvColor(POLY_OPA_DISP++, 0x00, 0x1E, 0x46, 0xFF);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, gChuchuEyesDL);

    } else {
        Scene_SetRenderModeXlu(play, 1, 2U);
        gSPSegment(POLY_XLU_DISP++, 0x09, (u32)D_80A31B44[(u8)this->unk149]);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gChuchuEyesDL);
    }

    for (i = 0; i < 5; i++) {
        Matrix_MultVec3f(&D_80A31B94[i], &this->limbPos[i]);
    }

    if (this->actionFunc == EnSlime_UpdateRespawn) {
        Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
        Matrix_RotateYS(this->respawnRotY, MTXMODE_APPLY);
        Matrix_Scale(this->respawnScale.x, this->respawnScale.y, this->respawnScale.z, MTXMODE_APPLY);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gChuchuPuddleDL);
    }

    if ((this->actor.params != EN_SLIME_TYPE_BLUE) && (this->actor.scale.x > 0.0f)) {
        POLY_OPA_DISP = func_801660B8(play, POLY_OPA_DISP);
        POLY_OPA_DISP = func_8012C724(POLY_OPA_DISP);

        Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y + (2000.0f * this->actor.scale.y),
                         this->actor.world.pos.z, MTXMODE_NEW);
        Matrix_Scale(0.03f, 0.03f, 0.03f, MTXMODE_APPLY);

        gSPSegment(POLY_OPA_DISP++, 0x08, (u32)this->dropObjectTex);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, gItemDropDL);
    }

    Actor_DrawDamageEffects(play, &this->actor, this->limbPos, EN_SLIME_LIMBPOS_COUNT, this->effectScale, this->frozenSteamScale,
                            this->effectAlpha, this->damageEffectType);

    CLOSE_DISPS(play->state.gfxCtx);
}
