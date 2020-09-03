#ifndef _Z_EN_RECEPGIRL_H_
#define _Z_EN_RECEPGIRL_H_

#include <global.h>

struct EnRecepgirl;

typedef struct EnRecepgirl {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x170];
} EnRecepgirl; // size = 0x2B4

extern const ActorInit En_Recepgirl_InitVars;

#endif
