#ifndef Z_EN_KUSA2_H
#define Z_EN_KUSA2_H

#include "global.h"

struct EnKusa2;

typedef void (*EnKusa2ActionFunc)(struct EnKusa2*, GlobalContext*);

typedef struct EnKusa2 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x4C];
    /* 0x0190 */ EnKusa2ActionFunc actionFunc;
    /* 0x0194 */ char unk_194[0x40];
} EnKusa2; // size = 0x1D4

extern const ActorInit En_Kusa2_InitVars;

#endif // Z_EN_KUSA2_H
