/*
 * File: z_en_ru.c
 * Overlay: ovl_En_Ru
 * Description: OoT's Adult Ruto (unused)
 */

#include "z_en_ru.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnRu*)thisx)

void EnRu_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRu_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRu_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRu_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A38DF4(EnRu* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Ru_InitVars = {
    ACTOR_EN_RU,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_RU2,
    sizeof(EnRu),
    (ActorFunc)EnRu_Init,
    (ActorFunc)EnRu_Destroy,
    (ActorFunc)EnRu_Update,
    (ActorFunc)EnRu_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A39450 = {
    { COLTYPE_HIT0, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 18, 64, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_80A3947C = { 0, 0, 0, 0, MASS_IMMOVABLE };

// static DamageTable sDamageTable = {
static DamageTable D_80A39488 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(0, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(0, 0x0),
    /* Zora boomerang */ DMG_ENTRY(0, 0x0),
    /* Normal arrow   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
    /* Goron punch    */ DMG_ENTRY(0, 0x0),
    /* Sword          */ DMG_ENTRY(0, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(0, 0x0),
    /* Ice arrow      */ DMG_ENTRY(0, 0x0),
    /* Light arrow    */ DMG_ENTRY(0, 0x0),
    /* Goron spikes   */ DMG_ENTRY(0, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x0),
    /* Deku bubble    */ DMG_ENTRY(0, 0x0),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0x0),
    /* Zora punch     */ DMG_ENTRY(0, 0x0),
    /* Spin attack    */ DMG_ENTRY(0, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0x0),
};

#endif

extern ColliderCylinderInit D_80A39450;
extern CollisionCheckInfoInit2 D_80A3947C;
extern DamageTable D_80A39488;

extern UNK_TYPE D_0600C700;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ru/func_80A389A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ru/func_80A38A68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ru/func_80A38B7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ru/func_80A38BF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ru/func_80A38C70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ru/func_80A38DF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ru/EnRu_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ru/EnRu_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ru/EnRu_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ru/func_80A38FB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ru/func_80A390F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ru/EnRu_Draw.s")
