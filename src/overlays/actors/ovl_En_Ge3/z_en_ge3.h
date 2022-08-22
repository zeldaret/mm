#ifndef Z_EN_GE3_H
#define Z_EN_GE3_H

#include "global.h"

struct EnGe3;

typedef void (*EnGe3ActionFunc)(struct EnGe3*, PlayState*);

typedef struct EnGe3 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1D8];
    /* 0x31C */ EnGe3ActionFunc actionFunc;
} EnGe3; // size = 0x320

extern const ActorInit En_Ge3_InitVars;

#endif // Z_EN_GE3_H
