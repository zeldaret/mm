/*
 * File: z_en_raf.c
 * Overlay: ovl_En_Raf
 * Description: Carnivorous Lily Pad
 */

#include "z_en_raf.h"

#define FLAGS (ACTOR_FLAG_8000000)

#define THIS ((EnRaf*)thisx)

void EnRaf_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRaf_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRaf_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRaf_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnRaf_SetupIdle(EnRaf* this);
void EnRaf_Idle(EnRaf* this, GlobalContext* globalCtx);
void func_80A17414(EnRaf* this);
void func_80A17464(EnRaf* this, GlobalContext* globalCtx);
void func_80A17530(EnRaf* this);
void func_80A175E4(EnRaf* this, GlobalContext* globalCtx);
void func_80A17848(EnRaf* this, GlobalContext* globalCtx);
void func_80A178A0(EnRaf* this, GlobalContext* globalCtx);
void EnRaf_Explode(EnRaf* this, GlobalContext* globalCtx);
void EnRaf_PostDetonation(EnRaf* this, GlobalContext* globalCtx);
void EnRaf_Convulse(EnRaf* this, GlobalContext* globalCtx);
void EnRaf_SetupDissolve(EnRaf* this);
void EnRaf_Dissolve(EnRaf* this, GlobalContext* globalCtx);
void EnRaf_SetupDeadIdle(EnRaf* this);
void EnRaf_DeadIdle(EnRaf* this, GlobalContext* globalCtx);
void EnRaf_InitializeParticle(EnRaf* this, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, f32 arg4, s16 arg5);
void EnRaf_UpdateParticles(EnRaf* this, GlobalContext* globalCtx);
void EnRaf_DrawParticles(EnRaf* this, GlobalContext* globalCtx);

typedef enum {
    /* 0 */ EN_RAF_ANIMATION_IDLE,
    /* 1 */ EN_RAF_ANIMATION_CLOSE,
    /* 2 */ EN_RAF_ANIMATION_CHEW,
    /* 3 */ EN_RAF_ANIMATION_SPIT,
    /* 4 */ EN_RAF_ANIMATION_CONVULSE,
    /* 5 */ EN_RAF_ANIMATION_DEATH,
} EnRafAnimationIndex;

typedef enum {
    /* 0 */ EN_RAF_ACTION_IDLE,
    /* 1 */ EN_RAF_ACTION_UNK_1,
    /* 2 */ EN_RAF_ACTION_UNK_2,
    /* 3 */ EN_RAF_ACTION_UNK_3,
    /* 4 */ EN_RAF_ACTION_EXPLODE,
    /* 5 */ EN_RAF_ACTION_CONVULSE,
    /* 6 */ EN_RAF_ACTION_DISSOLVE,
    /* 7 */ EN_RAF_ACTION_DEAD_IDLE,
} EnRafAction;

typedef enum {
    /* 0 */ EN_RAF_GRAB_TARGET_PLAYER,
    /* 1 */ EN_RAF_GRAB_TARGET_EXPLOSIVE,
    /* 2 */ EN_RAF_GRAB_TARGET_GORON_PLAYER
} EnRafGrabTarget;

const ActorInit En_Raf_InitVars = {
    ACTOR_EN_RAF,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_RAF,
    sizeof(EnRaf),
    (ActorFunc)EnRaf_Init,
    (ActorFunc)EnRaf_Destroy,
    (ActorFunc)EnRaf_Update,
    (ActorFunc)EnRaf_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_ENEMY,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x04, 0x10 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 50, 10, -10, { 0, 0, 0 } },
};

static u8 sTeethClearPixelTableFirstPass[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
    1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0,
};

static u8 sTeethClearPixelTableSecondPass[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

static u8 sPetalClearPixelTableFirstPass[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1,
    1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0,
    1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0,
    0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1,
    1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1,
    1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1,
    1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0,
    0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0,
    0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0,
    1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0,
    0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1,
};

static u8 sPetalClearPixelTableSecondPass[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0xF),
    /* Deku Stick     */ DMG_ENTRY(0, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xE),
    /* Zora boomerang */ DMG_ENTRY(0, 0xF),
    /* Normal arrow   */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(0, 0xF),
    /* Sword          */ DMG_ENTRY(0, 0xF),
    /* Goron pound    */ DMG_ENTRY(0, 0xF),
    /* Fire arrow     */ DMG_ENTRY(0, 0xF),
    /* Ice arrow      */ DMG_ENTRY(0, 0xF),
    /* Light arrow    */ DMG_ENTRY(0, 0xF),
    /* Goron spikes   */ DMG_ENTRY(0, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0xF),
    /* Deku bubble    */ DMG_ENTRY(0, 0xF),
    /* Deku launch    */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0xF),
    /* Zora barrier   */ DMG_ENTRY(0, 0xF),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0xF),
    /* Zora punch     */ DMG_ENTRY(0, 0xF),
    /* Spin attack    */ DMG_ENTRY(0, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0xF),
};

