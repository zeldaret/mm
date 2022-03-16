/*
 * File: z_en_kame.c
 * Overlay: ovl_En_Kame
 * Description: Snapper Turtle
 */

#include "z_en_kame.h"
#include "objects/object_tl/object_tl.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_400)

#define THIS ((EnKame*)thisx)

void EnKame_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKame_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKame_Update(Actor* thisx, GlobalContext* globalCtx);
void EnKame_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AD70A0(EnKame* this);
void func_80AD70EC(EnKame* this, GlobalContext* globalCtx);
void func_80AD71B4(EnKame* this);
void func_80AD7254(EnKame* this, GlobalContext* globalCtx);
void func_80AD73A8(EnKame* this);
void func_80AD7424(EnKame* this, GlobalContext* globalCtx);
void func_80AD76CC(EnKame* this);
void func_80AD7798(EnKame* this, GlobalContext* globalCtx);
void func_80AD792C(EnKame* this);
void func_80AD7948(EnKame* this, GlobalContext* globalCtx);
void func_80AD7B18(EnKame* this);
void func_80AD7B90(EnKame* this, GlobalContext* globalCtx);
void func_80AD7D40(EnKame* this, GlobalContext* globalCtx);
void func_80AD7DA4(EnKame* this);
void func_80AD7E0C(EnKame* this, GlobalContext* globalCtx);
void func_80AD7EC0(EnKame* this);
void func_80AD7F10(EnKame* this, GlobalContext* globalCtx);
void func_80AD7FF8(EnKame* this, GlobalContext* globalCtx);
void func_80AD810C(EnKame* this, GlobalContext* globalCtx);
void func_80AD8148(EnKame* this, GlobalContext* globalCtx);
void func_80AD825C(EnKame* this, GlobalContext* globalCtx);
void func_80AD8364(EnKame* this);
void func_80AD8388(EnKame* this, GlobalContext* globalCtx);
void func_80AD8D64(Actor* thisx, GlobalContext* globalCtx);

const ActorInit En_Kame_InitVars = {
    ACTOR_EN_KAME,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_TL,
    sizeof(EnKame),
    (ActorFunc)EnKame_Init,
    (ActorFunc)EnKame_Destroy,
    (ActorFunc)EnKame_Update,
    (ActorFunc)EnKame_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HARD,
        AT_NONE | AT_TYPE_ENEMY,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x00, 0x04 },
        { 0xF7CF7FFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON | BUMP_HOOKABLE,
        OCELEM_ON,
    },
    { 35, 40, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit sColChkInfoInit = { 3, 15, 30, 80 };

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xD),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0xE),
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
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

static TexturePtr D_80AD8E34[] = { object_tl_Tex_0055A0, object_tl_Tex_0057A0, object_tl_Tex_0059A0,
                                   object_tl_Tex_0057A0 };

static InitChainEntry sInitChain[] = {
    ICHAIN_S8(hintId, 1, ICHAIN_CONTINUE),
    ICHAIN_F32(gravity, -1, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 3500, ICHAIN_STOP),
};

static s32 D_80AD8E50 = false;

void EnKame_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnKame* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime1, &object_tl_Skel_007C70, &object_tl_Anim_004210, this->jointTable1,
                       this->morphTable1, 13);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime2, &object_tl_Skel_001A50, &object_tl_Anim_000B30, this->jointTable2,
                       this->morphTable2, 4);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 55.0f);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);

    if (!D_80AD8E50) {
        s32 i;

        for (i = 0; i < ARRAY_COUNT(D_80AD8E34); i++) {
            D_80AD8E34[i] = Lib_SegmentedToVirtual(D_80AD8E34[i]);
        }
        D_80AD8E50 = true;
    }

    func_80AD70A0(this);
}

void EnKame_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnKame* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80AD6F34(EnKame* this) {
    if (this->unk_29C != 0) {
        this->unk_29C++;
        if (this->unk_29C == 4) {
            this->unk_29C = 0;
        }
    } else if (Rand_ZeroOne() < 0.05f) {
        this->unk_29C = 1;
    }
}

