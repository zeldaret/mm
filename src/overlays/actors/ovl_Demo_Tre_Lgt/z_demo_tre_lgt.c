/*
 * File: z_demo_tre_lgt.c
 * Overlay: ovl_Demo_Tre_Lgt
 * Description: Light Radiating From Treasure Chest
 */

#include "z_demo_tre_lgt.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((DemoTreLgt*)thisx)

void DemoTreLgt_Init(Actor* thisx, GlobalContext* globalCtx);
void DemoTreLgt_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DemoTreLgt_Update(Actor* thisx, GlobalContext* globalCtx);
void DemoTreLgt_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Demo_Tre_Lgt_InitVars = {
    ACTOR_DEMO_TRE_LGT,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_BOX,
    sizeof(DemoTreLgt),
    (ActorFunc)DemoTreLgt_Init,
    (ActorFunc)DemoTreLgt_Destroy,
    (ActorFunc)DemoTreLgt_Update,
    (ActorFunc)DemoTreLgt_Draw,
};

#endif

extern UNK_TYPE D_06007D78;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Tre_Lgt/DemoTreLgt_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Tre_Lgt/DemoTreLgt_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Tre_Lgt/func_808E0EE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Tre_Lgt/func_808E0EF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Tre_Lgt/func_808E0F4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Tre_Lgt/func_808E0FE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Tre_Lgt/DemoTreLgt_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Tre_Lgt/func_808E12A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Tre_Lgt/DemoTreLgt_Draw.s")
