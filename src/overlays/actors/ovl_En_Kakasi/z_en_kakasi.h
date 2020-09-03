#ifndef _Z_EN_KAKASI_H_
#define _Z_EN_KAKASI_H_

#include <global.h>

struct EnKakasi;

typedef struct EnKakasi {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x15C];
} EnKakasi; // size = 0x2A0

extern const ActorInit En_Kakasi_InitVars;

#endif
