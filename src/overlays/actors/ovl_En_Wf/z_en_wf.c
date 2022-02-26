/*
 * File: z_en_wf.c
 * Overlay: ovl_En_Wf
 * Description: Wolfos and White Wolfos
 */

#include "z_en_wf.h"
#include "overlays/actors/ovl_En_Bom_Chu/z_en_bom_chu.h"
#include "overlays/actors/ovl_Obj_Ice_Poly/z_obj_ice_poly.h"
#include "objects/object_wf/object_wf.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_400)

#define THIS ((EnWf*)thisx)

void EnWf_Init(Actor* thisx, GlobalContext* globalCtx);
void EnWf_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnWf_Update(Actor* thisx, GlobalContext* globalCtx);
void EnWf_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80990F0C(EnWf* this);
void func_80990F50(EnWf* this, GlobalContext* globalCtx);
void func_80990FC8(EnWf* this);
void func_80991040(EnWf* this, GlobalContext* globalCtx);
void func_80991174(EnWf* this, GlobalContext* globalCtx);
void func_80991200(EnWf* this);
void func_80991280(EnWf* this, GlobalContext* globalCtx);
void func_80991438(EnWf* this);
void func_8099149C(EnWf* this, GlobalContext* globalCtx);
void func_80991738(EnWf* this);
void func_8099177C(EnWf* this, GlobalContext* globalCtx);
void func_80991948(EnWf* this);
void func_809919F4(EnWf* this, GlobalContext* globalCtx);
void func_80991C04(EnWf* this);
void func_80991C80(EnWf* this, GlobalContext* globalCtx);
void func_80992068(EnWf* this, GlobalContext* globalCtx);
void func_8099223C(EnWf* this);
void func_809922B4(EnWf* this, GlobalContext* globalCtx);
void func_809923E4(EnWf* this, GlobalContext* globalCtx);
void func_809924EC(EnWf* this, GlobalContext* globalCtx);
void func_809926D0(EnWf* this);
void func_80992784(EnWf* this, GlobalContext* globalCtx);
void func_8099282C(EnWf* this);
void func_809928CC(EnWf* this, GlobalContext* globalCtx);
void func_80992A74(EnWf* this, GlobalContext* globalCtx);
void func_80992B8C(EnWf* this, GlobalContext* globalCtx);
void func_80992D6C(EnWf* this);
void func_80992E0C(EnWf* this, GlobalContext* globalCtx);
void func_80992FD4(EnWf* this);
void func_80993018(EnWf* this, GlobalContext* globalCtx);
void func_80993148(EnWf* this);
void func_80993194(EnWf* this, GlobalContext* globalCtx);
void func_80993350(EnWf* this);
void func_809933A0(EnWf* this, GlobalContext* globalCtx);
void func_80993524(EnWf* this);
void func_8099357C(EnWf* this, GlobalContext* globalCtx);
s32 func_8099408C(GlobalContext* globalCtx, EnWf* this);

const ActorInit En_Wf_InitVars = {
    ACTOR_EN_WF,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_WF,
    sizeof(EnWf),
    (ActorFunc)EnWf_Init,
    (ActorFunc)EnWf_Destroy,
    (ActorFunc)EnWf_Update,
    (ActorFunc)EnWf_Draw,
};

static ColliderJntSphElementInit sJntSphElementsInit[4] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x10 },
            { 0x00000000, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_NONE,
            OCELEM_NONE,
        },
        { 15, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x10 },
            { 0x00000000, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_NONE,
            OCELEM_NONE,
        },
        { 21, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK1,
            { 0x00000000, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_HOOKABLE,
            OCELEM_ON,
        },
        { 17, { { 800, 0, 0 }, 25 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK1,
            { 0x00000000, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_HOOKABLE,
            OCELEM_ON,
        },
        { 12, { { 0, 0, 0 }, 30 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_METAL,
        AT_NONE | AT_TYPE_ENEMY,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    4,
    sJntSphElementsInit,
};

static ColliderCylinderInit sCylinderInit1 = {
    {
        COLTYPE_HIT5,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 20, 50, 0, { 0, 0, 0 } },
};

static ColliderCylinderInit sCylinderInit2 = {
    {
        COLTYPE_HIT5,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 15, 20, -15, { 0, 0, 0 } },
};

static DamageTable sDamageTable1 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(2, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(3, 0x0),
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

static DamageTable sDamageTable2 = {
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
    /* Goron pound    */ DMG_ENTRY(3, 0x0),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
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

static CollisionCheckInfoInit sColChkInfoInit = { 8, 50, 100, MASS_HEAVY };

static TexturePtr D_809942B0[] = {
    object_wf_Tex_007AA8,
    object_wf_Tex_0082A8,
    object_wf_Tex_0084A8,
    object_wf_Tex_0082A8,
};

static TexturePtr D_809942C0[] = {
    object_wf_Tex_000300,
    object_wf_Tex_0027D8,
    object_wf_Tex_0029D8,
    object_wf_Tex_0027D8,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_STOP),
};

static s32 D_809942D8 = 0;

void EnWf_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnWf* this = THIS;
    s32 i;
    s32 temp_s0;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 70.0f);
    this->actor.shape.shadowAlpha = 150;
    Collider_InitAndSetJntSph(globalCtx, &this->collider1, &this->actor, &sJntSphInit, this->collider1Elements);
    Collider_InitAndSetCylinder(globalCtx, &this->collider2, &this->actor, &sCylinderInit1);
    Collider_InitAndSetCylinder(globalCtx, &this->collider3, &this->actor, &sCylinderInit2);
    Math_Vec3f_Copy(&this->actor.focus.pos, &this->actor.world.pos);

    if (this->actor.shape.rot.x <= 0) {
        this->unk_2A8 = 10000.0f;
    } else {
        this->unk_2A8 = this->actor.shape.rot.x * 40.0f;
    }

    this->actor.shape.rot.x = 0;
    this->actor.world.rot.x = 0;

    if (ENWF_GET_80(&this->actor)) {
        this->unk_295 = true;
    } else {
        this->unk_295 = false;
    }

    if (this->unk_295) {
        temp_s0 = this->actor.shape.rot.z + 100;
        temp_s0 = CLAMP(temp_s0, 1, 255);
        this->actor.shape.rot.z = 0;
        this->actor.world.rot.z = 0;
        this->actor.child = Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_OBJ_ICE_POLY, this->actor.world.pos.x,
                                        this->actor.world.pos.y, this->actor.world.pos.z, 0, this->actor.shape.rot.y, 0,
                                        temp_s0 | 0xFF00);
        if (this->actor.child != NULL) {
            Player* player = GET_PLAYER(globalCtx);

            this->actor.child->xzDistToPlayer = Actor_XZDistanceBetweenActors(&this->actor, &player->actor);
            this->unk_2A4 = (temp_s0 * 0.5f) + 45.0f;
            this->unk_29C = 0x32000 / this->unk_2A4;
            this->actor.shape.rot.y = Actor_YawBetweenActors(&this->actor, &player->actor);
            this->actor.world.pos.x -= this->unk_2A4 * Math_SinS(this->actor.shape.rot.y);
            this->actor.world.pos.z -= this->unk_2A4 * Math_CosS(this->actor.shape.rot.y);
        }
    }

    if (Flags_GetClear(globalCtx, this->actor.room)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    this->actor.params &= 0x3F;
    Actor_SetScale(&this->actor, 0.0075f);

    if (this->actor.params == 0) {
        SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_wf_Skel_0095D0, &object_wf_Anim_00A3CC,
                           this->jointTable, this->morphTable, 22);
        this->actor.hintId = 0x4C;
        CollisionCheck_SetInfo(&this->actor.colChkInfo, &sDamageTable2, &sColChkInfoInit);
        this->collider1.elements[0].info.toucher.damage = 8;
        this->collider1.elements[1].info.toucher.damage = 8;
        this->actor.colChkInfo.health = 6;
    } else {
        SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_wf_Skel_003BC0, &object_wf_Anim_00A3CC,
                           this->jointTable, this->morphTable, 22);
        this->actor.hintId = 0x57;
        CollisionCheck_SetInfo(&this->actor.colChkInfo, &sDamageTable1, &sColChkInfoInit);
    }

    if (this->actor.child == NULL) {
        func_80990F0C(this);
        this->unk_2A0 = 0;
    } else {
        func_80992FD4(this);
    }

    func_800BC154(globalCtx, &globalCtx->actorCtx, &this->actor, 5);

    if (D_809942D8 == 0) {
        for (i = 0; i < ARRAY_COUNT(D_809942B0); i++) {
            D_809942B0[i] = Lib_SegmentedToVirtual(D_809942B0[i]);
            D_809942C0[i] = Lib_SegmentedToVirtual(D_809942C0[i]);
        }
        D_809942D8 = 1;
    }
    this->unk_2A2 = Rand_ZeroFloat(96.0f);
}

void EnWf_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnWf* this = THIS;

    Collider_DestroyJntSph(globalCtx, &this->collider1);
    Collider_DestroyCylinder(globalCtx, &this->collider2);
    Collider_DestroyCylinder(globalCtx, &this->collider3);
}

