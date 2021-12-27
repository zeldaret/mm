#ifndef Z_EN_ZOG_H
#define Z_EN_ZOG_H

#include "global.h"

struct EnZog;

typedef void (*EnZogActionFunc)(struct EnZog*, GlobalContext*);

#define ENZOG_GET_F(thisx) ((thisx)->params & 0xF)
#define ENZOG_GET_FC00(thisx) (((thisx)->params & 0xFC00) >> 0xA)

#define ENZOG_F_2 2
#define ENZOG_FC00_63 63

typedef struct EnZog {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider;
    /* 0x190 */ SkelAnime skelAnime;
    /* 0x1D4 */ Vec3s jointTable[23];
    /* 0x25E */ Vec3s morphTable[23];
    /* 0x2E8 */ Path* unk_2E8;
    /* 0x2EC */ s32 unk_2EC;
    /* 0x2F0 */ Vec3f unk_2F0;
    /* 0x2FC */ s16 unk_2FC;
    /* 0x2FE */ s16 unk_2FE;
    /* 0x300 */ s16 unk_300;
    /* 0x302 */ s16 unk_302;
    /* 0x304 */ s16 unk_304;
    /* 0x306 */ s16 unk_306;
    /* 0x308 */ s16 unk_308;
    /* 0x30A */ u16 unk_30A;
    /* 0x30C */ s16 unk_30C[7];
    /* 0x31A */ s16 unk_31A;
    /* 0x31C */ s16 unk_31C;
    /* 0x31E */ s16 unk_31E;
    /* 0x320 */ s16 unk_320;
    /* 0x322 */ s16 unk_322;
    /* 0x324 */ s16 unk_324;
    /* 0x328 */ EnZogActionFunc actionFunc;
} EnZog; // size = 0x32C

extern const ActorInit En_Zog_InitVars;

#endif // Z_EN_ZOG_H
