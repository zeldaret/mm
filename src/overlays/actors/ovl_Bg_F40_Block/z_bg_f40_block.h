#ifndef Z_BG_F40_BLOCK_H
#define Z_BG_F40_BLOCK_H

#include "global.h"

struct BgF40Block;

typedef void (*BgF40BlockActionFunc)(struct BgF40Block*, GlobalContext*);

#define BGF40BLOCK_GET_PATH(thisx) (((thisx)->params & 0x1FC) >> 2)
#define BGF40BLOCK_GET_SWITCHFLAG(thisx) (((thisx)->params & 0xFE00) >> 9)

typedef struct BgF40Block {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ Path* path;
    /* 0x0160 */ s32 unk_160;
    /* 0x0164 */ s32 unk_164;
    /* 0x0168 */ s32 unk_168;
    /* 0x016C */ BgF40BlockActionFunc actionFunc;
} BgF40Block; // size = 0x170

extern const ActorInit Bg_F40_Block_InitVars;

#endif // Z_BG_F40_BLOCK_H
