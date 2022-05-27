#ifndef Z_EN_BB_H
#define Z_EN_BB_H

#include "global.h"

struct EnBb;

typedef void (*EnBbActionFunc)(struct EnBb*, GlobalContext*);

typedef struct EnBb {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x104];
    /* 0x0248 */ EnBbActionFunc actionFunc;
    /* 0x024C */ char unk_24C[0x100];
} EnBb; // size = 0x34C

extern const ActorInit En_Bb_InitVars;

#endif // Z_EN_BB_H
