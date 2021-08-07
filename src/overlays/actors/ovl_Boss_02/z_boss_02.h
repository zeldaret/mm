#ifndef Z_BOSS_02_H
#define Z_BOSS_02_H

#include "global.h"

struct Boss02;

typedef void (*Boss02ActionFunc)(struct Boss02* this, GlobalContext* globalCtx);

typedef struct Boss02 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x152C];
    /* 0x1670 */ Boss02ActionFunc actionFunc;
    /* 0x1674 */ char unk_1674[0x70C];
} Boss02; // size = 0x1D80

extern const ActorInit Boss_02_InitVars;

#endif // Z_BOSS_02_H
