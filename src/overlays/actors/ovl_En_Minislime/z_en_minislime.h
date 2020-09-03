#ifndef _Z_EN_MINISLIME_H_
#define _Z_EN_MINISLIME_H_

#include <global.h>

struct EnMinislime;

typedef struct EnMinislime {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x68];
} EnMinislime; // size = 0x1AC

extern const ActorInit En_Minislime_InitVars;

#endif
