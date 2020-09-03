#ifndef _Z_EN_ZORAEGG_H_
#define _Z_EN_ZORAEGG_H_

#include <global.h>

struct EnZoraegg;

typedef struct EnZoraegg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xB8];
} EnZoraegg; // size = 0x1FC

extern const ActorInit En_Zoraegg_InitVars;

#endif
