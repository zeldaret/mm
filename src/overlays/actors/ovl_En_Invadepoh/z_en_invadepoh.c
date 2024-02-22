#include "z_en_invadepoh.h"

#include "prevent_bss_reordering.h"
#include "sys_cfb.h"
#include "z64horse.h"
#include "overlays/actors/ovl_En_Clear_Tag/z_en_clear_tag.h"
#include "overlays/actors/ovl_En_Door/z_en_door.h"

#include "assets/objects/gameplay_keep/gameplay_keep.h"

#define FLAGS 0x00000010

#define THIS ((EnInvadepoh*)thisx)

#define EN_INVADEPOH_ALIEN_ACTIVE (1 << 0)
#define EN_INVADEPOH_ALIEN_CLOSEST (1 << 1)

#define BARN_X_POSITION -409
#define BARN_Y_POSITION 265
#define BARN_Z_POSITION -1829

#define SPAWN_X_POSITION -193
#define SPAWN_Y_POSITION 235
#define SPAWN_Z_POSITION -434

typedef enum EnInvadepohEventState {
    /* 0 */ EN_INVADEPOH_EVENT_UNSET,
    /* 1 */ EN_INVADEPOH_EVENT_WAIT,
    /* 2 */ EN_INVADEPOH_EVENT_ACTIVE,
    /* 3 */ EN_INVADEPOH_EVENT_CLEAR,
    /* 4 */ EN_INVADEPOH_EVENT_FAILED
} EnInvadepohEventState;

typedef enum EnInvadepohFaceAnimationType {
    /* 0 */ EN_INVADEPOH_FACE_ANIMATION_TYPE_FIXED,
    /* 1 */ EN_INVADEPOH_FACE_ANIMATION_TYPE_BRANCHED,
    /* 2 */ EN_INVADEPOH_FACE_ANIMATION_TYPE_DELAYED_BRANCHED
} EnInvadepohFaceAnimationType;

void EnInvadepoh_Init(Actor* thisx, PlayState* play2);
void EnInvadepoh_Destroy(Actor* thisx, PlayState* play2);
void EnInvadepoh_InvasionHandler_Update(Actor* thisx, PlayState* play2);

// Update functions
void EnInvadepoh_Alien_WaitForObject(Actor* thisx, PlayState* play2);
void EnInvadepoh_Alien_Update(Actor* thisx, PlayState* play2);
void EnInvadepoh_Cow_WaitForObject(Actor* thisx, PlayState* play2);
void EnInvadepoh_Cow_Update(Actor* thisx, PlayState* play2);
void EnInvadepoh_CowTail_WaitForObject(Actor* thisx, PlayState* play2);
void EnInvadepoh_CowTail_Update(Actor* thisx, PlayState* play2);
void EnInvadepoh_AbductedRomani_Update(Actor* thisx, PlayState* play2);
void EnInvadepoh_AbductedRomani_WaitForObject(Actor* thisx, PlayState* play2);
void EnInvadepoh_SilentRomani_WaitForObject(Actor* thisx, PlayState* play2);
void EnInvadepoh_SilentRomani_Update(Actor* thisx, PlayState* play2);
void EnInvadepoh_Ufo_Update(Actor* thisx, PlayState* play2);
void EnInvadepoh_Night1Romani_WaitForObject(Actor* thisx, PlayState* play2);
void EnInvadepoh_Night1Romani_WaitForEvent(Actor* thisx, PlayState* play2);
void EnInvadepoh_Night1Romani_Update(Actor* thisx, PlayState* play2);
void EnInvadepoh_BarnRomani_WaitForObject(Actor* thisx, PlayState* play2);
void EnInvadepoh_BarnRomani_WaitForEvent(Actor* thisx, PlayState* play2);
void EnInvadepoh_BarnRomani_Update(Actor* thisx, PlayState* play2);
void EnInvadepoh_RewardRomani_WaitForObject(Actor* thisx, PlayState* play2);
void EnInvadepoh_RewardRomani_Update(Actor* thisx, PlayState* play2);
void EnInvadepoh_Dog_WaitForObject(Actor* thisx, PlayState* play2);
void EnInvadepoh_Dog_WaitForEvent(Actor* thisx, PlayState* play2);
void EnInvadepoh_Dog_Update(Actor* thisx, PlayState* play2);
void EnInvadepoh_Night3Cremia_WaitForObject(Actor* thisx, PlayState* play2);
void EnInvadepoh_Night3Cremia_WaitForEvent(Actor* thisx, PlayState* play2);
void EnInvadepoh_Night3Cremia_Update(Actor* thisx, PlayState* play2);
void EnInvadepoh_Night3Romani_WaitForObject(Actor* thisx, PlayState* play2);
void EnInvadepoh_Night3Romani_WaitForEvent(Actor* thisx, PlayState* play2);
void EnInvadepoh_Night3Romani_Update(Actor* thisx, PlayState* play2);
void EnInvadepoh_AlienAbductor_WaitForObject(Actor* thisx, PlayState* play2);

// Draw functions
void EnInvadepoh_AlienAbductor_Update(Actor* thisx, PlayState* play2);
void EnInvadepoh_InvasionHandler_Draw(Actor* thisx, PlayState* play);
void EnInvadepoh_Alien_Draw(Actor* thisx, PlayState* play2);
void EnInvadepoh_Cow_Draw(Actor* thisx, PlayState* play2);
void EnInvadepoh_CowTail_Draw(Actor* thisx, PlayState* play2);
void EnInvadepoh_Romani_Draw(Actor* thisx, PlayState* play);
void EnInvadepoh_Ufo_Draw(Actor* thisx, PlayState* play2);
void EnInvadepoh_Dog_Draw(Actor* thisx, PlayState* play);
void EnInvadepoh_Cremia_Draw(Actor* thisx, PlayState* play);

