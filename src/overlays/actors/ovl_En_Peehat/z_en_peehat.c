/*
 * File: z_en_peehat.c
 * Overlay: ovl_En_Peehat
 * Description: Peahat
 */

#include "z_en_peehat.h"
#include "overlays/actors/ovl_En_Bom/z_en_bom.h"
#include "objects/object_ph/object_ph.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10)

#define THIS ((EnPeehat*)thisx)

void EnPeehat_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPeehat_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPeehat_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPeehat_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80897498(EnPeehat* this);
void func_80897520(EnPeehat* this, GlobalContext* globalCtx);
void func_80897648(EnPeehat* this);
void func_808976DC(EnPeehat* this, GlobalContext* globalCtx);
void func_80897910(EnPeehat* this, GlobalContext* globalCtx);
void func_80897A34(EnPeehat* this);
void func_80897A94(EnPeehat* this, GlobalContext* globalCtx);
void func_80897D48(EnPeehat* this, GlobalContext* globalCtx);
void func_80897EAC(EnPeehat* this);
void func_80897F44(EnPeehat* this, GlobalContext* globalCtx);
void func_80898124(EnPeehat* this);
void func_80898144(EnPeehat* this, GlobalContext* globalCtx);
void func_808982E0(EnPeehat* this);
void func_80898338(EnPeehat* this, GlobalContext* globalCtx);
void func_80898454(EnPeehat* this, GlobalContext* globalCtx);
void func_808984E0(EnPeehat* this);
void func_80898594(EnPeehat* this, GlobalContext* globalCtx);
void func_80898654(EnPeehat* this);
void func_808986A4(EnPeehat* this, GlobalContext* globalCtx);

const ActorInit En_Peehat_InitVars = {
    ACTOR_EN_PEEHAT,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_PH,
    sizeof(EnPeehat),
    (ActorFunc)EnPeehat_Init,
    (ActorFunc)EnPeehat_Destroy,
    (ActorFunc)EnPeehat_Update,
    (ActorFunc)EnPeehat_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_WOOD,
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
    { 50, 120, -20, { 0, 0, 0 } },
};

static ColliderSphereInit sSphereInit = {
    {
        COLTYPE_HIT6,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_SPHERE,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 0, { { 0, 0, 0 }, 40 }, 100 },
};

static ColliderTrisElementInit sTrisElementsInit[2] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x10 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x10 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
    },
};

static ColliderTrisInit sTrisInit = {
    {
        COLTYPE_METAL,
        AT_NONE | AT_TYPE_ENEMY,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_TYPE_1,
        COLSHAPE_TRIS,
    },
    2,
    sTrisElementsInit,
};

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x1),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x5),
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

static CollisionCheckInfoInit2 sColChkInfoInit1 = { 15, 50, 120, -20, MASS_HEAVY };

static CollisionCheckInfoInit2 sColChkInfoInit2 = { 1, 20, 15, -5, 30 };

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 4200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 800, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1800, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 700, ICHAIN_STOP),
};

void EnPeehat_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnPeehat* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    SkelAnime_Init(globalCtx, &this->skelAnime, &object_ph_Skel_001C80, &object_ph_Anim_0009C4, this->jointTable,
                   this->morphTable, 24);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 27.0f);
    this->unk_2B0 = 0;
    Math_Vec3f_Copy(&this->actor.focus.pos, &this->actor.world.pos);
    this->actor.floorHeight = this->actor.world.pos.y;
    Collider_InitAndSetCylinder(globalCtx, &this->colliderCylinder, &this->actor, &sCylinderInit);
    Collider_InitAndSetSphere(globalCtx, &this->colliderSphere, &this->actor, &sSphereInit);
    Collider_InitAndSetTris(globalCtx, &this->colliderTris, &this->actor, &sTrisInit, this->colliderTriElements);

    if (this->actor.params == 0) {
        CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit1);
        if (gSaveContext.save.isNight) {
            this->actor.shape.yOffset = -1000.0f;
        }
        Actor_SetScale(&this->actor, 0.036f);
        this->actor.hintId = 0x48;
        func_80897498(this);
    } else {
        CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit2);
        this->actor.scale.z = this->actor.scale.x = 0.006f;
        this->actor.scale.y = 0.003f;
        this->actor.velocity.y = 6.0f;

        this->colliderCylinder.dim.radius = 20;
        this->colliderCylinder.dim.height = 15;
        this->colliderCylinder.dim.yShift = -5;
        this->actor.hintId = 0x49;
        this->colliderCylinder.base.ocFlags1 &= ~OC1_ON;

        func_80897A34(this);
    }
}

