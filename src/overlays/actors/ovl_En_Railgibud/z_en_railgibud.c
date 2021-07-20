#include "z_en_railgibud.h"

#define FLAGS 0x00000415

#define THIS ((EnRailgibud*)thisx)

void EnRailgibud_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRailgibud_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRailgibud_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRailgibud_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0

const ActorInit En_Railgibud_InitVars = {
    ACTOR_EN_RAILGIBUD,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_RD,
    sizeof(EnRailgibud),
    (ActorFunc)EnRailgibud_Init,
    (ActorFunc)EnRailgibud_Destroy,
    (ActorFunc)EnRailgibud_Update,
    (ActorFunc)EnRailgibud_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BA82A0 = {
    { COLTYPE_HIT0, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7EFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 20, 70, 0, { 0, 0, 0 } },
};


// static DamageTable sDamageTable = {
static DamageTable D_80BA82CC = {
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


// sColChkInfoInit
static CollisionCheckInfoInit2 D_80BA82EC = { 8, 0, 0, 0, MASS_IMMOVABLE };


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80BA82FC[] = {
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -3500, ICHAIN_STOP),
};

#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA5400.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/EnRailgibud_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/EnRailgibud_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA57A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA57F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA59F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA5A34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA5AF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA5B64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA5DBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA5E18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA6054.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA60B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA6158.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA61A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA6284.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA62D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA6440.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA64AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA6584.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA6604.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA6664.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA66C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA6800.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA6974.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA6B30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA6B9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA6D10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA6DAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA6DF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA7088.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA71E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA7234.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA7388.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA7434.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA7578.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA76C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/EnRailgibud_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA7878.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA789C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA78F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/EnRailgibud_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA7B6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA7C78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA7CF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA7D04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA7D14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA7D30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA7DC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA8050.asm")
