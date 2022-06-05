#ifndef Z_EN_AH_H
#define Z_EN_AH_H

#include "global.h"

struct EnAh;

typedef void (*EnAhActionFunc)(struct EnAh*, GlobalContext*);
typedef void (*EnAhUnkFunc)(struct EnAh*, GlobalContext*);

typedef struct EnAh {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ EnAhActionFunc actionFunc;
    /* 0x018C */ EnAhUnkFunc unk_18C;
    /* 0x0190 */ ColliderCylinder collider;
    /* 0x01DC */ u8 unk_1DC;
    /* 0x01E0 */ s32 unk_1E0;
    /* 0x01E4 */ Actor* unk_1E4;
    /* 0x01E8 */ Vec3f unk_1E8[2];
    /* 0x0200 */ Vec3s unk_200[2];
    /* 0x020C */ Vec3s jointTable[17];
    /* 0x0272 */ Vec3s morphTable[17];
    /* 0x02D8 */ u16 unk_2D8;
    /* 0x02DA */ u16 unk_2DA;
    /* 0x02DC */ f32 unk_2DC;
    /* 0x02E0 */ UNK_TYPE1 unk2E0[0xC];
    /* 0x02EC */ s16 unk_2EC;
    /* 0x02EE */ s16 unk_2EE;
    /* 0x02F0 */ s16 unk_2F0;
    /* 0x02F2 */ s16 unk_2F2;
    /* 0x02F4 */ s16 unk_2F4;
    /* 0x02F6 */ s16 unk_2F6;
    /* 0x02F8 */ s16 unk_2F8;
    /* 0x02FA */ s16 unk_2FA;
    /* 0x02FC */ s16 unk_2FC;
    /* 0x02FE */ s16 unk_2FE;
    /* 0x0300 */ s32 unk_300;
} EnAh; // size = 0x304

extern const ActorInit En_Ah_InitVars;

#endif // Z_EN_AH_H
