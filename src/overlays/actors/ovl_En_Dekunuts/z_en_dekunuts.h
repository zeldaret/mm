#ifndef _Z_EN_DEKUNUTS_H_
#define _Z_EN_DEKUNUTS_H_

#include <global.h>

struct EnDekunuts;

typedef struct EnDekunuts {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x184];
} EnDekunuts; // size = 0x2C8

extern const ActorInit En_Dekunuts_InitVars;

#endif
