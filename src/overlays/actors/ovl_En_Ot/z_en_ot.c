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
*/

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
