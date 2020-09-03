#ifndef _Z_BOSS_HAKUGIN_H_
#define _Z_BOSS_HAKUGIN_H_

#include <global.h>

struct BossHakugin;

typedef struct BossHakugin {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_0144[0x36CC];
} BossHakugin; // size = 0x3810

extern const ActorInit Boss_Hakugin_InitVars;

#endif
