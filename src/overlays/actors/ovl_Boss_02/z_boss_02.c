/*
 * File: z_boss_02.c
 * Overlay: ovl_Boss_02
 * Description: Twinmold
 */

#include "z_boss_02.h"
#include "overlays/actors/ovl_Door_Warp1/z_door_warp1.h"
#include "overlays/actors/ovl_Item_B_Heart/z_item_b_heart.h"
#include "objects/object_boss02/object_boss02.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((Boss02*)thisx)

void Boss02_Init(Actor* thisx, GlobalContext* globalCtx);
void Boss02_Destroy(Actor* thisx, GlobalContext* globalCtx);
void Boss02_Update(Actor* thisx, GlobalContext* globalCtx);
void Boss02_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_809DAA74(Boss02* this, GlobalContext* globalCtx);
void func_809DAA98(Boss02* this, GlobalContext* globalCtx);
void func_809DAAA8(Boss02* this, GlobalContext* globalCtx);
void func_809DAB78(Boss02* this, GlobalContext* globalCtx);
void func_809DC218(Actor* thisx, GlobalContext* globalCtx);
void func_809DC78C(Actor* thisx, GlobalContext* globalCtx);
void func_809DD0A8(Actor* thisx, GlobalContext* globalCtx);
void func_809DD0CC(GlobalContext* globalCtx);
void func_809DD2F8(GlobalContext* globalCtx);
void func_809DD934(Boss02* this, GlobalContext* globalCtx);
void func_809DEAC4(Boss02* this, GlobalContext* globalCtx);

static u8 D_809E0420;
static u8 D_809E0421;
static u8 D_809E0422;
static Boss02* D_809E0424;
static Boss02* D_809E0428;
static Boss02* D_809E042C;
static u8 D_809E0430;
static DoorWarp1* D_809E0434;
static Boss02Effects D_809E0438[150];

