#ifndef _Z_BG_IKANA_BLOCK_H_
#define _Z_BG_IKANA_BLOCK_H_

#include <global.h>

struct BgIkanaBlock;

typedef struct BgIkanaBlock {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x3C];
} BgIkanaBlock; // size = 0x180

extern const ActorInit Bg_Ikana_Block_InitVars;

#endif