void EnPeehat_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnPeehat* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->colliderCylinder);
    Collider_DestroySphere(globalCtx, &this->colliderSphere);
    Collider_DestroyTris(globalCtx, &this->colliderTris);
    if (this->actor.params != 0) {
        EnPeehat* parent = (EnPeehat*)this->actor.parent;

        if ((parent != NULL) && (parent->actor.update != NULL)) {
            parent->unk_2AC--;
        }
    }
}

void func_80897170(EnPeehat* this) {
    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX;
    this->drawDmgEffScale = 1.1f;
    this->drawDmgEffFrozenSteamScale = 1.6500001f;
    this->drawDmgEffAlpha = 1.0f;
    this->colliderSphere.base.colType = COLTYPE_HIT3;
    this->unk_2B0 = 80;
    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 80);
}

void func_808971DC(EnPeehat* this, GlobalContext* globalCtx) {
    if (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
        this->colliderSphere.base.colType = COLTYPE_HIT6;
        this->drawDmgEffAlpha = 0.0f;
        Actor_SpawnIceEffects(globalCtx, &this->actor, this->limbPos, ARRAY_COUNT(this->limbPos), 2, 0.5f, 0.35f);
    }
}

void func_80897258(GlobalContext* globalCtx, EnPeehat* this, Vec3f* arg2, f32 arg3, f32 arg4) {
    static Vec3f D_80899558 = { 0.0f, 8.0f, 0.0f };
    static Vec3f D_80899564 = { 0.0f, -1.5f, 0.0f };
    Vec3f sp44;
    s16 sp42 = Rand_Next() >> 0x10;
    s32 temp_v1;

    sp44.y = this->actor.floorHeight;
    sp44.x = (Math_SinS(sp42) * arg3) + arg2->x;
    sp44.z = (Math_CosS(sp42) * arg3) + arg2->z;

    D_80899564.x = randPlusMinusPoint5Scaled(1.05f);
    D_80899564.z = randPlusMinusPoint5Scaled(1.05f);
    D_80899558.y = randPlusMinusPoint5Scaled(4.0f) + 8.0f;

    EffectSsHahen_Spawn(globalCtx, &sp44, &D_80899558, &D_80899564, 0, (Rand_ZeroFloat(5.0f) + 12.0f) * arg4, -1, 10,
                        NULL);
}

void func_80897390(EnPeehat* this, GlobalContext* globalCtx) {
    s32 i;
    s16 phi_s2 = BINANG_ROT180(this->actor.yawTowardsPlayer);
    Actor* actor;

    this->colliderCylinder.base.acFlags &= ~AC_HIT;

    for (i = 3 - this->unk_2AC; i > 0; i--) {
        actor =
            Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_PEEHAT, this->actor.world.pos.x,
                               this->actor.world.pos.y + 50.0f, this->actor.world.pos.z, 0, phi_s2, 0, 1);
        phi_s2 += 0x5555;

        if (actor != NULL) {
            this->unk_2AC++;
        }
    }

    this->unk_2B0 = 8;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PIHAT_DAMAGE);
}

void func_80897498(EnPeehat* this) {
    Animation_Change(&this->skelAnime, &object_ph_Anim_0009C4, 0.0f, 3.0f,
                     Animation_GetLastFrame(&object_ph_Anim_0009C4), 2, 0.0f);
    this->unk_2B0 = 0;
    this->unk_2AD = 1;
    this->colliderCylinder.base.acFlags &= ~AC_HIT;
    this->actionFunc = func_80897520;
}

void func_80897520(EnPeehat* this, GlobalContext* globalCtx) {
    if (!gSaveContext.save.isNight) {
        this->actor.flags |= ACTOR_FLAG_1;
        this->colliderSphere.base.acFlags |= AC_ON;
        if (this->actor.xzDistToPlayer < 740.0f) {
            func_80897648(this);
        } else {
            Math_StepToF(&this->actor.shape.yOffset, -1000.0f, 10.0f);
        }
    } else {
        this->actor.flags &= ~ACTOR_FLAG_1;
        this->colliderSphere.base.acFlags &= ~AC_ON;
        Math_StepToF(&this->actor.shape.yOffset, -1000.0f, 50.0f);
        if (this->unk_2B0 != 0) {
            this->unk_2B0--;
            if (this->unk_2B0 & 4) {
                Math_StepToF(&this->unk_2C4, 0.205f, 0.235f);
            } else {
                Math_StepToF(&this->unk_2C4, 0.0f, 0.005f);
            }
        } else if (this->colliderCylinder.base.acFlags & AC_HIT) {
            func_80897390(this, globalCtx);
        }
    }
}

