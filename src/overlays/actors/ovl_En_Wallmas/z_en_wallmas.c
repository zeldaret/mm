/*
 * File: z_en_wallmas.c
 * Overlay: ovl_En_Wallmas
 * Description: Wallmaster
 */

#include "z_en_wallmas.h"
#include "overlays/actors/ovl_En_Encount1/z_en_encount1.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_400)

#define THIS ((EnWallmas*)thisx)

void EnWallmas_Init(Actor* thisx, GlobalContext* globalCtx);
void EnWallmas_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnWallmas_Update(Actor* thisx, GlobalContext* globalCtx);
void EnWallmas_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnWallmas_TimerInit(EnWallmas* this, GlobalContext* globalCtx);
void EnWallmas_WaitToDrop(EnWallmas* this, GlobalContext* globalCtx);
void EnWallmas_SetupDrop(EnWallmas* this, GlobalContext* globalCtx);
void EnWallmas_Drop(EnWallmas* this, GlobalContext* globalCtx);
void EnWallmas_SetupLand(EnWallmas* this, GlobalContext* globalCtx);
void EnWallmas_Land(EnWallmas* this, GlobalContext* globalCtx);
void EnWallmas_SetupStand(EnWallmas* this);
void EnWallmas_Stand(EnWallmas* this, GlobalContext* globalCtx);
void EnWallmas_SetupWalk(EnWallmas* this);
void EnWallmas_Walk(EnWallmas* this, GlobalContext* globalCtx);
void EnWallmas_SetupJumpToCeiling(EnWallmas* this);
void EnWallmas_JumpToCeiling(EnWallmas* this, GlobalContext* globalCtx);
void EnWallmas_SetupReturnToCeiling(EnWallmas* this);
void EnWallmas_ReturnToCeiling(EnWallmas* this, GlobalContext* globalCtx);
void EnWallmas_Damage(EnWallmas* this, GlobalContext* globalCtx);
void EnWallmas_SetupCooldown(EnWallmas* this);
void EnWallmas_Cooldown(EnWallmas* this, GlobalContext* globalCtx);
void EnWallmas_SetupDie(EnWallmas* this, GlobalContext* globalCtx);
void EnWallmas_Die(EnWallmas* this, GlobalContext* globalCtx);
void EnWallmas_SetupTakePlayer(EnWallmas* this, GlobalContext* globalCtx);
void EnWallmas_TakePlayer(EnWallmas* this, GlobalContext* globalCtx);
void EnWallmas_ProximityOrSwitchInit(EnWallmas* this);
void EnWallmas_WaitForProximity(EnWallmas* this, GlobalContext* globalCtx);
void EnWallmas_WaitForSwitchFlag(EnWallmas* this, GlobalContext* globalCtx);
void EnWallmas_Stun(EnWallmas* this, GlobalContext* globalCtx);

const ActorInit En_Wallmas_InitVars = {
    ACTOR_EN_WALLMAS,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_WALLMASTER,
    sizeof(EnWallmas),
    (ActorFunc)EnWallmas_Init,
    (ActorFunc)EnWallmas_Destroy,
    (ActorFunc)EnWallmas_Update,
    (ActorFunc)EnWallmas_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT0,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON | BUMP_HOOKABLE,
        OCELEM_ON,
    },
    { 30, 40, 0, { 0, 0, 0 } },
};

