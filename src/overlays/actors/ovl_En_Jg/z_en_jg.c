#include "z_en_jg.h"

#define FLAGS 0x00000019

#define THIS ((EnJg*)thisx)

void EnJg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnJg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnJg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnJg_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0

const ActorInit En_Jg_InitVars = {
    ACTOR_EN_JG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_JG,
    sizeof(EnJg),
    (ActorFunc)EnJg_Init,
    (ActorFunc)EnJg_Destroy,
    (ActorFunc)EnJg_Update,
    (ActorFunc)EnJg_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B75820 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 60, 80, 0, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_80B7584C = { 0, 50, 80, 0, MASS_IMMOVABLE };


// static DamageTable sDamageTable = {
static DamageTable D_80B75858 = {
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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B73A90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B73AE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B73B98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B73C58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B73DF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B73E3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B73F1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B7406C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B7408C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B74134.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B741F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B742F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B74440.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B74550.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B747C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B74840.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B749D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B74AD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B74B54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B74BC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B74E5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B750A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B7517C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B751F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/EnJg_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/EnJg_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/EnJg_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B75658.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B75708.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/EnJg_Draw.asm")
