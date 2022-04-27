/*
 * File: z_en_snowman.c
 * Overlay: ovl_En_Snowman
 * Description: Enos
 */

#include "z_en_snowman.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4)

#define THIS ((EnSnowman*)thisx)

void EnSnowman_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSnowman_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSnowman_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSnowman_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B173D0(EnSnowman* this);
void func_80B1746C(EnSnowman* this, GlobalContext* globalCtx);
void func_80B177EC(EnSnowman* this, GlobalContext* globalCtx);
void func_80B178B8(EnSnowman* this, GlobalContext* globalCtx);
void func_80B179D0(EnSnowman* this);
void func_80B17A58(EnSnowman* this, GlobalContext* globalCtx);
void func_80B17CE8(EnSnowman* this);
void func_80B17D78(EnSnowman* this, GlobalContext* globalCtx);
void func_80B17EB4(EnSnowman* this);
void func_80B17EFC(EnSnowman* this, GlobalContext* globalCtx);
void func_80B17F4C(EnSnowman* this, GlobalContext* globalCtx);
void func_80B17FE0(EnSnowman* this, GlobalContext* globalCtx);
void func_80B18124(EnSnowman* this, GlobalContext* globalCtx);
void func_80B183A4(EnSnowman* this, GlobalContext* globalCtx);
void func_80B1848C(EnSnowman* this, GlobalContext* globalCtx);
void func_80B18600(EnSnowman* this);
void func_80B1861C(EnSnowman* this, GlobalContext* globalCtx);
void func_80B18908(EnSnowman* this);
void func_80B189C4(EnSnowman* this, GlobalContext* globalCtx);
void func_80B189D4(EnSnowman* this);
void func_80B18A04(EnSnowman* this, GlobalContext* globalCtx);
void func_80B18A28(EnSnowman* this, Vec3f* arg1, s32 arg2);
void func_80B18BB4(EnSnowman* this, GlobalContext* globalCtx, Vec3f* arg2);
void func_80B18C7C(EnSnowman* this, GlobalContext* globalCtx);
void func_80B19474(Actor* thisx, GlobalContext* globalCtx);
void func_80B19948(Actor* thisx, GlobalContext* globalCtx);
void func_80B19998(Actor* thisx, GlobalContext* globalCtx);

const ActorInit En_Snowman_InitVars = {
    ACTOR_EN_SNOWMAN,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_SNOWMAN,
    sizeof(EnSnowman),
    (ActorFunc)EnSnowman_Init,
    (ActorFunc)EnSnowman_Destroy,
    (ActorFunc)EnSnowman_Update,
    (ActorFunc)EnSnowman_Draw,
};

static ColliderCylinderInit sCylinderInit1 = {
    {
        COLTYPE_HIT4,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0.0f, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON | BUMP_HOOKABLE,
        OCELEM_ON,
    },
    { 60, 80, 0, { 0, 0, 0 } },
};

static ColliderCylinderInit sCylinderInit2 = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x00, 0x04 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NONE,
        BUMP_ON,
        OCELEM_ON,
    },
    { 60, 80, 0, { 0, 0, 0 } },
};

typedef enum {
    /* 0x0 */ EN_SNOWMAN_DMGEFF_NONE,
    /* 0x1 */ EN_SNOWMAN_DMGEFF_STUN,
    /* 0x2 */ EN_SNOWMAN_DMGEFF_FIRE_ARROW,
    /* 0x4 */ EN_SNOWMAN_DMGEFF_LIGHT_ARROW = 0x4,
    /* 0x5 */ EN_SNOWMAN_DMGEFF_ZORA_MAGIC,
    /* 0xF */ EN_SNOWMAN_DMGEFF_HOOKSHOT = 0xF,
} EnTalkGibudDamageEffect;

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, EN_SNOWMAN_DMGEFF_STUN),
    /* Deku Stick     */ DMG_ENTRY(1, EN_SNOWMAN_DMGEFF_NONE),
    /* Horse trample  */ DMG_ENTRY(1, EN_SNOWMAN_DMGEFF_NONE),
    /* Explosives     */ DMG_ENTRY(1, EN_SNOWMAN_DMGEFF_NONE),
    /* Zora boomerang */ DMG_ENTRY(1, EN_SNOWMAN_DMGEFF_NONE),
    /* Normal arrow   */ DMG_ENTRY(1, EN_SNOWMAN_DMGEFF_NONE),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, EN_SNOWMAN_DMGEFF_NONE),
    /* Hookshot       */ DMG_ENTRY(1, EN_SNOWMAN_DMGEFF_HOOKSHOT),
    /* Goron punch    */ DMG_ENTRY(2, EN_SNOWMAN_DMGEFF_NONE),
    /* Sword          */ DMG_ENTRY(1, EN_SNOWMAN_DMGEFF_NONE),
    /* Goron pound    */ DMG_ENTRY(1, EN_SNOWMAN_DMGEFF_NONE),
    /* Fire arrow     */ DMG_ENTRY(2, EN_SNOWMAN_DMGEFF_FIRE_ARROW),
    /* Ice arrow      */ DMG_ENTRY(1, EN_SNOWMAN_DMGEFF_NONE),
    /* Light arrow    */ DMG_ENTRY(2, EN_SNOWMAN_DMGEFF_LIGHT_ARROW),
    /* Goron spikes   */ DMG_ENTRY(1, EN_SNOWMAN_DMGEFF_NONE),
    /* Deku spin      */ DMG_ENTRY(0, EN_SNOWMAN_DMGEFF_STUN),
    /* Deku bubble    */ DMG_ENTRY(1, EN_SNOWMAN_DMGEFF_NONE),
    /* Deku launch    */ DMG_ENTRY(2, EN_SNOWMAN_DMGEFF_NONE),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, EN_SNOWMAN_DMGEFF_STUN),
    /* Zora barrier   */ DMG_ENTRY(0, EN_SNOWMAN_DMGEFF_ZORA_MAGIC),
    /* Normal shield  */ DMG_ENTRY(0, EN_SNOWMAN_DMGEFF_NONE),
    /* Light ray      */ DMG_ENTRY(0, EN_SNOWMAN_DMGEFF_NONE),
    /* Thrown object  */ DMG_ENTRY(1, EN_SNOWMAN_DMGEFF_NONE),
    /* Zora punch     */ DMG_ENTRY(1, EN_SNOWMAN_DMGEFF_NONE),
    /* Spin attack    */ DMG_ENTRY(1, EN_SNOWMAN_DMGEFF_NONE),
    /* Sword beam     */ DMG_ENTRY(0, EN_SNOWMAN_DMGEFF_NONE),
    /* Normal Roll    */ DMG_ENTRY(0, EN_SNOWMAN_DMGEFF_NONE),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, EN_SNOWMAN_DMGEFF_NONE),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, EN_SNOWMAN_DMGEFF_NONE),
    /* Unblockable    */ DMG_ENTRY(0, EN_SNOWMAN_DMGEFF_NONE),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, EN_SNOWMAN_DMGEFF_NONE),
    /* Powder Keg     */ DMG_ENTRY(1, EN_SNOWMAN_DMGEFF_NONE),
};

