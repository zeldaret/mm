#ifndef _Z_EN_TANRON3_H_
#define _Z_EN_TANRON3_H_

#include <global.h>

struct EnTanron3;

typedef struct EnTanron3 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1B8];
} EnTanron3; // size = 0x2FC

extern const ActorInit En_Tanron3_InitVars;

#endif