static DamageTable sDamageTable1 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(0, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
    /* Goron punch    */ DMG_ENTRY(2, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(0, 0xF),
    /* Fire arrow     */ DMG_ENTRY(5, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x0),
    /* Deku bubble    */ DMG_ENTRY(0, 0x0),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(2, 0xF),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

static DamageTable sDamageTable2 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(0, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
    /* Goron punch    */ DMG_ENTRY(2, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(0, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(5, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x0),
    /* Deku bubble    */ DMG_ENTRY(0, 0x0),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(2, 0xF),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

const ActorInit Boss_02_InitVars = {
    ACTOR_BOSS_02,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BOSS02,
    sizeof(Boss02),
    (ActorFunc)Boss02_Init,
    (ActorFunc)Boss02_Destroy,
    (ActorFunc)Boss02_Update,
    (ActorFunc)Boss02_Draw,
};

static f32 D_809DF5B0 = 1.0f;

static s16 D_809DF5B4[] = {
    0, 195, 190, 185, 180, 175, 170, 165, 160, 155, 150, 145, 140, 135, 130, 125, 120, 115, 110, 105, 100, 95, 90, 0,
};

static s16 D_809DF5E4[] = {
    0, 196, 192, 188, 184, 180, 176, 172, 168, 164, 160, 156, 152, 148, 144, 140, 136, 132, 128, 124, 120, 116, 112,
};

static ColliderJntSphElementInit sJntSphElementsInit1[22] = {
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x04, 0x10 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 1, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x04, 0x10 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 2, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x04, 0x10 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 3, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x04, 0x10 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 4, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x04, 0x10 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 5, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x04, 0x10 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 6, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x04, 0x10 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 7, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x04, 0x10 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 8, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x04, 0x10 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 9, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x04, 0x10 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 10, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x04, 0x10 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 11, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x04, 0x10 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 12, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x04, 0x10 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 13, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x04, 0x10 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 14, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x04, 0x10 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 15, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x04, 0x10 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 16, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x04, 0x10 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 17, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x04, 0x10 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 18, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x04, 0x10 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 19, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x04, 0x10 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 20, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x04, 0x10 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 21, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x04, 0x10 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 0, { { 0, 0, 0 }, 130 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit1 = {
    {
        COLTYPE_METAL,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_PLAYER,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    22,
    sJntSphElementsInit1,
};

static ColliderJntSphElementInit sJntSphElementsInit2[2] = {
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x04, 0x10 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 0, { { 0, 0, 0 }, 130 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x04, 0x10 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 22, { { 0, 0, 0 }, 110 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit2 = {
    {
        COLTYPE_HIT0,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_PLAYER,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    2,
    sJntSphElementsInit2,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_METAL,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK2,
        { 0xF7CFFFFF, 0x04, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 150, 200, 0, { 0, 0, 0 } },
};

static Vec3f D_809DF9C0[] = {
    { 0.0f, -200.0f, 1000.0f },    { 0.0f, 500.0f, 1000.0f },        { 0.0f, 1000.0f, 1000.0f },
    { 1000.0f, 500.0f, 1000.0f },  { 1000.0f, 1000.0f, -1000.0f },   { -1000.0f, 500.0f, -1000.0f },
    { -1000.0f, 500.0f, 1000.0f }, { -1000.0f, -1000.0f, -1000.0f }, { -1000.0f, -1000.0f, -1000.0f },
};

static Vec3f D_809DFA2C[] = {
    { 0.0f, -200.0f, -800.0f },  { 0.0f, 800.0f, -800.0f },   { 800.0f, 300.0f, -800.0f },
    { -800.0f, 800.0f, 0.0f },   { -800.0f, -1000.0f, 0.0f }, { -800.0f, -1000.0f, 0.0f },
    { -800.0f, -1000.0f, 0.0f }, { -800.0f, -1000.0f, 0.0f }, { -800.0f, -1000.0f, 0.0f },
};

void func_809DA1D0(GlobalContext* globalCtx, u8 arg1, u8 arg2, u8 arg3, u8 arg4) {
    MREG(64) = 1;
    MREG(65) = arg1;
    MREG(66) = arg2;
    MREG(67) = arg3;
    MREG(68) = arg4;
}

void func_809DA22C(GlobalContext* globalCtx, u8 arg1) {
    MREG(68) = arg1;
}

void func_809DA24C(GlobalContext* globalCtx) {
    MREG(64) = 0;
}

void func_809DA264(Boss02Effects* effects, Vec3f* vec, f32 arg2) {
    s16 i;

    for (i = 0; i < ARRAY_COUNT(D_809E0438); i++, effects++) {
        if (effects->unk_24 == 0) {
            effects->unk_24 = 1;
            effects->unk_00 = *vec;
            effects->unk_0C.x = randPlusMinusPoint5Scaled(30.0f);
            effects->unk_0C.y = Rand_ZeroFloat(7.0f) + 7.0f;
            effects->unk_0C.z = randPlusMinusPoint5Scaled(30.0f);
            effects->unk_18.y = -0.3f;
            effects->unk_34 = arg2;
            effects->unk_2C = 255;
            effects->unk_26 = 0;
            effects->unk_38 = 2.0f * arg2;
            effects->unk_18.x = effects->unk_18.z = 0.0f;
            break;
        }
    }
}

void func_809DA344(Boss02Effects* effects, Vec3f* vec) {
    s16 i;

    for (i = 0; i < ARRAY_COUNT(D_809E0438); i++, effects++) {
        if (effects->unk_24 == 0) {
            effects->unk_24 = 3;
            effects->unk_00 = *vec;
            effects->unk_26 = Rand_ZeroFloat(20.0f);
            effects->unk_0C.x = randPlusMinusPoint5Scaled(50.0f);
            effects->unk_0C.y = randPlusMinusPoint5Scaled(50.0f);
            effects->unk_0C.z = randPlusMinusPoint5Scaled(50.0f);
            effects->unk_18.z = 0.0f;
            effects->unk_18.x = 0.0f;
            effects->unk_18.y = -1.5f;
            effects->unk_34 = Rand_ZeroFloat(0.04f) + 0.02f;
            effects->unk_30 = Rand_ZeroFloat(32767.0f);
            effects->unk_2E = Rand_ZeroFloat(32767.0f);
            break;
        }
    }
}

void func_809DA460(Boss02Effects* effects, Vec3f* vec) {
    s16 i;

    for (i = 0; i < ARRAY_COUNT(D_809E0438); i++, effects++) {
        if ((effects->unk_24 == 0) || (effects->unk_24 == 3)) {
            effects->unk_24 = 4;
            effects->unk_00 = *vec;
            Math_Vec3f_Copy(&effects->unk_0C, &gZeroVec3f);
            Math_Vec3f_Copy(&effects->unk_18, &gZeroVec3f);
            effects->unk_2C = 0xFF;
            effects->unk_34 = 0.0f;
            break;
        }
    }
}

void func_809DA50C(s32 arg0, ColliderJntSph* collider, Vec3f* arg2) {
    collider->elements[arg0].dim.worldSphere.center.x = arg2->x;
    collider->elements[arg0].dim.worldSphere.center.y = arg2->y;
    collider->elements[arg0].dim.worldSphere.center.z = arg2->z;
    collider->elements[arg0].dim.worldSphere.radius =
        collider->elements[arg0].dim.modelSphere.radius * collider->elements[arg0].dim.scale * D_809DF5B0;
}

void Boss02_Init(Actor* thisx, GlobalContext* globalCtx) {
    Boss02* this = THIS;
    s32 i;
    s32 pad[2];

    if ((gSaveContext.save.weekEventReg[52] & 0x20) && (this->actor.params == 0)) {
        D_809E0434 = (DoorWarp1*)Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_DOOR_WARP1,
                                                    0.0f, 60.0f, 0.0f, 0, 0, 0, 1);
        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_ITEM_B_HEART, 0.0f, 30.0f, -150.0f, 0, 1, 0, 0);
    }

    this->actor.targetMode = 10;
    this->unk_1D3C.z = this->unk_1D3C.x = 0.0f;
    this->unk_1D3C.y = 1.0f;
    if (this->actor.params == 200) {
        D_809E042C = this;
        globalCtx->specialEffects = (void*)D_809E0438;
        this->actor.update = func_809DC78C;
        this->actor.draw = func_809DD0A8;
        this->actor.flags &= ~ACTOR_FLAG_1;
        this->unk_1D70 = 0.00999999977648f;
        if ((KREG(64) != 0) || (gSaveContext.eventInf[5] & 0x20) || (D_809E0434 != NULL)) {
            this->unk_1D20 = 0;
            D_809E0430 = KREG(15) + 20;
        } else {
            this->unk_1D20 = 1;
        }
        XREG(41) = KREG(14) + 20;
        this->unk_01AC = 1.0f;
        Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_TANRON5, 0.0f, 1000.0f, 0.0f, 0, 0,
                           0, 0);
    } else if (this->actor.params == 100) {
        this->actor.update = func_809DC218;
        this->actor.draw = NULL;
        this->actor.hintId = 0x2E;
    } else {
        if (this->actor.params != 35) {
            this->actor.params = 0;
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_BOSS_02, 0.0f, 0.0f, 0.0f, 0, 0, 0, 200);
            D_809E0424 = this;
            D_809E0428 = (Boss02*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_BOSS_02, this->actor.world.pos.x,
                                              this->actor.world.pos.y, this->actor.world.pos.z, this->actor.world.rot.x,
                                              this->actor.world.rot.y, this->actor.world.rot.z, 35);
            D_809E0424->actor.colChkInfo.damageTable = &sDamageTable2;
            D_809E0428->actor.colChkInfo.damageTable = &sDamageTable1;
            D_809E0424->unk_1674 = D_809E0428;
            D_809E0428->unk_1674 = D_809E0424;
        }

        this->actor.colChkInfo.mass = MASS_HEAVY;
        this->actor.colChkInfo.health = 20;
        Actor_SetScale(&this->actor, 0.01f);
        SkelAnime_Init(globalCtx, &this->skelAnime, &object_boss02_Skel_009B10, &object_boss02_Anim_009C78,
                       this->jointTable, this->morphTable, 13);
        Collider_InitAndSetJntSph(globalCtx, &this->colliderSphere1, &this->actor, &sJntSphInit1,
                                  this->colliderSphere1Elements);
        Collider_InitAndSetJntSph(globalCtx, &this->colliderSphere2, &this->actor, &sJntSphInit2,
                                  this->colliderSphere2Elements);
        Collider_InitAndSetCylinder(globalCtx, &this->colliderCylinder, &this->actor, &sCylinderInit);

        if (D_809E0434 != NULL) {
            func_809DAA74(this, globalCtx);
        } else {
            func_809DAAA8(this, globalCtx);
        }

        for (i = 0; i < ARRAY_COUNT(this->unk_01BC); i++) {
            this->unk_01BC[i].x = this->actor.world.pos.x;
            this->unk_01BC[i].y = this->actor.world.pos.y;
            this->unk_01BC[i].z = this->actor.world.pos.z;
        }

        this->unk_014C = Rand_ZeroFloat(1000.0f);
        this->unk_1678 = 22;
        Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_BOSS_02, 0.0f, 0.0f, 0.0f, 0, 0, 0,
                           100);
    }
}

void Boss02_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void func_809DAA74(Boss02* this, GlobalContext* globalCtx) {
    this->actionFunc = func_809DAA98;
    this->actor.world.pos.y = -3000.0f;
}

void func_809DAA98(Boss02* this, GlobalContext* globalCtx) {
}

void func_809DAAA8(Boss02* this, GlobalContext* globalCtx) {
    this->actionFunc = func_809DAB78;
    Animation_MorphToLoop(&this->skelAnime, &object_boss02_Anim_009C78, 0.0f);
    if (D_809E042C->unk_1D20 != 0) {
        this->unk_0144 = 10;
    } else {
        this->unk_0144 = 100;
        this->unk_01A8 = 25.0f;
        D_809E042C->unk_1D7E = 100;
        this->actor.world.pos.x = 0.0f;
        if (D_809E0424 == this) {
            this->actor.world.pos.z = -1000.0f;
        } else {
            this->actor.world.pos.z = 1400.0f;
        }
    }
    this->actor.world.pos.y = -500.0f;
}

void func_809DAB78(Boss02* this, GlobalContext* globalCtx) {
    static Color_RGBA8 D_809DFA98 = { 185, 140, 70, 255 };
    s32 pad;
    Player* player = GET_PLAYER(globalCtx);
    CollisionPoly* spDC;
    Vec3f spD0;
    f32 spCC;
    f32 spC8;
    f32 spC4;
    s32 i;
    f32 temp_f0;
    f32 phi_f2;
    s16 temp_s0;
    s16 temp_s2;
    Boss02* spB0 = this->unk_1674;
    Vec3f spA4;
    f32 spA0;
    f32 sp9C;
    Vec3f sp90;
    CollisionPoly* sp8C;
    s32 sp88;
    Vec3f sp7C;
    Vec3f sp70;
    Vec3f sp64;

    spCC = this->unk_01B0.x - this->actor.world.pos.x;
    spC8 = this->unk_01B0.y - this->actor.world.pos.y;
    spC4 = this->unk_01B0.z - this->actor.world.pos.z;

    if ((this->unk_0144 != 10) && (this->unk_0144 <= 20)) {
        SkelAnime_Update(&this->skelAnime);
        temp_s0 = Math_Atan2S(spCC, spC4);
        temp_s2 = Math_Atan2S(spC8, sqrtf(SQ(spCC) + SQ(spC4)));
        Math_ApproachS(&this->actor.world.rot.y, temp_s0, 0x14, this->unk_0164);
        Math_ApproachS(&this->actor.shape.rot.x, temp_s2, 0x14, this->unk_0164);
        Math_ApproachS(&this->unk_0198, this->unk_019A, 1, 0x20);
        this->unk_0196 += this->unk_0198;
        Math_ApproachF(&this->unk_019C, this->unk_01A0, 0.1f, 100.0f);
        this->unk_01A4 = Math_SinS(this->unk_0196) * this->unk_019C;
        this->actor.world.rot.x = this->actor.shape.rot.x + this->unk_01A4;

        if (!(this->unk_014C & 0x1F) && (D_809E042C->unk_1D20 == 0)) {
            this->unk_01A0 = Rand_ZeroFloat(0x1000) + 0x800;
            this->unk_019A = Rand_ZeroFloat(0x400) + 0x200;
        }

        if (this->unk_0195 != 0) {
            Math_ApproachF(&this->unk_0164, this->unk_0168 * 1.25f, 1.0f, 62.5f);
        } else {
            Math_ApproachF(&this->unk_0164, this->unk_0168, 1.0f, 50.0f);
        }

        this->unk_0168 = 2000.0f;
        if (this->unk_0195 != 0) {
            this->actor.speedXZ = this->unk_01A8 * D_809DF5B0 * 1.25f;
            this->skelAnime.playSpeed = 2.0f;
        } else {
            this->actor.speedXZ = this->unk_01A8 * D_809DF5B0;
        }

        Actor_UpdateVelocityWithoutGravity(&this->actor);
        Actor_UpdatePos(&this->actor);

        spD0 = this->actor.world.pos;
        if (D_809E0422 != 0) {
            spD0.y = 5000.0f;
        } else {
            spD0.y = 2000.0f;
        }

        temp_f0 = BgCheck_EntityRaycastFloor1(&globalCtx->colCtx, &spDC, &spD0);
        if (((this->unk_017C.y < temp_f0) && (temp_f0 <= this->unk_0188.y)) ||
            ((temp_f0 < this->unk_017C.y) && (this->unk_0188.y <= temp_f0))) {
            this->unk_0170 = this->unk_017C;
            this->unk_0170.y = temp_f0;
            this->unk_016C = 120;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_INBOSS_ROAR_OLD);
        }

        this->actor.flags &= ~ACTOR_FLAG_1;
        if (this->unk_0195 != 0) {
            this->actor.world.rot.z = Math_SinS(this->unk_014C * 0x1200) * 0xE00;
        } else {
            this->actor.world.rot.z = Math_SinS(this->unk_014C * 0xC00) * 0xE00;
        }

        this->unk_014E++;
        if (this->unk_014E >= ARRAY_COUNT(this->unk_01BC)) {
            this->unk_014E = 0;
        }

        this->unk_01BC[this->unk_014E].x = this->actor.world.pos.x;
        this->unk_01BC[this->unk_014E].y = this->actor.world.pos.y;
        this->unk_01BC[this->unk_014E].z = this->actor.world.pos.z;

        this->unk_0B1C[this->unk_014E].x = BINANG_TO_RAD(this->actor.world.rot.x);
        this->unk_0B1C[this->unk_014E].y = BINANG_TO_RAD(this->actor.world.rot.y);
        this->unk_0B1C[this->unk_014E].z = BINANG_TO_RAD(this->actor.world.rot.z);
    }

    if ((this->unk_0144 < 10) && (spB0->unk_0144 >= 20)) {
        this->unk_01B0.y = -1000.0f * D_809DF5B0;
        if (D_809E0422 != 0) {
            this->unk_01B0.y += 3150.0f;
        }
        this->unk_0144 = 3;
        this->unk_0146[0] = 50;
    }

    switch (this->unk_0144) {
        default:
            return;

        case 0:
            if ((this->actor.params == 0) && (Rand_ZeroOne() < 0.75f)) {
                this->actor.world.pos.x = player->actor.world.pos.x;
                this->actor.world.pos.z = player->actor.world.pos.z;
                this->actor.world.pos.y = player->actor.world.pos.y - (600.0f * D_809DF5B0);
            } else {
                this->actor.world.pos.x = randPlusMinusPoint5Scaled(5000.0f * D_809DF5B0);
                this->actor.world.pos.z = randPlusMinusPoint5Scaled(5000.0f * D_809DF5B0);
                this->actor.world.pos.y = -500.0f * D_809DF5B0;
                if (D_809E0422 != 0) {
                    this->actor.world.pos.y += 3150.0f;
                }
            }

            if ((fabsf(this->actor.world.pos.x) < (500.0f * D_809DF5B0)) &&
                (fabsf(this->actor.world.pos.z) < (500.0f * D_809DF5B0))) {
                return;
            }

        case 100:
            this->actor.shape.rot.x = 0x4000;
            this->unk_01B0.x = this->actor.world.pos.x;
            this->unk_01B0.y = this->actor.world.pos.y + (1000.0f * D_809DF5B0);
            this->unk_01B0.z = this->actor.world.pos.z;
            this->unk_0146[0] = 100;
            this->unk_0144 = 1;

        case 1:
            if (this->unk_0146[0] == 0) {
                if (Rand_ZeroOne() < 0.3f) {
                    this->unk_0144 = 5;
                    this->unk_0146[0] = 150;
                } else {
                    this->unk_0144 = 2;
                    this->unk_01B0.x = randPlusMinusPoint5Scaled(3000.0f * D_809DF5B0);
                    this->unk_01B0.z = randPlusMinusPoint5Scaled(3000.0f * D_809DF5B0);
                    if ((fabsf(this->unk_01B0.x) < (500.0f * D_809DF5B0)) &&
                        (fabsf(this->unk_01B0.z) < (500.0f * D_809DF5B0))) {
                        this->unk_01B0.x = 500.0f;
                        this->unk_01B0.z = 500.0f;
                    }
                    this->unk_01B0.y = Rand_ZeroFloat(800.0f * D_809DF5B0) + (200.0f * D_809DF5B0);
                    if (D_809E0422 != 0) {
                        this->unk_01B0.y += 3150.0f;
                    }
                }
                this->unk_0164 = 0.0f;
            }
            return;

        case 2:
            if (this->unk_0195 != 0) {
                phi_f2 = 700.0f;
            } else {
                phi_f2 = 500.0f;
            }
            if (sqrtf(SQ(spCC) + SQ(spC8) + SQ(spC4)) < (phi_f2 * D_809DF5B0)) {
                this->unk_0144 = 3;
                this->unk_01B0.y = -3000.0f * D_809DF5B0;
                if (D_809E0422 != 0) {
                    this->unk_01B0.y += 3150.0f;
                }
                this->unk_0146[0] = 150;
                this->unk_0164 = 0.0f;
            }
            return;

        case 3:
            if (this->unk_0146[0] == 0) {
                this->unk_0144 = 0;
            }
            return;

        case 5:
            this->unk_01B0.x = player->actor.world.pos.x;
            this->unk_01B0.y = player->actor.world.pos.y + (100.0f * D_809DF5B0);
            this->unk_01B0.z = player->actor.world.pos.z;
            if (this->unk_0146[0] == 0) {
                this->unk_0144 = 3;
                this->unk_01B0.x = randPlusMinusPoint5Scaled(500.0f * D_809DF5B0) + this->actor.world.pos.x;
                this->unk_01B0.y = -3000.0f * D_809DF5B0;
                if (D_809E0422 != 0) {
                    this->unk_01B0.y += 3150.0f;
                }
                this->unk_01B0.z = randPlusMinusPoint5Scaled(500.0f * D_809DF5B0) + this->actor.world.pos.z;
                this->unk_0146[0] = 150;
                this->unk_0164 = 0.0f;
            }
            return;

        case 10:
            if (this->unk_1678 != 0) {
                this->unk_019A = 0x500;
                this->unk_01A0 = 0x1200;
            } else {
                this->colliderCylinder.dim.radius = 150.0f * D_809DF5B0;
                this->colliderCylinder.dim.height = 200.0f * D_809DF5B0;
                this->colliderCylinder.dim.yShift = 0;
                Collider_UpdateCylinder(&this->actor, &this->colliderCylinder);
                CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderCylinder.base);
                CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliderCylinder.base);
            }
            return;

        case 11:
            if (this == D_809E0424) {
                this->unk_01B0.x = D_809DF9C0[this->unk_1D1A].x;
                this->unk_01B0.y = D_809DF9C0[this->unk_1D1A].y;
                this->unk_01B0.z = D_809DF9C0[this->unk_1D1A].z;
            } else {
                this->unk_01B0.x = D_809DFA2C[this->unk_1D1A].x;
                this->unk_01B0.y = D_809DFA2C[this->unk_1D1A].y;
                this->unk_01B0.z = D_809DFA2C[this->unk_1D1A].z;
            }
            this->actor.shape.rot.x = 0x4000;
            this->unk_0144 = 12;
            this->actor.world.pos.x = this->unk_01B0.x;
            this->actor.world.pos.y = -200.0f;
            this->actor.world.pos.z = this->unk_01B0.z;
            this->unk_01A8 = 25.0f;
            return;

        case 12:
            if (sqrtf(SQ(spCC) + SQ(spC8) + SQ(spC4)) < 500.0f) {
                this->unk_1D1A++;
                this->unk_0164 = 0.0f;
                if (this->unk_1D1A > 8) {
                    this->unk_1D1A = 8;
                }
                if (this == D_809E0424) {
                    this->unk_01B0.x = D_809DF9C0[this->unk_1D1A].x;
                    this->unk_01B0.y = D_809DF9C0[this->unk_1D1A].y;
                    this->unk_01B0.z = D_809DF9C0[this->unk_1D1A].z;
                } else {
                    this->unk_01B0.x = D_809DFA2C[this->unk_1D1A].x;
                    this->unk_01B0.y = D_809DFA2C[this->unk_1D1A].y;
                    this->unk_01B0.z = D_809DFA2C[this->unk_1D1A].z;
                }
            }
            return;

        case 20:
            this->unk_0152 = 15;
            if ((s16)(BREG(71) + 140) < this->unk_0146[1]) {
                if (this->unk_0146[0] == 0) {
                    Matrix_RotateY(Math_Atan2S(-player->actor.world.pos.x, -player->actor.world.pos.z), MTXMODE_NEW);
                    Matrix_GetStateTranslationAndScaledZ(1500.0f * D_809DF5B0, &spA4);
                    this->unk_0146[0] = 50;
                    this->unk_01B0.x = player->actor.world.pos.x + spA4.x;
                    this->unk_01B0.y = randPlusMinusPoint5Scaled(500.0f * D_809DF5B0) + (600.0f * D_809DF5B0);
                    if (D_809E0422 != 0) {
                        this->unk_01B0.y += 3150.0f;
                    }
                    this->unk_01B0.z = player->actor.world.pos.z + spA4.z;
                }
                this->unk_0168 = 3000.0f;
            } else {
                this->unk_01B0.y += 10.0f * D_809DF5B0;
                this->unk_0168 = 5000.0f;
            }
            this->unk_019A = 0x1000;
            this->unk_01A8 = 25.0f;
            this->unk_01A0 = 0x1800;
            if (this->unk_0146[1] == 0) {
                this->unk_015C = 1;
                this->unk_0144 = 21;
                this->unk_0146[0] = 20;
                this->unk_0152 = 0;
                D_809E042C->unk_1D20 = 102;
                D_809E042C->unk_1D5C = 0.0f;
                play_sound(NA_SE_EN_INBOSS_DEAD_PRE2_OLD);
            } else if (!(this->unk_0146[1] & 0xF) && (Rand_ZeroOne() < 0.5f)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_INBOSS_DAMAGE_OLD);
            }
            return;

        case 21:
            this->unk_01A8 = 0.0f;
            this->actor.speedXZ = 0.0f;
            if (this->unk_0146[0] == 0) {
                this->unk_0146[0] = 3;

                for (i = 0; i < 35; i++) {
                    func_809DA344(globalCtx->specialEffects, &this->unk_147C[this->unk_1678]);
                }

                func_809DA460(globalCtx->specialEffects, &this->unk_147C[this->unk_1678]);
                play_sound(NA_SE_EV_EXPLOSION);

                this->unk_1678--;
                if (this->unk_1678 <= 0) {
                    this->unk_0144 = 22;
                    this->actor.gravity = -1.0f * D_809DF5B0;
                    this->actor.velocity.y = 0.0f;
                    this->actor.terminalVelocity = -1000.0f * D_809DF5B0;
                    this->unk_0164 = randPlusMinusPoint5Scaled(0.05f);

                    spCC = player->actor.world.pos.x - this->actor.world.pos.x;
                    spC4 = player->actor.world.pos.z - this->actor.world.pos.z;
                    if (sqrtf(SQ(spCC) + SQ(spC4)) < (400.0f * D_809DF5B0)) {
                        this->actor.speedXZ = 15.0f * D_809DF5B0;
                    }

                    spCC = this->actor.world.pos.x;
                    spC4 = this->actor.world.pos.z;
                    if (sqrtf(SQ(spCC) + SQ(spC4)) < (400.0f * D_809DF5B0)) {
                        this->actor.speedXZ = 15.0f * D_809DF5B0;
                    }

                    if (spB0->unk_0144 >= 10) {
                        Audio_QueueSeqCmd(NA_BGM_CLEAR_BOSS | 0x8000);
                    }

                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_INBOSS_DEAD_OLD);
                }
            }
            return;

        case 22:
            i = (this->unk_014E + 196) % ARRAY_COUNT(this->unk_01BC);

            Math_Vec3f_Copy(&this->unk_01BC[i], &this->actor.world.pos);
            this->unk_0B1C[i].y += this->unk_0164;
            Math_ApproachF(&this->unk_0B1C[i].x, -(M_PI / 2), 0.1f, 0.07f);
            Actor_MoveWithGravity(&this->actor);
            Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 50.0f, 150.0f, 100.0f, 4);

            if (this->actor.bgCheckFlags & 1) {
                this->unk_0144 = 23;
                this->actor.speedXZ = 0.0f;
                this->unk_0170 = this->unk_017C;
                this->unk_016C = 30;
                this->unk_0170.y = this->actor.floorHeight;
                D_809E042C->unk_1D20 = 103;
                D_809E042C->unk_1D1C = 0;
                D_809E042C->unk_0146[0] = 15;
                D_809E042C->unk_0150 = 0;
                play_sound(NA_SE_EV_LIGHTNING);

                for (i = 0; i < 30; i++) {
                    func_809DA344(globalCtx->specialEffects, &this->unk_0170);
                }

                this->unk_0146[0] = 10;
            }
            break;

        case 23:
            i = (this->unk_014E + 196) % ARRAY_COUNT(this->unk_01BC);
            Math_Vec3f_Copy(&this->unk_01BC[i], &this->actor.world.pos);
            Math_ApproachF(&this->unk_0B1C[i].x, -(M_PI / 2), 0.05f, 0.07f);

            if (this->unk_0146[0] & 1) {
                sp9C = Rand_ZeroFloat(M_PI);

                for (i = 0; i < 15; i++) {
                    Matrix_InsertYRotation_f(((2.0f * (i * M_PI)) / 15.0f) + sp9C, MTXMODE_NEW);
                    Matrix_GetStateTranslationAndScaledZ((10 - this->unk_0146[0]) * (D_809DF5B0 * 300.0f) * 0.1f,
                                                         &sp90);
                    spD0.x = this->unk_0170.x + sp90.x;
                    spD0.y = this->unk_0170.y + (1000.0f * D_809DF5B0);
                    spD0.z = this->unk_0170.z + sp90.z;
                    if (BgCheck_EntityRaycastFloor3(&globalCtx->colCtx, &sp8C, &sp88, &spD0) != BGCHECK_Y_MIN) {
                        spA0 = BgCheck_EntityRaycastFloor1(&globalCtx->colCtx, &sp8C, &spD0);
                        Matrix_GetStateTranslationAndScaledZ(5.0f * D_809DF5B0, &sp70);
                        sp70.y = 2.0f * D_809DF5B0;
                        sp64.y = 0.3f * D_809DF5B0;
                        sp64.z = 0.0f;
                        sp64.x = 0.0f;
                        sp7C.x = spD0.x;
                        sp7C.y = spA0;
                        sp7C.z = spD0.z;
                        func_800B0F18(globalCtx, &sp7C, &sp70, &sp64, &D_809DFA98, &D_809DFA98,
                                      (Rand_ZeroFloat(500.0f) + 1200.0f) * D_809DF5B0, 20.0f * D_809DF5B0,
                                      Rand_ZeroFloat(5.0f) + 14.0f);
                    }
                }
            }
    }

    this->colliderCylinder.dim.radius = 150.0f * D_809DF5B0;
    this->colliderCylinder.dim.height = 200.0f * D_809DF5B0;
    this->colliderCylinder.dim.yShift = 0;
    Collider_UpdateCylinder(&this->actor, &this->colliderCylinder);
    CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->colliderCylinder.base);
}

