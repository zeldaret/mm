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
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_JSO,
    sizeof(EnJso2),
    (ActorFunc)EnJso2_Init,
    (ActorFunc)EnJso2_Destroy,
    (ActorFunc)EnJso2_Update,
    (ActorFunc)EnJso2_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/EnJso2_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/EnJso2_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A776E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A77790.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A77880.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A778D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A778F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A78588.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A785E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A787FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A78868.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A78A70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A78ACC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A78B04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A78B70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A78C08.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A78C7C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A78E8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A78F04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A78F80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A79038.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A790E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A7919C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A79300.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A79364.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A79450.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A794C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A79524.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A79600.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A796BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A7980C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A79864.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A798C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A7998C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A79A84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A79B60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A79BA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A7A0D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A7A124.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A7A2EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A7A360.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/EnJso2_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A7AA48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/func_80A7AA9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jso2_0x80A773C0/EnJso2_Draw.asm")