static Vec3f D_80A193BC = { 1.0f, 1.0f, 1.0f };

static AnimationHeader* sAnimations[] = {
    &gCarnivorousLilyPadSpitAnim, &gCarnivorousLilyPadCloseAnim,    &gCarnivorousLilyPadChewAnim,
    &gCarnivorousLilyPadSpitAnim, &gCarnivorousLilyPadConvulseAnim, &gCarnivorousLilyPadDeathAnim,
};

static u8 sAnimationModes[] = {
    ANIMMODE_ONCE, ANIMMODE_ONCE, ANIMMODE_LOOP, ANIMMODE_ONCE, ANIMMODE_LOOP, ANIMMODE_ONCE,
};

static Vec3f D_80A193E8 = { 1.0f, 1.0f, 1.0f };

static Vec3f D_80A193F4 = { 0.0f, 0.0f, 0.0f };

static Vec3f D_80A19400 = { 0.0f, 0.0f, 0.0f };

static Vec3f D_80A1940C = { 1.0f, 1.0f, 1.0f };

static s16 D_80A19418[] = { 0, 4, 6 };

static Vec3f D_80A19420[] = {
    { 1.0f, 1.0f, 1.0f },
    { 1.0f, 2.0f, 1.0f },
    { 0.0f, 1.5f, 0.7f },
};

static Vec3f D_80A19444[] = {
    { 1.0f, 1.0f, 1.0f },
    { 3.0f, 2.0f, 1.5f },
    { 1.5f, 1.2f, 0.8f },
};

static s16 D_80A19468[] = { 0, 7, 9, 13, 19 };

static Vec3f D_80A19474[] = {
    { 1.0f, 1.5f, 0.7f }, { 1.0f, 2.0f, 1.5f }, { 1.0f, 2.0f, 0.5f }, { 1.0f, 2.0f, 0.5f }, { 1.0f, 1.0f, 1.0f },
};

static Vec3f D_80A194B0[] = {
    { 1.5f, 1.5f, 1.7f }, { 1.5f, 1.5f, 1.3f }, { 3.0f, 1.0f, 0.5f }, { 1.0f, 1.0f, 0.5f }, { 1.0f, 1.0f, 1.0f },
};

/**
 * Sets the `index`th pixel of the trap teeth texture to 0 (transparent black)
 * according to the `clearPixelTable`
 */
void EnRaf_ClearPixelsTeeth(u16* texture, u8* clearPixelTable, s32 index) {
    if ((index < 0x40) && (clearPixelTable[index] != 0)) {
        texture[index] = 0;
    }
}

/**
 * Sets the `index`th pixel of the trap petal texture to 0 (transparent black)
 * according to the `clearPixelTable`
 */
void EnRaf_ClearPixelsPetal(u16* texture, u8* clearPixelTable, s32 index) {
    if (clearPixelTable[index] != 0) {
        texture[index] = 0;
    }
}

void EnRaf_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnRaf* this = THIS;
    Vec3f sp60 = D_80A193BC;
    s32 i;
    s32 j;
    CollisionHeader* colHeader = NULL;

    DynaPolyActor_Init(&this->dyna, 0);
    CollisionHeader_GetVirtual(&gCarnivorousLilyPadCol, &colHeader);
    this->dyna.bgId = DynaPoly_SetBgActor(globalCtx, &globalCtx->colCtx.dyna, &this->dyna.actor, colHeader);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->dyna.actor, &sCylinderInit);
    this->dyna.actor.targetMode = 3;
    this->dyna.actor.colChkInfo.mass = MASS_IMMOVABLE;
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gCarnivorousLilyPadSkel, &gCarnivorousLilyPadSpitAnim,
                       this->jointTable, this->morphTable, CARNIVOROUS_LILY_PAD_LIMB_MAX);
    for (i = 0; i < 12; i++) {
        Math_Vec3f_Copy(&this->targetLimbScale[i], &sp60);
        Math_Vec3f_Copy(&this->limbScale[i], &sp60);
    }

    this->dyna.actor.colChkInfo.damageTable = &sDamageTable;
    this->dyna.actor.colChkInfo.health = BREG(1) + 2;
    this->type = EN_RAF_GET_TYPE(&this->dyna.actor);
    this->reviveTimer = EN_RAF_GET_REVIVE_TIMER(&this->dyna.actor);
    this->switchFlag = EN_RAF_GET_SWITCH_FLAG(&this->dyna.actor);
    if (this->switchFlag == 0x7F) {
        this->switchFlag = -1;
    }

    if (this->reviveTimer == 31) {
        this->reviveTimer = -1;
    } else {
        this->reviveTimer = 30;
    }

    if (((this->switchFlag >= 0) || (this->type == EN_RAF_TYPE_ALEADY_DEAD) ||
         (gSaveContext.save.weekEventReg[12] & 1)) &&
        ((Flags_GetSwitch(globalCtx, this->switchFlag)) || (this->type == EN_RAF_TYPE_ALEADY_DEAD))) {
        for (j = 2; j < 11; j++) {
            Math_Vec3f_Copy(&this->limbScale[j], &gZeroVec3f);
            Math_Vec3f_Copy(&this->targetLimbScale[j], &gZeroVec3f);
        }

        EnRaf_SetupDeadIdle(this);
    } else {
        this->bobPhase = Rand_ZeroFloat(1.0f) * 20000.0f;
        Actor_SetScale(&this->dyna.actor, 0.01f);
        EnRaf_SetupIdle(this);
    }
}

