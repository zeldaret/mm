/*
 * File: z_en_tite.c
 * Overlay: ovl_En_Tite
 * Description: Tektites
 */

#include "z_en_tite.h"
#include "objects/object_tite/object_tite.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_200)

#define THIS ((EnTite*)thisx)

void EnTite_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTite_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTite_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTite_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80893ED4(EnTite* this);
void func_80893F30(EnTite* this, GlobalContext* globalCtx);
void func_80893FD0(EnTite* this);
void func_80894024(EnTite* this, GlobalContext* globalCtx);
void func_8089408C(EnTite* this, GlobalContext* globalCtx);
void func_808942B4(EnTite* this, GlobalContext* globalCtx);
void func_80894414(EnTite* this);
void func_80894454(EnTite* this, GlobalContext* globalCtx);
void func_8089452C(EnTite* this, GlobalContext* globalCtx);
void func_808945B4(EnTite* this, GlobalContext* globalCtx);
void func_808945EC(EnTite* this);
void func_80894638(EnTite* this, GlobalContext* globalCtx);
void func_8089484C(EnTite* this);
void func_80894910(EnTite* this, GlobalContext* globalCtx);
void func_80894B2C(EnTite* this);
void func_80894BC8(EnTite* this, GlobalContext* globalCtx);
void func_80894E0C(EnTite* this, GlobalContext* globalCtx);
void func_80895020(EnTite* this, GlobalContext* globalCtx);
void func_808951B8(EnTite* this, GlobalContext* globalCtx);
void func_80895424(EnTite* this, GlobalContext* globalCtx);
void func_808955E4(EnTite* this);
void func_80895640(EnTite* this, GlobalContext* globalCtx);
void func_808956B8(EnTite* this);
void func_80895738(EnTite* this, GlobalContext* globalCtx);
void func_80895A10(EnTite* this);
void func_80895AC0(EnTite* this, GlobalContext* globalCtx);
void func_80895CB0(EnTite* this);
void func_80895D08(EnTite* this, GlobalContext* globalCtx);
void func_80895E28(EnTite* this, GlobalContext* globalCtx);

const ActorInit En_Tite_InitVars = {
    ACTOR_EN_TITE,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_TITE,
    sizeof(EnTite),
    (ActorFunc)EnTite_Init,
    (ActorFunc)EnTite_Destroy,
    (ActorFunc)EnTite_Update,
    (ActorFunc)EnTite_Draw,
};

static ColliderSphereInit sSphereInit = {
    {
        COLTYPE_HIT6,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_SPHERE,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x00, 0x08 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_HARD,
        BUMP_ON | BUMP_HOOKABLE,
        OCELEM_ON,
    },
    { 0, { { 0, 1500, 0 }, 20 }, 100 },
};

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
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
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

static CollisionCheckInfoInit sColChkInfoInit = { 2, 40, 40, MASS_HEAVY };

static TexturePtr D_80896B24[2][3] = {
    { object_tite_Tex_001300, object_tite_Tex_001700, object_tite_Tex_001900 },
    { object_tite_Tex_001B00, object_tite_Tex_001F00, object_tite_Tex_002100 },
};

static Color_RGBA8 D_80896B3C = { 250, 250, 250, 255 };
static Color_RGBA8 D_80896B40 = { 180, 180, 180, 255 };
static Vec3f D_80896B44 = { 0.0f, 0.45f, 0.0f };

static InitChainEntry sInitChain[] = {
    ICHAIN_S8(hintId, 70, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_CONTINUE),
    ICHAIN_F32(terminalVelocity, -40, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -1000, ICHAIN_STOP),
};

static s32 D_80896B60 = 0;
static Vec3f D_80896B64 = { 0.0f, 0.3f, 0.0f };

void EnTite_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnTite* this = THIS;
    s32 i;
    s32 j;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    SkelAnime_Init(globalCtx, &this->skelAnime, &object_tite_Skel_003A20, &object_tite_Anim_0012E4, this->jointTable,
                   this->morphTable, 25);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 60.0f);
    Actor_SetFocus(&this->actor, 20.0f);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    Collider_InitAndSetSphere(globalCtx, &this->collider, &this->actor, &sSphereInit);
    this->collider.dim.worldSphere.radius = sSphereInit.dim.modelSphere.radius;
    this->unk_2C0 = 0x1D;

    if (!D_80896B60) {
        for (i = 0; i < ARRAY_COUNT(D_80896B24); i++) {
            for (j = 0; j < ARRAY_COUNT(D_80896B24[0]); j++) {
                D_80896B24[i][j] = Lib_SegmentedToVirtual(D_80896B24[i][j]);
            }
        }
        D_80896B60 = true;
    }

    if (this->actor.params == ENTITE_MINUS_3) {
        this->actor.params = ENTITE_MINUS_2;
        this->unk_2BE = 240;
        this->actor.flags &= ~ACTOR_FLAG_1;
        this->actor.shape.yOffset = -3000.0f;
        this->actor.shape.shadowDraw = NULL;
        func_80895A10(this);
    } else {
        if (this->actor.params == ENTITE_MINUS_4) {
            this->actor.params = ENTITE_MINUS_2;
            this->unk_2BE = 240;
        } else if (this->actor.params == ENTITE_MINUS_2) {
            this->unk_2BE = 128;
        } else {
            this->unk_2BE = 64;
        }
        func_80893ED4(this);
    }

    if (this->actor.params == ENTITE_MINUS_2) {
        this->unk_2C0 |= 0x40;
        this->actor.colChkInfo.health = 3;
    }
}

void EnTite_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnTite* this = THIS;

    Collider_DestroySphere(globalCtx, &this->collider);
}