// Action functions
void EnInvadepoh_InvasionHandler_SetupWait(EnInvadepoh* this);
void EnInvadepoh_InvasionHandler_Wait(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_InvasionHandler_SetupQueueInvasionCs(EnInvadepoh* this);
void EnInvadepoh_InvasionHandler_QueueInvasionCs(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_InvasionHandler_SetupInvasionCs(EnInvadepoh* this);
void EnInvadepoh_InvasionHandler_InvasionCs(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_InvasionHandler_SetupInvasion(EnInvadepoh* this);
void EnInvadepoh_InvasionHandler_Invasion(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_InvasionHandler_SetupQueueVictoryCs(EnInvadepoh* this);
void EnInvadepoh_InvasionHandler_QueueVictoryCs(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_InvasionHandler_SetupVictoryCs(EnInvadepoh* this);
void EnInvadepoh_InvasionHandler_VictoryCs(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_InvasionHandler_SetupRomaniReward(EnInvadepoh* this);
void EnInvadepoh_InvasionHandler_RomaniReward(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_InvasionHandler_SetupGoodEnd(EnInvadepoh* this);
void EnInvadepoh_InvasionHandler_GoodEnd(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_InvasionHandler_SetupFailure(EnInvadepoh* this);
void EnInvadepoh_InvasionHandler_Failure(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_InvasionHandler_SetupBadEnd(EnInvadepoh* this);
void EnInvadepoh_InvasionHandler_BadEnd(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Alien_WaitForEvent(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Invade_WaitToRespawn(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Alien_SetupWarpIn(EnInvadepoh* this);
void EnInvadepoh_Alien_WarpIn(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Alien_SetupAttack(EnInvadepoh* this);
void EnInvadepoh_Alien_Attack(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Alien_Hitstun(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Alien_SetupDeath(EnInvadepoh* this);
void EnInvadepoh_Alien_Death(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_AbductedRomani_Wait(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_AbductedRomani_SetupYell(EnInvadepoh* this);
void EnInvadepoh_AbductedRomani_Yell(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_AbductedRomani_SetupStruggle(EnInvadepoh* this);
void EnInvadepoh_AbductedRomani_Struggle(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_AbductedRomani_SetupEnd(EnInvadepoh* this);
void EnInvadepoh_AbductedRomani_End(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_SilentRomani_Walk(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_SilentRomani_SetupIdle(EnInvadepoh* this);
void EnInvadepoh_SilentRomani_Idle(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_SilentRomani_Talk(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Ufo_SetupDescend(EnInvadepoh* this);
void EnInvadepoh_Ufo_Descend(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Ufo_SetupHover(EnInvadepoh* this);
void EnInvadepoh_Ufo_Hover(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Ufo_SetupSpawnAliens(EnInvadepoh* this);
void EnInvadepoh_Ufo_SpawnAliens(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Ufo_SetupAboveBarn(EnInvadepoh* this);
void EnInvadepoh_Ufo_AboveBarn(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Ufo_Circle(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Ufo_SetupFlee(EnInvadepoh* this);
void EnInvadepoh_Ufo_Flee(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Ufo_SetupLeaveBarn(EnInvadepoh* this);
void EnInvadepoh_Ufo_LeaveBarn(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Night1Romani_Walk(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Night1Romani_Talk(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_BarnRomani_Idle(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_BarnRomani_SetupLookAround(EnInvadepoh* this);
void EnInvadepoh_BarnRomani_LookAround(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_BarnRomani_Walk(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_BarnRomani_Talk(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_RewardRomani_ClearCheck(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_RewardRomani_SetupStartCs(EnInvadepoh* this);
void EnInvadepoh_RewardRomani_StartCs(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_RewardRomani_SetupTalk(EnInvadepoh* this);
void EnInvadepoh_RewardRomani_Talk(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_RewardRomani_SetupGiveBottle(EnInvadepoh* this);
void EnInvadepoh_RewardRomani_GiveBottle(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_RewardRomani_SetupAfterGiveBottle(EnInvadepoh* this);
void EnInvadepoh_RewardRomani_AfterGiveBottle(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_RewardRomani_SetupFinished(EnInvadepoh* this);
void EnInvadepoh_RewardRomani_Finished(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Dog_Walk(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Dog_SetupRun(EnInvadepoh* this);
void EnInvadepoh_Dog_Run(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Dog_SetupBark(EnInvadepoh* this);
void EnInvadepoh_Dog_Bark(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Dog_Jump(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Night3Cremia_Walk(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Night3Cremia_Talk(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Night3Cremia_SetupIdle(EnInvadepoh* this);
void EnInvadepoh_Night3Cremia_Idle(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Night3Romani_Walk(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Night3Romani_Talk(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Night3Romani_SetupIdle(EnInvadepoh* this);
void EnInvadepoh_Night3Romani_Idle(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_AlienAbductor_Cow(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_AlienAbductor_Romani(EnInvadepoh* this, PlayState* play);

s32 EnInvadepoh_SnapToFloor(EnInvadepoh* this);
s32 EnInvadepoh_StepTowardXZ(f32* pxValue, f32* pzValue, f32 xTarget, f32 zTarget, f32 speed);

ActorInit En_Invadepoh_InitVars = {
    ACTOR_EN_INVADEPOH,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnInvadepoh),
    (ActorFunc)EnInvadepoh_Init,
    (ActorFunc)EnInvadepoh_Destroy,
    (ActorFunc)EnInvadepoh_InvasionHandler_Update,
    (ActorFunc)NULL,
};

ColliderCylinderInit sAlienCylinderInit = {
    {
        COLTYPE_HIT3,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK4,
        { 0xF7CFFFFF, 0x00, 0x04 },
        { 0x00003820, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NONE,
        BUMP_ON,
        OCELEM_ON,
    },
    { 40, 95, 10, { 0, 0, 0 } },
};

ColliderCylinderInit sHumanCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 18, 46, 0, { 0, 0, 0 } },
};

ColliderCylinderInit sDogCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 13, 19, 0, { 0, 0, 0 } },
};

Vec3f sUfoSpawnOffset = { 216.0f, -20.0f, 1395.0f };

s32 sEventState = EN_INVADEPOH_EVENT_UNSET;

typedef enum RomaniEyeTexture {
    /* 0 */ ROMANI_EYE_OPEN,
    /* 1 */ ROMANI_EYE_HALF,
    /* 2 */ ROMANI_EYE_CLOSED,
    /* 3 */ ROMANI_EYE_HAPPY,
    /* 4 */ ROMANI_EYE_SAD,
    /* 5 */ ROMANI_EYE_MAX
} RomaniEyeTexture;

TexturePtr sRomaniEyeTextures[ROMANI_EYE_MAX] = {
    gRomaniEyeOpenTex,   // ROMANI_EYE_OPEN
    gRomaniEyeHalfTex,   // ROMANI_EYE_HALF
    gRomaniEyeClosedTex, // ROMANI_EYE_CLOSED
    gRomaniEyeHappyTex,  // ROMANI_EYE_HAPPY
    gRomaniEyeSadTex,    // ROMANI_EYE_SAD
};

typedef enum RomaniMouthTexture {
    /* 0 */ ROMANI_MOUTH_HAPPY,
    /* 1 */ ROMANI_MOUTH_FROWN,
    /* 2 */ ROMANI_MOUTH_HANGING_OPEN,
    /* 3 */ ROMANI_MOUTH_SMILE,
    /* 4 */ ROMANI_MOUTH_MAX
} RomaniMouthTexture;

TexturePtr sRomaniMouthTextures[ROMANI_MOUTH_MAX] = {
    gRomaniMouthHappyTex,       // ROMANI_MOUTH_HAPPY
    gRomaniMouthFrownTex,       // ROMANI_MOUTH_FROWN
    gRomaniMouthHangingOpenTex, // ROMANI_MOUTH_HANGING_OPEN
    gRomaniMouthSmileTex,       // ROMANI_MOUTH_SMILE
};

s8 sRomaniTexturesDesegmented = false;

typedef enum CremiaEyeTexture {
    /* 0 */ CREMIA_EYE_OPEN,
    /* 1 */ CREMIA_EYE_HALF,
    /* 2 */ CREMIA_EYE_CLOSED,
    /* 3 */ CREMIA_EYE_HAPPY,
    /* 4 */ CREMIA_EYE_ANGRY,
    /* 5 */ CREMIA_EYE_SAD,
    /* 6 */ CREMIA_EYE_MAX
} CremiaEyeTexture;

TexturePtr sCremiaEyeTextures[CREMIA_EYE_MAX] = {
    gCremiaEyeOpenTex,   // CREMIA_EYE_OPEN
    gCremiaEyeHalfTex,   // CREMIA_EYE_HALF
    gCremiaEyeClosedTex, // CREMIA_EYE_CLOSED
    gCremiaEyeHappyTex,  // CREMIA_EYE_HAPPY
    gCremiaEyeAngryTex,  // CREMIA_EYE_ANGRY
    gCremiaEyeSadTex,    // CREMIA_EYE_SAD
};

typedef enum CremiaMouthTexture {
    /* 0 */ CREMIA_MOUTH_NORMAL,
    /* 1 */ CREMIA_MOUTH_SLIGHT_SMILE,
    /* 2 */ CREMIA_MOUTH_FROWN,
    /* 3 */ CREMIA_MOUTH_HANGING_OPEN,
    /* 4 */ CREMIA_MOUTH_MAX
} CremiaMouthTexture;

TexturePtr sCremiaMouthTextures[CREMIA_MOUTH_MAX] = {
    gCremiaMouthNormalTex,      // CREMIA_MOUTH_NORMAL
    gCremiaMouthSlightSmileTex, // CREMIA_MOUTH_SLIGHT_SMILE
    gCremiaMouthFrownTex,       // CREMIA_MOUTH_FROWN
    gCremiaMouthHangingOpenTex, // CREMIA_MOUTH_HANGING_OPEN
};

s8 sCremiaTexturesDesegmented = false;

s8 sRewardFinished = false;

MtxF sAlienLeftEyeBeamMtxF;
MtxF sAlienRightEyeBeamMtxF;
EnInvadepoh* sAliens[8];
u8 sAlienStateFlags[8];
s8 sAliensTooClose;

typedef struct EnInvadepohWarpEffect {
    /* 0x0 */ s8 type;
    /* 0x1 */ s8 timer;
    /* 0x2 */ u8 alpha;
    /* 0x4 */ Vec3f pos;
} EnInvadepohWarpEffect; // size = 0x10

EnInvadepohWarpEffect sWarpEffects[10];
EnInvadepoh* sUfo;
EnInvadepoh* sRomani;
EnInvadepoh* sCremia;
AnimatedMaterial* sAlienEyeBeamTexAnim;
AnimatedMaterial* sAlienEmptyTexAnim;
static s16 sCsIdList[3];
EnInvadepoh* sClosestAlien;

#define BITPACK(field, value, width, offset) \
    (((field) & ~(((1 << (width)) - 1) << (offset))) | (((value) & ((1 << (width)) - 1)) << (offset)))
#define BITUNPACK(field, width, offset) (((field) & (((1 << width) - 1) << (offset))) >> (offset))

#define PACK_U16_INTO_U32_ARRAY(u32array, index, value)                          \
    if (((index) % 2) == 0) {                                                    \
        u32array[(index) >> 1] = BITPACK(u32array[(index) >> 1], value, 16, 0);  \
    } else {                                                                     \
        u32array[(index) >> 1] = BITPACK(u32array[(index) >> 1], value, 16, 16); \
    }                                                                            \
    (void)0

#define UNPACK_U16_FROM_U32_ARRAY(var, u32array, index)  \
    if (((index) % 2) == 0) {                            \
        var = BITUNPACK(u32array[(index) >> 1], 16, 0);  \
    } else {                                             \
        var = BITUNPACK(u32array[(index) >> 1], 16, 16); \
    }                                                    \
    (void)0

void EnInvadepoh_Alien_SetSpawnTime(s32 alienIndex, s32 warpTime) {
    warpTime -= CLOCK_TIME(2, 30);
    warpTime = CLAMP_MIN(warpTime, 0);

    if ((alienIndex % 2) == 0) {
        gSaveContext.save.saveInfo.unk_E64[alienIndex >> 1] =
            (gSaveContext.save.saveInfo.unk_E64[alienIndex >> 1] & ~0xFFFF) | (warpTime & 0xFFFF);
    } else {
        gSaveContext.save.saveInfo.unk_E64[alienIndex >> 1] =
            (gSaveContext.save.saveInfo.unk_E64[alienIndex >> 1] & 0xFFFF) | ((warpTime & 0xFFFF) << 0x10);
    }
}

s32 EnInvadepoh_Alien_GetSpawnTime(s32 alienIndex) {
    u32 warpTime;

    if ((alienIndex % 2) == 0) {
        warpTime = gSaveContext.save.saveInfo.unk_E64[alienIndex >> 1] & 0xFFFF;
    } else {
        warpTime = (gSaveContext.save.saveInfo.unk_E64[alienIndex >> 1] & ~0xFFFF) >> 0x10;
    }
    return warpTime + CLOCK_TIME(2, 30);
}

void EnInvadepoh_Alien_SetKillCount(s32 count) {
    gSaveContext.save.saveInfo.unk_E64[4] = (gSaveContext.save.saveInfo.unk_E64[4] & ~0xFF) | (count & 0xFF);
}

s32 EnInvadepoh_Alien_GetKillCount(void) {
    return gSaveContext.save.saveInfo.unk_E64[4] & 0xFF;
}

s32 EnInvadepoh_Alien_AddKill(void) {
    s32 killCount = EnInvadepoh_Alien_GetKillCount();

    if (killCount < 12) {
        killCount++;
        EnInvadepoh_Alien_SetKillCount(killCount);
    }
    return killCount;
}

void EnInvadepoh_Alien_SetRespawnTime(s32 alienIndex) {
    s32 currentTime = CURRENT_TIME;

    if ((CURRENT_DAY == 1) && (currentTime >= CLOCK_TIME(2, 30)) && (currentTime < CLOCK_TIME(5, 15))) {
        s32 spawnDelay = (12 - EnInvadepoh_Alien_GetKillCount()) * 25.0f;

        EnInvadepoh_Alien_SetSpawnTime(alienIndex, currentTime + spawnDelay);
    }
}

s32 EnInvadepoh_Alien_GetCurrentPoint(EnInvadepoh* this) {
    s32 i;
    s32 lastPoint = this->endPoint - 1;

    for (i = 0; i < lastPoint; i++) {
        if (this->pathProgress < this->pathCheckpoints[i]) {
            break;
        }
    }
    return i;
}

void EnInvadepoh_Romani_ApplyProgress(EnInvadepoh* this, s8* currentPoint, Vec3f* pathPosition) {
    f32 curPathLength = 0.0f;
    f32 curCheckpoint = 0.0f;
    f32 invPathLength = 1.0f / this->pathLength;
    s32 endPoint = this->endPoint;
    s32 i;
    Vec3f curToNext;
    Vec3s* curPathPoint = this->pathPoints;
    Vec3s* nextPathPoint = curPathPoint + 1;
    f32 nextCheckpoint;
    f32 nextPathLength;
    f32 segmentProgress;
    f32 pathSegLength;

    for (i = 0; i < endPoint; i++) {
        curToNext.x = nextPathPoint->x - curPathPoint->x;
        curToNext.y = nextPathPoint->y - curPathPoint->y;
        curToNext.z = nextPathPoint->z - curPathPoint->z;
        pathSegLength = Math3D_Vec3fMagnitude(&curToNext);
        nextPathLength = curPathLength + pathSegLength;
        nextCheckpoint = nextPathLength * invPathLength;
        if (this->pathProgress <= nextCheckpoint) {
            *currentPoint = i;
            segmentProgress = (this->pathProgress - curCheckpoint) / (nextCheckpoint - curCheckpoint);
            pathPosition->x = (segmentProgress * curToNext.x) + curPathPoint->x;
            pathPosition->y = (segmentProgress * curToNext.y) + curPathPoint->y;
            pathPosition->z = (segmentProgress * curToNext.z) + curPathPoint->z;
            return;
        }
        curPathPoint = nextPathPoint++;
        curPathLength = nextPathLength;
        curCheckpoint = nextCheckpoint;
    }
    *currentPoint = endPoint;
    pathPosition->x = this->pathPoints[endPoint].x;
    pathPosition->y = this->pathPoints[endPoint].y;
    pathPosition->z = this->pathPoints[endPoint].z;
}

void EnInvadepoh_Alien_TurnToPath(EnInvadepoh* this, s16 step, s16 offset) {
    s32 pad;
    Vec3s* curPathPoint = &this->pathPoints[this->currentPoint];
    Vec3s* nextPathPoint = curPathPoint + 1;
    Vec3f curPathPointF;
    Vec3f nextPathPointF;

    if (this->currentPoint != this->endPoint) {
        Math_Vec3s_ToVec3f(&curPathPointF, curPathPoint);
        Math_Vec3s_ToVec3f(&nextPathPointF, nextPathPoint);
        Math_ScaledStepToS(&this->actor.shape.rot.y, Math_Vec3f_Yaw(&curPathPointF, &nextPathPointF) + offset, step);
    }
}

void EnInvadepoh_Romani_TurnToPath(EnInvadepoh* this, s16 scale, s16 step, s16 minStep) {
    s32 pad;
    Vec3s* curPathPoint = &this->pathPoints[this->currentPoint];
    Vec3s* nextPathPoint = curPathPoint + 1;
    Vec3f curPathPointF;
    Vec3f nextPathPointF;

    if (this->currentPoint != this->endPoint) {
        Math_Vec3s_ToVec3f(&curPathPointF, curPathPoint);
        Math_Vec3s_ToVec3f(&nextPathPointF, nextPathPoint);
        Math_SmoothStepToS(&this->actor.shape.rot.y, Math_Vec3f_Yaw(&curPathPointF, &nextPathPointF), scale, step,
                           minStep);
    }
}

void EnInvadepoh_SetYawAlongPath(EnInvadepoh* this) {
    s32 pad;
    Vec3s* curPathPoint = &this->pathPoints[this->currentPoint];
    Vec3s* nextPathPoint = curPathPoint + 1;
    Vec3f curPathPointF;
    Vec3f nextPathPointF;

    Math_Vec3s_ToVec3f(&curPathPointF, curPathPoint);
    Math_Vec3s_ToVec3f(&nextPathPointF, nextPathPoint);
    this->actor.shape.rot.y = Math_Vec3f_Yaw(&curPathPointF, &nextPathPointF);
}

f32 EnInvadepoh_GetPathLength(EnInvadepoh* this) {
    s32 pointCount = this->endPoint + 1;
    s32 i;
    Vec3f prevPathVec;
    Vec3f curPathVec;
    Vec3s* curPathPoint = this->pathPoints;
    f32 pathLength = 0.0f;

    Math_Vec3s_ToVec3f(&curPathVec, curPathPoint);

    for (curPathPoint++, i = 1; i < pointCount; curPathPoint++, i++) {
        Math_Vec3f_Copy(&prevPathVec, &curPathVec);
        Math_Vec3s_ToVec3f(&curPathVec, curPathPoint);
        pathLength += Math3D_Distance(&prevPathVec, &curPathVec);
    }
    return pathLength;
}

void EnInvadepoh_SetPath(EnInvadepoh* this, PlayState* play) {
    Path* path = &play->setupPathList[EN_INVADEPOH_GET_PATH(&this->actor)];

    this->endPoint = path->count - 1;
    this->pathPoints = Lib_SegmentedToVirtual(path->points);
}

void EnInvadepoh_SetPosToPathPoint(EnInvadepoh* this, s32 point) {
    Math_Vec3s_ToVec3f(&this->actor.world.pos, &this->pathPoints[point]);
}

s32 EnInvadepoh_Dog_IsOnPath(EnInvadepoh* this, f32 highValue, f32 lowValue) {
    Vec3s* nextPoint = &this->pathPoints[this->currentPoint] + 1;
    Vec3s* currentPoint = &this->pathPoints[this->currentPoint];
    s32 pad;
    f32 pathSegmentX;
    f32 pathSegmentZ;
    f32 pathUnitVecZ;
    f32 pathUnitVecX;
    f32 travelSegmentX;
    f32 travelSegmentZ;
    f32 distAlongPath;
    f32 pathSegmentLength;
    f32 distOffPath;
    s16 pathYaw;

    if (this->currentPoint >= this->endPoint) {
        return false;
    }

    pathSegmentX = (nextPoint->x - currentPoint->x);
    pathSegmentZ = (nextPoint->z - currentPoint->z);
    pathYaw = Math_Atan2S_XY(pathSegmentZ, pathSegmentX);
    pathUnitVecZ = Math_CosS(pathYaw);
    pathUnitVecX = Math_SinS(pathYaw);
    travelSegmentX = this->actor.world.pos.x - currentPoint->x;
    travelSegmentZ = this->actor.world.pos.z - currentPoint->z;

    distOffPath = fabsf((travelSegmentX * pathUnitVecZ) - (travelSegmentZ * pathUnitVecX));
    if (distOffPath > (highValue - lowValue)) {
        return false;
    }

    pathSegmentLength = Math3D_XZLength(pathSegmentX, pathSegmentZ);
    distAlongPath = (travelSegmentZ * pathUnitVecZ) + (travelSegmentX * pathUnitVecX);
    if ((distAlongPath < 0.0f) || (pathSegmentLength < distAlongPath)) {
        return false;
    }
    return true;
}

s32 EnInvadepoh_Dog_FindClosestWaypoint(EnInvadepoh* this, Vec3f* pos) {
    s32 waypoint;
    s32 endPoint = this->endPoint;
    Vec3s* pathPoint;
    Vec3f pathPoint3f;
    f32 minDist = FLT_MAX;
    s32 closestPoint = 0;
    f32 pointToPos;

    for (waypoint = 0, pathPoint = this->pathPoints; waypoint < endPoint; waypoint++, pathPoint++) {
        Math_Vec3s_ToVec3f(&pathPoint3f, pathPoint);
        pointToPos = Math3D_Vec3fDistSq(&pathPoint3f, pos);
        if (pointToPos < minDist) {
            minDist = pointToPos;
            closestPoint = waypoint;
        }
    }
    return closestPoint;
}

void EnInvadepoh_Alien_SetProgress(EnInvadepoh* this) {
    s32 pad;
    s32 currentTime = CURRENT_TIME;
    s32 warpInTime = EnInvadepoh_Alien_GetSpawnTime(EN_INVADEPOH_GET_INDEX(&this->actor));

    if (sEventState == EN_INVADEPOH_EVENT_WAIT) {
        this->pathProgress = 0.0f;
    } else if (sEventState == EN_INVADEPOH_EVENT_ACTIVE) {
        if ((currentTime - warpInTime) < 0) {
            this->pathProgress = 0.0f;
        } else {
            this->pathProgress = (currentTime - warpInTime) * (1.0f / 3600.0f);
            if (this->pathProgress > 1.0f) {
                this->pathProgress = 1.0f;
            }
        }
    }
    this->currentPoint = EnInvadepoh_Alien_GetCurrentPoint(this);
}

void EnInvadepoh_Alien_SetCheckpoints(EnInvadepoh* this) {
    f32 invPathLength = 1.0f / this->pathLength;
    s32 endPoint = this->endPoint;
    s32 i;
    Vec3f prevPathPoint;
    Vec3f pathPointF;
    Vec3s* pathPoint = this->pathPoints;
    f32 pathPointLength = 0.0f;
    f32* pathCheckpoints;

    Math_Vec3s_ToVec3f(&pathPointF, pathPoint);
    pathPoint++;
    pathCheckpoints = this->pathCheckpoints;
    for (i = 1; i < endPoint; i++, pathPoint++, pathCheckpoints++) {
        Math_Vec3f_Copy(&prevPathPoint, &pathPointF);
        Math_Vec3s_ToVec3f(&pathPointF, pathPoint);
        pathPointLength += Math3D_Distance(&prevPathPoint, &pathPointF);
        *pathCheckpoints = pathPointLength * invPathLength;
        if (*pathCheckpoints < 0.0f) {
            *pathCheckpoints = 0.0f;
        } else if (*pathCheckpoints > 1.0f) {
            *pathCheckpoints = 1.0f;
        }
    }
}

void EnInvadepoh_Alien_SetupPath(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_SetPath(this, play);
    this->pathLength = EnInvadepoh_GetPathLength(this);
    EnInvadepoh_Alien_SetCheckpoints(this);
}

void EnInvadepoh_SilentRomani_SetupPath(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_SetPath(this, play);
}

void EnInvadepoh_SilentRomani_SetNextPathPoint(EnInvadepoh* this) {
    this->currentPoint++;
    if (this->currentPoint >= this->endPoint) {
        this->currentPoint = 0;
    }
}

void EnInvadepoh_Night1Romani_SetupPath(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_SetPath(this, play);
    this->pathLength = EnInvadepoh_GetPathLength(this);
}

void EnInvadepoh_Night1Romani_SetProgress(EnInvadepoh* this) {
    if ((CURRENT_TIME < CLOCK_TIME(2, 00)) || (CURRENT_TIME >= CLOCK_TIME(6, 00))) {
        this->pathProgress = 0.0f;
    } else if ((CURRENT_TIME >= CLOCK_TIME(2, 15)) && (CURRENT_TIME < CLOCK_TIME(6, 00))) {
        this->pathProgress = 1.0f;
    } else {
        f32 progress = (CURRENT_TIME - CLOCK_TIME(2, 00)) * (1.0f / (CLOCK_TIME(2, 15) - CLOCK_TIME(2, 00)));

        this->pathProgress = progress;
        this->pathProgress = CLAMP(this->pathProgress, 0.0f, 1.0f);
    }
}

void EnInvadepoh_BarnRomani_SetupPath(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_SetPath(this, play);
}

void EnInvadepoh_BarnRomani_SetNextPathPoint(EnInvadepoh* this) {
    if (this->currentPoint < this->endPoint) {
        this->currentPoint++;
    }
}

void EnInvadepoh_Dog_SetupPath(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_SetPath(this, play);
    this->pathStep = 1;
}

void EnInvadepoh_Dog_SetNextPathPoint(EnInvadepoh* this) {
    this->currentPoint += this->pathStep;
    if (this->currentPoint >= this->endPoint) {
        this->currentPoint = 0;
    } else if (this->currentPoint < 0) {
        this->currentPoint = this->endPoint - 1;
    }
}

void EnInvadepoh_Night3Romani_SetupPath(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_SetPath(this, play);
    this->pathLength = EnInvadepoh_GetPathLength(this);
}

void EnInvadepoh_Night3Romani_SetProgress(EnInvadepoh* this) {
    if ((CURRENT_TIME < CLOCK_TIME(20, 00)) && (CURRENT_TIME >= CLOCK_TIME(6, 00))) {
        this->pathProgress = 0.0f;
    } else if ((CURRENT_TIME >= CLOCK_TIME(20, 14) + 15) || (CURRENT_TIME < CLOCK_TIME(6, 00))) {
        this->pathProgress = 1.0f;
    } else {
        f32 progress = (CURRENT_TIME - CLOCK_TIME(20, 00)) * (1.0f / (CLOCK_TIME(20, 14) + 15 - CLOCK_TIME(20, 00)));

        this->pathProgress = progress;
        this->pathProgress = CLAMP(this->pathProgress, 0.0f, 1.0f);
    }
}

void EnInvadepoh_Alien_ApplyProgress(EnInvadepoh* this, PlayState* play) {
    s32 pad;
    Vec3s* curPathPoint;
    Vec3s* nextPathPoint;
    Vec3f curPathPointF;
    Vec3f nextPathPointF;
    f32 yPosTemp = this->actor.world.pos.y;
    f32 curCheckpoint;
    f32 nextCheckpoint;

    curPathPoint = this->pathPoints + this->currentPoint;
    nextPathPoint = curPathPoint + 1;
    curCheckpoint = (this->currentPoint <= 0) ? 0.0f : this->pathCheckpoints[this->currentPoint - 1];
    nextCheckpoint = (this->currentPoint < (this->endPoint - 1)) ? this->pathCheckpoints[this->currentPoint] : 1.0f;

    if (nextCheckpoint - curCheckpoint < 0.001f) {
        Math_Vec3s_ToVec3f(&this->currentPos, curPathPoint);
    } else {
        f32 nextWeight = this->pathProgress - curCheckpoint;
        f32 prevWeight = nextCheckpoint - this->pathProgress;
        f32 invPathLength = 1.0f / (nextCheckpoint - curCheckpoint);
        s32 pad3;

        Math_Vec3s_ToVec3f(&curPathPointF, curPathPoint);
        Math_Vec3s_ToVec3f(&nextPathPointF, nextPathPoint);
        this->currentPos.x = ((curPathPointF.x * prevWeight) + (nextPathPointF.x * nextWeight)) * invPathLength;
        this->currentPos.y = ((curPathPointF.y * prevWeight) + (nextPathPointF.y * nextWeight)) * invPathLength;
        this->currentPos.z = ((curPathPointF.z * prevWeight) + (nextPathPointF.z * nextWeight)) * invPathLength;
    }

    Math_Vec3f_Copy(&this->actor.world.pos, &this->currentPos);
    func_800B4AEC(play, &this->actor, 0.0f);

    if (this->actor.floorHeight > (BGCHECK_Y_MIN + 1.0f)) {
        if (yPosTemp < this->actor.floorHeight) {
            if (this->actor.velocity.y < 0.0f) {
                this->actor.velocity.y = 0.0f;
            } else {
                this->actor.velocity.y += 2.0f;
                this->actor.velocity.y = CLAMP_MAX(this->actor.velocity.y, 30.0f);
            }
            this->actor.world.pos.y = this->actor.velocity.y + yPosTemp;
            if (this->actor.floorHeight < this->actor.world.pos.y) {
                this->actor.world.pos.y = this->actor.floorHeight;
            }
        } else {
            if (this->actor.velocity.y > 0.0f) {
                this->actor.velocity.y = 0.0f;
            } else {
                this->actor.velocity.y -= 2.0f;
            }
            this->actor.world.pos.y = this->actor.velocity.y + yPosTemp;
            if (this->actor.world.pos.y < this->actor.floorHeight) {
                this->actor.world.pos.y = this->actor.floorHeight;
                this->actor.velocity.y = CLAMP_MIN(this->actor.velocity.y, -30.0f);
            }
        }
    } else {
        this->actor.world.pos.y = yPosTemp;
    }
}

void EnInvadepoh_Alien_Knockback(EnInvadepoh* this, PlayState* play) {
    if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
        this->actor.velocity.y *= 0.3f;
        this->actor.speed *= 0.8f;
    } else if (this->actor.bgCheckFlags & BGCHECKFLAG_WALL) {
        this->actor.velocity.y *= 0.8f;
        this->actor.speed *= 0.3f;
    } else {
        this->actor.velocity.y *= 0.8f;
        this->actor.speed *= 0.8f;
    }
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 40.0f, 0.0f, UPDBGCHECKINFO_FLAG_1 | UPDBGCHECKINFO_FLAG_4);
}

void EnInvadepoh_Alien_EmptyFunc(EnInvadepoh* this) {
}

s32 EnInvadepoh_Romani_MoveAlongPath(EnInvadepoh* this, PlayState* play, f32 speed, f32 height) {
    s32 pad;
    Vec3s* nextPathPoint = &this->pathPoints[this->currentPoint + 1];
    s32 reachedNextPoint = EnInvadepoh_StepTowardXZ(&this->actor.world.pos.x, &this->actor.world.pos.z,
                                                    nextPathPoint->x, nextPathPoint->z, speed);

    func_800B4AEC(play, &this->actor, height);
    EnInvadepoh_SnapToFloor(this);
    return reachedNextPoint;
}

void EnInvadepoh_Night1Romani_MoveAlongPathTimed(EnInvadepoh* this, PlayState* play) {
    s32 pad;
    f32 yPosTemp = this->actor.world.pos.y;

    EnInvadepoh_Romani_ApplyProgress(this, &this->currentPoint, &this->actor.world.pos);
    this->actor.world.pos.y = yPosTemp;
    func_800B4AEC(play, &this->actor, 50.0f);
    EnInvadepoh_SnapToFloor(this);
}

s32 EnInvadepoh_Dog_MoveAlongPath(EnInvadepoh* this, PlayState* play) {
    s32 pad;
    Vec3s* currentPathPoint = &this->pathPoints[this->currentPoint];
    s32 nextPoint;
    Vec3s* nextPathPoint;
    f32 nextPathPointX;
    f32 nextPathPointZ;
    f32 curPathPointX;
    f32 curPathPointZ;
    Vec3f currentToNext;
    Vec3f worldToNext;
    Vec3f worldToCurrent;
    Vec3f worldToTarget;
    f32 angleToNext;
    s32 reachedNext = false;

    nextPoint = this->currentPoint + this->pathStep;

    if (nextPoint >= this->endPoint) {
        nextPoint = 0;
    } else if (nextPoint < 0) {
        nextPoint = this->endPoint - 1;
    }

    nextPathPoint = &this->pathPoints[nextPoint];

    curPathPointX = currentPathPoint->x;
    curPathPointZ = currentPathPoint->z;
    nextPathPointX = nextPathPoint->x;
    nextPathPointZ = nextPathPoint->z;

    currentToNext.x = nextPathPointX - curPathPointX;
    currentToNext.y = 0.0f;
    currentToNext.z = nextPathPointZ - curPathPointZ;

    worldToNext.x = nextPathPointX - this->actor.world.pos.x;
    worldToNext.y = 0.0f;
    worldToNext.z = nextPathPointZ - this->actor.world.pos.z;

    worldToCurrent.x = curPathPointX - this->actor.world.pos.x;
    worldToCurrent.y = 0.0f;
    worldToCurrent.z = curPathPointZ - this->actor.world.pos.z;

    if (this->actor.speed > 0.0f) {
        if (Math3D_AngleBetweenVectors(&currentToNext, &worldToNext, &angleToNext)) {
            reachedNext = true;
        } else if (angleToNext <= 0.0f) {
            reachedNext = true;
        }
    }

    // Instead of targeting nextPathPoint, the target is about 5% beyond it along that path segment.
    worldToTarget.x = ((worldToNext.x + worldToCurrent.x) * 0.9f) + currentToNext.x;
    worldToTarget.y = 0.0f;
    worldToTarget.z = ((worldToNext.z + worldToCurrent.z) * 0.9f) + currentToNext.z;

    Math_SmoothStepToS(&this->actor.world.rot.y, Math_Atan2S_XY(worldToTarget.z, worldToTarget.x), 4, 0xFA0, 0x64);
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 15.0f, 0.0f,
                            EnInvadepoh_Dog_IsOnPath(this, 50.0f, 15.0f)
                                ? UPDBGCHECKINFO_FLAG_4
                                : UPDBGCHECKINFO_FLAG_1 | UPDBGCHECKINFO_FLAG_4);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.world.rot.y, 3, 0x1F40, 0x64);

    return reachedNext;
}

void EnInvadepoh_Dog_Move(EnInvadepoh* this, PlayState* play) {
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 15.0f, 0.0f, UPDBGCHECKINFO_FLAG_1 | UPDBGCHECKINFO_FLAG_4);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.world.rot.y, 3, 0x1F40, 0x64);
}

void EnInvadepoh_Night3Romani_MoveAlongPathTimed(EnInvadepoh* this, PlayState* play) {
    s32 pad;
    f32 yPosTemp = this->actor.world.pos.y;

    EnInvadepoh_Romani_ApplyProgress(this, &this->currentPoint, &this->actor.world.pos);
    this->actor.world.pos.y = yPosTemp;
    func_800B4AEC(play, &this->actor, 50.0f);
    EnInvadepoh_SnapToFloor(this);
}

void EnInvadepoh_Romani_DesegmentTextures(void) {
    TexturePtr* texPtr;
    s32 i;

    if (!sRomaniTexturesDesegmented) {
        sRomaniTexturesDesegmented = true;
        for (i = 0, texPtr = sRomaniEyeTextures; i < 5; i++, texPtr++) {
            *texPtr = Lib_SegmentedToVirtual(*texPtr);
        }
        for (i = 0, texPtr = sRomaniMouthTextures; i < 4; i++, texPtr++) {
            *texPtr = Lib_SegmentedToVirtual(*texPtr);
        }
    }
}

void EnInvadepoh_Cremia_DesegmentTextures(void) {
    TexturePtr* texture;
    s32 i;

    if (!sCremiaTexturesDesegmented) {
        sCremiaTexturesDesegmented = true;
        for (i = 0, texture = sCremiaEyeTextures; i < 6; i++, texture++) {
            *texture = Lib_SegmentedToVirtual(*texture);
        }
        for (i = 0, texture = sCremiaMouthTextures; i < 4; i++, texture++) {
            *texture = Lib_SegmentedToVirtual(*texture);
        }
    }
}

void EnInvadepoh_Alien_SetTexAnim(void) {
    sAlienEmptyTexAnim = Lib_SegmentedToVirtual(gAlienEmptyTexAnim);
    sAlienEyeBeamTexAnim = Lib_SegmentedToVirtual(gAlienEyeBeamTexAnim);
}

s32 EnInvadepoh_StepTowardXZ(f32* pxValue, f32* pzValue, f32 xTarget, f32 zTarget, f32 speed) {
    f32 xDiff = xTarget - *pxValue;
    f32 zDiff = zTarget - *pzValue;
    f32 distToTarget = Math3D_XZLength(xDiff, zDiff);

    if (speed < distToTarget) {
        f32 progressStep = speed / distToTarget;

        *pxValue += progressStep * xDiff;
        *pzValue += progressStep * zDiff;
        return false;
    } else {
        *pxValue = xTarget;
        *pzValue = zTarget;
        return true;
    }
}

s32 EnInvadepoh_SnapToFloor(EnInvadepoh* this) {
    if (this->actor.floorHeight > BGCHECK_Y_MIN + 1.0f) {
        this->actor.world.pos.y = this->actor.floorHeight;
        return true;
    }
    return false;
}

void EnInvadepoh_InvasionHandler_CheckState(EnInvadepoh* this, PlayState* play) {
    if (sEventState == EN_INVADEPOH_EVENT_UNSET) {
        if (CURRENT_DAY < 1) {
            sEventState = EN_INVADEPOH_EVENT_WAIT;
        } else if (CURRENT_DAY == 1) {
            s32 currentTime = CURRENT_TIME;

            if (!((currentTime >= CLOCK_TIME(2, 30)) && (currentTime < CLOCK_TIME(6, 00)))) {
                sEventState = EN_INVADEPOH_EVENT_WAIT;
            } else if (currentTime < CLOCK_TIME(5, 15)) {
                s32 i;
                s32 firstSpawn = CLOCK_TIME(5, 15);
                s32 pad;

                for (i = 0; i < this->alienCount; i++) {
                    s32 spawnTime = EnInvadepoh_Alien_GetSpawnTime(i);

                    firstSpawn = MIN(spawnTime, firstSpawn);
                }
                if (currentTime < (firstSpawn + 3601)) { // 79 in-game minutes
                    sEventState = EN_INVADEPOH_EVENT_ACTIVE;
                }
            }
        }
        if (sEventState == EN_INVADEPOH_EVENT_UNSET) {
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_DEFENDED_AGAINST_THEM)) {
                sEventState = EN_INVADEPOH_EVENT_CLEAR;
            } else {
                sEventState = EN_INVADEPOH_EVENT_FAILED;
            }
        }
    }
}

void EnInvadepoh_InvasionHandler_SpawnAliens(EnInvadepoh* this, PlayState* play) {
    s32 pathIndex = EN_INVADEPOH_GET_PATH(&this->actor);
    s32 i;

    for (i = 0; i < this->alienCount; i++) {
        sAliens[i] = (EnInvadepoh*)Actor_Spawn(&play->actorCtx, play, ACTOR_EN_INVADEPOH, this->actor.world.pos.x,
                                               this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0,
                                               EN_INVADEPOH_PARAMS(pathIndex, EN_INVADEPOH_TYPE_ALIEN, i));
        if (pathIndex != EN_INVADEPOH_PATH_INDEX_NONE) {
            Path* path = &play->setupPathList[pathIndex];

            pathIndex = path->additionalPathIndex;
        }
    }
}

void EnInvadepoh_AlienAbductor_SpawnCow(EnInvadepoh* this, PlayState* play, s32 index) {
    Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EN_INVADEPOH, this->actor.home.pos.x,
                       this->actor.home.pos.y, this->actor.home.pos.z, 0, 0, 0,
                       EN_INVADEPOH_PARAMS(0, EN_INVADEPOH_TYPE_COW, index));
}

void EnInvadepoh_AlienAbductor_SpawnRomani(EnInvadepoh* this, PlayState* play) {
    Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EN_INVADEPOH, this->actor.home.pos.x,
                       this->actor.home.pos.y, this->actor.home.pos.z, 0, 0, 0,
                       EN_INVADEPOH_PARAMS(0, EN_INVADEPOH_TYPE_ROMANI_ABDUCTED, 0));
}

void EnInvadepoh_InvasionHandler_SpawnUfo(EnInvadepoh* this, PlayState* play) {
    sUfo = (EnInvadepoh*)Actor_Spawn(&play->actorCtx, play, ACTOR_EN_INVADEPOH, this->actor.world.pos.x,
                                     this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0,
                                     EN_INVADEPOH_PARAMS(0, EN_INVADEPOH_TYPE_UFO, 0));
}

void EnInvadepoh_Ufo_ReplaceTranslation(Vec3f* translation) {
    MtxF* curMtxF = Matrix_GetCurrent();

    curMtxF->xw = translation->x;
    curMtxF->yw = translation->y;
    curMtxF->zw = translation->z;
}

s32 EnInvadepoh_Romani_OpenDoor(EnInvadepoh* this, PlayState* play, f32 rangeSq, s32 doorTimer) {
    Actor* doorActor = play->actorCtx.actorLists[ACTORCAT_DOOR].first;
    EnDoor* door;
    s32 doorOpened = false;

    while (doorActor != NULL) {
        if ((doorActor->id == ACTOR_EN_DOOR) && (doorActor->update != NULL)) {
            door = (EnDoor*)doorActor;
            if ((door->knobDoor.dyna.actor.room == this->actor.room) &&
                (Math3D_Vec3fDistSq(&door->knobDoor.dyna.actor.world.pos, &this->actor.world.pos) < rangeSq)) {

                door->openTimer = doorTimer;
                doorOpened = true;
                break;
            }
        }
        doorActor = doorActor->next;
    }
    return doorOpened;
}

void EnInvadepoh_Romani_StartTextBox(EnInvadepoh* this, PlayState* play, u16 textId) {
    this->textId = textId;
    Message_StartTextbox(play, textId, &this->actor);
}

void EnInvadepoh_InvasionHandler_SetCutscenes(EnInvadepoh* this) {
    s16 csId = this->actor.csId;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sCsIdList); i++) {
        sCsIdList[i] = csId;
        csId = CutsceneManager_GetAdditionalCsId(csId);
    }
}

s32 EnInvadepoh_Alien_LensFlareDepthCheck(PlayState* play, Vec3f* pos) {
    Vec3f projectedPos;
    f32 invW;

    Actor_GetProjectedPos(play, pos, &projectedPos, &invW);

    if ((projectedPos.z > 1.0f) && (fabsf(projectedPos.x * invW) < 1.0f) && (fabsf(projectedPos.y * invW) < 1.0f)) {
        f32 screenPosX = PROJECTED_TO_SCREEN_X(projectedPos, invW);
        f32 screenPosY = PROJECTED_TO_SCREEN_Y(projectedPos, invW);
        s32 wZ = (s32)(projectedPos.z * invW * 16352.0f) + 16352;

        if (wZ < SysCfb_GetZBufferInt(screenPosX, screenPosY)) {
            return true;
        }
    }
    return false;
}

void EnInvadepoh_InvasionHandler_SetClosestAlien(EnInvadepoh* this) {
    s32 i;
    f32 minDistSqToBarn = FLT_MAX;
    s32 closestAlienIndex = -1;

    for (i = 0; i < this->alienCount; i++) {
        if ((sAliens[i] != NULL) && sAliens[i]->shouldDraw) {
            f32 distSqToBarn = Math3D_Vec3fDistSq(&sAliens[i]->actor.world.pos, &this->actor.world.pos);

            if (minDistSqToBarn > distSqToBarn) {
                minDistSqToBarn = distSqToBarn;
                closestAlienIndex = i;
            }
        }
        sAlienStateFlags[i] &= ~EN_INVADEPOH_ALIEN_CLOSEST;
    }

    sAliensTooClose = false;

    if (minDistSqToBarn <= SQ(2000.0f)) {
        sAlienStateFlags[closestAlienIndex] |= EN_INVADEPOH_ALIEN_CLOSEST;
        if (minDistSqToBarn <= SQ(340.0f)) {
            sAliensTooClose = true;
        }
    }
}

EnInvadepoh* EnInvadepoh_Dog_GetClosestAlien(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (sAlienStateFlags[i] & EN_INVADEPOH_ALIEN_CLOSEST) {
            return sAliens[i];
        }
    }
    return NULL;
}

s8 EnInvadepoh_Interact_GetNextAnim(EnInvadepohFaceAnimNext* nextAnims, s32 nextAnimCount) {
    f32 rand = Rand_ZeroOne();
    EnInvadepohFaceAnimNext* nextAnim = nextAnims;
    s32 nextIndex;

    nextAnimCount--;
    for (nextIndex = 0; nextIndex < nextAnimCount; nextIndex++, nextAnim++) {
        if (rand <= nextAnim->chance) {
            break;
        }
    }

    //! FAKE:
    return (nextAnims + nextIndex)->index;
}

void EnInvadepoh_Interact_SetNextAnim(EnInvadepohFaceAnimInfo* faceInfo, EnInvadepohFaceAnim* faceAnim) {
    faceInfo->curAnimType = faceAnim->type;
    faceInfo->curAnim = faceAnim;
    faceInfo->curFrame = 0;
    faceInfo->curIndex = faceAnim->frames->texIndex[0];
    if (faceInfo->curAnimType == EN_INVADEPOH_FACE_ANIMATION_TYPE_DELAYED_BRANCHED) {
        EnInvadepohFaceAnimDelayedBranched* faceDelayedLoopAnim = (EnInvadepohFaceAnimDelayedBranched*)faceAnim;

        faceInfo->delayTimer = Rand_S16Offset(faceDelayedLoopAnim->minDelay, faceDelayedLoopAnim->maxDelay);
    }
}

void EnInvadepoh_Interact_UpdateFixedAnim(EnInvadepohFaceAnimInfo* faceInfo, EnInvadepohFaceAnim** animations) {
    EnInvadepohFaceAnim* faceAnim = faceInfo->curAnim;
    EnInvadepohFaceFrames* faceFrames = faceAnim->frames;

    if (faceInfo->curFrame < (faceFrames->count - 1)) {
        faceInfo->curFrame++;
        faceInfo->curIndex = faceFrames->texIndex[faceInfo->curFrame];
    }
}

void EnInvadepoh_Interact_UpdateBranchedAnim(EnInvadepohFaceAnimInfo* faceInfo, EnInvadepohFaceAnim** animations) {
    EnInvadepohFaceAnimBranched* faceAnimLoop = (EnInvadepohFaceAnimBranched*)faceInfo->curAnim;
    EnInvadepohFaceFrames* faceFrames = faceAnimLoop->anim.frames;

    if (faceInfo->curFrame < (faceFrames->count - 1)) {
        faceInfo->curFrame++;
        faceInfo->curIndex = faceFrames->texIndex[faceInfo->curFrame];
    } else {
        EnInvadepohFaceAnim* nextAnim =
            animations[EnInvadepoh_Interact_GetNextAnim(faceAnimLoop->nextAnims, faceAnimLoop->nextCount)];

        EnInvadepoh_Interact_SetNextAnim(faceInfo, nextAnim);
    }
}

void EnInvadepoh_Interact_UpdateDelayedBranchedAnim(EnInvadepohFaceAnimInfo* faceInfo,
                                                    EnInvadepohFaceAnim** animations) {
    EnInvadepohFaceAnimDelayedBranched* faceAnimLoopDelayed = (EnInvadepohFaceAnimDelayedBranched*)faceInfo->curAnim;
    EnInvadepohFaceFrames* faceFrames = faceAnimLoopDelayed->loop.anim.frames;

    if (faceInfo->curFrame < (faceFrames->count - 1)) {
        faceInfo->curFrame++;
        faceInfo->curIndex = faceFrames->texIndex[faceInfo->curFrame];
    } else if (faceInfo->delayTimer > 0) {
        faceInfo->delayTimer--;
    } else {
        EnInvadepohFaceAnim* nextAnim = animations[EnInvadepoh_Interact_GetNextAnim(
            faceAnimLoopDelayed->loop.nextAnims, faceAnimLoopDelayed->loop.nextCount)];

        EnInvadepoh_Interact_SetNextAnim(faceInfo, nextAnim);
    }
}

typedef enum RomaniEyeAnimation {
    /* 0 */ ROMANI_EYE_ANIMATION_0,
    /* 1 */ ROMANI_EYE_ANIMATION_1,
    /* 2 */ ROMANI_EYE_ANIMATION_2,
    /* 3 */ ROMANI_EYE_ANIMATION_3,
    /* 4 */ ROMANI_EYE_ANIMATION_4,
    /* 5 */ ROMANI_EYE_ANIMATION_5,
    /* 6 */ ROMANI_EYE_ANIMATION_6,
    /* 7 */ ROMANI_EYE_ANIMATION_7,
    /* 8 */ ROMANI_EYE_ANIMATION_MAX
} RomaniEyeAnimation;

s8 D_80B4E99C[1] = { ROMANI_EYE_OPEN };
s8 D_80B4E9A0[4] = { ROMANI_EYE_OPEN, ROMANI_EYE_HALF, ROMANI_EYE_CLOSED, ROMANI_EYE_OPEN };
s8 D_80B4E9A4[5] = { ROMANI_EYE_OPEN, ROMANI_EYE_HALF, ROMANI_EYE_CLOSED, ROMANI_EYE_HALF, ROMANI_EYE_OPEN };
s8 D_80B4E9AC[6] = { ROMANI_EYE_OPEN,   ROMANI_EYE_HALF, ROMANI_EYE_CLOSED,
                     ROMANI_EYE_CLOSED, ROMANI_EYE_HALF, ROMANI_EYE_OPEN };
s8 D_80B4E9B4[8] = { ROMANI_EYE_OPEN, ROMANI_EYE_HALF, ROMANI_EYE_CLOSED, ROMANI_EYE_HALF,
                     ROMANI_EYE_OPEN, ROMANI_EYE_HALF, ROMANI_EYE_CLOSED, ROMANI_EYE_OPEN };
s8 D_80B4E9BC[1] = { ROMANI_EYE_HALF };
s8 D_80B4E9C0[1] = { ROMANI_EYE_HAPPY };
EnInvadepohFaceFrames D_80B4E9C4 = { D_80B4E99C, ARRAY_COUNT(D_80B4E99C) };
EnInvadepohFaceFrames D_80B4E9CC = { D_80B4E9A0, ARRAY_COUNT(D_80B4E9A0) };
EnInvadepohFaceFrames D_80B4E9D4 = { D_80B4E9A4, ARRAY_COUNT(D_80B4E9A4) };
EnInvadepohFaceFrames D_80B4E9DC = { D_80B4E9AC, ARRAY_COUNT(D_80B4E9AC) };
EnInvadepohFaceFrames D_80B4E9E4 = { D_80B4E9B4, ARRAY_COUNT(D_80B4E9B4) };
EnInvadepohFaceFrames D_80B4E9EC = { D_80B4E9BC, ARRAY_COUNT(D_80B4E9BC) };
EnInvadepohFaceFrames D_80B4E9F4 = { D_80B4E9C0, ARRAY_COUNT(D_80B4E9C0) };
EnInvadepohFaceAnim D_80B4E9FC = { EN_INVADEPOH_FACE_ANIMATION_TYPE_FIXED, &D_80B4E9C4 };
EnInvadepohFaceAnimNext D_80B4EA04[4] = {
    { ROMANI_EYE_ANIMATION_2, 0.5f },
    { ROMANI_EYE_ANIMATION_3, 0.9f },
    { ROMANI_EYE_ANIMATION_4, 0.97f },
    { ROMANI_EYE_ANIMATION_5, 1.0f },
};
EnInvadepohFaceAnimNext D_80B4EA24[1] = { ROMANI_EYE_ANIMATION_1, 1.0f };
EnInvadepohFaceAnimDelayedBranched D_80B4EA2C = {
    { { EN_INVADEPOH_FACE_ANIMATION_TYPE_DELAYED_BRANCHED, &D_80B4E9C4 }, ARRAY_COUNT(D_80B4EA04), D_80B4EA04 }, 40, 60
};
EnInvadepohFaceAnimBranched D_80B4EA40 = { { EN_INVADEPOH_FACE_ANIMATION_TYPE_BRANCHED, &D_80B4E9CC },
                                           ARRAY_COUNT(D_80B4EA24),
                                           D_80B4EA24 };
EnInvadepohFaceAnimBranched D_80B4EA50 = { { EN_INVADEPOH_FACE_ANIMATION_TYPE_BRANCHED, &D_80B4E9D4 },
                                           ARRAY_COUNT(D_80B4EA24),
                                           D_80B4EA24 };
EnInvadepohFaceAnimBranched D_80B4EA60 = { { EN_INVADEPOH_FACE_ANIMATION_TYPE_BRANCHED, &D_80B4E9DC },
                                           ARRAY_COUNT(D_80B4EA24),
                                           D_80B4EA24 };
EnInvadepohFaceAnimBranched D_80B4EA70 = { { EN_INVADEPOH_FACE_ANIMATION_TYPE_BRANCHED, &D_80B4E9E4 },
                                           ARRAY_COUNT(D_80B4EA24),
                                           D_80B4EA24 };
EnInvadepohFaceAnim D_80B4EA80 = { EN_INVADEPOH_FACE_ANIMATION_TYPE_FIXED, &D_80B4E9EC };
EnInvadepohFaceAnim D_80B4EA88 = { EN_INVADEPOH_FACE_ANIMATION_TYPE_FIXED, &D_80B4E9F4 };
EnInvadepohFaceAnim* D_80B4EA90[ROMANI_EYE_ANIMATION_MAX] = {
    &D_80B4E9FC,           // ROMANI_EYE_ANIMATION_0
    &D_80B4EA2C.loop.anim, // ROMANI_EYE_ANIMATION_1
    &D_80B4EA40.anim,      // ROMANI_EYE_ANIMATION_2
    &D_80B4EA50.anim,      // ROMANI_EYE_ANIMATION_3
    &D_80B4EA60.anim,      // ROMANI_EYE_ANIMATION_4
    &D_80B4EA70.anim,      // ROMANI_EYE_ANIMATION_5
    &D_80B4EA80,           // ROMANI_EYE_ANIMATION_6
    &D_80B4EA88,           // ROMANI_EYE_ANIMATION_7
};

typedef enum RomaniMouthAnimation {
    /* 0 */ ROMANI_MOUTH_ANIMATION_0,
    /* 1 */ ROMANI_MOUTH_ANIMATION_1,
    /* 2 */ ROMANI_MOUTH_ANIMATION_2,
    /* 3 */ ROMANI_MOUTH_ANIMATION_3,
    /* 4 */ ROMANI_MOUTH_ANIMATION_MAX
} RomaniMouthAnimation;

s8 D_80B4EAB0[1] = { ROMANI_MOUTH_HAPPY };
s8 D_80B4EAB4[1] = { ROMANI_MOUTH_FROWN };
s8 D_80B4EAB8[1] = { ROMANI_MOUTH_HANGING_OPEN };
s8 D_80B4EABC[1] = { ROMANI_MOUTH_SMILE };
EnInvadepohFaceFrames D_80B4EAC0 = { D_80B4EAB0, ARRAY_COUNT(D_80B4EAB0) };
EnInvadepohFaceFrames D_80B4EAC8 = { D_80B4EAB4, ARRAY_COUNT(D_80B4EAB4) };
EnInvadepohFaceFrames D_80B4EAD0 = { D_80B4EAB8, ARRAY_COUNT(D_80B4EAB8) };
EnInvadepohFaceFrames D_80B4EAD8 = { D_80B4EABC, ARRAY_COUNT(D_80B4EABC) };
EnInvadepohFaceAnim D_80B4EAE0 = { EN_INVADEPOH_FACE_ANIMATION_TYPE_FIXED, &D_80B4EAC0 };
EnInvadepohFaceAnim D_80B4EAE8 = { EN_INVADEPOH_FACE_ANIMATION_TYPE_FIXED, &D_80B4EAC8 };
EnInvadepohFaceAnim D_80B4EAF0 = { EN_INVADEPOH_FACE_ANIMATION_TYPE_FIXED, &D_80B4EAD0 };
EnInvadepohFaceAnim D_80B4EAF8 = { EN_INVADEPOH_FACE_ANIMATION_TYPE_FIXED, &D_80B4EAD8 };
EnInvadepohFaceAnim* D_80B4EB00[ROMANI_MOUTH_ANIMATION_MAX] = {
    &D_80B4EAE0, // ROMANI_MOUTH_ANIMATION_0
    &D_80B4EAE8, // ROMANI_MOUTH_ANIMATION_1
    &D_80B4EAF0, // ROMANI_MOUTH_ANIMATION_2
    &D_80B4EAF8, // ROMANI_MOUTH_ANIMATION_3
};

typedef enum CremiaEyeAnimation {
    /* 0 */ CREMIA_EYE_ANIMATION_0,
    /* 1 */ CREMIA_EYE_ANIMATION_1,
    /* 2 */ CREMIA_EYE_ANIMATION_2,
    /* 3 */ CREMIA_EYE_ANIMATION_3,
    /* 4 */ CREMIA_EYE_ANIMATION_4,
    /* 5 */ CREMIA_EYE_ANIMATION_5,
    /* 6 */ CREMIA_EYE_ANIMATION_MAX
} CremiaEyeAnimation;

s8 D_80B4EB10[1] = { CREMIA_EYE_OPEN };
s8 D_80B4EB14[4] = { CREMIA_EYE_OPEN, CREMIA_EYE_HALF, CREMIA_EYE_CLOSED, CREMIA_EYE_OPEN };
s8 D_80B4EB18[5] = { CREMIA_EYE_OPEN, CREMIA_EYE_HALF, CREMIA_EYE_CLOSED, CREMIA_EYE_HALF, CREMIA_EYE_OPEN };
s8 D_80B4EB20[6] = { CREMIA_EYE_OPEN,   CREMIA_EYE_HALF, CREMIA_EYE_CLOSED,
                     CREMIA_EYE_CLOSED, CREMIA_EYE_HALF, CREMIA_EYE_OPEN };
s8 D_80B4EB28[8] = { CREMIA_EYE_OPEN, CREMIA_EYE_HALF, CREMIA_EYE_CLOSED, CREMIA_EYE_HALF,
                     CREMIA_EYE_OPEN, CREMIA_EYE_HALF, CREMIA_EYE_CLOSED, CREMIA_EYE_OPEN };
EnInvadepohFaceFrames D_80B4EB30 = { D_80B4EB10, ARRAY_COUNT(D_80B4EB10) };
EnInvadepohFaceFrames D_80B4EB38 = { D_80B4EB14, ARRAY_COUNT(D_80B4EB14) };
EnInvadepohFaceFrames D_80B4EB40 = { D_80B4EB18, ARRAY_COUNT(D_80B4EB18) };
EnInvadepohFaceFrames D_80B4EB48 = { D_80B4EB20, ARRAY_COUNT(D_80B4EB20) };
EnInvadepohFaceFrames D_80B4EB50 = { D_80B4EB28, ARRAY_COUNT(D_80B4EB28) };
EnInvadepohFaceAnim D_80B4EB58 = { EN_INVADEPOH_FACE_ANIMATION_TYPE_FIXED, &D_80B4EB30 };
EnInvadepohFaceAnimNext D_80B4EB60[4] = {
    { CREMIA_EYE_ANIMATION_2, 0.5f },
    { CREMIA_EYE_ANIMATION_3, 0.9f },
    { CREMIA_EYE_ANIMATION_4, 0.95f },
    { CREMIA_EYE_ANIMATION_5, 1.0f },
};
EnInvadepohFaceAnimNext D_80B4EB80[1] = { CREMIA_EYE_ANIMATION_1, 1.0f };
EnInvadepohFaceAnimDelayedBranched D_80B4EB88 = {
    { { EN_INVADEPOH_FACE_ANIMATION_TYPE_DELAYED_BRANCHED, &D_80B4EB30 }, ARRAY_COUNT(D_80B4EB60), D_80B4EB60 }, 40, 60
};
EnInvadepohFaceAnimBranched D_80B4EB9C = { { EN_INVADEPOH_FACE_ANIMATION_TYPE_BRANCHED, &D_80B4EB38 },
                                           ARRAY_COUNT(D_80B4EB80),
                                           D_80B4EB80 };
EnInvadepohFaceAnimBranched D_80B4EBAC = { { EN_INVADEPOH_FACE_ANIMATION_TYPE_BRANCHED, &D_80B4EB40 },
                                           ARRAY_COUNT(D_80B4EB80),
                                           D_80B4EB80 };
EnInvadepohFaceAnimBranched D_80B4EBBC = { { EN_INVADEPOH_FACE_ANIMATION_TYPE_BRANCHED, &D_80B4EB48 },
                                           ARRAY_COUNT(D_80B4EB80),
                                           D_80B4EB80 };
EnInvadepohFaceAnimBranched D_80B4EBCC = { { EN_INVADEPOH_FACE_ANIMATION_TYPE_BRANCHED, &D_80B4EB50 },
                                           ARRAY_COUNT(D_80B4EB80),
                                           D_80B4EB80 };
EnInvadepohFaceAnim* D_80B4EBDC[CREMIA_EYE_ANIMATION_MAX] = {
    &D_80B4EB58,           // CREMIA_EYE_ANIMATION_0
    &D_80B4EB88.loop.anim, // CREMIA_EYE_ANIMATION_1
    &D_80B4EB9C.anim,      // CREMIA_EYE_ANIMATION_2
    &D_80B4EBAC.anim,      // CREMIA_EYE_ANIMATION_3
    &D_80B4EBBC.anim,      // CREMIA_EYE_ANIMATION_4
    &D_80B4EBCC.anim,      // CREMIA_EYE_ANIMATION_5
};

typedef enum CremiaMouthAnimation {
    /* 0 */ CREMIA_MOUTH_ANIMATION_0,
    /* 1 */ CREMIA_MOUTH_ANIMATION_MAX
} CremiaMouthAnimation;

s8 D_80B4EBF4[1] = { CREMIA_MOUTH_NORMAL };
EnInvadepohFaceFrames D_80B4EBF8 = { D_80B4EBF4, ARRAY_COUNT(D_80B4EBF4) };
EnInvadepohFaceAnim D_80B4EC00 = { EN_INVADEPOH_FACE_ANIMATION_TYPE_FIXED, &D_80B4EBF8 };
EnInvadepohFaceAnim* D_80B4EC08[CREMIA_MOUTH_ANIMATION_MAX] = {
    &D_80B4EC00, // CREMIA_MOUTH_ANIMATION_0
};

void EnInvadepoh_Interact_UpdateAnimation(EnInvadepohFaceAnimInfo* faceInfo) {
    static EnInvadepohFaceFunc sFaceUpdateFuncs[3] = {
        EnInvadepoh_Interact_UpdateFixedAnim,
        EnInvadepoh_Interact_UpdateBranchedAnim,
        EnInvadepoh_Interact_UpdateDelayedBranchedAnim,
    };

    if ((faceInfo->animations != NULL) && (faceInfo->curAnim != NULL)) {
        sFaceUpdateFuncs[faceInfo->curAnimType](faceInfo, faceInfo->animations);
    }
}

void EnInvadepoh_Interact_Init(EnInvadepohInteractInfo* interactInfo, EnInvadepohFaceAnim** eyeAnimations,
                               s32 curEyeAnim, EnInvadepohFaceAnim** mouthAnimations, s32 curMouthAnim,
                               Vec3s* headRotTarget, s16 headRotMaxStep, f32 headRotStepScale, f32 torsoRotScaleTargetY,
                               f32 torsoRotScaleStepY) {
    Math_Vec3s_Copy(&interactInfo->headRotTarget, headRotTarget);
    interactInfo->headRotMaxStep = headRotMaxStep;
    interactInfo->headRotStepScale = headRotStepScale;
    interactInfo->torsoRotScaleTargetY = torsoRotScaleTargetY;
    interactInfo->torsoRotScaleStepY = torsoRotScaleStepY;
    if (eyeAnimations != NULL) {
        EnInvadepohFaceAnim* faceAnim = eyeAnimations[curEyeAnim];

        interactInfo->eyeAnim.animations = eyeAnimations;
        interactInfo->eyeAnim.curAnimType = faceAnim->type;
        interactInfo->eyeAnim.curAnim = faceAnim;
        interactInfo->eyeAnim.delayTimer = 0;
        interactInfo->eyeAnim.curFrame = 0;
        interactInfo->eyeAnim.curIndex = faceAnim->frames->texIndex[0];
    }
    if (mouthAnimations != NULL) {
        EnInvadepohFaceAnim* faceAnim = mouthAnimations[curMouthAnim];

        interactInfo->mouthAnim.animations = mouthAnimations;
        interactInfo->mouthAnim.curAnimType = faceAnim->type;
        interactInfo->mouthAnim.curAnim = faceAnim;
        interactInfo->mouthAnim.delayTimer = 0;
        interactInfo->mouthAnim.curFrame = 0;
        interactInfo->mouthAnim.curIndex = faceAnim->frames->texIndex[0];
    }
}

void EnInvadepoh_Interact_Update(EnInvadepohInteractInfo* interactInfo) {
    Vec3f scaledRotStep;
    Vec3s rotStep;

    rotStep.x = interactInfo->headRotTarget.x - interactInfo->headRot.x;
    rotStep.y = interactInfo->headRotTarget.y - interactInfo->headRot.y;
    rotStep.z = interactInfo->headRotTarget.z - interactInfo->headRot.z;
    Math_Vec3s_ToVec3f(&scaledRotStep, &rotStep);
    Math_Vec3f_Scale(&scaledRotStep, interactInfo->headRotStepScale);
    Math_Vec3f_ToVec3s(&rotStep, &scaledRotStep);
    rotStep.x = ABS(rotStep.x);
    rotStep.y = ABS(rotStep.y);
    rotStep.z = ABS(rotStep.z);
    rotStep.x = CLAMP_MAX(rotStep.x, interactInfo->headRotMaxStep);
    rotStep.y = CLAMP_MAX(rotStep.y, interactInfo->headRotMaxStep);
    rotStep.z = CLAMP_MAX(rotStep.z, interactInfo->headRotMaxStep);

    Math_ScaledStepToS(&interactInfo->headRot.x, interactInfo->headRotTarget.x, rotStep.x);
    Math_ScaledStepToS(&interactInfo->headRot.y, interactInfo->headRotTarget.y, rotStep.y);
    Math_ScaledStepToS(&interactInfo->headRot.z, interactInfo->headRotTarget.z, rotStep.z);
    Math_StepToF(&interactInfo->torsoRotScaleY, interactInfo->torsoRotScaleTargetY, interactInfo->torsoRotScaleStepY);

    if (interactInfo->torsoRotX != interactInfo->torsoTargetRotX) {
        s16 torsoRotStep = interactInfo->torsoTargetRotX - interactInfo->torsoRotX;

        torsoRotStep *= interactInfo->torsoRotStepScale;
        torsoRotStep = ABS(torsoRotStep);
        torsoRotStep = CLAMP(torsoRotStep, 0x64, interactInfo->torsoRotMaxStep);
        Math_ScaledStepToS(&interactInfo->torsoRotX, interactInfo->torsoTargetRotX, torsoRotStep);
    }
    EnInvadepoh_Interact_UpdateAnimation(&interactInfo->eyeAnim);
    EnInvadepoh_Interact_UpdateAnimation(&interactInfo->mouthAnim);
}

void EnInvadepoh_Ufo_SpawnSparkles(EnInvadepoh* this, PlayState* play, s32 spawnCount) {
    static Color_RGBA8 sLightYellow = { 255, 255, 200, 255 };
    static Color_RGBA8 sGoldenYellow = { 255, 200, 0, 0 };
    s32 i;
    Vec3f pos;
    Vec3f velocity;
    Vec3f accel;
    f32 spawnOffset;
    s16 spawnAngle = 0;

    for (i = 0; i < spawnCount; i++) {
        spawnAngle += (s16)(0x10000 * 1.0f / spawnCount);
        spawnOffset = (Rand_ZeroOne() * 0.5f) + 0.5f;

        pos.x = Math_SinS(spawnAngle) * spawnOffset;
        pos.z = Math_CosS(spawnAngle) * spawnOffset;

        velocity.x = (Rand_ZeroOne() * 16.0f) + (pos.x * 30.0f) - 8.0f;
        velocity.y = -8.0f;
        velocity.z = (Rand_ZeroOne() * 16.0f) + (pos.z * 30.0f) - 8.0f;

        accel.x = velocity.x * -0.025f;
        accel.y = velocity.y * -0.025f;
        accel.z = velocity.z * -0.025f;

        pos.x = (pos.x * 100.0f) + this->actor.world.pos.x;
        pos.y = (Rand_ZeroOne() * 180.0f) + this->actor.world.pos.y - 90.0f;
        pos.z = (pos.z * 100.0f) + this->actor.world.pos.z;
        EffectSsKirakira_SpawnDispersed(play, &pos, &velocity, &accel, &sLightYellow, &sGoldenYellow, 6000, -40);
    }
}

s32 EnInvadepoh_Alien_SpawnWarp(Vec3f* spawnPos) {
    EnInvadepohWarpEffect* warpEffect = sWarpEffects;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sWarpEffects); i++, warpEffect++) {
        if (warpEffect->timer <= 0) {
            warpEffect->type = 0;
            warpEffect->timer = 40;
            Math_Vec3f_Copy(&warpEffect->pos, spawnPos);
            warpEffect->alpha = 0;
            return true;
        }
    }
    return false;
}

void EnInvadepoh_InvasionHandler_WarpFade(EnInvadepohWarpEffect* warpEffect) {
    if (warpEffect->timer > 20) {
        if (warpEffect->alpha < 125) {
            warpEffect->alpha += 10;
        } else {
            warpEffect->alpha = 135;
        }
    } else {
        if (warpEffect->alpha > 13) {
            warpEffect->alpha -= 13;
        } else {
            warpEffect->alpha = 0;
        }
    }
}

s32 EnInvadepoh_InvasionHandler_UpdateWarps(void) {
    static void (*sEnInvadepohWarpUpdateFuncs[1])(EnInvadepohWarpEffect*) = { EnInvadepoh_InvasionHandler_WarpFade };
    s32 warpActive = false;
    s32 i;
    EnInvadepohWarpEffect* warpEffect;

    for (i = 0, warpEffect = sWarpEffects; i < 10; i++, warpEffect++) {
        if (warpEffect->timer > 0) {
            sEnInvadepohWarpUpdateFuncs[warpEffect->type](warpEffect);
            warpActive = true;
            warpEffect->timer--;
        }
    }
    return warpActive;
}

void EnInvadepoh_InvasionHandler_Init(EnInvadepoh* this, PlayState* play) {
    s32 alienCount;
    s32 pathIndex;

    this->actor.flags |= ACTOR_FLAG_20;
    pathIndex = EN_INVADEPOH_GET_PATH(&this->actor);

    for (alienCount = 1; alienCount < 8; alienCount++) {
        Path* path = &play->setupPathList[pathIndex];

        pathIndex = path->additionalPathIndex;
        if (pathIndex == EN_INVADEPOH_PATH_INDEX_NONE) {
            break;
        }
    }

    this->alienCount = alienCount;
    EnInvadepoh_InvasionHandler_CheckState(this, play);
    EnInvadepoh_InvasionHandler_SetCutscenes(this);
    Actor_ChangeCategory(play, &play->actorCtx, &this->actor, ACTORCAT_SWITCH);

    if (sEventState == EN_INVADEPOH_EVENT_WAIT) {
        EnInvadepoh_InvasionHandler_SetupWait(this);
    } else if (sEventState == EN_INVADEPOH_EVENT_ACTIVE) {
        if (CURRENT_TIME < CLOCK_TIME(2, 31)) {
            EnInvadepoh_InvasionHandler_SetupWait(this);
        } else {
            EnInvadepoh_InvasionHandler_SpawnUfo(this, play);
            EnInvadepoh_InvasionHandler_SpawnAliens(this, play);
            SEQCMD_PLAY_SEQUENCE(SEQ_PLAYER_BGM_MAIN, 0, NA_BGM_ALIEN_INVASION | SEQ_FLAG_ASYNC);
            EnInvadepoh_InvasionHandler_SetupInvasion(this);
        }
    } else if (sEventState == EN_INVADEPOH_EVENT_CLEAR) {
        if (gSaveContext.save.entrance == ENTRANCE(ROMANI_RANCH, 6)) {
            EnInvadepoh_InvasionHandler_SetupRomaniReward(this);
        } else if (gSaveContext.save.entrance == ENTRANCE(ROMANI_RANCH, 7)) {
            EnInvadepoh_InvasionHandler_SetupGoodEnd(this);
        } else {
            EnInvadepoh_InvasionHandler_SetupGoodEnd(this);
        }
    } else if (sEventState == EN_INVADEPOH_EVENT_FAILED) {
        EnInvadepoh_InvasionHandler_SetupBadEnd(this);
    }
}

InitChainEntry sAlienInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 500, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 600, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};

void EnInvadepoh_Alien_Init(EnInvadepoh* this, PlayState* play) {
    s32 pad;

    Actor_ProcessInitChain(&this->actor, sAlienInitChain);
    Collider_InitCylinder(play, &this->collider);
    ActorShape_Init(&this->actor.shape, 6800.0f, ActorShadow_DrawWhiteCircle, 150.0f);
    this->actor.shape.shadowAlpha = 140;
    this->actor.flags = ACTOR_FLAG_10 | ACTOR_FLAG_IGNORE_QUAKE | ACTOR_FLAG_80000000;

    if (EN_INVADEPOH_GET_TYPE(&this->actor) == EN_INVADEPOH_TYPE_ALIEN_ABDUCTOR) {
        this->actor.update = EnInvadepoh_AlienAbductor_WaitForObject;
        this->actor.world.pos.y = this->actor.home.pos.y + 150.0f;
    } else {
        this->actor.update = EnInvadepoh_Alien_WaitForObject;
        Collider_SetCylinder(play, &this->collider, &this->actor, &sAlienCylinderInit);
        this->actor.colChkInfo.mass = 40;
    }

    this->objectSlot = Object_GetSlot(&play->objectCtx, OBJECT_UCH);
    if (this->objectSlot <= OBJECT_SLOT_NONE) {
        Actor_Kill(&this->actor);
    }
}

InitChainEntry sCowInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};

void EnInvadepoh_Cow_Init(EnInvadepoh* this, PlayState* play) {
    Actor_ProcessInitChain(&this->actor, sCowInitChain);
    this->actor.update = EnInvadepoh_Cow_WaitForObject;
    Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EN_INVADEPOH, 0.0f, 0.0f, 0.0f, 0, 0, 0,
                       EN_INVADEPOH_PARAMS(0, EN_INVADEPOH_TYPE_COW_TAIL, 0));

    this->objectSlot = Object_GetSlot(&play->objectCtx, OBJECT_COW);
    if (this->objectSlot <= OBJECT_SLOT_NONE) {
        Actor_Kill(&this->actor);
    }
}

InitChainEntry sCowTailInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};

void EnInvadepoh_CowTail_Init(EnInvadepoh* this, PlayState* play) {
    Actor_ProcessInitChain(&this->actor, sCowTailInitChain);
    this->actor.update = EnInvadepoh_CowTail_WaitForObject;

    this->objectSlot = Object_GetSlot(&play->objectCtx, OBJECT_COW);
    if (this->objectSlot <= OBJECT_SLOT_NONE) {
        Actor_Kill(&this->actor);
    }
}

InitChainEntry sRomaniInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE), ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_CONTINUE),  ICHAIN_F32(targetArrowOffset, 1500, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};

void EnInvadepoh_Romani_Init(EnInvadepoh* this, PlayState* play) {
    s32 pad;
    s32 romaniType = EN_INVADEPOH_GET_TYPE(&this->actor);

    Actor_ProcessInitChain(&this->actor, sRomaniInitChain);

    if ((romaniType == EN_INVADEPOH_TYPE_ROMANI_NIGHT_1) || (romaniType == EN_INVADEPOH_TYPE_ROMANI_NIGHT_3)) {
        this->actor.targetMode = TARGET_MODE_3;
    } else {
        this->actor.targetMode = TARGET_MODE_6;
    }

    Actor_ChangeCategory(play, &play->actorCtx, &this->actor, ACTORCAT_NPC);
    Collider_InitCylinder(play, &this->collider);
    if (romaniType != EN_INVADEPOH_TYPE_ROMANI_ABDUCTED) {
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 18.0f);
        Collider_SetCylinder(play, &this->collider, &this->actor, &sHumanCylinderInit);
        this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    }

    if (romaniType == EN_INVADEPOH_TYPE_ROMANI_ABDUCTED) {
        this->actor.update = EnInvadepoh_AbductedRomani_WaitForObject;
    } else if (romaniType == EN_INVADEPOH_TYPE_ROMANI_SILENT) {
        this->actor.update = EnInvadepoh_SilentRomani_WaitForObject;
        this->actor.flags = ACTOR_FLAG_10 | ACTOR_FLAG_FRIENDLY | ACTOR_FLAG_TARGETABLE;
    } else if (romaniType == EN_INVADEPOH_TYPE_ROMANI_NIGHT_1) {
        this->actor.update = EnInvadepoh_Night1Romani_WaitForObject;
    } else if (romaniType == EN_INVADEPOH_TYPE_ROMANI_BARN) {
        this->actor.update = EnInvadepoh_BarnRomani_WaitForObject;
    } else if (romaniType == EN_INVADEPOH_TYPE_ROMANI_REWARD) {
        this->actor.update = EnInvadepoh_RewardRomani_WaitForObject;
    } else {
        this->actor.update = EnInvadepoh_Night3Romani_WaitForObject;
    }

    this->objectSlot = Object_GetSlot(&play->objectCtx, OBJECT_MA1);
    if (this->objectSlot <= OBJECT_SLOT_NONE) {
        Actor_Kill(&this->actor);
    }

    if (romaniType == EN_INVADEPOH_TYPE_ROMANI_SILENT) {
        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_DEFENDED_AGAINST_THEM)) {
            Actor_Kill(&this->actor);
        }
    } else if (romaniType == EN_INVADEPOH_TYPE_ROMANI_NIGHT_1) {
        if ((CURRENT_TIME < CLOCK_TIME(6, 00)) && (CURRENT_TIME >= CLOCK_TIME(2, 15))) {
            Actor_Kill(&this->actor);
        }
    } else if (romaniType == EN_INVADEPOH_TYPE_ROMANI_BARN) {
        // nothing
    } else if (romaniType == EN_INVADEPOH_TYPE_ROMANI_REWARD) {
        if (gSaveContext.save.entrance != ENTRANCE(ROMANI_RANCH, 6)) {
            Actor_Kill(&this->actor);
        }
    } else if (romaniType == EN_INVADEPOH_TYPE_ROMANI_NIGHT_3) {
        if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_DEFENDED_AGAINST_THEM)) {
            Actor_Kill(&this->actor);
        }
        sRomani = this;
    }
}

InitChainEntry sUfoInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE), ICHAIN_F32(uncullZoneScale, 1000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1000, ICHAIN_CONTINUE), ICHAIN_VEC3S(shape, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(terminalVelocity, -100, ICHAIN_CONTINUE),   ICHAIN_VEC3F_DIV1000(scale, 1000, ICHAIN_STOP),
};

void EnInvadepoh_Ufo_Init(EnInvadepoh* this, PlayState* play) {
    Actor_ProcessInitChain(&this->actor, sUfoInitChain);
    this->actor.update = EnInvadepoh_Ufo_Update;
    this->actor.draw = EnInvadepoh_Ufo_Draw;
    Actor_ChangeCategory(play, &play->actorCtx, &this->actor, ACTORCAT_NPC);
    if ((sEventState == EN_INVADEPOH_EVENT_WAIT) || (CURRENT_TIME < CLOCK_TIME(2, 31))) {
        this->actor.world.pos.x += sUfoSpawnOffset.x;
        this->actor.world.pos.y += sUfoSpawnOffset.y + 3000.0f;
        this->actor.world.pos.z += sUfoSpawnOffset.z;
        EnInvadepoh_Ufo_SetupDescend(this);
    } else if (sEventState == EN_INVADEPOH_EVENT_ACTIVE) {
        this->actor.world.pos.y += 1500.0f;
        EnInvadepoh_Ufo_SetupAboveBarn(this);
    } else {
        Actor_Kill(&this->actor);
    }
}

InitChainEntry sDogInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 2000, ICHAIN_CONTINUE),  ICHAIN_F32(uncullZoneScale, 50, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 50, ICHAIN_CONTINUE),   ICHAIN_F32(gravity, -3, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, TARGET_MODE_4, ICHAIN_CONTINUE), ICHAIN_VEC3F_DIV1000(scale, 7, ICHAIN_STOP),
};

void EnInvadepoh_Dog_Init(EnInvadepoh* this, PlayState* play) {
    s32 pad;

    Actor_ProcessInitChain(&this->actor, sDogInitChain);
    this->actor.update = EnInvadepoh_Dog_WaitForObject;
    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, &this->actor, &sDogCylinderInit);
    this->actor.colChkInfo.mass = 80;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 24.0f);

    this->objectSlot = Object_GetSlot(&play->objectCtx, OBJECT_DOG);
    if (this->objectSlot <= OBJECT_SLOT_NONE) {
        Actor_Kill(&this->actor);
    }
}

InitChainEntry sCremiaInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE), ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 150, ICHAIN_CONTINUE),  ICHAIN_F32(targetArrowOffset, 1500, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, TARGET_MODE_3, ICHAIN_CONTINUE), ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};

void EnInvadepoh_Cremia_Init(EnInvadepoh* this, PlayState* play) {
    s32 pad;

    Actor_ProcessInitChain(&this->actor, sCremiaInitChain);
    this->actor.update = EnInvadepoh_Night3Cremia_WaitForObject;
    Actor_ChangeCategory(play, &play->actorCtx, &this->actor, ACTORCAT_NPC);
    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, &this->actor, &sHumanCylinderInit);
    this->actor.colChkInfo.mass = MASS_HEAVY;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 18.0f);

    this->objectSlot = Object_GetSlot(&play->objectCtx, OBJECT_MA2);
    if (this->objectSlot <= OBJECT_SLOT_NONE) {
        Actor_Kill(&this->actor);
    }

    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_DEFENDED_AGAINST_THEM)) {
        Actor_Kill(&this->actor);
    }

    sCremia = this;
}

void EnInvadepoh_Init(Actor* thisx, PlayState* play2) {
    static EnInvadepohInitFunc sInitFuncs[EN_INVADEPOH_TYPE_MAX] = {
        EnInvadepoh_InvasionHandler_Init, // EN_INVADEPOH_TYPE_INVASION_HANDLER
        EnInvadepoh_Alien_Init,           // EN_INVADEPOH_TYPE_ALIEN
        EnInvadepoh_Cow_Init,             // EN_INVADEPOH_TYPE_COW
        EnInvadepoh_CowTail_Init,         // EN_INVADEPOH_TYPE_COW_TAIL
        EnInvadepoh_Romani_Init,          // EN_INVADEPOH_TYPE_ROMANI_ABDUCTED
        EnInvadepoh_Romani_Init,          // EN_INVADEPOH_TYPE_ROMANI_SILENT
        EnInvadepoh_Ufo_Init,             // EN_INVADEPOH_TYPE_UFO
        EnInvadepoh_Romani_Init,          // EN_INVADEPOH_TYPE_ROMANI_NIGHT_1
        EnInvadepoh_Romani_Init,          // EN_INVADEPOH_TYPE_ROMANI_BARN
        EnInvadepoh_Romani_Init,          // EN_INVADEPOH_TYPE_ROMANI_REWARD
        EnInvadepoh_Dog_Init,             // EN_INVADEPOH_TYPE_DOG
        EnInvadepoh_Cremia_Init,          // EN_INVADEPOH_TYPE_CREMIA_NIGHT_3
        EnInvadepoh_Romani_Init,          // EN_INVADEPOH_TYPE_ROMANI_NIGHT_3
        EnInvadepoh_Alien_Init,           // EN_INVADEPOH_TYPE_ALIEN_ABDUCTOR
    };
    EnInvadepoh* this = THIS;
    PlayState* play = play2;

    sInitFuncs[EN_INVADEPOH_GET_TYPE(&this->actor)](this, play);
}

void EnInvadepoh_InvasionHandler_Destroy(EnInvadepoh* this, PlayState* play) {
}

void EnInvadepoh_Alien_Destroy(EnInvadepoh* this, PlayState* play) {
    s32 pad;
    s32 index = EN_INVADEPOH_GET_INDEX(&this->actor);

    Collider_DestroyCylinder(play, &this->collider);
    sAliens[index] = NULL;
}

void EnInvadepoh_Cow_Destroy(EnInvadepoh* this, PlayState* play) {
    if (this->actor.parent != NULL) {
        this->actor.parent->child = NULL;
    }
    if (this->actor.child != NULL) {
        this->actor.child->parent = NULL;
    }
}

void EnInvadepoh_CowTail_Destroy(EnInvadepoh* this, PlayState* play) {
    if (this->actor.parent != NULL) {
        this->actor.parent->child = NULL;
    }
}

void EnInvadepoh_Romani_Destroy(EnInvadepoh* this, PlayState* play) {
    Collider_DestroyCylinder(play, &this->collider);
}

void EnInvadepoh_Ufo_Destroy(EnInvadepoh* this, PlayState* play) {
    sUfo = NULL;
}

void EnInvadepoh_Dog_Destroy(EnInvadepoh* this, PlayState* play) {
    Collider_DestroyCylinder(play, &this->collider);
}

void EnInvadepoh_Cremia_Destroy(EnInvadepoh* this, PlayState* play) {
    Collider_DestroyCylinder(play, &this->collider);
    sCremia = NULL;
}

void EnInvadepoh_Night3Romani_Destroy(EnInvadepoh* this, PlayState* play) {
    Collider_DestroyCylinder(play, &this->collider);
    sRomani = NULL;
}

void EnInvadepoh_AlienAbductor_Destroy(EnInvadepoh* this, PlayState* play) {
    Actor* thisx = &this->actor;

    Collider_DestroyCylinder(play, &this->collider);

    if (thisx->child != NULL) {
        thisx->child->parent = NULL;
    }
}

void EnInvadepoh_Destroy(Actor* thisx, PlayState* play2) {
    static EnInvadepohDestroyFunc sDestroyFuncs[EN_INVADEPOH_TYPE_MAX] = {
        EnInvadepoh_InvasionHandler_Destroy, // EN_INVADEPOH_TYPE_INVASION_HANDLER
        EnInvadepoh_Alien_Destroy,           // EN_INVADEPOH_TYPE_ALIEN
        EnInvadepoh_Cow_Destroy,             // EN_INVADEPOH_TYPE_COW
        EnInvadepoh_CowTail_Destroy,         // EN_INVADEPOH_TYPE_COW_TAIL
        EnInvadepoh_Romani_Destroy,          // EN_INVADEPOH_TYPE_ROMANI_ABDUCTED
        EnInvadepoh_Romani_Destroy,          // EN_INVADEPOH_TYPE_ROMANI_SILENT
        EnInvadepoh_Ufo_Destroy,             // EN_INVADEPOH_TYPE_UFO
        EnInvadepoh_Romani_Destroy,          // EN_INVADEPOH_TYPE_ROMANI_NIGHT_1
        EnInvadepoh_Romani_Destroy,          // EN_INVADEPOH_TYPE_ROMANI_BARN
        EnInvadepoh_Romani_Destroy,          // EN_INVADEPOH_TYPE_ROMANI_REWARD
        EnInvadepoh_Dog_Destroy,             // EN_INVADEPOH_TYPE_DOG
        EnInvadepoh_Cremia_Destroy,          // EN_INVADEPOH_TYPE_CREMIA_NIGHT_3
        EnInvadepoh_Night3Romani_Destroy,    // EN_INVADEPOH_TYPE_ROMANI_NIGHT_3
        EnInvadepoh_AlienAbductor_Destroy,   // EN_INVADEPOH_TYPE_ALIEN_ABDUCTOR
    };
    EnInvadepoh* this = THIS;
    PlayState* play = play2;

    sDestroyFuncs[EN_INVADEPOH_GET_TYPE(&this->actor)](this, play);
}

void EnInvadepoh_InvasionHandler_SetupWait(EnInvadepoh* this) {
    sEventState = EN_INVADEPOH_EVENT_WAIT;
    this->actionFunc = EnInvadepoh_InvasionHandler_Wait;
}

void EnInvadepoh_InvasionHandler_Wait(EnInvadepoh* this, PlayState* play) {
    if ((CURRENT_TIME < CLOCK_TIME(6, 00)) && (CURRENT_TIME >= CLOCK_TIME(2, 30))) {
        EnInvadepoh_InvasionHandler_SpawnUfo(this, play);
        EnInvadepoh_InvasionHandler_SpawnAliens(this, play);
        EnInvadepoh_InvasionHandler_SetupQueueInvasionCs(this);
    }
}

void EnInvadepoh_InvasionHandler_SetupQueueInvasionCs(EnInvadepoh* this) {
    sEventState = EN_INVADEPOH_EVENT_ACTIVE;
    this->timer = 2;
    this->actionFunc = EnInvadepoh_InvasionHandler_QueueInvasionCs;
}

void EnInvadepoh_InvasionHandler_QueueInvasionCs(EnInvadepoh* this, PlayState* play) {
    if (this->timer > 0) {
        this->timer--;
    } else if (CutsceneManager_IsNext(sCsIdList[0])) {
        CutsceneManager_StartWithPlayerCs(sCsIdList[0], &this->actor);
        EnInvadepoh_InvasionHandler_SetupInvasionCs(this);
    } else {
        CutsceneManager_Queue(sCsIdList[0]);
    }
}

void EnInvadepoh_InvasionHandler_SetupInvasionCs(EnInvadepoh* this) {
    sEventState = EN_INVADEPOH_EVENT_ACTIVE;
    this->timer = 160;
    this->actionFunc = EnInvadepoh_InvasionHandler_InvasionCs;
}

void EnInvadepoh_InvasionHandler_InvasionCs(EnInvadepoh* this, PlayState* play) {
    static s16 sAlienSpawnTimes[] = {
        130, 125, 115, 100, 80, 78, 76, 74,
    };
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sAlienSpawnTimes); i++) {
        if (this->timer == sAlienSpawnTimes[i]) {
            sAlienStateFlags[i] |= EN_INVADEPOH_ALIEN_ACTIVE;
        }
    }

    this->timer--;
    if (this->timer <= 0) {
        CutsceneManager_Stop(sCsIdList[0]);
        SEQCMD_PLAY_SEQUENCE(SEQ_PLAYER_BGM_MAIN, 0, NA_BGM_ALIEN_INVASION | SEQ_FLAG_ASYNC);
        EnInvadepoh_InvasionHandler_SetupInvasion(this);
    }
}

void EnInvadepoh_InvasionHandler_SetupInvasion(EnInvadepoh* this) {
    sEventState = EN_INVADEPOH_EVENT_ACTIVE;
    this->actionFunc = EnInvadepoh_InvasionHandler_Invasion;
}

void EnInvadepoh_InvasionHandler_Invasion(EnInvadepoh* this, PlayState* play) {
    if ((CURRENT_TIME < CLOCK_TIME(6, 00)) && (CURRENT_TIME >= CLOCK_TIME(5, 15))) {
        SET_WEEKEVENTREG(WEEKEVENTREG_DEFENDED_AGAINST_THEM);
        EnInvadepoh_InvasionHandler_SetupQueueVictoryCs(this);
    } else {
        s32 i;

        EnInvadepoh_InvasionHandler_SetClosestAlien(this);

        for (i = 0; i < this->alienCount; i++) {
            if ((sAliens[i] != NULL) && (sAliens[i]->pathCompleted)) {
                EnInvadepoh_InvasionHandler_SetupFailure(this);
                break;
            }
        }
    }
}

void EnInvadepoh_InvasionHandler_SetupQueueVictoryCs(EnInvadepoh* this) {
    sEventState = EN_INVADEPOH_EVENT_CLEAR;
    this->actionFunc = EnInvadepoh_InvasionHandler_QueueVictoryCs;
}

void EnInvadepoh_InvasionHandler_QueueVictoryCs(EnInvadepoh* this, PlayState* play) {
    if (CutsceneManager_IsNext(sCsIdList[1])) {
        CutsceneManager_StartWithPlayerCs(sCsIdList[1], &this->actor);
        EnInvadepoh_InvasionHandler_SetupVictoryCs(this);
    } else {
        CutsceneManager_Queue(sCsIdList[1]);
    }
}

void EnInvadepoh_InvasionHandler_SetupVictoryCs(EnInvadepoh* this) {
    sEventState = EN_INVADEPOH_EVENT_CLEAR;
    this->timer = 110;
    this->actionFunc = EnInvadepoh_InvasionHandler_VictoryCs;
}

void EnInvadepoh_InvasionHandler_VictoryCs(EnInvadepoh* this, PlayState* play) {
    if (this->timer == 100) {
        Audio_PlayFanfare(NA_BGM_CLEAR_EVENT);
    }

    this->timer--;
    if (this->timer <= 0) {
        play->nextEntrance = ENTRANCE(ROMANI_RANCH, 6);
        gSaveContext.nextCutsceneIndex = 0;
        play->transitionTrigger = TRANS_TRIGGER_START;
        play->transitionType = TRANS_TYPE_73;
        gSaveContext.nextTransitionType = TRANS_TYPE_72;
        D_801BDAA0 = true;
        gHorseIsMounted = false;
        EnInvadepoh_InvasionHandler_SetupGoodEnd(this);
    }
}

void EnInvadepoh_InvasionHandler_SetupRomaniReward(EnInvadepoh* this) {
    sEventState = EN_INVADEPOH_EVENT_CLEAR;
    this->actionFunc = EnInvadepoh_InvasionHandler_RomaniReward;
}

void EnInvadepoh_InvasionHandler_RomaniReward(EnInvadepoh* this, PlayState* play) {
    if (sRewardFinished) {
        play->nextEntrance = ENTRANCE(ROMANI_RANCH, 7);
        gSaveContext.nextCutsceneIndex = 0;
        play->transitionTrigger = TRANS_TRIGGER_START;
        play->transitionType = TRANS_TYPE_72;
        gSaveContext.nextTransitionType = TRANS_TYPE_72;
        EnInvadepoh_InvasionHandler_SetupGoodEnd(this);
    }
}

void EnInvadepoh_InvasionHandler_SetupGoodEnd(EnInvadepoh* this) {
    sEventState = EN_INVADEPOH_EVENT_CLEAR;
    this->actionFunc = EnInvadepoh_InvasionHandler_GoodEnd;
}

void EnInvadepoh_InvasionHandler_GoodEnd(EnInvadepoh* this, PlayState* play) {
}

void EnInvadepoh_InvasionHandler_SetupFailure(EnInvadepoh* this) {
    sEventState = EN_INVADEPOH_EVENT_FAILED;
    this->actionFunc = EnInvadepoh_InvasionHandler_Failure;
}

void EnInvadepoh_InvasionHandler_Failure(EnInvadepoh* this, PlayState* play) {
    play->nextEntrance = ENTRANCE(ROMANI_RANCH, 0);
    gSaveContext.nextCutsceneIndex = 0xFFF3;
    play->transitionTrigger = TRANS_TRIGGER_START;
    play->transitionType = TRANS_TYPE_72;
    gSaveContext.nextTransitionType = TRANS_TYPE_72;
    SET_WEEKEVENTREG(WEEKEVENTREG_89_10);
    EnInvadepoh_InvasionHandler_SetupBadEnd(this);
}

void EnInvadepoh_InvasionHandler_SetupBadEnd(EnInvadepoh* this) {
    sEventState = EN_INVADEPOH_EVENT_FAILED;
    this->actionFunc = EnInvadepoh_InvasionHandler_BadEnd;
}

void EnInvadepoh_InvasionHandler_BadEnd(EnInvadepoh* this, PlayState* play) {
}

void EnInvadepoh_InvasionHandler_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;

    this->actionFunc(this, play);

    this->actor.draw = EnInvadepoh_InvasionHandler_UpdateWarps() ? EnInvadepoh_InvasionHandler_Draw : NULL;
}

void EnInvadepoh_Alien_SetupWaitForEvent(EnInvadepoh* this) {
    this->collider.base.atFlags &= ~AT_ON;
    this->collider.base.acFlags &= ~AC_ON;
    this->collider.base.ocFlags1 &= ~OC1_ON;
    this->actor.flags &= ~ACTOR_FLAG_80000000;
    this->alpha = 0;
    this->actor.draw = NULL;
    this->shouldDraw = false;
    this->shouldDrawDeathFlash = false;
    this->eyeBeamAlpha = 0;
    this->actionFunc = EnInvadepoh_Alien_WaitForEvent;
}

void EnInvadepoh_Alien_WaitForEvent(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_Alien_SetProgress(this);
    EnInvadepoh_Alien_ApplyProgress(this, play);
    EnInvadepoh_Alien_TurnToPath(this, 0x320, 0);

    if (sAlienStateFlags[EN_INVADEPOH_GET_INDEX(&this->actor)] & EN_INVADEPOH_ALIEN_ACTIVE) {
        Actor_SetScale(&this->actor, 0.01f);
        EnInvadepoh_SnapToFloor(this);
        EnInvadepoh_Alien_SpawnWarp(&this->actor.world.pos);
        EnInvadepoh_Alien_SetupWarpIn(this);
    }
}

void EnInvadepoh_Alien_SetupWaitToRespawn(EnInvadepoh* this) {
    this->collider.base.atFlags &= ~AT_ON;
    this->collider.base.acFlags &= ~AC_ON;
    this->collider.base.ocFlags1 &= ~OC1_ON;
    this->actor.flags &= ~ACTOR_FLAG_80000000;
    this->alpha = 0;
    this->actor.draw = NULL;
    this->shouldDraw = false;
    this->shouldDrawDeathFlash = false;
    this->eyeBeamAlpha = 0;
    this->actionFunc = EnInvadepoh_Invade_WaitToRespawn;
}

void EnInvadepoh_Invade_WaitToRespawn(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_Alien_SetProgress(this);
    EnInvadepoh_Alien_ApplyProgress(this, play);
    EnInvadepoh_Alien_TurnToPath(this, 0x320, 0);

    if (this->pathProgress > 0.0f) {
        Actor_SetScale(&this->actor, 0.01f);
        EnInvadepoh_SnapToFloor(this);
        EnInvadepoh_Alien_SpawnWarp(&this->actor.world.pos);
        EnInvadepoh_Alien_SetupWarpIn(this);
    }
}

void EnInvadepoh_Alien_SetupWarpIn(EnInvadepoh* this) {
    Animation_MorphToLoop(&this->skelAnime, &gAlienFloatAnim, -6.0f);
    this->collider.base.atFlags &= ~AT_ON;
    this->collider.base.acFlags &= ~AC_ON;
    this->collider.base.ocFlags1 &= ~OC1_ON;
    this->alpha = 0;
    this->actor.draw = EnInvadepoh_Alien_Draw;
    this->shouldDraw = true;
    this->shouldDrawDeathFlash = false;
    this->eyeBeamAlpha = 0;
    this->actor.flags |= ACTOR_FLAG_80000000;
    this->actionFunc = EnInvadepoh_Alien_WarpIn;
}

void EnInvadepoh_Alien_WarpIn(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_Alien_SetProgress(this);
    EnInvadepoh_Alien_ApplyProgress(this, play);
    EnInvadepoh_Alien_TurnToPath(this, 0x320, 0);
    Actor_PlaySfx_Flagged(&this->actor, NA_SE_EN_FOLLOWERS_BEAM_PRE - SFX_FLAG);

    if (this->pathProgress >= 0.9999f) {
        this->pathCompleted = true;
    }

    if (this->alpha >= 249) {
        this->alpha = 255;
    } else {
        this->alpha += 6;
    }

    if (this->alpha > 128) {
        this->collider.base.atFlags |= AT_ON;
        this->collider.base.acFlags |= AC_ON;
        this->collider.base.ocFlags1 |= OC1_ON;
    }

    if (this->alpha == 255) {
        if (this->eyeBeamAlpha >= 245) {
            this->eyeBeamAlpha = 255;
            EnInvadepoh_Alien_SetupAttack(this);
        } else {
            this->eyeBeamAlpha += 10;
        }
    }
}

void EnInvadepoh_Alien_SetupAttack(EnInvadepoh* this) {
    if (this->skelAnime.animation != &gAlienFloatAnim) {
        Animation_MorphToLoop(&this->skelAnime, &gAlienFloatAnim, -6.0f);
    }
    this->collider.base.atFlags |= AT_ON;
    this->collider.base.acFlags |= AC_ON;
    this->collider.base.ocFlags1 |= OC1_ON;
    this->alpha = 255;
    this->actor.draw = EnInvadepoh_Alien_Draw;
    this->shouldDraw = true;
    this->shouldDrawDeathFlash = false;
    this->eyeBeamAlpha = 255;
    this->actor.flags |= ACTOR_FLAG_80000000;
    this->actionFunc = EnInvadepoh_Alien_Attack;
}

void EnInvadepoh_Alien_Attack(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_Alien_SetProgress(this);
    EnInvadepoh_Alien_ApplyProgress(this, play);
    EnInvadepoh_Alien_TurnToPath(this, 0x320, 0);
    Actor_PlaySfx_Flagged(&this->actor, NA_SE_EN_FOLLOWERS_BEAM_PRE - SFX_FLAG);
    if (this->pathProgress >= 0.9999f) {
        this->pathCompleted = true;
    }
}

void EnInvadepoh_Alien_SetupHitstun(EnInvadepoh* this) {
    this->collider.base.atFlags &= ~AT_ON;
    this->collider.base.acFlags &= ~AC_ON;
    this->collider.base.ocFlags1 |= OC1_ON;
    Animation_PlayLoop(&this->skelAnime, &gAlienJerkingAnim);
    Actor_SetColorFilter(&this->actor, COLORFILTER_COLORFLAG_RED, 255, COLORFILTER_BUFFLAG_OPA, 16);
    this->alpha = 255;
    this->actor.draw = EnInvadepoh_Alien_Draw;
    this->shouldDraw = true;
    this->shouldDrawDeathFlash = false;
    this->eyeBeamAlpha = 0;
    this->timer = 8;
    this->frameCounter = 0;
    this->actor.flags |= ACTOR_FLAG_80000000;
    this->actionFunc = EnInvadepoh_Alien_Hitstun;
}

void EnInvadepoh_Alien_Hitstun(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_Alien_Knockback(this, play);

    this->timer--;
    if (this->timer <= 0) {
        EnInvadepoh_Alien_SetupDeath(this);
    }
}

void EnInvadepoh_Alien_SetupDeath(EnInvadepoh* this) {
    this->collider.base.atFlags &= ~AT_ON;
    this->collider.base.acFlags &= ~AC_ON;
    this->collider.base.ocFlags1 &= ~OC1_ON;
    Animation_PlayLoop(&this->skelAnime, &gAlienDeathAnim);
    this->actor.flags &= ~ACTOR_FLAG_TARGETABLE;
    this->timer = 10;
    this->alpha = 255;
    this->actor.draw = EnInvadepoh_Alien_Draw;
    this->shouldDraw = true;
    this->shouldDrawDeathFlash = false;
    this->eyeBeamAlpha = 255;
    this->actor.flags |= ACTOR_FLAG_80000000;
    this->actionFunc = EnInvadepoh_Alien_Death;
}

void EnInvadepoh_Alien_Death(EnInvadepoh* this, PlayState* play) {
    static Vec3f sDeathScales[] = {
        { 0.01f, 0.01f, 0.01f }, { 0.02f, 0.01f, 0.005f }, { -0.01f, 0.0f, 0.0f },
        { 0.01f, 0.01f, 0.01f }, { 0.005f, 0.01f, 0.02f },
    };
    static Vec3f sDeathFlashScales[] = {
        { 0.0005f, 0.027999999f, 0.01f }, { -0.01f, 0.0f, 0.0f }, { -0.01f, 0.0f, 0.0f },
        { 0.016f, 0.0004f, 0.01f },       { -0.01f, 0.0f, 0.0f }, { 0.0005f, 0.0005f, 0.0005f },
        { 0.0002f, 0.0002f, 0.0002f },
    };
    Vec3f* deathScale;

    EnInvadepoh_Alien_EmptyFunc(this);

    if (this->frameCounter < 5) {
        deathScale = &sDeathScales[this->frameCounter];
        if (deathScale->x > 0.0f) {
            this->shouldDraw = true;
            this->eyeBeamAlpha = 255;
            Math_Vec3f_Copy(&this->actor.scale, deathScale);
        } else {
            this->shouldDraw = false;
            this->eyeBeamAlpha = 0;
        }
    } else {
        this->shouldDraw = false;
        this->eyeBeamAlpha = 0;
    }

    if ((this->frameCounter >= 2) && (this->frameCounter < 9)) {
        deathScale = &sDeathFlashScales[this->frameCounter - 2];
        if (deathScale->x > 0.0f) {
            this->shouldDrawDeathFlash = true;
            Math_Vec3f_Copy(&this->deathFlashScale, deathScale);
        } else {
            this->shouldDrawDeathFlash = false;
        }
    } else {
        this->shouldDrawDeathFlash = false;
    }

    this->frameCounter++;

    if (this->timer == 8) {
        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, this->actor.world.pos.x, this->actor.world.pos.y - 10.0f,
                    this->actor.world.pos.z, 0, 0, 3, CLEAR_TAG_PARAMS(CLEAR_TAG_SMOKE));
    }

    if (this->timer == 8) {
        Enemy_StartFinishingBlow(play, &this->actor);
    }

    this->timer--;
    if (this->timer <= 0) {
        EnInvadepoh_Alien_SetRespawnTime(EN_INVADEPOH_GET_INDEX(&this->actor));
        EnInvadepoh_Alien_AddKill();
        Item_DropCollectible(play, &this->actor.world.pos, ITEM00_ARROWS_30);
        EnInvadepoh_Alien_SetupWaitToRespawn(this);
    }
}

void EnInvadepoh_Alien_WaitForObject(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;

    if (Object_IsLoaded(&play->objectCtx, this->objectSlot)) {
        this->actor.objectSlot = this->objectSlot;
        Actor_SetObjectDependency(play, &this->actor);
        EnInvadepoh_Alien_SetTexAnim();
        this->actor.update = EnInvadepoh_Alien_Update;
        SkelAnime_InitFlex(play, &this->skelAnime, &gAlienSkel, &gAlienFloatAnim, this->jointTable, this->morphTable,
                           ALIEN_LIMB_MAX);
        this->skelAnime.curFrame = (EN_INVADEPOH_GET_INDEX(&this->actor)) * this->skelAnime.endFrame / 8.0f;
        EnInvadepoh_Alien_SetupPath(this, play);
        EnInvadepoh_Alien_SetProgress(this);
        EnInvadepoh_Alien_ApplyProgress(this, play);
        EnInvadepoh_SetYawAlongPath(this);
        EnInvadepoh_SnapToFloor(this);

        if ((sEventState == EN_INVADEPOH_EVENT_WAIT) || (CURRENT_TIME < CLOCK_TIME(2, 31))) {
            EnInvadepoh_Alien_SetupWaitForEvent(this);
        } else if (sEventState == EN_INVADEPOH_EVENT_ACTIVE) {
            if (this->pathProgress >= 0.0001f) {
                EnInvadepoh_Alien_SetupAttack(this);
            } else {
                EnInvadepoh_Alien_SetupWarpIn(this);
            }
        } else {
            Actor_Kill(&this->actor);
        }
    }
}

void EnInvadepoh_Alien_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;

    if (sEventState == EN_INVADEPOH_EVENT_CLEAR) {
        if ((this->actionFunc == EnInvadepoh_Alien_Attack) || (this->actionFunc == EnInvadepoh_Alien_WarpIn)) {
            thisx->speed = 0.0f;
            thisx->velocity.y = 0.0f;
            thisx->gravity = 0.0f;
            EnInvadepoh_Alien_SetupHitstun(this);
        } else if ((this->actionFunc == EnInvadepoh_Invade_WaitToRespawn) ||
                   (this->actionFunc == EnInvadepoh_Alien_WaitForEvent)) {
            Actor_Kill(thisx);
            return;
        }
    } else if (this->collider.base.acFlags & AC_HIT) {
        Actor* hitbox = this->collider.base.ac;

        thisx->speed = hitbox->speed * 0.5f;
        thisx->speed = CLAMP(thisx->speed, -60.0f, 60.0f);

        thisx->world.rot.y = hitbox->world.rot.y;
        thisx->gravity = 0.0f;

        thisx->velocity.y = hitbox->velocity.y * 0.5f;
        thisx->velocity.y = CLAMP(thisx->velocity.y, -30.0f, 30.0f);

        SoundSource_PlaySfxAtFixedWorldPos(play, &thisx->world.pos, 50, NA_SE_EN_INVADER_DEAD);
        EnInvadepoh_Alien_SetupHitstun(this);
    }

    this->actionFunc(this, play);

    if (thisx->draw != NULL) {
        this->isAnimFinished = SkelAnime_Update(&this->skelAnime);
    }

    Collider_UpdateCylinder(thisx, &this->collider);

    if (this->collider.base.atFlags & AT_ON) {
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.base);
    } else {
        this->collider.base.atFlags &= ~AT_HIT;
    }

    if (this->collider.base.acFlags & AC_ON) {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
    } else {
        this->collider.base.acFlags &= ~AC_HIT;
    }

    if (this->collider.base.ocFlags1 & OC1_ON) {
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    } else {
        this->collider.base.ocFlags1 &= ~OC1_HIT;
    }
}

void EnInvadepoh_Cow_WaitForObject(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;

    if (Object_IsLoaded(&play->objectCtx, this->objectSlot)) {
        this->actor.objectSlot = this->objectSlot;
        Actor_SetObjectDependency(play, &this->actor);
        this->actor.update = EnInvadepoh_Cow_Update;
        this->actor.draw = EnInvadepoh_Cow_Draw;
        SkelAnime_InitFlex(play, &this->skelAnime, &gCowSkel, NULL, this->jointTable, this->morphTable, COW_LIMB_MAX);
        Animation_PlayLoop(&this->skelAnime, &gCowMooAnim);
    }
}

void EnInvadepoh_Cow_Update(Actor* thisx, PlayState* play2) {
    static s16 D_80B4EDC0[3] = { -0x1F40, -0x1770, -0x2AF8 };
    PlayState* play = play2;
    EnInvadepoh* this = THIS;
    s32 index;

    if ((sUfo == NULL) || (this->actor.parent == NULL)) {
        Actor_Kill(&this->actor);
        return;
    }

    index = EN_INVADEPOH_GET_INDEX(&this->actor);
    SkelAnime_Update(&this->skelAnime);
    Math_ScaledStepToS(&this->actor.shape.rot.x, D_80B4EDC0[index], 0x32);

    if (this->actor.child != NULL) {
        s32 pad;
        MtxF tailMtxF;

        Matrix_Push();
        Matrix_SetTranslateRotateYXZ(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z,
                                     &this->actor.shape.rot);
        Matrix_Translate(0.0f, 57.0f, -36.0f, MTXMODE_APPLY);
        Matrix_RotateXS(this->actor.shape.rot.x * -0.7f, MTXMODE_APPLY);
        Matrix_RotateZS(this->actor.shape.rot.z * -0.7f, MTXMODE_APPLY);
        Matrix_MultZero(&this->actor.child->world.pos);
        Matrix_Get(&tailMtxF);
        Matrix_MtxFToYXZRot(&tailMtxF, &this->actor.child->shape.rot, false);
        Matrix_Pop();
    }
}

void EnInvadepoh_CowTail_WaitForObject(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;

    if (Object_IsLoaded(&play->objectCtx, this->objectSlot)) {
        this->actor.objectSlot = this->objectSlot;
        Actor_SetObjectDependency(play, &this->actor);
        this->actor.update = EnInvadepoh_CowTail_Update;
        this->actor.draw = EnInvadepoh_CowTail_Draw;
        SkelAnime_InitFlex(play, &this->skelAnime, &gCowTailSkel, NULL, this->jointTable, this->morphTable,
                           COW_TAIL_LIMB_MAX);
        Animation_PlayLoop(&this->skelAnime, &gCowTailSwishAnim);
    }
}

void EnInvadepoh_CowTail_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;

    if ((sUfo == NULL) || (this->actor.parent == NULL)) {
        Actor_Kill(&this->actor);
    } else {
        SkelAnime_Update(&this->skelAnime);
    }
}

void EnInvadepoh_AbductedRomani_SetupWait(EnInvadepoh* this) {
    this->timer = 40;
    Animation_MorphToLoop(&this->skelAnime, &gRomaniLookAroundAnim, -10.0f);
    this->actor.draw = NULL;
    this->actionFunc = EnInvadepoh_AbductedRomani_Wait;
}

void EnInvadepoh_AbductedRomani_Wait(EnInvadepoh* this, PlayState* play) {
    this->timer--;
    if (this->timer <= 0) {
        EnInvadepoh_Romani_StartTextBox(this, play, 0x332F); // Romani's scream when abducted
        this->actor.draw = EnInvadepoh_Romani_Draw;
        EnInvadepoh_AbductedRomani_SetupYell(this);
    }
}

void EnInvadepoh_AbductedRomani_SetupYell(EnInvadepoh* this) {
    this->timer = 60;
    Animation_MorphToLoop(&this->skelAnime, &gRomaniLookAroundAnim, -10.0f);
    this->actor.draw = EnInvadepoh_Romani_Draw;
    this->actionFunc = EnInvadepoh_AbductedRomani_Yell;
}

void EnInvadepoh_AbductedRomani_Yell(EnInvadepoh* this, PlayState* play) {
    if (this->timer == 20) {
        EnInvadepohInteractInfo* interactInfo = &this->interactInfo;

        interactInfo->headRotTarget.x = 0x7D0;
        interactInfo->headRotTarget.y = 0;
        interactInfo->headRotTarget.z = 0;
        interactInfo->headRotStepScale = 0.1f;
        interactInfo->headRotMaxStep = 0x3E8;
    }

    this->timer--;
    if (this->timer <= 0) {
        EnInvadepoh_AbductedRomani_SetupStruggle(this);
    }
}

void EnInvadepoh_AbductedRomani_SetupStruggle(EnInvadepoh* this) {
    this->interactInfo.headRotTarget.x = 0xBB8;
    this->interactInfo.headRotTarget.y = 0;
    this->interactInfo.headRotTarget.z = 0;
    this->interactInfo.headRotStepScale = 0.24f;
    this->interactInfo.headRotMaxStep = 0xBB8;
    this->interactInfo.torsoTargetRotX = 0x3A98;
    this->interactInfo.torsoRotStepScale = 0.1f;
    this->interactInfo.torsoRotMaxStep = 0x7D0;
    this->timer = 50;

    Animation_Change(&this->skelAnime, &gRomaniRunAnim, 2.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -5.0f);
    this->actor.draw = EnInvadepoh_Romani_Draw;
    this->actionFunc = EnInvadepoh_AbductedRomani_Struggle;
}

void EnInvadepoh_AbductedRomani_Struggle(EnInvadepoh* this, PlayState* play) {
    if (this->timer == 40) {
        this->interactInfo.headRotTarget.y = 0x1B58;
    } else if (this->timer == 30) {
        this->interactInfo.headRotTarget.y = -0x1B58;
    } else if (this->timer == 20) {
        this->interactInfo.headRotTarget.y = 0x1B58;
    } else if (this->timer == 10) {
        this->interactInfo.headRotTarget.y = 0;
    }

    this->timer--;
    if (this->timer <= 0) {
        EnInvadepoh_AbductedRomani_SetupEnd(this);
    }
}

void EnInvadepoh_AbductedRomani_SetupEnd(EnInvadepoh* this) {
    this->interactInfo.headRotTarget.x = 0;
    this->interactInfo.headRotTarget.y = 0;
    this->interactInfo.headRotTarget.z = 0;
    this->interactInfo.headRotStepScale = 0.24f;
    this->interactInfo.headRotMaxStep = 0x1388;
    this->interactInfo.torsoTargetRotX = 0;
    this->interactInfo.torsoRotStepScale = 0.28f;
    this->interactInfo.torsoRotMaxStep = 0x1B58;

    Animation_MorphToPlayOnce(&this->skelAnime, &gRomaniIdleAnim, -10.0f);
    this->actor.draw = EnInvadepoh_Romani_Draw;
    this->actionFunc = EnInvadepoh_AbductedRomani_End;
}

void EnInvadepoh_AbductedRomani_End(EnInvadepoh* this, PlayState* play) {
}

void EnInvadepoh_AbductedRomani_WaitForObject(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;
    s32 pad;

    if (Object_IsLoaded(&play->objectCtx, this->objectSlot)) {
        this->actor.objectSlot = this->objectSlot;
        Actor_SetObjectDependency(play, &this->actor);
        EnInvadepoh_Romani_DesegmentTextures();
        this->actor.update = EnInvadepoh_AbductedRomani_Update;
        SkelAnime_InitFlex(play, &this->skelAnime, &gRomaniSkel, &gRomaniIdleAnim, this->jointTable, this->morphTable,
                           ROMANI_LIMB_MAX);
        EnInvadepoh_Interact_Init(&this->interactInfo, D_80B4EA90, ROMANI_EYE_ANIMATION_6, D_80B4EB00,
                                  ROMANI_MOUTH_ANIMATION_2, &gZeroVec3s, 0x1388, 0.05f, 0.3f, 0.12f);
        Animation_PlayLoop(&this->skelAnime, &gRomaniIdleAnim);
        EnInvadepoh_AbductedRomani_SetupWait(this);
    }
}

void EnInvadepoh_AbductedRomani_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;
    EnInvadepohInteractInfo* interactInfo = &this->interactInfo;

    if (this->actor.parent == NULL) {
        Actor_Kill(&this->actor);
        return;
    }

    this->actionFunc(this, play);

    SkelAnime_Update(&this->skelAnime);
    EnInvadepoh_Interact_Update(&this->interactInfo);

    if (interactInfo->torsoRotX != 0) {
        this->actor.shape.rot.x = -interactInfo->torsoRotX;
    }
}

void EnInvadepoh_SilentRomani_SetupWalk(EnInvadepoh* this) {
    static s16 D_80B4EDC8[4] = { -0x708, -0x3E8, 0, 0x7D0 };
    EnInvadepohInteractInfo* interactInfo = &this->interactInfo;

    this->timer = Rand_S16Offset(150, 250);
    interactInfo->headRotTarget.x = D_80B4EDC8[Rand_Next() >> 0x1E];
    interactInfo->headRotTarget.y = 0;
    interactInfo->headRotTarget.z = 0;
    interactInfo->headRotStepScale = 0.1f;
    interactInfo->headRotMaxStep = 0x320;
    Animation_MorphToLoop(&this->skelAnime, &gRomaniWalkAnim, -10.0f);
    this->actionFunc = EnInvadepoh_SilentRomani_Walk;
}

void EnInvadepoh_SilentRomani_Walk(EnInvadepoh* this, PlayState* play) {
    s32 pad;

    Math_StepToF(&this->actor.speed, 1.6f, 0.1f);

    if (EnInvadepoh_Romani_MoveAlongPath(this, play, this->actor.speed, 50.0f)) {
        EnInvadepoh_SilentRomani_SetNextPathPoint(this);
        this->shapeAngularVelocityY = 0xC8;
        this->actor.speed *= 0.25f;
    } else {
        Math_StepToS(&this->shapeAngularVelocityY, 0x7D0, 0x46);
    }

    EnInvadepoh_Romani_TurnToPath(this, 6, this->shapeAngularVelocityY, 0x46);

    if (CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40) &&
        (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 7.0f))) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_ROMANI_WALK);
    }

    if (this->timer > 0) {
        this->timer--;
    } else {
        EnInvadepoh_SilentRomani_SetupIdle(this);
    }
}

