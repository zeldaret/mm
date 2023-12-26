#ifndef Z_EN_ZL4_H
#define Z_EN_ZL4_H

#include "global.h"

struct EnZl4;

typedef void (*EnZl4ActionFunc)(struct EnZl4*, PlayState*);

typedef struct EnZl4 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime unk144;
    /* 0x188 */ char pad188[0x108];
    /* 0x290 */ EnZl4ActionFunc actionFunc;
    /* 0x294 */ char pad294[0x4C];
    /* 0x2E0 */ s16 unk2E0;
    /* 0x2E2 */ char pad2E2[0xE];
    /* 0x2F0 */ s32 unk2F0;
} EnZl4; /* size = 0x2F4 */

#endif // Z_EN_ZL4_H
