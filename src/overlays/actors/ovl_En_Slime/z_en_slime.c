/*
 * File: z_en_slime.c
 * Overlay: ovl_En_Slime
 * Description: Chuchu
 */

#include "z_en_slime.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_200)

#define THIS ((EnSlime*)thisx)

void EnSlime_Init(Actor* thisx, PlayState* play);
void EnSlime_Destroy(Actor* thisx, PlayState* play);
void EnSlime_Update(Actor* thisx, PlayState* play);
void EnSlime_Draw(Actor* thisx, PlayState* play);

void func_80A2EFAC(EnSlime* this);
void func_80A2F028(EnSlime* this, PlayState* play);
void func_80A2F0A8(EnSlime* this); 

void func_80A2F110(EnSlime* this);
void func_80A2F140(EnSlime* this, PlayState* play); //Default action func
void func_80A2F180(EnSlime* this);    

void func_80A2F1A4(EnSlime* this, PlayState* play);
void func_80A2F354(EnSlime* this);
void func_80A2F418(EnSlime* this, PlayState* play);
void func_80A2F684(EnSlime* this);
void func_80A2F6CC(EnSlime* this, PlayState* play);
void func_80A2F8B4(EnSlime* this);
void func_80A2F8E0(EnSlime* this, PlayState* play);
void func_80A2F9A0(EnSlime* this);
void func_80A2FA88(EnSlime* this, PlayState* play);
void func_80A2FB60(EnSlime* this);
void func_80A2FBA0(EnSlime* this, PlayState* play);
void func_80A2FD94(EnSlime* this);
void func_80A2FE38(EnSlime* this, PlayState* play);
void func_80A30018(EnSlime* this, PlayState* play, s32 arg2);
void func_80A30344(EnSlime* this, PlayState* play); //Action func
void func_80A30454(EnSlime* this);
void func_80A304B8(EnSlime* this, PlayState* play);
f32 func_80A3072C(f32, f32);
void func_80A30778(EnSlime* this);
void func_80A30820(EnSlime* this, PlayState* play);
void func_80A30924(EnSlime* this);
void func_80A309C8(EnSlime* this);
void func_80A30944(EnSlime* this, PlayState* play);
void func_80A30A20(EnSlime* this, PlayState* play);
void func_80A30A90(EnSlime* this);
void func_80A30AE4(EnSlime* this, PlayState* play);
void func_80A30BE0(EnSlime* this);
void func_80A30C2C(EnSlime* this, PlayState* play);
void func_80A30C68(EnSlime* this);
void func_80A30CEC(EnSlime* this, PlayState* play); //Action func
void func_80A30F98(EnSlime* this, PlayState* play);

#if 0
const ActorInit En_Slime_InitVars = {
    ACTOR_EN_SLIME,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_SLIME,
    sizeof(EnSlime),
    (ActorFunc)EnSlime_Init,
    (ActorFunc)EnSlime_Destroy,
    (ActorFunc)EnSlime_Update,
    (ActorFunc)EnSlime_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A31AF0 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 22, 35, 0, { 0, 0, 0 } },
};

// static DamageTable sDamageTable = {
static DamageTable D_80A31B1C = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(3, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xE),
    /* Goron punch    */ DMG_ENTRY(0, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0x0),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(0, 0xF),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(1, 0x5),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0xF),
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
static CollisionCheckInfoInit D_80A31B3C = { 1, 22, 35, 60 };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A31B54[] = {
    ICHAIN_F32(gravity, -2, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 6000, ICHAIN_STOP),
};

#endif


extern u8 D_0405BEF0[];
extern u8 D_0405E6F0[];
extern u8 D_0405FFC0[];
extern u8 D_0405F6F0[];
extern UNK_TYPE D_060004C0;
extern u8 D_06000650[];
extern UNK_TYPE D_06000828;
extern u8 D_06000A10[];

extern void* D_80A31B44[];
extern s32 D_80A31B5C;
extern Color_RGBA8 D_80A31B60;
extern Color_RGBA8 D_80A31B64;
extern Vec3f D_80A31B68;

extern ColliderCylinderInit D_80A31AF0;
extern DamageTable D_80A31B1C;
extern CollisionCheckInfoInit D_80A31B3C;
extern InitChainEntry D_80A31B54[];

extern Color_RGBA8 D_80A31B74[];
extern Color_RGBA8 D_80A31B84[];
extern Vec3f D_80A31B94[];

extern void* D_80A32200;


