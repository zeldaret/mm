#include "z_en_racedog.h"

#define FLAGS 0x80000010

#define THIS ((EnRacedog*)thisx)

void EnRacedog_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRacedog_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRacedog_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRacedog_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Racedog_InitVars = {
    ACTOR_EN_RACEDOG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DOG,
    sizeof(EnRacedog),
    (ActorFunc)EnRacedog_Init,
    (ActorFunc)EnRacedog_Destroy,
    (ActorFunc)EnRacedog_Update,
    (ActorFunc)EnRacedog_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B25E98 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 13, 19, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_80B25EC4 = { 0, 0, 0, 0, 1 };

// static DamageTable sDamageTable = {
static DamageTable D_80B25ED0 = {
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
static InitChainEntry D_80B25FF0[] = {
    ICHAIN_F32(uncullZoneForward, 1000, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80B25E98;
extern CollisionCheckInfoInit2 D_80B25EC4;
extern DamageTable D_80B25ED0;
extern InitChainEntry D_80B25FF0[];

extern UNK_TYPE D_06000618;
extern UNK_TYPE D_060080F0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B24630.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B246F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B2478C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B248B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/EnRacedog_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/EnRacedog_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B24C14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B24CB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B24E14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B24F08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B251EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B252F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B2538C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B25448.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B25490.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B255AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B256BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/EnRacedog_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B2583C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B258D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B25A74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B25A90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/EnRacedog_Draw.s")