void EnInvadepoh_SilentRomani_SetupIdle(EnInvadepoh* this) {
    EnInvadepohInteractInfo* interactInfo = &this->interactInfo;
    f32 rand = Rand_ZeroOne();

    this->timer = Rand_S16Offset(150, 150);

    if (rand < 0.5f) {
        this->silentRomaniState = 0;
        Math_Vec3s_Copy(&interactInfo->headRotTarget, &gZeroVec3s);
        interactInfo->headRotStepScale = 0.1f;
        interactInfo->headRotMaxStep = 0x3E8;
    } else if (rand < 0.75f) {
        this->silentRomaniState = 1;
        interactInfo->headRotTarget.x = Rand_S16Offset(0, 0x7D0);
        interactInfo->headRotTarget.y = 0;
        interactInfo->headRotTarget.z = 0;
        interactInfo->headRotStepScale = 0.06f;
        interactInfo->headRotMaxStep = 0x3E8;
    } else if (rand < 0.8f) {
        this->silentRomaniState = 2;
        interactInfo->headRotTarget.x = Rand_S16Offset(-0x7D0, 0x7D0);
        interactInfo->headRotTarget.y = 0;
        interactInfo->headRotTarget.z = 0;
        interactInfo->headRotStepScale = 0.05f;
        interactInfo->headRotMaxStep = 0x3E8;
    } else {
        this->silentRomaniState = 3;
        interactInfo->headRotTarget.x = 0;
        interactInfo->headRotTarget.y = 0;
        interactInfo->headRotTarget.z = Rand_S16Offset(-0x9C4, 0x1388);
        interactInfo->headRotStepScale = 0.04f;
        interactInfo->headRotMaxStep = 0x3E8;
    }

    Animation_MorphToLoop(&this->skelAnime, &gRomaniIdleAnim, -10.0f);
    this->actionFunc = EnInvadepoh_SilentRomani_Idle;
}

