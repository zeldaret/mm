#ifndef Z_EN_FALL2_H
#define Z_EN_FALL2_H

#include "global.h"

struct EnFall2;

typedef void (*EnFall2ActionFunc)(struct EnFall2*, GlobalContext*);

typedef struct EnFall2 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x1A4];
    /* 0x02E8 */ EnFall2ActionFunc actionFunc;
} EnFall2; // size = 0x2EC

extern const ActorInit En_Fall2_InitVars;

#endif // Z_EN_FALL2_H
