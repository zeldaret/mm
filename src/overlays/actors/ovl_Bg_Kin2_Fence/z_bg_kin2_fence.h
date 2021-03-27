#ifndef Z_BG_KIN2_FENCE_H
#define Z_BG_KIN2_FENCE_H

#include <global.h>

struct BgKin2Fence;

typedef struct BgKin2Fence {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ ColliderJntSph collider;
    /* 0x15C */ char unk_144[0x108];
} BgKin2Fence; // size = 0x284

extern const ActorInit Bg_Kin2_Fence_InitVars;

#endif // Z_BG_KIN2_FENCE_H
