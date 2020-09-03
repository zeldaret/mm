#ifndef _Z_EN_ISHI_H_
#define _Z_EN_ISHI_H_

#include <global.h>

struct EnIshi;

typedef struct EnIshi {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x54];
} EnIshi; // size = 0x198

extern const ActorInit En_Ishi_InitVars;

#endif
