#ifndef Z_EN_TRT_H
#define Z_EN_TRT_H

#include "global.h"

struct EnTrt;

typedef void (*EnTrtActionFunc)(struct EnTrt* this, GlobalContext* globalCtx);

typedef struct EnTrt {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnTrtActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x2E8];
} EnTrt; // size = 0x430

extern const ActorInit En_Trt_InitVars;

#endif // Z_EN_TRT_H
