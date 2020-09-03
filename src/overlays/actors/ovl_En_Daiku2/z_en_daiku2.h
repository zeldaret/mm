#ifndef _Z_EN_DAIKU2_H_
#define _Z_EN_DAIKU2_H_

#include <global.h>

struct EnDaiku2;

typedef struct EnDaiku2 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xC84];
} EnDaiku2; // size = 0xDC8

extern const ActorInit En_Daiku2_InitVars;

#endif
