#ifndef Z_EN_HEISHI_H
#define Z_EN_HEISHI_H

#include "global.h"

struct EnHeishi;

typedef void (*EnHeishiActionFunc)(struct EnHeishi* this, GlobalContext* globalCtx);

typedef struct EnHeishi {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x110];
    /* 0x0254 */ EnHeishiActionFunc actionFunc;
    /* 0x0258 */ char unk_258[0x78];
} EnHeishi; // size = 0x2D0

extern const ActorInit En_Heishi_InitVars;

#endif // Z_EN_HEISHI_H
