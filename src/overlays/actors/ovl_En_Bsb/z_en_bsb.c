#include "z_en_bsb.h"

#define FLAGS 0x02000035

#define THIS ((EnBsb*)thisx)

void EnBsb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBsb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBsb_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBsb_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0

// static ColliderJntSphElementInit sJntSphElementsInit[7] = {
static ColliderJntSphElementInit D_80C0F8D4[7] = {
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 10, { { 1000, 400, 0 }, 40 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x04, 0x08 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 9, { { 0, 700, 200 }, 35 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 6, { { 100, 600, 0 }, 35 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { 3, { { 400, 200, 0 }, 40 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 13, { { 700, -100, 0 }, 35 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 16, { { 200, 300, 0 }, 30 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 19, { { 200, 300, 0 }, 30 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80C0F9D0 = {
    { COLTYPE_HIT6, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    7, D_80C0F8D4, // sJntSphElementsInit,
};


// static DamageTable sDamageTable = {
static DamageTable D_80C0F9E0 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0xD),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xE),
    /* Zora boomerang */ DMG_ENTRY(0, 0xF),
    /* Normal arrow   */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(1, 0xD),
    /* Sword          */ DMG_ENTRY(1, 0xD),
    /* Goron pound    */ DMG_ENTRY(1, 0xD),
    /* Fire arrow     */ DMG_ENTRY(0, 0x2),
    /* Ice arrow      */ DMG_ENTRY(0, 0x3),
    /* Light arrow    */ DMG_ENTRY(0, 0x4),
    /* Goron spikes   */ DMG_ENTRY(0, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0xC),
    /* Deku bubble    */ DMG_ENTRY(0, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xE),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(1, 0x5),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xD),
    /* Spin attack    */ DMG_ENTRY(1, 0xD),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xD),
};


const ActorInit En_Bsb_InitVars = {
    ACTOR_EN_BSB,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_BSB,
    sizeof(EnBsb),
    (ActorFunc)EnBsb_Init,
    (ActorFunc)EnBsb_Destroy,
    (ActorFunc)EnBsb_Update,
    (ActorFunc)EnBsb_Draw,
};

#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0B290.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0B31C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/EnBsb_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/EnBsb_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0B888.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0B970.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0BA58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0BC30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0BE1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0BF2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0BFE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0C0F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0C238.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0C32C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0C364.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0C430.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0C484.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0C610.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0C6A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0C86C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0C8EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0CA28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0CB3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0CCCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0CD04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0CD90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0CDE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0CF4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0CFDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0D00C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0D10C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0D214.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0D27C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0D334.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0D384.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0D3C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0D51C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0D964.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0D9B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0DA58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0DB18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0E178.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0E1C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0E3B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0E480.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0E4FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0E618.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0E9CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/EnBsb_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0EEA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0F078.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0F170.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/EnBsb_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0F544.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0F640.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bsb_0x80C0B290/func_80C0F758.asm")
