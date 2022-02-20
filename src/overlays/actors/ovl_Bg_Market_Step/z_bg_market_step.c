/*
 * File: z_bg_market_step.c
 * Overlay: ovl_Bg_Market_Step
 * Description: West Clocktown - most scenery
 */

#include "z_bg_market_step.h"
#include "objects/object_market_obj/object_market_obj.h"

#define FLAGS (ACTOR_FLAG_20 | ACTOR_FLAG_10000000)

#define THIS ((BgMarketStep*)thisx)

void BgMarketStep_Init(Actor* thisx, GlobalContext* globalCtx);
void BgMarketStep_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Bg_Market_Step_InitVars = {
    ACTOR_BG_MARKET_STEP,  ACTORCAT_BG,           FLAGS,
    OBJECT_MARKET_OBJ,     sizeof(BgMarketStep),  (ActorFunc)BgMarketStep_Init,
    (ActorFunc)Actor_Noop, (ActorFunc)Actor_Noop, (ActorFunc)BgMarketStep_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 1, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 1, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 1000, ICHAIN_STOP),
};

Gfx* D_80AF0120[] = { object_market_obj_DL_01F050, object_market_obj_DL_018DA0 };
Gfx* D_80AF0128[] = { object_market_obj_DL_01EF10, object_market_obj_DL_018C60 };

void BgMarketStep_Init(Actor* thisx, GlobalContext* globalCtx) {
    BgMarketStep* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
}
void BgMarketStep_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 index = thisx->params & 1;

    Gfx_DrawDListOpa(globalCtx, D_80AF0120[index]);
    Gfx_DrawDListOpa(globalCtx, D_80AF0128[index]);
}