void EnRaf_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnRaf* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnRaf_ChangeAnimation(EnRaf* this, s32 index) {
    f32 startFrame = 0.0f;
    f32 playSpeed = 1.0f;

    this->endFrame = Animation_GetLastFrame(sAnimations[index]);
    if (index == EN_RAF_ANIMATION_IDLE) {
        startFrame = this->endFrame;
    } else if (index == EN_RAF_ANIMATION_CLOSE) {
        playSpeed = 2.0f;
    }

    Animation_Change(&this->skelAnime, sAnimations[index], playSpeed, startFrame, this->endFrame,
                     sAnimationModes[index], -4.0f);
}

void EnRaf_SetupIdle(EnRaf* this) {
    Vec3f sp3C = D_80A193E8;
    s32 i;

    EnRaf_ChangeAnimation(this, EN_RAF_ANIMATION_IDLE);
    for (i = 2; i < 11; i++) {
        Math_Vec3f_Copy(&this->targetLimbScale[i], &sp3C);
    }

    this->unk_3C2 = 3;
    this->action = EN_RAF_ACTION_IDLE;
    this->actionFunc = EnRaf_Idle;
}

void EnRaf_Idle(EnRaf* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Actor* explosive;
    f32 xDiff;
    f32 yDiff;
    f32 zDiff;

    if (this->timer == 0) {
        if ((player->transformation != PLAYER_FORM_DEKU) &&
            (this->dyna.actor.xzDistToPlayer < (BREG(48) + 80.0f) && (player->invincibilityTimer == 0) &&
             DynaPolyActor_IsInRidingMovingState(&this->dyna) && !(player->stateFlags1 & 0x8000000) &&
             globalCtx->grabPlayer(globalCtx, player))) {
            player->actor.parent = &this->dyna.actor;
            this->grabTarget = EN_RAF_GRAB_TARGET_PLAYER;

            if (player->transformation == PLAYER_FORM_GORON) {
                this->grabTarget = EN_RAF_GRAB_TARGET_GORON_PLAYER;
            } else {
                player->unk_AE8 = 50;
            }

            this->playerYRotWhenGrabbed = player->actor.world.rot.y;
            func_80A17414(this);
            return;
        }

        if ((globalCtx->gameplayFrames % 2) == 0) {
            return;
        }

        explosive = globalCtx->actorCtx.actorLists[ACTORCAT_EXPLOSIVES].first;
        while (explosive != NULL) {
            if ((EnRaf*)explosive == this) {
                explosive = explosive->next;
                continue;
            }

            xDiff = explosive->world.pos.x - this->dyna.actor.world.pos.x;
            yDiff = explosive->world.pos.y - this->dyna.actor.world.pos.y;
            zDiff = explosive->world.pos.z - this->dyna.actor.world.pos.z;
            if ((fabsf(xDiff) < 80.0f) && (fabsf(yDiff) < 30.0f) && (fabsf(zDiff) < 80.0f) &&
                (explosive->update != NULL) && (explosive->velocity.y != 0.0f)) {
                Actor_MarkForDeath(explosive);
                this->grabTarget = EN_RAF_GRAB_TARGET_EXPLOSIVE;
                this->collider.dim.radius = 30;
                this->collider.dim.height = 90;
                this->collider.dim.yShift = -10;
                func_80A17414(this);
                return;
            }

            explosive = explosive->next;
        }
    }
}

void func_80A17414(EnRaf* this) {
    EnRaf_ChangeAnimation(this, EN_RAF_ANIMATION_CLOSE);
    this->unk_3C2 = 1;
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EN_SUISEN_DRINK);
    this->action = EN_RAF_ACTION_UNK_1;
    this->actionFunc = func_80A17464;
}

void func_80A17464(EnRaf* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    f32 curFrame = this->skelAnime.curFrame;

    if ((this->grabTarget != EN_RAF_GRAB_TARGET_EXPLOSIVE) && (player->stateFlags2 & 0x80) &&
        (&this->dyna.actor == player->actor.parent)) {
        Math_ApproachF(&player->actor.world.pos.x, this->dyna.actor.world.pos.x, 0.3f, 10.0f);
        Math_ApproachF(&player->actor.world.pos.y, this->dyna.actor.world.pos.y, 0.3f, 10.0f);
        Math_ApproachF(&player->actor.world.pos.z, this->dyna.actor.world.pos.z, 0.3f, 10.0f);
    }

    if (this->endFrame <= curFrame) {
        func_80A17530(this);
    }
}

