#ifndef _Z_EN_GEG_H_
#define _Z_EN_GEG_H_

#include <global.h>

struct EnGeg;

typedef struct EnGeg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x3AC];
} EnGeg; // size = 0x4F0

extern const ActorInit En_Geg_InitVars;

#endif
