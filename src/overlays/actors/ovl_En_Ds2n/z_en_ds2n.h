#ifndef Z_EN_DS2N_H
#define Z_EN_DS2N_H

#include "global.h"

struct EnDs2n;

typedef void (*EnDs2nActionFunc)(struct EnDs2n*, PlayState*);

typedef struct EnDs2n {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x90];
    /* 0x1D4 */ EnDs2nActionFunc actionFunc;
    /* 0x1D8 */ char unk_1D8[0x5C];
} EnDs2n; // size = 0x234

extern const ActorInit En_Ds2n_InitVars;

#endif // Z_EN_DS2N_H
