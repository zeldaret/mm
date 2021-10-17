#ifndef Z_EN_NWC_H
#define Z_EN_NWC_H

#include "global.h"

struct EnNwc;

typedef void (*EnNwcActionFunc)(struct EnNwc*, GlobalContext*);

typedef struct EnNwc {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x120];
    /* 0x0264 */ EnNwcActionFunc actionFunc;
} EnNwc; // size = 0x268

extern const ActorInit En_Nwc_InitVars;

#endif // Z_EN_NWC_H
