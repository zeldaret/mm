#ifndef _Z_EN_PO_FUSEN_H_
#define _Z_EN_PO_FUSEN_H_

#include <global.h>

struct EnPoFusen;

typedef struct EnPoFusen {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x130];
} EnPoFusen; // size = 0x274

extern const ActorInit En_Po_Fusen_InitVars;

#endif
