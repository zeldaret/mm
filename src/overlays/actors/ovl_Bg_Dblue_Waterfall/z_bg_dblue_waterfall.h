#ifndef Z_BG_DBLUE_WATERFALL_H
#define Z_BG_DBLUE_WATERFALL_H

#include "global.h"

struct BgDblueWaterfall;

typedef void (*BgDblueWaterfallActionFunc)(struct BgDblueWaterfall*, GlobalContext*);

typedef struct BgDblueWaterfall {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x50];
    /* 0x0194 */ BgDblueWaterfallActionFunc actionFunc;
    /* 0x0198 */ char unk_198[0x14];
} BgDblueWaterfall; // size = 0x1AC

extern const ActorInit Bg_Dblue_Waterfall_InitVars;

#endif // Z_BG_DBLUE_WATERFALL_H
