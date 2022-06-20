/*
 * File: z_boss_01.c
 * Overlay: ovl_Boss_01
 * Description: Odolwa
 */

#include "z_boss_01.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((Boss01*)thisx)

void Boss01_Init(Actor* thisx, GlobalContext* globalCtx);
void Boss01_Destroy(Actor* thisx, GlobalContext* globalCtx);
void Boss01_Update(Actor* thisx, GlobalContext* globalCtx);
void Boss01_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_809D12B4(Boss01* this, GlobalContext* globalCtx);
void func_809D1B2C(Boss01* this, GlobalContext* globalCtx);
void func_809D1E74(Boss01* this, GlobalContext* globalCtx);
void func_809D20D0(Boss01* this, GlobalContext* globalCtx);
void func_809D25E8(Boss01* this, GlobalContext* globalCtx);
void func_809D26B8(Boss01* this, GlobalContext* globalCtx);
void func_809D27D4(Boss01* this, GlobalContext* globalCtx);
void func_809D2AA0(Boss01* this, GlobalContext* globalCtx);
void func_809D2BCC(Boss01* this, GlobalContext* globalCtx);
void func_809D2CDC(Boss01* this, GlobalContext* globalCtx);
void func_809D2E4C(Boss01* this, GlobalContext* globalCtx);
void func_809D30D0(Boss01* this, GlobalContext* globalCtx);
void func_809D345C(Boss01* this, GlobalContext* globalCtx);
void func_809D3530(Boss01* this, GlobalContext* globalCtx);
void func_809D3ADC(Boss01* this, GlobalContext* globalCtx);
void func_809D3CD0(Boss01* this, GlobalContext* globalCtx);
void func_809D4464(Boss01* this, GlobalContext* globalCtx);
void func_809D6314(Boss01* this, GlobalContext* globalCtx);
void func_809D6488(Boss01* this, GlobalContext* globalCtx);
void func_809D6588(Boss01* this, GlobalContext* globalCtx);
void func_809D65E0(Boss01* this, GlobalContext* globalCtx);

#if 0
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

#endif

extern DamageTable D_809D7990;
extern DamageTable D_809D79B0;
extern ColliderJntSphElementInit D_809D79D0[3];
extern ColliderJntSphInit D_809D7A3C;
extern ColliderJntSphElementInit D_809D7A4C[1];
extern ColliderJntSphInit D_809D7A70;
extern ColliderJntSphElementInit D_809D7A80[11];
extern ColliderJntSphInit D_809D7C0C;
extern ColliderJntSphElementInit D_809D7C1C[2];
extern ColliderJntSphInit D_809D7C64;
extern ColliderCylinderInit D_809D7C74;
extern ColliderCylinderInit D_809D7CA0;

extern UNK_TYPE D_06000C44;
extern UNK_TYPE D_06001884;
extern UNK_TYPE D_0600C338;
extern UNK_TYPE D_0600C5E0;
extern UNK_TYPE D_0600C7A8;
extern UNK_TYPE D_0600E3E8;
extern UNK_TYPE D_0600FDEC;
extern UNK_TYPE D_0600FF94;
extern UNK_TYPE D_06010980;
extern UNK_TYPE D_060124CC;
extern UNK_TYPE D_06012B70;
extern UNK_TYPE D_06012D10;
extern UNK_TYPE D_06012EBC;
extern UNK_TYPE D_06013480;
extern UNK_TYPE D_0601407C;
extern UNK_TYPE D_06014F14;
extern UNK_TYPE D_06015A30;
extern UNK_TYPE D_06016168;
extern UNK_TYPE D_060164CC;
extern UNK_TYPE D_0601F6A4;
extern UNK_TYPE D_060204AC;
extern UNK_TYPE D_060213A8;
extern UNK_TYPE D_06022550;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D0530.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D0550.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D0678.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D082C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D089C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D092C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D0AA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/Boss01_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/Boss01_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D119C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D1258.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D12B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D1AB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D1B2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D1E5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D1E74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D1EA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D20D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D2588.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D25E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D2664.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D26B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D2780.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D27D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D2858.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D2914.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D2A44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D2AA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D2BCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D2CDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D2DE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D2E4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D3074.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D30D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D32B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D3374.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D3400.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D345C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D34D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D3530.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D35A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D365C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D370C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D3A7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D3ADC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D3C10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D3CD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D441C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D4464.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D44C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D4668.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/Boss01_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D519C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D5584.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D55CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/Boss01_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D5B0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D5BC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D5FB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D606C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D62D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D6314.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D6424.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D6488.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D64E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D6540.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D6588.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D65E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D670C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D694C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D6B08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D6BB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D6C98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D6E7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D73D4.s")
