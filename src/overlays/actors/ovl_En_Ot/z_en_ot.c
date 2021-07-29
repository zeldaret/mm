#include "z_en_ot.h"

#define FLAGS 0x00000019

#define THIS ((EnOt*)thisx)

void EnOt_Init(Actor* thisx, GlobalContext* globalCtx);
void EnOt_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnOt_Update(Actor* thisx, GlobalContext* globalCtx);
void EnOt_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B5BE04(EnOt* this, GlobalContext* globalCtx);
void func_80B5BED4(EnOt* this, GlobalContext* globalCtx);
void func_80B5BFB8(EnOt* this, GlobalContext* globalCtx);
void func_80B5C1CC(EnOt* this, GlobalContext* globalCtx);
void func_80B5C25C(EnOt* this, GlobalContext* globalCtx);
void func_80B5C3D8(EnOt* this, GlobalContext* globalCtx);
void func_80B5C64C(EnOt* this, GlobalContext* globalCtx);
void func_80B5C6DC(EnOt* this, GlobalContext* globalCtx);
void func_80B5C950(EnOt* this, GlobalContext* globalCtx);
void func_80B5C9C0(EnOt* this, GlobalContext* globalCtx);
void func_80B5CA30(EnOt* this, GlobalContext* globalCtx);
void func_80B5CB0C(EnOt* this, GlobalContext* globalCtx);
void func_80B5CBEC(EnOt* this, GlobalContext* globalCtx);
void func_80B5CCA0(EnOt* this, GlobalContext* globalCtx);
void func_80B5CD40(EnOt* this, GlobalContext* globalCtx);
void func_80B5CEC8(EnOt* this, GlobalContext* globalCtx);
void func_80B5D160(EnOt* this, GlobalContext* globalCtx);
void func_80B5D750(EnOt* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Ot_InitVars = {
    ACTOR_EN_OT,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_OT,
    sizeof(EnOt),
    (ActorFunc)EnOt_Init,
    (ActorFunc)EnOt_Destroy,
    (ActorFunc)EnOt_Update,
    (ActorFunc)EnOt_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B5E3A0 = {
    { COLTYPE_HIT0, AT_NONE, AC_ON | AC_TYPE_PLAYER | AC_TYPE_ENEMY, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 5, 33, -20, { 0, 0, 0 } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B5E3FC[] = {
    ICHAIN_F32(uncullZoneScale, 80, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 80, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80B5E3A0;
extern InitChainEntry D_80B5E3FC[];

extern UNK_TYPE D_06000078;
extern UNK_TYPE D_060004A0;
extern UNK_TYPE D_060005F8;
extern UNK_TYPE D_060008D8;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5B2E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/EnOt_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/EnOt_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5BAAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5BB38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5BDA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5BE04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5BE88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5BED4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5BF60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5BFB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5C154.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5C1CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5C244.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5C25C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5C3B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5C3D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5C634.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5C64C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5C684.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5C6DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5C910.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5C950.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5C9A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5C9C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5C9D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5CA30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5CAD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5CB0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5CBA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5CBEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5CC88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5CCA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5CCF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5CD40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5CE6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5CEC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5D114.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5D160.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5D37C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5D470.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5D648.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5D750.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/EnOt_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5DAEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5DB6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/EnOt_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5DECC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5DF58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5E078.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ot/func_80B5E1D8.s")
