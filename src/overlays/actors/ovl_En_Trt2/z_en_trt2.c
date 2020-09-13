#include "z_en_trt2.h"

#define FLAGS 0x00000009

#define THIS ((EnTrt2*)thisx)

void EnTrt2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTrt2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTrt2_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Trt2_InitVars = {
    ACTOR_EN_TRT2,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_TRT,
    sizeof(EnTrt2),
    (ActorFunc)EnTrt2_Init,
    (ActorFunc)EnTrt2_Destroy,
    (ActorFunc)EnTrt2_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD3380.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD341C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD349C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD3530.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD3664.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD36EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD381C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD38B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD3A24.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD3AE4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD3B6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD3BE4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD3C94.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD3CEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD3DA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD3E34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD3EF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD3FF4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD40AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD4110.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD417C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD4298.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD431C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD434C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD4550.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD4608.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD469C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD46F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD475C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD48F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD49B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD4A78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD4B08.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD4B4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD4C4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD4CCC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD4DB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD4FE4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/EnTrt2_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/EnTrt2_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/EnTrt2_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD5234.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD5394.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD54C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD5584.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD566C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt2_0x80AD3380/func_80AD56E8.asm")
