/*
 * File: z_en_floormas.c
 * Overlay: ovl_En_Floormas
 * Description: Floormaster
 */

#include "z_en_floormas.h"

#define FLAGS 0x00000405

#define THIS ((EnFloormas*)thisx)

void EnFloormas_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFloormas_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFloormas_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFloormas_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_808D0B08(EnFloormas* this);
void func_808D0B50(EnFloormas* this, GlobalContext* globalCtx);
void func_808D0C14(EnFloormas* this);
void func_808D0C58(EnFloormas* this, GlobalContext* globalCtx);
void func_808D0CE4(EnFloormas* this);
void func_808D0D70(EnFloormas* this, GlobalContext* globalCtx);
void func_808D0ECC(EnFloormas* this);
void func_808D0F14(EnFloormas* this, GlobalContext* globalCtx);
void func_808D0F50(EnFloormas* this);
void func_808D0F80(EnFloormas* this, GlobalContext* globalCtx);
void func_808D108C(EnFloormas* this);
void func_808D11BC(EnFloormas* this, GlobalContext* globalCtx);
void func_808D1380(EnFloormas* this, GlobalContext* globalCtx);
void func_808D1458(EnFloormas* this, GlobalContext* globalCtx);
void func_808D161C(EnFloormas* this);
void func_808D1650(EnFloormas* this, GlobalContext* globalCtx);
void func_808D1740(EnFloormas* this);
void func_808D17EC(EnFloormas* this, GlobalContext* globalCtx);
void func_808D19D4(EnFloormas* this);
void func_808D1B44(EnFloormas* this, GlobalContext* globalCtx);
void func_808D1BCC(EnFloormas* this);
void func_808D1C1C(EnFloormas* this, GlobalContext* globalCtx);
void func_808D1D0C(EnFloormas* this);
void func_808D1D6C(EnFloormas* this, GlobalContext* globalCtx);
void func_808D1ED4(EnFloormas* this, GlobalContext* globalCtx);
void func_808D1F7C(EnFloormas* this, GlobalContext* globalCtx);
void func_808D1FD4(EnFloormas* this);
void func_808D2040(EnFloormas* this, GlobalContext* globalCtx);
void func_808D217C(EnFloormas* this, Player* player);
void func_808D22C8(EnFloormas* this, GlobalContext* globalCtx);
void func_808D2484(EnFloormas* this);
void func_808D24F0(EnFloormas* this, GlobalContext* globalCtx);
void func_808D2700(EnFloormas* this);
void func_808D2764(EnFloormas* this, GlobalContext* globalCtx);
void func_808D2A20(EnFloormas* this);
void func_808D2AA8(EnFloormas* this, GlobalContext* globalCtx);
void func_808D2AB8(EnFloormas* this);
void func_808D2AF4(EnFloormas* this, GlobalContext* globalCtx);
void func_808D2C08(EnFloormas* this, GlobalContext* globalCtx);
void func_808D2CDC(EnFloormas* this);
void func_808D2D30(EnFloormas* this, GlobalContext* globalCtx);
void func_808D2DC0(EnFloormas* this, GlobalContext* globalCtx);
void func_808D3754(Actor* thisx, GlobalContext* globalCtx);

extern AnimationHeader D_06000590;
extern AnimationHeader D_06000EA4;
extern AnimationHeader D_060019CC;
extern AnimationHeader D_06002158;
extern AnimationHeader D_060039B0;
extern AnimationHeader D_060041F4;
extern Gfx D_06008688[];
extern FlexSkeletonHeader D_06008FB0;
extern AnimationHeader D_06009244;
extern AnimationHeader D_06009520;
extern AnimationHeader D_06009DB0;
extern AnimationHeader D_0600A054;

const ActorInit En_Floormas_InitVars = {
    ACTOR_EN_FLOORMAS,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_WALLMASTER,
    sizeof(EnFloormas),
    (ActorFunc)EnFloormas_Init,
    (ActorFunc)EnFloormas_Destroy,
    (ActorFunc)EnFloormas_Update,
    (ActorFunc)EnFloormas_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT0,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x04, 0x10 },
        { 0xF7EFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_HARD,
        BUMP_ON | BUMP_HOOKABLE,
        OCELEM_ON,
    },
    { 25, 40, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit sColChkInfoInit = { 3, 30, 40, 150 };

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x5),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0xE),
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
    ICHAIN_S8(hintId, 49, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 5500, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -1000, ICHAIN_STOP),
};

static Vec3f D_808D3900[] = {
    { 25.0f, 45.0f, -7.0f }, { 25.0f, 40.0f, -12.0f }, { 25.0f, 35.0f, -2.0f },
    { 10.0f, 20.0f, -4.0f }, { 15.0f, 25.0f, -2.0f },
};

static s8 D_808D393C[] = {
    -1, -1, -1, -1, 0, -1, -1, 1, -1, 2, -1, -1, 3, -1, 4, -1, -1, 5, -1, -1, -1, 6, 7, -1, 8,
};

static Color_RGBA8 D_808D3958 = { 0, 255, 0, 0 };

