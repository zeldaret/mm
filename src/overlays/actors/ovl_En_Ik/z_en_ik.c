/*
 * File: z_en_ik.c
 * Overlay: ovl_En_Ik
 * Description: Iron Knuckle
 */

#include "z_en_ik.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_400)

#define THIS ((EnIk*)thisx)

void EnIk_Init(Actor* thisx, GlobalContext* globalCtx);
void EnIk_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnIk_Update(Actor* thisx, GlobalContext* globalCtx);
void EnIk_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnIk_Thaw(EnIk* this, GlobalContext* globalCtx);
s32 func_80929C80(EnIk* this, GlobalContext* globalCtx);
s32 EnIk_DetermineAttack(EnIk* this);
void EnIk_CheckActions(EnIk* this, GlobalContext* globalCtx);
void func_80929E88(EnIk* this);
void func_80929F20(EnIk* this, GlobalContext* globalCtx);
void EnIk_SetupWalk(EnIk* this);
void EnIk_WalkTowardsPlayer(EnIk* this, GlobalContext* globalCtx);
void EnIk_SetupRun(EnIk* this);
void EnIk_RunTowardsPlayer(EnIk* this, GlobalContext* globalCtx);
void func_8092A28C(EnIk* this);
void func_8092A33C(EnIk* this, GlobalContext* globalCtx);
void EnIk_SetupPulloutAxe(EnIk* this);
void EnIk_PulloutAxe(EnIk* this, GlobalContext* globalCtx);
void EnIk_SetupHorizontalDoubleAttack(EnIk* this);
void EnIk_HorizontalDoubleAttack(EnIk* this, GlobalContext* globalCtx);
void func_8092A8D8(EnIk* this);
void func_8092A994(EnIk* this, GlobalContext* globalCtx);
void func_8092AA6C(EnIk* this);
void func_8092AB14(EnIk* this, GlobalContext* globalCtx);
void EnIk_SetupBlock(EnIk* this);
void EnIk_Block(EnIk* this, GlobalContext* globalCtx);
void func_8092AC4C(EnIk* this, s32 arg1);
void func_8092ACFC(EnIk* this, GlobalContext* globalCtx);
void EnIk_SetupDeath(EnIk* this);
void func_8092AE14(EnIk* this, GlobalContext* globalCtx);
void func_8092AFD4(EnIk* this, GlobalContext* globalCtx);
void EnIk_SetupCutscene(EnIk* this);
void EnIk_PlayCutscene(EnIk* this, GlobalContext* globalCtx);
void func_8092B1B4(EnIk* this, GlobalContext* globalCtx);
void EnIk_ArmorDestroyed(EnIk* this, GlobalContext* globalCtx);

typedef struct {
    Gfx* unk00;
    s16 unk04;
} EnIkUnkStruct;

EnIkUnkStruct D_8092BFA0[] = {
    { object_ik_DL_00CF08, 0x0000 }, { object_ik_DL_00A5D8, 0x0000 }, { object_ik_DL_00A6D0, 0x7FFF },
    { object_ik_DL_00A820, 0x4000 }, { object_ik_DL_00A780, 0xC000 }, { ((void*)0), 0x4000 },
    { ((void*)0), 0xC000 },
};

static Gfx* D_8092BFD8[3][3] = {
    { object_ik_DL_00D038, object_ik_DL_00D050, object_ik_DL_00D068 },
    { object_ik_DL_00D080, object_ik_DL_00D098, object_ik_DL_00D098 },
    { object_ik_DL_00D0B0, object_ik_DL_00D0C8, object_ik_DL_00D0C8 },
};

const ActorInit En_Ik_InitVars = {
    ACTOR_EN_IK,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_IK,
    sizeof(EnIk),
    (ActorFunc)EnIk_Init,
    (ActorFunc)EnIk_Destroy,
    (ActorFunc)EnIk_Update,
    (ActorFunc)EnIk_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_METAL,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK2,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON | BUMP_HOOKABLE,
        OCELEM_ON,
    },
    { 25, 80, 0, { 0, 0, 0 } },
};

static ColliderTrisElementInit sTrisElementsInit[2] = {
    {
        {
            ELEMTYPE_UNK2,
            { 0x00000000, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { -10.0f, 14.0f, 2.0f }, { -10.0f, -6.0f, 2.0f }, { 9.0f, 14.0f, 2.0f } } },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0x00000000, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { -10.0f, -6.0f, 2.0f }, { 9.0f, -6.0f, 2.0f }, { 9.0f, 14.0f, 2.0f } } },
    },
};

static ColliderTrisInit sTrisInit = {
    {
        COLTYPE_METAL,
        AT_NONE,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_TYPE_2,
        COLSHAPE_TRIS,
    },
    2,
    sTrisElementsInit,
};