void func_80897648(EnPeehat* this) {
    if (this->actionFunc != func_80898454) {
        Animation_Change(&this->skelAnime, &object_ph_Anim_0009C4, 0.0f, 3.0f,
                         Animation_GetLastFrame(&object_ph_Anim_0009C4), 2, 0.0f);
    }
    this->unk_2B0 = 16;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PIHAT_UP);
    this->actionFunc = func_808976DC;
}

void func_808976DC(EnPeehat* this, GlobalContext* globalCtx) {
    Vec3f sp34;

    Math_StepToF(&this->actor.shape.yOffset, 0.0f, 50.0f);

    if (Math_ScaledStepToS(&this->unk_2B2, 4000, 800)) {
        if (this->unk_2B0 != 0) {
            this->unk_2B0--;
            if ((this->unk_2B0 == 0) && (this->skelAnime.playSpeed < 0.5f)) {
                this->unk_2B0 = -1;
                this->skelAnime.playSpeed = 1.0f;
            }
        }

        if (SkelAnime_Update(&this->skelAnime) || (this->unk_2B0 == 0)) {
            func_80897EAC(this);
        } else {
            this->actor.world.pos.y += 6.5f;
        }

        if ((this->actor.world.pos.y - this->actor.floorHeight) < 80.0f) {
            Math_Vec3f_Copy(&sp34, &this->actor.world.pos);
            sp34.y = this->actor.floorHeight;
            func_800BBFB0(globalCtx, &sp34, 90.0f, 1, 150, 100, 1);
        }
    }

    func_80897258(globalCtx, this, &this->actor.world.pos, 75.0f, 2.0f);
    Math_StepToF(&this->unk_2C4, 0.075f, 0.005f);
    this->unk_2B4 += this->unk_2B2;
}

void func_80897864(EnPeehat* this) {
    Animation_PlayLoop(&this->skelAnime, &object_ph_Anim_0005C4);
    this->unk_2B8 = 0.0f;
    if (this->actionFunc == func_80898338) {
        this->unk_2AD = -this->unk_2AD;
    } else {
        this->unk_2AD = (Rand_ZeroOne() < 0.5f) ? 1 : -1;
    }
    this->colliderTris.base.atFlags |= AT_ON;
    this->actionFunc = func_80897910;
}

void func_80897910(EnPeehat* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    Math_StepToF(&this->actor.speedXZ, 3.0f, 0.25f);
    Math_StepToF(&this->actor.world.pos.y, this->actor.floorHeight + 80.0f, 3.0f);
    SkelAnime_Update(&this->skelAnime);
    if (!gSaveContext.save.isNight && (Math_Vec3f_DistXZ(&this->actor.home.pos, &player->actor.world.pos) < 1200.0f)) {
        Math_ScaledStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 1000);
        this->actor.shape.rot.y += (s16)(this->unk_2AD * 450);
    } else {
        func_80898124(this);
    }
    Math_ScaledStepToS(&this->unk_2B2, 4000, 500);
    this->unk_2B4 += this->unk_2B2;
    Math_StepToF(&this->unk_2C4, 0.075f, 0.005f);
    func_800B9010(&this->actor, NA_SE_EN_PIHAT_FLY - SFX_FLAG);
}

void func_80897A34(EnPeehat* this) {
    Animation_PlayLoop(&this->skelAnime, &object_ph_Anim_0005C4);
    this->unk_2B0 = 30;
    this->actor.speedXZ = 5.3f;
    this->colliderTris.base.atFlags |= AT_ON;
    this->actionFunc = func_80897A94;
}