void EnFloormas_Init(Actor* thisx, GlobalContext* globalCtx2) {
    EnFloormas* this = THIS;
    GlobalContext* globalCtx = globalCtx2;
    s32 pad;
    s32 params;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 50.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &D_06008FB0, &D_06009DB0, this->jointTable, this->morphTable, 25);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);

    this->unk_192 = -1600;
    params = ENFLOORMAS_GET_8000(&this->actor);
    this->actor.params = ENFLOORMAS_GET_7FFF(&this->actor);

    if (params != 0) {
        this->actor.flags |= 0x80;
        this->actor.draw = func_808D3754;
    }

    if (this->actor.params == ENFLOORMAS_GET_7FFF_10) {
        this->actor.draw = NULL;
        this->actor.flags &= ~1;
        this->actionFunc = func_808D2AA8;
        return;
    }

    this->actor.parent = Actor_SpawnAsChildAndCutscene(
        &globalCtx->actorCtx, globalCtx, ACTOR_EN_FLOORMAS, this->actor.world.pos.x, this->actor.world.pos.y,
        this->actor.world.pos.z, 0, 0, 0, params + 0x10, -1, this->actor.unk20, NULL);
    if (this->actor.parent == NULL) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    this->actor.child = Actor_SpawnAsChildAndCutscene(
        &globalCtx->actorCtx, globalCtx, ACTOR_EN_FLOORMAS, this->actor.world.pos.x, this->actor.world.pos.y,
        this->actor.world.pos.z, 0, 0, 0, params + 0x10, -1, this->actor.unk20, NULL);
    if (this->actor.child == NULL) {
        Actor_MarkForDeath(this->actor.parent);
        Actor_MarkForDeath(&this->actor);
        return;
    }

    this->actor.parent->child = &this->actor;
    this->actor.parent->parent = this->actor.child;
    this->actor.child->parent = &this->actor;
    this->actor.child->child = this->actor.parent;
    func_808D0B08(this);
}

void EnFloormas_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnFloormas* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_808D08D0(EnFloormas* this) {
    this->collider.base.colType = COLTYPE_HARD;
    this->collider.base.acFlags |= AC_HARD;
    this->collider.info.bumper.dmgFlags &= ~0x8000;
    this->unk_190 = 40;
}

void func_808D0908(EnFloormas* this) {
    this->collider.base.colType = COLTYPE_HIT0;
    this->collider.base.acFlags &= ~AC_HARD;
    this->collider.info.bumper.dmgFlags |= 0x8000;
    this->unk_190 = 0;
}

void func_808D0930(EnFloormas* this, GlobalContext* globalCtx) {
    if (this->actor.scale.x > 0.009f) {
        this->actor.shape.rot.y = BINANG_ROT180(this->actor.yawTowardsPlayer);
        func_808D19D4((EnFloormas*)this->actor.child);
        func_808D19D4((EnFloormas*)this->actor.parent);
        func_808D19D4(this);
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_KUSAMUSHI_HIDE);
    } else {
        Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.world.pos, 0x90);
        func_808D1ED4(this, globalCtx);
    }
}

void func_808D09CC(EnFloormas* this) {
    this->unk_18C = 10;
    this->unk_2C8 = 0.55f;
    this->unk_2CC = 0.82500005f;
    this->unk_2C4 = 1.0f;
    this->collider.base.colType = COLTYPE_HIT3;
    this->unk_18E = 80;
    this->actor.flags &= ~(0x400 | 0x200);
    func_800BCB70(&this->actor, 0x4000, 255, 0, 80);
}

void func_808D0A48(EnFloormas* this, GlobalContext* globalCtx) {
    if (this->unk_18C == 10) {
        this->unk_18C = 0;
        this->collider.base.colType = COLTYPE_HIT0;
        this->unk_2C4 = 0.0f;
        func_800BF7CC(globalCtx, &this->actor, this->unk_2D0, ARRAY_COUNT(this->unk_2D0), 2,
                      this->actor.scale.x * 30.000002f, this->actor.scale.x * 20.0f);
        if (this->actor.scale.x > 0.009f) {
            this->actor.flags |= 0x400;
        } else {
            this->actor.flags |= 0x200;
        }
    }
}

void func_808D0B08(EnFloormas* this) {
    Animation_PlayOnce(&this->skelAnime, &D_06009DB0);
    this->actor.speedXZ = 0.0f;
    this->actionFunc = func_808D0B50;
}

void func_808D0B50(EnFloormas* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        if ((this->actor.xzDistToPlayer < 400.0f) && !Actor_IsActorFacingLink(&this->actor, 0x4000)) {
            this->unk_190 = this->actor.yawTowardsPlayer;
            func_808D108C(this);
        } else if ((this->actor.xzDistToPlayer < 280.0f) && Actor_IsActorFacingLink(&this->actor, 0x2000)) {
            func_808D1380(this, globalCtx);
        } else {
            func_808D0C14(this);
        }
    }
}

void func_808D0C14(EnFloormas* this) {
    Animation_MorphToPlayOnce(&this->skelAnime, &D_0600A054, -3.0f);
    this->actionFunc = func_808D0C58;
}

void func_808D0C58(EnFloormas* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->actor.scale.x > 0.009f) {
            func_808D0CE4(this);
        } else if (this->actor.params == ENFLOORMAS_GET_7FFF_20) {
            func_808D1D0C(this);
        } else {
            func_808D1BCC(this);
        }
    }
}

void func_808D0CE4(EnFloormas* this) {
    if (this->actionFunc != func_808D0F80) {
        Animation_PlayLoopSetSpeed(&this->skelAnime, &D_060041F4, 1.5f);
    } else {
        this->skelAnime.playSpeed = 1.5f;
    }

    this->unk_18E = Rand_S16Offset(2, 4);
    this->actor.speedXZ = 1.5f;
    this->actionFunc = func_808D0D70;
}

void func_808D0D70(EnFloormas* this, GlobalContext* globalCtx) {
    s32 temp_v0;

    SkelAnime_Update(&this->skelAnime);
    temp_v0 = Animation_OnFrame(&this->skelAnime, 0.0f);
    if ((temp_v0 != 0) && (this->unk_18E != 0)) {
        this->unk_18E--;
    }

    if ((temp_v0 != 0) || Animation_OnFrame(&this->skelAnime, 12.0f) || Animation_OnFrame(&this->skelAnime, 24.0f) ||
        Animation_OnFrame(&this->skelAnime, 36.0f)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_FALL_WALK);
    }

    if ((this->actor.xzDistToPlayer < 320.0f) && Actor_IsActorFacingLink(&this->actor, 0x4000)) {
        func_808D0F50(this);
    } else if (this->actor.bgCheckFlags & 8) {
        this->unk_190 = this->actor.wallYaw;
        func_808D108C(this);
    } else if ((this->actor.xzDistToPlayer < 400.0f) && !Actor_IsActorFacingLink(&this->actor, 0x4000)) {
        this->unk_190 = this->actor.yawTowardsPlayer;
        func_808D108C(this);
    } else if (this->unk_18E == 0) {
        func_808D0ECC(this);
    }
}

