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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80A9FDB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80A9FE3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80A9FED8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA00CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA0100.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA0158.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA01C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA0264.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA0420.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA05F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA0634.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA066C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA071C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA076C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA09DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA0B08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA0DA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA0E1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA0E90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/DmStk_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/DmStk_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA16F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA1704.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA1714.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA17F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA18D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA192C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA1998.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA19EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA1A50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA1AC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA1AF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA1B9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA1C64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA1D1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA26CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA2720.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA27EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/DmStk_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA2B14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA2BC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA33A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/DmStk_Draw.asm")
