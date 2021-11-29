/*
 * File: z_en_talk_gibud.c
 * Overlay: ovl_En_Talk_Gibud
 * Description: Gibdos requesting items Beneath the Well
 */

#include "z_en_talk_gibud.h"

#define FLAGS 0x00000415

#define THIS ((EnTalkGibud*)thisx)

void EnTalkGibud_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTalkGibud_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTalkGibud_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTalkGibud_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnTalkGibud_Idle(EnTalkGibud* this, GlobalContext* globalCtx);
void EnTalkGibud_SetupAttemptStun(EnTalkGibud* this);
void EnTalkGibud_AttemptStun(EnTalkGibud* this, GlobalContext* globalCtx);
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
s32 EnTalkGibud_PlayerCanBeGrabbed(EnTalkGibud* this, GlobalContext* globalCtx);
s32 EnTalkGibud_PlayerOutOfRange(EnTalkGibud* this, GlobalContext* globalCtx);
void EnTalkGibud_TurnTowardsPlayer(EnTalkGibud* this, GlobalContext* globalCtx);
s32 EnTalkGibud_MoveToIdealGrabPositionAndRotation(EnTalkGibud* this, GlobalContext* globalCtx);
void EnTalkGibud_Dead(EnTalkGibud* this, GlobalContext* globalCtx);
void EnTalkGibud_Disappear(EnTalkGibud* this, GlobalContext* globalCtx);
void EnTalkGibud_Revive(EnTalkGibud* this, GlobalContext* globalCtx);
void EnTalkGibud_Damage(EnTalkGibud* this, GlobalContext* globalCtx);
void EnTalkGibud_Talk(EnTalkGibud* this, GlobalContext* globalCtx);
void EnTalkGibud_PassiveIdle(EnTalkGibud* this, GlobalContext* globalCtx);
void EnTalkGibud_Stunned(EnTalkGibud* this, GlobalContext* globalCtx);
void EnTalkGibud_SetupDamage(EnTalkGibud* this);
void EnTalkGibud_SetupDead(EnTalkGibud* this);
void EnTalkGibud_SetupRevive(EnTalkGibud* this);
void EnTalkGibud_SetupTalk(EnTalkGibud* this);
void EnTalkGibud_SetupDisappear(EnTalkGibud* this);
void EnTalkGibud_SetupIdle(EnTalkGibud* this);
void EnTalkGibud_FacePlayerWhenTalking(EnTalkGibud* this, GlobalContext* globalCtx);

extern FlexSkeletonHeader D_060053E8; // Gibdo skeleton
extern AnimationHeader D_06006678;    // grab attack
extern AnimationHeader D_06006B08;    // release grab
extern AnimationHeader D_06006EEC;    // start grab
extern AnimationHeader D_060073A4;    // look away?
extern AnimationHeader D_06007BBC;    // wiping away tears while crouching
extern AnimationHeader D_060081A8;    // crying while crouching
extern AnimationHeader D_06009298;    // death
extern AnimationHeader D_06009900;    // damage
extern AnimationHeader D_0600A450;    // standing up from crouch
extern AnimationHeader D_0600ABE0;    // idle
extern FlexSkeletonHeader D_06010B88; // Redead skeleton
extern AnimationHeader D_060113EC;    // walk
extern AnimationHeader D_060118D8;    // pirouette (called wait_baree in MM3D)
extern AnimationHeader D_06011DB8;    // clapping dance (called wait_dance_b in MM3D)
extern AnimationHeader D_0601216C;    // squatting dance (called wait_kosakku in MM3D)

typedef struct {
    /* 0x00 */ s32 itemActionParam;
    /* 0x04 */ s32 item;
    /* 0x08 */ s32 amount;
    /* 0x0C */ s16 isBottledItem;
} EnTalkGibudRequestedItem;

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

