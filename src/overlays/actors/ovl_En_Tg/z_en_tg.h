#ifndef Z_EN_TG_H
#define Z_EN_TG_H

#include "global.h"

struct EnTg;

typedef void (*EnTgActionFunc)(struct EnTg*, PlayState*);

typedef struct EnTg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnTgActionFunc actionFunc;
    /* 0x148 */ char unk_148[0x400];
} EnTg; // size = 0x548

extern const ActorInit En_Tg_InitVars;

#endif // Z_EN_TG_H
