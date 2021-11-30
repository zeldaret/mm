/*
 * File z_en_am.c
 * Overlay: ovl_En_Am
 * Description: Armos
 */

#include "z_en_am.h"
#include "overlays/actors/ovl_En_Bom/z_en_bom.h"
#include "overlays/actors/ovl_En_Bombf/z_en_bombf.h"

#define FLAGS 0x00000405

#define THIS ((EnAm*)thisx)

void EnAm_Init(Actor* thisx, GlobalContext* globalCtx);
void EnAm_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnAm_Update(Actor* thisx, GlobalContext* globalCtx);
void EnAm_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_808AFF9C(EnAm* this);
void func_808B0040(EnAm* this, GlobalContext* globalCtx);
void func_808B00D8(EnAm* this);
void func_808B0124(EnAm* this, GlobalContext* globalCtx);
void func_808B0358(EnAm* this);
void func_808B03C0(EnAm* this, GlobalContext* globalCtx);
void func_808B0460(EnAm* this);
void func_808B04A8(EnAm* this, GlobalContext* globalCtx);
void func_808B0508(EnAm* this, GlobalContext* globalCtx);
void func_808B057C(EnAm* this);
void func_808B05C8(EnAm* this, GlobalContext* globalCtx);
void func_808B0640(EnAm* this);
void func_808B066C(EnAm* this, GlobalContext* globalCtx);
void func_808B06D0(EnAm* this, GlobalContext* globalCtx);
void func_808B07A8(EnAm* this, GlobalContext* globalCtx);
void func_808B0820(EnAm* this);
void func_808B0894(EnAm* this, GlobalContext* globalCtx);
void func_808B0B4C(EnAm* this, GlobalContext* globalCtx);
void func_808B0EA4(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* actor);

const ActorInit En_Am_InitVars = {
    ACTOR_EN_AM,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_AM,
    sizeof(EnAm),
    (ActorFunc)EnAm_Init,
    (ActorFunc)EnAm_Destroy,
    (ActorFunc)EnAm_Update,
    (ActorFunc)EnAm_Draw,
};

static ColliderCylinderInit sEnemyCylinderInit = {
    {
        COLTYPE_HIT5,
        AT_NONE | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x00, 0x08 },
        { 0x81C2C788, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON | BUMP_HOOKABLE,
        OCELEM_ON,
    },
    { 23, 98, 0, { 0, 0, 0 } },
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_METAL,
        AT_NONE,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x760D3877, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 23, 98, 0, { 0, 0, 0 } },
};

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0xF),
    /* Deku Stick     */ DMG_ENTRY(0, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0xF),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(0, 0xF),
    /* Normal arrow   */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xD),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(0, 0xF),
    /* Ice arrow      */ DMG_ENTRY(0, 0xF),
    /* Light arrow    */ DMG_ENTRY(0, 0xF),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(0, 0xF),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0xF),
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
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

static CollisionCheckInfoInit sColChkInfoInit = { 1, 23, 98, MASS_HEAVY };

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 14, ICHAIN_CONTINUE),
    ICHAIN_S8(hintId, 19, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -4000, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_STOP),
};

static Vec3f sVelocity = { 0.0f, -1.5f, 0.0f };

static Vec3f sAccel = { 0.0f, -0.20000000298f, 0.0f };

static Color_RGBA8 D_808B1118 = { 100, 100, 100, 0 };

static Color_RGBA8 D_808B111C = { 40, 40, 40, 0 };

static Color_RGBA8 D_808B1120 = { 150, 150, 150, 255 };

static Color_RGBA8 D_808B1124 = { 100, 100, 100, 150 };

static Vec3f D_808B1128[] = {
    { 4700.0f, -500.0f, 1800.0f }, { 4700.0f, -500.0f, -1800.0f }, { 2000.0f, -1500.0f, 0.0f },
    { 2000.0f, 0.0f, -1500.0f },   { 2000.0f, 0.0f, 1500.0f },
};

static Vec3f D_808B1164[] = {
    { 0.0f, -3000.0f, 0.0f },
    { 700.0f, -800.0f, 0.0f },
};

static Vec3f D_808B117C[] = {
    { 800.0f, 1000.0f, -1000.0f },
    { 800.0f, 1000.0f, 1000.0f },
    { 800.0f, -1000.0f, 1000.0f },
    { 800.0f, -1000.0f, -1000.0f },
};

