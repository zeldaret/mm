#ifndef _Z_EN_BIGOKUTA_H_
#define _Z_EN_BIGOKUTA_H_

#include <global.h>

struct EnBigokuta;

typedef struct EnBigokuta {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2B4];
} EnBigokuta; // size = 0x3F8

extern const ActorInit En_Bigokuta_InitVars;

#endif
