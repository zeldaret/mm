/*
 * File: z_en_minideath.c
 * Overlay: ovl_En_Minideath
 * Description: Gomess's bats
 */

#include "z_en_minideath.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_UNFRIENDLY | ACTOR_FLAG_10)

#define THIS ((EnMinideath*)thisx)

void EnMinideath_Init(Actor* thisx, PlayState* play);
void EnMinideath_Destroy(Actor* thisx, PlayState* play);
void EnMinideath_Update(Actor* thisx, PlayState* play);

void func_808CA860(EnMinideath* this, PlayState* play);
void func_808CA8F4(EnMinideath* this, PlayState* play);
void func_808CAAEC(EnMinideath* this, PlayState* play);
void func_808CABB0(EnMinideath* this, PlayState* play);
void func_808CACD8(EnMinideath* this, PlayState* play);
void func_808CAE18(EnMinideath* this, PlayState* play);
void func_808CAF68(EnMinideath* this, PlayState* play);
void func_808CB094(EnMinideath* this, PlayState* play);
void func_808CB22C(EnMinideath* this, PlayState* play);
void func_808CB454(EnMinideath* this, PlayState* play);
void func_808CB59C(EnMinideath* this, PlayState* play);
void func_808CB6D4(EnMinideath* this, PlayState* play);
void func_808CB7CC(EnMinideath* this, PlayState* play);

#if 0
ActorInit En_Minideath_InitVars = {
    /**/ ACTOR_EN_MINIDEATH,
    /**/ ACTORCAT_ENEMY,
    /**/ FLAGS,
    /**/ OBJECT_DEATH,
    /**/ sizeof(EnMinideath),
    /**/ EnMinideath_Init,
    /**/ EnMinideath_Destroy,
    /**/ EnMinideath_Update,
    /**/ NULL,
};

// static ColliderJntSphElementInit sJntSphElementsInit[3] = {
static ColliderJntSphElementInit D_808CBF50[3] = {
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_808CBFBC = {
    { COLTYPE_NONE, AT_NONE | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_NONE | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    ARRAY_COUNT(sJntSphElementsInit), D_808CBF50, // sJntSphElementsInit,
};

// static DamageTable sDamageTable = {
static DamageTable D_808CBFCC = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(1, 0x5),
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

// sColChkInfoInit
static CollisionCheckInfoInit D_808CBFEC = { 1, 15, 30, 10 };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_808CBFF4[] = {
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_STOP),
};

#endif

extern ColliderJntSphElementInit D_808CBF50[3];
extern ColliderJntSphInit D_808CBFBC;
extern DamageTable D_808CBFCC;
extern CollisionCheckInfoInit D_808CBFEC;
extern InitChainEntry D_808CBFF4[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/EnMinideath_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/EnMinideath_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CA268.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CA308.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CA34C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CA458.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CA7D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CA860.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CA8E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CA8F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CAAC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CAAEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CAB90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CABB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CAC54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CACD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CAE00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CAE18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CAF08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CAF68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CB07C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CB094.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CB0C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CB22C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CB418.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CB454.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CB524.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CB59C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CB6A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CB6D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CB7B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CB7CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CB810.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CB8F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/EnMinideath_Update.s")
