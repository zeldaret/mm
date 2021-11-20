#ifndef Z_EN_BABA_H
#define Z_EN_BABA_H

#include "global.h"

struct EnBaba;

typedef void (*EnBabaActionFunc)(struct EnBaba*, GlobalContext*);

typedef struct EnBaba {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x4];
    /* 0x0148 */ EnBabaActionFunc actionFunc;
    /* 0x014C */ char unk_14C[0x2F4];
} EnBaba; // size = 0x440

extern const ActorInit En_Baba_InitVars;

#endif // Z_EN_BABA_H
