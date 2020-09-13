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
    ACTORTYPE_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnTest),
    (ActorFunc)EnTest_Init,
    (ActorFunc)EnTest_Destroy,
    (ActorFunc)EnTest_Update,
    (ActorFunc)EnTest_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Test_0x80862B70/func_80862B70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test_0x80862B70/func_80862CBC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test_0x80862B70/func_80862EDC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test_0x80862B70/func_80863048.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test_0x80862B70/EnTest_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test_0x80862B70/EnTest_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test_0x80862B70/EnTest_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test_0x80862B70/func_808634B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test_0x80862B70/EnTest_Draw.asm")
