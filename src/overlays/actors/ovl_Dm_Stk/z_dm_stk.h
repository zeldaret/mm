#ifndef Z_DM_STK_H
#define Z_DM_STK_H

#include "global.h"

struct DmStk;

typedef struct DmStk {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1F8];
} DmStk; // size = 0x33C

extern const ActorInit Dm_Stk_InitVars;

#endif // Z_DM_STK_H
