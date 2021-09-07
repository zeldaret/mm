#ifndef Z_EN_ARROW_H
#define Z_EN_ARROW_H

#include "global.h"

struct EnArrow;

typedef void (*EnArrowActionFunc)(struct EnArrow*, GlobalContext*);

typedef struct EnArrow {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x130];
    /* 0x0274 */ EnArrowActionFunc actionFunc;
} EnArrow; // size = 0x278

extern const ActorInit En_Arrow_InitVars;

#endif // Z_EN_ARROW_H
