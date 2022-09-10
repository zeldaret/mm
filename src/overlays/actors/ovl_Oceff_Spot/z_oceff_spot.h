#ifndef Z_OCEFF_SPOT_H
#define Z_OCEFF_SPOT_H

#include "global.h"

struct OceffSpot;

typedef void (*OceffSpotActionFunc)(struct OceffSpot*, PlayState*);

typedef struct OceffSpot {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x30];
    /* 0x174 */ OceffSpotActionFunc actionFunc;
} OceffSpot; // size = 0x178

extern const ActorInit Oceff_Spot_InitVars;

#endif // Z_OCEFF_SPOT_H
