#include "z_boss_01.h"

#define FLAGS 0x00000035

#define THIS ((Boss01*)thisx)

void Boss01_Init(Actor* thisx, GlobalContext* globalCtx);
void Boss01_Destroy(Actor* thisx, GlobalContext* globalCtx);
void Boss01_Update(Actor* thisx, GlobalContext* globalCtx);
void Boss01_Draw(Actor* thisx, GlobalContext* globalCtx);

/*

// static DamageTable sDamageTable = {
static DamageTable D_809D7990 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xE),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0xE),
    /* Sword          */ DMG_ENTRY(1, 0xE),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(0, 0x1),
    /* Deku launch    */ DMG_ENTRY(1, 0xE),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0xB),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xE),
    /* Spin attack    */ DMG_ENTRY(1, 0xD),
    /* Sword beam     */ DMG_ENTRY(2, 0xC),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xE),
};


// static DamageTable sDamageTable = {
static DamageTable D_809D79B0 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(2, 0xF),
    /* Zora boomerang */ DMG_ENTRY(0, 0x1),
    /* Normal arrow   */ DMG_ENTRY(2, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(0, 0x1),
    /* Deku launch    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x1),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xE),
    /* Spin attack    */ DMG_ENTRY(2, 0xD),
    /* Sword beam     */ DMG_ENTRY(2, 0xD),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};


// static ColliderJntSphElementInit sJntSphElementsInit[3] = {
static ColliderJntSphElementInit D_809D79D0[3] = {
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x04, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 35 }, 100 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x04, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 35 }, 100 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x04, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 70 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_809D7A3C = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    3, D_809D79D0, // sJntSphElementsInit,
};


// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_809D7A4C[1] = {
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 36 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_809D7A70 = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    1, D_809D7A4C, // sJntSphElementsInit,
};


// static ColliderJntSphElementInit sJntSphElementsInit[11] = {
static ColliderJntSphElementInit D_809D7A80[11] = {
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 30 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 25 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_809D7C0C = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    11, D_809D7A80, // sJntSphElementsInit,
};


// static ColliderJntSphElementInit sJntSphElementsInit[2] = {
static ColliderJntSphElementInit D_809D7C1C[2] = {
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x04, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 36 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x04, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 36 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_809D7C64 = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    2, D_809D7C1C, // sJntSphElementsInit,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809D7C74 = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7FFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 15, 15, 10, { 0, 0, 0 } },
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809D7CA0 = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7FFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 8, 15, 10, { 0, 0, 0 } },
};


const ActorInit Boss_01_InitVars = {
    ACTOR_BOSS_01,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BOSS01,
    sizeof(Boss01),
    (ActorFunc)Boss01_Init,
    (ActorFunc)Boss01_Destroy,
    (ActorFunc)Boss01_Update,
    (ActorFunc)Boss01_Draw,
};

*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D0530.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D0550.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D0678.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D082C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D089C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D092C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D0AA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/Boss01_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/Boss01_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D119C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D1258.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D12B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D1AB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D1B2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D1E5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D1E74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D1EA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D20D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D2588.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D25E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D2664.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D26B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D2780.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D27D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D2858.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D2914.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D2A44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D2AA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D2BCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D2CDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D2DE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D2E4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D3074.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D30D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D32B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D3374.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D3400.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D345C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D34D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D3530.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D35A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D365C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D370C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D3A7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D3ADC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D3C10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D3CD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D441C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D4464.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D44C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D4668.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/Boss01_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D519C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D5584.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D55CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/Boss01_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D5B0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D5BC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D5FB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D606C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D62D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D6314.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D6424.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D6488.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D64E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D6540.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D6588.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D65E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D670C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D694C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D6B08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D6BB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D6C98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D6E7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D73D4.asm")
