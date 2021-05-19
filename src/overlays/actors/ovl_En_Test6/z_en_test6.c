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
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnTest6),
    (ActorFunc)EnTest6_Init,
    (ActorFunc)EnTest6_Destroy,
    (ActorFunc)EnTest6_Update,
    (ActorFunc)EnTest6_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test6_0x80A90730/func_80A90730.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test6_0x80A90730/func_80A90C08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test6_0x80A90730/func_80A90C34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test6_0x80A90730/func_80A90C54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test6_0x80A90730/func_80A90D20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test6_0x80A90730/func_80A90D34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test6_0x80A90730/func_80A90FC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test6_0x80A90730/func_80A91324.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test6_0x80A90730/EnTest6_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test6_0x80A90730/EnTest6_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test6_0x80A90730/func_80A9156C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test6_0x80A90730/func_80A91690.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test6_0x80A90730/func_80A916F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test6_0x80A90730/func_80A91760.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test6_0x80A90730/func_80A920C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test6_0x80A90730/func_80A92118.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test6_0x80A90730/func_80A92188.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test6_0x80A90730/EnTest6_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test6_0x80A90730/func_80A92950.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test6_0x80A90730/func_80A93298.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test6_0x80A90730/func_80A9369C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test6_0x80A90730/func_80A939E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test6_0x80A90730/EnTest6_Draw.asm")