void func_80893A18(EnTite* this) {
    this->collider.base.colType = COLTYPE_HIT6;
    this->collider.base.acFlags &= ~AC_HARD;
}

s32 func_80893A34(EnTite* this, GlobalContext* globalCtx) {
    if ((this->actor.params == ENTITE_MINUS_2) && (this->actor.bgCheckFlags & 1) &&
        (func_800C99D4(&globalCtx->colCtx, this->actor.floorPoly, this->actor.floorBgId) == 5)) {
        return true;
    }
    return false;
}

void func_80893A9C(EnTite* this, GlobalContext* globalCtx) {
    if (func_80893A34(this, globalCtx)) {
        func_808956B8(this);
    } else {
        func_80893FD0(this);
    }
}

s32 func_80893ADC(EnTite* this) {
    if ((this->actor.params == ENTITE_MINUS_2) && (this->actor.bgCheckFlags & 0x20)) {
        return true;
    }
    return false;
}

s32 func_80893B10(EnTite* this) {
    Math_StepToF(&this->actor.velocity.y, 0.0f, 2.0f);
    return Math_StepToF(&this->actor.world.pos.y, (this->actor.world.pos.y + this->actor.depthInWater) - 1.0f, 2.0f);
}

void func_80893B70(EnTite* this) {
    if (this->actor.params == ENTITE_MINUS_2) {
        if (this->actor.bgCheckFlags & 0x20) {
            this->actor.gravity = 0.0f;
            func_80893B10(this);
        } else {
            this->actor.gravity = -1.0f;
        }
    }
}

void func_80893BCC(EnTite* this, GlobalContext* globalCtx) {
    Vec3f sp7C;
    s32 i;
    s32 j;

    if (this->actor.bgCheckFlags & 2) {
        u32 surface = func_800C9BB8(&globalCtx->colCtx, this->actor.floorPoly, this->actor.floorBgId);

        if ((surface == COLPOLY_SURFACE_GROUND) || (surface == COLPOLY_SURFACE_SAND)) {
            for (i = 5; i < ARRAY_COUNT(this->limbPos); i++) {
                func_800BBFB0(globalCtx, &this->limbPos[i], 1.0f, 2, 80, 15, 1);
            }
        } else if (surface == COLPOLY_SURFACE_SNOW) {
            Vec3f* ptr;

            for (i = 5; i < ARRAY_COUNT(this->limbPos); i++) {
                for (j = 0; j < 2; j++) {
                    ptr = &this->limbPos[i];
                    sp7C.x = ptr->x + randPlusMinusPoint5Scaled(1.0f);
                    sp7C.y = ptr->y + randPlusMinusPoint5Scaled(1.0f);
                    sp7C.z = ptr->z + randPlusMinusPoint5Scaled(1.0f);
                    func_800B0DE0(globalCtx, &sp7C, &gZeroVec3f, &D_80896B64, &D_80896B3C, &D_80896B40,
                                  (s32)Rand_ZeroFloat(16.0f) + 80, 15);
                }
            }
        }
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_EYEGOLE_ATTACK);
    }
}

void func_80893DD4(EnTite* this) {
    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX;
    this->collider.base.colType = COLTYPE_HIT3;
    this->unk_2BC = 80;
    this->drawDmgEffScale = 0.5f;
    this->drawDmgEffFrozenSteamScale = 0.75f;
    this->drawDmgEffAlpha = 1.0f;
    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 80);
    this->actor.flags &= ~ACTOR_FLAG_200;
}

void func_80893E54(EnTite* this, GlobalContext* globalCtx) {
    if (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
        this->collider.base.colType = COLTYPE_HIT6;
        this->drawDmgEffAlpha = 0.0f;
        Actor_SpawnIceEffects(globalCtx, &this->actor, this->limbPos, 9, 2, 0.2f, 0.2f);
        this->actor.flags |= ACTOR_FLAG_200;
    }
}

void func_80893ED4(EnTite* this) {
    Animation_MorphToLoop(&this->skelAnime, &object_tite_Anim_0012E4, 4.0f);
    this->unk_2BC = Rand_S16Offset(15, 30);
    this->actor.speedXZ = 0.0f;
    this->actionFunc = func_80893F30;
}

void func_80893F30(EnTite* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    func_80893B70(this);
    if (this->unk_2BC > 0) {
        this->unk_2BC--;
    } else if ((Player_GetMask(globalCtx) != PLAYER_MASK_STONE) && (this->actor.xzDistToPlayer < 300.0f) &&
               (this->actor.playerHeightRel < 80.0f)) {
        func_808945EC(this);
    }
}

void func_80893FD0(EnTite* this) {
    Animation_PlayOnce(&this->skelAnime, &object_tite_Anim_00083C);
    this->actor.velocity.y = 0.0f;
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = func_80894024;
}

void func_80894024(EnTite* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        func_8089408C(this, globalCtx);
    } else {
        func_80893B70(this);
        Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 1000);
        this->actor.world.rot.y = this->actor.shape.rot.y;
    }
}