static ColliderQuadInit sQuadInit = {
    {
        COLTYPE_NONE,
        AT_NONE | AT_TYPE_ENEMY,
        AC_NONE,
        OC1_NONE,
        OC2_TYPE_2,
        COLSHAPE_QUAD,
    },
    {
        ELEMTYPE_UNK0,
        { 0x20000000, 0x04, 0x40 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL | TOUCH_UNK7,
        BUMP_NONE,
        OCELEM_NONE,
    },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

static DamageTable sDamageTableArmor = {
    /* Deku Nut       */ DMG_ENTRY(0, 0xF),
    /* Deku Stick     */ DMG_ENTRY(0, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(0, 0xF),
    /* Normal arrow   */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(2, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(3, 0x0),
    /* Fire arrow     */ DMG_ENTRY(0, 0xF),
    /* Ice arrow      */ DMG_ENTRY(0, 0xF),
    /* Light arrow    */ DMG_ENTRY(1, 0x4),
    /* Goron spikes   */ DMG_ENTRY(0, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0xF),
    /* Deku bubble    */ DMG_ENTRY(0, 0xF),
    /* Deku launch    */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0xF),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(0, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};

static DamageTable sDamageTableNoArmor = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(2, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(3, 0x0),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
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

static CollisionCheckInfoInit sColChkInfoInit = { 18, 25, 80, MASS_HEAVY };

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(targetArrowOffset, 2916, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 12, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -1000, ICHAIN_STOP),
};

static EffectBlureInit2 D_8092C174 = {
    0, 8, 0, { 255, 255, 150, 200 }, { 255, 255, 255, 64 }, { 255, 255, 150, 0 }, { 255, 255, 255, 0 }, 8,
    0, 2, 0, { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
};

static s32 D_8092C198 = 0;

Vec3f D_8092C19C = { 0.0f, 0.5f, 0.0f };

s8 D_8092C1A8[] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0,  -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, 3,  5,  4,  6,  1,  2,  -1, -1, 0,  0 };

Vec3f D_8092C1C8 = { 2000.0f, -200.0f, -5200.0f };

Vec3f D_8092C1D4 = { 300.0f, -200.0f, 0.0f };

s8 D_8092C1E0[] = { -1, -1, -1, 0,  1, 2,  3,  4,  5,  -1, -1, -1, 6,  -1, -1, 7,
                    -1, -1, 8,  -1, 9, 10, -1, 11, -1, 12, -1, -1, -1, -1, 0,  0 };

Vec3f D_8092C200 = { 0.52999997139f, 0.52999997139f, 0.52999997139f };

typedef enum {
    /* 00 */ IK_DRAW_EFFECT_THAW,
    /* 10 */ IK_DRAW_EFFECT_FROZEN = 10,
    /* 20 */ IK_DRAW_EFFECT_LIGHT_ORBS = 20,
} EnIkDrawEffectType;

void EnIk_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 i;
    EnIk* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gIronKnuckleSkel, &gIronKnuckleWalkAnim, this->jointTable,
                       this->morphTable, IRON_KNUCKLE_LIMB_MAX);
    Collider_InitAndSetCylinder(globalCtx, &this->colliderCylinder, &this->actor, &sCylinderInit);
    Collider_UpdateCylinder(&this->actor, &this->colliderCylinder);
    Collider_InitAndSetTris(globalCtx, &this->colliderTris, &this->actor, &sTrisInit, this->shieldColliderItems);
    Collider_InitAndSetQuad(globalCtx, &this->colliderQuad, &this->actor, &sQuadInit);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &sDamageTableArmor, &sColChkInfoInit);
    this->actor.params &= IK_PARAMS_FF;
    this->actor.params -= IK_PARAMS_01;

    Effect_Add(globalCtx, &this->effectIndex, EFFECT_BLURE2, 0, 0, &D_8092C174);
    if (!D_8092C198) {

        for (i = 0; i < ARRAY_COUNT(D_8092BFD8); i++) {
            D_8092BFD8[i][0] = Lib_SegmentedToVirtual(D_8092BFD8[i][0]);
            D_8092BFD8[i][1] = Lib_SegmentedToVirtual(D_8092BFD8[i][1]);
            D_8092BFD8[i][2] = Lib_SegmentedToVirtual(D_8092BFD8[i][2]);
        }
        D_8092C198 = true;
    }
    func_80929E88(this);
}

void EnIk_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnIk* this = THIS;

    Collider_DestroyTris(globalCtx, &this->colliderTris);
    Collider_DestroyCylinder(globalCtx, &this->colliderCylinder);
    Collider_DestroyQuad(globalCtx, &this->colliderQuad);
    Effect_Destroy(globalCtx, this->effectIndex);
}

void EnIk_Frozen(EnIk* this) {
    this->drawEffect = IK_DRAW_EFFECT_FROZEN;
    this->effectScale = 0.65f;
    this->unk_30C = 0.97499996f;
    this->effectAlpha = 1.0f;
    this->counter = 80;
    this->actor.flags &= ~ACTOR_FLAG_400;
    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 80);
}

void EnIk_Thaw(EnIk* this, GlobalContext* globalCtx) {
    if (this->drawEffect == IK_DRAW_EFFECT_FROZEN) {
        this->drawEffect = IK_DRAW_EFFECT_THAW;
        this->effectAlpha = 0.0f;
        Actor_SpawnIceEffects(globalCtx, &this->actor, this->limbPos, ARRAY_COUNT(this->limbPos), 2, 0.3f, 0.2f);
        this->actor.flags |= ACTOR_FLAG_400;
    }
}

void EnIk_HitArmor(EnIk* this, GlobalContext* globalCtx) {
    this->effectAlpha = 4.0f;
    this->effectScale = 0.65f;
    this->drawEffect = 20;
    Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, this->colliderCylinder.info.bumper.hitPos.x,
                this->colliderCylinder.info.bumper.hitPos.y, this->colliderCylinder.info.bumper.hitPos.z, 0, 0, 0, 4);
}