extern AnimationHeader D_06000238;
extern AnimationHeader D_0600033C;
extern AnimationHeader D_06005B3C;
extern SkeletonHeader D_06005948;

void EnAm_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnAm* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 42.857143f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &D_06005948, &D_0600033C, this->jointTable, this->morphTable, 14);
    Collider_InitAndSetCylinder(globalCtx, &this->enemyCollider, &this->actor, &sEnemyCylinderInit);
    Collider_InitAndSetCylinder(globalCtx, &this->collider2, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    this->actor.home.pos.x -= 9.0f * Math_SinS(this->actor.shape.rot.y);
    this->actor.home.pos.z -= 9.0f * Math_CosS(this->actor.shape.rot.y);
    this->actor.world.pos.x = this->actor.home.pos.x;
    this->actor.world.pos.z = this->actor.home.pos.z;
    func_808AFF9C(this);
}

void EnAm_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnAm* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->enemyCollider);
    Collider_DestroyCylinder(globalCtx, &this->collider2);
}

void func_808AFE38(EnAm* this, GlobalContext* globalCtx) {
    s32 i;
    Vec3f pos;
    s32 pad;

    for (i = 4; i > 0; i--) {
        pos.x = randPlusMinusPoint5Scaled(65.0f) + this->actor.world.pos.x;
        pos.y = randPlusMinusPoint5Scaled(10.0f) + (this->actor.world.pos.y + 40.0f);
        pos.z = randPlusMinusPoint5Scaled(65.0f) + this->actor.world.pos.z;
        EffectSsKiraKira_SpawnSmall(globalCtx, &pos, &sVelocity, &sAccel, &D_808B1118, &D_808B111C);
    }
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_AMOS_WALK);
    func_800BBDAC(globalCtx, &this->actor, &this->actor.world.pos, 4.0f, 3, 8.0f, 0x12C, 0xF, 0);
}

void func_808AFF9C(EnAm* this) {
    f32 lastFrame = Animation_GetLastFrame(&D_0600033C);

    Animation_Change(&this->skelAnime, &D_0600033C, 0.0f, lastFrame, lastFrame, 0, 0.0f);
    this->enemyCollider.info.bumper.dmgFlags = 0x80000088;
    this->collider2.info.bumper.dmgFlags = 0x77CFFF77;
    if (this->actor.colChkInfo.health != 0) {
        this->enemyCollider.base.atFlags &= ~1;
    }
    Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.home.pos);
    this->actionFunc = func_808B0040;
}

void func_808B0040(EnAm* this, GlobalContext* globalCtx) {
    if (((this->enemyCollider.base.ocFlags1 & 2) && (this->enemyCollider.base.ocFlags2 & 1)) ||
        (this->collider2.base.acFlags & 2)) {
        if (this->unk_234 == 0) {
            func_808B00D8(this);
        }
        return;
    }
    if (this->unk_234 >= 0xB) {
        this->unk_234 -= 0xA;
    } else {
        this->unk_234 = 0;
        this->actor.flags &= -2;
        this->unk_23A = 0;
    }
}

void func_808B00D8(EnAm* this) {
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_AMOS_WAVE);
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_AMOS_VOICE);
    this->unk_238 = 0x12C;
    this->actionFunc = func_808B0124;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B0124.s")
void func_808B0124(EnAm* this, GlobalContext* globalCtx) {
    s32 sp2C;
    f32 sp28;
    u8 pad; // could be fake
    f32 sp20;
    f32 sin;

    if (this->unk_234 + 0x14 >= 0xFF) {
        this->unk_234 = 0xFF;
        this->actor.flags |= 1;
        this->enemyCollider.info.bumper.dmgFlags = 0x81C2C788;
        this->collider2.info.bumper.dmgFlags = 0x760D3877;
        this->enemyCollider.base.atFlags |= 1;
        this->actor.shape.yOffset = 0.0f;
        func_808B0358(this);
        return;
    }
    sp2C = this->unk_234 + 0x14;
    sp20 = randPlusMinusPoint5Scaled(10.0f);
    sp28 = Math_CosS(this->actor.shape.rot.y) * sp20;
    sin = Math_SinS(this->actor.shape.rot.y);
    this->actor.world.pos.x = this->actor.home.pos.x + sp28;
    this->actor.world.pos.z = this->actor.home.pos.z + (sin * sp20);
    this->unk_234 = sp2C;
}