void func_80AD6F9C(EnKame* this) {
    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX;
    this->drawDmgEffScale = 0.6f;
    this->drawDmgEffFrozenSteamScale = 0.90000004f;
    this->drawDmgEffAlpha = 1.0f;
    this->collider.base.colType = COLTYPE_HIT3;
    this->unk_2A2 = 80;
    this->actor.flags &= ~ACTOR_FLAG_400;
    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 80);
}

void func_80AD7018(EnKame* this, GlobalContext* globalCtx) {
    if (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
        this->collider.base.colType = COLTYPE_HIT6;
        this->drawDmgEffAlpha = 0.0f;
        Actor_SpawnIceEffects(globalCtx, &this->actor, this->limbPos, 10, 2, 0.3f, 0.2f);
        this->actor.flags |= ACTOR_FLAG_400;
    }
}

void func_80AD70A0(EnKame* this) {
    Animation_MorphToPlayOnce(&this->skelAnime1, &object_tl_Anim_004210, -5.0f);
    this->actor.speedXZ = 0.0f;
    this->actionFunc = func_80AD70EC;
}

void func_80AD70EC(EnKame* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (Animation_OnFrame(&this->skelAnime1, 10.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PAMET_VOICE);
        this->unk_2A0 = 40;
    }

    if ((Player_GetMask(globalCtx) != PLAYER_MASK_STONE) && !(player->stateFlags1 & 0x800000) &&
        (this->actor.xzDistToPlayer < 240.0f)) {
        func_80AD73A8(this);
    } else if (SkelAnime_Update(&this->skelAnime1)) {
        func_80AD71B4(this);
    }
}

void func_80AD71B4(EnKame* this) {
    Animation_MorphToLoop(&this->skelAnime1, &object_tl_Anim_00823C, -5.0f);
    this->actor.speedXZ = 0.5f;
    this->unk_29E = Animation_GetLastFrame(&object_tl_Anim_00823C) * ((s32)Rand_ZeroFloat(5.0f) + 3);
    this->unk_2A4 = this->actor.shape.rot.y;
    this->collider.base.acFlags |= (AC_HARD | AC_ON);
    this->collider.base.colType = COLTYPE_HARD;
    this->actionFunc = func_80AD7254;
}

void func_80AD7254(EnKame* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if ((Player_GetMask(globalCtx) != PLAYER_MASK_STONE) && !(player->stateFlags1 & 0x800000) &&
        (this->actor.xzDistToPlayer < 240.0f)) {
        func_80AD73A8(this);
        return;
    }

    SkelAnime_Update(&this->skelAnime1);

    if (this->unk_2A4 != this->actor.shape.rot.y) {
        Math_ScaledStepToS(&this->actor.shape.rot.y, this->unk_2A4, 0x100);
        this->actor.world.rot.y = this->actor.shape.rot.y;
    } else if (Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos) > 40.0f) {
        this->unk_2A4 = Actor_YawToPoint(&this->actor, &this->actor.home.pos) + (Rand_Next() >> 0x14);
    }

    this->unk_29E--;
    if (this->unk_29E == 0) {
        func_80AD70A0(this);
    } else if (Animation_OnFrame(&this->skelAnime1, 0.0f) || Animation_OnFrame(&this->skelAnime1, 15.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PAMET_WALK);
    }
}

void func_80AD73A8(EnKame* this) {
    Animation_MorphToPlayOnce(&this->skelAnime1, &object_tl_Anim_001C68, -3.0f);
    this->unk_29E = 0;
    this->unk_2AC = 1.0f;
    this->unk_2A8 = 1.0f;
    this->actor.speedXZ = 0.0f;
    if (this->unk_2A0 == 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PAMET_VOICE);
    }
    this->actionFunc = func_80AD7424;
}

