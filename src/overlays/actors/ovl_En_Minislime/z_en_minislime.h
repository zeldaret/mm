#ifndef Z_EN_MINISLIME_H
#define Z_EN_MINISLIME_H

#include "global.h"

struct EnMinislime;

typedef void (*EnMinislimeActionFunc)(struct EnMinislime* this, GlobalContext* globalCtx);

typedef struct EnMinislime {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnMinislimeActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x64];
} EnMinislime; // size = 0x1AC

extern const ActorInit En_Minislime_InitVars;

#endif // Z_EN_MINISLIME_H
