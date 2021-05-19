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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Arrow_Ice_0x80922430/func_80922430.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Arrow_Ice_0x80922430/ArrowIce_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Arrow_Ice_0x80922430/ArrowIce_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Arrow_Ice_0x80922430/func_809224DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Arrow_Ice_0x80922430/func_809225D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Arrow_Ice_0x80922430/func_80922628.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Arrow_Ice_0x80922430/func_809227F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Arrow_Ice_0x80922430/ArrowIce_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Arrow_Ice_0x80922430/ArrowIce_Draw.asm")
