#ifndef _Z_EN_SUTTARI_H_
#define _Z_EN_SUTTARI_H_

#include <global.h>

struct EnSuttari;

typedef struct EnSuttari {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x318];
} EnSuttari; // size = 0x45C

extern const ActorInit En_Suttari_InitVars;

#endif
