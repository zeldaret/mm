#ifndef Z_EN_SHN_H
#define Z_EN_SHN_H

#include "global.h"

struct EnShn;

typedef void (*EnShnActionFunc)(struct EnShn*, GlobalContext*);

typedef struct EnShn {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnShnActionFunc actionFunc;
    /* 0x148 */ SkelAnime unk148;                   /* inferred */
    /* 0x18C */ char pad18C[0x4C];                  /* maybe part of unk148[2]? */
    /* 0x1D8 */ u16 unk1D8;
    /* 0x1DA */ char pad1DA[0x20];                  /* maybe part of unk1D8[0x11]? */
    /* 0x1FA */ Vec3s unk1FA;
    /* 0x200 */ char pad200[0x5A];                  /* maybe part of unk1FA[0x10]? */
    /* 0x25A */ Vec3s unk25A;
    /* 0x260 */ char pad260[0x5E];                  /* maybe part of unk25A[0x10]? */
    /* 0x2BE */ s16 unk2BE;
    /* 0x2C0 */ char pad2C0[0xC];                   /* maybe part of unk2BE[7]? */
    /* 0x2CC */ f32 unk2CC;                         /* inferred */
    /* 0x2D0 */ char pad2D0[8];                     /* maybe part of unk2CC[3]? */
    /* 0x2D8 */ s32 unk2D8;
    /* 0x2DC */ char pad2DC[4];
    /* 0x2E0 */ s32 unk2E0;
    /* 0x2E4 */ char pad2E4[4];
    /* 0x2E8 */ s32 unk2E8;
    /* 0x2EC */ char pad2EC[4];
} EnShn;  // size = 0x2F0

extern const ActorInit En_Shn_InitVars;

#endif // Z_EN_SHN_H
