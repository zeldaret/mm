/*
 * File: z_en_po_sisters.c
 * Overlay: ovl_En_Po_Sisters
 * Description: Poe Sisters
 */

#include "z_en_po_sisters.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "objects/object_po_sisters/object_po_sisters.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_1000 | ACTOR_FLAG_4000)

#define THIS ((EnPoSisters*)thisx)

void EnPoSisters_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPoSisters_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPoSisters_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPoSisters_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B1AA88(EnPoSisters* this);
void func_80B1AAE8(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1ABB8(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1AC40(EnPoSisters* this);
void func_80B1ACB8(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1AE28(EnPoSisters* this);
void func_80B1AE3C(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1AF8C(EnPoSisters* this);
void func_80B1B020(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1B0E0(EnPoSisters* this);
void func_80B1B168(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1B2F0(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1B444(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1B5B4(EnPoSisters* this);
void func_80B1B628(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1B70C(EnPoSisters* this);
void func_80B1B7BC(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1B860(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1B940(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1BA3C(EnPoSisters* this);
void func_80B1BA90(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1BC4C(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1BCA0(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1BCF0(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1BE4C(EnPoSisters* this, s32 arg1);
void func_80B1BF2C(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1C030(EnPoSisters* this);
void func_80B1C0A4(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1C2E8(EnPoSisters* this);
void func_80B1C340(EnPoSisters* this, GlobalContext* globalCtx);

static Color_RGBA8 D_80B1DA30[] = {
    { 255, 170, 255, 255 },
    { 255, 200, 0, 255 },
    { 0, 170, 255, 255 },
    { 170, 255, 0, 255 },
};

static Color_RGBA8 D_80B1DA40[] = {
    { 100, 0, 255, 255 },
    { 255, 0, 0, 255 },
    { 0, 0, 255, 255 },
    { 0, 150, 0, 255 },
};

const ActorInit En_Po_Sisters_InitVars = {
    ACTOR_EN_PO_SISTERS,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_PO_SISTERS,
    sizeof(EnPoSisters),
    (ActorFunc)EnPoSisters_Init,
    (ActorFunc)EnPoSisters_Destroy,
    (ActorFunc)EnPoSisters_Update,
    (ActorFunc)EnPoSisters_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT3,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x00, 0x08 },
        { 0xF7CBFFFE, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON | BUMP_HOOKABLE,
        OCELEM_ON,
    },
    { 18, 60, 15, { 0, 0, 0 } },
};

static CollisionCheckInfoInit sColChkInfoInit = { 6, 25, 60, 50 };

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0xF),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
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
    /* Spin attack    */ DMG_ENTRY(1, 0xE),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 7, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 6000, ICHAIN_STOP),
};

void EnPoSisters_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnPoSisters* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 50.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &object_po_sisters_Skel_0065C8, &object_po_sisters_Anim_0014CC,
                   this->jointTable, this->morphTable, 12);
    this->unk_226 = 255;
    this->unk_227 = 255;
    this->unk_228 = 210;
    this->unk_229 = 255;
    this->lightNode = LightContext_InsertLight(globalCtx, &globalCtx->lightCtx, &this->lightInfo);
    Lights_PointGlowSetInfo(&this->lightInfo, this->actor.home.pos.x, this->actor.home.pos.y, this->actor.home.pos.z, 0,
                            0, 0, 0);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    this->unk_18C = ENPOSISTERS_GET_300(thisx);
    this->actor.hintId = this->unk_18C + 80;
    this->unk_18D = ENPOSISTERS_GET_C00(thisx);
    this->unk_18E = 32;
    this->unk_18F = 20;
    this->unk_190 = 1;
    this->unk_191 = 0x20;
    this->unk_2EC = 110.0f;
    thisx->flags &= ~1;

    if (ENPOSISTERS_GET_1000(&this->actor)) {
        func_80B1AA88(this);
    } else if (this->unk_18C == 0) {
        if (this->unk_18D == 0) {
            this->actor.colChkInfo.health = 8;
            this->collider.info.toucher.damage = 16;
            this->collider.base.ocFlags1 = (OC1_TYPE_PLAYER | OC1_ON);
            func_80B1BCF0(this, globalCtx);
            func_80B1C2E8(this);
        } else {
            this->actor.flags &= ~(ACTOR_FLAG_200 | ACTOR_FLAG_4000);
            this->collider.info.elemType = ELEMTYPE_UNK4;
            this->collider.info.bumper.dmgFlags |= (0x40000 | 0x1);
            this->collider.base.ocFlags1 = OC1_NONE;
            func_80B1BE4C(this, false);
        }
    } else {
        func_80B1C2E8(this);
    }
    this->actor.params &= 0xFF;
}

void EnPoSisters_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnPoSisters* this = THIS;

    LightContext_RemoveLight(globalCtx, &globalCtx->lightCtx, this->lightNode);
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80B1A648(EnPoSisters* this, s32 arg1, Vec3f* pos) {
    s32 i;
    Vec3f* ptr;
    f32 temp_f20 = arg1;

    for (i = 0; i < this->unk_190; i++) {
        ptr = &this->unk_22C[i];
        ptr->x = Math_SinS(this->actor.shape.rot.y + (this->unk_192 * 0x800) + (i * 0x2000)) * (SQ(temp_f20) * 0.1f) +
                 pos->x;
        ptr->z = Math_CosS(this->actor.shape.rot.y + (this->unk_192 * 0x800) + (i * 0x2000)) * (SQ(temp_f20) * 0.1f) +
                 pos->z;
        ptr->y = pos->y + temp_f20;
    }
}

void func_80B1A768(EnPoSisters* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    f32 sp20;

    if ((this->unk_18D == 0) || (this->actionFunc != func_80B1B444)) {
        if (((player->swordState == 0) || (player->swordAnimation >= 30)) &&
            ((player->actor.world.pos.y - player->actor.floorHeight) < 1.0f)) {
            Math_StepToF(&this->unk_2EC, 110.0f, 3.0f);
        } else {
            Math_StepToF(&this->unk_2EC, 170.0f, 10.0f);
        }
        sp20 = this->unk_2EC;
    } else if (this->unk_18D != 0) {
        sp20 = this->actor.parent->xzDistToPlayer;
    }

    this->actor.world.pos.x = (Math_SinS(BINANG_ROT180(this->actor.shape.rot.y)) * sp20) + player->actor.world.pos.x;
    this->actor.world.pos.z = (Math_CosS(BINANG_ROT180(this->actor.shape.rot.y)) * sp20) + player->actor.world.pos.z;
}

void func_80B1A894(EnPoSisters* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    Math_ApproachF(&this->actor.world.pos.y, player->actor.world.pos.y + 5.0f, 0.5f, 3.0f);

    if (this->unk_18E == 0) {
        this->unk_18E = 32;
        if (this->unk_18E) {}
    }

    if (this->unk_18E != 0) {
        this->unk_18E--;
    }

    this->actor.world.pos.y += (2.0f + (0.5f * Rand_ZeroOne())) * Math_SinS(this->unk_18E * 0x800);
    if ((this->unk_229 == 255) && (this->actionFunc != func_80B1B168) && (this->actionFunc != func_80B1B020)) {
        if (this->actionFunc == func_80B1B628) {
            func_800B9010(&this->actor, NA_SE_EN_PO_AWAY - SFX_FLAG);
        } else {
            func_800B9010(&this->actor, NA_SE_EN_PO_FLY - SFX_FLAG);
        }
    }
}

void func_80B1A9B0(EnPoSisters* this, GlobalContext* globalCtx) {
    if (this->actor.isTargeted && (this->unk_229 == 255)) {
        if (this->unk_18F != 0) {
            this->unk_18F--;
        }
    } else {
        this->unk_18F = 20;
    }

    if (this->unk_229 == 0) {
        if (this->unk_194 != 0) {
            this->unk_194--;
        }
    }

    if ((this->actionFunc != func_80B1B020) && (this->actionFunc != func_80B1B168) &&
        (this->actionFunc != func_80B1B444)) {
        if (this->unk_18F == 0) {
            func_80B1B70C(this);
        } else if ((this->unk_194 == 0) && (this->unk_229 == 0)) {
            func_80B1B860(this, globalCtx);
        }
    }
}

void func_80B1AA88(EnPoSisters* this) {
    Animation_MorphToLoop(&this->skelAnime, &object_po_sisters_Anim_0014CC, -3.0f);
    this->actor.speedXZ = 0.0f;
    this->unk_192 = Rand_S16Offset(100, 50);
    this->actionFunc = func_80B1AAE8;
}

void func_80B1AAE8(EnPoSisters* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if (DECR(this->unk_192) == 0) {
        this->unk_192 = Rand_S16Offset(100, 50);
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PO_LAUGH2);
    }
}

void func_80B1AB5C(EnPoSisters* this) {
    Animation_MorphToLoop(&this->skelAnime, &object_po_sisters_Anim_0014CC, -3.0f);
    this->unk_192 = Rand_S16Offset(2, 3);
    this->actor.speedXZ = 0.0f;
    this->actionFunc = func_80B1ABB8;
}

void func_80B1ABB8(EnPoSisters* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
        if (this->unk_192 != 0) {
            this->unk_192--;
        }
    }

    if ((this->unk_192 == 0) || (this->actor.xzDistToPlayer < 600.0f)) {
        func_80B1AC40(this);
    }
}

void func_80B1AC40(EnPoSisters* this) {
    if (this->actionFunc != func_80B1AE3C) {
        Animation_MorphToLoop(&this->skelAnime, &object_po_sisters_Anim_000D40, -3.0f);
    }
    this->unk_192 = Rand_S16Offset(15, 3);
    this->unk_191 |= (0x6 | 0x1);
    this->actionFunc = func_80B1ACB8;
}

void func_80B1ACB8(EnPoSisters* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    Math_StepToF(&this->actor.speedXZ, 1.0f, 0.2f);
    if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
        if (this->unk_192 != 0) {
            this->unk_192--;
        }
    }

    if ((this->actor.xzDistToPlayer < 600.0f) && (fabsf(this->actor.playerHeightRel + 5.0f) < 30.0f)) {
        func_80B1AE28(this);
    } else if ((this->unk_192 == 0) && Math_StepToF(&this->actor.speedXZ, 0.0f, 0.2f)) {
        func_80B1AB5C(this);
    }

    if (this->actor.bgCheckFlags & 8) {
        Math_ScaledStepToS(&this->actor.world.rot.y, Actor_YawToPoint(&this->actor, &this->actor.home.pos), 0x71C);
    } else if (Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos) > 600.0f) {
        Math_ScaledStepToS(&this->actor.world.rot.y, Actor_YawToPoint(&this->actor, &this->actor.home.pos), 0x71C);
    }
}

void func_80B1AE28(EnPoSisters* this) {
    this->actionFunc = func_80B1AE3C;
}

void func_80B1AE3C(EnPoSisters* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 sp22;

    SkelAnime_Update(&this->skelAnime);
    sp22 = this->actor.yawTowardsPlayer - player->actor.shape.rot.y;
    Math_StepToF(&this->actor.speedXZ, 2.0f, 0.2f);

    if (sp22 > 0x3000) {
        Math_ScaledStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer + 0x3000, 0x71C);
    } else if (sp22 < -0x3000) {
        Math_ScaledStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer - 0x3000, 0x71C);
    } else {
        Math_ScaledStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 0x71C);
    }

    if ((this->actor.xzDistToPlayer < 320.0f) && (fabsf(this->actor.playerHeightRel + 5.0f) < 30.0f)) {
        func_80B1AF8C(this);
    } else if (this->actor.xzDistToPlayer > 720.0f) {
        func_80B1AC40(this);
    }
}

void func_80B1AF8C(EnPoSisters* this) {
    if (this->unk_229 != 0) {
        this->collider.base.colType = COLTYPE_METAL;
        this->collider.base.acFlags |= AC_HARD;
    }

    Animation_MorphToLoop(&this->skelAnime, &object_po_sisters_Anim_000114, -5.0f);
    this->actor.speedXZ = 0.0f;
    this->unk_192 = Animation_GetLastFrame(&object_po_sisters_Anim_000114.common) * 3 + 3;
    this->unk_191 &= ~2;
    this->actionFunc = func_80B1B020;
}

void func_80B1B020(EnPoSisters* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if (this->unk_192 != 0) {
        this->unk_192--;
    }

    this->actor.shape.rot.y += ((s32)((this->skelAnime.endFrame + 1.0f) * 3.0f) - this->unk_192) * 0x180;

    if ((this->unk_192 == 18) || (this->unk_192 == 7)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PO_ROLL);
    } else if (this->unk_192 == 0) {
        func_80B1B0E0(this);
    }
}

void func_80B1B0E0(EnPoSisters* this) {
    this->actor.speedXZ = 5.0f;
    if (this->unk_18C == 0) {
        this->collider.base.colType = COLTYPE_METAL;
        this->collider.base.acFlags |= AC_HARD;
        Animation_MorphToLoop(&this->skelAnime, &object_po_sisters_Anim_000114, -5.0f);
    }
    this->unk_192 = 5;
    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    this->unk_191 |= 8;
    this->actionFunc = func_80B1B168;
}

void func_80B1B168(EnPoSisters* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
        if (this->unk_192 != 0) {
            this->unk_192--;
        }
    }

    this->actor.shape.rot.y += (s32)(1152.0f * this->skelAnime.endFrame);

    if (this->unk_192 == 0) {
        s16 rotY = this->actor.shape.rot.y - this->actor.world.rot.y;

        if (ABS_ALT(rotY) < 0x1000) {
            if (this->unk_18C != 0) {
                this->collider.base.colType = COLTYPE_HIT3;
                this->collider.base.acFlags &= ~AC_HARD;
                func_80B1AC40(this);
            } else {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PO_LAUGH2);
                func_80B1BE4C(this, globalCtx);
            }
        }
    }
    if (Animation_OnFrame(&this->skelAnime, 1.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PO_ROLL);
    }
}

void func_80B1B280(EnPoSisters* this) {
    Animation_MorphToLoop(&this->skelAnime, &object_po_sisters_Anim_000D40, -3.0f);
    this->actor.world.rot.y = BINANG_ROT180(this->actor.yawTowardsPlayer);
    if (this->unk_18C != 0) {
        this->collider.base.colType = COLTYPE_HIT3;
        this->collider.base.acFlags &= ~AC_HARD;
    }
    this->actionFunc = func_80B1B2F0;
}

void func_80B1B2F0(EnPoSisters* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    this->actor.shape.rot.y -= (s16)(this->actor.speedXZ * 10.0f * 128.0f);
    if (Math_StepToF(&this->actor.speedXZ, 0.0f, 0.1f)) {
        this->actor.world.rot.y = this->actor.shape.rot.y;
        if (this->unk_18C != 0) {
            func_80B1AC40(this);
        } else {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PO_LAUGH2);
            func_80B1BE4C(this, globalCtx);
        }
    }
}

void func_80B1B3A8(EnPoSisters* this) {
    Animation_MorphToPlayOnce(&this->skelAnime, &object_po_sisters_Anim_0008C0, -3.0f);
    if (this->collider.base.ac != NULL) {
        func_800BE504(&this->actor, &this->collider);
    }

    if (this->unk_18C != 0) {
        this->actor.speedXZ = 10.0f;
    }

    this->unk_191 &= ~(0x8 | 0x2 | 0x1);
    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 16);
    this->actionFunc = func_80B1B444;
}

