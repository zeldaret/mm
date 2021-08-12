#ifndef Z_EN_CNE_01_H
#define Z_EN_CNE_01_H

#include "global.h"

struct EnCne01;

typedef void (*EnCne01ActionFunc)(struct EnCne01*, GlobalContext*);

typedef struct EnCne01 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnCne01ActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x4D4];
} EnCne01; // size = 0x61C

extern const ActorInit En_Cne_01_InitVars;

#endif // Z_EN_CNE_01_H
