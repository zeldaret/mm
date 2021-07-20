#include "z_en_bbfall.h"

#define FLAGS 0x00000215

#define THIS ((EnBbfall*)thisx)

void EnBbfall_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBbfall_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBbfall_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBbfall_Draw(Actor* thisx, GlobalContext* globalCtx);

/*

const ActorInit En_Bbfall_InitVars = {
    ACTOR_EN_BBFALL,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_BB,
    sizeof(EnBbfall),
    (ActorFunc)EnBbfall_Init,
    (ActorFunc)EnBbfall_Destroy,
    (ActorFunc)EnBbfall_Update,
    (ActorFunc)EnBbfall_Draw,
};


// static ColliderJntSphElementInit sJntSphElementsInit[3] = {
static ColliderJntSphElementInit D_808C0D30[3] = {
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x01, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x01, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_NONE, OCELEM_NONE, },
        { 0, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x01, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_NONE, OCELEM_NONE, },
        { 0, { { 0, 0, 0 }, 20 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_808C0D9C = {
    { COLTYPE_HIT3, AT_NONE | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    3, D_808C0D30, // sJntSphElementsInit,
};


// static DamageTable sDamageTable = {
static DamageTable D_808C0DAC = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xE),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x0),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x5),
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
static CollisionCheckInfoInit D_808C0DCC = { 2, 20, 40, 50 };


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_808C0DD4[] = {
    ICHAIN_S8(hintId, 36, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 10, ICHAIN_STOP),
};

*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/EnBbfall_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/EnBbfall_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BF344.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BF3B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BF438.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BF4B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BF514.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BF578.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BF5AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BF5E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BF734.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BF7A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BF830.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BF894.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BF8DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BFA18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BFA3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BFAB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BFB4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BFCCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BFE58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BFF8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808C00A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808C013C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808C0178.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808C01E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/EnBbfall_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808C07D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808C080C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/EnBbfall_Draw.asm")
