#ifndef Z_BG_IKANA_BLOCK_H
#define Z_BG_IKANA_BLOCK_H

#include "global.h"

struct BgIkanaBlock;

typedef void (*BgIkanaBlockActionFunc)(struct BgIkanaBlock* this, GlobalContext* globalCtx);

typedef struct BgIkanaBlock {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x1C];
    /* 0x0160 */ BgIkanaBlockActionFunc actionFunc;
    /* 0x0164 */ char unk_164[0x1C];
} BgIkanaBlock; // size = 0x180

extern const ActorInit Bg_Ikana_Block_InitVars;

#endif // Z_BG_IKANA_BLOCK_H