void func_809907D4(EnWf* this) {
    this->drawDmgEffScale = 0.75f;
    this->drawDmgEffFrozenSteamScale = 1.125f;
    this->drawDmgEffAlpha = 1.0f;
    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX;
    this->collider2.base.colType = COLTYPE_HIT3;
    this->collider3.base.colType = COLTYPE_HIT3;
    this->unk_2A0 = 80;
    this->actor.flags &= ~ACTOR_FLAG_400;
    Actor_SetColorFilter(&this->actor, 0x4000, 0xFF, 0, 80);
}

void func_80990854(EnWf* this, GlobalContext* globalCtx) {
    if (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
        this->collider2.base.colType = COLTYPE_HIT5;
        this->collider3.base.colType = COLTYPE_HIT5;
        this->drawDmgEffAlpha = 0.0f;
        Actor_SpawnIceEffects(globalCtx, &this->actor, this->limbPos, 10, 2, 0.3f, 0.2f);
        this->actor.flags |= ACTOR_FLAG_400;
    }
}

void func_809908E0(EnWf* this) {
    if (this->unk_294 != 0) {
        this->unk_294++;
        if (this->unk_294 == 4) {
            this->unk_294 = 0;
        }
    } else if (Rand_ZeroOne() < 0.05f) {
        this->unk_294 = 1;
    }
}

s32 func_80990948(GlobalContext* globalCtx, EnWf* this, s16 arg2) {
    Player* player = GET_PLAYER(globalCtx);
    s32 sp38;
    s32 pad;
    s32 pad2;
    s16 sp2E;
    Actor* actor;

    sp38 = ABS_ALT(BINANG_SUB(this->actor.wallYaw, this->actor.shape.rot.y));

    if (((this->unk_295 == 0) ||
         ((this->unk_295 == 1) && (this->actor.child != NULL) && (this->actor.child->update != NULL))) &&
        (this->actor.xzDistToPlayer > 160.0f) &&
        (this->unk_2A8 < Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos))) {
        func_80993524(this);
        return true;
    }

    if (func_800BE184(globalCtx, &this->actor, 100.0f, 10000, 12000, this->actor.shape.rot.y) &&
        ((player->swordAnimation == 0x11) || ((globalCtx->gameplayFrames % 2) != 0))) {
        func_8099282C(this);
        return true;
    }

    if (func_800BE184(globalCtx, &this->actor, 100.0f, 24000, 0x2AA8, this->actor.shape.rot.y)) {
        this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
        this->actor.world.rot.y = this->actor.yawTowardsPlayer;
        if ((this->actor.bgCheckFlags & 8) && (sp38 < 12000)) {
            func_809926D0(this);
            return true;
        }

        if ((player->swordAnimation == 0x11) || ((globalCtx->gameplayFrames % 2) != 0)) {
            func_8099282C(this);
            return true;
        }

        func_8099223C(this);
        return true;
    }

    actor = func_800BC444(globalCtx, &this->actor, 80.0f);
    if ((actor != NULL) && (actor->id == ACTOR_EN_BOM_CHU)) {
        EnBomChu* bomchu = (EnBomChu*)actor;

        this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
        this->actor.world.rot.y = this->actor.yawTowardsPlayer;
        if (BINANG_ROT180(this->actor.shape.rot.y - bomchu->actor.world.rot.y) < 16000) {
            func_809926D0(this);
        }
        return true;
    }

    if (arg2 != 0) {
        if (!Actor_IsFacingPlayer(&this->actor, 7000)) {
            func_80992A74(this, globalCtx);
            return true;
        }

        sp2E = player->actor.shape.rot.y - this->actor.shape.rot.y;
        if ((this->actor.xzDistToPlayer <= 80.0f) && !Actor_OtherIsTargeted(globalCtx, &this->actor)) {
            if (((globalCtx->gameplayFrames % 8) != 0) || (ABS_ALT(sp2E) < 0x38E0)) {
                func_80991C04(this);
                return true;
            }
        }

        func_80991948(this);
        return true;
    }
    return false;
}

