/*
 * File: z_boss_07.c
 * Overlay: ovl_Boss_07
 * Description: Majora
 */

#include "z_boss_07.h"
#include "z64shrink_window.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_UNFRIENDLY | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((Boss07*)thisx)

void Boss07_Init(Actor* thisx, PlayState* play);
void Boss07_Destroy(Actor* thisx, PlayState* play);
void Boss07_Update(Actor* thisx, PlayState* play);
void Boss07_Draw(Actor* thisx, PlayState* play);

void func_809F5E88(Boss07* this, PlayState* play);
void func_809F65F4(Boss07* this, PlayState* play);
void func_809F748C(Boss07* this, PlayState* play);
void func_809F76D0(Boss07* this, PlayState* play);
void func_809F77A8(Boss07* this, PlayState* play);
void func_809F7968(Boss07* this, PlayState* play);
void func_809F7BC4(Boss07* this, PlayState* play);
void func_809F805C(Boss07* this, PlayState* play);
void func_809F86B8(Boss07* this, PlayState* play);
void func_809F87C8(Boss07* this, PlayState* play);
void func_809F8908(Boss07* this, PlayState* play);
void func_809F8B1C(Boss07* this, PlayState* play);
void func_809F8D04(Boss07* this, PlayState* play);
void func_809F8EC8(Boss07* this, PlayState* play);
void func_809F91D4(Boss07* this, PlayState* play);
void func_809FCCCC(Boss07* this, PlayState* play);
void func_809FD710(Boss07* this, PlayState* play);
void func_809FD89C(Boss07* this, PlayState* play);
void func_809FDAB0(Boss07* this, PlayState* play);
void func_809FDF54(Boss07* this, PlayState* play);
void func_809FE0E4(Boss07* this, PlayState* play);
void func_809FE348(Boss07* this, PlayState* play);
void func_809FE524(Boss07* this, PlayState* play);
void func_809FE734(Boss07* this, PlayState* play);
void func_809FFA80(Boss07* this, PlayState* play);
void func_809FFEAC(Boss07* this, PlayState* play);
void func_80A00274(Boss07* this, PlayState* play);
void func_80A00554(Boss07* this, PlayState* play);
void func_80A00720(Boss07* this, PlayState* play);
void func_80A01750(Boss07* this, PlayState* play);
void func_80A0264C(Boss07* this, PlayState* play);
void func_80A04890(Boss07* this, PlayState* play);
void func_80A04E5C(Boss07* this, PlayState* play);
void func_80A05608(Boss07* this, PlayState* play);
void func_80A05B50(Boss07* this, PlayState* play);
void func_80A05DDC(Boss07* this, PlayState* play);

#if 0
// static DamageTable sDamageTable = {
static DamageTable D_80A07980 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(2, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(2, 0xF),
    /* Sword beam     */ DMG_ENTRY(2, 0x9),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(2, 0xF),
};

// static DamageTable sDamageTable = {
static DamageTable D_80A079A0 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xC),
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
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0xA),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xD),
    /* Sword beam     */ DMG_ENTRY(2, 0x9),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(4, 0xC),
};

// static DamageTable sDamageTable = {
static DamageTable D_80A079C0 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0xE),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xC),
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
    /* Goron spikes   */ DMG_ENTRY(1, 0xE),
    /* Deku spin      */ DMG_ENTRY(1, 0xE),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xE),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0xA),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xE),
    /* Spin attack    */ DMG_ENTRY(1, 0xD),
    /* Sword beam     */ DMG_ENTRY(2, 0x9),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(2, 0xC),
};

// static DamageTable sDamageTable = {
static DamageTable D_80A079E0 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(2, 0xE),
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
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xD),
    /* Sword beam     */ DMG_ENTRY(2, 0x9),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(2, 0xE),
};

// static DamageTable sDamageTable = {
static DamageTable D_80A07A00 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0xD),
    /* Horse trample  */ DMG_ENTRY(1, 0xE),
    /* Explosives     */ DMG_ENTRY(1, 0xB),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0xE),
    /* Goron punch    */ DMG_ENTRY(1, 0xE),
    /* Sword          */ DMG_ENTRY(1, 0xD),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0xE),
    /* Ice arrow      */ DMG_ENTRY(1, 0xE),
    /* Light arrow    */ DMG_ENTRY(1, 0xE),
    /* Goron spikes   */ DMG_ENTRY(1, 0xC),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(1, 0xD),
    /* Light ray      */ DMG_ENTRY(1, 0xD),
    /* Thrown object  */ DMG_ENTRY(1, 0xE),
    /* Zora punch     */ DMG_ENTRY(1, 0xE),
    /* Spin attack    */ DMG_ENTRY(1, 0xA),
    /* Sword beam     */ DMG_ENTRY(1, 0xA),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(2, 0xB),
};

ActorInit Boss_07_InitVars = {
    /**/ ACTOR_BOSS_07,
    /**/ ACTORCAT_BOSS,
    /**/ FLAGS,
    /**/ OBJECT_BOSS07,
    /**/ sizeof(Boss07),
    /**/ Boss07_Init,
    /**/ Boss07_Destroy,
    /**/ Boss07_Update,
    /**/ Boss07_Draw,
};

// static ColliderJntSphElementInit sJntSphElementsInit[11] = {
static ColliderJntSphElementInit D_80A07A40[11] = {
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 30 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 25 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 150 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 150 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 150 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 150 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80A07BCC = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    ARRAY_COUNT(sJntSphElementsInit), D_80A07A40, // sJntSphElementsInit,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A07BDC = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 80, 200, 0, { 0, 0, 0 } },
};

// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_80A07C08[1] = {
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 36 }, 200 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80A07C2C = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    ARRAY_COUNT(sJntSphElementsInit), D_80A07C08, // sJntSphElementsInit,
};

// static ColliderQuadInit sQuadInit = {
static ColliderQuadInit D_80A07C3C = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_QUAD, },
    { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x04, 0x00 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

// static ColliderQuadInit sQuadInit = {
static ColliderQuadInit D_80A07C8C = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_QUAD, },
    { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

// static ColliderJntSphElementInit sJntSphElementsInit[11] = {
static ColliderJntSphElementInit D_80A07CDC[11] = {
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 25 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 40 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 150 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 150 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 150 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 150 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80A07E68 = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    ARRAY_COUNT(sJntSphElementsInit), D_80A07CDC, // sJntSphElementsInit,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A07E78 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x04, 0x10 }, { 0x00300000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 15, 30, -15, { 0, 0, 0 } },
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A07EA4 = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 50, 100, -50, { 0, 0, 0 } },
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A07ED0 = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7FFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 40, 20, 15, { 0, 0, 0 } },
};

#endif

extern DamageTable D_80A07980;
extern DamageTable D_80A079A0;
extern DamageTable D_80A079C0;
extern DamageTable D_80A079E0;
extern DamageTable D_80A07A00;
extern ColliderJntSphElementInit D_80A07A40[11];
extern ColliderJntSphInit D_80A07BCC;
extern ColliderCylinderInit D_80A07BDC;
extern ColliderJntSphElementInit D_80A07C08[1];
extern ColliderJntSphInit D_80A07C2C;
extern ColliderQuadInit D_80A07C3C;
extern ColliderQuadInit D_80A07C8C;
extern ColliderJntSphElementInit D_80A07CDC[11];
extern ColliderJntSphInit D_80A07E68;
extern ColliderCylinderInit D_80A07E78;
extern ColliderCylinderInit D_80A07EA4;
extern ColliderCylinderInit D_80A07ED0;

extern UNK_TYPE D_06000194;
extern UNK_TYPE D_06000428;
extern UNK_TYPE D_06000D0C;
extern UNK_TYPE D_06002C40;
extern UNK_TYPE D_06002D84;
extern UNK_TYPE D_06003854;
extern UNK_TYPE D_06003A64;
extern UNK_TYPE D_06009C7C;
extern UNK_TYPE D_06009EA8;
extern UNK_TYPE D_0600A194;
extern UNK_TYPE D_0600A400;
extern UNK_TYPE D_0600AE40;
extern UNK_TYPE D_0600AFB0;
extern UNK_TYPE D_0600B020;
extern UNK_TYPE D_0600C7D8;
extern UNK_TYPE D_0600CEE8;
extern UNK_TYPE D_060149A0;
extern UNK_TYPE D_06019E48;
extern UNK_TYPE D_0601DEB4;
extern UNK_TYPE D_06022BB4;
extern UNK_TYPE D_06023DAC;
extern UNK_TYPE D_06025018;
extern UNK_TYPE D_06025878;
extern UNK_TYPE D_060269EC;
extern UNK_TYPE D_06026EA0;
extern UNK_TYPE D_06027270;
extern UNK_TYPE D_0602EEC8;
extern UNK_TYPE D_0602EF68;
extern UNK_TYPE D_0602EFE8;
extern UNK_TYPE D_0602F640;
extern UNK_TYPE D_0602F840;
extern UNK_TYPE D_06033F80;
extern UNK_TYPE D_0603B330;
extern UNK_TYPE D_0603CBD0;
extern UNK_TYPE D_0603D7F0;
extern UNK_TYPE D_0603DD1C;
extern UNK_TYPE D_06040930;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F4980.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F49A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F49C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F4AE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F4BB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F4C40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F4CBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F4D10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F4D54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F4FAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F4FF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F51E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F52CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F536C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F5494.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/Boss07_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/Boss07_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F5E14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F5E88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F64F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F65F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F7400.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F748C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F7688.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F76D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F77A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F783C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F7968.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F7AB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F7BC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F7D2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F805C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F8658.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F86B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F87C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F8908.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F8AB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F8B1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F8D04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F8DEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F8E68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F8EC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F91D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F9280.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F93DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F94AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F99C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F9CEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F9E94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/Boss07_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FAA44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FB114.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FB504.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FB55C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FB728.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FB7D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FBB9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FBF94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/Boss07_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FC4C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FC8B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FC960.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FCBC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FCC70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FCCCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FD5F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FD710.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FD818.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FD89C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FD984.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FDAB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FDB2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FDBA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FDEDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FDF54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FE068.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FE0E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FE2D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FE348.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FE4B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FE524.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FE6B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FE734.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FEE70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FF0E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FF12C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FF5CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FF678.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FF6B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FF810.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FF900.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FFA04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FFA80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FFE64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FFEAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A0021C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A00274.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A00484.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A00554.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A006D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A006F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A00720.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A016E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A01750.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A025AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A0264C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A02B30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A02C54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A03238.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A036C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A03868.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A03F18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A03F5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A0434C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A045A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A04768.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A04878.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A04890.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A04DE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A04E5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A055E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A05608.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A05694.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A057A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A05AF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A05B50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A05C88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A05DDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A06500.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A06990.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A06C64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A06E24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A06F48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A07604.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A07638.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A07740.s")
