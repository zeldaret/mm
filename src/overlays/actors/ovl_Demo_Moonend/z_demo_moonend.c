#include "z_demo_moonend.h"

#define FLAGS 0x00000030

#define THIS ((DemoMoonend*)thisx)

void DemoMoonend_Init(Actor* thisx, GlobalContext* globalCtx);
void DemoMoonend_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DemoMoonend_Update(Actor* thisx, GlobalContext* globalCtx);
void DemoMoonend_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
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
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Moonend_0x80C17A10/DemoMoonend_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Moonend_0x80C17A10/DemoMoonend_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Moonend_0x80C17A10/func_80C17B50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Moonend_0x80C17A10/func_80C17B60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Moonend_0x80C17A10/func_80C17C48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Moonend_0x80C17A10/DemoMoonend_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Moonend_0x80C17A10/func_80C17E70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Moonend_0x80C17A10/func_80C17EE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Moonend_0x80C17A10/DemoMoonend_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Moonend_0x80C17A10/func_80C17FCC.asm")
