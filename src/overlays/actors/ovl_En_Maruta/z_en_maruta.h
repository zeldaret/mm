#ifndef _Z_EN_MARUTA_H_
#define _Z_EN_MARUTA_H_

#include <global.h>

struct EnMaruta;

typedef struct EnMaruta {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xE0];
} EnMaruta; // size = 0x224

extern const ActorInit En_Maruta_InitVars;

#endif
