#include "z_en_test2.h"

#define FLAGS 0x00000090

#define THIS ((EnTest2*)thisx)

void EnTest2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTest2_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Test2_InitVars = {
    ACTOR_EN_TEST2,
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnTest2),
    (ActorFunc)EnTest2_Init,
    (ActorFunc)Actor_NoOp,
    (ActorFunc)EnTest2_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test2/EnTest2_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test2/EnTest2_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test2/func_80A3E4EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test2/func_80A3E524.s")
