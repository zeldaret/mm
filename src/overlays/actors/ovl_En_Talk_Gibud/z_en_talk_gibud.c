/*
 * File: z_en_talk_gibud.c
 * Overlay: ovl_En_Talk_Gibud
 * Description: Gibdos requesting items Beneath the Well
 */

#include "z_en_talk_gibud.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_400)

#define THIS ((EnTalkGibud*)thisx)

void EnTalkGibud_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTalkGibud_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTalkGibud_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTalkGibud_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnTalkGibud_SetupIdle(EnTalkGibud* this);
void EnTalkGibud_Idle(EnTalkGibud* this, GlobalContext* globalCtx);
void EnTalkGibud_SetupAttemptPlayerFreeze(EnTalkGibud* this);
void EnTalkGibud_AttemptPlayerFreeze(EnTalkGibud* this, GlobalContext* globalCtx);
void EnTalkGibud_SetupWalkToPlayer(EnTalkGibud* this);
void EnTalkGibud_WalkToPlayer(EnTalkGibud* this, GlobalContext* globalCtx);
void EnTalkGibud_SetupGrab(EnTalkGibud* this);
void EnTalkGibud_Grab(EnTalkGibud* this, GlobalContext* globalCtx);
void EnTalkGibud_SetupGrabFail(EnTalkGibud* this);
void EnTalkGibud_GrabFail(EnTalkGibud* this, GlobalContext* globalCtx);
void EnTalkGibud_SetupTurnAwayAndShakeHead(EnTalkGibud* this);
void EnTalkGibud_TurnAwayAndShakeHead(EnTalkGibud* this, GlobalContext* globalCtx);
void EnTalkGibud_SetupWalkToHome(EnTalkGibud* this);
void EnTalkGibud_WalkToHome(EnTalkGibud* this, GlobalContext* globalCtx);
void EnTalkGibud_Stunned(EnTalkGibud* this, GlobalContext* globalCtx);
void EnTalkGibud_SetupDamage(EnTalkGibud* this);
void EnTalkGibud_Damage(EnTalkGibud* this, GlobalContext* globalCtx);
void EnTalkGibud_SetupDead(EnTalkGibud* this);
void EnTalkGibud_Dead(EnTalkGibud* this, GlobalContext* globalCtx);
void EnTalkGibud_SetupRevive(EnTalkGibud* this);
void EnTalkGibud_Revive(EnTalkGibud* this, GlobalContext* globalCtx);
void EnTalkGibud_PassiveIdle(EnTalkGibud* this, GlobalContext* globalCtx);
void EnTalkGibud_SetupTalk(EnTalkGibud* this);
void EnTalkGibud_Talk(EnTalkGibud* this, GlobalContext* globalCtx);
void EnTalkGibud_SetupDisappear(EnTalkGibud* this);
void EnTalkGibud_Disappear(EnTalkGibud* this, GlobalContext* globalCtx);
void EnTalkGibud_FacePlayerWhenTalking(EnTalkGibud* this, GlobalContext* globalCtx);
s32 EnTalkGibud_PlayerInRangeWithCorrectState(EnTalkGibud* this, GlobalContext* globalCtx);
s32 EnTalkGibud_PlayerOutOfRange(EnTalkGibud* this, GlobalContext* globalCtx);
void EnTalkGibud_TurnTowardsPlayer(EnTalkGibud* this, GlobalContext* globalCtx);
s32 EnTalkGibud_MoveToIdealGrabPositionAndRotation(EnTalkGibud* this, GlobalContext* globalCtx);

typedef struct {
    /* 0x0 */ s32 itemActionParam;
    /* 0x4 */ s32 item;
    /* 0x8 */ s32 amount;
    /* 0xC */ s16 isBottledItem;
} EnTalkGibudRequestedItem;

typedef enum {
    /* 0 */ EN_TALK_GIBUD_REQUESTED_ITEM_MET,
    /* 1 */ EN_TALK_GIBUD_REQUESTED_ITEM_NOT_ENOUGH_AMMO,
    /* 2 */ EN_TALK_GIBUD_REQUESTED_ITEM_NOT_MET,
} EnTalkGibudRequestedItemState;

typedef enum {
    /*  0 */ EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_BLUE_POTION,
    /*  1 */ EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_BEANS,
    /*  2 */ EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_SPRING_WATER,
    /*  3 */ EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_FISH,
    /*  4 */ EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_BUGS,
    /*  5 */ EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_DEKU_NUTS,
    /*  6 */ EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_BOMBS,
    /*  7 */ EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_HOT_SPRING_WATER,
    /*  8 */ EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_BIG_POE,
    /*  9 */ EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_MILK,
} EnTalkGibudRequestedItemIndex;

typedef enum {
    /*  0 */ EN_TALK_GIBUD_ANIMATION_GRAB_ATTACK,
    /*  1 */ EN_TALK_GIBUD_ANIMATION_GRAB_END,
    /*  2 */ EN_TALK_GIBUD_ANIMATION_GRAB_START,
    /*  3 */ EN_TALK_GIBUD_ANIMATION_LOOK_BACK,
    /*  4 */ EN_TALK_GIBUD_ANIMATION_CROUCH_WIPING_TEARS,
    /*  5 */ EN_TALK_GIBUD_ANIMATION_CROUCH_CRYING,
    /*  6 */ EN_TALK_GIBUD_ANIMATION_DEATH,
    /*  7 */ EN_TALK_GIBUD_ANIMATION_DAMAGE,
    /*  8 */ EN_TALK_GIBUD_ANIMATION_CROUCH_END,
    /*  9 */ EN_TALK_GIBUD_ANIMATION_IDLE,
    /* 10 */ EN_TALK_GIBUD_ANIMATION_WALK,
    /* 11 */ EN_TALK_GIBUD_ANIMATION_DANCE_SQUAT,
    /* 12 */ EN_TALK_GIBUD_ANIMATION_DANCE_PIROUETTE,
    /* 13 */ EN_TALK_GIBUD_ANIMATION_DANCE_CLAP,
} EnTalkGibudAnimations;

typedef enum {
    /* 0 */ EN_TALK_GIBUD_TYPE_GIBDO,
    /* 1 */ EN_TALK_GIBUD_TYPE_REDEAD,
} EnTalkGibudType;

typedef enum {
    /* 0 */ EN_TALK_GIBUD_GRAB_START,
    /* 1 */ EN_TALK_GIBUD_GRAB_ATTACK,
    /* 2 */ EN_TALK_GIBUD_GRAB_RELEASE,
} EnTalkGibudGrabState;

const ActorInit En_Talk_Gibud_InitVars = {
    ACTOR_EN_TALK_GIBUD,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_RD,
    sizeof(EnTalkGibud),
    (ActorFunc)EnTalkGibud_Init,
    (ActorFunc)EnTalkGibud_Destroy,
    (ActorFunc)EnTalkGibud_Update,
    (ActorFunc)EnTalkGibud_Draw,
};

