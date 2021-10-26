#ifndef Z_EN_GE1_H
#define Z_EN_GE1_H

#include "global.h"

struct EnGe1;

typedef void (*EnGe1ActionFunc)(struct EnGe1*, GlobalContext*);

typedef struct EnGe1 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x184];
    /* 0x02C8 */ EnGe1ActionFunc actionFunc;
} EnGe1; // size = 0x2CC

extern const ActorInit En_Ge1_InitVars;

#endif // Z_EN_GE1_H
