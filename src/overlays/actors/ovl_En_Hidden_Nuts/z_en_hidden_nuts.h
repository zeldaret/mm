#ifndef Z_EN_HIDDEN_NUTS_H
#define Z_EN_HIDDEN_NUTS_H

#include "global.h"

struct EnHiddenNuts;

typedef void (*EnHiddenNutsActionFunc)(struct EnHiddenNuts*, PlayState*);

#define ENHIDDENNUTS_GET_SWITCHFLAG(thisx) ((thisx)->params & 0x7F)
#define ENHIDDENNUTS_GET_F80(thisx) (((thisx)->params >> 7) & 0x1F)

typedef struct EnHiddenNuts {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[10];
    /* 0x1C4 */ Vec3s morphTable[10];
    /* 0x200 */ EnHiddenNutsActionFunc actionFunc;
    /* 0x204 */ Path* path;
    /* 0x208 */ s16 unk_208;
    /* 0x20A */ u8 unk_20A;
    /* 0x20C */ Vec3f unk_20C;
    /* 0x218 */ s16 unk_218;
    /* 0x21A */ s16 unk_21A;
    /* 0x21C */ s16 switchFlag;
    /* 0x21E */ s16 unk_21E;
    /* 0x220 */ s32 unk_220;
    /* 0x224 */ s16 unk_224;
    /* 0x226 */ s16 unk_226;
    /* 0x228 */ f32 unk_228;
    /* 0x22C */ f32 unk_22C;
    /* 0x230 */ UNK_TYPE1 unk230[4];
    /* 0x234 */ ColliderCylinder collider;
} EnHiddenNuts; // size = 0x280

extern const ActorInit En_Hidden_Nuts_InitVars;

#endif // Z_EN_HIDDEN_NUTS_H
