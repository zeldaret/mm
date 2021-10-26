#include "z_bg_market_step.h"

#define FLAGS 0x10000020

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

extern Gfx D_0601F050[];
extern Gfx D_06018DA0[];
extern Gfx D_0601EF10[];
extern Gfx D_06018C60[];
Gfx* D_80AF0120[] = { D_0601F050, D_06018DA0 };
Gfx* D_80AF0128[] = { D_0601EF10, D_06018C60 };

void BgMarketStep_Init(Actor* thisx, GlobalContext* globalCtx) {
    BgMarketStep* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
}
void BgMarketStep_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 index = thisx->params & 1;

    func_800BDFC0(globalCtx, D_80AF0120[index]);
    func_800BDFC0(globalCtx, D_80AF0128[index]);
}
