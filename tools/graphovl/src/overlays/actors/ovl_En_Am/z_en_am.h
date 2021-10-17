#ifndef Z_EN_AM_H
#define Z_EN_AM_H

#include "global.h"

struct EnAm;

typedef void (*EnAmActionFunc)(struct EnAm*, GlobalContext*);

typedef struct EnAm {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xEC];
    /* 0x0230 */ EnAmActionFunc actionFunc;
    /* 0x0234 */ char unk_234[0x14C];
} EnAm; // size = 0x380

extern const ActorInit En_Am_InitVars;

#endif // Z_EN_AM_H
