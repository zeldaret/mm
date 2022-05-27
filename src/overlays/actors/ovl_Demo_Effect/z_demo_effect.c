/*
 * File: z_demo_effect.c
 * Overlay: ovl_Demo_Effect
 * Description: Various cutscene effects (blue warp in, Great Fairy vanish, etc.)
 */

#include "z_demo_effect.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DemoEffect*)thisx)

void DemoEffect_Init(Actor* thisx, GlobalContext* globalCtx);
void DemoEffect_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DemoEffect_Update(Actor* thisx, GlobalContext* globalCtx);

void func_808CD940(DemoEffect* this, GlobalContext* globalCtx);
void func_808CDBDC(DemoEffect* this, GlobalContext* globalCtx);
void func_808CDCEC(DemoEffect* this, GlobalContext* globalCtx);
void func_808CDD70(DemoEffect* this, GlobalContext* globalCtx);

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