static AnimationInfo sAnimations[] = {
    { &gGibdoRedeadGrabAttackAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -8.0f },
    { &gGibdoRedeadGrabEndAnim, 0.5f, 0.0f, 0.0f, ANIMMODE_ONCE_INTERP, 0.0f },
    { &gGibdoRedeadGrabStartAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -8.0f },
    { &gGibdoRedeadLookBackAnim, 0.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -8.0f },
    { &gGibdoRedeadWipingTearsAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -8.0f },
    { &gGibdoRedeadSobbingAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -8.0f },
    { &gGibdoRedeadDeathAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -8.0f },
    { &gGibdoRedeadDamageAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -8.0f },
    { &gGibdoRedeadStandUpAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -8.0f },
    { &gGibdoRedeadIdleAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -8.0f },
    { &gGibdoRedeadWalkAnim, 0.4f, 0.0f, 0.0f, ANIMMODE_LOOP_INTERP, -8.0f },
    { &gGibdoRedeadSquattingDanceAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -8.0f },
    { &gGibdoRedeadPirouetteAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -8.0f },
    { &gGibdoRedeadClappingDanceAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -8.0f },
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
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7EFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON | BUMP_HOOKABLE,
        OCELEM_ON,
    },
    { 20, 70, 0, { 0, 0, 0 } },
};

typedef enum {
    /* 0x0 */ EN_TALK_GIBUD_DMGEFF_NONE,       // Does not interact with the Gibdo/Redead at all
    /* 0x1 */ EN_TALK_GIBUD_DMGEFF_STUN,       // Stuns without applying any effect
    /* 0x2 */ EN_TALK_GIBUD_DMGEFF_FIRE_ARROW, // Damages, applies a fire effect, and changes a Gibdo into a Redead
    /* 0x4 */ EN_TALK_GIBUD_DMGEFF_LIGHT_ARROW = 0x4, // Damages and applies a light effect
    /* 0xC */ EN_TALK_GIBUD_DMGEFF_ZORA_MAGIC = 0xC,  // Stuns and applies an electric effect
    /* 0xD */ EN_TALK_GIBUD_DMGEFF_RECOIL,            // Deals no damage, but displays hit mark and recoil animation
    /* 0xE */ EN_TALK_GIBUD_DMGEFF_LIGHT_RAY,         // Instantly kills a Redead on contact
    /* 0xF */ EN_TALK_GIBUD_DMGEFF_DAMAGE,            // Deals damage and plays the damage animation
} EnTalkGibudDamageEffect;

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, EN_TALK_GIBUD_DMGEFF_NONE),
    /* Deku Stick     */ DMG_ENTRY(2, EN_TALK_GIBUD_DMGEFF_DAMAGE),
    /* Horse trample  */ DMG_ENTRY(0, EN_TALK_GIBUD_DMGEFF_NONE),
    /* Explosives     */ DMG_ENTRY(1, EN_TALK_GIBUD_DMGEFF_DAMAGE),
    /* Zora boomerang */ DMG_ENTRY(0, EN_TALK_GIBUD_DMGEFF_RECOIL),
    /* Normal arrow   */ DMG_ENTRY(0, EN_TALK_GIBUD_DMGEFF_RECOIL),
    /* UNK_DMG_0x06   */ DMG_ENTRY(2, EN_TALK_GIBUD_DMGEFF_DAMAGE),
    /* Hookshot       */ DMG_ENTRY(0, EN_TALK_GIBUD_DMGEFF_RECOIL),
    /* Goron punch    */ DMG_ENTRY(1, EN_TALK_GIBUD_DMGEFF_DAMAGE),
    /* Sword          */ DMG_ENTRY(1, EN_TALK_GIBUD_DMGEFF_DAMAGE),
    /* Goron pound    */ DMG_ENTRY(1, EN_TALK_GIBUD_DMGEFF_DAMAGE),
    /* Fire arrow     */ DMG_ENTRY(1, EN_TALK_GIBUD_DMGEFF_FIRE_ARROW),
    /* Ice arrow      */ DMG_ENTRY(0, EN_TALK_GIBUD_DMGEFF_RECOIL),
    /* Light arrow    */ DMG_ENTRY(2, EN_TALK_GIBUD_DMGEFF_LIGHT_ARROW),
    /* Goron spikes   */ DMG_ENTRY(1, EN_TALK_GIBUD_DMGEFF_DAMAGE),
    /* Deku spin      */ DMG_ENTRY(0, EN_TALK_GIBUD_DMGEFF_STUN),
    /* Deku bubble    */ DMG_ENTRY(0, EN_TALK_GIBUD_DMGEFF_RECOIL),
    /* Deku launch    */ DMG_ENTRY(2, EN_TALK_GIBUD_DMGEFF_DAMAGE),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, EN_TALK_GIBUD_DMGEFF_NONE),
    /* Zora barrier   */ DMG_ENTRY(0, EN_TALK_GIBUD_DMGEFF_ZORA_MAGIC),
    /* Normal shield  */ DMG_ENTRY(0, EN_TALK_GIBUD_DMGEFF_NONE),
    /* Light ray      */ DMG_ENTRY(0, EN_TALK_GIBUD_DMGEFF_LIGHT_RAY),
    /* Thrown object  */ DMG_ENTRY(1, EN_TALK_GIBUD_DMGEFF_DAMAGE),
    /* Zora punch     */ DMG_ENTRY(1, EN_TALK_GIBUD_DMGEFF_DAMAGE),
    /* Spin attack    */ DMG_ENTRY(1, EN_TALK_GIBUD_DMGEFF_DAMAGE),
    /* Sword beam     */ DMG_ENTRY(0, EN_TALK_GIBUD_DMGEFF_NONE),
    /* Normal Roll    */ DMG_ENTRY(0, EN_TALK_GIBUD_DMGEFF_NONE),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, EN_TALK_GIBUD_DMGEFF_NONE),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, EN_TALK_GIBUD_DMGEFF_NONE),
    /* Unblockable    */ DMG_ENTRY(0, EN_TALK_GIBUD_DMGEFF_NONE),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, EN_TALK_GIBUD_DMGEFF_NONE),
    /* Powder Keg     */ DMG_ENTRY(1, EN_TALK_GIBUD_DMGEFF_DAMAGE),
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 8, 0, 0, 0, MASS_HEAVY };

