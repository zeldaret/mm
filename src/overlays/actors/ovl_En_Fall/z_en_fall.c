#include "z_en_fall.h"

#define FLAGS 0x00000030

#define THIS ((EnFall*)thisx)

void EnFall_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFall_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFall_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Fall_InitVars = {
    ACTOR_EN_FALL,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnFall),
    (ActorFunc)EnFall_Init,
    (ActorFunc)EnFall_Destroy,
    (ActorFunc)EnFall_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Fall_0x80A6BF90/func_80A6BF90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fall_0x80A6BF90/func_80A6C1DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fall_0x80A6BF90/EnFall_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fall_0x80A6BF90/EnFall_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fall_0x80A6BF90/func_80A6C3AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fall_0x80A6BF90/func_80A6C3FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fall_0x80A6BF90/func_80A6C7C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fall_0x80A6BF90/func_80A6C9A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fall_0x80A6BF90/func_80A6CA9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fall_0x80A6BF90/func_80A6CB74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fall_0x80A6BF90/func_80A6CD38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fall_0x80A6BF90/func_80A6CD74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fall_0x80A6BF90/func_80A6CECC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fall_0x80A6BF90/func_80A6CF60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fall_0x80A6BF90/func_80A6CF70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fall_0x80A6BF90/EnFall_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fall_0x80A6BF90/func_80A6D100.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fall_0x80A6BF90/func_80A6D220.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fall_0x80A6BF90/func_80A6D444.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fall_0x80A6BF90/func_80A6D504.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fall_0x80A6BF90/func_80A6D698.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fall_0x80A6BF90/func_80A6D75C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fall_0x80A6BF90/func_80A6D88C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fall_0x80A6BF90/func_80A6D98C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fall_0x80A6BF90/func_80A6DA7C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fall_0x80A6BF90/func_80A6DC20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fall_0x80A6BF90/func_80A6DC40.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fall_0x80A6BF90/func_80A6DD3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fall_0x80A6BF90/func_80A6E07C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fall_0x80A6BF90/func_80A6E214.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fall_0x80A6BF90/func_80A6E37C.asm")
