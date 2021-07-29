#ifndef Z_EN_ZOV_H
#define Z_EN_ZOV_H

#include "global.h"

struct EnZov;

typedef void (*EnZovActionFunc)(struct EnZov* this, GlobalContext* globalCtx);

typedef struct EnZov {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x1EC];
    /* 0x0330 */ EnZovActionFunc actionFunc;
} EnZov; // size = 0x334

extern const ActorInit En_Zov_InitVars;

#endif // Z_EN_ZOV_H
