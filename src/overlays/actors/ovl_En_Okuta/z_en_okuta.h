#ifndef Z_EN_OKUTA_H
#define Z_EN_OKUTA_H

#include "global.h"

struct EnOkuta;

typedef void (*EnOkutaActionFunc)(struct EnOkuta*, PlayState*);

typedef struct EnOkuta {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x44];
    /* 0x188 */ EnOkutaActionFunc actionFunc;
    /* 0x18C */ char unk_18C[0x1A8];
} EnOkuta; // size = 0x334

#endif // Z_EN_OKUTA_H
