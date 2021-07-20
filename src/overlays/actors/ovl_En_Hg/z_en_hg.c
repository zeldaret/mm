#include "z_en_hg.h"

#define FLAGS 0x02100019

#define THIS ((EnHg*)thisx)

void EnHg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHg_Draw(Actor* thisx, GlobalContext* globalCtx);

/*

const ActorInit En_Hg_InitVars = {
    ACTOR_EN_HG,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_HARFGIBUD,
    sizeof(EnHg),
    (ActorFunc)EnHg_Init,
    (ActorFunc)EnHg_Destroy,
    (ActorFunc)EnHg_Update,
    (ActorFunc)EnHg_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BCFFB0 = {
    { COLTYPE_HIT0, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 18, 46, 0, { 0, 0, 0 } },
};


// static DamageTable sDamageTable = {
static DamageTable D_80BCFFDC = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0xD),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(3, 0xC),
    /* Normal arrow   */ DMG_ENTRY(3, 0xC),
    /* UNK_DMG_0x06   */ DMG_ENTRY(2, 0xF),
    /* Hookshot       */ DMG_ENTRY(0, 0x1),
    /* Goron punch    */ DMG_ENTRY(2, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(3, 0x2),
    /* Ice arrow      */ DMG_ENTRY(3, 0x3),
    /* Light arrow    */ DMG_ENTRY(1, 0x4),
    /* Goron spikes   */ DMG_ENTRY(2, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(1, 0xD),
    /* Deku launch    */ DMG_ENTRY(2, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
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


// sColChkInfoInit
static CollisionCheckInfoInit2 D_80BCFFFC = { 0, 0, 0, 0, 128 };

*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/EnHg_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/EnHg_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCF354.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCF398.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCF468.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCF4AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCF5F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCF634.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCF68C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCF6D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCF710.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCF778.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCF7D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCF88C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCF8A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCF93C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCF95C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCFC0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/EnHg_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCFE54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCFE70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/EnHg_Draw.asm")
