#ifndef Z_EN_RZ_H
#define Z_EN_RZ_H

#include "global.h"

struct EnRz;

typedef void (*EnRzActionFunc)(struct EnRz* this, GlobalContext* globalCtx);

typedef struct EnRz {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x2EC];
    /* 0x0430 */ EnRzActionFunc actionFunc;
} EnRz; // size = 0x434

extern const ActorInit En_Rz_InitVars;

#endif // Z_EN_RZ_H
