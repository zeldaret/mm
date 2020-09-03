#ifndef _Z_OCEFF_SPOT_H_
#define _Z_OCEFF_SPOT_H_

#include <global.h>

struct OceffSpot;

typedef struct OceffSpot {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x34];
} OceffSpot; // size = 0x178

extern const ActorInit Oceff_Spot_InitVars;

#endif
