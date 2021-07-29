#ifndef Z_BOSS_HAKUGIN_H
#define Z_BOSS_HAKUGIN_H

#include "global.h"

struct BossHakugin;

typedef void (*BossHakuginActionFunc)(struct BossHakugin* this, GlobalContext* globalCtx);

typedef struct BossHakugin {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ BossHakuginActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x3684];
} BossHakugin; // size = 0x3810

extern const ActorInit Boss_Hakugin_InitVars;

#endif // Z_BOSS_HAKUGIN_H
