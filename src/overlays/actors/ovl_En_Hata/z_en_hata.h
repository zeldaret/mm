#ifndef _Z_EN_HATA_H_
#define _Z_EN_HATA_H_

#include <global.h>

struct EnHata;

typedef struct EnHata {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x16C];
} EnHata; // size = 0x2B0

extern const ActorInit En_Hata_InitVars;

#endif