void func_809DBFB4(Boss02* this, GlobalContext* globalCtx) {
    Boss02* temp_s6 = this->unk_1674;
    s32 temp;
    s32 i;
    u8 damage;

    if (this->unk_0154 == 0) {
        if (D_809E0422 != 0) {
            temp = 0;
        } else {
            temp = 1;
        }

        for (i = temp; i < ARRAY_COUNT(this->colliderSphere2Elements); i++) {
            if (this->colliderSphere2.elements[i].info.bumperFlags & BUMP_HIT) {
                this->colliderSphere2.elements[i].info.bumperFlags &= ~BUMP_HIT;
                this->unk_0154 = 15;
                this->unk_0156 = 15;

                if (i == 0) {
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_INBOSS_DAMAGE_OLD);
                    this->unk_015C = 1;
                } else {
                    Audio_PlaySfxAtPos(&this->unk_167C, NA_SE_EN_INBOSS_DAMAGE_OLD);
                    this->unk_015C = 10;
                }

                if (D_809E0422 != 0) {
                    this->unk_0152 = 15;
                } else {
                    this->unk_0152 = 12;
                }

                damage = this->actor.colChkInfo.damage;

                if (temp_s6->unk_0144 < 20) {
                    do {
                        do {
                            this->actor.colChkInfo.health -= damage;
                        } while (0);
                    } while (0);

                    if ((s8)this->actor.colChkInfo.health <= 0) {
                        Actor_MarkForDeath(this->actor.child);
                        this->actor.child = NULL;
                        Enemy_StartFinishingBlow(globalCtx, &this->actor);
                        this->skelAnime.playSpeed = 2.0f;
                        this->unk_0144 = 20;

                        if (temp_s6->unk_0144 >= 10) {
                            Audio_QueueSeqCmd(0x100100FF);
                        } else {
                            temp_s6->unk_0195 = 1;
                        }

                        this->unk_0146[1] = BREG(70) + 170;
                        this->unk_0146[0] = 0;
                        this->actor.shape.rot.x = 0x4000;

                        if (D_809E0422 == 0) {
                            if (this->actor.world.pos.y < -200.0f) {
                                this->actor.world.pos.y = -200.0f;
                            }
                        } else if (this->actor.world.pos.y < 3130.0f) {
                            this->actor.world.pos.y = 3130.0f;
                        }

                        D_809E042C->unk_1D20 = 100;

                        if (this == D_809E0424) {
                            D_809E042C->unk_0194 = 0;
                        } else {
                            D_809E042C->unk_0194 = 1;
                        }
                    }
                }
            }
        }
    }
}