static EnTalkGibudRequestedItem sRequestedItemTable[] = {
    { PLAYER_AP_BOTTLE_POTION_BLUE, ITEM_POTION_BLUE, 1, true },
    { PLAYER_AP_MAGIC_BEANS, ITEM_MAGIC_BEANS, 5, false },
    { PLAYER_AP_BOTTLE_SPRING_WATER, ITEM_SPRING_WATER, 1, true },
    { PLAYER_AP_BOTTLE_FISH, ITEM_FISH, 1, true },
    { PLAYER_AP_BOTTLE_BUG, ITEM_BUG, 1, true },
    { PLAYER_AP_NUT, ITEM_NUT, 10, false },
    { PLAYER_AP_BOMB, ITEM_BOMB, 10, false },
    { PLAYER_AP_BOTTLE_HOT_SPRING_WATER, ITEM_HOT_SPRING_WATER, 1, true },
    { PLAYER_AP_BOTTLE_BIG_POE, ITEM_BIG_POE, 1, true },
    { PLAYER_AP_BOTTLE_MILK, ITEM_MILK_BOTTLE, 1, true },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -3500, ICHAIN_STOP),
};

static Vec3f sVelocity = { 0.0f, 0.0f, 0.0f };

static Vec3f sAccel = { 0.0f, 0.600000023842f, 0.0f };

void EnTalkGibud_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnTalkGibud* this = THIS;
    s32 i;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->actor.targetMode = 0;
    this->actor.hintId = 0x2D;
    this->actor.textId = 0;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 28.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gGibdoSkel, &gGibdoRedeadIdleAnim, this->jointTable,
                       this->morphTable, GIBDO_LIMB_MAX);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);

    this->playerStunWaitTimer = 0;
    this->grabState = EN_TALK_GIBUD_GRAB_START;
    this->grabWaitTimer = 0;
    this->itemActionParam = PLAYER_AP_NONE;
    this->drawDmgEffTimer = 0;
    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
    this->isTalking = false;
    this->type = EN_TALK_GIBUD_TYPE_GIBDO;
    this->requestedItemIndex = EN_TALK_GIBUD_REQUESTED_ITEM_INDEX(thisx);
    this->switchFlag = EN_TALK_GIBUD_SWITCH_FLAG(thisx);
    this->drawDmgEffAlpha = 0.0f;
    this->drawDmgEffScale = 0.0f;

    for (i = 0; i < ARRAY_COUNT(this->limbPos); i++) {
        this->limbPos[i] = gZeroVec3f;
    }

    if (this->requestedItemIndex < EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_BLUE_POTION) {
        this->requestedItemIndex = EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_BLUE_POTION;
    }

    if (this->requestedItemIndex > EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_MILK) {
        this->requestedItemIndex = EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_MILK;
    }

    if (this->switchFlag == 0xFF) {
        this->switchFlag = -1;
    }

    if (this->switchFlag != -1 && Flags_GetSwitch(globalCtx, this->switchFlag)) {
        Actor_MarkForDeath(&this->actor);
    }

    EnTalkGibud_SetupIdle(this);
}

void EnTalkGibud_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnTalkGibud* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnTalkGibud_SetupIdle(EnTalkGibud* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, EN_TALK_GIBUD_ANIMATION_IDLE);
    this->actionFunc = EnTalkGibud_Idle;
}

/**
 * This is the idle for when the player is not wearing the Gibdo Mask. The
 * Gibdo will attack the player if they get too close.
 */
void EnTalkGibud_Idle(EnTalkGibud* this, GlobalContext* globalCtx) {
    if (this->actor.xzDistToPlayer <= 150.0f && func_800B715C(globalCtx)) {
        EnTalkGibud_SetupAttemptPlayerFreeze(this);
    }

    Math_SmoothStepToS(&this->headRotation.y, 0, 1, 0x64, 0);
    Math_SmoothStepToS(&this->upperBodyRotation.y, 0, 1, 0x64, 0);
}

void EnTalkGibud_SetupAttemptPlayerFreeze(EnTalkGibud* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, EN_TALK_GIBUD_ANIMATION_IDLE);
    this->actionFunc = EnTalkGibud_AttemptPlayerFreeze;
}

void EnTalkGibud_AttemptPlayerFreeze(EnTalkGibud* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 rot = this->actor.shape.rot.y + this->headRotation.y + this->upperBodyRotation.y;
    s16 yaw = BINANG_SUB(this->actor.yawTowardsPlayer, rot);

    if (ABS_ALT(yaw) < 0x2008) {
        player->actor.freezeTimer = 60;
        func_8013ECE0(this->actor.xzDistToPlayer, 255, 20, 150);
        func_80123E90(globalCtx, &this->actor);
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_REDEAD_AIM);
        EnTalkGibud_SetupWalkToPlayer(this);
    }

    EnTalkGibud_TurnTowardsPlayer(this, globalCtx);
}

void EnTalkGibud_SetupWalkToPlayer(EnTalkGibud* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, EN_TALK_GIBUD_ANIMATION_WALK);
    this->actor.speedXZ = 0.4f;

    if (this->actionFunc == EnTalkGibud_AttemptPlayerFreeze) {
        this->playerStunWaitTimer = 80;
    } else {
        this->playerStunWaitTimer = 20;
    }

    this->actionFunc = EnTalkGibud_WalkToPlayer;
}

void EnTalkGibud_WalkToPlayer(EnTalkGibud* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 pad;

    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xFA);
    this->actor.world.rot = this->actor.shape.rot;
    Math_SmoothStepToS(&this->headRotation.y, 0, 1, 0x64, 0);
    Math_SmoothStepToS(&this->upperBodyRotation.y, 0, 1, 0x64, 0);

    if (EnTalkGibud_PlayerInRangeWithCorrectState(this, globalCtx) && Actor_IsFacingPlayer(&this->actor, 0x38E3)) {
        if ((this->grabWaitTimer == 0) && (this->actor.xzDistToPlayer <= 45.0f)) {
            player->actor.freezeTimer = 0;
            if (gSaveContext.save.playerForm == PLAYER_FORM_GORON || gSaveContext.save.playerForm == PLAYER_FORM_DEKU) {
                // If the Gibdo/Redead tries to grab Goron or Deku Link, it will fail to
                // do so. It will appear to take damage and shake its head side-to-side.
                EnTalkGibud_SetupGrabFail(this);
            } else if (globalCtx->grabPlayer(globalCtx, player)) {
                EnTalkGibud_SetupGrab(this);
            }
        } else {
            if (this->playerStunWaitTimer == 0) {
                player->actor.freezeTimer = 40;
                this->playerStunWaitTimer = 60;
                func_8013ECE0(this->actor.xzDistToPlayer, 255, 20, 150);
                func_80123E90(globalCtx, &this->actor);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_REDEAD_AIM);
            } else {
                this->playerStunWaitTimer--;
            }
        }
    } else if ((this->grabWaitTimer == 0) && (this->actor.xzDistToPlayer <= 45.0f)) {
        EnTalkGibud_SetupWalkToHome(this);
    } else if (EnTalkGibud_PlayerOutOfRange(this, globalCtx)) {
        EnTalkGibud_SetupWalkToHome(this);
    }

    if (this->grabWaitTimer > 0) {
        this->grabWaitTimer--;
    }

    if (Animation_OnFrame(&this->skelAnime, 10.0f) || Animation_OnFrame(&this->skelAnime, 22.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_RIZA_WALK);
    } else if (!(globalCtx->gameplayFrames & 95)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_REDEAD_CRY);
    }
}

