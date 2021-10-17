#ifndef Z_EN_AM_H
#define Z_EN_AM_H

#include <global.h>

struct EnAm;

typedef struct EnAm {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x23C];
} EnAm; // size = 0x380

extern const ActorInit En_Am_InitVars;

#endif // Z_EN_AM_H