static CollisionCheckInfoInit sColChkInfoInit = { 2, 60, 80, 150 };

static Color_RGBA8 D_80B19A80 = { 250, 250, 250, 255 };

static Color_RGBA8 D_80B19A84 = { 180, 180, 180, 255 };

static Vec3f D_80B19A88 = { 0.0f, 1.5f, 0.0f };

static Gfx* D_80B19A94[] = { gEnosSmallSnowballDL, gEnosLargeSnowballDL, gEnosSmallSnowballDL };

static Gfx* D_80B19AA0[] = { gEnosSnowFragment1DL, gEnosSnowFragment2DL, gEnosSnowFragment3DL };

static InitChainEntry sInitChain[] = {
    ICHAIN_S8(hintId, 20, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 3000, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -1000, ICHAIN_STOP),
};

static Vec3f D_80B19AB8 = { 0.0f, -1.0f, 0.0f };

static Vec3f D_80B19AC4 = { 0.0f, -0.5f, 0.0f };

static s8 D_80B19AD0[] = {
    -1, -1, -1, -1, -1, -1, 0, 1, -1, 2, 3, 4,
};

static Vec3f D_80B19ADC[] = {
    { 2000.0f, 3000.0f, 0.0f }, { 2000.0f, -2000.0f, 0.0f }, { 3000.0f, 0.0f, 0.0f },
    { 1000.0f, 0.0f, 3000.0f }, { 1000.0f, 0.0f, -3000.0f },
};

void EnSnowman_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnSnowman* this = THIS;
    s32 phi_v1;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    phi_v1 = ((this->actor.params >> 8) & 0xFF);
    if (phi_v1 == 0xFF) {
        phi_v1 = 0;
    }

    this->actor.params &= 7;
    if (EN_SNOWMAN_GET_TYPE(&this->actor) < EN_SNOWMAN_TYPE_SMALL_SNOWBALL) {
        SkelAnime_InitFlex(globalCtx, &this->bodySkelAnime, &gEnosSkel, &gEnosSurfaceAnim, this->bodyJointTable,
                           this->bodyMorphTable, ENOS_LIMB_MAX);
        SkelAnime_InitFlex(globalCtx, &this->snowPileSkelAnime, &gEnosSnowPileSkel, &gEnosSnowPileMoveAnim,
                           this->snowPileJointTable, this->snowPileMorphTable, ENOS_SNOW_PILE_LIMB_MAX);
        CollisionCheck_SetInfo(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
        Collider_InitAndSetCylinder(globalCtx, &this->unk_32C, &this->actor, &sCylinderInit1);
        if (EN_SNOWMAN_GET_TYPE(&this->actor) == EN_SNOWMAN_TYPE_LARGE) {
            this->actor.flags |= ACTOR_FLAG_400;
            Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_SNOWMAN, this->actor.world.pos.x,
                               this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, EN_SNOWMAN_TYPE_SPLIT);
            this->actor.parent = Actor_SpawnAsChildAndCutscene(
                &globalCtx->actorCtx, globalCtx, ACTOR_EN_SNOWMAN, this->actor.world.pos.x, this->actor.world.pos.y,
                this->actor.world.pos.z, 0, 0, 0, EN_SNOWMAN_TYPE_SPLIT, -1, this->actor.unk20, NULL);
            if ((this->actor.child == NULL) || (this->actor.parent == NULL)) {
                if (this->actor.child != NULL) {
                    Actor_MarkForDeath(this->actor.child);
                }

                if (this->actor.parent != NULL) {
                    Actor_MarkForDeath(this->actor.parent);
                }

                Actor_MarkForDeath(&this->actor);
                return;
            }

            this->actor.parent->child = &this->actor;
            this->actor.child->child = this->actor.parent;
            this->actor.parent->parent = this->actor.child;
            if (1) {}
            Actor_SetScale(&this->actor, 0.02f);
        }

        this->unk_294 = thisx->scale.x * 100.0f;
        this->unk_29C = (240.0f * this->unk_294) + (phi_v1 * 0.1f * 40.0f);
        if (EN_SNOWMAN_GET_TYPE(thisx) == EN_SNOWMAN_TYPE_SPLIT) {
            func_80B18908(this);
        } else {
            func_80B173D0(this);
        }
    } else {
        Player* player = GET_PLAYER(globalCtx);

        this->actor.flags &= ~ACTOR_FLAG_1;
        Collider_InitAndSetCylinder(globalCtx, &this->unk_32C, &this->actor, &sCylinderInit2);
        this->actor.world.rot.y = Actor_YawBetweenActors(&this->actor, &player->actor);
        this->actor.velocity.y = (Actor_XZDistanceBetweenActors(&this->actor, &player->actor) * 0.035f) + -5.0f;
        this->actor.velocity.y = CLAMP_MAX(this->actor.velocity.y, 3.5f);
        if (EN_SNOWMAN_GET_TYPE(&this->actor) == EN_SNOWMAN_TYPE_SMALL_SNOWBALL) {
            this->actor.speedXZ = 15.0f;
        } else {
            this->actor.speedXZ = 22.5f;
            this->actor.velocity.y *= 1.5f;
        }

        this->actor.world.pos.x += this->actor.speedXZ * Math_SinS(this->actor.world.rot.y);
        this->actor.world.pos.y += this->actor.velocity.y;
        this->actor.world.pos.z += this->actor.speedXZ * Math_CosS(this->actor.world.rot.y);
        if (EN_SNOWMAN_GET_TYPE(&this->actor) == EN_SNOWMAN_TYPE_SMALL_SNOWBALL) {
            this->unk_32C.dim.radius = 8;
            this->unk_32C.dim.height = 12;
            this->unk_32C.dim.yShift = -6;
            ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 10.0f);
        } else {
            this->unk_32C.dim.radius = 50;
            this->unk_32C.dim.height = 122;
            this->unk_32C.dim.yShift = -8;
            this->unk_32C.info.toucher.damage = 16;
            this->actor.world.pos.y -= 32.0f;
            Actor_SetScale(&this->actor, 0.006f);
            ActorShape_Init(&this->actor.shape, 5333.3335f, ActorShadow_DrawCircle, 170.0f);
            this->actor.gravity = -1.5f;
        }

        this->actor.flags |= ACTOR_FLAG_10;
        this->actor.update = func_80B19474;
        this->actor.draw = func_80B19998;
        this->unk_28C = 5;
    }
}

