#ifndef Z_BG_F40_BLOCK_H
#define Z_BG_F40_BLOCK_H

#include <global.h>

struct BgF40Block;

typedef struct BgF40Block {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2C];
} BgF40Block; // size = 0x170

extern const ActorInit Bg_F40_Block_InitVars;

#endif // Z_BG_F40_BLOCK_H