void EnSlime_Init(Actor* thisx, PlayState* play) {
    s32 actorParamsHi;
    s32 i;
    EnSlime* this = THIS;

    Actor_ProcessInitChain(&this->actor, D_80A31B54);
    Collider_InitAndSetCylinder(play, &this->unk1BC, &this->actor, &D_80A31AF0);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &D_80A31B1C, &D_80A31B3C);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 38.0f);

    this->unk148 = 0xFF;
    this->unk149 = 0;
    this->unk158 = 0.0f;

    if (this->actor.shape.rot.x <= 0) {
        this->unk170 = 30000.0f;
    } else {
        this->unk170 = (f32)this->actor.shape.rot.x * 40.0f;
    }

    this->actor.shape.rot.x = 0;
    actorParamsHi = (this->actor.params >> 8) & 0xFF;
    this->actor.shape.rot.z = 0;
    this->actor.params = this->actor.params & 0xFF;
    if (actorParamsHi == 0xFF) {
        actorParamsHi = 0;
    }

    this->unk152 = (actorParamsHi * 0x14) + 0xC8;

    if (!D_80A31B5C) {
        for (i = 0; i < 4; i++) {
            D_80A31B44[i] = Lib_SegmentedToVirtual(D_80A31B44[i]);
        }
        D_80A32200 = Lib_SegmentedToVirtual(&D_06000828);
        D_80A31B5C = 1;
    }

    if (this->actor.params == 2) {
        this->unk160 = Lib_SegmentedToVirtual(&D_0405BEF0);
        this->actor.hintId = 0x22;
    } else if (this->actor.params == 1) {
        this->unk160 = Lib_SegmentedToVirtual(&D_0405FFC0);
        this->actor.hintId = 0x5D;
    } else if (this->actor.params == 3) {
        this->unk160 = Lib_SegmentedToVirtual(&D_0405E6F0);
        this->actor.hintId = 5;
    } else {
        this->actor.hintId = 6;
    }

    func_80A2F110(this);
}

void EnSlime_Destroy(Actor* thisx, PlayState* play) {
    EnSlime* this = THIS;
    Collider_DestroyCylinder(play, &this->unk1BC);
}

void func_80A2EFAC(EnSlime* this) {
    this->unk14A = 0xA;
    this->unk168 = 0.4f;
    this->unk1BC.base.colType = 3;
    this->unk16C = 0.6f;
    this->unk164 = 1.0f;
    this->unk14C = 0x50;
    this->actor.flags &= ~0x400;
    Actor_SetColorFilter(&this->actor, 0x4000, 0xFF, 0x2000, 0x50);
}

void func_80A2F028(EnSlime* this, PlayState* play) {
    if (this->unk14A == 0xA) {
        this->unk14A = 0;
        this->unk1BC.base.colType = 0xA;
        this->unk164 = 0.0f;
        Actor_SpawnIceEffects(play, &this->actor, this->unk180, 5, 2, 0.2f, 0.2f);
        this->actor.flags |= 0x200;
    }
}

void func_80A2F0A8(EnSlime* this) {
    if (this->unk149 != 0) {
        if (++this->unk149 == 4) {
            this->unk149 = 0;
        }
    } else if (Rand_ZeroOne() < 0.05f) {
        this->unk149 = 1;
    }
}

void func_80A2F110(EnSlime* this) {
    this->actor.scale.x = 0.008f;
    this->actor.scale.z = 0.008f;
    this->actor.scale.y = 0.011f;
    this->actionFunc = func_80A2F140;
}

void func_80A2F140(EnSlime* this, PlayState* play) {
    if (this->actor.bgCheckFlags & 1) {
        this->actor.flags &= ~0x10;
        func_80A2F180(this);
    }
}

void func_80A2F180(EnSlime* this) {
    this->unk14C = 0x19;
    this->actionFunc = func_80A2F1A4;
    this->actor.speedXZ = 0.0f;
}

void func_80A2F1A4(EnSlime* this, PlayState* play) {
    f32 temp_fs0;
    f32 temp_fv1;

    this->unk14C -= 1;
    temp_fs0 = sqrtf((f32)this->unk14C) * 0.2f;
    func_80A2F0A8(this);

    temp_fv1 = ((sin_rad(this->unk14C * 1.2566371f) * (0.13f * temp_fs0)) + 1.0f) * 0.01f;
    this->actor.scale.x = temp_fv1;
    this->actor.scale.z = temp_fv1;
    if (this->unk14C < 0x18) {
        this->actor.scale.y = ((cos_rad(this->unk14C * 1.2566371f) * (0.05f * temp_fs0)) + 1.0f) * 0.01f;
    }

    this->actor.shape.rot.x = randPlusMinusPoint5Scaled(512.0f) * temp_fs0;
    this->actor.shape.rot.z = randPlusMinusPoint5Scaled(512.0f) * temp_fs0;
    if ((Player_GetMask(play) != 0x10) && (this->actor.xzDistToPlayer < 280.0f) &&
        (Actor_IsFacingPlayer(&this->actor, 0x5000) != 0)) {
        func_80A2F8B4(this);
    } else if (this->unk14C == 0) {
        func_80A2F354(this);
    }
}

void func_80A2F354(EnSlime* this) {
    this->unk14C = 0x78;
    if (Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos) > 120.0f) {
        this->unk14E = Actor_YawToPoint(&this->actor, &this->actor.home.pos);
    } else if (Rand_ZeroOne() < 0.7f) {
        this->unk14E = (s32)randPlusMinusPoint5Scaled(16384.0f) + this->actor.shape.rot.y;
    }
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = func_80A2F418;
}

