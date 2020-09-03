#ifndef _Z_EN_MA4_H_
#define _Z_EN_MA4_H_

#include <global.h>

struct EnMa4;

typedef struct EnMa4 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1FC];
} EnMa4; // size = 0x340

extern const ActorInit En_Ma4_InitVars;

#endif