s32 func_80929C80(EnIk* this, GlobalContext* globalCtx) {
    if ((this->drawArmorFlags != 0) && (this->actionFunc != EnIk_Block) &&
        (func_800BE184(globalCtx, &this->actor, 100.0f, 0x2710, 0x4000, this->actor.shape.rot.y) != 0)) {
        EnIk_SetupBlock(this);
        return true;
    }
    return false;
}

s32 EnIk_DetermineAttack(EnIk* this) {
    s16 yawDiff;
    s32 phi_a2;
    s32 phi_v1;

    if ((this->actor.xzDistToPlayer < 100.0f) && (fabsf(this->actor.playerHeightRel) < 150.0f)) {

        phi_a2 = (this->drawArmorFlags == 0) ? 0xAAA : 0x3FFC;
        yawDiff = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
        phi_v1 = ABS_ALT(yawDiff);

        if (phi_a2 >= phi_v1) {
            if (Rand_ZeroOne() < 0.5f) {
                func_8092A28C(this);
                return true;
            }
            EnIk_SetupHorizontalDoubleAttack(this);
            return true;
        } else if ((this->drawArmorFlags != 0) || ((phi_v1 > 0x4000) && (Rand_ZeroOne() < 0.1f))) {
            func_8092A8D8(this);
            return true;
        }
    }
    return false;
}

// check actions before move?
void EnIk_CheckActions(EnIk* this, GlobalContext* globalCtx) {
    if (!func_80929C80(this, globalCtx) && !EnIk_DetermineAttack(this)) {
        if (this->drawArmorFlags != 0) {
            EnIk_SetupRun(this);
        } else {
            EnIk_SetupWalk(this);
        }
    }
}

void func_80929E88(EnIk* this) {
    f32 frameCount = Animation_GetLastFrame(&gIronKnuckleHorizontalDoubleAttackAnim);

    if (this->drawArmorFlags != 0) {
        this->counter = 10;
    } else {
        this->counter = 0;
    }
    Animation_Change(&this->skelAnime, &gIronKnuckleEndHorizontalAttackAnim, 1.0f, frameCount, frameCount, 2,
                     this->counter);
    this->actionFunc = func_80929F20;
    this->actor.speedXZ = 0.0f;
}

void func_80929F20(EnIk* this, GlobalContext* globalCtx) {
    if (this->counter > 0) {
        this->counter--;
        SkelAnime_Update(&this->skelAnime);
        if (this->counter == 0) {
            EnIk_CheckActions(this, globalCtx);
        }
    } else if ((this->colliderCylinder.base.acFlags & AC_HIT)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_IRONNACK_ARMOR_HIT);
        func_801A2E54(NA_BGM_MINI_BOSS);
        this->actor.hintId = 0x35;
        this->colliderCylinder.base.acFlags &= ~AC_HIT;
        this->invincibilityFrames = 12;
        EnIk_SetupWalk(this);
    }
}

void EnIk_SetupWalk(EnIk* this) {
    Animation_MorphToLoop(&this->skelAnime, &gIronKnuckleWalkAnim, -4.0f);
    this->actor.speedXZ = 0.9f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = EnIk_WalkTowardsPlayer;
}

void EnIk_WalkTowardsPlayer(EnIk* this, GlobalContext* globalCtx) {
    s16 temp_a1;

    SkelAnime_Update(&this->skelAnime);
    if ((Animation_OnFrame(&this->skelAnime, 0.0f)) || (Animation_OnFrame(&this->skelAnime, 16.0f))) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_IRONNACK_WALK);
    }
    temp_a1 = this->actor.wallYaw - this->actor.shape.rot.y;
    if ((this->actor.bgCheckFlags & 8) && (ABS_ALT(temp_a1) >= 0x4000)) {
        temp_a1 = (this->actor.yawTowardsPlayer > 0) ? this->actor.wallYaw - 0x4000 : this->actor.wallYaw + 0x4000;
        Math_ScaledStepToS(&this->actor.shape.rot.y, temp_a1, 0x320);
    } else {
        Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x320);
    }
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (func_80929C80(this, globalCtx) == 0) {
        EnIk_DetermineAttack(this);
    }
}

void EnIk_SetupRun(EnIk* this) {
    Animation_MorphToLoop(&this->skelAnime, &gIronKnuckleRunAnim, -4.0f);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_TWINROBA_SHOOT_VOICE);
    this->actor.speedXZ = 2.5f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = EnIk_RunTowardsPlayer;
}

void EnIk_RunTowardsPlayer(EnIk* this, GlobalContext* globalCtx) {
    s16 temp_a1;

    SkelAnime_Update(&this->skelAnime);
    if ((Animation_OnFrame(&this->skelAnime, 2.0f) != 0) || (Animation_OnFrame(&this->skelAnime, 9.0f) != 0)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_IRONNACK_WALK);
    }
    temp_a1 = this->actor.wallYaw - this->actor.shape.rot.y;
    if ((this->actor.bgCheckFlags & 8) && (ABS_ALT(temp_a1) >= 0x4000)) {
        temp_a1 = (this->actor.yawTowardsPlayer > 0) ? this->actor.wallYaw - 0x4000 : this->actor.wallYaw + 0x4000;
        Math_ScaledStepToS(&this->actor.shape.rot.y, temp_a1, 0x4B0);
    } else {
        Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x4B0);
    }
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (func_80929C80(this, globalCtx) == 0) {
        EnIk_DetermineAttack(this);
    }
}