void func_80990C6C(EnWf* this, GlobalContext* globalCtx, s32 arg2) {
    static Vec3f D_809942DC = { 0.0f, 0.1f, 0.0f };
    static Color_RGBA8 D_809942E8 = { 185, 140, 70, 255 };
    static Color_RGBA8 D_809942EC = { 255, 255, 255, 255 };
    s32 i;
    Vec3f sp88;
    u32 temp_v0;
    Color_RGBA8* phi_s1;
    s16 phi_s6;

    if (this->actor.floorPoly != NULL) {
        temp_v0 = func_800C99D4(&globalCtx->colCtx, this->actor.floorPoly, this->actor.floorBgId);
        if (temp_v0 != 5) {
            if ((temp_v0 == 15) || (temp_v0 == 14)) {
                phi_s1 = &D_809942EC;
                phi_s6 = Rand_ZeroFloat(150.0f) + 350.0f;
                arg2 += 2;
            } else {
                phi_s1 = &D_809942E8;
                phi_s6 = Rand_ZeroFloat(100.0f) + 250.0f;
            }

            for (i = 0; i < arg2; i++) {
                sp88.x = randPlusMinusPoint5Scaled(50.0f) + this->actor.world.pos.x;
                sp88.y = Rand_ZeroFloat(5.0f) + this->actor.world.pos.y;
                sp88.z = randPlusMinusPoint5Scaled(50.0f) + this->actor.world.pos.z;
                func_800B0F18(globalCtx, &sp88, &gZeroVec3f, &D_809942DC, phi_s1, phi_s1, phi_s6, 5,
                              Rand_ZeroFloat(5.0f) + 14.0f);
            }
        }
    }
}

void func_80990E4C(EnWf* this, GlobalContext* globalCtx) {
    if (Animation_OnFrame(&this->skelAnime, 1.0f) && (this->actor.bgCheckFlags & 1)) {
        func_80990C6C(this, globalCtx, 2);
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WOLFOS_WALK);
    }
}

s32 func_80990EAC(EnWf* this) {
    ObjIcePoly* icePoly = (ObjIcePoly*)this->actor.child;

    if (icePoly->unk_148 < 200) {
        return true;
    }
    return false;
}

void func_80990ED4(EnWf* this) {
    this->actor.child = NULL;
    this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WOLFOS_APPEAR);
    func_80991438(this);
}

void func_80990F0C(EnWf* this) {
    this->collider2.base.acFlags &= ~AC_ON;
    this->actor.shape.shadowScale = 0.0f;
    this->actor.scale.y = 0.0f;
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->unk_2A0 = 60;
    this->actionFunc = func_80990F50;
}

void func_80990F50(EnWf* this, GlobalContext* globalCtx) {
    f32 phi_f2 = 240.0f;

    if (this->unk_2A0 != 0) {
        this->unk_2A0--;
    }

    if (this->unk_2A0 <= 0) {
        if (this->unk_2A8 < 240.0f) {
            phi_f2 = this->unk_2A8;
        }

        if (this->actor.xzDistToPlayer < phi_f2) {
            func_80990FC8(this);
        }
    }
}

void func_80990FC8(EnWf* this) {
    Animation_Change(&this->skelAnime, &object_wf_Anim_0053D0, 0.5f, 0.0f, 7.0f, 3, 0.0f);
    this->unk_2A0 = 5;
    this->actor.flags |= ACTOR_FLAG_1;
    this->actionFunc = func_80991040;
}

void func_80991040(EnWf* this, GlobalContext* globalCtx) {
    if (this->unk_2A0 != 0) {
        this->actor.scale.y += this->actor.scale.x * 0.2f;
        Math_StepToF(&this->actor.shape.shadowScale, 70.0f, 14.0f);
        this->unk_2A0--;
        if (this->unk_2A0 == 0) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WOLFOS_APPEAR);
        }
    } else if (SkelAnime_Update(&this->skelAnime)) {
        this->actor.scale.y = this->actor.scale.x;
        func_80991200(this);
    }
}

void func_809910F0(EnWf* this) {
    this->collider2.base.acFlags &= ~AC_ON;
    this->actor.speedXZ = 0.0f;
    Animation_Change(&this->skelAnime, &object_wf_Anim_0053D0, 0.5f, 0.0f, 7.0f, 3, -5.0f);
    this->unk_2A0 = 5;
    this->actionFunc = func_80991174;
}

void func_80991174(EnWf* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->unk_2A0 > 0) {
            this->actor.scale.y -= this->actor.scale.x * 0.2f;
            Math_StepToF(&this->actor.shape.shadowScale, 0.0f, 14.0f);
            this->unk_2A0--;
        } else {
            func_80990F0C(this);
        }
    }
}

void func_80991200(EnWf* this) {
    this->collider2.base.acFlags |= AC_ON;
    Animation_MorphToLoop(&this->skelAnime, &object_wf_Anim_00A3CC, -4.0f);
    this->unk_2A0 = (s32)Rand_ZeroFloat(10.0f) + 2;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = func_80991280;
    this->actor.speedXZ = 0.0f;
}

void func_80991280(EnWf* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 temp_v0;
    s32 phi_v1;

    SkelAnime_Update(&this->skelAnime);
    if (this->unk_298 != 0) {
        temp_v0 = (this->actor.yawTowardsPlayer - this->actor.shape.rot.y) - this->unk_29E;
        if (ABS_ALT(temp_v0) > 0x2000) {
            this->unk_298--;
            return;
        }
        this->unk_298 = 0;
    }

    if (!func_8099408C(globalCtx, this) && !func_80990948(globalCtx, this, 0)) {
        phi_v1 = ABS_ALT(BINANG_SUB(player->actor.shape.rot.y, this->actor.shape.rot.y));
        if ((this->actor.xzDistToPlayer < 80.0f) && (player->swordState != 0) && (phi_v1 >= 0x1F40)) {
            this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
            this->actor.world.rot.y = this->actor.yawTowardsPlayer;
            func_80991948(this);
        } else {
            this->unk_2A0--;
            if (this->unk_2A0 == 0) {
                if (Actor_IsFacingPlayer(&this->actor, 0x1555)) {
                    if (Rand_ZeroOne() > 0.3f) {
                        func_80991438(this);
                    } else {
                        func_80991948(this);
                    }
                } else {
                    func_80991738(this);
                }

                if (this->unk_2A2 == 0) {
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WOLFOS_CRY);
                }
            }
        }
    }
}

void func_80991438(EnWf* this) {
    this->collider2.base.acFlags |= AC_ON;
    Animation_MorphToLoop(&this->skelAnime, &object_wf_Anim_005700, -4.0f);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actor.speedXZ = 8.0f;
    this->actionFunc = func_8099149C;
}

void func_8099149C(EnWf* this, GlobalContext* globalCtx) {
    f32 sp2C;
    s32 sp28;
    s32 pad;
    Player* player = GET_PLAYER(globalCtx);

    if (!func_8099408C(globalCtx, this)) {
        Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 500);
        this->actor.world.rot.y = this->actor.shape.rot.y;
        if (Actor_OtherIsTargeted(globalCtx, &this->actor)) {
            sp2C = 150.0f;
        } else {
            sp2C = 0.0f;
        }

        sp28 = ABS_ALT(BINANG_SUB(player->actor.shape.rot.y, this->actor.shape.rot.y));

        if ((this->actor.xzDistToPlayer < (150.0f + sp2C)) && (player->swordState != 0) && (sp28 >= 0x1F40)) {
            this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
            this->actor.world.rot.y = this->actor.yawTowardsPlayer;
            if (Rand_ZeroOne() > 0.7f) {
                func_80991948(this);
                return;
            }
        }

        SkelAnime_Update(&this->skelAnime);
        if (!func_80990948(globalCtx, this, 0)) {
            if (!Actor_IsFacingPlayer(&this->actor, 0x11C7)) {
                if (Rand_ZeroOne() > 0.5f) {
                    func_80991948(this);
                } else {
                    func_80991200(this);
                }
            } else if (this->actor.xzDistToPlayer < (90.0f + sp2C)) {
                if (!Actor_OtherIsTargeted(globalCtx, &this->actor) &&
                    ((Rand_ZeroOne() > 0.03f) || ((this->actor.xzDistToPlayer <= 80.0f) && (sp28 < 0x38E0)))) {
                    func_80991C04(this);
                } else if (Actor_OtherIsTargeted(globalCtx, &this->actor) && (Rand_ZeroOne() > 0.5f)) {
                    func_8099223C(this);
                } else {
                    func_80991948(this);
                }
            }

            if (this->unk_2A2 == 0) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WOLFOS_CRY);
            }

            func_80990E4C(this, globalCtx);
        }
    }
}

