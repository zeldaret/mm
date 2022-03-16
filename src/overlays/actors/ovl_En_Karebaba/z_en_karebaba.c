/*
 * File: z_en_karebaba.c
 * Overlay: ovl_En_Karebaba
 * Description: Wilted Deku Baba
 */

#include "z_en_karebaba.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "objects/object_dekubaba/object_dekubaba.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4)

#define THIS ((EnKarebaba*)thisx)

void EnKarebaba_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKarebaba_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKarebaba_Update(Actor* thisx, GlobalContext* globalCtx);
void EnKarebaba_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_808F155C(EnKarebaba* this);
void func_808F15B0(EnKarebaba* this, GlobalContext* globalCtx);
void func_808F1648(EnKarebaba* this);
void func_808F169C(EnKarebaba* this, GlobalContext* globalCtx);
void func_808F16FC(EnKarebaba* this);
void func_808F1778(EnKarebaba* this, GlobalContext* globalCtx);
void func_808F1878(EnKarebaba* this);
void func_808F190C(EnKarebaba* this, GlobalContext* globalCtx);
void func_808F1A3C(EnKarebaba* this);
void func_808F1A58(EnKarebaba* this, GlobalContext* globalCtx);
void func_808F1BF8(EnKarebaba* this);
void func_808F1C84(EnKarebaba* this, GlobalContext* globalCtx);
void func_808F1FAC(EnKarebaba* this);
void func_808F200C(EnKarebaba* this, GlobalContext* globalCtx);
void func_808F20FC(EnKarebaba* this, GlobalContext* globalCtx);
void func_808F21A4(EnKarebaba* this, GlobalContext* globalCtx);
void func_808F220C(EnKarebaba* this);
void func_808F228C(EnKarebaba* this, GlobalContext* globalCtx);
void func_808F238C(EnKarebaba* this);
void func_808F241C(EnKarebaba* this, GlobalContext* globalCtx);
void func_808F254C(EnKarebaba* this, GlobalContext* globalCtx);

const ActorInit En_Karebaba_InitVars = {
    ACTOR_EN_KAREBABA,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_DEKUBABA,
    sizeof(EnKarebaba),
    (ActorFunc)EnKarebaba_Init,
    (ActorFunc)EnKarebaba_Destroy,
    (ActorFunc)EnKarebaba_Update,
    (ActorFunc)EnKarebaba_Draw,
};

static ColliderCylinderInit sCylinderInit1 = {
    {
        COLTYPE_HARD,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 7, 25, 0, { 0, 0, 0 } },
};

static ColliderCylinderInit sCylinderInit2 = {
    {
        COLTYPE_HARD,
        AT_ON | AT_TYPE_ENEMY,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x00, 0x04 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_WOOD,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 4, 25, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit sColChkInfoInit = { 1, 15, 80, MASS_HEAVY };

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(3, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(2, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(1, 0x5),
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

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(targetArrowOffset, 2500, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, 1, ICHAIN_STOP),
};

Color_RGBA8 D_808F2E28 = { 0, 0, 0, 0 };

Gfx* D_808F2E2C[] = { object_dekubaba_DL_001330, object_dekubaba_DL_001628, object_dekubaba_DL_001828 };

void EnKarebaba_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnKarebaba* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 22.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &object_dekubaba_Skel_002A40, &object_dekubaba_Anim_0002B8,
                   this->jointTable, this->morphTable, 8);

    Collider_InitAndSetCylinder(globalCtx, &this->collider2, &this->actor, &sCylinderInit1);
    Collider_UpdateCylinder(&this->actor, &this->collider2);
    Collider_InitAndSetCylinder(globalCtx, &this->collider1, &this->actor, &sCylinderInit2);
    Collider_UpdateCylinder(&this->actor, &this->collider1);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);

    this->unk_22C = NULL;
    if (this->actor.params == ENKAREBABA_2) {
        this->actor.hintId = 2;
    } else {
        this->actor.hintId = 9;
    }

    if (this->actor.params == ENKAREBABA_0) {
        func_808F155C(this);
    } else {
        func_808F1648(this);
    }
}

void EnKarebaba_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnKarebaba* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider2);
    Collider_DestroyCylinder(globalCtx, &this->collider1);
}

