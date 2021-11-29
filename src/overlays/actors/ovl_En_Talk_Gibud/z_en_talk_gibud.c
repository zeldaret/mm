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

void func_80AFEB7C(EnTalkGibud* this, GlobalContext* globalCtx);
void func_80AFEC08(EnTalkGibud* this);
void func_80AFEC4C(EnTalkGibud* this, GlobalContext* globalCtx);
void func_80AFED08(EnTalkGibud* this);
void func_80AFED7C(EnTalkGibud* this, GlobalContext* globalCtx);
void func_80AFEFD4(EnTalkGibud* this);
void func_80AFF030(EnTalkGibud* this, GlobalContext* globalCtx);
void func_80AFF22C(EnTalkGibud* this);
void func_80AFF288(EnTalkGibud* this, GlobalContext* globalCtx);
void func_80AFF330(EnTalkGibud* this);
void func_80AFF378(EnTalkGibud* this, GlobalContext* globalCtx);
void func_80AFF45C(EnTalkGibud* this);
void func_80AFF4AC(EnTalkGibud* this, GlobalContext* globalCtx);
s32 func_80B0040C(EnTalkGibud* this, GlobalContext* globalCtx);
s32 func_80B00484(EnTalkGibud* this, GlobalContext* globalCtx);
void func_80B005EC(EnTalkGibud* this, GlobalContext* globalCtx);
s32 func_80B00760(EnTalkGibud* this, GlobalContext* globalCtx);
void func_80AFF8E4(EnTalkGibud* this, GlobalContext* globalCtx);
void func_80B00158(EnTalkGibud* this, GlobalContext* globalCtx);
void func_80AFFA68(EnTalkGibud* this, GlobalContext* globalCtx);
void func_80AFF76C(EnTalkGibud* this, GlobalContext* globalCtx);
void func_80AFFFBC(EnTalkGibud* this, GlobalContext* globalCtx);
void func_80AFFE94(EnTalkGibud* this, GlobalContext* globalCtx);
void func_80AFF6A0(EnTalkGibud* this, GlobalContext* globalCtx);
void func_80AFF700(EnTalkGibud* this);
void func_80AFF880(EnTalkGibud* this);
void func_80AFF9CC(EnTalkGibud* this);
void func_80AFFFA4(EnTalkGibud* this);
void func_80B000FC(EnTalkGibud* this);
void func_80AFEB38(EnTalkGibud* this);
void func_80B00384(EnTalkGibud* this, GlobalContext* globalCtx);

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
extern AnimationHeader D_060118D8;    // dance 1
extern AnimationHeader D_06011DB8;    // dance 2
extern AnimationHeader D_0601216C;    // dance 3

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

static ActorAnimationEntry D_80B01200[] = {
    { &D_06006678, 1.0f, 0.0f, 0.0f, 0, -8.0f }, { &D_06006B08, 0.5f, 0.0f, 0.0f, 3, 0.0f },
    { &D_06006EEC, 1.0f, 0.0f, 0.0f, 2, -8.0f }, { &D_060073A4, 0.0f, 0.0f, 0.0f, 2, -8.0f },
    { &D_06007BBC, 1.0f, 0.0f, 0.0f, 2, -8.0f }, { &D_060081A8, 1.0f, 0.0f, 0.0f, 0, -8.0f },
    { &D_06009298, 1.0f, 0.0f, 0.0f, 2, -8.0f }, { &D_06009900, 1.0f, 0.0f, 0.0f, 2, -8.0f },
    { &D_0600A450, 1.0f, 0.0f, 0.0f, 2, -8.0f }, { &D_0600ABE0, 1.0f, 0.0f, 0.0f, 0, -8.0f },
    { &D_060113EC, 0.4f, 0.0f, 0.0f, 1, -8.0f }, { &D_0601216C, 1.0f, 0.0f, 0.0f, 0, -8.0f },
    { &D_060118D8, 1.0f, 0.0f, 0.0f, 0, -8.0f }, { &D_06011DB8, 1.0f, 0.0f, 0.0f, 0, -8.0f },
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B01350 = {
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

// static DamageTable sDamageTable = {
static DamageTable D_80B0137C = {
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

// sColChkInfoInit
static CollisionCheckInfoInit2 D_80B0139C = { 8, 0, 0, 0, MASS_HEAVY };

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

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B01448[] = {
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -3500, ICHAIN_STOP),
};

static Vec3f D_80B01454 = { 0.0f, 0.0f, 0.0f };

static Vec3f D_80B01460 = { 0.0f, 0.600000023842f, 0.0f };

void EnTalkGibud_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnTalkGibud* this = THIS;
    s32 i;

    Actor_ProcessInitChain(&this->actor, D_80B01448);
    this->actor.targetMode = 0;
    this->actor.hintId = 0x2D;
    this->actor.textId = 0;
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 28.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &D_060053E8, &D_0600ABE0, this->jointTable, this->morphTable, 26);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &D_80B01350);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &D_80B0137C, &D_80B0139C);
    this->unk_3EA = 0;
    this->unk_3EC = 0;
    this->unk_3EE = 0;
    this->itemActionParam = PLAYER_AP_NONE;
    this->unk_3F0 = 0;
    this->unk_3F6 = 0;
    this->unk_3F4 = 0;
    this->unk_3F2 = 0;
    this->requestedItemIndex = EN_TALK_GIBUD_REQUESTED_ITEM_INDEX(thisx);
    this->switchFlag = EN_TALK_GIBUD_SWITCH_FLAG(thisx);
    this->unk_29C = 0.0f;
    this->unk_2A0 = 0.0f;

    for (i = 0; i < ARRAY_COUNT(this->unk_1D8); i++) {
        this->unk_1D8[i] = D_801D15B0;
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

    func_80AFEB38(this);
}

