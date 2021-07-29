#ifndef Z_EN_BBA_01_H
#define Z_EN_BBA_01_H

#include "global.h"

struct EnBba01;

typedef void (*EnBba01ActionFunc)(struct EnBba01* this, GlobalContext* globalCtx);

typedef struct EnBba01 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnBba01ActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x4D4];
} EnBba01; // size = 0x61C

extern const ActorInit En_Bba_01_InitVars;

#endif // Z_EN_BBA_01_H
