#include "z_en_jso2.h"

#define FLAGS 0x80100035

#define THIS ((EnJso2*)thisx)

void EnJso2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnJso2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnJso2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnJso2_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Jso2_InitVars = {
    ACTOR_EN_JSO2,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_JSO,
    sizeof(EnJso2),
    (ActorFunc)EnJso2_Init,
    (ActorFunc)EnJso2_Destroy,
    (ActorFunc)EnJso2_Update,
    (ActorFunc)EnJso2_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/EnJso2_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/EnJso2_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A776E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A77790.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A77880.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A778D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A778F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A78588.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A785E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A787FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A78868.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A78A70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A78ACC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A78B04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A78B70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A78C08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A78C7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A78E8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A78F04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A78F80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A79038.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A790E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A7919C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A79300.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A79364.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A79450.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A794C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A79524.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A79600.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A796BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A7980C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A79864.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A798C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A7998C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A79A84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A79B60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A79BA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A7A0D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A7A124.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A7A2EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A7A360.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/EnJso2_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A7AA48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/func_80A7AA9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso2/EnJso2_Draw.s")