void EnTalkGibud_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnTalkGibud* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80AFEB38(EnTalkGibud* this) {
    func_800BDC5C(&this->skelAnime, D_80B01200, 9);
    this->actionFunc = func_80AFEB7C;
}

void func_80AFEB7C(EnTalkGibud* this, GlobalContext* globalCtx) {
    if (this->actor.xzDistToPlayer <= 150.0f && func_800B715C(globalCtx)) {
        func_80AFEC08(this);
    }
    Math_SmoothStepToS(&this->unk_3DE.y, 0, 1, 0x64, 0);
    Math_SmoothStepToS(&this->unk_3E4.y, 0, 1, 0x64, 0);
}

void func_80AFEC08(EnTalkGibud* this) {
    func_800BDC5C(&this->skelAnime, D_80B01200, 9);
    this->actionFunc = func_80AFEC4C;
}

void func_80AFEC4C(EnTalkGibud* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 rot = this->actor.shape.rot.y + this->unk_3DE.y + this->unk_3E4.y;
    s16 yaw = BINANG_SUB(this->actor.yawTowardsPlayer, rot);

    if (ABS_ALT(yaw) < 0x2008) {
        player->actor.freezeTimer = 60;
        func_8013ECE0(this->actor.xzDistToPlayer, 255, 20, 150);
        func_80123E90(globalCtx, &this->actor);
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_REDEAD_AIM);
        func_80AFED08(this);
    }
    func_80B005EC(this, globalCtx);
}

void func_80AFED08(EnTalkGibud* this) {
    func_800BDC5C(&this->skelAnime, D_80B01200, 10);
    this->actor.speedXZ = 0.4f;
    if (this->actionFunc == func_80AFEC4C) {
        this->unk_3EA = 0x50;
    } else {
        this->unk_3EA = 0x14;
    }
    this->actionFunc = func_80AFED7C;
}

void func_80AFED7C(EnTalkGibud* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 pad;

    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xFA);
    this->actor.world.rot = this->actor.shape.rot;
    Math_SmoothStepToS(&this->unk_3DE.y, 0, 1, 100, 0);
    Math_SmoothStepToS(&this->unk_3E4.y, 0, 1, 100, 0);
    if (func_80B0040C(this, globalCtx) && Actor_IsActorFacingLink(&this->actor, 0x38E3)) {
        if (this->unk_3EE == 0 && this->actor.xzDistToPlayer <= 45.0f) {
            player->actor.freezeTimer = 0;
            if ((gSaveContext.playerForm == PLAYER_FORM_GORON) || (gSaveContext.playerForm == PLAYER_FORM_DEKU)) {
                func_80AFF22C(this);
            } else if (globalCtx->grabPlayer(globalCtx, player)) {
                func_80AFEFD4(this);
            }
        } else {
            if (this->unk_3EA == 0) {
                player->actor.freezeTimer = 40;
                this->unk_3EA = 60;
                func_8013ECE0(this->actor.xzDistToPlayer, 255, 20, 150);
                func_80123E90(globalCtx, &this->actor);
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_REDEAD_AIM);
            } else {
                this->unk_3EA--;
            }
        }
    } else if (this->unk_3EE == 0 && this->actor.xzDistToPlayer <= 45.0f) {
        func_80AFF45C(this);
    } else if (func_80B00484(this, globalCtx)) {
        func_80AFF45C(this);
    }
    if (this->unk_3EE > 0) {
        this->unk_3EE--;
    }

    if (Animation_OnFrame(&this->skelAnime, 10.0f) || Animation_OnFrame(&this->skelAnime, 22.0f)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_RIZA_WALK);
    } else if (!(globalCtx->gameplayFrames & 0x5F)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_REDEAD_CRY);
    }
}

