#ifndef _Z_EN_MKK_H_
#define _Z_EN_MKK_H_

#include <global.h>

struct EnMkk;

typedef struct EnMkk {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x90];
} EnMkk; // size = 0x1D4

extern const ActorInit En_Mkk_InitVars;

#endif