void func_809DC218(Actor* thisx, GlobalContext* globalCtx) {
    Boss02* this = THIS;
    s32 pad;
    Vec3f sp24;
    CollisionPoly* sp20;

    this->unk_014C++;
    if ((this->unk_014C + this->actor.params) & 1) {
        sp24 = this->actor.world.pos;
        this->actor.focus.pos = this->actor.world.pos;
        if (D_809E0422 != 0) {
            sp24.y = 5000.0f;
        } else {
            sp24.y = 2000.0f;
        }

        if ((this->actor.focus.pos.y < BgCheck_EntityRaycastFloor1(&globalCtx->colCtx, &sp20, &sp24)) ||
            (D_809E0422 != 0)) {
            this->actor.flags &= ~ACTOR_FLAG_1;
        } else {
            this->actor.flags |= ACTOR_FLAG_1;
        }
    }
}

void Boss02_Update(Actor* thisx, GlobalContext* globalCtx) {
    Vec3f sp3C;
    Boss02* this = THIS;
    s32 pad;
    s16 i;

    if (D_809E0422 == 0) {
        Actor_SetScale(&this->actor, 0.6f);
    } else {
        Actor_SetScale(&this->actor, 0.060000001f);
    }

    if (D_809E042C->unk_1D18 == 0) {
        for (i = 0; i < ARRAY_COUNT(this->unk_0146); i++) {
            if (this->unk_0146[i] != 0) {
                this->unk_0146[i]--;
            }
        }

        if (this->unk_016C != 0) {
            this->unk_016C--;
        }

        if (this->unk_0154 != 0) {
            this->unk_0154--;
        }

        if (this->unk_0156 != 0) {
            this->unk_0156--;
        }

        if (this->unk_0152 != 0) {
            this->unk_0152--;
        }

        this->unk_014C++;

        this->actionFunc(this, globalCtx);

        if (this->unk_016C != 0) {
            if ((this->unk_016C == 60) && (this->unk_0144 < 20)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_INBOSS_ROAR_OLD);
            }
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_INBOSS_SAND_OLD - SFX_FLAG);

            if (this->unk_0144 > 20) {
                sp3C.x = randPlusMinusPoint5Scaled(100.0f * D_809DF5B0) + this->unk_0170.x;
                sp3C.y = randPlusMinusPoint5Scaled(50.0f * D_809DF5B0) + this->unk_0170.y;
                sp3C.z = randPlusMinusPoint5Scaled(100.0f * D_809DF5B0) + this->unk_0170.z;
                func_809DA264(globalCtx->specialEffects, &sp3C, Rand_ZeroFloat(3.0f) + 6.0f);
            }

            if ((this->unk_014C % 2) == 0) {
                sp3C.x = randPlusMinusPoint5Scaled(100.0f * D_809DF5B0) + this->unk_0170.x;
                sp3C.y = randPlusMinusPoint5Scaled(50.0f * D_809DF5B0) + this->unk_0170.y;
                sp3C.z = randPlusMinusPoint5Scaled(100.0f * D_809DF5B0) + this->unk_0170.z;
                func_809DA264(globalCtx->specialEffects, &sp3C, Rand_ZeroFloat(3.0f) + 6.0f);
            }
        }

        if ((this->unk_0144 < 20) && (this->unk_0144 != 10)) {
            func_809DBFB4(this, globalCtx);
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliderSphere1.base);
            CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->colliderSphere1.base);
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderSphere1.base);
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliderSphere2.base);
            CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->colliderSphere2.base);
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderSphere2.base);
        }

        switch (this->unk_015C) {
            case 1:
                this->unk_015A = 0;
                this->unk_0158 = this->unk_015A;
                this->unk_015C++;

            case 2:
                this->unk_015A += 2;
                if (this->unk_015A > 20) {
                    this->unk_015C++;
                }
                this->unk_0156 |= 4;
                break;

            case 3:
                this->unk_0158 += 2;
                if (this->unk_0158 > 20) {
                    this->unk_015C = 0;
                }
                this->unk_0156 |= 4;
                break;

            case 10:
                this->unk_015A = 21;
                this->unk_0158 = this->unk_015A;
                this->unk_015C++;

            case 11:
                this->unk_0158 -= 2;
                if (this->unk_0158 <= 0) {
                    this->unk_0158 = 0;
                    this->unk_015C++;
                }
                this->unk_0156 |= 4;
                break;

            case 12:
                this->unk_015A -= 2;
                if (this->unk_015A <= 0) {
                    this->unk_015A = 0;
                    this->unk_015C = 0;
                }
                this->unk_0156 |= 4;
                break;
        }
    }
}

void func_809DC78C(Actor* thisx, GlobalContext* globalCtx) {
    Boss02* this = THIS;

    this->unk_01AC = D_809DF5B0;
    globalCtx->envCtx.sandstormState = 0xD;

    if (D_809E0434 != NULL) {
        this->unk_1D74 = KREG(23) + -15.0f;
        D_801F4E30 = 0;
        globalCtx->envCtx.lightSettingOverride = 1;
        globalCtx->skyboxId = 1;
    } else if (D_809E0422 == 0) {
        this->unk_1D74 = 0.0f;
        D_801F4E30 = this->unk_1D7C;
        globalCtx->envCtx.lightSettingOverride = 0;
        globalCtx->skyboxId = 2;
    } else {
        this->unk_1D74 = KREG(23) + -15.0f;
        D_801F4E30 = ((KREG(24) * 0.1f) + 1.0f) * this->unk_1D7C;
        globalCtx->envCtx.lightSettingOverride = 1;
        globalCtx->skyboxId = 1;
    }

    Math_ApproachS(&this->unk_1D7C, this->unk_1D7E, 1, 3);

    if (this->unk_0146[0] != 0) {
        this->unk_0146[0]--;
    }

    if (D_809E0434 == NULL) {
        if (D_809E0430 != 0) {
            D_809E0430--;
            if (D_809E0430 == 0) {
                Audio_QueueSeqCmd(NA_BGM_BOSS | 0x8000);
            }
        }
    }

    func_809DD0CC(globalCtx);
    func_809DEAC4(this, globalCtx);
    func_809DD934(this, globalCtx);
}

