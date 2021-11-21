/*
 * File: z_en_geg.c
 * Overlay: ovl_En_Geg
 * Description: Goron With Don Gero's Mask
 */

#include "z_en_geg.h"

#define FLAGS 0x00000019

#define THIS ((EnGeg*)thisx)

void EnGeg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGeg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGeg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGeg_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BB217C(EnGeg* this, GlobalContext* globalCtx);
void func_80BB221C(EnGeg* this, GlobalContext* globalCtx);
void func_80BB2520(EnGeg* this, GlobalContext* globalCtx);
void func_80BB26EC(EnGeg* this, GlobalContext* globalCtx);
void func_80BB27D4(EnGeg* this, GlobalContext* globalCtx);
void func_80BB2944(EnGeg* this, GlobalContext* globalCtx);
void func_80BB2A54(EnGeg* this, GlobalContext* globalCtx);
void func_80BB2B1C(EnGeg* this, GlobalContext* globalCtx);
void func_80BB2E00(EnGeg* this, GlobalContext* globalCtx);
void func_80BB2F7C(EnGeg* this, GlobalContext* globalCtx);
void func_80BB30B4(EnGeg* this, GlobalContext* globalCtx);
void func_80BB31B8(EnGeg* this, GlobalContext* globalCtx);
void func_80BB32AC(EnGeg* this, GlobalContext* globalCtx);
void func_80BB3318(EnGeg* this, GlobalContext* globalCtx);
void func_80BB347C(EnGeg* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Geg_InitVars = {
    ACTOR_EN_GEG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_OF1D_MAP,
    sizeof(EnGeg),
    (ActorFunc)EnGeg_Init,
    (ActorFunc)EnGeg_Destroy,
    (ActorFunc)EnGeg_Update,
    (ActorFunc)EnGeg_Draw,
};

// static ColliderSphereInit sSphereInit = {
static ColliderSphereInit D_80BB3E70 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_SPHERE, },
    { ELEMTYPE_UNK0, { 0x20000000, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 0, { { 0, 0, 0 }, 0 }, 100 },
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BB3E9C = {
    { COLTYPE_HIT1, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 0, 0, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_80BB3EC8 = { 0, 0, 0, 0, MASS_IMMOVABLE };

// static DamageTable sDamageTable = {
static DamageTable D_80BB3ED4 = {
    /* Deku Nut       */ DMG_ENTRY(1, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(1, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x0),
    /* Ice arrow      */ DMG_ENTRY(1, 0x0),
    /* Light arrow    */ DMG_ENTRY(1, 0x0),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, 0x0),
    /* Zora barrier   */ DMG_ENTRY(1, 0x0),
    /* Normal shield  */ DMG_ENTRY(1, 0x0),
    /* Light ray      */ DMG_ENTRY(1, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(1, 0x0),
    /* Normal Roll    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(1, 0x0),
    /* Unblockable    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(1, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};

#endif

extern ColliderSphereInit D_80BB3E70;
extern ColliderCylinderInit D_80BB3E9C;
extern CollisionCheckInfoInit2 D_80BB3EC8;
extern DamageTable D_80BB3ED4;

extern UNK_TYPE D_06004DB0;
extern UNK_TYPE D_060091A8;
extern UNK_TYPE D_06012DE0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB16D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB178C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB18FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB19C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB1B14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB1C1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB1C8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB1D04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB1D64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB1FCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB2020.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB2088.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB217C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB221C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB2520.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB26EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB27D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB2944.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB2A54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB2B1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB2E00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB2F7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB30B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB31B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB32AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB3318.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB347C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/EnGeg_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/EnGeg_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/EnGeg_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB3728.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB3860.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB387C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB39F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB3BE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB3CB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/EnGeg_Draw.s")
