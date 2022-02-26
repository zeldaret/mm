/*
 * File: z_en_poh.c
 * Overlay: ovl_En_Poh
 * Description: Poe
 */

#include "z_en_poh.h"
#include "objects/object_po/object_po.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_200 | ACTOR_FLAG_1000)

#define THIS ((EnPoh*)thisx)

void EnPoh_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPoh_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPoh_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPoh_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B2CAA4(EnPoh* this, GlobalContext* globalCtx);
void func_80B2CB60(EnPoh* this);
void func_80B2CBBC(EnPoh* this, GlobalContext* globalCtx);
void func_80B2CD14(EnPoh* this);
void func_80B2CD64(EnPoh* this, GlobalContext* globalCtx);
void func_80B2CEC8(EnPoh* this);
void func_80B2CF28(EnPoh* this, GlobalContext* globalCtx);
void func_80B2D07C(EnPoh* this, GlobalContext* globalCtx);
void func_80B2D0E8(EnPoh* this);
void func_80B2D140(EnPoh* this, GlobalContext* globalCtx);
void func_80B2D2C0(EnPoh* this);
void func_80B2D300(EnPoh* this, GlobalContext* globalCtx);
void func_80B2D628(EnPoh* this, GlobalContext* globalCtx);
void func_80B2D694(EnPoh* this);
void func_80B2D6EC(EnPoh* this, GlobalContext* globalCtx);
void func_80B2D7D4(EnPoh* this, GlobalContext* globalCtx);
void func_80B2D980(EnPoh* this, GlobalContext* globalCtx);
void func_80B2DAD0(EnPoh* this);
void func_80B2DB44(EnPoh* this, GlobalContext* globalCtx);
void func_80B2DC50(EnPoh* this, GlobalContext* globalCtx);
void func_80B2DD2C(EnPoh* this, GlobalContext* globalCtx);
void func_80B2E0B0(EnPoh* this);
void func_80B2E180(EnPoh* this, GlobalContext* globalCtx);
void func_80B2E1D8(EnPoh* this);
void func_80B2E230(EnPoh* this, GlobalContext* globalCtx);
void func_80B2E3B0(EnPoh* this);
void func_80B2E3F8(EnPoh* this, GlobalContext* globalCtx);
void func_80B2F328(Actor* thisx, GlobalContext* globalCtx);
void func_80B2F37C(Actor* thisx, GlobalContext* globalCtx);

const ActorInit En_Poh_InitVars = {
    ACTOR_EN_POH,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_PO,
    sizeof(EnPoh),
    (ActorFunc)EnPoh_Init,
    (ActorFunc)EnPoh_Destroy,
    (ActorFunc)EnPoh_Update,
    (ActorFunc)EnPoh_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT3,
        AT_NONE,
        AC_NONE | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CBFFFE, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON | BUMP_HOOKABLE,
        OCELEM_ON,
    },
    { 20, 40, 20, { 0, 0, 0 } },
};

static ColliderJntSphElementInit sJntSphElementsInit[1] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x08 },
            { 0x00000000, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_NONE,
            OCELEM_ON,
        },
        { 18, { { 0, 1400, 0 }, 10 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_HIT3,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    1,
    sJntSphElementsInit,
};

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0xF),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xE),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x0),
    /* Ice arrow      */ DMG_ENTRY(1, 0x0),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
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

static CollisionCheckInfoInit sColChkInfoInit = { 3, 25, 50, 50 };

static InitChainEntry sInitChain[] = {
    ICHAIN_S8(hintId, 68, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 3200, ICHAIN_STOP),
};

void EnPoh_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnPoh* this = THIS;
    s32 pad;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 30.0f);
    Collider_InitAndSetJntSph(globalCtx, &this->colliderSph, &this->actor, &sJntSphInit, this->colliderSphElements);
    this->colliderSph.elements[0].dim.worldSphere.radius = 0;
    this->colliderSph.elements[0].dim.worldSphere.center.x = this->actor.world.pos.x;
    this->colliderSph.elements[0].dim.worldSphere.center.y = this->actor.world.pos.y;
    this->colliderSph.elements[0].dim.worldSphere.center.z = this->actor.world.pos.z;
    Collider_InitAndSetCylinder(globalCtx, &this->colliderCylinder, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    this->unk_18D = 32;
    this->unk_190 = Rand_S16Offset(700, 300);
    this->lightNode = LightContext_InsertLight(globalCtx, &globalCtx->lightCtx, &this->lightInfo);
    Lights_PointGlowSetInfo(&this->lightInfo, this->actor.home.pos.x, this->actor.home.pos.y, this->actor.home.pos.z,
                            255, 255, 255, 0);
    SkelAnime_Init(globalCtx, &this->skelAnime, &object_po_Skel_0050D0, &object_po_Anim_000A60, this->jointTable,
                   this->morphTable, 21);
    this->actor.bgCheckFlags |= 0x400;
    func_80B2D0E8(this);
}

