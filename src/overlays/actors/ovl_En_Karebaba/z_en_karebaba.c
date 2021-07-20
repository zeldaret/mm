#include "z_en_karebaba.h"

#define FLAGS 0x00000005

#define THIS ((EnKarebaba*)thisx)

void EnKarebaba_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKarebaba_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKarebaba_Update(Actor* thisx, GlobalContext* globalCtx);
void EnKarebaba_Draw(Actor* thisx, GlobalContext* globalCtx);

/*

const ActorInit En_Karebaba_InitVars = {
    ACTOR_EN_KAREBABA,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_DEKUBABA,
    sizeof(EnKarebaba),
    (ActorFunc)EnKarebaba_Init,
    (ActorFunc)EnKarebaba_Destroy,
    (ActorFunc)EnKarebaba_Update,
    (ActorFunc)EnKarebaba_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_808F2DA0 = {
    { COLTYPE_HARD, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 7, 25, 0, { 0, 0, 0 } },
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_808F2DCC = {
    { COLTYPE_HARD, AT_ON | AT_TYPE_ENEMY, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x04 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_WOOD, BUMP_NONE, OCELEM_ON, },
    { 4, 25, 0, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit D_808F2DF8 = { 1, 15, 80, MASS_HEAVY };


// static DamageTable sDamageTable = {
static DamageTable D_808F2E00 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(3, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(2, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
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


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_808F2E20[] = {
    ICHAIN_F32(targetArrowOffset, 2500, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, 1, ICHAIN_STOP),
};

*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/EnKarebaba_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/EnKarebaba_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F1374.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F13FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F152C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F155C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F15B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F1648.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F169C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F16FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F1778.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F1878.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F190C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F1A3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F1A58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F1BF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F1C84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F1FAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F200C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F20FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F21A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F220C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F228C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F238C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F241C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F24F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F254C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/EnKarebaba_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F280C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/EnKarebaba_Draw.asm")
