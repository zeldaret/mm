#ifndef _Z_EN_INVADEPOH_DEMO_H_
#define _Z_EN_INVADEPOH_DEMO_H_

#include <global.h>

struct EnInvadepohDemo;

typedef struct EnInvadepohDemo {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x184];
} EnInvadepohDemo; // size = 0x2C8

extern const ActorInit En_Invadepoh_Demo_InitVars;

#endif