void EnPoh_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnPoh* this = THIS;

    LightContext_RemoveLight(globalCtx, &globalCtx->lightCtx, this->lightNode);
    Collider_DestroyJntSph(globalCtx, &this->colliderSph);
    Collider_DestroyCylinder(globalCtx, &this->colliderCylinder);
}

void func_80B2C910(Vec3f* vec, GlobalContext* globalCtx) {
    Camera* activeCam = GET_ACTIVE_CAM(globalCtx);
    Vec3f sp20;
    f32 temp_f0;

    if (activeCam != NULL) {
        Math_Vec3f_Diff(&activeCam->eye, &activeCam->at, &sp20);
        temp_f0 = Math3D_Vec3fMagnitude(&sp20);
        if (temp_f0 > 1.0f) {
            temp_f0 = 11.0f / temp_f0;
        } else {
            temp_f0 = 11.0f;
        }
        Math_Vec3f_ScaleAndStore(&sp20, temp_f0, vec);
    } else {
        Math_Vec3f_Copy(vec, &gZeroVec3f);
    }
}

void func_80B2C9B8(EnPoh* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    Math_StepToF(&this->actor.world.pos.y, player->actor.world.pos.y, 1.0f);
    this->actor.world.pos.y += 2.5f * Math_SinS(this->unk_18D * 0x800);
    if (this->unk_18D != 0) {
        this->unk_18D--;
    }

    if (!this->unk_18D) {
        this->unk_18D = 32;
    }
}

void func_80B2CA4C(EnPoh* this) {
    Animation_PlayLoop(&this->skelAnime, &object_po_Anim_0015B0);
    this->unk_18E = Rand_S16Offset(2, 3);
    this->actionFunc = func_80B2CAA4;
    this->actor.speedXZ = 0.0f;
}

void func_80B2CAA4(EnPoh* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if (Animation_OnFrame(&this->skelAnime, 0.0f) && (this->unk_18E != 0)) {
        this->unk_18E--;
    }

    func_80B2C9B8(this, globalCtx);

    if (this->actor.xzDistToPlayer < 200.0f) {
        func_80B2CD14(this);
    } else if (this->unk_18E == 0) {
        func_80B2CB60(this);
    }

    if (this->unk_197 == 255) {
        func_800B9010(&this->actor, NA_SE_EN_PO_FLY - SFX_FLAG);
    }
}

void func_80B2CB60(EnPoh* this) {
    Animation_PlayLoop(&this->skelAnime, &object_po_Anim_000A60);
    this->unk_18E = Rand_S16Offset(15, 3);
    this->colliderCylinder.base.acFlags |= AC_ON;
    this->actionFunc = func_80B2CBBC;
}

void func_80B2CBBC(EnPoh* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    Math_StepToF(&this->actor.speedXZ, 1.0f, 0.2f);
    if (Animation_OnFrame(&this->skelAnime, 0.0f) && (this->unk_18E != 0)) {
        this->unk_18E--;
    }

    if (Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos) > 400.0f) {
        this->unk_192 = Actor_YawToPoint(&this->actor, &this->actor.home.pos);
    }

    Math_ScaledStepToS(&this->actor.world.rot.y, this->unk_192, 0x71C);
    func_80B2C9B8(this, globalCtx);
    if ((this->actor.xzDistToPlayer < 200.0f) && (this->unk_18E < 19)) {
        func_80B2CD14(this);
    } else if (this->unk_18E == 0) {
        if (Rand_ZeroOne() < 0.1f) {
            func_80B2D694(this);
        } else {
            func_80B2CA4C(this);
        }
    }

    if (this->unk_197 == 255) {
        func_800B9010(&this->actor, NA_SE_EN_PO_FLY - SFX_FLAG);
    }
}

void func_80B2CD14(EnPoh* this) {
    Animation_PlayLoop(&this->skelAnime, &object_po_Anim_000A60);
    this->actionFunc = func_80B2CD64;
    this->unk_18E = 0;
    this->actor.speedXZ = 2.0f;
}

void func_80B2CD64(EnPoh* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 yawDiff;

    SkelAnime_Update(&this->skelAnime);
    if (this->unk_18E != 0) {
        this->unk_18E--;
    }

    yawDiff = this->actor.yawTowardsPlayer - player->actor.shape.rot.y;
    if (yawDiff > 0x3000) {
        Math_ScaledStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer + 0x3000, 0x71C);
    } else if (yawDiff < -0x3000) {
        Math_ScaledStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer - 0x3000, 0x71C);
    } else {
        Math_ScaledStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 0x71C);
    }

    func_80B2C9B8(this, globalCtx);

    if (this->actor.xzDistToPlayer > 280.0f) {
        func_80B2CB60(this);
    } else if ((this->unk_18E == 0) && (this->actor.xzDistToPlayer < 140.0f) &&
               !Player_IsFacingActor(&this->actor, 0x2AAA, globalCtx)) {
        func_80B2CEC8(this);
    }

    if (this->unk_197 == 255) {
        func_800B9010(&this->actor, NA_SE_EN_PO_FLY - SFX_FLAG);
    }
}

