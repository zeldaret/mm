#ifndef Z_EN_RAT_H
#define Z_EN_RAT_H

#include "global.h"
#include "objects/object_rat/object_rat.h"

#define EN_RAT_GET_8000(thisx) ((thisx)->params & 0x8000)
#define EN_RAT_GET_ATTACK_RANGE(thisx) ((thisx)->params & 0xFF)

struct EnRat;

typedef void (*EnRatActionFunc)(struct EnRat*, PlayState*);

typedef struct EnRat {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnRatActionFunc actionFunc;
    /* 0x18C */ u8 hasLostTrackOfPlayer;
    /* 0x18D */ u8 unk_18D;
    /* 0x18E */ s16 animationLoopCounter;
    /* 0x190 */ s16 timer; // Used for both exploding and reviving
    /* 0x192 */ s16 stunTimer; // Set to -2 and -1 when hit with the Hookshot
    /* 0x194 */ Vec3s jointTable[REAL_BOMBCHU_LIMB_MAX];
    /* 0x1D0 */ Vec3s morphTable[REAL_BOMBCHU_LIMB_MAX];
    /* 0x20C */ Vec3f axisForwards;
    /* 0x218 */ Vec3f axisUp;
    /* 0x224 */ Vec3f axisLeft;
    /* 0x230 */ Vec3f smokePos;
    /* 0x23C */ Vec3f sparkOffsets[2];
    /* 0x254 */ f32 visualJitter;
    /* 0x258 */ f32 attackRange;
    /* 0x25C */ f32 revivePosY;
    /* 0x260 */ s32 blure1Index;
    /* 0x264 */ s32 blure2Index;
    /* 0x268 */ ColliderSphere collider;
} EnRat; // size = 0x2C0

extern const ActorInit En_Rat_InitVars;

#endif // Z_EN_RAT_H
