#ifndef Z_EN_BOM_BOWL_MAN_H
#define Z_EN_BOM_BOWL_MAN_H

#include "global.h"

struct EnBomBowlMan;

typedef void (*EnBomBowlManActionFunc)(struct EnBomBowlMan*, GlobalContext*);

#define ENBOMBOWLMAN_GET_F(thisx) ((thisx)->params & 0xF)
#define ENBOMBOWLMAN_GET_F0(thisx) (((thisx)->params >> 4) & 0xF)
#define ENBOMBOWLMAN_GET_FF00(thisx) (((thisx)->params >> 8) & 0xFF)

#define ENBOMBOWLMAN_F0_0 0
#define ENBOMBOWLMAN_F0_2 2

#define ENBOMBOWLMAN_FF00_MINUS1 -1

typedef struct EnBomBowlMan {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[21];
    /* 0x0206 */ Vec3s morphTable[21];
    /* 0x0284 */ EnBomBowlManActionFunc actionFunc;
    /* 0x0288 */ s16 unk_288;
    /* 0x028A */ s16 unk_28A;
    /* 0x028C */ UNK_TYPE1 unk28C[2];
    /* 0x028E */ s16 unk_28E;
    /* 0x0290 */ s16 unk_290;
    /* 0x0292 */ UNK_TYPE1 unk292[2];
    /* 0x0294 */ Path* path;
    /* 0x0298 */ s16 unk_298;
    /* 0x029A */ s16 unk_29A;
    /* 0x029C */ s16 unk_29C;
    /* 0x029E */ s16 unk_29E;
    /* 0x02A0 */ Vec3f unk_2A0;
    /* 0x02AC */ UNK_TYPE1 unk2AC[0xC];
    /* 0x02B8 */ s16 unk_2B8;
    /* 0x02BA */ s16 unk_2BA;
    /* 0x02BC */ s16 unk_2BC;
    /* 0x02BE */ UNK_TYPE1 unk2BE[2];
    /* 0x02C0 */ s16 unk_2C0;
    /* 0x02C2 */ s16 unk_2C2;
    /* 0x02C4 */ f32 unk_2C4;
    /* 0x02C8 */ f32 unk_2C8;
    /* 0x02CC */ s16 unk_2CC[2];
    /* 0x02D0 */ s16 unk_2D0;
    /* 0x02D2 */ s16 unk_2D2;
    /* 0x02D4 */ s16 unk_2D4;
    /* 0x02D6 */ s16 unk_2D6;
    /* 0x02D8 */ struct EnBomBowlMan* unk_2D8[5];
    /* 0x02EC */ UNK_TYPE1 unk2EC[0x4];
    /* 0x02F0 */ s16 unk_2F0;
    /* 0x02F2 */ s16 unk_2F2;
    /* 0x02F4 */ s16 unk_2F4;
    /* 0x02F6 */ s16 unk_2F6;
    /* 0x02F8 */ s32 unk_2F8;
} EnBomBowlMan; // size = 0x2FC

extern const ActorInit En_Bom_Bowl_Man_InitVars;

#endif // Z_EN_BOM_BOWL_MAN_H