void func_8089408C(EnTite* this, GlobalContext* globalCtx) {
    Animation_PlayOnce(&this->skelAnime, &object_tite_Anim_0004F8);
    if (!func_80893ADC(this)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_TEKU_JUMP);
    } else {
        this->actor.world.pos.y += this->actor.depthInWater;
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_TEKU_JUMP_WATER);
    }

    if (this->actor.shape.yOffset < 0.0f) {
        s32 i;
        Vec3f sp70;
        Vec3f sp64;

        sp64.y = 3.0f;
        this->actor.shape.yOffset = 0.0f;

        for (i = 0; i < 4; i++) {
            sp64.x = 2.0f * Math_SinS(this->actor.shape.rot.y);
            sp64.z = 2.0f * Math_CosS(this->actor.shape.rot.y);
            sp70.x = this->actor.world.pos.x + (12.5f * sp64.x);
            sp70.y = this->actor.world.pos.y + 15.0f;
            sp70.z = this->actor.world.pos.z + (12.5f * sp64.z);
            func_800B0DE0(globalCtx, &sp70, &sp64, &D_80896B44, &D_80896B3C, &D_80896B40, 500, 50);
            this->actor.shape.rot.y += 0x4000;
        }

        this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
        this->actor.world.rot.y = this->actor.shape.rot.y;
        this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        this->actor.flags |= ACTOR_FLAG_1;
        this->actor.velocity.y = 10.0f;
    } else {
        this->actor.velocity.y = 8.0f;
    }

    this->actor.bgCheckFlags &= ~(0x40 | 0x20 | 0x2 | 0x1);
    this->actor.gravity = -1.0f;
    this->actor.speedXZ = 4.0f;
    this->actionFunc = func_808942B4;
}

void func_808942B4(EnTite* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if (((this->actor.bgCheckFlags & 1) || (func_80893ADC(this) && (this->actor.depthInWater > 0.0f))) &&
        (this->actor.velocity.y <= 0.0f)) {
        this->actor.speedXZ = 0.0f;
        this->collider.base.atFlags &= ~AT_HIT;
        if (!func_80893ADC(this)) {
            func_80893BCC(this, globalCtx);
            func_80894414(this);
        } else {
            this->actor.gravity = 0.0f;
            if (this->actor.velocity.y < -8.0f) {
                func_8089452C(this, globalCtx);
            } else {
                this->actor.velocity.y = 0.0f;
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_TEKU_LAND_WATER2);
                func_80894414(this);
            }
        }
    } else if (!(this->collider.base.atFlags & AT_HIT)) {
        this->actor.flags |= ACTOR_FLAG_1000000;
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    } else {
        this->collider.base.atFlags &= ~AT_HIT;
        func_80894B2C(this);
    }
}

void func_80894414(EnTite* this) {
    Animation_PlayOnce(&this->skelAnime, &object_tite_Anim_00069C);
    this->actionFunc = func_80894454;
}

void func_80894454(EnTite* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        if ((Player_GetMask(globalCtx) == PLAYER_MASK_STONE) || (this->actor.xzDistToPlayer > 450.0f) ||
            (this->actor.playerHeightRel > 80.0f)) {
            func_80893ED4(this);
        } else if (!Actor_IsFacingPlayer(&this->actor, 0x2328)) {
            func_808945EC(this);
        } else {
            func_80893A9C(this, globalCtx);
        }
    } else {
        Math_ScaledStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 1500);
        func_80893B70(this);
    }
}

void func_8089452C(EnTite* this, GlobalContext* globalCtx) {
    Vec3f sp2C;

    Math_Vec3f_Copy(&sp2C, &this->actor.world.pos);
    sp2C.y += this->actor.depthInWater;
    this->actor.velocity.y *= 0.75f;
    EffectSsGRipple_Spawn(globalCtx, &sp2C, 0, 500, 0);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_TEKU_LAND_WATER);
    this->actionFunc = func_808945B4;
}

void func_808945B4(EnTite* this, GlobalContext* globalCtx) {
    if (func_80893B10(this)) {
        func_80894414(this);
    }
}

void func_808945EC(EnTite* this) {
    Animation_PlayLoop(&this->skelAnime, &object_tite_Anim_000A14);
    this->actor.speedXZ = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->actionFunc = func_80894638;
}

void func_80894638(EnTite* this, GlobalContext* globalCtx) {
    s16 temp_v0;
    s16 temp_v1;

    func_80893B70(this);
    temp_v0 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
    if (temp_v0 > 0) {
        temp_v1 = (s32)(temp_v0 * (1.0f / 42.0f)) + 10;
    } else {
        temp_v1 = (s32)(temp_v0 * (1.0f / 42.0f)) - 10;
    }

    this->actor.shape.rot.y = this->actor.shape.rot.y + (temp_v1 * 2);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->skelAnime.playSpeed = temp_v1 * 0.01f;
    SkelAnime_Update(&this->skelAnime);

    if (Animation_OnFrame(&this->skelAnime, 7.0f)) {
        if (func_80893ADC(this)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_TEKU_WALK_WATER);
        } else {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_TEKU_WALK);
        }
    }

    if ((Player_GetMask(globalCtx) == PLAYER_MASK_STONE) || (this->actor.xzDistToPlayer > 450.0f) ||
        (this->actor.playerHeightRel > 80.0f)) {
        func_80893ED4(this);
    } else if (((this->actor.bgCheckFlags & 1) || (func_80893ADC(this) && (this->actor.depthInWater < 10.0f))) &&
               Actor_IsFacingPlayer(&this->actor, 0xE38)) {
        if ((this->actor.xzDistToPlayer <= 180.0f) && (this->actor.playerHeightRel <= 80.0f)) {
            func_80893A9C(this, globalCtx);
        } else {
            func_8089484C(this);
        }
    }
}

void func_8089484C(EnTite* this) {
    Animation_MorphToPlayOnce(&this->skelAnime, &object_tite_Anim_000C70, -3.0f);
    if (this->actionFunc != func_80894910) {
        this->unk_2B8 = Rand_S16Offset(1, 3);
    }
    this->actor.velocity.y = 9.5f;
    this->actor.gravity = -1.0f;
    this->actor.speedXZ = 4.0f;
    if (func_80893ADC(this)) {
        this->actor.world.pos.y += this->actor.depthInWater;
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_TEKU_JUMP_WATER);
    } else {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_TEKU_JUMP);
    }
    this->actionFunc = func_80894910;
}

