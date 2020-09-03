#ifndef _Z_EN_DEKUBABA_H_
#define _Z_EN_DEKUBABA_H_

#include <global.h>

struct EnDekubaba;

typedef struct EnDekubaba {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2D8];
} EnDekubaba; // size = 0x41C

extern const ActorInit En_Dekubaba_InitVars;

#endif
