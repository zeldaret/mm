#ifndef Z_EN_TANRON2_H
#define Z_EN_TANRON2_H

#include "global.h"

struct EnTanron2;

typedef void (*EnTanron2ActionFunc)(struct EnTanron2*, GlobalContext*);

typedef struct EnTanron2 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnTanron2ActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0xB4];
} EnTanron2; // size = 0x1FC

extern const ActorInit En_Tanron2_InitVars;

#endif // Z_EN_TANRON2_H
