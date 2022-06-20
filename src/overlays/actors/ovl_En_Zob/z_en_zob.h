#ifndef Z_EN_ZOB_H
#define Z_EN_ZOB_H

#include "global.h"

struct EnZob;

typedef void (*EnZobActionFunc)(struct EnZob*, GlobalContext*);

#define ENZOB_GET_F(thisx) ((thisx)->params & 0xF)

enum {
    /* 1 */ ENZOB_F_1 = 1,
    /* 2 */ ENZOB_F_2,
};

typedef struct EnZob {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[24];
    /* 0x0218 */ Vec3s morphTable[24];
    /* 0x02A8 */ ColliderCylinder collider;
    /* 0x02F4 */ u16 unk_2F4;
    /* 0x02F6 */ Vec3s unk_2F6;
    /* 0x02FC */ Vec3s unk_2FC;
    /* 0x0302 */ s16 unk_302;
    /* 0x0304 */ u16 unk_304;
    /* 0x0306 */ s16 unk_306[4];
    /* 0x030E */ s16 unk_30E;
    /* 0x0310 */ s16 unk_310;
    /* 0x0312 */ s16 unk_312;
    /* 0x0314 */ EnZobActionFunc actionFunc;
} EnZob; // size = 0x318

extern const ActorInit En_Zob_InitVars;

#endif // Z_EN_ZOB_H
