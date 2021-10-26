#ifndef Z_EN_RACEDOG_H
#define Z_EN_RACEDOG_H

#include "global.h"

struct EnRacedog;

typedef void (*EnRacedogActionFunc)(struct EnRacedog*, GlobalContext*);

typedef struct EnRacedog {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnRacedogActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x180];
} EnRacedog; // size = 0x2C8

extern const ActorInit En_Racedog_InitVars;

#endif // Z_EN_RACEDOG_H
