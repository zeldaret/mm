#include "z_en_trt2.h"

#define FLAGS 0x00000009

#define THIS ((EnTrt2*)thisx)

void EnTrt2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTrt2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTrt2_Update(Actor* thisx, GlobalContext* globalCtx);

/*
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
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD3380.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD341C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD349C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD3530.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD3664.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD36EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD381C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD38B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD3A24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD3AE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD3B6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD3BE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD3C94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD3CEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD3DA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD3E34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD3EF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD3FF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD40AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD4110.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD417C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD4298.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD431C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD434C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD4550.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD4608.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD469C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD46F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD475C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD48F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD49B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD4A78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD4B08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD4B4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD4C4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD4CCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD4DB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD4FE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/EnTrt2_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/EnTrt2_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/EnTrt2_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD5234.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD5394.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD54C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD5584.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD566C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt2/func_80AD56E8.s")
