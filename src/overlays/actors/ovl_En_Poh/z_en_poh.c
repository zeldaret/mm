#include "z_en_poh.h"

#define FLAGS 0x00001205

#define THIS ((EnPoh*)thisx)

void EnPoh_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPoh_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPoh_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPoh_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B2CAA4(EnPoh* this, GlobalContext* globalCtx);
void func_80B2CBBC(EnPoh* this, GlobalContext* globalCtx);
void func_80B2CD64(EnPoh* this, GlobalContext* globalCtx);
void func_80B2CF28(EnPoh* this, GlobalContext* globalCtx);
void func_80B2D07C(EnPoh* this, GlobalContext* globalCtx);
void func_80B2D140(EnPoh* this, GlobalContext* globalCtx);
void func_80B2D300(EnPoh* this, GlobalContext* globalCtx);
void func_80B2D628(EnPoh* this, GlobalContext* globalCtx);
void func_80B2D6EC(EnPoh* this, GlobalContext* globalCtx);
void func_80B2D7D4(EnPoh* this, GlobalContext* globalCtx);
void func_80B2D980(EnPoh* this, GlobalContext* globalCtx);
void func_80B2DB44(EnPoh* this, GlobalContext* globalCtx);
void func_80B2DD2C(EnPoh* this, GlobalContext* globalCtx);
void func_80B2E180(EnPoh* this, GlobalContext* globalCtx);
void func_80B2E230(EnPoh* this, GlobalContext* globalCtx);
void func_80B2E3F8(EnPoh* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Poh_InitVars = {
    ACTOR_EN_POH,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_PO,
    sizeof(EnPoh),
    (ActorFunc)EnPoh_Init,
    (ActorFunc)EnPoh_Destroy,
    (ActorFunc)EnPoh_Update,
    (ActorFunc)EnPoh_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B2F680 = {
    { COLTYPE_HIT3, AT_NONE, AC_NONE | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CBFFFE, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 20, 40, 20, { 0, 0, 0 } },
};

// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_80B2F6AC[1] = {
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x08 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
        { 18, { { 0, 1400, 0 }, 10 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80B2F6D0 = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    1, D_80B2F6AC, // sJntSphElementsInit,
};

// static DamageTable sDamageTable = {
static DamageTable D_80B2F6E0 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0xF),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xE),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x0),
    /* Ice arrow      */ DMG_ENTRY(1, 0x0),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
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

// sColChkInfoInit
static CollisionCheckInfoInit D_80B2F700 = { 3, 25, 50, 50 };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B2F708[] = {
    ICHAIN_S8(hintId, 68, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 3200, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80B2F680;
extern ColliderJntSphElementInit D_80B2F6AC[1];
extern ColliderJntSphInit D_80B2F6D0;
extern DamageTable D_80B2F6E0;
extern CollisionCheckInfoInit D_80B2F700;
extern InitChainEntry D_80B2F708[];

extern UNK_TYPE D_060001A8;
extern UNK_TYPE D_060004EC;
extern UNK_TYPE D_060006E0;
extern UNK_TYPE D_06000A60;
extern UNK_TYPE D_060011C4;
extern UNK_TYPE D_060015B0;
extern UNK_TYPE D_06002608;
extern UNK_TYPE D_06002D28;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/EnPoh_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/EnPoh_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2C910.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2C9B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2CA4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2CAA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2CB60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2CBBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2CD14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2CD64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2CEC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2CF28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2CFF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2D07C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2D0E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2D140.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2D2C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2D300.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2D5DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2D628.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2D694.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2D6EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2D76C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2D7D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2D924.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2D980.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2DAD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2DB44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2DC50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2DD2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2DDF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2E0B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2E180.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2E1D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2E230.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2E3B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2E3F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2E438.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2E55C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2E6C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2E8E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/EnPoh_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2ED14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2EDD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/EnPoh_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2F328.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2F37C.s")