void func_80894910(EnTite* this, GlobalContext* globalCtx) {
    Vec3f sp34;

    Math_SmoothStepToF(&this->actor.speedXZ, 0.0f, 0.1f, 1.0f, 0.0f);
    SkelAnime_Update(&this->skelAnime);
    if (this->actor.bgCheckFlags & 0x40) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_TEKU_LAND_WATER);

        if (func_80893ADC(this)) {
            Math_Vec3f_Copy(&sp34, &this->actor.world.pos);
            sp34.y += this->actor.depthInWater;
            this->actor.velocity.y *= 0.75f;
            EffectSsGRipple_Spawn(globalCtx, &sp34, 0, 500, 0);
        }
    } else {
        func_80893BCC(this, globalCtx);
    }

    if (((this->actor.bgCheckFlags & 1) || (func_80893ADC(this) && (this->actor.depthInWater > 0.0f))) &&
        (this->actor.velocity.y <= 0.0f)) {
        this->actor.speedXZ = 0.0f;
        Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 4000);
        this->actor.world.rot.y = this->actor.shape.rot.y;

        if (func_80893ADC(this)) {
            this->actor.gravity = 0.0f;
            if (!func_80893B10(this)) {
                return;
            }
        }

        if ((Player_GetMask(globalCtx) == PLAYER_MASK_STONE) || (this->actor.xzDistToPlayer > 450.0f) ||
            (this->actor.playerHeightRel > 80.0f)) {
            func_80893ED4(this);
        } else if ((this->actor.xzDistToPlayer <= 180.0f) && (this->actor.playerHeightRel <= 80.0f)) {
            func_808945EC(this);
        } else {
            func_8089484C(this);
        }
    } else {
        Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 1000);
    }
}

void func_80894B2C(EnTite* this) {
    Animation_MorphToLoop(&this->skelAnime, &object_tite_Anim_0012E4, 4.0f);
    this->actor.speedXZ = -6.0f;
    this->actor.gravity = -1.0f;
    if (this->collider.base.ac != NULL) {
        func_800BE568(&this->actor, &this->collider);
    } else {
        this->actor.world.rot.y = BINANG_ROT180(this->actor.yawTowardsPlayer);
    }
    this->actor.world.rot.y += 0x8000;
    this->actionFunc = func_80894BC8;
}

void func_80894BC8(EnTite* this, GlobalContext* globalCtx) {
    Math_SmoothStepToF(&this->actor.speedXZ, 0.0f, 1.0f, 0.5f, 0.0f);
    SkelAnime_Update(&this->skelAnime);
    if (func_80893ADC(this) && (this->actor.velocity.y <= 0.0f)) {
        this->actor.gravity = 0.0f;
        this->actor.velocity.y = 0.0f;
        this->actor.world.pos.y += this->actor.depthInWater - 1.0f;
    }

    if (this->actor.bgCheckFlags & 0x40) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_TEKU_LAND_WATER2);
    } else {
        func_80893BCC(this, globalCtx);
    }

    if ((this->actor.speedXZ == 0.0f) && ((this->actor.bgCheckFlags & 1) || func_80893ADC(this))) {
        this->actor.world.rot.y = this->actor.shape.rot.y;
        this->collider.base.acFlags |= AC_ON;
        if ((Player_GetMask(globalCtx) == PLAYER_MASK_STONE) ||
            (((this->actor.xzDistToPlayer > 450.0f) || (this->actor.playerHeightRel > 80.0f)) &&
             (ABS_ALT(this->actor.shape.rot.x) < 4000) && (ABS_ALT(this->actor.shape.rot.z) < 4000))) {
            func_80893ED4(this);
        } else if ((this->actor.xzDistToPlayer < 180.0f) && (this->actor.playerHeightRel <= 80.0f) &&
                   Actor_IsFacingPlayer(&this->actor, 0x1770)) {
            func_80893A9C(this, globalCtx);
        } else {
            func_8089484C(this);
        }
    }
}

void func_80894DD0(EnTite* this) {
    this->actor.speedXZ = 0.0f;
    if (this->actor.velocity.y > 0.0f) {
        this->actor.velocity.y = 0.0f;
    }
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = func_80894E0C;
}

void func_80894E0C(EnTite* this, GlobalContext* globalCtx) {
    if (this->unk_2BC != 0) {
        this->unk_2BC--;
    }

    if ((func_80893ADC(this) != 0) && (this->actor.velocity.y <= 0.0f)) {
        this->actor.gravity = 0.0f;
        this->actor.velocity.y = 0.0f;
        this->actor.world.pos.y += this->actor.depthInWater;
    }

    if (this->actor.bgCheckFlags & 0x40) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_TEKU_LAND_WATER2);
    } else {
        func_80893BCC(this, globalCtx);
    }

    if (this->unk_2BC == 0) {
        func_80893E54(this, globalCtx);
        if (this->actor.colChkInfo.health == 0) {
            func_80895020(this, globalCtx);
        } else if (this->unk_2B9 != 0) {
            func_808955E4(this);
        } else if ((Player_GetMask(globalCtx) == PLAYER_MASK_STONE) ||
                   (((this->actor.xzDistToPlayer > 450.0f) || (this->actor.playerHeightRel > 80.0f)) &&
                    (ABS_ALT(this->actor.shape.rot.x) < 4000) && (ABS_ALT(this->actor.shape.rot.z) < 4000))) {
            func_80893ED4(this);
        } else if ((this->actor.xzDistToPlayer < 180.0f) && (this->actor.playerHeightRel <= 80.0f) &&
                   Actor_IsFacingPlayer(&this->actor, 0x1770)) {
            func_80893A9C(this, globalCtx);
        } else {
            func_8089484C(this);
        }
    }
}