typedef enum {
    /* 0x0 */ WALLMASTER_DMGEFF_NONE,
    /* 0x1 */ WALLMASTER_DMGEFF_STUN,
    /* 0x2 */ WALLMASTER_DMGEFF_FIRE_ARROW,
    /* 0x3 */ WALLMASTER_DMGEFF_ICE_ARROW,
    /* 0x4 */ WALLMASTER_DMGEFF_LIGHT_ARROW,
    /* 0x5 */ WALLMASTER_DMGEFF_ZORA_MAGIC,
    /* 0xF */ WALLMASTER_DMGEFF_HOOKSHOT = 0xF
} EnWallmasDamageEffect;

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, WALLMASTER_DMGEFF_STUN),
    /* Deku Stick     */ DMG_ENTRY(1, WALLMASTER_DMGEFF_NONE),
    /* Horse trample  */ DMG_ENTRY(1, WALLMASTER_DMGEFF_NONE),
    /* Explosives     */ DMG_ENTRY(1, WALLMASTER_DMGEFF_NONE),
    /* Zora boomerang */ DMG_ENTRY(1, WALLMASTER_DMGEFF_NONE),
    /* Normal arrow   */ DMG_ENTRY(1, WALLMASTER_DMGEFF_NONE),
    /* UNK_DMG_0x06   */ DMG_ENTRY(1, WALLMASTER_DMGEFF_NONE),
    /* Hookshot       */ DMG_ENTRY(0, WALLMASTER_DMGEFF_HOOKSHOT),
    /* Goron punch    */ DMG_ENTRY(1, WALLMASTER_DMGEFF_NONE),
    /* Sword          */ DMG_ENTRY(1, WALLMASTER_DMGEFF_NONE),
    /* Goron pound    */ DMG_ENTRY(1, WALLMASTER_DMGEFF_NONE),
    /* Fire arrow     */ DMG_ENTRY(2, WALLMASTER_DMGEFF_FIRE_ARROW),
    /* Ice arrow      */ DMG_ENTRY(1, WALLMASTER_DMGEFF_ICE_ARROW),
    /* Light arrow    */ DMG_ENTRY(2, WALLMASTER_DMGEFF_LIGHT_ARROW),
    /* Goron spikes   */ DMG_ENTRY(1, WALLMASTER_DMGEFF_NONE),
    /* Deku spin      */ DMG_ENTRY(0, WALLMASTER_DMGEFF_STUN),
    /* Deku bubble    */ DMG_ENTRY(1, WALLMASTER_DMGEFF_NONE),
    /* Deku launch    */ DMG_ENTRY(2, WALLMASTER_DMGEFF_NONE),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, WALLMASTER_DMGEFF_STUN),
    /* Zora barrier   */ DMG_ENTRY(0, WALLMASTER_DMGEFF_ZORA_MAGIC),
    /* Normal shield  */ DMG_ENTRY(0, WALLMASTER_DMGEFF_NONE),
    /* Light ray      */ DMG_ENTRY(0, WALLMASTER_DMGEFF_NONE),
    /* Thrown object  */ DMG_ENTRY(1, WALLMASTER_DMGEFF_NONE),
    /* Zora punch     */ DMG_ENTRY(1, WALLMASTER_DMGEFF_NONE),
    /* Spin attack    */ DMG_ENTRY(1, WALLMASTER_DMGEFF_NONE),
    /* Sword beam     */ DMG_ENTRY(0, WALLMASTER_DMGEFF_NONE),
    /* Normal Roll    */ DMG_ENTRY(0, WALLMASTER_DMGEFF_NONE),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, WALLMASTER_DMGEFF_NONE),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, WALLMASTER_DMGEFF_NONE),
    /* Unblockable    */ DMG_ENTRY(0, WALLMASTER_DMGEFF_NONE),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, WALLMASTER_DMGEFF_NONE),
    /* Powder Keg     */ DMG_ENTRY(1, WALLMASTER_DMGEFF_NONE),
};

static CollisionCheckInfoInit sColChkInfoInit = { 3, 30, 40, 150 };

static InitChainEntry sInitChain[] = {
    ICHAIN_S8(hintId, 48, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 5500, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -1500, ICHAIN_STOP),
};

static f32 sYOffsetPerForm[] = { 50.0f, 55.0f, 50.0f, 20.0f, 30.0f };

/**
 * This maps a given limb based on its limbIndex to its appropriate index
 * in the limbPos array. An index of -1 indicates that the limb is not part
 * of the limbPos array.
 */
static s8 sLimbIndexToLimbPosIndex[] = {
    -1, -1, -1, -1, 0, -1, -1, 1, -1, 2, -1, -1, 3, -1, 4, -1, -1, 5, -1, -1, -1, 6, 7, -1, 8,
};