void func_808F1374(EnKarebaba* this, GlobalContext* globalCtx) {
    s32 phi_a3;

    if (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
        this->drawDmgEffAlpha = 0.0f;
        if (this->actor.params == ENKAREBABA_2) {
            phi_a3 = 1;
        } else {
            phi_a3 = 4;
        }
        Actor_SpawnIceEffects(globalCtx, &this->actor, this->limbPos, phi_a3, 4, 0.3f, 0.2f);
    }
}

void func_808F13FC(EnKarebaba* this, GlobalContext* globalCtx) {
    if (this->actor.colChkInfo.damageEffect == 2) {
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
        this->drawDmgEffScale = 0.75f;
        this->drawDmgEffAlpha = 3.0f;
    } else if (this->actor.colChkInfo.damageEffect == 4) {
        this->drawDmgEffScale = 0.75f;
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_LIGHT_ORBS;
        this->drawDmgEffAlpha = 3.0f;
        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, this->collider2.info.bumper.hitPos.x,
                    this->collider2.info.bumper.hitPos.y, this->collider2.info.bumper.hitPos.z, 0, 0, 0,
                    CLEAR_TAG_SMALL_LIGHT_RAYS);
    } else if (this->actor.colChkInfo.damageEffect == 3) {
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX;
        this->drawDmgEffScale = 0.75f;
        this->drawDmgEffAlpha = 1.0f;
        this->drawDmgEffFrozenSteamScale = 1.125f;
    } else if (this->actor.colChkInfo.damageEffect == 5) {
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_ELECTRIC_SPARKS_MEDIUM;
        this->drawDmgEffScale = 0.75f;
        this->drawDmgEffAlpha = 3.0f;
    }
}

void func_808F152C(EnKarebaba* this) {
    this->collider2.dim.radius = 7;
    this->collider2.dim.height = 25;
    this->collider2.base.colType = COLTYPE_HARD;
    this->collider2.base.acFlags |= AC_HARD;
    this->collider1.dim.height = 25;
}

void func_808F155C(EnKarebaba* this) {
    Actor_SetScale(&this->actor, 0.0f);
    this->actor.shape.rot.x = -0x4000;
    this->unk_1EE = 0;
    this->actor.world.pos.y = this->actor.home.pos.y + 14.0f;
    this->actionFunc = func_808F15B0;
}

void func_808F15B0(EnKarebaba* this, GlobalContext* globalCtx) {
    f32 sp1C;

    this->unk_1EE++;
    sp1C = this->unk_1EE * 0.05f;
    Actor_SetScale(&this->actor, 0.005f * sp1C);
    this->actor.world.pos.y = this->actor.home.pos.y + (14.0f * sp1C);
    if (this->unk_1EE == 20) {
        func_808F1648(this);
    }
}

void func_808F1648(EnKarebaba* this) {
    Actor_SetScale(&this->actor, 0.005f);
    this->actor.shape.rot.x = -0x4000;
    this->actor.world.pos.y = this->actor.home.pos.y + 14.0f;
    this->actionFunc = func_808F169C;
}

void func_808F169C(EnKarebaba* this, GlobalContext* globalCtx) {
    if ((this->actor.xzDistToPlayer < 200.0f) && (fabsf(this->actor.playerHeightRel) < 30.0f)) {
        func_808F16FC(this);
    }
}

void func_808F16FC(EnKarebaba* this) {
    Animation_Change(&this->skelAnime, &object_dekubaba_Anim_0002B8, 4.0f, 0.0f,
                     Animation_GetLastFrame(&object_dekubaba_Anim_0002B8), 0, -3.0f);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_DEKU_WAKEUP);
    this->actionFunc = func_808F1778;
}

void func_808F1778(EnKarebaba* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);

    if (Math_StepToF(&this->actor.scale.x, 0.01f, 0.0005f) && (this->actor.params == ENKAREBABA_2)) {
        func_808F1878(this);
    }

    this->actor.scale.z = this->actor.scale.x;
    this->actor.scale.y = this->actor.scale.x;

    if ((this->actor.params == ENKAREBABA_1) &&
        Math_StepToF(&this->actor.world.pos.y, this->actor.home.pos.y + 60.0f, 5.0f)) {
        func_808F1878(this);
    }

    this->actor.shape.rot.y += 0x1999;
    EffectSsHahen_SpawnBurst(globalCtx, &this->actor.home.pos, 3.0f, 0, 12, 5, 1, -1, 10, NULL);
}