void func_80895020(EnTite* this, GlobalContext* globalCtx) {
    Vec3f sp74;
    s32 i;
    f32 temp_f0;
    Vec3f* ptr;

    this->actor.speedXZ = 0.0f;
    this->collider.base.acFlags &= ~AC_ON;
    this->actor.colorFilterTimer = 0;
    SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 40, NA_SE_EN_TEKU_DEAD);
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->actor.flags |= ACTOR_FLAG_10;
    this->unk_2BA = 1;
    Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.world.pos, this->unk_2BE);
    this->unk_2BC = 25;
    this->actor.gravity = -0.58f;
    this->actor.velocity.y = 0.0f;
    this->actor.speedXZ = 0.0f;

    ptr = &this->unk_33C[0];
    for (i = 0; i < ARRAY_COUNT(this->limbPos); i++, ptr++) {
        Math_Vec3f_Diff(&this->limbPos[i], &this->actor.world.pos, &sp74);
        temp_f0 = Math3D_Vec3fMagnitude(&sp74);
        if (temp_f0 > 1.0f) {
            temp_f0 = 1.2f / temp_f0;
        }

        ptr->x = sp74.x * temp_f0;
        ptr->z = sp74.z * temp_f0;
        ptr->y = Rand_ZeroFloat(3.5f) + 5.5f;
    }
    this->actionFunc = func_808951B8;
}

void func_808951B8(EnTite* this, GlobalContext* globalCtx) {
    s32 i;

    this->unk_2BC--;
    Math_SmoothStepToS(&this->actor.world.rot.z, 0x4000, 4, 0x1000, 0x400);

    if (this->unk_2BC == 0) {
        for (i = 0; i < ARRAY_COUNT(this->limbPos); i++) {
            func_800B3030(globalCtx, &this->limbPos[i], &gZeroVec3f, &gZeroVec3f, 40, 7, 1);
            SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->limbPos[i], 11, NA_SE_EN_EXTINCT);
        }
        Actor_MarkForDeath(&this->actor);
    } else {
        for (i = 0; i < ARRAY_COUNT(this->unk_33C); i++) {
            Math_Vec3f_Sum(&this->limbPos[i], &this->unk_33C[i], &this->limbPos[i]);
            this->unk_33C[i].y += this->actor.gravity;
        }
    }
}

void func_808952EC(EnTite* this) {
    Animation_PlayLoopSetSpeed(&this->skelAnime, &object_tite_Anim_000A14, 1.5f);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST1_GROW_HEAD);
    this->collider.base.acFlags &= ~AC_ON;
    func_80893A18(this);
    this->unk_2B9 = 1;
    this->unk_2BC = 400;
    this->actor.speedXZ = 0.0f;
    this->actor.gravity = -1.0f;
    this->unk_2B8 = Rand_ZeroOne() * 50.0f;
    this->actor.bgCheckFlags &= ~1;
    this->actor.velocity.y = 11.0f;
    this->actionFunc = func_80895424;
}

void func_80895424(EnTite* this, GlobalContext* globalCtx) {
    Math_ScaledStepToS(&this->actor.shape.rot.z, -0x8000, 4000);
    if (this->unk_2B8 != 0) {
        this->unk_2B8--;
    } else {
        this->unk_2B8 = Rand_ZeroOne() * 30.0f;
        this->skelAnime.curFrame = Rand_ZeroOne() * 5.0f;
    }

    SkelAnime_Update(&this->skelAnime);

    if (this->actor.bgCheckFlags & 1) {
        this->collider.base.acFlags |= AC_ON;
        if (this->actor.bgCheckFlags & 2) {
            Actor_SpawnFloorDustRing(globalCtx, &this->actor, &this->actor.world.pos, 20.0f, 11, 4.0f, 0, 0, 0);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_EYEGOLE_ATTACK);
        }

        if (this->unk_2BC == 0) {
            func_808955E4(this);
        } else {
            this->unk_2BC--;
        }
    } else if (this->actor.shape.yOffset < 2800.0f) {
        this->actor.shape.yOffset += 400.0f;
    }
}

void func_808955E4(EnTite* this) {
    this->unk_2B9 = 0;
    this->actor.velocity.y = 13.0f;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST1_GROW_HEAD);
    this->actor.bgCheckFlags &= ~1;
    this->collider.base.acFlags &= ~AC_ON;
    this->actionFunc = func_80895640;
}

void func_80895640(EnTite* this, GlobalContext* globalCtx) {
    Math_ScaledStepToS(&this->actor.shape.rot.z, 0, 4000);
    SkelAnime_Update(&this->skelAnime);
    if (this->actor.bgCheckFlags & 1) {
        this->collider.base.acFlags |= AC_ON;
        this->actor.shape.yOffset = 0.0f;
        func_80893BCC(this, globalCtx);
        func_80893ED4(this);
    }
}

void func_808956B8(EnTite* this) {
    this->unk_2BC = 400;
    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    this->collider.base.colType = COLTYPE_HARD;
    this->collider.base.acFlags |= AC_HARD;
    this->actor.gravity = -1.0f;
    this->actionFunc = func_80895738;
}

void func_808956FC(EnTite* this) {
    this->unk_2BC = -1;
    this->actor.bgCheckFlags &= ~1;
    this->actor.velocity.y = 7.5f;
    func_80893A18(this);
}