void EnWallmas_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnWallmas* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.5f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gWallmasterSkel, &gWallmasterIdleAnim, this->jointTable,
                       this->morphTable, WALLMASTER_LIMB_MAX);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);

    this->switchFlag = WALLMASTER_GET_SWITCH_FLAG(thisx);
    this->actor.params &= 0xFF;
    this->detectionRadius = this->actor.shape.rot.x * 40.0f * 0.1f;
    this->actor.shape.rot.x = 0;
    this->actor.world.rot.x = 0;
    if (this->detectionRadius <= 0.0f) {
        this->detectionRadius = 200.0f;
    }

    Actor_SetFocus(&this->actor, 25.0f);

    if (WALLMASTER_IS_FROZEN(&this->actor)) {
        Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_OBJ_ICE_POLY, this->actor.world.pos.x,
                           this->actor.world.pos.y - 15.0f, this->actor.world.pos.z, this->actor.world.rot.x,
                           (this->actor.world.rot.y + 0x5900), this->actor.world.rot.z, 0xFF50);
        this->actor.params &= ~0x80;
        EnWallmas_SetupReturnToCeiling(this);
        return;
    }

    if (WALLMASTER_GET_TYPE(&this->actor) == WALLMASTER_TYPE_FLAG) {
        if (Flags_GetSwitch(globalCtx, this->switchFlag)) {
            Actor_MarkForDeath(&this->actor);
            return;
        }

        EnWallmas_ProximityOrSwitchInit(this);
    } else if (WALLMASTER_GET_TYPE(&this->actor) == WALLMASTER_TYPE_PROXIMITY) {
        EnWallmas_ProximityOrSwitchInit(this);
    } else {
        EnWallmas_TimerInit(this, globalCtx);
    }
}

void EnWallmas_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnWallmas* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);

    if (this->actor.parent != NULL) {
        EnEncount1* encount1 = (EnEncount1*)this->actor.parent;

        if ((encount1->actor.update != NULL) && (encount1->unk_14E > 0)) {
            encount1->unk_14E--;
        }
    }
}

void EnWallmas_Freeze(EnWallmas* this) {
    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX;
    this->drawDmgEffScale = 0.55f;
    this->drawDmgEffFrozenSteamScale = 0.82500005f;
    this->drawDmgEffAlpha = 1.0f;
    this->collider.base.colType = 3;
    this->timer = 80;
    this->actor.flags &= ~ACTOR_FLAG_400;
    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 80);
}

void EnWallmas_ThawIfFrozen(EnWallmas* this, GlobalContext* globalCtx) {
    if (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
        this->collider.base.colType = 0;
        this->drawDmgEffAlpha = 0.0f;
        Actor_SpawnIceEffects(globalCtx, &this->actor, this->limbPos, 11, 2, 0.3f, 0.2f);
        this->actor.flags |= ACTOR_FLAG_400;
    }
}

void EnWallmas_TimerInit(EnWallmas* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    this->actor.flags &= ~ACTOR_FLAG_1;
    this->actor.flags |= ACTOR_FLAG_20;
    this->timer = 130;
    this->actor.velocity.y = 0.0f;
    this->actor.world.pos.y = player->actor.world.pos.y;
    this->actor.floorHeight = player->actor.floorHeight;
    this->actor.draw = EnWallmas_Draw;
    this->actionFunc = EnWallmas_WaitToDrop;
}

void EnWallmas_WaitToDrop(EnWallmas* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f* playerPos = &player->actor.world.pos;

    this->actor.world.pos = *playerPos;
    this->actor.floorHeight = player->actor.floorHeight;
    this->actor.floorPoly = player->actor.floorPoly;

    if (this->timer != 0) {
        this->timer--;
    }

    if ((player->stateFlags1 & 0x08100000) || (player->stateFlags2 & 0x80) || (player->unk_B5E > 0) ||
        (player->actor.freezeTimer > 0) || !(player->actor.bgCheckFlags & 1) ||
        ((WALLMASTER_GET_TYPE(&this->actor) == WALLMASTER_TYPE_PROXIMITY) &&
         (Math_Vec3f_DistXZ(&this->actor.home.pos, playerPos) > (120.f + this->detectionRadius)))) {
        func_801A75E8(NA_SE_EN_FALL_AIM);
        this->timer = 130;
    }

    if (this->timer == 80) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FALL_AIM);
    }

    if (this->timer == 0) {
        EnWallmas_SetupDrop(this, globalCtx);
    }
}

