#ifndef Z_EN_RD_H
#define Z_EN_RD_H

#include "global.h"

struct EnRd;

typedef void (*EnRdActionFunc)(struct EnRd* this, GlobalContext* globalCtx);

typedef struct EnRd {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnRdActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x268];
} EnRd; // size = 0x3F4

extern const ActorInit En_Rd_InitVars;

#endif // Z_EN_RD_H