void func_80B2CEC8(EnPoh* this) {
    Animation_MorphToLoop(&this->skelAnime, &object_po_Anim_0001A8, -6.0f);
    this->unk_18E = 12;
    this->actor.speedXZ = 0.0f;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PO_LAUGH);
    this->actionFunc = func_80B2CF28;
}

void func_80B2CF28(EnPoh* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PO_KANTERA);
        if (this->unk_18E != 0) {
            this->unk_18E--;
        }
    }

    func_80B2C9B8(this, globalCtx);
    if (this->unk_18E >= 10) {
        Math_ScaledStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 0xAAA);
    } else if (this->unk_18E == 9) {
        this->actor.speedXZ = 5.0f;
        this->skelAnime.playSpeed = 2.0f;
    } else if (this->unk_18E == 0) {
        func_80B2CB60(this);
        this->unk_18E = 0x17;
    }
}

void func_80B2CFF8(EnPoh* this) {
    Animation_MorphToPlayOnce(&this->skelAnime, &object_po_Anim_0004EC, -6.0f);
    func_800BE504(&this->actor, &this->colliderCylinder);
    this->colliderCylinder.base.acFlags &= ~AC_ON;
    this->actor.speedXZ = 5.0f;
    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 16);
    this->actionFunc = func_80B2D07C;
}

void func_80B2D07C(EnPoh* this, GlobalContext* globalCtx) {
    Math_StepToF(&this->actor.speedXZ, 0.0f, 0.5f);
    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->actor.colChkInfo.health != 0) {
            func_80B2DAD0(this);
        } else {
            func_80B2D2C0(this);
        }
    }
}

void func_80B2D0E8(EnPoh* this) {
    this->unk_197 = 0;
    this->actor.flags &= ~ACTOR_FLAG_1;
    Animation_PlayOnceSetSpeed(&this->skelAnime, &object_po_Anim_0011C4, 0.0f);
    this->actionFunc = func_80B2D140;
}

void func_80B2D140(EnPoh* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        this->unk_197 = 255;
        this->unk_190 = Rand_S16Offset(700, 300);
        this->actor.flags |= ACTOR_FLAG_1;
        func_80B2CB60(this);
    } else if (this->skelAnime.curFrame > 10.0f) {
        this->unk_197 = (this->skelAnime.curFrame - 10.0f) * 0.05f * 255.0f;
    }

    if ((this->skelAnime.playSpeed < 0.5f) && (this->actor.xzDistToPlayer < 280.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_APPEAR);
        this->skelAnime.playSpeed = 1.0f;
    }
}

void func_80B2D2C0(EnPoh* this) {
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->unk_18E = 0;
    this->actor.hintId = 0xFF;
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->actionFunc = func_80B2D300;
}

void func_80B2D300(EnPoh* this, GlobalContext* globalCtx) {
    static Vec3f D_80B2F710 = { 0.0f, 3.0f, 0.0f };
    Vec3f sp44;
    f32 sp40;
    s32 pad;
    s16 sp3A;
    s16 sp38;
    s16 sp36;

    this->unk_18E++;
    if (this->unk_18E < 8) {
        sp38 = Camera_GetCamDirYaw(GET_ACTIVE_CAM(globalCtx)) + 0x4800;
        if (this->unk_18E < 5) {
            sp3A = (this->unk_18E * 0x1000) - 0x4000;
            sp44.y = (Math_SinS(sp3A) * 23.0f) + (this->actor.world.pos.y + 40.0f);
            sp40 = Math_CosS(sp3A) * 23.0f;
            sp44.x = (Math_SinS(sp38) * sp40) + this->actor.world.pos.x;
            sp44.z = (Math_CosS(sp38) * sp40) + this->actor.world.pos.z;
        } else {
            sp44.y = this->actor.world.pos.y + 40.0f + (15.0f * (this->unk_18E - 5));
            sp44.x = (Math_SinS(sp38) * 23.0f) + this->actor.world.pos.x;
            sp44.z = (Math_CosS(sp38) * 23.0f) + this->actor.world.pos.z;
        }
        sp36 = (this->unk_18E * 10) + 80;
        func_800B3030(globalCtx, &sp44, &D_80B2F710, &gZeroVec3f, sp36, 0, 2);
        sp44.x = (2.0f * this->actor.world.pos.x) - sp44.x;
        sp44.z = (2.0f * this->actor.world.pos.z) - sp44.z;
        func_800B3030(globalCtx, &sp44, &D_80B2F710, &gZeroVec3f, sp36, 0, 2);
        sp44.x = this->actor.world.pos.x;
        sp44.z = this->actor.world.pos.z;
        func_800B3030(globalCtx, &sp44, &D_80B2F710, &gZeroVec3f, sp36, 0, 2);
    } else if (this->unk_18E == 28) {
        func_80B2DC50(this, globalCtx);
    } else if (this->unk_18E > 18) {
        this->actor.scale.x = (28 - this->unk_18E) * 0.001f;
        this->actor.scale.y = (28 - this->unk_18E) * 0.001f;
        this->actor.scale.z = (28 - this->unk_18E) * 0.001f;
        this->actor.world.pos.y += 5.0f;
    }

    if (this->unk_18E < 18) {
        func_800B9010(&this->actor, NA_SE_EN_COMMON_EXTINCT_LEV - SFX_FLAG);
    }

    if (this->unk_18E == 18) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WIZ_DISAPPEAR);
    }
}

