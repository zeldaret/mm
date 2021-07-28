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

extern ColliderCylinderInit D_80BA82A0;
extern DamageTable D_80BA82CC;
extern CollisionCheckInfoInit2 D_80BA82EC;
extern InitChainEntry D_80BA82FC[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA5400.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/EnRailgibud_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/EnRailgibud_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA57A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA57F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA59F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA5A34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA5AF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA5B64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA5DBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA5E18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA6054.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA60B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA6158.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA61A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA6284.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA62D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA6440.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA64AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA6584.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA6604.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA6664.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA66C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA6800.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA6974.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA6B30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA6B9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA6D10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA6DAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA6DF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA7088.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA71E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA7234.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA7388.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA7434.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA7578.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA76C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/EnRailgibud_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA7878.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA789C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA78F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/EnRailgibud_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA7B6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA7C78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA7CF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA7D04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA7D14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA7D30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA7DC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA8050.s")
