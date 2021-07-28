#include "z_en_rr.h"

#define FLAGS 0x00000405

#define THIS ((EnRr*)thisx)

void EnRr_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRr_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRr_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRr_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Rr_InitVars = {
    ACTOR_EN_RR,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_RR,
    sizeof(EnRr),
    (ActorFunc)EnRr_Init,
    (ActorFunc)EnRr_Destroy,
    (ActorFunc)EnRr_Update,
    (ActorFunc)EnRr_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_808FC150 = {
    { COLTYPE_HIT0, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x20000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 45, 60, 0, { 0, 0, 0 } },
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_808FC17C = {
    { COLTYPE_HIT0, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x20000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_ON | BUMP_HOOKABLE, OCELEM_NONE, },
    { 30, 45, -30, { 0, 0, 0 } },
};

// static DamageTable sDamageTable = {
static DamageTable D_808FC1A8 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(3, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(0, 0x1),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xE),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(3, 0x0),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(2, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(2, 0x5),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(2, 0x0),
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
static CollisionCheckInfoInit D_808FC1C8 = { 3, 45, 60, 250 };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_808FC1D0[] = {
    ICHAIN_S8(hintId, 55, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, 2, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -400, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 2000, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 30, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_808FC150;
extern ColliderCylinderInit D_808FC17C;
extern DamageTable D_808FC1A8;
extern CollisionCheckInfoInit D_808FC1C8;
extern InitChainEntry D_808FC1D0[];

extern UNK_TYPE D_06000470;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/EnRr_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/EnRr_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FA01C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FA11C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FA19C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FA238.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FA260.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FA344.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FA3F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FA4F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FA6B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FA7AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FA870.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FA910.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FA9CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FAA94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FAC80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FAD1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FAE50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FAF94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FB088.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FB1C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FB2C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FB398.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FB42C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FB680.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FB710.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FB794.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/EnRr_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/EnRr_Draw.s")