void func_80AD7424(EnKame* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (SkelAnime_Update(&this->skelAnime1)) {
        if ((Player_GetMask(globalCtx) != PLAYER_MASK_STONE) && !(player->stateFlags1 & 0x800000) &&
            ((this->unk_29E == 0) || (this->actor.xzDistToPlayer < 120.0f))) {
            func_80AD76CC(this);
        } else {
            this->unk_29E--;
            if (this->unk_29E == 0) {
                func_80AD7B18(this);
            }
        }
    } else if (this->skelAnime1.curFrame > 2.0f) {
        this->unk_2AC = 1.5f - ((this->skelAnime1.curFrame - 2.0f) * (7.0f / 30));
        this->unk_2A8 = 1.5f - ((this->skelAnime1.curFrame - 2.0f) * (1.0f / 12));
    } else {
        f32 frame = this->skelAnime1.curFrame;

        this->unk_2AC = (0.25f * frame) + 1.0f;
        this->unk_2A8 = (0.25f * frame) + 1.0f;
    }
}

void func_80AD7568(EnKame* this) {
    this->actor.speedXZ = this->unk_2A6 * (5.0f / 7552);
    this->actor.shape.rot.z = this->unk_2A6 * 0.11016949f;
}

void func_80AD75A8(EnKame* this, GlobalContext* globalCtx) {
    static Color_RGBA8 D_80AD8E54 = { 250, 250, 250, 255 };
    static Color_RGBA8 D_80AD8E58 = { 180, 180, 180, 255 };
    static Vec3f D_80AD8E5C = { 0.0f, 0.75f, 0.0f };

    if ((this->actor.bgCheckFlags & 1) && (this->actor.speedXZ >= 3.0f)) {
        if ((globalCtx->gameplayFrames % 2) == 0) {
            u32 temp_v0 = func_800C9BB8(&globalCtx->colCtx, this->actor.floorPoly, this->actor.floorBgId);

            if ((temp_v0 == 0) || (temp_v0 == 1)) {
                func_800B1210(globalCtx, &this->actor.world.pos, &D_80AD8E5C, &gZeroVec3f, 550, 100);
            } else if (temp_v0 == 14) {
                func_800B0DE0(globalCtx, &this->actor.world.pos, &D_80AD8E5C, &gZeroVec3f, &D_80AD8E54, &D_80AD8E58,
                              550, 100);
            }
        }
    }

    if (this->unk_2A6 > 0x1200) {
        func_800B9010(&this->actor, NA_SE_EN_PAMET_ROLL - SFX_FLAG);
    }
}

void func_80AD76CC(EnKame* this) {
    if (this->actor.draw == EnKame_Draw) {
        this->actor.draw = func_80AD8D64;
        this->unk_2A6 = 0x3B00;
        this->unk_2AC = 0.5f;
        func_80AD7568(this);
        this->unk_29E = 15;
        this->actor.speedXZ = 0.0f;
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PAMET_CUTTER_ON);
        this->unk_2BC.y = this->actor.home.pos.y - 100.0f;
    } else {
        this->actor.world.rot.y = Actor_YawToPoint(&this->actor, &this->actor.home.pos);
        Math_Vec3f_Copy(&this->unk_2BC, &this->actor.home.pos);
        this->unk_29E = 0;
    }
    this->actor.flags |= ACTOR_FLAG_10;
    this->actionFunc = func_80AD7798;
}

