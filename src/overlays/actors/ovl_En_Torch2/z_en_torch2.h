#ifndef Z_EN_TORCH2_H
#define Z_EN_TORCH2_H

#include <global.h>

struct EnTorch2;

typedef struct EnTorch2 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider;
    /* 0x190 */ u8 step;
    /* 0x191 */ u8 framesUntilNextStep;
    /* 0x192 */ s16 alpha;
} EnTorch2; // size = 0x194

extern const ActorInit En_Torch2_InitVars;

#endif // Z_EN_TORCH2_H
