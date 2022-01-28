#ifndef Z_BOSS_HAKUGIN_H
#define Z_BOSS_HAKUGIN_H

#include "global.h"

struct BossHakugin;

typedef void (*BossHakuginActionFunc)(struct BossHakugin*, GlobalContext*);

typedef struct BossHakuginParticle {
    /* 0x00 */ Vec3f unk_0;
    /* 0x0C */ Vec3f unk_C;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ Vec3s unk_1C;
    /* 0x24 */ f32 unk_24;
} BossHakuginParticle; // size = 0x28

typedef struct BossHakugin {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_0144[0x44];
    /* 0x0188 */ BossHakuginActionFunc actionFunc;
    /* 0x018C */ char unk_018C[0x86C];
    /* 0x09F8 */ BossHakuginParticle unk_9F8[180];
    /* 0x2618 */ char unk_2618[0x11F8];
} BossHakugin; // size = 0x3810

extern const ActorInit Boss_Hakugin_InitVars;

#endif // Z_BOSS_HAKUGIN_H
