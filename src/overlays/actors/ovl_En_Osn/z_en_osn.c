#include "z_en_osn.h"

#define FLAGS 0x00000019

#define THIS ((EnOsn*)thisx)

void EnOsn_Init(Actor* thisx, GlobalContext* globalCtx);
void EnOsn_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnOsn_Update(Actor* thisx, GlobalContext* globalCtx);
void EnOsn_Draw(Actor* thisx, GlobalContext* globalCtx);

/*

const ActorInit En_Osn_InitVars = {
    ACTOR_EN_OSN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_OSN,
    sizeof(EnOsn),
    (ActorFunc)EnOsn_Init,
    (ActorFunc)EnOsn_Destroy,
    (ActorFunc)EnOsn_Update,
    (ActorFunc)EnOsn_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80AD2518 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 30, 40, 0, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_80AD2544 = { 0, 0, 0, 0, MASS_IMMOVABLE };


// static DamageTable sDamageTable = {
static DamageTable D_80AD2550 = {
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


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80AD2570[] = {
    ICHAIN_U8(targetMode, 0, ICHAIN_STOP),
};

*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD0830.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD08B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD0998.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD0A24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD0AB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD0B38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD0E10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD10FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD1398.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD144C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD14C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD1634.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD16A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD19A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD1A4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/EnOsn_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/EnOsn_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/EnOsn_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD1DA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD1E28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/EnOsn_Draw.asm")
