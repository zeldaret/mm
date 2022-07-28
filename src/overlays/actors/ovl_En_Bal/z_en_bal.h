#ifndef Z_EN_BAL_H
#define Z_EN_BAL_H

#include "global.h"

struct EnBal;

typedef void (*EnBalActionFunc)(struct EnBal*, PlayState*);

typedef struct EnBal {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x48];
    /* 0x18C */ EnBalActionFunc actionFunc;
    /* 0x190 */ char unk_190[0x224];
} EnBal; // size = 0x3B4

extern const ActorInit En_Bal_InitVars;

#endif // Z_EN_BAL_H
