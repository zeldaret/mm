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

#if 0
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

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B01350 = {
    { COLTYPE_HIT0, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7EFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
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

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B01448[] = {
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -3500, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80B01350;
extern DamageTable D_80B0137C;
extern CollisionCheckInfoInit2 D_80B0139C;
extern InitChainEntry D_80B01448[];
extern ActorAnimationEntry D_80B01200[];

extern FlexSkeletonHeader D_060053E8;
extern UNK_TYPE D_06009298;
extern AnimationHeader D_0600ABE0;
extern UNK_TYPE D_06010B88;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/EnTalkGibud_Init.s")

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
    Math_SmoothStepToS(&this->unk_3E0, 0, 1, 0x64, 0);
    Math_SmoothStepToS(&this->unk_3E6, 0, 1, 0x64, 0);
}

void func_80AFEC08(EnTalkGibud* this) {
    func_800BDC5C(&this->skelAnime, D_80B01200, 9);
    this->actionFunc = func_80AFEC4C;
}

void func_80AFEC4C(EnTalkGibud* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 rot = this->actor.shape.rot.y + this->unk_3E0 + this->unk_3E6;
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
    Math_SmoothStepToS(&this->unk_3E0, 0, 1, 100, 0);
    Math_SmoothStepToS(&this->unk_3E6, 0, 1, 100, 0);
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
    Math_SmoothStepToS(&this->unk_3E0, 0, 1, 0x12C, 0);
    Math_SmoothStepToS(&this->unk_3E6, 0, 1, 0x12C, 0);
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
        this->unk_3E0 = Math_SinS(this->unk_3EA * 0xFA0) * (0x256F * ((60 - this->unk_3EA) / 60.0f));
        this->unk_3EA++;
    }
}

void func_80AFF45C(EnTalkGibud* this) {
    func_800BDC5C(&this->skelAnime, D_80B01200, 10);
    this->actor.speedXZ = 0.4f;
    this->actionFunc = func_80AFF4AC;
}

void func_80AFF4AC(EnTalkGibud* this, GlobalContext* globalCtx) {
    Math_SmoothStepToS(&this->unk_3E0, 0, 1, 100, 0);
    Math_SmoothStepToS(&this->unk_3E6, 0, 1, 100, 0);
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

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFF76C.s")

void func_80AFF880(EnTalkGibud* this) {
    func_800BDC5C(&this->skelAnime, D_80B01200, 6);
    this->actor.flags &= -2;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_REDEAD_DEAD);
    this->unk_3EA = 0;
    this->actionFunc = func_80AFF8E4;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFF8E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFF9CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFFA68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFFAB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFFC10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFFC9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFFD3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFFE3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFFE94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFFFA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFFFBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80B000FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80B00158.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80B00384.s")

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
    s16 temp_v0 = (this->actor.yawTowardsPlayer - this->actor.shape.rot.y) - this->unk_3E6;
    s16 phi_a2 = CLAMP(temp_v0, -500, 500);

    temp_v0 -= this->unk_3E0;
    temp_v0 = CLAMP(temp_v0, -500, 500);

    if (BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.shape.rot.y) >= 0) {
        this->unk_3E6 += ABS_ALT(phi_a2);
        this->unk_3E0 += ABS_ALT(temp_v0);
    } else {
        this->unk_3E6 -= ABS_ALT(phi_a2);
        this->unk_3E0 -= ABS_ALT(temp_v0);
    }

    this->unk_3E6 = CLAMP(this->unk_3E6, -0x495F, 0x495F);
    this->unk_3E0 = CLAMP(this->unk_3E0, -0x256F, 0x256F);
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

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80B00F08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80B00F64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/EnTalkGibud_Draw.s")