void func_80B2D5DC(EnPoh* this) {
    Animation_PlayOnce(&this->skelAnime, &object_po_Anim_000A60);
    this->actionFunc = func_80B2D628;
    this->actor.speedXZ = -5.0f;
}

void func_80B2D628(EnPoh* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        this->actor.world.rot.y = this->actor.shape.rot.y;
        func_80B2CB60(this);
        this->unk_18E = 23;
    } else {
        Math_StepToF(&this->actor.speedXZ, 0.0f, 0.5f);
        this->actor.shape.rot.y += 0x1000;
    }
}

void func_80B2D694(EnPoh* this) {
    Animation_PlayLoop(&this->skelAnime, &object_po_Anim_0015B0);
    this->unk_192 = BINANG_ROT180(this->actor.world.rot.y);
    this->actionFunc = func_80B2D6EC;
    this->actor.speedXZ = 0.0f;
}

void func_80B2D6EC(EnPoh* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if (Math_ScaledStepToS(&this->actor.world.rot.y, this->unk_192, 0x71C)) {
        func_80B2CB60(this);
    }

    if (this->actor.xzDistToPlayer < 200.0f) {
        func_80B2CD14(this);
    }

    func_80B2C9B8(this, globalCtx);
}

void func_80B2D76C(EnPoh* this) {
    this->unk_18C = 32;
    this->unk_192 = 0x2000;
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PO_DISAPPEAR);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PO_LAUGH);
    this->colliderCylinder.base.acFlags &= ~AC_ON;
    this->actionFunc = func_80B2D7D4;
}

void func_80B2D7D4(EnPoh* this, GlobalContext* globalCtx) {
    if (this->unk_18C != 0) {
        this->unk_18C--;
    }

    this->actor.world.rot.y += this->unk_192;

    if (this->unk_18C < 16) {
        Math_ScaledStepToS(&this->unk_192, 0, 0x200);
    }

    func_80B2C9B8(this, globalCtx);
    this->unk_197 = this->unk_18C * (255.0f / 32.0f);
    if (this->unk_18C == 0) {
        this->unk_190 = Rand_S16Offset(100, 50);
        this->colliderCylinder.info.bumper.dmgFlags = 0x40001;
        func_80B2CB60(this);
    }
}

void func_80B2D924(EnPoh* this) {
    this->unk_18C = 0;
    this->unk_192 = 0x2000;
    this->actor.speedXZ = 0.0f;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_APPEAR);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PO_LAUGH);
    this->colliderCylinder.base.acFlags &= ~AC_ON;
    this->actionFunc = func_80B2D980;
}

void func_80B2D980(EnPoh* this, GlobalContext* globalCtx) {
    this->unk_18C++;
    this->actor.world.rot.y -= this->unk_192;
    if (this->unk_18C > 15) {
        Math_ScaledStepToS(&this->unk_192, 0, 0x200);
    }

    func_80B2C9B8(this, globalCtx);
    this->unk_197 = this->unk_18C * (255.0f / 32.0f);
    if (this->unk_18C == 32) {
        this->unk_190 = Rand_S16Offset(700, 300);
        this->unk_18C = 0;
        this->colliderCylinder.info.bumper.dmgFlags = ~0x8340001;
        func_80B2CB60(this);
    }
}

void func_80B2DAD0(EnPoh* this) {
    Animation_MorphToLoop(&this->skelAnime, &object_po_Anim_0006E0, -5.0f);
    this->actor.speedXZ = 5.0f;
    this->actor.world.rot.y = BINANG_ROT180(this->actor.shape.rot.y);
    this->colliderCylinder.base.acFlags |= AC_ON;
    this->unk_18E = 200;
    this->actionFunc = func_80B2DB44;
}

void func_80B2DB44(EnPoh* this, GlobalContext* globalCtx) {
    f32 sp24;

    SkelAnime_Update(&this->skelAnime);
    sp24 = Math_SinS(this->unk_18D * 0x800) * 3.0f;
    this->actor.world.pos.x -= sp24 * Math_CosS(this->actor.shape.rot.y);
    this->actor.world.pos.z += sp24 * Math_SinS(this->actor.shape.rot.y);
    Math_ScaledStepToS(&this->actor.world.rot.y, BINANG_ROT180(this->actor.yawTowardsPlayer), 0x71C);
    func_80B2C9B8(this, globalCtx);
    this->unk_18E--;
    if ((this->unk_18E == 0) || (this->actor.xzDistToPlayer > 250.0f)) {
        this->actor.world.rot.y = this->actor.shape.rot.y;
        func_80B2CB60(this);
    }
    func_800B9010(&this->actor, NA_SE_EN_PO_AWAY - SFX_FLAG);
}