void func_80897A94(EnPeehat* this, GlobalContext* globalCtx) {
    s32 pad;

    if ((this->actor.parent != NULL) && (this->actor.parent->update == NULL)) {
        this->actor.parent = NULL;
    }

    if ((this->actor.world.pos.y - this->actor.floorHeight) >= 70.0f) {
        Math_StepToF(&this->actor.velocity.y, -1.3f, 0.5f);
    } else {
        Math_StepToF(&this->actor.velocity.y, -0.135f, 0.05f);
    }

    if (this->unk_2B0 > 0) {
        this->unk_2B0--;
    } else {
        Math_ScaledStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 0x33E);
        this->colliderCylinder.base.ocFlags1 |= OC1_ON;
    }

    this->actor.shape.rot.y += 0x15E;
    SkelAnime_Update(&this->skelAnime);
    Math_ScaledStepToS(&this->unk_2B2, 4000, 500);
    this->unk_2B4 += this->unk_2B2;
    Math_StepToF(&this->unk_2C4, 0.075f, 0.005f);
    func_800B9010(&this->actor, NA_SE_EN_PIHAT_SM_FLY - SFX_FLAG);

    if (this->colliderTris.base.atFlags & AT_BOUNCED) {
        this->colliderTris.base.atFlags &= ~(AT_BOUNCED | AT_ON);
        this->actor.colChkInfo.health = 0;
        func_808982E0(this);
    } else if ((this->colliderCylinder.base.acFlags & AC_HIT) || (this->actor.bgCheckFlags & 1)) {
        func_800B3030(globalCtx, &this->actor.world.pos, &gZeroVec3f, &gZeroVec3f, 40, 7, 0);
        SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 11, NA_SE_EN_EXTINCT);
        if (!(this->actor.bgCheckFlags & 1)) {
            SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 40, NA_SE_EN_PIHAT_SM_DEAD);
        }
        Actor_MarkForDeath(&this->actor);
    } else if (this->colliderTris.base.atFlags & AT_HIT) {
        this->colliderTris.base.atFlags &= ~AT_HIT;
        if (BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.world.rot.y) > 0) {
            this->actor.world.rot.y -= 0x2000;
        } else {
            this->actor.world.rot.y += 0x2000;
        }
        this->unk_2B0 = 40;
    } else if (this->colliderCylinder.base.ocFlags1 & OC1_HIT) {
        this->colliderCylinder.base.ocFlags1 &= ~OC1_HIT;
        if ((BINANG_SUB(Actor_YawBetweenActors(&this->actor, this->colliderCylinder.base.oc),
                        this->actor.world.rot.y)) > 0) {
            this->actor.world.rot.y -= 0x2000;
        } else {
            this->actor.world.rot.y += 0x2000;
        }
        this->unk_2B0 = 10;
    }
}

void func_80897D00(EnPeehat* this) {
    Animation_PlayOnce(&this->skelAnime, &object_ph_Anim_000350);
    this->colliderTris.base.atFlags &= ~AT_ON;
    this->actionFunc = func_80897D48;
}

void func_80897D48(EnPeehat* this, GlobalContext* globalCtx) {
    Vec3f sp34;

    Math_StepToF(&this->actor.shape.yOffset, -1000.0f, 50.0f);
    Math_StepToF(&this->actor.speedXZ, 0.0f, 1.0f);
    Math_ScaledStepToS(&this->actor.shape.rot.x, 0, 50);
    if (SkelAnime_Update(&this->skelAnime)) {
        func_80897498(this);
        this->actor.world.pos.y = this->actor.floorHeight;
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PIHAT_LAND);
    } else if (this->actor.floorHeight < this->actor.world.pos.y) {
        Math_SmoothStepToF(&this->actor.world.pos.y, this->actor.floorHeight, 0.3f, 3.5f, 0.25f);
        if ((this->actor.world.pos.y - this->actor.floorHeight) < 60.0f) {
            Math_Vec3f_Copy(&sp34, &this->actor.world.pos);
            sp34.y = this->actor.floorHeight;
            func_800BBFB0(globalCtx, &sp34, 80.0f, 1, 150, 100, 1);
            func_80897258(globalCtx, this, &sp34, 75.0f, 2.0f);
        }
    }
    Math_ScaledStepToS(&this->unk_2B2, 0, 100);
    this->unk_2B4 += this->unk_2B2;
}

void func_80897EAC(EnPeehat* this) {
    Animation_PlayLoop(&this->skelAnime, &object_ph_Anim_0005C4);
    this->actor.speedXZ = Rand_ZeroFloat(0.5f) + 2.5f;
    this->unk_2B0 = Rand_ZeroFloat(10.0f) + 10.0f;
    this->colliderTris.base.atFlags |= AT_ON;
    this->colliderSphere.base.acFlags |= AC_ON;
    this->actionFunc = func_80897F44;
}