void func_80A17530(EnRaf* this) {
    s32 i;

    EnRaf_ChangeAnimation(this, EN_RAF_ANIMATION_CHEW);
    this->chewCount = 0;
    for (i = 0; i < 12; i++) {
        this->unk_354[i].x = Rand_S16Offset(8, 8) << 8;
        this->unk_354[i].y = Rand_S16Offset(8, 8) << 8;
        this->unk_354[i].z = Rand_S16Offset(8, 8) << 8;
    }

    this->unk_3C2 = 2;
    this->action = EN_RAF_ACTION_UNK_2;
    this->actionFunc = func_80A175E4;
}

void func_80A175E4(EnRaf* this, GlobalContext* globalCtx) {
    f32 temp;
    f32 curFrame;
    Player* player = GET_PLAYER(globalCtx);

    curFrame = this->skelAnime.curFrame;
    temp = (BREG(51) / 100.0f) + 0.2f;
    Math_ApproachF(&this->unk_3A4, temp, 0.2f, 0.03f);

    if ((player->stateFlags2 & 0x80) && (this->grabTarget != EN_RAF_GRAB_TARGET_EXPLOSIVE) &&
        (&this->dyna.actor == player->actor.parent)) {
        Math_ApproachF(&player->actor.world.pos.x, this->dyna.actor.world.pos.x, 0.3f, 10.0f);
        Math_ApproachF(&player->actor.world.pos.y, this->dyna.actor.world.pos.y, 0.3f, 10.0f);
        Math_ApproachF(&player->actor.world.pos.z, this->dyna.actor.world.pos.z, 0.3f, 10.0f);
    }

    if (this->endFrame <= curFrame) {
        if (BREG(52) == 0) {
            this->chewCount++;
        }

        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EN_SUISEN_EAT);
        switch (this->grabTarget) {
            case EN_RAF_GRAB_TARGET_PLAYER:
                globalCtx->damagePlayer(globalCtx, -2);
                func_800B8E58((Player*)this, player->ageProperties->unk_92 + NA_SE_VO_LI_DAMAGE_S);
                CollisionCheck_GreenBlood(globalCtx, NULL, &player->actor.world.pos);
                if ((this->chewCount > (BREG(53) + 5)) || !(player->stateFlags2 & 0x80)) {
                    player->actor.freezeTimer = 10;
                    func_80A17848(this, globalCtx);
                    return;
                }
                break;

            case EN_RAF_GRAB_TARGET_EXPLOSIVE:
                Actor_ApplyDamage(&this->dyna.actor);
                if (this->chewCount > (BREG(54) + 4)) {
                    EnRaf_Explode(this, globalCtx);
                    return;
                }
                break;

            case EN_RAF_GRAB_TARGET_GORON_PLAYER:
                if (this->chewCount > (BREG(54) + 4)) {
                    player->actor.parent = NULL;
                    player->unk_AE8 = 1000;
                    EnRaf_Explode(this, globalCtx);
                }
                break;
        }
    }
}

void func_80A17848(EnRaf* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    EnRaf_ChangeAnimation(this, EN_RAF_ANIMATION_SPIT);
    player->actor.freezeTimer = 10;
    this->unk_3C2 = 3;
    this->action = EN_RAF_ACTION_UNK_3;
    this->actionFunc = func_80A178A0;
}

void func_80A178A0(EnRaf* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    f32 curFrame = this->skelAnime.curFrame;

    if (Animation_OnFrame(&this->skelAnime, 10.0f)) {
        player->actor.freezeTimer = 0;
        player->actor.parent = NULL;
        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EN_SUISEN_THROW);
        func_800B8D50(globalCtx, &this->dyna.actor, BREG(55) + 3.0f, this->playerYRotWhenGrabbed + 0x8000,
                      BREG(56) + 10.0f, 0);
    } else if (curFrame < 10.0f) {
        player->actor.freezeTimer = 10;
    }

    if (this->endFrame <= curFrame) {
        this->unk_3C2 = 3;
        this->action = EN_RAF_ACTION_IDLE;
        this->timer = 20;
        this->actionFunc = EnRaf_Idle;
    }
}

