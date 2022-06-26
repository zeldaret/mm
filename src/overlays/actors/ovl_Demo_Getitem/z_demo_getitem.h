#ifndef Z_DEMO_GETITEM_H
#define Z_DEMO_GETITEM_H

#include "global.h"

struct DemoGetitem;

typedef void (*DemoGetitemActionFunc)(struct DemoGetitem*, PlayState*);

typedef struct DemoGetitem {
    /* 0x0000 */ Actor actor;
    /* 0x144 */ s16 item;
    /* 0x146 */ u16 action;
    /* 0x148 */ s8 object;
    /* 0x014C */ DemoGetitemActionFunc actionFunc;
} DemoGetitem; // size = 0x150

extern const ActorInit Demo_Getitem_InitVars;

#endif // Z_DEMO_GETITEM_H
