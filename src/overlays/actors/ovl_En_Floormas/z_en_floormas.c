#include "z_en_floormas.h"

#define FLAGS 0x00000405

#define THIS ((EnFloormas*)thisx)

void EnFloormas_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFloormas_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFloormas_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFloormas_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_808D0B50(EnFloormas* this, GlobalContext* globalCtx);
void func_808D0C58(EnFloormas* this, GlobalContext* globalCtx);
void func_808D0D70(EnFloormas* this, GlobalContext* globalCtx);
void func_808D0F14(EnFloormas* this, GlobalContext* globalCtx);
void func_808D0F80(EnFloormas* this, GlobalContext* globalCtx);
void func_808D11BC(EnFloormas* this, GlobalContext* globalCtx);
void func_808D1458(EnFloormas* this, GlobalContext* globalCtx);
void func_808D1650(EnFloormas* this, GlobalContext* globalCtx);
void func_808D17EC(EnFloormas* this, GlobalContext* globalCtx);
void func_808D1B44(EnFloormas* this, GlobalContext* globalCtx);
void func_808D1C1C(EnFloormas* this, GlobalContext* globalCtx);
void func_808D1D6C(EnFloormas* this, GlobalContext* globalCtx);
void func_808D1F7C(EnFloormas* this, GlobalContext* globalCtx);
void func_808D2040(EnFloormas* this, GlobalContext* globalCtx);
void func_808D22C8(EnFloormas* this, GlobalContext* globalCtx);
void func_808D24F0(EnFloormas* this, GlobalContext* globalCtx);
void func_808D2764(EnFloormas* this, GlobalContext* globalCtx);
void func_808D2AA8(EnFloormas* this, GlobalContext* globalCtx);
void func_808D2AF4(EnFloormas* this, GlobalContext* globalCtx);
void func_808D2C08(EnFloormas* this, GlobalContext* globalCtx);
void func_808D2D30(EnFloormas* this, GlobalContext* globalCtx);
void func_808D2DC0(EnFloormas* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Floormas_InitVars = {
    ACTOR_EN_FLOORMAS,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_WALLMASTER,
    sizeof(EnFloormas),
    (ActorFunc)EnFloormas_Init,
    (ActorFunc)EnFloormas_Destroy,
    (ActorFunc)EnFloormas_Update,
    (ActorFunc)EnFloormas_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_808D38A0 = {
    { COLTYPE_HIT0, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7EFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 25, 40, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit D_808D38CC = { 3, 30, 40, 150 };

// static DamageTable sDamageTable = {
static DamageTable D_808D38D4 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
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
    /* Light ray      */ DMG_ENTRY(0, 0xE),
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

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_808D38F4[] = {
    ICHAIN_S8(hintId, 49, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 5500, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -1000, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_808D38A0;
extern CollisionCheckInfoInit D_808D38CC;
extern DamageTable D_808D38D4;
extern InitChainEntry D_808D38F4[];

extern UNK_TYPE D_06000590;
extern UNK_TYPE D_06000EA4;
extern UNK_TYPE D_060019CC;
extern UNK_TYPE D_06002158;
extern UNK_TYPE D_060039B0;
extern UNK_TYPE D_060041F4;
extern UNK_TYPE D_06008688;
extern UNK_TYPE D_06009244;
extern UNK_TYPE D_06009520;
extern UNK_TYPE D_06009DB0;
extern UNK_TYPE D_0600A054;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/EnFloormas_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/EnFloormas_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D08D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D0908.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D0930.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D09CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D0A48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D0B08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D0B50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D0C14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D0C58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D0CE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D0D70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D0ECC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D0F14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D0F50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D0F80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D108C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D11BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D1380.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D1458.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D14DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D161C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D1650.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D1740.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D17EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D19D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D1B44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D1BCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D1C1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D1D0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D1D6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D1ED4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D1F7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D1FD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D2040.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D217C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D22C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D2484.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D24F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D2700.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D2764.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D2A20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D2AA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D2AB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D2AF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D2B18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D2C08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D2CDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D2D30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D2D6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D2DC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D2E34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/EnFloormas_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D3488.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D34C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/EnFloormas_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D3754.s")
