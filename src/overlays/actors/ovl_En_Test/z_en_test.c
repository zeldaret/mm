#include "z_en_test.h"

#define FLAGS 0x00000010

#define THIS ((EnTest*)thisx)

void EnTest_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTest_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTest_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTest_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
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
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test_0x80862B70/func_80862B70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test_0x80862B70/func_80862CBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test_0x80862B70/func_80862EDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test_0x80862B70/func_80863048.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test_0x80862B70/EnTest_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test_0x80862B70/EnTest_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test_0x80862B70/EnTest_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test_0x80862B70/func_808634B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test_0x80862B70/EnTest_Draw.asm")
