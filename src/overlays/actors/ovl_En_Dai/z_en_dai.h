#ifndef _Z_EN_DAI_H_
#define _Z_EN_DAI_H_

#include <global.h>

struct EnDai;

typedef struct EnDai {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x930];
} EnDai; // size = 0xA74

extern const ActorInit En_Dai_InitVars;

#endif