void func_80991738(EnWf* this) {
    Animation_MorphToLoop(&this->skelAnime, &object_wf_Anim_009808, -4.0f);
    this->actionFunc = func_8099177C;
}

void func_8099177C(EnWf* this, GlobalContext* globalCtx) {
    s16 temp_v0;
    s16 phi_v1;
    f32 phi_f2;
    f32 phi_f12;

    if (!func_8099408C(globalCtx, this) && !func_80990948(globalCtx, this, 0)) {
        temp_v0 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
        if (temp_v0 > 0) {
            phi_v1 = (temp_v0 * 0.25f) + 2000.0f;
        } else {
            phi_v1 = (temp_v0 * 0.25f) - 2000.0f;
        }

        this->actor.shape.rot.y += phi_v1;
        this->actor.world.rot.y = this->actor.shape.rot.y;

        if (temp_v0 > 0) {
            phi_f2 = phi_v1 * 0.5f;
            phi_f12 = 1.0f;
            if (phi_f2 > 1.0f) {
                phi_f2 = phi_f12;
            }
        } else {
            phi_f2 = phi_v1 * 0.5f;
            phi_f12 = -1.0f;
            if (phi_f2 < -1.0f) {
                phi_f2 = phi_f12;
            }
        }

        this->skelAnime.playSpeed = -phi_f2;
        SkelAnime_Update(&this->skelAnime);
        if (Actor_IsFacingPlayer(&this->actor, 0x1555)) {
            if (Rand_ZeroOne() > 0.8f) {
                func_80991948(this);
            } else {
                func_80991438(this);
            }
        }
        if (this->unk_2A2 == 0) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WOLFOS_CRY);
        }
    }
}

void func_80991948(EnWf* this) {
    this->collider2.base.acFlags |= AC_ON;
    Animation_MorphToLoop(&this->skelAnime, &object_wf_Anim_005700, -4.0f);
    if (Rand_ZeroOne() > 0.5f) {
        this->unk_29A = 16000;
    } else {
        this->unk_29A = -16000;
    }
    this->actor.speedXZ = 6.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->unk_2A0 = (s32)Rand_ZeroFloat(30.0f) + 30;
    this->actionFunc = func_809919F4;
}

void func_809919F4(EnWf* this, GlobalContext* globalCtx) {
    s16 sp26;
    Player* player = GET_PLAYER(globalCtx);
    s16 temp_v0;

    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer + this->unk_29A, 2500);
    if (!func_8099408C(globalCtx, this) && !func_80990948(globalCtx, this, 0)) {
        this->actor.world.rot.y = this->actor.shape.rot.y;
        sp26 = BINANG_ROT180(player->actor.shape.rot.y + this->unk_29A);
        if (this->actor.bgCheckFlags & 8) {
            temp_v0 = (this->actor.wallYaw - this->actor.yawTowardsPlayer) - this->unk_29A;
            if (ABS_ALT(temp_v0) > 0x2EE0) {
                this->unk_29A = -this->unk_29A;
            }
        }

        SkelAnime_Update(&this->skelAnime);
        func_80990E4C(this, globalCtx);

        if (this->unk_2A2 == 0) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WOLFOS_CRY);
        }

        if ((Math_CosS(sp26 - this->actor.shape.rot.y) < -0.85f) && !Actor_OtherIsTargeted(globalCtx, &this->actor) &&
            (this->actor.xzDistToPlayer <= 80.0f)) {
            func_80991C04(this);
        } else {
            this->unk_2A0--;
            if (this->unk_2A0 == 0) {
                if (Actor_OtherIsTargeted(globalCtx, &this->actor) && (Rand_ZeroOne() > 0.5f)) {
                    func_8099223C(this);
                } else {
                    func_80991200(this);
                    this->unk_2A0 = (s32)Rand_ZeroFloat(3.0f) + 1;
                }
            }
        }
    }
}

void func_80991C04(EnWf* this) {
    this->collider2.base.acFlags |= AC_ON;
    Animation_PlayOnce(&this->skelAnime, &object_wf_Anim_004638);
    this->collider1.base.atFlags &= ~AT_BOUNCED;
    this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    this->unk_2A0 = 7;
    this->skelAnime.endFrame = 20.0f;
    this->actor.speedXZ = 0.0f;
    this->actionFunc = func_80991C80;
}

void func_80991C80(EnWf* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 sp30;
    s32 sp2C;
    s16 sp2A;

    sp2A = BINANG_SUB(player->actor.shape.rot.y, this->actor.shape.rot.y);
    sp30 = ABS_ALT(BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.shape.rot.y));

    this->actor.speedXZ = 0.0f;
    if (((this->skelAnime.curFrame >= 9.0f) && (this->skelAnime.curFrame < 13.0f)) ||
        ((this->skelAnime.curFrame >= 17.0f) && (this->skelAnime.curFrame < 20.0f))) {
        if (!(this->collider1.base.atFlags & AT_ON)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WOLFOS_ATTACK);
        }
        this->collider1.base.atFlags |= AT_ON;
    } else {
        this->collider1.base.atFlags &= ~AT_ON;
    }

    sp2C = Animation_OnFrame(&this->skelAnime, 15.0f);
    if (((sp2C != 0) && !Actor_IsTargeted(globalCtx, &this->actor) &&
         (!Actor_IsFacingPlayer(&this->actor, 0x2000) || (this->actor.xzDistToPlayer >= 100.0f))) ||
        SkelAnime_Update(&this->skelAnime)) {
        if ((sp2C == 0) && (this->unk_2A0 != 0)) {
            this->actor.shape.rot.y += (s16)(0xCCC * (1.5f + ((this->unk_2A0 - 4) * 0.4f)));
            func_80990C6C(this, globalCtx, 1);
            this->unk_2A0--;
        } else if (!Actor_IsFacingPlayer(&this->actor, 0x1554) && (sp2C == 0)) {
            func_80991200(this);
            this->unk_2A0 = (s32)Rand_ZeroFloat(5.0f) + 5;
            if (sp30 >= 0x32C9) {
                this->unk_298 = 7;
            }
        } else if ((Rand_ZeroOne() > 0.7f) || (this->actor.xzDistToPlayer >= 120.0f)) {
            func_80991200(this);
            this->unk_2A0 = (s32)Rand_ZeroFloat(5.0f) + 5;
        } else {
            this->actor.world.rot.y = this->actor.yawTowardsPlayer;
            if (Rand_ZeroOne() > 0.7f) {
                func_80992A74(this, globalCtx);
            } else if (ABS_ALT(sp2A) < 0x2711) {
                if (sp30 >= 0x3E81) {
                    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
                    func_80991948(this);
                } else {
                    func_80990948(globalCtx, this, 1);
                }
            } else {
                func_80991948(this);
            }
        }
    }
}

