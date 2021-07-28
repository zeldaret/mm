#include "z_en_rail_skb.h"

#define FLAGS 0x00000015

#define THIS ((EnRailSkb*)thisx)

void EnRailSkb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRailSkb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRailSkb_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRailSkb_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Rail_Skb_InitVars = {
    ACTOR_EN_RAIL_SKB,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_SKB,
    sizeof(EnRailSkb),
    (ActorFunc)EnRailSkb_Init,
    (ActorFunc)EnRailSkb_Destroy,
    (ActorFunc)EnRailSkb_Update,
    (ActorFunc)EnRailSkb_Draw,
};

// static ColliderJntSphElementInit sJntSphElementsInit[2] = {
static ColliderJntSphElementInit D_80B73408[2] = {
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x04 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_NONE, },
        { 15, { { 0, 0, 0 }, 10 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 20 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80B73450 = {
    { COLTYPE_HIT6, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    2, D_80B73408, // sJntSphElementsInit,
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_80B73460 = { 2, 0, 0, 0, MASS_IMMOVABLE };

// static DamageTable sDamageTable = {
static DamageTable D_80B7346C = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0xD),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(3, 0xC),
    /* Normal arrow   */ DMG_ENTRY(3, 0xC),
    /* UNK_DMG_0x06   */ DMG_ENTRY(2, 0xF),
    /* Hookshot       */ DMG_ENTRY(1, 0x1),
    /* Goron punch    */ DMG_ENTRY(2, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(3, 0x2),
    /* Ice arrow      */ DMG_ENTRY(3, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(1, 0xD),
    /* Deku launch    */ DMG_ENTRY(2, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0xB),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(2, 0x0),
    /* Normal Roll    */ DMG_ENTRY(4, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B73490[] = {
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_STOP),
};

#endif

extern ColliderJntSphElementInit D_80B73408[2];
extern ColliderJntSphInit D_80B73450;
extern CollisionCheckInfoInit2 D_80B73460;
extern DamageTable D_80B7346C;
extern InitChainEntry D_80B73490[];

extern UNK_TYPE D_060064E0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B708C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B70AB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B70B04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B70D24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/EnRailSkb_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/EnRailSkb_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B70FA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B70FF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B710AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B710E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B71114.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B7114C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B71228.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B7123C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B712FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B71314.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B71354.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B713A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B71488.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B714D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B7151C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B715AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B71650.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B716A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B717C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B717E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B718B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B718C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B71910.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B71954.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B71A08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B71A58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B71B6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B71BB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B71D8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B71DF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B71EA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B71F3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B72100.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B72190.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B723F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B72430.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B725C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B726B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B72830.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B7285C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B72880.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B72970.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/EnRailSkb_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B72E88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B7302C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/EnRailSkb_Draw.s")
