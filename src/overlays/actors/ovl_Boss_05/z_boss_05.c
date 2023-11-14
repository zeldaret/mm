/*
 * File: z_boss_05.c
 * Overlay: ovl_Boss_05
 * Description: Bio Deku Baba
 */

#include "z_boss_05.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_UNFRIENDLY)

#define THIS ((Boss05*)thisx)

void Boss05_Init(Actor* thisx, PlayState* play);
void Boss05_Destroy(Actor* thisx, PlayState* play);
void Boss05_Update(Actor* thisx, PlayState* play);
void Boss05_Draw(Actor* thisx, PlayState* play);

void func_809EEDE8(Boss05* this, PlayState* play);
void func_809EF9BC(Boss05* this, PlayState* play);
void func_809EFAB4(Boss05* this, PlayState* play);
void func_809F010C(Boss05* this, PlayState* play);
void func_809F0244(Boss05* this, PlayState* play);
void func_809F0374(Boss05* this, PlayState* play);
void func_809F04C0(Boss05* this, PlayState* play);
void func_809F0590(Boss05* this, PlayState* play);
void func_809F06B8(Boss05* this, PlayState* play);
void func_809F0780(Boss05* this, PlayState* play);
void func_809F0ABC(Boss05* this, PlayState* play);
void func_809F0B0C(Boss05* this, PlayState* play);

#if 0
// static ColliderJntSphElementInit sJntSphElementsInit[2] = {
static ColliderJntSphElementInit D_809F1B2C[2] = {
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 15 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_809F1B74 = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    ARRAY_COUNT(sJntSphElementsInit), D_809F1B2C, // sJntSphElementsInit,
};

// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_809F1B84[1] = {
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 20 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_809F1BA8 = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    ARRAY_COUNT(sJntSphElementsInit), D_809F1B84, // sJntSphElementsInit,
};

// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_809F1BB8[1] = {
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7FFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 15 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_809F1BDC = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    ARRAY_COUNT(sJntSphElementsInit), D_809F1BB8, // sJntSphElementsInit,
};

// static DamageTable sDamageTable = {
static DamageTable D_809F1C00 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(3, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(3, 0x0),
    /* Goron punch    */ DMG_ENTRY(2, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xE),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x3),
    /* Light arrow    */ DMG_ENTRY(3, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(3, 0xF),
    /* Deku launch    */ DMG_ENTRY(2, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(1, 0xF),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
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
static DamageTable D_809F1C20 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(3, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x1),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(2, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(1, 0xF),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(1, 0x2),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

ActorInit Boss_05_InitVars = {
    /**/ ACTOR_BOSS_05,
    /**/ ACTORCAT_ENEMY,
    /**/ FLAGS,
    /**/ OBJECT_BOSS05,
    /**/ sizeof(Boss05),
    /**/ Boss05_Init,
    /**/ Boss05_Destroy,
    /**/ Boss05_Update,
    /**/ Boss05_Draw,
};

#endif

extern ColliderJntSphElementInit D_809F1B2C[2];
extern ColliderJntSphInit D_809F1B74;
extern ColliderJntSphElementInit D_809F1B84[1];
extern ColliderJntSphInit D_809F1BA8;
extern ColliderJntSphElementInit D_809F1BB8[1];
extern ColliderJntSphInit D_809F1BDC;
extern DamageTable D_809F1C00;
extern DamageTable D_809F1C20;

extern UNK_TYPE D_060006A4;
extern UNK_TYPE D_06000A5C;
extern UNK_TYPE D_06000ABC;
extern UNK_TYPE D_06002F0C;
extern UNK_TYPE D_06003448;
extern UNK_TYPE D_06006240;
extern UNK_TYPE D_06006E50;
extern UNK_TYPE D_06007488;
extern UNK_TYPE D_06007908;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809EE4E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809EE668.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/Boss05_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/Boss05_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809EECBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809EEDD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809EEDE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809EF9BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809EFAB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809EFE50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F0014.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F0058.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F00CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F010C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F01CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F0244.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F02D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F0374.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F0474.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F04C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F0538.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F0590.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F0650.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F06B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F0708.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F0780.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F0A0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F0A64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F0ABC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F0B0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/Boss05_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F1050.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F1170.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F1284.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F12A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F135C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F1404.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F1430.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F1464.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F14AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F1550.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/Boss05_Draw.s")
