#ifndef Z_BG_DBLUE_WATERFALL_H
#define Z_BG_DBLUE_WATERFALL_H

#include "global.h"

struct BgDblueWaterfall;

typedef struct BgDblueWaterfall {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x68];
} BgDblueWaterfall; // size = 0x1AC

extern const ActorInit Bg_Dblue_Waterfall_InitVars;

#endif // Z_BG_DBLUE_WATERFALL_H
