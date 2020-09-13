#include "z_en_test6.h"

#define FLAGS 0x02200030

#define THIS ((EnTest6*)thisx)

void EnTest6_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTest6_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTest6_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTest6_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Test6_InitVars = {
    ACTOR_EN_TEST6,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnTest6),
    (ActorFunc)EnTest6_Init,
    (ActorFunc)EnTest6_Destroy,
    (ActorFunc)EnTest6_Update,
    (ActorFunc)EnTest6_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Test6_0x80A90730/func_80A90730.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test6_0x80A90730/func_80A90C08.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test6_0x80A90730/func_80A90C34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test6_0x80A90730/func_80A90C54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test6_0x80A90730/func_80A90D20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test6_0x80A90730/func_80A90D34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test6_0x80A90730/func_80A90FC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test6_0x80A90730/func_80A91324.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test6_0x80A90730/EnTest6_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test6_0x80A90730/EnTest6_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test6_0x80A90730/func_80A9156C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test6_0x80A90730/func_80A91690.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test6_0x80A90730/func_80A916F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test6_0x80A90730/func_80A91760.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test6_0x80A90730/func_80A920C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test6_0x80A90730/func_80A92118.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test6_0x80A90730/func_80A92188.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test6_0x80A90730/EnTest6_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test6_0x80A90730/func_80A92950.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test6_0x80A90730/func_80A93298.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test6_0x80A90730/func_80A9369C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test6_0x80A90730/func_80A939E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test6_0x80A90730/EnTest6_Draw.asm")
