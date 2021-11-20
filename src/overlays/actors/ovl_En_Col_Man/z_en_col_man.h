#ifndef Z_EN_COL_MAN_H
#define Z_EN_COL_MAN_H

#include "global.h"

struct EnColMan;

typedef void (*EnColManActionFunc)(struct EnColMan*, GlobalContext*);

typedef struct EnColMan {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnColManActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x58];
} EnColMan; // size = 0x1A0

extern const ActorInit En_Col_Man_InitVars;

#endif // Z_EN_COL_MAN_H