void EnTalkGibud_SetupGrab(EnTalkGibud* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, EN_TALK_GIBUD_ANIMATION_GRAB_START);
    this->grabDamageTimer = 0;
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->grabState = EN_TALK_GIBUD_GRAB_START;
    this->actionFunc = EnTalkGibud_Grab;
}

void EnTalkGibud_Grab(EnTalkGibud* this, GlobalContext* globalCtx) {
    Player* player2 = GET_PLAYER(globalCtx);
    Player* player = player2;
    s32 inPositionToAttack;
    u16 damageSfxId;

    switch (this->grabState) {
        case EN_TALK_GIBUD_GRAB_START:
            inPositionToAttack = EnTalkGibud_MoveToIdealGrabPositionAndRotation(this, globalCtx);
            if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) && (inPositionToAttack == true)) {
                this->grabState = EN_TALK_GIBUD_GRAB_ATTACK;
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, EN_TALK_GIBUD_ANIMATION_GRAB_ATTACK);
            }
            break;

        case EN_TALK_GIBUD_GRAB_ATTACK:
            if (this->grabDamageTimer == 20) {
                s16 requiredScopeTemp;

                damageSfxId = player->ageProperties->unk_92 + NA_SE_VO_LI_DAMAGE_S;
                globalCtx->damagePlayer(globalCtx, -8);
                func_800B8E58(player, damageSfxId);
                func_8013ECE0(this->actor.xzDistToPlayer, 240, 1, 12);
                this->grabDamageTimer = 0;
            } else {
                this->grabDamageTimer++;
            }

            if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_REDEAD_ATTACK);
            }

            if (!(player->stateFlags2 & 0x80) || (player->unk_B62 != 0)) {
                if ((player->unk_B62 != 0) && (player->stateFlags2 & 0x80)) {
                    player->stateFlags2 &= ~0x80;
                    player->unk_AE8 = 100;
                }

                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, EN_TALK_GIBUD_ANIMATION_GRAB_END);
                this->actor.flags |= ACTOR_FLAG_1;
                this->grabState = EN_TALK_GIBUD_GRAB_RELEASE;
                this->grabDamageTimer = 0;
            }
            break;

        case EN_TALK_GIBUD_GRAB_RELEASE:
            if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                this->grabWaitTimer = 20;
                this->actor.shape.yOffset = 0.0f;
                EnTalkGibud_SetupWalkToPlayer(this);
            } else {
                Math_SmoothStepToF(&this->actor.shape.yOffset, 0.0f, 1.0f, 400.0f, 0.0f);
            }
            break;
    }
}

void EnTalkGibud_SetupGrabFail(EnTalkGibud* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, EN_TALK_GIBUD_ANIMATION_DAMAGE);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_REDEAD_DAMAGE);
    this->actor.speedXZ = -2.0f;
    this->actionFunc = EnTalkGibud_GrabFail;
}

void EnTalkGibud_GrabFail(EnTalkGibud* this, GlobalContext* globalCtx) {
    if (this->actor.speedXZ < 0.0f) {
        this->actor.speedXZ += 0.15f;
    }

    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    Math_SmoothStepToS(&this->headRotation.y, 0, 1, 0x12C, 0);
    Math_SmoothStepToS(&this->upperBodyRotation.y, 0, 1, 0x12C, 0);
    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        this->actor.world.rot.y = this->actor.shape.rot.y;
        EnTalkGibud_SetupTurnAwayAndShakeHead(this);
    }
}

void EnTalkGibud_SetupTurnAwayAndShakeHead(EnTalkGibud* this) {
    this->headShakeTimer = 0;
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, EN_TALK_GIBUD_ANIMATION_WALK);
    this->actionFunc = EnTalkGibud_TurnAwayAndShakeHead;
}

void EnTalkGibud_TurnAwayAndShakeHead(EnTalkGibud* this, GlobalContext* globalCtx) {
    Math_SmoothStepToS(&this->actor.world.rot.y, BINANG_ROT180(this->actor.yawTowardsPlayer), 5, 3500, 200);
    this->actor.shape.rot.y = this->actor.world.rot.y;
    if (this->headShakeTimer > 60) {
        EnTalkGibud_SetupWalkToHome(this);
        this->playerStunWaitTimer = 0;
    } else {
        this->headRotation.y =
            Math_SinS(this->headShakeTimer * 4000) * (0x256F * ((60 - this->headShakeTimer) / 60.0f));
        this->headShakeTimer++;
    }
}

void EnTalkGibud_SetupWalkToHome(EnTalkGibud* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, EN_TALK_GIBUD_ANIMATION_WALK);
    this->actor.speedXZ = 0.4f;
    this->actionFunc = EnTalkGibud_WalkToHome;
}

void EnTalkGibud_WalkToHome(EnTalkGibud* this, GlobalContext* globalCtx) {
    Math_SmoothStepToS(&this->headRotation.y, 0, 1, 100, 0);
    Math_SmoothStepToS(&this->upperBodyRotation.y, 0, 1, 100, 0);
    if (Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos) < 5.0f) {
        if (this->actor.speedXZ > 0.2f) {
            this->actor.speedXZ -= 0.2f;
        } else {
            this->actor.speedXZ = 0.0f;
        }

        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 1, 200, 10);
        this->actor.world.rot.y = this->actor.shape.rot.y;
        if (this->actor.world.rot.y == this->actor.home.rot.y) {
            EnTalkGibud_SetupIdle(this);
        }
    } else {
        Math_ScaledStepToS(&this->actor.shape.rot.y, Actor_YawToPoint(&this->actor, &this->actor.home.pos), 450);
        this->actor.world.rot = this->actor.shape.rot;
    }
    if (EnTalkGibud_PlayerInRangeWithCorrectState(this, globalCtx)) {
        if (gSaveContext.save.playerForm != PLAYER_FORM_GORON && gSaveContext.save.playerForm != PLAYER_FORM_DEKU &&
            Actor_IsFacingPlayer(&this->actor, 0x38E3)) {
            EnTalkGibud_SetupWalkToPlayer(this);
        }
    }
}

void EnTalkGibud_SetupStunned(EnTalkGibud* this) {
    this->stunTimer = 10;
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;

    if (this->drawDmgEffTimer != 0) {
        Actor_SetColorFilter(&this->actor, 0, 0xC8, 0, 0x28);
    } else {
        Actor_SetColorFilter(&this->actor, 0, 0xC8, 0, 0x28);
    }

    this->actionFunc = EnTalkGibud_Stunned;
}

void EnTalkGibud_Stunned(EnTalkGibud* this, GlobalContext* globalCtx) {
    if (this->actor.colorFilterTimer == 0) {
        if (this->actor.colChkInfo.health == 0) {
            EnTalkGibud_SetupDead(this);
        } else {
            EnTalkGibud_SetupDamage(this);
        }
    }

    if (this->stunTimer != 0) {
        this->stunTimer--;
    }
}

