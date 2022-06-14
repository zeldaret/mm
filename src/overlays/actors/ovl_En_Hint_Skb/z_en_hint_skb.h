#ifndef Z_EN_HINT_SKB_H
#define Z_EN_HINT_SKB_H

#include "global.h"

struct EnHintSkb;

typedef void (*EnHintSkbActionFunc)(struct EnHintSkb*, GlobalContext*);

#define ENHINTSKB_GET_FF(thisx) ((thisx)->params & 0xFF)

typedef struct EnHintSkb {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderJntSph collider;
    /* 0x0164 */ ColliderJntSphElement colliderElement[2];
    /* 0x01E4 */ SkelAnime skelAnime;
    /* 0x0228 */ EnHintSkbActionFunc actionFunc;
    /* 0x022C */ Vec3f limbPos[14];
    /* 0x02D4 */ f32 drawDmgEffAlpha;
    /* 0x02D8 */ f32 drawDmgEffScale;
    /* 0x02DC */ s32 limbCount;
    /* 0x02E0 */ Vec3s jointTable[20];
    /* 0x0358 */ Vec3s morphtable[20];
    /* 0x03D0 */ UNK_TYPE1 unk3D0[0xC];
    /* 0x03DC */ s16 unk_3DC;
    /* 0x03DE */ s16 unk_3DE;
    /* 0x03E0 */ s16 unk_3E0;
    /* 0x03E2 */ s16 drawDmgEffTimer;
    /* 0x03E4 */ s16 unk_3E4;
    /* 0x03E6 */ u16 unk_3E6;
    /* 0x03E8 */ u8 unk_3E8;
    /* 0x03E9 */ u8 drawDmgEffType;
} EnHintSkb; // size = 0x3EC

extern const ActorInit En_Hint_Skb_InitVars;

#endif // Z_EN_HINT_SKB_H
