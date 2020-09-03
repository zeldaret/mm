#ifndef Z_EN_TORCH_H
#define Z_EN_TORCH_H

#include <global.h>

struct EnTorch;

typedef struct EnTorch {
    /* 0x000 */ Actor actor;
} EnTorch; // size = 0x144

extern const ActorInit En_Torch_InitVars;

#endif // Z_EN_TORCH_H