void Boss02_Draw(Actor* thisx, GlobalContext* globalCtx2) {
    static Gfx* D_809DFA9C[] = {
        object_boss02_DL_00ECF0, object_boss02_DL_00EF90, object_boss02_DL_00F310, object_boss02_DL_00F690,
        object_boss02_DL_00FA10, object_boss02_DL_00FD90, object_boss02_DL_010110, object_boss02_DL_010490,
        object_boss02_DL_010810, object_boss02_DL_010B90, object_boss02_DL_010F10, object_boss02_DL_011290,
        object_boss02_DL_011610, object_boss02_DL_011990, object_boss02_DL_011D10, object_boss02_DL_012090,
        object_boss02_DL_012410, object_boss02_DL_012790, object_boss02_DL_012B10, object_boss02_DL_012E90,
        object_boss02_DL_013210, object_boss02_DL_013590,
    };
    static Vec3f D_809DFAF4 = { -10000.0f, -100000.0f, -100000.0f };
    GlobalContext* globalCtx = globalCtx2;
    Boss02* this = THIS;
    s32 i;
    s32 idx;
    Mtx* mtx;
    Mtx* mtxIter;
    s32 phi_v0;
    f32 phi_f12;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    f32 spA0;
    f32 sp9C;
    f32 sp98;

    mtxIter = mtx = GRAPH_ALLOC(globalCtx->state.gfxCtx, sizeof(Mtx) * 23);

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    if (this->actor.params == 0) {
        gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(object_boss02_Tex_0003A0));
    } else {
        gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(object_boss02_Tex_0041A0));
    }

    gSPSegment(POLY_OPA_DISP++, 0x0D, mtx);

    if (D_809E0422 == 0) {
        sp98 = -500.0f;
    } else {
        sp98 = 3100.0f;
    }

    sp9C = this->unk_0152 * (M_PI / 4) * (1.0f / 15);
    if (this->unk_0144 < 20) {
        spAC = Math_SinS(this->unk_014C * 0x2200) * sp9C * 0.5f;
        spA8 = Math_CosS(this->unk_014C * 0x3200) * sp9C;
    } else {
        spAC = Math_SinS(this->unk_014C * 0x1000) * sp9C * 0.5f;
        spA8 = Math_CosS(this->unk_014C * 0x1500) * sp9C;
    }

    idx = (this->unk_014E + 196) % ARRAY_COUNT(this->unk_01BC);
    Matrix_InsertTranslation(this->unk_01BC[idx].x, this->unk_01BC[idx].y, this->unk_01BC[idx].z, MTXMODE_NEW);
    Matrix_InsertYRotation_f(this->unk_0B1C[idx].y + spA8, MTXMODE_APPLY);
    Matrix_RotateStateAroundXAxis(spAC - this->unk_0B1C[idx].x);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
    Matrix_InsertTranslation(0.0f, 0.0f, 250.0f, MTXMODE_APPLY);
    Matrix_GetStateTranslationAndScaledZ(150.0f, &this->unk_147C[0]);
    this->unk_0188 = this->unk_017C;
    Matrix_GetStateTranslationAndScaledZ(300.0f, &this->unk_017C);
    Math_Vec3f_Copy(&this->actor.focus.pos, &this->unk_017C);

    if ((this->unk_0156 & 1) && (this->unk_0158 == 0)) {
        POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 255, 0x384, 0x44B);
    }

    SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, NULL, NULL, &this->actor);
    POLY_OPA_DISP = func_801660B8(globalCtx, POLY_OPA_DISP);

    spA4 = 0.0f;
    spA0 = 0.0f;
    for (i = 0; i < ARRAY_COUNT(D_809DFA9C); i++, mtxIter++) {
        if (this->unk_0195 != 0) {
            phi_v0 = (D_809DF5E4[i + 1] + this->unk_014E) % ARRAY_COUNT(this->unk_01BC);
        } else {
            phi_v0 = (D_809DF5B4[i + 1] + this->unk_014E) % ARRAY_COUNT(this->unk_01BC);
        }

        if ((i == 21) && (this->unk_0144 < 20)) {
            spA4 = spAC;
            spA0 = spA8;
        }

        Matrix_InsertTranslation(this->unk_01BC[phi_v0].x, this->unk_01BC[phi_v0].y, this->unk_01BC[phi_v0].z,
                                 MTXMODE_NEW);
        Matrix_InsertYRotation_f(this->unk_0B1C[phi_v0].y + spA0, MTXMODE_APPLY);
        Matrix_RotateStateAroundXAxis(spA4 - this->unk_0B1C[phi_v0].x);
        Matrix_InsertZRotation_f(this->unk_0B1C[phi_v0].z, MTXMODE_APPLY);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_InsertYRotation_f(M_PI / 2, MTXMODE_APPLY);
        Matrix_RotateStateAroundXAxis(-(M_PI / 2));
        Matrix_ToMtx(mtxIter);

        gSPMatrix(POLY_OPA_DISP++, mtxIter, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        if ((this->unk_0156 & 1) && (i >= this->unk_0158) && (this->unk_015A >= i)) {
            POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 255, 0x384, 0x44B);
        }

        if (i < this->unk_1678) {
            if (sp98 < this->unk_01BC[phi_v0].y) {
                gSPDisplayList(POLY_OPA_DISP++, D_809DFA9C[i]);
            }
            POLY_OPA_DISP = func_801660B8(globalCtx, POLY_OPA_DISP);
        }

        if (i == 21) {
            phi_f12 = 600.0f;
        } else {
            phi_f12 = 200.0f;
        }

        Matrix_GetStateTranslationAndScaledX(phi_f12, &this->unk_147C[i + 1]);

        if (i == 21) {
            Actor* child = this->actor.child;

            if (child != NULL) {
                Matrix_GetStateTranslationAndScaledX(500.0f, &this->actor.child->world.pos);
            }

            func_809DA50C(1, &this->colliderSphere2, &this->unk_147C[i + 1]);
            SkinMatrix_Vec3fMtxFMultXYZW(&globalCtx->viewProjectionMtxF, &this->unk_147C[i + 1], &this->unk_167C,
                                         &this->actor.projectedW);
        } else {
            func_809DA50C(i, &this->colliderSphere1, &this->unk_147C[i + 1]);
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);

    if (D_809E0422 == 0) {
        func_809DA50C(0, &this->colliderSphere2, &D_809DFAF4);
        func_809DA50C(21, &this->colliderSphere1, &this->unk_147C[0]);
    } else {
        func_809DA50C(0, &this->colliderSphere2, &this->unk_147C[0]);
        func_809DA50C(21, &this->colliderSphere1, &D_809DFAF4);
    }
}

void func_809DD0A8(Actor* thisx, GlobalContext* globalCtx) {
    func_809DD2F8(globalCtx);
}

void func_809DD0CC(GlobalContext* globalCtx) {
    Boss02Effects* effect = (Boss02Effects*)globalCtx->specialEffects;
    f32 phi_f22;
    s16 i;

    if (D_809E0422 == 0) {
        phi_f22 = 0.0f;
    } else {
        phi_f22 = 3150.0f;
    }

    for (i = 0; i < ARRAY_COUNT(D_809E0438); i++, effect++) {
        if (effect->unk_24) {
            effect->unk_26++;
            effect->unk_00.x += effect->unk_0C.x * D_809DF5B0;
            effect->unk_00.y += effect->unk_0C.y * D_809DF5B0;
            effect->unk_00.z += effect->unk_0C.z * D_809DF5B0;
            effect->unk_0C.y += effect->unk_18.y;

            if (effect->unk_24 < 3) {
                Math_ApproachF(&effect->unk_34, effect->unk_38, 0.1f, 0.1f);
                if (effect->unk_24 == 2) {
                    effect->unk_2C -= 18;
                } else {
                    effect->unk_2C -= 15;
                }
                if (effect->unk_2C <= 0) {
                    effect->unk_24 = 0;
                }
            } else if (effect->unk_24 == 3) {
                effect->unk_2E += 0x1000;
                effect->unk_30 += 0x1500;
                if ((effect->unk_00.y < phi_f22) || (effect->unk_26 > 50)) {
                    effect->unk_24 = 0;
                }
            } else if (effect->unk_24 == 4) {
                Math_ApproachF(&effect->unk_34, 80.0f, 0.2f, 20.0f);
                effect->unk_2C -= 15;
                if (effect->unk_2C <= 0) {
                    effect->unk_24 = 0;
                }
            }
        }
    }
}