void func_80991FD8(EnWf* this) {
    f32 phi_f0 = 1.0f;

    if (this->skelAnime.curFrame > 15.0f) {
        phi_f0 = 15.0f;
    }
    Animation_Change(&this->skelAnime, &object_wf_Anim_004638, -0.5f, this->skelAnime.curFrame - 1.0f, phi_f0, 3, 0.0f);
    this->collider1.base.atFlags &= ~AT_ON;
    this->actionFunc = func_80992068;
}

void func_80992068(EnWf* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 sp28;
    s16 sp26;

    sp26 = BINANG_SUB(player->actor.shape.rot.y, this->actor.shape.rot.y);
    sp28 = ABS_ALT(BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.shape.rot.y));

    if (SkelAnime_Update(&this->skelAnime)) {
        if (!Actor_IsFacingPlayer(&this->actor, 0x1554)) {
            func_80991200(this);
            this->unk_2A0 = (s32)Rand_ZeroFloat(5.0f) + 5;
            if (sp28 > 0x32C8) {
                this->unk_298 = 30;
            }
        } else if ((Rand_ZeroOne() > 0.7f) || (this->actor.xzDistToPlayer >= 120.0f)) {
            func_80991200(this);
            this->unk_2A0 = (s32)Rand_ZeroFloat(5.0f) + 5;
        } else {
            this->actor.world.rot.y = this->actor.yawTowardsPlayer;
            if (Rand_ZeroOne() > 0.7f) {
                func_80992A74(this, globalCtx);
            } else if (ABS_ALT(sp26) < 0x2711) {
                if (sp28 > 0x3E80) {
                    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
                    func_80991948(this);
                } else {
                    func_80990948(globalCtx, this, 1);
                }
            } else {
                func_80991948(this);
            }
        }
    }
}

void func_8099223C(EnWf* this) {
    this->collider2.base.acFlags &= ~AC_ON;
    Animation_MorphToPlayOnce(&this->skelAnime, &object_wf_Anim_004A90, -3.0f);
    this->unk_2A0 = 0;
    this->actor.speedXZ = -6.0f;
    this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_TEKU_JUMP);
    this->actionFunc = func_809922B4;
}

void func_809922B4(EnWf* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        if (!Actor_OtherIsTargeted(globalCtx, &this->actor) && (this->actor.xzDistToPlayer < 170.0f) &&
            (this->actor.xzDistToPlayer > 140.0f) && (Rand_ZeroOne() < 0.2f)) {
            func_80991438(this);
        } else if ((globalCtx->gameplayFrames % 2) != 0) {
            func_80992A74(this, globalCtx);
        } else {
            func_80991200(this);
        }
    }
    if (this->unk_2A2 == 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WOLFOS_CRY);
    }
}

void func_809923B0(EnWf* this) {
    this->actor.speedXZ = 0.0f;
    if (this->actor.velocity.y > 0.0f) {
        this->actor.velocity.y = 0.0f;
    }
    this->actionFunc = func_809923E4;
}

void func_809923E4(EnWf* this, GlobalContext* globalCtx) {
    if (this->unk_2A0 != 0) {
        this->unk_2A0--;
    }

    if (this->unk_2A0 == 0) {
        func_80990854(this, globalCtx);
        if (this->actor.colChkInfo.health == 0) {
            func_80992D6C(this);
        } else {
            func_80990948(globalCtx, this, 1);
        }
    }
}

void func_8099245C(EnWf* this) {
    this->collider2.base.acFlags &= ~AC_ON;
    Animation_MorphToPlayOnce(&this->skelAnime, &object_wf_Anim_009A50, -4.0f);
    if (this->actor.bgCheckFlags & 1) {
        this->actor.speedXZ = -4.0f;
    }
    this->unk_298 = 0;
    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WOLFOS_DAMAGE);
    this->actionFunc = func_809924EC;
}

void func_809924EC(EnWf* this, GlobalContext* globalCtx) {
    s16 sp26;

    if (this->actor.bgCheckFlags & 2) {
        this->actor.speedXZ = 0.0f;
    }

    if ((this->actor.bgCheckFlags & 1) && (this->actor.speedXZ < 0.0f)) {
        this->actor.speedXZ += 0.05f;
    }

    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 3000);
    if (SkelAnime_Update(&this->skelAnime)) {
        sp26 = this->actor.wallYaw - this->actor.shape.rot.y;

        if (func_80990948(globalCtx, this, 0)) {
            return;
        }

        if ((this->actor.bgCheckFlags & 8) && (ABS_ALT(sp26) < 0x2EE0) && (this->actor.xzDistToPlayer < 120.0f)) {
            func_809926D0(this);
        } else if (!func_8099408C(globalCtx, this)) {
            if ((this->actor.xzDistToPlayer <= 80.0f) && !Actor_OtherIsTargeted(globalCtx, &this->actor) &&
                ((globalCtx->gameplayFrames % 8) != 0)) {
                func_80991C04(this);
            } else if (Rand_ZeroOne() > 0.5f) {
                func_80991200(this);
                this->unk_2A0 = (s32)Rand_ZeroFloat(5.0f) + 5;
                this->unk_298 = 30;
            } else {
                func_8099223C(this);
            }
        }
    }
}

void func_809926D0(EnWf* this) {
    this->collider2.base.acFlags &= ~AC_ON;
    Animation_Change(&this->skelAnime, &object_wf_Anim_004A90, -1.0f,
                     Animation_GetLastFrame(&object_wf_Anim_004A90.common), 0.0f, 2, -3.0f);
    this->unk_2A0 = 0;
    this->actor.speedXZ = 6.5f;
    this->actor.velocity.y = 15.0f;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_TEKU_JUMP);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = func_80992784;
}

void func_80992784(EnWf* this, GlobalContext* globalCtx) {
    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2500);
    if (SkelAnime_Update(&this->skelAnime) && (this->actor.bgCheckFlags & (2 | 1))) {
        this->actor.shape.rot.x = 0;
        this->actor.world.rot.y = this->actor.yawTowardsPlayer;
        this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
        this->actor.velocity.y = 0.0f;
        this->actor.speedXZ = 0.0f;
        this->actor.world.pos.y = this->actor.floorHeight;
        if (!Actor_OtherIsTargeted(globalCtx, &this->actor)) {
            func_80991C04(this);
        } else {
            func_80991200(this);
        }
    }
}

