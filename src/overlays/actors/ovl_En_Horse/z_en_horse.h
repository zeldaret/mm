#ifndef Z_EN_HORSE_H
#define Z_EN_HORSE_H

#include "global.h"

struct EnHorse;

#define ENHORSE_JUMPING (1 << 2)   /* 0x4 */

typedef struct EnHorse {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x00C];
    /* 0x150 */ s32 unk_150;
    /* 0x154 */ char unk_154[0x94];
    /* 0x1E8 */ u32 stateFlags;
    /* 0x1EC */ char unk_1EC[0x3A8];
} EnHorse; // size = 0x594

#define EN_HORSE_CHECK_JUMPING(horseActor) \
    (((horseActor)->stateFlags & ENHORSE_JUMPING) \
        ? true                       \
        : false)

extern const ActorInit En_Horse_InitVars;

#endif // Z_EN_HORSE_H
