#ifndef _Z_EN_BSB_H_
#define _Z_EN_BSB_H_

#include <global.h>

struct EnBsb;

typedef struct EnBsb {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_0144[0x1014];
} EnBsb; // size = 0x1158

extern const ActorInit En_Bsb_InitVars;

#endif
