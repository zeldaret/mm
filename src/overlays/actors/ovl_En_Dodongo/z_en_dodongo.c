/*
 * File: z_en_dodongo.c
 * Overlay: ovl_En_Dodongo
 * Description: Dodongo
 */

#include "z_en_dodongo.h"
#include "overlays/actors/ovl_En_Bom/z_en_bom.h"
#include "overlays/actors/ovl_En_Bombf/z_en_bombf.h"
#include "objects/object_dodongo/object_dodongo.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_400)

#define THIS ((EnDodongo*)thisx)

void EnDodongo_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDodongo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDodongo_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDodongo_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_808773C4(EnDodongo* this);
void func_80877424(EnDodongo* this, GlobalContext* globalCtx);
void func_80877494(EnDodongo* this);
void func_80877500(EnDodongo* this, GlobalContext* globalCtx);
void func_808777A8(EnDodongo* this);
void func_8087784C(EnDodongo* this, GlobalContext* globalCtx);
void func_80877D50(EnDodongo* this);
void func_80877D90(EnDodongo* this, GlobalContext* globalCtx);
void func_80877E60(EnDodongo* this, GlobalContext* globalCtx);
void func_80878354(EnDodongo* this);
void func_80878424(EnDodongo* this, GlobalContext* globalCtx);
void func_808785B0(EnDodongo* this, GlobalContext* globalCtx);
void func_8087864C(EnDodongo* this);
void func_808786C8(EnDodongo* this, GlobalContext* globalCtx);
void func_80878724(EnDodongo* this);
void func_808787B0(EnDodongo* this, GlobalContext* globalCtx);

const ActorInit En_Dodongo_InitVars = {
    ACTOR_EN_DODONGO,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_DODONGO,
    sizeof(EnDodongo),
    (ActorFunc)EnDodongo_Init,
    (ActorFunc)EnDodongo_Destroy,
    (ActorFunc)EnDodongo_Update,
    (ActorFunc)EnDodongo_Draw,
};

