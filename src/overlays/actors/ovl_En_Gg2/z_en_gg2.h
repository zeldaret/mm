#ifndef Z_EN_GG2_H
#define Z_EN_GG2_H

#include "global.h"

struct EnGg2;

typedef void (*EnGg2ActionFunc)(struct EnGg2*, GlobalContext*);

#define ENGG2_GET_FC00(thisx) (((thisx)->params & 0xFC00) >> 0xA)

typedef struct EnGg2 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ UNK_TYPE1 unk144[0x4C];
    /* 0x0190 */ SkelAnime skelAnime;
    /* 0x01D4 */ EnGg2ActionFunc actionFunc;
    /* 0x01D8 */ Path* unk_1D8;
    /* 0x01DC */ s32 unk_1DC;
    /* 0x01E0 */ Vec3s unk_1E0;
    /* 0x01E6 */ Vec3s unk_1E6;
    /* 0x01EC */ Vec3s jointTable[20];
    /* 0x0264 */ Vec3s morphTable[20];
    /* 0x02DC */ UNK_TYPE1 unk2DC[0x8];
    /* 0x02E4 */ s16 unk_2E4;
    /* 0x02E6 */ UNK_TYPE1 unk2E6[4];
    /* 0x02EA */ s16 unk_2EA;
    /* 0x02EC */ s16 unk_2EC;
    /* 0x02EE */ s16 unk_2EE;
    /* 0x02F0 */ u8 unk_2F0;
    /* 0x02F1 */ u8 unk_2F1;
    /* 0x02F2 */ s16 unk_2F2;
    /* 0x02F4 */ s16 unk_2F4;
    /* 0x02F6 */ s16 unk_2F6;
    /* 0x02F8 */ UNK_TYPE1 unk2F8[0xC];
    /* 0x0304 */ Vec3f unk_304;
} EnGg2; // size = 0x310

extern const ActorInit En_Gg2_InitVars;

#endif // Z_EN_GG2_H
