#ifndef Z_EN_DNQ_H
#define Z_EN_DNQ_H

#include "global.h"

struct EnDnq;

typedef void (*EnDnqActionFunc)(struct EnDnq* this, GlobalContext* globalCtx);

typedef struct EnDnq {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x48];
    /* 0x018C */ EnDnqActionFunc actionFunc;
    /* 0x0190 */ char unk_190[0x218];
} EnDnq; // size = 0x3A8

extern const ActorInit En_Dnq_InitVars;

#endif // Z_EN_DNQ_H