void EnInvadepoh_SilentRomani_Idle(EnInvadepoh* this, PlayState* play) {
    EnInvadepohInteractInfo* interactInfo = &this->interactInfo;

    Math_StepToF(&this->actor.speed, 0.0f, 0.2f);

    if (EnInvadepoh_Romani_MoveAlongPath(this, play, this->actor.speed, 50.0f)) {
        EnInvadepoh_SilentRomani_SetNextPathPoint(this);
    }

    if (this->silentRomaniState == 0) {
        if ((this->actor.xzDistToPlayer < 350.0f) && (play->gameplayFrames & 0x60)) {
            Player* player = GET_PLAYER(play);
            s16 angleToPlayer = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos) * 0.85f;

            interactInfo->headRotTarget.x = CLAMP((s16)(angleToPlayer - this->actor.shape.rot.x), -0x9C4, 0x9C4);

            angleToPlayer = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
            interactInfo->headRotTarget.y = CLAMP((s16)(angleToPlayer * 0.7f), -0x1F40, 0x1F40);
        }
    } else {
        interactInfo->headRotTarget.x = 0;
        interactInfo->headRotTarget.y = 0;
    }

    if (this->timer > 0) {
        s32 timerMod32 = (u32)this->timer % 0x20;

        if ((timerMod32 == 0) && (Rand_ZeroOne() < 0.3f)) {
            s32 next_silentRomaniState = (s32)Rand_Next() % 4;

            if (next_silentRomaniState != this->silentRomaniState) {
                this->silentRomaniState = next_silentRomaniState;
                if (this->silentRomaniState == 0) {
                    Math_Vec3s_Copy(&interactInfo->headRotTarget, &gZeroVec3s);
                    interactInfo->headRotStepScale = 0.07f;
                } else if (this->silentRomaniState == 1) {
                    interactInfo->headRotTarget.x = Rand_S16Offset(0x3E8, 0x3E8);
                    interactInfo->headRotTarget.y = Rand_S16Offset(-0x3E8, 0x7D0);
                    interactInfo->headRotTarget.z = Rand_S16Offset(-0x320, 0x640);
                    interactInfo->headRotStepScale = 0.06f;
                } else if (this->silentRomaniState == 2) {
                    interactInfo->headRotTarget.x = Rand_S16Offset(-0x7D0, 0x3E8);
                    interactInfo->headRotTarget.y = Rand_S16Offset(-0x3E8, 0x7D0);
                    interactInfo->headRotTarget.z = Rand_S16Offset(-0x320, 0x640);
                    interactInfo->headRotStepScale = 0.05f;
                } else {
                    interactInfo->headRotTarget.x = Rand_S16Offset(-0x3E8, 0x7D0);
                    interactInfo->headRotTarget.y = Rand_S16Offset(-0x7D0, 0xFA0);
                    interactInfo->headRotTarget.z = Rand_S16Offset(-0x7D0, 0xFA0);
                    interactInfo->headRotStepScale = 0.04f;
                }
            }
        }
        this->timer--;
        return;
    }

    EnInvadepoh_SilentRomani_SetupWalk(this);
}

