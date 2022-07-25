#ifndef Z_EN_STONE_HEISHI_H
#define Z_EN_STONE_HEISHI_H

#include "global.h"

struct EnStoneheishi;

typedef void (*EnStoneheishiActionFunc)(struct EnStoneheishi*, PlayState*);

typedef struct EnStoneheishi {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x110];
    /* 0x254 */ EnStoneheishiActionFunc actionFunc;
    /* 0x258 */ char unk_258[0x6C];
} EnStoneheishi; // size = 0x2C4

#endif // Z_EN_STONE_HEISHI_H
