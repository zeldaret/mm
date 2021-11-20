#ifndef Z_EN_TAB_H
#define Z_EN_TAB_H

#include "global.h"

struct EnTab;

typedef void (*EnTabActionFunc)(struct EnTab*, GlobalContext*);

typedef struct EnTab {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnTabActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x1B0];
} EnTab; // size = 0x33C

extern const ActorInit En_Tab_InitVars;

#endif // Z_EN_TAB_H