void EnSnowman_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnSnowman* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->unk_32C);
}

void func_80B16FC0(EnSnowman* this, GlobalContext* globalCtx) {
    s16 phi_s1 = 0;
    Vec3f sp78;
    f32 temp_fs0;
    s32 i;

    sp78.y = (Rand_ZeroFloat(10.0f) * this->unk_294) + this->actor.world.pos.y;
    for (i = 0; i < 16; i++) {
        temp_fs0 = (Rand_ZeroFloat(10.0f) + 20.0f) * this->unk_294;
        sp78.x = (Math_SinS(phi_s1) * temp_fs0) + this->actor.world.pos.x;
        sp78.z = (Math_CosS(phi_s1) * temp_fs0) + this->actor.world.pos.z;
        func_800B0DE0(globalCtx, &sp78, &D_80B19A88, &gZeroVec3f, &D_80B19A80, &D_80B19A84, this->unk_294 * 400.0f, 10);
        phi_s1 += 0x1000;
    }
}

void func_80B17144(EnSnowman* this, GlobalContext* globalCtx) {
    s16 temp_s0;
    s16 temp_s1;
    Vec3f pos;
    Vec3f velocity;
    f32 temp_fs1;
    s32 i;

    for (i = 0; i < 15; i++) {
        temp_s0 = Rand_S16Offset(0x1800, 0x2800);
        temp_s1 = ((u32)Rand_Next() >> 0x10);
        temp_fs1 = Rand_ZeroFloat(3.0f) + 8.0f;
        velocity.x = (temp_fs1 * Math_CosS(temp_s0)) * Math_SinS(temp_s1);
        velocity.y = temp_fs1 * Math_SinS(temp_s0);
        velocity.z = (temp_fs1 * Math_CosS(temp_s0)) * Math_CosS(temp_s1);
        pos.x = (Rand_ZeroFloat(10.0f) * velocity.x) + this->unk_2B4.x;
        pos.y = (Rand_ZeroFloat(8.0f) * velocity.y) + this->unk_2B4.y;
        pos.z = (Rand_ZeroFloat(10.0f) * velocity.z) + this->unk_2B4.z;
        EffectSsHahen_Spawn(globalCtx, &pos, &velocity, &D_80B19AB8, 0,
                            Rand_S16Offset((((i % 3) * 50) + 50), (((i % 3) * 25) + 25)), 452, 20, D_80B19AA0[i % 3]);
    }

    func_800B0DE0(globalCtx, &this->unk_2B4, &gZeroVec3f, &gZeroVec3f, &D_80B19A80, &D_80B19A84, 1000, 150);
}

void func_80B173D0(EnSnowman* this) {
    Animation_PlayLoop(&this->snowPileSkelAnime, &gEnosSnowPileMoveAnim);
    this->actor.scale.y = this->actor.scale.x;
    this->actor.speedXZ = 2.0f;
    this->actor.draw = func_80B19948;
    this->unk_28C = 0x28;
    this->unk_28A = 0;
    this->unk_32C.dim.radius = this->unk_294 * 30.0f;
    this->unk_32C.dim.height = this->unk_294 * 10.0f;
    this->actionFunc = func_80B1746C;
}

void func_80B1746C(EnSnowman* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f sp38;

    SkelAnime_Update(&this->snowPileSkelAnime);
    if (EN_SNOWMAN_GET_TYPE(&this->actor) == EN_SNOWMAN_TYPE_LARGE) {
        func_800B9010(&this->actor, NA_SE_EN_YMAJIN_MOVE - SFX_FLAG);
    } else {
        func_800B9010(&this->actor, NA_SE_EN_YMAJIN_MINI_MOVE - SFX_FLAG);
    }

    if (this->unk_28C > 0) {
        this->unk_28C--;
    }

    if (this->unk_28C == 0) {
        this->unk_32C.base.acFlags |= AC_ON;
    }

    if ((this->unk_290 == 0) && (EN_SNOWMAN_GET_TYPE(&this->actor) == EN_SNOWMAN_TYPE_SPLIT)) {
        if ((this->actor.parent->colChkInfo.health != 0) && (this->actor.child->colChkInfo.health != 0)) {
            sp38.x = (this->actor.parent->world.pos.x + this->actor.child->world.pos.x + this->actor.world.pos.x) *
                     0.33333334f;
            sp38.z = (this->actor.parent->world.pos.z + this->actor.child->world.pos.z + this->actor.world.pos.z) *
                     0.33333334f;
        } else if (this->actor.parent->colChkInfo.health != 0) {
            sp38.x = (this->actor.parent->world.pos.x + this->actor.world.pos.x) / 2.0f;
            sp38.z = (this->actor.parent->world.pos.z + this->actor.world.pos.z) / 2.0f;
        } else if (this->actor.child->colChkInfo.health != 0) {
            sp38.x = (this->actor.child->world.pos.x + this->actor.world.pos.x) / 2.0f;
            sp38.z = (this->actor.child->world.pos.z + this->actor.world.pos.z) / 2.0f;
        } else {
            sp38.x = this->actor.world.pos.x;
            sp38.z = this->actor.world.pos.z;
        }

        sp38.y = this->actor.world.pos.y;
        func_80B18BB4((EnSnowman*)this->actor.parent, globalCtx, &sp38);
        func_80B18BB4((EnSnowman*)this->actor.child, globalCtx, &sp38);
        func_80B18BB4(this, globalCtx, &sp38);
    } else if ((this->unk_28C == 0) && (fabsf(this->actor.playerHeightRel) < 60.0f) &&
               (this->actor.xzDistToPlayer < this->unk_29C) && (Player_GetMask(globalCtx) != PLAYER_MASK_STONE) &&
               !(player->stateFlags1 & 0x800000)) {
        func_80B177EC(this, globalCtx);
    } else if (this->unk_28E != this->actor.shape.rot.y) {
        if (Math_ScaledStepToS(&this->actor.shape.rot.y, this->unk_28E, 0x100) != 0) {
            this->unk_28A = 0;
        }

        this->actor.world.rot.y = this->actor.shape.rot.y;
    } else if (this->actor.bgCheckFlags & 8) {
        this->unk_28E = this->actor.wallYaw;
    } else if (Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos) > 200.0f) {
        this->unk_28E = Actor_YawToPoint(&this->actor, &this->actor.home.pos) + (Rand_Next() >> 0x14);
    } else if (Rand_ZeroOne() < 0.02f) {
        this->unk_28E += (s16)((((u32)Rand_Next() >> 0x13) + 0x1000) * ((Rand_ZeroOne() < 0.5f) ? -1 : 1));
    }
}

