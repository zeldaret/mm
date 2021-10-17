#ifndef Z_DEMO_KANKYO_H
#define Z_DEMO_KANKYO_H

#include "global.h"

struct DemoKankyo;

typedef void (*DemoKankyoActionFunc)(struct DemoKankyo*, GlobalContext*);

typedef struct DemoKankyo {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x1500];
    /* 0x1644 */ DemoKankyoActionFunc actionFunc;
    /* 0x1648 */ char unk_1648[0x8];
} DemoKankyo; // size = 0x1650

extern const ActorInit Demo_Kankyo_InitVars;

#endif // Z_DEMO_KANKYO_H
