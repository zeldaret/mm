#ifndef _Z_EN_HONOTRAP_H_
#define _Z_EN_HONOTRAP_H_

#include <global.h>

struct EnHonotrap;

typedef struct EnHonotrap {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x180];
} EnHonotrap; // size = 0x2C4

extern const ActorInit En_Honotrap_InitVars;

#endif
