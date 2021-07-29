#ifndef Z_EN_KAREBABA_H
#define Z_EN_KAREBABA_H

#include "global.h"

struct EnKarebaba;

typedef void (*EnKarebabaActionFunc)(struct EnKarebaba* this, GlobalContext* globalCtx);

typedef struct EnKarebaba {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnKarebabaActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x13C];
} EnKarebaba; // size = 0x2C8

extern const ActorInit En_Karebaba_InitVars;

#endif // Z_EN_KAREBABA_H