void func_8092A28C(EnIk* this) {
    s32 pad;
    f32 playbackSpeed;

    this->actor.speedXZ = 0.0f;
    if (this->drawArmorFlags != 0) {
        playbackSpeed = 1.5f;
    } else {
        playbackSpeed = 1.2f;
    }
    Animation_Change(&this->skelAnime, &gIronKnuckleVerticleAttackAnim, playbackSpeed, 0.0f,
                     Animation_GetLastFrame(&gIronKnuckleVerticleAttackAnim.common), 3, -4.0f);
    this->counter = 0;
    this->unk_2F8 = -1;
    this->actionFunc = func_8092A33C;
}

void func_8092A33C(EnIk* this, GlobalContext* globalCtx) {
    Vec3f sp2C;

    this->counter++;
    if (!(this->skelAnime.curFrame < 7.0f) || !func_80929C80(this, globalCtx)) {
        if (Animation_OnFrame(&this->skelAnime, 15.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_IRONNACK_SWING_AXE);

        } else if (Animation_OnFrame(&this->skelAnime, 21.0f) != 0) {
            sp2C.x = (Math_SinS((this->actor.shape.rot.y + 0x6A4)) * 70.0f) + this->actor.world.pos.x;
            sp2C.z = (Math_CosS((this->actor.shape.rot.y + 0x6A4)) * 70.0f) + this->actor.world.pos.z;
            sp2C.y = this->actor.world.pos.y;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_IRONNACK_HIT_GND);
            func_800DFD04(globalCtx->cameraPtrs[globalCtx->activeCamera], 2, 25, 5);
            func_8013ECE0(this->actor.xyzDistToPlayerSq, 180, 20, 100);
            CollisionCheck_SpawnShieldParticles(globalCtx, &sp2C);
        }

        if ((this->skelAnime.curFrame > 13.0f) && (this->skelAnime.curFrame < 23.0f)) {
            this->colliderQuad.base.atFlags |= AT_ON;
            if (this->drawArmorFlags != 0) {
                this->actor.speedXZ = sin_rad((this->skelAnime.curFrame - 13.0f) * (M_PI / 20)) * 10.0f;
            }
        } else {
            this->colliderQuad.base.atFlags &= ~AT_ON;
            this->actor.speedXZ = 0.0f;
        }

        if ((this->drawArmorFlags != 0) && (this->skelAnime.curFrame < 13.0f)) {
            Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x5DC);
            this->actor.world.rot.y = this->actor.shape.rot.y;
        }

        if (SkelAnime_Update(&this->skelAnime)) {
            EnIk_SetupPulloutAxe(this);
        }
    }
}

void EnIk_SetupPulloutAxe(EnIk* this) {
    Animation_PlayOnce(&this->skelAnime, &gIronKnuckleEndVerticleAttackAnim);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_IRONNACK_PULLOUT);
    this->actionFunc = EnIk_PulloutAxe;
}

void EnIk_PulloutAxe(EnIk* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->skelAnime.animation == &gIronkKnuckleRecoverVerticleAttackAnim) {
            EnIk_CheckActions(this, globalCtx);
        } else {
            Animation_Change(&this->skelAnime, &gIronkKnuckleRecoverVerticleAttackAnim,
                             (this->drawArmorFlags != 0) ? 1.5f : 1.0f, 0.0f,
                             Animation_GetLastFrame(&gIronkKnuckleRecoverVerticleAttackAnim.common), 3, 0.0f);
        }
    }
}

void EnIk_SetupHorizontalDoubleAttack(EnIk* this) {
    this->actor.speedXZ = 0.0f;
    // If the armor has been knocked off animation is sped up
    Animation_Change(&this->skelAnime, &gIronKnuckleHorizontalDoubleAttackAnim, (this->drawArmorFlags != 0) ? 1.3f : 1.0f,
                     0.0f, Animation_GetLastFrame(&gIronKnuckleHorizontalDoubleAttackAnim.common), 3,
                     (this->drawArmorFlags != 0) ? 4.0f : 10.0f);
    this->counter = 0;
    this->unk_2F8 = -1;
    this->actionFunc = EnIk_HorizontalDoubleAttack;
}

void EnIk_HorizontalDoubleAttack(EnIk* this, GlobalContext* globalCtx) {
    f32 phi_f2;

    this->counter++;
    if ((Animation_OnFrame(&this->skelAnime, 1.0f)) || (Animation_OnFrame(&this->skelAnime, 13.0f))) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_IRONNACK_SWING_AXE);
    }
    if (((this->skelAnime.curFrame > 1.0f) && (this->skelAnime.curFrame < 9.0f)) ||
        ((this->skelAnime.curFrame > 12.0f) && (this->skelAnime.curFrame < 20.0f))) {
        if (this->drawArmorFlags != 0) {
            Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x5DC);
            this->actor.world.rot.y = this->actor.shape.rot.y;
            if (this->skelAnime.curFrame > 12.0f) {
                phi_f2 = this->skelAnime.curFrame - 12.0f;
            } else {
                phi_f2 = this->skelAnime.curFrame - 1.0f;
            }
            this->actor.speedXZ = sin_rad((M_PI / 8) * phi_f2) * 4.5f;
        }
        this->colliderQuad.base.atFlags |= AT_ON;
    } else {
        this->colliderQuad.base.atFlags &= ~AT_ON;
        this->actor.speedXZ = 0.0f;
    }
    if (SkelAnime_Update(&this->skelAnime) != 0) {
        func_8092AA6C(this);
    }
}

