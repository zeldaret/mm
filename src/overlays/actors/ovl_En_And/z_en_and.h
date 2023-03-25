#ifndef Z_EN_AND_H
#define Z_EN_AND_H

#include "global.h"

struct EnAnd;

typedef void (*EnAndActionFunc)(struct EnAnd*, PlayState*);

typedef struct EnAnd {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnAndActionFunc actionFunc;
    /* 0x18C */ u8 unk18C;                          /* inferred */
    /* 0x18D */ char pad18D[0x7];
    /* 0x194 */ Vec3f unk194; // limb pos
    /* 0x1A0 */ Vec3f unk1A0; // limb pos
    /* 0x1AC */ Vec3s unk1AC; // limb rot
    /* 0x1B2 */ Vec3s unk1B2; // limb rot
    /* 0x1B8 */ Vec3s jointTable[26];
    /* 0x254 */ Vec3s morphTable[26];
    /* 0x2F0 */ u16 unk2F0;                         /* inferred */
    /* 0x2F2 */ char pad2F2[0x4];
    /* 0x2F6 */ s16 unk2F6; // Some rotations
    /* 0x2F8 */ s16 unk2F8;
    /* 0x2FA */ s16 unk2FA;
    /* 0x2FC */ s16 unk2FC;
    /* 0x2FE */ char pad2FE[0x2];
    /* 0x300 */ s16 blinkTimer;
    /* 0x302 */ s16 eyeTexIndex;
    /* 0x304 */ s32 currentAnim;
    /* 0x308 */ s32 unk308;                         /* inferred */
    /* 0x30C */ s32 unk30C;                         /* inferred */
    /* 0x310 */ char pad310[4];
} EnAnd; // size = 0x314

#endif // Z_EN_AND_H
