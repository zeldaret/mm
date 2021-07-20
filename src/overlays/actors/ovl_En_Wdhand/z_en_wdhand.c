#include "z_en_wdhand.h"

#define FLAGS 0x00000005

#define THIS ((EnWdhand*)thisx)

void EnWdhand_Init(Actor* thisx, GlobalContext* globalCtx);
void EnWdhand_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnWdhand_Update(Actor* thisx, GlobalContext* globalCtx);
void EnWdhand_Draw(Actor* thisx, GlobalContext* globalCtx);

/*

const ActorInit En_Wdhand_InitVars = {
    ACTOR_EN_WDHAND,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_WDHAND,
    sizeof(EnWdhand),
    (ActorFunc)EnWdhand_Init,
    (ActorFunc)EnWdhand_Destroy,
    (ActorFunc)EnWdhand_Update,
    (ActorFunc)EnWdhand_Draw,
};


// static ColliderJntSphElementInit sJntSphElementsInit[7] = {
static ColliderJntSphElementInit D_80AF63E0[7] = {
    {
        { ELEMTYPE_UNK1, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_ON, OCELEM_ON, },
        { 50, { { 0, 575, 0 }, 10 }, 100 },
    },
    {
        { ELEMTYPE_UNK1, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_ON, OCELEM_ON, },
        { 50, { { 0, 1725, 0 }, 10 }, 100 },
    },
    {
        { ELEMTYPE_UNK1, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_ON, OCELEM_ON, },
        { 50, { { 0, 575, 0 }, 10 }, 100 },
    },
    {
        { ELEMTYPE_UNK1, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_ON, OCELEM_ON, },
        { 50, { { 0, 1725, 0 }, 10 }, 100 },
    },
    {
        { ELEMTYPE_UNK1, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_ON, OCELEM_ON, },
        { 50, { { 0, 575, 0 }, 10 }, 100 },
    },
    {
        { ELEMTYPE_UNK1, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_ON, OCELEM_ON, },
        { 50, { { 0, 1725, 0 }, 10 }, 100 },
    },
    {
        { ELEMTYPE_UNK1, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_ON, OCELEM_ON, },
        { 50, { { 0, 1000, 0 }, 15 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80AF64DC = {
    { COLTYPE_HIT0, AT_NONE | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    7, D_80AF63E0, // sJntSphElementsInit,
};


// sColChkInfoInit
static CollisionCheckInfoInit D_80AF64EC = { 1, 25, 25, MASS_HEAVY };


// static DamageTable sDamageTable = {
static DamageTable D_80AF64F4 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(0, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
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
    /* Zora barrier   */ DMG_ENTRY(1, 0x0),
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
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};

*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/EnWdhand_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/EnWdhand_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF4608.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF4670.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF46F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF488C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF48D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF4964.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF4A88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF4C18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF4C64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF4ED0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF4F30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF4F6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF4FF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF5130.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF520C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF5650.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF56A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF5820.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF5E3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/EnWdhand_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF5FE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/EnWdhand_Draw.asm")
