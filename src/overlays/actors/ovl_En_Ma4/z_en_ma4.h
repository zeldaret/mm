#ifndef Z_EN_MA4_H
#define Z_EN_MA4_H

#include <global.h>

struct EnMa4;

typedef struct EnMa4 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1F4];
    /* 0x338 */ s16 unk338; // modified by EnPoFusen
    /* 0x33A */ char unk33A[0x6];
    
} EnMa4; // size = 0x340

extern const ActorInit En_Ma4_InitVars;

#endif // Z_EN_MA4_H
