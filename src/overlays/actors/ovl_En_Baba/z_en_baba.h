#ifndef Z_EN_BABA_H
#define Z_EN_BABA_H

#include "global.h"

struct EnBaba;

typedef void (*EnBabaActionFunc)(struct EnBaba*, PlayState*);

#define ENBABA_GET_3F00(thisx) (((thisx)->params & 0x3F00) >> 8)
#define ENBABA_GET_C000(thisx) (((thisx)->params & 0xC000) >> 0xE)

#define ENBABA_3F00_3F 0x3F

enum {
    /* 0 */ ENBABA_C000_0,
    /* 1 */ ENBABA_C000_1,
    /* 2 */ ENBABA_C000_2,
};

typedef struct EnBaba {
    /* 0x000 */ Actor actor;
    /* 0x144 */ struct EnOssan* unk_144;
    /* 0x148 */ EnBabaActionFunc actionFunc;
    /* 0x14C */ UNK_TYPE1 unk14C[4];
    /* 0x150 */ SkelAnime skelAnime;
    /* 0x194 */ ColliderCylinder collider;
    /* 0x1E0 */ u16 unk_1E0;
    /* 0x1E2 */ u8 unk_1E2;
    /* 0x1E4 */ Path* path;
    /* 0x1E8 */ s16 unk_1E8;
    /* 0x1EA */ UNK_TYPE1 unk1EA[0x1C];
    /* 0x206 */ Vec3s jointTable[18];
    /* 0x272 */ Vec3s morphTable[18];
    /* 0x2DE */ Vec3s trackTarget;
    /* 0x2E4 */ Vec3s headRot;
    /* 0x2EA */ Vec3s torsoRot;
    /* 0x2F0 */ UNK_TYPE1 unk2F0[0x12];
    /* 0x302 */ s16 unk_302[18];
    /* 0x326 */ s16 unk_326[18];
    /* 0x34A */ UNK_TYPE1 unk34A[0xBA];
    /* 0x404 */ s16 unk_404;
    /* 0x406 */ UNK_TYPE1 unk406[4];
    /* 0x40A */ u16 unk_40A;
    /* 0x40C */ s32 unk_40C;
    /* 0x410 */ Path* timePath;
    /* 0x414 */ Vec3f timePathTargetPos;
    /* 0x420 */ f32 timePathProgress;
    /* 0x424 */ s32 timePathTotalTime;
    /* 0x428 */ s32 timePathWaypointTime;
    /* 0x42C */ s32 timePathWaypoint;
    /* 0x430 */ s32 timePathElapsedTime;
    /* 0x434 */ u8 unk_434;
    /* 0x436 */ s16 timePathTimeSpeed;
    /* 0x438 */ s32 unk_438;
    /* 0x43C */ s32 unk_43C;
} EnBaba; // size = 0x440

extern const ActorInit En_Baba_InitVars;

#endif // Z_EN_BABA_H
