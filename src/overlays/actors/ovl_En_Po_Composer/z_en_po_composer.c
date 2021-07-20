#include "z_en_po_composer.h"

#define FLAGS 0x02100019

#define THIS ((EnPoComposer*)thisx)

void EnPoComposer_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPoComposer_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPoComposer_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPoComposer_Draw(Actor* thisx, GlobalContext* globalCtx);

/*

const ActorInit En_Po_Composer_InitVars = {
    ACTOR_EN_PO_COMPOSER,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_PO_COMPOSER,
    sizeof(EnPoComposer),
    (ActorFunc)EnPoComposer_Init,
    (ActorFunc)EnPoComposer_Destroy,
    (ActorFunc)EnPoComposer_Update,
    (ActorFunc)EnPoComposer_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BC6780 = {
    { COLTYPE_HIT3, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 20, 40, 20, { 0, 0, 0 } },
};


// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_80BC67AC[1] = {
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x08 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
        { 9, { { 0, -1500, 0 }, 10 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80BC67D0 = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    1, D_80BC67AC, // sJntSphElementsInit,
};


// sColChkInfoInit
static CollisionCheckInfoInit D_80BC67E0 = { 4, 25, 50, 40 };


// static DamageTable sDamageTable = {
static DamageTable D_80BC67E8 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(2, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(2, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x1),
    /* Normal arrow   */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(2, 0x0),
    /* Hookshot       */ DMG_ENTRY(2, 0x1),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(2, 0x0),
    /* Goron pound    */ DMG_ENTRY(4, 0x0),
    /* Fire arrow     */ DMG_ENTRY(2, 0x0),
    /* Ice arrow      */ DMG_ENTRY(2, 0x0),
    /* Light arrow    */ DMG_ENTRY(2, 0x0),
    /* Goron spikes   */ DMG_ENTRY(2, 0x0),
    /* Deku spin      */ DMG_ENTRY(2, 0x0),
    /* Deku bubble    */ DMG_ENTRY(2, 0x0),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(4, 0x0),
    /* Spin attack    */ DMG_ENTRY(2, 0x0),
    /* Sword beam     */ DMG_ENTRY(2, 0x0),
    /* Normal Roll    */ DMG_ENTRY(8, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(4, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(4, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0x0),
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80BC6958[] = {
    ICHAIN_F32(targetArrowOffset, 3200, ICHAIN_STOP),
};

*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/EnPoComposer_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/EnPoComposer_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC5250.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC5294.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC52D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC52F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC538C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC53A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC53B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC5404.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC552C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC5570.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC5580.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC55E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC562C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC5670.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC5680.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC56D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC5738.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC5780.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC57E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC5830.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC5898.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC58E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC59BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC59EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC5CC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC5D34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC5DEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC5FE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/EnPoComposer_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC60BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC617C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/EnPoComposer_Draw.asm")
