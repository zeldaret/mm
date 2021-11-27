#ifndef Z_EN_DAIKU_H
#define Z_EN_DAIKU_H

#include "global.h"

struct EnDaiku;

typedef void (*EnDaikuActionFunc)(struct EnDaiku*, GlobalContext*);

#define ENDAIKU_GET_FF(thisx) ((thisx)->params & 0xFF);
#define ENDAIKU_GET_FF00(thisx) (((thisx)->params >> 8) & 0xFF);

enum {
    /* 0x0 */ ENDAIKU_PARAMS_FF_0,
    /* 0x1 */ ENDAIKU_PARAMS_FF_1,
    /* 0x2 */ ENDAIKU_PARAMS_FF_2,
    /* 0x3 */ ENDAIKU_PARAMS_FF_3,
};

typedef struct EnDaiku {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[17];
    /* 0x1EE */ Vec3s morphTable[17];
    /* 0x254 */ EnDaikuActionFunc actionFunc;
    /* 0x258 */ Path* unk_258;
    /* 0x25C */ s16 unk_25C;
    /* 0x25E */ s16 unk_25E;
    /* 0x260 */ s16 unk_260;
    /* 0x262 */ UNK_TYPE1 unk_262[0x2];
    /* 0x264 */ s16 unk_264;
    /* 0x266 */ s16 unk_266;
    /* 0x268 */ UNK_TYPE1 unk_268[0x4];
    /* 0x26C */ Vec3f unk_26C;
    /* 0x278 */ s32 unk_278;
    /* 0x27C */ s16 unk_27C;
    /* 0x27E */ s16 unk_27E;
    /* 0x280 */ s16 unk_280;
    /* 0x282 */ s16 unk_282;
    /* 0x284 */ f32 unk_284;
    /* 0x288 */ s16 unk_288;
    /* 0x28A */ s16 unk_28A;
    /* 0x28C */ s16 unk_28C;
    /* 0x28E */ UNK_TYPE1 unk_28E[0xE];
    /* 0x29C */ ColliderCylinder collider;
} EnDaiku; // size = 0x2E8

extern const ActorInit En_Daiku_InitVars;

#endif // Z_EN_DAIKU_H