void func_808D0ECC(EnFloormas* this) {
    Animation_PlayOnce(&this->skelAnime, &D_06009244);
    this->actor.speedXZ = 0.0f;
    this->actionFunc = func_808D0F14;
}

void func_808D0F14(EnFloormas* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        func_808D0B08(this);
    }
}

void func_808D0F50(EnFloormas* this) {
    this->unk_18E = 0;
    this->actor.speedXZ = 5.0f;
    this->skelAnime.playSpeed = 3.0f;
    this->actionFunc = func_808D0F80;
}

void func_808D0F80(EnFloormas* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 12.0f) ||
        Animation_OnFrame(&this->skelAnime, 24.0f) || Animation_OnFrame(&this->skelAnime, 36.0f)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_FALL_WALK);
    }

    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 3, 0x71C);
    if ((this->actor.xzDistToPlayer < 280.0f) && Actor_IsActorFacingLink(&this->actor, 0x2000) &&
        !(this->actor.bgCheckFlags & 8)) {
        func_808D1380(this, globalCtx);
    } else if (this->actor.xzDistToPlayer > 400.0f) {
        func_808D0CE4(this);
    }
}

void func_808D108C(EnFloormas* this) {
    s16 sp36 = this->unk_190 - this->actor.shape.rot.y;

    this->actor.speedXZ = 0.0f;
    if (sp36 > 0) {
        Animation_MorphToPlayOnce(&this->skelAnime, &D_06002158, -3.0f);
    } else {
        Animation_Change(&this->skelAnime, &D_06002158, -1.0f, Animation_GetLastFrame(&D_06002158.common), 0.0f, 2,
                         -3.0f);
    }

    if (this->actor.scale.x > 0.009f) {
        this->unk_190 = sp36 * (1.0f / 15.0f);
    } else {
        this->skelAnime.playSpeed *= 2.0f;
        this->unk_190 = sp36 * (2.0f / 15.0f);
    }

    this->actionFunc = func_808D11BC;
}

void func_808D11BC(EnFloormas* this, GlobalContext* globalCtx) {
    f32 frame;
    f32 sp30;
    f32 sp2C;

    if (SkelAnime_Update(&this->skelAnime)) {
        func_808D0C14(this);
    }

    if (((this->skelAnime.playSpeed > 0.0f) && Animation_OnFrame(&this->skelAnime, 21.0f)) ||
        ((this->skelAnime.playSpeed < 0.0f) && Animation_OnFrame(&this->skelAnime, 6.0f))) {
        if (this->actor.scale.x > 0.009f) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_FALL_WALK);
        } else {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_FLOORMASTER_SM_WALK);
        }
    }

    frame = this->skelAnime.curFrame;
    if ((frame >= 7.0f) && (frame < 22.0f)) {
        sp30 = Math_SinS(this->actor.shape.rot.y + 0x4268);
        sp2C = Math_CosS(this->actor.shape.rot.y + 0x4268);
        this->actor.shape.rot.y += this->unk_190;
        this->actor.world.pos.x -= this->actor.scale.x * 2700.0f * (Math_SinS(this->actor.shape.rot.y + 0x4268) - sp30);
        this->actor.world.pos.z -= this->actor.scale.x * 2700.0f * (Math_CosS(this->actor.shape.rot.y + 0x4268) - sp2C);
    }
}

void func_808D1380(EnFloormas* this, GlobalContext* globalCtx) {
    Animation_Change(&this->skelAnime, &D_06009520, 3.0f, 0.0f, Animation_GetLastFrame(&D_06009520.common), 2, -3.0f);
    this->actor.speedXZ = 0.0f;
    this->actor.gravity = 0.0f;
    func_808D08D0(this);
    func_800BBDAC(globalCtx, &this->actor, &this->actor.world.pos, 15.0f, 6, 20.0f, 300, 100, 1);
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_FLOORMASTER_ATTACK);
    this->actionFunc = func_808D1458;
}

void func_808D1458(EnFloormas* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        func_808D161C(this);
    }

    this->actor.shape.rot.x += 0x140;
    this->actor.world.pos.y += 10.0f;
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 3, 0xAAA);
    Math_StepToS(&this->unk_192, 1200, 100);
}

void func_808D14DC(EnFloormas* this, GlobalContext* globalCtx) {
    Vec3f sp34;
    Vec3f sp28;

    sp34.x = this->actor.world.pos.x;
    sp34.z = this->actor.world.pos.z;
    sp34.y = this->actor.floorHeight;

    sp28.y = 2.0f;
    sp28.x = Math_SinS(this->actor.shape.rot.y + 0x6000) * 7.0f;
    sp28.z = Math_CosS(this->actor.shape.rot.y + 0x6000) * 7.0f;

    func_800B1210(globalCtx, &sp34, &sp28, &D_801D15B0, 0x1C2, 0x64);
    sp28.x = Math_SinS(this->actor.shape.rot.y - 0x6000) * 7.0f;
    sp28.z = Math_CosS(this->actor.shape.rot.y - 0x6000) * 7.0f;
    func_800B1210(globalCtx, &sp34, &sp28, &D_801D15B0, 0x1C2, 0x64);
    func_800B9010(&this->actor, NA_SE_EN_FLOORMASTER_SLIDING - SFX_FLAG);
}

void func_808D161C(EnFloormas* this) {
    this->unk_18E = 25;
    this->actor.gravity = -0.15f;
    this->actor.speedXZ = 0.5f;
    this->actionFunc = func_808D1650;
}

