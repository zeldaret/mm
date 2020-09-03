#ifndef _Z_EN_TANRON1_H_
#define _Z_EN_TANRON1_H_

#include <global.h>

struct EnTanron1;

typedef struct EnTanron1 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_0144[0x3228];
} EnTanron1; // size = 0x336C

extern const ActorInit En_Tanron1_InitVars;

#endif
