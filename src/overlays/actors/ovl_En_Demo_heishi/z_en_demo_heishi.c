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
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_SDN,
    sizeof(EnDemoheishi),
    (ActorFunc)EnDemoheishi_Init,
    (ActorFunc)EnDemoheishi_Destroy,
    (ActorFunc)EnDemoheishi_Update,
    (ActorFunc)EnDemoheishi_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Demo_heishi/EnDemoheishi_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Demo_heishi/EnDemoheishi_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Demo_heishi/func_80BE95EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Demo_heishi/func_80BE9678.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Demo_heishi/func_80BE970C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Demo_heishi/func_80BE975C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Demo_heishi/func_80BE97F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Demo_heishi/func_80BE980C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Demo_heishi/EnDemoheishi_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Demo_heishi/func_80BE9974.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Demo_heishi/EnDemoheishi_Draw.s")
