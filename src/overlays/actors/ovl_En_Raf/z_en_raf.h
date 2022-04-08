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
    /* 0x354 */ char unk_354[0x5C];
    /* 0x3B0 */ f32 unk_3B0;
    /* 0x3B4 */ char unk_3B4[0x6];
    /* 0x3BA */ s16 unk_3BA;
    /* 0x3BC */ char unk_3BC[2];
    /* 0x3BE */ s16 unk_3BE;
    /* 0x3C0 */ s16 unk_3C0;
    /* 0x3C2 */ char unk_3C2[0xE];
    /* 0x3D0 */ ColliderCylinder collider;
    /* 0x41C */ char pad_41C[0x6C8];
} EnRaf; // size = 0xAE4

extern const ActorInit En_Raf_InitVars;

#endif // Z_EN_RAF_H
