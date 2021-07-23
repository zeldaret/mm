#ifndef Z_EN_OKUTA_H
#define Z_EN_OKUTA_H

#include "global.h"

struct EnOkuta;

typedef struct EnOkuta {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1F0];
} EnOkuta; // size = 0x334

extern const ActorInit En_Okuta_InitVars;

#endif // Z_EN_OKUTA_H