void func_8092A8D8(EnIk* this) {
    f32 phi_f0;

    this->actor.speedXZ = 0.0f;
    if (this->drawArmorFlags != 0) {
        this->actor.world.rot.z = 0x1000;
        phi_f0 = 1.3f;
    } else {
        this->actor.world.rot.z = 0xB00;
        phi_f0 = 1.0f;
    }
    Animation_Change(&this->skelAnime, &gIronKnuckleHorizontalDoubleAttackAnim, phi_f0, 12.0f,
                     Animation_GetLastFrame(&gIronKnuckleHorizontalDoubleAttackAnim.common), 3, 5.0f);
    this->counter = 0;
    this->unk_2F8 = -1;
    this->actionFunc = func_8092A994;
}

void func_8092A994(EnIk* this, GlobalContext* globalCtx) {
    this->counter++;
    if (Animation_OnFrame(&this->skelAnime, 13.0f) != 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_IRONNACK_SWING_AXE);
    }
    if ((this->skelAnime.curFrame > 12.0f) && (this->skelAnime.curFrame < 20.0f)) {
        this->colliderQuad.base.atFlags |= AT_ON;
    } else {
        this->colliderQuad.base.atFlags &= ~AT_ON;
    }
    this->actor.shape.rot.y += this->actor.world.rot.z;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (SkelAnime_Update(&this->skelAnime) != 0) {
        func_8092AA6C(this);
    }
}

void func_8092AA6C(EnIk* this) {
    Animation_Change(&this->skelAnime, &gIronKnuckleEndHorizontalAttackAnim, (this->drawArmorFlags != 0) ? 2.0f : 1.0f, 0.0f,
                     Animation_GetLastFrame(&gIronKnuckleHorizontalDoubleAttackAnim), 3, -4.0f);
    this->actionFunc = func_8092AB14;
}

void func_8092AB14(EnIk* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        EnIk_CheckActions(this, globalCtx);
    }
}

void EnIk_SetupBlock(EnIk* this) {
    this->actor.speedXZ = 0.0f;
    Animation_Change(&this->skelAnime, &gIronKnuckleBlockAnim, 2.0f, 0.0f,
                     Animation_GetLastFrame(&gIronKnuckleBlockAnim), 2, -2.0f);
    this->counter = 20;
    this->actionFunc = EnIk_Block;
}

void EnIk_Block(EnIk* this, GlobalContext* globalCtx) {
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliderTris.base);
    if (SkelAnime_Update(&this->skelAnime)) {
        this->counter--;
        if (this->counter == 0) {
            EnIk_CheckActions(this, globalCtx);
        }
    }
}

void func_8092AC4C(EnIk* this, s32 arg1) {
    s16 temp_v0;

    if (arg1 != 0) {
        func_800BE504(&this->actor, &this->colliderCylinder);
    }
    this->actor.speedXZ = 6.0f;
    temp_v0 = (this->actor.world.rot.y - this->actor.shape.rot.y) + 0x8000;
    if (ABS_ALT(temp_v0) <= 0x4000) {
        Animation_MorphToPlayOnce(&this->skelAnime, &gIronKuckleFrontHitAnim, -4.0f);
    } else {
        Animation_MorphToPlayOnce(&this->skelAnime, &gIronKuckleBackHitAnim, -4.0f);
    }
    this->actionFunc = func_8092ACFC;
}

void func_8092ACFC(EnIk* this, GlobalContext* globalCtx) {
    Math_StepToF(&this->actor.speedXZ, 0.0f, 1.0f);
    if (this->subCamId != CAM_ID_MAIN) {
        Play_CameraSetAtEye(globalCtx, this->subCamId, &this->actor.focus.pos,
                            &Play_GetCamera(globalCtx, this->subCamId)->eye);
    }
    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->subCamId != CAM_ID_MAIN) {
            ActorCutscene_Stop(this->actor.cutscene);
            this->subCamId = CAM_ID_MAIN;
            func_80929E88(this);
        } else {
            EnIk_CheckActions(this, globalCtx);
        }
    } else {
        this->actor.colorFilterTimer = 12;
        this->invincibilityFrames = 12;
    }
}

void EnIk_SetupDeath(EnIk* this) {
    this->actor.speedXZ = 0.0f;
    Animation_MorphToPlayOnce(&this->skelAnime, &gIronKnuckleDeathAnim, -4.0f);
    this->counter = 24;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_IRONNACK_DEAD);
    this->actionFunc = func_8092AE14;
}

void func_8092AE14(EnIk* this, GlobalContext* globalCtx) {
    s32 i;
    Vec3f effectPos;

    this->invincibilityFrames = 12;
    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->counter == 24) {
            SoundSource_PlaySfxEachFrameAtFixedWorldPos(globalCtx, &this->actor.world.pos, 35,
                                                        NA_SE_EN_COMMON_EXTINCT_LEV - SFX_FLAG);
        }

        if (this->counter != 0) {
            this->counter--;
            for (i = 6 - (this->counter >> 2); i >= 0; i--) {
                effectPos.x = randPlusMinusPoint5Scaled(80.0f) + this->actor.world.pos.x;
                effectPos.z = randPlusMinusPoint5Scaled(80.0f) + this->actor.world.pos.z;
                effectPos.y = randPlusMinusPoint5Scaled(50.0f) + (this->actor.world.pos.y + 20.0f);
                func_800B3030(globalCtx, &effectPos, &D_8092C19C, &D_8092C19C, 100, 0, 2);
            }
            if (this->counter == 0) {
                Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.world.pos, 0xB0);
                ActorCutscene_Stop(this->actor.cutscene);
                Actor_MarkForDeath(&this->actor);
            }
        }
        return;
    }
    if (Animation_OnFrame(&this->skelAnime, 23.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_IRONNACK_WALK);
    }
}

