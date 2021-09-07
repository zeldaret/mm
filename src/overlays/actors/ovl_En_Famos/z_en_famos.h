#ifndef Z_EN_FAMOS_H
#define Z_EN_FAMOS_H

#include "global.h"

struct EnFamos;

typedef void (*EnFamosActionFunc)(struct EnFamos*, GlobalContext*);

typedef struct EnFamos {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x8C];
    /* 0x01D0 */ EnFamosActionFunc actionFunc;
    /* 0x01D4 */ char unk_1D4[0x440];
} EnFamos; // size = 0x614

extern const ActorInit En_Famos_InitVars;

#endif // Z_EN_FAMOS_H
