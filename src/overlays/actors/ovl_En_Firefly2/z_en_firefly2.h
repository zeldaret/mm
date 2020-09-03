#ifndef _Z_EN_FIREFLY2_H_
#define _Z_EN_FIREFLY2_H_

#include <global.h>

struct EnFirefly2;

typedef struct EnFirefly2 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x228];
} EnFirefly2; // size = 0x36C

extern const ActorInit En_Firefly2_InitVars;

#endif
