#include "z_en_dg.h"

#define FLAGS 0x00800019

#define THIS ((EnDg*)thisx)

void EnDg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDg_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Dg_InitVars = {
    ACTOR_EN_DG,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_DOG,
    sizeof(EnDg),
    (ActorFunc)EnDg_Init,
    (ActorFunc)EnDg_Destroy,
    (ActorFunc)EnDg_Update,
    (ActorFunc)EnDg_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_8098C304 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0xF7CFFFFF, 0x04, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 13, 19, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_8098C330 = { 0, 0, 0, 0, 1 };

// static DamageTable sDamageTable = {
static DamageTable D_8098C33C = {
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

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8098C45C[] = {
    ICHAIN_F32(uncullZoneForward, 1000, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_8098C304;
extern CollisionCheckInfoInit2 D_8098C330;
extern DamageTable D_8098C33C;
extern InitChainEntry D_8098C45C[];

extern UNK_TYPE D_060080F0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_80989140.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_80989204.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098933C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_80989418.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_809895B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_80989674.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_80989864.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_80989974.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_809899C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_80989A08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_80989A48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_80989A9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_80989ADC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_80989BF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_80989D38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_80989E18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_80989FC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098A064.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098A1B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098A234.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098A468.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098A55C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098A618.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098A70C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098A89C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098A938.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098AAAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098AB48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098AC34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098AE58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098AF44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098AF98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098B004.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098B198.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098B28C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098B390.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098B464.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098B560.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098B88C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098BA64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098BB10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098BBEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098BC54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/EnDg_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/EnDg_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/EnDg_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098BFB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098BFD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/EnDg_Draw.s")
