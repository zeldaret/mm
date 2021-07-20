#include "z_en_ot.h"

#define FLAGS 0x00000019

#define THIS ((EnOt*)thisx)

void EnOt_Init(Actor* thisx, GlobalContext* globalCtx);
void EnOt_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnOt_Update(Actor* thisx, GlobalContext* globalCtx);
void EnOt_Draw(Actor* thisx, GlobalContext* globalCtx);

/*

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

*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5B2E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/EnOt_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/EnOt_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5BAAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5BB38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5BDA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5BE04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5BE88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5BED4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5BF60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5BFB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5C154.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5C1CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5C244.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5C25C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5C3B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5C3D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5C634.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5C64C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5C684.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5C6DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5C910.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5C950.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5C9A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5C9C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5C9D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5CA30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5CAD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5CB0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5CBA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5CBEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5CC88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5CCA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5CCF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5CD40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5CE6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5CEC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5D114.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5D160.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5D37C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5D470.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5D648.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5D750.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/EnOt_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5DAEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5DB6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/EnOt_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5DECC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5DF58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5E078.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ot_0x80B5B2E0/func_80B5E1D8.asm")
