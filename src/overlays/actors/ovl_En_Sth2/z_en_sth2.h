#ifndef Z_EN_STH2_H
#define Z_EN_STH2_H

#include "global.h"

struct EnSth2;

typedef void (*EnSth2ActionFunc)(struct EnSth2*, PlayState*);

typedef struct EnSth2 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable;
    /* 0x18E */ UNK_TYPE1 pad18E[0x5A];
    /* 0x1E8 */ Vec3s morphTable;
    /* 0x1EE */ UNK_TYPE1 pad1EE[0x5A];
    /* 0x248 */ s16 unused;
    /* 0x24A */ u8 objIndex;
    /* 0x24C */ EnSth2ActionFunc actionFunc;
} EnSth2; // size = 0x250

extern const ActorInit En_Sth2_InitVars;

#endif // Z_EN_STH2_H