void func_80B1B444(EnPoSisters* this, GlobalContext* globalCtx) {
    s32 temp_f18;

    if (SkelAnime_Update(&this->skelAnime) && !(this->actor.flags & ACTOR_FLAG_8000)) {
        if (this->actor.colChkInfo.health != 0) {
            if (this->unk_18C != 0) {
                func_80B1B5B4(this);
            } else if (this->unk_18D != 0) {
                func_80B1BE4C(this, 0);
            } else {
                func_80B1BE4C(this, globalCtx);
            }
        } else {
            func_80B1BA3C(this);
        }
    }

    if (this->unk_18D != 0) {
        Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.parent->shape.rot.y,
                           (this->unk_18D == 2) ? 0x800 : 0x400);
        temp_f18 = ((this->skelAnime.endFrame - this->skelAnime.curFrame) * 255.0f) / this->skelAnime.endFrame;
        this->unk_229 = CLAMP(temp_f18, 0, 255);
        this->actor.world.pos.y = this->actor.parent->world.pos.y;
        func_80B1A768(this, globalCtx);
    } else if (this->unk_18C != 0) {
        Math_StepToF(&this->actor.speedXZ, 0.0f, 0.5f);
    }
}

void func_80B1B5B4(EnPoSisters* this) {
    Animation_MorphToLoop(&this->skelAnime, &object_po_sisters_Anim_000A54, -3.0f);
    this->actor.world.rot.y = BINANG_ROT180(this->actor.shape.rot.y);
    this->unk_192 = 5;
    this->unk_191 |= (0x8 | 0x2 | 0x1);
    this->actor.speedXZ = 5.0f;
    this->actionFunc = func_80B1B628;
}