void func_80B177EC(EnSnowman* this, GlobalContext* globalCtx) {
    Animation_PlayOnce(&this->bodySkelAnime, &gEnosSurfaceAnim);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_YMAJIN_SURFACE);
    this->unk_32C.dim.radius = this->unk_294 * 40.0f;
    this->unk_32C.dim.height = this->unk_294 * 25.0f;
    this->actor.draw = EnSnowman_Draw;
    this->actor.scale.y = this->actor.scale.x * 0.4f;
    this->actor.speedXZ = 0.0f;
    this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    func_80B16FC0(this, globalCtx);
    this->unk_32C.base.acFlags &= ~AC_ON;
    this->actionFunc = func_80B178B8;
}

void func_80B178B8(EnSnowman* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    Math_StepToF(&this->actor.scale.y, this->actor.scale.x,
                 (this->actor.scale.x * 0.6f) / Animation_GetLastFrame(&gEnosSurfaceAnim));
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x1000);

    if (SkelAnime_Update(&this->bodySkelAnime)) {
        if (this->unk_289 == 1) {
            func_80B17F4C(this, globalCtx);
        } else if (!(player->stateFlags1 & 0x800000) && (Player_GetMask(globalCtx) != PLAYER_MASK_STONE)) {
            this->unk_32C.base.acFlags |= AC_ON;
            this->unk_28C = 3;
            func_80B179D0(this);
        } else {
            this->unk_32C.base.acFlags |= AC_ON;
            this->actor.scale.y = this->actor.scale.x;
            func_80B17EB4(this);
        }
    }
}

void func_80B179D0(EnSnowman* this) {
    this->actor.scale.y = this->actor.scale.x;
    if (EN_SNOWMAN_GET_TYPE(&this->actor) == EN_SNOWMAN_TYPE_LARGE) {
        this->unk_298 = 15.0f;
        Animation_PlayOnce(&this->bodySkelAnime, &gEnosLargeSnowballCreateAnim);
    } else {
        this->unk_298 = 6.0f;
        Animation_PlayOnce(&this->bodySkelAnime, &gEnosSmallSnowballCreateAnim);
    }

    this->actionFunc = func_80B17A58;
}

void func_80B17A58(EnSnowman* this, GlobalContext* globalCtx) {
    Vec3f sp3C;

    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x1000);
    if ((EN_SNOWMAN_GET_TYPE(&this->actor) != EN_SNOWMAN_TYPE_LARGE) && (this->unk_288 != 0) &&
        ((globalCtx->gameplayFrames % 2) != 0)) {
        sp3C.x = randPlusMinusPoint5Scaled(10.0f) + this->unk_2B4.x;
        sp3C.y = randPlusMinusPoint5Scaled(10.0f) + this->unk_2B4.y;
        sp3C.z = randPlusMinusPoint5Scaled(10.0f) + this->unk_2B4.z;
        func_800B0DE0(globalCtx, &sp3C, &D_80B19A88, &gZeroVec3f, &D_80B19A80, &D_80B19A84, 500, 30);
    } else if (EN_SNOWMAN_GET_TYPE(&this->actor) == EN_SNOWMAN_TYPE_LARGE) {
        if ((this->bodySkelAnime.curFrame > 3.0f) && (this->bodySkelAnime.curFrame < 14.0f) &&
            ((globalCtx->gameplayFrames % 2) != 0)) {
            sp3C.x = (this->actor.world.pos.x + (70.0f * Math_SinS(this->actor.shape.rot.y))) +
                     randPlusMinusPoint5Scaled(40.0f);
            sp3C.y = this->actor.world.pos.y + randPlusMinusPoint5Scaled(20.0f);
            sp3C.z = (this->actor.world.pos.z + (70.0f * Math_CosS(this->actor.shape.rot.y))) +
                     randPlusMinusPoint5Scaled(40.0f);
            func_800B0DE0(globalCtx, &sp3C, &D_80B19A88, &gZeroVec3f, &D_80B19A80, &D_80B19A84, 1000, 150);
        }
    }

    if (SkelAnime_Update(&this->bodySkelAnime)) {
        func_80B17CE8(this);
    } else if (Animation_OnFrame(&this->bodySkelAnime, this->unk_298)) {
        if (EN_SNOWMAN_GET_TYPE(&this->actor) == EN_SNOWMAN_TYPE_LARGE) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_YMAJIN_HOLD_SNOW);
        } else {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_YMAJIN_MINI_HOLD);
        }

        this->unk_288 = 1;
    }
}

void func_80B17CE8(EnSnowman* this) {
    if (EN_SNOWMAN_GET_TYPE(&this->actor) == EN_SNOWMAN_TYPE_LARGE) {
        Animation_PlayOnce(&this->bodySkelAnime, &gEnosLargeSnowballThrowAnim);
        this->unk_298 = 17.0f;
    } else {
        Animation_PlayOnce(&this->bodySkelAnime, &gEnosSmallSnowballThrowAnim);
        this->unk_298 = 15.0f;
    }

    this->unk_28C--;
    this->actionFunc = func_80B17D78;
}

