#include "z_en_skb.h"

#define FLAGS 0x00000005

#define THIS ((EnSkb*)thisx)

void EnSkb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSkb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSkb_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSkb_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
// static ColliderJntSphElementInit sJntSphElementsInit[2] = {
static ColliderJntSphElementInit D_80997498[2] = {
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
static ColliderJntSphInit D_809974E0 = {
    { COLTYPE_HIT6, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    2, D_80997498, // sJntSphElementsInit,
};

// static DamageTable sDamageTable = {
static DamageTable D_809974F0 = {
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

const ActorInit En_Skb_InitVars = {
    ACTOR_EN_SKB,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_SKB,
    sizeof(EnSkb),
    (ActorFunc)EnSkb_Init,
    (ActorFunc)EnSkb_Destroy,
    (ActorFunc)EnSkb_Update,
    (ActorFunc)EnSkb_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80997548[] = {
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_STOP),
};

#endif

extern ColliderJntSphElementInit D_80997498[2];
extern ColliderJntSphInit D_809974E0;
extern DamageTable D_809974F0;
extern InitChainEntry D_80997548[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_809947B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_8099495C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_809949C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80994A30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80994A9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/EnSkb_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/EnSkb_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80994DA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80994E2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80994E94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80994F7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_8099504C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80995068.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80995190.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80995244.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_809952D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_8099533C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_809953E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_8099544C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_809954F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_8099556C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_8099571C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80995818.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_809958F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_8099599C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80995A30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80995A8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80995C24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80995C84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80995D3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80995DC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80995E08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80995E64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80995F98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_809960AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_809961E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80996284.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_809962D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_8099630C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_809963C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_809963D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80996474.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_809964A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_809964DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80996544.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80996594.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_8099672C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80996AD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80996BEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80996D68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/EnSkb_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80996F78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_809970D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/EnSkb_Draw.s")
