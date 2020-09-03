#ifndef _Z_EN_ARROW_H_
#define _Z_EN_ARROW_H_

#include <global.h>

struct EnArrow;

typedef struct EnArrow {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x134];
} EnArrow; // size = 0x278

extern const ActorInit En_Arrow_InitVars;

#endif
