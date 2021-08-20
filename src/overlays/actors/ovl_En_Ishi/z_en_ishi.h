#ifndef Z_EN_ISHI_H
#define Z_EN_ISHI_H

#include "global.h"

struct EnIshi;

typedef void (*EnIshiActionFunc)(struct EnIshi*, GlobalContext*);

typedef struct EnIshi {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x4C];
    /* 0x0190 */ EnIshiActionFunc actionFunc;
    /* 0x0194 */ char unk_194[0x4];
} EnIshi; // size = 0x198

extern const ActorInit En_Ishi_InitVars;

#endif // Z_EN_ISHI_H
