#ifndef Z_EN_GIANT_H
#define Z_EN_GIANT_H

#include "global.h"

struct EnGiant;

typedef void (*EnGiantActionFunc)(struct EnGiant*, GlobalContext*);

typedef struct EnGiant {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x154];
    /* 0x0298 */ EnGiantActionFunc actionFunc;
} EnGiant; // size = 0x29C

extern const ActorInit En_Giant_InitVars;

#endif // Z_EN_GIANT_H
