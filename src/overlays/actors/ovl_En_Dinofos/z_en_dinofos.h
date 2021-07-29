#ifndef Z_EN_DINOFOS_H
#define Z_EN_DINOFOS_H

#include "global.h"

struct EnDinofos;

typedef void (*EnDinofosActionFunc)(struct EnDinofos* this, GlobalContext* globalCtx);

typedef struct EnDinofos {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x140];
    /* 0x0284 */ EnDinofosActionFunc actionFunc;
    /* 0x0288 */ char unk_288[0x3BC];
} EnDinofos; // size = 0x644

extern const ActorInit En_Dinofos_InitVars;

#endif // Z_EN_DINOFOS_H
