#include "z_en_test5.h"

#define FLAGS 0x00000010

#define THIS ((EnTest5*)thisx)

void EnTest5_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTest5_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTest5_Update(Actor* thisx, GlobalContext* globalCtx);

/*
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
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test5_0x80A903B0/func_80A903B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test5_0x80A903B0/EnTest5_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test5_0x80A903B0/EnTest5_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test5_0x80A903B0/func_80A90478.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test5_0x80A903B0/EnTest5_Update.asm")
