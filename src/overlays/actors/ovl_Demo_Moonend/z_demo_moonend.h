#ifndef Z_DEMO_MOONEND_H
#define Z_DEMO_MOONEND_H

#include "global.h"

struct DemoMoonend;

typedef void (*DemoMoonendActionFunc)(struct DemoMoonend*, GlobalContext*);

typedef struct DemoMoonend {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x19C];
    /* 0x02E0 */ DemoMoonendActionFunc actionFunc;
} DemoMoonend; // size = 0x2E4

extern const ActorInit Demo_Moonend_InitVars;

#endif // Z_DEMO_MOONEND_H
