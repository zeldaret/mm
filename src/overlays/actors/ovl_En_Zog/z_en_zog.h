#ifndef _Z_EN_ZOG_H_
#define _Z_EN_ZOG_H_

#include <global.h>

struct EnZog;

typedef struct EnZog {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1E8];
} EnZog; // size = 0x32C

extern const ActorInit En_Zog_InitVars;

#endif