void func_80A2F418(EnSlime* this, PlayState* play) {
    f32 sp2C;

    func_80A2F0A8(this);
    this->unk14C--;
    Math_ApproachS(&this->actor.shape.rot.y, this->unk14E, 4, 0x100);
    if (this->actor.bgCheckFlags & 8) {
        this->unk14E = this->actor.wallYaw;
    } else {
        if (Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos) > 120.0f) {
            this->unk14E = Actor_YawToPoint(&this->actor, &this->actor.home.pos);
        }
    }
    sp2C = fabsf(sin_rad((f32)this->unk14C * 0.1308997f));
    Math_StepToF(&this->actor.scale.z, ((0.15f * sp2C) + 1.0f) * 0.01f, 0.0002f);
    Math_StepToF(&this->actor.scale.x, (1.0f - (0.2f * sp2C)) * 0.01f, 0.0002f);
    Math_StepToF(&this->actor.scale.y, (1.0f - (0.1f * sp2C)) * 0.01f, 0.0002f);

    this->actor.speedXZ = (0.8f * sp2C) + 0.2f;
    this->actor.shape.rot.x = (s16)(2048.0f * sp2C);
    this->actor.world.rot.y = this->actor.shape.rot.y;

    if (this->unk170 < Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos)) {
        func_80A2F684(this);
    } else if ((Player_GetMask(play) != 0x10) && (this->actor.xzDistToPlayer < 280.0f) &&
               (Actor_IsFacingPlayer(&this->actor, 0x5000))) {
        func_80A2F8B4(this);
    } else if (this->unk14C == 0) {
        func_80A2F180(this);
    }
}

void func_80A2F684(EnSlime* this) {
    this->unk14C = 0x18;
    this->unk14E = Actor_YawToPoint(&this->actor, &this->actor.home.pos);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = func_80A2F6CC;
}

void func_80A2F6CC(EnSlime* this, PlayState* play) {
    f32 temp_fs0;

    func_80A2F0A8(this);
    this->unk14C--;
    Math_ApproachS(&this->actor.shape.rot.y, this->unk14E, 4, 0x400);
    if (this->actor.bgCheckFlags & 8) {
        this->unk14E = this->actor.wallYaw;
    } else {
        this->unk14E = Actor_YawToPoint(&this->actor, &this->actor.home.pos);
    }

    temp_fs0 = fabsf(sin_rad((f32)this->unk14C * 0.1308997f));
    Math_StepToF(&this->actor.scale.z, ((0.15f * temp_fs0) + 1.0f) * 0.01f, 0.0002f);
    Math_StepToF(&this->actor.scale.x, (1.0f - (0.2f * temp_fs0)) * 0.01f, 0.0002f);
    Math_StepToF(&this->actor.scale.y, (1.0f - (0.1f * temp_fs0)) * 0.01f, 0.0002f);

    this->actor.speedXZ = (0.8f * temp_fs0) + 0.2f;
    this->actor.shape.rot.x = (s16)(s32)(2048.0f * temp_fs0);
    this->actor.world.rot.y = this->actor.shape.rot.y;

    if (this->unk14C == 0) {
        this->unk14C = 0x18;
    }
    if (Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos) < (this->unk170 * 0.8f)) {
        func_80A2F180(this);
    }
}

void func_80A2F8B4(EnSlime* this) {
    this->actor.shape.rot.x = 0;
    this->actor.shape.rot.z = 0;
    this->unk14C = 8;
    this->actionFunc = func_80A2F8E0;
    this->actor.speedXZ = 0.0f;
}

void func_80A2F8E0(EnSlime* this, PlayState* play) {
    f32 temp_fv0;
    f32 temp_fv1;

    this->unk14C -= 1;
    func_80A2F0A8(this);
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 4, 0x1000);
    // temp_v0 = this->unk14C;
    if (this->unk14C >= 0) {
        temp_fv0 = (f32)(8 - this->unk14C);
        temp_fv1 = ((temp_fv0 * 0.04f) + 1.0f) * 0.01f;
        this->actor.scale.x = temp_fv1;
        this->actor.scale.y = (1.0f - (temp_fv0 * 0.05f)) * 0.01f;
        this->actor.scale.z = temp_fv1;
    }
    if (this->unk14C < -2) {
        func_80A2F9A0(this);
    }
}

void func_80A2F9A0(EnSlime* this) {
    if (this->actor.xzDistToPlayer > 120.0f) {
        this->actor.velocity.y = 11.0f;
        this->actor.speedXZ = 5.0f;
        this->actor.gravity = -2.0f;
    } else {
        this->actor.velocity.y = 18.0f;
        this->actor.speedXZ = 7.0f;
        this->actor.gravity = -3.5f;
    }
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->unk14C = 0xC;
    this->unk149 = 0;
    Math_StepToF(&this->actor.scale.x, 0.008f, 0.0025f);
    Math_StepToF(&this->actor.scale.y, 0.011f, 0.0025f);
    this->actor.scale.z = this->actor.scale.x;
    Actor_PlaySfxAtPos(&this->actor, 0x38B9U);
    this->actionFunc = func_80A2FA88;
}

void func_80A2FA88(EnSlime* this, PlayState* play) {
    this->unk14C--;
    if (this->unk1BC.base.atFlags & 2) {
        if (this->actor.speedXZ > 0.0f) {
            this->actor.speedXZ *= -1.2f;
            this->unk1BC.base.atFlags &= 0xFFFD;
        }
    }
    Math_StepToF(&this->actor.scale.x, 0.008f, 0.0025f);
    Math_StepToF(&this->actor.scale.y, 0.011f, 0.0025f);
    this->actor.scale.z = this->actor.scale.x;
    if ((this->actor.velocity.y < 0.0f) && (this->actor.bgCheckFlags & 1)) {
        func_80A2FB60(this);
    }
}

