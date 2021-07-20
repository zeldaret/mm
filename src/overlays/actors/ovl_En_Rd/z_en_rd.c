#include "z_en_rd.h"

#define FLAGS 0x00000415

#define THIS ((EnRd*)thisx)

void EnRd_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRd_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRd_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRd_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0

const ActorInit En_Rd_InitVars = {
    ACTOR_EN_RD,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_RD,
    sizeof(EnRd),
    (ActorFunc)EnRd_Init,
    (ActorFunc)EnRd_Destroy,
    (ActorFunc)EnRd_Update,
    (ActorFunc)EnRd_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_808D70E0 = {
    { COLTYPE_HIT0, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7EFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 20, 70, 0, { 0, 0, 0 } },
};


// static DamageTable sDamageTable = {
static DamageTable D_808D710C = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(2, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(0, 0xD),
    /* Normal arrow   */ DMG_ENTRY(0, 0xD),
    /* UNK_DMG_0x06   */ DMG_ENTRY(2, 0xF),
    /* Hookshot       */ DMG_ENTRY(0, 0xD),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(0, 0xD),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(0, 0xD),
    /* Deku launch    */ DMG_ENTRY(2, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0xC),
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


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_808D712C[] = {
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -3500, ICHAIN_STOP),
};

#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/EnRd_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/EnRd_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D4190.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D41FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D4260.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D4308.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D43AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D45D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D4660.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D47DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D4868.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D49E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D4A90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D4B20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D4CA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D4DC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D4E60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D4FE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D506C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D53C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D5440.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D5660.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D56E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D586C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D58CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D5C54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D5CCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D5D88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D5DF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D5E98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D5F18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D6008.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D6054.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D60B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D6130.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D616C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D6200.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D6310.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D6388.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D64D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D65BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D66A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D6814.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D6A94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D6B64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/EnRd_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D6DA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D6DFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/EnRd_Draw.asm")
