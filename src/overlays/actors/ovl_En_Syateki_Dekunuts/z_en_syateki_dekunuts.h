#ifndef Z_EN_SYATEKI_DEKUNUTS_H
#define Z_EN_SYATEKI_DEKUNUTS_H

#include "global.h"

#define EN_SYATEKI_DEKUNUTS_GET_PARAM_F(thisx) ((thisx)->params & 0xF)
#define EN_SYATEKI_DEKUNUTS_GET_PARAM_F0(thisx) (((thisx)->params & 0xF0) >> 4)
#define EN_SYATEKI_DEKUNUTS_GET_PARAM_FF00(thisx) (((thisx)->params & 0xFF00) >> 8)

struct EnSyatekiDekunuts;

typedef void (*EnSyatekiDekunutsActionFunc)(struct EnSyatekiDekunuts*, GlobalContext*);

typedef struct EnSyatekiDekunuts {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnSyatekiDekunutsActionFunc actionFunc;
    /* 0x18C */ ColliderCylinder collider;
    /* 0x1D8 */ s16 unk_1D8;
    /* 0x1DA */ s16 unk_1DA;
    /* 0x1CD */ s16 unk_1DC;
    /* 0x1DE */ UNK_TYPE1 unk_1DE[0x4];
    /* 0x1E2 */ s16 unk_1E2;
    /* 0x1E4 */ Vec3s* unk_1E4;
    /* 0x1E8 */ s16 unk_1E8;
    /* 0x1EA */ s16 unk_1EA;
    /* 0x1EC */ s16 unk_1EC;
    /* 0x1EE */ s16 unk_1EE;
    /* 0x1F0 */ s16 unk_1F0;
    /* 0x1F2 */ s16 unk_1F2;
    /* 0x1F4 */ Vec3s jointTable[10];
    /* 0x230 */ Vec3s morphTable[10];
    /* 0x26C */ UNK_TYPE1 unk_26C[0x4];
} EnSyatekiDekunuts; // size = 0x270

extern const ActorInit En_Syateki_Dekunuts_InitVars;

#endif // Z_EN_SYATEKI_DEKUNUTS_H
