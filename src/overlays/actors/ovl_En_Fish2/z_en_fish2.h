#ifndef Z_EN_FISH2_H
#define Z_EN_FISH2_H

#include "global.h"

struct EnFish2;

typedef void (*EnFish2ActionFunc)(struct EnFish2*, GlobalContext*);

typedef struct EnFish2 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x164];
    /* 0x02A8 */ EnFish2ActionFunc actionFunc;
    /* 0x02AC */ char unk_2AC[0x1D6C];
} EnFish2; // size = 0x2018

extern const ActorInit En_Fish2_InitVars;

#endif // Z_EN_FISH2_H
