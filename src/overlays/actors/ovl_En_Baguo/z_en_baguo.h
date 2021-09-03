#ifndef Z_EN_BAGUO_H
#define Z_EN_BAGUO_H

#include "global.h"

struct EnBaguo;

typedef void (*EnBaguoActionFunc)(struct EnBaguo*, GlobalContext*);

typedef struct EnBaguo {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x68];
    /* 0x01AC */ EnBaguoActionFunc actionFunc;
    /* 0x01B0 */ char unk_1B0[0x71C];
} EnBaguo; // size = 0x8CC

extern const ActorInit En_Baguo_InitVars;

#endif // Z_EN_BAGUO_H
