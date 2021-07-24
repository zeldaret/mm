#ifndef Z_BOSS_HAKUGIN_H
#define Z_BOSS_HAKUGIN_H

#include "global.h"

struct BossHakugin;

typedef struct BossHakugin {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_0144[0x36CC];
} BossHakugin; // size = 0x3810

extern const ActorInit Boss_Hakugin_InitVars;

#endif // Z_BOSS_HAKUGIN_H
