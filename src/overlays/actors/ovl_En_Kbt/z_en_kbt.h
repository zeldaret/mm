#ifndef Z_EN_KBT_H
#define Z_EN_KBT_H

#include "global.h"

struct EnKbt;

typedef void (*EnKbtActionFunc)(struct EnKbt*, GlobalContext*);

typedef struct EnKbt {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x144];
    /* 0x0288 */ EnKbtActionFunc actionFunc;
} EnKbt; // size = 0x28C

extern const ActorInit En_Kbt_InitVars;

#endif // Z_EN_KBT_H
