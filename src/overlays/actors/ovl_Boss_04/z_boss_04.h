#ifndef Z_BOSS_04_H
#define Z_BOSS_04_H

#include "global.h"

struct Boss04;

typedef void (*Boss04ActionFunc)(struct Boss04*, GlobalContext*);

typedef struct Boss04 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[9];
    /* 0x01BE */ Vec3s morphtable[9];
    /* 0x01F4 */ s16 unk_1F4;
    /* 0x01F6 */ u8 unk_1F6;
    /* 0x01F7 */ u8 unk_1F7;
    /* 0x01F8 */ s16 unk_1F8;
    /* 0x01FA */ s16 unk_1FA;
    /* 0x01FC */ UNK_TYPE1 unk_1FC[2];
    /* 0x01FE */ s16 unk_1FE;
    /* 0x0200 */ s16 unk_200;
    /* 0x0204 */ Boss04ActionFunc actionFunc;
    /* 0x0208 */ ColliderJntSph collider1;
    /* 0x0228 */ ColliderJntSphElement collider1Elements[1];
    /* 0x0268 */ ColliderJntSph collider2;
    /* 0x0288 */ ColliderJntSphElement collider2Elements[1];
    /* 0x02C8 */ s16 unk_2C8;
    /* 0x02CC */ f32 unk_2CC;
    /* 0x02D0 */ f32 unk_2D0;
    /* 0x02D4 */ s16 unk_2D4;
    /* 0x02D6 */ s16 unk_2D6;
    /* 0x02D8 */ s16 unk_2D8;
    /* 0x02DA */ s16 unk_2DA;
    /* 0x02DC */ s16 unk_2DC;
    /* 0x02DE */ s16 unk_2DE;
    /* 0x02E0 */ s16 unk_2E0;
    /* 0x02E2 */ s16 unk_2E2;
    /* 0x02E4 */ Vec3f unk_2E4[16];
    /* 0x02E4 */ Vec3f unk_3A4[15];
    /* 0x02E4 */ Vec3f unk_458[15];
    /* 0x02E4 */ Vec3f unk_50C[11];
    /* 0x02E4 */ Vec3f unk_590[11];
    /* 0x02E4 */ Vec3f unk_614[6];
    /* 0x02E4 */ Vec3f unk_65C[6];
    /* 0x02E4 */ Vec3f unk_6A4;
    /* 0x02E4 */ Vec3f unk_6B0;
    /* 0x06BC */ Vec3f unk_6BC;
    /* 0x06C8 */ Vec3f unk_6C8;
    /* 0x06D4 */ f32 unk_6D4;
    /* 0x06D8 */ f32 unk_6D8;
    /* 0x06DC */ f32 unk_6DC;
    /* 0x06E0 */ f32 unk_6E0;
    /* 0x06E4 */ f32 unk_6E4;
    /* 0x06E8 */ f32 unk_6E8;
    /* 0x06EC */ UNK_TYPE1 unk_6EC[4];
    /* 0x06F0 */ f32 unk_6F0;
    /* 0x06F4 */ s16 unk_6F4;
    /* 0x06F6 */ s16 unk_6F6;
    /* 0x06F8 */ f32 unk_6F8;
    /* 0x06FC */ f32 unk_6FC;
    /* 0x0700 */ f32 unk_700;
    /* 0x0704 */ u32 unk_704;
    /* 0x0708 */ s16 unk_708;
    /* 0x070A */ s16 unk_70A;
    /* 0x070C */ Vec3f unk_70C;
    /* 0x0718 */ Vec3f unk_718;
    /* 0x0724 */ UNK_TYPE1 unk_724[4];
    /* 0x0728 */ f32 unk_728;
    /* 0x072C */ UNK_TYPE1 unk_72C[0x10];
    /* 0x073C */ f32 unk_73C;
    /* 0x0740 */ UNK_TYPE1 unk_740[4];
    /* 0x0744 */ f32 unk_744;
    /* 0x0748 */ s16 unk_748;
    /* 0x074A */ u8 unk_74A;
} Boss04; // size = 0x74C

extern const ActorInit Boss_04_InitVars;

#endif // Z_BOSS_04_H