void EnWallmas_SetupDrop(EnWallmas* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    Animation_Change(&this->skelAnime, &gWallmasterLungeAnim, 0.0f, 20.0f,
                     Animation_GetLastFrame(&gWallmasterLungeAnim), ANIMMODE_ONCE, 0.0f);

    this->yTarget = player->actor.world.pos.y;
    this->actor.world.pos.y = player->actor.world.pos.y + 300.0f;
    this->actor.shape.rot.y = player->actor.shape.rot.y + 0x8000;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actor.floorHeight = player->actor.floorHeight;
    this->actor.flags |= ACTOR_FLAG_1;
    this->actor.flags &= ~ACTOR_FLAG_20;
    this->actionFunc = EnWallmas_Drop;
}

void EnWallmas_Drop(EnWallmas* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if ((player->stateFlags2 & 0x80) || (player->actor.freezeTimer > 0)) {
        EnWallmas_SetupReturnToCeiling(this);
    } else if (!Play_InCsMode(globalCtx) && !(player->stateFlags2 & 0x10) && (player->invincibilityTimer >= 0) &&
               (this->actor.xzDistToPlayer < 30.0f) && (this->actor.playerHeightRel < -5.0f) &&
               (-(f32)(player->cylinder.dim.height + 10) < this->actor.playerHeightRel)) {
        EnWallmas_SetupTakePlayer(this, globalCtx);
    } else if (this->actor.world.pos.y <= this->yTarget) {
        this->actor.world.pos.y = this->yTarget;
        this->actor.velocity.y = 0.0f;
        EnWallmas_SetupLand(this, globalCtx);
    }
}

void EnWallmas_SetupLand(EnWallmas* this, GlobalContext* globalCtx) {
    Animation_Change(&this->skelAnime, &gWallmasterJumpAnim, 1.0f, 41.0f, Animation_GetLastFrame(&gWallmasterJumpAnim),
                     ANIMMODE_ONCE, -3.0f);

    Actor_SpawnFloorDustRing(globalCtx, &this->actor, &this->actor.world.pos, 15.0f, 6, 20.0f, 300, 100, true);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FALL_LAND);
    this->actionFunc = EnWallmas_Land;
}

void EnWallmas_Land(EnWallmas* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        EnWallmas_SetupStand(this);
    }
}

void EnWallmas_SetupStand(EnWallmas* this) {
    Animation_PlayOnce(&this->skelAnime, &gWallmasterStandUpAnim);
    this->actionFunc = EnWallmas_Stand;
}

void EnWallmas_Stand(EnWallmas* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        EnWallmas_SetupWalk(this);
    }

    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer + 0x8000, 0xB6);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

void EnWallmas_SetupWalk(EnWallmas* this) {
    Animation_PlayOnceSetSpeed(&this->skelAnime, &gWallmasterWalkAnim, 3.0f);
    this->actor.speedXZ = 3.0f;
    this->actionFunc = EnWallmas_Walk;
}

void EnWallmas_Walk(EnWallmas* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        EnWallmas_SetupJumpToCeiling(this);
    }

    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer + 0x8000, 0xB6);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 12.0f) ||
        Animation_OnFrame(&this->skelAnime, 24.0f) || Animation_OnFrame(&this->skelAnime, 36.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FALL_WALK);
    }
}

void EnWallmas_SetupJumpToCeiling(EnWallmas* this) {
    Animation_PlayOnce(&this->skelAnime, &gWallmasterStopWalkAnim);
    this->actor.speedXZ = 0.0f;
    this->actionFunc = EnWallmas_JumpToCeiling;
}

void EnWallmas_JumpToCeiling(EnWallmas* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        EnWallmas_SetupReturnToCeiling(this);
    }
}

