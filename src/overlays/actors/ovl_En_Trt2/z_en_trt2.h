#ifndef Z_EN_TRT2_H
#define Z_EN_TRT2_H

#include "global.h"

struct EnTrt2;

typedef void (*EnTrt2ActionFunc)(struct EnTrt2* this, GlobalContext* globalCtx);

typedef struct EnTrt2 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnTrt2ActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x294];
} EnTrt2; // size = 0x3DC

extern const ActorInit En_Trt2_InitVars;

#endif // Z_EN_TRT2_H
