#ifndef Z_EN_TAB_H
#define Z_EN_TAB_H

#include "global.h"

struct EnTab;

typedef struct EnTab {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1F8];
} EnTab; // size = 0x33C

extern const ActorInit En_Tab_InitVars;

#endif // Z_EN_TAB_H
