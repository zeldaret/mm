#ifndef Z_EN_RAIL_SKB_H
#define Z_EN_RAIL_SKB_H

#include "global.h"

struct EnRailSkb;

typedef void (*EnRailSkbActionFunc)(struct EnRailSkb*, GlobalContext*);
typedef void (*EnRailSkbUnkFunc)(struct EnRailSkb*);

#define ENRAILSKB_GET_FF00(thisx) (((thisx)->params >> 8) & 0xFF)
#define ENRAILSKB_GET_FF(thisx) ((thisx)->params & 0xFF)

typedef struct EnRailSkb {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderJntSph collider;
    /* 0x164 */ ColliderJntSphElement colliderElements[2];
    /* 0x1E4 */ SkelAnime skelAnime;
    /* 0x228 */ EnRailSkbActionFunc actionFunc;
    /* 0x22C */ ObjHakaisi* unk_22C;
    /* 0x230 */ Vec3s* unk_230;
    /* 0x234 */ Vec3f limbPos[14];
    /* 0x2DC */ s32 limbCount;
    /* 0x2E0 */ s32 unk_2E0;
    /* 0x2E4 */ s32 unk_2E4;
    /* 0x2E8 */ s32 unk_2E8;
    /* 0x2EC */ f32 drawDmgEffAlpha;
    /* 0x2F0 */ f32 drawDmgEffScale;
    /* 0x2F4 */ Vec3s jointTable[20];
    /* 0x36C */ Vec3s morphTable[20];
    /* 0x3E4 */ UNK_TYPE1 unk3E4[0xC];
    /* 0x3F0 */ s16 drawDmgEffTimer;
    /* 0x3F2 */ s16 unk_3F2;
    /* 0x3F4 */ s16 unk_3F4;
    /* 0x3F6 */ s16 unk_3F6;
    /* 0x3F8 */ s16 unk_3F8;
    /* 0x3FA */ s16 unk_3FA;
    /* 0x3FC */ s16 unk_3FC;
    /* 0x3FE */ s16 unk_3FE;
    /* 0x400 */ u16 unk_400;
    /* 0x402 */ u8 unk_402;
    /* 0x403 */ u8 drawDmgEffType;
} EnRailSkb; // size = 0x404

extern const ActorInit En_Rail_Skb_InitVars;

#endif // Z_EN_RAIL_SKB_H
