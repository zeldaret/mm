#ifndef _Z_EN_ELFBUB_H_
#define _Z_EN_ELFBUB_H_

#include <global.h>

struct EnElfbub;

typedef struct EnElfbub {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x60];
} EnElfbub; // size = 0x1A4

extern const ActorInit En_Elfbub_InitVars;

#endif
