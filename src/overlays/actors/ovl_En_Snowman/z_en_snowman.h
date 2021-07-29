#ifndef Z_EN_SNOWMAN_H
#define Z_EN_SNOWMAN_H

#include "global.h"

struct EnSnowman;

typedef void (*EnSnowmanActionFunc)(struct EnSnowman* this, GlobalContext* globalCtx);

typedef struct EnSnowman {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x13C];
    /* 0x0280 */ EnSnowmanActionFunc actionFunc;
    /* 0x0284 */ char unk_284[0xF4];
} EnSnowman; // size = 0x378

extern const ActorInit En_Snowman_InitVars;

#endif // Z_EN_SNOWMAN_H
