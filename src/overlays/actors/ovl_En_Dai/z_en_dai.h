#ifndef Z_EN_DAI_H
#define Z_EN_DAI_H

#include "global.h"

struct EnDai;

typedef void (*EnDaiActionFunc)(struct EnDai* this, GlobalContext* globalCtx);

typedef struct EnDaiParticle {
    /* 0x00 */ u8 isEnabled;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ UNK_TYPE1 unk_03[0xD];
    /* 0x10 */ Vec3f unk_10;
    /* 0x1C */ Vec3f unk_1C;
    /* 0x28 */ Vec3f unk_28;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
} EnDaiParticle; // size = 0x3C

typedef struct EnDai {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnDaiActionFunc actionFunc;
    /* 0x18C */ MtxF unk_18C;
    /* 0x1CC */ u8 unk_1CC;
    /* 0x1CD */ u8 unk_1CD;
    /* 0x1CE */ u16 unk_1CE;
    /* 0x1D0 */ s32 unk_1D0;
    /* 0x1D4 */ s16 unk_1D4;
    /* 0x1D6 */ s16 unk_1D6;
    /* 0x1D8 */ s16 unk_1D8;
    /* 0x1DA */ s16 unk_1DA;
    /* 0x1DC */ s16 unk_1DC;
    /* 0x1E0 */ f32 unk_1E0;
    /* 0x1E4 */ Vec3f unk_1E4;
    /* 0x1F0 */ Vec3f unk_1F0;
    /* 0x1FC */ Vec3f unk_1FC;
    /* 0x208 */ Vec3s jointTable[19];
    /* 0x27A */ Vec3s morphTable[19];
    /* 0x2EC */ EnDaiParticle particles[32];
    /* 0xA6C */ s32 unk_A6C;
    /* 0xA70 */ s32 unk_A70;
} EnDai; // size = 0xA74

extern const ActorInit En_Dai_InitVars;

#endif // Z_EN_DAI_H
