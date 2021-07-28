#include "z_demo_effect.h"

#define FLAGS 0x00000030

#define THIS ((DemoEffect*)thisx)

void DemoEffect_Init(Actor* thisx, GlobalContext* globalCtx);
void DemoEffect_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DemoEffect_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Demo_Effect_InitVars = {
    ACTOR_DEMO_EFFECT,
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(DemoEffect),
    (ActorFunc)DemoEffect_Init,
    (ActorFunc)DemoEffect_Destroy,
    (ActorFunc)DemoEffect_Update,
    (ActorFunc)NULL,
};

#endif

extern UNK_TYPE D_06000050;
extern UNK_TYPE D_06000060;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Effect/DemoEffect_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Effect/DemoEffect_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Effect/func_808CD940.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Effect/func_808CD998.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Effect/func_808CDAD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Effect/func_808CDBDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Effect/func_808CDCEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Effect/func_808CDD70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Effect/func_808CDDE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Effect/DemoEffect_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Effect/func_808CDE78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Effect/func_808CDFF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Effect/func_808CE078.s")
