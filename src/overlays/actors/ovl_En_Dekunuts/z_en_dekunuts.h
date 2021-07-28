#ifndef Z_EN_DEKUNUTS_H
#define Z_EN_DEKUNUTS_H

#include "global.h"

struct EnDekunuts;

typedef void (*EnDekunutsActionFunc)(struct EnDekunuts*, GlobalContext*);

#define ENDEKUNUTS_FF00(thisx) (((thisx)->params >> 8) & 0xFF);

enum {
    /* 0x0 */ ENDEKUNUTS_PARAMS_0,
    /* 0x1 */ ENDEKUNUTS_PARAMS_1,
    /* 0x2 */ ENDEKUNUTS_PARAMS_2,
    /* 0xFF*/ ENDEKUNUTS_PARAMS_FF = 0xFF,
};

typedef struct EnDekunuts {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnDekunutsActionFunc actionFunc;
    /* 0x18C */ u8 unk_18C;
    /* 0x18D */ u8 unk_18D;
    /* 0x18E */ u8 unk_18E;
    /* 0x190 */ s16 unk_190;
    /* 0x192 */ s16 unk_192;
    /* 0x194 */ s16 unk_194;
    /* 0x196 */ Vec3s jointTable[10];
    /* 0x1D2 */ Vec3s morphTable[10];
    /* 0x210 */ f32 unk_210;
    /* 0x214 */ f32 unk_214;
    /* 0x218 */ f32 unk_218;
    /* 0x21C */ Vec3f unk_21C[8];
    /* 0x27C */ ColliderCylinder collider;
} EnDekunuts; // size = 0x2C8

extern const ActorInit En_Dekunuts_InitVars;

#endif // Z_EN_DEKUNUTS_H
