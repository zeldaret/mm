#include "z_en_jso.h"

#define FLAGS 0x00000015

#define THIS ((EnJso*)thisx)

void EnJso_Init(Actor* thisx, GlobalContext* globalCtx);
void EnJso_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnJso_Update(Actor* thisx, GlobalContext* globalCtx);

/*

// static DamageTable sDamageTable = {
static DamageTable D_809B0F48 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x1),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(2, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x5),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};


const ActorInit En_Jso_InitVars = {
    ACTOR_EN_JSO,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_JSO,
    sizeof(EnJso),
    (ActorFunc)EnJso_Init,
    (ActorFunc)EnJso_Destroy,
    (ActorFunc)EnJso_Update,
    (ActorFunc)NULL,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809B0F88 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x08, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 22, 55, 0, { 0, 0, 0 } },
};


// static ColliderQuadInit sQuadInit = {
static ColliderQuadInit D_809B0FB4 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_NONE, OC1_NONE, OC2_NONE, COLSHAPE_QUAD, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x04, 0x08 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL | TOUCH_UNK7, BUMP_NONE, OCELEM_NONE, },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/EnJso_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/EnJso_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809ADBC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809ADC7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809ADCB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AE754.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AE87C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AE9B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AEA08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AECA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AED00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AED54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AEDAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AEE44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AEEC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AF064.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AF110.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AF28C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AF2F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AF368.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AF3C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AF3FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AF440.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AF470.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AF53C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AF5F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AF714.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AF76C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AF7F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AF8D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AF99C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AFA58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AFAF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AFC10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AFE38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809B0034.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/EnJso_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809B0734.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809B0820.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809B0B70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809B0BB0.asm")