void func_808D1650(EnFloormas* this, GlobalContext* globalCtx) {
    f32 temp_f0_2;

    if (this->unk_18E != 0) {
        this->unk_18E--;
    }

    Math_StepToF(&this->actor.speedXZ, 15.0f, SQ(this->actor.speedXZ) * (1.0f / 3.0f));
    Math_ScaledStepToS(&this->actor.shape.rot.x, -0x1680, 0x140);

    temp_f0_2 = this->actor.world.pos.y - this->actor.floorHeight;
    if (temp_f0_2 < 10.0f) {
        this->actor.world.pos.y = this->actor.floorHeight + 10.0f;
        this->actor.gravity = 0.0f;
        this->actor.velocity.y = 0.0f;
    }

    if (temp_f0_2 < 12.0f) {
        func_808D14DC(this, globalCtx);
    }

    if ((this->actor.bgCheckFlags & 8) || (this->unk_18E == 0)) {
        func_808D1740(this);
    }
}

void func_808D1740(EnFloormas* this) {
    Animation_Change(&this->skelAnime, &D_060019CC, 1.0f, 41.0f, 42.0f, 2, 5.0f);
    if ((this->actor.speedXZ < 0.0f) || (this->actionFunc != func_808D1650)) {
        this->unk_18E = 30;
    } else {
        this->unk_18E = 45;
    }
    this->actor.gravity = -1.0f;
    this->actionFunc = func_808D17EC;
}

void func_808D17EC(EnFloormas* this, GlobalContext* globalCtx) {
    s32 sp24 = this->actor.bgCheckFlags & 1;

    if (this->actor.bgCheckFlags & 2) {
        if (this->actor.params != ENFLOORMAS_GET_7FFF_40) {
            func_808D0908(this);
        }

        if (this->actor.velocity.y < -4.0f) {
            if (this->actor.scale.x > 0.009f) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_FALL_LAND);
            } else {
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_FLOORMASTER_SM_LAND);
            }
        }
    }

    if (this->actor.bgCheckFlags & 8) {
        this->actor.speedXZ = 0.0f;
    }

    if (sp24 != 0) {
        Math_StepToF(&this->actor.speedXZ, 0.0f, 2.0f);
    }

    if ((this->actor.speedXZ > 0.0f) && ((this->actor.world.pos.y - this->actor.floorHeight) < 12.0f)) {
        func_808D14DC(this, globalCtx);
    }

    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->unk_18E != 0) {
            this->unk_18E--;
        }

        if ((this->unk_18E == 0) && (sp24 != 0)) {
            if (this->skelAnime.endFrame < 45.0f) {
                this->skelAnime.endFrame = Animation_GetLastFrame(&D_060019CC.common);
            } else if (this->actor.params == ENFLOORMAS_GET_7FFF_40) {
                func_808D2700(this);
            } else {
                func_808D0C14(this);
                this->unk_194 = 50;
            }
        }
    }

    Math_ScaledStepToS(&this->actor.shape.rot.x, 0, 0x140);
    Math_StepToS(&this->unk_192, -1600, 100);
}

void func_808D19D4(EnFloormas* this) {
    Actor* parent;

    this->actor.colorFilterTimer = 0;
    this->unk_2C4 = 0.0f;
    Actor_SetScale(&this->actor, 0.004f);
    this->actor.flags |= 0x10;
    if ((this->actor.flags & 0x80) == 0x80) {
        this->actor.draw = func_808D3754;
    } else {
        this->actor.draw = EnFloormas_Draw;
    }

    parent = this->actor.parent;
    this->actor.shape.rot.y = parent->shape.rot.y + 0x5555;
    this->actor.world.pos = parent->world.pos;
    this->actor.params = ENFLOORMAS_GET_7FFF_10;
    Animation_Change(&this->skelAnime, &D_060019CC, 1.0f, 41.0f, Animation_GetLastFrame(&D_060019CC.common), 2, 0.0f);
    this->collider.dim.radius = sCylinderInit.dim.radius * 0.6f;
    this->collider.dim.height = sCylinderInit.dim.height * 0.6f;
    this->actor.flags &= ~0x400;
    this->actor.flags |= 0x200;
    this->actor.colChkInfo.health = 1;
    this->actor.speedXZ = 4.0f;
    this->actor.velocity.y = 7.0f;
    this->actionFunc = func_808D1B44;
}

void func_808D1B44(EnFloormas* this, GlobalContext* globalCtx) {
    if (this->actor.bgCheckFlags & 1) {
        if (SkelAnime_Update(&this->skelAnime)) {
            this->actor.flags |= 1;
            this->unk_194 = 50;
            func_808D0C14(this);
        }
        Math_StepToF(&this->actor.speedXZ, 0.0f, 1.0f);
    }
    if (this->actor.bgCheckFlags & 2) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_FLOORMASTER_SM_LAND);
    }
}

void func_808D1BCC(EnFloormas* this) {
    Animation_PlayLoopSetSpeed(&this->skelAnime, &D_060041F4, 4.5f);
    this->actor.speedXZ = 5.0f;
    this->actionFunc = func_808D1C1C;
}

void func_808D1C1C(EnFloormas* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if (this->unk_194 != 0) {
        this->unk_194--;
    }

    if (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 18.0f)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_FLOORMASTER_SM_WALK);
    }

    if (this->unk_194 == 0) {
        func_808D1D0C(this);
    } else if (this->actor.bgCheckFlags & 8) {
        this->unk_190 = this->actor.wallYaw;
        func_808D108C(this);
    } else if (this->actor.xzDistToPlayer < 120.0f) {
        Math_ScaledStepToS(&this->actor.shape.rot.y, BINANG_ROT180(this->actor.yawTowardsPlayer), 0x38E);
    }
}

void func_808D1D0C(EnFloormas* this) {
    if (this->actionFunc != func_808D1C1C) {
        Animation_PlayLoopSetSpeed(&this->skelAnime, &D_060041F4, 4.5f);
    }
    this->actor.speedXZ = 5.0f;
    this->actionFunc = func_808D1D6C;
}

