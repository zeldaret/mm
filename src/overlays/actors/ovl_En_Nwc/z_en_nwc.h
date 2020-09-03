#ifndef _Z_EN_NWC_H_
#define _Z_EN_NWC_H_

#include <global.h>

struct EnNwc;

typedef struct EnNwc {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x124];
} EnNwc; // size = 0x268

extern const ActorInit En_Nwc_InitVars;

#endif
