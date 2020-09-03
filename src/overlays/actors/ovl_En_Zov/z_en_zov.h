#ifndef _Z_EN_ZOV_H_
#define _Z_EN_ZOV_H_

#include <global.h>

struct EnZov;

typedef struct EnZov {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1F0];
} EnZov; // size = 0x334

extern const ActorInit En_Zov_InitVars;

#endif
