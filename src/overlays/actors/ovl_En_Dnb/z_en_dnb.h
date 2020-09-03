#ifndef _Z_EN_DNB_H_
#define _Z_EN_DNB_H_

#include <global.h>

struct EnDnb;

typedef struct EnDnb {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_0144[0x33F4];
} EnDnb; // size = 0x3538

extern const ActorInit En_Dnb_InitVars;

#endif