void func_80AD7798(EnKame* this, GlobalContext* globalCtx) {
    if (this->unk_29E == 15) {
        this->unk_2AC += 0.2f;
        if (this->unk_2AC > 1.1f) {
            this->unk_29E--;
            this->collider.base.atFlags |= AT_ON;
            this->unk_2AC = 1.0f;
        }
    } else if (this->unk_29E > 0) {
        this->unk_29E--;
    } else if (Math_ScaledStepToS(&this->unk_2A6, 0x3B00, (s32)(this->unk_2A6 * 0.09f) + 45)) {
        if (this->unk_2BC.y < this->actor.home.pos.y) {
            this->actor.world.rot.y = this->actor.yawTowardsPlayer;
            this->unk_2BC.x = (Math_SinS(this->actor.world.rot.y) * 360.0f) + this->actor.world.pos.x;
            this->unk_2BC.z = (Math_CosS(this->actor.world.rot.y) * 360.0f) + this->actor.world.pos.z;
        }
        func_80AD792C(this);
    }

    this->actor.shape.rot.y += this->unk_2A6;

    if (!(this->unk_2BC.y < this->actor.home.pos.y) || (this->actionFunc != func_80AD7798)) {
        func_80AD7568(this);
    }
    func_80AD75A8(this, globalCtx);
}

void func_80AD792C(EnKame* this) {
    this->unk_29E = -1;
    this->actionFunc = func_80AD7948;
}

void func_80AD7948(EnKame* this, GlobalContext* globalCtx) {
    s32 temp_v1;

    this->actor.shape.rot.y += this->unk_2A6;
    func_80AD75A8(this, globalCtx);

    if (this->unk_29E == -1) {
        s16 temp_v0 = Actor_YawToPoint(&this->actor, &this->unk_2BC) - this->actor.world.rot.y;

        temp_v1 = ABS_ALT(temp_v0);

        if ((this->actor.bgCheckFlags & 8) || (temp_v1 > 0x3000) ||
            (Actor_XZDistanceToPoint(&this->actor, &this->unk_2BC) < 50.0f)) {
            s8 pad;

            if (this->unk_2BC.y < this->actor.home.pos.y) {
                this->unk_29E = 0x300;
            } else {
                this->unk_29E = 0;
            }
        }
        return;
    }

    if (Math_ScaledStepToS(&this->unk_2A6, this->unk_29E, (s32)(this->unk_2A6 * 0.09f) + 45)) {
        if (this->unk_29E == 0) {
            if (this->unk_2AC >= 1.0f) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PAMET_CUTTER_OFF);
            }
            this->unk_2AC -= 0.1f;
            this->collider.base.atFlags &= ~AT_ON;
            if (this->unk_2AC < 0.5f) {
                this->actor.flags &= ~ACTOR_FLAG_10;
                func_80AD7B18(this);
            }
        } else {
            func_80AD76CC(this);
        }
    }
    func_80AD7568(this);
}

void func_80AD7B18(EnKame* this) {
    this->actor.draw = EnKame_Draw;
    Animation_MorphToPlayOnce(&this->skelAnime1, &object_tl_Anim_0031DC, -3.0f);
    this->actor.speedXZ = 0.0f;
    this->unk_2AC = 0.1f;
    this->unk_2A8 = 1.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = func_80AD7B90;
}

void func_80AD7B90(EnKame* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime1)) {
        func_80AD71B4(this);
    } else if (this->skelAnime1.curFrame > 7.0f) {
        this->unk_2AC = 1.5f - ((this->skelAnime1.curFrame - 7.0f) * (1.0f / 6));
        this->unk_2A8 = 1.5f - ((this->skelAnime1.curFrame - 7.0f) * (1.0f / 6));
    } else {
        f32 frame = this->skelAnime1.curFrame;

        this->unk_2AC = (0.2f * frame) + 0.1f;
        this->unk_2A8 = ((1.0f / 14) * frame) + 1.0f;
    }
}

void func_80AD7C54(EnKame* this) {
    if (this->actionFunc == func_80AD7E0C) {
        Animation_MorphToPlayOnce(&this->skelAnime1, &object_tl_Anim_0035EC, -3.0f);
        this->unk_29E = 1;
        this->collider.info.bumper.dmgFlags &= ~0x8000;
    } else {
        Animation_MorphToPlayOnce(&this->skelAnime1, &object_tl_Anim_0039C0, -3.0f);
        this->unk_29E = 0;
        this->collider.info.bumper.dmgFlags |= 0x8000;
    }

    this->actor.draw = EnKame_Draw;
    this->actor.speedXZ = 0.0f;
    this->collider.base.acFlags &= ~AC_ON;
    this->collider.base.atFlags &= ~AT_ON;
    this->collider.base.atFlags &= ~(AT_BOUNCED | AT_HIT);
    this->actor.flags &= ~ACTOR_FLAG_10;
    this->actor.shape.rot.z = 0;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PAMET_REVERSE);
    this->actionFunc = func_80AD7D40;
}

