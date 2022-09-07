#ifndef Z_EN_GE2_H
#define Z_EN_GE2_H

#include "global.h"
#include "z64snap.h"

struct EnGe2;

typedef void (*EnGe2ActionFunc)(struct EnGe2*, PlayState*);

// typedef struct EnGe2 {
//     /* 0x000 */ PictoActor picto;
//     /* 0x144 */ char unk_144[0x1C0];
//     /* 0x308 */ EnGe2ActionFunc actionFunc;
// } EnGe2; // size = 0x30C

typedef struct EnGe2 {
    /* 0x000 */ PictoActor picto;
    /* 0x148 */ ColliderCylinder unk148;            /* inferred */
    /* 0x194 */ SkelAnime skelAnime;                   /* inferred */
    /* 0x1D8 */ Vec3s jointTable[22];
    /* 0x25C */ Vec3s morphTable[22];
    /* 0x2E0 */ s16 unk2E0;                         /* inferred */
    /* 0x2E2 */ s16 unk2E2;                         /* inferred */
    /* 0x2E4 */ Vec3s unk2E4;
    /* 0x2E8 */ char pad2EA[6];                     /* maybe part of unk2E6[5]? */
    /* 0x2F0 */ Path *unk2F0;                         /* inferred */
    /* 0x2F4 */ s32 unk2F4;                         /* inferred */
    /* 0x2F8 */ u16 unk2F8;                         /* inferred */
    /* 0x2FA */ s16 unk2FA;                         /* inferred */
    /* 0x2FC */ f32 unk2FC;                         /* inferred */
    /* 0x300 */ u8 unk300;                          /* inferred */
    /* 0x301 */ u8 unk301;                          /* inferred */
    /* 0x302 */ s16 unk302;                         /* inferred */
    /* 0x304 */ char pad304[2];
    /* 0x306 */ s16 unk306;                         /* inferred */
    /* 0x308 */ EnGe2ActionFunc actionFunc;
} EnGe2; // size = 0x30C

extern const ActorInit En_Ge2_InitVars;

#endif // Z_EN_GE2_H
