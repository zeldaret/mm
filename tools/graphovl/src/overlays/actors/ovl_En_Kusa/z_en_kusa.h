#ifndef Z_EN_KUSA_H
#define Z_EN_KUSA_H

#include "global.h"

struct EnKusa;

typedef void (*EnKusaActionFunc)(struct EnKusa*, GlobalContext*);

typedef struct EnKusa {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnKusaActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x54];
} EnKusa; // size = 0x19C

extern const ActorInit En_Kusa_InitVars;

#endif // Z_EN_KUSA_H
