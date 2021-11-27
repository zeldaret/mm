/*
 * File: z_en_test5.c
 * Overlay: ovl_En_Test5
 * Description: Spring Water
 */

#include "z_en_test5.h"

#define FLAGS 0x00000010

#define THIS ((EnTest5*)thisx)

void EnTest5_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTest5_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTest5_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80A90478(EnTest5* this, GlobalContext* globalCtx);

void EnTest5_SetupAction(EnTest5* this, EnTest5ActionFunc actionFunc);

#if 0
const ActorInit En_Test5_InitVars = {
    ACTOR_EN_TEST5,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnTest5),
    (ActorFunc)EnTest5_Init,
    (ActorFunc)EnTest5_Destroy,
    (ActorFunc)EnTest5_Update,
    (ActorFunc)NULL,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test5/EnTest5_SetupAction.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test5/EnTest5_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test5/EnTest5_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test5/func_80A90478.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test5/EnTest5_Update.s")
