#include "z_arrow_ice.h"

#define FLAGS 0x02000010

#define THIS ((ArrowIce*)thisx)

void ArrowIce_Init(Actor* thisx, GlobalContext* globalCtx);
void ArrowIce_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ArrowIce_Update(Actor* thisx, GlobalContext* globalCtx);
void ArrowIce_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Arrow_Ice_InitVars = {
    ACTOR_ARROW_ICE,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ArrowIce),
    (ActorFunc)ArrowIce_Init,
    (ActorFunc)ArrowIce_Destroy,
    (ActorFunc)ArrowIce_Update,
    (ActorFunc)ArrowIce_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Ice/func_80922430.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Ice/ArrowIce_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Ice/ArrowIce_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Ice/func_809224DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Ice/func_809225D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Ice/func_80922628.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Ice/func_809227F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Ice/ArrowIce_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Ice/ArrowIce_Draw.s")