void func_8099282C(EnWf* this) {
    this->collider2.base.acFlags |= AC_ON;
    this->collider1.base.atFlags &= ~AT_ON;
    this->unk_2A0 = 10;
    this->actor.speedXZ = 0.0f;
    Animation_Change(&this->skelAnime, &object_wf_Anim_004C44, -1.0f,
                     Animation_GetLastFrame(&object_wf_Anim_004C44.common), 0.0f, 2, -2.0f);
    this->actionFunc = func_809928CC;
}

void func_809928CC(EnWf* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 sp2A;

    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->unk_2A0 != 0) {
            this->unk_2A0--;
        } else if (func_800BE184(globalCtx, &this->actor, 100.0f, 10000, 0x4000, this->actor.shape.rot.y)) {
            if ((player->swordAnimation != 0x11) || ((globalCtx->gameplayFrames % 2) != 0)) {
                this->unk_2A0 = 10;
            } else {
                func_8099223C(this);
            }
        } else if (Actor_IsFacingPlayer(&this->actor, 0x4000) && (this->actor.xzDistToPlayer < 60.0f) &&
                   (fabsf(this->actor.playerHeightRel) < 50.0f)) {
            sp2A = player->actor.shape.rot.y - this->actor.shape.rot.y;
            if (!Actor_OtherIsTargeted(globalCtx, &this->actor) &&
                (((globalCtx->gameplayFrames % 2) != 0) || (ABS_ALT(sp2A) < 0x38E0))) {
                func_80991C04(this);
            } else {
                func_80991948(this);
            }
        } else {
            func_80991948(this);
        }
    }
}

void func_80992A74(EnWf* this, GlobalContext* globalCtx) {
    Player* player;
    f32 temp_f0;

    this->collider2.base.acFlags |= AC_ON;
    Animation_MorphToLoop(&this->skelAnime, &object_wf_Anim_005700, -4.0f);
    player = GET_PLAYER(globalCtx);
    temp_f0 = Math_SinS((player->actor.shape.rot.y + this->unk_29A) - this->actor.yawTowardsPlayer);
    if (temp_f0 > 0.0f) {
        this->unk_29A = 16000;
    } else if (temp_f0 < 0.0f) {
        this->unk_29A = -16000;
    } else if (Rand_ZeroOne() > 0.5f) {
        this->unk_29A = 16000;
    } else {
        this->unk_29A = -16000;
    }
    this->actor.speedXZ = 6.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->unk_2A0 = (s32)Rand_ZeroFloat(10.0f) + 5;
    this->actionFunc = func_80992B8C;
}

void func_80992B8C(EnWf* this, GlobalContext* globalCtx) {
    s32 sp28;
    s32 sp2C;
    Player* player = GET_PLAYER(globalCtx);

    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer + this->unk_29A, 2000);
    if (this->actor.bgCheckFlags & 8) {
        sp2C = BINANG_SUB((this->actor.wallYaw - this->actor.yawTowardsPlayer), this->unk_29A);
        if (ABS_ALT(sp2C) > 0x2EE0) {
            this->unk_29A = -this->unk_29A;
        }
    }

    this->actor.world.rot.y = this->actor.shape.rot.y;
    SkelAnime_Update(&this->skelAnime);

    if (!func_80990948(globalCtx, this, 0)) {
        this->unk_2A0--;
        if (this->unk_2A0 == 0) {
            sp28 = ABS_ALT(BINANG_SUB(player->actor.shape.rot.y, this->actor.yawTowardsPlayer));
            if (sp28 >= 0x3A98) {
                func_80991200(this);
                this->unk_2A0 = (s32)Rand_ZeroFloat(3.0f) + 1;
            } else {
                this->actor.world.rot.y = this->actor.shape.rot.y;
                if ((this->actor.xzDistToPlayer <= 80.0f) && !Actor_OtherIsTargeted(globalCtx, &this->actor) &&
                    (((globalCtx->gameplayFrames % 4) == 0) || (sp28 < 0x38E0))) {
                    func_80991C04(this);
                } else {
                    func_80991438(this);
                }
            }
        }

        func_80990E4C(this, globalCtx);

        if (this->unk_2A2 == 0) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WOLFOS_CRY);
        }
    }
}

void func_80992D6C(EnWf* this) {
    this->collider2.base.acFlags &= ~AC_ON;
    Animation_MorphToPlayOnce(&this->skelAnime, &object_wf_Anim_0053D0, -4.0f);
    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    if (this->actor.bgCheckFlags & 1) {
        this->actor.speedXZ = -6.0f;
    }
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->unk_2A0 = 25;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WOLFOS_DEAD);
    this->actionFunc = func_80992E0C;
}

void func_80992E0C(EnWf* this, GlobalContext* globalCtx) {
    static Vec3f D_809942F0 = { 0.0f, 0.5f, 0.0f };

    if (this->actor.bgCheckFlags & 2) {
        this->actor.speedXZ = 0.0f;
    }

    if (this->actor.bgCheckFlags & 1) {
        Math_StepToF(&this->actor.speedXZ, 0.0f, 0.5f);
    }

    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->unk_295 != 0) {
            Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.world.pos, 0x70);
        } else {
            Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.world.pos, 0x60);
        }
        Actor_MarkForDeath(&this->actor);
    } else {
        s32 i;
        Vec3f sp60;

        if (this->unk_2A0 == 25) {
            SoundSource_PlaySfxEachFrameAtFixedWorldPos(globalCtx, &this->actor.world.pos, 36,
                                                        NA_SE_EN_COMMON_EXTINCT_LEV - SFX_FLAG);
        }

        this->unk_2A0--;

        for (i = (25 - this->unk_2A0) >> 1; i >= 0; i--) {
            sp60.x = randPlusMinusPoint5Scaled(60.0f) + this->actor.world.pos.x;
            sp60.z = randPlusMinusPoint5Scaled(60.0f) + this->actor.world.pos.z;
            sp60.y = randPlusMinusPoint5Scaled(50.0f) + (this->actor.world.pos.y + 20.0f);
            func_800B3030(globalCtx, &sp60, &D_809942F0, &D_809942F0, 100, 0, 2);
        }

        func_800B9010(&this->actor, NA_SE_EN_COMMON_EXTINCT_LEV - SFX_FLAG);
    }
}

void func_80992FD4(EnWf* this) {
    Animation_MorphToLoop(&this->skelAnime, &object_wf_Anim_00A3CC, -4.0f);
    this->actionFunc = func_80993018;
}

