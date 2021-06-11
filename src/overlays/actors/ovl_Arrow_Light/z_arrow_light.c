#include "z_arrow_light.h"

#define FLAGS 0x02000010

#define THIS ((ArrowLight*)thisx)

void ArrowLight_Init(Actor* thisx, GlobalContext* globalCtx);
void ArrowLight_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ArrowLight_Update(Actor* thisx, GlobalContext* globalCtx);
void ArrowLight_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Arrow_Light_InitVars = {
    ACTOR_ARROW_LIGHT,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ArrowLight),
    (ActorFunc)ArrowLight_Init,
    (ActorFunc)ArrowLight_Destroy,
    (ActorFunc)ArrowLight_Update,
    (ActorFunc)ArrowLight_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Light/func_80924300.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Light/ArrowLight_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Light/ArrowLight_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Light/func_809243AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Light/func_809244A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Light/func_809244F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Light/func_809246C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Light/ArrowLight_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Light/ArrowLight_Draw.s")
