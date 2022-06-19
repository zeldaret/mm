#ifndef Z_EN_BJT_H
#define Z_EN_BJT_H

#include "global.h"

struct EnBjt;

typedef void (*EnBjtActionFunc)(struct EnBjt*, PlayState*);

typedef struct EnBjt {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnBjtActionFunc actionFunc;
    /* 0x18C */ ColliderCylinder collider;
    /* 0x1D8 */ u8 unk1D8;
    /* 0x1DC */ s32 unk1DC;
    /* 0x1E0 */ Vec3s unk1E0[7];
    /* 0x20A */ Vec3s unk20A[7];
    /* 0x234 */ u16 unk234;
    /* 0x236 */ u16 unk236;
    /* 0x238 */ f32 unk238;
    /* 0x23C */ f32 unk23C;
    /* 0x240 */ s16 unk240;
    /* 0x242 */ s16 unk242;
    /* 0x244 */ char unk244[4];
    /* 0x248 */ s32 unk248;
    /* 0x24C */ void *unk24C;
    /* 0x250 */ s32 unk250;
    /* 0x254 */ char pad254[8]; /* maybe part of unk250[3]? */
} EnBjt; // size = 0x25C


extern const ActorInit En_Bjt_InitVars;

#endif // Z_EN_BJT_H
