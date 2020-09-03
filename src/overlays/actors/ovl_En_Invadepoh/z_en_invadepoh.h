#ifndef _Z_EN_INVADEPOH_H_
#define _Z_EN_INVADEPOH_H_

#include <global.h>

struct EnInvadepoh;

typedef struct EnInvadepoh {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x27C];
} EnInvadepoh; // size = 0x3C0

extern const ActorInit En_Invadepoh_InitVars;

#endif
