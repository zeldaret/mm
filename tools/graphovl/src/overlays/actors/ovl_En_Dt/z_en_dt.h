#ifndef Z_EN_DT_H
#define Z_EN_DT_H

#include "global.h"

struct EnDt;

typedef void (*EnDtActionFunc)(struct EnDt*, GlobalContext*);

typedef struct EnDt {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xF8];
    /* 0x023C */ EnDtActionFunc actionFunc;
    /* 0x0240 */ char unk_240[0xA0];
} EnDt; // size = 0x2E0

extern const ActorInit En_Dt_InitVars;

#endif // Z_EN_DT_H
