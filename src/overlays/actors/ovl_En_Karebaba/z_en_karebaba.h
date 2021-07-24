#ifndef Z_EN_KAREBABA_H
#define Z_EN_KAREBABA_H

#include "global.h"

struct EnKarebaba;

typedef struct EnKarebaba {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x184];
} EnKarebaba; // size = 0x2C8

extern const ActorInit En_Karebaba_InitVars;

#endif // Z_EN_KAREBABA_H
