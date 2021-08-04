#ifndef Z_BOSS_06_H
#define Z_BOSS_06_H

#include "global.h"

struct Boss06;

typedef void (*Boss06ActionFunc)(struct Boss06* this, GlobalContext* globalCtx);

typedef struct Boss06 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x54];
    /* 0x0198 */ Boss06ActionFunc actionFunc;
    /* 0x019C */ char unk_19C[0x894];
} Boss06; // size = 0xA30

extern const ActorInit Boss_06_InitVars;

#endif // Z_BOSS_06_H
