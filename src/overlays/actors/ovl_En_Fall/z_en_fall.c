#include "z_en_fall.h"

#define FLAGS 0x00000030

#define THIS ((EnFall*)thisx)

void EnFall_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFall_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFall_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Fall_InitVars = {
    ACTOR_EN_FALL,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnFall),
    (ActorFunc)EnFall_Init,
    (ActorFunc)EnFall_Destroy,
    (ActorFunc)EnFall_Update,
    (ActorFunc)NULL,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6BF90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6C1DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/EnFall_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/EnFall_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6C3AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6C3FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6C7C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6C9A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6CA9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6CB74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6CD38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6CD74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6CECC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6CF60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6CF70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/EnFall_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6D100.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6D220.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6D444.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6D504.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6D698.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6D75C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6D88C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6D98C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6DA7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6DC20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6DC40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6DD3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6E07C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6E214.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6E37C.s")
