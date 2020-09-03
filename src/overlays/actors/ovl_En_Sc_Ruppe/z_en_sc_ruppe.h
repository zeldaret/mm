#ifndef _Z_EN_SC_RUPPE_H_
#define _Z_EN_SC_RUPPE_H_

#include <global.h>

struct EnScRuppe;

typedef struct EnScRuppe {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x54];
} EnScRuppe; // size = 0x198

extern const ActorInit En_Sc_Ruppe_InitVars;

#endif
