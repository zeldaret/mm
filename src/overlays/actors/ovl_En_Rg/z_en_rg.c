#include "z_en_rg.h"

#define FLAGS 0x80000010

#define THIS ((EnRg*)thisx)

void EnRg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRg_Draw(Actor* thisx, GlobalContext* globalCtx);

/*

const ActorInit En_Rg_InitVars = {
    ACTOR_EN_RG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_OF1D_MAP,
    sizeof(EnRg),
    (ActorFunc)EnRg_Init,
    (ActorFunc)EnRg_Destroy,
    (ActorFunc)EnRg_Update,
    (ActorFunc)EnRg_Draw,
};


// static ColliderSphereInit sSphereInit = {
static ColliderSphereInit D_80BF5760 = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_PLAYER | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_SPHERE, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 0, { { 0, 0, 0 }, 20 }, 100 },
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BF578C = {
    { COLTYPE_HIT1, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 20, 62, 0, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_80BF57B8 = { 0, 0, 0, 0, MASS_IMMOVABLE };


// static DamageTable sDamageTable = {
static DamageTable D_80BF57C4 = {
    /* Deku Nut       */ DMG_ENTRY(1, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0x0),
    /* Ice arrow      */ DMG_ENTRY(1, 0x0),
    /* Light arrow    */ DMG_ENTRY(1, 0x0),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, 0x0),
    /* Zora barrier   */ DMG_ENTRY(1, 0x0),
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

*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF3920.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF3C64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF3DA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF3DC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF3E88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF3ED4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF3F14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF3FF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF4024.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF409C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF40F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF416C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF4220.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF42BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF43FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF4560.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF45B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF47AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF4934.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF4964.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF4AB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF4D64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF4DA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF4EBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF4FC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/EnRg_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/EnRg_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/EnRg_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF547C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF5588.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/EnRg_Draw.asm")
