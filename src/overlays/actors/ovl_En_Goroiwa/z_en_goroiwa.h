#ifndef Z_EN_GOROIWA_H
#define Z_EN_GOROIWA_H

#include "global.h"

struct EnGoroiwa;

typedef void (*EnGoroiwaActionFunc)(struct EnGoroiwa*, GlobalContext*);

typedef struct EnGoroiwa {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x60];
    /* 0x01A4 */ EnGoroiwaActionFunc actionFunc;
    /* 0x01A8 */ char unk_1A8[0xA4];
} EnGoroiwa; // size = 0x24C

extern const ActorInit En_Goroiwa_InitVars;

#endif // Z_EN_GOROIWA_H
