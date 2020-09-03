#ifndef _Z_EN_HS_H_
#define _Z_EN_HS_H_

#include <global.h>

struct EnHs;

typedef struct EnHs {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x254];
} EnHs; // size = 0x398

extern const ActorInit En_Hs_InitVars;

#endif
