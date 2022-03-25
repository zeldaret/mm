/*
 * File: z_en_bigpamet.c
 * Overlay: ovl_En_Bigpamet
 * Description: Gekko & Snapper Miniboss - Snapper
 */

#include "z_en_bigpamet.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_400)

#define THIS ((EnBigpamet*)thisx)

void EnBigpamet_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBigpamet_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBigpamet_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBigpamet_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A281DC(EnBigpamet* this, GlobalContext* globalCtx);
void func_80A282C8(EnBigpamet* this, GlobalContext* globalCtx);
void func_80A283A0(EnBigpamet* this, GlobalContext* globalCtx);
void func_80A2844C(EnBigpamet* this, GlobalContext* globalCtx);
void func_80A2855C(EnBigpamet* this, GlobalContext* globalCtx);
void func_80A2866C(EnBigpamet* this, GlobalContext* globalCtx);
void func_80A28708(EnBigpamet* this, GlobalContext* globalCtx);
void func_80A287E8(EnBigpamet* this, GlobalContext* globalCtx);
void func_80A289C8(EnBigpamet* this, GlobalContext* globalCtx);
void func_80A28A98(EnBigpamet* this, GlobalContext* globalCtx);
void func_80A28D0C(EnBigpamet* this, GlobalContext* globalCtx);
void func_80A28DC0(EnBigpamet* this, GlobalContext* globalCtx);
void func_80A28E98(EnBigpamet* this, GlobalContext* globalCtx);
void func_80A28EE8(EnBigpamet* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Bigpamet_InitVars = {
    ACTOR_EN_BIGPAMET,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_TL,
    sizeof(EnBigpamet),
    (ActorFunc)EnBigpamet_Init,
    (ActorFunc)EnBigpamet_Destroy,
    (ActorFunc)EnBigpamet_Update,
    (ActorFunc)EnBigpamet_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A29700 = {
    { COLTYPE_HARD, AT_NONE | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x04, 0x04 }, { 0xF7CF7FFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 53, 50, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit D_80A2972C = { 1, 53, 60, 250 };

// static DamageTable sDamageTable = {
static DamageTable D_80A29734 = {
    /* Deku Nut       */ DMG_ENTRY(1, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0x0),
    /* Ice arrow      */ DMG_ENTRY(1, 0x0),
    /* Light arrow    */ DMG_ENTRY(1, 0x0),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, 0x0),
    /* Zora barrier   */ DMG_ENTRY(1, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(1, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A29764[] = {
    ICHAIN_S8(hintId, 1, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 15, ICHAIN_CONTINUE),
    ICHAIN_F32(gravity, -2, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 4333, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, 5, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80A29700;
extern CollisionCheckInfoInit D_80A2972C;
extern DamageTable D_80A29734;
extern InitChainEntry D_80A29764[];

extern UNK_TYPE D_06000440;
extern UNK_TYPE D_06000AF4;
extern UNK_TYPE D_06001C68;
extern UNK_TYPE D_060031DC;
extern UNK_TYPE D_06004210;
extern UNK_TYPE D_0600823C;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/EnBigpamet_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/EnBigpamet_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A2768C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A276F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A2778C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A27970.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A27B58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A27DD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A27FE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A2811C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A281B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A281DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A28274.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A282C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A28378.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A283A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A283F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A2844C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A284E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A2855C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A28618.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A2866C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A286C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A28708.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A28760.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A287E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A28970.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A289C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A28A28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A28A98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A28B98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A28D0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A28D80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A28DC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A28E40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A28E98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A28ED4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A28EE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A29028.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A29094.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/EnBigpamet_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A292A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A293E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A29494.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/EnBigpamet_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A29580.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A29628.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A2966C.s")