void EnTalkGibud_SetupDamage(EnTalkGibud* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, EN_TALK_GIBUD_ANIMATION_DAMAGE);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_REDEAD_DAMAGE);
    this->stunTimer = 0;
    this->grabWaitTimer = 0;
    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    this->actor.speedXZ = -2.0f;
    this->actionFunc = EnTalkGibud_Damage;
}

void EnTalkGibud_Damage(EnTalkGibud* this, GlobalContext* globalCtx) {
    if (this->actor.speedXZ < 0.0f) {
        this->actor.speedXZ += 0.15f;
    }

    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        this->unk_3F7 = -1;
        this->actor.world.rot.y = this->actor.shape.rot.y;
        if ((this->drawDmgEffTimer > 0) && (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FIRE) &&
            (this->type == EN_TALK_GIBUD_TYPE_GIBDO)) {
            this->actor.hintId = 0x2A;
            this->actor.flags &= ~(ACTOR_FLAG_8 | ACTOR_FLAG_1);
            this->actor.flags |= (ACTOR_FLAG_4 | ACTOR_FLAG_1);
            SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gRedeadSkel, NULL, this->jointTable, this->morphTable,
                               GIBDO_LIMB_MAX);
            this->type = EN_TALK_GIBUD_TYPE_REDEAD;
        }

        if (EnTalkGibud_PlayerOutOfRange(this, globalCtx)) {
            EnTalkGibud_SetupWalkToHome(this);
        } else {
            EnTalkGibud_SetupWalkToPlayer(this);
        }
    }
}

void EnTalkGibud_SetupDead(EnTalkGibud* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, EN_TALK_GIBUD_ANIMATION_DEATH);
    this->actor.flags &= ~ACTOR_FLAG_1;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_REDEAD_DEAD);
    this->deathTimer = 0;
    this->actionFunc = EnTalkGibud_Dead;
}

void EnTalkGibud_Dead(EnTalkGibud* this, GlobalContext* globalCtx) {
    if (this->deathTimer > 300) {
        EnTalkGibud_SetupRevive(this);
    } else {
        Math_SmoothStepToS(&this->headRotation.y, 0, 1, 250, 0);
        Math_SmoothStepToS(&this->upperBodyRotation.y, 0, 1, 250, 0);
        this->deathTimer++;
    }

    if ((this->deathTimer == 20) && (this->drawDmgEffTimer > 0) && (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FIRE) &&
        (this->type == EN_TALK_GIBUD_TYPE_GIBDO)) {
        SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gRedeadSkel, NULL, this->jointTable, this->morphTable,
                           GIBDO_LIMB_MAX);
        this->type = EN_TALK_GIBUD_TYPE_REDEAD;
    }
}

void EnTalkGibud_SetupRevive(EnTalkGibud* this) {
    Animation_Change(&this->skelAnime, &gGibdoRedeadDeathAnim, -1.0f, Animation_GetLastFrame(&gGibdoRedeadDeathAnim),
                     0.0f, 2, -8.0f);
    this->actor.flags |= ACTOR_FLAG_1;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_REDEAD_REVERSE);
    this->deathTimer = 0;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = EnTalkGibud_Revive;
}

void EnTalkGibud_Revive(EnTalkGibud* this, GlobalContext* globalCtx) {
    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        this->actor.colChkInfo.health = 8;
        EnTalkGibud_SetupIdle(this);
    }
}

void EnTalkGibud_GetTextIdForRequestedItem(EnTalkGibud* this, GlobalContext* globalCtx) {
    switch (this->requestedItemIndex) {
        case EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_BLUE_POTION:
            Message_StartTextbox(globalCtx, 0x138C, &this->actor);
            this->textId = 0x138C;
            break;

        case EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_BEANS:
            Message_StartTextbox(globalCtx, 0x138D, &this->actor);
            this->textId = 0x138D;
            break;

        case EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_SPRING_WATER:
            Message_StartTextbox(globalCtx, 0x138E, &this->actor);
            this->textId = 0x138E;
            break;

        case EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_FISH:
            Message_StartTextbox(globalCtx, 0x138F, &this->actor);
            this->textId = 0x138F;
            break;

        case EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_BUGS:
            Message_StartTextbox(globalCtx, 0x1390, &this->actor);
            this->textId = 0x1390;
            break;

        case EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_DEKU_NUTS:
            Message_StartTextbox(globalCtx, 0x1391, &this->actor);
            this->textId = 0x1391;
            break;

        case EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_BOMBS:
            Message_StartTextbox(globalCtx, 0x1392, &this->actor);
            this->textId = 0x1392;
            break;

        case EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_HOT_SPRING_WATER:
            Message_StartTextbox(globalCtx, 0x1393, &this->actor);
            this->textId = 0x1393;
            break;

        case EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_BIG_POE:
            Message_StartTextbox(globalCtx, 0x1394, &this->actor);
            this->textId = 0x1394;
            break;

        case EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_MILK:
            Message_StartTextbox(globalCtx, 0x1395, &this->actor);
            this->textId = 0x1395;
            break;
    }
}

void EnTalkGibud_GetNextTextBoxId(EnTalkGibud* this, GlobalContext* globalCtx) {
    if (Message_ShouldAdvance(globalCtx)) {
        switch (this->textId) {
            case 0x1388:
                EnTalkGibud_GetTextIdForRequestedItem(this, globalCtx);
                break;

            case 0x138C:
            case 0x138D:
            case 0x138E:
            case 0x138F:
            case 0x1390:
            case 0x1391:
            case 0x1392:
            case 0x1393:
            case 0x1394:
            case 0x1395:
                // Prompts the player to choose an item
                Message_StartTextbox(globalCtx, 0xFF, &this->actor);
                this->textId = 0xFF;
                break;
        }
    }
}

s32 EnTalkGibud_PresentedItemMatchesRequest(EnTalkGibud* this, GlobalContext* globalCtx, s32 presentedItemActionParam) {
    EnTalkGibudRequestedItem* requestedItem = &sRequestedItemTable[this->requestedItemIndex];

    if (requestedItem->itemActionParam == presentedItemActionParam) {
        if (!requestedItem->isBottledItem) {
            if (AMMO(requestedItem->item) >= requestedItem->amount) {
                return EN_TALK_GIBUD_REQUESTED_ITEM_MET;
            } else {
                return EN_TALK_GIBUD_REQUESTED_ITEM_NOT_ENOUGH_AMMO;
            }
        }
        if (Interface_HasItemInBottle(requestedItem->item)) {
            return EN_TALK_GIBUD_REQUESTED_ITEM_MET;
        }
    }
    return EN_TALK_GIBUD_REQUESTED_ITEM_NOT_MET;
}

