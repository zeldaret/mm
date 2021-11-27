/*
 * File: z_en_hint_skb.c
 * Overlay: ovl_En_Hint_Skb
 * Description: Stalchild that gives hints in Oceanside Spider House
 */

#include "z_en_hint_skb.h"

#define FLAGS 0x00000019

#define THIS ((EnHintSkb*)thisx)

void EnHintSkb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHintSkb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHintSkb_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHintSkb_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80C1FE20(EnHintSkb* this, GlobalContext* globalCtx);
void func_80C1FE80(EnHintSkb* this, GlobalContext* globalCtx);
void func_80C1FF88(EnHintSkb* this, GlobalContext* globalCtx);
void func_80C200B8(EnHintSkb* this, GlobalContext* globalCtx);
void func_80C2016C(EnHintSkb* this, GlobalContext* globalCtx);
void func_80C20334(EnHintSkb* this, GlobalContext* globalCtx);
void func_80C204F0(EnHintSkb* this, GlobalContext* globalCtx);
void func_80C20590(EnHintSkb* this, GlobalContext* globalCtx);
void func_80C2069C(EnHintSkb* this, GlobalContext* globalCtx);
void func_80C2077C(EnHintSkb* this, GlobalContext* globalCtx);
void func_80C208D0(EnHintSkb* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Hint_Skb_InitVars = {
    ACTOR_EN_HINT_SKB,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_SKB,
    sizeof(EnHintSkb),
    (ActorFunc)EnHintSkb_Init,
    (ActorFunc)EnHintSkb_Destroy,
    (ActorFunc)EnHintSkb_Update,
    (ActorFunc)EnHintSkb_Draw,
};

// static ColliderJntSphElementInit sJntSphElementsInit[2] = {
static ColliderJntSphElementInit D_80C21C80[2] = {
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
static ColliderJntSphInit D_80C21CC8 = {
    { COLTYPE_HIT6, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    2, D_80C21C80, // sJntSphElementsInit,
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_80C21CD8 = { 2, 0, 0, 0, MASS_IMMOVABLE };

// static DamageTable sDamageTable = {
static DamageTable D_80C21CE4 = {
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
static InitChainEntry D_80C21E3C[] = {
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_STOP),
};

#endif

extern ColliderJntSphElementInit D_80C21C80[2];
extern ColliderJntSphInit D_80C21CC8;
extern CollisionCheckInfoInit2 D_80C21CD8;
extern DamageTable D_80C21CE4;
extern InitChainEntry D_80C21E3C[];

extern UNK_TYPE D_06002190;
extern UNK_TYPE D_06003584;
extern UNK_TYPE D_0600697C;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/EnHintSkb_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/EnHintSkb_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C1FE0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C1FE20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C1FE30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C1FE80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C1FF30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C1FF88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C2003C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C200B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C2011C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C2016C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C20274.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C20334.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C20484.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C204F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C20540.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C20590.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C2066C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C2069C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C2075C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C2077C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C208BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C208D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C20A74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C20B88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C20C24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C20D64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C20E90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C21250.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C21320.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C21414.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C21468.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C215E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/EnHintSkb_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C21858.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/func_80C219D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hint_Skb/EnHintSkb_Draw.s")
