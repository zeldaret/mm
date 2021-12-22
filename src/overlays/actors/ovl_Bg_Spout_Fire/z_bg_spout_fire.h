#ifndef Z_BG_SPOUT_FIRE_H
#define Z_BG_SPOUT_FIRE_H

#include "global.h"

struct BgSpoutFire;

typedef void (*BgSpoutFireActionFunc)(struct BgSpoutFire*, GlobalContext*);

typedef struct BgSpoutFire {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ BgSpoutFireActionFunc actionFunc;
    /* 0x0148 */ char unk_148[0x50];
} BgSpoutFire; // size = 0x198

extern const ActorInit Bg_Spout_Fire_InitVars;

#endif // Z_BG_SPOUT_FIRE_H
