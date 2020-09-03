#ifndef _Z_EN_TRU_H_
#define _Z_EN_TRU_H_

#include <global.h>

struct EnTru;

typedef struct EnTru {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x7F0];
} EnTru; // size = 0x934

extern const ActorInit En_Tru_InitVars;

#endif