void func_808B0208(EnAm* this, GlobalContext* globalCtx) {
    if ((this->actor.speedXZ > 0.0f) && (this->actor.bgCheckFlags & 8)) {
        this->actor.world.rot.y = (this->actor.wallYaw * 2) - this->actor.world.rot.y;
        this->actor.world.pos.x += this->actor.speedXZ * Math_SinS(this->actor.world.rot.y);
        this->actor.world.pos.z += this->actor.speedXZ * Math_CosS(this->actor.world.rot.y);
    }
    SkelAnime_Update(&this->skelAnime);
    if (Animation_OnFrame(&this->skelAnime, 8.0f) != 0) {
        this->actor.speedXZ = this->unk_240;
        this->actor.velocity.y = 12.0f;
    } else if (this->skelAnime.curFrame > 11.0f) {
        if ((this->actor.bgCheckFlags & 1) == 0) {
            this->skelAnime.curFrame = 11.0f;
        } else {
            Math_ScaledStepToS(&this->actor.world.rot.y, this->unk_23C, 0x1F40);
            this->actor.speedXZ = 0.0f;
            if ((this->actor.bgCheckFlags & 2) != 0) {
                func_808AFE38(this, globalCtx);
            }
        }
    }
    if (this->actionFunc != func_808B0894) {
        this->actor.shape.rot.y = this->actor.world.rot.y;
    }
}

void func_808B0358(EnAm* this) {
    Animation_PlayLoopSetSpeed(&this->skelAnime, &D_06000238, 4.0f);
    this->deathTimer = 3;
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->unk_240 = 6.0f;
    this->actionFunc = func_808B03C0;
}

void func_808B03C0(EnAm* this, GlobalContext* globalCtx) {
    this->unk_23C = this->actor.yawTowardsPlayer;
    func_808B0208(this, globalCtx);
    if ((this->actor.bgCheckFlags & 2)) {
        this->deathTimer--;
    }
    if (this->deathTimer == 0) {
        func_808B0640(this);
    } else if ((this->unk_238 == 0) || Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos) > 240.0f) {
        func_808B0460(this);
    }
}

void func_808B0460(EnAm* this) {
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->unk_240 = 0.0f;
    this->unk_23C = Actor_YawToPoint(&this->actor, &this->actor.home.pos);
    this->actionFunc = func_808B04A8;
}

void func_808B04A8(EnAm* this, GlobalContext* globalCtx) {
    func_808B0208(this, globalCtx);
    if (this->unk_23C == this->actor.world.rot.y) {
        func_808B057C(this);
    }
}

void func_808B04E4(EnAm* this) {
    this->unk_240 = 0.0f;
    this->unk_23C = this->actor.home.rot.y;
    this->actionFunc = func_808B0508;
}

void func_808B0508(EnAm* this, GlobalContext* globalCtx) {
    func_808B0208(this, globalCtx);
    if ((this->actor.bgCheckFlags & 1) == 0) {
        Math_StepToF(&this->actor.world.pos.x, this->actor.home.pos.x, 2.0f);
        Math_StepToF(&this->actor.world.pos.z, this->actor.home.pos.z, 2.0f);
    }
    if (this->actor.home.rot.y == this->actor.world.rot.y) {
        func_808AFF9C(this);
    }
}

void func_808B057C(EnAm* this) {
    this->unk_240 = 6.0f;
    this->unk_23C = Actor_YawToPoint(&this->actor, &this->actor.home.pos);
    this->deathTimer = 1;
    this->actionFunc = func_808B05C8;
}

void func_808B05C8(EnAm* this, GlobalContext* globalCtx) {
    this->unk_23C = Actor_YawToPoint(&this->actor, &this->actor.home.pos);
    func_808B0208(this, globalCtx);
    if (Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos) < 8.0f) {
        func_808B04E4(this);
    }
}

void func_808B0640(EnAm* this) {
    this->deathTimer = 0x28;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->unk_240 = 0.0f;
    this->actionFunc = func_808B066C;
}

