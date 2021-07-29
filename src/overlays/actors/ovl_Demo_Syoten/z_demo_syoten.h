#ifndef Z_DEMO_SYOTEN_H
#define Z_DEMO_SYOTEN_H

#include "global.h"

struct DemoSyoten;

typedef void (*DemoSyotenActionFunc)(struct DemoSyoten* this, GlobalContext* globalCtx);

typedef struct DemoSyoten {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x2B0];
    /* 0x03F4 */ DemoSyotenActionFunc actionFunc;
} DemoSyoten; // size = 0x3F8

extern const ActorInit Demo_Syoten_InitVars;

#endif // Z_DEMO_SYOTEN_H