void func_80A2FB60(EnSlime* this) {
    this->unk14C = 0xF;
    this->actor.scale.x = 0.0132f;
    this->actor.scale.y = 0.0074399994f;
    this->actor.scale.z = 0.0132f;
    this->actionFunc = func_80A2FBA0;
    this->actor.speedXZ = 0.0f;
}

void func_80A2FBA0(EnSlime* this, PlayState* play) {
    f32 sp24;
    f32 sp20;
    f32 temp_fv1_2;

    func_80A2F0A8(this);
    this->unk14C--;
    sp24 = ((this->unk14C / 5) + 1) * 1.6f;
    sp20 = sqrtf(this->unk14C) * 0.2f;
    temp_fv1_2 = ((cos_rad(this->unk14C * 1.2566371f) * (0.05f * sp24)) + 1.0f) * 0.01f;
    this->actor.scale.x = temp_fv1_2;
    this->actor.scale.z = temp_fv1_2;
    if (this->unk14C < 0xF) {
        this->actor.scale.y = (1.0f - (sin_rad((f32)this->unk14C * 1.2566371f) * (0.04f * sp24))) * 0.01f;
    }
    this->actor.shape.rot.x = (s16)(s32)(randPlusMinusPoint5Scaled(512.0f) * sp20);
    this->actor.shape.rot.z = (s16)(s32)(randPlusMinusPoint5Scaled(512.0f) * sp20);
    if (this->unk170 < Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos)) {
        func_80A2F684(this);
    }
    else if ((Player_GetMask(play) != 0x10) && (this->actor.xzDistToPlayer < 280.0f) && (this->unk14C < 0xC)) {
        func_80A2F8B4(this);
    }
    else if (this->unk14C == 0) {
        func_80A2F180(this);
    }
}

void func_80A2FD94(EnSlime* this) {
    this->actor.speedXZ = 10.0f;
    if (this->actor.velocity.y > 0.0f) {
        this->actor.velocity.y = 0.0f;
    }
    this->unk1BC.base.acFlags &= ~1;
    this->unk14C = 0x1E;
    Actor_PlaySfxAtPos(&this->actor, 0x38BFU);
    if (this->unk1BC.base.ac != NULL) {
        this->actor.world.rot.y = Actor_YawBetweenActors(&this->actor, this->unk1BC.base.ac) + 0x8000;
    } else {
        this->actor.world.rot.y = this->actor.yawTowardsPlayer + 0x8000;
    }
    this->actionFunc = func_80A2FE38;
}

void func_80A2FE38(EnSlime* this, PlayState* play) {
    f32 sp24;
    f32 temp_fv1_2;

    func_80A2F0A8(this);
    this->unk14C--;
    Math_StepToF(&this->actor.speedXZ, 0.0f, 1.0f);
    sp24 = sqrtf(this->unk14C);
    if (this->unk14C < 0x1E) {
        temp_fv1_2 = ((cos_rad(this->unk14C * 1.2566371f) * (0.08f * sp24)) + 1.0f) * 0.01f;
        this->actor.scale.x = temp_fv1_2;
        this->actor.scale.z = temp_fv1_2;
    }
    if (this->unk14C == 0xF) {
        this->unk1BC.base.acFlags |= 1;
    }
    this->actor.scale.y = ((sin_rad((f32)this->unk14C * 1.2566371f) * (0.07f * sp24)) + 1.0f) * 0.01f;
    this->actor.shape.rot.x = (s16)(s32)(randPlusMinusPoint5Scaled(512.0f) * sp24);
    this->actor.shape.rot.z = (s16)(s32)(randPlusMinusPoint5Scaled(512.0f) * sp24);
    if (this->unk14C == 0) {
        if (this->unk170 < Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos)) {
            func_80A2F684(this);
        } else if ((this->actor.xzDistToPlayer < 280.0f) && (Player_GetMask(play) != 0x10)) {
            func_80A2F8B4(this);
        } else
            func_80A2F180(this);
    }
}

