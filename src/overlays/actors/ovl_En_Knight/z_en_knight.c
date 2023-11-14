/*
 * File: z_en_knight.c
 * Overlay: ovl_En_Knight
 * Description: Igos du Ikana and his lackeys
 */

#include "z_en_knight.h"
#include "z64shrink_window.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_UNFRIENDLY | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnKnight*)thisx)

void EnKnight_Init(Actor* thisx, PlayState* play);
void EnKnight_Destroy(Actor* thisx, PlayState* play);
void EnKnight_Update(Actor* thisx, PlayState* play);
void EnKnight_Draw(Actor* thisx, PlayState* play);

void func_809B331C(EnKnight* this, PlayState* play);
void func_809B33F0(EnKnight* this, PlayState* play);
void func_809B3618(EnKnight* this, PlayState* play);
void func_809B3834(EnKnight* this, PlayState* play);
void func_809B3958(EnKnight* this, PlayState* play);
void func_809B3B94(EnKnight* this, PlayState* play);
void func_809B40E8(EnKnight* this, PlayState* play);
void func_809B41F8(EnKnight* this, PlayState* play);
void func_809B4308(EnKnight* this, PlayState* play);
void func_809B4C58(EnKnight* this, PlayState* play);
void func_809B4ED8(EnKnight* this, PlayState* play);
void func_809B5058(EnKnight* this, PlayState* play);
void func_809B52E8(EnKnight* this, PlayState* play);
void func_809B5698(EnKnight* this, PlayState* play);
void func_809B58D4(EnKnight* this, PlayState* play);
void func_809B5B08(EnKnight* this, PlayState* play);
void func_809B5D54(EnKnight* this, PlayState* play);
void func_809B5ED0(EnKnight* this, PlayState* play);
void func_809B601C(EnKnight* this, PlayState* play);
void func_809B6764(EnKnight* this, PlayState* play);
void func_809B6C54(EnKnight* this, PlayState* play);
void func_809B6D94(EnKnight* this, PlayState* play);
void func_809B6F40(EnKnight* this, PlayState* play);
void func_809B71DC(EnKnight* this, PlayState* play);
void func_809B7778(EnKnight* this, PlayState* play);
void func_809B7950(EnKnight* this, PlayState* play);
void func_809B8458(EnKnight* this, PlayState* play);
void func_809BA0CC(EnKnight* this, PlayState* play);
void func_809BA978(EnKnight* this, PlayState* play);

#if 0
// static DamageTable sDamageTable = {
static DamageTable D_809BDB04 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(0, 0x1),
    /* Normal arrow   */ DMG_ENTRY(3, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(0, 0xD),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(2, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0xA),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0xE),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

// static DamageTable sDamageTable = {
static DamageTable D_809BDB24 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(3, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(2, 0xF),
    /* Deku launch    */ DMG_ENTRY(2, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0xA),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(1, 0xD),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_809BDB44[1] = {
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 27 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_809BDB8C = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    ARRAY_COUNT(sJntSphElementsInit), D_809BDB44, // sJntSphElementsInit,
};

// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_809BDB68[1] = {
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 32 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_809BDB9C = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    ARRAY_COUNT(sJntSphElementsInit), D_809BDB68, // sJntSphElementsInit,
};

// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_809BDBAC[1] = {
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 27 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_809BDBD0 = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    ARRAY_COUNT(sJntSphElementsInit), D_809BDBAC, // sJntSphElementsInit,
};

// static ColliderJntSphElementInit sJntSphElementsInit[2] = {
static ColliderJntSphElementInit D_809BDBE0[2] = {
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7EFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7EFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 17 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_809BDC28 = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER | OC1_TYPE_1, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    ARRAY_COUNT(sJntSphElementsInit), D_809BDBE0, // sJntSphElementsInit,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809BDC38 = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 15, 20, -10, { 0, 0, 0 } },
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809BDC64 = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ALL, AC_ON | AC_TYPE_PLAYER | AC_TYPE_ENEMY | AC_TYPE_OTHER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7FFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 20, 40, 0, { 0, 0, 0 } },
};

ActorInit En_Knight_InitVars = {
    /**/ ACTOR_EN_KNIGHT,
    /**/ ACTORCAT_BOSS,
    /**/ FLAGS,
    /**/ OBJECT_KNIGHT,
    /**/ sizeof(EnKnight),
    /**/ EnKnight_Init,
    /**/ EnKnight_Destroy,
    /**/ EnKnight_Update,
    /**/ EnKnight_Draw,
};

#endif

extern DamageTable D_809BDB04;
extern DamageTable D_809BDB24;
extern ColliderJntSphElementInit D_809BDB44[1];
extern ColliderJntSphInit D_809BDB8C;
extern ColliderJntSphElementInit D_809BDB68[1];
extern ColliderJntSphInit D_809BDB9C;
extern ColliderJntSphElementInit D_809BDBAC[1];
extern ColliderJntSphInit D_809BDBD0;
extern ColliderJntSphElementInit D_809BDBE0[2];
extern ColliderJntSphInit D_809BDC28;
extern ColliderCylinderInit D_809BDC38;
extern ColliderCylinderInit D_809BDC64;

extern UNK_TYPE D_060005A8;
extern UNK_TYPE D_06001CDC;
extern UNK_TYPE D_06002174;
extern UNK_TYPE D_06003008;
extern UNK_TYPE D_060031F0;
extern UNK_TYPE D_06003650;
extern UNK_TYPE D_060040E0;
extern UNK_TYPE D_06004620;
extern UNK_TYPE D_06004974;
extern UNK_TYPE D_060079D4;
extern UNK_TYPE D_06008524;
extern UNK_TYPE D_06008D80;
extern UNK_TYPE D_06009538;
extern UNK_TYPE D_06009D8C;
extern UNK_TYPE D_0600A530;
extern UNK_TYPE D_0600AFAC;
extern UNK_TYPE D_0600B5D4;
extern UNK_TYPE D_0600BCF4;
extern UNK_TYPE D_0600CDE0;
extern UNK_TYPE D_0600DDCC;
extern UNK_TYPE D_0600EA90;
extern UNK_TYPE D_0600EF44;
extern UNK_TYPE D_06010E98;
extern UNK_TYPE D_06011298;
extern UNK_TYPE D_06013020;
extern UNK_TYPE D_06018BC4;
extern UNK_TYPE D_06020950;
extern UNK_TYPE D_06022728;
extern UNK_TYPE D_06022CAC;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B20F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B21F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B22CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/EnKnight_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/EnKnight_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B2DD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B2F54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B316C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B31E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B329C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B331C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B3394.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B33F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B35BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B3618.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B37C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B3834.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B389C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B3958.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B3A7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B3B94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B3CD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B3DAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B3E9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B3F0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B4024.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B40E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B41D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B41F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B42B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B4308.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B47EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B4880.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B4BFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B4C58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B4E84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B4ED8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B4F90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B5058.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B51DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B52E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B5634.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B5698.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B58D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B592C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B59FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B5B08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B5D38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B5D54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B5E90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B5ED0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B5FA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B601C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B631C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B638C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B6528.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B6574.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B6764.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B6C04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B6C54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B6D38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B6D94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B6EC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B6F40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B7190.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B71DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B7708.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B7778.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B78A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B7950.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B842C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B8458.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B9A18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B9D24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B9E00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B9F8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BA058.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BA0CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BA940.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BA978.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/EnKnight_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BC2C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BC67C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BC720.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BC8B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BCA80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BCAD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BCB54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BCB78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/EnKnight_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BD1AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BD260.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BD29C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BD490.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BD858.s")
