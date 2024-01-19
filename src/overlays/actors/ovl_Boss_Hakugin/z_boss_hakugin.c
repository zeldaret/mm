/*
 * File: z_boss_hakugin.c
 * Overlay: ovl_Boss_Hakugin
 * Description: Goht
 */

#include "z_boss_hakugin.h"
#include "z64quake.h"
#include "z64rumble.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_UNFRIENDLY | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((BossHakugin*)thisx)

void BossHakugin_Init(Actor* thisx, PlayState* play);
void BossHakugin_Destroy(Actor* thisx, PlayState* play);
void BossHakugin_Update(Actor* thisx, PlayState* play);
void BossHakugin_Draw(Actor* thisx, PlayState* play);

void func_80B08018(BossHakugin* this, PlayState* play);
void func_80B0813C(BossHakugin* this, PlayState* play);
void func_80B082AC(BossHakugin* this, PlayState* play);
void func_80B0863C(BossHakugin* this, PlayState* play);
void func_80B08960(BossHakugin* this, PlayState* play);
void func_80B08CB8(BossHakugin* this, PlayState* play);
void func_80B091D8(BossHakugin* this, PlayState* play);
void func_80B094E0(BossHakugin* this, PlayState* play);
void func_80B098BC(BossHakugin* this, PlayState* play);
void func_80B09C78(BossHakugin* this, PlayState* play);
void func_80B09E20(BossHakugin* this, PlayState* play);
void func_80B09EDC(BossHakugin* this, PlayState* play);
void func_80B0A2A4(BossHakugin* this, PlayState* play);
void func_80B0A638(BossHakugin* this, PlayState* play);
void func_80B0A8C4(BossHakugin* this, PlayState* play);

#if 0
ActorInit Boss_Hakugin_InitVars = {
    /**/ ACTOR_BOSS_HAKUGIN,
    /**/ ACTORCAT_BOSS,
    /**/ FLAGS,
    /**/ OBJECT_BOSS_HAKUGIN,
    /**/ sizeof(BossHakugin),
    /**/ BossHakugin_Init,
    /**/ BossHakugin_Destroy,
    /**/ BossHakugin_Update,
    /**/ BossHakugin_Draw,
};

// static ColliderJntSphElementInit sJntSphElementsInit[19] = {
static ColliderJntSphElementInit D_80B0E700[19] = {
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 16, { { 1300, 200, 0 }, 30 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 15, { { 1400, 300, 0 }, 35 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 2, { { 1600, -400, 0 }, 26 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 6, { { 1700, 200, 400 }, 18 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 8, { { 1000, 0, 0 }, 10 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 9, { { 500, 0, 0 }, 9 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 11, { { 1700, 200, -400 }, 18 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 13, { { 1000, 0, 0 }, 10 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 14, { { 500, 0, 0 }, 9 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 21, { { 800, 0, 400 }, 15 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 22, { { 500, 200, 0 }, 9 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 24, { { 300, 0, 0 }, 8 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 25, { { 500, 100, 0 }, 9 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 28, { { 800, 0, -400 }, 15 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 29, { { 500, 200, 0 }, 9 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 31, { { 300, 0, 0 }, 8 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 32, { { 500, 100, 0 }, 9 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 16, { { 2400, -400, -2900 }, 12 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 16, { { 2400, -400, 2900 }, 12 }, 270 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80B0E9AC = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    ARRAY_COUNT(sJntSphElementsInit), D_80B0E700, // sJntSphElementsInit,
};

// static ColliderTrisElementInit sTrisElementsInit[1] = {
static ColliderTrisElementInit D_80B0E9BC[1] = {
    {
        { ELEMTYPE_UNK5, { 0x20000000, 0x03, 0x08 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_NONE, OCELEM_NONE, },
        { { { 22.0f, 0.0f, 100.0f }, { 0.0f, 0.0f, -100.0f }, { -22.0f, 0.0f, 100.0f } } },
    },
};

// static ColliderTrisInit sTrisInit = {
static ColliderTrisInit D_80B0E9F8 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_NONE, OC1_NONE, OC2_TYPE_1, COLSHAPE_TRIS, },
    ARRAY_COUNT(sTrisElementsInit), D_80B0E9BC, // sTrisElementsInit,
};

// static ColliderSphereInit sSphereInit = {
static ColliderSphereInit D_80B0EA08 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_NONE, OC1_NONE, OC2_TYPE_2, COLSHAPE_SPHERE, },
    { ELEMTYPE_UNK5, { 0x20000000, 0x00, 0x08 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_NONE, OCELEM_NONE, },
    { 1, { { 0, 0, 0 }, 23 }, 100 },
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B0EA34 = {
    { COLTYPE_HARD, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x02, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_ON, OCELEM_ON, },
    { 170, 40, 0, { 0, 0, 0 } },
};

// static DamageTable sDamageTable = {
static DamageTable D_80B0EA60 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xC),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0xE),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x3),
    /* Light arrow    */ DMG_ENTRY(1, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(1, 0xD),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xC),
};

// sColChkInfoInit
static CollisionCheckInfoInit D_80B0EA80 = { 30, 80, 100, MASS_IMMOVABLE };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B0EAD8[] = {
    ICHAIN_S8(hintId, 27, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 27, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, TARGET_MODE_5, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_STOP),
};

#endif

extern ColliderJntSphElementInit D_80B0E700[19];
extern ColliderJntSphInit D_80B0E9AC;
extern ColliderTrisElementInit D_80B0E9BC[1];
extern ColliderTrisInit D_80B0E9F8;
extern ColliderSphereInit D_80B0EA08;
extern ColliderCylinderInit D_80B0EA34;
extern DamageTable D_80B0EA60;
extern CollisionCheckInfoInit D_80B0EA80;
extern InitChainEntry D_80B0EAD8[];

extern UNK_TYPE D_06002054;
extern UNK_TYPE D_0600319C;
extern UNK_TYPE D_06010488;
extern UNK_TYPE D_06011208;
extern UNK_TYPE D_06012ED0;
extern UNK_TYPE D_060134D0;
extern UNK_TYPE D_06013828;
extern UNK_TYPE D_06014040;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/BossHakugin_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/BossHakugin_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0573C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B057A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B058C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B05A64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B05B04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B05CBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B05D4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B05EE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0607C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B06558.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B06600.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0696C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B06B20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B06C08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B06D38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B06F48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0728C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B07450.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B07700.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0791C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B07B88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B07BFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B07DA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B07EEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B08018.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B08124.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0813C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0825C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B082AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B08550.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0863C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B08848.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B08960.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B08C1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B08CB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B09178.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B091D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B093C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B094E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B09840.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B098BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B09A94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B09C78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B09DFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B09E20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B09E84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B09EDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B09F7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0A2A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0A5EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0A638.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0A87C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0A8C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0AC30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0ADFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0B238.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0B34C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0B3F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0B548.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0B660.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/BossHakugin_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0C000.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0C1BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0C398.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0C570.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0C7B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0CAF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0CCD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0CF24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/BossHakugin_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0D2B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0D69C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0D750.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0D9CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0DFA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0E548.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0E5A4.s")