void func_808F1878(EnKarebaba* this) {
    if (this->actionFunc != func_808F1A58) {
        Actor_SetScale(&this->actor, 0.01f);

        this->collider2.base.colType = COLTYPE_HIT6;
        this->collider2.base.acFlags &= ~AC_HARD;
        this->collider2.dim.radius = 15;

        if (this->actor.params == ENKAREBABA_1) {
            this->collider2.dim.height = 80;
            this->collider1.dim.height = 80;
        } else {
            this->collider2.dim.height = 35;
            this->collider1.dim.height = 35;
        }
    }

    this->unk_1EE = 40;
    this->actionFunc = func_808F190C;
}

void func_808F190C(EnKarebaba* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    SkelAnime_Update(&this->skelAnime);

    if (this->unk_1EE != 0) {
        this->unk_1EE--;
    }

    if (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 12.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_MIZUBABA1_MOUTH);
    }

    if (this->collider2.base.acFlags & AC_HIT) {
        func_808F13FC(this, globalCtx);
        if (this->actor.params == ENKAREBABA_1) {
            func_808F1BF8(this);
        } else {
            func_808F1FAC(this);
        }
        Enemy_StartFinishingBlow(globalCtx, &this->actor);
    } else if (Math_Vec3f_DistXZ(&this->actor.home.pos, &player->actor.world.pos) > 240.0f) {
        func_808F220C(this);
    } else if ((this->unk_1EE == 0) && (this->actor.params == ENKAREBABA_1)) {
        func_808F1A3C(this);
    }
}

void func_808F1A3C(EnKarebaba* this) {
    this->unk_1EE = 40;
    this->actionFunc = func_808F1A58;
}

void func_808F1A58(EnKarebaba* this, GlobalContext* globalCtx) {
    s32 phi_v0;
    f32 sp28;

    if (this->unk_1EE != 0) {
        this->unk_1EE--;
    }

    SkelAnime_Update(&this->skelAnime);

    if (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 12.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_MIZUBABA1_MOUTH);
    }

    phi_v0 = 20 - this->unk_1EE;
    phi_v0 = 20 - ABS_ALT(phi_v0);
    if (phi_v0 > 10) {
        phi_v0 = 10;
    }

    this->collider1.dim.radius = sCylinderInit2.dim.radius + (phi_v0 * 2);
    this->actor.shape.rot.x = 0xC000 - (phi_v0 << 8);
    this->actor.shape.rot.y += phi_v0 * 0x2C0;
    this->actor.world.pos.y = (Math_SinS(this->actor.shape.rot.x) * -60.0f) + this->actor.home.pos.y;

    sp28 = Math_CosS(this->actor.shape.rot.x) * 60.0f;
    this->actor.world.pos.x = (Math_SinS(this->actor.shape.rot.y) * sp28) + this->actor.home.pos.x;
    this->actor.world.pos.z = (Math_CosS(this->actor.shape.rot.y) * sp28) + this->actor.home.pos.z;

    if (this->collider2.base.acFlags & AC_HIT) {
        func_808F13FC(this, globalCtx);
        func_808F1BF8(this);
        Enemy_StartFinishingBlow(globalCtx, &this->actor);
    } else if (this->unk_1EE == 0) {
        func_808F1878(this);
    }
}

void func_808F1BF8(EnKarebaba* this) {
    if (this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
        this->unk_1EE = 0;
        this->actor.gravity = -0.8f;
        this->actor.velocity.y = 4.0f;
        this->actor.world.rot.y = BINANG_ROT180(this->actor.shape.rot.y);
        this->actor.speedXZ = 3.0f;
    } else {
        this->unk_1EE = 3;
    }

    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_DEKU_JR_DEAD);
    this->actor.flags |= (ACTOR_FLAG_10 | ACTOR_FLAG_20);
    this->actionFunc = func_808F1C84;
}

