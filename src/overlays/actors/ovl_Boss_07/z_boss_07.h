#ifndef Z_BOSS_07_H
#define Z_BOSS_07_H

#include "global.h"

struct Boss07;

typedef void (*Boss07ActionFunc)(struct Boss07*, PlayState*);

typedef struct Boss07 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ Boss07ActionFunc actionFunc;
    /* 0x0148 */ char unk_148[0xAAD8];
} Boss07; // size = 0xAC20

#endif // Z_BOSS_07_H
