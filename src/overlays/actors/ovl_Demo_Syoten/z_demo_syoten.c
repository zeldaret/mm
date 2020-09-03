#include "z_demo_syoten.h"

#define FLAGS 0x00000030

#define THIS ((DemoSyoten*)thisx)

void DemoSyoten_Init(Actor* thisx, GlobalContext* globalCtx);
void DemoSyoten_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DemoSyoten_Update(Actor* thisx, GlobalContext* globalCtx);
void DemoSyoten_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Demo_Syoten_InitVars = {
    ACTOR_DEMO_SYOTEN,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    OBJECT_SYOTEN,
    sizeof(DemoSyoten),
    (ActorFunc)DemoSyoten_Init,
    (ActorFunc)DemoSyoten_Destroy,
    (ActorFunc)DemoSyoten_Update,
    (ActorFunc)DemoSyoten_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Demo_Syoten_0x80C16480/DemoSyoten_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Demo_Syoten_0x80C16480/DemoSyoten_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Demo_Syoten_0x80C16480/func_80C16760.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Demo_Syoten_0x80C16480/func_80C16818.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Demo_Syoten_0x80C16480/func_80C168D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Demo_Syoten_0x80C16480/func_80C16974.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Demo_Syoten_0x80C16480/func_80C16A64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Demo_Syoten_0x80C16480/func_80C16A74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Demo_Syoten_0x80C16480/func_80C16BD4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Demo_Syoten_0x80C16480/func_80C16DD4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Demo_Syoten_0x80C16480/func_80C16EAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Demo_Syoten_0x80C16480/func_80C17008.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Demo_Syoten_0x80C16480/DemoSyoten_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Demo_Syoten_0x80C16480/func_80C170F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Demo_Syoten_0x80C16480/func_80C173B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Demo_Syoten_0x80C16480/func_80C17468.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Demo_Syoten_0x80C16480/DemoSyoten_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Demo_Syoten_0x80C16480/func_80C17690.asm")
