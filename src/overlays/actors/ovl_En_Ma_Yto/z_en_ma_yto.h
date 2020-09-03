#ifndef _Z_EN_MA_YTO_H_
#define _Z_EN_MA_YTO_H_

#include <global.h>

struct EnMaYto;

typedef struct EnMaYto {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1E0];
} EnMaYto; // size = 0x324

extern const ActorInit En_Ma_Yto_InitVars;

#endif