void func_8092AFB4(EnIk* this) {
    this->invincibilityFrames = 0;
    this->actionFunc = func_8092AFD4;
    this->actor.speedXZ = 0.0f;
}

void func_8092AFD4(EnIk* this, GlobalContext* globalCtx) {
    if (this->counter) {
        this->counter--;
    }
    if (this->counter == 0) {
        EnIk_Thaw(this, globalCtx);
        if (this->actor.colChkInfo.health == 0) {
            EnIk_SetupCutscene(this);
        } else {
            EnIk_CheckActions(this, globalCtx);
        }
    }
}

void EnIk_SetupCutscene(EnIk* this) {
    ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    this->actor.speedXZ = 0.0f;
    if (this->actor.colChkInfo.health != 0) {
        func_800BE504(&this->actor, &this->colliderCylinder);
    }
    this->actionFunc = EnIk_PlayCutscene;
}

void EnIk_PlayCutscene(EnIk* this, GlobalContext* globalCtx) {
    Vec3f subCamEye;

    this->invincibilityFrames = 12;
    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene) != 0) {
        if (this->actor.cutscene != -1) {
            ActorCutscene_StartAndSetFlag(this->actor.cutscene, &this->actor);
            this->subCamId = ActorCutscene_GetCurrentCamera(this->actor.cutscene);
            subCamEye.x = (Math_SinS((this->actor.shape.rot.y - 0x2000)) * 120.0f) + this->actor.focus.pos.x;
            subCamEye.y = this->actor.focus.pos.y + 20.0f;
            subCamEye.z = (Math_CosS((this->actor.shape.rot.y - 0x2000)) * 120.0f) + this->actor.focus.pos.z;
            Play_CameraSetAtEye(globalCtx, this->subCamId, &this->actor.focus.pos, &subCamEye);
        }
        if (this->actor.colChkInfo.health != 0) {
            func_8092AC4C(this, 0);
        } else {
            EnIk_SetupDeath(this);
        }
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void func_8092B1B4(EnIk* this, GlobalContext* globalCtx) {
    s32 pad;
    f32 pad2;
    s32 sp2C;

    if (this->actionFunc == func_80929F20) {
        return;
    }
    if (this->colliderTris.base.acFlags & AC_BOUNCED) {
        f32 sin = Animation_GetLastFrame(&gIronKnuckleBlockAnim) - 2.0f;
        if (this->skelAnime.curFrame < sin) {
            this->skelAnime.curFrame = sin;
        }
        this->colliderTris.base.acFlags &= ~AC_BOUNCED;
        this->colliderCylinder.base.acFlags &= ~AC_HIT;
    } else if ((this->colliderCylinder.base.acFlags & AC_HIT)) {
        sp2C = 0;
        Actor_SetDropFlag(&this->actor, &this->colliderCylinder.info);
        this->colliderCylinder.base.acFlags &= ~AC_HIT;
        if ((this->actor.colChkInfo.damageEffect != 15) &&
            ((this->drawEffect != 10) || ((this->colliderCylinder.info.acHitInfo->toucher.dmgFlags & 0xDB0B3) == 0))) {
            Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 12);
            this->invincibilityFrames = 12;
            EnIk_Thaw(this, globalCtx);
            this->colliderQuad.base.atFlags &= ~AT_ON;
            if (Actor_ApplyDamage(&this->actor) == 0) {
                if (this->drawArmorFlags == 0) {
                    this->actor.colChkInfo.health = 9;
                    sp2C = 1;
                } else {
                    Enemy_StartFinishingBlow(globalCtx, &this->actor);
                    func_801A2ED8();
                }
            }
            if (sp2C == 1) {
                this->drawArmorFlags = 1;
                this->colliderCylinder.base.colType = 3;
                this->actor.colChkInfo.damageTable = &sDamageTableNoArmor;
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_IRONNACK_ARMOR_OFF_DEMO);
                EnIk_SetupCutscene(this);
            } else if (this->drawArmorFlags) {
                if (this->actor.colChkInfo.damageEffect == 3) {
                    EnIk_Frozen(this);
                    func_8092AFB4(this);
                    if (this->actor.colChkInfo.health == 0) {
                        this->counter = 3;
                        this->invincibilityFrames = 12;
                    }
                } else {
                    if (this->actor.colChkInfo.damageEffect == 2) {
                        this->effectAlpha = 4.0f;
                        this->effectScale = 0.65f;
                        this->drawEffect = 0;
                    } else if (this->actor.colChkInfo.damageEffect == 4) {
                        EnIk_HitArmor(this, globalCtx);
                    }
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_IRONNACK_DAMAGE);
                    if (this->actor.colChkInfo.health != 0) {
                        func_8092AC4C(this, 1);
                    } else {
                        EnIk_SetupCutscene(this);
                    }
                }
            } else {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_IRONNACK_ARMOR_HIT);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_IRONNACK_DAMAGE);
                if (this->actor.colChkInfo.damageEffect == 4) {
                    EnIk_HitArmor(this, globalCtx);
                }
            }
        }
    }
}

