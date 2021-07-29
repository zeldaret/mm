#ifndef Z_EN_JG_H
#define Z_EN_JG_H

#include "global.h"

struct EnJg;

typedef void (*EnJgActionFunc)(struct EnJg* this, GlobalContext* globalCtx);

typedef struct EnJg {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x98];
    /* 0x01DC */ EnJgActionFunc actionFunc;
    /* 0x01E0 */ char unk_1E0[0x1F4];
} EnJg; // size = 0x3D4

extern const ActorInit En_Jg_InitVars;

#endif // Z_EN_JG_H
