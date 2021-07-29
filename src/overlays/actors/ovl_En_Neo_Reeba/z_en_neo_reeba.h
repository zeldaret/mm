#ifndef Z_EN_NEO_REEBA_H
#define Z_EN_NEO_REEBA_H

#include "global.h"

struct EnNeoReeba;

typedef void (*EnNeoReebaActionFunc)(struct EnNeoReeba* this, GlobalContext* globalCtx);

typedef struct EnNeoReeba {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x168];
    /* 0x02AC */ EnNeoReebaActionFunc actionFunc;
    /* 0x02B0 */ char unk_2B0[0x64];
} EnNeoReeba; // size = 0x314

extern const ActorInit En_Neo_Reeba_InitVars;

#endif // Z_EN_NEO_REEBA_H
