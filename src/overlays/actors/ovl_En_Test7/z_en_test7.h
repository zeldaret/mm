#ifndef Z_EN_TEST7_H
#define Z_EN_TEST7_H

#include "global.h"

struct EnTest7;

typedef void (*EnTest7ActionFunc)(struct EnTest7* this, GlobalContext* globalCtx);

typedef struct EnTest7 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x1D18];
    /* 0x1E5C */ EnTest7ActionFunc actionFunc;
    /* 0x1E60 */ char unk_1E60[0x3C];
} EnTest7; // size = 0x1E9C

extern const ActorInit En_Test7_InitVars;

#endif // Z_EN_TEST7_H