static ActorAnimationEntry sAnimations[] = {
    { &D_06006678, 1.0f, 0.0f, 0.0f, 0, -8.0f }, { &D_06006B08, 0.5f, 0.0f, 0.0f, 3, 0.0f },
    { &D_06006EEC, 1.0f, 0.0f, 0.0f, 2, -8.0f }, { &D_060073A4, 0.0f, 0.0f, 0.0f, 2, -8.0f },
    { &D_06007BBC, 1.0f, 0.0f, 0.0f, 2, -8.0f }, { &D_060081A8, 1.0f, 0.0f, 0.0f, 0, -8.0f },
    { &D_06009298, 1.0f, 0.0f, 0.0f, 2, -8.0f }, { &D_06009900, 1.0f, 0.0f, 0.0f, 2, -8.0f },
    { &D_0600A450, 1.0f, 0.0f, 0.0f, 2, -8.0f }, { &D_0600ABE0, 1.0f, 0.0f, 0.0f, 0, -8.0f },
    { &D_060113EC, 0.4f, 0.0f, 0.0f, 1, -8.0f }, { &D_0601216C, 1.0f, 0.0f, 0.0f, 0, -8.0f },
    { &D_060118D8, 1.0f, 0.0f, 0.0f, 0, -8.0f }, { &D_06011DB8, 1.0f, 0.0f, 0.0f, 0, -8.0f },
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

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(2, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(0, 0xD),
    /* Normal arrow   */ DMG_ENTRY(0, 0xD),
    /* UNK_DMG_0x06   */ DMG_ENTRY(2, 0xF),
    /* Hookshot       */ DMG_ENTRY(0, 0xD),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(0, 0xD),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(0, 0xD),
    /* Deku launch    */ DMG_ENTRY(2, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0xC),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0xE),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 8, 0, 0, 0, MASS_HEAVY };

static EnTalkGibudRequestedItem sRequestedItemTable[] = {
    { PLAYER_AP_BOTTLE_POTION_BLUE, ITEM_POTION_BLUE, 1, true },
    { PLAYER_AP_BEAN, ITEM_BEAN, 5, false },
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
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 28.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &D_060053E8, &D_0600ABE0, this->jointTable, this->morphTable, 26);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    this->stunPreventionTimer = 0;
    this->grabState = EN_TALK_GIBUD_GRAB_START;
    this->grabPreventionTimer = 0;
    this->itemActionParam = PLAYER_AP_NONE;
    this->effectTimer = 0;
    this->effectType = 0;
    this->isTalking = false;
    this->type = EN_TALK_GIBUD_TYPE_GIBDO;
    this->requestedItemIndex = EN_TALK_GIBUD_REQUESTED_ITEM_INDEX(thisx);
    this->switchFlag = EN_TALK_GIBUD_SWITCH_FLAG(thisx);
    this->effectAlpha = 0.0f;
    this->effectScale = 0.0f;

    for (i = 0; i < ARRAY_COUNT(this->limbPos); i++) {
        this->limbPos[i] = D_801D15B0;
    }

    if (this->requestedItemIndex < 0) {
        this->requestedItemIndex = 0;
    }
    if (this->requestedItemIndex >= ARRAY_COUNT(sRequestedItemTable)) {
        this->requestedItemIndex = ARRAY_COUNT(sRequestedItemTable) - 1;
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
    func_800BDC5C(&this->skelAnime, sAnimations, EN_TALK_GIBUD_ANIMATION_IDLE);
    this->actionFunc = EnTalkGibud_Idle;
}

/**
 * This is the idle for when the player is not wearing the Gibdo Mask. The
 * Gibdo will attack the player if they get too close.
 */
void EnTalkGibud_Idle(EnTalkGibud* this, GlobalContext* globalCtx) {
    if (this->actor.xzDistToPlayer <= 150.0f && func_800B715C(globalCtx)) {
        EnTalkGibud_SetupAttemptStun(this);
    }
    Math_SmoothStepToS(&this->headRotation.y, 0, 1, 0x64, 0);
    Math_SmoothStepToS(&this->upperBodyRotation.y, 0, 1, 0x64, 0);
}

void EnTalkGibud_SetupAttemptStun(EnTalkGibud* this) {
    func_800BDC5C(&this->skelAnime, sAnimations, EN_TALK_GIBUD_ANIMATION_IDLE);
    this->actionFunc = EnTalkGibud_AttemptStun;
}

void EnTalkGibud_AttemptStun(EnTalkGibud* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 rot = this->actor.shape.rot.y + this->headRotation.y + this->upperBodyRotation.y;
    s16 yaw = BINANG_SUB(this->actor.yawTowardsPlayer, rot);

    if (ABS_ALT(yaw) < 0x2008) {
        player->actor.freezeTimer = 60;
        func_8013ECE0(this->actor.xzDistToPlayer, 255, 20, 150);
        func_80123E90(globalCtx, &this->actor);
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_REDEAD_AIM);
        EnTalkGibud_SetupWalkToPlayer(this);
    }
    EnTalkGibud_TurnTowardsPlayer(this, globalCtx);
}