void func_80A30018(EnSlime* this, PlayState* play, s32 arg2) {
    s32 i;
    Vec3f vec0;
    Vec3f vec1;

    f32 tempf1;
    f32 tempf2;
    f32 random;

    this->unk1BC.base.acFlags &= ~1;
    if (this->actor.velocity.y > 0.0f) {
        this->actor.velocity.y = 0.0f;
    }
    Actor_SetColorFilter(&this->actor, 0x4000U, 0xFFU, 0x2000U, 0x14);
    this->unk14C = 0x14;
    this->actor.speedXZ = 10.0f;
    if (arg2 == 1) {
        func_800BE504(&this->actor, &this->unk1BC);
    }

    this->unk149 = 0;
    Actor_SetScale(&this->actor, 0.01f);
    this->unk154 = Rand_ZeroOne() * 6.2831855f;
    this->unk15C = Rand_ZeroOne() * 6.2831855f;
    tempf1 = Math_SinS(this->actor.world.rot.y) * 10.0f;
    tempf2 = Math_CosS(this->actor.world.rot.y) * 10.0f;
    vec1.x = this->actor.world.pos.x + tempf1;
    vec1.y = this->actor.world.pos.y + 20.0f;
    vec1.z = this->actor.world.pos.z + tempf2;
    EffectSsGSplash_Spawn(play, &vec1, NULL, NULL, 1, 0x226);

    for (i = 0; i < 10; i++) {
        vec1.x = randPlusMinusPoint5Scaled(40.0f) + this->actor.world.pos.x + tempf1;
        vec1.y = randPlusMinusPoint5Scaled(10.0f) + this->actor.world.pos.y + 40.0f;
        vec1.z = randPlusMinusPoint5Scaled(40.0f) + this->actor.world.pos.z + tempf2;

        random = Rand_ZeroOne();
        vec0.x = -Math_SinS(this->actor.world.rot.y) * ((random * 3.5f) + 1.0f);
        random = Rand_ZeroOne();
        vec0.z = -Math_CosS(this->actor.world.rot.y) * ((random * 3.5f) + 1.0f);
        vec0.y = (Rand_ZeroOne() * 6.0f) + 2.0f;
        EffectSsDtBubble_SpawnCustomColor(play, &vec1, &vec0, &D_80A31B68, &D_80A31B60, &D_80A31B64,
                                          Rand_S16Offset(0x28, 0x14), 0x14, 0);
    }

    if (this->actor.colChkInfo.health == 0) {
        Actor_PlaySfxAtPos(&this->actor, 0x38BEU);
    } else {
        Actor_PlaySfxAtPos(&this->actor, 0x38BAU);
    }
    this->actionFunc = func_80A30344;
}

void func_80A30344(EnSlime* this, PlayState* play) {
    this->unk14C--;
    Math_StepToF(&this->actor.speedXZ, 0.0f, 1.0f);
    if ((this->unk14C % 5) == 0) {
        this->unk154 = Rand_ZeroOne() * 6.2831855f;
        this->unk15C = Rand_ZeroOne() * 6.2831855f;
    }
    if (this->unk14C == 0) {
        if (this->actor.colChkInfo.health != 0) {
            this->unk1BC.base.acFlags |= 1;
            if ((this->actor.xzDistToPlayer < 280.0f) && (Player_GetMask(play) != 0x10)) {
                func_80A2F8B4(this);
                return;
            }
            func_80A2F180(this);
            return;
        }
        SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, 0x28U, 0x38BBU);
        func_80A30454(this);
    }
}

void func_80A30454(EnSlime* this) {
    this->unk1BC.base.acFlags &= 0xFFFE;
    if (this->actor.velocity.y > 0.0f) {
        this->actor.velocity.y = 0.0f;
    }
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = func_80A304B8;
    this->actor.speedXZ = 0.0f;
}

void func_80A304B8(EnSlime* this, PlayState* play) {
    s32 i;
    Vec3f vec1;
    Vec3f vec2;

    f32 random;
    s32 factor;

    if (Math_StepToF(&this->actor.scale.x, 0.0f, 0.002f) != 0) {
        vec2.x = this->actor.world.pos.x;
        vec2.y = this->actor.world.pos.y + 20.0f;
        vec2.z = this->actor.world.pos.z;
        EffectSsGSplash_Spawn(play, &vec2, NULL, NULL, 1, 0x320);

        for (i = 0; i < 15; i++) {
            random = Rand_ZeroOne();

            if (Rand_ZeroOne() < 0.5f)
                factor = -1;
            else
                factor = 1;
            vec1.x = factor * ((random * 2.5f) + 2.0f);

            random = Rand_ZeroOne();
            if (Rand_ZeroOne() < 0.5f)
                factor = -1;
            else
                factor = 1;
            vec1.z = factor * ((random * 2.5f) + 2.0f);

            vec1.y = (Rand_ZeroOne() * 6.0f) + 2.0f;
            EffectSsDtBubble_SpawnCustomColor(play, &vec2, &vec1, &D_80A31B68, &D_80A31B60, &D_80A31B64,
                                              Rand_S16Offset(0x28, 0x14), 0x14, 0);
        }

        if (this->actor.params == 2) {
            Item_DropCollectible(play, &this->actor.world.pos, 5U);
        } else if (this->actor.params == 1) {
            Item_DropCollectible(play, &this->actor.world.pos, 0xFU);
        } else if (this->actor.params == 3) {
            Item_DropCollectible(play, &this->actor.world.pos, 3U);
        }
        func_80A30BE0(this);
    }
    this->actor.scale.y = this->actor.scale.x;
    this->actor.scale.z = this->actor.scale.x;
}

f32 func_80A3072C(f32 arg0, f32 arg1) {
    s32 temp = (s32)(arg0 - arg1);

    if (temp > 0) {
        temp = temp + 0x1E;
    } else {
        temp = temp - 0x1E;
    }
    return ((f32)(temp / 60) * 60.0f) + arg1;
}

