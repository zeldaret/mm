#ifndef _Z_EN_TANRON4_H_
#define _Z_EN_TANRON4_H_

#include <global.h>

struct EnTanron4;

typedef struct EnTanron4 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xEC];
} EnTanron4; // size = 0x230

extern const ActorInit En_Tanron4_InitVars;

#endif