void func_80AFEFD4(EnTalkGibud* this) {
    func_800BDC5C(&this->skelAnime, D_80B01200, 2);
    this->unk_3EA = 0;
    this->actor.flags &= -2;
    this->unk_3EC = 0;
    this->actionFunc = func_80AFF030;
}

void func_80AFF030(EnTalkGibud* this, GlobalContext* globalCtx) {
    Player* player2 = GET_PLAYER(globalCtx);
    Player* player = player2;
    s32 sp34;
    u16 sp32;

    switch (this->unk_3EC) {
        case 0:
            sp34 = func_80B00760(this, globalCtx);
            if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) && sp34 == 1) {
                this->unk_3EC = 1;
                func_800BDC5C(&this->skelAnime, D_80B01200, 0);
            }
            break;

        case 1:
            if (this->unk_3EA == 20) {
                s16 requiredScopeTemp;

                sp32 = player->ageProperties->unk_92 + 0x6805;
                globalCtx->damagePlayer(globalCtx, -8);
                func_800B8E58(&player->actor, sp32);
                func_8013ECE0(this->actor.xzDistToPlayer, 240, 1, 12);
                this->unk_3EA = 0;
            } else {
                this->unk_3EA++;
            }

            if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_REDEAD_ATTACK);
            }

            if (!(player->stateFlags2 & 0x80) || (player->unk_B62 != 0)) {
                if ((player->unk_B62 != 0) && (player->stateFlags2 & 0x80)) {
                    player->stateFlags2 &= ~0x80;
                    player->unk_AE8 = 100;
                }
                func_800BDC5C(&this->skelAnime, D_80B01200, 1);
                this->actor.flags |= 1;
                this->unk_3EC = 2;
                this->unk_3EA = 0;
            }
            break;

        case 2:
            if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                this->unk_3EE = 20;
                this->actor.shape.yOffset = 0.0f;
                func_80AFED08(this);
            } else {
                Math_SmoothStepToF(&this->actor.shape.yOffset, 0.0f, 1.0f, 400.0f, 0.0f);
            }
            break;
    }
}

void func_80AFF22C(EnTalkGibud* this) {
    func_800BDC5C(&this->skelAnime, D_80B01200, 7);
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_REDEAD_DAMAGE);
    this->actionFunc = func_80AFF288;
    this->actor.speedXZ = -2.0f;
}

void func_80AFF288(EnTalkGibud* this, GlobalContext* globalCtx) {
    if (this->actor.speedXZ < 0.0f) {
        this->actor.speedXZ += 0.15f;
    }
    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    Math_SmoothStepToS(&this->unk_3DE.y, 0, 1, 0x12C, 0);
    Math_SmoothStepToS(&this->unk_3E4.y, 0, 1, 0x12C, 0);
    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        this->actor.world.rot.y = this->actor.shape.rot.y;
        func_80AFF330(this);
    }
}

void func_80AFF330(EnTalkGibud* this) {
    this->unk_3EA = 0;
    func_800BDC5C(&this->skelAnime, D_80B01200, 10);
    this->actionFunc = func_80AFF378;
}

void func_80AFF378(EnTalkGibud* this, GlobalContext* globalCtx) {
    Math_SmoothStepToS(&this->actor.world.rot.y, BINANG_ROT180(this->actor.yawTowardsPlayer), 5, 3500, 200);
    this->actor.shape.rot.y = this->actor.world.rot.y;
    if (this->unk_3EA > 60) {
        func_80AFF45C(this);
        this->unk_3EA = 0;
    } else {
        this->unk_3DE.y = Math_SinS(this->unk_3EA * 0xFA0) * (0x256F * ((60 - this->unk_3EA) / 60.0f));
        this->unk_3EA++;
    }
}

void func_80AFF45C(EnTalkGibud* this) {
    func_800BDC5C(&this->skelAnime, D_80B01200, 10);
    this->actor.speedXZ = 0.4f;
    this->actionFunc = func_80AFF4AC;
}

