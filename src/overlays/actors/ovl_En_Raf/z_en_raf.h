#ifndef Z_EN_RAF_H
#define Z_EN_RAF_H

#include "global.h"

struct EnRaf;

typedef void (*EnRafActionFunc)(struct EnRaf*, GlobalContext*);

typedef struct EnRaf {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xEC];
    /* 0x0230 */ EnRafActionFunc actionFunc;
    /* 0x0234 */ char unk_234[0x8B0];
} EnRaf; // size = 0xAE4

extern const ActorInit En_Raf_InitVars;

#endif // Z_EN_RAF_H
