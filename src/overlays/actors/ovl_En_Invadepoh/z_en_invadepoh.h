#ifndef Z_EN_INVADEPOH_H
#define Z_EN_INVADEPOH_H

#include "global.h"

struct EnInvadepoh;

typedef struct EnInvadepoh {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x27C];
} EnInvadepoh; // size = 0x3C0

#endif // Z_EN_INVADEPOH_H
