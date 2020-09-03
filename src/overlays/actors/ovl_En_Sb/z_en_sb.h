#ifndef _Z_EN_SB_H_
#define _Z_EN_SB_H_

#include <global.h>

struct EnSb;

typedef struct EnSb {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x110];
} EnSb; // size = 0x254

extern const ActorInit En_Sb_InitVars;

#endif
