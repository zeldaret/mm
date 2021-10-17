#ifndef Z_EN_RR_H
#define Z_EN_RR_H

#include "global.h"

struct EnRr;

typedef void (*EnRrActionFunc)(struct EnRr*, GlobalContext*);

typedef struct EnRr {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnRrActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x27C];
} EnRr; // size = 0x3C4

extern const ActorInit En_Rr_InitVars;

#endif // Z_EN_RR_H