void EnWallmas_SetupReturnToCeiling(EnWallmas* this) {
    this->timer = 0;
    this->actor.speedXZ = 0.0f;
    Animation_Change(&this->skelAnime, &gWallmasterJumpAnim, 3.0f, 0.0f, Animation_GetLastFrame(&gWallmasterJumpAnim),
                     ANIMMODE_ONCE, -3.0f);
    this->actionFunc = EnWallmas_ReturnToCeiling;
}

void EnWallmas_ReturnToCeiling(EnWallmas* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    SkelAnime_Update(&this->skelAnime);
    if (this->skelAnime.curFrame > 20.0f) {
        this->actor.world.pos.y += 30.0f;
        this->timer += 9;
        this->actor.flags &= ~ACTOR_FLAG_2000;
    }

    if (Animation_OnFrame(&this->skelAnime, 20.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FALL_UP);
    }

    if (this->actor.playerHeightRel < -900.0f) {
        if (WALLMASTER_GET_TYPE(&this->actor) == WALLMASTER_TYPE_FLAG) {
            Actor_MarkForDeath(&this->actor);
            return;
        }

        if ((WALLMASTER_GET_TYPE(&this->actor) == WALLMASTER_TYPE_TIMER_ONLY) ||
            (Math_Vec3f_DistXZ(&this->actor.home.pos, &player->actor.world.pos) < this->detectionRadius)) {
            EnWallmas_TimerInit(this, globalCtx);
        } else {
            EnWallmas_ProximityOrSwitchInit(this);
        }
    }
}

void EnWallmas_SetupDamage(EnWallmas* this, s32 arg1) {
    Animation_MorphToPlayOnce(&this->skelAnime, &gWallmasterDamageAnim, -3.0f);

    if (arg1) {
        func_800BE504(&this->actor, &this->collider);
    }

    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 20);
    this->actor.speedXZ = 5.0f;
    this->actor.velocity.y = 10.0f;
    this->actionFunc = EnWallmas_Damage;
}

void EnWallmas_Damage(EnWallmas* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->actor.colChkInfo.health == 0) {
            EnWallmas_SetupDie(this, globalCtx);
        } else {
            EnWallmas_SetupCooldown(this);
        }
    }

    if (Animation_OnFrame(&this->skelAnime, 13.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_EYEGOLE_ATTACK);
    }

    Math_StepToF(&this->actor.speedXZ, 0.0f, 0.2f);
}

void EnWallmas_SetupCooldown(EnWallmas* this) {
    Animation_PlayOnce(&this->skelAnime, &gWallmasterRecoverFromDamageAnim);
    this->actor.speedXZ = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = EnWallmas_Cooldown;
}

void EnWallmas_Cooldown(EnWallmas* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        EnWallmas_SetupReturnToCeiling(this);
    }
}

void EnWallmas_SetupDie(EnWallmas* this, GlobalContext* globalCtx) {
    this->actor.speedXZ = 0.0f;
    this->actor.velocity.y = 0.0f;
    func_800B3030(globalCtx, &this->actor.world.pos, &gZeroVec3f, &gZeroVec3f, 250, -10, 2);
    SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 11, NA_SE_EN_EXTINCT);
    this->actionFunc = EnWallmas_Die;
}

void EnWallmas_Die(EnWallmas* this, GlobalContext* globalCtx) {
    if (Math_StepToF(&this->actor.scale.x, 0.0f, 0.0015f)) {
        Actor_SetScale(&this->actor, 0.01f);
        Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.world.pos, 0x90);
        Actor_MarkForDeath(&this->actor);
    }

    this->actor.scale.z = this->actor.scale.x;
    this->actor.scale.y = this->actor.scale.x;
}

void EnWallmas_SetupTakePlayer(EnWallmas* this, GlobalContext* globalCtx) {
    Animation_MorphToPlayOnce(&this->skelAnime, &gWallmasterHoverAnim, -5.0f);
    this->timer = -30;
    this->actionFunc = EnWallmas_TakePlayer;
    this->actor.speedXZ = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->yTarget = this->actor.playerHeightRel;
    func_800B724C(globalCtx, &this->actor, 18);
}

