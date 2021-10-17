#ifndef Z_BG_MARKET_STEP_H
#define Z_BG_MARKET_STEP_H

#include "global.h"

struct BgMarketStep;

typedef struct BgMarketStep {
    /* 0x000 */ Actor actor;
} BgMarketStep; // size = 0x144

extern const ActorInit Bg_Market_Step_InitVars;

#endif // Z_BG_MARKET_STEP_H
