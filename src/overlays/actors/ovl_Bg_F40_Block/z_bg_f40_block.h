#ifndef Z_BG_F40_BLOCK_H
#define Z_BG_F40_BLOCK_H

#include "global.h"

struct BgF40Block;

typedef void (*BgF40BlockActionFunc)(struct BgF40Block* this, GlobalContext* globalCtx);

typedef struct BgF40Block {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x28];
    /* 0x016C */ BgF40BlockActionFunc actionFunc;
} BgF40Block; // size = 0x170

extern const ActorInit Bg_F40_Block_InitVars;

#endif // Z_BG_F40_BLOCK_H
