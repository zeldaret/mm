#ifndef _Z_EN_OKUTA_H_
#define _Z_EN_OKUTA_H_

#include <global.h>

struct EnOkuta;

typedef struct EnOkuta {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1F0];
} EnOkuta; // size = 0x334

extern const ActorInit En_Okuta_InitVars;

#endif