void func_80B1B628(EnPoSisters* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    Math_ScaledStepToS(&this->actor.world.rot.y, BINANG_ROT180(this->actor.yawTowardsPlayer), 0x71C);
    if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
        if (this->unk_192 != 0) {
            this->unk_192--;
        }
    }

    if (this->actor.bgCheckFlags & 8) {
        this->actor.world.rot.y = this->actor.shape.rot.y;
        this->unk_191 |= 2;
        func_80B1B70C(this);
    } else if ((this->unk_192 == 0) && (this->actor.xzDistToPlayer > 480.0f)) {
        this->actor.world.rot.y = this->actor.shape.rot.y;
        func_80B1AC40(this);
    }
}

void func_80B1B70C(EnPoSisters* this) {
    Animation_Change(&this->skelAnime, &object_po_sisters_Anim_00119C, 1.5f, 0.0f,
                     Animation_GetLastFrame(&object_po_sisters_Anim_00119C.common), 2, -3.0f);
    this->unk_194 = 100;
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->unk_191 &= ~(0x4 | 0x1);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PO_DISAPPEAR);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PO_LAUGH2);
    this->actionFunc = func_80B1B7BC;
}

void func_80B1B7BC(EnPoSisters* this, GlobalContext* globalCtx) {
    s32 temp_f18;

    if (SkelAnime_Update(&this->skelAnime)) {
        this->unk_229 = 0;
        this->collider.info.bumper.dmgFlags = (0x40000 | 0x1);
        func_80B1AC40(this);
    } else {
        temp_f18 = ((this->skelAnime.endFrame - this->skelAnime.curFrame) * 255.0f) / this->skelAnime.endFrame;
        this->unk_229 = CLAMP(temp_f18, 0, 255);
    }
}

