#ifndef Z_EN_RAF_H
#define Z_EN_RAF_H

#include "global.h"

#define EN_RAF_GET_7F(thisx) ((thisx)->params & 0x7F)
#define EN_RAF_GET_1F(thisx) (((thisx)->params >> 7) & 0x1F)
#define EN_RAF_GET_F(thisx) (((thisx)->params >> 12) & 0xF)

struct EnRaf;

typedef void (*EnRafActionFunc)(struct EnRaf*, GlobalContext*);

typedef struct EnRaf {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ SkelAnime skelAnime;
    /* 0x1A0 */ Vec3s jointTable[12];
    /* 0x1E8 */ Vec3s morphTable[12];
    /* 0x230 */ EnRafActionFunc actionFunc;
    /* 0x234 */ Vec3f unk_234[12];
    /* 0x2C4 */ Vec3f unk_2C4[12];
    /* 0x354 */ Vec3s unk_354[12];
    /* 0x39C */ s16 unk_39C;
    /* 0x39E */ char unk_39E[0x2];
    /* 0x3A0 */ f32 unk_3A0;
    /* 0x3A4 */ char unk_3A4[0xC];
    /* 0x3B0 */ f32 unk_3B0;
    /* 0x3B4 */ s16 unk_3B4;
    /* 0x3B6 */ char unk_3B6[0x4];
    /* 0x3BA */ s16 unk_3BA;
    /* 0x3BC */ s16 unk_3BC;
    /* 0x3BE */ s16 unk_3BE;
    /* 0x3C0 */ s16 unk_3C0;
    /* 0x3C2 */ s16 unk_3C2;
    /* 0x3C4 */ s16 unk_3C4;
    /* 0x3C6 */ s16 unk_3C6;
    /* 0x3C8 */ char unk_3C8[0x8];
    /* 0x3D0 */ ColliderCylinder collider;
    /* 0x41C */ char pad_41C[0x6C8];
} EnRaf; // size = 0xAE4

extern const ActorInit En_Raf_InitVars;

#endif // Z_EN_RAF_H
