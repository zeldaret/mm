#ifndef _Z_EN_RAF_H_
#define _Z_EN_RAF_H_

#include <global.h>

struct EnRaf;

typedef struct EnRaf {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x9A0];
} EnRaf; // size = 0xAE4

extern const ActorInit En_Raf_InitVars;

#endif