void func_80AFF4AC(EnTalkGibud* this, GlobalContext* globalCtx) {
    Math_SmoothStepToS(&this->unk_3DE.y, 0, 1, 100, 0);
    Math_SmoothStepToS(&this->unk_3E4.y, 0, 1, 100, 0);
    if (Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos) < 5.0f) {
        if (this->actor.speedXZ > 0.2f) {
            this->actor.speedXZ -= 0.2f;
        } else {
            this->actor.speedXZ = 0.0f;
        }
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 1, 200, 10);
        this->actor.world.rot.y = this->actor.shape.rot.y;
        if (this->actor.world.rot.y == this->actor.home.rot.y) {
            func_80AFEB38(this);
        }
    } else {
        Math_ScaledStepToS(&this->actor.shape.rot.y, Actor_YawToPoint(&this->actor, &this->actor.home.pos), 450);
        this->actor.world.rot = this->actor.shape.rot;
    }
    if (func_80B0040C(this, globalCtx)) {
        if ((gSaveContext.playerForm != PLAYER_FORM_GORON) && (gSaveContext.playerForm != PLAYER_FORM_DEKU) &&
            Actor_IsActorFacingLink(&this->actor, 0x38E3)) {
            func_80AFED08(this);
        }
    }
}

void func_80AFF618(EnTalkGibud* this) {
    this->unk_3EA = 0xA;
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (this->unk_3F0 != 0) {
        func_800BCB70(&this->actor, 0U, 0xC8, 0, 0x28);
    } else {
        func_800BCB70(&this->actor, 0U, 0xC8, 0, 0x28);
    }
    this->actionFunc = func_80AFF6A0;
}

void func_80AFF6A0(EnTalkGibud* this, GlobalContext* globalCtx) {
    if (this->actor.colorFilterTimer == 0) {
        if (this->actor.colChkInfo.health == 0) {
            func_80AFF880(this);
        } else {
            func_80AFF700(this);
        }
    }
    if (this->unk_3EA != 0) {
        this->unk_3EA--;
    }
}

void func_80AFF700(EnTalkGibud* this) {
    func_800BDC5C(&this->skelAnime, D_80B01200, 7);
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_REDEAD_DAMAGE);
    this->unk_3EA = 0;
    this->unk_3EE = 0;
    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    this->actionFunc = func_80AFF76C;
    this->actor.speedXZ = -2.0f;
}

void func_80AFF76C(EnTalkGibud* this, GlobalContext* globalCtx) {
    if (this->actor.speedXZ < 0.0f) {
        this->actor.speedXZ += 0.15f;
    }
    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        this->unk_3F7 = -1;
        this->actor.world.rot.y = this->actor.shape.rot.y;
        if (this->unk_3F0 > 0 && this->unk_3F6 == 0 && this->unk_3F2 == 0) {
            this->actor.hintId = 0x2A;
            this->actor.flags &= ~(0x8 | 0x1);
            this->actor.flags |= (0x4 | 0x1);
            SkelAnime_InitFlex(globalCtx, &this->skelAnime, &D_06010B88, NULL, this->jointTable, this->morphTable, 26);
            this->unk_3F2 = 1;
        }
        if (func_80B00484(this, globalCtx)) {
            func_80AFF45C(this);
        } else {
            func_80AFED08(this);
        }
    }
}

void func_80AFF880(EnTalkGibud* this) {
    func_800BDC5C(&this->skelAnime, D_80B01200, 6);
    this->actor.flags &= -2;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_REDEAD_DEAD);
    this->unk_3EA = 0;
    this->actionFunc = func_80AFF8E4;
}

void func_80AFF8E4(EnTalkGibud* this, GlobalContext* globalCtx) {
    if (this->unk_3EA > 300) {
        func_80AFF9CC(this);
    } else {
        Math_SmoothStepToS(&this->unk_3DE.y, 0, 1, 250, 0);
        Math_SmoothStepToS(&this->unk_3E4.y, 0, 1, 250, 0);
        this->unk_3EA += 1;
    }
    if (this->unk_3EA == 20 && this->unk_3F0 > 0 && this->unk_3F6 == 0 && this->unk_3F2 == 0) {
        SkelAnime_InitFlex(globalCtx, &this->skelAnime, &D_06010B88, NULL, this->jointTable, this->morphTable, 26);
        this->unk_3F2 = 1;
    }
}

void func_80AFF9CC(EnTalkGibud* this) {
    Animation_Change(&this->skelAnime, &D_06009298, -1.0f, Animation_GetLastFrame(&D_06009298), 0.0f, 2, -8.0f);
    this->actor.flags |= 1;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_REDEAD_REVERSE);
    this->unk_3EA = 0;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = func_80AFFA68;
}

