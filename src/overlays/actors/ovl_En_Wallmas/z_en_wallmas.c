#include "z_en_wallmas.h"

#define FLAGS 0x00000415

#define THIS ((EnWallmas*)thisx)

void EnWallmas_Init(Actor* thisx, GlobalContext* globalCtx);
void EnWallmas_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnWallmas_Update(Actor* thisx, GlobalContext* globalCtx);
void EnWallmas_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80874BE4(EnWallmas* this, GlobalContext* globalCtx);
void func_80874DE8(EnWallmas* this, GlobalContext* globalCtx);
void func_80874FD8(EnWallmas* this, GlobalContext* globalCtx);
void func_80875054(EnWallmas* this, GlobalContext* globalCtx);
void func_80875108(EnWallmas* this, GlobalContext* globalCtx);
void func_8087520C(EnWallmas* this, GlobalContext* globalCtx);
void func_808752CC(EnWallmas* this, GlobalContext* globalCtx);
void func_80875484(EnWallmas* this, GlobalContext* globalCtx);
void func_8087556C(EnWallmas* this, GlobalContext* globalCtx);
void func_80875638(EnWallmas* this, GlobalContext* globalCtx);
void func_8087571C(EnWallmas* this, GlobalContext* globalCtx);
void func_80875910(EnWallmas* this, GlobalContext* globalCtx);
void func_8087596C(EnWallmas* this, GlobalContext* globalCtx);
void func_80875A0C(EnWallmas* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Wallmas_InitVars = {
    ACTOR_EN_WALLMAS,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_WALLMASTER,
    sizeof(EnWallmas),
    (ActorFunc)EnWallmas_Init,
    (ActorFunc)EnWallmas_Destroy,
    (ActorFunc)EnWallmas_Update,
    (ActorFunc)EnWallmas_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80876360 = {
    { COLTYPE_HIT0, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 30, 40, 0, { 0, 0, 0 } },
};

// static DamageTable sDamageTable = {
static DamageTable D_8087638C = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(1, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x5),
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
static CollisionCheckInfoInit D_808763AC = { 3, 30, 40, 150 };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_808763B4[] = {
    ICHAIN_S8(hintId, 48, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 5500, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -1500, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80876360;
extern DamageTable D_8087638C;
extern CollisionCheckInfoInit D_808763AC;
extern InitChainEntry D_808763B4[];

extern UNK_TYPE D_06000590;
extern UNK_TYPE D_06000EA4;
extern UNK_TYPE D_060019CC;
extern UNK_TYPE D_0600299C;
extern UNK_TYPE D_060041F4;
extern UNK_TYPE D_06008688;
extern UNK_TYPE D_06009244;
extern UNK_TYPE D_06009520;
extern UNK_TYPE D_06009DB0;
extern UNK_TYPE D_0600A054;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/EnWallmas_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/EnWallmas_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80874A88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80874B04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80874B88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80874BE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80874D1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80874DE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80874F14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80874FD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80875014.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80875054.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_808750B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80875108.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_808751C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_8087520C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80875248.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_808752CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_808753F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80875484.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80875518.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_8087556C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_808755A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80875638.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_808756AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_8087571C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_808758C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80875910.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_8087596C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_808759B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80875A0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80875A74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/EnWallmas_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80875F04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_808760A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80876118.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/EnWallmas_Draw.s")