void func_809DD2F8(GlobalContext* globalCtx) {
    u8 flag = false;
    Boss02Effects* effect = (Boss02Effects*)globalCtx->specialEffects;
    s16 i;
    u8 phi_a0;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);

    for (i = 0; i < ARRAY_COUNT(D_809E0438); i++, effect++) {
        if (effect->unk_24 == 1) {
            if (!flag) {
                gSPDisplayList(POLY_XLU_DISP++, object_boss02_DL_000230);
                gDPSetEnvColor(POLY_XLU_DISP++, 185, 140, 70, 128);
                flag++;
            }

            phi_a0 = effect->unk_2C;
            if (effect->unk_2C > 255) {
                phi_a0 = 255;
            }

            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 185, 140, 70, phi_a0);
            gSPSegment(POLY_XLU_DISP++, 0x08,
                       Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, effect->unk_26 + (i * 3),
                                        (effect->unk_26 + (i * 3)) * 5, 32, 64, 1, 0, 0, 32, 32));

            Matrix_InsertTranslation(effect->unk_00.x, effect->unk_00.y, effect->unk_00.z, MTXMODE_NEW);
            Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);
            Matrix_Scale(effect->unk_34 * D_809DF5B0, effect->unk_34 * D_809DF5B0, 1.0f, MTXMODE_APPLY);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, object_boss02_DL_0002E0);
        }
    }

    effect = (Boss02Effects*)globalCtx->specialEffects;
    for (i = 0, flag = false; i < ARRAY_COUNT(D_809E0438); i++, effect++) {
        if (effect->unk_24 == 3) {
            if (!flag) {
                gDPSetCombineLERP(POLY_OPA_DISP++, SHADE, 0, PRIMITIVE, 0, SHADE, 0, PRIMITIVE, 0, SHADE, 0, PRIMITIVE,
                                  0, SHADE, 0, PRIMITIVE, 0);
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0x01, 100, 100, 120, 255);
                flag++;
            }
            Matrix_InsertTranslation(effect->unk_00.x, effect->unk_00.y, effect->unk_00.z, MTXMODE_NEW);
            Matrix_RotateY(effect->unk_30, MTXMODE_APPLY);
            Matrix_InsertXRotation_s(effect->unk_2E, MTXMODE_APPLY);
            Matrix_Scale(effect->unk_34 * D_809DF5B0, effect->unk_34 * D_809DF5B0, effect->unk_34 * D_809DF5B0,
                         MTXMODE_APPLY);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, gameplay_keep_DL_01A620);
        }
    }

    effect = (Boss02Effects*)globalCtx->specialEffects;
    for (i = 0, flag = false; i < ARRAY_COUNT(D_809E0438); i++, effect++) {
        if (effect->unk_24 == 4) {
            if (!flag) { //! @bug - dev forgot to set flag to 1, should only apply to first entry?
                gSPDisplayList(POLY_XLU_DISP++, gLightOrb1DL);
                gDPSetEnvColor(POLY_XLU_DISP++, 255, 0, 0, 128);
            }

            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 200, (u8)effect->unk_2C);

            Matrix_InsertTranslation(effect->unk_00.x, effect->unk_00.y, effect->unk_00.z, MTXMODE_NEW);
            Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);
            Matrix_Scale(effect->unk_34 * D_809DF5B0, effect->unk_34 * D_809DF5B0, 1.0f, MTXMODE_APPLY);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, gLightOrbVtxDL);
        }
    }

    effect = (Boss02Effects*)globalCtx->specialEffects;
    for (i = 0, flag = false; i < ARRAY_COUNT(D_809E0438); i++, effect++) {
        if (effect->unk_24 == 2) {
            if (!flag) {
                gSPDisplayList(POLY_XLU_DISP++, object_boss02_DL_000230);
                gDPSetEnvColor(POLY_XLU_DISP++, 30, 30, 30, 128);
                flag++;
            }

            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 30, 30, 30, (u8)effect->unk_2C);
            gSPSegment(POLY_XLU_DISP++, 0x08,
                       Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, effect->unk_26 + (i * 3),
                                        (effect->unk_26 + (i * 3)) * 5, 32, 64, 1, 0, 0, 32, 32));

            Matrix_InsertTranslation(effect->unk_00.x, effect->unk_00.y, effect->unk_00.z, MTXMODE_NEW);
            Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);
            Matrix_Scale(effect->unk_34 * D_809DF5B0, effect->unk_34 * D_809DF5B0, 1.0f, MTXMODE_APPLY);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, object_boss02_DL_0002E0);
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_809DD934(Boss02* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 i;
    Actor* temp_a0_5;
    Vec3f sp58;
    u8 sp57 = 0;
    f32 phi_f0_2;
    s16 phi_v1;

    this->unk_1D14++;

    switch (this->unk_1D18) {
        case 0:
            if (player->stateFlags1 & 0x100) {
                Cutscene_Start(globalCtx, &globalCtx->csCtx);
                this->unk_1D22 = Play_CreateSubCamera(globalCtx);
                Play_CameraChangeStatus(globalCtx, CAM_ID_MAIN, 1);
                Play_CameraChangeStatus(globalCtx, this->unk_1D22, 7);
                func_8016566C(150);
                this->unk_1D14 = 0;
                this->unk_1D5C = 0.0f;
                this->unk_1D58 = 0.0f;
                if (D_809E0422 == 0) {
                    this->unk_1D18 = 1;
                    this->unk_1D68 = 10.0f;
                    this->unk_1D64 = 60.0f;
                    this->unk_1D6C = 23.0f;
                    this->unk_1D70 = 0.01f;
                    this->unk_1D74 = 0.0f;
                    goto label1;
                } else {
                    this->unk_1D18 = 10;
                    this->unk_1D68 = 10.0f;
                    this->unk_1D64 = 200.0f;
                    this->unk_1D6C = 273.0f;
                    this->unk_1D70 = 0.1f;
                    this->unk_1D74 = -100.0f;
                    sp57 = 1;
                    goto label2;
                }
            }
            break;

        case 1:
            if ((this->unk_1D14 < 80U) && (D_809E0420 != 0) &&
                CHECK_BTN_ANY(CONTROLLER1(globalCtx)->press.button,
                              BTN_A | BTN_B | BTN_CUP | BTN_CDOWN | BTN_CLEFT | BTN_CRIGHT)) {
                this->unk_1D18++;
                this->unk_1D78 = 1;
                this->unk_1D14 = 0;
            } else {
            label1:
                if (this->unk_1D14 >= 50U) {
                    if (this->unk_1D14 == (u32)(BREG(43) + 60)) {
                        play_sound(NA_SE_PL_TRANSFORM_GIANT);
                    }
                    Math_ApproachF(&this->unk_1D64, 200.0f, 0.1f, this->unk_1D5C * 640.0f);
                    Math_ApproachF(&this->unk_1D6C, 273.0f, 0.1f, this->unk_1D5C * 150.0f);
                    Math_ApproachF(&this->unk_1D70, 0.1f, 0.2f, this->unk_1D5C * 0.1f);
                    Math_ApproachF(&this->unk_1D74, -100.0f, 1.0f, this->unk_1D5C * 100.0f);
                    Math_ApproachF(&this->unk_1D5C, 1.0f, 1.0f, 0.001f);
                } else {
                    Math_ApproachF(&this->unk_1D64, 30.0f, 0.1f, 1.0f);
                }

                if (this->unk_1D14 > 50U) {
                    Math_ApproachZeroF(&this->unk_1D58, 1.0f, 0.06f);
                } else {
                    Math_ApproachF(&this->unk_1D58, 0.4f, 1.0f, 0.02f);
                }

                if (this->unk_1D14 == 107U) {
                    this->unk_1D78 = 1;
                }

                if (this->unk_1D14 < 121U) {
                    break;
                }

                sp57 = 1;
                D_809E0420 = 1;
                goto block_38;
            }
            break;

        case 2:
            if (this->unk_1D14 < 8U) {
                break;
            }
            sp57 = 1;
            goto block_38;

        case 10:
            if ((this->unk_1D14 < 30U) && (D_809E0421 != 0) &&
                CHECK_BTN_ANY(CONTROLLER1(globalCtx)->press.button,
                              BTN_A | BTN_B | BTN_CUP | BTN_CDOWN | BTN_CLEFT | BTN_CRIGHT)) {
                this->unk_1D18++;
                this->unk_1D78 = 1;
                this->unk_1D14 = 0;
                break;
            }

        label2:
            if (this->unk_1D14 != 0U) {
                if (this->unk_1D14 == (u32)(BREG(44) + 10)) {
                    play_sound(NA_SE_PL_TRANSFORM_NORAML);
                }
                Math_ApproachF(&this->unk_1D64, 60.0f, 0.1f, this->unk_1D5C * 640.0f);
                Math_ApproachF(&this->unk_1D6C, 23.0f, 0.1f, this->unk_1D5C * 150.0f);
                Math_ApproachF(&this->unk_1D70, 0.01f, 0.1f, 0.003f);
                Math_ApproachF(&this->unk_1D74, 0.0f, 1.0f, this->unk_1D5C * 100.0f);
                Math_ApproachF(&this->unk_1D5C, 2.0f, 1.0f, 0.01f);
            }

            if (this->unk_1D14 == 42U) {
                this->unk_1D78 = 1;
            }

            if (this->unk_1D14 > 50U) {
                D_809E0421 = 1;
                goto block_38;
            }
            break;

        case 11:
            if (this->unk_1D14 < 8U) {
                break;
            }

        block_38:
        case 20:
            this->unk_1D18 = 0;
            func_80169AFC(globalCtx, this->unk_1D22, 0);
            this->unk_1D22 = 0;
            Cutscene_End(globalCtx, &globalCtx->csCtx);
            this->actor.flags |= ACTOR_FLAG_1;
            player->stateFlags1 &= ~0x100;
            this->unk_1D70 = 0.01f;
            func_80165690();
            break;
    }

    if (player->transformation == PLAYER_FORM_FIERCE_DEITY) {
        Actor_SetScale(&player->actor, this->unk_1D70 * 1.5f);
    } else {
        Actor_SetScale(&player->actor, this->unk_1D70);
    }

    globalCtx->envCtx.lightSettings.fogNear = this->unk_1D74;

    if (sp57) {
        D_809E0422 = 1 - D_809E0422;
        if (D_809E0422 == 0) {
            D_809DF5B0 = 1.0f;
        } else {
            D_809DF5B0 = 0.1f;
        }

        this->unk_01AC = D_809DF5B0;
        if (D_809E0422 == 0) {
            if (D_809E0434 != NULL) {
                D_809E0434->unk_203 = 0;
                D_809E0434->unk_204 = 1.0f;
                D_809E0434->dyna.actor.world.pos.y = 60.0f;
            }

            player->actor.world.pos.x *= 10.0f;
            player->actor.world.pos.y -= 3150.0f;
            player->actor.world.pos.y *= 10.0f;
            player->unk_B68 = player->actor.world.pos.y;
            player->actor.world.pos.z *= 10.0f;

            if ((D_809E0434 != NULL) && ((SQ(player->actor.world.pos.z) + SQ(player->actor.world.pos.x)) < SQ(60.0f))) {
                player->actor.world.pos.z = 60.0f;
                player->actor.world.pos.x = 60.0f;
            }

            D_809E0424->actor.world.pos.x *= 10.0f;
            D_809E0424->actor.world.pos.y -= 3150.0f;
            D_809E0424->actor.world.pos.y *= 10.0f;
            D_809E0424->actor.world.pos.z *= 10.0f;

            D_809E0424->unk_0170.x *= 10.0f;
            D_809E0424->unk_0170.y -= 3150.0f;
            D_809E0424->unk_0170.y *= 10.0f;
            D_809E0424->unk_0170.z *= 10.0f;

            for (i = 0; i < ARRAY_COUNT(this->unk_01BC); i++) {
                D_809E0424->unk_01BC[i].x *= 10.0f;
                D_809E0424->unk_01BC[i].y -= 3150.0f;
                D_809E0424->unk_01BC[i].y *= 10.0f;
                D_809E0424->unk_01BC[i].z *= 10.0f;
            }

            D_809E0424->unk_01B0.x *= 10.0f;
            D_809E0424->unk_01B0.y -= 3150.0f;
            D_809E0424->unk_01B0.y *= 10.0f;
            D_809E0424->unk_01B0.z *= 10.0f;

            D_809E0424->unk_017C.y -= 3150.0f;
            D_809E0424->unk_017C.y *= 10.0f;
            D_809E0424->unk_0188.y -= 3150.0f;
            D_809E0424->unk_0188.y *= 10.0f;

            D_809E0428->actor.world.pos.x *= 10.0f;
            D_809E0428->actor.world.pos.y -= 3150.0f;
            D_809E0428->actor.world.pos.y *= 10.0f;
            D_809E0428->actor.world.pos.z *= 10.0f;

            D_809E0428->unk_0170.x *= 10.0f;
            D_809E0428->unk_0170.y -= 3150.0f;
            D_809E0428->unk_0170.y *= 10.0f;
            D_809E0428->unk_0170.z *= 10.0f;

            for (i = 0; i < ARRAY_COUNT(this->unk_01BC); i++) {
                D_809E0428->unk_01BC[i].x *= 10.0f;
                D_809E0428->unk_01BC[i].y -= 3150.0f;
                D_809E0428->unk_01BC[i].y *= 10.0f;
                D_809E0428->unk_01BC[i].z *= 10.0f;
            }

            D_809E0428->unk_01B0.x *= 10.0f;
            D_809E0428->unk_01B0.y -= 3150.0f;
            D_809E0428->unk_01B0.y *= 10.0f;
            D_809E0428->unk_01B0.z *= 10.0f;

            D_809E0428->unk_017C.y -= 3150.0f;
            D_809E0428->unk_017C.y *= 10.0f;
            D_809E0428->unk_0188.y -= 3150.0f;
            D_809E0428->unk_0188.y *= 10.0f;

        } else {
            if (D_809E0434 != 0) {
                D_809E0434->unk_203 = 1;
                D_809E0434->unk_204 = 0.1f;
                D_809E0434->dyna.actor.world.pos.y = 3155.0f;
            }

            player->actor.world.pos.x *= 0.1f;
            player->actor.world.pos.y *= 0.1f;
            player->actor.world.pos.y += 3150.0f;
            player->unk_B68 = player->actor.world.pos.y;
            player->actor.world.pos.z *= 0.1f;

            D_809E0424->actor.world.pos.x *= 0.1f;
            D_809E0424->actor.world.pos.y *= 0.1f;
            D_809E0424->actor.world.pos.y += 3150.0f;
            D_809E0424->actor.world.pos.z *= 0.1f;

            D_809E0424->unk_0170.x *= 0.1f;
            D_809E0424->unk_0170.y *= 0.1f;
            D_809E0424->unk_0170.y += 3150.0f;
            D_809E0424->unk_0170.z *= 0.1f;

            for (i = 0; i < ARRAY_COUNT(this->unk_01BC); i++) {
                D_809E0424->unk_01BC[i].x *= 0.1f;
                D_809E0424->unk_01BC[i].y *= 0.1f;
                D_809E0424->unk_01BC[i].y += 3150.0f;
                D_809E0424->unk_01BC[i].z *= 0.1f;
            }

            D_809E0424->unk_01B0.x *= 0.1f;
            D_809E0424->unk_01B0.y *= 0.1f;
            D_809E0424->unk_01B0.y += 3150.0f;
            D_809E0424->unk_01B0.z *= 0.1f;

            D_809E0424->unk_017C.y *= 0.1f;
            D_809E0424->unk_017C.y += 3150.0f;
            D_809E0424->unk_0188.y *= 0.1f;
            D_809E0424->unk_0188.y += 3150.0f;

            D_809E0428->actor.world.pos.x *= 0.1f;
            D_809E0428->actor.world.pos.y *= 0.1f;
            D_809E0428->actor.world.pos.y += 3150.0f;
            D_809E0428->actor.world.pos.z *= 0.1f;

            D_809E0428->unk_0170.x *= 0.1f;
            D_809E0428->unk_0170.y *= 0.1f;
            D_809E0428->unk_0170.y += 3150.0f;
            D_809E0428->unk_0170.z *= 0.1f;

            for (i = 0; i < ARRAY_COUNT(this->unk_01BC); i++) {
                D_809E0428->unk_01BC[i].x *= 0.1f;
                D_809E0428->unk_01BC[i].y *= 0.1f;
                D_809E0428->unk_01BC[i].y += 3150.0f;
                D_809E0428->unk_01BC[i].z *= 0.1f;
            }

            D_809E0428->unk_01B0.x *= 0.1f;
            D_809E0428->unk_01B0.y *= 0.1f;
            D_809E0428->unk_01B0.y += 3150.0f;
            D_809E0428->unk_01B0.z *= 0.1f;

            D_809E0428->unk_017C.y *= 0.1f;
            D_809E0428->unk_017C.y += 3150.0f;
            D_809E0428->unk_0188.y *= 0.1f;
            D_809E0428->unk_0188.y += 3150.0f;
        }

        player->actor.home.pos = player->actor.world.pos;
        player->actor.prevPos = player->actor.world.pos;

        temp_a0_5 = globalCtx->actorCtx.actorLists[ACTORCAT_BG].first;
        while (temp_a0_5 != NULL) {
            if (temp_a0_5->id == ACTOR_BG_INIBS_MOVEBG) {
                Actor_MarkForDeath(temp_a0_5);
                break;
            }
            temp_a0_5 = temp_a0_5->next;
        }
        {
            f32 tmp = D_809E0422 ? 3150.0f : 0.0f;

            Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_BG_INIBS_MOVEBG, 0, tmp, 0, 0, 0, 0, D_809E0422);
        }

        temp_a0_5 = globalCtx->actorCtx.actorLists[ACTORCAT_BOSS].first;
        while (temp_a0_5 != NULL) {
            if ((temp_a0_5->id == ACTOR_EN_TANRON5) || (temp_a0_5->id == ACTOR_ITEM_B_HEART)) {
                if (D_809E0422 == 0) {
                    temp_a0_5->world.pos.y -= 3150.0f;
                    temp_a0_5->world.pos.y *= 10.0f;

                    temp_a0_5->floorHeight -= 3150.0f;
                    temp_a0_5->floorHeight *= 10.0f;

                    phi_f0_2 = 10.0f;
                } else {
                    temp_a0_5->world.pos.y *= 0.1f;
                    temp_a0_5->world.pos.y += 3150.0f;

                    temp_a0_5->floorHeight *= 0.1f;
                    temp_a0_5->floorHeight += 3150.0f;

                    phi_f0_2 = 0.1f;
                }

                temp_a0_5->world.pos.x *= phi_f0_2;
                temp_a0_5->world.pos.z *= phi_f0_2;

                temp_a0_5->speedXZ *= phi_f0_2;

                temp_a0_5->velocity.x *= phi_f0_2;
                temp_a0_5->velocity.y *= phi_f0_2;
                temp_a0_5->velocity.z *= phi_f0_2;

                temp_a0_5->gravity *= phi_f0_2;
                temp_a0_5->terminalVelocity *= phi_f0_2;

                temp_a0_5->scale.x *= phi_f0_2;
                temp_a0_5->scale.y *= phi_f0_2;
                temp_a0_5->scale.z *= phi_f0_2;

                if (temp_a0_5->id == ACTOR_ITEM_B_HEART) {
                    ((ItemBHeart*)temp_a0_5)->unk_168 *= phi_f0_2;
                }
            }
            temp_a0_5 = temp_a0_5->next;
        }
    }

    switch (this->unk_1D78) {
        case 0:
            break;

        case 1:
            this->unk_1D7A = 0;
            func_809DA1D0(globalCtx, 255, 255, 255, 0);
            this->unk_1D78 = 2;
            play_sound(NA_SE_SY_TRANSFORM_MASK_FLASH);

        case 2:
            this->unk_1D7A += 40;
            if (this->unk_1D7A >= 400) {
                this->unk_1D78 = 3;
            }
            phi_v1 = this->unk_1D7A;
            if (phi_v1 > 255) {
                phi_v1 = 255;
            }
            func_809DA22C(globalCtx, phi_v1);
            break;

        case 3:
            this->unk_1D7A -= 40;
            if (this->unk_1D7A <= 0) {
                this->unk_1D7A = 0;
                this->unk_1D78 = 0;
                func_809DA24C(globalCtx);
            } else {
                phi_v1 = this->unk_1D7A;
                if (phi_v1 > 255) {
                    phi_v1 = 255;
                }
                func_809DA22C(globalCtx, phi_v1);
            }
            break;
    }

    if ((this->unk_1D18 != 0) && (this->unk_1D22 != 0)) {
        Matrix_RotateY(player->actor.shape.rot.y, MTXMODE_NEW);
        Matrix_GetStateTranslationAndScaledZ(this->unk_1D64, &sp58);

        this->unk_1D24.x = player->actor.world.pos.x + sp58.x;
        this->unk_1D24.y = player->actor.world.pos.y + sp58.y + this->unk_1D68;
        this->unk_1D24.z = player->actor.world.pos.z + sp58.z;

        this->unk_1D30.x = player->actor.world.pos.x;
        this->unk_1D30.y = player->actor.world.pos.y + this->unk_1D6C;
        this->unk_1D30.z = player->actor.world.pos.z;

        this->unk_1D54 = Math_SinS(this->unk_1D14 * 1512) * this->unk_1D58;
        Matrix_InsertZRotation_f(this->unk_1D54, MTXMODE_APPLY);
        Matrix_GetStateTranslationAndScaledY(1.0f, &this->unk_1D3C);
        Play_CameraSetAtEyeUp(globalCtx, this->unk_1D22, &this->unk_1D30, &this->unk_1D24, &this->unk_1D3C);
        ShrinkWindow_SetLetterboxTarget(27);
    }
}

