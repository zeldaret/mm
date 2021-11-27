#ifndef Z_DM_BAL_H
#define Z_DM_BAL_H

#include "global.h"

struct DmBal;

typedef void (*DmBalActionFunc)(struct DmBal*, GlobalContext*);

typedef struct DmBal {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ DmBalActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x1B0];
} DmBal; // size = 0x33C

extern const ActorInit Dm_Bal_InitVars;

#endif // Z_DM_BAL_H
