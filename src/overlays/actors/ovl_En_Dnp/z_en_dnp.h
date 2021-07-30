#ifndef Z_EN_DNP_H
#define Z_EN_DNP_H

#include "global.h"

struct EnDnp;

typedef void (*EnDnpActionFunc)(struct EnDnp*, GlobalContext*);

#define ENDNP_PARAMS_7(thisx) ((thisx)->params & 7)

enum {
    /* 0x0 */ ENDNP_PARAMS_7_0,
    /* 0x1 */ ENDNP_PARAMS_7_1,
    /* 0x2 */ ENDNP_PARAMS_7_2,
};

typedef struct EnDnp {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnDnpActionFunc actionFunc;
    /* 0x18C */ ColliderCylinder collider;
    /* 0x1D8 */ Vec3f unk_1D8;
    /* 0x1E4 */ Vec3s unk_1E4;
    /* 0x1EA */ Vec3s jointTable[26];
    /* 0x286 */ Vec3s morphTable[26];
    /* 0x322 */ u16 unk_322;
    /* 0x324 */ u8 unk_324;
    /* 0x328 */ s32 unk_328;
    /* 0x32C */ UNK_TYPE1 unk_32C[0x2];
    /* 0x32E */ s16 unk_32E;
    /* 0x330 */ s16 unk_330;
    /* 0x332 */ s16 unk_332;
    /* 0x334 */ s16 unk_334;
    /* 0x336 */ s16 unk_336;
    /* 0x338 */ s16 unk_338;
    /* 0x33A */ UNK_TYPE1 unk_33A[0x6];
    /* 0x340 */ s32 unk_340;
} EnDnp; // size = 0x344

extern const ActorInit En_Dnp_InitVars;

#endif // Z_EN_DNP_H