void EnIk_ArmorDestroyed(EnIk* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 i;
    EnIkStruct* ptr;
    Vec3f effectPos;

    for (i = 0; i < ARRAY_COUNT(this->unk_550); i++) {
        ptr = &this->unk_550[i];

        if (ptr->unk_24 != 0) {
            Math_Vec3f_Sum(&ptr->unk_04, &ptr->unk_10, &ptr->unk_04);
            ptr->unk_10.y += -1.5f;
            if (ptr->unk_04.y < this->actor.floorHeight) {
                ptr->unk_24 = 0;
                ptr->unk_04.y = this->actor.floorHeight;

                for (i = 0; i < 4; i++) {
                    effectPos.x = randPlusMinusPoint5Scaled(20.0f) + ptr->unk_04.x;
                    effectPos.y = Rand_ZeroFloat(20.0f) + ptr->unk_04.y;
                    effectPos.z = randPlusMinusPoint5Scaled(20.0f) + ptr->unk_04.z;
                    func_800B3030(globalCtx, &effectPos, &gZeroVec3f, &gZeroVec3f, 40, 7, 2);
                }

                SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &ptr->unk_04, 11, NA_SE_EN_EXTINCT);
            }
        }
    }
}

void EnIk_Update(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnIk* this = THIS;

    if (this->actionFunc != EnIk_PlayCutscene) {
        func_8092B1B4(this, globalCtx);
    } else {
        this->colliderTris.base.acFlags &= ~0x80;
        this->colliderCylinder.base.acFlags &= ~AC_HIT;
    }
    this->actionFunc(this, globalCtx);
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 75.0f, 30.0f, 30.0f, 0x1D);
    this->actor.focus.rot.y = this->actor.shape.rot.y;
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderCylinder.base);
    if (this->invincibilityFrames == 0) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliderCylinder.base);
    } else {
        this->invincibilityFrames--;
    }
    if (this->colliderQuad.base.atFlags & AT_ON) {
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->colliderQuad.base);
    }
    if (this->actionFunc == EnIk_Block) {
        f32 cos;
        f32 sin;
        Vec3f sp5C;
        Vec3f sp50;
        Vec3f sp44;

        cos = Math_CosS(this->actor.shape.rot.y);
        sin = Math_SinS(this->actor.shape.rot.y);

        sp44.x = (this->actor.world.pos.x - (30.0f * cos)) + (20.0f * sin);
        sp44.y = this->actor.world.pos.y;
        sp44.z = this->actor.world.pos.z + (30.0f * sin) + (20.0f * cos);

        sp50.x = this->actor.world.pos.x + (30.0f * cos) + (20.0f * sin);
        sp50.y = this->actor.world.pos.y + 80.0f;
        sp50.z = (this->actor.world.pos.z - (30.0f * sin)) + (20.0f * cos);

        sp5C.x = sp44.x;
        sp5C.y = sp50.y;
        sp5C.z = sp44.z;

        Collider_SetTrisVertices(&this->colliderTris, 0, &sp44, &sp50, &sp5C);
        sp5C.x = sp50.x;
        sp5C.y = sp44.y;
        sp5C.z = sp50.z;
        Collider_SetTrisVertices(&this->colliderTris, 1, &sp44, &sp5C, &sp50);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliderTris.base);
    }
    if (this->effectAlpha > 0.0f) {
        if (this->drawEffect != 10) {
            Math_StepToF(&this->effectAlpha, 0.0f, 0.05f);
            this->effectScale = (this->effectAlpha + 1.0f) * 0.325f;
            if ((this->effectAlpha + 1.0f) * 0.325f > 0.65f) {
                this->effectScale = 0.65f;
            } else {
                this->effectScale = this->effectScale;
            }
        } else if (Math_StepToF(&this->unk_30C, 0.65f, 0.01625f) == 0) {
            func_800B9010(&this->actor, NA_SE_EV_ICE_FREEZE - SFX_FLAG);
        }
    }
    EnIk_ArmorDestroyed(this, globalCtx);
}

s32 EnIk_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnIk* this = THIS;

    if (this->drawArmorFlags != 0) {
        if (D_8092C1A8[limbIndex] > 0) {
            *dList = NULL;
        }
    }
    return false;
}

