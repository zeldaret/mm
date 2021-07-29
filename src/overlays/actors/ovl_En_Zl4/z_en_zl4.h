#ifndef Z_EN_ZL4_H
#define Z_EN_ZL4_H

#include "global.h"

struct EnZl4;

typedef void (*EnZl4ActionFunc)(struct EnZl4* this, GlobalContext* globalCtx);

typedef struct EnZl4 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x14C];
    /* 0x0290 */ EnZl4ActionFunc actionFunc;
    /* 0x0294 */ char unk_294[0x60];
} EnZl4; // size = 0x2F4

extern const ActorInit En_Zl4_InitVars;

#endif // Z_EN_ZL4_H
