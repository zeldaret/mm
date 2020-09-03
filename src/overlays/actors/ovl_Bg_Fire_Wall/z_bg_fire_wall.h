#ifndef _Z_BG_FIRE_WALL_H_
#define _Z_BG_FIRE_WALL_H_

#include <global.h>

struct BgFireWall;

typedef struct BgFireWall {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x6C];
} BgFireWall; // size = 0x1B0

extern const ActorInit Bg_Fire_Wall_InitVars;

#endif
