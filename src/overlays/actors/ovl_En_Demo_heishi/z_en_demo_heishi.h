#ifndef Z_EN_DEMO_HEISHI_H
#define Z_EN_DEMO_HEISHI_H

#include <global.h>

struct EnDemoheishi;

typedef struct EnDemoheishi {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x17C];
} EnDemoheishi; // size = 0x2C0

extern const ActorInit En_Demo_heishi_InitVars;

#endif // Z_EN_DEMO_HEISHI_H
