#ifndef Z_EN_MM3_H
#define Z_EN_MM3_H

#include "global.h"

struct EnMm3;

typedef void (*EnMm3ActionFunc)(struct EnMm3*, GlobalContext*);

typedef struct EnMm3 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ ColliderCylinder collider;
    /* 0x01D4 */ EnMm3ActionFunc actionFunc;
    /* 0x01D8 */ UNK_TYPE1 unk1D8[4];
    /* 0x01DC */ s32 unk_1DC;
    /* 0x01E0 */ Vec3s jointTable[16];
    /* 0x0240 */ Vec3s morphTable[16];
    /* 0x02A0 */ Vec3s unk_2A0;
    /* 0x02A6 */ Vec3s unk_2A6;
    /* 0x02AC */ s16 unk_2AC;
    /* 0x02AE */ s16 unk_2AE;
    /* 0x02B0 */ u16 unk_2B0;
    /* 0x02B2 */ u16 unk_2B2;
    /* 0x02B4 */ u16 unk_2B4;
} EnMm3; // size = 0x2B8

extern const ActorInit En_Mm3_InitVars;

#endif // Z_EN_MM3_H