void func_808D1D6C(EnFloormas* this, GlobalContext* globalCtx) {
    Actor* sp2C;
    s32 flags;

    SkelAnime_Update(&this->skelAnime);
    if (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 18.0f)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_FLOORMASTER_SM_WALK);
    }

    flags = this->actor.bgCheckFlags & 8;
    if (flags) {
        this->unk_190 = this->actor.wallYaw;
        func_808D108C(this);
    } else if (this->actor.params == ENFLOORMAS_GET_7FFF_20) {
        if (this->actor.parent->params == ENFLOORMAS_GET_7FFF_40) {
            sp2C = this->actor.parent;
        } else if (this->actor.child->params == ENFLOORMAS_GET_7FFF_40) {
            sp2C = this->actor.child;
        } else {
            this->actor.params = ENFLOORMAS_GET_7FFF_10;
            return;
        }

        Math_ScaledStepToS(&this->actor.shape.rot.y, Actor_YawBetweenActors(&this->actor, sp2C), 0x38E);

        if (Actor_XZDistanceBetweenActors(&this->actor, sp2C) < 80.0f) {
            func_808D2484(this);
        }
    } else {
        Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 3, 0x71C);
        if (this->actor.xzDistToPlayer < 80.0f) {
            func_808D1FD4(this);
        }
    }
}

void func_808D1ED4(EnFloormas* this, GlobalContext* globalCtx) {
    Vec3f sp34;

    this->actor.speedXZ = 0.0f;
    this->actor.velocity.y = 0.0f;
    sp34.x = this->actor.world.pos.x;
    sp34.y = this->actor.world.pos.y + 15.0f;
    sp34.z = this->actor.world.pos.z;
    func_800B3030(globalCtx, &sp34, &D_801D15B0, &D_801D15B0, 150, -10, 2);
    Audio_PlaySoundAtPosition(globalCtx, &this->actor.world.pos, 11, NA_SE_EN_EXTINCT);
    this->actionFunc = func_808D1F7C;
}

void func_808D1F7C(EnFloormas* this, GlobalContext* globalCtx) {
    if (Math_StepToF(&this->actor.scale.x, 0.0f, 0.0015f)) {
        func_808D2A20(this);
    }
    this->actor.scale.y = this->actor.scale.z = this->actor.scale.x;
}

void func_808D1FD4(EnFloormas* this) {
    Animation_Change(&this->skelAnime, &D_060019CC, 2.0f, 0.0f, 41.0f, 2, 0.0f);
    this->actor.speedXZ = 0.0f;
    this->actionFunc = func_808D2040;
}

void func_808D2040(EnFloormas* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    SkelAnime_Update(&this->skelAnime);
    if (this->skelAnime.curFrame < 20.0f) {
        Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 0xE38);
    } else if (Animation_OnFrame(&this->skelAnime, 20.0f)) {
        this->actor.speedXZ = 5.0f;
        this->actor.velocity.y = 7.0f;
    } else if (this->actor.bgCheckFlags & 2) {
        this->unk_18E = 50;
        this->actor.speedXZ = 0.0f;
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_FLOORMASTER_SM_LAND);
        func_808D1740(this);
    } else if ((this->actor.playerHeightRel < -10.0f) && (this->collider.base.ocFlags1 & OC1_HIT) &&
               (&player->actor == this->collider.base.oc)) {
        globalCtx->grabPlayer(globalCtx, player);
        func_808D217C(this, player);
    }
}

void func_808D217C(EnFloormas* this, Player* player) {
    Vec3f* ptr;
    u8 playerForm;

    Animation_Change(&this->skelAnime, &D_060019CC, 1.0f, 36.0f, 45.0f, 2, -3.0f);
    this->actor.flags &= ~1;
    this->actor.speedXZ = 0.0f;
    this->actor.velocity.y = 0.0f;
    func_808D08D0(this);
    playerForm = gSaveContext.playerForm;
    ptr = &D_808D3900[playerForm];
    this->actor.home.pos.x = ptr->z * Math_SinS(this->actor.shape.rot.y);
    this->actor.home.pos.y = CLAMP(-this->actor.playerHeightRel, ptr->x, ptr->y);
    this->actor.home.pos.z = ptr->z * Math_CosS(this->actor.shape.rot.y);
    Math_Vec3f_Sum(&player->actor.world.pos, &this->actor.home.pos, &this->actor.world.pos);
    this->actor.shape.rot.x = -0x4CE0;
    this->actionFunc = func_808D22C8;
}

void func_808D22C8(EnFloormas* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->skelAnime.playSpeed > 0.0f) {
            this->skelAnime.playSpeed = -1.0f;
            this->skelAnime.endFrame = 36.0f;
            this->skelAnime.startFrame = 45.0f;
        } else {
            this->skelAnime.playSpeed = 1.0f;
            this->skelAnime.endFrame = 45.0f;
            this->skelAnime.startFrame = 36.0f;
        }
    }

    Math_Vec3f_Sum(&player->actor.world.pos, &this->actor.home.pos, &this->actor.world.pos);

    if (!(player->stateFlags2 & 0x80) || (player->invincibilityTimer < 0)) {
        EnFloormas* parent = (EnFloormas*)this->actor.parent;
        EnFloormas* child = (EnFloormas*)this->actor.child;

        if (((parent->actionFunc == func_808D22C8) || (parent->actionFunc == func_808D2AA8)) &&
            ((child->actionFunc == func_808D22C8) || (child->actionFunc == func_808D2AA8))) {
            parent->actor.params = ENFLOORMAS_GET_7FFF_20;
            child->actor.params = ENFLOORMAS_GET_7FFF_20;
            this->actor.params = ENFLOORMAS_GET_7FFF_40;
        }

        this->actor.shape.rot.x = 0;
        this->actor.velocity.y = 6.0f;
        this->actor.flags |= 1;
        this->actor.speedXZ = -3.0f;
        func_808D1740(this);
    } else if ((this->unk_190 % 20) == 0) {
        func_800B8E58(&player->actor, NA_SE_VO_LI_DAMAGE_S + player->ageProperties->unk_92);
        globalCtx->damagePlayer(globalCtx, -4);
    }
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_FLOORMASTER_SM_STICK - SFX_FLAG);
}