void EnRaf_Explode(EnRaf* this, GlobalContext* globalCtx) {
    Vec3f spAC = D_80A193F4;
    Vec3f spA0 = D_80A19400;
    Vec3f sp94;
    s32 i;
    s32 pad;

    this->action = EN_RAF_ACTION_EXPLODE;
    Math_Vec3f_Copy(&sp94, &this->dyna.actor.world.pos);
    sp94.y += 10.0f;
    Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, sp94.x, sp94.y, sp94.z, 0, 0, 0,
                CLEAR_TAG_SMALL_EXPLOSION);
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_IT_BOMB_EXPLOSION);
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EN_SUISEN_DEAD);
    if (this->switchFlag >= 0) {
        Flags_SetSwitch(globalCtx, this->switchFlag);
    }

    this->unk_3C2 = 0;
    for (i = 0; i < BREG(57) + 30; i++) {
        spA0.x = (Rand_ZeroOne() - 0.5f) * 0.5f;
        spA0.y = -0.3f;
        spA0.z = (Rand_ZeroOne() - 0.5f) * 0.5f;
        spAC.x = Rand_ZeroOne() - 0.5f;
        spAC.y = Rand_ZeroOne() * 10.0f;
        spAC.z = Rand_ZeroOne() - 0.5f;
        EnRaf_InitializeParticle(this, &this->dyna.actor.world.pos, &spAC, &spA0,
                                 (Rand_ZeroFloat(1.0f) / 500.0f) + 0.002f, 90);
    }

    for (i = 2; i < 11; i++) {
        Math_Vec3f_Copy(&this->targetLimbScale[i], &gZeroVec3f);
    }

    this->timer = 5;
    if (this->grabTarget == EN_RAF_GRAB_TARGET_EXPLOSIVE) {
        func_800BC154(globalCtx, &globalCtx->actorCtx, &this->dyna.actor, 5);
        this->dyna.actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_4);
    }

    this->actionFunc = EnRaf_PostDetonation;
}