void func_80AD7D40(EnKame* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime1)) {
        if (this->unk_29E == 1) {
            func_80AD71B4(this);
        } else {
            this->unk_29E = 200;
            func_80AD7DA4(this);
        }
    }
}

void func_80AD7DA4(EnKame* this) {
    Animation_MorphToPlayOnce(&this->skelAnime1, &object_tl_Anim_0027D8, -3.0f);
    this->collider.base.acFlags |= AC_ON;
    this->collider.base.acFlags &= ~AC_HARD;
    this->collider.base.colType = COLTYPE_HIT6;
    this->actor.speedXZ = 0.0f;
    this->actionFunc = func_80AD7E0C;
}

void func_80AD7E0C(EnKame* this, GlobalContext* globalCtx) {
    if (this->unk_29E > 0) {
        this->unk_29E--;
        if (SkelAnime_Update(&this->skelAnime1)) {
            if (Rand_ZeroOne() > 0.5f) {
                Animation_PlayOnce(&this->skelAnime1, &object_tl_Anim_0027D8);
            } else {
                Animation_PlayOnce(&this->skelAnime1, &object_tl_Anim_002F88);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PAMET_ROAR);
            }
        }
    } else {
        func_80AD7EC0(this);
    }
}

void func_80AD7EC0(EnKame* this) {
    Animation_MorphToPlayOnce(&this->skelAnime1, &object_tl_Anim_002510, -3.0f);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PAMET_WAKEUP);
    this->actionFunc = func_80AD7F10;
}

void func_80AD7F10(EnKame* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime1)) {
        this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        func_80AD71B4(this);
    } else if (this->skelAnime1.curFrame >= 10.0f) {
        this->actor.shape.shadowDraw = NULL;
        this->collider.base.acFlags &= ~AC_ON;
        this->collider.info.bumper.dmgFlags &= ~0x8000;
    }
}

void func_80AD7FA4(EnKame* this) {
    this->actor.speedXZ = 0.0f;
    if (this->actor.velocity.y > 0.0f) {
        this->actor.velocity.y = 0.0f;
    }
    func_800BE504(&this->actor, &this->collider);
    this->actionFunc = func_80AD7FF8;
}

void func_80AD7FF8(EnKame* this, GlobalContext* globalCtx) {
    if (this->unk_2A2 != 0) {
        this->unk_2A2--;
    }

    if (this->unk_2A2 == 0) {
        func_80AD7018(this, globalCtx);
        if (this->actor.colChkInfo.health == 0) {
            func_80AD8148(this, NULL);
        } else {
            this->actor.world.rot.y = this->actor.shape.rot.y;
            func_80AD7DA4(this);
        }
    }
}

void func_80AD8060(EnKame* this) {
    s16 sp36 = Animation_GetLastFrame(&object_tl_Anim_0008B4);

    Animation_Change(&this->skelAnime1, &object_tl_Anim_0008B4, 1.0f, 0.0f, sp36, 2, -3.0f);
    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, sp36);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PAMET_DAMAGE);
    this->collider.base.acFlags &= ~AC_ON;
    this->actionFunc = func_80AD810C;
}

void func_80AD810C(EnKame* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime1)) {
        func_80AD7DA4(this);
    }
}

