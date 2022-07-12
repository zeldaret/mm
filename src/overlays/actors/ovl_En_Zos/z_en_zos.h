#ifndef Z_EN_ZOS_H
#define Z_EN_ZOS_H

#include "global.h"

struct EnZos;

typedef void (*EnZosActionFunc)(struct EnZos*, PlayState*);

#define ENZOS_GET_F(thisx) ((thisx)->params & 0xF)

enum {
    /* 1 */ ENZOS_F_1 = 1,
    /* 2 */ ENZOS_F_2,
};

typedef struct EnZos {
    /* 0x000 */ Actor actor;
    /* 0x144 */ Vec3s jointTable[18];
    /* 0x1B0 */ Vec3s morphTable[18];
    /* 0x21C */ SkelAnime skelAnime;
    /* 0x260 */ ColliderCylinder collider;
    /* 0x2AC */ s16 unk_2AC;
    /* 0x2AE */ s16 unk_2AE;
    /* 0x2B0 */ UNK_TYPE1 unk2B0[6];
    /* 0x2B6 */ u16 unk_2B6;
    /* 0x2B8 */ s16 unk_2B8;
    /* 0x2BA */ s16 unk_2BA;
    /* 0x2BC */ s16 unk_2BC;
    /* 0x2C0 */ EnZosActionFunc actionFunc;
} EnZos; // size = 0x2C4

extern const ActorInit En_Zos_InitVars;

#endif // Z_EN_ZOS_H