void func_80B2DC50(EnPoh* this, GlobalContext* globalCtx) {
    this->actor.update = func_80B2F328;
    this->actor.draw = func_80B2F37C;
    this->actor.shape.shadowDraw = NULL;
    this->actor.world.pos.x = this->unk_3D8.wx;
    this->actor.world.pos.y = this->unk_3D8.wy;
    this->actor.world.pos.z = this->unk_3D8.wz;
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.flags |= ACTOR_FLAG_10;
    this->actor.gravity = -1.0f;
    this->actor.shape.yOffset = 1500.0f;
    this->actor.world.pos.y -= 15.0f;
    this->actor.shape.rot.x = -0x8000;
    func_800BC154(globalCtx, &globalCtx->actorCtx, &this->actor, 8);
    this->actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_4);
    this->actionFunc = func_80B2DD2C;
}

void func_80B2DD2C(EnPoh* this, GlobalContext* globalCtx) {
    if ((this->actor.bgCheckFlags & 1) || (this->actor.floorHeight <= BGCHECK_Y_MIN)) {
        EffectSsHahen_SpawnBurst(globalCtx, &this->actor.world.pos, 6.0f, 0, 1, 1, 15, OBJECT_PO, 10,
                                 object_po_DL_002D28);
        func_80B2E0B0(this);
    }

    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 10.0f, 10.0f, 10.0f, 4);
}

void func_80B2DDF8(EnPoh* this, s32 arg1) {
    f32 temp_f2;

    this->unk_197 = CLAMP(this->unk_197 + arg1, 0, 255);

    if (arg1 < 0) {
        temp_f2 = this->unk_197 * (1.0f / 255.0f);
        this->actor.scale.x = this->actor.scale.z = (0.0056000003f * temp_f2) + 0.0014000001f;
        this->actor.scale.y = (0.007f - (0.007f * temp_f2)) + 0.007f;
    } else {
        temp_f2 = 1.0f;
        this->actor.scale.x = this->actor.scale.y = this->actor.scale.z = this->unk_197 * 0.000027450982f;
        this->actor.world.pos.y = this->actor.home.pos.y + ((15.0f / 255.0f) * this->unk_197);
    }

    this->unk_194 = 100.0f * temp_f2;
    this->unk_195 = 0;
    this->unk_196 = 150.0f * temp_f2;
    Lights_PointNoGlowSetInfo(&this->lightInfo, this->actor.world.pos.x, this->actor.world.pos.y,
                              this->actor.world.pos.z, 100, 0, 150, this->unk_197 * (200.0f / 255.0f));
}

void func_80B2E0B0(EnPoh* this) {
    Lights_PointNoGlowSetInfo(&this->lightInfo, this->actor.world.pos.x, this->actor.world.pos.y,
                              this->actor.world.pos.z, 0, 0, 0, 0);
    this->unk_190 = 0;
    this->actor.shape.rot.y = 0;
    this->unk_194 = 0;
    this->unk_197 = 0;
    this->unk_195 = 0;
    this->unk_196 = 200;
    this->actor.shape.rot.x = 0;
    this->actor.shape.yOffset = 0.0f;
    this->actor.gravity = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->actor.home.pos.y = this->actor.world.pos.y;
    this->actor.scale.x = 0.0f;
    this->actor.scale.y = 0.0f;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_METAL_BOX_BOUND);
    this->actionFunc = func_80B2E180;
}

void func_80B2E180(EnPoh* this, GlobalContext* globalCtx) {
    this->actor.home.pos.y += 2.0f;
    func_80B2DDF8(this, 20);
    if (this->unk_197 == 255) {
        func_80B2E1D8(this);
    }
}

void func_80B2E1D8(EnPoh* this) {
    this->actor.home.pos.y = this->actor.world.pos.y;
    Actor_SetFocus(&this->actor, -10.0f);
    this->unk_18E = 200;
    this->unk_18D = 32;
    this->actor.flags |= ACTOR_FLAG_1;
    this->actionFunc = func_80B2E230;
}

