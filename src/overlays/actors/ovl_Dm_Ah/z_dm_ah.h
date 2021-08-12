#ifndef Z_DM_AH_H
#define Z_DM_AH_H

#include "global.h"

struct DmAh;

typedef void (*DmAhActionFunc)(struct DmAh*, GlobalContext*);

typedef struct DmAh {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ DmAhActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x114];
} DmAh; // size = 0x2A0

extern const ActorInit Dm_Ah_InitVars;

#endif // Z_DM_AH_H
