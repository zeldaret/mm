#ifndef _Z_EN_TRT_H_
#define _Z_EN_TRT_H_

#include <global.h>

struct EnTrt;

typedef struct EnTrt {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2EC];
} EnTrt; // size = 0x430

extern const ActorInit En_Trt_InitVars;

#endif
