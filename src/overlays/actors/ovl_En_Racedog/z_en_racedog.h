#ifndef Z_EN_RACEDOG_H
#define Z_EN_RACEDOG_H

#include "global.h"

struct EnRacedog;

typedef void (*EnRacedogActionFunc)(struct EnRacedog*, GlobalContext*);

typedef struct EnRacedog {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnRacedogActionFunc actionFunc;
    /* 0x0148 */ char unk_148[0xA0];
    /* 0x01E8 */ s32 unk_1E8;
    /* 0x01EC */ char unk_1EC[0xA4];
    /* 0x0290 */ s16 unk_290;
    /* 0x0292 */ s16 unk_292;
    /* 0x0294 */ char unk_294[0x8];
    /* 0x029C */ s16 unk_29C;
    /* 0x029E */ char unk_29E[0x2A];
} EnRacedog; // size = 0x2C8

extern const ActorInit En_Racedog_InitVars;

#endif // Z_EN_RACEDOG_H
