#ifndef Z_EN_BOMJIMA_H
#define Z_EN_BOMJIMA_H

#include "global.h"

struct EnBomjima;

typedef void (*EnBomjimaActionFunc)(struct EnBomjima*, GlobalContext*);

typedef struct EnBomjima {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x140];
    /* 0x0284 */ EnBomjimaActionFunc actionFunc;
    /* 0x0288 */ char unk_288[0xBC];
} EnBomjima; // size = 0x344

extern const ActorInit En_Bomjima_InitVars;

#endif // Z_EN_BOMJIMA_H
