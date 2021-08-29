#ifndef Z_EN_HOLL_H
#define Z_EN_HOLL_H

#include "global.h"

struct EnHoll;

typedef void (*EnHollActionFunc)(struct EnHoll*, GlobalContext*);

typedef struct EnHoll {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x4];
    /* 0x0148 */ EnHollActionFunc actionFunc;
} EnHoll; // size = 0x14C

extern const ActorInit En_Holl_InitVars;

#endif // Z_EN_HOLL_H
