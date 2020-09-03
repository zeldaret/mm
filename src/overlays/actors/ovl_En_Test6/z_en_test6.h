#ifndef Z_EN_TEST6_H
#define Z_EN_TEST6_H

#include <global.h>

struct EnTest6;

typedef struct EnTest6 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x144];
} EnTest6; // size = 0x288

extern const ActorInit En_Test6_InitVars;

#endif // Z_EN_TEST6_H