void EnInvadepoh_SilentRomani_SetupTalk(EnInvadepoh* this) {
    EnInvadepohInteractInfo* interactInfo = &this->interactInfo;

    this->actor.speed = 0.0f;
    Animation_MorphToLoop(&this->skelAnime, &gRomaniIdleAnim, -10.0f);
    this->shapeAngularVelocityY = 0;
    interactInfo->headRotStepScale = 0.05f;
    interactInfo->headRotMaxStep = 0x4B0;
    this->actionFunc = EnInvadepoh_SilentRomani_Talk;
}

void EnInvadepoh_SilentRomani_Talk(EnInvadepoh* this, PlayState* play) {
    EnInvadepohInteractInfo* interactInfo = &this->interactInfo;
    Player* player = GET_PLAYER(play);
    s16 angleToPlayer;

    Math_StepToS(&this->shapeAngularVelocityY, 0x7D0, 0x32);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 6, this->shapeAngularVelocityY, 0x23);

    angleToPlayer = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos) * 0.85f;
    interactInfo->headRotTarget.x = CLAMP((s16)(angleToPlayer - this->actor.shape.rot.x), -0xBB8, 0xBB8);

    angleToPlayer = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
    interactInfo->headRotTarget.y = CLAMP((s16)(angleToPlayer * 0.7f), -0x1F40, 0x1F40);

    if (Actor_TextboxIsClosing(&this->actor, play)) {
        EnInvadepoh_SilentRomani_SetupIdle(this);
    }
}

void EnInvadepoh_SilentRomani_WaitForObject(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;

    if (Object_IsLoaded(&play->objectCtx, this->objectSlot)) {
        this->actor.objectSlot = this->objectSlot;
        Actor_SetObjectDependency(play, &this->actor);
        EnInvadepoh_Romani_DesegmentTextures();
        this->actor.update = EnInvadepoh_SilentRomani_Update;
        this->actor.draw = EnInvadepoh_Romani_Draw;
        this->actor.textId = 0x3330;
        SkelAnime_InitFlex(play, &this->skelAnime, &gRomaniSkel, &gRomaniIdleAnim, this->jointTable, this->morphTable,
                           ROMANI_LIMB_MAX);
        EnInvadepoh_Interact_Init(&this->interactInfo, D_80B4EA90, ROMANI_EYE_ANIMATION_6, D_80B4EB00,
                                  ROMANI_MOUTH_ANIMATION_2, &gZeroVec3s, 100, 0.03f, 0.3f, 0.03f);
        EnInvadepoh_SilentRomani_SetupPath(this, play);
        EnInvadepoh_SetPosToPathPoint(this, 0);
        func_800B4AEC(play, &this->actor, 50.0f);
        EnInvadepoh_SnapToFloor(this);
        EnInvadepoh_SilentRomani_SetupWalk(this);
    }
}

void EnInvadepoh_SilentRomani_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;
    s32 inUncullRange = CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40);
    s32 talkAccepted = Actor_TalkOfferAccepted(&this->actor, &play->state);

    if (talkAccepted) {
        Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_ROMANI);
        EnInvadepoh_SilentRomani_SetupTalk(this);
    }

    this->actionFunc(this, play);

    if (inUncullRange) {
        SkelAnime_Update(&this->skelAnime);
        EnInvadepoh_Interact_Update(&this->interactInfo);
        if ((this->actionFunc != EnInvadepoh_SilentRomani_Talk) && !talkAccepted && this->actor.isLockedOn) {
            Actor_OfferTalk(&this->actor, play, 100.0f);
        }
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    }
}

void EnInvadepoh_Ufo_SetupDescend(EnInvadepoh* this) {
    this->actor.gravity = -15.0f;
    this->ufoPulseScale = 0.0f;
    this->ufoPulseScaleTarget = 1.0f;
    this->ufoPulseScaleSpeed = 0.0f;
    this->ufoPulsePhaseVelocity = 0;
    this->actionFunc = EnInvadepoh_Ufo_Descend;
}

void EnInvadepoh_Ufo_Descend(EnInvadepoh* this, PlayState* play) {
    s32 pad;
    f32 distToTargetY;

    Actor_UpdateVelocityWithGravity(&this->actor);
    this->actor.velocity.y *= 0.97f;
    distToTargetY = Math_SmoothStepToF(&this->actor.world.pos.y, this->actor.home.pos.y + sUfoSpawnOffset.y + 300.0f,
                                       0.7f, fabsf(this->actor.velocity.y), 1.0f);
    Actor_PlaySfx_Flagged(&this->actor, NA_SE_EV_UFO_APPEAR - SFX_FLAG);

    if (fabsf(distToTargetY) < 1.0f) {
        EnInvadepoh_Ufo_SpawnSparkles(this, play, 50);
        EnInvadepoh_Ufo_SetupHover(this);
    }
}