void func_80B1B860(EnPoSisters* this, GlobalContext* globalCtx) {
    Animation_Change(&this->skelAnime, &object_po_sisters_Anim_00119C, 1.5f, 0.0f,
                     Animation_GetLastFrame(&object_po_sisters_Anim_00119C.common), 2, -3.0f);
    if (this->unk_18C == 0) {
        this->unk_2EC = 110.0f;
        func_80B1A768(this, globalCtx);
        this->unk_229 = 0;
        this->actor.draw = EnPoSisters_Draw;
    } else {
        this->actor.world.rot.y = this->actor.shape.rot.y;
    }

    this->unk_192 = 15;
    this->actor.speedXZ = 0.0f;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_APPEAR);
    this->unk_191 &= ~0x1;
    this->actionFunc = func_80B1B940;
}

void func_80B1B940(EnPoSisters* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime) != 0) {
        this->unk_229 = 255;
        if (this->unk_18C != 0) {
            this->unk_191 |= 1;
            this->collider.info.bumper.dmgFlags = ~(0x8000000 | 0x200000 | 0x100000 | 0x40000 | 0x1);
            if (this->unk_192 != 0) {
                this->unk_192--;
            }

            if (this->unk_192 == 0) {
                this->unk_18F = 20;
                func_80B1AC40(this);
            }
        } else {
            func_80B1C030(this);
        }
    } else {
        s32 temp_f18 = (this->skelAnime.curFrame * 255.0f) / this->skelAnime.endFrame;

        this->unk_229 = CLAMP(temp_f18, 0, 255);
        if (this->unk_18C == 0) {
            func_80B1A768(this, globalCtx);
        }
    }
}

void func_80B1BA3C(EnPoSisters* this) {
    this->unk_192 = 0;
    this->actor.speedXZ = 0.0f;
    this->actor.world.pos.y += 42.0f;
    this->actor.shape.yOffset = -6000.0f;
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->unk_191 = 0;
    this->actionFunc = func_80B1BA90;
}

