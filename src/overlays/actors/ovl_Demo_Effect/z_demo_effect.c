#include "z_demo_effect.h"

#define FLAGS 0x00000030

#define THIS ((DemoEffect*)thisx)

void DemoEffect_Init(Actor* thisx, GlobalContext* globalCtx);
void DemoEffect_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DemoEffect_Update(Actor* thisx, GlobalContext* globalCtx);

/*
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
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Effect_0x808CD740/DemoEffect_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Effect_0x808CD740/DemoEffect_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Effect_0x808CD740/func_808CD940.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Effect_0x808CD740/func_808CD998.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Effect_0x808CD740/func_808CDAD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Effect_0x808CD740/func_808CDBDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Effect_0x808CD740/func_808CDCEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Effect_0x808CD740/func_808CDD70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Effect_0x808CD740/func_808CDDE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Effect_0x808CD740/DemoEffect_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Effect_0x808CD740/func_808CDE78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Effect_0x808CD740/func_808CDFF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Effect_0x808CD740/func_808CE078.asm")