void func_80B2E230(EnPoh* this, GlobalContext* globalCtx) {

    if (Actor_HasParent(&this->actor, globalCtx)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    this->unk_18E--;
    if (this->unk_18E == 0) {
        func_80B2E3B0(this);
        return;
    }

    Actor_PickUp(&this->actor, globalCtx, GI_MAX, 35.0f, 60.0f);
    this->actor.world.pos.y = (Math_SinS(this->unk_18D * 0x800) * 5.0f) + this->actor.home.pos.y;
    if (this->unk_18D) {
        this->unk_18D--;
    }

    if (this->unk_18D == 0) {
        this->unk_18D = 32;
    }

    Actor_SetFocus(&this->actor, -10.0f);
    Lights_PointNoGlowSetInfo(&this->lightInfo, this->actor.world.pos.x, this->actor.world.pos.y,
                              this->actor.world.pos.z, 100, 0, 150, this->unk_197 * (40.0f / 51.0f));
}

void func_80B2E3B0(EnPoh* this) {
    func_801A7328(&this->actor.projectedPos, NA_SE_EN_PO_BIG_CRY - SFX_FLAG);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PO_LAUGH);
    this->actionFunc = func_80B2E3F8;
}

void func_80B2E3F8(EnPoh* this, GlobalContext* globalCtx) {
    func_80B2DDF8(this, -13);
    if (this->unk_197 == 0) {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80B2E438(EnPoh* this, GlobalContext* globalCtx) {
    if (this->colliderCylinder.base.acFlags & AC_HIT) {
        this->colliderCylinder.base.acFlags &= ~AC_HIT;
        if (!Actor_ApplyDamage(&this->actor)) {
            Enemy_StartFinishingBlow(globalCtx, &this->actor);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PO_DEAD);
        } else if (this->actor.colChkInfo.damage != 0) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PO_DAMAGE);
        }

        if (this->actor.colChkInfo.damageEffect != 14) {
            if (this->actor.colChkInfo.damageEffect == 15) {
                func_80B2D924(this);
            } else {
                if (this->actor.colChkInfo.damageEffect == 4) {
                    this->drawDmgEffAlpha = 4.0f;
                    this->drawDmgEffScale = 0.45f;
                    Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG,
                                this->colliderCylinder.info.bumper.hitPos.x,
                                this->colliderCylinder.info.bumper.hitPos.y,
                                this->colliderCylinder.info.bumper.hitPos.z, 0, 0, 0, CLEAR_TAG_LARGE_LIGHT_RAYS);
                }
                func_80B2CFF8(this);
            }
        }
    }
}

void func_80B2E55C(EnPoh* this) {
    if ((this->actionFunc != func_80B2D980) && (this->actionFunc != func_80B2D7D4) &&
        (this->actionFunc != func_80B2D140)) {
        if (this->unk_190 != 0) {
            this->unk_190--;
        }

        if (this->unk_197 == 255) {
            if (this->actor.isTargeted) {
                this->unk_18C++;
                this->unk_18C = CLAMP_MAX(this->unk_18C, 20);
            } else {
                this->unk_18C = 0;
            }

            if (((this->unk_18C == 20) || (this->unk_190 == 0)) &&
                ((this->actionFunc == func_80B2CAA4) || (this->actionFunc == func_80B2CBBC) ||
                 (this->actionFunc == func_80B2CD64) || (this->actionFunc == func_80B2DB44) ||
                 (this->actionFunc == func_80B2D6EC))) {
                func_80B2D76C(this);
            }
        } else if ((this->unk_197 == 0) && (this->unk_190 == 0) &&
                   ((this->actionFunc == func_80B2CAA4) || (this->actionFunc == func_80B2CBBC) ||
                    (this->actionFunc == func_80B2CD64) || (this->actionFunc == func_80B2D6EC))) {
            func_80B2D924(this);
        }
    }
}

void func_80B2E6C0(EnPoh* this) {
    if (this->actionFunc == func_80B2CF28) {
        this->unk_194 = CLAMP_MAX((s16)(this->unk_194 + 5), 255);
        this->unk_195 = CLAMP_MIN((s16)(this->unk_195 - 5), 50);
        this->unk_196 = CLAMP_MIN((s16)(this->unk_196 - 5), 0);
    } else if (this->actionFunc == func_80B2DB44) {
        this->unk_194 = CLAMP_MAX((s16)(this->unk_194 + 5), 80);
        this->unk_195 = CLAMP_MAX((s16)(this->unk_195 + 5), 255);
        this->unk_196 = CLAMP_MAX((s16)(this->unk_196 + 5), 225);
    } else if (this->actionFunc == func_80B2D07C) {
        if ((this->actor.colorFilterTimer & 2) != 0) {
            this->unk_194 = 0;
            this->unk_195 = 0;
            this->unk_196 = 0;
        } else {
            this->unk_194 = 80;
            this->unk_195 = 255;
            this->unk_196 = 225;
        }
    } else {
        u8 temp;

        this->unk_194 = CLAMP_MAX((s16)(this->unk_194 + 5), 255);
        this->unk_195 = CLAMP_MAX((s16)(this->unk_195 + 5), 255);
        temp = this->unk_196;
        if (this->unk_196 > 210) {
            this->unk_196 = CLAMP_MIN((s16)(temp - 5), 210);
        } else {
            this->unk_196 = CLAMP_MAX((s16)(temp + 5), 210);
        }
    }
}