void func_808D2484(EnFloormas* this) {
    Animation_Change(&this->skelAnime, &D_060019CC, 2.0f, 0.0f, 41.0f, 2, 0.0f);
    this->actor.speedXZ = 0.0f;
    this->actionFunc = func_808D24F0;
}

void func_808D24F0(EnFloormas* this, GlobalContext* globalCtx) {
    Actor* phi_s1;

    SkelAnime_Update(&this->skelAnime);
    if (this->actor.parent->params == ENFLOORMAS_GET_7FFF_40) {
        phi_s1 = this->actor.parent;
    } else if (this->actor.child->params == ENFLOORMAS_GET_7FFF_40) {
        phi_s1 = this->actor.child;
    } else {
        if (this->actor.bgCheckFlags & 2) {
            this->actor.params = ENFLOORMAS_GET_7FFF_10;
            func_808D1740(this);
        }
        return;
    }

    if (Animation_OnFrame(&this->skelAnime, 20.0f)) {
        this->actor.speedXZ = 5.0f;
        this->actor.velocity.y = 7.0f;
    } else if (this->skelAnime.curFrame < 20.0f) {
        Math_ApproachS(&this->actor.shape.rot.y, Actor_YawBetweenActors(&this->actor, phi_s1), 2, 0xE38);
    } else if (((phi_s1->world.pos.y - this->actor.world.pos.y) < -10.0f) &&
               (fabsf(this->actor.world.pos.x - phi_s1->world.pos.x) < 10.0f) &&
               (fabsf(this->actor.world.pos.z - phi_s1->world.pos.z) < 10.0f)) {
        func_808D2A20(this);
        this->collider.base.ocFlags1 |= OC1_ON;
    } else if (this->actor.bgCheckFlags & 2) {
        this->actor.speedXZ = 0.0f;
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_FLOORMASTER_SM_LAND);
        func_808D1740(this);
    }

    if ((fabsf(this->actor.world.pos.x - phi_s1->world.pos.x) < 5.0f) &&
        (fabsf(this->actor.world.pos.z - phi_s1->world.pos.z) < 5.0f)) {
        Math_StepToF(&this->actor.speedXZ, 0.0f, 2.0f);
    }
}

void func_808D2700(EnFloormas* this) {
    Animation_PlayOnce(&this->skelAnime, &D_06009DB0);
    this->unk_18E = 0;
    this->unk_194 = 1500;
    this->actor.params = ENFLOORMAS_GET_7FFF_40;
    this->actor.speedXZ = 0.0f;
    func_808D08D0(this);
    this->actionFunc = func_808D2764;
}

void func_808D2764(EnFloormas* this, GlobalContext* globalCtx) {
    EnFloormas* parent;
    EnFloormas* child;
    s32 phi_a2 = 0;
    f32 temp_f2;

    if (this->unk_194 != 0) {
        this->unk_194--;
    }

    parent = (EnFloormas*)this->actor.parent;
    child = (EnFloormas*)this->actor.child;
    if (this->unk_194 == 0) {
        if (parent->actionFunc != func_808D2AA8) {
            func_808D1ED4(parent, globalCtx);
        }
        if (child->actionFunc != func_808D2AA8) {
            func_808D1ED4(child, globalCtx);
        }
    } else {
        if ((parent->actionFunc != func_808D2AA8) && (parent->actionFunc != func_808D1F7C)) {
            phi_a2 = 1;
        }

        if ((child->actionFunc != func_808D2AA8) && (child->actionFunc != func_808D1F7C)) {
            phi_a2++;
        }
    }

    temp_f2 = this->actor.scale.x;

    if (phi_a2 == 1) {
        Math_StepToF(&this->actor.scale.x, 0.007f, 0.0005f);
    } else if (phi_a2 == 0) {
        Math_StepToF(&this->actor.scale.x, 0.01f, 0.0005f);
    }

    this->actor.scale.y = this->actor.scale.z = this->actor.scale.x;

    if (((temp_f2 == 0.007f) || (temp_f2 == 0.004f)) && (temp_f2 != this->actor.scale.x)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_FLOORMASTER_EXPAND);
    }

    this->collider.dim.radius = sCylinderInit.dim.radius * 100.0f * this->actor.scale.x;
    this->collider.dim.height = sCylinderInit.dim.height * 100.0f * this->actor.scale.x;

    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->actor.scale.x >= 0.01f) {
            this->actor.flags &= ~0x10;
            func_808D0908(this);
            this->actor.params = ENFLOORMAS_GET_7FFF_0;
            this->actor.flags &= ~0x200;
            this->actor.flags |= 0x400;
            this->actor.colChkInfo.health = sColChkInfoInit.health;
            func_808D0C14(this);
        } else if (this->unk_18E == 0) {
            Animation_PlayOnce(&this->skelAnime, &D_060039B0);
            this->unk_18E = 1;
        } else {
            Animation_PlayOnce(&this->skelAnime, &D_06009DB0);
            this->unk_18E = 0;
        }
    }

    func_800B9010(&this->actor, NA_SE_EN_FLOORMASTER_RESTORE - SFX_FLAG);
}

void func_808D2A20(EnFloormas* this) {
    EnFloormas* parent = (EnFloormas*)this->actor.parent;
    EnFloormas* child = (EnFloormas*)this->actor.child;

    this->unk_2C4 = 0.0f;

    if ((parent->actionFunc == func_808D2AA8) && (child->actionFunc == func_808D2AA8)) {
        func_808D2AB8(parent);
        func_808D2AB8(child);
        Actor_MarkForDeath(&this->actor);
    } else {
        this->actor.draw = NULL;
        this->actor.flags &= ~(0x10 | 0x1);
        this->actionFunc = func_808D2AA8;
    }
}

void func_808D2AA8(EnFloormas* this, GlobalContext* globalCtx) {
}

