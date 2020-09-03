#ifndef Z_BG_KIN2_FENCE_H
#define Z_BG_KIN2_FENCE_H

#include <global.h>

struct BgKin2Fence;

typedef struct BgKin2Fence {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x140];
} BgKin2Fence; // size = 0x284

extern const ActorInit Bg_Kin2_Fence_InitVars;

#endif // Z_BG_KIN2_FENCE_H
