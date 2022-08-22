#ifndef Z_EN_SKB_H
#define Z_EN_SKB_H

#include "global.h"

struct EnSkb;

typedef void (*EnSkbActionFunc)(struct EnSkb*, PlayState*);

#define ENSKB_GET_F0(thisx) (((thisx)->params >> 4) & 0xF)

typedef struct EnSkb {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ ColliderJntSph collider;
    /* 0x1A8 */ ColliderJntSphElement colliderElements[2];
    /* 0x228 */ EnSkbActionFunc actionFunc;
    /* 0x22C */ f32 drawDmgEffAlpha;
    /* 0x230 */ f32 drawDmgEffScale;
    /* 0x234 */ Vec3f limbPos[14];
    /* 0x2DC */ s32 limbCount;
    /* 0x2E0 */ Vec3s jointTable[20];
    /* 0x358 */ Vec3s morphTable[20];
    /* 0x3D0 */ s16 unk_3D0;
    /* 0x3D2 */ s16 drawDmgEffTimer;
    /* 0x3D4 */ s16 unk_3D4;
    /* 0x3D6 */ s16 unk_3D6;
    /* 0x3D8 */ s16 unk_3D8;
    /* 0x3DA */ s16 unk_3DA;
    /* 0x3DC */ s16 unk_3DC;
    /* 0x3DE */ s16 unk_3DE;
    /* 0x3E0 */ s16 unk_3E0;
    /* 0x3E2 */ s16 unk_3E2;
    /* 0x3E4 */ u8 unk_3E4;
    /* 0x3E5 */ u8 unk_3E5;
    /* 0x3E6 */ u8 drawDmgEffType;
} EnSkb; // size = 0x3E8

extern const ActorInit En_Skb_InitVars;

#endif // Z_EN_SKB_H
