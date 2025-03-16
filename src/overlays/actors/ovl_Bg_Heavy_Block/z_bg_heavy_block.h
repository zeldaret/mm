#ifndef Z_BG_HEAVY_BLOCK_H
#define Z_BG_HEAVY_BLOCK_H

#include "global.h"

struct BgHeavyBlock;

typedef void (*BgHeavyBlockActionFunc)(struct BgHeavyBlock*, PlayState*);

typedef struct BgHeavyBlock {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ char unk_15C[0x16C - 0x15C];
    /* 0x16C */ BgHeavyBlockActionFunc actionFunc;
} BgHeavyBlock; // size = 0x170

#endif // Z_BG_HEAVY_BLOCK_H
