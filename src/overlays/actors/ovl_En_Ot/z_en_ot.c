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
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_OT,
    sizeof(EnOt),
    (ActorFunc)EnOt_Init,
    (ActorFunc)EnOt_Destroy,
    (ActorFunc)EnOt_Update,
    (ActorFunc)EnOt_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5B2E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/EnOt_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/EnOt_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5BAAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5BB38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5BDA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5BE04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5BE88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5BED4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5BF60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5BFB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5C154.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5C1CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5C244.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5C25C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5C3B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5C3D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5C634.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5C64C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5C684.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5C6DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5C910.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5C950.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5C9A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5C9C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5C9D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5CA30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5CAD0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5CB0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5CBA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5CBEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5CC88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5CCA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5CCF4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5CD40.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5CE6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5CEC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5D114.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5D160.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5D37C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5D470.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5D648.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5D750.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/EnOt_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5DAEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5DB6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/EnOt_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5DECC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5DF58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5E078.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ot_0x80B5B2E0/func_80B5E1D8.asm")
