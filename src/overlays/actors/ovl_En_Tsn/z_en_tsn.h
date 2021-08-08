#ifndef Z_EN_TSN_H
#define Z_EN_TSN_H

#include "global.h"

struct EnTsn;

typedef void (*EnTsnActionFunc)(struct EnTsn* this, GlobalContext* globalCtx);

typedef struct EnTsn {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x90];
    /* 0x01D4 */ EnTsnActionFunc actionFunc;
    /* 0x01D8 */ char unk_1D8[0x5C];
} EnTsn; // size = 0x234

extern const ActorInit En_Tsn_InitVars;

#endif // Z_EN_TSN_H