void EnTalkGibud_CheckPresentedItem(EnTalkGibud* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 itemActionParam;

    if (this->itemActionParam == PLAYER_AP_NONE) {
        itemActionParam = func_80123810(globalCtx);
        if (itemActionParam != PLAYER_AP_NONE) {
            this->itemActionParam = itemActionParam;
        }
        if (this->itemActionParam > PLAYER_AP_NONE) {
            switch (EnTalkGibud_PresentedItemMatchesRequest(this, globalCtx, this->itemActionParam)) {
                case EN_TALK_GIBUD_REQUESTED_ITEM_MET:
                    player->actor.textId = 0x138A;
                    this->textId = 0x138A;
                    break;

                case EN_TALK_GIBUD_REQUESTED_ITEM_NOT_ENOUGH_AMMO:
                    player->actor.textId = 0x138B;
                    this->textId = 0x138B;
                    break;

                case EN_TALK_GIBUD_REQUESTED_ITEM_NOT_MET:
                    player->actor.textId = 0x1389;
                    this->textId = 0x1389;
                    break;

                default:
                    break;
            }
            func_801477B4(globalCtx);
        } else if (this->itemActionParam < PLAYER_AP_NONE) {
            Message_StartTextbox(globalCtx, 0x1389, &this->actor);
            this->textId = 0x1389;
        }
    }
}

void EnTalkGibud_SetupPassiveIdle(EnTalkGibud* this) {
    this->isTalking = false;
    if (this->actionFunc != EnTalkGibud_Talk) {
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, EN_TALK_GIBUD_ANIMATION_IDLE);
    }
    this->actionFunc = EnTalkGibud_PassiveIdle;
}

/**
 * This is the idle for when the player is wearing the Gibdo Mask. The
 * Gibdo will not attempt to attack the player and can be spoken to.
 */
void EnTalkGibud_PassiveIdle(EnTalkGibud* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->isTalking = true;
        Message_StartTextbox(globalCtx, 0x1388, &this->actor);
        this->textId = 0x1388;
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_REDEAD_AIM);
        EnTalkGibud_SetupTalk(this);
    } else if (this->actor.xzDistToPlayer < 100.0f && !(this->collider.base.acFlags & AC_HIT)) {
        func_800E9250(globalCtx, &this->actor, &this->headRotation, &this->upperBodyRotation, this->actor.focus.pos);
        func_800B8614(&this->actor, globalCtx, 100.0f);
    } else {
        Math_SmoothStepToS(&this->headRotation.y, 0, 1, 100, 0);
        Math_SmoothStepToS(&this->upperBodyRotation.y, 0, 1, 100, 0);
    }
}

void EnTalkGibud_SetupTalk(EnTalkGibud* this) {
    this->itemActionParam = PLAYER_AP_NONE;
    this->actionFunc = EnTalkGibud_Talk;
}

void EnTalkGibud_Talk(EnTalkGibud* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    EnTalkGibudRequestedItem* requestedItem;

    switch (Message_GetState(&globalCtx->msgCtx)) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
            break;

        case 5:
            EnTalkGibud_GetNextTextBoxId(this, globalCtx);
            break;

        case 6:
            if (Message_ShouldAdvance(globalCtx)) {
                if (this->textId == 0x138A) {
                    // Remove the requested item/amount from the player's inventory
                    requestedItem = &sRequestedItemTable[this->requestedItemIndex];
                    if (!requestedItem->isBottledItem) {
                        func_80115A14(requestedItem->item, -requestedItem->amount);
                    } else {
                        func_80123D50(globalCtx, player, ITEM_BOTTLE, PLAYER_AP_BOTTLE);
                    }
                    player->stateFlags1 |= 0x20;
                    player->stateFlags1 |= 0x20000000;
                    this->actor.flags |= ACTOR_FLAG_100000;
                    EnTalkGibud_SetupDisappear(this);
                } else {
                    EnTalkGibud_SetupPassiveIdle(this);
                }
            }
            break;

        case 16:
            EnTalkGibud_CheckPresentedItem(this, globalCtx);
            break;
    }
    EnTalkGibud_FacePlayerWhenTalking(this, globalCtx);
}

void EnTalkGibud_SetupDisappear(EnTalkGibud* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, EN_TALK_GIBUD_ANIMATION_IDLE);
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->disappearanceTimer = 40;
    this->actionFunc = EnTalkGibud_Disappear;
}

void EnTalkGibud_Disappear(EnTalkGibud* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f velocity = sVelocity;
    Vec3f accel = sAccel;
    Vec3f pos;
    s32 numFlamesToSpawn;
    s32 i;

    if (this->disappearanceTimer > 0) {
        numFlamesToSpawn = CLAMP_MAX(this->disappearanceTimer, 3);
        for (i = 0; i < numFlamesToSpawn; i++) {
            pos = this->actor.world.pos;
            pos.x += Rand_Centered() * 20.0f;
            pos.y += 50.0f + (Rand_Centered() * 50.0f);
            pos.z += Rand_Centered() * 20.0f;
            velocity.x += Rand_Centered() * 1.5f;
            velocity.z += Rand_Centered() * 1.5f;
            func_800B3030(globalCtx, &pos, &velocity, &accel, 100, 0, 1);
        }
        func_800B9010(&this->actor, NA_SE_EN_COMMON_EXTINCT_LEV - SFX_FLAG);
        player->stateFlags1 |= 0x20000000;
        this->disappearanceTimer--;
    } else {
        if (this->switchFlag != -1) {
            Flags_SetSwitch(globalCtx, this->switchFlag);
        }
        player->stateFlags1 &= ~0x20;
        player->stateFlags1 &= ~0x20000000;
        Actor_MarkForDeath(&this->actor);
    }
}

void EnTalkGibud_FacePlayerWhenTalking(EnTalkGibud* this, GlobalContext* globalCtx) {
    s16 target = this->actor.yawTowardsPlayer;

    Math_ScaledStepToS(&this->actor.shape.rot.y, target, 0x320);
    target -= this->actor.shape.rot.y;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    Math_ScaledStepToS(&this->upperBodyRotation.y, target, 0x258);
    target -= this->upperBodyRotation.y;
    Math_ScaledStepToS(&this->headRotation.y, target, 0x190);
}

s32 EnTalkGibud_PlayerInRangeWithCorrectState(EnTalkGibud* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if ((Actor_DistanceToPoint(&player->actor, &this->actor.home.pos) < 150.0f) &&
        !(player->stateFlags1 & (0x200000 | 0x80000 | 0x40000 | 0x4000 | 0x2000 | 0x80)) &&
        !(player->stateFlags2 & (0x4000 | 0x80))) {
        return true;
    }

    return false;
}

/**
 * Gibdos/Redeads have a very short range around their home where they will
 * engage with the player. If the player is out of this range, they will simply
 * walk back to their home.
 */
s32 EnTalkGibud_PlayerOutOfRange(EnTalkGibud* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (Actor_DistanceToPoint(&player->actor, &this->actor.home.pos) >= 150.0f) {
        return true;
    }

    return false;
}