void func_80895738(EnTite* this, GlobalContext* globalCtx) {
    func_80893BCC(this, globalCtx);
    if (this->collider.base.atFlags & AT_HIT) {
        this->collider.base.atFlags &= ~AT_HIT;
        this->actor.world.rot.y = BINANG_ROT180(this->actor.yawTowardsPlayer);
        if (this->collider.base.atFlags & AT_BOUNCED) {
            func_808956FC(this);
        }
    } else if (this->actor.bgCheckFlags & 8) {
        this->actor.world.rot.y = BINANG_SUB((this->actor.wallYaw * 2) - this->actor.world.rot.y, 0x8000);
    }

    if (this->unk_2BC == -1) {
        Math_StepToF(&this->actor.speedXZ, 0.0f, 0.3f);
        if (this->actor.bgCheckFlags & 1) {
            this->actor.world.rot.y = this->actor.shape.rot.y;
            func_80893ED4(this);
            this->unk_2BC = 100;
        }
    } else if (this->unk_2BC > 0) {
        this->unk_2BC--;
        Math_StepToF(&this->actor.speedXZ, 10.0f, 0.3f);
        this->actor.flags |= ACTOR_FLAG_1000000;
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        if (!func_80893A34(this, globalCtx)) {
            this->unk_2BC = 0;
        }
    } else if ((this->unk_2BC == 0) && Math_StepToF(&this->actor.speedXZ, 0.0f, 0.3f)) {
        this->actor.world.rot.y = this->actor.shape.rot.y;
        func_80893A18(this);
        if ((Player_GetMask(globalCtx) == PLAYER_MASK_STONE) || (this->actor.xzDistToPlayer > 450.0f) ||
            (this->actor.playerHeightRel > 80.0f)) {
            func_80893ED4(this);
        } else if (!Actor_IsFacingPlayer(&this->actor, 0x2328)) {
            func_808945EC(this);
        } else {
            func_80893A9C(this, globalCtx);
        }
    }
    this->actor.shape.rot.y += (s16)(this->actor.speedXZ * 768.0f);
}

void func_8089595C(EnTite* this, GlobalContext* globalCtx) {
    Vec3f sp2C;

    sp2C.x = randPlusMinusPoint5Scaled(20.0f) + this->actor.world.pos.x;
    sp2C.y = this->actor.world.pos.y + 15.0f;
    sp2C.z = randPlusMinusPoint5Scaled(20.0f) + this->actor.world.pos.z;
    func_800B0DE0(globalCtx, &sp2C, &gZeroVec3f, &D_80896B44, &D_80896B3C, &D_80896B40, 500, 50);
}

void func_80895A10(EnTite* this) {
    s32 pad;
    s16 rand;

    Animation_Change(&this->skelAnime, &object_tite_Anim_000A14, 2.0f, 0.0f, 0.0f, 0, 4.0f);
    this->actor.speedXZ = 0.0f;
    rand = Rand_S16Offset(20, 20);
    this->unk_2BC = ((Rand_ZeroOne() < 0.5f) ? -1 : 1) * rand;
    this->actionFunc = func_80895AC0;
}

void func_80895AC0(EnTite* this, GlobalContext* globalCtx) {
    s16 temp_v1;
    s32 temp_v0;

    SkelAnime_Update(&this->skelAnime);
    if (Animation_OnFrame(&this->skelAnime, 7.0f)) {
        if (Rand_ZeroOne() < 0.25f) {
            func_8089595C(this, globalCtx);
        }
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_TEKU_WALK);
    }

    if ((this->unk_2BC == 1) || (this->unk_2BC == -1)) {
        if (this->actor.bgCheckFlags & 8) {
            temp_v1 = this->actor.shape.rot.y - this->actor.wallYaw;
            temp_v0 = ABS_ALT(temp_v1);
            if (temp_v0 > 0x3000) {
                this->unk_2BC = (temp_v0 >> 9) * this->unk_2BC;
            }
        } else if (Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos) < 200.0f) {
            temp_v1 = this->actor.shape.rot.y - Actor_YawToPoint(&this->actor, &this->actor.home.pos);
            temp_v0 = ABS_ALT(temp_v1);
            if (temp_v0 > 0x2000) {
                this->unk_2BC = (temp_v0 >> 9) * this->unk_2BC;
            }
        }
    }

    if ((this->actor.xzDistToPlayer < 240.0f) && (Player_GetMask(globalCtx) != PLAYER_MASK_STONE)) {
        func_8089408C(this, globalCtx);
    } else if (this->unk_2BC > 0) {
        this->unk_2BC--;
        this->actor.shape.rot.y += 0x100;
    } else if (this->unk_2BC < 0) {
        this->unk_2BC++;
        this->actor.shape.rot.y -= 0x100;
    } else {
        func_80895CB0(this);
    }
}

void func_80895CB0(EnTite* this) {
    this->skelAnime.playSpeed = 1.0f;
    this->actor.speedXZ = 1.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->unk_2BC = Rand_S16Offset(20, 20);
    this->actionFunc = func_80895D08;
}

void func_80895D08(EnTite* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if (Animation_OnFrame(&this->skelAnime, 7.0f)) {
        if (Rand_ZeroOne() < 0.5f) {
            func_8089595C(this, globalCtx);
        }
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_TEKU_WALK);
    }
    if ((this->actor.xzDistToPlayer < 240.0f) && (Player_GetMask(globalCtx) != PLAYER_MASK_STONE)) {
        func_8089408C(this, globalCtx);
    } else {
        this->unk_2BC--;
        if (this->unk_2BC == 0) {
            func_80895A10(this);
        }
    }
}

void func_80895DE8(EnTite* this) {
    this->collider.base.acFlags &= ~AC_ON;
    this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
    this->skelAnime.playSpeed = 1.0f;
    this->actor.speedXZ = 0.0f;
    this->actionFunc = func_80895E28;
}

