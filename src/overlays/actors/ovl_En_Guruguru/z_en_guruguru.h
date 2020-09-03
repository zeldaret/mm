#ifndef _Z_EN_GURUGURU_H_
#define _Z_EN_GURUGURU_H_

#include <global.h>

struct EnGuruguru;

typedef struct EnGuruguru {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x180];
} EnGuruguru; // size = 0x2C4

extern const ActorInit En_Guruguru_InitVars;

#endif