void EnTalkGibud_SetupWalkToPlayer(EnTalkGibud* this) {
    func_800BDC5C(&this->skelAnime, sAnimations, EN_TALK_GIBUD_ANIMATION_WALK);
    this->actor.speedXZ = 0.4f;
    if (this->actionFunc == EnTalkGibud_AttemptStun) {
        this->stunPreventionTimer = 80;
    } else {
        this->stunPreventionTimer = 20;
    }
    this->actionFunc = EnTalkGibud_WalkToPlayer;
}

void EnTalkGibud_WalkToPlayer(EnTalkGibud* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 pad;

    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xFA);
    this->actor.world.rot = this->actor.shape.rot;
    Math_SmoothStepToS(&this->headRotation.y, 0, 1, 100, 0);
    Math_SmoothStepToS(&this->upperBodyRotation.y, 0, 1, 100, 0);
    if (EnTalkGibud_PlayerCanBeGrabbed(this, globalCtx) && Actor_IsActorFacingLink(&this->actor, 0x38E3)) {
        if (this->grabPreventionTimer == 0 && this->actor.xzDistToPlayer <= 45.0f) {
            player->actor.freezeTimer = 0;
            if (gSaveContext.playerForm == PLAYER_FORM_GORON || gSaveContext.playerForm == PLAYER_FORM_DEKU) {
                EnTalkGibud_SetupGrabFail(this);
            } else if (globalCtx->grabPlayer(globalCtx, player)) {
                EnTalkGibud_SetupGrab(this);
            }
        } else {
            if (this->stunPreventionTimer == 0) {
                player->actor.freezeTimer = 40;
                this->stunPreventionTimer = 60;
                func_8013ECE0(this->actor.xzDistToPlayer, 255, 20, 150);
                func_80123E90(globalCtx, &this->actor);
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_REDEAD_AIM);
            } else {
                this->stunPreventionTimer--;
            }
        }
    } else if (this->grabPreventionTimer == 0 && this->actor.xzDistToPlayer <= 45.0f) {
        EnTalkGibud_SetupWalkToHome(this);
    } else if (EnTalkGibud_PlayerOutOfRange(this, globalCtx)) {
        EnTalkGibud_SetupWalkToHome(this);
    }
    if (this->grabPreventionTimer > 0) {
        this->grabPreventionTimer--;
    }

    if (Animation_OnFrame(&this->skelAnime, 10.0f) || Animation_OnFrame(&this->skelAnime, 22.0f)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_RIZA_WALK);
    } else if (!(globalCtx->gameplayFrames & 0x5F)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_REDEAD_CRY);
    }
}

void EnTalkGibud_SetupGrab(EnTalkGibud* this) {
    func_800BDC5C(&this->skelAnime, sAnimations, EN_TALK_GIBUD_ANIMATION_GRAB_START);
    this->grabDamageTimer = 0;
    this->actor.flags &= -2;
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
            if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) && inPositionToAttack == true) {
                this->grabState = EN_TALK_GIBUD_GRAB_ATTACK;
                func_800BDC5C(&this->skelAnime, sAnimations, EN_TALK_GIBUD_ANIMATION_GRAB_ATTACK);
            }
            break;

        case EN_TALK_GIBUD_GRAB_ATTACK:
            if (this->grabDamageTimer == 20) {
                s16 requiredScopeTemp;

                damageSfxId = player->ageProperties->unk_92 + NA_SE_VO_LI_DAMAGE_S;
                globalCtx->damagePlayer(globalCtx, -8);
                func_800B8E58(&player->actor, damageSfxId);
                func_8013ECE0(this->actor.xzDistToPlayer, 240, 1, 12);
                this->grabDamageTimer = 0;
            } else {
                this->grabDamageTimer++;
            }

            if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_REDEAD_ATTACK);
            }

            if (!(player->stateFlags2 & 0x80) || (player->unk_B62 != 0)) {
                if ((player->unk_B62 != 0) && (player->stateFlags2 & 0x80)) {
                    player->stateFlags2 &= ~0x80;
                    player->unk_AE8 = 100;
                }
                func_800BDC5C(&this->skelAnime, sAnimations, EN_TALK_GIBUD_ANIMATION_GRAB_END);
                this->actor.flags |= 1;
                this->grabState = EN_TALK_GIBUD_GRAB_RELEASE;
                this->grabDamageTimer = 0;
            }
            break;

        case EN_TALK_GIBUD_GRAB_RELEASE:
            if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                this->grabPreventionTimer = 20;
                this->actor.shape.yOffset = 0.0f;
                EnTalkGibud_SetupWalkToPlayer(this);
            } else {
                Math_SmoothStepToF(&this->actor.shape.yOffset, 0.0f, 1.0f, 400.0f, 0.0f);
            }
            break;
    }
}

