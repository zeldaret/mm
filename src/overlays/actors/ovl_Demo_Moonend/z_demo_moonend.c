#include "z_demo_moonend.h"

#define FLAGS 0x00000030

#define THIS ((DemoMoonend*)thisx)

void DemoMoonend_Init(Actor* thisx, GlobalContext* globalCtx);
void DemoMoonend_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DemoMoonend_Update(Actor* thisx, GlobalContext* globalCtx);
void DemoMoonend_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Demo_Moonend_InitVars = {
    ACTOR_DEMO_MOONEND,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_MOONEND,
    sizeof(DemoMoonend),
    (ActorFunc)DemoMoonend_Init,
    (ActorFunc)DemoMoonend_Destroy,
    (ActorFunc)DemoMoonend_Update,
    (ActorFunc)DemoMoonend_Draw,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Moonend/DemoMoonend_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Moonend/DemoMoonend_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Moonend/func_80C17B50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Moonend/func_80C17B60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Moonend/func_80C17C48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Moonend/DemoMoonend_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Moonend/func_80C17E70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Moonend/func_80C17EE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Moonend/DemoMoonend_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Moonend/func_80C17FCC.s")
