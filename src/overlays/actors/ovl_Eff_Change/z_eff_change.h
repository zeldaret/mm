#ifndef Z_EFF_CHANGE_H
#define Z_EFF_CHANGE_H

#include "global.h"

struct EffChange;

typedef void (*EffChangeActionFunc)(struct EffChange*, GlobalContext*);

typedef struct EffChange {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x84];
    /* 0x01C8 */ EffChangeActionFunc actionFunc;
} EffChange; // size = 0x1CC

extern const ActorInit Eff_Change_InitVars;

#endif // Z_EFF_CHANGE_H