/**
 * If the Gibdo/Redead tries to grab Goron or Deku Link, it will fail to
 * do so. It will appear to take damage and shake its head side-to-side.
 */
void EnTalkGibud_SetupGrabFail(EnTalkGibud* this) {
    func_800BDC5C(&this->skelAnime, sAnimations, EN_TALK_GIBUD_ANIMATION_DAMAGE);
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_REDEAD_DAMAGE);
    this->actionFunc = EnTalkGibud_GrabFail;
    this->actor.speedXZ = -2.0f;
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
    func_800BDC5C(&this->skelAnime, sAnimations, EN_TALK_GIBUD_ANIMATION_WALK);
    this->actionFunc = EnTalkGibud_TurnAwayAndShakeHead;
}

void EnTalkGibud_TurnAwayAndShakeHead(EnTalkGibud* this, GlobalContext* globalCtx) {
    Math_SmoothStepToS(&this->actor.world.rot.y, BINANG_ROT180(this->actor.yawTowardsPlayer), 5, 3500, 200);
    this->actor.shape.rot.y = this->actor.world.rot.y;
    if (this->headShakeTimer > 60) {
        EnTalkGibud_SetupWalkToHome(this);
        this->stunPreventionTimer = 0;
    } else {
        this->headRotation.y =
            Math_SinS(this->headShakeTimer * 0xFA0) * (0x256F * ((60 - this->headShakeTimer) / 60.0f));
        this->headShakeTimer++;
    }
}

void EnTalkGibud_SetupWalkToHome(EnTalkGibud* this) {
    func_800BDC5C(&this->skelAnime, sAnimations, EN_TALK_GIBUD_ANIMATION_WALK);
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
    if (EnTalkGibud_PlayerCanBeGrabbed(this, globalCtx)) {
        if ((gSaveContext.playerForm != PLAYER_FORM_GORON) && (gSaveContext.playerForm != PLAYER_FORM_DEKU) &&
            Actor_IsActorFacingLink(&this->actor, 0x38E3)) {
            EnTalkGibud_SetupWalkToPlayer(this);
        }
    }
}

void EnTalkGibud_SetupStunned(EnTalkGibud* this) {
    this->stunTimer = 10;
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (this->effectTimer != 0) {
        func_800BCB70(&this->actor, 0U, 0xC8, 0, 0x28);
    } else {
        func_800BCB70(&this->actor, 0U, 0xC8, 0, 0x28);
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
    func_800BDC5C(&this->skelAnime, sAnimations, EN_TALK_GIBUD_ANIMATION_DAMAGE);
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_REDEAD_DAMAGE);
    this->stunTimer = 0;
    this->grabPreventionTimer = 0;
    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    this->actionFunc = EnTalkGibud_Damage;
    this->actor.speedXZ = -2.0f;
}

void EnTalkGibud_Damage(EnTalkGibud* this, GlobalContext* globalCtx) {
    if (this->actor.speedXZ < 0.0f) {
        this->actor.speedXZ += 0.15f;
    }
    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        this->unk_3F7 = -1;
        this->actor.world.rot.y = this->actor.shape.rot.y;
        if (this->effectTimer > 0 && this->effectType == 0 && this->type == EN_TALK_GIBUD_TYPE_GIBDO) {
            this->actor.hintId = 0x2A;
            this->actor.flags &= ~(0x8 | 0x1);
            this->actor.flags |= (0x4 | 0x1);
            SkelAnime_InitFlex(globalCtx, &this->skelAnime, &D_06010B88, NULL, this->jointTable, this->morphTable, 26);
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
    func_800BDC5C(&this->skelAnime, sAnimations, EN_TALK_GIBUD_ANIMATION_DEATH);
    this->actor.flags &= -2;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_REDEAD_DEAD);
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
    if (this->deathTimer == 20 && this->effectTimer > 0 && this->effectType == 0 &&
        this->type == EN_TALK_GIBUD_TYPE_GIBDO) {
        SkelAnime_InitFlex(globalCtx, &this->skelAnime, &D_06010B88, NULL, this->jointTable, this->morphTable, 26);
        this->type = EN_TALK_GIBUD_TYPE_REDEAD;
    }
}

