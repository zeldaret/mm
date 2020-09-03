#ifndef _Z_EN_WDHAND_H_
#define _Z_EN_WDHAND_H_

#include <global.h>

struct EnWdhand;

typedef struct EnWdhand {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x310];
} EnWdhand; // size = 0x454

extern const ActorInit En_Wdhand_InitVars;

#endif
