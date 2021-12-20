#ifndef Z_BG_FIRE_WALL_H
#define Z_BG_FIRE_WALL_H

#include "global.h"

struct BgFireWall;

typedef void (*BgFireWallActionFunc)(struct BgFireWall*, GlobalContext*);

typedef struct BgFireWall {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ BgFireWallActionFunc actionFunc;
    /* 0x0148 */ char unk_148[0x68];
} BgFireWall; // size = 0x1B0

extern const ActorInit Bg_Fire_Wall_InitVars;

#endif // Z_BG_FIRE_WALL_H
