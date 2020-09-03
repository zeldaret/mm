#ifndef _Z_BG_OPEN_SPOT_H_
#define _Z_BG_OPEN_SPOT_H_

#include <global.h>

struct BgOpenSpot;

typedef struct BgOpenSpot {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x4];
} BgOpenSpot; // size = 0x148

extern const ActorInit Bg_Open_Spot_InitVars;

#endif
