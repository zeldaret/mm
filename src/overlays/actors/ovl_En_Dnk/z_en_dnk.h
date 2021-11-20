#ifndef Z_EN_DNK_H
#define Z_EN_DNK_H

#include "global.h"

struct EnDnk;

typedef void (*EnDnkActionFunc)(struct EnDnk*, GlobalContext*);

#define ENDNK_GET_3(thisx) ((thisx)->params & 0x3)
#define ENDNK_GET_3C(thisx) ((thisx)->params & 0x3C)

enum {
    /* 0x0 */ ENDNK_GET_3_0,
    /* 0x1 */ ENDNK_GET_3_1,
    /* 0x2 */ ENDNK_GET_3_2,
    /* 0x3 */ ENDNK_GET_3_3,
    /* 0x4 */ ENDNK_GET_3_4,
};

typedef struct EnDnk {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnDnkActionFunc actionFunc;
    /* 0x18C */ UNK_TYPE1 unk_18C[0x4];
    /* 0x190 */ ColliderCylinder collider;
    /* 0x1DC */ Vec3s jointTable[11];
    /* 0x21E */ Vec3s morphTable[11];
    /* 0x260 */ Gfx* unk_260[11];
    /* 0x28C */ u16 unk_28C;
    /* 0x28E */ s8 unk_28E;
    /* 0x290 */ s16 unk_290;
    /* 0x292 */ s16 unk_292;
    /* 0x294 */ s16 unk_294;
    /* 0x296 */ s16 unk_296;
    /* 0x298 */ s16 unk_298;
    /* 0x29A */ UNK_TYPE1 unk_29A[0x4];
    /* 0x29E */ s16 unk_29E;
    /* 0x2A0 */ s16 unk_2A0;
    /* 0x2A2 */ s16 unk_2A2;
} EnDnk; // size = 0x2A4

extern const ActorInit En_Dnk_InitVars;

#endif // Z_EN_DNK_H
