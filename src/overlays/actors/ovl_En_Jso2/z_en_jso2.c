/*
 * File: z_en_jso2.c
 * Overlay: ovl_En_Jso2
 * Description: Garo Master
 */

#include "z_en_jso2.h"

#define FLAGS                                                                                            \
    (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_UNFRIENDLY | ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_100000 | \
     ACTOR_FLAG_80000000)

#define THIS ((EnJso2*)thisx)

void EnJso2_Init(Actor* thisx, PlayState* play);
void EnJso2_Destroy(Actor* thisx, PlayState* play);
void EnJso2_Update(Actor* thisx, PlayState* play);
void EnJso2_Draw(Actor* thisx, PlayState* play);

void func_80A778F8(EnJso2* this, PlayState* play);
void func_80A785E4(EnJso2* this, PlayState* play);
void func_80A78868(EnJso2* this, PlayState* play);
void func_80A78ACC(EnJso2* this, PlayState* play);
void func_80A78B70(EnJso2* this, PlayState* play);
void func_80A78C7C(EnJso2* this, PlayState* play);
void func_80A78F04(EnJso2* this, PlayState* play);
void func_80A79038(EnJso2* this, PlayState* play);
void func_80A7919C(EnJso2* this, PlayState* play);
void func_80A79364(EnJso2* this, PlayState* play);
void func_80A794C8(EnJso2* this, PlayState* play);
void func_80A79600(EnJso2* this, PlayState* play);
void func_80A7980C(EnJso2* this, PlayState* play);
void func_80A798C8(EnJso2* this, PlayState* play);
void func_80A79A84(EnJso2* this, PlayState* play);
void func_80A79BA0(EnJso2* this, PlayState* play);
void func_80A7A124(EnJso2* this, PlayState* play);
void func_80A7A2EC(EnJso2* this, PlayState* play);

#if 0
// static DamageTable sDamageTable = {
static DamageTable D_80A7B4F0 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
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
    /* Zora barrier   */ DMG_ENTRY(0, 0x5),
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

ActorInit En_Jso2_InitVars = {
    /**/ ACTOR_EN_JSO2,
    /**/ ACTORCAT_ENEMY,
    /**/ FLAGS,
    /**/ OBJECT_JSO,
    /**/ sizeof(EnJso2),
    /**/ EnJso2_Init,
    /**/ EnJso2_Destroy,
    /**/ EnJso2_Update,
    /**/ EnJso2_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A7B608 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x08, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 22, 70, 0, { 0, 0, 0 } },
};

// static ColliderQuadInit sQuadInit = {
static ColliderQuadInit D_80A7B634 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_NONE, OC1_NONE, OC2_NONE, COLSHAPE_QUAD, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x09, 0x10 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL | TOUCH_UNK7, BUMP_NONE, OCELEM_NONE, },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

#endif

extern DamageTable D_80A7B4F0;
extern ColliderCylinderInit D_80A7B608;
extern ColliderQuadInit D_80A7B634;

extern UNK_TYPE D_06002ED8;
extern UNK_TYPE D_060081F4;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/EnJso2_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/EnJso2_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A776E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A77790.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A77880.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A778D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A778F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A78588.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A785E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A787FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A78868.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A78A70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A78ACC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A78B04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A78B70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A78C08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A78C7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A78E8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A78F04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A78F80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A79038.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A790E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A7919C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A79300.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A79364.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A79450.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A794C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A79524.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A79600.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A796BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A7980C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A79864.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A798C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A7998C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A79A84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A79B60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A79BA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A7A0D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A7A124.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A7A2EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A7A360.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/EnJso2_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A7AA48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A7AA9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/EnJso2_Draw.s")
