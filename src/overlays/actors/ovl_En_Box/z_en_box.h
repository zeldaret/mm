#ifndef _Z_EN_BOX_H_
#define _Z_EN_BOX_H_

#include <global.h>

struct EnBox;

typedef struct EnBox {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xE0];
} EnBox; // size = 0x224

extern const ActorInit En_Box_InitVars;

#endif
