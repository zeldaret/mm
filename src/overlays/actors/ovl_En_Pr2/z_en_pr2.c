#include "z_en_pr2.h"

#define FLAGS 0x00000015

#define THIS ((EnPr2*)thisx)

void EnPr2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPr2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPr2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPr2_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
// static DamageTable sDamageTable = {
static DamageTable D_80A75BC0 = {
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
    /* Fire arrow     */ DMG_ENTRY(1, 0xF),
    /* Ice arrow      */ DMG_ENTRY(1, 0xF),
    /* Light arrow    */ DMG_ENTRY(2, 0xF),
    /* Goron spikes   */ DMG_ENTRY(0, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(1, 0xF),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0x0),
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


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A75BE0 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_1, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x08, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 17, 32, -10, { 0, 0, 0 } },
};


const ActorInit En_Pr2_InitVars = {
    ACTOR_EN_PR2,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_PR,
    sizeof(EnPr2),
    (ActorFunc)EnPr2_Init,
    (ActorFunc)EnPr2_Destroy,
    (ActorFunc)EnPr2_Update,
    (ActorFunc)EnPr2_Draw,
};


extern DamageTable D_80A75BC0;
extern ColliderCylinderInit D_80A75BE0;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pr2_0x80A73FA0/EnPr2_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pr2_0x80A73FA0/EnPr2_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pr2_0x80A73FA0/func_80A7429C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pr2_0x80A73FA0/func_80A7436C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pr2_0x80A73FA0/func_80A74510.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pr2_0x80A73FA0/func_80A745C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pr2_0x80A73FA0/func_80A745FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pr2_0x80A73FA0/func_80A74888.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pr2_0x80A73FA0/func_80A748E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pr2_0x80A73FA0/func_80A74DEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pr2_0x80A73FA0/func_80A74E90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pr2_0x80A73FA0/func_80A751B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pr2_0x80A73FA0/func_80A75310.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pr2_0x80A73FA0/func_80A755D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pr2_0x80A73FA0/EnPr2_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pr2_0x80A73FA0/func_80A758E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pr2_0x80A73FA0/func_80A75950.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pr2_0x80A73FA0/func_80A759D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pr2_0x80A73FA0/EnPr2_Draw.asm")