void EnInvadepoh_Ufo_SetupHover(EnInvadepoh* this) {
    this->actor.velocity.y *= 0.1f;
    this->timer = 20;
    this->ufoPulseScaleTarget = 0.3f;
    this->ufoPulseScaleSpeed = 0.03f;
    this->ufoPulsePhaseVelocity = 0xBB8;
    this->actionFunc = EnInvadepoh_Ufo_Hover;
}

void EnInvadepoh_Ufo_Hover(EnInvadepoh* this, PlayState* play) {
    f32 hoverY = this->actor.home.pos.y + sUfoSpawnOffset.y + 300.0f;

    if (this->actor.world.pos.y < hoverY) {
        this->actor.gravity = 3.0f;
    } else {
        this->actor.gravity = -2.0f;
    }

    this->actor.velocity.y *= 0.96f;
    Actor_MoveWithGravity(&this->actor);
    Actor_PlaySfx_Flagged(&this->actor, NA_SE_EV_UFO_APPEAR - SFX_FLAG);

    this->timer--;
    if (this->timer <= 0) {
        EnInvadepoh_Ufo_SetupSpawnAliens(this);
    }
}

void EnInvadepoh_Ufo_SetupSpawnAliens(EnInvadepoh* this) {
    this->timer = 120;
    this->ufoPulseScaleTarget = 0.2f;
    this->ufoPulseScaleSpeed = 0.01f;
    this->actor.gravity = 33.0f;
    this->ufoPulsePhaseVelocity = 0xBB8;
    this->ufoTargetPosIndex = 0;
    this->frameCounter = 0;
    this->actionFunc = EnInvadepoh_Ufo_SpawnAliens;
}

void EnInvadepoh_Ufo_SpawnAliens(EnInvadepoh* this, PlayState* play) {
    static Vec3f sUfoTargetOffsets[] = {
        { -1813.0f, 374.0f, 1900.0f }, { 2198.0f, 153.0f, 3365.0f }, { -1434.0f, 262.0f, 3365.0f },
        { -393.0f, 396.0f, 1084.0f },  { 0.0f, 1500.0f, 0.0f },
    };
    s32 pad;
    Vec3f ufoTargetPos;
    s32 pad2;

    if (this->frameCounter < 25) {
        this->frameCounter++;
    } else {
        this->frameCounter = 0;
        this->ufoTargetPosIndex++;
        this->ufoTargetPosIndex = CLAMP_MAX(this->ufoTargetPosIndex, ARRAY_COUNT(sUfoTargetOffsets) - 1);
        this->actor.gravity = 33.0f;
        EnInvadepoh_Ufo_SpawnSparkles(this, play, 20);
    }

    Math_Vec3f_Sum(&sUfoTargetOffsets[this->ufoTargetPosIndex], &this->actor.home.pos, &ufoTargetPos);

    if (Math3D_Vec3fDistSq(&this->actor.world.pos, &ufoTargetPos) < SQ(400.0f)) {
        this->actor.speed *= 0.8f;
    } else {
        Math_StepToF(&this->actor.speed, 170.0f, 21.0f);
        this->actor.speed *= 0.98f;
    }

    if (EnInvadepoh_StepTowardXZ(&this->actor.world.pos.x, &this->actor.world.pos.z, ufoTargetPos.x, ufoTargetPos.z,
                                 this->actor.speed)) {
        this->actor.speed = 0.0f;
    }

    if (ufoTargetPos.y < this->actor.world.pos.y) {
        Math_StepToF(&this->actor.gravity, -12.0f, 7.0f);
    } else {
        Math_StepToF(&this->actor.gravity, 5.0f, 4.0f);
    }

    this->actor.velocity.y += this->actor.gravity;
    this->actor.velocity.y *= 0.97f;
    this->actor.world.pos.y += this->actor.velocity.y;

    Actor_PlaySfx_Flagged(&this->actor, NA_SE_EV_UFO_APPEAR - SFX_FLAG);

    if (this->timer > 0) {
        this->timer--;
    } else {
        EnInvadepoh_Ufo_SetupAboveBarn(this);
    }
}

void EnInvadepoh_Ufo_SetupAboveBarn(EnInvadepoh* this) {
    this->ufoPulseScaleTarget = 0.2f;
    this->ufoPulseScaleSpeed = 0.01f;
    this->ufoPulsePhaseVelocity = 0xBB8;
    this->actor.velocity.y *= 0.8f;
    this->actionFunc = EnInvadepoh_Ufo_AboveBarn;
}

void EnInvadepoh_Ufo_AboveBarn(EnInvadepoh* this, PlayState* play) {
    s32 pad;
    Vec3f ufoTargetPos;

    ufoTargetPos.x = this->actor.home.pos.x;
    ufoTargetPos.y = this->actor.home.pos.y + 1500.0f;
    ufoTargetPos.z = this->actor.home.pos.z;
    Math_SmoothStepToS(&this->actor.world.rot.y, Math_Vec3f_Yaw(&this->actor.world.pos, &ufoTargetPos), 0xA, 0xBB8,
                       0x64);

    if ((play->gameplayFrames % 0x40) < 14) {
        Math_StepToF(&this->actor.speed, 5.0f, 1.0f);
    } else {
        this->actor.speed *= 0.97f;
    }

    this->actor.gravity = (ufoTargetPos.y < this->actor.world.pos.y) ? -0.5f : 2.0f;
    this->actor.velocity.y *= 0.97f;

    Actor_MoveWithGravity(&this->actor);

    if (sEventState == EN_INVADEPOH_EVENT_CLEAR) {
        EnInvadepoh_Ufo_SetupLeaveBarn(this);
    }
}

void EnInvadepoh_Ufo_SetupCircle(EnInvadepoh* this) {
    this->ufoPulseScaleTarget = 0.2f;
    this->ufoPulseScaleSpeed = 0.01f;
    this->actor.gravity = -1.5f;
    this->ufoPulsePhaseVelocity = 0xBB8;
    this->timer = 35;
    this->actionFunc = EnInvadepoh_Ufo_Circle;
}

void EnInvadepoh_Ufo_Circle(EnInvadepoh* this, PlayState* play) {
    s32 pad;
    Vec3f ufoTargetPos;

    ufoTargetPos.x = this->actor.home.pos.x + sUfoSpawnOffset.x;
    ufoTargetPos.y = this->actor.home.pos.y + sUfoSpawnOffset.y + 400.0f;
    ufoTargetPos.z = this->actor.home.pos.z + sUfoSpawnOffset.z;
    Math_SmoothStepToS(&this->actor.world.rot.y, Math_Vec3f_Yaw(&this->actor.world.pos, &ufoTargetPos), 4, 0x1F40,
                       0x64);
    Math_StepToF(&this->actor.speed, 70.0f, 3.0f);
    this->actor.gravity = (ufoTargetPos.y < this->actor.world.pos.y) ? -2.0f : 2.0f;
    this->actor.velocity.y *= 0.97f;

    Actor_MoveWithGravity(&this->actor);

    if (this->timer > 0) {
        this->timer--;
    } else {
        EnInvadepoh_Ufo_SetupFlee(this);
    }
}

void EnInvadepoh_Ufo_SetupFlee(EnInvadepoh* this) {
    this->ufoPulseScaleTarget = 0.2f;
    this->ufoPulseScaleSpeed = 0.01f;
    this->actor.gravity = 1.0f;
    this->ufoPulsePhaseVelocity = 0xBB8;
    this->timer = 60;
    this->actionFunc = EnInvadepoh_Ufo_Flee;
}

void EnInvadepoh_Ufo_Flee(EnInvadepoh* this, PlayState* play) {
    Math_StepToF(&this->actor.speed, 150.0f, 4.0f);
    this->actor.velocity.y *= 0.95f;
    Actor_MoveWithGravity(&this->actor);

    if (this->timer > 0) {
        this->timer--;
    } else {
        Actor_Kill(&this->actor);
    }
}

void EnInvadepoh_Ufo_SetupLeaveBarn(EnInvadepoh* this) {
    this->timer = 40;
    this->ufoPulseScaleTarget = 0.2f;
    this->ufoPulseScaleSpeed = 0.01f;
    this->actor.speed = 0.0f;
    this->ufoPulsePhaseVelocity = 0xBB8;
    this->actionFunc = EnInvadepoh_Ufo_LeaveBarn;
}

void EnInvadepoh_Ufo_LeaveBarn(EnInvadepoh* this, PlayState* play) {
    s32 pad;
    Vec3f ufoTargetPos;

    ufoTargetPos.x = this->actor.home.pos.x;
    ufoTargetPos.y = this->actor.home.pos.y + 800.0f;
    ufoTargetPos.z = this->actor.home.pos.z;
    Math_SmoothStepToS(&this->actor.world.rot.y, Math_Vec3f_Yaw(&this->actor.world.pos, &ufoTargetPos), 4, 0x1F40,
                       0x64);
    Math_StepToF(&this->actor.speed, 30.0f, 3.0f);
    this->actor.velocity.y *= 0.98f;
    this->actor.gravity = (ufoTargetPos.y < this->actor.world.pos.y) ? -0.5f : 2.0f;
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 0.0f, 0.0f, 0.0f, UPDBGCHECKINFO_FLAG_4);

    if (this->timer > 0) {
        this->timer--;
    } else {
        EnInvadepoh_Ufo_SetupCircle(this);
    }
}

void EnInvadepoh_Ufo_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;
    f32 scaleMod;

    this->actionFunc(this, play);

    this->ufoPulsePhase += this->ufoPulsePhaseVelocity;
    Math_StepToF(&this->ufoPulseScale, this->ufoPulseScaleTarget, this->ufoPulseScaleSpeed);

    scaleMod = 1.0f + (Math_SinS(this->ufoPulsePhase) * this->ufoPulseScale);
    Actor_SetScale(&this->actor, 0.27f * scaleMod);
    Math_StepToS(&this->angularVelocity, 0x258, 8);
    this->actor.world.rot.y += this->angularVelocity;
    this->angle += 0x258;
}

void EnInvadepoh_Night1Romani_SetupWalk(EnInvadepoh* this) {
    EnInvadepohInteractInfo* interactInfo = &this->interactInfo;

    Animation_MorphToLoop(&this->skelAnime, &gRomaniWalkAnim, -10.0f);
    interactInfo->headRotTarget.x = 0;
    interactInfo->headRotTarget.y = 0;
    interactInfo->headRotTarget.z = 0;
    interactInfo->headRotStepScale = 0.1f;
    interactInfo->headRotMaxStep = 0x320;
    this->actionFunc = EnInvadepoh_Night1Romani_Walk;
}

void EnInvadepoh_Night1Romani_Walk(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_Night1Romani_SetProgress(this);
    EnInvadepoh_Night1Romani_MoveAlongPathTimed(this, play);
    EnInvadepoh_Romani_TurnToPath(this, 6, 0x7D0, 0x64);

    if ((this->currentPoint == 0) || ((this->currentPoint + 1) == this->endPoint)) {
        if (!this->doorOpened) {
            s32 trueTimeSpeed = Environment_GetTimeSpeed(play);
            s32 doorTimer = trueTimeSpeed;

            if (trueTimeSpeed > 0) {
                // This is really dividing by trueTimeSpeed, but matching requires writing like this
                doorTimer = (R_TIME_SPEED * -16.0f / doorTimer) - 0.5f;
                this->doorOpened = EnInvadepoh_Romani_OpenDoor(this, play, SQ(80.0f), doorTimer);
            }
        }
        this->actor.flags &= ~(ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY);
    } else {
        this->doorOpened = false;
        this->actor.flags |= (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY);
    }

    if (CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40) &&
        (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 7.0f))) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_ROMANI_WALK);
    }

    if (this->pathProgress >= 0.9999f) {
        Actor_Kill(&this->actor);
    }
}

void EnInvadepoh_Night1Romani_SetupTalk(EnInvadepoh* this) {
    this->interactInfo.headRotStepScale = 0.08f;
    this->interactInfo.headRotMaxStep = 0x7D0;
    this->shapeAngularVelocityY = 0;
    Animation_MorphToLoop(&this->skelAnime, &gRomaniIdleAnim, -10.0f);
    this->actionFunc = EnInvadepoh_Night1Romani_Talk;
}

void EnInvadepoh_Night1Romani_Talk(EnInvadepoh* this, PlayState* play) {
    EnInvadepohInteractInfo* interactInfo = &this->interactInfo;
    Player* player = GET_PLAYER(play);
    s16 angleToPlayer;

    Math_StepToS(&this->shapeAngularVelocityY, 0x7D0, 0x1F4);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, this->shapeAngularVelocityY, 0x28);
    angleToPlayer = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos) * 0.85f;
    interactInfo->headRotTarget.x = CLAMP((s16)(angleToPlayer - this->actor.shape.rot.x), -0xBB8, 0xBB8);

    angleToPlayer = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
    interactInfo->headRotTarget.y = CLAMP((s16)(angleToPlayer * 0.7f), -0x1F40, 0x1F40);

    if (Actor_TextboxIsClosing(&this->actor, play)) {
        if (this->actor.textId == 0x332D) {
            SET_WEEKEVENTREG(WEEKEVENTREG_54_10);
            this->actor.textId = 0x332E;
        }
        EnInvadepoh_Night1Romani_SetupWalk(this);
    }
}

void EnInvadepoh_Night1Romani_WaitForObject(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;
    s32 pad;
    s32 currentTime;

    if (Object_IsLoaded(&play->objectCtx, this->objectSlot)) {
        currentTime = CURRENT_TIME;
        this->actor.objectSlot = this->objectSlot;
        Actor_SetObjectDependency(play, &this->actor);
        EnInvadepoh_Romani_DesegmentTextures();
        SkelAnime_InitFlex(play, &this->skelAnime, &gRomaniSkel, &gRomaniWalkAnim, this->jointTable, this->morphTable,
                           ROMANI_LIMB_MAX);
        EnInvadepoh_Interact_Init(&this->interactInfo, D_80B4EA90, ROMANI_EYE_ANIMATION_1, D_80B4EB00,
                                  ROMANI_MOUTH_ANIMATION_1, &gZeroVec3s, 0x64, 0.03f, 0.3f, 0.03f);
        EnInvadepoh_Night1Romani_SetupPath(this, play);
        EnInvadepoh_Night1Romani_SetProgress(this);
        EnInvadepoh_Night1Romani_MoveAlongPathTimed(this, play);
        EnInvadepoh_SetYawAlongPath(this);
        EnInvadepoh_SnapToFloor(this);

        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_PROMISED_TO_HELP_WITH_THEM)) {
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_54_10)) {
                this->actor.textId = 0x332E;
            } else {
                this->actor.textId = 0x332D;
            }
        } else {
            this->actor.textId = 0x332C;
        }

        if ((currentTime >= CLOCK_TIME(18, 00)) || (currentTime < CLOCK_TIME(2, 00))) {
            this->actor.update = EnInvadepoh_Night1Romani_WaitForEvent;
            this->actor.draw = NULL;
        } else if ((currentTime < CLOCK_TIME(6, 00)) && (currentTime >= CLOCK_TIME(2, 00)) &&
                   (currentTime < CLOCK_TIME(2, 15))) {
            this->actor.update = EnInvadepoh_Night1Romani_Update;
            this->actor.draw = EnInvadepoh_Romani_Draw;
            EnInvadepoh_Night1Romani_SetupWalk(this);
        } else {
            Actor_Kill(&this->actor);
        }
    }
}

void EnInvadepoh_Night1Romani_WaitForEvent(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;

    if ((CURRENT_TIME < CLOCK_TIME(6, 00)) && (CURRENT_TIME >= CLOCK_TIME(2, 00))) {
        this->actor.update = EnInvadepoh_Night1Romani_Update;
        this->actor.draw = EnInvadepoh_Romani_Draw;
        EnInvadepoh_Night1Romani_SetupWalk(this);
    }
}

void EnInvadepoh_Night1Romani_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;
    s32 inUncullRange = CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40);
    s32 talkAccepted = Actor_TalkOfferAccepted(&this->actor, &play->state);

    if (talkAccepted) {
        Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_ROMANI);
        EnInvadepoh_Night1Romani_SetupTalk(this);
    }

    this->actionFunc(this, play);

    if (inUncullRange && (this->actor.update != NULL)) {
        SkelAnime_Update(&this->skelAnime);
        EnInvadepoh_Interact_Update(&this->interactInfo);
        if ((this->actionFunc != EnInvadepoh_Night1Romani_Talk) && !talkAccepted && this->actor.isLockedOn) {
            Actor_OfferTalk(&this->actor, play, 350.0f);
        }
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    }
}

void EnInvadepoh_BarnRomani_SetupIdle(EnInvadepoh* this) {
    EnInvadepohInteractInfo* interactInfo = &this->interactInfo;

    Animation_MorphToLoop(&this->skelAnime, &gRomaniIdleAnim, -10.0f);
    interactInfo->headRotTarget.x = 0;
    interactInfo->headRotTarget.y = 0;
    interactInfo->headRotTarget.z = 0;
    interactInfo->headRotStepScale = 0.1f;
    interactInfo->headRotMaxStep = 0x5DC;

    this->timer = Rand_S16Offset(200, 200);
    this->angle = this->actor.shape.rot.y;
    this->actor.flags |= (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY);
    this->actionFunc = EnInvadepoh_BarnRomani_Idle;
}

void EnInvadepoh_BarnRomani_Idle(EnInvadepoh* this, PlayState* play) {
    s32 pad;
    EnInvadepohInteractInfo* interactInfo = &this->interactInfo;

    if ((play->gameplayFrames % 0x100) == 0) {
        Vec3f pathPointF;
        s16 yawToPath;

        Math_Vec3s_ToVec3f(&pathPointF, this->pathPoints);
        yawToPath = Math_Vec3f_Yaw(&this->actor.world.pos, &pathPointF);
        this->angle = Rand_S16Offset(-0x1F40, 0x3E80) + yawToPath;
        this->shapeAngularVelocityY = 0;
    }
    Math_StepToS(&this->shapeAngularVelocityY, 0x7D0, 0x28);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->angle, 6, this->shapeAngularVelocityY, 0x28);

    if (this->actor.xzDistToPlayer < 300.0f) {
        Player* player = GET_PLAYER(play);
        s16 angleToPlayer;

        angleToPlayer = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos) * 0.85f;
        interactInfo->headRotTarget.x = CLAMP((s16)(angleToPlayer - this->actor.shape.rot.x), -0x9C4, 0x9C4);

        angleToPlayer = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
        interactInfo->headRotTarget.y = CLAMP((s16)(angleToPlayer * 0.7f), -0x1F40, 0x1F40);

        if ((play->gameplayFrames % 0x100) == 0) {
            interactInfo->headRotTarget.z = Rand_S16Offset(-0x5DC, 0xBB8);
        }
    } else {
        interactInfo->headRotTarget.x = 0;
        interactInfo->headRotTarget.y = 0;
        interactInfo->headRotTarget.z = 0;
    }

    if (this->timer > 0) {
        this->timer--;
    } else {
        EnInvadepoh_BarnRomani_SetupLookAround(this);
    }
}

void EnInvadepoh_BarnRomani_SetupLookAround(EnInvadepoh* this) {
    EnInvadepohInteractInfo* interactInfo = &this->interactInfo;

    Animation_MorphToPlayOnce(&this->skelAnime, &gRomaniLookAroundAnim, -10.0f);
    interactInfo->headRotTarget.x = 0;
    interactInfo->headRotTarget.y = 0;
    interactInfo->headRotTarget.z = 0;
    interactInfo->headRotStepScale = 0.1f;
    interactInfo->headRotMaxStep = 0x320;
    this->actor.flags |= (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY);
    this->actionFunc = EnInvadepoh_BarnRomani_LookAround;
}

void EnInvadepoh_BarnRomani_LookAround(EnInvadepoh* this, PlayState* play) {
    if (this->isAnimFinished) {
        EnInvadepoh_BarnRomani_SetupIdle(this);
    }
}

void EnInvadepoh_BarnRomani_SetupWalk(EnInvadepoh* this) {
    EnInvadepohInteractInfo* interactInfo = &this->interactInfo;

    Animation_MorphToLoop(&this->skelAnime, &gRomaniWalkAnim, 0.0f);
    interactInfo->headRotTarget.x = 0;
    interactInfo->headRotTarget.y = 0;
    interactInfo->headRotTarget.z = 0;
    interactInfo->headRotStepScale = 0.1f;
    interactInfo->headRotMaxStep = 0x320;
    this->actionFunc = EnInvadepoh_BarnRomani_Walk;
}

void EnInvadepoh_BarnRomani_Walk(EnInvadepoh* this, PlayState* play) {
    s32 pad;

    Math_StepToF(&this->actor.speed, 5.0f, 1.0f);

    if (EnInvadepoh_Romani_MoveAlongPath(this, play, this->actor.speed, 50.0f)) {
        EnInvadepoh_BarnRomani_SetNextPathPoint(this);
        this->shapeAngularVelocityY = 0x5DC;
        this->actor.speed *= 0.5f;
    } else {
        Math_StepToS(&this->shapeAngularVelocityY, 0x190, 0x32);
    }

    EnInvadepoh_Romani_TurnToPath(this, 6, this->shapeAngularVelocityY, 50);

    if (this->currentPoint == 0) {
        if (!this->doorOpened) {
            this->doorOpened = EnInvadepoh_Romani_OpenDoor(this, play, SQ(80.0f), -15);
        }
        this->actor.flags &= ~(ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY);
    } else {
        this->doorOpened = false;
        this->actor.flags |= (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY);
    }

    if (CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40) &&
        (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 7.0f))) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_ROMANI_WALK);
    }

    if (this->currentPoint == this->endPoint) {
        EnInvadepoh_BarnRomani_SetupIdle(this);
    }
}

void EnInvadepoh_BarnRomani_SetupTalk(EnInvadepoh* this) {
    this->interactInfo.headRotStepScale = 0.08f;
    this->interactInfo.headRotMaxStep = 0x7D0;
    this->shapeAngularVelocityY = 0;
    Animation_MorphToLoop(&this->skelAnime, &gRomaniIdleAnim, 0.0f);
    this->actionFunc = EnInvadepoh_BarnRomani_Talk;
}

void EnInvadepoh_BarnRomani_Talk(EnInvadepoh* this, PlayState* play) {
    EnInvadepohInteractInfo* interactInfo = &this->interactInfo;
    Player* player = GET_PLAYER(play);
    s16 angleToPlayer;

    Math_StepToS(&this->shapeAngularVelocityY, 0x7D0, 0x1F4);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, this->shapeAngularVelocityY, 0x28);
    angleToPlayer = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos) * 0.85f;
    interactInfo->headRotTarget.x = CLAMP((s16)(angleToPlayer - this->actor.shape.rot.x), -0xBB8, 0xBB8);

    angleToPlayer = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
    interactInfo->headRotTarget.y = CLAMP((s16)(angleToPlayer * 0.7f), -0x1F40, 0x1F40);

    if (Actor_TextboxIsClosing(&this->actor, play)) {
        if (this->actor.textId == 0x332D) {
            SET_WEEKEVENTREG(WEEKEVENTREG_54_10);
            this->actor.textId = 0x332E;
        }

        if (this->currentPoint == this->endPoint) {
            EnInvadepoh_BarnRomani_SetupIdle(this);
        } else {
            EnInvadepoh_BarnRomani_SetupWalk(this);
        }
    }
}

void EnInvadepoh_BarnRomani_WaitForObject(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;
    s32 pad;

    if (Object_IsLoaded(&play->objectCtx, this->objectSlot)) {
        s32 currentTime = CURRENT_TIME;

        this->actor.objectSlot = this->objectSlot;
        Actor_SetObjectDependency(play, &this->actor);
        EnInvadepoh_Romani_DesegmentTextures();
        SkelAnime_InitFlex(play, &this->skelAnime, &gRomaniSkel, &gRomaniWalkAnim, this->jointTable, this->morphTable,
                           ROMANI_LIMB_MAX);
        EnInvadepoh_Interact_Init(&this->interactInfo, D_80B4EA90, ROMANI_EYE_ANIMATION_1, D_80B4EB00,
                                  ROMANI_MOUTH_ANIMATION_1, &gZeroVec3s, 100, 0.03f, 0.3f, 0.03f);
        EnInvadepoh_BarnRomani_SetupPath(this, play2);

        if ((currentTime < CLOCK_TIME(2, 15)) || (currentTime >= CLOCK_TIME(6, 00))) {
            this->currentPoint = 0;
            this->actor.update = EnInvadepoh_BarnRomani_WaitForEvent;
        } else {
            this->currentPoint = this->endPoint;
            this->actor.update = EnInvadepoh_BarnRomani_Update;
            this->actor.draw = EnInvadepoh_Romani_Draw;
            EnInvadepoh_BarnRomani_SetupIdle(this);
        }

        EnInvadepoh_SetPosToPathPoint(this, this->currentPoint);
        EnInvadepoh_SetYawAlongPath(this);
        func_800B4AEC(play, &this->actor, 50.0f);
        EnInvadepoh_SnapToFloor(this);

        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_PROMISED_TO_HELP_WITH_THEM)) {
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_54_10)) {
                this->actor.textId = 0x332E;
            } else {
                this->actor.textId = 0x332D;
            }
        } else {
            this->actor.textId = 0x332C;
        }
    }
}

void EnInvadepoh_BarnRomani_WaitForEvent(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;

    if ((CURRENT_TIME < CLOCK_TIME(6, 00)) && (CURRENT_TIME >= CLOCK_TIME(2, 15))) {
        this->actor.update = EnInvadepoh_BarnRomani_Update;
        this->actor.draw = EnInvadepoh_Romani_Draw;
        EnInvadepoh_BarnRomani_SetupWalk(this);
    }
}

void EnInvadepoh_BarnRomani_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;
    s32 inUncullRange = CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40);
    s32 talkAccepted = Actor_TalkOfferAccepted(&this->actor, &play->state);

    if (talkAccepted) {
        Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_ROMANI);
        EnInvadepoh_BarnRomani_SetupTalk(this);
    }

    this->actionFunc(this, play);

    if (inUncullRange) {
        this->isAnimFinished = SkelAnime_Update(&this->skelAnime);
        EnInvadepoh_Interact_Update(&this->interactInfo);
        if ((this->actionFunc != EnInvadepoh_BarnRomani_Talk) && !talkAccepted && this->actor.isLockedOn) {
            Actor_OfferTalk(&this->actor, play, 100.0f);
        }
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    }
}

void EnInvadepoh_RewardRomani_SetupClearCheck(EnInvadepoh* this) {
    this->actionFunc = EnInvadepoh_RewardRomani_ClearCheck;
}

void EnInvadepoh_RewardRomani_ClearCheck(EnInvadepoh* this, PlayState* play) {
    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_DEFENDED_AGAINST_THEM)) {
        this->actor.draw = EnInvadepoh_Romani_Draw;
        this->actor.flags |= (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY);
        EnInvadepoh_RewardRomani_SetupStartCs(this);
    }
}

void EnInvadepoh_RewardRomani_SetupStartCs(EnInvadepoh* this) {
    this->actor.flags |= ACTOR_FLAG_10000;
    this->actionFunc = EnInvadepoh_RewardRomani_StartCs;
}

void EnInvadepoh_RewardRomani_StartCs(EnInvadepoh* this, PlayState* play) {
    if (Actor_TalkOfferAccepted(&this->actor, &play->state)) {
        EnInvadepoh_Romani_StartTextBox(this, play, 0x3331);
        EnInvadepoh_RewardRomani_SetupTalk(this);
    } else {
        Actor_OfferTalk(&this->actor, play, 2000.0f);
    }
}

