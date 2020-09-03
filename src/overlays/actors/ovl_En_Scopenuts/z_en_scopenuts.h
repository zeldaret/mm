#ifndef _Z_EN_SCOPENUTS_H_
#define _Z_EN_SCOPENUTS_H_

#include <global.h>

struct EnScopenuts;

typedef struct EnScopenuts {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x230];
} EnScopenuts; // size = 0x374

extern const ActorInit En_Scopenuts_InitVars;

#endif
