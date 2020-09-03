#ifndef _Z_EN_SNOWWD_H_
#define _Z_EN_SNOWWD_H_

#include <global.h>

struct EnSnowwd;

typedef struct EnSnowwd {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x54];
} EnSnowwd; // size = 0x198

extern const ActorInit En_Snowwd_InitVars;

#endif