void func_80897F44(EnPeehat* this, GlobalContext* globalCtx) {
    s32 pad;
    f32 cos;
    Player* player = GET_PLAYER(globalCtx);

    if ((this->actor.world.pos.y - this->actor.floorHeight) > 75.0f) {
        this->actor.world.pos.y -= 1.0f;
    }

    cos = cos_rad(this->unk_2B8);
    this->actor.world.pos.y += cos * 1.4f;
    this->unk_2B8 += fabsf(cos * 0.18f) + 0.07f;
    this->unk_2B0--;

    if (this->unk_2B0 <= 0) {
        this->actor.speedXZ = Rand_ZeroFloat(0.5f) + 2.5f;
        this->unk_2B0 = Rand_ZeroFloat(10.0f) + 10.0f;
        this->unk_2B6 = randPlusMinusPoint5Scaled(1000.0f);
    }

    SkelAnime_Update(&this->skelAnime);
    this->actor.world.rot.y += this->unk_2B6;
    this->actor.shape.rot.y += 0x15E;

    if (!gSaveContext.save.isNight && (Math_Vec3f_DistXZ(&this->actor.home.pos, &player->actor.world.pos) < 1200.0f)) {
        this->actor.world.rot.y = this->actor.yawTowardsPlayer;
        func_80897864(this);
    } else {
        func_80898124(this);
    }

    Math_ScaledStepToS(&this->unk_2B2, 4000, 500);
    this->unk_2B4 += this->unk_2B2;
    Math_StepToF(&this->unk_2C4, 0.075f, 0.005f);
    func_800B9010(&this->actor, NA_SE_EN_PIHAT_FLY - SFX_FLAG);
}

void func_80898124(EnPeehat* this) {
    this->actionFunc = func_80898144;
    this->actor.speedXZ = 2.5f;
}

void func_80898144(EnPeehat* this, GlobalContext* globalCtx) {
    s32 step;
    f32 cos;
    Player* player = GET_PLAYER(globalCtx);

    if ((this->actor.world.pos.y - this->actor.floorHeight) > 75.0f) {
        this->actor.world.pos.y -= 1.0f;
    } else {
        this->actor.world.pos.y += 1.0f;
    }
    cos = cos_rad(this->unk_2B8);
    this->actor.world.pos.y += cos * 1.4f;

    cos = cos_rad(this->unk_2B8);
    this->unk_2B8 += fabsf(cos * 0.18f) + 0.07f;

    step = Math_Vec3f_Yaw(&this->actor.world.pos, &this->actor.home.pos);
    Math_ScaledStepToS(&this->actor.world.rot.y, step, 0x258);
    Math_ScaledStepToS(&this->actor.shape.rot.x, 0x1194, 0x258);

    this->actor.shape.rot.y += 0x15E;
    this->unk_2B4 += this->unk_2B2;

    if (Math_Vec3f_DistXZ(&this->actor.world.pos, &this->actor.home.pos) < 2.0f) {
        func_80897D00(this);
    }

    if (!gSaveContext.save.isNight && (Math_Vec3f_DistXZ(&this->actor.home.pos, &player->actor.world.pos) < 1200.0f)) {
        func_80897864(this);
    }
    func_800B9010(&this->actor, NA_SE_EN_PIHAT_FLY - SFX_FLAG);
}

void func_808982E0(EnPeehat* this) {
    Animation_MorphToPlayOnce(&this->skelAnime, &object_ph_Anim_000844, -4.0f);
    this->actor.speedXZ = -9.0f;
    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    this->actionFunc = func_80898338;
}

void func_80898338(EnPeehat* this, GlobalContext* globalCtx) {
    this->unk_2B4 += this->unk_2B2;
    SkelAnime_Update(&this->skelAnime);

    if (Math_StepToF(&this->actor.speedXZ, 0.0f, 0.5f)) {
        if (this->actor.params != 0) {
            func_800B3030(globalCtx, &this->actor.world.pos, &gZeroVec3f, &gZeroVec3f, 40, 7, 0);
            SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 30, NA_SE_EN_EXTINCT);
            SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 40, NA_SE_EN_PIHAT_SM_DEAD);
            Actor_MarkForDeath(&this->actor);
        } else {
            func_80897864(this);
        }
    }
    func_800B9010(&this->actor, NA_SE_EN_PIHAT_FLY - SFX_FLAG);
}

void func_80898414(EnPeehat* this) {
    func_800BE568(&this->actor, &this->colliderSphere);
    this->unk_2B2 = 0;
    this->actor.speedXZ = 0.0f;
    this->actionFunc = func_80898454;
}

void func_80898454(EnPeehat* this, GlobalContext* globalCtx) {
    if (this->unk_2B0 != 0) {
        this->unk_2B0--;
    }

    Math_StepToF(&this->actor.world.pos.y, this->actor.floorHeight, 8.0f);

    if (this->unk_2B0 == 0) {
        func_808971DC(this, globalCtx);
        if (this->actor.colChkInfo.health == 0) {
            func_808984E0(this);
        } else {
            func_80897648(this);
        }
    }
}

void func_808984E0(EnPeehat* this) {
    Animation_MorphToPlayOnce(&this->skelAnime, &object_ph_Anim_000844, -4.0f);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PIHAT_DAMAGE);
    this->unk_2B2 = 4000;
    this->unk_2B0 = 14;
    this->actor.speedXZ = 10.0f;
    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 14);
    this->colliderSphere.base.acFlags &= ~AC_ON;
    this->unk_2C4 = 0.0f;
    if (this->actor.colChkInfo.health == 0) {
        this->actor.velocity.y = 6.0f;
    }
    this->actionFunc = func_80898594;
}