void func_80993018(EnWf* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
        if (func_80990EAC(this)) {
            func_80990ED4(this);
        } else if (this->actor.child->xzDistToPlayer < (80.0f + this->unk_2A4)) {
            func_80993350(this);
        } else {
            s16 temp_v0 = Actor_YawBetweenActors(this->actor.child, &this->actor);
            s16 temp_v1 = BINANG_SUB(temp_v0 - this->actor.child->yawTowardsPlayer, 0x8000);

            if (ABS_ALT(temp_v1) > 0x800) {
                func_80993148(this);
            } else {
                Math_ScaledStepToS(&this->actor.shape.rot.y, BINANG_ROT180(temp_v0), 0x800);
            }
        }
    } else {
        func_80990ED4(this);
    }
}

void func_80993148(EnWf* this) {
    Animation_MorphToLoop(&this->skelAnime, &object_wf_Anim_005700, -4.0f);
    this->actor.speedXZ = 0.0f;
    this->actionFunc = func_80993194;
}

void func_80993194(EnWf* this, GlobalContext* globalCtx) {
    s16 sp36;
    s16 sp34;
    s16 sp32;

    SkelAnime_Update(&this->skelAnime);
    func_80990E4C(this, globalCtx);
    if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
        if (func_80990EAC(this)) {
            func_80990ED4(this);
        } else {
            if (this->actor.child->xzDistToPlayer < (80.0f + this->unk_2A4)) {
                func_80993350(this);
            } else {
                sp36 = Actor_YawBetweenActors(this->actor.child, &this->actor);
                sp34 = Math_SmoothStepToS(&sp36, BINANG_ROT180(this->actor.child->yawTowardsPlayer), 10, this->unk_29C,
                                          16);
                this->actor.world.pos.x = (Math_SinS(sp36) * this->unk_2A4) + this->actor.child->world.pos.x;
                this->actor.world.pos.z = (Math_CosS(sp36) * this->unk_2A4) + this->actor.child->world.pos.z;
                if (sp34 < -0x800) {
                    sp32 = sp36 - 0x4000;
                } else if (sp34 > 0x800) {
                    sp32 = sp36 + 0x4000;
                } else {
                    sp32 = sp36 + 0x8000;
                    func_80992FD4(this);
                }
                Math_ScaledStepToS(&this->actor.shape.rot.y, sp32, 0x800);
            }
        }
    } else {
        func_80990ED4(this);
    }

    if (this->unk_2A2 == 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WOLFOS_CRY);
    }
}

void func_80993350(EnWf* this) {
    Animation_MorphToLoop(&this->skelAnime, &object_wf_Anim_005700, -4.0f);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WOLFOS_APPEAR);
    this->actionFunc = func_809933A0;
}

void func_809933A0(EnWf* this, GlobalContext* globalCtx) {
    s16 sp2E;
    s16 sp2C;
    s16 phi_a1;

    SkelAnime_Update(&this->skelAnime);
    func_80990E4C(this, globalCtx);
    if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
        if (func_80990EAC(this)) {
            func_80990ED4(this);
        } else {
            sp2E = Actor_YawBetweenActors(this->actor.child, &this->actor);
            Math_ScaledStepToS(&sp2E, this->actor.child->yawTowardsPlayer, this->unk_29C >> 2);
            sp2C = sp2E - this->actor.child->yawTowardsPlayer;
            this->actor.world.pos.x = (Math_SinS(sp2E) * this->unk_2A4) + this->actor.child->world.pos.x;
            this->actor.world.pos.z = (Math_CosS(sp2E) * this->unk_2A4) + this->actor.child->world.pos.z;
            if (sp2C > 0) {
                phi_a1 = sp2E - 0x4000;
            } else {
                phi_a1 = sp2E + 0x4000;
            }
            Math_ScaledStepToS(&this->actor.shape.rot.y, phi_a1, 0x800);
            if (ABS_ALT(sp2C) < 0x3000) {
                func_80991438(this);
            }
        }
    } else {
        func_80990ED4(this);
    }
    if (this->unk_2A2 == 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WOLFOS_CRY);
    }
}

void func_80993524(EnWf* this) {
    Animation_MorphToLoop(&this->skelAnime, &object_wf_Anim_005700, -4.0f);
    this->actor.speedXZ = 6.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = func_8099357C;
}

void func_8099357C(EnWf* this, GlobalContext* globalCtx) {
    s16 sp2E;

    SkelAnime_Update(&this->skelAnime);
    func_80990E4C(this, globalCtx);
    if (this->unk_295 != 0) {
        if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
            sp2E = Actor_YawBetweenActors(&this->actor, this->actor.child);
            if (func_80990EAC(this)) {
                this->actor.child = NULL;
                func_80991738(this);
                return;
            }

            if (this->actor.bgCheckFlags & 8) {
                if (BINANG_SUB(sp2E, this->actor.wallYaw) > 0) {
                    sp2E = this->actor.wallYaw - 0x4000;
                } else {
                    sp2E = this->actor.wallYaw + 0x4000;
                }
            }

            Math_SmoothStepToS(&this->actor.shape.rot.y, sp2E, 10, 0x800, 16);
            this->actor.world.rot.y = this->actor.shape.rot.y;

            if (Actor_XZDistanceBetweenActors(&this->actor, this->actor.child) < (this->unk_2A4 + 10.0f)) {
                func_80993148(this);
            }
        } else {
            this->actor.child = NULL;
            func_80991738(this);
        }
    } else {
        Math_SmoothStepToS(&this->actor.shape.rot.y, Actor_YawToPoint(&this->actor, &this->actor.home.pos), 10, 0x800,
                           16);
        this->actor.world.rot.y = this->actor.shape.rot.y;
        if (Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos) < 40.0f) {
            func_809910F0(this);
        }
    }

    if (this->unk_2A2 == 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WOLFOS_CRY);
    }
}

void func_80993738(EnWf* this, GlobalContext* globalCtx) {
    if ((this->actionFunc == func_80991280) && (this->unk_298 != 0)) {
        this->unk_29E = Math_SinS(this->unk_298 * 4200) * 8920.0f;
    } else if ((this->actionFunc == func_80991C80) || (this->actionFunc == func_8099357C) ||
               (this->actionFunc == func_80991040) || (this->actionFunc == func_80991174)) {
        Math_ScaledStepToS(&this->unk_29E, 0, 1000);
    } else if (this->actionFunc != func_809923E4) {
        Math_ScaledStepToS(&this->unk_29E, this->actor.yawTowardsPlayer - this->actor.shape.rot.y, 1000);
        this->unk_29E = CLAMP(this->unk_29E, -0x3127, 0x3127);
    }
}

