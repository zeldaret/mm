#ifndef Z_EN_TEST5_H
#define Z_EN_TEST5_H

#include "global.h"

struct EnTest5;

typedef void (*EnTest5ActionFunc)(struct EnTest5* this, GlobalContext* globalCtx);

typedef struct EnTest5 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x14];
    /* 0x0158 */ EnTest5ActionFunc actionFunc;
} EnTest5; // size = 0x15C

extern const ActorInit En_Test5_InitVars;

#endif // Z_EN_TEST5_H
