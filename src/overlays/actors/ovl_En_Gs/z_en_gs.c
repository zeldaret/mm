#include "z_en_gs.h"

#define FLAGS 0x02000019

#define THIS ((EnGs*)thisx)

void EnGs_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGs_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGs_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGs_Draw(Actor* thisx, GlobalContext* globalCtx);

/*

const ActorInit En_Gs_InitVars = {
    ACTOR_EN_GS,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_GS,
    sizeof(EnGs),
    (ActorFunc)EnGs_Init,
    (ActorFunc)EnGs_Destroy,
    (ActorFunc)EnGs_Update,
    (ActorFunc)EnGs_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_8099A3A0 = {
    { COLTYPE_METAL, AT_NONE, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 21, 48, 0, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_8099A3CC = { 0, 0, 0, 0, MASS_IMMOVABLE };


// static DamageTable sDamageTable = {
static DamageTable D_8099A3D8 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0xE),
    /* Deku Stick     */ DMG_ENTRY(0, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(0, 0xC),
    /* Zora boomerang */ DMG_ENTRY(0, 0xE),
    /* Normal arrow   */ DMG_ENTRY(0, 0xE),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xE),
    /* Goron punch    */ DMG_ENTRY(0, 0xD),
    /* Sword          */ DMG_ENTRY(0, 0xF),
    /* Goron pound    */ DMG_ENTRY(0, 0xD),
    /* Fire arrow     */ DMG_ENTRY(0, 0xB),
    /* Ice arrow      */ DMG_ENTRY(0, 0xB),
    /* Light arrow    */ DMG_ENTRY(0, 0xB),
    /* Goron spikes   */ DMG_ENTRY(0, 0xE),
    /* Deku spin      */ DMG_ENTRY(0, 0xE),
    /* Deku bubble    */ DMG_ENTRY(0, 0xD),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0xE),
    /* Zora punch     */ DMG_ENTRY(0, 0xE),
    /* Spin attack    */ DMG_ENTRY(0, 0xE),
    /* Sword beam     */ DMG_ENTRY(0, 0xE),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0xC),
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8099A404[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80997A90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80997AFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/EnGs_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/EnGs_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80997D14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80997D38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80997DEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80997E4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80997FF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80998040.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_8099807C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80998300.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80998334.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_809984F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_809985B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80998704.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_8099874C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_809989B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_809989F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80998A48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80998BBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80998D44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80998F9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80999584.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_809995A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80999A8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80999AC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80999B34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80999BC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/EnGs_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/EnGs_Draw.asm")
