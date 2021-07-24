#include "z_en_okuta.h"

#define FLAGS 0x00000005

#define THIS ((EnOkuta*)thisx)

void EnOkuta_Init(Actor* thisx, GlobalContext* globalCtx);
void EnOkuta_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnOkuta_Update(Actor* thisx, GlobalContext* globalCtx);
void EnOkuta_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Okuta_InitVars = {
    ACTOR_EN_OKUTA,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_OKUTA,
    sizeof(EnOkuta),
    (ActorFunc)EnOkuta_Init,
    (ActorFunc)EnOkuta_Destroy,
    (ActorFunc)EnOkuta_Update,
    (ActorFunc)EnOkuta_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_808708A0 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK4, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON, OCELEM_ON, },
    { 13, 20, 0, { 0, 0, 0 } },
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_808708CC = {
    { COLTYPE_HIT0, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON, OCELEM_ON, },
    { 20, 40, -30, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit D_808708F8 = { 4, 15, 60, 100 };


// static DamageTable sDamageTable = {
static DamageTable D_80870900 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
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
    /* Fire arrow     */ DMG_ENTRY(1, 0x0),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
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


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80870920[] = {
    ICHAIN_S8(hintId, 66, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 6500, ICHAIN_STOP),
};


extern ColliderCylinderInit D_808708A0;
extern ColliderCylinderInit D_808708CC;
extern CollisionCheckInfoInit D_808708F8;
extern DamageTable D_80870900;
extern InitChainEntry D_80870920[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/EnOkuta_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/EnOkuta_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086E084.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086E0F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086E168.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086E214.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086E27C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086E2C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086E378.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086E3B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086E4FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086E52C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086E5E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086E658.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086E7A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086E7E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086E8E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086E948.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086EAE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086EC00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086EE8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086EF14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086EF90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086EFE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086F2FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086F434.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086F4B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086F4F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086F57C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086F694.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086F8FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086FCA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/EnOkuta_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_808700C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_80870254.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_808704DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_808705C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/EnOkuta_Draw.asm")
