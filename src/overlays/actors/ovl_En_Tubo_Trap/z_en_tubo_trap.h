#ifndef Z_EN_TUBO_TRAP_H
#define Z_EN_TUBO_TRAP_H

#include "global.h"

struct EnTuboTrap;

typedef void (*EnTuboTrapActionFunc)(struct EnTuboTrap*, GlobalContext*);

typedef struct EnTuboTrap {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnTuboTrapActionFunc actionFunc;
    /* 0x0148 */ f32 targetHeight;
    /* 0x014C */ Vec3f originPos;
    /* 0x0158 */ ColliderCylinder collider;
} EnTuboTrap; // size = 0x1A4

extern const ActorInit En_Tubo_Trap_InitVars;



#endif // Z_EN_TUBO_TRAP_H