void EnWallmas_TakePlayer(EnWallmas* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (Animation_OnFrame(&this->skelAnime, 1.0f)) {
        func_800B8E58(player, player->ageProperties->unk_92 + NA_SE_VO_LI_DAMAGE_S);
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FALL_CATCH);
    }

    if (SkelAnime_Update(&this->skelAnime)) {
        player->actor.world.pos.x = this->actor.world.pos.x;
        player->actor.world.pos.z = this->actor.world.pos.z;

        if (this->timer < 0) {
            this->actor.world.pos.y += 2.0f;
        } else {
            this->actor.world.pos.y += 10.0f;
        }

        player->actor.world.pos.y = this->actor.world.pos.y - sYOffsetPerForm[((void)0, gSaveContext.save.playerForm)];
        if (this->timer == -30) {
            func_800B8E58(player, player->ageProperties->unk_92 + NA_SE_VO_LI_TAKEN_AWAY);
        }

        if (this->timer == 0) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FALL_UP);
        }

        this->timer += 2;
    } else {
        Math_StepToF(&this->actor.world.pos.y,
                     sYOffsetPerForm[((void)0, gSaveContext.save.playerForm)] + player->actor.world.pos.y, 5.0f);
    }

    Math_StepToF(&this->actor.world.pos.x, player->actor.world.pos.x, 3.0f);
    Math_StepToF(&this->actor.world.pos.z, player->actor.world.pos.z, 3.0f);

    if (this->timer == 30) {
        play_sound(NA_SE_OC_ABYSS);
        func_80169FDC(&globalCtx->state);
    }
}

void EnWallmas_ProximityOrSwitchInit(EnWallmas* this) {
    this->timer = 0;
    this->actor.draw = NULL;
    this->actor.flags &= ~ACTOR_FLAG_1;
    if (WALLMASTER_GET_TYPE(&this->actor) == WALLMASTER_TYPE_PROXIMITY) {
        this->actionFunc = EnWallmas_WaitForProximity;
    } else {
        this->actionFunc = EnWallmas_WaitForSwitchFlag;
    }
}

void EnWallmas_WaitForProximity(EnWallmas* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (Math_Vec3f_DistXZ(&this->actor.home.pos, &player->actor.world.pos) < this->detectionRadius) {
        EnWallmas_TimerInit(this, globalCtx);
    }
}

void EnWallmas_WaitForSwitchFlag(EnWallmas* this, GlobalContext* globalCtx) {
    if (Flags_GetSwitch(globalCtx, this->switchFlag)) {
        EnWallmas_TimerInit(this, globalCtx);
        this->timer = 81;
    }
}

void EnWallmas_SetupStun(EnWallmas* this) {
    this->actor.speedXZ = 0.0f;
    if (this->actor.velocity.y > 0.0f) {
        this->actor.velocity.y = 0.0f;
    }

    func_800BE504(&this->actor, &this->collider);
    this->actionFunc = EnWallmas_Stun;
}

void EnWallmas_Stun(EnWallmas* this, GlobalContext* globalCtx) {
    if (this->timer != 0) {
        this->timer--;
    }

    if (this->timer == 0) {
        EnWallmas_ThawIfFrozen(this, globalCtx);
        if (this->actor.colChkInfo.health == 0) {
            EnWallmas_SetupDamage(this, false);
        } else {
            this->actor.world.rot.y = this->actor.shape.rot.y;
            EnWallmas_SetupReturnToCeiling(this);
        }
    }
}

