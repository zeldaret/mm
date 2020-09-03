#ifndef _Z_EN_RD_H_
#define _Z_EN_RD_H_

#include <global.h>

struct EnRd;

typedef struct EnRd {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2B0];
} EnRd; // size = 0x3F4

extern const ActorInit En_Rd_InitVars;

#endif