void func_808D2AB8(EnFloormas* this) {
    this->collider.base.atFlags &= ~(AT_HIT | AT_ON);
    this->collider.base.acFlags &= ~(AC_HIT | AC_ON);
    this->collider.base.ocFlags1 &= ~(OC1_HIT | OC1_ON);
    this->actionFunc = func_808D2AF4;
}

void func_808D2AF4(EnFloormas* this, GlobalContext* globalCtx) {
    Actor_MarkForDeath(&this->actor);
}

void func_808D2B18(EnFloormas* this) {
    Animation_MorphToPlayOnce(&this->skelAnime, &D_06000590, -3.0f);
    func_800BE504(&this->actor, &this->collider);
    func_800BCB70(&this->actor, 0x4000, 255, 0, 20);
    this->actor.speedXZ = 5.0f;
    this->actor.velocity.y = 5.5f;
    if (this->actor.params == ENFLOORMAS_GET_7FFF_40) {
        EnFloormas* parent = (EnFloormas*)this->actor.parent;

        if ((parent->actionFunc != func_808D2AA8) && (parent->actor.colChkInfo.health > 0)) {
            func_808D2700(parent);
        } else {
            EnFloormas* child = (EnFloormas*)this->actor.child;

            if ((child->actionFunc != func_808D2AA8) && (child->actor.colChkInfo.health > 0)) {
                func_808D2700(child);
            }
        }
        this->actor.params = ENFLOORMAS_GET_7FFF_20;
    }
    this->actionFunc = func_808D2C08;
}

void func_808D2C08(EnFloormas* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime) && (this->actor.bgCheckFlags & 1)) {
        if (this->actor.colChkInfo.health == 0) {
            func_808D0930(this, globalCtx);
        } else {
            func_808D2CDC(this);
        }
    }

    if (Animation_OnFrame(&this->skelAnime, 13.0f)) {
        if (this->actor.scale.x > 0.009f) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_EYEGOLE_ATTACK);
        } else {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_EYEGOLE_ATTACK);
        }
    }

    Math_StepToF(&this->actor.speedXZ, 0.0f, 0.2f);
}

void func_808D2CDC(EnFloormas* this) {
    Animation_PlayOnce(&this->skelAnime, &D_06000EA4);
    this->actor.speedXZ = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = func_808D2D30;
}

void func_808D2D30(EnFloormas* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        func_808D0C14(this);
    }
}

void func_808D2D6C(EnFloormas* this) {
    this->actor.speedXZ = 0.0f;
    if (this->actor.velocity.y > 0.0f) {
        this->actor.velocity.y = 0.0f;
    }
    func_800BE504(&this->actor, &this->collider);
    this->actionFunc = func_808D2DC0;
}

void func_808D2DC0(EnFloormas* this, GlobalContext* globalCtx) {
    if (this->unk_18E != 0) {
        this->unk_18E--;
    }

    if (this->unk_18E == 0) {
        func_808D0A48(this, globalCtx);
        if (this->actor.colChkInfo.health == 0) {
            this->collider.base.acFlags |= AC_ON;
            func_808D0930(this, globalCtx);
        } else {
            func_808D0C14(this);
        }
    }
}

void func_808D2E34(EnFloormas* this, GlobalContext* globalCtx) {
    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        func_800BE258(&this->actor, &this->collider.info);
        if ((this->unk_18C != 10) || !(this->collider.info.acHitInfo->toucher.dmgFlags & 0xDB0B3)) {
            if (this->actor.colChkInfo.damageEffect == 0xE) {
                func_808D0908(this);
                this->actor.colorFilterTimer = 0;
                this->actor.colChkInfo.damage = 4;
                this->unk_192 = -1600;
                this->actor.gravity = -1.0f;
                this->unk_2C4 = 4.0f;
                this->unk_2C8 = 0.55f;
                this->unk_18C = 20;
            }

            if (this->collider.base.colType != COLTYPE_HARD) {
                if (!Actor_ApplyDamage(&this->actor)) {
                    if (this->actor.scale.x > 0.009f) {
                        Audio_PlayActorSound2(&this->actor, NA_SE_EN_DAIOCTA_REVERSE);
                    } else {
                        Audio_PlayActorSound2(&this->actor, NA_SE_EN_FLOORMASTER_SM_DEAD);
                    }
                    Enemy_StartFinishingBlow(globalCtx, &this->actor);
                    this->actor.flags &= ~1;
                } else if (this->actor.colChkInfo.damage != 0) {
                    Audio_PlayActorSound2(&this->actor, NA_SE_EN_FALL_DAMAGE);
                }

                func_808D0A48(this, globalCtx);

                if (this->actor.colChkInfo.damageEffect != 0xF) {
                    if (this->actor.colChkInfo.damageEffect == 3) {
                        func_808D09CC(this);
                        if (this->actor.colChkInfo.health == 0) {
                            this->unk_18E = 3;
                            this->collider.base.acFlags &= ~AC_ON;
                        }
                        func_808D2D6C(this);
                    } else if (this->actor.colChkInfo.damageEffect == 1) {
                        this->unk_18E = 40;
                        func_800BCB70(&this->actor, 0, 255, 0, 40);
                        Audio_PlayActorSound2(&this->actor, NA_SE_EN_COMMON_FREEZE);
                        func_808D2D6C(this);
                    } else if (this->actor.colChkInfo.damageEffect == 5) {
                        this->unk_18E = 40;
                        func_800BCB70(&this->actor, 0, 255, 0, 40);
                        Audio_PlayActorSound2(&this->actor, NA_SE_EN_COMMON_FREEZE);
                        this->unk_2C8 = 0.55f;
                        this->unk_2C4 = 2.0f;
                        this->unk_18C = 31;
                        func_808D2D6C(this);
                    } else {
                        if (this->actor.colChkInfo.damageEffect == 2) {
                            this->unk_2C4 = 4.0f;
                            this->unk_2C8 = 0.55f;
                            this->unk_18C = 0;
                        } else if (this->actor.colChkInfo.damageEffect == 4) {
                            this->unk_2C4 = 4.0f;
                            this->unk_2C8 = 0.55f;
                            this->unk_18C = 20;
                            Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG,
                                        this->collider.info.bumper.hitPos.x, this->collider.info.bumper.hitPos.y,
                                        this->collider.info.bumper.hitPos.z, 0, 0, 0,
                                        (this->actor.scale.x > 0.009f) ? CLEAR_TAG_LARGE_LIGHT_RAYS
                                                                       : CLEAR_TAG_SMALL_LIGHT_RAYS);
                        }
                        func_808D2B18(this);
                    }
                }
            }
        }
    }
}

