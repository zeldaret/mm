#ifndef Z_EFF_LASTDAY_H
#define Z_EFF_LASTDAY_H

#include "global.h"

struct EffLastday;

typedef void (*EffLastdayActionFunc)(struct EffLastday*, GlobalContext*);

typedef struct EffLastday {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x10];
    /* 0x0154 */ EffLastdayActionFunc actionFunc;
} EffLastday; // size = 0x158

extern const ActorInit Eff_Lastday_InitVars;

#endif // Z_EFF_LASTDAY_H
