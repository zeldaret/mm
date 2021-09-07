#ifndef Z_EN_BBFALL_H
#define Z_EN_BBFALL_H

#include "global.h"

struct EnBbfall;

typedef void (*EnBbfallActionFunc)(struct EnBbfall*, GlobalContext*);

typedef struct EnBbfall {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x104];
    /* 0x0248 */ EnBbfallActionFunc actionFunc;
    /* 0x024C */ char unk_24C[0x218];
} EnBbfall; // size = 0x464

extern const ActorInit En_Bbfall_InitVars;

#endif // Z_EN_BBFALL_H