void func_80B17D78(EnSnowman* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 sp40;

    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x1000);
    if (SkelAnime_Update(&this->bodySkelAnime)) {
        if ((this->unk_28C != 0) && (Player_GetMask(globalCtx) != PLAYER_MASK_STONE) &&
            !(player->stateFlags1 & 0x800000)) {
            func_80B179D0(this);
        } else {
            this->unk_28C = 0;
            func_80B17EB4(this);
        }
    } else if (Animation_OnFrame(&this->bodySkelAnime, this->unk_298)) {
        this->unk_288 = 0;
        if (EN_SNOWMAN_GET_TYPE(&this->actor) == EN_SNOWMAN_TYPE_LARGE) {
            sp40 = 4;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_YMAJIN_THROW);
        } else {
            sp40 = 3;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_YMAJIN_MINI_THROW);
        }

        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_SNOWMAN, this->unk_2B4.x, this->unk_2B4.y,
                    this->unk_2B4.z, 0, this->actor.yawTowardsPlayer, 0, sp40);
    }
}

void func_80B17EB4(EnSnowman* this) {
    Animation_PlayLoop(&this->bodySkelAnime, &gEnosIdleAnim);
    this->unk_28C = 0x3C;
    this->actionFunc = func_80B17EFC;
}

void func_80B17EFC(EnSnowman* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->bodySkelAnime);
    if (this->unk_28C > 0) {
        this->unk_28C--;
    } else {
        func_80B17F4C(this, globalCtx);
    }
}

void func_80B17F4C(EnSnowman* this, GlobalContext* globalCtx) {
    Animation_Change(&this->bodySkelAnime, &gEnosSurfaceAnim, -1.0f, Animation_GetLastFrame(&gEnosSurfaceAnim), 0.0f,
                     ANIMMODE_ONCE, -3.0f);
    func_80B16FC0(this, globalCtx);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_YMAJIN_HIDE);
    this->actionFunc = func_80B17FE0;
}

void func_80B17FE0(EnSnowman* this, GlobalContext* globalCtx) {
    Math_StepToF(&this->actor.scale.y, this->actor.scale.x * 0.4f,
                 (this->actor.scale.x * 0.6f) / Animation_GetLastFrame(&gEnosSurfaceAnim));

    if (SkelAnime_Update(&this->bodySkelAnime)) {
        if (this->unk_289 == 1) {
            this->actor.draw = func_80B19948;
            this->unk_32C.base.acFlags |= AC_ON;
            func_80B18BB4(this, globalCtx, &this->unk_2A8);
        } else {
            func_80B173D0(this);
        }
    }
}

void func_80B180A4(EnSnowman* this) {
    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 50);
    this->unk_32C.base.acFlags &= ~AC_ON;
    this->unk_28C = 0x32;
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->actor.flags |= ACTOR_FLAG_10;
    this->actor.scale.y = this->actor.scale.x;
    this->actor.speedXZ = 0.0f;
    this->actionFunc = func_80B18124;
}

void func_80B18124(EnSnowman* this, GlobalContext* globalCtx) {
    Vec3f sp3C;
    Vec3f sp30;

    this->unk_28C--;
    if ((this->unk_28C >= 0x26) && (!(this->unk_28C & 1))) {
        sp3C.y = (this->unk_28C - 0x26) * 0.083333336f;
        sp3C.x = randPlusMinusPoint5Scaled(1.5f) * sp3C.y;
        sp3C.z = randPlusMinusPoint5Scaled(1.5f) * sp3C.y;
        sp3C.y += 0.8f;
        sp30.x = ((sp3C.x >= 0.0f ? 1.0f : -1.0f) * Rand_ZeroFloat(20.0f) * this->unk_294) + this->actor.world.pos.x;
        sp30.z = ((sp3C.z >= 0.0f ? 1.0f : -1.0f) * Rand_ZeroFloat(20.0f) * this->unk_294) + this->actor.world.pos.z;
        sp30.y = this->actor.world.pos.y + 3.0f;
        EffectSsIceSmoke_Spawn(globalCtx, &sp30, &sp3C, &gZeroVec3f, this->unk_294 * 300.0f);
    }

    if (this->unk_28C == 0) {
        Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.world.pos, 0x60);
        if (EN_SNOWMAN_GET_TYPE(&this->actor) == EN_SNOWMAN_TYPE_SPLIT) {
            func_80B18908(this);
        } else if (EN_SNOWMAN_GET_TYPE(&this->actor) == EN_SNOWMAN_TYPE_LARGE) {
            Actor_MarkForDeath(this->actor.parent);
            Actor_MarkForDeath(this->actor.child);
            Actor_MarkForDeath(&this->actor);
        } else {
            Actor_MarkForDeath(&this->actor);
        }
    }

    this->actor.scale.y = this->unk_28C * 0.0002f * this->unk_294;
    this->actor.scale.x = (this->unk_294 * 0.0139999995f) - (0.4f * this->actor.scale.y);
    this->actor.scale.z = (this->unk_294 * 0.0139999995f) - (0.4f * this->actor.scale.y);
}

void func_80B18380(EnSnowman* this) {
    if (this->actionFunc != func_80B183A4) {
        this->unk_284 = this->actionFunc;
    }

    this->actionFunc = func_80B183A4;
}

void func_80B183A4(EnSnowman* this, GlobalContext* globalCtx) {
    if (this->actor.colorFilterTimer == 0) {
        this->actionFunc = this->unk_284;
    }
}

void func_80B183C4(EnSnowman* this) {
    Animation_PlayLoop(&this->bodySkelAnime, &gEnosDamageAnim);
    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 20);
    this->unk_32C.base.acFlags &= ~AC_ON;
    this->unk_28C = 0x14;
    this->actor.draw = EnSnowman_Draw;
    this->actor.scale.y = this->actor.scale.x;
    this->actor.speedXZ = 10.0f;
    func_800BE504(&this->actor, &this->unk_32C);

    if (EN_SNOWMAN_GET_TYPE(&this->actor) == EN_SNOWMAN_TYPE_LARGE) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_YMAJIN_DAMAGE);
    } else {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_YMAJIN_MINI_DAMAGE);
    }

    this->actionFunc = func_80B1848C;
}

