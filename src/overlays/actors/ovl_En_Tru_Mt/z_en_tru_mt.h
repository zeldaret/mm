#ifndef Z_EN_TRU_MT_H
#define Z_EN_TRU_MT_H

#include "global.h"

struct EnTruMt;

typedef void (*EnTruMtActionFunc)(struct EnTruMt*, GlobalContext*);

typedef struct EnTruMt {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnTruMtActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x260];
} EnTruMt; // size = 0x3A8

extern const ActorInit En_Tru_Mt_InitVars;

#endif // Z_EN_TRU_MT_H
