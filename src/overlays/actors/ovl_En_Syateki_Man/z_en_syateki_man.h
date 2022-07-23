#ifndef Z_EN_SYATEKI_MAN_H
#define Z_EN_SYATEKI_MAN_H

#include "global.h"
#include "objects/object_shn/object_shn.h"


struct EnSyatekiMan;

typedef void (*EnSyatekiManActionFunc)(struct EnSyatekiMan*, PlayState*);

#define ENSYATEKIMAN_GET_FF00(thisx) (((thisx)->params & 0xFF00) >> 8)

typedef struct {
    /* 0x00 */ s16 index;
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 y;
    /* 0x0C */ f32 z;
    /* 0x10 */ s32 variable;
} EnSyatekiManUnkStruct; // size = 0x14

typedef struct EnSyatekiMan {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnSyatekiManActionFunc actionFunc;
    /* 0x18C */ Path* path;
    /* 0x190 */ s32 unk_190;
    /* 0x194 */ s32 unk_194;
    /* 0x198 */ Vec3s jointTable[BURLY_GUY_LIMB_MAX];
    /* 0x1F8 */ Vec3s morphTable[BURLY_GUY_LIMB_MAX];
    /* 0x258 */ Vec3s unk_258;
    /* 0x25E */ Vec3s unk_25E;
    /* 0x264 */ s16 eyeIndex;
    /* 0x266 */ s16 blinkTimer;
    /* 0x268 */ UNK_TYPE1 unk268[0x2];
    /* 0x26A */ s16 unk_26A;
    /* 0x26C */ s16 unk_26C;
    /* 0x26E */ s16 unk_26E;
    /* 0x270 */ s16 unk_270;
    /* 0x272 */ s16 unk_272;
    /* 0x274 */ s16 unk_274;
    /* 0x276 */ s16 unk_276;
    /* 0x278 */ s16 unk_278;
    /* 0x27A */ s16 unk_27A;
    /* 0x27C */ s16 unk_27C;
    /* 0x27E */ s16 unk_27E;
    /* 0x280 */ s16 unk_280;
    /* 0x282 */ s16 unk_282;
    /* 0x284 */ s16 unk_284;
} EnSyatekiMan; // size = 0x288

extern const ActorInit En_Syateki_Man_InitVars;

#endif // Z_EN_SYATEKI_MAN_H
