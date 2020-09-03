#ifndef _Z_DEMO_SYOTEN_H_
#define _Z_DEMO_SYOTEN_H_

#include <global.h>

struct DemoSyoten;

typedef struct DemoSyoten {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2B4];
} DemoSyoten; // size = 0x3F8

extern const ActorInit Demo_Syoten_InitVars;

#endif
