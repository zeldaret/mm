/*
 * File: z_demo_getitem.c
 * Overlay: ovl_Demo_Getitem
 * Description: Cutscene object for Great Fairy's Mask and Great Fairy's Sword
 */

#include "z_demo_getitem.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DemoGetitem*)thisx)

void DemoGetitem_Init(Actor* thisx, GlobalContext* globalCtx);
void DemoGetitem_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DemoGetitem_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Demo_Getitem_InitVars = {
    ACTOR_DEMO_GETITEM,
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(DemoGetitem),
    (ActorFunc)DemoGetitem_Init,
    (ActorFunc)DemoGetitem_Destroy,
    (ActorFunc)DemoGetitem_Update,
    (ActorFunc)NULL,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Getitem/DemoGetitem_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Getitem/DemoGetitem_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Getitem/func_80A4FB10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Getitem/func_80A4FB68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Getitem/DemoGetitem_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Getitem/func_80A4FCF0.s")