void func_809DEAC4(Boss02* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Boss02* sp68;
    Vec3f sp5C;
    f32 sp58 = 0.0f;

    this->unk_1D1C++;
    if (this->unk_0194 == 0) {
        sp68 = D_809E0424;
    } else {
        sp68 = D_809E0428;
    }

    switch (this->unk_1D20) {
        case 0:
            break;

        case 1:
            if ((gSaveContext.save.weekEventReg[52] & 0x20) || ((u32)(KREG(13) + 15) >= this->unk_1D1C)) {
                break;
            }
            Cutscene_Start(globalCtx, &globalCtx->csCtx);
            this->unk_1D22 = Play_CreateSubCamera(globalCtx);
            Play_CameraChangeStatus(globalCtx, CAM_ID_MAIN, 1);
            Play_CameraChangeStatus(globalCtx, this->unk_1D22, 7);
            this->unk_1D20 = 2;
            this->unk_1D1C = 0;

        case 2:
            player->actor.shape.rot.y = -0x8000;
            player->actor.world.rot.y = player->actor.shape.rot.y;
            this->unk_1D24.x = player->actor.world.pos.x - 20.0f;
            this->unk_1D24.y = (Player_GetHeight(player) + player->actor.world.pos.y) - 29.0f;
            this->unk_1D24.z = player->actor.world.pos.z - 50;

            this->unk_1D30.x = player->actor.world.pos.x;
            this->unk_1D30.y = (Player_GetHeight(player) + player->actor.world.pos.y) - 17.0f;
            this->unk_1D30.z = player->actor.world.pos.z;
            if (this->unk_1D1C >= 30) {
                if (this->unk_1D1C == 30) {
                    func_8013EC44(0.0f, 50, 200, 1);
                }
                this->unk_0150 += 0x4000;
                sp58 = (Math_SinS(this->unk_0150) * (BREG(19) + 5)) * 0.1f;
                Matrix_InsertZRotation_f(Math_SinS(this->unk_1D1C * 0x3000) * ((KREG(28) * 0.001f) + 0.017f),
                                         MTXMODE_NEW);
                Matrix_GetStateTranslationAndScaledY(1.0f, &this->unk_1D3C);
                func_8019F128(NA_SE_EV_EARTHQUAKE_LAST - SFX_FLAG);
            }

            if (this->unk_1D1C == 20) {
                this->unk_1D7E = 100;
            }

            if (this->unk_1D1C == 45) {
                func_800B7298(globalCtx, &this->actor, 21);
                D_809E0430 = KREG(91) + 43;
            }

            if (this->unk_1D1C == 85) {
                D_809E0424->unk_0144 = 11;
                D_809E0424->unk_014C = 0;
            }

            if (this->unk_1D1C == 92) {
                func_8013EC44(0.0f, 255, 30, 100);
            }

            if (this->unk_1D1C == 100) {
                func_800B7298(globalCtx, &this->actor, 0x73);
            }

            if (this->unk_1D1C == 112) {
                this->unk_1D20 = 10;
                this->unk_1D1C = 0;
            }
            break;

        case 10:
            if (this->unk_1D1C < 310) {
                this->unk_1D48 = sp68->actor.world.pos;
                this->unk_1D24.x = (sp68->actor.world.pos.x * 50.0f) * 0.001f;
                this->unk_1D24.y = (sp68->actor.world.pos.y * 50.0f) * 0.001f;
                if (this->unk_1D24.y < 100.0f) {
                    this->unk_1D24.y = 100.0f;
                }
                this->unk_1D24.z = (sp68->actor.world.pos.z * 100) * 0.001f;
            }

            Math_ApproachF(&this->unk_1D30.x, this->unk_1D48.x, 0.1f, 3000.0f);
            Math_ApproachF(&this->unk_1D30.y, this->unk_1D48.y, 0.1f, 3000.0f);
            Math_ApproachF(&this->unk_1D30.z, this->unk_1D48.z, 0.1f, 3000.0f);

            if (this->unk_1D1C == 100) {
                D_809E0428->unk_0144 = 11;
                D_809E0428->unk_014C = 0;
                this->unk_0194 = 1;
            }

            if (this->unk_1D1C == (u32)(KREG(92) + 125)) {
                TitleCard_InitBossName(&globalCtx->state, &globalCtx->actorCtx.titleCtxt,
                                       Lib_SegmentedToVirtual(object_boss02_Tex_008650), 160, 180, 128, 40);
            }

            if (this->unk_1D1C == (u32)(BREG(27) + 335)) {
                func_80169AFC(globalCtx, this->unk_1D22, 0);
                this->unk_1D22 = 0;
                Cutscene_End(globalCtx, &globalCtx->csCtx);
                func_800B7298(globalCtx, &this->actor, 6);
                this->actor.flags |= ACTOR_FLAG_1;
                this->unk_1D20 = 0;
                D_809E0424->unk_0144 = D_809E0428->unk_0144 = 3;
                D_809E0424->unk_0146[0] = D_809E0428->unk_0146[0] = 60;
                gSaveContext.eventInf[5] |= 0x20;
            }
            break;

        case 100:
            if (ActorCutscene_GetCurrentIndex() == -1) {
                Cutscene_Start(globalCtx, &globalCtx->csCtx);
                this->unk_1D22 = Play_CreateSubCamera(globalCtx);
                Play_CameraChangeStatus(globalCtx, CAM_ID_MAIN, 1);
                Play_CameraChangeStatus(globalCtx, this->unk_1D22, 7);
                this->unk_1D20 = 101;
                this->unk_1D1C = 0;
                this->unk_1D5C = 1.0f;
                this->unk_1D30 = sp68->actor.world.pos;
            } else {
                break;
            }

        case 101:
        case 102:
        case_10x:
            if ((this->unk_1D20 == 101) || (this->unk_1D20 == 103)) {
                this->unk_1D48 = sp68->actor.world.pos;
            } else {
                this->unk_1D48 = sp68->unk_147C[sp68->unk_1678];
            }

            this->unk_1D24.x = player->actor.world.pos.x;
            this->unk_1D24.y = player->actor.world.pos.y + 100.0f;
            if (D_809E0422 == 0) {
                if (this->unk_1D24.y < 100.0f) {
                    this->unk_1D24.y = 100.0f;
                }
            } else if (this->unk_1D24.y < 3160.0f) {
                this->unk_1D24.y = 3160.0f;
            }

            if (this->unk_1D48.y < (100.0f * D_809DF5B0)) {
                this->unk_1D48.y = (100.0f * D_809DF5B0);
            }

            this->unk_1D24.z = player->actor.world.pos.z;
            Math_ApproachF(&this->unk_1D30.x, this->unk_1D48.x, 0.3f, this->unk_1D5C * 500.0f);
            Math_ApproachF(&this->unk_1D30.y, this->unk_1D48.y, 0.3f, this->unk_1D5C * 500.0f);
            Math_ApproachF(&this->unk_1D30.z, this->unk_1D48.z, 0.3f, this->unk_1D5C * 500.0f);
            Math_ApproachF(&this->unk_1D5C, 1.0f, 1.0f, 0.02f);
            break;

        case 103:
            this->unk_0150 += 0x4000;
            sp58 = Math_SinS(this->unk_0150);
            sp58 = (sp58 * this->unk_0146[0]) * 1.5f;
            if (this->unk_1D1C == 30) {
                func_80169AFC(globalCtx, this->unk_1D22, 0);
                this->unk_1D22 = 0;
                Cutscene_End(globalCtx, &globalCtx->csCtx);
                func_800B7298(globalCtx, &this->actor, 6);
                this->unk_1D20 = 0;
                this->actor.flags |= ACTOR_FLAG_1;
                sp68->unk_0144 = 10;
                if ((D_809E0424->unk_0144 >= 10) && (D_809E0428->unk_0144 >= 10)) {
                    f32 phi_f0;

                    this->unk_1D7E = 0;
                    if (D_809E0422 == 0) {
                        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_ITEM_B_HEART, 0.0f, 30.0f, -150.0f, 0, 1, 0,
                                    0);
                        phi_f0 = 60.0f;
                    } else {
                        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_ITEM_B_HEART, 0.0f, 3153.0f, -15.0f, 0, 1, 0,
                                    35);
                        phi_f0 = 3155.0f;
                    }
                    D_809E0434 = (DoorWarp1*)Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx,
                                                                ACTOR_DOOR_WARP1, 0.0f, phi_f0, 0.0f, 0, 0, 0, 1);

                    if (D_809E0422 == 0) {
                        D_809E0434->unk_203 = 0;
                        D_809E0434->unk_204 = 1.0f;
                    } else {
                        D_809E0434->unk_203 = 1;
                        D_809E0434->unk_204 = 0.1f;
                    }
                }
            }
            goto case_10x;
    }

    if ((this->unk_1D20 != 0) && (this->unk_1D22 != 0)) {
        sp5C = this->unk_1D24;
        sp5C.y += sp58 * D_809DF5B0;
        Play_CameraSetAtEyeUp(globalCtx, this->unk_1D22, &this->unk_1D30, &sp5C, &this->unk_1D3C);
        this->unk_1D3C.z = this->unk_1D3C.x = 0.0f;
        this->unk_1D3C.y = 1.0f;
        ShrinkWindow_SetLetterboxTarget(27);
    }
}
