/*
 * File: z_en_tg.c
 * Overlay: ovl_En_Tg
 * Description: Target Game (Honey & Darling)
 */

#include "z_en_tg.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnTg*)thisx)

void EnTg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTg_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_8098FA70(EnTg* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Tg_InitVars = {
    ACTOR_EN_TG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MU,
    sizeof(EnTg),
    (ActorFunc)EnTg_Init,
    (ActorFunc)EnTg_Destroy,
    (ActorFunc)EnTg_Update,
    (ActorFunc)EnTg_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809901C0 = {
    { COLTYPE_HIT0, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 18, 64, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_809901EC = { 0, 0, 0, 0, MASS_IMMOVABLE };

// static DamageTable sDamageTable = {
static DamageTable D_809901F8 = {
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

extern ColliderCylinderInit D_809901C0;
extern CollisionCheckInfoInit2 D_809901EC;
extern DamageTable D_809901F8;

extern UNK_TYPE D_0600B0E0;
extern UNK_TYPE D_0600B2B0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098F800.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098F8A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098F928.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/EnTg_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/EnTg_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098FA70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/EnTg_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098FBB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098FBD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/EnTg_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098FD50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098FEA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8099000C.s")