void func_80AFFA68(EnTalkGibud* this, GlobalContext* globalCtx) {
    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        this->actor.colChkInfo.health = 8;
        func_80AFEB38(this);
    }
}

void func_80AFFAB0(EnTalkGibud* this, GlobalContext* globalCtx) {
    switch (this->requestedItemIndex) {
        case 0:
            func_801518B0(globalCtx, 0x138C, &this->actor);
            this->unk_3DC = 0x138C;
            break;
        case 1:
            func_801518B0(globalCtx, 0x138D, &this->actor);
            this->unk_3DC = 0x138D;
            break;
        case 2:
            func_801518B0(globalCtx, 0x138E, &this->actor);
            this->unk_3DC = 0x138E;
            break;
        case 3:
            func_801518B0(globalCtx, 0x138F, &this->actor);
            this->unk_3DC = 0x138F;
            break;
        case 4:
            func_801518B0(globalCtx, 0x1390, &this->actor);
            this->unk_3DC = 0x1390;
            break;
        case 5:
            func_801518B0(globalCtx, 0x1391, &this->actor);
            this->unk_3DC = 0x1391;
            break;
        case 6:
            func_801518B0(globalCtx, 0x1392, &this->actor);
            this->unk_3DC = 0x1392;
            break;
        case 7:
            func_801518B0(globalCtx, 0x1393, &this->actor);
            this->unk_3DC = 0x1393;
            break;
        case 8:
            func_801518B0(globalCtx, 0x1394, &this->actor);
            this->unk_3DC = 0x1394;
            break;
        case 9:
            func_801518B0(globalCtx, 0x1395, &this->actor);
            this->unk_3DC = 0x1395;
            break;
    }
}

void func_80AFFC10(EnTalkGibud* this, GlobalContext* globalCtx) {
    if (func_80147624(globalCtx)) {
        switch (this->unk_3DC) {
            case 0x1388:
                func_80AFFAB0(this, globalCtx);
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
                this->unk_3DC = 0xFF;
                break;
        }
    }
}

s32 func_80AFFC9C(EnTalkGibud* this, GlobalContext* globalCtx, s32 itemActionParam) {
    EnTalkGibudRequestedItem* requestedItem = &sRequestedItemTable[this->requestedItemIndex];

    if (requestedItem->itemActionParam == itemActionParam) {
        if (!requestedItem->isBottledItem) {
            if (AMMO(requestedItem->item) >= requestedItem->amount) {
                return 0;
            }
            return 1;
        }
        if (func_80114F2C(requestedItem->item)) {
            return 0;
        }
    }
    return 2;
}

void func_80AFFD3C(EnTalkGibud* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 itemActionParam;

    if (this->itemActionParam == PLAYER_AP_NONE) {
        itemActionParam = func_80123810(globalCtx);
        if (itemActionParam != PLAYER_AP_NONE) {
            this->itemActionParam = itemActionParam;
        }
        if (this->itemActionParam > PLAYER_AP_NONE) {
            switch (func_80AFFC9C(this, globalCtx, this->itemActionParam)) {
                case 0:
                    player->actor.textId = 0x138A;
                    this->unk_3DC = 0x138A;
                    break;
                case 1:
                    player->actor.textId = 0x138B;
                    this->unk_3DC = 0x138B;
                    break;
                case 2:
                    player->actor.textId = 0x1389;
                    this->unk_3DC = 0x1389;
                    break;
                default:
                    break;
            }
            func_801477B4(globalCtx);
        } else if (this->itemActionParam < PLAYER_AP_NONE) {
            func_801518B0(globalCtx, 0x1389, &this->actor);
            this->unk_3DC = 0x1389;
        }
    }
}

void func_80AFFE3C(EnTalkGibud* this) {
    this->unk_3F4 = 0;
    if (this->actionFunc != func_80AFFFBC) {
        func_800BDC5C(&this->skelAnime, D_80B01200, 9);
    }
    this->actionFunc = func_80AFFE94;
}

void func_80AFFE94(EnTalkGibud* this, GlobalContext* globalCtx) {
    if (func_800B84D0(&this->actor, globalCtx)) {
        this->unk_3F4 = 1;
        func_801518B0(globalCtx, 0x1388, &this->actor);
        this->unk_3DC = 0x1388;
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_REDEAD_AIM);
        func_80AFFFA4(this);
    } else if (this->actor.xzDistToPlayer < 100.0f && !(this->collider.base.acFlags & AC_HIT)) {
        func_800E9250(globalCtx, &this->actor, &this->unk_3DE, &this->unk_3E4, this->actor.focus.pos);
        func_800B8614(&this->actor, globalCtx, 100.0f);
    } else {
        Math_SmoothStepToS(&this->unk_3DE.y, 0, 1, 100, 0);
        Math_SmoothStepToS(&this->unk_3E4.y, 0, 1, 100, 0);
    }
}

