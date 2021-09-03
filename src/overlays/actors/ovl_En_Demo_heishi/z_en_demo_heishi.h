#ifndef Z_EN_DEMO_HEISHI_H
#define Z_EN_DEMO_HEISHI_H

#include "global.h"

struct EnDemoheishi;

typedef void (*EnDemoheishiActionFunc)(struct EnDemoheishi*, GlobalContext*);

typedef struct EnDemoheishi {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x110];
    /* 0x0254 */ EnDemoheishiActionFunc actionFunc;
    /* 0x0258 */ char unk_258[0x68];
} EnDemoheishi; // size = 0x2C0

extern const ActorInit En_Demo_heishi_InitVars;

#endif // Z_EN_DEMO_HEISHI_H