void EnWallmas_UpdateDamage(EnWallmas* this, GlobalContext* globalCtx) {
    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        Actor_SetDropFlag(&this->actor, &this->collider.info);

        if ((this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) ||
            (!(this->collider.info.acHitInfo->toucher.dmgFlags & 0xDB0B3))) {
            if (Actor_ApplyDamage(&this->actor) == 0) {
                Enemy_StartFinishingBlow(globalCtx, &this->actor);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_DAIOCTA_REVERSE);
                this->actor.flags &= ~ACTOR_FLAG_1;
            } else if (this->actor.colChkInfo.damage != 0) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FALL_DAMAGE);
            }

            EnWallmas_ThawIfFrozen(this, globalCtx);

            if (this->actor.colChkInfo.damageEffect != WALLMASTER_DMGEFF_HOOKSHOT) {
                if (this->actor.colChkInfo.damageEffect == WALLMASTER_DMGEFF_ICE_ARROW) {
                    EnWallmas_Freeze(this);
                    if (this->actor.colChkInfo.health == 0) {
                        this->timer = 3;
                        this->collider.base.acFlags &= ~AC_ON;
                    }

                    EnWallmas_SetupStun(this);
                } else if (this->actor.colChkInfo.damageEffect == WALLMASTER_DMGEFF_STUN) {
                    this->timer = 40;
                    Actor_SetColorFilter(&this->actor, 0, 255, 0, 40);
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
                    EnWallmas_SetupStun(this);
                } else if (this->actor.colChkInfo.damageEffect == WALLMASTER_DMGEFF_ZORA_MAGIC) {
                    this->timer = 40;
                    Actor_SetColorFilter(&this->actor, 0, 255, 0, 40);
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
                    this->drawDmgEffScale = 0.55f;
                    this->drawDmgEffAlpha = 2.0f;
                    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_ELECTRIC_SPARKS_MEDIUM;
                    EnWallmas_SetupStun(this);
                } else {
                    if (this->actor.colChkInfo.damageEffect == WALLMASTER_DMGEFF_FIRE_ARROW) {
                        this->drawDmgEffAlpha = 4.0f;
                        this->drawDmgEffScale = 0.55f;
                        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
                    } else if (this->actor.colChkInfo.damageEffect == WALLMASTER_DMGEFF_LIGHT_ARROW) {
                        this->drawDmgEffAlpha = 4.0f;
                        this->drawDmgEffScale = 0.55f;
                        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_LIGHT_ORBS;
                        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG,
                                    this->collider.info.bumper.hitPos.x, this->collider.info.bumper.hitPos.y,
                                    this->collider.info.bumper.hitPos.z, 0, 0, 0, CLEAR_TAG_LARGE_LIGHT_RAYS);
                    }

                    EnWallmas_SetupDamage(this, true);
                }
            }
        }
    }
}

void EnWallmas_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnWallmas* this = THIS;

    EnWallmas_UpdateDamage(this, globalCtx);
    this->actionFunc(this, globalCtx);

    if ((this->actionFunc != EnWallmas_WaitToDrop) && (this->actionFunc != EnWallmas_WaitForProximity) &&
        (this->actionFunc != EnWallmas_TakePlayer) && (this->actionFunc != EnWallmas_WaitForSwitchFlag)) {
        if ((this->actionFunc != EnWallmas_ReturnToCeiling) && (this->actionFunc != EnWallmas_TakePlayer)) {
            Actor_MoveWithGravity(&this->actor);
        }

        if (this->actionFunc != EnWallmas_Drop) {
            Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 25.0f, 0.0f, 0x1DU);
        }

        if ((this->actionFunc != EnWallmas_Die) && (this->actionFunc != EnWallmas_Drop)) {
            Collider_UpdateCylinder(&this->actor, &this->collider);
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
            if ((this->actionFunc != EnWallmas_Damage) && (this->actor.bgCheckFlags & 1) &&
                (this->actor.freezeTimer == 0)) {
                CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
            }
        }

        Actor_SetFocus(&this->actor, 25.0f);

        if (this->drawDmgEffAlpha > 0.0f) {
            if (this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
                Math_StepToF(&this->drawDmgEffAlpha, 0.0f, 0.05f);
                this->drawDmgEffScale = (this->drawDmgEffAlpha + 1.0f) * 0.275f;
                this->drawDmgEffScale = CLAMP_MAX(this->drawDmgEffScale, 0.55f);
            } else if (Math_StepToF(&this->drawDmgEffFrozenSteamScale, 0.55f, 0.01375f) == 0) {
                func_800B9010(&this->actor, NA_SE_EV_ICE_FREEZE - SFX_FLAG);
            }
        }
    }
}