void EnInvadepoh_RewardRomani_SetupTalk(EnInvadepoh* this) {
    this->actionFunc = EnInvadepoh_RewardRomani_Talk;
}

void EnInvadepoh_RewardRomani_Talk(EnInvadepoh* this, PlayState* play) {
    if ((Message_GetState(&play->msgCtx) == TEXT_STATE_EVENT) && Message_ShouldAdvance(play)) {
        if (this->textId == 0x3331) {
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_22_02)) {
                EnInvadepoh_Romani_StartTextBox(this, play, 0x3334);
                Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_DEFENDED_AGAINST_THEM);
                Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_ROMANI);
            } else {
                EnInvadepoh_Romani_StartTextBox(this, play, 0x3333);
            }
        } else if (this->textId == 0x3333) {
            EnInvadepoh_RewardRomani_SetupGiveBottle(this);
        } else if (this->textId == 0x3334) {
            Message_CloseTextbox(play);
            EnInvadepoh_RewardRomani_SetupFinished(this);
        }
    }
}

void EnInvadepoh_RewardRomani_SetupGiveBottle(EnInvadepoh* this) {
    this->timer = 2;
    this->actionFunc = EnInvadepoh_RewardRomani_GiveBottle;
}

void EnInvadepoh_RewardRomani_GiveBottle(EnInvadepoh* this, PlayState* play) {
    if (this->timer > 0) {
        this->timer--;
        if (this->timer == 0) {
            Message_CloseTextbox(play);
        }
    }
    if (Actor_HasParent(&this->actor, play)) {
        this->actor.parent = NULL;
        SET_WEEKEVENTREG(WEEKEVENTREG_22_02);
        EnInvadepoh_RewardRomani_SetupAfterGiveBottle(this);
    } else {
        Actor_OfferGetItem(&this->actor, play, GI_MILK_BOTTLE, 2000.0f, 2000.0f);
    }
}

void EnInvadepoh_RewardRomani_SetupAfterGiveBottle(EnInvadepoh* this) {
    this->actionFunc = EnInvadepoh_RewardRomani_AfterGiveBottle;
}

void EnInvadepoh_RewardRomani_AfterGiveBottle(EnInvadepoh* this, PlayState* play) {
    if (Actor_TalkOfferAccepted(&this->actor, &play->state)) {
        EnInvadepoh_Romani_StartTextBox(this, play, 0x3334);
        Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_RECEIVED_MILK_BOTTLE);
        Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_DEFENDED_AGAINST_THEM);
        Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_ROMANI);
        EnInvadepoh_RewardRomani_SetupTalk(this);
    } else {
        Actor_OfferTalkExchangeEquiCylinder(&this->actor, play, 2000.0f, PLAYER_IA_MINUS1);
    }
}

void EnInvadepoh_RewardRomani_SetupFinished(EnInvadepoh* this) {
    this->actor.flags &= ~(ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY);
    this->actionFunc = EnInvadepoh_RewardRomani_Finished;
}

void EnInvadepoh_RewardRomani_Finished(EnInvadepoh* this, PlayState* play) {
    if (play->msgCtx.bombersNotebookEventQueueCount == 0) {
        if (play->msgCtx.msgMode == 0) {
            sRewardFinished = true;
        } else if ((Message_GetState(&play->msgCtx) == TEXT_STATE_DONE) ||
                   (Message_GetState(&play->msgCtx) == TEXT_STATE_EVENT)) {
            sRewardFinished = true;
        }
    }
}

void EnInvadepoh_RewardRomani_WaitForObject(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;
    EnInvadepohInteractInfo* interactInfo = &this->interactInfo;

    if (Object_IsLoaded(&play2->objectCtx, this->objectSlot)) {
        this->actor.objectSlot = this->objectSlot;
        Actor_SetObjectDependency(play, &this->actor);
        EnInvadepoh_Romani_DesegmentTextures();
        this->actor.update = EnInvadepoh_RewardRomani_Update;
        SkelAnime_InitFlex(play, &this->skelAnime, &gRomaniSkel, &gRomaniWalkAnim, this->jointTable, this->morphTable,
                           ROMANI_LIMB_MAX);
        Animation_MorphToLoop(&this->skelAnime, &gRomaniIdleAnim, 0.0f);
        EnInvadepoh_Interact_Init(&this->interactInfo, D_80B4EA90, ROMANI_EYE_ANIMATION_1, D_80B4EB00,
                                  ROMANI_MOUTH_ANIMATION_3, &gZeroVec3s, 0x7D0, 0.08f, 0.3f, 0.03f);
        interactInfo->headRotStepScale = 0.08f;
        interactInfo->headRotMaxStep = 0x7D0;
        func_800B4AEC(play, &this->actor, 50.0f);
        EnInvadepoh_SnapToFloor(this);
        EnInvadepoh_RewardRomani_SetupClearCheck(this);
    }
}

void EnInvadepoh_RewardRomani_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;
    EnInvadepohInteractInfo* interactInfo = &this->interactInfo;
    s32 inUncullRange = CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40);

    this->actionFunc(this, play);

    if (inUncullRange && (this->actor.update != NULL)) {
        Player* player;
        s16 angleToPlayer;

        SkelAnime_Update(&this->skelAnime);
        player = GET_PLAYER(play);
        Math_StepToS(&this->shapeAngularVelocityY, 0x7D0, 0x28);
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 6, this->shapeAngularVelocityY, 40);
        angleToPlayer = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos) * 0.9f;
        interactInfo->headRotTarget.x = CLAMP((s16)(angleToPlayer - this->actor.shape.rot.x), -0xBB8, 0xBB8);

        angleToPlayer = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
        interactInfo->headRotTarget.y = CLAMP((s16)(angleToPlayer * 0.7f), -0x1F40, 0x1F40);
        EnInvadepoh_Interact_Update(&this->interactInfo);
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    }
}

void EnInvadepoh_Dog_PlayWalkSfx(EnInvadepoh* this) {
    s32 pad;

    if (Animation_OnFrame(&this->skelAnime, 1.0f) || Animation_OnFrame(&this->skelAnime, 7.0f)) {
        Actor_PlaySfx(&this->actor, NA_SE_EV_MONKEY_WALK);
    }
}

void EnInvadepoh_Dog_SetupWalk(EnInvadepoh* this) {
    Animation_MorphToLoop(&this->skelAnime, &gDogWalkAnim, -6.0f);
    this->timer = Rand_S16Offset(50, 80);
    this->actionFunc = EnInvadepoh_Dog_Walk;
}

void EnInvadepoh_Dog_Walk(EnInvadepoh* this, PlayState* play) {
    Math_StepToF(&this->actor.speed, 1.1f, 0.5f);

    if (EnInvadepoh_Dog_MoveAlongPath(this, play)) {
        EnInvadepoh_Dog_SetNextPathPoint(this);
    }

    EnInvadepoh_Dog_PlayWalkSfx(this);

    if (this->dogTargetPoint >= 0) {
        this->timer = 0;
    }

    if (this->timer > 0) {
        this->timer--;
    } else {
        EnInvadepoh_Dog_SetupRun(this);
    }
}

void EnInvadepoh_Dog_SetupRun(EnInvadepoh* this) {
    Animation_MorphToLoop(&this->skelAnime, &gDogRunAnim, -6.0f);
    this->timer = Rand_S16Offset(50, 200);
    this->actionFunc = EnInvadepoh_Dog_Run;
}

void EnInvadepoh_Dog_Run(EnInvadepoh* this, PlayState* play) {
    Math_StepToF(&this->actor.speed, 3.8f, 0.45f);

    if (this->dogTargetPoint >= 0) {
        f32 distToTarget;
        Vec3f targetPathPoint;

        Math_Vec3s_ToVec3f(&targetPathPoint, &this->pathPoints[this->dogTargetPoint]);
        distToTarget = Math3D_Vec3fDistSq(&this->actor.world.pos, &targetPathPoint);
        if (distToTarget < SQ(80.0f)) {
            this->actor.speed *= 0.85f;
        } else if (distToTarget < SQ(150.0f)) {
            this->actor.speed *= 0.93f;
        } else if (distToTarget < SQ(250.0f)) {
            this->actor.speed *= 0.96f;
        }
        if ((this->currentPoint == this->dogTargetPoint) || (distToTarget < SQ(50.0f))) {
            this->timer = 0;
        }
    }

    EnInvadepoh_Dog_PlayWalkSfx(this);

    if (EnInvadepoh_Dog_MoveAlongPath(this, play)) {
        EnInvadepoh_Dog_SetNextPathPoint(this);
    }

    if (this->timer > 0) {
        this->timer--;
    } else if (this->dogTargetPoint >= 0) {
        if (!sAliensTooClose && (Rand_ZeroOne() < 0.4f)) {
            Actor_PlaySfx(&this->actor, NA_SE_EV_SMALL_DOG_GROAN);
        }
        EnInvadepoh_Dog_SetupBark(this);
    } else {
        EnInvadepoh_Dog_SetupWalk(this);
    }
}

void EnInvadepoh_Dog_SetupBark(EnInvadepoh* this) {
    Animation_MorphToPlayOnce(&this->skelAnime, &gDogBarkAnim, -6.0f);
    this->actionFunc = EnInvadepoh_Dog_Bark;
}

void EnInvadepoh_Dog_Bark(EnInvadepoh* this, PlayState* play) {
    s32 pad;

    Math_StepToF(&this->actor.speed, 0.0f, 1.0f);
    Math_SmoothStepToS(&this->actor.world.rot.y, Actor_WorldYawTowardActor(&this->actor, &sClosestAlien->actor), 5,
                       0x1388, 0x64);
    EnInvadepoh_Dog_Move(this, play);

    if (Animation_OnFrame(&this->skelAnime, 13.0f) || Animation_OnFrame(&this->skelAnime, 19.0f)) {
        Actor_PlaySfx(&this->actor, NA_SE_EV_SMALL_DOG_ANG_BARK);
    }

    if (this->isAnimFinished) {
        EnInvadepoh_Dog_SetupRun(this);
    }
}

void EnInvadepoh_Dog_SetupJump(EnInvadepoh* this) {
    Animation_MorphToPlayOnce(&this->skelAnime, &gDogJumpAnim, -6.0f);
    this->actionFunc = EnInvadepoh_Dog_Jump;
}

void EnInvadepoh_Dog_Jump(EnInvadepoh* this, PlayState* play) {
    Math_StepToF(&this->actor.speed, 0.5f, 1.0f);
    EnInvadepoh_Dog_Move(this, play);

    if (this->isAnimFinished) {
        EnInvadepoh_Dog_SetupRun(this);
    }
}

void EnInvadepoh_Dog_WaitForObject(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;

    if (!Object_IsLoaded(&play->objectCtx, this->objectSlot)) {
        return;
    }

    this->actor.objectSlot = this->objectSlot;
    Actor_SetObjectDependency(play, &this->actor);
    SkelAnime_InitFlex(play, &this->skelAnime, &gDogSkel, &gDogWalkAnim, this->jointTable, this->morphTable,
                       DOG_LIMB_MAX);
    EnInvadepoh_Interact_Init(&this->interactInfo, NULL, 0, NULL, 0, &gZeroVec3s, 0xBB8, 0.1f, 0.0f, 0.0f);
    EnInvadepoh_Dog_SetupPath(this, play);
    EnInvadepoh_SetPosToPathPoint(this, 0);
    func_800B4AEC(play, &this->actor, 50.0f);
    EnInvadepoh_SnapToFloor(this);
    Math_Vec3f_Copy(&this->currentPos, &this->actor.world.pos);

    if (sEventState == EN_INVADEPOH_EVENT_ACTIVE) {
        this->actor.update = EnInvadepoh_Dog_Update;
        this->actor.draw = EnInvadepoh_Dog_Draw;
        this->actor.flags |= ACTOR_FLAG_TARGETABLE;
        EnInvadepoh_Dog_SetupWalk(this);
    } else if (sEventState == EN_INVADEPOH_EVENT_WAIT) {
        this->actor.update = EnInvadepoh_Dog_WaitForEvent;
    } else {
        Actor_Kill(&this->actor);
    }
}

void EnInvadepoh_Dog_WaitForEvent(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;

    if (sEventState == EN_INVADEPOH_EVENT_ACTIVE) {
        this->actor.update = EnInvadepoh_Dog_Update;
        this->actor.draw = EnInvadepoh_Dog_Draw;
        this->actor.flags |= ACTOR_FLAG_TARGETABLE;
        EnInvadepoh_Dog_SetupWalk(this);
    }
}

void EnInvadepoh_Dog_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;
    s32 inUncullRange = CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40);

    sClosestAlien = EnInvadepoh_Dog_GetClosestAlien();
    if (sClosestAlien == NULL) {
        s32 hadTarget = (this->dogTargetPoint >= 0);

        this->dogTargetPoint = -1;
        if (hadTarget) {
            EnInvadepoh_Dog_SetupJump(this);
        }
    } else {
        s32 lastTargetPoint = this->dogTargetPoint;
        s32 pointsToTarget;
        s32 halfwayPoint;

        this->dogTargetPoint = EnInvadepoh_Dog_FindClosestWaypoint(this, &sClosestAlien->actor.world.pos);
        if (lastTargetPoint != this->dogTargetPoint) {
            pointsToTarget = this->dogTargetPoint - this->currentPoint;
            if (pointsToTarget < 0) {
                pointsToTarget += this->endPoint;
            }

            halfwayPoint = this->endPoint >> 1;
            if (halfwayPoint < pointsToTarget) {
                this->pathStep = -1;
            } else if (pointsToTarget < halfwayPoint) {
                this->pathStep = 1;
            }
        }
    }

    this->actionFunc(this, play);

    this->isAnimFinished = SkelAnime_Update(&this->skelAnime);

    if (inUncullRange && (this->actor.update != NULL)) {
        EnInvadepoh_Interact_Update(&this->interactInfo);
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    }
}

void EnInvadepoh_Night3Cremia_SetupWalk(EnInvadepoh* this) {
    EnInvadepohInteractInfo* interactInfo = &this->interactInfo;

    Animation_MorphToLoop(&this->skelAnime, &gCremiaWalkAnim, -6.0f);
    interactInfo->headRotTarget.x = 0;
    interactInfo->headRotTarget.y = 0;
    interactInfo->headRotTarget.z = 0;
    interactInfo->headRotStepScale = 0.1f;
    interactInfo->headRotMaxStep = 0x320;

    this->shapeAngularVelocityY = 0;
    this->actionFunc = EnInvadepoh_Night3Cremia_Walk;
}

void EnInvadepoh_Night3Cremia_Walk(EnInvadepoh* this, PlayState* play) {
    EnInvadepohInteractInfo* interactInfo = &this->interactInfo;
    EnInvadepoh* romani = sRomani;
    s32 pad;
    s32 tempFrames;
    s32 pad2;
    s16 angleToRomani;
    s16 targetYaw;
    s16 angleToPlayer;

    if (romani != NULL) {
        if (romani->currentPoint == 0) {
            this->distanceToRomani = 40.0f;
            this->angle = -0x8000;
            this->actor.flags &= ~(ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY);
        } else if (romani->currentPoint < (romani->endPoint - 1)) {
            this->distanceToRomani = 40.0f;
            Math_ScaledStepToS(&this->angle, -0x4800, 0xC8);
            this->actor.flags |= (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY);
        } else {
            Math_StepToF(&this->distanceToRomani, 5.0f, 3.0f);
            Math_ScaledStepToS(&this->angle, -0x8000, 0x12C);
            this->actor.flags &= ~(ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY);
        }

        angleToRomani = this->angle + romani->actor.world.rot.y;
        this->actor.world.pos.x = (Math_SinS(angleToRomani) * this->distanceToRomani) + romani->actor.world.pos.x;
        this->actor.world.pos.y = romani->actor.world.pos.y;
        this->actor.world.pos.z = (Math_CosS(angleToRomani) * this->distanceToRomani) + romani->actor.world.pos.z;
        func_800B4AEC(play, &this->actor, 50.0f);
        EnInvadepoh_SnapToFloor(this);
        Math_StepToS(&this->shapeAngularVelocityY, 0xBB8, 0x1F5);

        if (Math3D_Vec3fDistSq(&this->actor.prevPos, &this->actor.world.pos) > SQ(0.01f)) {
            Math_SmoothStepToS(&this->actor.shape.rot.y, Math_Vec3f_Yaw(&this->actor.prevPos, &this->actor.world.pos),
                               3, this->shapeAngularVelocityY, 0x1F4);
        }

        tempFrames = (play->gameplayFrames + 20) % 0x80;
        if (tempFrames & 0x40) {
            targetYaw = Math_Vec3f_Yaw(&this->actor.world.pos, &romani->actor.world.pos);
            if (tempFrames == 0x40) {
                this->shapeAngularVelocityY = 0;
            }
            Math_StepToS(&this->shapeAngularVelocityY, 0x7D0, 0x28);
            Math_SmoothStepToS(&this->actor.shape.rot.y, targetYaw, 6, this->shapeAngularVelocityY, 0x28);
            angleToPlayer = Math_Vec3f_Pitch(&this->actor.focus.pos, &romani->actor.focus.pos) * 0.85f;
            interactInfo->headRotTarget.x = CLAMP((s16)(angleToPlayer - this->actor.shape.rot.x), -0xBB8, 0xBB8);

            angleToPlayer = targetYaw - this->actor.shape.rot.y;
            interactInfo->headRotTarget.y = CLAMP((s16)(angleToPlayer * 0.7f), -0x1F40, 0x1F40);
        }
    }

    if (CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40) &&
        (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 12.0f))) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_ROMANI_WALK);
    }

    if (CURRENT_TIME > CLOCK_TIME(20, 15)) {
        Actor_Kill(&this->actor);
    } else if ((romani != NULL) && (romani->actionFunc == EnInvadepoh_Night3Romani_Talk)) {
        EnInvadepoh_Night3Cremia_SetupIdle(this);
    }
}

void EnInvadepoh_Night3Cremia_SetupTalk(EnInvadepoh* this) {
    this->interactInfo.headRotStepScale = 0.08f;
    this->interactInfo.headRotMaxStep = 0x7D0;
    Animation_MorphToLoop(&this->skelAnime, &gCremiaIdleAnim, -6.0f);
    this->shapeAngularVelocityY = 0;
    this->actionFunc = EnInvadepoh_Night3Cremia_Talk;
}

void EnInvadepoh_Night3Cremia_Talk(EnInvadepoh* this, PlayState* play) {
    EnInvadepohInteractInfo* interactInfo = &this->interactInfo;
    Player* player = GET_PLAYER(play);
    s16 angleToPlayer;

    Math_StepToS(&this->shapeAngularVelocityY, 0x9C4, 0x1C2);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, this->shapeAngularVelocityY, 0x28);
    angleToPlayer = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos) * 0.85f;
    interactInfo->headRotTarget.x = CLAMP((s16)(angleToPlayer - this->actor.shape.rot.x), -0xBB8, 0xBB8);

    angleToPlayer = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
    interactInfo->headRotTarget.y = CLAMP((s16)(angleToPlayer * 0.7f), -0x1F40, 0x1F40);
    if (Actor_TextboxIsClosing(&this->actor, play)) {
        EnInvadepoh_Night3Cremia_SetupWalk(this);
    }
}

void EnInvadepoh_Night3Cremia_SetupIdle(EnInvadepoh* this) {
    this->interactInfo.headRotStepScale = 0.08f;
    this->interactInfo.headRotMaxStep = 0x7D0;
    Animation_MorphToLoop(&this->skelAnime, &gCremiaIdleAnim, -6.0f);
    this->shapeAngularVelocityY = 0;
    this->actionFunc = EnInvadepoh_Night3Cremia_Idle;
}

void EnInvadepoh_Night3Cremia_Idle(EnInvadepoh* this, PlayState* play) {
    EnInvadepohInteractInfo* interactInfo = &this->interactInfo;
    Player* player = GET_PLAYER(play);
    s16 angleToPlayer;

    Math_StepToS(&this->shapeAngularVelocityY, 0x7D0, 0xC8);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 6, this->shapeAngularVelocityY, 0x28);
    angleToPlayer = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos) * 0.85f;
    interactInfo->headRotTarget.x = CLAMP((s16)(angleToPlayer - this->actor.shape.rot.x), -0xBB8, 0xBB8);

    angleToPlayer = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
    interactInfo->headRotTarget.y = CLAMP((s16)(angleToPlayer * 0.7f), -0x1F40, 0x1F40);
    if (sRomani == NULL) {
        EnInvadepoh_Night3Cremia_SetupWalk(this);
    } else if ((sRomani != NULL) && (sRomani->actionFunc != EnInvadepoh_Night3Romani_Talk)) {
        EnInvadepoh_Night3Cremia_SetupWalk(this);
    }
}

void EnInvadepoh_Night3Cremia_WaitForObject(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;
    s32 pad;

    if (Object_IsLoaded(&play2->objectCtx, this->objectSlot)) {
        s32 currentTime = CURRENT_TIME;

        this->actor.objectSlot = this->objectSlot;
        Actor_SetObjectDependency(play, &this->actor);
        EnInvadepoh_Cremia_DesegmentTextures();
        SkelAnime_InitFlex(play, &this->skelAnime, &gCremiaSkel, &gCremiaWalkAnim, this->jointTable, this->morphTable,
                           CREMIA_LIMB_MAX);
        EnInvadepoh_Interact_Init(&this->interactInfo, D_80B4EBDC, CREMIA_EYE_ANIMATION_1, D_80B4EC08,
                                  CREMIA_MOUTH_ANIMATION_0, &gZeroVec3s, 100, 0.03f, 0.3f, 0.03f);
        this->actor.textId = 0x33CD;

        if (currentTime < CLOCK_TIME(20, 01) + 30) {
            this->angle = -0x8000;
            this->distanceToRomani = 40.0f;
        } else if (currentTime > CLOCK_TIME(20, 14) + 1) {
            this->angle = -0x4800;
            this->distanceToRomani = 20.0f;
        } else {
            this->angle = -0x8000;
            this->distanceToRomani = 40.0f;
        }

        if ((CLOCK_TIME(6, 00) <= currentTime) && (currentTime < CLOCK_TIME(20, 00) + 30)) {
            this->actor.update = EnInvadepoh_Night3Cremia_WaitForEvent;
            this->actor.draw = NULL;
        } else if ((CLOCK_TIME(20, 00) + 30 <= currentTime) && (currentTime < CLOCK_TIME(20, 15))) {
            this->actor.update = EnInvadepoh_Night3Cremia_Update;
            this->actor.draw = EnInvadepoh_Cremia_Draw;
            EnInvadepoh_Night3Cremia_SetupWalk(this);
        } else {
            Actor_Kill(&this->actor);
        }
    }
}

void EnInvadepoh_Night3Cremia_WaitForEvent(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;

    if ((CURRENT_TIME >= CLOCK_TIME(20, 00) + 30) && (CURRENT_TIME < CLOCK_TIME(20, 15))) {
        this->actor.update = EnInvadepoh_Night3Cremia_Update;
        this->actor.draw = EnInvadepoh_Cremia_Draw;
        EnInvadepoh_Night3Cremia_SetupWalk(this);
    }
}

void EnInvadepoh_Night3Cremia_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;
    s32 inUncullRange = CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40);
    s32 talkAccepted = Actor_TalkOfferAccepted(&this->actor, &play->state);

    if (talkAccepted) {
        Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_CREMIA);
        EnInvadepoh_Night3Cremia_SetupTalk(this);
    }

    this->actionFunc(this, play2);

    if (inUncullRange && (this->actor.update != NULL)) {
        SkelAnime_Update(&this->skelAnime);
        EnInvadepoh_Interact_Update(&this->interactInfo);
        if ((this->actionFunc != EnInvadepoh_Night3Cremia_Talk) && !talkAccepted && this->actor.isLockedOn) {
            Actor_OfferTalk(&this->actor, play, 350.0f);
        }
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    }
}

void EnInvadepoh_Night3Romani_SetupWalk(EnInvadepoh* this) {
    EnInvadepohInteractInfo* interactInfo = &this->interactInfo;

    Animation_MorphToLoop(&this->skelAnime, &gRomaniWalkAnim, -10.0f);
    interactInfo->headRotTarget.x = 0;
    interactInfo->headRotTarget.y = 0;
    interactInfo->headRotTarget.z = 0;
    interactInfo->headRotStepScale = 0.1f;
    interactInfo->headRotMaxStep = 0x320;
    this->actionFunc = EnInvadepoh_Night3Romani_Walk;
}

void EnInvadepoh_Night3Romani_Walk(EnInvadepoh* this, PlayState* play) {
    EnInvadepohInteractInfo* interactInfo = &this->interactInfo;
    EnInvadepoh* cremia = sCremia;
    s32 curPoint;
    s32 tempFrames;
    s32 doorTimer;
    s32 pad;
    Vec3f curPathPointF;
    Vec3f nextPathPointF;

    EnInvadepoh_Night3Romani_SetProgress(this);
    EnInvadepoh_Night3Romani_MoveAlongPathTimed(this, play);
    EnInvadepoh_Romani_TurnToPath(this, 6, 0x7D0, 0x64);

    curPoint = (this->currentPoint < this->endPoint) ? this->currentPoint : this->endPoint - 1;

    Math_Vec3s_ToVec3f(&curPathPointF, &this->pathPoints[curPoint]);
    Math_Vec3s_ToVec3f(&nextPathPointF, &this->pathPoints[curPoint + 1]);
    Math_SmoothStepToS(&this->actor.world.rot.y, Math_Vec3f_Yaw(&curPathPointF, &nextPathPointF) + 0, 5, 0x7D0, 100);

    if ((this->currentPoint == 0) || (this->currentPoint == this->endPoint - 1)) {
        if (!this->doorOpened) {
            s32 trueTimeSpeed = Environment_GetTimeSpeed(play);
            doorTimer = trueTimeSpeed;

            if (trueTimeSpeed > 0) {
                // This is really dividing by trueTimeSpeed, but matching requires writing like this
                doorTimer = (R_TIME_SPEED * -23.0f / doorTimer) - 0.5f;
                this->doorOpened = EnInvadepoh_Romani_OpenDoor(this, play, SQ(80.0f), doorTimer);
            }
        }
        this->actor.flags &= ~(ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY);
    } else {
        this->doorOpened = false;
        this->actor.flags |= (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY);
    }
    tempFrames = play->gameplayFrames % 0x80;
    if (tempFrames & 0x40) {
        s16 targetYaw = Math_Vec3f_Yaw(&this->actor.world.pos, &cremia->actor.world.pos);
        s16 angleToPlayer;

        if (tempFrames == 0x40) {
            this->shapeAngularVelocityY = 0;
        }
        Math_StepToS(&this->shapeAngularVelocityY, 0x7D0, 0x28);
        Math_SmoothStepToS(&this->actor.shape.rot.y, targetYaw, 6, this->shapeAngularVelocityY, 40);
        angleToPlayer = Math_Vec3f_Pitch(&this->actor.focus.pos, &cremia->actor.focus.pos) * 0.85f;
        interactInfo->headRotTarget.x = CLAMP((s16)(angleToPlayer - this->actor.shape.rot.x), -0xBB8, 0xBB8);

        angleToPlayer = targetYaw - this->actor.shape.rot.y;
        interactInfo->headRotTarget.y = CLAMP((s16)(angleToPlayer * 0.7f), -0x1F40, 0x1F40);
    }

    if (CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40) &&
        (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 7.0f))) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_ROMANI_WALK);
    }

    if (this->pathProgress >= 0.9999f) {
        Actor_Kill(&this->actor);
    } else if ((cremia != NULL) && (cremia->actionFunc == EnInvadepoh_Night3Cremia_Talk)) {
        EnInvadepoh_Night3Romani_SetupIdle(this);
    }
}

