#include "z_en_poh.h"

#define FLAGS 0x00001205

#define THIS ((EnPoh*)thisx)

void EnPoh_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPoh_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPoh_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPoh_Draw(Actor* thisx, GlobalContext* globalCtx);

/*

const ActorInit En_Poh_InitVars = {
    ACTOR_EN_POH,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_PO,
    sizeof(EnPoh),
    (ActorFunc)EnPoh_Init,
    (ActorFunc)EnPoh_Destroy,
    (ActorFunc)EnPoh_Update,
    (ActorFunc)EnPoh_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B2F680 = {
    { COLTYPE_HIT3, AT_NONE, AC_NONE | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CBFFFE, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 20, 40, 20, { 0, 0, 0 } },
};


// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_80B2F6AC[1] = {
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x08 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
        { 18, { { 0, 1400, 0 }, 10 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80B2F6D0 = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    1, D_80B2F6AC, // sJntSphElementsInit,
};


// static DamageTable sDamageTable = {
static DamageTable D_80B2F6E0 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0xF),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xE),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x0),
    /* Ice arrow      */ DMG_ENTRY(1, 0x0),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
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
static CollisionCheckInfoInit D_80B2F700 = { 3, 25, 50, 50 };


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B2F708[] = {
    ICHAIN_S8(hintId, 68, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 3200, ICHAIN_STOP),
};

*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/EnPoh_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/EnPoh_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2C910.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2C9B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2CA4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2CAA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2CB60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2CBBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2CD14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2CD64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2CEC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2CF28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2CFF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2D07C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2D0E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2D140.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2D2C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2D300.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2D5DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2D628.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2D694.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2D6EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2D76C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2D7D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2D924.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2D980.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2DAD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2DB44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2DC50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2DD2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2DDF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2E0B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2E180.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2E1D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2E230.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2E3B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2E3F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2E438.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2E55C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2E6C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2E8E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/EnPoh_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2ED14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2EDD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/EnPoh_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2F328.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Poh_0x80B2C6F0/func_80B2F37C.asm")