void EnFloormas_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnFloormas* this = THIS;
    s32 pad;

    if (this->actionFunc != func_808D2AA8) {
        if (this->collider.base.atFlags & AT_HIT) {
            this->collider.base.atFlags &= ~AT_HIT;
            this->actor.speedXZ *= -0.5f;
            this->actor.speedXZ = CLAMP_MAX(this->actor.speedXZ, -5.0f);
            this->actor.velocity.y = 5.0f;
            func_808D1740(this);
        }

        func_808D2E34(this, globalCtx);
        this->actionFunc(this, globalCtx);
        if (this->actionFunc != func_808D2AF4) {
            if (this->actionFunc != func_808D2C08) {
                this->actor.world.rot.y = this->actor.shape.rot.y;
            }

            if (this->actionFunc != func_808D22C8) {
                Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
            }

            Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, this->actor.scale.x * 3000.0f, 0.0f, 0x1D);
            Collider_UpdateCylinder(&this->actor, &this->collider);
            if (this->actionFunc == func_808D1650) {
                this->actor.flags |= 0x1000000;
                CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
            }

            if (this->actionFunc != func_808D22C8) {
                if ((this->actionFunc != func_808D1B44) && (this->actionFunc != func_808D2C08) &&
                    (this->actionFunc != func_808D1F7C)) {
                    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
                }

                if ((this->actionFunc != func_808D24F0) || (this->skelAnime.curFrame < 20.0f)) {
                    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
                }
            }

            Actor_SetHeight(&this->actor, this->actor.scale.x * 2500.0f);
            if (this->collider.base.colType == COLTYPE_HARD) {
                if (this->unk_190 != 0) {
                    this->unk_190--;
                }

                if (this->unk_190 == 0) {
                    this->unk_190 = 40;
                }
            }

            if (this->unk_2C4 > 0.0f) {
                if (this->unk_18C != 10) {
                    Math_StepToF(&this->unk_2C4, 0.0f, 0.05f);
                    this->unk_2C8 = (this->unk_2C4 + 1.0f) * 0.275f;
                    this->unk_2C8 = CLAMP_MAX(this->unk_2C8, 0.55f);
                } else if (!Math_StepToF(&this->unk_2CC, 0.55f, 0.01375f)) {
                    func_800B9010(&this->actor, NA_SE_EV_ICE_FREEZE - SFX_FLAG);
                }
            }
        }
    }
}

s32 EnFloormas_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                Actor* thisx, Gfx** gfx) {
    EnFloormas* this = THIS;

    if (limbIndex == 1) {
        pos->z += this->unk_192;
    }
    return false;
}

void EnFloormas_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx,
                             Gfx** gfx) {
    EnFloormas* this = THIS;

    if (D_808D393C[limbIndex] != -1) {
        Matrix_GetStateTranslation(&this->unk_2D0[D_808D393C[limbIndex]]);
    }

    if (limbIndex == 19) {
        Matrix_GetStateTranslationAndScaledX(1000.0f, &this->unk_2D0[9]);
        Matrix_GetStateTranslationAndScaledX(-1000.0f, &this->unk_2D0[10]);
        return;
    }

    if (limbIndex == 2) {
        Matrix_StatePush();
        Matrix_InsertTranslation(1600.0f, -700.0f, -1700.0f, MTXMODE_APPLY);
        Matrix_InsertYRotation_f(M_PI / 3, MTXMODE_APPLY);
        Matrix_InsertZRotation_f(M_PI / 12, MTXMODE_APPLY);
        Matrix_Scale(2.0f, 2.0f, 2.0f, MTXMODE_APPLY);

        gSPMatrix((*gfx)++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList((*gfx)++, D_06008688);

        Matrix_StatePop();
    }
}

void EnFloormas_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnFloormas* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    if (this->collider.base.colType == COLTYPE_HARD) {
        func_800AE2A0(globalCtx, &D_808D3958, this->unk_190 % 40, 40);
    }

    POLY_OPA_DISP =
        SkelAnime_DrawFlex(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                           EnFloormas_OverrideLimbDraw, EnFloormas_PostLimbDraw, &this->actor, POLY_OPA_DISP);
    if (this->collider.base.colType == COLTYPE_HARD) {
        func_800AE5A0(globalCtx);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);

    func_800BE680(globalCtx, &this->actor, this->unk_2D0, ARRAY_COUNT(this->unk_2D0),
                  100.0f * (this->unk_2C8 * this->actor.scale.x), 100.0f * (this->unk_2CC * this->actor.scale.x),
                  this->unk_2C4, this->unk_18C);
}

void func_808D3754(Actor* thisx, GlobalContext* globalCtx) {
    EnFloormas* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);
    if (this->collider.base.colType == COLTYPE_HARD) {
        func_800AE5E4(globalCtx, &D_808D3958, this->unk_190 % 40, 40);
    }

    POLY_XLU_DISP =
        SkelAnime_DrawFlex(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                           EnFloormas_OverrideLimbDraw, EnFloormas_PostLimbDraw, &this->actor, POLY_XLU_DISP);
    if (this->collider.base.colType == COLTYPE_HARD) {
        func_800AE8EC(globalCtx);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);

    func_800BE680(globalCtx, &this->actor, this->unk_2D0, ARRAY_COUNT(this->unk_2D0),
                  this->unk_2C8 * this->actor.scale.x * 100.0f, this->unk_2CC * this->actor.scale.x * 100.0f,
                  this->unk_2C4, this->unk_18C);
}