void EnTalkGibud_SetupRevive(EnTalkGibud* this) {
    Animation_Change(&this->skelAnime, &D_06009298, -1.0f, Animation_GetLastFrame(&D_06009298), 0.0f, 2, -8.0f);
    this->actor.flags |= 1;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_REDEAD_REVERSE);
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
        case 0:
            func_801518B0(globalCtx, 0x138C, &this->actor);
            this->textId = 0x138C;
            break;
        case 1:
            func_801518B0(globalCtx, 0x138D, &this->actor);
            this->textId = 0x138D;
            break;
        case 2:
            func_801518B0(globalCtx, 0x138E, &this->actor);
            this->textId = 0x138E;
            break;
        case 3:
            func_801518B0(globalCtx, 0x138F, &this->actor);
            this->textId = 0x138F;
            break;
        case 4:
            func_801518B0(globalCtx, 0x1390, &this->actor);
            this->textId = 0x1390;
            break;
        case 5:
            func_801518B0(globalCtx, 0x1391, &this->actor);
            this->textId = 0x1391;
            break;
        case 6:
            func_801518B0(globalCtx, 0x1392, &this->actor);
            this->textId = 0x1392;
            break;
        case 7:
            func_801518B0(globalCtx, 0x1393, &this->actor);
            this->textId = 0x1393;
            break;
        case 8:
            func_801518B0(globalCtx, 0x1394, &this->actor);
            this->textId = 0x1394;
            break;
        case 9:
            func_801518B0(globalCtx, 0x1395, &this->actor);
            this->textId = 0x1395;
            break;
    }
}

void func_80AFFC10(EnTalkGibud* this, GlobalContext* globalCtx) {
    if (func_80147624(globalCtx)) {
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
                func_801518B0(globalCtx, 0xFF, &this->actor);
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
        if (func_80114F2C(requestedItem->item)) {
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
            func_801518B0(globalCtx, 0x1389, &this->actor);
            this->textId = 0x1389;
        }
    }
}

void EnTalkGibud_SetupPassiveIdle(EnTalkGibud* this) {
    this->isTalking = false;
    if (this->actionFunc != EnTalkGibud_Talk) {
        func_800BDC5C(&this->skelAnime, sAnimations, EN_TALK_GIBUD_ANIMATION_IDLE);
    }
    this->actionFunc = EnTalkGibud_PassiveIdle;
}

/**
 * This is the idle for when the player is wearing the Gibdo Mask. The
 * Gibdo will not attempt to attack the player and can be spoken to.
 */
