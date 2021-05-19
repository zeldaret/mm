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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/EnJso2_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/EnJso2_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A776E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A77790.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A77880.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A778D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A778F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A78588.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A785E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A787FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A78868.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A78A70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A78ACC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A78B04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A78B70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A78C08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A78C7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A78E8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A78F04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A78F80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A79038.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A790E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A7919C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A79300.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A79364.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A79450.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A794C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A79524.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A79600.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A796BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A7980C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A79864.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A798C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A7998C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A79A84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A79B60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A79BA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A7A0D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A7A124.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A7A2EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A7A360.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/EnJso2_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A7AA48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/func_80A7AA9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso2_0x80A773C0/EnJso2_Draw.asm")
