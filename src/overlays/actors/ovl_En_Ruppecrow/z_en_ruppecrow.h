#ifndef Z_EN_RUPPECROW_H
#define Z_EN_RUPPECROW_H

#include "global.h"

struct EnRuppecrow;

typedef void (*EnRuppecrowActionFunc)(struct EnRuppecrow* this, GlobalContext* globalCtx);

typedef struct EnRuppecrow {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x94];
    /* 0x01D8 */ EnRuppecrowActionFunc actionFunc;
    /* 0x01DC */ char unk_1DC[0x128];
} EnRuppecrow; // size = 0x304

extern const ActorInit En_Ruppecrow_InitVars;

#endif // Z_EN_RUPPECROW_H