void func_80A30778(EnSlime* this) {
    this->unk1BC.base.acFlags &= ~1;
    this->actor.flags &= ~1;
    this->unk164 = 0.0f;
    this->actor.speedXZ = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->actor.gravity = 0.0f;
    this->unk154 = func_80A3072C(this->actor.world.pos.x, this->actor.home.pos.x);
    this->unk15C = func_80A3072C(this->actor.world.pos.z, this->actor.home.pos.z);
    Actor_SetColorFilter(&this->actor, 0x8000, 0x80FF, 0x2000, 0xA);
    this->unk149 = 0;
    this->unk148 = 0xFE;
    this->actionFunc = func_80A30820;
}

void func_80A30820(EnSlime* this, PlayState* play) {
    s32 temp;

    temp = Math_StepToF(&this->actor.world.pos.x, this->unk154, 10.0f);
    temp &= Math_StepToF(&this->actor.world.pos.z, this->unk15C, 10.0f);

    this->actor.colorFilterTimer = 0xA;
    if (temp) {
        this->actor.child = Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, 0x143, this->actor.world.pos.x,
                                               this->actor.world.pos.y + 30.0f, this->actor.world.pos.z, 0, 0, 0, 0);
        if (this->actor.child != NULL) {
            this->actor.child->cutscene = this->actor.cutscene;
            func_80A30924(this);
        } else {
            this->actor.colorFilterTimer = 0;
            this->unk1BC.base.acFlags |= 1;
            this->unk148 = 0xFF;
            this->actor.flags |= 1;
            this->actor.gravity = -2.0f;
            func_80A2F180(this);
        }
    }
}

void func_80A30924(EnSlime* this) {
    this->actor.flags |= 0x10;
    this->actionFunc = func_80A30944;
}

void func_80A30944(EnSlime* this, PlayState* play) {
    if (this->unk148 == 0) {
        if ((this->actor.child == NULL) || (this->actor.child->update == NULL) ||
            !(this->actor.child->scale.y >= 0.1f)) {
            func_80A30A90(this);
        }
    } else {
        this->actor.colorFilterTimer = 0xA;
        if (this->unk148 - 5 < 0) {
            this->unk148 = 0;
        } else
            this->unk148 -= 5;
    }
}

void func_80A309C8(EnSlime* this) {
    this->actor.speedXZ = 0.0f;
    func_800BE504(&this->actor, &this->unk1BC);
    if (this->actor.velocity.y > 0.0f) {
        this->actor.velocity.y = 0.0f;
    }
    this->actionFunc = func_80A30A20;
}

void func_80A30A20(EnSlime* this, PlayState* play) {
    this->unk14C--;
    if (this->unk14C == 0) {
        func_80A2F028(this, play);
        if (this->actor.colChkInfo.health == 0) {
            func_80A30018(this, play, 0);
        } else {
            this->actor.world.rot.y = this->actor.shape.rot.y;
            func_80A2F354(this);
        }
    }
}

void func_80A30A90(EnSlime* this) {
    this->actor.colorFilterTimer = 0;
    this->actor.gravity = -2.0f;
    Actor_SetColorFilter(&this->actor, 0x8000U, 0x80FFU, 0x2000U, 0xA);
    this->actionFunc = func_80A30AE4;
}

void func_80A30AE4(EnSlime* this, PlayState* play) {
    s32 temp;

    this->actor.colorFilterTimer = 0xA;
    if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
        temp = (0.1f - this->actor.child->scale.y) * 10.0f * 255.0f;
        this->unk148 = (u8)(CLAMP(temp, 0, 0xff));
    } else {
        this->actor.child = NULL;
        temp = this->unk148 + 10;
        this->unk148 = (u8)(CLAMP_MAX(temp, 0xff));
    }
    if (this->unk148 == 0xFF) {
        this->unk1BC.base.acFlags |= 1;
        this->actor.flags |= 1;
        this->actor.flags &= ~0x10;
        func_80A2F180(this);
    }
}

void func_80A30BE0(EnSlime* this) {
    this->actor.draw = NULL;
    this->actor.flags |= 0x10;
    this->unk164 = 0.0f;
    this->actor.gravity = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->actor.speedXZ = 0.0f;
    this->unk1BC.base.ocFlags1 &= ~0x1;
    this->unk14C = this->unk152;
    this->actionFunc = func_80A30C2C;
}

void func_80A30C2C(EnSlime* this, PlayState* play) {
    if (this->unk14C == 0)
        func_80A30C68(this);
    else
        this->unk14C--;
}

void func_80A30C68(EnSlime* this) {
    this->actor.draw = EnSlime_Draw;
    this->actor.colChkInfo.health = D_80A31B3C.health;
    this->unk148 = 0xFF;
    Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.home.pos);
    this->unk14C = 0;
    this->actor.colorFilterTimer = 0;
    this->actor.home.rot.y = this->actor.yawTowardsPlayer;
    Actor_PlaySfxAtPos(&this->actor, 0x39FEU);
    this->actionFunc = func_80A30CEC;
    this->actor.gravity = -2.0f;
}

