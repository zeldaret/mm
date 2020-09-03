#ifndef _Z_DM_BAL_H_
#define _Z_DM_BAL_H_

#include <global.h>

struct DmBal;

typedef struct DmBal {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1F8];
} DmBal; // size = 0x33C

extern const ActorInit Dm_Bal_InitVars;

#endif
