#ifndef Z_BOSS_04_H
#define Z_BOSS_04_H

#include "global.h"

struct Boss04;

typedef void (*Boss04ActionFunc)(struct Boss04* this, GlobalContext* globalCtx);

typedef struct Boss04 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xC0];
    /* 0x0204 */ Boss04ActionFunc actionFunc;
    /* 0x0208 */ char unk_208[0x544];
} Boss04; // size = 0x74C

extern const ActorInit Boss_04_InitVars;

#endif // Z_BOSS_04_H