void func_80B1848C(EnSnowman* this, GlobalContext* globalCtx) {
    s32 temp_v0;

    SkelAnime_Update(&this->bodySkelAnime);
    temp_v0 = CLAMP_MAX(this->unk_28C, 0xA);
    this->actor.shape.rot.y += temp_v0 * 0x300;
    Math_StepToF(&this->actor.speedXZ, 0.0f, 0.5f);

    if (EN_SNOWMAN_GET_TYPE(&this->actor) == EN_SNOWMAN_TYPE_LARGE) {
        Math_StepToF(&this->actor.scale.y, 0.012999999f, 0.00070000003f);
        this->actor.scale.x = this->actor.scale.y;
        this->actor.scale.z = this->actor.scale.y;
    }

    if (this->unk_28C > 0) {
        this->unk_28C--;
    } else if (EN_SNOWMAN_GET_TYPE(&this->actor) == EN_SNOWMAN_TYPE_LARGE) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_YMAJIN_SPLIT);
        func_80B16FC0(this, globalCtx);
        this->drawDmgEffAlpha = 0.0f;
        func_80B18A28((EnSnowman*)this->actor.parent, &this->actor.world.pos, this->actor.shape.rot.y + 0x5555);
        func_80B18A28((EnSnowman*)this->actor.child, &this->actor.world.pos, this->actor.shape.rot.y - 0x5555);
        func_80B18A28(this, &this->actor.world.pos, this->actor.shape.rot.y);
        Math_Vec3f_Copy(&this->unk_2B4, &this->actor.world.pos);
        func_80B17144(this, globalCtx);
    } else if (this->actor.colChkInfo.health != 0) {
        this->unk_32C.base.acFlags |= AC_ON;
        func_80B17F4C(this, globalCtx);
    } else {
        func_80B18600(this);
    }
}

void func_80B18600(EnSnowman* this) {
    this->drawDmgEffAlpha = 0.0f;
    this->actionFunc = func_80B1861C;
}

void func_80B1861C(EnSnowman* this, GlobalContext* globalCtx) {
    Vec3f velocity;
    Vec3f pos;
    s16 temp_s0;
    s16 temp_s1;
    f32 temp_fs1;
    s32 i;

    for (i = 0; i < 15; i++) {
        temp_s0 = Rand_S16Offset(0x1000, 0x3000);
        temp_s1 = ((u32)Rand_Next() >> 0x10);
        temp_fs1 = Rand_ZeroFloat(2.0f) + 4.0f;
        velocity.x = (temp_fs1 * Math_CosS(temp_s0)) * Math_SinS(temp_s1);
        velocity.y = temp_fs1 * Math_SinS(temp_s0);
        velocity.z = (temp_fs1 * Math_CosS(temp_s0)) * Math_CosS(temp_s1);
        pos.x = (Rand_ZeroFloat(6.0f) * velocity.x) + this->actor.world.pos.x;
        pos.y = (Rand_ZeroFloat(3.0f) * velocity.y) + this->actor.world.pos.y;
        pos.z = (Rand_ZeroFloat(6.0f) * velocity.z) + this->actor.world.pos.z;
        EffectSsHahen_Spawn(globalCtx, &pos, &velocity, &D_80B19AC4, 0,
                            Rand_S16Offset((((i % 3) * 20) + 20), (((i % 3) * 10) + 10)), 452, 20, D_80B19AA0[i % 3]);
    }

    func_800B0DE0(globalCtx, &this->actor.world.pos, &gZeroVec3f, &gZeroVec3f, &D_80B19A80, &D_80B19A84, 500, 30);
    SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 30, NA_SE_EN_YMAJIN_DEAD_BREAK);
    Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.world.pos, 0x60);
    if (EN_SNOWMAN_GET_TYPE(&this->actor) == EN_SNOWMAN_TYPE_SPLIT) {
        func_80B18908(this);
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80B18908(EnSnowman* this) {
    this->unk_32C.base.acFlags &= ~AC_HIT;
    this->unk_32C.base.acFlags &= ~AC_HIT;
    this->actor.draw = NULL;
    if (this->unk_289 == 1) {
        this->unk_289 = 2;
    }

    this->actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_10);
    if ((this->actor.parent != NULL) && (((EnSnowman*)this->actor.parent)->actionFunc == func_80B189C4)) {
        if ((this->actor.child != NULL) && (((EnSnowman*)this->actor.child)->actionFunc == func_80B189C4)) {
            func_80B189D4((EnSnowman*)this->actor.parent);
            func_80B189D4((EnSnowman*)this->actor.child);
            Actor_MarkForDeath(&this->actor);
        }
    }

    this->actionFunc = func_80B189C4;
}

void func_80B189C4(EnSnowman* this, GlobalContext* globalCtx) {
}

void func_80B189D4(EnSnowman* this) {
    this->unk_32C.base.acFlags &= ~(AC_ON | AC_HIT);
    this->unk_32C.base.ocFlags1 &= ~(OC1_ON | OC1_HIT);
    this->actionFunc = func_80B18A04;
}

void func_80B18A04(EnSnowman* this, GlobalContext* globalCtx) {
    Actor_MarkForDeath(&this->actor);
}

void func_80B18A28(EnSnowman* this, Vec3f* arg1, s32 arg2) {
    this->actor.flags |= ACTOR_FLAG_1;
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.shape.rot.y = arg2;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->unk_289 = 0;
    this->actor.colChkInfo.health = 2;
    this->unk_294 = 1.0f;
    this->actor.world.pos.x = (Math_SinS(arg2) * 40.0f) + arg1->x;
    this->actor.world.pos.y = arg1->y;
    this->actor.world.pos.z = (Math_CosS(arg2) * 40.0f) + arg1->z;
    this->unk_290 = 0x258;
    this->actor.params = EN_SNOWMAN_TYPE_SPLIT;
    this->actor.flags &= ~ACTOR_FLAG_400;
    this->unk_32C.base.ocFlags1 |= OC1_ON;
    this->unk_32C.base.acFlags &= ~AC_ON;
    func_80B173D0(this);
}

void func_80B18B30(EnSnowman* arg0, EnSnowman* arg1) {
    Actor_PlaySfxAtPos(&arg1->actor, NA_SE_EN_YMAJIN_UNITE);
    arg1->unk_298 += 0.005f;
    arg0->unk_289 = 3;
    arg0->unk_32C.base.ocFlags1 &= ~OC1_HIT;
    arg0->unk_32C.base.acFlags &= ~AC_HIT;
    arg0->unk_32C.base.ocFlags1 &= ~OC1_ON;
    arg0->unk_32C.base.acFlags &= ~AC_ON;
    arg0->unk_298 = 0.0f;
}