void EnWallmas_DrawShadow(EnWallmas* this, GlobalContext* globalCtx) {
    s32 pad;
    f32 xzScale;
    MtxF mf;
    Gfx* gfx;

    if ((this->actor.floorPoly != NULL) && ((this->timer < 81) || (this->actionFunc == EnWallmas_Stun))) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        gfx = POLY_OPA_DISP;

        gSPDisplayList(&gfx[0], &sSetupDL[6 * 44]);
        gDPSetPrimColor(&gfx[1], 0, 0, 0, 0, 0, 255);
        func_800C0094(this->actor.floorPoly, this->actor.world.pos.x, this->actor.floorHeight, this->actor.world.pos.z,
                      &mf);
        Matrix_InsertMatrix(&mf, MTXMODE_NEW);

        if ((this->actionFunc != EnWallmas_WaitToDrop) && (this->actionFunc != EnWallmas_ReturnToCeiling) &&
            (this->actionFunc != EnWallmas_TakePlayer) && (this->actionFunc != EnWallmas_WaitForSwitchFlag)) {
            xzScale = this->actor.scale.x * 50.0f;
        } else {
            xzScale = CLAMP_MAX(80 - this->timer, 80) * 0.00625f;
        }

        Matrix_Scale(xzScale, 1.0f, xzScale, MTXMODE_APPLY);
        gSPMatrix(&gfx[2], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(&gfx[3], gCircleShadowDL);

        POLY_OPA_DISP = &gfx[4];

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

s32 EnWallmas_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                               Actor* thisx) {
    EnWallmas* this = THIS;

    if (limbIndex == WALLMASTER_LIMB_ROOT) {
        if (this->actionFunc != EnWallmas_TakePlayer) {
            pos->z -= 1600.0f;
        } else {
            pos->z -= (1600.0f * (this->skelAnime.endFrame - this->skelAnime.curFrame)) / this->skelAnime.endFrame;
        }
    }

    return false;
}

void EnWallmas_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnWallmas* this = THIS;
    Gfx* gfx;

    if (sLimbIndexToLimbPosIndex[limbIndex] != -1) {
        Matrix_GetStateTranslation(&this->limbPos[sLimbIndexToLimbPosIndex[limbIndex]]);
    }

    if (limbIndex == WALLMASTER_LIMB_WRIST) {
        Matrix_GetStateTranslationAndScaledX(1000.0f, &this->limbPos[9]);
        Matrix_GetStateTranslationAndScaledX(-1000.0f, &this->limbPos[10]);
    } else if (limbIndex == WALLMASTER_LIMB_HAND) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        gfx = POLY_OPA_DISP;

        Matrix_StatePush();
        Matrix_InsertTranslation(1600.0f, -700.0f, -1700.0f, MTXMODE_APPLY);
        Matrix_RotateY(0x2AAA, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(0xAAA, MTXMODE_APPLY);
        Matrix_Scale(2.0f, 2.0f, 2.0f, MTXMODE_APPLY);

        gSPMatrix(&gfx[0], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(&gfx[1], gWallmasterLittleFingerDL);

        POLY_OPA_DISP = &gfx[2];

        Matrix_StatePop();

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

void EnWallmas_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnWallmas* this = THIS;

    if (this->actionFunc != EnWallmas_WaitToDrop) {
        func_8012C28C(globalCtx->state.gfxCtx);
        SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                              this->skelAnime.dListCount, EnWallmas_OverrideLimbDraw, EnWallmas_PostLimbDraw,
                              &this->actor);
        Actor_DrawDamageEffects(globalCtx, &this->actor, this->limbPos, ARRAY_COUNT(this->limbPos),
                                this->drawDmgEffScale, this->drawDmgEffFrozenSteamScale, this->drawDmgEffAlpha,
                                this->drawDmgEffType);
    }

    if (this->actor.colorFilterTimer != 0) {
        func_800AE5A0(globalCtx);
    }

    EnWallmas_DrawShadow(this, globalCtx);
}
