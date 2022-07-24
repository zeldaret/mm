#ifndef Z_EN_STOP_HEISHI_H
#define Z_EN_STOP_HEISHI_H

#include "global.h"

struct EnStopheishi;

typedef void (*EnStopheishiActionFunc)(struct EnStopheishi*, PlayState*);

typedef struct EnStopheishi {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x110];
    /* 0x254 */ EnStopheishiActionFunc actionFunc;
    /* 0x258 */ char unk_258[0x90];
} EnStopheishi; // size = 0x2E8

extern const ActorInit En_Stop_heishi_InitVars;

#endif // Z_EN_STOP_HEISHI_H