void func_80898594(EnPeehat* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    this->unk_2B4 += this->unk_2B2;
    Math_ScaledStepToS(&this->unk_2B2, 4000, 250);
    Math_StepToF(&this->actor.world.pos.y, this->actor.floorHeight + 88.5f, 3.0f);
    Math_StepToF(&this->actor.speedXZ, 0.0f, 0.5f);
    this->unk_2B0--;
    if (this->unk_2B0 <= 0) {
        if (this->actor.colChkInfo.health == 0) {
            func_80898654(this);
        } else {
            func_80897EAC(this);
        }
    }
}

void func_80898654(EnPeehat* this) {
    Animation_PlayLoop(&this->skelAnime, &object_ph_Anim_0005C4);
    this->unk_2B0 = 5;
    this->unk_2B8 = 0.0f;
    this->actionFunc = func_808986A4;
}

void func_808986A4(EnPeehat* this, GlobalContext* globalCtx) {
    if (this->unk_2B0 == 5) {
        EnBom* bomb = (EnBom*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_BOM, this->actor.world.pos.x,
                                          this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0x602, 0);

        if (bomb != NULL) {
            bomb->timer = 0;
        }
    }

    this->unk_2B0--;

    if (this->unk_2B0 == 0) {
        Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.world.pos, 0xE0);
        Actor_MarkForDeath(&this->actor);
    }
}

void func_8089874C(EnPeehat* this, GlobalContext* globalCtx) {
    if (this->colliderTris.base.acFlags & AC_BOUNCED) {
        this->colliderTris.base.acFlags &= ~AC_BOUNCED;
        this->colliderSphere.base.acFlags &= ~AC_HIT;
        return;
    }

    if (this->colliderSphere.base.acFlags & AC_HIT) {
        this->colliderSphere.base.acFlags &= ~AC_HIT;
        if ((this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) ||
            !(this->colliderSphere.info.acHitInfo->toucher.dmgFlags & 0xDB0B3)) {
            if (!Actor_ApplyDamage(&this->actor)) {
                Enemy_StartFinishingBlow(globalCtx, &this->actor);
            }

            this->colliderTris.base.atFlags &= ~(AT_HIT | AT_ON);
            Actor_SetDropFlag(&this->actor, &this->colliderSphere.info);
            func_808971DC(this, globalCtx);

            if (this->actor.colChkInfo.damageEffect == 5) {
                this->unk_2B0 = 40;
                Actor_SetColorFilter(&this->actor, 0, 255, 0, 40);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
                this->drawDmgEffScale = 1.1f;
                this->drawDmgEffAlpha = 2.0f;
                this->drawDmgEffType = ACTOR_DRAW_DMGEFF_ELECTRIC_SPARKS_LARGE;
                func_80898414(this);
            } else if (this->actor.colChkInfo.damageEffect == 1) {
                this->unk_2B0 = 40;
                Actor_SetColorFilter(&this->actor, 0, 200, 0, 40);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
                func_80898414(this);
            } else if (this->actor.colChkInfo.damageEffect == 3) {
                func_80897170(this);
                if (this->actor.colChkInfo.health == 0) {
                    this->unk_2B0 = 3;
                    this->colliderSphere.base.acFlags &= ~AC_ON;
                }
                func_80898414(this);
            } else {
                if (this->actor.colChkInfo.damageEffect == 2) {
                    this->drawDmgEffAlpha = 4.0f;
                    this->drawDmgEffScale = 2.1f;
                    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
                } else if (this->actor.colChkInfo.damageEffect == 4) {
                    this->drawDmgEffAlpha = 4.0f;
                    this->drawDmgEffScale = 1.1f;
                    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_LIGHT_ORBS;
                    Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG,
                                this->colliderSphere.info.bumper.hitPos.x, this->colliderSphere.info.bumper.hitPos.y,
                                this->colliderSphere.info.bumper.hitPos.z, 0, 0, 0, CLEAR_TAG_LARGE_LIGHT_RAYS);
                }
                func_800BE568(&this->actor, &this->colliderSphere);
                func_808984E0(this);
            }
        }
    } else if ((this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) &&
               (this->colliderCylinder.base.acFlags & AC_HIT) &&
               ((this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) ||
                !(this->colliderCylinder.info.acHitInfo->toucher.dmgFlags & 0xDB0B3))) {
        func_808971DC(this, globalCtx);
        this->actor.colorFilterTimer = 0;
        func_80897648(this);
    }
}

