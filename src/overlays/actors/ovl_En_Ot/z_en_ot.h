#ifndef Z_EN_OT_H
#define Z_EN_OT_H

#include "global.h"

struct EnOt;

typedef void (*EnOtActionFunc)(struct EnOt*, GlobalContext*);

typedef struct EnOt {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnOtActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x610];
} EnOt; // size = 0x758

extern const ActorInit En_Ot_InitVars;

#endif // Z_EN_OT_H
