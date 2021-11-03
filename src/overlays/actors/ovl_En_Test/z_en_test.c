/*
 * File: z_en_test.c
 * Overlay: ovl_En_Test
 * Description: Goron crater mark
 */

#include "z_en_test.h"

#define FLAGS 0x00000010

#define THIS ((EnTest*)thisx)

void EnTest_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTest_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTest_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTest_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Test_InitVars = {
    ACTOR_EN_TEST,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnTest),
    (ActorFunc)EnTest_Init,
    (ActorFunc)EnTest_Destroy,
    (ActorFunc)EnTest_Update,
    (ActorFunc)EnTest_Draw,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test/func_80862B70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test/func_80862CBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test/func_80862EDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test/func_80863048.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test/EnTest_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test/EnTest_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test/EnTest_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test/func_808634B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test/EnTest_Draw.s")
