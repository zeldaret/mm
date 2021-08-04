#include "z_demo_syoten.h"

#define FLAGS 0x00000030

#define THIS ((DemoSyoten*)thisx)

void DemoSyoten_Init(Actor* thisx, GlobalContext* globalCtx);
void DemoSyoten_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DemoSyoten_Update(Actor* thisx, GlobalContext* globalCtx);
void DemoSyoten_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Demo_Syoten_InitVars = {
    ACTOR_DEMO_SYOTEN,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_SYOTEN,
    sizeof(DemoSyoten),
    (ActorFunc)DemoSyoten_Init,
    (ActorFunc)DemoSyoten_Destroy,
    (ActorFunc)DemoSyoten_Update,
    (ActorFunc)DemoSyoten_Draw,
};

#endif

extern UNK_TYPE D_0600023C;
extern UNK_TYPE D_06001298;
extern UNK_TYPE D_060018C0;
extern UNK_TYPE D_06002880;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Syoten/DemoSyoten_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Syoten/DemoSyoten_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Syoten/func_80C16760.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Syoten/func_80C16818.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Syoten/func_80C168D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Syoten/func_80C16974.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Syoten/func_80C16A64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Syoten/func_80C16A74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Syoten/func_80C16BD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Syoten/func_80C16DD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Syoten/func_80C16EAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Syoten/func_80C17008.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Syoten/DemoSyoten_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Syoten/func_80C170F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Syoten/func_80C173B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Syoten/func_80C17468.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Syoten/DemoSyoten_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Syoten/func_80C17690.s")
