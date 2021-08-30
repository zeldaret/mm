#ifndef Z_EN_OKUTA_H
#define Z_EN_OKUTA_H

#include "global.h"

struct EnOkuta;

typedef void (*EnOkutaActionFunc)(struct EnOkuta*, GlobalContext*);

typedef struct EnOkuta {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnOkutaActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x1A8];
} EnOkuta; // size = 0x334

extern const ActorInit En_Okuta_InitVars;

#endif // Z_EN_OKUTA_H
