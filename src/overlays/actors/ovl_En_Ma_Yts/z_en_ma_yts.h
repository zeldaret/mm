#ifndef _Z_EN_MA_YTS_H_
#define _Z_EN_MA_YTS_H_

#include <global.h>

struct EnMaYts;

typedef struct EnMaYts {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1F8];
} EnMaYts; // size = 0x33C

extern const ActorInit En_Ma_Yts_InitVars;

#endif
