#ifndef _Z_EN_TORCH_H_
#define _Z_EN_TORCH_H_

#include <global.h>

struct EnTorch;

typedef struct EnTorch {
    /* 0x000 */ Actor actor;
} EnTorch; // size = 0x144

extern const ActorInit En_Torch_InitVars;

#endif
