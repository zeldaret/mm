#ifndef Z_EN_GG2_H
#define Z_EN_GG2_H

#include "global.h"

struct EnGg2;

typedef void (*EnGg2ActionFunc)(struct EnGg2* this, GlobalContext* globalCtx);

typedef struct EnGg2 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x90];
    /* 0x01D4 */ EnGg2ActionFunc actionFunc;
    /* 0x01D8 */ char unk_1D8[0x138];
} EnGg2; // size = 0x310

extern const ActorInit En_Gg2_InitVars;

#endif // Z_EN_GG2_H