void func_80A30CEC(EnSlime* this, PlayState* play) {
    f32 temp_f0;
    f32 temp_f1;

    if (++this->unk14C == 0x1C) {
        this->actor.flags &= ~0x10;
        this->actor.flags |= 1;
        this->unk1BC.base.acFlags |= 1;
        this->actor.shape.rot.y = this->actor.home.rot.y;
        func_80A2F354(this);
    } else {
        if (this->unk14C < 0xC) {
            temp_f0 = this->unk14C * 0.0008333333f;
            this->unk174.x = temp_f0;
            this->unk174.z = temp_f0;
            this->unk174.y = 2.0f * temp_f0;
            this->unk150 = this->unk14C * 1638.4f;
        } else if (this->unk14C < 0x14) {
            temp_f0 = (this->unk14C - 0xC) * 0.000625f;
            temp_f1 = 0.01f + temp_f0;
            this->unk174.x = temp_f1;
            this->unk174.z = temp_f1;
            this->unk174.y = 2.0f * (0.01f - temp_f0);
            this->unk150 = this->unk14C * 1638.4f;
        } else if (this->unk14C < 0x18) {
            temp_f0 = (this->unk14C - 0x14) * 0.0033333332f;
            temp_f1 = 0.015f - temp_f0;
            this->unk174.x = temp_f1;
            this->unk174.z = temp_f1;
            this->unk174.y = (2.0f * temp_f0) + 0.01f;
            Actor_SetScale(&this->actor, 1.5f * temp_f0);
            this->unk150 = ((0x17 - this->unk14C) * 7281.778f) + 10922.667f;
            this->actor.shape.rot.y = (0x1C - this->unk14C) * 4096.0f;
        } else {
            Actor_SetScale(&this->actor, (((0x1C - this->unk14C) * 0.1f) + 1.0f) * 0.01f);
            Math_Vec3f_Copy(&this->unk174, &gZeroVec3f);
            this->actor.shape.rot.y = ((0x1C - this->unk14C) * 4096.0f);
        }

        if (this->unk14C == 0x15) {
            this->unk1BC.base.ocFlags1 |= 1;
        }

        this->unk150 += this->actor.home.rot.y;
        this->actor.shape.rot.y += this->actor.home.rot.y;
    }
}

void func_80A30F98(EnSlime* this, PlayState* play) {
    if (this->unk1BC.base.acFlags & 2) {
        this->unk1BC.base.acFlags &= ~0x2;
        if ((this->unk14A != 0xA) || !(this->unk1BC.info.acHitInfo->toucher.dmgFlags & 0xDB0B3)) {
            func_80A2F028(this, play);
            if ((this->actor.params == 0) && (this->actor.colChkInfo.damageEffect == 3)) {
                this->actor.colChkInfo.damage = 0;
            }
            if (Actor_ApplyDamage(&this->actor) == 0) {
                Actor_SetDropFlag(&this->actor, &this->unk1BC.info);
                Enemy_StartFinishingBlow(play, &this->actor);
                this->actor.flags &= ~1;
            }

            if (this->actor.colChkInfo.damageEffect == 0xF) {
                func_80A2FD94(this);
            } else if (this->actor.colChkInfo.damageEffect == 1) {
                this->unk14C = 0x28;
                Actor_SetColorFilter(&this->actor, 0U, 0xFFU, 0x2000U, 0x28);
                Actor_PlaySfxAtPos(&this->actor, 0x389EU);
                func_80A309C8(this);
            } else if (this->actor.colChkInfo.damageEffect != 0xE) {
                if (this->actor.colChkInfo.damageEffect == 3) {
                    if (this->actor.params == 0) {
                        func_80A30778(this);
                    } else {
                        func_80A2EFAC(this);
                        if (this->actor.colChkInfo.health == 0) {
                            this->unk14C = 3;
                            this->unk1BC.base.acFlags &= ~1;
                        }
                        func_80A309C8(this);
                    }
                } else {
                    if (this->actor.colChkInfo.damageEffect == 4) {
                        this->unk164 = 4.0f;
                        this->unk168 = 0.4f;
                        this->unk14A = 0x14;
                        Actor_Spawn(&play->actorCtx, play, 0xA2, this->unk1BC.info.bumper.hitPos.x,
                                    this->unk1BC.info.bumper.hitPos.y, this->unk1BC.info.bumper.hitPos.z, 0, 0, 0, 4);
                    } else if (this->actor.colChkInfo.damageEffect == 5) {
                        this->unk14A = 0x20;
                        this->unk164 = 4.0f;
                        this->unk168 = 0.4f;
                    }
                    func_80A30018(this, play, 1);
                }
            }
        }
    }
}