void EnInvadepoh_Night3Romani_SetupTalk(EnInvadepoh* this) {
    this->interactInfo.headRotStepScale = 0.08f;
    this->interactInfo.headRotMaxStep = 0xFA0;
    Animation_MorphToLoop(&this->skelAnime, &gRomaniIdleAnim, -10.0f);
    this->shapeAngularVelocityY = 0;
    this->actionFunc = EnInvadepoh_Night3Romani_Talk;
}

void EnInvadepoh_Night3Romani_Talk(EnInvadepoh* this, PlayState* play) {
    EnInvadepohInteractInfo* interactInfo = &this->interactInfo;
    Player* player = GET_PLAYER(play);
    s16 angleToPlayer;

    Math_StepToS(&this->shapeAngularVelocityY, 0xBB8, 0x1F4);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 6, this->shapeAngularVelocityY, 40);
    angleToPlayer = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos) * 0.85f;
    interactInfo->headRotTarget.x = CLAMP((s16)(angleToPlayer - this->actor.shape.rot.x), -0xBB8, 0xBB8);

    angleToPlayer = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
    interactInfo->headRotTarget.y = CLAMP((s16)(angleToPlayer * 0.7f), -0x1F40, 0x1F40);
    if (Actor_TextboxIsClosing(&this->actor, play)) {
        EnInvadepoh_Night3Romani_SetupWalk(this);
    }
}

void EnInvadepoh_Night3Romani_SetupIdle(EnInvadepoh* this) {
    this->interactInfo.headRotStepScale = 0.08f;
    this->interactInfo.headRotMaxStep = 0x7D0;
    Animation_MorphToLoop(&this->skelAnime, &gRomaniIdleAnim, -10.0f);
    this->shapeAngularVelocityY = 0;
    this->actionFunc = EnInvadepoh_Night3Romani_Idle;
}

void EnInvadepoh_Night3Romani_Idle(EnInvadepoh* this, PlayState* play) {
    EnInvadepohInteractInfo* interactInfo = &this->interactInfo;
    Player* player = GET_PLAYER(play);
    s16 angleToPlayer;

    Math_StepToS(&this->shapeAngularVelocityY, 0x7D0, 0xC8);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 6, this->shapeAngularVelocityY, 40);
    angleToPlayer = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos) * 0.85f;
    interactInfo->headRotTarget.x = CLAMP((s16)(angleToPlayer - this->actor.shape.rot.x), -0xBB8, 0xBB8);

    angleToPlayer = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
    interactInfo->headRotTarget.y = CLAMP((s16)(angleToPlayer * 0.7f), -0x1F40, 0x1F40);

    if (sCremia == NULL) {
        EnInvadepoh_Night3Romani_SetupWalk(this);
    } else if ((sCremia != NULL) && (sCremia->actionFunc != EnInvadepoh_Night3Cremia_Talk)) {
        EnInvadepoh_Night3Romani_SetupWalk(this);
    }
}

void EnInvadepoh_Night3Romani_WaitForObject(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;
    s32 pad;

    if (Object_IsLoaded(&play2->objectCtx, this->objectSlot)) {
        s32 currentTime = CURRENT_TIME;

        this->actor.objectSlot = this->objectSlot;
        Actor_SetObjectDependency(play, &this->actor);
        EnInvadepoh_Romani_DesegmentTextures();
        SkelAnime_InitFlex(play, &this->skelAnime, &gRomaniSkel, &gRomaniWalkAnim, this->jointTable, this->morphTable,
                           ROMANI_LIMB_MAX);
        EnInvadepoh_Interact_Init(&this->interactInfo, D_80B4EA90, ROMANI_EYE_ANIMATION_1, D_80B4EB00,
                                  ROMANI_MOUTH_ANIMATION_3, &gZeroVec3s, 100, 0.03f, 0.3f, 0.03f);
        EnInvadepoh_Night3Romani_SetupPath(this, play);
        this->actor.world.rot.y = this->actor.shape.rot.y;
        EnInvadepoh_Night3Romani_SetProgress(this);
        EnInvadepoh_Night3Romani_MoveAlongPathTimed(this, play);
        EnInvadepoh_SetYawAlongPath(this);
        EnInvadepoh_SnapToFloor(this);
        this->actor.textId = 0x33CE;
        if ((currentTime >= CLOCK_TIME(6, 00)) && (currentTime < CLOCK_TIME(20, 00))) {
            this->actor.update = EnInvadepoh_Night3Romani_WaitForEvent;
            this->actor.draw = NULL;
        } else if ((currentTime >= CLOCK_TIME(20, 00)) && (currentTime < CLOCK_TIME(20, 14) + 15)) {
            this->actor.update = EnInvadepoh_Night3Romani_Update;
            this->actor.draw = EnInvadepoh_Romani_Draw;
            EnInvadepoh_Night3Romani_SetupWalk(this);
        } else {
            Actor_Kill(&this->actor);
        }
    }
}

void EnInvadepoh_Night3Romani_WaitForEvent(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;

    if ((CURRENT_TIME >= CLOCK_TIME(20, 00)) && (CURRENT_TIME < CLOCK_TIME(20, 14) + 15)) {
        this->actor.update = EnInvadepoh_Night3Romani_Update;
        this->actor.draw = EnInvadepoh_Romani_Draw;
        EnInvadepoh_Night3Romani_SetupWalk(this);
    }
}

void EnInvadepoh_Night3Romani_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;
    s32 inUncullRange = CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40);
    s32 talkAccepted = Actor_TalkOfferAccepted(&this->actor, &play->state);

    if (talkAccepted) {
        Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_ROMANI);
        EnInvadepoh_Night3Romani_SetupTalk(this);
    }

    this->actionFunc(this, play);

    if (inUncullRange && (this->actor.update != NULL)) {
        SkelAnime_Update(&this->skelAnime);
        EnInvadepoh_Interact_Update(&this->interactInfo);
        if ((this->actionFunc != EnInvadepoh_Night3Romani_Talk) && !talkAccepted && this->actor.isLockedOn) {
            Actor_OfferTalk(&this->actor, play, 350.0f);
        }
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    }
}

typedef struct EnInvadepohUnkStruct1 {
    /* 0x0 */ f32 accel;
    /* 0x4 */ s16 angularVelocity;
    /* 0x6 */ s16 angularAcceleration;
} EnInvadepohUnkStruct1; // size = 0x8

void EnInvadepoh_AlienAbductor_SetupCow(EnInvadepoh* this) {
    static EnInvadepohUnkStruct1 D_80B4EE0C[3] = {
        { 0.08f, 0x2BC, -0xA },
        { 0.09f, 0x12C, -0x5 },
        { 0.05f, 0x190, 0x0 },
    };
    s32 pad;
    s32 index = EN_INVADEPOH_GET_INDEX(&this->actor);
    s32 pad2;

    Animation_PlayLoop(&this->skelAnime, &gAlienHoldingCowAnim);
    this->skelAnime.curFrame = (EN_INVADEPOH_GET_INDEX(&this->actor)) * this->skelAnime.endFrame * 0.25f;
    this->alpha = 255;
    this->actor.draw = EnInvadepoh_Alien_Draw;
    this->shouldDraw = true;
    this->shouldDrawDeathFlash = false;
    this->eyeBeamAlpha = 255;
    this->alienAbductorAccelY = D_80B4EE0C[index].accel;
    this->angle = index * 0x5555;
    this->actor.world.pos.x = Math_SinS(this->angle) * 80.0f + this->actor.home.pos.x;
    this->actor.world.pos.y = this->actor.home.pos.y;
    this->actor.world.pos.z = Math_CosS(this->angle) * 80.0f + this->actor.home.pos.z;
    this->actor.shape.rot.y = this->angle + 0x4000;
    this->shapeAngularVelocityY = D_80B4EE0C[index].angularVelocity;
    this->shapeAngularAccelerationY = D_80B4EE0C[index].angularAcceleration;
    this->actionFunc = EnInvadepoh_AlienAbductor_Cow;
    this->actor.velocity.y = 0.0f;
}

void EnInvadepoh_AlienAbductor_Cow(EnInvadepoh* this, PlayState* play) {
    Actor* cow;
    f32 distToTarget;

    if (sUfo == NULL) {
        Actor_Kill(&this->actor);
        return;
    }

    Math_StepToF(&this->actor.velocity.y, 15.0f, this->alienAbductorAccelY);
    distToTarget = Math_SmoothStepToF(&this->actor.world.pos.y, this->actor.home.pos.y + 850.0f, 0.2f,
                                      this->actor.velocity.y, 0.01f);
    this->angle += 0x2BC;
    this->actor.world.pos.x = Math_SinS(this->angle) * 80.0f + this->actor.home.pos.x;
    this->actor.world.pos.z = Math_CosS(this->angle) * 80.0f + this->actor.home.pos.z;
    this->shapeAngularVelocityY += this->shapeAngularAccelerationY;
    this->actor.shape.rot.y += this->shapeAngularVelocityY;

    if (this->actor.child != NULL) {
        cow = this->actor.child;
        cow->world.pos.x = this->actor.world.pos.x;
        cow->world.pos.y = this->actor.world.pos.y - 38.0f;
        cow->world.pos.z = this->actor.world.pos.z;
        cow->shape.rot.y = this->actor.shape.rot.y;
    }

    if (distToTarget < 5.0f) {
        Actor_Kill(&this->actor);
    }
}

void EnInvadepoh_AlienAbductor_SetupRomani(EnInvadepoh* this) {
    Animation_PlayLoop(&this->skelAnime, &gAlienHoldingCowAnim);
    this->skelAnime.curFrame = (EN_INVADEPOH_GET_INDEX(&this->actor)) * this->skelAnime.endFrame * 0.25f;
    this->alpha = 255;
    this->actor.draw = NULL;
    this->shouldDraw = true;
    this->shouldDrawDeathFlash = false;
    this->eyeBeamAlpha = 255;
    this->angularVelocity = 0x190;
    this->angle = 0;
    this->timer = 200;
    this->actionFunc = EnInvadepoh_AlienAbductor_Romani;
    this->actor.velocity.y = 0.0f;
}

void EnInvadepoh_AlienAbductor_Romani(EnInvadepoh* this, PlayState* play) {
    s32 timer;
    f32 tempAngularVelocity;
    s32 reachedTargetY = 0;

    if (this->timer > 0) {
        this->timer--;
    }

    if (this->timer > 160) {
        this->actor.draw = NULL;
    } else {
        this->actor.draw = EnInvadepoh_Alien_Draw;
        timer = (reachedTargetY ? 0 : this->timer);

        if ((timer < 105) && (timer >= 100)) {
            this->actor.gravity = -1.0f;
            Math_SmoothStepToS(&this->actor.shape.rot.x, 0x2000, 8, 0x320, 0x28);
        } else {
            this->actor.gravity = 0.7f;
            Math_SmoothStepToS(&this->actor.shape.rot.x, 0, 8, 0x320, 0x28);
        }

        this->actor.velocity.y += this->actor.gravity;
        this->actor.velocity.y *= 0.92f;

        if (this->timer > 80) {
            this->actor.world.pos.y += this->actor.velocity.y;
        } else {
            f32 targetY = this->actor.home.pos.y + 850.0f;

            reachedTargetY = Math_StepToF(&this->actor.world.pos.y, targetY, fabsf(this->actor.velocity.y));
        }

        tempAngularVelocity = (this->angle * -0.06f) + this->angularVelocity;
        tempAngularVelocity *= 0.98f;
        this->angularVelocity = tempAngularVelocity;
        this->actor.shape.rot.y += this->angularVelocity;

        if (this->actor.child != NULL) {
            Actor* romani = this->actor.child;

            romani->world.pos.x = this->actor.world.pos.x;
            romani->world.pos.y = this->actor.world.pos.y - 30.0f;
            romani->world.pos.z = this->actor.world.pos.z;
            romani->shape.rot.y = this->actor.shape.rot.y;
        }
    }

    if ((this->timer <= 0) || reachedTargetY) {
        Actor_Kill(&this->actor);
    }
}

void EnInvadepoh_AlienAbductor_WaitForObject(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;
    s32 index;

    if (Object_IsLoaded(&play->objectCtx, this->objectSlot)) {
        index = EN_INVADEPOH_GET_INDEX(&this->actor);
        this->actor.objectSlot = this->objectSlot;
        Actor_SetObjectDependency(play, &this->actor);
        EnInvadepoh_Alien_SetTexAnim();
        this->actor.update = EnInvadepoh_AlienAbductor_Update;
        SkelAnime_InitFlex(play, &this->skelAnime, &gAlienSkel, &gAlienHoldingCowAnim, this->jointTable,
                           this->morphTable, ALIEN_LIMB_MAX);
        if (index < 3) {
            EnInvadepoh_AlienAbductor_SpawnCow(this, play, index);
            EnInvadepoh_AlienAbductor_SetupCow(this);
        } else {
            EnInvadepoh_AlienAbductor_SpawnRomani(this, play);
            EnInvadepoh_AlienAbductor_SetupRomani(this);
        }
    }
}

void EnInvadepoh_AlienAbductor_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;

    this->actionFunc(this, play);

    if (this->actor.update != NULL) {
        SkelAnime_Update(&this->skelAnime);
        Actor_PlaySfx_Flagged(&this->actor, NA_SE_EN_FOLLOWERS_BEAM_PRE - SFX_FLAG);
    }
}

void EnInvadepoh_InvasionHandler_DrawWarps(PlayState* play) {
    s32 i;
    EnInvadepohWarpEffect* warpEffect;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Xlu(play->state.gfxCtx);

    for (i = 0, warpEffect = sWarpEffects; i < 10; i++, warpEffect++) {
        if (warpEffect->timer > 0) {
            u32 warpScrollX1 = (play->gameplayFrames + (u8)(i * 0x10)) % 0x80;
            u32 warpScrollY2 = (play->gameplayFrames * -0xF) % 0x100;

            Matrix_Translate(warpEffect->pos.x, warpEffect->pos.y, warpEffect->pos.z, MTXMODE_NEW);
            Matrix_Scale(0.1f, 0.1f, 0.1f, MTXMODE_APPLY);
            gDPPipeSync(POLY_XLU_DISP++);
            gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 255, 255, 170, warpEffect->alpha);
            gDPSetEnvColor(POLY_XLU_DISP++, 255, 50, 0, 0);
            gSPSegment(
                POLY_XLU_DISP++, 0x8,
                Gfx_TwoTexScroll(play->state.gfxCtx, 0, warpScrollX1, 0, 0x20, 0x40, 1, 0, warpScrollY2, 0x20, 0x40));
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_02E510);
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void EnInvadepoh_InvasionHandler_Draw(Actor* thisx, PlayState* play) {
    EnInvadepoh_InvasionHandler_DrawWarps(play);
}

s32 EnInvadepoh_Alien_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                       Actor* thisx, Gfx** gfx) {
    return false;
}

void EnInvadepoh_Alien_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* pos, Actor* thisx, Gfx** gfx) {
    static Vec3f sFocusOffset = { 2000.0f, 1000.0f, 0.0f };
    EnInvadepoh* this = THIS;

    if ((limbIndex == ALIEN_LIMB_LEFT_EYE) && (this->eyeBeamAlpha != 0)) {
        Matrix_Push();
        Matrix_RotateZS(-0x53ED, MTXMODE_APPLY);
        Matrix_RotateYS(-0x3830, MTXMODE_APPLY);
        Matrix_Scale(1.0f, 1.0f, 1.5f, MTXMODE_APPLY);
        Matrix_Get(&sAlienLeftEyeBeamMtxF);
        Matrix_Pop();
    } else if ((limbIndex == ALIEN_LIMB_RIGHT_EYE) && (this->eyeBeamAlpha != 0)) {
        Matrix_Push();
        Matrix_RotateZS(-0x53ED, MTXMODE_APPLY);
        Matrix_RotateYS(-0x47D0, MTXMODE_APPLY);
        Matrix_Scale(1.0f, 1.0f, 1.5f, MTXMODE_APPLY);
        Matrix_Get(&sAlienRightEyeBeamMtxF);
        Matrix_Pop();
    }
    if (limbIndex == ALIEN_LIMB_HEAD) {
        Matrix_MultVec3f(&sFocusOffset, &this->actor.focus.pos);
    }
}

void EnInvadepoh_Alien_Draw(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Xlu(play->state.gfxCtx);
    Matrix_Push();

    if (this->shouldDraw) {
        if (this->alpha == 255) {
            Gfx_SetupDL25_Opa(play->state.gfxCtx);
            AnimatedMat_Draw(play, sAlienEmptyTexAnim);
            Scene_SetRenderModeXlu(play, 0, 1);
            gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);
            POLY_OPA_DISP = SkelAnime_DrawFlex(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                               this->skelAnime.dListCount, EnInvadepoh_Alien_OverrideLimbDraw,
                                               EnInvadepoh_Alien_PostLimbDraw, &this->actor, POLY_OPA_DISP);
        } else {
            AnimatedMat_Draw(play, sAlienEmptyTexAnim);
            Scene_SetRenderModeXlu(play, 1, 2);
            gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, this->alpha);
            POLY_XLU_DISP = SkelAnime_DrawFlex(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                               this->skelAnime.dListCount, EnInvadepoh_Alien_OverrideLimbDraw,
                                               EnInvadepoh_Alien_PostLimbDraw, &this->actor, POLY_XLU_DISP);
        }

        if (this->eyeBeamAlpha != 0) {
            Gfx* ptr;

            AnimatedMat_Draw(play, sAlienEyeBeamTexAnim);

            OPEN_DISPS(play->state.gfxCtx);
            ptr = POLY_XLU_DISP;

            gDPPipeSync(ptr++);
            gDPSetPrimColor(ptr++, 0, 0xFF, 240, 180, 100, 60);
            gDPSetEnvColor(ptr++, 255, 255, 255, 100.0f / 170.0f * this->eyeBeamAlpha);

            Matrix_Mult(&sAlienLeftEyeBeamMtxF, MTXMODE_NEW);
            gSPMatrix(ptr++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(ptr++, gAlienEyeBeamDL);

            Matrix_Mult(&sAlienRightEyeBeamMtxF, MTXMODE_NEW);
            gSPMatrix(ptr++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(ptr++, gAlienEyeBeamDL);

            POLY_XLU_DISP = ptr;
            CLOSE_DISPS(play->state.gfxCtx);
        }
    }

    if (this->shouldDrawDeathFlash) {
        Matrix_SetTranslateRotateYXZ(this->actor.world.pos.x, this->actor.world.pos.y + 68.0f, this->actor.world.pos.z,
                                     &this->actor.shape.rot);
        Matrix_Scale(this->deathFlashScale.x, this->deathFlashScale.y, this->deathFlashScale.z, MTXMODE_APPLY);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gAlienDeathFlashDL);
    }

    if (this->shouldDraw) {
        Gfx* ptr;
        Vec3f glowOffset;
        Vec3f glowPos;
        s32 glowAlpha;

        OPEN_DISPS(play->state.gfxCtx);
        ptr = POLY_XLU_DISP;

        ptr = Gfx_SetupDL20_NoCD(ptr);

        gDPSetDither(ptr++, G_CD_NOISE);
        gDPSetCombineLERP(ptr++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE,
                          0);

        Matrix_Mult(&play->billboardMtxF, MTXMODE_NEW);
        Matrix_MultVecZ(60.0f, &glowOffset);

        glowPos.x = this->actor.world.pos.x + glowOffset.x;
        glowPos.y = this->actor.world.pos.y + glowOffset.y + 68.0f;
        glowPos.z = this->actor.world.pos.z + glowOffset.z;

        Matrix_Translate(glowPos.x, glowPos.y, glowPos.z, MTXMODE_NEW);
        Matrix_Scale(0.25f, 0.25f, 0.25f, MTXMODE_APPLY);

        glowAlpha = 100.0f / 255.0f * this->alpha;

        gSPDisplayList(ptr++, gameplay_keep_DL_029CB0);
        gDPSetPrimColor(ptr++, 0, 0, 240, 180, 100, glowAlpha);
        gSPMatrix(ptr++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(ptr++, gameplay_keep_DL_029CF0);

        POLY_XLU_DISP = ptr;

        if ((this->alpha > 128) && EnInvadepoh_Alien_LensFlareDepthCheck(play, &glowPos)) {
            Environment_DrawLensFlare(play, &play->envCtx, &play->view, play->state.gfxCtx, glowPos, 10.0f, 9.0f, 0, 0);
        }

        CLOSE_DISPS(play->state.gfxCtx);
    }

    Matrix_Pop();

    CLOSE_DISPS(play->state.gfxCtx);
}

s32 EnInvadepoh_Cow_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                     Actor* thisx) {
    if (limbIndex == COW_LIMB_NOSE_RING) {
        EnInvadepoh* this = THIS;

        rot->x -= this->actor.shape.rot.x;
    }
    return false;
}

void EnInvadepoh_Cow_Draw(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;

    Gfx_SetupDL37_Opa(play->state.gfxCtx);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, (s32)this->skelAnime.dListCount,
                          EnInvadepoh_Cow_OverrideLimbDraw, NULL, &this->actor);
}

void EnInvadepoh_CowTail_Draw(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;

    Gfx_SetupDL37_Opa(play->state.gfxCtx);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount, NULL,
                          NULL, &this->actor);
}

s32 EnInvadepoh_Romani_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                        Actor* thisx) {
    if (limbIndex == ROMANI_LIMB_HEAD) {
        EnInvadepoh* this = THIS;

        rot->x += this->interactInfo.headRot.y;
        rot->y += this->interactInfo.headRot.z;
        rot->z += this->interactInfo.headRot.x;
    } else if (limbIndex == ROMANI_LIMB_TORSO) {
        EnInvadepoh* this = THIS;

        // The rot variable here is in model space, whereas the interactInfo variables are in world space.
        // Romani's torso is lying on its side in model space, which is why this assignment looks weird.
        rot->x += (s16)(this->interactInfo.torsoRotScaleY * this->interactInfo.headRot.y);
        rot->z += this->interactInfo.torsoRotX;
    }
    return false;
}

void EnInvadepoh_Romani_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* pos, Actor* thisx) {
    static Vec3f sFocusOffset = { 400.0f, 270.0f, 0.0f };
    EnInvadepoh* this = THIS;

    if (limbIndex == ROMANI_LIMB_LEFT_HAND) {
        OPEN_DISPS(play->state.gfxCtx);

        gSPDisplayList(POLY_OPA_DISP++, gRomaniBowDL);

        CLOSE_DISPS(play->state.gfxCtx);
    } else if (limbIndex == ROMANI_LIMB_HEAD) {
        Matrix_MultVec3f(&sFocusOffset, &this->actor.focus.pos);
    }
}

void EnInvadepoh_Romani_Draw(Actor* thisx, PlayState* play) {
    EnInvadepoh* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Opa(play->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x09, sRomaniMouthTextures[this->interactInfo.mouthAnim.curIndex]);
    gSPSegment(POLY_OPA_DISP++, 0x08, sRomaniEyeTextures[this->interactInfo.eyeAnim.curIndex]);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnInvadepoh_Romani_OverrideLimbDraw, EnInvadepoh_Romani_PostLimbDraw, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}

void EnInvadepoh_Ufo_Draw(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = THIS;
    Vec3f flashPos;

    Matrix_Push();
    Matrix_Mult(&play->billboardMtxF, MTXMODE_NEW);
    Matrix_MultVecZ(200.0f, &flashPos);
    Matrix_Pop();
    flashPos.x += this->actor.world.pos.x;
    flashPos.y += this->actor.world.pos.y;
    flashPos.z += this->actor.world.pos.z;
    EnInvadepoh_Ufo_ReplaceTranslation(&flashPos);
    Matrix_ReplaceRotation(&play->billboardMtxF);
    Matrix_RotateZS(this->angle, MTXMODE_APPLY);

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Xlu(play->state.gfxCtx);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(POLY_XLU_DISP++, 0xFF, 0x80, 255, 255, 0, 180);
    gDPSetEnvColor(POLY_XLU_DISP++, 255, 50, 0, 0);
    gSPDisplayList(POLY_XLU_DISP++, gEffFlash1DL);

    if (EnInvadepoh_Alien_LensFlareDepthCheck(play, &flashPos)) {
        Environment_DrawLensFlare(play, &play->envCtx, &play->view, play->state.gfxCtx, flashPos, 20.0f, 9.0f, 0, 0);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

s32 EnInvadepoh_Dog_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                     Actor* thisx) {
    if ((limbIndex == DOG_LIMB_HEAD) || (limbIndex == DOG_LIMB_RIGHT_FACE_HAIR) ||
        (limbIndex == DOG_LIMB_LEFT_FACE_HAIR)) {
        EnInvadepoh* this = THIS;

        rot->x += this->interactInfo.headRot.x;
        rot->y += this->interactInfo.headRot.y;
        rot->z += this->interactInfo.headRot.z;
    }
    return false;
}

void EnInvadepoh_Dog_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* pos, Actor* thisx) {
    if (limbIndex == DOG_LIMB_HEAD) {
        EnInvadepoh* this = THIS;

        Matrix_MultVecY(20.0f, &this->actor.focus.pos);
    }
}

void EnInvadepoh_Dog_Draw(Actor* thisx, PlayState* play) {
    EnInvadepoh* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Opa(play->state.gfxCtx);
    gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 200, 0);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnInvadepoh_Dog_OverrideLimbDraw, EnInvadepoh_Dog_PostLimbDraw, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}

s32 EnInvadepoh_Cremia_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                        Actor* thisx) {
    if (limbIndex == CREMIA_LIMB_HEAD) {
        EnInvadepoh* this = THIS;

        rot->x += this->interactInfo.headRot.y;
        rot->y += this->interactInfo.headRot.z;
        rot->z += this->interactInfo.headRot.x;
    } else if (limbIndex == CREMIA_LIMB_TORSO) {
        EnInvadepoh* this = THIS;

        // The rot variable here is in model space, whereas the interactInfo variables are in world space.
        // Cremia's torso is lying on its side in model space, which is why this assignment looks weird.
        rot->x += (s16)(this->interactInfo.torsoRotScaleY * this->interactInfo.headRot.y);
    }
    return false;
}

void EnInvadepoh_Cremia_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* pos, Actor* thisx) {
    if (limbIndex == CREMIA_LIMB_HEAD) {
        EnInvadepoh* this = THIS;

        Matrix_MultZero(&this->actor.focus.pos);
    }
}

void EnInvadepoh_Cremia_Draw(Actor* thisx, PlayState* play) {
    EnInvadepoh* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Opa(play->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x09, sCremiaMouthTextures[this->interactInfo.mouthAnim.curIndex]);
    gSPSegment(POLY_OPA_DISP++, 0x08, sCremiaEyeTextures[this->interactInfo.eyeAnim.curIndex]);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnInvadepoh_Cremia_OverrideLimbDraw, EnInvadepoh_Cremia_PostLimbDraw, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}