void EnTalkGibud_CheckForGibdoMask(EnTalkGibud* this, GlobalContext* globalCtx) {
    if ((this->actionFunc != EnTalkGibud_Grab) && (this->actionFunc != EnTalkGibud_Dead) &&
        (this->actionFunc != EnTalkGibud_Disappear) && (this->actionFunc != EnTalkGibud_Revive) &&
        (this->actionFunc != EnTalkGibud_Damage) && (this->actionFunc != EnTalkGibud_Talk)) {
        if (this->actionFunc != EnTalkGibud_PassiveIdle) {
            if (Player_GetMask(globalCtx) == PLAYER_MASK_GIBDO) {
                this->actor.flags &= ~(ACTOR_FLAG_4 | ACTOR_FLAG_1);
                this->actor.flags |= (ACTOR_FLAG_8 | ACTOR_FLAG_1);
                this->actor.hintId = 0xFF;
                this->actor.textId = 0;
                EnTalkGibud_SetupPassiveIdle(this);
            }
        } else if (Player_GetMask(globalCtx) != PLAYER_MASK_GIBDO) {
            this->actor.flags &= ~(ACTOR_FLAG_8 | ACTOR_FLAG_1);
            this->actor.flags |= (ACTOR_FLAG_4 | ACTOR_FLAG_1);
            if (this->type == EN_TALK_GIBUD_TYPE_REDEAD) {
                this->actor.hintId = 0x2A;
            } else {
                this->actor.hintId = 0x2D;
            }
            this->actor.textId = 0;
            EnTalkGibud_SetupWalkToHome(this);
        }
    }
}

void EnTalkGibud_TurnTowardsPlayer(EnTalkGibud* this, GlobalContext* globalCtx) {
    s16 headAngle = (this->actor.yawTowardsPlayer - this->actor.shape.rot.y) - this->upperBodyRotation.y;
    s16 upperBodyAngle = CLAMP(headAngle, -500, 500);

    headAngle -= this->headRotation.y;
    headAngle = CLAMP(headAngle, -500, 500);

    if (BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.shape.rot.y) >= 0) {
        this->upperBodyRotation.y += ABS_ALT(upperBodyAngle);
        this->headRotation.y += ABS_ALT(headAngle);
    } else {
        this->upperBodyRotation.y -= ABS_ALT(upperBodyAngle);
        this->headRotation.y -= ABS_ALT(headAngle);
    }

    this->upperBodyRotation.y = CLAMP(this->upperBodyRotation.y, -0x495F, 0x495F);
    this->headRotation.y = CLAMP(this->headRotation.y, -0x256F, 0x256F);
}

/**
 * Returns true if the Gibdo is in the correct position and rotation to start
 * performing its grab attack. Regardless of what this returns, the Gibdo is
 * moved closer to this ideal position and rotation.
 */
s32 EnTalkGibud_MoveToIdealGrabPositionAndRotation(EnTalkGibud* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f targetPos;
    f32 distanceFromTargetPos;
    f32 distanceFromTargetYOffset = 0.0f;
    s16 distanceFromTargetAngle;

    targetPos = player->actor.world.pos;
    targetPos.x -= 25.0f * Math_SinS(player->actor.shape.rot.y);
    targetPos.z -= 25.0f * Math_CosS(player->actor.shape.rot.y);
    distanceFromTargetPos = Math_Vec3f_StepTo(&this->actor.world.pos, &targetPos, 10.0f);
    distanceFromTargetAngle = Math_SmoothStepToS(&this->actor.shape.rot.y, player->actor.shape.rot.y, 1, 0x1770, 0x64);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (gSaveContext.save.playerForm == PLAYER_FORM_HUMAN) {
        distanceFromTargetYOffset = Math_SmoothStepToF(&this->actor.shape.yOffset, -1500.0f, 1.0f, 150.0f, 0.0f);
    }

    if ((distanceFromTargetPos == 0.0f) && (ABS_ALT(distanceFromTargetAngle) < 100) &&
        (distanceFromTargetYOffset == 0.0f)) {
        return true;
    }

    return false;
}

void EnTalkGibud_PlayAnimation(EnTalkGibud* this, GlobalContext* globalCtx) {
    if (this->actionFunc != EnTalkGibud_Stunned) {
        SkelAnime_Update(&this->skelAnime);
    }
}

void EnTalkGibud_MoveWithGravity(EnTalkGibud* this, GlobalContext* globalCtx) {
    if ((this->actionFunc == EnTalkGibud_WalkToPlayer) || (this->actionFunc == EnTalkGibud_WalkToHome) ||
        (this->actionFunc == EnTalkGibud_Damage)) {
        Actor_MoveWithGravity(&this->actor);
    }
}

void EnTalkGibud_UpdateDamage(EnTalkGibud* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        Actor_ApplyDamage(&this->actor);

        switch (this->actor.colChkInfo.damageEffect) {
            case EN_TALK_GIBUD_DMGEFF_DAMAGE:
                Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 8);
                if (player->unk_ADC != 0) {
                    this->unk_3F7 = player->unk_ADD;
                }
                this->actor.shape.yOffset = 0.0f;
                if (this->actor.colChkInfo.health == 0) {
                    EnTalkGibud_SetupDead(this);
                } else {
                    EnTalkGibud_SetupDamage(this);
                }
                break;

            case EN_TALK_GIBUD_DMGEFF_LIGHT_RAY:
                if (this->type == EN_TALK_GIBUD_TYPE_REDEAD) {
                    this->actor.colChkInfo.health = 0;
                    this->actor.shape.yOffset = 0.0f;
                    EnTalkGibud_SetupDead(this);
                }
                break;

            case EN_TALK_GIBUD_DMGEFF_FIRE_ARROW:
                Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 8);
                if (this->actor.colChkInfo.health == 0) {
                    EnTalkGibud_SetupDead(this);
                } else {
                    EnTalkGibud_SetupDamage(this);
                }
                this->drawDmgEffTimer = 180;
                this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
                this->drawDmgEffAlpha = 1.0f;
                break;

            case EN_TALK_GIBUD_DMGEFF_LIGHT_ARROW:
                Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 8);
                if (this->actor.colChkInfo.health == 0) {
                    EnTalkGibud_SetupDead(this);
                } else {
                    EnTalkGibud_SetupDamage(this);
                }
                this->drawDmgEffTimer = 60;
                this->drawDmgEffType = ACTOR_DRAW_DMGEFF_LIGHT_ORBS;
                this->drawDmgEffAlpha = 1.0f;
                break;

            case EN_TALK_GIBUD_DMGEFF_ZORA_MAGIC:
                if (this->actionFunc != EnTalkGibud_Grab &&
                    (this->actionFunc != EnTalkGibud_Stunned || this->stunTimer == 0)) {
                    this->drawDmgEffAlpha = 1.0f;
                    this->drawDmgEffTimer = 40;
                    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_ELECTRIC_SPARKS_SMALL;
                    EnTalkGibud_SetupStunned(this);
                }
                break;

            case EN_TALK_GIBUD_DMGEFF_STUN:
                if ((this->actionFunc != EnTalkGibud_Stunned) || this->stunTimer == 0) {
                    EnTalkGibud_SetupStunned(this);
                }
                break;
        }
    }
}

