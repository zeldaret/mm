#ifndef _Z_EN_TANRON6_H_
#define _Z_EN_TANRON6_H_

#include <global.h>

struct EnTanron6;

typedef struct EnTanron6 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xC0];
} EnTanron6; // size = 0x204

extern const ActorInit En_Tanron6_InitVars;

#endif
