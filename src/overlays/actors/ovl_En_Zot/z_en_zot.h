#ifndef Z_EN_ZOT_H
#define Z_EN_ZOT_H

#include "global.h"

struct EnZot;

typedef void (*EnZotActionFunc)(struct EnZot*, GlobalContext*);

#define ENZOT_GET_1F(thisx) ((thisx)->params & 0x1F)
#define ENZOT_GET_FC00(thisx) (((thisx)->params & 0xFC00) >> 0xA)

typedef struct EnZot {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ ColliderCylinder collider;
    /* 0x01D4 */ Vec3s jointTable[20];
    /* 0x024C */ Vec3s morphTable[20];
    /* 0x02C4 */ Vec3s unk_2C4;
    /* 0x02CA */ Vec3s unk_2CA;
    /* 0x02D0 */ Path* path;
    /* 0x02D4 */ s32 unk_2D4;
    /* 0x02D8 */ Actor* unk_2D8[5];
    /* 0x02EC */ s16 unk_2EC;
    /* 0x02EE */ s16 unk_2EE;
    /* 0x02F0 */ s16 unk_2F0;
    /* 0x02F2 */ u16 unk_2F2;
    /* 0x02F4 */ s16 unk_2F4;
    /* 0x02F8 */ EnZotActionFunc actionFunc;
} EnZot; // size = 0x2FC

extern const ActorInit En_Zot_InitVars;

#endif // Z_EN_ZOT_H