void func_80B2E8E0(EnPoh* this) {
    if ((this->actionFunc == func_80B2D140) && (this->skelAnime.curFrame < 12.0f)) {
        this->unk_198 = this->unk_199 = this->unk_19A = (this->skelAnime.curFrame * 16.66f) + 55.0f;
        this->unk_19B = this->skelAnime.curFrame * 16.666666f;
    } else {
        f32 rand = Rand_ZeroOne();

        this->unk_198 = (s32)(rand * 30.0f) + 225;
        this->unk_199 = (s32)(rand * 100.0f) + 155;
        this->unk_19A = (s32)(rand * 160.0f) + 95;
        this->unk_19B = 200;
    }
}

void EnPoh_Update(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnPoh* this = THIS;
    s32 pad;

    if (this->colliderSph.base.atFlags & AT_HIT) {
        this->colliderSph.base.atFlags &= ~AT_HIT;
        func_80B2D5DC(this);
    }

    func_80B2E438(this, globalCtx);
    func_80B2E55C(this);
    this->actionFunc(this, globalCtx);
    Actor_MoveWithGravity(&this->actor);
    if ((this->actionFunc == func_80B2CF28) && (this->unk_18E < 10)) {
        this->actor.flags |= ACTOR_FLAG_1000000;
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->colliderSph.base);
    }

    Collider_UpdateCylinder(&this->actor, &this->colliderCylinder);
    if (this->colliderCylinder.base.acFlags & AC_ON) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliderCylinder.base);
    }

    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderCylinder.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderSph.base);
    Actor_SetFocus(&this->actor, 42.0f);

    if ((this->actionFunc != func_80B2D07C) && (this->actionFunc != func_80B2D628)) {
        if (this->actionFunc == func_80B2DB44) {
            this->actor.shape.rot.y = BINANG_ROT180(this->actor.world.rot.y);
        } else {
            this->actor.shape.rot.y = this->actor.world.rot.y;
        }
    }

    func_80B2E8E0(this);
    this->actor.shape.shadowAlpha = this->unk_197;
    if (this->drawDmgEffAlpha > 0.0f) {
        Math_StepToF(&this->drawDmgEffAlpha, 0.0f, 0.05f);
        if (this->unk_197 != 255) {
            if (this->unk_197 * (1.0f / 255.0f) < this->unk_197) {
                this->drawDmgEffAlpha = this->unk_197 * (1.0f / 255.0f);
            }
        }

        this->drawDmgEffScale = (this->drawDmgEffAlpha + 1.0f) * (9.0f / 40.0f);
        this->drawDmgEffScale = CLAMP_MAX(this->drawDmgEffScale, 0.45f);
    }
}

s32 EnPoh_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx,
                           Gfx** gfx) {
    EnPoh* this = THIS;

    if ((this->unk_197 == 0) || (limbIndex == 18) || ((this->actionFunc == func_80B2D300) && (this->unk_18E >= 2))) {
        *dList = NULL;
    }

    if (limbIndex == 19) {
        gDPPipeSync((*gfx)++);
        gDPSetEnvColor((*gfx)++, this->unk_194, this->unk_195, this->unk_196, this->unk_197);
    }

    return false;
}

void EnPoh_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    static s8 D_80B2F71C[] = {
        -1, -1, -1, -1, 4, 5, -1, -1, -1, 0, 1, -1, -1, -1, -1, -1, 2, -1, -1, 3, -1,
    };
    static Vec3f D_80B2F734[] = {
        { -600.0f, 500.0f, 1700.0f },
        { -600.0f, 500.0f, -1700.0f },
        { 1000.0f, 1700.0f, 0.0f },
    };
    s32 temp_s3;
    Vec3f sp60;
    EnPoh* this = THIS;
    s32 pad;

    Collider_UpdateSpheres(limbIndex, &this->colliderSph);
    if ((this->actionFunc == func_80B2D300) && (this->unk_18E >= 2) && (limbIndex == 5)) {
        gSPMatrix((*gfx)++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList((*gfx)++, object_po_DL_002608);
    }

    if (limbIndex == 18) {
        if ((this->actionFunc == func_80B2D300) && (this->unk_18E >= 19) && (this->actor.scale.x != 0.0f)) {
            Matrix_Scale(0.01f / this->actor.scale.x, 0.01f / this->actor.scale.x, 0.01f / this->actor.scale.x,
                         MTXMODE_APPLY);
        }
        Matrix_CopyCurrentState(&this->unk_3D8);
        func_80B2C910(&sp60, globalCtx);
        Lights_PointGlowSetInfo(&this->lightInfo, this->colliderSph.elements[0].dim.worldSphere.center.x + (s32)sp60.x,
                                this->colliderSph.elements[0].dim.worldSphere.center.y + (s32)sp60.y,
                                this->colliderSph.elements[0].dim.worldSphere.center.z + (s32)sp60.z, this->unk_198,
                                this->unk_199, this->unk_19A, this->unk_19B * (200.0f / 255.0f));
    }

    temp_s3 = D_80B2F71C[limbIndex];
    if (temp_s3 != -1) {
        if (temp_s3 < 4) {
            Matrix_GetStateTranslation(&this->limbPos[temp_s3]);
        } else if (temp_s3 == 4) {
            Matrix_GetStateTranslationAndScaledX(2000.0f, &this->limbPos[temp_s3]);
        } else {
            s32 i;
            Vec3f* vec = &this->limbPos[temp_s3 + 2];
            Vec3f* vec2 = &D_80B2F734[0];

            Matrix_GetStateTranslationAndScaledX(-2000.0f, &this->limbPos[temp_s3]);
            Matrix_GetStateTranslationAndScaledY(-2000.0f, &this->limbPos[temp_s3 + 1]);

            for (i = temp_s3 + 2; i < ARRAY_COUNT(this->limbPos); i++, vec++, vec2++) {
                Matrix_MultiplyVector3fByState(vec2, vec);
            }
        }
    }
}

