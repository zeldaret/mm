#ifndef Z_EN_KUJIYA_H
#define Z_EN_KUJIYA_H

#include "global.h"

struct EnKujiya;

typedef void (*EnKujiyaActionFunc)(struct EnKujiya* this, GlobalContext* globalCtx);

typedef struct EnKujiya {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnKujiyaActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x4];
} EnKujiya; // size = 0x14C

extern const ActorInit En_Kujiya_InitVars;

#endif // Z_EN_KUJIYA_H