void EnRaf_PostDetonation(EnRaf* this, GlobalContext* globalCtx) {
    if (this->timer == 0) {
        this->collider.dim.radius = 50;
        this->collider.dim.height = 10;
        func_800BC154(globalCtx, &globalCtx->actorCtx, &this->dyna.actor, 6);
        this->dyna.actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_4);
        EnRaf_SetupDeadIdle(this);
    } else if (this->grabTarget == EN_RAF_GRAB_TARGET_EXPLOSIVE) {
        this->collider.dim.radius = 80;
        this->collider.dim.height = 50;
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

void EnRaf_SetupConvulse(EnRaf* this) {
    EnRaf_ChangeAnimation(this, EN_RAF_ANIMATION_CONVULSE);
    this->chewCount = 0;
    this->action = EN_RAF_ACTION_CONVULSE;
    this->actionFunc = EnRaf_Convulse;
}

void EnRaf_Convulse(EnRaf* this, GlobalContext* globalCtx) {
    f32 curFrame = this->skelAnime.curFrame;

    if (this->endFrame <= curFrame) {
        this->chewCount++;
        if (this->chewCount > (BREG(2) + 2)) {
            if (this->switchFlag >= 0) {
                Flags_SetSwitch(globalCtx, this->switchFlag);
            }

            EnRaf_SetupDissolve(this);
        }
    }
}

void EnRaf_SetupDissolve(EnRaf* this) {
    EnRaf_ChangeAnimation(this, EN_RAF_ANIMATION_DEATH);
    this->action = EN_RAF_ACTION_DISSOLVE;
    this->dissolveTimer = 0;
    this->actionFunc = EnRaf_Dissolve;
}

void EnRaf_Dissolve(EnRaf* this, GlobalContext* globalCtx) {
    f32 curFrame = this->skelAnime.curFrame;
    s32 i;

    if (this->endFrame <= curFrame) {
        this->dissolveTimer++;
        if (this->dissolveTimer < (BREG(3) + 105)) {
            for (i = 0; i < (BREG(4) + 5); i++) {
                EnRaf_ClearPixelsPetal(Lib_SegmentedToVirtual(&gCarnivorousLilyPadTrapPetalTex),
                                       sPetalClearPixelTableFirstPass, this->petalClearPixelFirstPassIndex);
                EnRaf_ClearPixelsTeeth(Lib_SegmentedToVirtual(&gCarnivorousLilyPadTrapTeethTex),
                                       sTeethClearPixelTableFirstPass, this->teethClearPixelFirstPassIndex);
                if (this->petalClearPixelFirstPassIndex < 0x200) {
                    this->petalClearPixelFirstPassIndex++;
                }

                if (this->teethClearPixelFirstPassIndex < 0x40) {
                    this->teethClearPixelFirstPassIndex++;
                }
            }
        }
    }

    if (this->dissolveTimer > (BREG(5) + 50)) {
        for (i = 0; i < (BREG(6) + 5); i++) {
            EnRaf_ClearPixelsPetal(Lib_SegmentedToVirtual(&gCarnivorousLilyPadTrapPetalTex),
                                   sPetalClearPixelTableSecondPass, this->petalClearPixelSecondPassIndex);
            EnRaf_ClearPixelsTeeth(Lib_SegmentedToVirtual(&gCarnivorousLilyPadTrapTeethTex),
                                   sTeethClearPixelTableSecondPass, this->teethClearPixelSecondPassIndex);
            if (this->petalClearPixelSecondPassIndex < 0x200) {
                this->petalClearPixelSecondPassIndex++;
            }

            if (this->teethClearPixelSecondPassIndex < 0x40) {
                this->teethClearPixelSecondPassIndex++;
            }
        }
    }

    if (this->dissolveTimer > (BREG(7) + 160)) {
        for (i = 2; i < 11; i++) {
            Math_Vec3f_Copy(&this->limbScale[i], &gZeroVec3f);
            Math_Vec3f_Copy(&this->targetLimbScale[i], &gZeroVec3f);
        }

        EnRaf_SetupDeadIdle(this);
    }
}

void EnRaf_SetupDeadIdle(EnRaf* this) {
    if (this->action == EN_RAF_ACTION_EXPLODE) {
        this->timer = 90;
    } else {
        this->action = EN_RAF_ACTION_DEAD_IDLE;
    }

    this->actionFunc = EnRaf_DeadIdle;
}

void EnRaf_DeadIdle(EnRaf* this, GlobalContext* globalCtx) {
    Vec3f sp3C = D_80A1940C;
    s32 i;

    if (this->timer == 0) {
        this->action = EN_RAF_ACTION_DEAD_IDLE;
    }

    if (this->reviveTimer >= 0) {
        DECR(this->reviveTimer);

        if (this->reviveTimer == 0) {
            EnRaf_ChangeAnimation(this, EN_RAF_ANIMATION_SPIT);
            for (i = 2; i < 11; i++) {
                Math_Vec3f_Copy(&this->targetLimbScale[i], &sp3C);
            }

            this->unk_3C2 = 3;
            this->action = EN_RAF_ACTION_IDLE;
            this->reviveTimer = EN_RAF_GET_REVIVE_TIMER(&this->dyna.actor);
            this->reviveTimer += 30;
            this->actionFunc = EnRaf_Idle;
        }
    }
}

void EnRaf_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnRaf* this = THIS;
    WaterBox* waterBox;
    f32 ySurface;
    Vec3f ripplePos;
    s32 i;

    SkelAnime_Update(&this->skelAnime);
    DECR(this->rippleTimer);
    DECR(this->timer);
    this->actionFunc(this, globalCtx);

    if ((this->action == EN_RAF_ACTION_IDLE) && (gSaveContext.save.weekEventReg[12] & 1)) {
        this->unk_3C2 = 0;
        EnRaf_SetupConvulse(this);
        return;
    }

    if (DynaPolyActor_IsInRidingMovingState(&this->dyna)) {
        if ((this->heightDiffFromPlayer > -0.1f) && !this->isCurrentlyInRidingMovingState) {
            this->heightDiffFromPlayer = -20.0f;
            this->isCurrentlyInRidingMovingState = true;
            Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EN_COMMON_WATER_MID);
        }
    } else {
        this->isCurrentlyInRidingMovingState = false;
    }

    this->bobPhase += 3000.0f;
    this->heightDiffFromBob = 2.0f * Math_SinS(this->bobPhase);
    if (this->type != EN_RAF_TYPE_NO_WATER_INTERACTIONS) {
        ySurface = BREG(60) + (this->dyna.actor.world.pos.y - 60.0f);
        if (WaterBox_GetSurface1(globalCtx, &globalCtx->colCtx, this->dyna.actor.world.pos.x,
                                 this->dyna.actor.world.pos.z, &ySurface, &waterBox)) {
            ySurface -= this->heightDiffFromBob + BREG(59);
            Math_ApproachF(&this->dyna.actor.world.pos.y, this->heightDiffFromPlayer + ySurface, 0.5f, 40.0f);
            if (this->rippleTimer == 0) {
                this->rippleTimer = 30;
                if (this->unk_3C2 == 2) {
                    this->rippleTimer = 10;
                }

                Math_Vec3f_Copy(&ripplePos, &this->dyna.actor.world.pos);
                ripplePos.y = ySurface;
                EffectSsGRipple_Spawn(globalCtx, &ripplePos, 650, 3150, 0);
            }
        }
    } else {
        Math_ApproachF(&this->dyna.actor.world.pos.y,
                       (this->dyna.actor.home.pos.y + this->heightDiffFromPlayer) - this->heightDiffFromBob, 0.5f,
                       40.0f);
    }

    Math_ApproachZeroF(&this->heightDiffFromPlayer, 0.3f, 2.0f);
    if (this->action == EN_RAF_ACTION_EXPLODE) {
        EnRaf_UpdateParticles(this, globalCtx);
    }

    for (i = 0; i < 12; i++) {
        if (this->action < EN_RAF_ACTION_EXPLODE) {
            Math_ApproachF(&this->limbScale[i].x, this->targetLimbScale[i].x, 0.4f, 0.5f);
            Math_ApproachF(&this->limbScale[i].y, this->targetLimbScale[i].y, 0.4f, 0.5f);
            Math_ApproachF(&this->limbScale[i].z, this->targetLimbScale[i].z, 0.4f, 0.5f);
        } else {
            Math_ApproachF(&this->limbScale[i].x, this->targetLimbScale[i].x, 1.0f, 1.0f);
            Math_ApproachF(&this->limbScale[i].y, this->targetLimbScale[i].y, 1.0f, 1.0f);
            Math_ApproachF(&this->limbScale[i].z, this->targetLimbScale[i].z, 1.0f, 1.0f);
        }
    }

    Collider_UpdateCylinder(&this->dyna.actor, &this->collider);
    if (this->action < EN_RAF_ACTION_EXPLODE) {
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

void EnRaf_TransformLimbDraw(GlobalContext* globalCtx2, s32 limbIndex, Actor* thisx) {
    GlobalContext* globalCtx = globalCtx2;
    EnRaf* this = THIS;
    s32 i;

    switch (this->unk_3C2) {
        case 1:
            if ((limbIndex == CARNIVOROUS_LILY_PAD_LIMB_TRAP_1_MIDDLE_SEGMENT) ||
                (limbIndex == CARNIVOROUS_LILY_PAD_LIMB_TRAP_3_MIDDLE_SEGMENT) ||
                (limbIndex == CARNIVOROUS_LILY_PAD_LIMB_TRAP_2_MIDDLE_SEGMENT)) {
                for (i = 0; i < 3; i++) {
                    if ((s16)this->skelAnime.curFrame == D_80A19418[i]) {
                        Math_Vec3f_Copy(&this->targetLimbScale[limbIndex], &D_80A19420[i]);
                    }
                }
            }

            if ((limbIndex == CARNIVOROUS_LILY_PAD_LIMB_TRAP_1_UPPER_SEGMENT) ||
                (limbIndex == CARNIVOROUS_LILY_PAD_LIMB_TRAP_3_UPPER_SEGMENT) ||
                (limbIndex == CARNIVOROUS_LILY_PAD_LIMB_TRAP_2_UPPER_SEGMENT)) {
                for (i = 0; i < 3; i++) {
                    if ((s16)this->skelAnime.curFrame == D_80A19418[i]) {
                        Math_Vec3f_Copy(&this->targetLimbScale[limbIndex], &D_80A19444[i]);
                    }
                }
            }
            break;

        case 2:
            if ((limbIndex == CARNIVOROUS_LILY_PAD_LIMB_TRAP_1_MIDDLE_SEGMENT) ||
                (limbIndex == CARNIVOROUS_LILY_PAD_LIMB_TRAP_3_MIDDLE_SEGMENT) ||
                (limbIndex == CARNIVOROUS_LILY_PAD_LIMB_TRAP_2_MIDDLE_SEGMENT)) {
                Math_Vec3f_Copy(&this->targetLimbScale[limbIndex], &D_80A19420[2]);
            } else if ((limbIndex == CARNIVOROUS_LILY_PAD_LIMB_TRAP_1_UPPER_SEGMENT) ||
                       (limbIndex == CARNIVOROUS_LILY_PAD_LIMB_TRAP_3_UPPER_SEGMENT) ||
                       (limbIndex == CARNIVOROUS_LILY_PAD_LIMB_TRAP_2_UPPER_SEGMENT)) {
                Math_Vec3f_Copy(&this->targetLimbScale[limbIndex], &D_80A19444[2]);
            }

            if ((limbIndex > CARNIVOROUS_LILY_PAD_LIMB_FLOWER) && (limbIndex < CARNIVOROUS_LILY_PAD_LIMB_ROOTS)) {
                Matrix_RotateY((this->unk_354[limbIndex].y * globalCtx->gameplayFrames), MTXMODE_APPLY);
                Matrix_InsertXRotation_s((this->unk_354[limbIndex].x * globalCtx->gameplayFrames), MTXMODE_APPLY);
                Matrix_InsertZRotation_s((this->unk_354[limbIndex].z * globalCtx->gameplayFrames), MTXMODE_APPLY);
                Matrix_Scale(this->unk_3A4 + 1.0f, 1.0f, 1.0f, MTXMODE_APPLY);
                Matrix_InsertZRotation_s(-(this->unk_354[limbIndex].z * globalCtx->gameplayFrames), MTXMODE_APPLY);
                Matrix_InsertXRotation_s(-(this->unk_354[limbIndex].x * globalCtx->gameplayFrames), MTXMODE_APPLY);
                Matrix_RotateY(-(this->unk_354[limbIndex].y * globalCtx->gameplayFrames), MTXMODE_APPLY);
            }
            break;

        case 3:
            if ((limbIndex == CARNIVOROUS_LILY_PAD_LIMB_TRAP_1_MIDDLE_SEGMENT) ||
                (limbIndex == CARNIVOROUS_LILY_PAD_LIMB_TRAP_3_MIDDLE_SEGMENT) ||
                (limbIndex == CARNIVOROUS_LILY_PAD_LIMB_TRAP_2_MIDDLE_SEGMENT)) {
                for (i = 0; i < 5; i++) {
                    if ((s16)this->skelAnime.curFrame == D_80A19468[i]) {
                        Math_Vec3f_Copy(&this->targetLimbScale[limbIndex], &D_80A19474[i]);
                    }
                }
            }

            if ((limbIndex == CARNIVOROUS_LILY_PAD_LIMB_TRAP_1_UPPER_SEGMENT) ||
                (limbIndex == CARNIVOROUS_LILY_PAD_LIMB_TRAP_3_UPPER_SEGMENT) ||
                (limbIndex == CARNIVOROUS_LILY_PAD_LIMB_TRAP_2_UPPER_SEGMENT)) {
                for (i = 0; i < 4; i++) {
                    if ((s16)this->skelAnime.curFrame == D_80A19468[i]) {
                        Math_Vec3f_Copy(&this->targetLimbScale[limbIndex], &D_80A194B0[i]);
                    }
                }
            }
            break;
    }

    Matrix_Scale(this->limbScale[limbIndex].x, this->limbScale[limbIndex].y, this->limbScale[limbIndex].z,
                 MTXMODE_APPLY);
}

void EnRaf_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnRaf* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    SkelAnime_DrawTransformFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   this->skelAnime.dListCount, NULL, NULL, EnRaf_TransformLimbDraw, &this->dyna.actor);
    if (this->action == 4) {
        EnRaf_DrawParticles(this, globalCtx);
    }
}

