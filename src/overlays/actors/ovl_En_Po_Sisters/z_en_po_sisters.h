#ifndef Z_EN_PO_SISTERS_H
#define Z_EN_PO_SISTERS_H

#include "global.h"

struct EnPoSisters;

typedef void (*EnPoSistersActionFunc)(struct EnPoSisters*, GlobalContext*);

typedef struct EnPoSisters {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnPoSistersActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x20C];
} EnPoSisters; // size = 0x398

extern const ActorInit En_Po_Sisters_InitVars;

#endif // Z_EN_PO_SISTERS_H
