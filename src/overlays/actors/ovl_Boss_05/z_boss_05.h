#ifndef Z_BOSS_05_H
#define Z_BOSS_05_H

#include "global.h"

struct Boss05;

typedef void (*Boss05ActionFunc)(struct Boss05* this, GlobalContext* globalCtx);

typedef struct Boss05 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x2C];
    /* 0x0170 */ Boss05ActionFunc actionFunc;
    /* 0x0174 */ char unk_174[0x394];
} Boss05; // size = 0x508

extern const ActorInit Boss_05_InitVars;

#endif // Z_BOSS_05_H