void func_808F1C84(EnKarebaba* this, GlobalContext* globalCtx) {
    s32 i;
    Vec3f sp78;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;

    if (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
        this->unk_1EE--;
        if (this->unk_1EE == 0) {
            this->actor.gravity = -0.8f;
            this->actor.speedXZ = 3.0f;
            this->actor.velocity.y = 4.0f;
            this->actor.world.rot.y = BINANG_ROT180(this->actor.shape.rot.y);
            func_808F1374(this, globalCtx);
        }
    } else {
        Math_StepToF(&this->actor.speedXZ, 0.0f, 0.1f);

        if (this->unk_1EE == 0) {
            Math_ScaledStepToS(&this->actor.shape.rot.x, 0x4800, 0x71C);
            EffectSsHahen_SpawnBurst(globalCtx, &this->actor.world.pos, 3.0f, 0, 12, 5, 1, -1, 10, NULL);

            if ((this->actor.scale.x > 0.005f) && ((this->actor.bgCheckFlags & 2) || (this->actor.bgCheckFlags & 8))) {
                this->actor.scale.z = 0.0f;
                this->actor.scale.y = 0.0f;
                this->actor.scale.x = 0.0f;
                this->actor.speedXZ = 0.0f;
                this->actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_4);
                EffectSsHahen_SpawnBurst(globalCtx, &this->actor.world.pos, 3.0f, 0, 12, 5, 15, -1, 10, NULL);
            }

            if (this->actor.bgCheckFlags & 2) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_EYEGOLE_ATTACK);
                this->unk_1EE = 1;
            }
        } else if (this->unk_1EE == 1) {
            Math_Vec3f_Copy(&sp78, &this->actor.world.pos);

            temp_f24 = Math_SinS(this->actor.shape.rot.x) * 20.0f;
            temp_f20 = (-20.0f * Math_CosS(this->actor.shape.rot.x)) * Math_SinS(this->actor.shape.rot.y);
            temp_f22 = (-20.0f * Math_CosS(this->actor.shape.rot.x)) * Math_CosS(this->actor.shape.rot.y);

            for (i = 0; i < 4; i++) {
                func_800B1210(globalCtx, &sp78, &gZeroVec3f, &gZeroVec3f, 500, 50);
                sp78.x += temp_f20;
                sp78.y += temp_f24;
                sp78.z += temp_f22;
            }

            func_800B1210(globalCtx, &this->actor.home.pos, &gZeroVec3f, &gZeroVec3f, 500, 100);
            func_808F20FC(this, globalCtx);
        }
    }
}

void func_808F1FAC(EnKarebaba* this) {
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_DEKU_JR_DEAD);
    this->actor.flags |= (ACTOR_FLAG_10 | ACTOR_FLAG_20);
    this->actor.flags &= ~ACTOR_FLAG_1;
    if (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
        this->unk_1EE = 3;
    }
    this->actionFunc = func_808F200C;
}

void func_808F200C(EnKarebaba* this, GlobalContext* globalCtx) {
    if (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
        this->unk_1EE--;
        if (this->unk_1EE == 0) {
            func_808F1374(this, globalCtx);
        }
    } else {
        if (Math_StepToF(&this->actor.scale.x, 0.0f, 0.0005f)) {
            Item_DropCollectible(globalCtx, &this->actor.world.pos, ITEM00_NUTS_1);
            func_808F238C(this);
        } else {
            EffectSsHahen_SpawnBurst(globalCtx, &this->actor.world.pos, 3.0f, 0, 12, 5, 1, -1, 10, NULL);
            Math_StepToF(&this->actor.world.pos.y, this->actor.home.pos.y, 1.0f);
        }
        this->actor.scale.y = this->actor.scale.x;
        this->actor.scale.z = this->actor.scale.x;
    }
}

void func_808F20FC(EnKarebaba* this, GlobalContext* globalCtx) {
    Actor_SetScale(&this->actor, 0.03f);
    this->actor.shape.rot.x -= 0x4000;
    this->actor.shape.yOffset = 1000.0f;
    this->actor.gravity = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->actor.shape.shadowScale = 3.0f;
    func_800BC154(globalCtx, &globalCtx->actorCtx, &this->actor, 8);
    this->unk_1EE = 200;
    this->actor.flags &= ~ACTOR_FLAG_20;
    this->drawDmgEffAlpha = 0.0f;
    this->actionFunc = func_808F21A4;
}

void func_808F21A4(EnKarebaba* this, GlobalContext* globalCtx) {
    if (this->unk_1EE != 0) {
        this->unk_1EE--;
    }

    if (Actor_HasParent(&this->actor, globalCtx) || (this->unk_1EE == 0)) {
        func_808F238C(this);
    } else {
        Actor_PickUpNearby(&this->actor, globalCtx, GI_STICKS_1);
    }
}

