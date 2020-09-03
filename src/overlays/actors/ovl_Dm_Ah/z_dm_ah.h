#ifndef _Z_DM_AH_H_
#define _Z_DM_AH_H_

#include <global.h>

struct DmAh;

typedef struct DmAh {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x15C];
} DmAh; // size = 0x2A0

extern const ActorInit Dm_Ah_InitVars;

#endif