void func_80B18BB4(EnSnowman* this, GlobalContext* globalCtx, Vec3f* arg2) {
    if (this->actor.colChkInfo.health == 0) {
        this->unk_289 = 2;
    } else {
        this->actor.flags |= ACTOR_FLAG_10;
        Math_Vec3f_Copy(&this->unk_2A8, arg2);
        this->unk_289 = 1;
        if (this->actionFunc != func_80B17FE0) {
            this->unk_290 = 0x190;
            this->unk_298 = 0.01f;
        }

        if (this->actor.draw == func_80B19948) {
            this->actor.speedXZ = 3.0f;
            this->actionFunc = func_80B18C7C;
        } else {
            this->unk_288 = 0;
            this->actor.speedXZ = 0.0f;
            func_80B17F4C(this, globalCtx);
        }
    }
}

void func_80B18C7C(EnSnowman* this, GlobalContext* globalCtx) {
    EnSnowman* parent;
    EnSnowman* child;

    SkelAnime_Update(&this->snowPileSkelAnime);
    parent = (EnSnowman*)this->actor.parent;
    child = (EnSnowman*)this->actor.child;
    Math_ScaledStepToS(&this->actor.shape.rot.y, Actor_YawToPoint(&this->actor, &this->unk_2A8), 0x1000);
    this->actor.world.rot.y = this->actor.shape.rot.y;

    if (this->unk_289 == 1) {
        if (this->unk_32C.base.ocFlags1 & OC1_HIT) {
            if ((this->unk_32C.base.oc == this->actor.parent) && (parent->unk_289 == 1)) {
                if (this->actor.scale.x < this->actor.parent->scale.x) {
                    func_80B18B30(this, parent);
                } else {
                    func_80B18B30(parent, this);
                }
            } else if ((this->unk_32C.base.oc == this->actor.child) && (child->unk_289 == 1)) {
                if (this->actor.scale.x < this->actor.child->scale.x) {
                    func_80B18B30(this, child);
                } else {
                    func_80B18B30(child, this);
                }
            }
        }

        if (parent->unk_289 == 2) {
            func_80B18B30(parent, this);
        }

        if (child->unk_289 == 2) {
            func_80B18B30(child, this);
        }
    }

    if ((this->unk_290 == 0) && (parent->unk_298 > 0.0f) && (child->unk_298 > 0.0f) && (this->unk_298 < 0.011f) &&
        (this->unk_289 != 3)) {
        this->unk_289 = 2;
        this->unk_298 = 0.0f;
    }

    if (Actor_XZDistanceToPoint(&this->actor, &this->unk_2A8) < 20.0f) {
        this->actor.speedXZ = 0.0f;
    }

    if (Math_StepToF(&this->actor.scale.x, this->unk_298, 0.0005f)) {
        if (this->unk_298 < 0.01f) {
            func_80B18908(this);
        } else if (this->unk_298 > 0.018f) {
            Actor_SetScale(&this->actor, 0.02f);
            this->actor.params = EN_SNOWMAN_TYPE_LARGE;
            this->actor.flags |= ACTOR_FLAG_400;
            this->unk_32C.base.ocFlags1 |= OC1_ON;
            this->unk_289 = 3;
            this->unk_294 = 2.0f;
            func_80B173D0(this);
        }
    }

    this->actor.scale.y = this->actor.scale.x;
    this->actor.scale.z = this->actor.scale.x;
}

void EnSnowman_UpdateDamage(EnSnowman* this, GlobalContext* globalCtx) {
    if (this->unk_32C.base.acFlags & AC_HIT) {
        this->unk_32C.base.acFlags &= ~AC_HIT;
        Actor_SetDropFlag(&this->actor, &this->unk_32C.info);
        if ((this->actor.colChkInfo.damageEffect != EN_SNOWMAN_DMGEFF_HOOKSHOT) ||
            (EN_SNOWMAN_GET_TYPE(&this->actor) != EN_SNOWMAN_TYPE_LARGE)) {
            if (this->actor.colChkInfo.damageEffect == EN_SNOWMAN_DMGEFF_FIRE_ARROW) {
                Enemy_StartFinishingBlow(globalCtx, &this->actor);
                Actor_ApplyDamage(&this->actor);
                func_80B180A4(this);
            } else {
                if ((this->actionFunc == func_80B1746C) || (this->actionFunc == func_80B18C7C)) {
                    func_80B177EC(this, globalCtx);
                } else if (this->actor.colChkInfo.damageEffect == EN_SNOWMAN_DMGEFF_STUN) {
                    Actor_SetColorFilter(&this->actor, 0, 255, 0, 40);
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
                    func_80B18380(this);
                } else if (this->actor.colChkInfo.damageEffect == EN_SNOWMAN_DMGEFF_ZORA_MAGIC) {
                    Actor_SetColorFilter(&this->actor, 0, 255, 0, 40);
                    this->unk_2A4 = 0.55f;
                    this->drawDmgEffAlpha = 2.0f;
                    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_ELECTRIC_SPARKS_LARGE;
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
                    func_80B18380(this);
                } else if (EN_SNOWMAN_GET_TYPE(&this->actor) == EN_SNOWMAN_TYPE_LARGE) {
                    if (this->unk_288 == 1) {
                        this->unk_288 = 0;
                        func_80B17144(this, globalCtx);
                    }

                    func_80B183C4(this);
                } else {
                    if (Actor_ApplyDamage(&this->actor) == 0) {
                        Enemy_StartFinishingBlow(globalCtx, &this->actor);
                    }

                    func_80B183C4(this);
                }
            }

            if (this->actor.colChkInfo.damageEffect == EN_SNOWMAN_DMGEFF_LIGHT_ARROW) {
                this->unk_2A4 = 0.55f;
                this->drawDmgEffAlpha = 4.0f;
                this->drawDmgEffType = ACTOR_DRAW_DMGEFF_LIGHT_ORBS;
                Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, this->unk_32C.info.bumper.hitPos.x,
                            this->unk_32C.info.bumper.hitPos.y, this->unk_32C.info.bumper.hitPos.z, 0, 0, 0,
                            CLEAR_TAG_LARGE_LIGHT_RAYS);
            }
        }
    }
}

