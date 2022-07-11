#ifndef Z_EN_GE1_H
#define Z_EN_GE1_H

#include "global.h"

struct EnGe1;

typedef void (*EnGe1ActionFunc)(struct EnGe1*, PlayState*);


typedef struct EnGe1 {
    /* 0x000 */ PictoActor picto;
    /* 0x148 */ ColliderCylinder collider;
    /* 0x194 */ SkelAnime skelAnime;
    /* 0x1D8 */ Vec3f unk1D8;
    /* 0x1E4 */ Vec3s jointTable[16];
    /* 0x244 */ Vec3s morphTable[16];
    /* 0x2A4 */ Vec3s unk2A4;
    /* 0x2AA */ Vec3s unk2AA;
    /* 0x2B0 */ Path *unk2B0;                         /* inferred */
    /* 0x2B4 */ s32 unk2B4;                         /* inferred */
    /* 0x2B8 */ s16 unk2B8;                         /* inferred */
    /* 0x2BA */ s16 unk2BA;                         /* inferred */
    /* 0x2BC */ u16 unk2BC;                         /* inferred */
    /* 0x2BE */ s16 unk2BE;                         /* inferred */
    /* 0x2C0 */ s16 unk2C0;                         /* inferred */
    /* 0x2C2 */ s16 unk2C2;                         /* inferred */
    /* 0x2C4 */ u8 unk2C4;                          /* inferred */
    /* 0x2C8 */ EnGe1ActionFunc actionFunc;
} EnGe1; // size = 0x2CC

extern const ActorInit En_Ge1_InitVars;

#endif // Z_EN_GE1_H
