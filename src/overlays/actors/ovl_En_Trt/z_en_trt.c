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
    (ActorFunc)EnTrt_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8B770.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8B80C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8B88C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8B964.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8B9B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8BA3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8BAF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8BB3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8BB8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8BC8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8BCD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8BD28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8BD7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8BDD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8BEF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8BF24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8BFE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8C168.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8C1E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8C288.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8C488.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8C564.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8C64C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8C6CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8C74C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8C8A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8C98C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8CA2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8CB0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8CBFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8CCB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8CCF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8CD2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8CEE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8D094.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8D380.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8D5C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8D880.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8D9CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8DAAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8DBBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8DD10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8DD60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8DEBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8DF20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8DFBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8E02C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8E0D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8E26C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8E30C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8E330.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8E3CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8E458.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8E4D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8E5A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8E754.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8E774.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8E79C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8E830.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8E890.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8E91C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8E92C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8E94C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8E9A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8EB4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8EB9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8EBD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8ECA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8ED3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8EFA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8EFF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8F268.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8F404.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/EnTrt_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/EnTrt_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/EnTrt_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8F8C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8FA00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8FB34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8FBB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8FC64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/EnTrt_Draw.asm")
