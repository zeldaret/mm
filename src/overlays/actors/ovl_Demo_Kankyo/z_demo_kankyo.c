/*
 * File: z_demo_kankyo.c
 * Overlay: ovl_Demo_Kankyo
 * Description: Background Lost Woods Particles
 */

#include "z_demo_kankyo.h"

#define FLAGS 0x00000030

#define THIS ((DemoKankyo*)thisx)

void DemoKankyo_Init(Actor* thisx, GlobalContext* globalCtx);
void DemoKankyo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DemoKankyo_Update(Actor* thisx, GlobalContext* globalCtx);
void DemoKankyo_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_808CF06C(DemoKankyo* this, GlobalContext* globalCtx);
void func_808CF0CC(DemoKankyo* this, GlobalContext* globalCtx);

void DemoKankyo_SetupAction(DemoKankyo* this, DemoKankyoActionFunc actionFunc);

#if 0
const ActorInit Demo_Kankyo_InitVars = {
    ACTOR_DEMO_KANKYO,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(DemoKankyo),
    (ActorFunc)DemoKankyo_Init,
    (ActorFunc)DemoKankyo_Destroy,
    (ActorFunc)DemoKankyo_Update,
    (ActorFunc)DemoKankyo_Draw,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Kankyo/DemoKankyo_SetupAction.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Kankyo/func_808CE45C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Kankyo/func_808CF06C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Kankyo/func_808CF0CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Kankyo/DemoKankyo_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Kankyo/DemoKankyo_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Kankyo/DemoKankyo_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Kankyo/func_808CF970.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Kankyo/func_808CFE04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Kankyo/DemoKankyo_Draw.s")