void EnRaf_InitializeParticle(EnRaf* this, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, f32 arg4, s16 arg5) {
    s16 i;
    EnRafParticle* particle = this->particles;

    for (i = 0; i < ARRAY_COUNT(this->particles); i++, particle++) {
        if (!particle->isVisible) {
            particle->isVisible = true;
            particle->position = *arg1;
            particle->velocity = *arg2;
            particle->acceleration = *arg3;
            particle->scale = arg4;
            particle->timer = arg5;
            particle->rotation.x = randPlusMinusPoint5Scaled(30000.0f);
            particle->rotation.y = randPlusMinusPoint5Scaled(30000.0f);
            particle->rotation.z = randPlusMinusPoint5Scaled(30000.0f);
            return;
        }
    }
}

void EnRaf_UpdateParticles(EnRaf* this, GlobalContext* globalCtx) {
    s32 i;
    EnRafParticle* particle = this->particles;

    for (i = 0; i < ARRAY_COUNT(this->particles); i++, particle++) {
        if (particle->isVisible) {
            particle->position.x += particle->velocity.x;
            particle->position.y += particle->velocity.y;
            particle->position.z += particle->velocity.z;
            particle->rotation.x += 0xBB8;
            particle->rotation.y += 0xBB8;
            particle->rotation.z += 0xBB8;
            particle->velocity.x += particle->acceleration.x;
            particle->velocity.y += particle->acceleration.y;
            particle->velocity.z += particle->acceleration.z;

            if (this->type != EN_RAF_TYPE_NO_WATER_INTERACTIONS) {
                if (particle->position.y < (this->dyna.actor.world.pos.y - 10.0f)) {
                    EffectSsGSplash_Spawn(globalCtx, &particle->position, NULL, NULL, 0, particle->scale * 200000.0f);
                    SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &particle->position, 50, NA_SE_EV_BOMB_DROP_WATER);
                    particle->isVisible = false;
                }
            } else if (particle->position.y < (this->dyna.actor.world.pos.y - 10.0f)) {
                Math_ApproachZeroF(&particle->scale, 0.2f, 0.001f);
                if (particle->scale <= 0.0001f) {
                    particle->timer = 0;
                }
            }

            if (particle->timer != 0) {
                particle->timer--;
            } else {
                particle->isVisible = false;
            }
        }
    }
}

void EnRaf_DrawParticles(EnRaf* this, GlobalContext* globalCtx) {
    s16 i;
    EnRafParticle* particle = this->particles;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;

    OPEN_DISPS(gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    for (i = 0; i < ARRAY_COUNT(this->particles); i++, particle++) {
        if (particle->isVisible) {
            Matrix_InsertTranslation(particle->position.x, particle->position.y, particle->position.z, MTXMODE_NEW);
            Matrix_Scale(particle->scale, particle->scale, particle->scale, MTXMODE_APPLY);
            Matrix_InsertXRotation_s(particle->rotation.x, MTXMODE_APPLY);
            Matrix_RotateY(particle->rotation.y, MTXMODE_APPLY);
            Matrix_InsertZRotation_s(particle->rotation.z, MTXMODE_APPLY);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, gCarnivorousLilyPadParticleDL);
        }
    }

    CLOSE_DISPS(gfxCtx);
}
