#ifndef Z_EN_AOB_01_H
#define Z_EN_AOB_01_H

#include "global.h"

struct EnAob01;

typedef void (*EnAob01ActionFunc)(struct EnAob01* this, GlobalContext* globalCtx);

typedef struct EnAob01 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnAob01ActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x2FC];
} EnAob01; // size = 0x444

extern const ActorInit En_Aob_01_InitVars;

#endif // Z_EN_AOB_01_H
