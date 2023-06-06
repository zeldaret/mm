#ifndef Z_EN_INVADEPOH_H
#define Z_EN_INVADEPOH_H

#include "global.h"
#include "assets/objects/object_uch/object_uch.h"
#include "assets/objects/object_ma1/object_ma1.h"
#include "assets/objects/object_ma2/object_ma2.h"
#include "assets/objects/object_cow/object_cow.h"
#include "assets/objects/object_dog/object_dog.h"

struct EnInvadepoh;

typedef void (*EnInvadepohActionFunc)(struct EnInvadepoh* this, PlayState* play);
typedef void (*EnInvadepohMainFunc)(Actor* thisx, PlayState* play); // PlayState, not GameState

typedef struct {
    /* 0x0 */ f32 unk0;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 unk6;
} EnInvadepohUnkStruct1; // size = 0x8

typedef struct {
    /* 0x0 */ s8 type;
    /* 0x1 */ s8 timer;
    /* 0x2 */ u8 alpha;
    /* 0x4 */ Vec3f pos;
} EnInvadepohWarpEffect; // size = 0x10

typedef struct {
    /* 0x0 */ s8* texIndex;
    /* 0x1 */ s8 count;
} EnInvadepohFaceFrames; // size = 0x2

typedef struct {
    /* 0x0 */ s8 index;
    /* 0x4 */ f32 chance;
} EnInvadepohFaceAnimNext; // size = 0x8

#if 1
typedef struct {
    /* 0x0 */ s8 type;
    /* 0x4 */ EnInvadepohFaceFrames* frames;
} EnInvadepohFaceAnim; // size = 0x8

typedef struct {
    /* 0x0 */ EnInvadepohFaceAnim anim;
    /* 0x8 */ s8 nextCount;
    /* 0xC */ EnInvadepohFaceAnimNext* nextAnims;
} EnInvadepohFaceAnimBranched; // size = 0x10

typedef struct {
    /* 0x00 */ EnInvadepohFaceAnimBranched loop;
    /* 0x10 */ s16 minDelay;
    /* 0x12 */ s16 maxDelay;
} EnInvadepohFaceAnimDelayedBranched; // size = 0x14

#else

typedef struct {
    /* 0x0 */ s8 type;
    /* 0x4 */ EnInvadepohFaceFrames* frames;
} EnInvadepohFaceAnimOnce; // size = 0x8

typedef struct {
    /* 0x0 */ s8 type;
    /* 0x4 */ EnInvadepohFaceFrames* frames;
    /* 0x8 */ s8 nextCount;
    /* 0xC */ EnInvadepohFaceAnimNext* nextAnims;
} EnInvadepohFaceAnimBranched; // size = 0x10

typedef struct {
    /* 0x0 */ s8 type;
    /* 0x4 */ EnInvadepohFaceFrames* frames;
    /* 0x8 */ s8 nextCount;
    /* 0xC */ EnInvadepohFaceAnimNext* nextAnims;
    /* 0x10 */ s16 minDelay;
    /* 0x12 */ s16 maxDelay;
} EnInvadepohFaceAnimDelayedBranched; // size = 0x14

typedef union {
    EnInvadepohFaceAnimOnce once;
    EnInvadepohFaceAnimBranched branch;
    EnInvadepohFaceAnimDelayedBranched delay;
} EnInvadepohFaceAnim;

#endif

typedef struct {
    /* 0x0 */ EnInvadepohFaceAnim** animSet;
    /* 0x4 */ s8 curAnimType;
    /* 0x8 */ EnInvadepohFaceAnim* curAnim;
    /* 0xC */ s16 delayTimer;
    /* 0xE */ s8 curFrame;
    /* 0xF */ s8 curIndex;
} EnInvadePohFaceAnimInfo; // size = 0x10

typedef struct {
    /* 0x00 */ EnInvadePohFaceAnimInfo eyeAnim;
    /* 0x10 */ EnInvadePohFaceAnimInfo mouthAnim;
    /* 0x20 */ Vec3s headRot;
    /* 0x26 */ Vec3s headRotTarget;
    /* 0x2C */ s16 maxTurnRate;
    /* 0x30 */ f32 scaledTurnRate;
    /* 0x34 */ f32 torsoRotXMod;
    /* 0x38 */ f32 torsoRotXModTarget;
    /* 0x3c */ f32 torsoRotXModStep;
    /* 0x40 */ s16 torsoRotZ;
    /* 0x42 */ s16 torsoRotZTarget;
    /* 0x44 */ f32 torsoMaxTurnRate;
    /* 0x48 */ s16 torsoMaxTurnStep;
} EnInvadePohInteractInfo; // size = 0x4C

typedef void (*EnInvadepohFaceFunc) (EnInvadePohFaceAnimInfo*, EnInvadepohFaceAnim**);