void EnPeehat_Update(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnPeehat* this = THIS;

    if (thisx->params == 0) {
        func_8089874C(this, globalCtx);
    }
    Actor_MoveWithGravity(thisx);
    Actor_UpdateBgCheckInfo(globalCtx, thisx, 25.0f, 30.0f, 30.0f, 5);

    this->actionFunc(this, globalCtx);

    if ((globalCtx->gameplayFrames % 128) == 0) {
        this->unk_2C0 = Rand_ZeroFloat(0.25f) + 0.5f;
    }

    this->unk_2BC += this->unk_2C0;
    if (thisx->params == 0) {
        if (this->actionFunc == func_80897910) {
            Math_ScaledStepToS(&thisx->shape.rot.x, 6000, 300);
        } else {
            Math_ScaledStepToS(&thisx->shape.rot.x, 0, 300);
        }
    } else {
        Actor_SetFocus(thisx, 0.0f);
    }

    Collider_UpdateCylinder(thisx, &this->colliderCylinder);
    this->colliderCylinder.dim.pos.y += (s16)(thisx->shape.yOffset * thisx->scale.y);
    if (this->colliderCylinder.base.ocFlags1 & OC1_ON) {
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderCylinder.base);
    }

    if (thisx->params == 0) {
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderSphere.base);
        if (this->colliderSphere.base.acFlags & AC_ON) {
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliderSphere.base);
        }
    }

    if (this->colliderTris.base.atFlags & AT_HIT) {
        this->colliderTris.base.atFlags &= ~AT_HIT;
        func_808982E0(this);
    }

    if (this->colliderTris.base.atFlags & AT_ON) {
        thisx->flags |= 0x1000000;
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->colliderTris.base);
        if (thisx->params == 0) {
            Vec3f sp74;
            CollisionPoly* sp70;
            s32 sp6C;
            s32 i;

            sp70 = NULL;
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliderTris.base);

            for (i = 1; i >= 0; i--) {
                if (BgCheck_EntityLineTest1(&globalCtx->colCtx, &thisx->world.pos, &this->unk_2D4[i], &sp74, &sp70,
                                            true, true, false, true, &sp6C)) {
                    func_800BBFB0(globalCtx, &sp74, 0.0f, 1, 300, 150, 1);
                    func_80897258(globalCtx, this, &sp74, 0.0f, 1.5f);
                }
            }
        }
    }

    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliderCylinder.base);

    if (this->actionFunc != func_80898454) {
        Math_StepToF(&this->unk_2C4, 0.0f, 0.001f);
    }

    if (this->drawDmgEffAlpha > 0.0f) {
        if (this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
            Math_StepToF(&this->drawDmgEffAlpha, 0.0f, 0.05f);
            if (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FIRE) {
                this->drawDmgEffScale = (this->drawDmgEffAlpha + 1.0f) * 1.05f;
                this->drawDmgEffScale = CLAMP_MAX(this->drawDmgEffScale, 2.1f);
            } else {
                this->drawDmgEffScale = (this->drawDmgEffAlpha + 1.0f) * 0.55f;
                this->drawDmgEffScale = CLAMP_MAX(this->drawDmgEffScale, 1.1f);
            }
        } else if (!Math_StepToF(&this->drawDmgEffFrozenSteamScale, 1.1f, 0.0275f)) {
            func_800B9010(thisx, NA_SE_EV_ICE_FREEZE - SFX_FLAG);
        }
    }
}

