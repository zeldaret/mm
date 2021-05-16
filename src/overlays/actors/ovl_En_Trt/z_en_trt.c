#include "z_en_trt.h"

#define FLAGS 0x00000009

#define THIS ((EnTrt*)thisx)

void EnTrt_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTrt_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTrt_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTrt_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Trt_InitVars = {
    ACTOR_EN_TRT,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_TRT,
    sizeof(EnTrt),
    (ActorFunc)EnTrt_Init,
    (ActorFunc)EnTrt_Destroy,
    (ActorFunc)EnTrt_Update,
    (ActorFunc)EnTrt_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8B770.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8B80C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8B88C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8B964.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8B9B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8BA3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8BAF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8BB3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8BB8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8BC8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8BCD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8BD28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8BD7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8BDD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8BEF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8BF24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8BFE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8C168.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8C1E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8C288.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8C488.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8C564.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8C64C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8C6CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8C74C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8C8A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8C98C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8CA2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8CB0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8CBFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8CCB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8CCF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8CD2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8CEE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8D094.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8D380.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8D5C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8D880.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8D9CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8DAAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8DBBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8DD10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8DD60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8DEBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8DF20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8DFBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8E02C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8E0D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8E26C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8E30C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8E330.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8E3CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8E458.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8E4D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8E5A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8E754.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8E774.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8E79C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8E830.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8E890.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8E91C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8E92C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8E94C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8E9A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8EB4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8EB9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8EBD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8ECA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8ED3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8EFA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8EFF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8F268.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8F404.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/EnTrt_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/EnTrt_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/EnTrt_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8F8C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8FA00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8FB34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8FBB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/func_80A8FC64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Trt/EnTrt_Draw.s")