void func_80AD8148(EnKame* this, GlobalContext* globalCtx) {
    Animation_PlayLoop(&this->skelAnime1, &object_tl_Anim_000AF4);
    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 20);
    this->collider.base.acFlags &= ~AC_ON;
    this->collider.base.atFlags &= ~AT_ON;
    this->collider.base.atFlags &= ~(AC_HARD | AC_HIT);
    this->actor.velocity.y = 15.0f;
    this->actor.speedXZ = 1.5f;
    if (globalCtx != NULL) {
        Enemy_StartFinishingBlow(globalCtx, &this->actor);
        if (this->actor.draw == func_80AD8D64) {
            this->actor.draw = EnKame_Draw;
        } else {
            func_800BE504(&this->actor, &this->collider);
        }
    }
    this->actor.bgCheckFlags &= ~0x1;
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->actor.flags |= ACTOR_FLAG_10;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PAMET_DEAD);
    this->unk_29E = 0;
    this->actionFunc = func_80AD825C;
}

void func_80AD825C(EnKame* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime1);
    if ((this->actor.bgCheckFlags & 1) && (this->actor.velocity.y < 0.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_HIPLOOP_LAND);
        func_80AD8364(this);
    } else {
        if (this->unk_29E == 1) {
            this->actor.colorFilterTimer = 100;
        } else if (this->actor.colorFilterTimer == 0) {
            Actor_SetColorFilter(&this->actor, 0xC000, 255, 0, 100);
        }
        this->actor.shape.rot.x += Rand_S16Offset(0x700, 0x1400);
        this->actor.shape.rot.y += (s16)Rand_ZeroFloat(5120.0f);
        this->actor.shape.rot.z += Rand_S16Offset(0x700, 0x1400);
    }
}

void func_80AD8364(EnKame* this) {
    this->unk_29E = 20;
    this->actor.speedXZ = 0.0f;
    this->actionFunc = func_80AD8388;
}

void func_80AD8388(EnKame* this, GlobalContext* globalCtx) {
    Vec3f sp34;

    SkelAnime_Update(&this->skelAnime1);
    this->actor.colorFilterTimer = 100;
    if (this->unk_29E > 0) {
        this->unk_29E--;
        if (this->unk_29E == 0) {
            SoundSource_PlaySfxEachFrameAtFixedWorldPos(globalCtx, &this->actor.world.pos, 21,
                                                        NA_SE_EN_COMMON_EXTINCT_LEV - SFX_FLAG);
        }
    } else {
        this->actor.scale.x -= 0.001f;
        if (this->actor.scale.x <= 0.0f) {
            Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.world.pos, 0x60);
            Actor_MarkForDeath(&this->actor);
        } else {
            this->actor.scale.y = this->actor.scale.x;
            this->actor.scale.z = this->actor.scale.x;
        }
        sp34.x = randPlusMinusPoint5Scaled(40.0f) + this->actor.world.pos.x;
        sp34.y = this->actor.world.pos.y + 15.0f;
        sp34.z = randPlusMinusPoint5Scaled(40.0f) + this->actor.world.pos.z;
        func_800B3030(globalCtx, &sp34, &gZeroVec3f, &gZeroVec3f, 100, 0, 2);
    }
}

