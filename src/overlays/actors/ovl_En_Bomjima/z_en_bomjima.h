#ifndef Z_EN_BOMJIMA_H
#define Z_EN_BOMJIMA_H

#include "global.h"

struct EnBomjima;

typedef void (*EnBomjimaActionFunc)(struct EnBomjima*, GlobalContext*);

#define ENBOMJIMA_GET_F0(thisx) (((thisx)->params >> 4) & 0xF)
#define ENBOMJIMA_GET_F(thisx) ((thisx)->params & 0xF)

typedef struct EnBomjima {
    /* 0x0000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[21];
    /* 0x206 */ Vec3s morphTable[21];
    /* 0x284 */ EnBomjimaActionFunc actionFunc;
    /* 0x288 */ s16 unk_288;
    /* 0x28A */ s16 unk_28A;
    /* 0x28C */ UNK_TYPE1 unk28C[2];
    /* 0x28E */ s16 unk_28E;
    /* 0x290 */ s16 unk_290;
    /* 0x292 */ UNK_TYPE1 unk292[2];
    /* 0x294 */ s16 unk_294;
    /* 0x296 */ UNK_TYPE1 unk296[4];
    /* 0x29A */ s16 unk_29A;
    /* 0x29C */ UNK_TYPE1 unk29C[4];
    /* 0x2A0 */ s16 unk_2A0;
    /* 0x2A2 */ s16 unk_2A2;
    /* 0x2A4 */ Vec3f unk_2A4;
    /* 0x2B0 */ Vec3f unk_2B0;
    /* 0x2BC */ s16 unk_2BC;
    /* 0x2BE */ s16 unk_2BE;
    /* 0x2C0 */ s16 unk_2C0;
    /* 0x2C2 */ s16 unk_2C2;
    /* 0x2C4 */ s16 unk_2C4;
    /* 0x2C6 */ s16 unk_2C6;
    /* 0x2C8 */ s16 unk_2C8;
    /* 0x2CA */ s16 unk_2CA;
    /* 0x2CC */ f32 unk_2CC;
    /* 0x2D0 */ f32 unk_2D0;
    /* 0x2D4 */ s16 unk_2D4[2];
    /* 0x2D8 */ UNK_TYPE1 unk2D8[4]; // maybe a part of the above?
    /* 0x2DC */ s16 unk_2DC;
    /* 0x2DE */ s16 unk_2DE;
    /* 0x2E0 */ s16 unk_2E0;
    /* 0x2E2 */ s16 unk_2E2;
    /* 0x2E4 */ s16 unk_2E4;
    /* 0x2E6 */ s16 unk_2E6;
    /* 0x2E8 */ s16 unk_2E8;
    /* 0x2EA */ s16 unk_2EA;
    /* 0x2EC */ s32 unk_2EC;
    /* 0x2F0 */ EnBombal* unk_2F0;
    /* 0x2F4 */ s16 unk_2F4;
    /* 0x2F8 */ ColliderCylinder collider;
} EnBomjima; // size = 0x344

extern const ActorInit En_Bomjima_InitVars;

#endif // Z_EN_BOMJIMA_H
