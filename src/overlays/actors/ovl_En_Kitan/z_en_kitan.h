#ifndef Z_EN_KITAN_H
#define Z_EN_KITAN_H

#include "global.h"

struct EnKitan;

typedef void (*EnKitanActionFunc)(struct EnKitan*, PlayState*);

typedef struct EnKitan {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x194];
    /* 0x2D8 */ EnKitanActionFunc actionFunc;
} EnKitan; // size = 0x2DC

#endif // Z_EN_KITAN_H