void func_80AD84C0(EnKame* this, GlobalContext* globalCtx) {
    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;

        Actor_SetDropFlag(&this->actor, &this->collider.info);
        if ((this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) &&
            (this->collider.info.acHitInfo->toucher.dmgFlags & 0xDB0B3)) {
            return;
        }

        func_80AD7018(this, globalCtx);
        if (this->actor.colChkInfo.damageEffect == 13) {
            return;
        }

        if (this->actor.colChkInfo.damageEffect == 14) {
            func_80AD8148(this, globalCtx);
        } else if (this->actor.colChkInfo.damageEffect == 15) {
            if (this->collider.base.acFlags & AC_HARD) {
                func_80AD7C54(this);
            } else if (!Actor_ApplyDamage(&this->actor)) {
                func_80AD8148(this, globalCtx);
            } else {
                func_80AD8060(this);
            }
        } else if ((this->actionFunc == func_80AD70EC) || (this->actionFunc == func_80AD7254)) {
            func_80AD73A8(this);
            this->unk_29E = 21;
        } else if (!(this->collider.base.acFlags & AC_HARD)) {
            if (this->actor.colChkInfo.damageEffect == 5) {
                this->unk_2A2 = 40;
                Actor_SetColorFilter(&this->actor, 0, 255, 0, 40);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
                this->drawDmgEffScale = 0.6f;
                this->drawDmgEffAlpha = 2.0f;
                this->drawDmgEffType = ACTOR_DRAW_DMGEFF_ELECTRIC_SPARKS_SMALL;
                func_80AD7FA4(this);
            } else if (this->actor.colChkInfo.damageEffect == 1) {
                this->unk_2A2 = 40;
                Actor_SetColorFilter(&this->actor, 0, 255, 0, 40);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
                func_80AD7FA4(this);
            } else if (this->actor.colChkInfo.damageEffect == 3) {
                func_80AD6F9C(this);
                if (!Actor_ApplyDamage(&this->actor)) {
                    this->unk_2A2 = 3;
                    this->collider.base.acFlags &= ~AC_ON;
                }
                func_80AD7FA4(this);
            } else {
                if (this->actor.colChkInfo.damageEffect == 2) {
                    this->drawDmgEffScale = 0.6f;
                    this->drawDmgEffAlpha = 4.0f;
                    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
                } else if (this->actor.colChkInfo.damageEffect == 4) {
                    this->drawDmgEffScale = 0.6f;
                    this->drawDmgEffAlpha = 4.0f;
                    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_LIGHT_ORBS;
                    Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG,
                                this->collider.info.bumper.hitPos.x, this->collider.info.bumper.hitPos.y,
                                this->collider.info.bumper.hitPos.z, 0, 0, 0, CLEAR_TAG_LARGE_LIGHT_RAYS);
                }

                if (!Actor_ApplyDamage(&this->actor)) {
                    func_80AD8148(this, globalCtx);
                } else {
                    func_80AD8060(this);
                }
            }
        }
    }

    if ((globalCtx->actorCtx.unk2 != 0) && (this->actor.xyzDistToPlayerSq < SQ(200.0f)) &&
        (this->collider.base.acFlags & AC_ON)) {
        func_80AD7018(this, globalCtx);
        func_80AD7C54(this);
    }
}

void EnKame_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnKame* this = THIS;

    func_80AD6F34(this);

    if (this->unk_2A0 != 0) {
        this->unk_2A0--;
    }

    func_80AD84C0(this, globalCtx);

    if ((this->collider.base.atFlags & AT_HIT) && (this->collider.base.atFlags & AT_BOUNCED)) {
        this->collider.base.atFlags &= ~(AT_BOUNCED | AT_HIT);
        func_80AD76CC(this);
        if (Actor_XZDistanceToPoint(&this->actor, &this->unk_2BC) < 50.0f) {
            this->collider.base.atFlags &= ~AT_ON;
        }
        this->unk_2A6 = 0x3B00;
        func_80AD7568(this);
    }

    this->actionFunc(this, globalCtx);

    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 40.0f, 60.0f, 40.0f, 0x1F);

    if (this->actor.shape.shadowDraw != NULL) {
        Actor_SetFocus(&this->actor, 25.0f);
        Collider_UpdateCylinder(&this->actor, &this->collider);
    }

    if (this->collider.base.atFlags & AT_ON) {
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }

    if (this->collider.base.acFlags & AC_ON) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }

    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);

    if (this->drawDmgEffAlpha > 0.0f) {
        if (this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
            Math_StepToF(&this->drawDmgEffAlpha, 0.0f, 0.05f);
            this->drawDmgEffScale = (this->drawDmgEffAlpha + 1.0f) * 0.3f;
            if (this->drawDmgEffScale > 0.6f) {
                this->drawDmgEffScale = 0.6f;
            } else {
                this->drawDmgEffScale = this->drawDmgEffScale;
            }
        } else if (!Math_StepToF(&this->drawDmgEffFrozenSteamScale, 0.6f, 0.015000001f)) {
            func_800B9010(&this->actor, NA_SE_EV_ICE_FREEZE - SFX_FLAG);
        }
    }
}

