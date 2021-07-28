#include "z_dm_stk.h"

#define FLAGS 0x02000030

#define THIS ((DmStk*)thisx)

void DmStk_Init(Actor* thisx, GlobalContext* globalCtx);
void DmStk_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmStk_Update(Actor* thisx, GlobalContext* globalCtx);
void DmStk_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Dm_Stk_InitVars = {
    ACTOR_DM_STK,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_STK,
    sizeof(DmStk),
    (ActorFunc)DmStk_Init,
    (ActorFunc)DmStk_Destroy,
    (ActorFunc)DmStk_Update,
    (ActorFunc)DmStk_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80AA35A0 = {
    { COLTYPE_HIT1, AT_NONE, AC_ON | AC_HARD | AC_TYPE_PLAYER | AC_TYPE_ENEMY, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 14, 38, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_80AA35CC = { 1, 0, 0, 0, MASS_IMMOVABLE };

// static DamageTable sDamageTable = {
static DamageTable D_80AA35D8 = {
    /* Deku Nut       */ DMG_ENTRY(1, 0xF),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(1, 0xF),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(1, 0xF),
    /* Hookshot       */ DMG_ENTRY(1, 0xF),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0xF),
    /* Ice arrow      */ DMG_ENTRY(1, 0xF),
    /* Light arrow    */ DMG_ENTRY(1, 0xF),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, 0xF),
    /* Zora barrier   */ DMG_ENTRY(1, 0xF),
    /* Normal shield  */ DMG_ENTRY(1, 0xF),
    /* Light ray      */ DMG_ENTRY(1, 0xF),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(1, 0xF),
    /* Normal Roll    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(1, 0xF),
    /* Unblockable    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(1, 0xF),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

#endif

extern ColliderCylinderInit D_80AA35A0;
extern CollisionCheckInfoInit2 D_80AA35CC;
extern DamageTable D_80AA35D8;

extern UNK_TYPE D_06006BB0;
extern UNK_TYPE D_0600AEC0;
extern UNK_TYPE D_06013328;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80A9FDB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80A9FE3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80A9FED8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA00CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA0100.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA0158.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA01C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA0264.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA0420.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA05F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA0634.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA066C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA071C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA076C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA09DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA0B08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA0DA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA0E1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA0E90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/DmStk_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/DmStk_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA16F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA1704.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA1714.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA17F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA18D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA192C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA1998.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA19EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA1A50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA1AC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA1AF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA1B9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA1C64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA1D1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA26CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA2720.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA27EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/DmStk_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA2B14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA2BC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA33A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/DmStk_Draw.s")
