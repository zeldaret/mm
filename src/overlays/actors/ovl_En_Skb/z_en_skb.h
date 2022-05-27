#ifndef Z_EN_SKB_H
#define Z_EN_SKB_H

#include "global.h"

struct EnSkb;

typedef void (*EnSkbActionFunc)(struct EnSkb*, GlobalContext*);

#define ENSKB_GET_F0(thisx) (((thisx)->params >> 4) & 0xF)

typedef struct EnSkb {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ ColliderJntSph collider;
    /* 0x01A8 */ ColliderJntSphElement colliderElements[2];
    /* 0x0228 */ EnSkbActionFunc actionFunc;
    /* 0x022C */ f32 drawDmgEffAlpha;
    /* 0x0230 */ f32 drawDmgEffScale;
    /* 0x0234 */ Vec3f limbPos[14];
    /* 0x02DC */ s32 limbCount;
    /* 0x02E0 */ Vec3s jointTable[20];
    /* 0x0358 */ Vec3s morphTable[20];
    /* 0x03D0 */ s16 unk_3D0;
    /* 0x03D2 */ s16 drawDmgEffTimer;
    /* 0x03D4 */ s16 unk_3D4;
    /* 0x03D6 */ s16 unk_3D6;
    /* 0x03D8 */ s16 unk_3D8;
    /* 0x03DA */ s16 unk_3DA;
    /* 0x03DC */ s16 unk_3DC;
    /* 0x03DE */ s16 unk_3DE;
    /* 0x03E0 */ s16 unk_3E0;
    /* 0x03E2 */ s16 unk_3E2;
    /* 0x03E4 */ u8 unk_3E4;
    /* 0x03E5 */ u8 unk_3E5;
    /* 0x03E6 */ u8 drawDmgEffType;
} EnSkb; // size = 0x3E8

extern const ActorInit En_Skb_InitVars;

#endif // Z_EN_SKB_H