void func_808F220C(EnKarebaba* this) {
    Animation_Change(&this->skelAnime, &object_dekubaba_Anim_0002B8, -3.0f,
                     Animation_GetLastFrame(&object_dekubaba_Anim_0002B8), 0.0f, 2, -3.0f);
    func_808F152C(this);
    this->actionFunc = func_808F228C;
}

void func_808F228C(EnKarebaba* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);

    if (Math_StepToF(&this->actor.scale.x, 0.005f, 0.0005f) && (this->actor.params == ENKAREBABA_2)) {
        func_808F1648(this);
    }

    this->actor.scale.z = this->actor.scale.x;
    this->actor.scale.y = this->actor.scale.x;

    if ((this->actor.params == ENKAREBABA_1) &&
        Math_StepToF(&this->actor.world.pos.y, this->actor.home.pos.y + 14.0f, 5.0f)) {
        func_808F1648(this);
    }

    this->actor.shape.rot.y += 0x1999;
    EffectSsHahen_SpawnBurst(globalCtx, &this->actor.home.pos, 3.0f, 0, 12, 5, 1, -1, 10, NULL);
}

void func_808F238C(EnKarebaba* this) {
    Animation_Change(&this->skelAnime, &object_dekubaba_Anim_0002B8, 0.0f, 0.0f, 0.0f, 2, 0.0f);
    func_808F152C(this);
    this->actor.shape.rot.x = -0x4000;
    this->unk_1EE = 200;
    this->actor.parent = NULL;
    this->actor.shape.shadowScale = 0.0f;
    this->drawDmgEffAlpha = 0.0f;
    Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.home.pos);
    this->actionFunc = func_808F254C;
}

void func_808F241C(EnKarebaba* this, GlobalContext* globalCtx) {
    f32 sp1C;

    this->unk_1EE++;
    sp1C = this->unk_1EE * 0.05f;
    Actor_SetScale(&this->actor, 0.005f * sp1C);
    this->actor.world.pos.y = this->actor.home.pos.y + (14.0f * sp1C);

    if (this->unk_1EE == 20) {
        this->actor.flags &= ~ACTOR_FLAG_10;
        this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_4);
        if (this->actor.params == ENKAREBABA_1) {
            func_800BC154(globalCtx, &globalCtx->actorCtx, &this->actor, 5);
        }
        func_808F1648(this);
    }
}

void func_808F24F8(EnKarebaba* this) {
    this->actor.shape.yOffset = 0.0f;
    this->actor.shape.shadowScale = 22.0f;
    this->collider1.dim.radius = sCylinderInit2.dim.radius;
    Actor_SetScale(&this->actor, 0.0f);
    this->actionFunc = func_808F241C;
}

void func_808F254C(EnKarebaba* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);

    if (this->unk_1EE != 0) {
        this->unk_1EE--;
    }

    if (this->unk_1EE == 0) {
        func_808F24F8(this);
    }
}

void EnKarebaba_Update(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnKarebaba* this = THIS;
    f32 max;

    this->actionFunc(this, globalCtx);

    if (this->drawDmgEffAlpha > 0.0f) {
        if (this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
            Math_StepToF(&this->drawDmgEffAlpha, 0.0f, 0.05f);
            this->drawDmgEffScale = (this->drawDmgEffAlpha + 1.0f) * 0.375f;
            if (this->drawDmgEffScale > 0.75f) {
                this->drawDmgEffScale = 0.75f;
            } else {
                this->drawDmgEffScale = this->drawDmgEffScale;
            }
        } else if (!Math_StepToF(&this->drawDmgEffFrozenSteamScale, 0.75f, 0.01875f)) {
            func_800B9010(&this->actor, NA_SE_EV_ICE_FREEZE - SFX_FLAG);
        }
    }

    if (this->actionFunc != func_808F254C) {
        if (this->actionFunc == func_808F1C84) {
            Actor_MoveWithGravity(&this->actor);
            Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 10.0f, 15.0f, 10.0f, 5);
        } else {
            Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
            if (this->unk_22C == 0) {
                this->unk_22C = this->actor.floorPoly;
            }
        }

        if ((this->actionFunc != func_808F1C84) && (this->actionFunc != func_808F200C) &&
            (this->actionFunc != func_808F21A4)) {
            if ((this->actionFunc != func_808F241C) && (this->actionFunc != func_808F15B0)) {
                CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
                CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider2.base);
            }

            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
            Actor_SetFocus(&this->actor, (this->actor.scale.x * 10.0f) / 0.01f);

            max = this->actor.home.pos.y + 40.0f;
            this->actor.focus.pos.x = this->actor.home.pos.x;
            this->actor.focus.pos.y = CLAMP_MAX(this->actor.focus.pos.y, max);
            this->actor.focus.pos.z = this->actor.home.pos.z;
        }
    }
}

