#ifndef Z_EN_STOP_HEISHI_H
#define Z_EN_STOP_HEISHI_H

#include "global.h"

struct EnStopheishi;

typedef void (*EnStopheishiActionFunc)(struct EnStopheishi*, GlobalContext*);

typedef struct EnStopheishi {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x110];
    /* 0x0254 */ EnStopheishiActionFunc actionFunc;
    /* 0x0258 */ char unk_258[0x90];
} EnStopheishi; // size = 0x2E8

extern const ActorInit En_Stop_heishi_InitVars;

#endif // Z_EN_STOP_HEISHI_H