void EnSlime_Update(Actor* thisx, PlayState* play) {
    EnSlime* this = THIS;
    s32 pad;
    Player* player = GET_PLAYER(play);

    func_80A30F98(this, play);
    this->actionFunc(this, play);

    thisx->shape.shadowAlpha = this->unk148;
    if (this->unk148 == 0xFF) {
        if (thisx->scale.y > 0.0001f) {
            thisx->targetArrowOffset = 60.0f / thisx->scale.y;
        }

        if (this->unk1BC.base.ocFlags1 & 1) {
            Actor_MoveWithGravity(thisx);
            Actor_UpdateBgCheckInfo(play, thisx, 20.0f, 35.0f, 40.0f, 0x1DU);
        }

        Collider_UpdateCylinder(thisx, &this->unk1BC);
        this->unk1BC.dim.radius = D_80A31AF0.dim.radius * (100.0f * thisx->scale.z);
        this->unk1BC.dim.height = D_80A31AF0.dim.height * (100.0f * thisx->scale.y);

        if (this->actionFunc == func_80A2FA88) {
            CollisionCheck_SetAT(play, &play->colChkCtx, &this->unk1BC.base);
        }

        if (this->unk1BC.base.acFlags & 1) {
            CollisionCheck_SetAC(play, &play->colChkCtx, &this->unk1BC.base);
        }

        if (player->stateFlags3 & 0x100) {
            this->unk1BC.base.ocFlags1 &= ~0x8;
        } else {
            this->unk1BC.base.ocFlags1 |= 8;
        }

        if (this->unk1BC.base.ocFlags1 & 1) {
            CollisionCheck_SetOC(play, &play->colChkCtx, &this->unk1BC.base);
        }

        Actor_SetFocus(thisx, 15.0f);
        if (this->unk164 > 0.0f) {
            if (this->unk14A != 0xA) {
                Math_StepToF(&this->unk164, 0.0f, 0.05f);
                this->unk168 = (this->unk164 + 1.0f) * 0.2f;
                this->unk168 = CLAMP_MAX(this->unk168, 0.4f);
            } else if (Math_StepToF(&this->unk16C, 0.4f, 0.01f) == 0) {
                func_800B9010(thisx, 0x20B2U);
            }
        }
    }
}

void EnSlime_Draw(Actor* thisx, PlayState* play) {
    s32 i;
    EnSlime* this = THIS;
    Vec3f vec3f;
    Color_RGBA8* color1;
    Color_RGBA8* color2;
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C28C(play->state.gfxCtx);
    func_8012C2DC(play->state.gfxCtx);
    func_800B8118(&this->actor, play, 0);
    if (this->unk148 != 0xFF) {
        gSPSegment(POLY_XLU_DISP++, 0x0A, (u32)D_801AEFA0);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0xAA, 0xFF, 0xFF, 0xFF, 0xFF);
        gDPSetEnvColor(POLY_XLU_DISP++, 0x96, 0xFF, 0xFF, this->unk148);
    } else {
        color1 = &D_80A31B74[this->actor.params];
        color2 = &D_80A31B84[this->actor.params];
        AnimatedMat_Draw(play, (AnimatedMaterial*)D_80A32200);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x64, color1->r, color1->g, color1->b, color1->a);
        gDPSetEnvColor(POLY_XLU_DISP++, color2->r, color2->g, color2->b, 0xFF);
    }

    if (this->actionFunc == func_80A30344) {
        vec3f.x = 1.0f - (sin_rad((f32)this->unk14C * 1.5707964f) * 0.3f);
        vec3f.y = (sin_rad((f32)this->unk14C * 1.5707964f) * 0.3f) + 1.0f;
        vec3f.z = 1.0f - (cos_rad((f32)this->unk14C * 1.5707964f) * 0.3f);

        Matrix_RotateXFApply(this->unk154);
        Matrix_RotateZF(this->unk15C, MTXMODE_APPLY);
        Matrix_Scale(vec3f.x, vec3f.y, vec3f.z, MTXMODE_APPLY);
        Matrix_RotateZF(-this->unk15C, MTXMODE_APPLY);
        Matrix_RotateXFApply(-this->unk154);
    }

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, (u32)&D_060004C0);

    if (this->unk148 == 0xFF) {
        Scene_SetRenderModeXlu(play, 0, 1U);

        gSPSegment(POLY_OPA_DISP++, 0x09, (u32)D_80A31B44[(u8)this->unk149]);
        gDPSetEnvColor(POLY_OPA_DISP++, 0x00, 0x1E, 0x46, 0xFF);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, (u32)&D_06000650);

    } else {
        Scene_SetRenderModeXlu(play, 1, 2U);
        gSPSegment(POLY_XLU_DISP++, 0x09, (u32)D_80A31B44[(u8)this->unk149]);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, (u32)&D_06000650);
    }

    for (i = 0; i < 5; i++) {
        Matrix_MultVec3f(&D_80A31B94[i], &this->unk180[i]);
    }

    if (this->actionFunc == func_80A30CEC) {
        Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
        Matrix_RotateYS(this->unk150, MTXMODE_APPLY);
        Matrix_Scale(this->unk174.x, this->unk174.y, this->unk174.z, MTXMODE_APPLY);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, (u32)&D_06000A10);
    }

    if ((this->actor.params != 0) && (this->actor.scale.x > 0.0f)) {
        POLY_OPA_DISP = func_801660B8(play, POLY_OPA_DISP);
        POLY_OPA_DISP = func_8012C724(POLY_OPA_DISP);

        Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y + (2000.0f * this->actor.scale.y),
                         this->actor.world.pos.z, MTXMODE_NEW);
        Matrix_Scale(0.03f, 0.03f, 0.03f, MTXMODE_APPLY);

        gSPSegment(POLY_OPA_DISP++, 0x08, (u32)this->unk160);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, (u32)&D_0405F6F0);
    }

    Actor_DrawDamageEffects(play, &this->actor, this->unk180, 5, this->unk168, this->unk16C, this->unk164,
                            (u8)(s32)this->unk14A);

    CLOSE_DISPS(play->state.gfxCtx);
}
