#ifndef Z_EN_SNOWWD_H
#define Z_EN_SNOWWD_H

#include "global.h"

struct EnSnowwd;

typedef void (*EnSnowwdActionFunc)(struct EnSnowwd* this, GlobalContext* globalCtx);

typedef struct EnSnowwd {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x50];
    /* 0x0194 */ EnSnowwdActionFunc actionFunc;
} EnSnowwd; // size = 0x198

extern const ActorInit En_Snowwd_InitVars;

#endif // Z_EN_SNOWWD_H