void func_808F280C(EnKarebaba* this, GlobalContext* globalCtx) {
    MtxF sp40;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C448(globalCtx->state.gfxCtx);

    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 0, 0, 0, 255);

    func_800C0094(this->unk_22C, this->actor.home.pos.x, this->actor.home.pos.y, this->actor.home.pos.z, &sp40);
    Matrix_InsertMatrix(&sp40, MTXMODE_NEW);
    Matrix_Scale(0.15f, 1.0f, 0.15f, MTXMODE_APPLY);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, gCircleShadowDL);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void EnKarebaba_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnKarebaba* this = THIS;
    s32 i;
    s32 sp94;
    s16 limbCount;
    f32 sp8C = 0.01f;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    Math_Vec3f_Copy(this->limbPos, &this->actor.world.pos);

    if (this->actionFunc == func_808F21A4) {
        if ((this->unk_1EE > 40) || (this->unk_1EE & 1)) {
            Matrix_InsertTranslation(0.0f, 0.0f, 200.0f, MTXMODE_APPLY);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, object_dekubaba_DL_003070);
        }
    } else if (this->actionFunc != func_808F254C) {
        func_800AE2A0(globalCtx, &D_808F2E28, 1, 2);
        SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, NULL, NULL, NULL);
        Matrix_InsertTranslation(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z,
                                 MTXMODE_NEW);

        if ((this->actionFunc == func_808F241C) || (this->actionFunc == func_808F200C) ||
            (this->actionFunc == func_808F15B0)) {
            sp8C = this->unk_1EE * 0.0005f;
        }

        Matrix_Scale(sp8C, sp8C, sp8C, MTXMODE_APPLY);
        Matrix_InsertRotation(this->actor.shape.rot.x, this->actor.shape.rot.y, 0, MTXMODE_APPLY);

        if (this->actor.params == ENKAREBABA_2) {
            sp94 = 1;
        } else if (this->actionFunc == func_808F1C84) {
            sp94 = 2;
        } else {
            sp94 = 3;
        }

        for (i = 0; i < sp94; i++) {
            Matrix_InsertTranslation(0.0f, 0.0f, -2000.0f, MTXMODE_APPLY);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, D_808F2E2C[i]);

            Matrix_GetStateTranslation(&this->limbPos[1 + i]);
            if ((i == 0) && (this->actionFunc == func_808F1C84)) {
                Matrix_GetStateTranslation(&this->actor.focus.pos);
            }
        }

        func_800AE5A0(globalCtx);
    }

    func_800AE2A0(globalCtx, &D_808F2E28, 1, 2);
    Matrix_InsertTranslation(this->actor.home.pos.x, this->actor.home.pos.y, this->actor.home.pos.z, MTXMODE_NEW);

    if (this->actionFunc != func_808F15B0) {
        sp8C = 0.01f;
    }

    Matrix_Scale(sp8C, sp8C, sp8C, MTXMODE_APPLY);
    Matrix_RotateY(this->actor.home.rot.y, MTXMODE_APPLY);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, object_dekubaba_DL_0010F0);

    if (this->actionFunc == func_808F1C84) {
        Matrix_InsertRotation(-0x4000, this->actor.shape.rot.y - this->actor.home.rot.y, 0, MTXMODE_APPLY);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, object_dekubaba_DL_001828);

        Matrix_GetStateTranslation(&this->limbPos[3]);
    }

    func_800AE5A0(globalCtx);

    if (this->actor.params == ENKAREBABA_2) {
        limbCount = 1;
    } else {
        limbCount = ARRAY_COUNT(this->limbPos);
    }

    Actor_DrawDamageEffects(globalCtx, &this->actor, this->limbPos, limbCount, this->drawDmgEffScale,
                            this->drawDmgEffFrozenSteamScale, this->drawDmgEffAlpha, this->drawDmgEffType);

    if (this->unk_22C != 0) {
        func_808F280C(this, globalCtx);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
