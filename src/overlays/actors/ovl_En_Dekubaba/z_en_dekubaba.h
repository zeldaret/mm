#ifndef Z_EN_DEKUBABA_H
#define Z_EN_DEKUBABA_H

#include "global.h"

struct EnDekubaba;

typedef void (*EnDekubabaActionFunc)(struct EnDekubaba*, GlobalContext*);

typedef struct EnDekubaba {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnDekubabaActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x290];
} EnDekubaba; // size = 0x41C

extern const ActorInit En_Dekubaba_InitVars;

#endif // Z_EN_DEKUBABA_H
