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
    ACTORTYPE_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ArrowLight),
    (ActorFunc)ArrowLight_Init,
    (ActorFunc)ArrowLight_Destroy,
    (ActorFunc)ArrowLight_Update,
    (ActorFunc)ArrowLight_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Arrow_Light_0x80924300/func_80924300.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Arrow_Light_0x80924300/ArrowLight_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Arrow_Light_0x80924300/ArrowLight_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Arrow_Light_0x80924300/func_809243AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Arrow_Light_0x80924300/func_809244A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Arrow_Light_0x80924300/func_809244F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Arrow_Light_0x80924300/func_809246C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Arrow_Light_0x80924300/ArrowLight_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Arrow_Light_0x80924300/ArrowLight_Draw.asm")
