#ifndef Z_EN_ZOB_H
#define Z_EN_ZOB_H

#include "global.h"

struct EnZob;

typedef void (*EnZobActionFunc)(struct EnZob*, GlobalContext*);

typedef struct EnZob {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x1D0];
    /* 0x0314 */ EnZobActionFunc actionFunc;
} EnZob; // size = 0x318

extern const ActorInit En_Zob_InitVars;

#endif // Z_EN_ZOB_H
