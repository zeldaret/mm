#ifndef Z_EN_GIANT_H
#define Z_EN_GIANT_H

#include "global.h"

struct EnGiant;

typedef void (*EnGiantActionFunc)(struct EnGiant*, GlobalContext*);

typedef struct EnGiant {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[16];
    /* 0x1E8 */ Vec3s morphTable[16];
    /* 0x248 */ char unk_248[0x2];
    /* 0x24A */ s16 unk_24A;
    /* 0x24C */ s16 unk_24C;
    /* 0x24E */ s16 unk_24E;
    /* 0x250 */ u16 unk_250;
    /* 0x252 */ char unk_252[0x46];
    /* 0x298 */ EnGiantActionFunc actionFunc;
} EnGiant; // size = 0x29C

extern const ActorInit En_Giant_InitVars;

#endif // Z_EN_GIANT_H