void func_808B066C(EnAm* this, GlobalContext* globalCtx) {
    if (this->deathTimer != 0) {
        this->deathTimer--;
    } else {
        this->unk_23C = this->actor.yawTowardsPlayer;
        func_808B0208(this, globalCtx);
        if (this->unk_23C == this->actor.shape.rot.y) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_AMOS_VOICE);
            func_808B0358(this);
        }
    }
}

void func_808B06D0(EnAm* this, GlobalContext* globalCtx) {
    Animation_Change(&this->skelAnime, &D_06005B3C, 1.0f, 4.0f, (Animation_GetLastFrame(&D_06005B3C) - 6), 2, 0.0f);
    func_800BE504(&this->actor, &this->enemyCollider);
    this->actor.speedXZ = 6.0f;
    func_800BCB70(&this->actor, 0x4000, 0xFF, 0, (Animation_GetLastFrame(&D_06005B3C) - 0xA));
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_EYEGOLE_DAMAGE);
    this->enemyCollider.base.acFlags &= ~1;
    this->unk_234 = 0xFF;
    this->actionFunc = func_808B07A8;
}

void func_808B07A8(EnAm* this, GlobalContext* globalCtx) {
    Math_StepToF(&this->actor.speedXZ, 0.0f, 0.5f);
    if (SkelAnime_Update(&this->skelAnime) != 0) {
        if (this->actor.colChkInfo.health == 0) {
            func_808B0820(this);
        } else {
            this->enemyCollider.base.acFlags |= 1;
            func_808B0358(this);
        }
    }
}

void func_808B0820(EnAm* this) {
    Animation_PlayLoopSetSpeed(&this->skelAnime, &D_06000238, 4.0f);
    this->deathTimer = 64;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actor.flags |= 0x10;
    this->actor.speedXZ = 0.0f;
    this->unk_240 = 6.0f;
    this->actionFunc = func_808B0894;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B0894.s")
void func_808B0894(EnAm* this, GlobalContext* globalCtx) {
    s32 i;
    Vec3f dustPos;
    s32 pad;

    this->deathTimer -= 1;
    this->unk_23C = this->actor.yawTowardsPlayer;
    func_808B0208(this, globalCtx);
    if (this->deathTimer == 1) {
        EnBom* bomb = (EnBom*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_BOM, this->actor.world.pos.x,
                                          this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 2, 0);
        if (bomb != NULL) {
            bomb->timer = 0;
        }
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_EYEGOLE_DEAD);
        Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.world.pos, 0xB0);

        for (i = 0; i < 8; i++) {
            dustPos.x = (Math_SinS(0) * 7.0f) + this->actor.world.pos.x;
            dustPos.y = (randPlusMinusPoint5Scaled(10.0f) * 6.0f) + (this->actor.world.pos.y + 40.0f);
            dustPos.z = (Math_CosS(0) * 7.0f) + this->actor.world.pos.z;

            func_800B0EB0(globalCtx, &dustPos, &D_801D15B0, &D_801D15B0, &D_808B1120, &D_808B1124, 200, 45, 12);
        }
    } else if (this->deathTimer == 0) {
        Actor_MarkForDeath(&this->actor);
        return;
    } else if (!(this->deathTimer & 3)) {
        func_800BCB70(&this->actor, 0x4000, 0xFF, 0, 4);
    }
    if (this->actor.world.rot.z < 0x1F40) {
        this->actor.world.rot.z += 0x320;
    }
    this->actor.shape.rot.y += this->actor.world.rot.z;
}

void func_808B0AD0(EnAm* this, GlobalContext* globalCtx) {
    Animation_Change(&this->skelAnime, &D_0600033C, 1.0f, 0.0f, 8.0f, 2, 0.0f);
    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    this->actor.speedXZ = -6.0f;
    this->actionFunc = func_808B0B4C;
}

void func_808B0B4C(EnAm* this, GlobalContext* globalCtx) {
    Math_StepToF(&this->actor.speedXZ, 0.0f, 0.5f);
    if (SkelAnime_Update(&this->skelAnime) != 0) {
        func_808B0358(this);
    }
}

