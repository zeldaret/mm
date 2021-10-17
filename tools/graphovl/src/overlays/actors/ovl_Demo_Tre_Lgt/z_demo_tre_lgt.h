#ifndef Z_DEMO_TRE_LGT_H
#define Z_DEMO_TRE_LGT_H

#include "global.h"

struct DemoTreLgt;

typedef struct DemoTreLgt {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x34];
} DemoTreLgt; // size = 0x178

extern const ActorInit Demo_Tre_Lgt_InitVars;

#endif // Z_DEMO_TRE_LGT_H
