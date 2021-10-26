#ifndef Z_EN_WARP_UZU_H
#define Z_EN_WARP_UZU_H

#include "global.h"

struct EnWarpUzu;

typedef void (*EnWarpUzuActionFunc)(struct EnWarpUzu*, GlobalContext*);

typedef struct EnWarpUzu {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnWarpUzuActionFunc actionFunc;
    /* 0x148 */ ColliderCylinder collider;
} EnWarpUzu; // size = 0x194

extern const ActorInit En_Warp_Uzu_InitVars;

#endif // Z_EN_WARP_UZU_H