void func_80B1BA90(EnPoSisters* this, GlobalContext* globalCtx) {
    s32 i;
    s32 end = this->unk_190;

    this->unk_192++;
    end++;
    if (end > ARRAY_COUNT(this->unk_22C)) {
        this->unk_190 = 8;
    } else {
        this->unk_190 = end;
    }

    for (end = this->unk_190 - 1; end > 0; end--) {
        this->unk_22C[end] = this->unk_22C[end - 1];
    }

    this->unk_22C[0].x =
        (Math_SinS((this->actor.shape.rot.y + (this->unk_192 * 0x3000)) - 0x4000) * (3000.0f * this->actor.scale.x)) +
        this->actor.world.pos.x;
    this->unk_22C[0].z =
        (Math_CosS((this->actor.shape.rot.y + (this->unk_192 * 0x3000)) - 0x4000) * (3000.0f * this->actor.scale.x)) +
        this->actor.world.pos.z;
    if (this->unk_192 < 8) {
        this->unk_22C[0].y = this->unk_22C[1].y - 9.0f;
    } else {
        this->unk_22C[0].y = this->unk_22C[1].y + 2.0f;
        if (this->unk_192 >= 16) {
            if (Math_StepToF(&this->actor.scale.x, 0.0f, 0.001f)) {
                func_80B1BC4C(this, globalCtx);
            }
            this->actor.scale.z = this->actor.scale.x;
            this->actor.scale.y = this->actor.scale.x;
        }
    }

    if (this->unk_192 == 16) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WIZ_DISAPPEAR);
    }
}

void func_80B1BC4C(EnPoSisters* this, GlobalContext* globalCtx) {
    this->unk_192 = 0;
    this->actor.world.pos.y = this->unk_22C[0].y;
    Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.world.pos, 0x80);
    this->actionFunc = func_80B1BCA0;
}

void func_80B1BCA0(EnPoSisters* this, GlobalContext* globalCtx) {
    this->unk_192++;
    if (this->unk_192 == 32) {
        Actor_MarkForDeath(&this->actor);
    } else {
        func_80B1A648(this, this->unk_192, &this->actor.world.pos);
    }
}

void func_80B1BCF0(EnPoSisters* this, GlobalContext* globalCtx) {
    Actor* sp4C =
        Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_PO_SISTERS, this->actor.world.pos.x,
                           this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, 0x400);
    Actor* sp48 =
        Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_PO_SISTERS, this->actor.world.pos.x,
                           this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, 0x800);
    Actor* sp44 =
        Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_PO_SISTERS, this->actor.world.pos.x,
                           this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, 0xC00);

    if ((sp4C == NULL) || (sp48 == NULL) || (sp44 == NULL)) {
        if (sp4C != NULL) {
            Actor_MarkForDeath(sp4C);
        }

        if (sp48 != NULL) {
            Actor_MarkForDeath(sp48);
        }

        if (sp44 != NULL) {
            Actor_MarkForDeath(sp44);
        }
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80B1BE4C(EnPoSisters* this, s32 arg1) {
    Vec3f sp34;

    this->actor.draw = NULL;
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->unk_194 = 100;
    this->unk_191 = 0x20;
    this->collider.base.colType = COLTYPE_HIT3;
    this->collider.base.acFlags &= ~AC_HARD;
    if (arg1) {
        sp34.x = this->actor.world.pos.x;
        sp34.y = this->actor.world.pos.y + 45.0f;
        sp34.z = this->actor.world.pos.z;
        func_800B3030(arg1, &sp34, &gZeroVec3f, &gZeroVec3f, 150, 0, 3);
    }
    Lights_PointSetColorAndRadius(&this->lightInfo, 0, 0, 0, 0);
    this->actionFunc = func_80B1BF2C;
}

void func_80B1BF2C(EnPoSisters* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    EnPoSisters* parent = (EnPoSisters*)this->actor.parent;

    if (this->unk_18D == 0) {
        if (this->unk_194 != 0) {
            this->unk_194--;
        }

        if (this->unk_194 == 0) {
            s32 rand = Rand_ZeroFloat(4.0f);

            this->actor.shape.rot.y = (rand * 0x4000) + this->actor.yawTowardsPlayer;
            this->actor.world.pos.y = player->actor.world.pos.y + 5.0f;
            func_80B1B860(this, globalCtx);
        }
    } else if (parent->actionFunc == func_80B1B940) {
        this->actor.shape.rot.y = this->actor.parent->shape.rot.y + (this->unk_18D * 0x4000);
        this->actor.world.pos.y = player->actor.world.pos.y + 5.0f;
        func_80B1B860(this, globalCtx);
    } else if (parent->actionFunc == func_80B1BA90) {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80B1C030(EnPoSisters* this) {
    Animation_MorphToLoop(&this->skelAnime, &object_po_sisters_Anim_000D40, -3.0f);
    this->unk_229 = 255;
    this->unk_192 = 300;
    this->unk_194 = 3;
    this->unk_191 |= (0x8 | 0x1);
    this->actor.flags |= ACTOR_FLAG_1;
    this->actionFunc = func_80B1C0A4;
}

void func_80B1C0A4(EnPoSisters* this, GlobalContext* globalCtx) {
    EnPoSisters* parent;

    if (this->unk_192 != 0) {
        this->unk_192--;
    }

    if (this->unk_194 > 0) {
        if (this->unk_192 >= 16) {
            SkelAnime_Update(&this->skelAnime);
            if (this->unk_18D == 0) {
                if (ABS_ALT(16 - this->unk_18E) < 14) {
                    this->actor.shape.rot.y +=
                        (s16)((0x580 - (this->unk_194 * 0x180)) * fabsf(Math_SinS(this->unk_18E * 0x800)));
                }

                if ((this->unk_192 >= 284) || (this->unk_192 < 31)) {
                    this->unk_191 |= 0x40;
                } else {
                    this->unk_191 &= ~0x40;
                }
            } else {
                this->actor.shape.rot.y = this->actor.parent->shape.rot.y + (this->unk_18D * 0x4000);
            }
        }
    }

    if (this->unk_18D == 0) {
        if ((this->unk_192 >= 284) || ((this->unk_192 < 31) && (this->unk_192 >= 16))) {
            this->unk_191 |= 0x40;
        } else {
            this->unk_191 &= ~0x40;
        }
    }

    if (this->unk_192 == 0) {
        if (this->unk_18D == 0) {
            func_80B1B0E0(this);
        } else {
            func_80B1BE4C(this, globalCtx);
        }
    } else if (this->unk_18D != 0) {
        parent = (EnPoSisters*)this->actor.parent;
        if (parent->actionFunc == func_80B1B444) {
            func_80B1B3A8(this);
        }
    } else if (this->unk_194 == 0) {
        this->unk_194 = -15;
    } else if (this->unk_194 < 0) {
        this->unk_194++;
        if (this->unk_194 == 0) {
            func_80B1B0E0(this);
        }
    }
    func_80B1A768(this, globalCtx);
}

void func_80B1C2E8(EnPoSisters* this) {
    Animation_PlayOnce(&this->skelAnime, &object_po_sisters_Anim_00119C);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_APPEAR);
    this->unk_229 = 0;
    this->unk_191 = 0x20;
    this->actionFunc = func_80B1C340;
}

void func_80B1C340(EnPoSisters* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        this->unk_229 = 255;
        this->actor.flags |= ACTOR_FLAG_1;
        this->unk_191 |= (0x10 | 0x8);
        if (this->unk_18C == 0) {
            func_80B1BE4C(this, globalCtx);
        } else {
            func_80B1AC40(this);
        }
    } else {
        f32 temp = this->skelAnime.curFrame / this->skelAnime.endFrame;
        s32 temp_f16 = 255.0f * temp;

        this->unk_229 = CLAMP(temp_f16, 0, 255);
    }
}

void func_80B1C408(EnPoSisters* this, GlobalContext* globalCtx) {
    Vec3f sp3C;

    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        Actor_SetDropFlag(&this->actor, &this->collider.info);

        if (this->unk_18D != 0) {
            ((EnPoSisters*)this->actor.parent)->unk_194--;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PO_LAUGH2);
            func_80B1BE4C(this, globalCtx);
            if (Rand_ZeroOne() < 0.2f) {
                sp3C.x = this->actor.world.pos.x;
                sp3C.y = this->actor.world.pos.y;
                sp3C.z = this->actor.world.pos.z;
                Item_DropCollectible(globalCtx, &sp3C, ITEM00_ARROWS_10);
            }
        } else if (this->collider.base.colType != 9) {
            if (this->actor.colChkInfo.damageEffect == 0xF) {
                this->actor.world.rot.y = this->actor.shape.rot.y;
                this->unk_191 |= 2;
                func_80B1B860(this, globalCtx);
            } else if ((this->unk_18C == 0) && (this->actor.colChkInfo.damageEffect == 0xE) &&
                       (this->actionFunc == func_80B1C0A4)) {
                if (this->unk_194 == 0) {
                    this->unk_194 = -45;
                }
            } else {
                if (Actor_ApplyDamage(&this->actor)) {
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PO_DAMAGE);
                } else {
                    Enemy_StartFinishingBlow(globalCtx, &this->actor);
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PO_SISTER_DEAD);
                }

                if (this->actor.colChkInfo.damageEffect == 4) {
                    this->drawDmgEffAlpha = 4.0f;
                    this->drawDmgEffScale = 0.5f;
                    Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG,
                                this->collider.info.bumper.hitPos.x, this->collider.info.bumper.hitPos.y,
                                this->collider.info.bumper.hitPos.z, 0, 0, 0, CLEAR_TAG_LARGE_LIGHT_RAYS);
                }
                func_80B1B3A8(this);
            }
        }
    }
}

