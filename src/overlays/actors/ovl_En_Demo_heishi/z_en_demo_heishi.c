#include "z_en_demo_heishi.h"

#define FLAGS 0x00000009

#define THIS ((EnDemoheishi*)thisx)

void EnDemoheishi_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDemoheishi_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDemoheishi_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDemoheishi_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Demo_heishi_InitVars = {
    ACTOR_EN_DEMO_HEISHI,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_SDN,
    sizeof(EnDemoheishi),
    (ActorFunc)EnDemoheishi_Init,
    (ActorFunc)EnDemoheishi_Destroy,
    (ActorFunc)EnDemoheishi_Update,
    (ActorFunc)EnDemoheishi_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Demo_heishi_0x80BE9510/EnDemoheishi_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Demo_heishi_0x80BE9510/EnDemoheishi_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Demo_heishi_0x80BE9510/func_80BE95EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Demo_heishi_0x80BE9510/func_80BE9678.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Demo_heishi_0x80BE9510/func_80BE970C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Demo_heishi_0x80BE9510/func_80BE975C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Demo_heishi_0x80BE9510/func_80BE97F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Demo_heishi_0x80BE9510/func_80BE980C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Demo_heishi_0x80BE9510/EnDemoheishi_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Demo_heishi_0x80BE9510/func_80BE9974.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Demo_heishi_0x80BE9510/EnDemoheishi_Draw.asm")
