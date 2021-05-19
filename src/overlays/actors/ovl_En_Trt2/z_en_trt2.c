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