void EnSnowman_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnSnowman* this = THIS;
    f32 wallCheckRadius;

    if (this->actionFunc != func_80B189C4) {
        DECR(this->unk_290);

        EnSnowman_UpdateDamage(this, globalCtx);
        this->actionFunc(this, globalCtx);

        if (this->actionFunc != func_80B18A04) {
            Actor_MoveWithGravity(&this->actor);
            if ((EN_SNOWMAN_GET_TYPE(&this->actor) == EN_SNOWMAN_TYPE_LARGE) && (this->actionFunc == func_80B17A58)) {
                wallCheckRadius = (this->bodySkelAnime.curFrame * 0.016666668f) + 1.0f;
                wallCheckRadius = CLAMP_MAX(wallCheckRadius, 1.3f);
                wallCheckRadius *= this->unk_32C.dim.radius;
            } else {
                wallCheckRadius = this->unk_32C.dim.radius;
            }

            Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, wallCheckRadius, 0.0f, 0x1D);
            if ((this->actor.floorPoly != NULL) && ((this->actor.floorPoly->normal.y * 0.00003051851f) < 0.7f)) {
                Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.prevPos);
                if (this->unk_28A == 0) {
                    this->unk_28E = Math_FAtan2F(this->actor.floorPoly->normal.z * 0.00003051851f,
                                                 this->actor.floorPoly->normal.x * 0.00003051851f);
                    this->unk_28A = 1;
                }
            } else {
                func_800BE3D0(&this->actor, this->actor.shape.rot.y, &this->actor.shape.rot);
            }

            Collider_UpdateCylinder(&this->actor, &this->unk_32C);
            if (this->unk_32C.base.acFlags & AC_ON) {
                CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->unk_32C.base);
            }
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->unk_32C.base);

            if (this->actor.draw == EnSnowman_Draw) {
                Actor_SetFocus(&this->actor, this->actor.scale.y * 1800.0f);
            } else {
                Actor_SetFocus(&this->actor, this->actor.scale.y * 720.0f);
            }

            if (this->drawDmgEffAlpha > 0.0f) {
                Math_StepToF(&this->drawDmgEffAlpha, 0.0f, 0.05f);
                this->unk_2A4 = (this->drawDmgEffAlpha + 1.0f) * 0.275f;
                this->unk_2A4 = CLAMP_MAX(this->unk_2A4, 0.55f);
            }
        }
    }
}

void func_80B19474(Actor* thisx, GlobalContext* globalCtx) {
    EnSnowman* this = THIS;
    s16 phi_s0;
    s32 i;

    if (this->unk_28C > 0) {
        this->unk_28C--;
    } else {
        this->unk_32C.base.ocFlags1 |= OC1_ON;
    }

    if ((this->actor.bgCheckFlags & 8) || (this->actor.bgCheckFlags & 1) || (this->actor.bgCheckFlags & 0x10) ||
        (this->unk_32C.base.atFlags & AT_HIT) || (this->unk_32C.base.acFlags & AC_HIT) ||
        (this->unk_32C.base.ocFlags1 & OC1_HIT)) {
        if (EN_SNOWMAN_GET_TYPE(&this->actor) == EN_SNOWMAN_TYPE_SMALL_SNOWBALL) {
            phi_s0 = 10;
            for (i = 0; i < 3; i++) {
                EffectSsHahen_SpawnBurst(globalCtx, &thisx->world.pos, 5.0f, 0, phi_s0, phi_s0 >> 1, 3, 452, 20,
                                         D_80B19AA0[i]);
                phi_s0 *= 2;
            }

            func_800B0DE0(globalCtx, &this->actor.world.pos, &gZeroVec3f, &gZeroVec3f, &D_80B19A80, &D_80B19A84, 500,
                          30);
            SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 20, NA_SE_EV_SMALL_SNOWBALL_BROKEN);
        } else {
            Math_Vec3f_Copy(&this->unk_2B4, &this->actor.world.pos);
            func_80B17144(this, globalCtx);
            SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 20, NA_SE_EV_SNOWBALL_BROKEN);
        }

        SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 20, NA_SE_IT_REFLECTION_WOOD);
        Actor_MarkForDeath(&this->actor);
    } else {
        this->actor.shape.rot.x += 0xF00;
        Actor_MoveWithGravity(&this->actor);
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, this->unk_32C.dim.radius * 0.6f,
                                this->unk_32C.dim.height - this->unk_32C.dim.yShift, 0x1F);
        Collider_UpdateCylinder(&this->actor, &this->unk_32C);
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->unk_32C.base);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->unk_32C.base);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->unk_32C.base);
    }
}

void EnSnowman_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnSnowman* this = THIS;
    s32 pad;
    Gfx* gfx;
    s32 i;

    if (D_80B19AD0[limbIndex] != -1) {
        if (D_80B19AD0[limbIndex] == 4) {
            for (i = 0; i < 5; i++) {
                Matrix_MultiplyVector3fByState(&D_80B19ADC[i], &this->limbPos[i + 4]);
            }
        } else {
            Matrix_GetStateTranslation(&this->limbPos[D_80B19AD0[limbIndex]]);
        }
    }

    if ((limbIndex == ENOS_LIMB_RIGHT_HAND) && (this->unk_288 == 1)) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        gfx = POLY_OPA_DISP;

        if (EN_SNOWMAN_GET_TYPE(thisx) != EN_SNOWMAN_TYPE_LARGE) {
            Matrix_InsertTranslation(800.0f, -600.0f, 0.0f, MTXMODE_APPLY);
        } else {
            Matrix_InsertTranslation(300.0f, -2300.0f, -1900.0f, MTXMODE_APPLY);
            Matrix_Scale(0.3f, 0.3f, 0.3f, MTXMODE_APPLY);
        }

        gSPMatrix(&gfx[0], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(&gfx[1], D_80B19A94[EN_SNOWMAN_GET_TYPE(&this->actor)]);

        POLY_OPA_DISP = &gfx[2];

        CLOSE_DISPS(globalCtx->state.gfxCtx);

        Matrix_GetStateTranslation(&this->unk_2B4);
    }
}

void EnSnowman_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnSnowman* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->bodySkelAnime.skeleton, this->bodySkelAnime.jointTable,
                          this->bodySkelAnime.dListCount, NULL, EnSnowman_PostLimbDraw, &this->actor);
    Actor_DrawDamageEffects(globalCtx, &this->actor, this->limbPos, ARRAY_COUNT(this->limbPos),
                            this->unk_2A4 * this->unk_294, 0.0f, this->drawDmgEffAlpha, this->drawDmgEffType);
}

void func_80B19948(Actor* thisx, GlobalContext* globalCtx) {
    EnSnowman* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->snowPileSkelAnime.skeleton, this->snowPileSkelAnime.jointTable,
                          this->snowPileSkelAnime.dListCount, NULL, NULL, &this->actor);
}

void func_80B19998(Actor* thisx, GlobalContext* globalCtx) {
    Gfx_DrawDListOpa(globalCtx, D_80B19A94[thisx->params - 3]);
}