void EnPoSisters_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnPoSisters* this = THIS;
    f32 temp_f2;
    Vec3f checkPos;
    s32 bgId;

    if (this->collider.base.atFlags & AT_HIT) {
        this->collider.base.atFlags &= ~AT_HIT;
        func_80B1B280(this);
    }

    func_80B1C408(this, globalCtx);
    if (this->unk_191 & 0x4) {
        func_80B1A9B0(this, globalCtx);
    }

    this->actionFunc(this, globalCtx);

    if (this->unk_191 & 0x8) {
        func_80B1A894(this, globalCtx);
    }

    Actor_MoveWithGravity(&this->actor);

    if (this->unk_191 & 0x10) {
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 0.0f, 5);
    } else {
        checkPos.x = this->actor.world.pos.x;
        checkPos.y = this->actor.world.pos.y + 10.0f;
        checkPos.z = this->actor.world.pos.z;
        this->actor.floorHeight =
            BgCheck_EntityRaycastFloor5(&globalCtx->colCtx, &this->actor.floorPoly, &bgId, &this->actor, &checkPos);
    }

    this->actor.shape.shadowAlpha = this->unk_229;
    Actor_SetFocus(&this->actor, 40.0f);

    if (this->drawDmgEffAlpha > 0.0f) {
        Math_StepToF(&this->drawDmgEffAlpha, 0.0f, 0.05f);
        if (this->unk_229 != 255) {
            temp_f2 = this->unk_229 * (1.0f / 255);
            if (temp_f2 < this->unk_229) {
                this->drawDmgEffAlpha = temp_f2;
            }
        }

        this->drawDmgEffScale = (this->drawDmgEffAlpha + 1.0f) * 0.25f;
        this->drawDmgEffScale = CLAMP_MAX(this->drawDmgEffScale, 0.5f);
    }

    if (this->unk_191 & (0x10 | 0x8 | 0x4 | 0x2 | 0x1)) {
        Collider_UpdateCylinder(&this->actor, &this->collider);
        if ((this->actionFunc == func_80B1B168) || (this->actionFunc == func_80B1B020)) {
            this->unk_190++;
            this->unk_190 = CLAMP_MAX(this->unk_190, ARRAY_COUNT(this->unk_22C));
        } else if (this->actionFunc != func_80B1BA90) {
            this->unk_190 = CLAMP_MIN(this->unk_190 - 1, 1);
        }

        if (this->actionFunc == func_80B1B168) {
            this->actor.flags |= ACTOR_FLAG_1000000;
            CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }

        if (this->unk_191 & 0x1) {
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }

        if (this->actionFunc != func_80B1BF2C) {
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }

        if (this->actionFunc == func_80B1B628) {
            this->actor.shape.rot.y = BINANG_ROT180(this->actor.world.rot.y);
        } else if (this->unk_191 & 0x2) {
            this->actor.shape.rot.y = this->actor.world.rot.y;
        }
    }
}

