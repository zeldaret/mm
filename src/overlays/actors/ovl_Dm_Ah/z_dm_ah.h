#ifndef Z_DM_AH_H
#define Z_DM_AH_H

#include "global.h"

struct DmAh;

typedef void (*DmAhActionFunc)(struct DmAh*, PlayState*);

typedef struct DmAh {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x44];
    /* 0x188 */ DmAhActionFunc actionFunc;
    /* 0x18C */ char unk_18C[0x114];
} DmAh; // size = 0x2A0

extern const ActorInit Dm_Ah_InitVars;

#endif // Z_DM_AH_H
