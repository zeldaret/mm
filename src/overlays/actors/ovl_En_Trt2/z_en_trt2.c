#include "z_en_trt2.h"

#define FLAGS 0x00000009

#define THIS ((EnTrt2*)thisx)

void EnTrt2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTrt2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTrt2_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Trt2_InitVars = {
    ACTOR_EN_TRT2,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_TRT,
    sizeof(EnTrt2),
    (ActorFunc)EnTrt2_Init,
    (ActorFunc)EnTrt2_Destroy,
    (ActorFunc)EnTrt2_Update,
    (ActorFunc)NULL,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80AD58A0 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 32, 56, 30, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_80AD58CC = { 1, 0, 0, 0, MASS_IMMOVABLE };


// static DamageTable sDamageTable = {
static DamageTable D_80AD58D8 = {
    /* Deku Nut       */ DMG_ENTRY(1, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x1),
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


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80AD5964[] = {
    ICHAIN_U8(targetMode, 3, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 500, ICHAIN_STOP),
};


extern ColliderCylinderInit D_80AD58A0;
extern CollisionCheckInfoInit2 D_80AD58CC;
extern DamageTable D_80AD58D8;
extern InitChainEntry D_80AD5964[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD3380.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD341C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD349C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD3530.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD3664.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD36EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD381C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD38B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD3A24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD3AE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD3B6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD3BE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD3C94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD3CEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD3DA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD3E34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD3EF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD3FF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD40AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD4110.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD417C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD4298.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD431C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD434C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD4550.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD4608.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD469C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD46F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD475C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD48F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD49B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD4A78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD4B08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD4B4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD4C4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD4CCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD4DB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD4FE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/EnTrt2_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/EnTrt2_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/EnTrt2_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD5234.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD5394.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD54C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD5584.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD566C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt2_0x80AD3380/func_80AD56E8.asm")
