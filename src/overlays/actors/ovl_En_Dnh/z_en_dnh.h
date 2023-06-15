#ifndef Z_EN_DNH_H
#define Z_EN_DNH_H

#include "global.h"

struct EnDnh;

typedef void (*EnDnhActionFunc)(struct EnDnh*, PlayState*);
typedef s32 (*MsgEventFunc)(Actor*, PlayState*);

typedef struct EnDnh {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnDnhActionFunc actionFunc;
    /* 0x148 */ SkelAnime skelAnime;
    /* 0x18C */ u16 unk18C;
    /* 0x190 */ s32 msgEventScript;
    /* 0x194 */ s32 unk194;
    /* 0x198 */ s16 unk198;
    /* 0x19A */ UNK_TYPE1 pad19A[2];
    /* 0x19C */ s16 timer;
    /* 0x19E */ s16 eyeTexIndex;
    /* 0x1A0 */ MsgEventFunc msgEventCallback;
    /* 0x1A4 */ Vec3s jointTable[2];
    /* 0x1B0 */ Vec3s morphTable[2];
} EnDnh; // size = 0x1BC

#endif // Z_EN_DNH_H
