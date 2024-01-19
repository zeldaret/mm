/*
 * File: z_bg_market_step.c
 * Overlay: ovl_Bg_Market_Step
 * Description: West Clocktown - most scenery
 */

#include "z_bg_market_step.h"
#include "objects/object_market_obj/object_market_obj.h"

#define FLAGS (ACTOR_FLAG_20 | ACTOR_FLAG_10000000)

#define THIS ((BgMarketStep*)thisx)

void BgMarketStep_Init(Actor* thisx, PlayState* play);
void BgMarketStep_Draw(Actor* thisx, PlayState* play);

ActorInit Bg_Market_Step_InitVars = {
    /**/ ACTOR_BG_MARKET_STEP,
    /**/ ACTORCAT_BG,
    /**/ FLAGS,
    /**/ OBJECT_MARKET_OBJ,
    /**/ sizeof(BgMarketStep),
    /**/ BgMarketStep_Init,
    /**/ Actor_Noop,
    /**/ Actor_Noop,
    /**/ BgMarketStep_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 1, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 1, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 1000, ICHAIN_STOP),
};

Gfx* sMarketDLs[] = {
    gWestClockTownMarketDayDL,
    gWestClockTownMarketNightDL,
};

Gfx* sBankAdvertisementsAndDoorDLs[] = {
    gWestClockTownMarketBankAdvertisementsAndDoorDayDL,
    gWestClockTownMarketBankAdvertisementsAndDoorNightDL,
};

void BgMarketStep_Init(Actor* thisx, PlayState* play) {
    BgMarketStep* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
}

void BgMarketStep_Draw(Actor* thisx, PlayState* play) {
    s32 timeOfDay = BG_MARKET_STEP_GET_TIME_OF_DAY(thisx);

    Gfx_DrawDListOpa(play, sMarketDLs[timeOfDay]);
    Gfx_DrawDListOpa(play, sBankAdvertisementsAndDoorDLs[timeOfDay]);
}