#define EN_INVADEPOH_LIMB_MAX 23
// #define EN_INVADEPOH_LIMB_MAX MAX(MAX(MAX(MAX(MAX(ALIEN_LIMB_MAX, ROMANI_LIMB_MAX), CREMIA_LIMB_MAX), DOG_LIMB_MAX), COW_LIMB_MAX), COW_TAIL_LIMB_MAX)

typedef struct EnInvadepoh {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[EN_INVADEPOH_LIMB_MAX];
    /* 0x212 */ Vec3s morphTable[EN_INVADEPOH_LIMB_MAX];
    /* 0x29C */ s8 finishedAnim;
    /* 0x2A0 */ ColliderCylinder collider;
    /* 0x2EC */ EnInvadepohActionFunc actionFunc;
    /* 0x2F0 */ s16 actionTimer;
    /* 0x2F2 */ s16 stateTimer;
    /* 0x2F4 */ s8 bankIndex;
    /* 0x2F8 */ f32 unk_2F8;
    /* 0x2FC */ char unk_2FC[4]; // unused? f32?
    /* 0x300 */ f32 unk_300;
    /* 0x304 */ s16 unk_304;
    /* 0x306 */ s16 unk_306;
    /* 0x308 */ s8 endPoint;
    /* 0x309 */ s8 currentPoint;
    /* 0x30A */ s8 pathStep;
    /* 0x30C */ Vec3s *pathPoints;
    /* 0x310 */ f32 pathLength;
    /* 0x314 */ Vec3f unk_314;
    /* 0x320 */ f32 progress;
    /* 0x324 */ EnInvadePohInteractInfo interactInfo;
    /* 0x370 */ s16 unk_370;
    /* 0x372 */ s16 unk_372;
    /* 0x374 */ s8 unk_374;
    /* 0x376 */ u16 textId;
    /* 0x378 */ s8 unk_378;
    /* 0x379 */ s8 spawnCount;
    /* 0x37C */ f32 checkpoints[3];
    /* 0x388 */ char unk_388; // unused?
    /* 0x389 */ u8 alpha;
    /* 0x38A */ s8 atBarn;
    /* 0x38B */ s8 present;
    /* 0x38C */ s8 drawDeathFlash;
    /* 0x38D */ u8 eyeBeamAlpha;
    /* 0x390 */ Vec3f deathFlashScale;
    /* 0x39C */ f32 pulseScale;
    /* 0x3A0 */ f32 pulseScaleTarget;
    /* 0x3A4 */ f32 pulseScaleRate;
    /* 0x3A8 */ s16 pulsePhase;
    /* 0x3AA */ s16 pulseRate;
    /* 0x3AC */ s8 lightBallTarget;
    /* 0x3AD */ char pad3AD[3];
    /* 0x3B0 */ char pad3B0[0xC]; // unused? Vec3f?
    /* 0x3BC */ s8 dogTargetPoint;
} EnInvadepoh; // size = 0x3C0

typedef enum {
    /* 0x0 */ ENINVADEPOH_HANDLER,         // Invasion event handler   
    /* 0x1 */ ENINVADEPOH_ALIEN_INVADER,   // Alien invader
    /* 0x2 */ ENINVADEPOH_COW,             // Abudcted cow, spawned by unused alien abductor   
    /* 0x3 */ ENINVADEPOH_COW_TAIL,        // Abducted cow tail, spawned by abducted cow   
    /* 0x4 */ ENINVADEPOH_ROMANI_ABDUCTED, // Abducted Romani, spawned by unused alien abductor       
    /* 0x5 */ ENINVADEPOH_ROMANI_CONFUSED, // Returned, confused Romani   
    /* 0x6 */ ENINVADEPOH_LIGHT_BALL,      // Light ball spaceship   
    /* 0x7 */ ENINVADEPOH_ROMANI_NIGHT_1,  // Romani running to barn on night 1
    /* 0x8 */ ENINVADEPOH_ROMANI_BARN,     // Romani in the barn on night 1
    /* 0x9 */ ENINVADEPOH_ROMANI_REWARD,   // Romani rewarding you for defeating invasion
    /* 0xA */ ENINVADEPOH_DOG,             // Dog during alien invasion   
    /* 0xB */ ENINVADEPOH_CREMIA_NIGHT_3,  // Cremia walking from barn to house on night 3
    /* 0xC */ ENINVADEPOH_ROMANI_NIGHT_3,  // Romnani walking from barn to house on night 3
    /* 0xD */ ENINVADEPOH_ALIEN_ABDUCTOR,  // Alien abductor, unused, carries cow or Romani
} EnInvadepohParamsTypes;

#define ENINVADEPOH_GET_INDEX(thisx) ((thisx)->params & 7)
#define ENINVADEPOH_GET_TYPE(thisx) ((thisx)->params >> 4 & 0xF)
#define ENINVADEPOH_GET_PATH(thisx) ((thisx)->params >> 8 & 0x7F)

#define ENINVADEPOH_SET_PARAMS(path, type, index) (((index) & 7) | (((path) << 8) & 0x7F00) | (((type) << 4) & 0xF0))

#endif // Z_EN_INVADEPOH_H