void EnTalkGibud_PassiveIdle(EnTalkGibud* this, GlobalContext* globalCtx) {
    if (func_800B84D0(&this->actor, globalCtx)) {
        this->isTalking = true;
        func_801518B0(globalCtx, 0x1388, &this->actor);
        this->textId = 0x1388;
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_REDEAD_AIM);
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

    switch (func_80152498(&globalCtx->msgCtx)) {
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
            func_80AFFC10(this, globalCtx);
            break;
        case 6:
            if (func_80147624(globalCtx)) {
                if (this->textId == 0x138A) {
                    requestedItem = &sRequestedItemTable[this->requestedItemIndex];
                    if (!requestedItem->isBottledItem) {
                        func_80115A14(requestedItem->item, -requestedItem->amount);
                    } else {
                        func_80123D50(globalCtx, player, ITEM_BOTTLE, PLAYER_AP_BOTTLE);
                    }
                    player->stateFlags1 |= 0x20;
                    player->stateFlags1 |= 0x20000000;
                    this->actor.flags |= 0x100000;
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
    func_800BDC5C(&this->skelAnime, sAnimations, EN_TALK_GIBUD_ANIMATION_IDLE);
    this->actor.flags &= -2;
    this->disappearanceTimer = 40;
    this->actionFunc = EnTalkGibud_Disappear;
}

void EnTalkGibud_Disappear(EnTalkGibud* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f velocity = sVelocity;
    Vec3f accel = sAccel;
    Vec3f pos;
    s32 phi_s3;
    s32 i;

    if (this->disappearanceTimer > 0) {
        phi_s3 = CLAMP_MAX(this->disappearanceTimer, 3);
        for (i = 0; i < phi_s3; i++) {
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
            Actor_SetSwitchFlag(globalCtx, this->switchFlag);
        }
        player->stateFlags1 &= ~0x20;
        player->stateFlags1 &= ~0x20000000;
        Actor_MarkForDeath(&this->actor);
    }
}

void EnTalkGibud_FacePlayerWhenTalking(EnTalkGibud* this, GlobalContext* globalCtx) {
    s16 temp;

    temp = this->actor.yawTowardsPlayer;
    Math_ScaledStepToS(&this->actor.shape.rot.y, temp, 0x320);
    temp -= this->actor.shape.rot.y;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    Math_ScaledStepToS(&this->upperBodyRotation.y, temp, 0x258);
    temp -= this->upperBodyRotation.y;
    Math_ScaledStepToS(&this->headRotation.y, temp, 0x190);
}

s32 EnTalkGibud_PlayerCanBeGrabbed(EnTalkGibud* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if ((Actor_DistanceToPoint(&player->actor, &this->actor.home.pos) < 150.0f) && !(player->stateFlags1 & 0x2C6080) &&
        !(player->stateFlags2 & 0x4080)) {
        return true;
    }

    return false;
}

s32 EnTalkGibud_PlayerOutOfRange(EnTalkGibud* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (Actor_DistanceToPoint(&player->actor, &this->actor.home.pos) >= 150.0f) {
        return true;
    }

    return false;
}

void EnTalkGibud_CheckForGibdoMask(EnTalkGibud* this, GlobalContext* globalCtx) {
    if (this->actionFunc != EnTalkGibud_Grab && this->actionFunc != EnTalkGibud_Dead &&
        this->actionFunc != EnTalkGibud_Disappear && this->actionFunc != EnTalkGibud_Revive &&
        this->actionFunc != EnTalkGibud_Damage && this->actionFunc != EnTalkGibud_Talk) {
        if (this->actionFunc != EnTalkGibud_PassiveIdle) {
            if (Player_GetMask(globalCtx) == PLAYER_MASK_GIBDO) {
                this->actor.flags &= ~(0x4 | 0x1);
                this->actor.flags |= (0x8 | 0x1);
                this->actor.hintId = 0xFF;
                this->actor.textId = 0;
                EnTalkGibud_SetupPassiveIdle(this);
            }
        } else if (Player_GetMask(globalCtx) != PLAYER_MASK_GIBDO) {
            this->actor.flags &= ~(0x8 | 0x1);
            this->actor.flags |= (0x4 | 0x1);
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
    s16 temp_v0 = (this->actor.yawTowardsPlayer - this->actor.shape.rot.y) - this->upperBodyRotation.y;
    s16 phi_a2 = CLAMP(temp_v0, -500, 500);

    temp_v0 -= this->headRotation.y;
    temp_v0 = CLAMP(temp_v0, -500, 500);

    if (BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.shape.rot.y) >= 0) {
        this->upperBodyRotation.y += ABS_ALT(phi_a2);
        this->headRotation.y += ABS_ALT(temp_v0);
    } else {
        this->upperBodyRotation.y -= ABS_ALT(phi_a2);
        this->headRotation.y -= ABS_ALT(temp_v0);
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
    if (gSaveContext.playerForm == PLAYER_FORM_HUMAN) {
        distanceFromTargetYOffset = Math_SmoothStepToF(&this->actor.shape.yOffset, -1500.0f, 1.0f, 150.0f, 0.0f);
    }

    if (distanceFromTargetPos == 0.0f && ABS_ALT(distanceFromTargetAngle) < 100 && distanceFromTargetYOffset == 0.0f) {
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
    if (this->actionFunc == EnTalkGibud_WalkToPlayer || this->actionFunc == EnTalkGibud_WalkToHome ||
        this->actionFunc == EnTalkGibud_Damage) {
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    }
}

void EnTalkGibud_CheckDamageEffect(EnTalkGibud* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        Actor_ApplyDamage(&this->actor);

        switch (this->actor.colChkInfo.damageEffect) {
            case 0xF:
                func_800BCB70(&this->actor, 0x4000, 255, 0, 8);
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

            case 0xE:
                if (this->type == EN_TALK_GIBUD_TYPE_REDEAD) {
                    this->actor.colChkInfo.health = 0;
                    this->actor.shape.yOffset = 0.0f;
                    EnTalkGibud_SetupDead(this);
                }
                break;

            case 0x2:
                func_800BCB70(&this->actor, 0x4000, 255, 0, 8);
                if (this->actor.colChkInfo.health == 0) {
                    EnTalkGibud_SetupDead(this);
                } else {
                    EnTalkGibud_SetupDamage(this);
                }
                this->effectTimer = 180;
                this->effectType = 0;
                this->effectAlpha = 1.0f;
                break;

            case 0x4:
                func_800BCB70(&this->actor, 0x4000, 255, 0, 8);
                if (this->actor.colChkInfo.health == 0) {
                    EnTalkGibud_SetupDead(this);
                } else {
                    EnTalkGibud_SetupDamage(this);
                }
                this->effectTimer = 60;
                this->effectType = 20;
                this->effectAlpha = 1.0f;
                break;

            case 0xC:
                if ((this->actionFunc != EnTalkGibud_Grab) &&
                    ((this->actionFunc != EnTalkGibud_Stunned) || (this->stunTimer == 0))) {
                    this->effectAlpha = 1.0f;
                    this->effectTimer = 40;
                    this->effectType = 30;
                    EnTalkGibud_SetupStunned(this);
                }
                break;

            case 0x1:
                if ((this->actionFunc != EnTalkGibud_Stunned) || (this->stunTimer == 0)) {
                    EnTalkGibud_SetupStunned(this);
                }
                break;
        }
    }
}

void EnTalkGibud_CheckCollision(EnTalkGibud* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (this->actionFunc != EnTalkGibud_Dead && this->actionFunc != EnTalkGibud_Disappear &&
        this->actionFunc != EnTalkGibud_Revive &&
        (this->actionFunc != EnTalkGibud_Grab || this->grabState == EN_TALK_GIBUD_GRAB_RELEASE)) {
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
    if (this->effectTimer > 0) {
        this->effectTimer--;
    }
    if (this->effectTimer < 20) {
        Math_SmoothStepToF(&this->effectScale, 0.0f, 0.5f, 0.03f, 0.0f);
        this->effectAlpha = this->effectTimer * 0.05f;
    } else {
        Math_SmoothStepToF(&this->effectScale, 0.5f, 0.1f, 0.02f, 0.0f);
    }
}

void EnTalkGibud_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnTalkGibud* this = THIS;

    EnTalkGibud_CheckForGibdoMask(this, globalCtx);
    EnTalkGibud_CheckDamageEffect(this, globalCtx);
    this->actionFunc(this, globalCtx);
    EnTalkGibud_PlayAnimation(this, globalCtx);
    EnTalkGibud_MoveWithGravity(this, globalCtx);
    EnTalkGibud_CheckCollision(this, globalCtx);
    EnTalkGibud_MoveGrabbedPlayerAwayFromWall(this, globalCtx);
    EnTalkGibud_UpdateEffect(this, globalCtx);
    this->actor.focus.pos = this->actor.world.pos;
    this->actor.focus.pos.y += 50.0f;
}

s32 EnTalkGibud_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                 Actor* thisx, Gfx** gfx) {
    EnTalkGibud* this = THIS;

    if (limbIndex == 12) {
        rot->y += this->upperBodyRotation.y;
    } else if (limbIndex == 23) {
        rot->y += this->headRotation.y;
    }

    return false;
}

void EnTalkGibud_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx,
                              Gfx** gfx) {
    EnTalkGibud* this = THIS;

    if ((this->effectTimer != 0) &&
        ((limbIndex == 3) || (limbIndex == 4) || (limbIndex == 6) || (limbIndex == 8) || (limbIndex == 9) ||
         (limbIndex == 11) || (limbIndex == 14) || (limbIndex == 16) || (limbIndex == 17) || (limbIndex == 18) ||
         (limbIndex == 20) || (limbIndex == 21) || (limbIndex == 22) || (limbIndex == 24) || (limbIndex == 25))) {
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
    if (this->effectTimer > 0) {
        func_800BE680(globalCtx, &this->actor, this->limbPos, ARRAY_COUNT(this->limbPos), this->effectScale, 0.5f,
                      this->effectAlpha, this->effectType);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
