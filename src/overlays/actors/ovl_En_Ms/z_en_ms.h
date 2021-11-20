#ifndef Z_EN_MS_H
#define Z_EN_MS_H

#include "global.h"

struct EnMs;

typedef void (*EnMsActionFunc)(struct EnMs*, GlobalContext*);

typedef struct EnMs {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xB0];
    /* 0x01F4 */ EnMsActionFunc actionFunc;
    /* 0x01F8 */ char unk_1F8[0x4C];
} EnMs; // size = 0x244

extern const ActorInit En_Ms_InitVars;

#endif // Z_EN_MS_H
