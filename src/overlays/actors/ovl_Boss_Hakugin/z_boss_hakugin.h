#ifndef Z_BOSS_HAKUGIN_H
#define Z_BOSS_HAKUGIN_H

#include "global.h"

struct BossHakugin;

typedef void (*BossHakuginActionFunc)(struct BossHakugin*, PlayState*);

typedef struct BossHakuginEffect {
    /* 0x00 */ Vec3f unk_0;
    /* 0x0C */ Vec3f unk_C;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ Vec3s unk_1C;
    /* 0x24 */ f32 unk_24;
} BossHakuginEffect; // size = 0x28

#define BOSS_HAKUGIN_EFFECT_COUNT 180

typedef struct BossHakuginFhgFlashUnkStruct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ char unk_0C[0x8];
} BossHakuginFhgFlashUnkStruct; // size = 0x14

typedef struct BossHakugin {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_0144[0x44];
    /* 0x0188 */ BossHakuginActionFunc actionFunc;
    /* 0x018C */ char unk_018C[0x5];
    /* 0x0191 */ u8 unk_191;
    /* 0x018C */ char unk_0192[0x866];
    /* 0x09F8 */ BossHakuginEffect unk_9F8[BOSS_HAKUGIN_EFFECT_COUNT];
    /* 0x2618 */ char unk_2618[0x8E8];
    /* 0x2F00 */ BossHakuginFhgFlashUnkStruct unk_2F00[7][15];
    /* 0x3734 */ char unk_3734[0xDC];
} BossHakugin; // size = 0x3810

#endif // Z_BOSS_HAKUGIN_H
