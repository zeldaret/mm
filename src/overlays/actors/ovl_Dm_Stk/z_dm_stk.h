#ifndef _Z_DM_STK_H_
#define _Z_DM_STK_H_

#include <global.h>

struct DmStk;

typedef struct DmStk {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1F8];
} DmStk; // size = 0x33C

extern const ActorInit Dm_Stk_InitVars;

#endif