void EnIk_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnIk* this = THIS;
    s32 sp80 = D_8092C1A8[limbIndex];
    Gfx* tmp;
    EnIkStruct* ptr;
    s16 sp76;
    Vec3f sp68;
    Vec3f sp5C;
    Vec3f sp50;
    Vec3f sp44;
    MtxF* mtfxPtr;

    if (this->drawArmorFlags == 0x1) {
        if (sp80 > 0) {
            ptr = &this->unk_550[sp80];
            mtfxPtr = Matrix_GetCurrentState();
            ptr->unk_04.x = mtfxPtr->mf[3][0];
            ptr->unk_04.y = mtfxPtr->mf[3][1];
            ptr->unk_04.z = mtfxPtr->mf[3][2];
            func_8018219C(mtfxPtr, &ptr->unk_1C, 0);
            ptr->unk_24 = 1;
            sp76 = D_8092BFA0[sp80].unk04 + ((Rand_Next() >> 0x13) + this->actor.shape.rot.y);
            ptr->unk_10.x = Math_SinS(sp76) * 5.0f;
            ptr->unk_10.y = 6.0f;
            ptr->unk_10.z = Math_CosS(sp76) * 5.0f;
            ptr->unk_00 = *dList;
        }
        if (limbIndex == IRON_KNUCKLE_LIMB_WAIST) {
            this->drawArmorFlags |= 0x2;
        }
    }

    if (limbIndex == IRON_KNUCKLE_LIMB_ROOT) {
        Matrix_GetStateTranslation(&this->actor.focus.pos);
        this->colliderCylinder.dim.pos.x = this->actor.focus.pos.x;
        this->colliderCylinder.dim.pos.y = this->actor.world.pos.y;
        this->colliderCylinder.dim.pos.z = this->actor.focus.pos.z;
    }

    if ((limbIndex == IRON_KNUCKLE_LIMB_17) && (this->unk_2F8 != this->counter) &&
        ((this->actionFunc == func_8092A33C) || (this->actionFunc == EnIk_HorizontalDoubleAttack) ||
         (this->actionFunc == func_8092A994))) {
        Math_Vec3f_Copy(&sp68, this->colliderQuad.dim.quad);
        Math_Vec3f_Copy(&sp5C, &this->colliderQuad.dim.quad[1]);
        Matrix_MultiplyVector3fByState(&D_8092C1C8, &sp50);
        Matrix_MultiplyVector3fByState(&D_8092C1D4, &sp44);
        Collider_SetQuadVertices(&this->colliderQuad, &sp44, &sp50, &sp68, &sp5C);
        if ((this->colliderQuad.base.atFlags & 1)) {
            EffectBlure_AddVertex(Effect_GetByIndex(this->effectIndex), &sp50, &sp44);
        }
        this->unk_2F8 = this->counter;
    }

    if (D_8092C1E0[limbIndex] != -1) {
        Matrix_GetStateTranslation(&this->limbPos[D_8092C1E0[limbIndex]]);
    }

    if ((sp80 == 0) || ((sp80 != -1) && (this->drawArmorFlags == 0) && (D_8092BFA0[sp80].unk00 != 0))) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        tmp = POLY_XLU_DISP;

        gSPMatrix(&tmp[0], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(&tmp[1], D_8092BFA0[sp80].unk00);
        POLY_XLU_DISP = &tmp[2];

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

void En_IkUpdateArmorDraw(EnIk* this, GlobalContext* globalCtx) {
    Gfx* gfxOpa;
    Gfx* gfxXlu;
    s32 sp54;
    EnIkStruct* ptr;
    s32 i;

    if (this->drawArmorFlags == 3) {
        sp54 = 0;

        OPEN_DISPS(globalCtx->state.gfxCtx);
        gfxOpa = POLY_OPA_DISP;
        gfxXlu = POLY_XLU_DISP;

        for (i = 0; i < ARRAY_COUNT(this->unk_550); i++) {
            ptr = &this->unk_550[i];
            if (ptr->unk_24 != 0) {
                Matrix_SetStateRotationAndTranslation(ptr->unk_04.x, ptr->unk_04.y, ptr->unk_04.z, &ptr->unk_1C);
                Matrix_Scale(0.012f, 0.012f, 0.012f, 1);

                gSPMatrix(gfxOpa++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(gfxOpa++, ptr->unk_00);

                if (D_8092BFA0[i].unk00 != NULL) {
                    gSPMatrix(gfxXlu++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPDisplayList(gfxXlu++, D_8092BFA0[i].unk00);
                }
            } else {
                sp54++;
            }
        }

        if (sp54 == ARRAY_COUNT(this->unk_550)) {
            this->drawArmorFlags = 5;
        }

        POLY_XLU_DISP = gfxXlu;
        POLY_OPA_DISP = gfxOpa;

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

void EnIk_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnIk* this = THIS;
    Gfx* gfx;
    Gfx** temp_v1_2;
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_800B8050(&this->actor, globalCtx, 0);
    func_800B8118(&this->actor, globalCtx, 0);
    gfx = POLY_XLU_DISP;
    gSPDisplayList(&gfx[0], &sSetupDL[6 * 25]);
    POLY_XLU_DISP = &gfx[1];
    gfx = POLY_OPA_DISP;
    gSPDisplayList(&gfx[0], &sSetupDL[6 * 25]);
    temp_v1_2 = D_8092BFD8[this->actor.params];
    gSPSegment(&gfx[1], 0x08, temp_v1_2[0]);
    gSPSegment(&gfx[2], 0x09, temp_v1_2[1]);
    gSPSegment(&gfx[3], 0x0A, temp_v1_2[2]);
    POLY_OPA_DISP = &gfx[4];

    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnIk_OverrideLimbDraw, EnIk_PostLimbDraw, &this->actor);
    En_IkUpdateArmorDraw(this, globalCtx);
    if (this->actor.colorFilterTimer != 0) {
        func_800AE5A0(globalCtx);
    }
    func_800BC620(&this->actor.focus.pos, &D_8092C200, 255, globalCtx);
    func_800BE680(globalCtx, &this->actor, this->limbPos, ARRAY_COUNT(this->limbPos), this->effectScale, this->unk_30C,
                  this->effectAlpha, this->drawEffect);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
