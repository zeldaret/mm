#ifndef Z_BG_IKANA_BOMBWALL_H
#define Z_BG_IKANA_BOMBWALL_H

#include "global.h"

struct BgIkanaBombwall;

typedef void (*BgIkanaBombwallActionFunc)(struct BgIkanaBombwall*, PlayState*);

#define BGIKANABOMBWALL_GET_SWITCHFLAG(thisx) ((thisx)->params & 0x7F)
#define BGIKANABOMBWALL_GET_100(thisx) (((thisx)->params >> 8) & 1)

typedef struct BgIkanaBombwall {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ ColliderCylinder collider;
    /* 0x01A8 */ BgIkanaBombwallActionFunc actionFunc;
    /* 0x01AC */ s8 unk_1AC;
} BgIkanaBombwall; // size = 0x1B0

extern const ActorInit Bg_Ikana_Bombwall_InitVars;

#endif // Z_BG_IKANA_BOMBWALL_H
