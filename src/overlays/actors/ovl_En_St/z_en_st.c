#include "z_en_st.h"

#define FLAGS 0x01004035

#define THIS ((EnSt*)thisx)

void EnSt_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSt_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSt_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_St_InitVars = {
    ACTOR_EN_ST,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_ST,
    sizeof(EnSt),
    (ActorFunc)EnSt_Init,
    (ActorFunc)EnSt_Destroy,
    (ActorFunc)EnSt_Update,
    (ActorFunc)NULL,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_808A75B0 = {
    { COLTYPE_HIT2, AT_ON | AT_TYPE_ENEMY, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0x800C3829, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 18, 48, -20, { 0, 0, 0 } },
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_808A75DC = {
    { COLTYPE_HIT2, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x77C3C7D6, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 18, 48, -20, { 0, 0, 0 } },
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_808A7608 = {
    { COLTYPE_METAL, AT_NONE, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK2, { 0x00000000, 0x00, 0x00 }, { 0x77C3C7D6, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 18, 48, -20, { 0, 0, 0 } },
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_808A7634 = {
    { COLTYPE_HIT2, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x800C3829, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 18, 48, -20, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_808A7660 = { 2, 0, 0, 0, MASS_IMMOVABLE };


// static DamageTable sDamageTable = {
static DamageTable D_808A766C = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x5),
    /* Normal shield  */ DMG_ENTRY(1, 0x0),
    /* Light ray      */ DMG_ENTRY(1, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0x0),
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


extern ColliderCylinderInit D_808A75B0;
extern ColliderCylinderInit D_808A75DC;
extern ColliderCylinderInit D_808A7608;
extern ColliderCylinderInit D_808A7634;
extern CollisionCheckInfoInit2 D_808A7660;
extern DamageTable D_808A766C;
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A5050.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A52A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A54B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A576C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A5988.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A5AF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A5BEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A5CCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A5D7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A5DCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A5F28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A6064.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A60E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A61F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A6220.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A63E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A6468.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A650C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A6580.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A6A3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A6A78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A6C04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A6D84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A6E24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A701C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/EnSt_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/EnSt_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/EnSt_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A73E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A7478.s")
