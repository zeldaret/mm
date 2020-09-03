#ifndef _Z_EN_OSSAN_H_
#define _Z_EN_OSSAN_H_

#include <global.h>

struct EnOssan;

typedef struct EnOssan {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2C8];
} EnOssan; // size = 0x40C

extern const ActorInit En_Ossan_InitVars;

#endif
