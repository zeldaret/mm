#ifndef _Z_BG_SPOUT_FIRE_H_
#define _Z_BG_SPOUT_FIRE_H_

#include <global.h>

struct BgSpoutFire;

typedef struct BgSpoutFire {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x54];
} BgSpoutFire; // size = 0x198

extern const ActorInit Bg_Spout_Fire_InitVars;

#endif
