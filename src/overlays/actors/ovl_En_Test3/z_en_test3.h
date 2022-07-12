#ifndef Z_EN_TEST3_H
#define Z_EN_TEST3_H

#include "global.h"

struct EnTest3;

typedef void (*EnTest3ActionFunc)(struct EnTest3*, PlayState*);

typedef struct EnTest3 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x628];
    /* 0x76C */ EnTest3ActionFunc actionFunc;
    /* 0x770 */ char unk_770[0x648];
} EnTest3; // size = 0xDB8

extern const ActorInit En_Test3_InitVars;

#endif // Z_EN_TEST3_H
