#ifndef Z_EN_DNP_H
#define Z_EN_DNP_H

#include "global.h"

struct EnDnp;

typedef void (*EnDnpActionFunc)(struct EnDnp* this, GlobalContext* globalCtx);

typedef struct EnDnp {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnDnpActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x1B8];
} EnDnp; // size = 0x344

extern const ActorInit En_Dnp_InitVars;

#endif // Z_EN_DNP_H