static ColliderJntSphElementInit sJntSphElementsInit1[10] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0x800CB019, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_HOOKABLE,
            OCELEM_ON,
        },
        { 7, { { 500, 0, 0 }, 27 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0x800CB019, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_HOOKABLE,
            OCELEM_ON,
        },
        { 21, { { -200, 0, 0 }, 20 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0x800CB019, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_HOOKABLE,
            OCELEM_ON,
        },
        { 28, { { -200, 0, 0 }, 20 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0x800CB019, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_HOOKABLE,
            OCELEM_ON,
        },
        { 22, { { 400, -400, 0 }, 20 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0x800CB019, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_HOOKABLE,
            OCELEM_ON,
        },
        { 29, { { 400, -400, 0 }, 20 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_HOOKABLE,
            OCELEM_ON,
        },
        { 16, { { 1000, 0, 0 }, 28 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x08 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_HOOKABLE,
            OCELEM_ON,
        },
        { 14, { { -300, 300, 0 }, 17 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x08 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_HOOKABLE,
            OCELEM_ON,
        },
        { 14, { { 800, 100, 0 }, 15 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x08 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_HOOKABLE,
            OCELEM_ON,
        },
        { 13, { { 600, 0, 0 }, 12 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x08 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_NONE,
            OCELEM_NONE,
        },
        { 13, { { 1500, 0, 0 }, 12 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit1 = {
    {
        COLTYPE_HIT0,
        AT_NONE | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    10,
    sJntSphElementsInit1,
};

static ColliderJntSphInit sJntSphInit2 = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    3,
    sJntSphElementsInit1,
};

static ColliderJntSphElementInit sJntSphElementsInit2[3] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0x20000000, 0x01, 0x10 },
            { 0x00000000, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_NONE,
            OCELEM_NONE,
        },
        { 2, { { 0, -10, 10 }, 25 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0x20000000, 0x01, 0x10 },
            { 0x00000000, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_NONE,
            OCELEM_NONE,
        },
        { 2, { { 0, -5, 50 }, 37 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0x20000000, 0x01, 0x10 },
            { 0x00000000, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_NONE,
            OCELEM_NONE,
        },
        { 2, { { 0, 0, 90 }, 50 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit3 = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_ENEMY,
        AC_NONE,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_JNTSPH,
    },
    3,
    sJntSphElementsInit2,
};

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(0, 0x1),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(2, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(3, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(1, 0xE),
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

static CollisionCheckInfoInit sColChkInfoInit = { 3, 100, 100, 80 };

static InitChainEntry sInitChain[] = {
    ICHAIN_S8(hintId, 13, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -1000, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 1400, ICHAIN_STOP),
};

void EnDodongo_Init(Actor* thisx, GlobalContext* globalCtx) {
    static EffectBlureInit2 D_80879308 = {
        2, 8, 0, { 255, 255, 255, 255 }, { 255, 255, 255, 64 }, { 255, 255, 255, 0 }, { 255, 255, 255, 0 }, 8,
        0, 0, 0, { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    };
    EnDodongo* this = THIS;
    s32 i;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->unk_32C.r = 255;
    this->unk_32C.g = 255;
    this->unk_32C.a = 200;
    this->unk_330.r = 255;
    this->unk_330.g = 10;
    this->unk_330.a = 200;
    Math_Vec3f_Copy(&this->unk_314, &D_801C5DB0);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 48.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &object_dodongo_Skel_008318, &object_dodongo_Anim_004C20,
                   this->jointTable, this->morphTable, 31);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    Collider_InitAndSetJntSph(globalCtx, &this->collider2, &this->actor, &sJntSphInit2, this->collider2Elements);
    Collider_InitAndSetJntSph(globalCtx, &this->collider1, &this->actor, &sJntSphInit1, this->collider1Elements);
    Collider_InitAndSetJntSph(globalCtx, &this->collider3, &this->actor, &sJntSphInit3, this->collider3Elements);

    for (i = 0; i < ARRAY_COUNT(this->collider2Elements); i++) {
        this->collider2.elements[i].info.elemType = ELEMTYPE_UNK2;
        this->collider2.elements[i].info.bumper.dmgFlags = 0x77C34FE6;
    }

    Effect_Add(globalCtx, &this->unk_338, EFFECT_BLURE2, 0, 0, &D_80879308);
    if (this->actor.params == 0) {
        Actor_SetScale(&this->actor, 3.0f / 160.0f);
        this->unk_334 = 1.0f;
    } else {
        Actor_SetScale(&this->actor, 3.0f / 80.0f);
        this->actor.colChkInfo.health = 12;
        this->unk_334 = 2.0f;

        for (i = 0; i < ARRAY_COUNT(this->collider1Elements); i++) {
            this->collider1.elements[i].dim.modelSphere.radius *= 2;
            this->collider1.elements[i].info.toucher.damage *= 2;
        }

        for (i = 0; i < ARRAY_COUNT(this->collider2Elements); i++) {
            this->collider2.elements[i].dim.modelSphere.radius *= 2;
        }

        for (i = 0; i < ARRAY_COUNT(this->collider3Elements); i++) {
            this->collider3.elements[i].dim.modelSphere.radius *= 2;
        }
    }

    func_808773C4(this);
}

void EnDodongo_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnDodongo* this = THIS;

    Effect_Destroy(globalCtx, this->unk_338);
    Collider_DestroyJntSph(globalCtx, &this->collider2);
    Collider_DestroyJntSph(globalCtx, &this->collider3);
    Collider_DestroyJntSph(globalCtx, &this->collider1);
}

void func_80876930(EnDodongo* this, GlobalContext* globalCtx, Vec3f* arg2) {
    static Color_RGBA8 D_8087932C = { 250, 250, 250, 255 };
    static Color_RGBA8 D_80879330 = { 180, 180, 180, 255 };
    static Color_RGBA8 D_80879334 = { 170, 130, 90, 255 };
    static Color_RGBA8 D_80879338 = { 100, 60, 20, 255 };
    static Vec3f D_8087933C = { 0.0f, 0.3f, 0.0f };
    s32 i;
    Vec3f sp88;
    s32 pad2;
    Color_RGBA8* sp80;
    Color_RGBA8* sp7C;
    s32 pad;
    s16 temp1;
    s16 temp2;
    f32 temp3;

    if (func_800C9BB8(&globalCtx->colCtx, this->actor.floorPoly, this->actor.floorBgId) == COLPOLY_SURFACE_SNOW) {
        sp80 = &D_8087932C;
        sp7C = &D_80879330;
    } else {
        sp80 = &D_80879334;
        sp7C = &D_80879338;
    }

    temp1 = this->unk_334 * 300.0f;
    temp2 = this->unk_334 * 15.0f;
    temp3 = this->unk_334 * 30.0f;

    for (i = 0; i < 3; i++) {
        sp88.x = randPlusMinusPoint5Scaled(temp3) + arg2->x;
        sp88.y = Rand_ZeroFloat(5.0f) + this->actor.floorHeight;
        sp88.z = randPlusMinusPoint5Scaled(temp3) + arg2->z;
        D_8087933C.x = randPlusMinusPoint5Scaled(2.0f);
        D_8087933C.z = randPlusMinusPoint5Scaled(2.0f);
        func_800B0DE0(globalCtx, &sp88, &gZeroVec3f, &D_8087933C, sp80, sp7C, temp1, temp2);
    }
}

void func_80876B08(EnDodongo* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 yDiff = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;

    if (ABS_ALT(yDiff) < 0x4000) {
        if (!(player->stateFlags1 & 0x00800000) && (Player_GetMask(globalCtx) != PLAYER_MASK_STONE)) {
            func_808777A8(this);
        } else {
            func_80877494(this);
        }
    } else if (Player_GetMask(globalCtx) != PLAYER_MASK_STONE) {
        func_80878354(this);
    } else {
        func_80877494(this);
    }
}

void func_80876BD0(EnDodongo* this, GlobalContext* globalCtx, s32 arg2) {
    if (this->actor.colChkInfo.damageEffect == 2) {
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
        this->drawDmgEffScale = 0.75f;
        this->drawDmgEffAlpha = 4.0f;
    } else if (this->actor.colChkInfo.damageEffect == 4) {
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_LIGHT_ORBS;
        this->drawDmgEffScale = 0.75f;
        this->drawDmgEffAlpha = 4.0f;
        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG,
                    this->collider1.elements[arg2].info.bumper.hitPos.x,
                    this->collider1.elements[arg2].info.bumper.hitPos.y,
                    this->collider1.elements[arg2].info.bumper.hitPos.z, 0, 0, 0, CLEAR_TAG_LARGE_LIGHT_RAYS);
    }
}

void func_80876CAC(EnDodongo* this) {
    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX;
    this->collider1.base.colType = COLTYPE_HIT3;
    this->drawDmgEffScale = 0.75f;
    this->drawDmgEffFrozenSteamScale = 1.125f;
    this->drawDmgEffAlpha = 1.0f;
    this->timer = 80;
    this->actor.flags &= ~ACTOR_FLAG_400;
    Actor_SetColorFilter(&this->actor, 0x4000, 0xFF, 0, 80);
}

void func_80876D28(EnDodongo* this, GlobalContext* globalCtx) {
    if (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
        this->timer = 0;
        this->actor.colorFilterTimer = 0;
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
        this->collider1.base.colType = COLTYPE_HIT0;
        this->drawDmgEffAlpha = 0.0f;
        Actor_SpawnIceEffects(globalCtx, &this->actor, &this->limbPos[0], 9, 2, this->unk_334 * 0.3f,
                              this->unk_334 * 0.2f);
        this->actor.flags |= ACTOR_FLAG_400;
    }
}

void func_80876DC4(EnDodongo* this, GlobalContext* globalCtx) {
    s32 pad;
    Vec3f sp80;
    Vec3f sp74;
    Vec3f sp68;
    s16 sp66;
    s16 sp64;
    s16 sp62;
    f32 temp_f22;
    f32 temp_f20;

    Math_Vec3f_Copy(&sp68, &this->limbPos[0]);
    sp66 = (Rand_Next() >> 0x12) + this->actor.shape.rot.y;
    temp_f20 = Math_CosS(sp66);
    temp_f22 = Math_SinS(sp66);

    if (this->unk_32C.r > 30) {
        this->unk_32C.r -= 16;
        this->unk_32C.g += -16;
    }

    if (this->unk_32C.b < 30) {
        this->unk_32C.b += 5;
        this->unk_32C.a += 8;
        this->unk_330.a += 8;
    }

    if (this->unk_330.r != 0) {
        this->unk_330.r -= 15;
    }

    if (this->unk_330.g != 0) {
        this->unk_330.g--;
    }

    sp80.x = temp_f22 * 3.5f * this->unk_334;
    sp80.y = this->unk_330.r * 0.02f * this->unk_334;
    sp80.z = temp_f20 * 3.5f * this->unk_334;
    sp74.x = (Rand_ZeroFloat(0.1f) + 0.15f) * -temp_f22 * this->unk_334;
    sp74.y = this->unk_334 * 0.3f;
    sp74.z = (Rand_ZeroFloat(0.1f) + 0.15f) * -temp_f20 * this->unk_334;
    sp64 = this->unk_334 * 100.0f;
    sp62 = this->unk_334 * 25.0f;
    func_800B0EB0(globalCtx, &sp68, &sp80, &sp74, &this->unk_32C, &this->unk_330, sp64, sp62, 0x14);

    sp66 = ((u32)Rand_Next() >> 0x13) + this->actor.shape.rot.y;
    temp_f20 = Math_CosS(sp66);
    temp_f22 = Math_SinS(sp66);

    sp68.x -= (temp_f20 * 6.0f) * this->unk_334;
    sp68.z += (temp_f22 * 6.0f) * this->unk_334;

    sp80.x = -temp_f20 * 3.5f * this->unk_334;
    sp80.z = temp_f22 * 3.5f * this->unk_334;

    sp74.x = (Rand_ZeroFloat(0.1f) + 0.15f) * temp_f20 * this->unk_334;
    sp74.z = (Rand_ZeroFloat(0.1f) + 0.15f) * -temp_f22 * this->unk_334;
    func_800B0EB0(globalCtx, &sp68, &sp80, &sp74, &this->unk_32C, &this->unk_330, sp64, sp62, 0x14);

    sp68.x = this->limbPos[0].x + (temp_f20 * 6.0f * this->unk_334);
    sp68.z = this->limbPos[0].z - (temp_f22 * 6.0f * this->unk_334);
    sp80.x *= -1.0f;
    sp80.z = sp80.z * -1.0f;
    sp74.x = (Rand_ZeroFloat(0.1f) + 0.15f) * -temp_f20 * this->unk_334;
    sp74.z = (Rand_ZeroFloat(0.1f) + 0.15f) * temp_f22 * this->unk_334;
    func_800B0EB0(globalCtx, &sp68, &sp80, &sp74, &this->unk_32C, &this->unk_330, sp64, sp62, 0x14);
}

s32 func_8087721C(EnDodongo* this) {
    if ((this->actionFunc == func_8087784C) && (this->skelAnime.curFrame >= 29.0f) &&
        (this->skelAnime.curFrame <= 43.0f)) {
        return true;
    }
    return false;
}

s32 func_80877278(EnDodongo* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Actor* explosive = globalCtx->actorCtx.actorLists[ACTORCAT_EXPLOSIVES].first;
    Vec3f sp44;

    // Bugfix from OoT
    while (explosive != NULL) {
        if (!explosive->params && (explosive->parent == NULL) && (explosive->update != NULL) &&
            (explosive != player->interactRangeActor) &&
            (((explosive->id == ACTOR_EN_BOM) && (((EnBom*)explosive)->timer > 0)) ||
             ((explosive->id == ACTOR_EN_BOMBF) && (((EnBombf*)explosive)->timer > 0)))) {
            Math_Vec3f_Diff(&explosive->world.pos, &this->unk_308, &sp44);
            if ((fabsf(sp44.x) < 20.0f) && (fabsf(sp44.y) < 10.0f) && (fabsf(sp44.z) < 20.0f)) {
                this->actor.child = explosive;
                explosive->freezeTimer = 30000; // 25 minutes
                return true;
            }
        }
        explosive = explosive->next;
    }
    return false;
}

void func_808773C4(EnDodongo* this) {
    Animation_MorphToLoop(&this->skelAnime, &object_dodongo_Anim_004C20, -4.0f);
    this->actor.speedXZ = 0.0f;
    this->timer = Rand_S16Offset(30, 50);
    this->actionFunc = func_80877424;
}

void func_80877424(EnDodongo* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if (this->timer != 0) {
        this->timer--;
    }

    if (this->timer == 0) {
        if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
            func_80877494(this);
        }
    }
}

void func_80877494(EnDodongo* this) {
    Animation_MorphToLoop(&this->skelAnime, &object_dodongo_Anim_008B1C, -4.0f);
    this->actor.speedXZ = this->unk_334 * 1.5f;
    this->timer = Rand_S16Offset(50, 70);
    this->actionFunc = func_80877500;
}

void func_80877500(EnDodongo* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f sp30;
    s16 temp_v1;

    SkelAnime_Update(&this->skelAnime);
    if (Animation_OnFrame(&this->skelAnime, 19.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_DODO_J_WALK);
        sp30.x = this->collider1Elements[2].dim.worldSphere.center.x;
        sp30.y = this->collider1Elements[2].dim.worldSphere.center.y;
        sp30.z = this->collider1Elements[2].dim.worldSphere.center.z;
        func_80876930(this, globalCtx, &sp30);
    } else if (Animation_OnFrame(&this->skelAnime, 39.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_DODO_J_WALK);
        sp30.x = this->collider1Elements[1].dim.worldSphere.center.x;
        sp30.y = this->collider1Elements[1].dim.worldSphere.center.y;
        sp30.z = this->collider1Elements[1].dim.worldSphere.center.z;
        func_80876930(this, globalCtx, &sp30);
    }

    if ((Math_Vec3f_DistXZ(&this->actor.home.pos, &player->actor.world.pos) < 400.0f) &&
        (Player_GetMask(globalCtx) != PLAYER_MASK_STONE)) {
        temp_v1 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
        Math_ScaledStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 0x1F4);
        if (this->actor.xzDistToPlayer < (100.0f * this->unk_334)) {
            if ((ABS_ALT(temp_v1) < 0x1388) && (this->actor.playerHeightRel < 60.0f) &&
                !(player->stateFlags1 & 0x800000)) {
                func_808777A8(this);
            }
        }
    } else {
        if ((Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos) > 150.0f) ||
            (Player_GetMask(globalCtx) == PLAYER_MASK_STONE)) {
            Math_ScaledStepToS(&this->actor.world.rot.y, Actor_YawToPoint(&this->actor, &this->actor.home.pos), 0x1F4);
        }

        this->timer--;
        if (this->timer == 0) {
            if (Rand_ZeroOne() > 0.7f) {
                this->timer = Rand_S16Offset(50, 70);
            } else {
                func_808773C4(this);
            }
        }
    }

    this->actor.shape.rot.y = this->actor.world.rot.y;
}

void func_808777A8(EnDodongo* this) {
    s32 i;
    Sphere16* sph;

    Animation_MorphToPlayOnce(&this->skelAnime, &object_dodongo_Anim_0028F0, -4.0f);
    this->actor.speedXZ = 0.0f;

    for (i = 0; i < ARRAY_COUNT(this->collider3Elements); i++) {
        sph = &this->collider3.elements[i].dim.worldSphere;

        sph->center.x = this->limbPos[0].x;
        sph->center.y = this->limbPos[0].y;
        sph->center.z = this->limbPos[0].z;
        sph->radius = 0;
    }

    this->actionFunc = func_8087784C;
}

void func_8087784C(EnDodongo* this, GlobalContext* globalCtx) {
    static Vec3f D_80879348 = { 0.0f, 0.9f, 0.0f };
    static Vec3f D_80879354 = { 0.0f, 0.0f, 0.0f };
    s16 frame;
    ColliderJntSphElement* element;
    s32 i;
    s32 end;
    f32 temp_f2;
    f32 temp_f12;

    if (Animation_OnFrame(&this->skelAnime, 24.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_DODO_J_CRY);
    }

    if (func_8087721C(this)) {
        func_800B9010(&this->actor, NA_SE_EN_DODO_J_FIRE - SFX_FLAG);
        frame = this->skelAnime.curFrame - 29.0f;
        end = frame >> 1;
        if (end > 3) {
            end = 3;
        }

        element = &this->collider3.elements[0];
        temp_f2 = Math_SinS(this->actor.shape.rot.y) * this->unk_334;
        temp_f12 = Math_CosS(this->actor.shape.rot.y) * this->unk_334;

        for (i = 0; i < end; i++, element++) {
            element->dim.worldSphere.center.x = this->limbPos[0].x + (element->dim.modelSphere.center.z * temp_f2);
            element->dim.worldSphere.center.y =
                this->limbPos[0].y + (element->dim.modelSphere.center.y * this->unk_334);
            element->dim.worldSphere.center.z = this->limbPos[0].z + (element->dim.modelSphere.center.z * temp_f12);
            element->dim.worldSphere.radius = element->dim.modelSphere.radius;
        }

        D_80879354.y = this->unk_334 * -4.5f;
        D_80879348.x = 2.5f * temp_f2;
        D_80879348.y = this->unk_334 * 1.4f;
        D_80879348.z = 2.5f * temp_f12;
        EffectSsDFire_Spawn(globalCtx, &this->limbPos[0], &D_80879354, &D_80879348, this->unk_334 * 100.0f,
                            this->unk_334 * 35.0f, 0xFF - (frame * 10), 5, 0, 8);
    } else if ((this->skelAnime.curFrame >= 2.0f) && (this->skelAnime.curFrame <= 20.0f)) {
        func_800B9010(&this->actor, NA_SE_EN_DODO_J_BREATH - SFX_FLAG);
    }

    if (SkelAnime_Update(&this->skelAnime)) {
        func_80877D50(this);
    }
}

void func_80877D50(EnDodongo* this) {
    Animation_PlayOnce(&this->skelAnime, &object_dodongo_Anim_003088);
    this->actionFunc = func_80877D90;
}

void func_80877D90(EnDodongo* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        func_808773C4(this);
        this->timer = Rand_S16Offset(10, 20);
    }
}

void func_80877DE0(EnDodongo* this) {
    Animation_Change(&this->skelAnime, &object_dodongo_Anim_0028F0, -1.0f, 35.0f, 0.0f, 2, -4.0f);
    this->actor.flags |= ACTOR_FLAG_10;
    this->timer = 25;
    this->actionFunc = func_80877E60;
    this->actor.speedXZ = 0.0f;
}

void func_80877E60(EnDodongo* this, GlobalContext* globalCtx) {
    static Vec3f D_80879360 = { 0.0f, 0.6f, 0.0f };
    static Color_RGBA8 D_8087936C = { 255, 255, 255, 255 };
    Vec3f sp84;
    Vec3f sp78;
    s16 i;
    Actor* explosive = globalCtx->actorCtx.actorLists[ACTORCAT_EXPLOSIVES].first;
    Vec3f sp64;
    s32 pad;
    s16 sp5E;
    s16 sp5C;

    while (explosive != NULL) {
        if (explosive == this->actor.child) {
            break;
        }
        explosive = explosive->next;
    }

    if (explosive == NULL) {
        this->actor.child = NULL;
    }

    if (this->actor.child != NULL) {
        Math_Vec3f_Copy(&this->actor.child->world.pos, &this->unk_308);
        this->actor.child->freezeTimer = 30000; // 25 minutes
    }

    if (Animation_OnFrame(&this->skelAnime, 28.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_DODO_J_EAT);
        if (this->actor.child != NULL) {
            Actor_MarkForDeath(this->actor.child);
            this->actor.child = NULL;
        }
        this->actor.flags &= ~ACTOR_FLAG_10;
    } else if (this->skelAnime.playSpeed > -0.5f) {
        this->timer--;
        if (this->timer == 10) {
            for (i = 10; i >= 0; i--) {
                sp84.x = randPlusMinusPoint5Scaled(10.0f);
                sp84.y = randPlusMinusPoint5Scaled(10.0f);
                sp84.z = randPlusMinusPoint5Scaled(10.0f);
                sp78.x = sp84.x * -0.1f;
                sp78.y = sp84.y * -0.1f;
                sp78.z = sp84.z * -0.1f;
                sp64.x = this->collider1Elements[0].dim.worldSphere.center.x + sp84.x;
                sp64.y = this->collider1Elements[0].dim.worldSphere.center.y + sp84.y;
                sp64.z = this->collider1Elements[0].dim.worldSphere.center.z + sp84.z;
                func_800B0EB0(globalCtx, &sp64, &sp84, &sp78, &this->unk_32C, &this->unk_330, this->unk_334 * 400.0f,
                              this->unk_334 * 10.0f, 10);
            }

            Actor_PlaySfxAtPos(&this->actor, NA_SE_IT_BOMB_EXPLOSION);
            if (this->actor.colChkInfo.health <= 4) {
                this->actor.colChkInfo.health = 0;
                Enemy_StartFinishingBlow(globalCtx, &this->actor);
            } else {
                this->actor.colChkInfo.health -= 4;
            }
            Actor_SetColorFilter(&this->actor, 0x4000, 0x78, 0, 8);
        }
    } else if (Animation_OnFrame(&this->skelAnime, 24.0f)) {
        this->timer--;
        this->skelAnime.playSpeed = 0.0f;
    }

    if (this->skelAnime.curFrame <= 27.0f) {
        if ((this->skelAnime.curFrame <= 25.0f) && (this->timer < 11)) {
            func_80876DC4(this, globalCtx);
        } else {
            sp5E = this->unk_334 * 50.0f;
            sp5C = this->unk_334 * 5.0f;
            Math_Vec3f_Copy(&sp64, &this->limbPos[0]);
            func_800B0DE0(globalCtx, &sp64, &gZeroVec3f, &D_80879360, &D_8087936C, &D_8087936C, sp5E, sp5C);
            sp64.x -= Math_CosS(this->actor.shape.rot.y) * 6.0f * this->unk_334;
            sp64.z += Math_SinS(this->actor.shape.rot.y) * 6.0f * this->unk_334;
            func_800B0DE0(globalCtx, &sp64, &gZeroVec3f, &D_80879360, &D_8087936C, &D_8087936C, sp5E, sp5C);
            sp64.x = (2.0f * this->limbPos[0].x) - sp64.x;
            sp64.z = (2.0f * this->limbPos[0].z) - sp64.z;
            func_800B0DE0(globalCtx, &sp64, &gZeroVec3f, &D_80879360, &D_8087936C, &D_8087936C, sp5E, sp5C);
        }
    }

    this->unk_314.z = Math_SinS((this->actor.colorFilterTimer * 0x1000) >> 1) + 1.0f;
    this->unk_314.x = Math_SinS(this->actor.colorFilterTimer * 0x1000) + 1.0f;
    this->unk_314.y = this->unk_314.z;
    SkelAnime_Update(&this->skelAnime);
    if (this->timer == 0) {
        if (this->actor.colChkInfo.health == 0) {
            func_80878724(this);
        } else {
            func_8087864C(this);
        }
        this->unk_304 = 1;
    }
}

void func_80878354(EnDodongo* this) {
    s32 pad;
    AnimationHeader* sp18;
    s16 yDiff = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;

    this->unk_306 = (0xFFFF - ABS_ALT(yDiff)) / 15;

    if (yDiff >= 0) {
        sp18 = &object_dodongo_Anim_0042C4;
        this->unk_306 = -this->unk_306;
    } else {
        sp18 = &object_dodongo_Anim_003B14;
    }

    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_DODO_J_TAIL);
    Animation_PlayOnceSetSpeed(&this->skelAnime, sp18, 2.0f);
    this->timer = 0;
    this->collider1.base.atFlags |= AT_ON;
    this->unk_304 = -1;
    this->actionFunc = func_80878424;
}

void func_80878424(EnDodongo* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f sp20;

    this->timer++;
    if (SkelAnime_Update(&this->skelAnime)) {
        if (!(player->stateFlags1 & 0x800000) && (Player_GetMask(globalCtx) != PLAYER_MASK_STONE)) {
            this->collider1.base.atFlags &= ~AT_ON;
            func_808777A8(this);
        } else {
            func_80877494(this);
        }
        return;
    }

    this->actor.world.rot.y += this->unk_306;
    this->actor.shape.rot.y = this->actor.world.rot.y;
    sp20.x = this->collider1Elements[1].dim.worldSphere.center.x;
    sp20.y = this->collider1Elements[1].dim.worldSphere.center.y;
    sp20.z = this->collider1Elements[1].dim.worldSphere.center.z;
    func_80876930(this, globalCtx, &sp20);
    sp20.x = this->collider1Elements[2].dim.worldSphere.center.x;
    sp20.y = this->collider1Elements[2].dim.worldSphere.center.y;
    sp20.z = this->collider1Elements[2].dim.worldSphere.center.z;
    func_80876930(this, globalCtx, &sp20);
    CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
    this->actor.flags |= ACTOR_FLAG_1000000;
}

void func_80878594(EnDodongo* this) {
    this->actionFunc = func_808785B0;
    this->actor.speedXZ = 0.0f;
}

void func_808785B0(EnDodongo* this, GlobalContext* globalCtx) {
    if (this->timer != 0) {
        this->timer--;
    }

    if (this->timer == 0) {
        func_80876D28(this, globalCtx);
        if (this->actor.colChkInfo.health == 0) {
            func_80878724(this);
        } else if (this->actor.xzDistToPlayer > 100.0f * this->unk_334) {
            func_80877494(this);
        } else {
            func_80876B08(this, globalCtx);
        }
    }
}

void func_8087864C(EnDodongo* this) {
    Animation_MorphToPlayOnce(&this->skelAnime, &object_dodongo_Anim_001A44, -4.0f);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_DODO_J_DAMAGE);
    this->timer = 0;
    this->unk_304 = 0;
    this->actor.speedXZ = 0.0f;
    Actor_SetColorFilter(&this->actor, 0x4000, 0xFF, 0, 8);
    this->actionFunc = func_808786C8;
}

void func_808786C8(EnDodongo* this, GlobalContext* globalCtx) {
    if (this->unk_304 == 1) {
        func_80876DC4(this, globalCtx);
    }

    if (SkelAnime_Update(&this->skelAnime)) {
        func_80876B08(this, globalCtx);
    }
}

void func_80878724(EnDodongo* this) {
    Animation_MorphToPlayOnce(&this->skelAnime, &object_dodongo_Anim_0013C4, -8.0f);
    this->timer = 0;
    this->unk_304 = 0;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_DODO_J_DEAD);
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->actor.speedXZ = 0.0f;
    Actor_SetColorFilter(&this->actor, 0x4000, 0xFF, 0, 8);
    this->actionFunc = func_808787B0;
}

void func_808787B0(EnDodongo* this, GlobalContext* globalCtx) {
    s32 pad;

    if (this->skelAnime.curFrame < 35.0f) {
        if (this->unk_304 != 0) {
            func_80876DC4(this, globalCtx);
        }
    } else if (this->actor.colorFilterTimer == 0) {
        Actor_SetColorFilter(&this->actor, 0x4000, 0x78, 0, 4);
    }

    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->timer == 0) {
            EnBom* bomb = (EnBom*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_BOM, this->actor.world.pos.x,
                                              this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, 0);
            if (bomb != NULL) {
                bomb->timer = 0;
            }
            this->timer = 8;
        }
    } else if (Animation_OnFrame(&this->skelAnime, 52.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GERUDOFT_DOWN);
    }

    if (this->timer != 0) {
        this->timer--;
        if (this->timer == 0) {
            if (this->actor.params == 0) {
                Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.world.pos, 0x90);
            } else {
                Item_DropCollectible(globalCtx, &this->actor.world.pos, ITEM00_RUPEE_PURPLE);
            }
            Actor_MarkForDeath(&this->actor);
        }
    }
}

void EnDodongo_UpdateDamage(EnDodongo* this, GlobalContext* globalCtx) {
    Vec3f sp3C;
    s32 i;

    if (this->collider2.base.acFlags & AC_HIT) {
        this->collider2.base.acFlags &= ~AC_HIT;
        this->collider1.base.acFlags &= ~AC_HIT;

        for (i = 0; i < ARRAY_COUNT(this->collider2Elements); i++) {
            if (this->collider2.elements[i].info.bumperFlags & BUMP_HIT) {
                break;
            }
        }

        if ((i != ARRAY_COUNT(this->collider2Elements)) &&
            ((this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) ||
             !(this->collider2.elements[i].info.acHitInfo->toucher.dmgFlags & 0xDB0B3))) {
            func_80876D28(this, globalCtx);
            Math_Vec3s_ToVec3f(&sp3C, &this->collider2.elements[i].info.bumper.hitPos);
            if (this->actor.colChkInfo.damageEffect == 0xF) {
                CollisionCheck_BlueBlood(globalCtx, NULL, &sp3C);
                EffectSsHitMark_SpawnFixedScale(globalCtx, 0, &sp3C);
            } else if (this->actor.colChkInfo.damageEffect != 14) {
                EffectSsHitMark_SpawnFixedScale(globalCtx, 3, &sp3C);
                CollisionCheck_SpawnShieldParticlesMetalSound(globalCtx, &sp3C, &this->actor.projectedPos);
            }
        }
    } else if (this->collider1.base.acFlags & AC_HIT) {
        this->collider2.base.acFlags &= ~AC_HIT;
        this->collider1.base.acFlags &= ~AC_HIT;
        Actor_SetDropFlagJntSph(&this->actor, &this->collider1);

        for (i = 0; i < ARRAY_COUNT(this->collider1Elements); i++) {
            if (this->collider1.elements[i].info.bumperFlags & BUMP_HIT) {
                break;
            }
        }

        if ((i != ARRAY_COUNT(this->collider1Elements)) &&
            ((this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) ||
             !(this->collider1.elements[i].info.acHitInfo->toucher.dmgFlags & 0xDB0B3))) {
            func_80876D28(this, globalCtx);
            if (this->actor.colChkInfo.damageEffect != 0xF) {
                if (!Actor_ApplyDamage(&this->actor)) {
                    Enemy_StartFinishingBlow(globalCtx, &this->actor);
                    if (this->actor.colChkInfo.damageEffect == 3) {
                        func_80876CAC(this);
                        this->timer = 3;
                        this->collider1.base.acFlags &= ~AC_ON;
                        this->collider2.base.acFlags &= ~AC_ON;
                        func_80878594(this);
                    } else {
                        func_80876BD0(this, globalCtx, i);
                        func_80878724(this);
                    }
                } else if (this->actor.colChkInfo.damageEffect == 1) {
                    this->timer = 40;
                    Actor_SetColorFilter(&this->actor, 0, 0xFF, 0, 40);
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
                    func_80878594(this);
                } else if (this->actor.colChkInfo.damageEffect == 5) {
                    this->timer = 40;
                    Actor_SetColorFilter(&this->actor, 0, 0xFF, 0, 40);
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
                    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_ELECTRIC_SPARKS_SMALL;
                    this->drawDmgEffScale = 0.75f;
                    this->drawDmgEffAlpha = 2.0f;
                    func_80878594(this);
                } else if (this->actor.colChkInfo.damageEffect == 3) {
                    func_80876CAC(this);
                    func_80878594(this);
                } else {
                    func_80876BD0(this, globalCtx, i);
                    func_8087864C(this);
                }
            }
        }
    }
}

void EnDodongo_Update(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnDodongo* this = THIS;

    EnDodongo_UpdateDamage(this, globalCtx);
    this->actionFunc(this, globalCtx);
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 75.0f, 60.0f, 70.0f, 0x1D);
    if (this->actor.bgCheckFlags & 2) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GERUDOFT_DOWN);
    }

    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
    if (this->actionFunc != func_808787B0) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider2.base);
        if ((this->actionFunc != func_808786C8) && (this->actionFunc != func_80877E60)) {
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
            if ((this->actionFunc != func_8087784C) && func_80877278(this, globalCtx)) {
                func_80877DE0(this);
            }
        }
    }

    if (func_8087721C(this)) {
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider3.base);
    }

    if (this->drawDmgEffAlpha > 0.0f) {
        if (this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
            Math_StepToF(&this->drawDmgEffAlpha, 0.0f, 0.05f);
            this->drawDmgEffScale = (this->drawDmgEffAlpha + 1.0f) * 0.375f;
            this->drawDmgEffScale = (this->drawDmgEffScale > 0.75f) ? 0.75f : this->drawDmgEffScale;
        } else if (!Math_StepToF(&this->drawDmgEffFrozenSteamScale, 0.75f, 0.01875f)) {
            func_800B9010(&this->actor, NA_SE_EV_ICE_FREEZE - SFX_FLAG);
        }
    }
}

