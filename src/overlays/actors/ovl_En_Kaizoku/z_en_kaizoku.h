#ifndef _Z_EN_KAIZOKU_H_
#define _Z_EN_KAIZOKU_H_

#include <global.h>

struct EnKaizoku;

typedef struct EnKaizoku {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x4AC];
} EnKaizoku; // size = 0x5F0

extern const ActorInit En_Kaizoku_InitVars;

#endif