void func_80AFFFA4(EnTalkGibud* this) {
    this->itemActionParam = PLAYER_AP_NONE;
    this->actionFunc = func_80AFFFBC;
}

void func_80AFFFBC(EnTalkGibud* this, GlobalContext* globalCtx) {
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
                if (this->unk_3DC == 0x138A) {
                    requestedItem = &sRequestedItemTable[this->requestedItemIndex];
                    if (!requestedItem->isBottledItem) {
                        func_80115A14(requestedItem->item, -requestedItem->amount);
                    } else {
                        func_80123D50(globalCtx, player, ITEM_BOTTLE, PLAYER_AP_BOTTLE);
                    }
                    player->stateFlags1 |= 0x20;
                    player->stateFlags1 |= 0x20000000;
                    this->actor.flags |= 0x100000;
                    func_80B000FC(this);
                } else {
                    func_80AFFE3C(this);
                }
            }
            break;
        case 16:
            func_80AFFD3C(this, globalCtx);
            break;
    }
    func_80B00384(this, globalCtx);
}

void func_80B000FC(EnTalkGibud* this) {
    func_800BDC5C(&this->skelAnime, D_80B01200, 9);
    this->actor.flags &= -2;
    this->unk_3EA = 0x28;
    this->actionFunc = func_80B00158;
}

