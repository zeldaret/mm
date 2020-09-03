#ifndef _Z_EN_DNH_H_
#define _Z_EN_DNH_H_

#include <global.h>

struct EnDnh;

typedef struct EnDnh {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x78];
} EnDnh; // size = 0x1BC

extern const ActorInit En_Dnh_InitVars;

#endif
