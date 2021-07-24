#ifndef Z_EFF_CHANGE_H
#define Z_EFF_CHANGE_H

#include "global.h"

struct EffChange;

typedef struct EffChange {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x88];
} EffChange; // size = 0x1CC

extern const ActorInit Eff_Change_InitVars;

#endif // Z_EFF_CHANGE_H
