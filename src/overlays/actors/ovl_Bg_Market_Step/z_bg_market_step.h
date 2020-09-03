#ifndef _Z_BG_MARKET_STEP_H_
#define _Z_BG_MARKET_STEP_H_

#include <global.h>

struct BgMarketStep;

typedef struct BgMarketStep {
    /* 0x000 */ Actor actor;
} BgMarketStep; // size = 0x144

extern const ActorInit Bg_Market_Step_InitVars;

#endif