void func_80B00158(EnTalkGibud* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f velocity = D_80B01454;
    Vec3f accel = D_80B01460;
    Vec3f pos;
    s32 phi_s3;
    s32 i;

    if (this->unk_3EA > 0) {
        phi_s3 = CLAMP_MAX(this->unk_3EA, 3);
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
        this->unk_3EA += -1;
    } else {
        if (this->switchFlag != -1) {
            Actor_SetSwitchFlag(globalCtx, this->switchFlag);
        }
        player->stateFlags1 &= ~0x20;
        player->stateFlags1 &= ~0x20000000;
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80B00384(EnTalkGibud* this, GlobalContext* globalCtx) {
    s16 temp;

    temp = this->actor.yawTowardsPlayer;
    Math_ScaledStepToS(&this->actor.shape.rot.y, temp, 0x320);
    temp -= this->actor.shape.rot.y;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    Math_ScaledStepToS(&this->unk_3E4.y, temp, 0x258);
    temp -= this->unk_3E4.y;
    Math_ScaledStepToS(&this->unk_3DE.y, temp, 0x190);
}

s32 func_80B0040C(EnTalkGibud* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if ((Actor_DistanceToPoint(&player->actor, &this->actor.home.pos) < 150.0f) && !(player->stateFlags1 & 0x2C6080) &&
        !(player->stateFlags2 & 0x4080)) {
        return true;
    }

    return false;
}

s32 func_80B00484(EnTalkGibud* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (Actor_DistanceToPoint(&player->actor, &this->actor.home.pos) >= 150.0f) {
        return true;
    }

    return false;
}

void func_80B004D0(EnTalkGibud* this, GlobalContext* globalCtx) {
    if (this->actionFunc != func_80AFF030 && this->actionFunc != func_80AFF8E4 && this->actionFunc != func_80B00158 &&
        this->actionFunc != func_80AFFA68 && this->actionFunc != func_80AFF76C && this->actionFunc != func_80AFFFBC) {
        if (this->actionFunc != func_80AFFE94) {
            if (Player_GetMask(globalCtx) == PLAYER_MASK_GIBDO) {
                this->actor.flags &= ~(0x4 | 0x1);
                this->actor.flags |= (0x8 | 0x1);
                this->actor.hintId = 0xFF;
                this->actor.textId = 0;
                func_80AFFE3C(this);
            }
        } else if (Player_GetMask(globalCtx) != PLAYER_MASK_GIBDO) {
            this->actor.flags &= ~(0x8 | 0x1);
            this->actor.flags |= (0x4 | 0x1);
            if (this->unk_3F2 == 1) {
                this->actor.hintId = 0x2A;
            } else {
                this->actor.hintId = 0x2D;
            }
            this->actor.textId = 0;
            func_80AFF45C(this);
        }
    }
}

void func_80B005EC(EnTalkGibud* this, GlobalContext* globalCtx) {
    s16 temp_v0 = (this->actor.yawTowardsPlayer - this->actor.shape.rot.y) - this->unk_3E4.y;
    s16 phi_a2 = CLAMP(temp_v0, -500, 500);

    temp_v0 -= this->unk_3DE.y;
    temp_v0 = CLAMP(temp_v0, -500, 500);

    if (BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.shape.rot.y) >= 0) {
        this->unk_3E4.y += ABS_ALT(phi_a2);
        this->unk_3DE.y += ABS_ALT(temp_v0);
    } else {
        this->unk_3E4.y -= ABS_ALT(phi_a2);
        this->unk_3DE.y -= ABS_ALT(temp_v0);
    }

    this->unk_3E4.y = CLAMP(this->unk_3E4.y, -0x495F, 0x495F);
    this->unk_3DE.y = CLAMP(this->unk_3DE.y, -0x256F, 0x256F);
}

s32 func_80B00760(EnTalkGibud* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f sp40;
    f32 sp3C;
    f32 sp38 = 0.0f;
    s16 temp_s0_2;

    sp40 = player->actor.world.pos;

    sp40.x -= 25.0f * Math_SinS(player->actor.shape.rot.y);
    sp40.z -= 25.0f * Math_CosS(player->actor.shape.rot.y);
    sp3C = Math_Vec3f_StepTo(&this->actor.world.pos, &sp40, 10.0f);
    temp_s0_2 = Math_SmoothStepToS(&this->actor.shape.rot.y, player->actor.shape.rot.y, 1, 0x1770, 0x64);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (gSaveContext.playerForm == PLAYER_FORM_HUMAN) {
        sp38 = Math_SmoothStepToF(&this->actor.shape.yOffset, -1500.0f, 1.0f, 150.0f, 0.0f);
    }

    if ((sp3C == 0.0f) && (ABS_ALT(temp_s0_2) < 100) && (sp38 == 0.0f)) {
        return true;
    }

    return false;
}

void func_80B008BC(EnTalkGibud* this, GlobalContext* globalCtx) {
    if (this->actionFunc != func_80AFF6A0) {
        SkelAnime_Update(&this->skelAnime);
    }
}

void func_80B008FC(EnTalkGibud* this, GlobalContext* globalCtx) {
    if (this->actionFunc == func_80AFED7C || this->actionFunc == func_80AFF4AC || this->actionFunc == func_80AFF76C) {
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    }
}

void func_80B0094C(EnTalkGibud* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        Actor_ApplyDamage(&this->actor);

        switch (this->actor.colChkInfo.damageEffect) {
            case 15:
                func_800BCB70(&this->actor, 0x4000, 255, 0, 8);
                if (player->unk_ADC != 0) {
                    this->unk_3F7 = player->unk_ADD;
                }
                this->actor.shape.yOffset = 0.0f;
                if (this->actor.colChkInfo.health == 0) {
                    func_80AFF880(this);
                } else {
                    func_80AFF700(this);
                }
                break;

            case 14:
                if (this->unk_3F2 == 1) {
                    this->actor.colChkInfo.health = 0;
                    this->actor.shape.yOffset = 0.0f;
                    func_80AFF880(this);
                }
                break;

            case 2:
                func_800BCB70(&this->actor, 0x4000, 255, 0, 8);
                if (this->actor.colChkInfo.health == 0) {
                    func_80AFF880(this);
                } else {
                    func_80AFF700(this);
                }
                this->unk_3F0 = 180;
                this->unk_3F6 = 0;
                this->unk_29C = 1.0f;
                break;

            case 4:
                func_800BCB70(&this->actor, 0x4000, 255, 0, 8);
                if (this->actor.colChkInfo.health == 0) {
                    func_80AFF880(this);
                } else {
                    func_80AFF700(this);
                }
                this->unk_3F0 = 60;
                this->unk_3F6 = 20;
                this->unk_29C = 1.0f;
                break;

            case 12:
                if ((this->actionFunc != func_80AFF030) &&
                    ((this->actionFunc != func_80AFF6A0) || (this->unk_3EA == 0))) {
                    this->unk_29C = 1.0f;
                    this->unk_3F0 = 40;
                    this->unk_3F6 = 30;
                    func_80AFF618(this);
                }
                break;

            case 1:
                if ((this->actionFunc != func_80AFF6A0) || (this->unk_3EA == 0)) {
                    func_80AFF618(this);
                }
                break;
        }
    }
}

