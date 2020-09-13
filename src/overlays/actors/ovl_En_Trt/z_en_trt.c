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
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_TRT,
    sizeof(EnTrt),
    (ActorFunc)EnTrt_Init,
    (ActorFunc)EnTrt_Destroy,
    (ActorFunc)EnTrt_Update,
    (ActorFunc)EnTrt_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8B770.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8B80C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8B88C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8B964.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8B9B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8BA3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8BAF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8BB3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8BB8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8BC8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8BCD4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8BD28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8BD7C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8BDD0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8BEF4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8BF24.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8BFE0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8C168.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8C1E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8C288.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8C488.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8C564.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8C64C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8C6CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8C74C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8C8A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8C98C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8CA2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8CB0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8CBFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8CCB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8CCF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8CD2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8CEE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8D094.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8D380.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8D5C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8D880.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8D9CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8DAAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8DBBC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8DD10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8DD60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8DEBC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8DF20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8DFBC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8E02C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8E0D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8E26C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8E30C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8E330.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8E3CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8E458.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8E4D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8E5A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8E754.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8E774.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8E79C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8E830.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8E890.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8E91C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8E92C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8E94C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8E9A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8EB4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8EB9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8EBD8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8ECA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8ED3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8EFA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8EFF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8F268.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8F404.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/EnTrt_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/EnTrt_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/EnTrt_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8F8C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8FA00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8FB34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8FBB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/func_80A8FC64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Trt_0x80A8B770/EnTrt_Draw.asm")