s32 func_80AD8A48(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnKame* this = THIS;

    if ((this->actionFunc == func_80AD7424) || (this->actionFunc == func_80AD7B90)) {
        if (limbIndex == 2) {
            Matrix_Scale(this->unk_2A8, this->unk_2AC, this->unk_2A8, MTXMODE_APPLY);
        } else if ((limbIndex == 11) || (limbIndex == 9) || (limbIndex == 7) || (limbIndex == 5)) {
            Matrix_Scale(this->unk_2A8, this->unk_2AC, this->unk_2AC, MTXMODE_APPLY);
        }
    }
    return false;
}

void func_80AD8AF8(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Vec3f D_80AD8E68[] = {
        { 1500.0f, 0.0f, -2000.0f }, { 1500.0f, 0.0f, 2000.0f }, { 1500.0f, 2000.0f, 0.0f },
        { 1500.0f, -2000.0f, 0.0f }, { 2500.0f, 0.0f, 0.0f },
    };
    static s8 D_80AD8EA4[] = { -1, -1, -1, 0, -1, -1, 1, -1, 2, -1, 3, -1, 4 };
    EnKame* this = THIS;

    if (D_80AD8EA4[limbIndex] != -1) {
        Matrix_GetStateTranslation(&this->limbPos[D_80AD8EA4[limbIndex]]);
    }

    if (limbIndex == 1) {
        s32 i;
        Vec3f* ptr;
        Vec3f* ptr2;

        if (this->actor.shape.shadowDraw == NULL) {
            Matrix_GetStateTranslation(&this->actor.world.pos);
        }

        ptr2 = D_80AD8E68;
        ptr = &this->limbPos[5];
        for (i = 0; i < ARRAY_COUNT(D_80AD8E68); i++) {
            Matrix_MultiplyVector3fByState(ptr2, ptr);
            ptr2++;
            ptr++;
        }
    }
}

void EnKame_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnKame* this = THIS;
    Vec3f sp40;

    if (this->actor.shape.shadowDraw == 0) {
        Math_Vec3f_Copy(&sp40, &this->actor.world.pos);
    }

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, D_80AD8E34[this->unk_29C]);

    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime1.skeleton, this->skelAnime1.jointTable,
                          this->skelAnime1.dListCount, func_80AD8A48, func_80AD8AF8, &this->actor);
    Actor_DrawDamageEffects(globalCtx, &this->actor, this->limbPos, ARRAY_COUNT(this->limbPos), this->drawDmgEffScale,
                            this->drawDmgEffFrozenSteamScale, this->drawDmgEffAlpha, this->drawDmgEffType);

    if (this->actor.shape.shadowDraw == NULL) {
        ActorShadow_DrawCircle(&this->actor, NULL, globalCtx);
        Actor_SetFocus(&this->actor, 25.0f);
        Collider_UpdateCylinder(&this->actor, &this->collider);
        Math_Vec3f_Copy(&this->actor.world.pos, &sp40);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

s32 Enkame_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                            Actor* thisx) {
    EnKame* this = THIS;

    if (limbIndex == 1) {
        pos->y -= 700.0f;
    }

    if ((this->unk_2AC != 1.0f) && (limbIndex == 3)) {
        Matrix_Scale(1.0f, this->unk_2AC, this->unk_2AC, MTXMODE_APPLY);
    }
    return false;
}

void func_80AD8D64(Actor* thisx, GlobalContext* globalCtx) {
    EnKame* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime2.skeleton, this->skelAnime2.jointTable,
                          this->skelAnime2.dListCount, Enkame_OverrideLimbDraw, NULL, &this->actor);
}