void func_80B00B8C(EnTalkGibud* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (this->actionFunc != func_80AFF8E4 && this->actionFunc != func_80B00158 && this->actionFunc != func_80AFFA68 &&
        (this->actionFunc != func_80AFF030 || this->unk_3EC == 2)) {
        if (this->unk_3F4 != 1) {
            Collider_UpdateCylinder(&this->actor, &this->collider);
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
            if (((this->actionFunc != func_80AFF76C) ||
                 ((player->unk_ADC != 0) && (player->unk_ADD != this->unk_3F7))) &&
                ((this->actionFunc != func_80AFF6A0) || (this->unk_3EA == 0))) {
                CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
            }
        }
    }
}

void func_80B00C94(EnTalkGibud* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f sp28;

    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, 20.0f, 35.0f, 29);
    if (this->actionFunc == func_80AFF030 && this->unk_3EC == 0 && (this->actor.bgCheckFlags & 8)) {
        sp28 = player->actor.world.pos;
        sp28.x += 10.0f * Math_SinS(this->actor.wallYaw);
        sp28.z += 10.0f * Math_CosS(this->actor.wallYaw);
        Math_Vec3f_StepTo(&player->actor.world.pos, &sp28, 5.0f);
    }
}

void func_80B00D9C(EnTalkGibud* this, GlobalContext* globalCtx) {
    if (this->unk_3F0 > 0) {
        this->unk_3F0--;
    }
    if (this->unk_3F0 < 0x14) {
        Math_SmoothStepToF(&this->unk_2A0, 0.0f, 0.5f, 0.03f, 0.0f);
        this->unk_29C = this->unk_3F0 * 0.05f;
    } else {
        Math_SmoothStepToF(&this->unk_2A0, 0.5f, 0.1f, 0.02f, 0.0f);
    }
}

void EnTalkGibud_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnTalkGibud* this = THIS;

    func_80B004D0(this, globalCtx);
    func_80B0094C(this, globalCtx);
    this->actionFunc(this, globalCtx);
    func_80B008BC(this, globalCtx);
    func_80B008FC(this, globalCtx);
    func_80B00B8C(this, globalCtx);
    func_80B00C94(this, globalCtx);
    func_80B00D9C(this, globalCtx);
    this->actor.focus.pos = this->actor.world.pos;
    this->actor.focus.pos.y += 50.0f;
}

s32 func_80B00F08(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx,
                  Gfx** gfx) {
    EnTalkGibud* this = THIS;

    if (limbIndex == 12) {
        rot->y += this->unk_3E4.y;
    } else if (limbIndex == 23) {
        rot->y += this->unk_3DE.y;
    }

    return false;
}

void func_80B00F64(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    EnTalkGibud* this = THIS;

    if ((this->unk_3F0 != 0) &&
        ((limbIndex == 3) || (limbIndex == 4) || (limbIndex == 6) || (limbIndex == 8) || (limbIndex == 9) ||
         (limbIndex == 11) || (limbIndex == 14) || (limbIndex == 16) || (limbIndex == 17) || (limbIndex == 18) ||
         (limbIndex == 20) || (limbIndex == 21) || (limbIndex == 22) || (limbIndex == 24) || (limbIndex == 25))) {
        Matrix_GetStateTranslation(&this->unk_1D8[this->unk_28C]);
        this->unk_28C++;
    }
}

void EnTalkGibud_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnTalkGibud* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    this->unk_28C = 0;
    if (this->actor.shape.shadowAlpha == 255) {
        func_8012C28C(globalCtx->state.gfxCtx);

        gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, this->actor.shape.shadowAlpha);
        gSPSegment(POLY_OPA_DISP++, 0x08, D_801AEFA0);

        POLY_OPA_DISP =
            SkelAnime_DrawFlex(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                               this->skelAnime.dListCount, func_80B00F08, func_80B00F64, &this->actor, POLY_OPA_DISP);
    } else {
        func_8012C2DC(globalCtx->state.gfxCtx);

        gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, this->actor.shape.shadowAlpha);
        gSPSegment(POLY_XLU_DISP++, 0x08, D_801AEF88);

        POLY_XLU_DISP =
            SkelAnime_DrawFlex(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                               this->skelAnime.dListCount, func_80B00F08, func_80B00F64, &this->actor, POLY_XLU_DISP);
    }
    if (this->unk_3F0 > 0) {
        func_800BE680(globalCtx, &this->actor, this->unk_1D8, ARRAY_COUNT(this->unk_1D8), this->unk_2A0, 0.5f,
                      this->unk_29C, this->unk_3F6);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
