#ifndef Z_EN_DRS_H
#define Z_EN_DRS_H

#include "global.h"

struct EnDrs;

typedef void (*EnDrsActionFunc)(struct EnDrs* this, GlobalContext* globalCtx);

typedef struct EnDrs {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnDrsActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x80];
} EnDrs; // size = 0x20C

extern const ActorInit En_Drs_InitVars;

#endif // Z_EN_DRS_H
