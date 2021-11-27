#ifndef Z_BG_F40_SWITCH_H
#define Z_BG_F40_SWITCH_H

#include "global.h"

struct BgF40Switch;

typedef void (*BgF40SwitchActionFunc)(struct BgF40Switch*, GlobalContext*);

typedef struct BgF40Switch {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x20];
    /* 0x0164 */ BgF40SwitchActionFunc actionFunc;
} BgF40Switch; // size = 0x168

extern const ActorInit Bg_F40_Switch_InitVars;

#endif // Z_BG_F40_SWITCH_H
