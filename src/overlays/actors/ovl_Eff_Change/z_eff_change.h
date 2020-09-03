#ifndef _Z_EFF_CHANGE_H_
#define _Z_EFF_CHANGE_H_

#include <global.h>

struct EffChange;

typedef struct EffChange {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x88];
} EffChange; // size = 0x1CC

extern const ActorInit Eff_Change_InitVars;

#endif