void func_8099386C(EnWf* this, GlobalContext* globalCtx) {
    s32 pad;
    ColliderCylinder* collider;

    if (this->collider1.base.acFlags & AC_BOUNCED) {
        this->collider1.base.acFlags &= ~(AC_BOUNCED | AC_HIT);
        this->collider2.base.acFlags &= ~AC_HIT;
        this->collider3.base.acFlags &= ~AC_HIT;
        return;
    }

    if ((this->collider2.base.acFlags & AC_HIT) || (this->collider3.base.acFlags & AC_HIT)) {
        if ((!(this->collider2.base.acFlags & AC_HIT) && (this->collider3.base.acFlags & AC_HIT)) ||
            !Actor_IsFacingPlayer(&this->actor, 0x4A38)) {
            this->actor.colChkInfo.damage *= 4;
        }

        if (this->collider2.base.acFlags & AC_HIT) {
            Actor_SetDropFlag(&this->actor, &this->collider2.info);
            collider = &this->collider2;
        } else {
            Actor_SetDropFlag(&this->actor, &this->collider3.info);
            collider = &this->collider3;
        }

        this->collider2.base.acFlags &= ~AC_HIT;
        this->collider3.base.acFlags &= ~AC_HIT;
        this->collider1.base.atFlags &= ~AT_ON;

        if (((this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) ||
             !(collider->info.acHitInfo->toucher.dmgFlags &
               (0x80000 | 0x40000 | 0x10000 | 0x8000 | 0x2000 | 0x1000 | 0x80 | 0x20 | 0x10 | 0x2 | 0x1))) &&
            (this->actor.colChkInfo.damageEffect != 0xF)) {
            if (!Actor_ApplyDamage(&this->actor)) {
                Enemy_StartFinishingBlow(globalCtx, &this->actor);
            }

            func_80990854(this, globalCtx);

            if (this->actor.colChkInfo.damageEffect == 1) {
                this->unk_2A0 = 40;
                Actor_SetColorFilter(&this->actor, 0, 0x78, 0, 40);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
                func_809923B0(this);
            } else if (this->actor.colChkInfo.damageEffect == 5) {
                this->unk_2A0 = 40;
                Actor_SetColorFilter(&this->actor, 0, 0xFF, 0, 40);
                this->drawDmgEffType = ACTOR_DRAW_DMGEFF_ELECTRIC_SPARKS_SMALL;
                this->drawDmgEffScale = 0.75f;
                this->drawDmgEffAlpha = 2.0f;
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
                func_809923B0(this);
            } else if (this->actor.colChkInfo.damageEffect == 3) {
                func_809907D4(this);
                if (this->actor.colChkInfo.health == 0) {
                    this->unk_2A0 = 3;
                    this->collider2.base.acFlags &= ~AC_ON;
                }
                func_809923B0(this);
            } else {
                if (this->actor.colChkInfo.damageEffect == 2) {
                    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
                    this->drawDmgEffScale = 0.75f;
                    this->drawDmgEffAlpha = 4.0f;
                } else if (this->actor.colChkInfo.damageEffect == 4) {
                    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_LIGHT_ORBS;
                    this->drawDmgEffScale = 0.75f;
                    this->drawDmgEffAlpha = 4.0f;
                    Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, collider->info.bumper.hitPos.x,
                                collider->info.bumper.hitPos.y, collider->info.bumper.hitPos.z, 0, 0, 0,
                                CLEAR_TAG_LARGE_LIGHT_RAYS);
                }

                Actor_SetColorFilter(&this->actor, 0x4000, 0xFF, 0, 8);
                if (this->actor.colChkInfo.health == 0) {
                    func_80992D6C(this);
                } else {
                    func_8099245C(this);
                }
            }
        }
    }
}

void EnWf_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnWf* this = THIS;

    if (this->unk_2A2 == 0) {
        this->unk_2A2 = 96;
    } else {
        this->unk_2A2--;
    }

    func_8099386C(this, globalCtx);
    if (this->actionFunc != func_809923E4) {
        func_809908E0(this);
    }

    this->actionFunc(this, globalCtx);

    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 32.0f, 30.0f, 60.0f, 0x1D);
    func_80993738(this, globalCtx);

    if (this->actor.bgCheckFlags & (2 | 1)) {
        func_800BE3D0(&this->actor, this->actor.shape.rot.y, &this->actor.shape.rot);
    } else {
        Math_ScaledStepToS(&this->actor.shape.rot.x, 0, 600);
        Math_ScaledStepToS(&this->actor.shape.rot.z, 0, 600);
    }

    if (this->actionFunc != func_80990F50) {
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
    }

    if (this->collider2.base.acFlags & AC_ON) {
        Collider_UpdateCylinder(&this->actor, &this->collider2);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider3.base);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider2.base);
    }

    if (this->actionFunc == func_809928CC) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
    }

    if (this->collider1.base.atFlags & AT_ON) {
        if (!(this->collider1.base.atFlags & AT_BOUNCED)) {
            CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
        } else {
            func_80991FD8(this);
        }
    }

    Actor_SetFocus(&this->actor, 25.0f);

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
}

s32 EnWf_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnWf* this = THIS;

    if ((limbIndex == 17) || (limbIndex == 18)) {
        rot->y -= this->unk_29E;
    }
    return false;
}

void EnWf_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static s8 D_809942FC[] = {
        -1, -1, -1, -1, -1, 0, 1, -1, -1, -1, -1, 2, -1, 3, 4, 5, 6, -1, -1, 7, 8, 9,
    };
    EnWf* this = THIS;
    Vec3f sp20;

    Collider_UpdateSpheres(limbIndex, &this->collider1);

    if (D_809942FC[limbIndex] != -1) {
        Matrix_GetStateTranslation(&this->limbPos[D_809942FC[limbIndex]]);
    }

    if (limbIndex == 6) {
        Matrix_GetStateTranslationAndScaledX(1200.0f, &sp20);
        this->collider3.dim.pos.x = sp20.x;
        this->collider3.dim.pos.y = sp20.y;
        this->collider3.dim.pos.z = sp20.z;
    }
}

void EnWf_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnWf* this = THIS;

    if (this->actionFunc != func_80990F50) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        func_8012C28C(globalCtx->state.gfxCtx);

        if (this->actor.params == 0) {
            gSPSegment(POLY_OPA_DISP++, 0x08, D_809942B0[this->unk_294]);
        } else {
            gSPSegment(POLY_OPA_DISP++, 0x08, D_809942C0[this->unk_294]);
        }

        CLOSE_DISPS(globalCtx->state.gfxCtx);

        SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                              this->skelAnime.dListCount, EnWf_OverrideLimbDraw, EnWf_PostLimbDraw, &this->actor);
        Actor_DrawDamageEffects(globalCtx, &this->actor, this->limbPos, ARRAY_COUNT(this->limbPos),
                                this->drawDmgEffScale, this->drawDmgEffFrozenSteamScale, this->drawDmgEffAlpha,
                                this->drawDmgEffType);
    }
}

s32 func_8099408C(GlobalContext* globalCtx, EnWf* this) {
    Actor* temp_v0 = func_800BC270(globalCtx, &this->actor, 80.0f, 0x138B0);
    s16 temp_v1;

    if (temp_v0 != NULL) {
        temp_v1 = (Actor_YawBetweenActors(&this->actor, temp_v0) - this->actor.shape.rot.y) - this->unk_29E;
        if (ABS_ALT(temp_v1) < 0x3000) {
            if (Rand_ZeroOne() < 0.5f) {
                func_8099223C(this);
            } else {
                func_8099282C(this);
            }
            return true;
        }
    }
    return false;
}
