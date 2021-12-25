#ifndef Z_EN_TEST6_H
#define Z_EN_TEST6_H

#include "global.h"

struct EnTest6;

typedef void (*EnTest6ActionFunc)(struct EnTest6*, GlobalContext*);

typedef struct EnTest6 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnTest6ActionFunc actionFunc;
    /* 0x0148 */ char unk_148[0x140];
} EnTest6; // size = 0x288

extern const ActorInit En_Test6_InitVars;

#endif // Z_EN_TEST6_H