void func_80B1C974(EnPoSisters* this) {
    if (this->skelAnime.animation == &object_po_sisters_Anim_000114) {
        this->unk_226 = CLAMP_MAX(this->unk_226 + 5, 255);
        this->unk_227 = CLAMP_MIN(this->unk_227 - 5, 50);
        this->unk_228 = CLAMP_MIN(this->unk_228 - 5, 0);
    } else if (this->skelAnime.animation == &object_po_sisters_Anim_000A54) {
        this->unk_226 = CLAMP_MAX(this->unk_226 + 5, 80);
        this->unk_227 = CLAMP_MAX(this->unk_227 + 5, 255);
        this->unk_228 = CLAMP_MAX(this->unk_228 + 5, 225);
    } else if (this->skelAnime.animation == &object_po_sisters_Anim_0008C0) {
        if (this->actor.colorFilterTimer & 0x2) {
            this->unk_226 = 0;
            this->unk_227 = 0;
            this->unk_228 = 0;
        } else {
            this->unk_226 = 80;
            this->unk_227 = 255;
            this->unk_228 = 225;
        }
    } else {
        this->unk_226 = CLAMP_MAX(this->unk_226 + 5, 255);
        this->unk_227 = CLAMP_MAX(this->unk_227 + 5, 255);

        if (this->unk_228 > 210) {
            if (this->unk_228 && this->unk_228 && this->unk_228) {}
            this->unk_228 = CLAMP_MIN(this->unk_228 - 5, 210);
        } else {
            this->unk_228 = CLAMP_MAX(this->unk_228 + 5, 210);
        }
    }
}

s32 EnPoSisters_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                 Actor* thisx, Gfx** gfx) {
    static Gfx* D_80B1DACC[] = {
        object_po_sisters_DL_001DE0,
        object_po_sisters_DL_002F88,
        object_po_sisters_DL_003628,
        object_po_sisters_DL_003DC8,
    };
    static Gfx* D_80B1DADC[] = {
        object_po_sisters_DL_001CB0,
        object_po_sisters_DL_002EB8,
        object_po_sisters_DL_003880,
        object_po_sisters_DL_004020,
    };
    static Color_RGBA8 D_80B1DAEC[] = {
        { 80, 0, 100, 0 },
        { 80, 15, 0, 0 },
        { 0, 70, 50, 0 },
        { 70, 70, 0, 0 },
    };
    EnPoSisters* this = THIS;

    if ((limbIndex == 1) && (this->unk_191 & 0x40)) {
        if (this->unk_192 >= 284) {
            rot->x += (this->unk_192 - 284) * 0x1000;
        } else {
            rot->x += (this->unk_192 - 15) * 0x1000;
        }
    }

    if ((this->unk_229 == 0) || (limbIndex == 8) || ((this->actionFunc == func_80B1BA90) && (this->unk_192 >= 8))) {
        *dList = NULL;
    } else if (limbIndex == 9) {
        *dList = D_80B1DACC[this->unk_18C];
    } else if (limbIndex == 10) {
        *dList = D_80B1DADC[this->unk_18C];

        gDPPipeSync((*gfx)++);
        gDPSetEnvColor((*gfx)++, this->unk_226, this->unk_227, this->unk_228, this->unk_229);
    } else if (limbIndex == 11) {
        Color_RGBA8* colour = &D_80B1DAEC[this->unk_18C];

        gDPPipeSync((*gfx)++);
        gDPSetEnvColor((*gfx)++, colour->r, colour->g, colour->b, this->unk_229);
    }

    return false;
}

