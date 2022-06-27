#ifndef Z_EN_SYATEKI_MAN_H
#define Z_EN_SYATEKI_MAN_H

#include "global.h"
#include "objects/object_shn/object_shn.h"

struct EnSyatekiMan;

typedef void (*EnSyatekiManActionFunc)(struct EnSyatekiMan*, PlayState*);

#define EN_SYATEKI_MAN_GET_PATH(thisx) (((thisx)->params & 0xFF00) >> 8)

typedef struct EnSyatekiMan {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ EnSyatekiManActionFunc actionFunc;
    /* 0x018C */ Path* path;
    /* 0x0190 */ s32 unk_190;
    /* 0x0194 */ s32 swampTargetActorListIndex;
    /* 0x0198 */ Vec3s jointTable[BURLY_GUY_LIMB_MAX];
    /* 0x01F8 */ Vec3s morphTable[BURLY_GUY_LIMB_MAX];
    /* 0x0258 */ Vec3s headRot;
    /* 0x025E */ Vec3s torsoRot;
    /* 0x0264 */ s16 eyeIndex;
    /* 0x0266 */ s16 blinkTimer;
    /* 0x0268 */ UNK_TYPE1 unk268[0x2];
    /* 0x026A */ s16 unk_26A;
    /* 0x026C */ s16 unk_26C;
    /* 0x026E */ s16 unk_26E;
    /* 0x0270 */ s16 unk_270;
    /* 0x0272 */ s16 unk_272;
    /* 0x0274 */ s16 unk_274;
    /* 0x0276 */ s16 unk_276;
    /* 0x0278 */ s16 dekuScrubHitCounter;
    /* 0x027A */ s16 guayHitCounter;
    /* 0x027C */ s16 unk_27C;
    /* 0x027E */ s16 unk_27E;
    /* 0x0280 */ s16 score;
    /* 0x0282 */ s16 unk_282;
    /* 0x0284 */ s16 textId;
} EnSyatekiMan; // size = 0x288

extern const ActorInit En_Syateki_Man_InitVars;

#endif // Z_EN_SYATEKI_MAN_H
