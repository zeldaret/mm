#ifndef _Z_EN_BJT_H_
#define _Z_EN_BJT_H_

#include <global.h>

struct EnBjt;

typedef struct EnBjt {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x118];
} EnBjt; // size = 0x25C

extern const ActorInit En_Bjt_InitVars;

#endif