void EnPoh_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnPoh* this = THIS;
    Gfx* gfx;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_80B2E6C0(this);
    if ((this->unk_197 == 255) || (this->unk_197 == 0)) {
        gfx = POLY_OPA_DISP;

        gSPDisplayList(&gfx[0], &sSetupDL[6 * 25]);
        gDPSetEnvColor(&gfx[1], this->unk_194, this->unk_195, this->unk_196, this->unk_197);
        gSPSegment(&gfx[2], 0x08, D_801AEFA0);

        gfx = SkelAnime_Draw(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, EnPoh_OverrideLimbDraw,
                             EnPoh_PostLimbDraw, &this->actor, &gfx[3]);

        POLY_OPA_DISP = gfx;
    } else {
        gfx = POLY_XLU_DISP;

        gSPDisplayList(&gfx[0], &sSetupDL[6 * 25]);
        gDPSetEnvColor(&gfx[1], 255, 255, 255, this->unk_197);
        gSPSegment(&gfx[2], 0x08, D_801AEF88);

        POLY_XLU_DISP = SkelAnime_Draw(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                       EnPoh_OverrideLimbDraw, EnPoh_PostLimbDraw, &this->actor, &gfx[3]);

        gfx = POLY_OPA_DISP;
        gSPDisplayList(gfx++, &sSetupDL[6 * 25]);
    }

    gDPPipeSync(&gfx[0]);
    gDPSetEnvColor(&gfx[1], this->unk_198, this->unk_199, this->unk_19A, 255);

    Matrix_SetCurrentState(&this->unk_3D8);

    gSPMatrix(&gfx[2], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(&gfx[3], object_po_DL_002D28);

    POLY_OPA_DISP = &gfx[4];
    Actor_DrawDamageEffects(globalCtx, &this->actor, this->limbPos, ARRAY_COUNT(this->limbPos),
                            this->actor.scale.x * 100.0f * this->drawDmgEffScale, 0.0f, this->drawDmgEffAlpha,
                            ACTOR_DRAW_DMGEFF_LIGHT_ORBS);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80B2F328(Actor* thisx, GlobalContext* globalCtx) {
    EnPoh* this = THIS;

    this->actionFunc(this, globalCtx);
    if (this->actionFunc != func_80B2DD2C) {
        this->unk_190++;
    }

    func_80B2E8E0(this);
}

void func_80B2F37C(Actor* thisx, GlobalContext* globalCtx) {
    EnPoh* this = THIS;
    s32 pad;
    Vec3f sp7C;
    Gfx* gfx;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    if (this->actionFunc == func_80B2DD2C) {
        gfx = POLY_OPA_DISP;

        gSPDisplayList(&gfx[0], &sSetupDL[6 * 25]);
        gDPSetEnvColor(&gfx[1], this->unk_198, this->unk_199, this->unk_19A, 255);

        func_80B2C910(&sp7C, globalCtx);
        Lights_PointGlowSetInfo(&this->lightInfo, this->actor.world.pos.x + sp7C.x, this->actor.world.pos.y + sp7C.y,
                                this->actor.world.pos.z + sp7C.z, this->unk_198, this->unk_199, this->unk_19A, 200);

        gSPMatrix(&gfx[2], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(&gfx[3], object_po_DL_002D28);

        POLY_OPA_DISP = &gfx[4];
    } else {
        func_8012C2DC(globalCtx->state.gfxCtx);

        gSPSegment(POLY_XLU_DISP++, 0x08,
                   Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 0x20, 0x40, 1, 0, (this->unk_190 * -8) & 0x1FF,
                                    0x20, 0x80));
        gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 255, 170, 255, this->unk_197);
        gDPSetEnvColor(POLY_XLU_DISP++, this->unk_194, this->unk_195, this->unk_196, 255);

        Matrix_InsertYRotation_f((Camera_GetCamDirYaw(GET_ACTIVE_CAM(globalCtx)) + 0x8000) * (M_PI / 32768),
                                 MTXMODE_APPLY);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, object_po_DL_003850);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
