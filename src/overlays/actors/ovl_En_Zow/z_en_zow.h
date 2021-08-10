#ifndef Z_EN_ZOW_H
#define Z_EN_ZOW_H

#include "global.h"

struct EnZow;

typedef void (*EnZowActionFunc)(struct EnZow* this, GlobalContext* globalCtx);

typedef struct EnZow {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x4D4];
    /* 0x0618 */ EnZowActionFunc actionFunc;
} EnZow; // size = 0x61C

extern const ActorInit En_Zow_InitVars;

#endif // Z_EN_ZOW_H
