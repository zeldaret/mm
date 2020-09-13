#ifndef Z_BG_TOBIRA01_H
#define Z_BG_TOBIRA01_H

#include <global.h>

struct BgTobira01;

typedef struct BgTobira01 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2C];
} BgTobira01; // size = 0x170

extern const ActorInit Bg_Tobira01_InitVars;

#endif // Z_BG_TOBIRA01_H
