#ifndef Z_EN_STONE_HEISHI_H
#define Z_EN_STONE_HEISHI_H

#include "global.h"

struct EnStoneheishi;

typedef struct EnStoneheishi {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x180];
} EnStoneheishi; // size = 0x2C4

extern const ActorInit En_Stone_heishi_InitVars;

#endif // Z_EN_STONE_HEISHI_H
