#ifndef Z_EN_ZL4_H
#define Z_EN_ZL4_H

#include "global.h"

struct EnZl4;

typedef void (*EnZl4ActionFunc)(struct EnZl4*, PlayState*);

typedef struct EnZl4 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x14C];
    /* 0x290 */ EnZl4ActionFunc actionFunc;
    /* 0x294 */ char unk_294[0x60];
} EnZl4; // size = 0x2F4

#endif // Z_EN_ZL4_H
