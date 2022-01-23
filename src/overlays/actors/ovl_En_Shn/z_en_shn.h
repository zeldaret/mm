#ifndef Z_EN_SHN_H
#define Z_EN_SHN_H

#include "global.h"

struct EnShn;

typedef void (*EnShnActionFunc)(struct EnShn*, GlobalContext*);

typedef struct EnShn {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnShnActionFunc actionFunc;
    /* 0x148 */ SkelAnime skelAnime; // size = 0x44            
    /* 0x18C */ char pad18C[0x4C];
    /* 0x1D8 */ u16 unk1D8;
    /* 0x1DA */ u16 unk1DA;
    /* 0x1DC */ s32 *unk1DC;
    /* 0x1E0 */ s32 unk1E0;
    /* 0x1E4 */ Player *unk1E4;
    /* 0x1E8 */ char pad1E8[0x12];
    /* 0x1FA */ Vec3s unk1FA;
    /* 0x200 */ char pad200[0x5A];
    /* 0x25A */ Vec3s unk25A;
    /* 0x260 */ char pad260[0x5A];
    /* 0x2BA */ s16 unk2BA;
    /* 0x2BC */ s16 unk2BC;
    /* 0x2BE */ s16 unk2BE;
    /* 0x2C0 */ char pad2C0[6];
    /* 0x2C6 */ s16 unk2C6;
    /* 0x2C8 */ s16 unk2C8;
    /* 0x2CA */ s16 unk2CA;
    /* 0x2CC */ f32 unk2CC;
    /* 0x2D0 */ char pad2D0[8];
    /* 0x2D8 */ s32 unk2D8;
    /* 0x2DC */ char pad2DC[4];
    /* 0x2E0 */ s32 unk2E0;
    /* 0x2E4 */ s32 unk2E4;
    /* 0x2E8 */ s32 unk2E8;
    /* 0x2EC */ s32 unk2EC;
} EnShn;   // size = 0x2F0

extern const ActorInit En_Shn_InitVars;

#endif // Z_EN_SHN_H
