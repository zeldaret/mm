#include "z_en_gk.h"

#define FLAGS 0x00000009

#define THIS ((EnGk*)thisx)

void EnGk_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGk_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGk_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGk_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Gk_InitVars = {
    ACTOR_EN_GK,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_GK,
    sizeof(EnGk),
    (ActorFunc)EnGk_Init,
    (ActorFunc)EnGk_Destroy,
    (ActorFunc)EnGk_Update,
    (ActorFunc)EnGk_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B53210 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 24, 32, 0, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_80B5323C = { 0, 24, 32, 0, MASS_IMMOVABLE };


// static DamageTable sDamageTable = {
static DamageTable D_80B53248 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(0, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(0, 0x0),
    /* Zora boomerang */ DMG_ENTRY(0, 0x0),
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
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
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
    /* Powder Keg     */ DMG_ENTRY(0, 0x0),
};


extern ColliderCylinderInit D_80B53210;
extern CollisionCheckInfoInit2 D_80B5323C;
extern DamageTable D_80B53248;
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B50410.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B50710.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B507A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B50854.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B50954.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B509A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B50B38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B50C78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B50E14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B50ED4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B5100C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B5123C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B51308.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B51398.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B51410.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B51510.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B51698.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B51760.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B51970.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B51B40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B51D9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B51EA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B51FD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B5202C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B5216C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B521E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B5227C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B52340.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B52430.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B5253C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B525E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B52654.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/EnGk_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/EnGk_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/EnGk_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B52AD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B52AF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B52D8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/EnGk_Draw.s")
