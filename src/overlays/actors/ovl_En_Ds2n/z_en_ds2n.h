#ifndef Z_EN_DS2N_H
#define Z_EN_DS2N_H

#include "global.h"

struct EnDs2n;

typedef void (*EnDs2nActionFunc)(struct EnDs2n*, GlobalContext*);

typedef struct EnDs2n {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x90];
    /* 0x01D4 */ EnDs2nActionFunc actionFunc;
    /* 0x01D8 */ char unk_1D8[0x5C];
} EnDs2n; // size = 0x234

extern const ActorInit En_Ds2n_InitVars;

#endif // Z_EN_DS2N_H
