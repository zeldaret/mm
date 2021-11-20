#ifndef Z_EN_GE3_H
#define Z_EN_GE3_H

#include "global.h"

struct EnGe3;

typedef void (*EnGe3ActionFunc)(struct EnGe3*, GlobalContext*);

typedef struct EnGe3 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x1D8];
    /* 0x031C */ EnGe3ActionFunc actionFunc;
} EnGe3; // size = 0x320

extern const ActorInit En_Ge3_InitVars;

#endif // Z_EN_GE3_H
