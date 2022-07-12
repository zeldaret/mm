#ifndef Z_EN_TUBO_TRAP_H
#define Z_EN_TUBO_TRAP_H

#include "global.h"

struct EnTuboTrap;

typedef void (*EnTuboTrapActionFunc)(struct EnTuboTrap*, PlayState*);

typedef struct EnTuboTrap {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnTuboTrapActionFunc actionFunc;
    /* 0x148 */ f32 targetHeight;
    /* 0x14C */ Vec3f originPos;
    /* 0x158 */ ColliderCylinder collider;
} EnTuboTrap; // size = 0x1A4

extern const ActorInit En_Tubo_Trap_InitVars;

#endif // Z_EN_TUBO_TRAP_H
