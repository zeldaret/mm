#ifndef _Z_EN_MM_H_
#define _Z_EN_MM_H_

#include <global.h>

struct EnMm;

typedef struct EnMm {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x54];
} EnMm; // size = 0x198

extern const ActorInit En_Mm_InitVars;

#endif
