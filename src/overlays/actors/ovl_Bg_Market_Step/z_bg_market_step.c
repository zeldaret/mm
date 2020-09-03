#include "z_bg_market_step.h"

#define FLAGS 0x10000020

#define THIS ((BgMarketStep*)thisx)

void BgMarketStep_Init(Actor* thisx, GlobalContext* globalCtx);
void BgMarketStep_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Market_Step_InitVars = {
    ACTOR_BG_MARKET_STEP,
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_MARKET_OBJ,
    sizeof(BgMarketStep),
    (ActorFunc)BgMarketStep_Init,
    (ActorFunc)func_800BDFB0,
    (ActorFunc)func_800BDFB0,
    (ActorFunc)BgMarketStep_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Market_Step_0x80AF0060/BgMarketStep_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Market_Step_0x80AF0060/BgMarketStep_Draw.asm")
