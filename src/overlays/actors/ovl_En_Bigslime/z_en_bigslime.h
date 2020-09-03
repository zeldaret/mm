#ifndef Z_EN_BIGSLIME_H
#define Z_EN_BIGSLIME_H

#include <global.h>

struct EnBigslime;

typedef struct EnBigslime {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_0144[0x34F0];
} EnBigslime; // size = 0x3634

extern const ActorInit En_Bigslime_InitVars;

#endif // Z_EN_BIGSLIME_H
