#ifndef Z_EN_INVADEPOH_DEMO_H
#define Z_EN_INVADEPOH_DEMO_H

#include "global.h"

struct EnInvadepohDemo;

typedef void (*EnInvadepohDemoActionFunc)(struct EnInvadepohDemo*, GlobalContext*);

typedef struct EnInvadepohDemo {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnInvadepohDemoActionFunc actionFunc;
    /* 0x0148 */ char unk_148[0x180];
} EnInvadepohDemo; // size = 0x2C8

extern const ActorInit En_Invadepoh_Demo_InitVars;

#endif // Z_EN_INVADEPOH_DEMO_H
