#ifndef _Z_EN_WIZ_H_
#define _Z_EN_WIZ_H_

#include <global.h>

struct EnWiz;

typedef struct EnWiz {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xC3C];
} EnWiz; // size = 0xD80

extern const ActorInit En_Wiz_InitVars;

#endif
