/*
 * File: z_demo_moonend.c
 * Overlay: ovl_Demo_Moonend
 * Description: Moon Disappearing (cutscene)
 */

#include "z_demo_moonend.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

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

extern UNK_TYPE D_06001214;
extern UNK_TYPE D_0600B540;
extern UNK_TYPE D_060129F0;

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