s32 EnPeehat_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                              Actor* thisx) {
    EnPeehat* this = THIS;
    s32 pad;

    if (limbIndex == 4) {
        rot->x = -this->unk_2B4;
    } else if ((limbIndex == 3) ||
               ((limbIndex == 23) && ((this->actionFunc == func_80898594) || (this->actionFunc == func_80897520)))) {
        OPEN_DISPS(globalCtx->state.gfxCtx);
        Gfx* gfx = POLY_OPA_DISP;

        Matrix_StatePush();
        Matrix_RotateStateAroundXAxis(this->unk_2BC * 0.115f);
        Matrix_InsertYRotation_f(this->unk_2BC * 0.13f, MTXMODE_APPLY);
        Matrix_InsertZRotation_f(this->unk_2BC * 0.1f, MTXMODE_APPLY);
        Matrix_Scale(1.0f - this->unk_2C4, this->unk_2C4 + 1.0f, 1.0f - this->unk_2C4, MTXMODE_APPLY);
        Matrix_InsertZRotation_f(-(this->unk_2BC * 0.1f), MTXMODE_APPLY);
        Matrix_InsertYRotation_f(-(this->unk_2BC * 0.13f), MTXMODE_APPLY);
        Matrix_RotateStateAroundXAxis(-(this->unk_2BC * 0.115f));

        gSPMatrix(&gfx[0], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(&gfx[1], *dList);

        Matrix_StatePop();

        POLY_OPA_DISP = &gfx[2];

        CLOSE_DISPS(globalCtx->state.gfxCtx);
        return true;
    }
    return false;
}

void EnPeehat_PostLimbDraw(GlobalContext* globalCtx2, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Vec3f D_80899570[] = {
        { 1300.0f, 1200.0f, 0.0f },
        { 1300.0f, -1200.0f, 0.0f },
        { 1300.0f, 0.0f, 1200.0f },
        { 1300.0f, 0.0f, -1200.0f },
    };
    static s8 D_808995A0[] = {
        -1, -1, -1, -1, -1, -1, -1, 0, -1, -1, 2, -1, -1, 4, -1, -1, 6, -1, -1, 8, -1, -1, 10, -1,
    };
    GlobalContext* globalCtx = globalCtx2;
    EnPeehat* this = THIS;
    s32 i;
    s32 index = D_808995A0[limbIndex];
    Gfx* gfx;

    if (index != -1) {
        Matrix_GetStateTranslationAndScaledX(2000.0f, &this->limbPos[index]);
        Matrix_GetStateTranslationAndScaledX(4000.0f, &this->limbPos[index + 1]);
    }

    if (limbIndex == 4) {
        Matrix_GetStateTranslationAndScaledZ(5500.0f, &this->unk_2D4[0]);
        Matrix_GetStateTranslationAndScaledZ(-5500.0f, &this->unk_2D4[1]);
    } else if ((limbIndex == 3) && (thisx->params == 0)) {
        Vec3f* vec = &D_80899570[0];
        Vec3f* vec2 = &this->limbPos[12];

        for (i = 0; i < ARRAY_COUNT(D_80899570); i++, vec++, vec2++) {
            Matrix_MultiplyVector3fByState(vec, vec2);
        }

        Matrix_GetStateTranslationAndScaledX(3000.0f, vec2++);
        Matrix_GetStateTranslationAndScaledX(-400.0f, vec2);

        OPEN_DISPS(globalCtx->state.gfxCtx);
        gfx = POLY_OPA_DISP;

        Matrix_InsertTranslation(-1000.0f, 0.0f, 0.0f, MTXMODE_APPLY);
        Collider_UpdateSphere(0, &this->colliderSphere);
        Matrix_InsertTranslation(500.0f, 0.0f, 0.0f, MTXMODE_APPLY);
        Matrix_InsertYRotation_f(3.2f, MTXMODE_APPLY);
        Matrix_Scale(0.3f, 0.2f, 0.2f, MTXMODE_APPLY);

        gSPMatrix(&gfx[0], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(&gfx[1], *dList);

        POLY_OPA_DISP = &gfx[2];
        Math_Vec3s_ToVec3f(&this->actor.focus.pos, &this->colliderSphere.dim.worldSphere.center);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

void EnPeehat_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnPeehat* this = THIS;
    Vec3f sp58;
    Vec3f sp4C;
    Vec3f sp40;
    s32 i;

    func_8012C28C(globalCtx->state.gfxCtx);

    SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, EnPeehat_OverrideLimbDraw,
                      (this->actor.params == 0) ? EnPeehat_PostLimbDraw : NULL, &this->actor);

    if ((this->actor.speedXZ != 0.0f) || (this->actor.velocity.y != 0.0f)) {
        Matrix_GetStateTranslationAndScaledZ(4500.0f, &sp40);
        Matrix_GetStateTranslationAndScaledZ(-4500.0f, &sp4C);
        Matrix_GetStateTranslationAndScaledX(4500.0f, &sp58);
        Collider_SetTrisVertices(&this->colliderTris, 0, &sp40, &sp4C, &sp58);
        Matrix_GetStateTranslationAndScaledX(-4500.0f, &sp58);
        Collider_SetTrisVertices(&this->colliderTris, 1, &sp40, &sp58, &sp4C);
    }

    if (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FIRE) {
        for (i = 0; i < ARRAY_COUNT(this->limbPos); i++) {
            this->limbPos[i].y -= 50.0f;
        }
    }

    Actor_DrawDamageEffects(globalCtx, &this->actor, this->limbPos, ARRAY_COUNT(this->limbPos), this->drawDmgEffScale,
                            this->drawDmgEffFrozenSteamScale, this->drawDmgEffAlpha, this->drawDmgEffType);
}