void func_80895E28(EnTite* this, GlobalContext* globalCtx) {
    Vec3f sp44;
    Vec3f sp38;
    s16 sp36;

    SkelAnime_Update(&this->skelAnime);
    this->actor.shape.rot.y += 0x1E00;

    sp44.x = (Math_SinS(this->actor.shape.rot.y) * 25.0f) + this->actor.world.pos.x;
    sp44.y = this->actor.world.pos.y + 15.0f;
    sp44.z = (Math_CosS(this->actor.shape.rot.y) * 25.0f) + this->actor.world.pos.z;

    sp36 = BINANG_SUB(this->actor.shape.rot.y, 0x4000);

    sp38.x = 2.0f * Math_SinS(sp36);
    sp38.y = 3.0f;
    sp38.z = 2.0f * Math_CosS(sp36);

    func_800B0DE0(globalCtx, &sp44, &sp38, &D_80896B44, &D_80896B3C, &D_80896B40, 500, 50);

    sp44.x = (2.0f * this->actor.world.pos.x) - sp44.x;
    sp44.z = (2.0f * this->actor.world.pos.z) - sp44.z;
    sp38.x *= -1.0f;
    sp38.z *= -1.0f;

    func_800B0DE0(globalCtx, &sp44, &sp38, &D_80896B44, &D_80896B3C, &D_80896B40, 500, 50);

    if (Math_StepToF(&this->actor.shape.yOffset, 0.0f, 200.0f)) {
        this->actor.flags |= ACTOR_FLAG_1;
        this->actor.world.rot.y = this->actor.shape.rot.y;
        this->collider.base.acFlags |= AC_ON;
        func_808945EC(this);
    }
}

void func_80895FF8(EnTite* this, GlobalContext* globalCtx) {
    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        this->collider.base.atFlags &= ~AT_HIT;
        if (this->collider.base.colType == COLTYPE_HARD) {
            func_808956FC(this);
            func_800BE568(&this->actor, &this->collider);
            return;
        }

        Actor_SetDropFlag(&this->actor, &this->collider.info);

        if ((this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) ||
            !(this->collider.info.acHitInfo->toucher.dmgFlags & 0xDB0B3)) {
            func_80893E54(this, globalCtx);
            if (this->actor.shape.yOffset < 0.0f) {
                func_80895DE8(this);
                return;
            }

            if (!Actor_ApplyDamage(&this->actor)) {
                Enemy_StartFinishingBlow(globalCtx, &this->actor);
            }

            if (this->actor.colChkInfo.damageEffect != 0xF) {
                if (this->actor.colChkInfo.damageEffect == 5) {
                    this->unk_2BC = 40;
                    Actor_SetColorFilter(&this->actor, 0, 200, 0, 40);
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
                    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_ELECTRIC_SPARKS_LARGE;
                    this->drawDmgEffScale = 0.5f;
                    this->drawDmgEffAlpha = 2.0f;
                    func_80894DD0(this);
                    return;
                }

                if (this->actor.colChkInfo.damageEffect == 1) {
                    this->unk_2BC = 40;
                    Actor_SetColorFilter(&this->actor, 0, 200, 0, 40);
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
                    func_80894DD0(this);
                    return;
                }

                if (this->actor.colChkInfo.damageEffect == 3) {
                    func_80893DD4(this);
                    if (this->actor.colChkInfo.health == 0) {
                        this->unk_2BC = 3;
                        this->collider.base.acFlags &= ~AC_ON;
                    }
                    func_80894DD0(this);
                    return;
                }

                if (this->actor.colChkInfo.damageEffect == 2) {
                    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
                    this->drawDmgEffAlpha = 4.0f;
                    this->drawDmgEffScale = 0.5f;
                } else if (this->actor.colChkInfo.damageEffect == 4) {
                    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_LIGHT_ORBS;
                    this->drawDmgEffAlpha = 4.0f;
                    this->drawDmgEffScale = 0.5f;
                    Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG,
                                this->collider.info.bumper.hitPos.x, this->collider.info.bumper.hitPos.y,
                                this->collider.info.bumper.hitPos.z, 0, 0, 0, CLEAR_TAG_LARGE_LIGHT_RAYS);
                }

                Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 8);

                if (this->actor.colChkInfo.health == 0) {
                    func_80895020(this, globalCtx);
                } else {
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_TEKU_DAMAGE);

                    if (this->unk_2B9 == 0) {
                        func_80894B2C(this);
                        this->collider.base.acFlags &= ~AC_ON;
                    } else {
                        func_808955E4(this);
                    }
                }
            }
        }
    } else if ((this->actor.bgCheckFlags & 1) && (this->collider.base.acFlags & AC_ON) &&
               (this->actor.colChkInfo.health != 0) && (globalCtx->actorCtx.unk2 != 0) &&
               (this->actor.xyzDistToPlayerSq < SQ(200.0f))) {
        this->actor.flags |= ACTOR_FLAG_1;
        if (this->actor.shape.yOffset < 0.0f) {
            this->actor.shape.yOffset = 0.0f;
            this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        }
        if (this->unk_2B9 != 0) {
            func_808955E4(this);
        } else {
            func_808952EC(this);
        }
    }
}

void func_808963B4(EnTite* this, GlobalContext* globalCtx) {
    s32 i;
    Vec3f sp48;

    if (this->actor.bgCheckFlags & 0x40) {
        for (i = 5; i < ARRAY_COUNT(this->limbPos); i++) {
            Math_Vec3f_Copy(&sp48, &this->limbPos[i]);
            sp48.y = this->actor.world.pos.y + this->actor.depthInWater;
            EffectSsGRipple_Spawn(globalCtx, &sp48, 0, 220, 0);
        }
    } else if (this->actor.bgCheckFlags & 0x20) {
        s32 temp = globalCtx->gameplayFrames & 7;

        if (!(temp & 1) && (this->actor.depthInWater < 10.0f)) {
            Math_Vec3f_Copy(&sp48, &this->limbPos[5 + (temp >> 1)]);
            sp48.y = this->actor.world.pos.y + this->actor.depthInWater;
            EffectSsGRipple_Spawn(globalCtx, &sp48, 0, 220, 0);
        }
    }
}

