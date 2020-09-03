#ifndef _Z_EN_MM3_H_
#define _Z_EN_MM3_H_

#include <global.h>

struct EnMm3;

typedef struct EnMm3 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x174];
} EnMm3; // size = 0x2B8

extern const ActorInit En_Mm3_InitVars;

#endif
