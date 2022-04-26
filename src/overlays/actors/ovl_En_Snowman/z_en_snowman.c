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

void func_80B1746C(EnSnowman* this, GlobalContext* globalCtx);
void func_80B178B8(EnSnowman* this, GlobalContext* globalCtx);
void func_80B17A58(EnSnowman* this, GlobalContext* globalCtx);
void func_80B17D78(EnSnowman* this, GlobalContext* globalCtx);
void func_80B17EFC(EnSnowman* this, GlobalContext* globalCtx);
void func_80B17FE0(EnSnowman* this, GlobalContext* globalCtx);
void func_80B18124(EnSnowman* this, GlobalContext* globalCtx);
void func_80B183A4(EnSnowman* this, GlobalContext* globalCtx);
void func_80B1848C(EnSnowman* this, GlobalContext* globalCtx);
void func_80B1861C(EnSnowman* this, GlobalContext* globalCtx);
void func_80B189C4(EnSnowman* this, GlobalContext* globalCtx);
void func_80B18A04(EnSnowman* this, GlobalContext* globalCtx);
void func_80B18C7C(EnSnowman* this, GlobalContext* globalCtx);
void func_80B19474(Actor* thisx, GlobalContext* globalCtx);
void func_80B19998(Actor* this, GlobalContext* globalCtx);
void func_80B173D0(EnSnowman* this);
void func_80B18908(EnSnowman* this);
void func_80B19948(Actor* thisx, GlobalContext* globalCtx);
void func_80B18BB4(EnSnowman* this, GlobalContext* globalCtx, Vec3f* arg2);
void func_80B177EC(EnSnowman* this, GlobalContext* globalCtx);
void func_80B179D0(EnSnowman* this);
void func_80B17EB4(EnSnowman* this);
void func_80B17F4C(EnSnowman* this, GlobalContext* globalCtx);
void func_80B17CE8(EnSnowman* this);
void func_80B189D4(EnSnowman* this);

#if 0
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

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B19A00 = {
    { COLTYPE_HIT4, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 60, 80, 0, { 0, 0, 0 } },
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B19A2C = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_NONE | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_ON, OCELEM_ON, },
    { 60, 80, 0, { 0, 0, 0 } },
};

// static DamageTable sDamageTable = {
static DamageTable D_80B19A58 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0xF),
    /* Goron punch    */ DMG_ENTRY(2, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x0),
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

