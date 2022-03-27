#ifndef Z_EN_HIDDEN_NUTS_H
#define Z_EN_HIDDEN_NUTS_H

#include "global.h"

struct EnHiddenNuts;

typedef void (*EnHiddenNutsActionFunc)(struct EnHiddenNuts*, GlobalContext*);

#define ENHIDDENNUTS_GET_SWITCHFLAG(thisx) ((thisx)->params & 0x7F)
#define ENHIDDENNUTS_GET_F80(thisx) (((thisx)->params >> 7) & 0x1F)

typedef struct EnHiddenNuts {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[10];
    /* 0x01C4 */ Vec3s morphTable[10];
    /* 0x0200 */ EnHiddenNutsActionFunc actionFunc;
    /* 0x0204 */ Path* path;
    /* 0x0208 */ s16 unk_208;
    /* 0x020A */ u8 unk_20A;
    /* 0x020C */ Vec3f unk_20C;
    /* 0x0218 */ s16 unk_218;
    /* 0x021A */ s16 unk_21A;
    /* 0x021C */ s16 switchFlag;
    /* 0x021E */ s16 unk_21E;
    /* 0x0220 */ s32 unk_220;
    /* 0x0224 */ s16 unk_224;
    /* 0x0226 */ s16 unk_226;
    /* 0x0228 */ f32 unk_228;
    /* 0x022C */ f32 unk_22C;
    /* 0x0230 */ UNK_TYPE1 unk230[4];
    /* 0x0234 */ ColliderCylinder collider;
} EnHiddenNuts; // size = 0x280

extern const ActorInit En_Hidden_Nuts_InitVars;

#endif // Z_EN_HIDDEN_NUTS_H
