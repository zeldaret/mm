#ifndef Z_EN_ZOS_H
#define Z_EN_ZOS_H

#include "global.h"

struct EnZos;

typedef void (*EnZosActionFunc)(struct EnZos*, GlobalContext*);

#define ENZOS_GET_F(thisx) ((thisx)->params & 0xF)

enum {
    /* 1 */ ENZOS_F_1 = 1,
    /* 2 */ ENZOS_F_2,
};

typedef struct EnZos {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ Vec3s jointTable[18];
    /* 0x01B0 */ Vec3s morphTable[18];
    /* 0x021C */ SkelAnime skelAnime;
    /* 0x0260 */ ColliderCylinder collider;
    /* 0x02AC */ s16 unk_2AC;
    /* 0x02AE */ s16 unk_2AE;
    /* 0x02B0 */ UNK_TYPE1 unk2B0[6];
    /* 0x02B6 */ u16 unk_2B6;
    /* 0x02B8 */ s16 unk_2B8;
    /* 0x02BA */ s16 unk_2BA;
    /* 0x02BC */ s16 unk_2BC;
    /* 0x02C0 */ EnZosActionFunc actionFunc;
} EnZos; // size = 0x2C4

extern const ActorInit En_Zos_InitVars;

#endif // Z_EN_ZOS_H