// sColChkInfoInit
static CollisionCheckInfoInit D_80B19A78 = { 2, 60, 80, 150 };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B19AAC[] = {
    ICHAIN_S8(hintId, 20, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 3000, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -1000, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80B19A00;
extern ColliderCylinderInit D_80B19A2C;
extern DamageTable D_80B19A58;
extern CollisionCheckInfoInit D_80B19A78;
extern InitChainEntry D_80B19AAC[];
extern Gfx* D_80B19A94[];
extern s8 D_80B19AD0[];
extern Vec3f D_80B19ADC[];
extern s16 D_80B19ADA;
extern Color_RGBA8 D_80B19A80;
extern Color_RGBA8 D_80B19A84;
extern Vec3f D_80B19A88;

extern AnimationHeader D_06000404;
extern UNK_TYPE D_06004628;
extern AnimationHeader D_060046D8;
extern AnimationHeader D_06004F14;
extern AnimationHeader D_0600554C;
extern AnimationHeader D_060058CC;
extern FlexSkeletonHeader D_060045A0;
extern FlexSkeletonHeader D_06004A90;
extern AnimationHeader D_060007B4;
extern AnimationHeader D_0600544C;

void EnSnowman_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnSnowman* this = THIS;
    s32 phi_v1;

    Actor_ProcessInitChain(&this->actor, D_80B19AAC);
    phi_v1 = ((this->actor.params >> 8) & 0xFF);
    if (phi_v1 == 0xFF) {
        phi_v1 = 0;
    }

    this->actor.params &= 7;
    if (this->actor.params < 3) {
        SkelAnime_InitFlex(globalCtx, &this->bodySkelAnime, &D_060045A0, &D_0600554C, this->bodyJointTable,
                           this->bodyMorphTable, 12);
        SkelAnime_InitFlex(globalCtx, &this->snowPileSkelAnime, &D_06004A90, &D_060046D8, this->snowPileJointTable,
                           this->snowPileMorphTable, 3);
        CollisionCheck_SetInfo(&this->actor.colChkInfo, &D_80B19A58, &D_80B19A78);
        Collider_InitAndSetCylinder(globalCtx, &this->unk_32C, &this->actor, &D_80B19A00);
        if (this->actor.params == 1) {
            this->actor.flags |= ACTOR_FLAG_400;
            Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_SNOWMAN, this->actor.world.pos.x,
                               this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, 2);
            this->actor.parent = Actor_SpawnAsChildAndCutscene(
                &globalCtx->actorCtx, globalCtx, ACTOR_EN_SNOWMAN, this->actor.world.pos.x, this->actor.world.pos.y,
                this->actor.world.pos.z, 0, 0, 0, 2, -1, this->actor.unk20, NULL);
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
        if (thisx->params == 2) {
            func_80B18908(this);
        } else {
            func_80B173D0(this);
        }
    } else {
        Player* player = GET_PLAYER(globalCtx);

        this->actor.flags &= ~ACTOR_FLAG_1;
        Collider_InitAndSetCylinder(globalCtx, &this->unk_32C, &this->actor, &D_80B19A2C);
        this->actor.world.rot.y = Actor_YawBetweenActors(&this->actor, &player->actor);
        this->actor.velocity.y = (Actor_XZDistanceBetweenActors(&this->actor, &player->actor) * 0.035f) + -5.0f;
        this->actor.velocity.y = CLAMP_MAX(this->actor.velocity.y, 3.5f);
        if (this->actor.params == 3) {
            this->actor.speedXZ = 15.0f;
        } else {
            this->actor.speedXZ = 22.5f;
            this->actor.velocity.y *= 1.5f;
        }

        this->actor.world.pos.x += this->actor.speedXZ * Math_SinS(this->actor.world.rot.y);
        this->actor.world.pos.y += this->actor.velocity.y;
        this->actor.world.pos.z += this->actor.speedXZ * Math_CosS(this->actor.world.rot.y);
        if (this->actor.params == 3) {
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

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B17144.s")

void func_80B173D0(EnSnowman* this) {
    Animation_PlayLoop(&this->snowPileSkelAnime, &D_060046D8);
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
    if (this->actor.params == 1) {
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

    if ((this->unk_290 == 0) && (this->actor.params == 2)) {
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
    Animation_PlayOnce(&this->bodySkelAnime, &D_0600554C);
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
                 (this->actor.scale.x * 0.6f) / Animation_GetLastFrame(&D_0600554C));
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
    if (this->actor.params == 1) {
        this->unk_298 = 15.0f;
        Animation_PlayOnce(&this->bodySkelAnime, &D_06000404);
    } else {
        this->unk_298 = 6.0f;
        Animation_PlayOnce(&this->bodySkelAnime, &D_060007B4);
    }

    this->actionFunc = func_80B17A58;
}

void func_80B17A58(EnSnowman* this, GlobalContext* globalCtx) {
    Vec3f sp3C;

    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x1000);
    if ((this->actor.params != 1) && (this->unk_288 != 0) && ((globalCtx->gameplayFrames % 2) != 0)) {
        sp3C.x = randPlusMinusPoint5Scaled(10.0f) + this->unk_2B4.x;
        sp3C.y = randPlusMinusPoint5Scaled(10.0f) + this->unk_2B4.y;
        sp3C.z = randPlusMinusPoint5Scaled(10.0f) + this->unk_2B4.z;
        func_800B0DE0(globalCtx, &sp3C, &D_80B19A88, &gZeroVec3f, &D_80B19A80, &D_80B19A84, 500, 30);
    } else if (this->actor.params == 1) {
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
        if (this->actor.params == 1) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_YMAJIN_HOLD_SNOW);
        } else {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_YMAJIN_MINI_HOLD);
        }

        this->unk_288 = 1;
    }
}

void func_80B17CE8(EnSnowman* this) {
    if (this->actor.params == 1) {
        Animation_PlayOnce(&this->bodySkelAnime, &D_06004F14);
        this->unk_298 = 17.0f;
    } else {
        Animation_PlayOnce(&this->bodySkelAnime, &D_0600544C);
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
        if (this->actor.params == 1) {
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
    Animation_PlayLoop(&this->bodySkelAnime, &D_060058CC);
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
    Animation_Change(&this->bodySkelAnime, &D_0600554C, -1.0f, Animation_GetLastFrame(&D_0600554C), 0.0f, ANIMMODE_ONCE,
                     -3.0f);
    func_80B16FC0(this, globalCtx);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_YMAJIN_HIDE);
    this->actionFunc = func_80B17FE0;
}

void func_80B17FE0(EnSnowman* this, GlobalContext* globalCtx) {
    Math_StepToF(&this->actor.scale.y, this->actor.scale.x * 0.4f,
                 (this->actor.scale.x * 0.6f) / Animation_GetLastFrame(&D_0600554C));

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

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B18124.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B18380.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B183A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B183C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B1848C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B18600.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B1861C.s")

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

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B18A28.s")

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
            this->actor.params = 1;
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

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B18F50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/EnSnowman_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B19474.s")

void func_80B19718(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
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

    if ((limbIndex == 10) && (this->unk_288 == 1)) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        gfx = POLY_OPA_DISP;

        if (thisx->params != 1) {
            Matrix_InsertTranslation(800.0f, -600.0f, 0.0f, MTXMODE_APPLY);
        } else {
            Matrix_InsertTranslation(300.0f, -2300.0f, -1900.0f, MTXMODE_APPLY);
            Matrix_Scale(0.3f, 0.3f, 0.3f, MTXMODE_APPLY);
        }

        gSPMatrix(&gfx[0], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(&gfx[1], D_80B19A94[this->actor.params]);

        POLY_OPA_DISP = &gfx[2];

        CLOSE_DISPS(globalCtx->state.gfxCtx);

        Matrix_GetStateTranslation(&this->unk_2B4);
    }
}

void EnSnowman_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnSnowman* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->bodySkelAnime.skeleton, this->bodySkelAnime.jointTable,
                          this->bodySkelAnime.dListCount, NULL, func_80B19718, &this->actor);
    Actor_DrawDamageEffects(globalCtx, &this->actor, this->limbPos, ARRAY_COUNT(this->limbPos),
                            this->unk_2A4 * this->unk_294, 0.0f, this->drawDmgEffAlpha, this->drawDmgEffType);
}

void func_80B19948(Actor* thisx, GlobalContext* globalCtx) {
    EnSnowman* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->snowPileSkelAnime.skeleton, this->snowPileSkelAnime.jointTable,
                          this->snowPileSkelAnime.dListCount, NULL, NULL, &this->actor);
}

void func_80B19998(Actor* this, GlobalContext* globalCtx) {
    Gfx_DrawDListOpa(globalCtx, D_80B19A94[this->params - 3]);
}