void EnTalkGibud_UpdateCollision(EnTalkGibud* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if ((this->actionFunc != EnTalkGibud_Dead) && (this->actionFunc != EnTalkGibud_Disappear) &&
        (this->actionFunc != EnTalkGibud_Revive) &&
        ((this->actionFunc != EnTalkGibud_Grab) || (this->grabState == EN_TALK_GIBUD_GRAB_RELEASE))) {
        if (this->isTalking != true) {
            Collider_UpdateCylinder(&this->actor, &this->collider);
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
            if (((this->actionFunc != EnTalkGibud_Damage) ||
                 ((player->unk_ADC != 0) && (player->unk_ADD != this->unk_3F7))) &&
                ((this->actionFunc != EnTalkGibud_Stunned) || (this->stunTimer == 0))) {
                CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
            }
        }
    }
}

/**
 * If the Gibdo is starting a grab and is touching a wall, the player is moved
 * away from that wall with this function. This can happen when the player's
 * back is close to a wall before being grabbed. The Gibdo changes its own
 * position to match the player's position at the start of a grab, so moving
 * the player like this will help prevent the Gibdo from looking like it's
 * clipping into the wall as it grabs onto the player.
 */
void EnTalkGibud_MoveGrabbedPlayerAwayFromWall(EnTalkGibud* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f targetPos;

    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, 20.0f, 35.0f, 29);
    if (this->actionFunc == EnTalkGibud_Grab && this->grabState == EN_TALK_GIBUD_GRAB_START &&
        (this->actor.bgCheckFlags & 8)) {
        targetPos = player->actor.world.pos;
        targetPos.x += 10.0f * Math_SinS(this->actor.wallYaw);
        targetPos.z += 10.0f * Math_CosS(this->actor.wallYaw);
        Math_Vec3f_StepTo(&player->actor.world.pos, &targetPos, 5.0f);
    }
}

void EnTalkGibud_UpdateEffect(EnTalkGibud* this, GlobalContext* globalCtx) {
    if (this->drawDmgEffTimer > 0) {
        this->drawDmgEffTimer--;
    }

    if (this->drawDmgEffTimer < 20) {
        Math_SmoothStepToF(&this->drawDmgEffScale, 0.0f, 0.5f, 0.03f, 0.0f);
        this->drawDmgEffAlpha = this->drawDmgEffTimer * 0.05f;
    } else {
        Math_SmoothStepToF(&this->drawDmgEffScale, 0.5f, 0.1f, 0.02f, 0.0f);
    }
}

void EnTalkGibud_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnTalkGibud* this = THIS;

    EnTalkGibud_CheckForGibdoMask(this, globalCtx);
    EnTalkGibud_UpdateDamage(this, globalCtx);

    this->actionFunc(this, globalCtx);

    EnTalkGibud_PlayAnimation(this, globalCtx);
    EnTalkGibud_MoveWithGravity(this, globalCtx);
    EnTalkGibud_UpdateCollision(this, globalCtx);
    EnTalkGibud_MoveGrabbedPlayerAwayFromWall(this, globalCtx);
    EnTalkGibud_UpdateEffect(this, globalCtx);

    this->actor.focus.pos = this->actor.world.pos;
    this->actor.focus.pos.y += 50.0f;
}

s32 EnTalkGibud_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                 Actor* thisx, Gfx** gfx) {
    EnTalkGibud* this = THIS;

    if (limbIndex == GIBDO_LIMB_UPPER_BODY_ROOT) {
        rot->y += this->upperBodyRotation.y;
    } else if (limbIndex == GIBDO_LIMB_HEAD_ROOT) {
        rot->y += this->headRotation.y;
    }

    return false;
}

void EnTalkGibud_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx,
                              Gfx** gfx) {
    EnTalkGibud* this = THIS;

    if ((this->drawDmgEffTimer != 0) &&
        ((limbIndex == GIBDO_LIMB_LEFT_THIGH) || (limbIndex == GIBDO_LIMB_LEFT_SHIN) ||
         (limbIndex == GIBDO_LIMB_LEFT_FOOT) || (limbIndex == GIBDO_LIMB_RIGHT_THIGH) ||
         (limbIndex == GIBDO_LIMB_RIGHT_SHIN) || (limbIndex == GIBDO_LIMB_RIGHT_FOOT) ||
         (limbIndex == GIBDO_LIMB_TORSO) || (limbIndex == GIBDO_LIMB_LEFT_SHOULDER_AND_UPPER_ARM) ||
         (limbIndex == GIBDO_LIMB_LEFT_FOREARM) || (limbIndex == GIBDO_LIMB_LEFT_HAND) ||
         (limbIndex == GIBDO_LIMB_RIGHT_SHOULDER_AND_UPPER_ARM) || (limbIndex == GIBDO_LIMB_RIGHT_FOREARM) ||
         (limbIndex == GIBDO_LIMB_RIGHT_HAND) || (limbIndex == GIBDO_LIMB_HEAD) || (limbIndex == GIBDO_LIMB_PELVIS))) {
        Matrix_GetStateTranslation(&this->limbPos[this->limbIndex]);
        this->limbIndex++;
    }
}

void EnTalkGibud_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnTalkGibud* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    this->limbIndex = 0;
    if (this->actor.shape.shadowAlpha == 255) {
        func_8012C28C(globalCtx->state.gfxCtx);

        gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, this->actor.shape.shadowAlpha);
        gSPSegment(POLY_OPA_DISP++, 0x08, D_801AEFA0);

        POLY_OPA_DISP = SkelAnime_DrawFlex(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                           this->skelAnime.dListCount, EnTalkGibud_OverrideLimbDraw,
                                           EnTalkGibud_PostLimbDraw, &this->actor, POLY_OPA_DISP);
    } else {
        func_8012C2DC(globalCtx->state.gfxCtx);

        gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, this->actor.shape.shadowAlpha);
        gSPSegment(POLY_XLU_DISP++, 0x08, D_801AEF88);

        POLY_XLU_DISP = SkelAnime_DrawFlex(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                           this->skelAnime.dListCount, EnTalkGibud_OverrideLimbDraw,
                                           EnTalkGibud_PostLimbDraw, &this->actor, POLY_XLU_DISP);
    }

    if (this->drawDmgEffTimer > 0) {
        Actor_DrawDamageEffects(globalCtx, &this->actor, this->limbPos, ARRAY_COUNT(this->limbPos),
                                this->drawDmgEffScale, 0.5f, this->drawDmgEffAlpha, this->drawDmgEffType);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
