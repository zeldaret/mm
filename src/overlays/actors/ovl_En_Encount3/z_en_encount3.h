#ifndef Z_EN_ENCOUNT3_H
#define Z_EN_ENCOUNT3_H

#include "global.h"

struct EnEncount3;

typedef void (*EnEncount3ActionFunc)(struct EnEncount3*, PlayState*);

typedef struct EnEncount3 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnEncount3ActionFunc actionFunc;
    /* 0x148 */ char unk_148[0x84];
} EnEncount3; // size = 0x1CC

extern const ActorInit En_Encount3_InitVars;

#endif // Z_EN_ENCOUNT3_H
