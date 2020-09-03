#ifndef Z_EN_MINISLIME_H
#define Z_EN_MINISLIME_H

#include <global.h>

struct EnMinislime;

typedef struct EnMinislime {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x68];
} EnMinislime; // size = 0x1AC

extern const ActorInit En_Minislime_InitVars;

#endif // Z_EN_MINISLIME_H