void EnPoSisters_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx,
                              Gfx** gfx) {
    static Vec3f D_80B1DAFC = { 1000.0f, -1700.0f, 0.0f };
    static s8 D_80B1DB08[] = {
        -1, -1, 0, 1, 2, -1, 3, -1, -1, -1, -1, -1,
    };
    EnPoSisters* this = THIS;
    s32 end;
    f32 temp_f2;

    if (D_80B1DB08[limbIndex] != -1) {
        Matrix_GetStateTranslation(&this->limbPos[D_80B1DB08[limbIndex]]);
    } else if (limbIndex == 9) {
        Matrix_GetStateTranslationAndScaledY(-2500.0f, &this->limbPos[4]);
        Matrix_GetStateTranslationAndScaledY(3000.0f, &this->limbPos[5]);
    } else if (limbIndex == 10) {
        Matrix_GetStateTranslationAndScaledY(-4000.0f, &this->limbPos[6]);
    } else if (limbIndex == 11) {
        Matrix_GetStateTranslationAndScaledX(3000.0f, &this->limbPos[7]);
    }

    if ((this->actionFunc == func_80B1BA90) && (this->unk_192 >= 8) && (limbIndex == 9)) {
        gSPMatrix((*gfx)++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList((*gfx)++, object_po_sisters_DL_0046E0);
    }

    if (limbIndex == 8) {
        if (this->unk_191 & 0x20) {
            for (end = this->unk_190 - 1; end > 0; end--) {
                this->unk_22C[end] = this->unk_22C[end - 1];
            }

            Matrix_MultiplyVector3fByState(&D_80B1DAFC, this->unk_22C);
        }

        if (this->unk_190 > 0) {
            Color_RGBA8* sp38 = &D_80B1DA30[this->unk_18C];

            temp_f2 = Rand_ZeroFloat(0.3f) + 0.7f;

            if (this->actionFunc == func_80B1BCA0) {
                Lights_PointNoGlowSetInfo(&this->lightInfo, this->unk_22C[0].x, this->unk_22C[0].y + 15.0f,
                                          this->unk_22C[0].z, sp38->r * temp_f2, sp38->g * temp_f2, sp38->b * temp_f2,
                                          200);
            } else {
                Lights_PointGlowSetInfo(&this->lightInfo, this->unk_22C[0].x, this->unk_22C[0].y + 15.0f,
                                        this->unk_22C[0].z, sp38->r * temp_f2, sp38->g * temp_f2, sp38->b * temp_f2,
                                        200);
            }
        } else {
            Lights_PointSetColorAndRadius(&this->lightInfo, 0, 0, 0, 0);
        }

        if (!(this->unk_191 & 0x80)) {
            Matrix_CopyCurrentState(&this->unk_358);
        }
    }
}

void EnPoSisters_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnPoSisters* this = THIS;
    Color_RGBA8* temp_s1 = &D_80B1DA40[this->unk_18C];
    Color_RGBA8* temp_s7 = &D_80B1DA30[this->unk_18C];
    s32 pad;
    s32 i;
    s32 phi_s5;
    f32 phi_f20;
    s32 pad2;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_80B1C974(this);
    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);

    if ((this->unk_229 == 255) || (this->unk_229 == 0)) {
        gDPSetEnvColor(POLY_OPA_DISP++, this->unk_226, this->unk_227, this->unk_228, this->unk_229);
        gSPSegment(POLY_OPA_DISP++, 0x09, D_801AEFA0);
        POLY_OPA_DISP =
            SkelAnime_Draw(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                           EnPoSisters_OverrideLimbDraw, EnPoSisters_PostLimbDraw, &this->actor, POLY_OPA_DISP);
    } else {
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 255, this->unk_229);
        gSPSegment(POLY_XLU_DISP++, 0x09, D_801AEF88);
        POLY_XLU_DISP =
            SkelAnime_Draw(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                           EnPoSisters_OverrideLimbDraw, EnPoSisters_PostLimbDraw, &this->actor, POLY_XLU_DISP);
    }

    if (!(this->unk_191 & 0x80)) {
        Matrix_SetCurrentState(&this->unk_358);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, object_po_sisters_DL_0027B0);
    }

    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 32, 64, 1, 0, (globalCtx->gameplayFrames * -20) % 512,
                                32, 128));
    gDPSetEnvColor(POLY_XLU_DISP++, temp_s1->r, temp_s1->g, temp_s1->b, temp_s1->a);

    if (this->actionFunc == func_80B1BCA0) {
        phi_s5 = (((-this->unk_192 * 255) + 0x1FE0) / 32) & 0xFF;
        phi_f20 = 0.0056000003f;
    } else {
        phi_s5 = 0;
        phi_f20 = this->actor.scale.x * 0.5f;
    }

    for (i = 0; i < this->unk_190; i++) {
        if (this->actionFunc != func_80B1BCA0) {
            phi_s5 = ((-i * 31) + 248) & 0xFF;
        }

        gDPPipeSync(POLY_XLU_DISP++);
        gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, temp_s7->r, temp_s7->g, temp_s7->b, phi_s5);

        Matrix_InsertTranslation(this->unk_22C[i].x, this->unk_22C[i].y, this->unk_22C[i].z, MTXMODE_NEW);
        Matrix_InsertRotation(0, BINANG_ROT180(Camera_GetCamDirYaw(GET_ACTIVE_CAM(globalCtx))), 0, MTXMODE_APPLY);

        if (this->actionFunc == func_80B1BA90) {
            f32 phi_f0;

            phi_f20 = ((this->unk_192 - i) * 0.025f) + 0.5f;
            phi_f0 = CLAMP(phi_f20, 0.5f, 0.8f);
            phi_f20 = phi_f0 * 0.007f;
        }
        Matrix_Scale(phi_f20, phi_f20, phi_f20, MTXMODE_APPLY);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gGameplayKeepDrawFlameDL);
    }

    Actor_DrawDamageEffects(globalCtx, &this->actor, this->limbPos, ARRAY_COUNT(this->limbPos),
                            this->actor.scale.x * 142.857131958f * this->drawDmgEffScale, 0.0f, this->drawDmgEffAlpha,
                            ACTOR_DRAW_DMGEFF_LIGHT_ORBS);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