void EnTite_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnTite* this = THIS;

    func_80895FF8(this, globalCtx);

    this->actionFunc(this, globalCtx);

    if (this->actionFunc != func_808951B8) {
        Actor_MoveWithGravity(&this->actor);
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 25.0f, 40.0f, 20.0f, this->unk_2C0);
        func_808963B4(this, globalCtx);
        if (this->actor.bgCheckFlags & 1) {
            func_800BE3D0(&this->actor, this->actor.shape.rot.y, &this->actor.shape.rot);
            if (this->unk_2B9 != 0) {
                this->actor.shape.rot.z = BINANG_ROT180(this->actor.shape.rot.z);
            }
        } else {
            Math_ScaledStepToS(&this->actor.shape.rot.x, 0, 1000);
            if (this->unk_2B9 == 0) {
                Math_ScaledStepToS(&this->actor.shape.rot.z, 0, 1000);
                if (this->actor.shape.yOffset > 0.0f) {
                    this->actor.shape.yOffset -= 400.0f;
                }
            }
        }

        Actor_SetFocus(&this->actor, this->actor.scale.y * 2000.0f);
        this->collider.dim.worldSphere.center.x = this->actor.world.pos.x;
        this->collider.dim.worldSphere.center.y = (s32)this->actor.world.pos.y + 15;
        this->collider.dim.worldSphere.center.z = this->actor.world.pos.z;

        if (this->collider.base.acFlags & AC_ON) {
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);

        if (this->drawDmgEffAlpha > 0.0f) {
            if (this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
                Math_StepToF(&this->drawDmgEffAlpha, 0.0f, 0.05f);
                this->drawDmgEffScale = (this->drawDmgEffAlpha + 1.0f) * 0.25f;
                this->drawDmgEffScale = CLAMP_MAX(this->drawDmgEffScale, 0.5f);
            } else if (!Math_StepToF(&this->drawDmgEffFrozenSteamScale, 0.5f, 0.0125f)) {
                func_800B9010(&this->actor, NA_SE_EV_ICE_FREEZE - SFX_FLAG);
            }
        }
    }
}

s32 EnTite_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                            Actor* thisx) {
    EnTite* this = THIS;

    if (this->unk_2BA == -1) {
        this->unk_3A8 = *dList;
        *dList = NULL;
    }
    return false;
}

void EnTite_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static s8 D_80896B70[] = {
        -1, -1, -1, -1, 0, -1, -1, -1, 1, -1, -1, -1, -1, 2, -1, -1, -1, -1, 3, -1, -1, -1, -1, 4, -1,
    };
    static s8 D_80896B8C[] = {
        -1, -1, -1, -1, 0, -1, -1, -1, 1, 5, -1, -1, -1, 2, 6, -1, -1, -1, 3, 7, -1, -1, -1, 4, 8,
    };
    EnTite* this = THIS;
    MtxF* matrix;
    s8 idx;

    if (this->unk_2BA == 0) {
        idx = D_80896B70[limbIndex];
        if (idx != -1) {
            Matrix_GetStateTranslation(&this->limbPos[idx]);
            if (idx >= 1) {
                Matrix_GetStateTranslationAndScaledX(2500.0f, &this->limbPos[idx + 4]);
            }
        }
    } else if (this->unk_2BA > 0) {
        if (D_80896B8C[limbIndex] != -1) {
            Matrix_GetStateTranslation(&this->limbPos[D_80896B8C[limbIndex]]);
        }

        if (limbIndex == 24) {
            this->unk_2BA = -1;
        }
    } else if (D_80896B8C[limbIndex] != -1) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        matrix = Matrix_GetCurrentState();
        matrix->wx = this->limbPos[D_80896B8C[limbIndex]].x;
        matrix->wy = this->limbPos[D_80896B8C[limbIndex]].y;
        matrix->wz = this->limbPos[D_80896B8C[limbIndex]].z;
        Matrix_InsertZRotation_s(this->actor.world.rot.z, MTXMODE_APPLY);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, this->unk_3A8);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

void EnTite_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnTite* this = THIS;
    Gfx* gfx;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    gfx = POLY_OPA_DISP;

    gSPDisplayList(&gfx[0], &sSetupDL[6 * 25]);

    if (this->actor.params == ENTITE_MINUS_2) {
        gSPSegment(&gfx[1], 0x08, D_80896B24[0][0]);
        gSPSegment(&gfx[2], 0x09, D_80896B24[0][1]);
        gSPSegment(&gfx[3], 0x0A, D_80896B24[0][2]);
    } else {
        gSPSegment(&gfx[1], 0x08, D_80896B24[1][0]);
        gSPSegment(&gfx[2], 0x09, D_80896B24[1][1]);
        gSPSegment(&gfx[3], 0x0A, D_80896B24[1][2]);
    }

    POLY_OPA_DISP = &gfx[4];

    SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, EnTite_OverrideLimbDraw,
                      EnTite_PostLimbDraw, &this->actor);
    Actor_DrawDamageEffects(globalCtx, &this->actor, this->limbPos, ARRAY_COUNT(this->limbPos), this->drawDmgEffScale,
                            this->drawDmgEffFrozenSteamScale, this->drawDmgEffAlpha, this->drawDmgEffType);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