s32 EnDodongo_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                               Actor* thisx) {
    EnDodongo* this = THIS;

    if (limbIndex == 1) {
        pos->z += 1000.0f;
    } else if ((limbIndex == 15) || (limbIndex == 16)) {
        Matrix_Scale(this->unk_314.x, this->unk_314.y, this->unk_314.z, MTXMODE_APPLY);
    }

    return false;
}

void EnDodongo_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Vec3f D_80879370 = { 1800.0f, 1200.0f, 0.0f };
    static Vec3f D_8087937C = { 1500.0f, 300.0f, 0.0f };
    static s8 D_80879388[] = {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2, 3,  4,
        -1, -1, -1, -1, -1, 5,  6,  -1, -1, -1, -1, -1, 7,  8, -1, 0,
    };
    EnDodongo* this = THIS;

    Collider_UpdateSpheres(limbIndex, &this->collider1);
    Collider_UpdateSpheres(limbIndex, &this->collider2);
    if (D_80879388[limbIndex] != -1) {
        Matrix_GetStateTranslation(&this->limbPos[D_80879388[limbIndex]]);
    }

    if (limbIndex == 7) {
        Matrix_MultiplyVector3fByState(&D_80879370, &this->unk_308);
        Matrix_MultiplyVector3fByState(&D_8087937C, &this->limbPos[0]);
        Matrix_GetStateTranslation(&this->actor.focus.pos);
        Matrix_GetStateTranslationAndScaledY(-200.0f, &this->limbPos[1]);
    } else if (limbIndex == 13) {
        Matrix_GetStateTranslationAndScaledX(1600.0f, &this->unk_320);
    }

    if ((limbIndex == 30) && (this->actionFunc == func_80878424) && (this->timer != this->unk_304)) {
        EffectBlure_AddVertex(Effect_GetByIndex(this->unk_338), &this->unk_320, &this->limbPos[4]);
        this->unk_304 = this->timer;
    }
}

void EnDodongo_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnDodongo* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, EnDodongo_OverrideLimbDraw,
                      EnDodongo_PostLimbDraw, &this->actor);
    Actor_DrawDamageEffects(globalCtx, &this->actor, this->limbPos, ARRAY_COUNT(this->limbPos),
                            this->drawDmgEffScale * this->unk_334, this->drawDmgEffFrozenSteamScale * this->unk_334,
                            this->drawDmgEffAlpha, this->drawDmgEffType);
}
