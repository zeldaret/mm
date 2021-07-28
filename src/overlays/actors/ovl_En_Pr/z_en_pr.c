#include "z_en_pr.h"

#define FLAGS 0x00000015

#define THIS ((EnPr*)thisx)

void EnPr_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPr_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPr_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPr_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
// static DamageTable sDamageTable = {
static DamageTable D_80A338A0 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(0, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0xF),
    /* Goron punch    */ DMG_ENTRY(0, 0x0),
    /* Sword          */ DMG_ENTRY(0, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(0, 0x0),
    /* Ice arrow      */ DMG_ENTRY(0, 0x0),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(0, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(1, 0x5),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(0, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

const ActorInit En_Pr_InitVars = {
    ACTOR_EN_PR,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_PR,
    sizeof(EnPr),
    (ActorFunc)EnPr_Init,
    (ActorFunc)EnPr_Destroy,
    (ActorFunc)EnPr_Update,
    (ActorFunc)EnPr_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A338F4 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK4, { 0x20000000, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 18, 20, 5, { 0, 0, 0 } },
};

#endif

extern DamageTable D_80A338A0;
extern ColliderCylinderInit D_80A338F4;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/EnPr_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/EnPr_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A3242C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A324E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A325E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A326F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A32740.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A32854.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A3289C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A3295C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A32984.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A32A40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A32AF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A32B20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A32CDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A32D28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A32E60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A32EA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A32F48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A33098.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/EnPr_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A3357C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A335B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/EnPr_Draw.s")
