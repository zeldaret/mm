#ifndef _Z_EN_KUJIYA_H_
#define _Z_EN_KUJIYA_H_

#include <global.h>

struct EnKujiya;

typedef struct EnKujiya {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x8];
} EnKujiya; // size = 0x14C

extern const ActorInit En_Kujiya_InitVars;

#endif
