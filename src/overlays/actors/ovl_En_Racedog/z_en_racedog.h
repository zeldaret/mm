#ifndef Z_EN_RACEDOG_H
#define Z_EN_RACEDOG_H

#include "global.h"
#include "objects/object_dog/object_dog.h"

#define ENRACEDOG_GET_INDEX(thisx) (((thisx)->params & 0x3E0) >> 5)
#define ENRACEDOG_GET_PATH(thisx) (((thisx)->params & 0xFC00) >> 10)

struct EnRacedog;

typedef void (*EnRacedogActionFunc)(struct EnRacedog*, GlobalContext*);

typedef struct EnRacedog {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnRacedogActionFunc actionFunc;
    /* 0x148 */ UNK_TYPE1 unk_148[0x4];
    /* 0x14C */ SkelAnime skelAnime;
    /* 0x190 */ ColliderCylinder collider;
    /* 0x1DC */ UNK_TYPE1 unk_1DC[0x4];
    /* 0x1E0 */ Path* path;
    /* 0x1E4 */ UNK_TYPE1 unk_1E4[0x4];
    /* 0x1E8 */ s32 currentPoint;
    /* 0x1EC */ Vec3s jointTable[DOG_LIMB_MAX];
    /* 0x23A */ Vec3s morphTable[DOG_LIMB_MAX];
    /* 0x288 */ s16 selectionArrowTimer;
    /* 0x28A */ s16 raceStartTimer;
    /* 0x28C */ s16 extraTimeBeforeRaceStart;
    /* 0x28A */ UNK_TYPE1 unk_28E[0x2];
    /* 0x290 */ s16 index;
    /* 0x292 */ s16 selectedDogIndex;
    /* 0x294 */ UNK_TYPE1 unk_294[0x4];
    /* 0x298 */ f32 targetSpeed;
    /* 0x29C */ s16 raceStatus;
    /* 0x2A0 */ Vec3f unk_2A0;
    /* 0x2AC */ Vec3f unk_2AC;
    /* 0x2B8 */ s32 pointForCurrentTargetSpeed;
    /* 0x2BC */ s32 selectionArrowGreenPrimColor;
    /* 0x2C0 */ s32 selectionArrowGreenEnvColor;
    /* 0x2C4 */ f32 selectionArrowScale;
} EnRacedog; // size = 0x2C8

extern const ActorInit En_Racedog_InitVars;

#endif // Z_EN_RACEDOG_H
