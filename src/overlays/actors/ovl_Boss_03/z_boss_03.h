#ifndef Z_BOSS_03_H
#define Z_BOSS_03_H

#include "global.h"

struct Boss03;

typedef void (*Boss03ActionFunc)(struct Boss03* this, GlobalContext* globalCtx);

typedef struct Boss03 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x1E4];
    /* 0x0328 */ Boss03ActionFunc actionFunc;
    /* 0x032C */ char unk_32C[0x250];
} Boss03; // size = 0x57C

extern const ActorInit Boss_03_InitVars;

#endif // Z_BOSS_03_H
