#ifndef Z_EN_SYATEKI_MAN_H
#define Z_EN_SYATEKI_MAN_H

#include "global.h"

struct EnSyatekiMan;

typedef void (*EnSyatekiManActionFunc)(struct EnSyatekiMan*, GlobalContext*);

#define ENSYATEKIMAN_GET_FF00(thisx) (((thisx)->params & 0xFF00) >> 8)

typedef struct {
    /* 0x00 */ s16 index;
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 y;
    /* 0x0C */ f32 z;
    /* 0x10 */ s32 variable;
} EnSyatekiManUnkStruct;

typedef struct EnSyatekiMan {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ EnSyatekiManActionFunc actionFunc;
    /* 0x018C */ Path* path;
    /* 0x0190 */ s32 unk_190;
    /* 0x0194 */ s32 unk_194;
    /* 0x0198 */ Vec3s jointTable[16];
    /* 0x01F8 */ Vec3s morphTable[16];
    /* 0x0258 */ Vec3s unk_258;
    /* 0x025E */ Vec3s unk_25E;
    /* 0x0264 */ s16 unk_264;
    /* 0x0266 */ s16 unk_266;
    /* 0x0268 */ UNK_TYPE1 unk268[0x2];
    /* 0x026A */ s16 unk_26A;
    /* 0x026C */ s16 unk_26C;
    /* 0x026E */ s16 unk_26E;
    /* 0x0270 */ s16 unk_270;
    /* 0x0272 */ s16 unk_272;
    /* 0x0274 */ s16 unk_274;
    /* 0x0276 */ s16 unk_276;
    /* 0x0278 */ s16 unk_278;
    /* 0x027A */ s16 unk_27A;
    /* 0x027C */ s16 unk_27C;
    /* 0x027E */ s16 unk_27E;
    /* 0x0280 */ s16 unk_280;
    /* 0x0282 */ s16 unk_282;
    /* 0x0284 */ s16 unk_284;
} EnSyatekiMan; // size = 0x288

extern const ActorInit En_Syateki_Man_InitVars;

#endif // Z_EN_SYATEKI_MAN_H
