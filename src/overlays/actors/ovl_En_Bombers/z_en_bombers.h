#ifndef Z_EN_BOMBERS_H
#define Z_EN_BOMBERS_H

#include "global.h"

struct EnBombers;

typedef void (*EnBombersActionFunc)(struct EnBombers*, GlobalContext*);

#define ENBOMBERS_GET_F(thisx) ((thisx)->params & 0xF)
#define ENBOMBERS_GET_F0(thisx) (((thisx)->params >> 4) & 0xF)

enum {
    /* 0 */ ENBOMBERS_F_0,
    /* 1 */ ENBOMBERS_F_1,
    /* 2 */ ENBOMBERS_F_2,
    /* 3 */ ENBOMBERS_F_3,
    /* 4 */ ENBOMBERS_F_4,
};

#define ENBOMBERS_F0_0 0

typedef struct EnBombers {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[21];
    /* 0x0206 */ Vec3s morphtable[21];
    /* 0x0284 */ EnBombersActionFunc actionFunc;
    /* 0x0288 */ s16 unk_288;
    /* 0x028A */ s16 unk_28A;
    /* 0x028C */ UNK_TYPE1 unk28C[2];
    /* 0x028E */ s16 unk_28E;
    /* 0x0290 */ s16 unk_290;
    /* 0x0294 */ Vec3f unk_294;
    /* 0x02A0 */ s16 unk_2A0;
    /* 0x02A2 */ UNK_TYPE1 unk2A2[2];
    /* 0x02A4 */ s16 unk_2A4;
    /* 0x02A6 */ s16 unk_2A6;
    /* 0x02A8 */ s16 unk_2A8;
    /* 0x02AA */ s16 unk_2AA;
    /* 0x02AC */ s16 unk_2AC;
    /* 0x02B0 */ f32 unk_2B0;
    /* 0x02B4 */ f32 unk_2B4;
    /* 0x02B8 */ s16 unk_2B8;
    /* 0x02BA */ s16 unk_2BA;
    /* 0x02BC */ s16 unk_2BC;
    /* 0x02BE */ s16 unk_2BE;
    /* 0x02C0 */ s16 unk_2C0;
    /* 0x02C4 */ s32 unk_2C4;
    /* 0x02C8 */ ColliderCylinder collider;
} EnBombers; // size = 0x314

extern const ActorInit En_Bombers_InitVars;

#endif // Z_EN_BOMBERS_H