s32 func_808B0B9C(EnAm* this, GlobalContext* globalCtx) {
    if ((this->enemyCollider.base.acFlags & 2) != 0) {
        this->enemyCollider.base.acFlags &= ~2;
        func_800BE258(&this->actor, &this->enemyCollider.info);
        if (Actor_ApplyDamage(&this->actor) == 0) {
            Enemy_StartFinishingBlow(globalCtx, &this->actor);
        }
        if (this->actor.colChkInfo.damageEffect == 0xD) {
            return 1;
        }
        if (this->actor.colChkInfo.health != 0) {
            this->enemyCollider.base.atFlags &= ~1;
        }
        this->enemyCollider.base.atFlags &= ~2;
        if (this->actor.colChkInfo.damageEffect == 4) {
            this->unk_248 = 0.7f;
            this->unk_244 = 4.0f;
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0xA2, this->enemyCollider.info.bumper.hitPos.x,
                        this->enemyCollider.info.bumper.hitPos.y, this->enemyCollider.info.bumper.hitPos.z, 0, 0, 0, 4);
        }
        func_808B06D0(this, globalCtx);
        return 1;
    }
    return 0;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/EnAm_Update.s")
void EnAm_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnAm* this = THIS;
    s32 pad;

    if (func_808B0B9C(this, globalCtx) == 0) {
        if ((this->enemyCollider.base.atFlags & 4) != 0) {
            this->enemyCollider.base.atFlags &= 0xFFF9;
            if (this->actor.colChkInfo.health == 0) {
                this->actor.world.rot.y = this->actor.yawTowardsPlayer + 0x8000;
            } else {
                func_808B0AD0(this, globalCtx);
            }
        }
    }
    if (this->unk_238 != 0) {
        this->unk_238--;
    }
    this->actionFunc(this, globalCtx);
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, 30.0f, 100.0f, 0x1D);
    Actor_SetHeight(&this->actor, 64.0f);
    Collider_UpdateCylinder(&this->actor, &this->enemyCollider);
    Collider_UpdateCylinder(&this->actor, &this->collider2);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->enemyCollider.base);
    if (this->enemyCollider.base.acFlags & AC_ON) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->enemyCollider.base);
    }
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider2.base);
    if (this->enemyCollider.base.atFlags & AC_ON) {
        this->actor.flags |= 0x1000000;
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->enemyCollider.base);
    }
    Math_StepToF(&this->unk_244, 0.0f, 0.05f);
    this->unk_248 = (this->unk_244 + 1.0f) * 0.35f;
    this->unk_248 = (this->unk_248 > 0.7f) ? 0.7f : this->unk_248;
}

void func_808B0EA4(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* actor) {
    s32 i;
    s32 phi_s3;
    Vec3f* phi_s1;
    Vec3f* phi_s2;
    EnAm* this = (EnAm*)actor;

    phi_s2 = 0;
    phi_s1 = 0;
    if (limbIndex == 4) {
        phi_s2 = &this->unk_24C[0];
        phi_s1 = D_808B1128;
        phi_s3 = 5;
    } else if (limbIndex == 0xD) {
        phi_s2 = &this->unk_24C[9];
        phi_s1 = D_808B117C;
        phi_s3 = 4;
    } else if ((limbIndex == 7) || (limbIndex == 0xA)) {
        phi_s2 = (limbIndex == 7) ? &this->unk_24C[5] : &this->unk_24C[7];
        phi_s1 = D_808B1164;
        phi_s3 = 2;
    } else {
        phi_s3 = 0;
    }
    for (i = 0; i < phi_s3; i++, phi_s2++, phi_s1++) {
        Matrix_MultiplyVector3fByState(phi_s1, phi_s2);
    }
}

void EnAm_Draw(Actor* thisx, GlobalContext* globalCtx) {
    Gfx* gfx;
    EnAm* this = (EnAm*)thisx;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    gfx = POLY_OPA_DISP;
    gSPDisplayList(&gfx[0], &sSetupDL[6 * 25]);
    gDPSetEnvColor(&gfx[1], 0, 0, 0, this->unk_234);
    POLY_OPA_DISP = &gfx[2];
    SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, NULL, func_808B0EA4,
                      &this->actor);
    func_800BE680(globalCtx, &this->actor, this->unk_24C, 0xD, this->unk_248, 0.0f, this->unk_244, 0x14);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
