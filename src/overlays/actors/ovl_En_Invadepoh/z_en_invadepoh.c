#include "z_en_invadepoh.h"
#include "overlays/actors/ovl_En_Door/z_en_door.h"
#include "assets/objects/gameplay_keep/gameplay_keep.h"

#define FLAGS 0x00000010

#define THIS ((EnInvadepoh*)thisx)

#define ENINVADEPOH_INVADER_ACTIVE 1
#define ENINVADEPOH_INVADER_CLOSEST 2

typedef enum {
    ENINVADEPOH_EVENT_UNSET,
    ENINVADEPOH_EVENT_WAIT,
    ENINVADEPOH_EVENT_ACTIVE,
    ENINVADEPOH_EVENT_CLEAR,
    ENINVADEPOH_EVENT_FAILED
} EnInvadepohEventState;

#if 1 // function prototypes
void EnInvadepoh_Init(Actor* thisx, PlayState* play);
void EnInvadepoh_Destroy(Actor* thisx, PlayState* play);
void EnInvadepoh_Event_Update(Actor* thisx, PlayState* play2);

// Update functions
void EnInvadepoh_Invader_WaitForObject(Actor* thisx, PlayState* play2);
void EnInvadepoh_Invader_Update(Actor* thisx, PlayState* play2);
void EnInvadepoh_Cow_WaitForObject(Actor* thisx, PlayState* play2);
void EnInvadepoh_Cow_Update(Actor* thisx, PlayState* play2);
void EnInvadepoh_CowTail_WaitForObject(Actor* thisx, PlayState* play2);
void EnInvadepoh_CowTail_Update(Actor* thisx, PlayState* play2);
void EnInvadepoh_AbductedRomani_Update(Actor* thisx, PlayState* play2);
void EnInvadepoh_AbductedRomani_WaitForObject(Actor* thisx, PlayState* play2);
void EnInvadepoh_ConfusedRomani_WaitForObject(Actor* thisx, PlayState* play2);
void EnInvadepoh_ConfusedRomani_Update(Actor* thisx, PlayState* play2);
void EnInvadepoh_LightBall_Update(Actor* thisx, PlayState* play2);
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
void EnInvadepoh_Cremia_WaitForObject(Actor* thisx, PlayState* play2);
void EnInvadepoh_Cremia_WaitForEvent(Actor* thisx, PlayState* play2);
void EnInvadepoh_Cremia_Update(Actor* thisx, PlayState* play2);
void EnInvadepoh_Night3Romani_WaitForObject(Actor* thisx, PlayState* play2);
void EnInvadepoh_Night3Romani_WaitForEvent(Actor* thisx, PlayState* play2);
void EnInvadepoh_Night3Romani_Update(Actor* thisx, PlayState* play2);
void EnInvadepoh_Abuductor_WaitForObject(Actor* thisx, PlayState* play2);

// Draw functions
void EnInvadepoh_Abductor_Update(Actor* thisx, PlayState* play2);
void EnInvadepoh_Event_Draw(Actor* thisx, PlayState* play);
void EnInvadepoh_Alien_Draw(Actor* thisx, PlayState* play2);
void EnInvadepoh_Cow_Draw(Actor* thisx, PlayState* play2);
void EnInvadepoh_CowTail_Draw(Actor* thisx, PlayState* play2);
void EnInvadepoh_Romani_Draw(Actor* thisx, PlayState* play);
void EnInvadepoh_LightBall_Draw(Actor* thisx, PlayState* play2);
void EnInvadepoh_Dog_Draw(Actor* thisx, PlayState* play);
void EnInvadepoh_Cremia_Draw(Actor* thisx, PlayState* play);

// Action functions
void EnInvadepoh_Event_SetupWait(EnInvadepoh* this);
void EnInvadepoh_Event_Wait(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Event_SetupQueueInvasionCs(EnInvadepoh* this);
void EnInvadepoh_Event_QueueInvasionCs(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Event_SetupInvasionCs(EnInvadepoh* this);
void EnInvadepoh_Event_InvasionCs(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Event_SetupInvasion(EnInvadepoh* this);
void EnInvadepoh_Event_Invasion(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Event_SetupQueueVictoryCs(EnInvadepoh* this);
void EnInvadepoh_Event_QueueVictoryCs(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Event_SetupVictoryCs(EnInvadepoh* this);
void EnInvadepoh_Event_VictoryCs(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Event_SetupRomaniReward(EnInvadepoh* this);
void EnInvadepoh_Event_RomaniReward(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Event_SetupGoodEnd(EnInvadepoh* this);
void EnInvadepoh_Event_GoodEnd(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Event_SetupFailure(EnInvadepoh* this);
void EnInvadepoh_Event_Failure(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Event_SetupBadEnd(EnInvadepoh* this);
void EnInvadepoh_Event_BadEnd(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Invader_WaitForEvent(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Invade_WaitToRespawn(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Invader_SetupWarpIn(EnInvadepoh* this);
void EnInvadepoh_Invader_WarpIn(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Invader_SetupAttack(EnInvadepoh* this);
void EnInvadepoh_Invader_Attack(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Invader_Hitstun(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_Invader_SetupDeath(EnInvadepoh* this);
void EnInvadepoh_Invader_Death(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B48324(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B48374(EnInvadepoh* this);
void EnInvadepoh_func_80B483CC(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4843C(EnInvadepoh* this);
void EnInvadepoh_func_80B484EC(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B48588(EnInvadepoh* this);
void EnInvadepoh_func_80B48610(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B48848(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B48948(EnInvadepoh* this);
void EnInvadepoh_func_80B48AD4(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B48E4C(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B491EC(EnInvadepoh* this);
void EnInvadepoh_func_80B49228(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B492FC(EnInvadepoh* this);
void EnInvadepoh_func_80B4934C(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B49404(EnInvadepoh* this);
void EnInvadepoh_func_80B49454(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B49628(EnInvadepoh* this);
void EnInvadepoh_func_80B49670(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B497EC(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B49904(EnInvadepoh* this);
void EnInvadepoh_func_80B4994C(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B499BC(EnInvadepoh* this);
void EnInvadepoh_func_80B49A00(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B49C38(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B49DFC(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4A350(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4A570(EnInvadepoh* this);
void EnInvadepoh_func_80B4A5E4(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4A67C(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4A81C(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4ACF0(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4AD3C(EnInvadepoh* this);
void EnInvadepoh_func_80B4AD60(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4ADB8(EnInvadepoh* this);
void EnInvadepoh_func_80B4ADCC(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4AEC0(EnInvadepoh* this);
void EnInvadepoh_func_80B4AEDC(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4AF80(EnInvadepoh* this);
void EnInvadepoh_func_80B4AF94(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4B024(EnInvadepoh* this);
void EnInvadepoh_func_80B4B048(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4B484(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4B510(EnInvadepoh* this);
void EnInvadepoh_func_80B4B564(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4B724(EnInvadepoh* this);
void EnInvadepoh_func_80B4B768(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4B864(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4BC4C(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4C058(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4C1BC(EnInvadepoh* this);
void EnInvadepoh_func_80B4C218(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4C730(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4CB0C(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4CC70(EnInvadepoh* this);
void EnInvadepoh_func_80B4CCCC(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4D290(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4D480(EnInvadepoh* this, PlayState* play);

s32 EnInvadepoh_SnapToFloor(EnInvadepoh* this);
s32 EnInvadepoh_func_80B450C0(f32* arg0, f32* arg1, f32 arg2, f32 arg3, f32 arg4);
#endif

ActorInit En_Invadepoh_InitVars = {
    ACTOR_EN_INVADEPOH,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnInvadepoh),
    (ActorFunc)EnInvadepoh_Init,
    (ActorFunc)EnInvadepoh_Destroy,
    (ActorFunc)EnInvadepoh_Event_Update,
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

Vec3f D_80B4E934 = { 216.0f, -20.0f, 1395.0f };

s32 sEventState = ENINVADEPOH_EVENT_UNSET;

TexturePtr sRomaniEyeTextures[5] = {
    gRomaniEyeOpenTex, gRomaniEyeHalfTex, gRomaniEyeClosedTex, gRomaniEyeHappyTex, gRomaniEyeSadTex,
};
TexturePtr sRomaniMouthTextures[4] = {
    gRomaniMouthHappyTex,
    gRomaniMouthFrownTex,
    gRomaniMouthHangingOpenTex,
    gRomaniMouthSmileTex,
};
s8 sRomaniTexturesDesegmented = false;

TexturePtr sCremiaEyeTextures[6] = {
    gCremiaEyeOpenTex, gCremiaEyeHalfTex, gCremiaEyeClosedTex, gCremiaEyeHappyTex, gCremiaEyeAngryTex, gCremiaEyeSadTex,
};
TexturePtr sCremiaMouthTextures[4] = {
    gCremiaMouthNormalTex,
    gCremiaMouthSlightSmileTex,
    gCremiaMouthFrownTex,
    gCremiaMouthHangingOpenTex,
};
s8 sCremiaTexturesDesegmented = false;

s8 sRewardFinished = false;

MtxF sAlienLeftEyeBeam;
MtxF sAlienRightEyeBeam;
EnInvadepoh* sAlienInvaders[8];
u8 sAlienStateFlags[8];
s8 sAliensTooClose;
EnInvadepohWarpEffect D_80B50350[10];
EnInvadepoh* sLightBall;
EnInvadepoh* sRomani;
EnInvadepoh* sCremia;
AnimatedMaterial* sAlienEyeBeamTexAnim;
AnimatedMaterial* sAlienEmptyTexAnim;
s16 sCutsceneIds[3];
EnInvadepoh* sClosestAlien;

void EnInvadepoh_Invader_SetWarpInTime(s32 arg0, s32 arg1) {
    arg1 -= CLOCK_TIME(2, 30);
    arg1 = CLAMP_MIN(arg1, 0);

    if ((arg0 % 2) == 0) {
        gSaveContext.save.saveInfo.unk_E64[arg0 >> 1] = 
            (gSaveContext.save.saveInfo.unk_E64[arg0 >> 1] & 0xFFFF0000) | (arg1 & 0xFFFF);
    } else {
        gSaveContext.save.saveInfo.unk_E64[arg0 >> 1] =
            (gSaveContext.save.saveInfo.unk_E64[arg0 >> 1] & 0xFFFF) | ((arg1 & 0xFFFF) << 0x10);
    }
}

s32 EnInvadepoh_Invader_GetWarpInTime(s32 invaderIndex) {
    u32 var_v1;

    if ((invaderIndex % 2) == 0) {
        var_v1 = gSaveContext.save.saveInfo.unk_E64[invaderIndex >> 1] & 0xFFFF;
    } else {
        var_v1 = (gSaveContext.save.saveInfo.unk_E64[invaderIndex >> 1] & 0xFFFF0000) >> 0x10;
    }
    return var_v1 + CLOCK_TIME(2, 30);
}

void EnInvadepoh_Invader_SetKillCount(s32 arg0) {
    gSaveContext.save.saveInfo.unk_E64[4] = (gSaveContext.save.saveInfo.unk_E64[4] & ~0xFF) | (arg0 & 0xFF);
}

s32 EnInvadepoh_Invader_GetKillCount(void) {
    return gSaveContext.save.saveInfo.unk_E64[4] & 0xFF;
}

s32 EnInvadepoh_Invader_AddKill(void) {
    s32 sp1C = EnInvadepoh_Invader_GetKillCount();

    if (sp1C < 12) {
        sp1C++;
        EnInvadepoh_Invader_SetKillCount(sp1C);
    }
    return sp1C;
}

void EnInvadepoh_Invader_ResetWarpInTime(s32 arg0) {
    s32 sp1C = gSaveContext.save.time;

    if ((CURRENT_DAY == 1) && (sp1C >= CLOCK_TIME(2, 30)) && (sp1C < CLOCK_TIME(5, 15))) {
        s32 sp18 = (12 - EnInvadepoh_Invader_GetKillCount()) * 25.0f;

        EnInvadepoh_Invader_SetWarpInTime(arg0, sp1C + sp18);
    }
}

s32 EnInvadepoh_Invader_GetCurrentPoint(EnInvadepoh* this) {
    s32 i;
    s32 lastPoint = this->endPoint - 1;

    for (i = 0; i < lastPoint; i++) {
        if (this->progress < this->checkpoints[i]) {
            break;
        }
    }
    return i;
}

void EnInvadepoh_func_80B43BC8(EnInvadepoh* this, s8* arg1, Vec3f* arg2) {
    f32 var_fs0 = 0.0f;
    f32 var_fs2 = 0.0f;
    f32 temp_fs1 = 1.0f / this->pathLength;
    s32 temp_s5 = this->endPoint;
    s32 var_s2;
    Vec3f sp70;
    Vec3s* var_s0 = this->pathPoints;
    Vec3s* var_s1 = var_s0 + 1;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv0_2;

    for (var_s2 = 0; var_s2 < temp_s5; var_s2++) {
        sp70.x = var_s1->x - var_s0->x;
        sp70.y = var_s1->y - var_s0->y;
        sp70.z = var_s1->z - var_s0->z;
        temp_fv0_2 = Math3D_Vec3fMagnitude(&sp70);
        temp_fa1 = var_fs0 + temp_fv0_2;
        temp_fa0 = temp_fa1 * temp_fs1;
        if (this->progress <= temp_fa0) {
            *arg1 = var_s2;
            temp_fv0 = (this->progress - var_fs2) / (temp_fa0 - var_fs2);
            arg2->x = (temp_fv0 * sp70.x) + var_s0->x;
            arg2->y = (temp_fv0 * sp70.y) + var_s0->y;
            arg2->z = (temp_fv0 * sp70.z) + var_s0->z;
            return;
        }
        var_s0 = var_s1++;
        var_fs0 = temp_fa1;
        var_fs2 = temp_fa0;
    }
    *arg1 = temp_s5;
    arg2->x = this->pathPoints[temp_s5].x;
    arg2->y = this->pathPoints[temp_s5].y;
    arg2->z = this->pathPoints[temp_s5].z;
}

void EnInvadepoh_Invader_TurnToPath(EnInvadepoh* this, s16 arg1, s16 arg2) {
    s32 pad;
    Vec3s* sp40 = &this->pathPoints[this->currentPoint];
    Vec3s* sp3C = sp40 + 1;
    Vec3f sp30;
    Vec3f sp24;

    if (this->currentPoint != this->endPoint) {
        Math_Vec3s_ToVec3f(&sp30, sp40);
        Math_Vec3s_ToVec3f(&sp24, sp3C);
        Math_ScaledStepToS(&this->actor.shape.rot.y, Math_Vec3f_Yaw(&sp30, &sp24) + arg2, arg1);
    }
}

void EnInvadepoh_func_80B43E6C(EnInvadepoh* this, s16 arg1, s16 arg2, s16 arg3) {
    s32 pad;
    Vec3s* sp40 = &this->pathPoints[this->currentPoint];
    Vec3s* sp3C = sp40 + 1;
    Vec3f sp30;
    Vec3f sp24;

    if (this->currentPoint != this->endPoint) {
        Math_Vec3s_ToVec3f(&sp30, sp40);
        Math_Vec3s_ToVec3f(&sp24, sp3C);
        Math_SmoothStepToS(&this->actor.shape.rot.y, Math_Vec3f_Yaw(&sp30, &sp24), arg1, arg2, arg3);
    }
}

void EnInvadepoh_SetYawAlongPath(EnInvadepoh* this) {
    s32 pad;
    Vec3s* sp40 = &this->pathPoints[this->currentPoint];
    Vec3s* sp3C = sp40 + 1;
    Vec3f sp30;
    Vec3f sp24;

    Math_Vec3s_ToVec3f(&sp30, sp40);
    Math_Vec3s_ToVec3f(&sp24, sp3C);
    this->actor.shape.rot.y = Math_Vec3f_Yaw(&sp30, &sp24);
}

f32 EnInvadepoh_GetPathLength(EnInvadepoh* this) {
    s32 temp_s4 = this->endPoint + 1;
    s32 var_s1;
    Vec3f sp54;
    Vec3f sp48;
    Vec3s* var_s0 = this->pathPoints;
    f32 var_fs0 = 0.0f;

    Math_Vec3s_ToVec3f(&sp48, var_s0);
    var_s0++;
    for (var_s1 = 1; var_s1 < temp_s4; var_s1++, var_s0++) {
        Math_Vec3f_Copy(&sp54, &sp48);
        Math_Vec3s_ToVec3f(&sp48, var_s0);
        var_fs0 += Math3D_Distance(&sp54, &sp48);
    }
    return var_fs0;
}

void EnInvadepoh_SetPath(EnInvadepoh* this, PlayState* play) {
    Path* path = &play->setupPathList[ENINVADEPOH_GET_PARAM_7F00(&this->actor)];

    this->endPoint = path->count - 1;
    this->pathPoints = Lib_SegmentedToVirtual(path->points);
}

void EnInvadepoh_SetPosToPathPoint(EnInvadepoh* this, s32 arg1) {
    Math_Vec3s_ToVec3f(&this->actor.world.pos, &this->pathPoints[arg1]);
}

s32 EnInvadepoh_Invader_IsOnPath(EnInvadepoh* thisx, f32 arg1, f32 arg2) {
    EnInvadepoh* this = thisx; // TODO: why recast?
    Vec3s* currentPoint = &this->pathPoints[this->currentPoint];
    Vec3s* nextPoint = &this->pathPoints[this->currentPoint] + 1;
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
    if (distOffPath > (arg1 - arg2)) {
        return false;
    }

    pathSegmentLength = Math3D_XZLength(pathSegmentX, pathSegmentZ);
    distAlongPath = (travelSegmentZ * pathUnitVecZ) + (travelSegmentX * pathUnitVecX);
    if ((distAlongPath < 0.0f) || (pathSegmentLength < distAlongPath)) {
        return false;
    }
    return true;
}

s32 EnInvadepoh_func_80B44234(EnInvadepoh* this, Vec3f* arg1) {
    s32 var_s0;
    s32 temp_s3 = this->endPoint;
    Vec3s* var_s1;
    Vec3f sp48;
    f32 var_fs0 = FLT_MAX;
    s32 var_s4 = 0;
    f32 temp_fv0;

    for (var_s0 = 0, var_s1 = this->pathPoints; var_s0 < temp_s3; var_s0++, var_s1++) {
        Math_Vec3s_ToVec3f(&sp48, var_s1);
        temp_fv0 = Math3D_Vec3fDistSq(&sp48, arg1);
        if (temp_fv0 < var_fs0) {
            var_fs0 = temp_fv0;
            var_s4 = var_s0;
        }
    }
    return var_s4;
}

void EnInvadepoh_Invader_SetProgress(EnInvadepoh* this) {
    s32 pad;
    s32 currentTime = gSaveContext.save.time;
    s32 warpInTime = EnInvadepoh_Invader_GetWarpInTime(ENINVADEPOH_GET_PARAM_7(&this->actor));

    if (sEventState == ENINVADEPOH_EVENT_WAIT) {
        this->progress = 0.0f;
    } else if (sEventState == ENINVADEPOH_EVENT_ACTIVE) {
        if ((currentTime - warpInTime) < 0) {
            this->progress = 0.0f;
        } else {
            this->progress = (currentTime - warpInTime) * (1.0f / 3600.0f);
            if (this->progress > 1.0f) {
                this->progress = 1.0f;
            }
        }
    }
    this->currentPoint = EnInvadepoh_Invader_GetCurrentPoint(this);
}

void EnInvadepoh_Invader_SetCheckpoints(EnInvadepoh* this) {
    f32 temp_fs3 = 1.0f / this->pathLength;
    s32 temp_s4 = this->endPoint;
    s32 var_s1;
    Vec3f sp54;
    Vec3f sp48;
    Vec3s* var_s0 = this->pathPoints;
    f32 var_fs0 = 0.0f;
    f32* var_s2;

    Math_Vec3s_ToVec3f(&sp48, var_s0);
    var_s0++;
    var_s2 = this->checkpoints;
    for (var_s1 = 1; var_s1 < temp_s4; var_s1++, var_s0++, var_s2++) {
        Math_Vec3f_Copy(&sp54, &sp48);
        Math_Vec3s_ToVec3f(&sp48, var_s0);
        var_fs0 += Math3D_Distance(&sp54, &sp48);
        *var_s2 = var_fs0 * temp_fs3;
        if (*var_s2 < 0.0f) {
            *var_s2 = 0.0f;
        } else if (*var_s2 > 1.0f) {
            *var_s2 = 1.0f;
        }
    }
}

void EnInvadepoh_Invader_SetupPath(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_SetPath(this, play);
    this->pathLength = EnInvadepoh_GetPathLength(this);
    EnInvadepoh_Invader_SetCheckpoints(this);
}

void EnInvadepoh_func_80B444F4(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_SetPath(this, play);
}

void EnInvadepoh_func_80B44514(EnInvadepoh* this) {
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
    if ((gSaveContext.save.time < CLOCK_TIME(2, 00)) || (gSaveContext.save.time >= CLOCK_TIME(6, 00))) {
        this->progress = 0.0f;
    } else if ((gSaveContext.save.time >= CLOCK_TIME(2, 15)) && (gSaveContext.save.time < CLOCK_TIME(6, 00))) {
        this->progress = 1.0f;
    } else {
        f32 temp = (gSaveContext.save.time - CLOCK_TIME(2, 00)) * (1.0f / (CLOCK_TIME(2, 15) - CLOCK_TIME(2, 00)));

        this->progress = temp;
        this->progress = CLAMP(this->progress, 0.0f, 1.0f);
    }
}

void EnInvadepoh_BarnRomani_SetupPath(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_SetPath(this, play);
}

void EnInvadepoh_func_80B44640(EnInvadepoh* this) {
    if (this->currentPoint < this->endPoint) {
        this->currentPoint++;
    }
}

void EnInvadepoh_Dog_SetupPath(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_SetPath(this, play);
    this->pathStep = 1;
}

void EnInvadepoh_func_80B44690(EnInvadepoh* this) {
    this->currentPoint += this->pathStep;
    if (this->currentPoint >= this->endPoint) {
        this->currentPoint = 0;
    } else if (this->currentPoint < 0) {
        this->currentPoint = this->endPoint - 1;
    }
}

void EnInvadepoh_func_80B446D0(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_SetPath(this, play);
    this->pathLength = EnInvadepoh_GetPathLength(this);
}

void EnInvadepoh_func_80B44700(EnInvadepoh* this) {
    if ((gSaveContext.save.time < CLOCK_TIME(20, 00)) && (gSaveContext.save.time >= CLOCK_TIME(6, 00))) {
        this->progress = 0.0f;
    } else if ((gSaveContext.save.time >= CLOCK_TIME(20, 14) + 15) || (gSaveContext.save.time < CLOCK_TIME(6, 00))) {
        this->progress = 1.0f;
    } else {
        f32 temp =
            (gSaveContext.save.time - CLOCK_TIME(20, 00)) * (1.0f / (CLOCK_TIME(20, 14) + 15 - CLOCK_TIME(20, 00)));

        this->progress = temp;
        this->progress = CLAMP(this->progress, 0.0f, 1.0f);
    }
}

void EnInvadepoh_Invader_SetPositionAlongPath(EnInvadepoh* this, PlayState* play) {
    s32 pad;
    Vec3s* sp60;
    s32 pad2;
    Vec3f sp50;
    Vec3f sp44;
    f32 sp40 = this->actor.world.pos.y;
    f32 sp3C;
    f32 sp38;

    sp60 = &this->pathPoints[this->currentPoint];
    sp3C = (this->currentPoint < 1) ? 0.0f : this->checkpoints[this->currentPoint - 1];
    sp38 = (this->currentPoint < (this->endPoint - 1)) ? this->checkpoints[this->currentPoint] : 1.0f;

    if (sp38 - sp3C < 0.001f) {
        Math_Vec3s_ToVec3f(&this->unk_314, sp60);
    } else {
        f32 sp34 = this->progress - sp3C;
        f32 sp30 = sp38 - this->progress;
        f32 sp2C = 1.0f / (sp38 - sp3C);
        s32 pad3;

        Math_Vec3s_ToVec3f(&sp50, sp60);
        Math_Vec3s_ToVec3f(&sp44, sp60 + 1);
        this->unk_314.x = ((sp50.x * sp30) + (sp44.x * sp34)) * sp2C;
        this->unk_314.y = ((sp50.y * sp30) + (sp44.y * sp34)) * sp2C;
        this->unk_314.z = ((sp50.z * sp30) + (sp44.z * sp34)) * sp2C;
    }
    Math_Vec3f_Copy(&this->actor.world.pos, &this->unk_314);
    func_800B4AEC(play, &this->actor, 0.0f);
    if (this->actor.floorHeight > BGCHECK_Y_MIN + 1.0f) {
        if (sp40 < this->actor.floorHeight) {
            if (this->actor.velocity.y < 0.0f) {
                this->actor.velocity.y = 0.0f;
            } else {
                this->actor.velocity.y += 2.0f;
                this->actor.velocity.y = CLAMP_MAX(this->actor.velocity.y, 30.0f);
            }
            this->actor.world.pos.y = this->actor.velocity.y + sp40;
            if (this->actor.floorHeight < this->actor.world.pos.y) {
                this->actor.world.pos.y = this->actor.floorHeight;
            }
        } else {
            if (this->actor.velocity.y > 0.0f) {
                this->actor.velocity.y = 0.0f;
            } else {
                this->actor.velocity.y -= 2.0f;
            }
            this->actor.world.pos.y = this->actor.velocity.y + sp40;
            if (this->actor.world.pos.y < this->actor.floorHeight) {
                this->actor.world.pos.y = this->actor.floorHeight;
                this->actor.velocity.y = CLAMP_MIN(this->actor.velocity.y, -30.0f);
            }
        }
    } else {
        this->actor.world.pos.y = sp40;
    }
}

void EnInvadepoh_Invader_Knockback(EnInvadepoh* this, PlayState* play) {
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
    Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 40.0f, 0.0f, 5);
}

void EnInvadepoh_func_80B44B78(EnInvadepoh* this) {
}

s32 EnInvadepoh_func_80B44B84(EnInvadepoh* this, PlayState* play, f32 arg2, f32 arg3) {
    s32 pad; // TODO: recast?
    Vec3s* temp_v0_2 = &this->pathPoints[this->currentPoint + 1];
    s32 sp2C =
        EnInvadepoh_func_80B450C0(&this->actor.world.pos.x, &this->actor.world.pos.z, temp_v0_2->x, temp_v0_2->z, arg2);

    func_800B4AEC(play, &this->actor, arg3);
    EnInvadepoh_SnapToFloor(this);
    return sp2C;
}

void EnInvadepoh_func_80B44C24(EnInvadepoh* this, PlayState* play) {
    s32 pad; // TODO: recast?
    f32 sp18 = this->actor.world.pos.y;

    EnInvadepoh_func_80B43BC8(this, &this->currentPoint, &this->actor.world.pos);
    this->actor.world.pos.y = sp18;
    func_800B4AEC(play, &this->actor, 50.0f);
    EnInvadepoh_SnapToFloor(this);
}

s32 EnInvadepoh_func_80B44C80(EnInvadepoh* this, PlayState* play) {
    Vec3s* temp_a2 = &this->pathPoints[this->currentPoint];
    Vec3s* temp_v0_2;
    s32 var_v1;
    u32 var_v0;
    f32 temp_v0_2x;
    f32 temp_v0_2z;
    f32 temp_a2x;
    f32 temp_a2z;
    Vec3f sp6C;
    Vec3f sp60;
    Vec3f sp54;
    Vec3f sp48;
    f32 sp44;
    s32 sp40 = 0;

    var_v1 = this->currentPoint + this->pathStep;

    if (var_v1 >= this->endPoint) {
        var_v1 = 0;
    } else if (var_v1 < 0) {
        var_v1 = this->endPoint - 1;
    }

    temp_v0_2 = &this->pathPoints[var_v1];

    temp_a2x = temp_a2->x;
    temp_a2z = temp_a2->z;
    temp_v0_2x = temp_v0_2->x;
    temp_v0_2z = temp_v0_2->z;

    sp6C.x = temp_v0_2x - temp_a2x;
    sp6C.y = 0.0f;
    sp6C.z = temp_v0_2z - temp_a2z;

    sp60.x = temp_v0_2x - this->actor.world.pos.x;
    sp60.y = 0.0f;
    sp60.z = temp_v0_2z - this->actor.world.pos.z;

    sp54.x = temp_a2x - this->actor.world.pos.x;
    sp54.y = 0.0f;
    sp54.z = temp_a2z - this->actor.world.pos.z;

    if (this->actor.speed > 0.0f) {
        if (Math3D_AngleBetweenVectors(&sp6C, &sp60, &sp44)) {
            sp40 = 1;
        } else if (sp44 <= 0.0f) {
            sp40 = 1;
        }
    }
    sp48.x = ((sp60.x + sp54.x) * 0.9f) + sp6C.x;
    sp48.y = 0.0f;
    sp48.z = ((sp60.z + sp54.z) * 0.9f) + sp6C.z;

    Math_SmoothStepToS(&this->actor.world.rot.y, Math_Atan2S_XY(sp48.z, sp48.x), 4, 0xFA0, 0x64);
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 15.0f, 0.0f,
                            EnInvadepoh_Invader_IsOnPath(this, 50.0f, 15.0f) ? UPDBGCHECKINFO_FLAG_4 : UPDBGCHECKINFO_FLAG_4 | UPDBGCHECKINFO_FLAG_1);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.world.rot.y, 3, 0x1F40, 0x64);
    return sp40;
}

void EnInvadepoh_func_80B44E90(EnInvadepoh* this, PlayState* play) {
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 15.0f, 0.0f, 5);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.world.rot.y, 3, 0x1F40, 0x64);
}

void EnInvadepoh_func_80B44EFC(EnInvadepoh* this, PlayState* play) {
    s32 pad; // TODO: recast?
    f32 sp18 = this->actor.world.pos.y;

    EnInvadepoh_func_80B43BC8(this, &this->currentPoint, &this->actor.world.pos);
    this->actor.world.pos.y = sp18;
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
    TexturePtr* var_s0;
    s32 i;

    if (!sCremiaTexturesDesegmented) {
        sCremiaTexturesDesegmented = true;
        for (i = 0, var_s0 = sCremiaEyeTextures; i < 6; i++, var_s0++) {
            *var_s0 = Lib_SegmentedToVirtual(*var_s0);
        }
        for (i = 0, var_s0 = sCremiaMouthTextures; i < 4; i++, var_s0++) {
            *var_s0 = Lib_SegmentedToVirtual(*var_s0);
        }
    }
}

void EnInvadepoh_Alien_SetTexAnim(void) {
    sAlienEmptyTexAnim = Lib_SegmentedToVirtual(gAlienEmptyTexAnim);
    sAlienEyeBeamTexAnim = Lib_SegmentedToVirtual(gAlienEyeBeamTexAnim);
}

s32 EnInvadepoh_func_80B450C0(f32* arg0, f32* arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 sp1C = arg2 - *arg0;
    f32 sp18 = arg3 - *arg1;
    f32 temp_fv0 = Math3D_XZLength(sp1C, sp18);

    if (arg4 < temp_fv0) {
        f32 temp_fv1 = arg4 / temp_fv0;

        *arg0 += temp_fv1 * sp1C;
        *arg1 += temp_fv1 * sp18;
        return false;
    } else {
        *arg0 = arg2;
        *arg1 = arg3;
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

void EnInvadepoh_Event_CheckState(EnInvadepoh* this, PlayState* play) {
    if (sEventState == ENINVADEPOH_EVENT_UNSET) {
        if (CURRENT_DAY < 1) {
            sEventState = ENINVADEPOH_EVENT_WAIT;
        } else if (CURRENT_DAY == 1) {
            s32 sp2C = gSaveContext.save.time;

            if ((sp2C < CLOCK_TIME(2, 30)) || (sp2C >= CLOCK_TIME(6, 00))) {
                sEventState = ENINVADEPOH_EVENT_WAIT;
            } else if (sp2C < CLOCK_TIME(5, 15)) {
                s32 var_s0;
                s32 var_s1 = CLOCK_TIME(5, 15);
                s32 temp;

                for (var_s0 = 0; var_s0 < this->spawnCount; var_s0++) {
                    s32 temp_v0 = EnInvadepoh_Invader_GetWarpInTime(var_s0);

                    var_s1 = MIN(temp_v0, var_s1);
                }
                if (sp2C < var_s1 + 3601) { // 79 in-game minutes
                    sEventState = ENINVADEPOH_EVENT_ACTIVE;
                }
            }
        }
        if (sEventState == ENINVADEPOH_EVENT_UNSET) {
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_22_01)) {
                sEventState = ENINVADEPOH_EVENT_CLEAR;
            } else {
                sEventState = ENINVADEPOH_EVENT_FAILED;
            }
        }
    }
}

void EnInvadepoh_Event_SpawnAliens(EnInvadepoh* this, PlayState* play) {
    s32 pathIndex = ENINVADEPOH_GET_PARAM_7F00(&this->actor);
    s32 i;

    for (i = 0; i < this->spawnCount; i++) {
        sAlienInvaders[i] = (EnInvadepoh*)Actor_Spawn(
            &play->actorCtx, play, ACTOR_EN_INVADEPOH, this->actor.world.pos.x, this->actor.world.pos.y,
            this->actor.world.pos.z, 0, 0, 0, ENINVADEPOH_SET_PARAMS(pathIndex, ENINVADEPOH_ALIEN_INVADER, i));
        if (pathIndex != 0xFF) {
            Path* path = &play->setupPathList[pathIndex];

            pathIndex = path->unk1;
        }
    }
}

void EnInvadepoh_func_80B453F4(EnInvadepoh* this, PlayState* play, s32 arg2) {
    Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EN_INVADEPOH, this->actor.home.pos.x,
                       this->actor.home.pos.y, this->actor.home.pos.z, 0, 0, 0,
                       ENINVADEPOH_SET_PARAMS(0, ENINVADEPOH_COW, arg2));
}

void EnInvadepoh_func_80B45460(EnInvadepoh* this, PlayState* play) {
    Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EN_INVADEPOH, this->actor.home.pos.x,
                       this->actor.home.pos.y, this->actor.home.pos.z, 0, 0, 0,
                       ENINVADEPOH_SET_PARAMS(0, ENINVADEPOH_ROMANI_ABDUCTED, 0));
}

void EnInvadepoh_Event_SpawnLightBall(EnInvadepoh* this, PlayState* play) {
    sLightBall =
        (EnInvadepoh*) Actor_Spawn(&play->actorCtx, play, ACTOR_EN_INVADEPOH, this->actor.world.pos.x, this->actor.world.pos.y,
                    this->actor.world.pos.z, 0, 0, 0, ENINVADEPOH_SET_PARAMS(0, ENINVADEPOH_LIGHT_BALL, 0));
}

void EnInvadepoh_func_80B45518(Vec3f* arg0) {
    MtxF* temp_v0 = Matrix_GetCurrent();

    temp_v0->mf[3][0] = arg0->x;
    temp_v0->mf[3][1] = arg0->y;
    temp_v0->mf[3][2] = arg0->z;
}

s32 EnInvadepoh_func_80B45550(EnInvadepoh* this, PlayState* play, f32 arg2, s32 arg3) {
    Actor* doorActor = play->actorCtx.actorLists[ACTORCAT_DOOR].first;
    EnDoor* door;
    s32 sp34 = false;

    while (doorActor != NULL) {
        if ((doorActor->id == ACTOR_EN_DOOR) && (doorActor->update != NULL)) {
            door = (EnDoor*)doorActor;
            if ((door->dyna.actor.room == this->actor.room) &&
                (Math3D_Vec3fDistSq(&door->dyna.actor.world.pos, &this->actor.world.pos) < arg2)) {

                door->unk_1A7 = arg3;
                sp34 = true;
                break;
            }
        }
        doorActor = doorActor->next;
    }
    return sp34;
}

void EnInvadepoh_Romani_SetTextId(EnInvadepoh* this, PlayState* play, u16 textId) {
    this->textId = textId;
    Message_StartTextbox(play, textId, &this->actor);
}

void EnInvadepoh_Event_SetCutscenes(EnInvadepoh* this) {
    s16 csId = this->actor.csId;
    s32 i;

    for (i = 0; i < 3; i++) {
        sCutsceneIds[i] = csId;
        csId = CutsceneManager_GetAdditionalCsId(csId);
    }
}

s32 EnInvadepoh_func_80B456A8(PlayState* play, Vec3f* arg1) {
    Vec3f sp34;
    f32 sp30;

    Actor_GetProjectedPos(play, arg1, &sp34, &sp30);
    if ((sp34.z > 1.0f) && (fabsf(sp34.x * sp30) < 1.0f) && (fabsf(sp34.y * sp30) < 1.0f)) {
        f32 sp2C = (sp34.x * sp30 * 160.0f) + 160.0f;
        f32 sp28 = (sp34.y * sp30 * -120.0f) + 120.0f;
        s32 sp24 = (s32)(sp34.z * sp30 * 16352.0f) + 16352;

        if (sp24 < func_80178A94(sp2C, sp28)) {
            return true;
        }
    }
    return false;
}

void EnInvadepoh_Event_SetClosestAlien(EnInvadepoh* this) {
    s32 i;
    f32 minDistSqToBarn = FLT_MAX;
    s32 closestAlienIndex = -1;

    for (i = 0; i < this->spawnCount; i++) {
        if ((sAlienInvaders[i] != NULL) && sAlienInvaders[i]->present) {
            f32 distSqToBarn = Math3D_Vec3fDistSq(&sAlienInvaders[i]->actor.world.pos, &this->actor.world.pos);

            if (distSqToBarn < minDistSqToBarn) {
                minDistSqToBarn = distSqToBarn;
                closestAlienIndex = i;
            }
        }
        sAlienStateFlags[i] &= ~ENINVADEPOH_INVADER_CLOSEST;
    }
    sAliensTooClose = false;
    if (minDistSqToBarn <= SQ(2000.0f)) {
        sAlienStateFlags[closestAlienIndex] |= ENINVADEPOH_INVADER_CLOSEST;
        if (minDistSqToBarn <= SQ(340.0f)) {
            sAliensTooClose = true;
        }
    }
}

EnInvadepoh* EnInvadepoh_Dog_GetClosestAlien(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (sAlienStateFlags[i] & ENINVADEPOH_INVADER_CLOSEST) {
            return sAlienInvaders[i];
        }
    }
    return NULL;
}

s8 EnInvadepoh_func_80B45980(EnInvadepohFaceAnimNext* arg0, s32 arg1) {
    f32 temp_fv0 = Rand_ZeroOne();
    EnInvadepohFaceAnimNext* var_v0 = arg0;
    s32 var_v1;

    arg1--;
    for (var_v1 = 0; var_v1 < arg1; var_v1++, var_v0++) {
        if (temp_fv0 <= var_v0->chance) {
            break;
        }
    }
    return (arg0 + var_v1)->index; // TODO: fake?
}

void EnInvadepoh_func_80B459E8(EnInvadePohFaceInfo* arg0, EnInvadepohFaceAnim* arg1) {
    arg0->curAnimType = arg1->type;
    arg0->curAnim = arg1;
    arg0->curFrame = 0;
    arg0->curIndex = arg1->frames->index[0];
    if (arg0->curAnimType == 2) {
        EnInvadepohFaceAnimLoopDelayed* temp = (EnInvadepohFaceAnimLoopDelayed*)arg1;

        arg0->delayTimer = Rand_S16Offset(temp->minDelay, temp->maxDelay);
    }
}

void EnInvadepoh_func_80B45A4C(EnInvadePohFaceInfo* arg0, EnInvadepohFaceAnim** arg1) {
    EnInvadepohFaceAnim* temp_v0 = arg0->curAnim;
    EnInvadepohFaceFrame* temp_v1 = temp_v0->frames;

    if (arg0->curFrame < (temp_v1->count - 1)) {
        arg0->curFrame++;
        arg0->curIndex = temp_v1->index[arg0->curFrame];
    }
}

void EnInvadepoh_func_80B45A94(EnInvadePohFaceInfo* arg0, EnInvadepohFaceAnim** arg1) {
    EnInvadepohFaceAnimLoop* temp_v0 = (EnInvadepohFaceAnimLoop*)arg0->curAnim;
    EnInvadepohFaceFrame* temp_v1 = temp_v0->anim.frames;

    if (arg0->curFrame < (temp_v1->count - 1)) {
        arg0->curFrame++;
        arg0->curIndex = temp_v1->index[arg0->curFrame];
    } else {
        EnInvadepohFaceAnim* temp_a1 = arg1[EnInvadepoh_func_80B45980(temp_v0->nextAnims, temp_v0->nextCount)];

        EnInvadepoh_func_80B459E8(arg0, temp_a1);
    }
}

void EnInvadepoh_func_80B45B1C(EnInvadePohFaceInfo* arg0, EnInvadepohFaceAnim** arg1) {
    EnInvadepohFaceAnimLoopDelayed* temp_v0 = (EnInvadepohFaceAnimLoopDelayed*)arg0->curAnim;
    EnInvadepohFaceFrame* temp_v1 = temp_v0->loop.anim.frames;

    if (arg0->curFrame < (temp_v1->count - 1)) {
        arg0->curFrame++;
        arg0->curIndex = temp_v1->index[arg0->curFrame];
    } else if (arg0->delayTimer > 0) {
        arg0->delayTimer--;
    } else {
        EnInvadepohFaceAnim* temp_a1 =
            arg1[EnInvadepoh_func_80B45980(temp_v0->loop.nextAnims, temp_v0->loop.nextCount)];

        EnInvadepoh_func_80B459E8(arg0, temp_a1);
    }
}

s8 D_80B4E99C[1] = { 0 };
s8 D_80B4E9A0[4] = { 0, 1, 2, 0 };
s8 D_80B4E9A4[5] = { 0, 1, 2, 1, 0 };
s8 D_80B4E9AC[6] = { 0, 1, 2, 2, 1, 0 };
s8 D_80B4E9B4[8] = { 0, 1, 2, 1, 0, 1, 2, 0 };
s8 D_80B4E9BC[1] = { 1 };
s8 D_80B4E9C0[1] = { 3 };
EnInvadepohFaceFrame D_80B4E9C4 = { D_80B4E99C, 1 };
EnInvadepohFaceFrame D_80B4E9CC = { D_80B4E9A0, 4 };
EnInvadepohFaceFrame D_80B4E9D4 = { D_80B4E9A4, 5 };
EnInvadepohFaceFrame D_80B4E9DC = { D_80B4E9AC, 6 };
EnInvadepohFaceFrame D_80B4E9E4 = { D_80B4E9B4, 8 };
EnInvadepohFaceFrame D_80B4E9EC = { D_80B4E9BC, 1 };
EnInvadepohFaceFrame D_80B4E9F4 = { D_80B4E9C0, 1 };
EnInvadepohFaceAnim D_80B4E9FC = { 0, &D_80B4E9C4 };
EnInvadepohFaceAnimNext D_80B4EA04[4] = {
    { 2, 0.5f },
    { 3, 0.9f },
    { 4, 0.97f },
    { 5, 1.0f },
};
EnInvadepohFaceAnimNext D_80B4EA24[1] = { 1, 1.0f };
EnInvadepohFaceAnimLoopDelayed D_80B4EA2C = { { { 2, &D_80B4E9C4 }, 4, D_80B4EA04 }, 40, 60 };
EnInvadepohFaceAnimLoop D_80B4EA40 = { { 1, &D_80B4E9CC }, 1, D_80B4EA24 };
EnInvadepohFaceAnimLoop D_80B4EA50 = { { 1, &D_80B4E9D4 }, 1, D_80B4EA24 };
EnInvadepohFaceAnimLoop D_80B4EA60 = { { 1, &D_80B4E9DC }, 1, D_80B4EA24 };
EnInvadepohFaceAnimLoop D_80B4EA70 = { { 1, &D_80B4E9E4 }, 1, D_80B4EA24 };
EnInvadepohFaceAnim D_80B4EA80 = { 0, &D_80B4E9EC };
EnInvadepohFaceAnim D_80B4EA88 = { 0, &D_80B4E9F4 };
EnInvadepohFaceAnim* D_80B4EA90[8] = {
    &D_80B4E9FC,      &D_80B4EA2C.loop.anim, &D_80B4EA40.anim, &D_80B4EA50.anim,
    &D_80B4EA60.anim, &D_80B4EA70.anim,      &D_80B4EA80,      &D_80B4EA88,
};

s8 D_80B4EAB0[1] = { 0 };
s8 D_80B4EAB4[1] = { 1 };
s8 D_80B4EAB8[1] = { 2 };
s8 D_80B4EABC[1] = { 3 };
EnInvadepohFaceFrame D_80B4EAC0 = { D_80B4EAB0, 1 };
EnInvadepohFaceFrame D_80B4EAC8 = { D_80B4EAB4, 1 };
EnInvadepohFaceFrame D_80B4EAD0 = { D_80B4EAB8, 1 };
EnInvadepohFaceFrame D_80B4EAD8 = { D_80B4EABC, 1 };
EnInvadepohFaceAnim D_80B4EAE0 = { 0, &D_80B4EAC0 };
EnInvadepohFaceAnim D_80B4EAE8 = { 0, &D_80B4EAC8 };
EnInvadepohFaceAnim D_80B4EAF0 = { 0, &D_80B4EAD0 };
EnInvadepohFaceAnim D_80B4EAF8 = { 0, &D_80B4EAD8 };
EnInvadepohFaceAnim* D_80B4EB00[4] = {
    &D_80B4EAE0,
    &D_80B4EAE8,
    &D_80B4EAF0,
    &D_80B4EAF8,
};

s8 D_80B4EB10[1] = { 0 };
s8 D_80B4EB14[4] = { 0, 1, 2, 0 };
s8 D_80B4EB18[5] = { 0, 1, 2, 1, 0 };
s8 D_80B4EB20[6] = { 0, 1, 2, 2, 1, 0 };
s8 D_80B4EB28[8] = { 0, 1, 2, 1, 0, 1, 2, 0 };
EnInvadepohFaceFrame D_80B4EB30 = { D_80B4EB10, 1 };
EnInvadepohFaceFrame D_80B4EB38 = { D_80B4EB14, 4 };
EnInvadepohFaceFrame D_80B4EB40 = { D_80B4EB18, 5 };
EnInvadepohFaceFrame D_80B4EB48 = { D_80B4EB20, 6 };
EnInvadepohFaceFrame D_80B4EB50 = { D_80B4EB28, 8 };
EnInvadepohFaceAnim D_80B4EB58 = { 0, &D_80B4EB30 };
EnInvadepohFaceAnimNext D_80B4EB60[4] = {
    { 2, 0.5f },
    { 3, 0.9f },
    { 4, 0.95f },
    { 5, 1.0f },
};
EnInvadepohFaceAnimNext D_80B4EB80[1] = { 1, 1.0f };
EnInvadepohFaceAnimLoopDelayed D_80B4EB88 = { { { 2, &D_80B4EB30 }, 4, D_80B4EB60 }, 40, 60 };
EnInvadepohFaceAnimLoop D_80B4EB9C = { { 1, &D_80B4EB38 }, 1, D_80B4EB80 };
EnInvadepohFaceAnimLoop D_80B4EBAC = { { 1, &D_80B4EB40 }, 1, D_80B4EB80 };
EnInvadepohFaceAnimLoop D_80B4EBBC = { { 1, &D_80B4EB48 }, 1, D_80B4EB80 };
EnInvadepohFaceAnimLoop D_80B4EBCC = { { 1, &D_80B4EB50 }, 1, D_80B4EB80 };
EnInvadepohFaceAnim* D_80B4EBDC[6] = {
    &D_80B4EB58, &D_80B4EB88.loop.anim, &D_80B4EB9C.anim, &D_80B4EBAC.anim, &D_80B4EBBC.anim, &D_80B4EBCC.anim,
};

s8 D_80B4EBF4[1] = { 0 };
EnInvadepohFaceFrame D_80B4EBF8 = { D_80B4EBF4, 1 };
EnInvadepohFaceAnim D_80B4EC00 = { 0, &D_80B4EBF8 };
EnInvadepohFaceAnim* D_80B4EC08[1] = { &D_80B4EC00 };

void EnInvadepoh_func_80B45BB8(EnInvadePohFaceInfo* arg0) {
    static EnInvadepohFaceFunc D_80B4EC0C[3] = {
        EnInvadepoh_func_80B45A4C,
        EnInvadepoh_func_80B45A94,
        EnInvadepoh_func_80B45B1C,
    };

    if ((arg0->animSet != NULL) && (arg0->curAnim != NULL)) {
        D_80B4EC0C[arg0->curAnimType](arg0, arg0->animSet);
    }
}

void EnInvadepoh_func_80B45C04(EnInvadePohUnkStruct_324* arg0, EnInvadepohFaceAnim** arg1, s32 arg2,
                               EnInvadepohFaceAnim** arg3, s32 arg4, Vec3s* arg5, s16 arg6, f32 arg7, f32 arg8,
                               f32 arg9) {
    Math_Vec3s_Copy(&arg0->unk_26, arg5);
    arg0->unk_2C = arg6;
    arg0->unk_30 = arg7;
    arg0->unk_38 = arg8;
    arg0->unk_3C = arg9;
    if (arg1 != NULL) {
        EnInvadepohFaceAnim* temp_v0 = arg1[arg2];

        arg0->eyeAnim.animSet = arg1;
        arg0->eyeAnim.curAnimType = temp_v0->type;
        arg0->eyeAnim.curAnim = temp_v0;
        arg0->eyeAnim.delayTimer = 0;
        arg0->eyeAnim.curFrame = 0;
        arg0->eyeAnim.curIndex = temp_v0->frames->index[0];
    }
    if (arg3 != NULL) {
        EnInvadepohFaceAnim* temp_v0 = arg3[arg4];

        arg0->mouthAnim.animSet = arg3;
        arg0->mouthAnim.curAnimType = temp_v0->type;
        arg0->mouthAnim.curAnim = temp_v0;
        arg0->mouthAnim.delayTimer = 0;
        arg0->mouthAnim.curFrame = 0;
        arg0->mouthAnim.curIndex = temp_v0->frames->index[0];
    }
}

void EnInvadepoh_func_80B45CE0(EnInvadePohUnkStruct_324* arg0) {
    Vec3f sp3C;
    Vec3s sp34;

    sp34.x = arg0->unk_26.x - arg0->unk_20.x;
    sp34.y = arg0->unk_26.y - arg0->unk_20.y;
    sp34.z = arg0->unk_26.z - arg0->unk_20.z;
    Math_Vec3s_ToVec3f(&sp3C, &sp34);
    Math_Vec3f_Scale(&sp3C, arg0->unk_30);
    Math_Vec3f_ToVec3s(&sp34, &sp3C);
    sp34.x = ABS(sp34.x);
    sp34.y = ABS(sp34.y);
    sp34.z = ABS(sp34.z);
    sp34.x = CLAMP_MAX(sp34.x, arg0->unk_2C);
    sp34.y = CLAMP_MAX(sp34.y, arg0->unk_2C);
    sp34.z = CLAMP_MAX(sp34.z, arg0->unk_2C);

    Math_ScaledStepToS(&arg0->unk_20.x, arg0->unk_26.x, sp34.x);
    Math_ScaledStepToS(&arg0->unk_20.y, arg0->unk_26.y, sp34.y);
    Math_ScaledStepToS(&arg0->unk_20.z, arg0->unk_26.z, sp34.z);
    Math_StepToF(&arg0->unk_34, arg0->unk_38, arg0->unk_3C);

    if (arg0->unk_40 != arg0->unk_42) {
        s16 var_a2 = arg0->unk_42 - arg0->unk_40;

        var_a2 *= arg0->unk_44;
        var_a2 = ABS(var_a2);
        var_a2 = CLAMP(var_a2, 100, arg0->unk_48);
        Math_ScaledStepToS(&arg0->unk_40, arg0->unk_42, var_a2);
    }
    EnInvadepoh_func_80B45BB8(&arg0->eyeAnim);
    EnInvadepoh_func_80B45BB8(&arg0->mouthAnim);
}

void EnInvadepoh_LightBall_SpawnSparkles(EnInvadepoh* this, PlayState* play, s32 arg2) {
    static Color_RGBA8 D_80B4EC18 = { 255, 255, 200, 255 };
    static Color_RGBA8 D_80B4EC1C = { 255, 200, 0, 0 };
    s32 var_s1;
    Vec3f spA8;
    Vec3f sp9C;
    Vec3f sp90;
    f32 temp_fs0;
    s16 var_s0 = 0;

    for (var_s1 = 0; var_s1 < arg2; var_s1++) {
        var_s0 += (s16)(0x10000 * 1.0f / arg2);
        temp_fs0 = (Rand_ZeroOne() * 0.5f) + 0.5f;

        spA8.x = Math_SinS(var_s0) * temp_fs0;
        spA8.z = Math_CosS(var_s0) * temp_fs0;

        sp9C.x = (Rand_ZeroOne() * 16.0f) + (spA8.x * 30.0f) - 8.0f;
        sp9C.y = -8.0f;
        sp9C.z = (Rand_ZeroOne() * 16.0f) + (spA8.z * 30.0f) - 8.0f;

        sp90.x = sp9C.x * -0.025f;
        sp90.y = sp9C.y * -0.025f;
        sp90.z = sp9C.z * -0.025f;

        spA8.x = (spA8.x * 100.0f) + this->actor.world.pos.x;
        spA8.y = (Rand_ZeroOne() * 180.0f) + this->actor.world.pos.y - 90.0f;
        spA8.z = (spA8.z * 100.0f) + this->actor.world.pos.z;
        EffectSsKirakira_SpawnDispersed(play, &spA8, &sp9C, &sp90, &D_80B4EC18, &D_80B4EC1C, 6000, -40);
    }
}

s32 EnInvadepoh_Invader_SpawnWarp(Vec3f* arg0) {
    EnInvadepohWarpEffect* warpEffect = D_80B50350;
    s32 i;

    for (i = 0; i < 10; i++, warpEffect++) {
        if (warpEffect->timer <= 0) {
            warpEffect->unk_0 = 0;
            warpEffect->timer = 40;
            Math_Vec3f_Copy(&warpEffect->pos, arg0);
            warpEffect->alpha = 0;
            return true;
        }
    }
    return false;
}

void EnInvadepoh_func_80B46184(EnInvadepohWarpEffect* warpEffect) {
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

s32 EnInvadepoh_Event_UpdateWarps(void) {
    static void (*D_80B4EC20[1])(EnInvadepohWarpEffect*) = { EnInvadepoh_func_80B46184 };
    s32 var_s4 = false;
    s32 i;
    EnInvadepohWarpEffect* warpEffect;

    for (i = 0, warpEffect = D_80B50350; i < 10; i++, warpEffect++) {
        if (warpEffect->timer > 0) {
            D_80B4EC20[warpEffect->unk_0](warpEffect);
            var_s4 = true;
            warpEffect->timer--;
        }
    }
    return var_s4;
}

void EnInvadepoh_Event_Init(Actor* thisx, PlayState* play) {
    // PlayState* play = play2; Massive problems
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    s32 spawnCount;
    s32 pathIndex;

    this->actor.flags |= ACTOR_FLAG_20;
    pathIndex = ENINVADEPOH_GET_PARAM_7F00(&this->actor);

    for (spawnCount = 1; spawnCount < 8; spawnCount++) {
        Path* path = &play->setupPathList[pathIndex];

        pathIndex = path->unk1;
        if (pathIndex == 0xFF) {
            break;
        }
    }
    this->spawnCount = spawnCount;
    EnInvadepoh_Event_CheckState(this, play);
    EnInvadepoh_Event_SetCutscenes(this);
    func_800BC154(play, &play->actorCtx, &this->actor, 0);
    if (sEventState == ENINVADEPOH_EVENT_WAIT) {
        EnInvadepoh_Event_SetupWait(this);
    } else if (sEventState == ENINVADEPOH_EVENT_ACTIVE) {
        if (gSaveContext.save.time < CLOCK_TIME(2, 31)) {
            EnInvadepoh_Event_SetupWait(this);
        } else {
            EnInvadepoh_Event_SpawnLightBall(this, play);
            EnInvadepoh_Event_SpawnAliens(this, play);
            AudioSeq_QueueSeqCmd(0x8000 | NA_BGM_ALIEN_INVASION);
            EnInvadepoh_Event_SetupInvasion(this);
        }
    } else if (sEventState == ENINVADEPOH_EVENT_CLEAR) {
        if (gSaveContext.save.entrance == ENTRANCE(ROMANI_RANCH, 6)) {
            EnInvadepoh_Event_SetupRomaniReward(this);
        } else if (gSaveContext.save.entrance == ENTRANCE(ROMANI_RANCH, 7)) {
            EnInvadepoh_Event_SetupGoodEnd(this);
        } else {
            EnInvadepoh_Event_SetupGoodEnd(this);
        }
    } else if (sEventState == ENINVADEPOH_EVENT_FAILED) {
        EnInvadepoh_Event_SetupBadEnd(this);
    }
}

InitChainEntry sAlienInitChain[4] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 500, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 600, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};
void EnInvadepoh_Alien_Init(Actor* thisx, PlayState* play) {
    // PlayState* play = play2; Stack size problems
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    Actor_ProcessInitChain(&this->actor, sAlienInitChain);
    Collider_InitCylinder(play, &this->collider);
    ActorShape_Init(&this->actor.shape, 6800.0f, ActorShadow_DrawWhiteCircle, 150.0f);
    this->actor.shape.shadowAlpha = 140;
    this->actor.flags = ACTOR_FLAG_80000000 | ACTOR_FLAG_1000 | ACTOR_FLAG_10;
    if (ENINVADEPOH_GET_PARAM_F0(&this->actor) == ENINVADEPOH_ALIEN_ABDUCTOR) {
        this->actor.update = EnInvadepoh_Abuductor_WaitForObject;
        this->actor.world.pos.y = this->actor.home.pos.y + 150.0f;
    } else {
        this->actor.update = EnInvadepoh_Invader_WaitForObject;
        Collider_SetCylinder(play, &this->collider, &this->actor, &sAlienCylinderInit);
        this->actor.colChkInfo.mass = 40;
    }
    this->bankIndex = Object_GetIndex(&play->objectCtx, OBJECT_UCH);
    if (this->bankIndex < 0) {
        Actor_Kill(&this->actor);
    }
}

InitChainEntry sCowInitChain[4] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};
void EnInvadepoh_Cow_Init(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    Actor_ProcessInitChain(&this->actor, sCowInitChain);
    this->actor.update = EnInvadepoh_Cow_WaitForObject;
    Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EN_INVADEPOH, 0.0f, 0.0f, 0.0f, 0, 0, 0,
                       ENINVADEPOH_SET_PARAMS(0, ENINVADEPOH_COW_TAIL, 0));
    this->bankIndex = Object_GetIndex(&play->objectCtx, OBJECT_COW);
    if (this->bankIndex < 0) {
        Actor_Kill(&this->actor);
    }
}

InitChainEntry sCowTailInitChain[4] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};
void EnInvadepoh_CowTail_Init(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    Actor_ProcessInitChain(&this->actor, sCowTailInitChain);
    this->actor.update = EnInvadepoh_CowTail_WaitForObject;
    this->bankIndex = Object_GetIndex(&play->objectCtx, OBJECT_COW);
    if (this->bankIndex < 0) {
        Actor_Kill(&this->actor);
    }
}

InitChainEntry sRomaniInitChain[5] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE), ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_CONTINUE),  ICHAIN_F32(targetArrowOffset, 1500, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};
void EnInvadepoh_Romani_Init(Actor* thisx, PlayState* play) {
    // PlayState* play = play2; Stack management problems
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    s32 temp_v1 = ENINVADEPOH_GET_PARAM_F0(&this->actor);

    Actor_ProcessInitChain(&this->actor, sRomaniInitChain);
    if ((temp_v1 == ENINVADEPOH_ROMANI_NIGHT_1) || (temp_v1 == ENINVADEPOH_ROMANI_NIGHT_3)) {
        this->actor.targetMode = 3;
    } else {
        this->actor.targetMode = 6;
    }
    func_800BC154(play, &play->actorCtx, &this->actor, 4);
    Collider_InitCylinder(play, &this->collider);
    if (temp_v1 != ENINVADEPOH_ROMANI_ABDUCTED) {
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 18.0f);
        Collider_SetCylinder(play, &this->collider, &this->actor, &sHumanCylinderInit);
        this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    }
    if (temp_v1 == ENINVADEPOH_ROMANI_ABDUCTED) {
        this->actor.update = EnInvadepoh_AbductedRomani_WaitForObject;
    } else if (temp_v1 == ENINVADEPOH_ROMANI_CONFUSED) {
        this->actor.update = EnInvadepoh_ConfusedRomani_WaitForObject;
        this->actor.flags = ACTOR_FLAG_10 | ACTOR_FLAG_8 | ACTOR_FLAG_1;
    } else if (temp_v1 == ENINVADEPOH_ROMANI_NIGHT_1) {
        this->actor.update = EnInvadepoh_Night1Romani_WaitForObject;
    } else if (temp_v1 == ENINVADEPOH_ROMANI_BARN) {
        this->actor.update = EnInvadepoh_BarnRomani_WaitForObject;
    } else if (temp_v1 == ENINVADEPOH_ROMANI_REWARD) {
        this->actor.update = EnInvadepoh_RewardRomani_WaitForObject;
    } else {
        this->actor.update = EnInvadepoh_Night3Romani_WaitForObject;
    }
    this->bankIndex = Object_GetIndex(&play->objectCtx, OBJECT_MA1);
    if (this->bankIndex < 0) {
        Actor_Kill(&this->actor);
    }
    if (temp_v1 == ENINVADEPOH_ROMANI_CONFUSED) {
        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_22_01)) {
            Actor_Kill(&this->actor);
        }
    } else if (temp_v1 == ENINVADEPOH_ROMANI_NIGHT_1) {
        if ((gSaveContext.save.time < CLOCK_TIME(6, 00)) && (gSaveContext.save.time >= CLOCK_TIME(2, 15))) {
            Actor_Kill(&this->actor);
        }
    } else if (temp_v1 == ENINVADEPOH_ROMANI_BARN) {
        // nothing
    } else if (temp_v1 == ENINVADEPOH_ROMANI_REWARD) {
        if (gSaveContext.save.entrance != ENTRANCE(ROMANI_RANCH, 6)) {
            Actor_Kill(&this->actor);
        }
    } else if (temp_v1 == ENINVADEPOH_ROMANI_NIGHT_3) {
        if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_22_01)) {
            Actor_Kill(&this->actor);
        }
        sRomani = this;
    }
}

InitChainEntry sLightBallInitChain[6] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE), ICHAIN_F32(uncullZoneScale, 1000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1000, ICHAIN_CONTINUE), ICHAIN_VEC3S(shape, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(terminalVelocity, -100, ICHAIN_CONTINUE),   ICHAIN_VEC3F_DIV1000(scale, 1000, ICHAIN_STOP),
};
void EnInvadepoh_LightBall_Init(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    Actor_ProcessInitChain(&this->actor, sLightBallInitChain);
    this->actor.update = EnInvadepoh_LightBall_Update;
    this->actor.draw = EnInvadepoh_LightBall_Draw;
    func_800BC154(play, &play->actorCtx, &this->actor, 4);
    if ((sEventState == ENINVADEPOH_EVENT_WAIT) || (gSaveContext.save.time < CLOCK_TIME(2, 31))) {
        this->actor.world.pos.x += D_80B4E934.x;
        this->actor.world.pos.y += D_80B4E934.y + 3000.0f;
        this->actor.world.pos.z += D_80B4E934.z;
        EnInvadepoh_func_80B491EC(this);
    } else if (sEventState == ENINVADEPOH_EVENT_ACTIVE) {
        this->actor.world.pos.y += 1500.0f;
        EnInvadepoh_func_80B49628(this);
    } else {
        Actor_Kill(&this->actor);
    }
}

InitChainEntry sDogInitChain[6] = {
    ICHAIN_F32(uncullZoneForward, 2000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 50, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 50, ICHAIN_CONTINUE),
    ICHAIN_F32(gravity, -3, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, 4, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 7, ICHAIN_STOP),
};
void EnInvadepoh_Dog_Init(Actor* thisx, PlayState* play) {
    // PlayState* play = play2; Stack size problems
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    Actor_ProcessInitChain(&this->actor, sDogInitChain);
    this->actor.update = EnInvadepoh_Dog_WaitForObject;
    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, &this->actor, &sDogCylinderInit);
    this->actor.colChkInfo.mass = 80;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 24.0f);
    this->bankIndex = Object_GetIndex(&play->objectCtx, OBJECT_DOG);
    if (this->bankIndex < 0) {
        Actor_Kill(&this->actor);
    }
}

InitChainEntry sCremiaInitChain[6] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 150, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 1500, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, 3, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};
void EnInvadepoh_Cremia_Init(Actor* thisx, PlayState* play) {
    // PlayState* play = play2; Stack size problems
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    Actor_ProcessInitChain(&this->actor, sCremiaInitChain);
    this->actor.update = EnInvadepoh_Cremia_WaitForObject;
    func_800BC154(play, &play->actorCtx, &this->actor, 4);
    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, &this->actor, &sHumanCylinderInit);
    this->actor.colChkInfo.mass = MASS_HEAVY;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 18.0f);
    this->bankIndex = Object_GetIndex(&play->objectCtx, OBJECT_MA2);
    if (this->bankIndex < 0) {
        Actor_Kill(&this->actor);
    }
    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_22_01)) {
        Actor_Kill(&this->actor);
    }
    sCremia = this;
}

void EnInvadepoh_Init(Actor* thisx, PlayState* play) {
    static ActorFunc sInitFuncs[14] = {
        /* 0x0 */ EnInvadepoh_Event_Init, // Event handler
        /* 0x1 */ EnInvadepoh_Alien_Init, // Alien invader
        /* 0x2 */ EnInvadepoh_Cow_Init, // Abducted cow
        /* 0x3 */ EnInvadepoh_CowTail_Init, // Cow tail
        /* 0x4 */ EnInvadepoh_Romani_Init, // Abducted Romani
        /* 0x5 */ EnInvadepoh_Romani_Init, // Confused Romani
        /* 0x6 */ EnInvadepoh_LightBall_Init, // Light ball
        /* 0x7 */ EnInvadepoh_Romani_Init, // Night 1 Romani
        /* 0x8 */ EnInvadepoh_Romani_Init, // Unknown Romani
        /* 0x9 */ EnInvadepoh_Romani_Init, // Reward Romani
        /* 0xA */ EnInvadepoh_Dog_Init, // Dog
        /* 0xB */ EnInvadepoh_Cremia_Init, // Night 3 Cremia
        /* 0xC */ EnInvadepoh_Romani_Init, // Night 3 Romani
        /* 0xD */ EnInvadepoh_Alien_Init, // Alien abductor
    };

    sInitFuncs[ENINVADEPOH_GET_PARAM_F0(thisx)](thisx, play);
}

void EnInvadepoh_Event_Destroy(Actor* thisx, PlayState* play2) {
}

void EnInvadepoh_Invader_Destroy(Actor* thisx, PlayState* play2) {
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    s32 sp18 = ENINVADEPOH_GET_PARAM_7(&this->actor);
    PlayState* play = play2;

    Collider_DestroyCylinder(play, &this->collider);
    sAlienInvaders[sp18] = NULL;
}

void EnInvadepoh_Cow_Destroy(Actor* thisx, PlayState* play2) {
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if (this->actor.parent != NULL) {
        this->actor.parent->child = NULL;
    }
    if (this->actor.child != NULL) {
        this->actor.child->parent = NULL;
    }
}

void EnInvadepoh_CowTail_Destroy(Actor* thisx, PlayState* play2) {
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if (this->actor.parent != NULL) {
        this->actor.parent->child = NULL;
    }
}

void EnInvadepoh_Romani_Destroy(Actor* thisx, PlayState* play2) {
    PlayState* play = play2; // both or neither recast required
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    Collider_DestroyCylinder(play, &this->collider);
}

void EnInvadepoh_LightBall_Destroy(Actor* thisx, PlayState* play2) {
    sLightBall = NULL;
}

void EnInvadepoh_Dog_Destroy(Actor* thisx, PlayState* play2) {
    PlayState* play = play2; // both or neither recast required
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    Collider_DestroyCylinder(play, &this->collider);
}

void EnInvadepoh_Cremia_Destroy(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    Collider_DestroyCylinder(play, &this->collider);
    sCremia = NULL;
}

void EnInvadepoh_Romani_Destroy2(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    Collider_DestroyCylinder(play, &this->collider);
    sRomani = NULL;
}

void EnInvadepoh_Abductor_Destroy(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx; // this recast required

    Collider_DestroyCylinder(play, &this->collider);
    if (this->actor.child != NULL) {
        this->actor.child->parent = NULL;
    }
}

void EnInvadepoh_Destroy(Actor* thisx, PlayState* play) {
    static ActorFunc D_80B4ECE8[14] = {
        /* 0x0 */ EnInvadepoh_Event_Destroy, // Event handler
        /* 0x1 */ EnInvadepoh_Invader_Destroy, // Alien invader
        /* 0x2 */ EnInvadepoh_Cow_Destroy, // Abducted cow
        /* 0x3 */ EnInvadepoh_CowTail_Destroy, // Cow tail
        /* 0x4 */ EnInvadepoh_Romani_Destroy, // Abducted Romani
        /* 0x5 */ EnInvadepoh_Romani_Destroy, // Confused Romani
        /* 0x6 */ EnInvadepoh_LightBall_Destroy, // Light ball
        /* 0x7 */ EnInvadepoh_Romani_Destroy, // Night 1 Romani
        /* 0x8 */ EnInvadepoh_Romani_Destroy, // Unknown Romani
        /* 0x9 */ EnInvadepoh_Romani_Destroy, // Reward Romani
        /* 0xA */ EnInvadepoh_Dog_Destroy, // Dog
        /* 0xB */ EnInvadepoh_Cremia_Destroy, // Night 3 Cremia
        /* 0xC */ EnInvadepoh_Romani_Destroy2, // Night 3 Romani
        /* 0xD */ EnInvadepoh_Abductor_Destroy, // Alien abductor
    };

    D_80B4ECE8[ENINVADEPOH_GET_PARAM_F0(thisx)](thisx, play);
}

void EnInvadepoh_Event_SetupWait(EnInvadepoh* this) {
    sEventState = ENINVADEPOH_EVENT_WAIT;
    this->actionFunc = EnInvadepoh_Event_Wait;
}

void EnInvadepoh_Event_Wait(EnInvadepoh* this, PlayState* play) {
    if ((gSaveContext.save.time < CLOCK_TIME(6, 00)) && (gSaveContext.save.time >= CLOCK_TIME(2, 30))) {
        EnInvadepoh_Event_SpawnLightBall(this, play);
        EnInvadepoh_Event_SpawnAliens(this, play);
        EnInvadepoh_Event_SetupQueueInvasionCs(this);
    }
}

void EnInvadepoh_Event_SetupQueueInvasionCs(EnInvadepoh* this) {
    sEventState = ENINVADEPOH_EVENT_ACTIVE;
    this->actionTimer = 2;
    this->actionFunc = EnInvadepoh_Event_QueueInvasionCs;
}

void EnInvadepoh_Event_QueueInvasionCs(EnInvadepoh* this, PlayState* play) {
    if (this->actionTimer > 0) {
        this->actionTimer--;
    } else if (CutsceneManager_IsNext(sCutsceneIds[0])) {
        CutsceneManager_StartWithPlayerCs(sCutsceneIds[0], &this->actor);
        EnInvadepoh_Event_SetupInvasionCs(this);
    } else {
        CutsceneManager_Queue(sCutsceneIds[0]);
    }
}

void EnInvadepoh_Event_SetupInvasionCs(EnInvadepoh* this) {
    sEventState = ENINVADEPOH_EVENT_ACTIVE;
    this->actionTimer = 160;
    this->actionFunc = EnInvadepoh_Event_InvasionCs;
}

void EnInvadepoh_Event_InvasionCs(EnInvadepoh* this, PlayState* play) {
    static s16 sAlienWarpTimes[8] = {
        130, 125, 115, 100, 80, 78, 76, 74,
    };
    s32 i;

    for (i = 0; i < 8; i++) {
        if (this->actionTimer == sAlienWarpTimes[i]) {
            sAlienStateFlags[i] |= ENINVADEPOH_INVADER_ACTIVE;
        }
    }
    this->actionTimer--;
    if (this->actionTimer <= 0) {
        CutsceneManager_Stop(sCutsceneIds[0]);
        AudioSeq_QueueSeqCmd(0x8000 | NA_BGM_ALIEN_INVASION);
        EnInvadepoh_Event_SetupInvasion(this);
    }
}

void EnInvadepoh_Event_SetupInvasion(EnInvadepoh* this) {
    sEventState = ENINVADEPOH_EVENT_ACTIVE;
    this->actionFunc = EnInvadepoh_Event_Invasion;
}

void EnInvadepoh_Event_Invasion(EnInvadepoh* this, PlayState* play) {
    Actor** var_v1;
    EnInvadepoh* temp_a0;
    s32 var_v0;
    s8 temp_a1;
    u16 temp_v0;
    s32 i;

    if ((gSaveContext.save.time < CLOCK_TIME(6, 00)) && (gSaveContext.save.time >= CLOCK_TIME(5, 15))) {
        SET_WEEKEVENTREG(WEEKEVENTREG_22_01);
        EnInvadepoh_Event_SetupQueueVictoryCs(this);
    } else {
        EnInvadepoh_Event_SetClosestAlien(this);
        for (i = 0; i < this->spawnCount; i++) {
            if ((sAlienInvaders[i] != NULL) && (sAlienInvaders[i]->atBarn)) {
                EnInvadepoh_Event_SetupFailure(this);
                break;
            }
        }
    }
}

void EnInvadepoh_Event_SetupQueueVictoryCs(EnInvadepoh* this) {
    sEventState = ENINVADEPOH_EVENT_CLEAR;
    this->actionFunc = EnInvadepoh_Event_QueueVictoryCs;
}

void EnInvadepoh_Event_QueueVictoryCs(EnInvadepoh* this, PlayState* play) {
    if (CutsceneManager_IsNext(sCutsceneIds[1])) {
        CutsceneManager_StartWithPlayerCs(sCutsceneIds[1], &this->actor);
        EnInvadepoh_Event_SetupVictoryCs(this);
    } else {
        CutsceneManager_Queue(sCutsceneIds[1]);
    }
}

void EnInvadepoh_Event_SetupVictoryCs(EnInvadepoh* this) {
    sEventState = ENINVADEPOH_EVENT_CLEAR;
    this->actionTimer = 110;
    this->actionFunc = EnInvadepoh_Event_VictoryCs;
}

void EnInvadepoh_Event_VictoryCs(EnInvadepoh* this, PlayState* play) {
    if (this->actionTimer == 100) {
        Audio_PlayFanfare(NA_BGM_CLEAR_EVENT);
    }
    this->actionTimer--;
    if (this->actionTimer <= 0) {
        play->nextEntrance = ENTRANCE(ROMANI_RANCH, 6);
        gSaveContext.nextCutsceneIndex = 0;
        play->transitionTrigger = TRANS_TRIGGER_START;
        play->transitionType = TRANS_TYPE_73;
        gSaveContext.nextTransitionType = TRANS_TYPE_72;
        D_801BDAA0 = 1;
        D_801BDA9C = 0;
        EnInvadepoh_Event_SetupGoodEnd(this);
    }
}

void EnInvadepoh_Event_SetupRomaniReward(EnInvadepoh* this) {
    sEventState = ENINVADEPOH_EVENT_CLEAR;
    this->actionFunc = EnInvadepoh_Event_RomaniReward;
}

void EnInvadepoh_Event_RomaniReward(EnInvadepoh* this, PlayState* play) {
    if (sRewardFinished) {
        play->nextEntrance = ENTRANCE(ROMANI_RANCH, 7);
        gSaveContext.nextCutsceneIndex = 0;
        play->transitionTrigger = TRANS_TRIGGER_START;
        play->transitionType = TRANS_TYPE_72;
        gSaveContext.nextTransitionType = TRANS_TYPE_72;
        EnInvadepoh_Event_SetupGoodEnd(this);
    }
}

void EnInvadepoh_Event_SetupGoodEnd(EnInvadepoh* this) {
    sEventState = ENINVADEPOH_EVENT_CLEAR;
    this->actionFunc = EnInvadepoh_Event_GoodEnd;
}

void EnInvadepoh_Event_GoodEnd(EnInvadepoh* this, PlayState* play) {
}

void EnInvadepoh_Event_SetupFailure(EnInvadepoh* this) {
    sEventState = ENINVADEPOH_EVENT_FAILED;
    this->actionFunc = EnInvadepoh_Event_Failure;
}

void EnInvadepoh_Event_Failure(EnInvadepoh* this, PlayState* play) {
    play->nextEntrance = ENTRANCE(ROMANI_RANCH, 0);
    gSaveContext.nextCutsceneIndex = 0xFFF3;
    play->transitionTrigger = TRANS_TRIGGER_START;
    play->transitionType = TRANS_TYPE_72;
    gSaveContext.nextTransitionType = TRANS_TYPE_72;
    SET_WEEKEVENTREG(WEEKEVENTREG_89_10);
    EnInvadepoh_Event_SetupBadEnd(this);
}

void EnInvadepoh_Event_SetupBadEnd(EnInvadepoh* this) {
    sEventState = ENINVADEPOH_EVENT_FAILED;
    this->actionFunc = EnInvadepoh_Event_BadEnd;
}

void EnInvadepoh_Event_BadEnd(EnInvadepoh* this, PlayState* play) {
}

void EnInvadepoh_Event_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    this->actionFunc(this, play);

    this->actor.draw = EnInvadepoh_Event_UpdateWarps() ? EnInvadepoh_Event_Draw : NULL;
}

void EnInvadepoh_Invader_SetupWaitForEvent(EnInvadepoh* this) {
    this->collider.base.atFlags &= ~AT_ON;
    this->collider.base.acFlags &= ~AC_ON;
    this->collider.base.ocFlags1 &= ~OC1_ON;
    this->actor.flags &= ~ACTOR_FLAG_80000000;
    this->alpha = 0;
    this->actor.draw = NULL;
    this->present = false;
    this->drawDeathFlash = false;
    this->eyeBeamAlpha = 0;
    this->actionFunc = EnInvadepoh_Invader_WaitForEvent;
}

void EnInvadepoh_Invader_WaitForEvent(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_Invader_SetProgress(this);
    EnInvadepoh_Invader_SetPositionAlongPath(this, play);
    EnInvadepoh_Invader_TurnToPath(this, 0x320, 0);
    if (sAlienStateFlags[ENINVADEPOH_GET_PARAM_7(&this->actor)] & ENINVADEPOH_INVADER_ACTIVE) {
        Actor_SetScale(&this->actor, 0.01f);
        EnInvadepoh_SnapToFloor(this);
        EnInvadepoh_Invader_SpawnWarp(&this->actor.world.pos);
        EnInvadepoh_Invader_SetupWarpIn(this);
    }
}

void EnInvadepoh_Invader_SetupWaitToRespawn(EnInvadepoh* this) {
    this->collider.base.atFlags &= ~AT_ON;
    this->collider.base.acFlags &= ~AC_ON;
    this->collider.base.ocFlags1 &= ~OC1_ON;
    this->actor.flags &= ~ACTOR_FLAG_80000000;
    this->alpha = 0;
    this->actor.draw = NULL;
    this->present = false;
    this->drawDeathFlash = false;
    this->eyeBeamAlpha = 0;
    this->actionFunc = EnInvadepoh_Invade_WaitToRespawn;
}

void EnInvadepoh_Invade_WaitToRespawn(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_Invader_SetProgress(this);
    EnInvadepoh_Invader_SetPositionAlongPath(this, play);
    EnInvadepoh_Invader_TurnToPath(this, 0x320, 0);
    if (this->progress > 0.0f) {
        Actor_SetScale(&this->actor, 0.01f);
        EnInvadepoh_SnapToFloor(this);
        EnInvadepoh_Invader_SpawnWarp(&this->actor.world.pos);
        EnInvadepoh_Invader_SetupWarpIn(this);
    }
}

void EnInvadepoh_Invader_SetupWarpIn(EnInvadepoh* this) {
    Animation_MorphToLoop(&this->skelAnime, &gAlienFloatAnim, -6.0f);
    this->collider.base.atFlags &= ~AT_ON;
    this->collider.base.acFlags &= ~AC_ON;
    this->collider.base.ocFlags1 &= ~OC1_ON;
    this->alpha = 0;
    this->actor.draw = EnInvadepoh_Alien_Draw;
    this->present = true;
    this->drawDeathFlash = false;
    this->eyeBeamAlpha = 0;
    this->actor.flags |= ACTOR_FLAG_80000000;
    this->actionFunc = EnInvadepoh_Invader_WarpIn;
}

void EnInvadepoh_Invader_WarpIn(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_Invader_SetProgress(this);
    EnInvadepoh_Invader_SetPositionAlongPath(this, play);
    EnInvadepoh_Invader_TurnToPath(this, 0x320, 0);
    func_800B9010(&this->actor, NA_SE_EN_FOLLOWERS_BEAM_PRE - SFX_FLAG);
    if (this->progress >= 0.9999f) {
        this->atBarn = true;
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
            EnInvadepoh_Invader_SetupAttack(this);
        } else {
            this->eyeBeamAlpha += 10;
        }
    }
}

void EnInvadepoh_Invader_SetupAttack(EnInvadepoh* this) {
    if (this->skelAnime.animation != &gAlienFloatAnim) {
        Animation_MorphToLoop(&this->skelAnime, &gAlienFloatAnim, -6.0f);
    }
    this->collider.base.atFlags |= AT_ON;
    this->collider.base.acFlags |= AC_ON;
    this->collider.base.ocFlags1 |= OC1_ON;
    this->alpha = 255;
    this->actor.draw = EnInvadepoh_Alien_Draw;
    this->present = true;
    this->drawDeathFlash = false;
    this->eyeBeamAlpha = 255;
    this->actor.flags |= ACTOR_FLAG_80000000;
    this->actionFunc = EnInvadepoh_Invader_Attack;
}

void EnInvadepoh_Invader_Attack(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_Invader_SetProgress(this);
    EnInvadepoh_Invader_SetPositionAlongPath(this, play);
    EnInvadepoh_Invader_TurnToPath(this, 0x320, 0);
    func_800B9010(&this->actor, NA_SE_EN_FOLLOWERS_BEAM_PRE - SFX_FLAG);
    if (this->progress >= 0.9999f) {
        this->atBarn = true;
    }
}

void EnInvadepoh_Invader_SetupHitstun(EnInvadepoh* this) {
    this->collider.base.atFlags &= ~AT_ON;
    this->collider.base.acFlags &= ~AC_ON;
    this->collider.base.ocFlags1 |= OC1_ON;
    Animation_PlayLoop(&this->skelAnime, &gAlienJerkingAnim);
    Actor_SetColorFilter(&this->actor, 0x4000, 0xFF, 0, 0x10);
    this->alpha = 255;
    this->actor.draw = EnInvadepoh_Alien_Draw;
    this->present = true;
    this->drawDeathFlash = false;
    this->eyeBeamAlpha = 0;
    this->actionTimer = 8;
    this->stateTimer = 0;
    this->actor.flags |= ACTOR_FLAG_80000000;
    this->actionFunc = EnInvadepoh_Invader_Hitstun;
}

void EnInvadepoh_Invader_Hitstun(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_Invader_Knockback(this, play);
    this->actionTimer--;
    if (this->actionTimer <= 0) {
        EnInvadepoh_Invader_SetupDeath(this);
    }
}

void EnInvadepoh_Invader_SetupDeath(EnInvadepoh* this) {
    this->collider.base.atFlags &= ~AT_ON;
    this->collider.base.acFlags &= ~AC_ON;
    this->collider.base.ocFlags1 &= ~OC1_ON;
    Animation_PlayLoop(&this->skelAnime, &gAlienDeathAnim);
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->actionTimer = 10;
    this->alpha = 255;
    this->actor.draw = EnInvadepoh_Alien_Draw;
    this->present = true;
    this->drawDeathFlash = false;
    this->eyeBeamAlpha = 255;
    this->actor.flags |= ACTOR_FLAG_80000000;
    this->actionFunc = EnInvadepoh_Invader_Death;
}

void EnInvadepoh_Invader_Death(EnInvadepoh* this, PlayState* play) {
    static Vec3f D_80B4ED30[5] = {
        { 0.01f, 0.01f, 0.01f }, { 0.02f, 0.01f, 0.005f }, { -0.01f, 0.0f, 0.0f },
        { 0.01f, 0.01f, 0.01f }, { 0.005f, 0.01f, 0.02f },
    };
    static Vec3f D_80B4ED6C[7] = {
        { 0.0005f, 0.027999999f, 0.01f }, { -0.01f, 0.0f, 0.0f }, { -0.01f, 0.0f, 0.0f },
        { 0.016f, 0.0004f, 0.01f },       { -0.01f, 0.0f, 0.0f }, { 0.0005f, 0.0005f, 0.0005f },
        { 0.0002f, 0.0002f, 0.0002f },
    };
    Vec3f* temp;

    EnInvadepoh_func_80B44B78(this);
    if (this->stateTimer < 5) {
        temp = &D_80B4ED30[this->stateTimer];
        if (temp->x > 0.0f) {
            this->present = true;
            this->eyeBeamAlpha = 255;
            Math_Vec3f_Copy(&this->actor.scale, temp);
        } else {
            this->present = false;
            this->eyeBeamAlpha = 0;
        }
    } else {
        this->present = false;
        this->eyeBeamAlpha = 0;
    }
    if ((this->stateTimer >= 2) && (this->stateTimer < 9)) {
        temp = &D_80B4ED6C[this->stateTimer - 2];
        if (temp->x > 0.0f) {
            this->drawDeathFlash = true;
            Math_Vec3f_Copy(&this->deathFlashScale, temp);
        } else {
            this->drawDeathFlash = false;
        }
    } else {
        this->drawDeathFlash = false;
    }
    this->stateTimer++;
    if (this->actionTimer == 8) {
        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, this->actor.world.pos.x, this->actor.world.pos.y - 10.0f,
                    this->actor.world.pos.z, 0, 0, 3, CLEAR_TAG_SMOKE);
    }
    if (this->actionTimer == 8) {
        Enemy_StartFinishingBlow(play, &this->actor);
    }
    this->actionTimer--;
    if (this->actionTimer <= 0) {
        EnInvadepoh_Invader_ResetWarpInTime(ENINVADEPOH_GET_PARAM_7(&this->actor));
        EnInvadepoh_Invader_AddKill();
        Item_DropCollectible(play, &this->actor.world.pos, 8);
        EnInvadepoh_Invader_SetupWaitToRespawn(this);
    }
}

void EnInvadepoh_Invader_WaitForObject(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if (Object_IsLoaded(&play->objectCtx, this->bankIndex)) {
        this->actor.objBankIndex = this->bankIndex;
        Actor_SetObjectDependency(play, &this->actor);
        EnInvadepoh_Alien_SetTexAnim();
        this->actor.update = EnInvadepoh_Invader_Update;
        SkelAnime_InitFlex(play, &this->skelAnime, &gAlienSkel, &gAlienFloatAnim, this->jointTable, this->morphTable,
                           ALIEN_LIMB_MAX);
        this->skelAnime.curFrame = (ENINVADEPOH_GET_PARAM_7(&this->actor)) * this->skelAnime.endFrame / 8.0f;
        EnInvadepoh_Invader_SetupPath(this, play);
        EnInvadepoh_Invader_SetProgress(this);
        EnInvadepoh_Invader_SetPositionAlongPath(this, play);
        EnInvadepoh_SetYawAlongPath(this);
        EnInvadepoh_SnapToFloor(this);
        if ((sEventState == ENINVADEPOH_EVENT_WAIT) || (gSaveContext.save.time < CLOCK_TIME(2, 31))) {
            EnInvadepoh_Invader_SetupWaitForEvent(this);
        } else if (sEventState == ENINVADEPOH_EVENT_ACTIVE) {
            if (this->progress >= 0.0001f) {
                EnInvadepoh_Invader_SetupAttack(this);
            } else {
                EnInvadepoh_Invader_SetupWarpIn(this);
            }
        } else {
            Actor_Kill(&this->actor);
        }
    }
}

void EnInvadepoh_Invader_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if (sEventState == ENINVADEPOH_EVENT_CLEAR) {
        if ((this->actionFunc == EnInvadepoh_Invader_Attack) || (this->actionFunc == EnInvadepoh_Invader_WarpIn)) {
            thisx->speed = 0.0f;
            thisx->velocity.y = 0.0f;
            thisx->gravity = 0.0f;
            EnInvadepoh_Invader_SetupHitstun(this);
        } else if ((this->actionFunc == EnInvadepoh_Invade_WaitToRespawn) || (this->actionFunc == EnInvadepoh_Invader_WaitForEvent)) {
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
        EnInvadepoh_Invader_SetupHitstun(this);
    }

    this->actionFunc(this, play);

    if (thisx->draw != NULL) {
        this->finishedAnim = SkelAnime_Update(&this->skelAnime);
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
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if (Object_IsLoaded(&play->objectCtx, this->bankIndex)) {
        this->actor.objBankIndex = this->bankIndex;
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
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    s32 sp6C;

    if ((sLightBall == NULL) || (this->actor.parent == NULL)) {
        Actor_Kill(&this->actor);
        return;
    }
    sp6C = ENINVADEPOH_GET_PARAM_7(&this->actor);
    SkelAnime_Update(&this->skelAnime);
    Math_ScaledStepToS(&this->actor.shape.rot.x, D_80B4EDC0[sp6C], 0x32);
    if (this->actor.child != NULL) {
        s32 pad;
        MtxF sp28;

        Matrix_Push();
        Matrix_SetTranslateRotateYXZ(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z,
                                     &this->actor.shape.rot);
        Matrix_Translate(0.0f, 57.0f, -36.0f, MTXMODE_APPLY);
        Matrix_RotateXS(this->actor.shape.rot.x * -0.7f, MTXMODE_APPLY);
        Matrix_RotateZS(this->actor.shape.rot.z * -0.7f, MTXMODE_APPLY);
        Matrix_MultZero(&this->actor.child->world.pos);
        Matrix_Get(&sp28);
        Matrix_MtxFToYXZRot(&sp28, &this->actor.child->shape.rot, 0);
        Matrix_Pop();
    }
}

void EnInvadepoh_CowTail_WaitForObject(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if (Object_IsLoaded(&play->objectCtx, this->bankIndex)) {
        this->actor.objBankIndex = this->bankIndex;
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
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if ((sLightBall == NULL) || (this->actor.parent == NULL)) {
        Actor_Kill(&this->actor);
    } else {
        SkelAnime_Update(&this->skelAnime);
    }
}

void EnInvadepoh_func_80B482D4(EnInvadepoh* this) {
    this->actionTimer = 40;
    Animation_MorphToLoop(&this->skelAnime, &gRomaniLookAroundAnim, -10.0f);
    this->actor.draw = NULL;
    this->actionFunc = EnInvadepoh_func_80B48324;
}

void EnInvadepoh_func_80B48324(EnInvadepoh* this, PlayState* play) {
    this->actionTimer--;
    if (this->actionTimer <= 0) {
        EnInvadepoh_Romani_SetTextId(this, play, 0x332F); // Romani's scream when abducted
        this->actor.draw = EnInvadepoh_Romani_Draw;
        EnInvadepoh_func_80B48374(this);
    }
}

void EnInvadepoh_func_80B48374(EnInvadepoh* this) {
    this->actionTimer = 60;
    Animation_MorphToLoop(&this->skelAnime, &gRomaniLookAroundAnim, -10.0f);
    this->actor.draw = EnInvadepoh_Romani_Draw;
    this->actionFunc = EnInvadepoh_func_80B483CC;
}

void EnInvadepoh_func_80B483CC(EnInvadepoh* this, PlayState* play) {
    if (this->actionTimer == 20) {
        EnInvadePohUnkStruct_324* temp_s0 = &this->unk_324;

        temp_s0->unk_26.x = 0x7D0;
        temp_s0->unk_26.y = 0;
        temp_s0->unk_26.z = 0;
        temp_s0->unk_30 = 0.1f;
        temp_s0->unk_2C = 0x3E8;
    }

    this->actionTimer--;
    if (this->actionTimer <= 0) {
        EnInvadepoh_func_80B4843C(this);
    }
}

void EnInvadepoh_func_80B4843C(EnInvadepoh* this) {
    this->unk_324.unk_26.x = 0xBB8;
    this->unk_324.unk_26.y = 0;
    this->unk_324.unk_26.z = 0;
    this->unk_324.unk_30 = 0.24f;
    this->unk_324.unk_2C = 0xBB8;
    this->unk_324.unk_42 = 0x3A98;
    this->unk_324.unk_44 = 0.1f;
    this->unk_324.unk_48 = 0x7D0;
    this->actionTimer = 50;

    Animation_Change(&this->skelAnime, &gRomaniRunAnim, 2.0f, 0.0f, 0.0f, 0, -5.0f);
    this->actor.draw = EnInvadepoh_Romani_Draw;
    this->actionFunc = EnInvadepoh_func_80B484EC;
}

void EnInvadepoh_func_80B484EC(EnInvadepoh* this, PlayState* play) {
    if (this->actionTimer == 40) {
        this->unk_324.unk_26.y = 0x1B58;
    } else if (this->actionTimer == 30) {
        this->unk_324.unk_26.y = -0x1B58;
    } else if (this->actionTimer == 20) {
        this->unk_324.unk_26.y = 0x1B58;
    } else if (this->actionTimer == 10) {
        this->unk_324.unk_26.y = 0;
    }
    this->actionTimer--;
    if (this->actionTimer <= 0) {
        EnInvadepoh_func_80B48588(this);
    }
}

void EnInvadepoh_func_80B48588(EnInvadepoh* this) {
    this->unk_324.unk_26.x = 0;
    this->unk_324.unk_26.y = 0;
    this->unk_324.unk_26.z = 0;
    this->unk_324.unk_30 = 0.24f;
    this->unk_324.unk_2C = 0x1388;
    this->unk_324.unk_42 = 0;
    this->unk_324.unk_44 = 0.28f;
    this->unk_324.unk_48 = 0x1B58;

    Animation_MorphToPlayOnce(&this->skelAnime, &gRomaniIdleAnim, -10.0f);
    this->actor.draw = EnInvadepoh_Romani_Draw;
    this->actionFunc = EnInvadepoh_func_80B48610;
}

void EnInvadepoh_func_80B48610(EnInvadepoh* this, PlayState* play) {
}

void EnInvadepoh_AbductedRomani_WaitForObject(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    s32 pad;

    if (Object_IsLoaded(&play->objectCtx, this->bankIndex)) {
        this->actor.objBankIndex = this->bankIndex;
        Actor_SetObjectDependency(play, &this->actor);
        EnInvadepoh_Romani_DesegmentTextures();
        this->actor.update = EnInvadepoh_AbductedRomani_Update;
        SkelAnime_InitFlex(play, &this->skelAnime, &gRomaniSkel, &gRomaniIdleAnim, this->jointTable, this->morphTable,
                           ROMANI_LIMB_MAX);
        EnInvadepoh_func_80B45C04(&this->unk_324, D_80B4EA90, 6, D_80B4EB00, 2, &gZeroVec3s, 0x1388, 0.05f, 0.3f,
                                  0.12f);
        Animation_PlayLoop(&this->skelAnime, &gRomaniIdleAnim);
        EnInvadepoh_func_80B482D4(this);
    }
}

void EnInvadepoh_AbductedRomani_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    EnInvadePohUnkStruct_324* temp_v1 = &this->unk_324;

    if (this->actor.parent == NULL) {
        Actor_Kill(&this->actor);
        return;
    }
    this->actionFunc(this, play);
    SkelAnime_Update(&this->skelAnime);
    EnInvadepoh_func_80B45CE0(&this->unk_324);
    if (temp_v1->unk_40 != 0) {
        this->actor.shape.rot.x = -temp_v1->unk_40;
    }
}

void EnInvadepoh_func_80B487B4(EnInvadepoh* this) {
    static s16 D_80B4EDC8[4] = { -0x708, -0x3E8, 0, 0x7D0 };
    EnInvadePohUnkStruct_324* temp_v1 = &this->unk_324;

    this->actionTimer = Rand_S16Offset(150, 250);
    temp_v1->unk_26.x = D_80B4EDC8[Rand_Next() >> 0x1E];
    temp_v1->unk_26.y = 0;
    temp_v1->unk_26.z = 0;
    temp_v1->unk_30 = 0.1f;
    temp_v1->unk_2C = 0x320;
    Animation_MorphToLoop(&this->skelAnime, &gRomaniWalkAnim, -10.0f);
    this->actionFunc = EnInvadepoh_func_80B48848;
}

void EnInvadepoh_func_80B48848(EnInvadepoh* this, PlayState* play) {
    s32 pad;

    Math_StepToF(&this->actor.speed, 1.6f, 0.1f);
    if (EnInvadepoh_func_80B44B84(this, play, this->actor.speed, 50.0f)) {
        EnInvadepoh_func_80B44514(this);
        this->unk_370 = 0xC8;
        this->actor.speed *= 0.25f;
    } else {
        Math_StepToS(&this->unk_370, 0x7D0, 0x46);
    }
    EnInvadepoh_func_80B43E6C(this, 6, this->unk_370, 0x46);
    if (CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40) &&
        (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 7.0f))) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_ROMANI_WALK);
    }
    if (this->actionTimer > 0) {
        this->actionTimer--;
    } else {
        EnInvadepoh_func_80B48948(this);
    }
}

void EnInvadepoh_func_80B48948(EnInvadepoh* this) {
    EnInvadePohUnkStruct_324* sp24 = &this->unk_324;
    f32 sp28 = Rand_ZeroOne();

    this->actionTimer = Rand_S16Offset(150, 150);
    if (sp28 < 0.5f) {
        this->unk_374 = 0;
        Math_Vec3s_Copy(&sp24->unk_26, &gZeroVec3s);
        sp24->unk_30 = 0.1f;
        sp24->unk_2C = 0x3E8;
    } else if (sp28 < 0.75f) {
        this->unk_374 = 1;
        sp24->unk_26.x = Rand_S16Offset(0, 0x7D0);
        sp24->unk_26.y = 0;
        sp24->unk_26.z = 0;
        sp24->unk_30 = 0.06f;
        sp24->unk_2C = 0x3E8;
    } else if (sp28 < 0.8f) {
        this->unk_374 = 2;
        sp24->unk_26.x = Rand_S16Offset(-0x7D0, 0x7D0);
        sp24->unk_26.y = 0;
        sp24->unk_26.z = 0;
        sp24->unk_30 = 0.05f;
        sp24->unk_2C = 0x3E8;
    } else {
        this->unk_374 = 3;
        sp24->unk_26.x = 0;
        sp24->unk_26.y = 0;
        sp24->unk_26.z = Rand_S16Offset(-0x9C4, 0x1388);
        sp24->unk_30 = 0.04f;
        sp24->unk_2C = 0x3E8;
    }
    Animation_MorphToLoop(&this->skelAnime, &gRomaniIdleAnim, -10.0f);
    this->actionFunc = EnInvadepoh_func_80B48AD4;
}

void EnInvadepoh_func_80B48AD4(EnInvadepoh* this, PlayState* play) {
    EnInvadePohUnkStruct_324* temp_s0 = &this->unk_324;

    Math_StepToF(&this->actor.speed, 0.0f, 0.2f);
    if (EnInvadepoh_func_80B44B84(this, play, this->actor.speed, 50.0f)) {
        EnInvadepoh_func_80B44514(this);
    }
    if (this->unk_374 == 0) {
        if ((this->actor.xzDistToPlayer < 350.0f) && (play->gameplayFrames & 0x60)) {
            Player* player = GET_PLAYER(play);
            s16 temp_v0 = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos) * 0.85f;

            temp_s0->unk_26.x = CLAMP((s16)(temp_v0 - this->actor.shape.rot.x), -0x9C4, 0x9C4);

            temp_v0 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
            temp_s0->unk_26.y = CLAMP((s16)(temp_v0 * 0.7f), -0x1F40, 0x1F40);
        }
    } else {
        temp_s0->unk_26.x = 0;
        temp_s0->unk_26.y = 0;
    }
    if (this->actionTimer > 0) {
        s32 temp = (u32)this->actionTimer % 0x20;

        if ((temp == 0) && (Rand_ZeroOne() < 0.3f)) {
            s32 temp_v1_3 = (s32)Rand_Next() % 4;

            if (temp_v1_3 != this->unk_374) {
                this->unk_374 = temp_v1_3;
                if (this->unk_374 == 0) {
                    Math_Vec3s_Copy(&temp_s0->unk_26, &gZeroVec3s);
                    temp_s0->unk_30 = 0.07f;
                } else if (this->unk_374 == 1) {
                    temp_s0->unk_26.x = Rand_S16Offset(0x3E8, 0x3E8);
                    temp_s0->unk_26.y = Rand_S16Offset(-0x3E8, 0x7D0);
                    temp_s0->unk_26.z = Rand_S16Offset(-0x320, 0x640);
                    temp_s0->unk_30 = 0.06f;
                } else if (this->unk_374 == 2) {
                    temp_s0->unk_26.x = Rand_S16Offset(-0x7D0, 0x3E8);
                    temp_s0->unk_26.y = Rand_S16Offset(-0x3E8, 0x7D0);
                    temp_s0->unk_26.z = Rand_S16Offset(-0x320, 0x640);
                    temp_s0->unk_30 = 0.05f;
                } else {
                    temp_s0->unk_26.x = Rand_S16Offset(-0x3E8, 0x7D0);
                    temp_s0->unk_26.y = Rand_S16Offset(-0x7D0, 0xFA0);
                    temp_s0->unk_26.z = Rand_S16Offset(-0x7D0, 0xFA0);
                    temp_s0->unk_30 = 0.04f;
                }
            }
        }
        this->actionTimer--;
        return;
    }
    EnInvadepoh_func_80B487B4(this);
}

void EnInvadepoh_func_80B48DE4(EnInvadepoh* this) {
    EnInvadePohUnkStruct_324* temp_v0 = &this->unk_324;

    this->actor.speed = 0.0f;
    Animation_MorphToLoop(&this->skelAnime, &gRomaniIdleAnim, -10.0f);
    this->unk_370 = 0;
    temp_v0->unk_30 = 0.05f;
    temp_v0->unk_2C = 0x4B0;
    this->actionFunc = EnInvadepoh_func_80B48E4C;
}

void EnInvadepoh_func_80B48E4C(EnInvadepoh* this, PlayState* play) {
    EnInvadePohUnkStruct_324* temp_v0 = &this->unk_324;
    Player* player = GET_PLAYER(play);
    s16 temp_v1;

    Math_StepToS(&this->unk_370, 0x7D0, 0x32);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 6, this->unk_370, 0x23);

    temp_v1 = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos) * 0.85f;
    temp_v0->unk_26.x = CLAMP((s16)(temp_v1 - this->actor.shape.rot.x), -0xBB8, 0xBB8);

    temp_v1 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
    temp_v0->unk_26.y = CLAMP((s16)(temp_v1 * 0.7f), -0x1F40, 0x1F40);

    if (Actor_TextboxIsClosing(&this->actor, play)) {
        EnInvadepoh_func_80B48948(this);
    }
}

void EnInvadepoh_ConfusedRomani_WaitForObject(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if (Object_IsLoaded(&play->objectCtx, this->bankIndex)) {
        this->actor.objBankIndex = this->bankIndex;
        Actor_SetObjectDependency(play, &this->actor);
        EnInvadepoh_Romani_DesegmentTextures();
        this->actor.update = EnInvadepoh_ConfusedRomani_Update;
        this->actor.draw = EnInvadepoh_Romani_Draw;
        this->actor.textId = 0x3330; // ........
        SkelAnime_InitFlex(play, &this->skelAnime, &gRomaniSkel, &gRomaniIdleAnim, this->jointTable, this->morphTable,
                           ROMANI_LIMB_MAX);
        EnInvadepoh_func_80B45C04(&this->unk_324, D_80B4EA90, 6, D_80B4EB00, 2, &gZeroVec3s, 100, 0.03f, 0.3f, 0.03f);
        EnInvadepoh_func_80B444F4(this, play);
        EnInvadepoh_SetPosToPathPoint(this, 0);
        func_800B4AEC(play, &this->actor, 50.0f);
        EnInvadepoh_SnapToFloor(this);
        EnInvadepoh_func_80B487B4(this);
    }
}

void EnInvadepoh_ConfusedRomani_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    s32 inUncullRange = CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40);
    s32 talkRequested = Actor_ProcessTalkRequest(&this->actor, &play->state);

    if (talkRequested) {
        func_80151BB4(play, 5);
        EnInvadepoh_func_80B48DE4(this);
    }
    this->actionFunc(this, play);
    if (inUncullRange) {
        SkelAnime_Update(&this->skelAnime);
        EnInvadepoh_func_80B45CE0(&this->unk_324);
        if ((this->actionFunc != EnInvadepoh_func_80B48E4C) && !talkRequested && this->actor.isTargeted) {
            func_800B8614(&this->actor, play, 100.0f);
        }
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    }
}

void EnInvadepoh_func_80B491EC(EnInvadepoh* this) {
    this->actor.gravity = -15.0f;
    this->pulseScale = 0.0f;
    this->pulseScaleTarget = 1.0f;
    this->pulseScaleRate = 0.0f;
    this->pulseRate = 0;
    this->actionFunc = EnInvadepoh_func_80B49228;
}

void EnInvadepoh_func_80B49228(EnInvadepoh* this, PlayState* play) {
    s32 pad;
    f32 sp28;

    Actor_UpdateVelocityWithGravity(&this->actor);
    this->actor.velocity.y *= 0.97f;
    sp28 = Math_SmoothStepToF(&this->actor.world.pos.y, this->actor.home.pos.y + D_80B4E934.y + 300.0f, 0.7f,
                              fabsf(this->actor.velocity.y), 1.0f);
    func_800B9010(&this->actor, NA_SE_EV_UFO_APPEAR - SFX_FLAG);
    if (fabsf(sp28) < 1.0f) {
        EnInvadepoh_LightBall_SpawnSparkles(this, play, 50);
        EnInvadepoh_func_80B492FC(this);
    }
}

void EnInvadepoh_func_80B492FC(EnInvadepoh* this) {
    this->actor.velocity.y *= 0.1f;
    this->actionTimer = 20;
    this->pulseScaleTarget = 0.3f;
    this->pulseScaleRate = 0.03f;
    this->pulseRate = 0xBB8;
    this->actionFunc = EnInvadepoh_func_80B4934C;
}

void EnInvadepoh_func_80B4934C(EnInvadepoh* this, PlayState* play) {
    f32 temp = this->actor.home.pos.y + D_80B4E934.y + 300.0f;

    if (this->actor.world.pos.y < temp) {
        this->actor.gravity = 3.0f;
    } else {
        this->actor.gravity = -2.0f;
    }
    this->actor.velocity.y *= 0.96f;
    Actor_MoveWithGravity(&this->actor);
    func_800B9010(&this->actor, NA_SE_EV_UFO_APPEAR - SFX_FLAG);
    this->actionTimer--;
    if (this->actionTimer <= 0) {
        EnInvadepoh_func_80B49404(this);
    }
}

void EnInvadepoh_func_80B49404(EnInvadepoh* this) {
    this->actionTimer = 120;
    this->pulseScaleTarget = 0.2f;
    this->pulseScaleRate = 0.01f;
    this->actor.gravity = 33.0f;
    this->pulseRate = 0xBB8;
    this->lightBallTarget = 0;
    this->stateTimer = 0;
    this->actionFunc = EnInvadepoh_func_80B49454;
}

void EnInvadepoh_func_80B49454(EnInvadepoh* this, PlayState* play) {
    static Vec3f sLightBallTargets[5] = {
        { -1813.0f, 374.0f, 1900.0f }, { 2198.0f, 153.0f, 3365.0f }, { -1434.0f, 262.0f, 3365.0f },
        { -393.0f, 396.0f, 1084.0f },  { 0.0f, 1500.0f, 0.0f },
    };
    s32 pad;
    Vec3f sp30;
    s32 pad2;

    if (this->stateTimer < 25) {
        this->stateTimer++;
    } else {
        this->stateTimer = 0;
        this->lightBallTarget++;
        this->lightBallTarget = CLAMP_MAX(this->lightBallTarget, ARRAY_COUNT(sLightBallTargets) - 1);
        this->actor.gravity = 33.0f;
        EnInvadepoh_LightBall_SpawnSparkles(this, play, 20);
    }
    Math_Vec3f_Sum(&sLightBallTargets[this->lightBallTarget], &this->actor.home.pos, &sp30);
    if (Math3D_Vec3fDistSq(&this->actor.world.pos, &sp30) < SQ(400.0f)) {
        this->actor.speed *= 0.8f;
    } else {
        Math_StepToF(&this->actor.speed, 170.0f, 21.0f);
        this->actor.speed *= 0.98f;
    }
    if (EnInvadepoh_func_80B450C0(&this->actor.world.pos.x, &this->actor.world.pos.z, sp30.x, sp30.z,
                                  this->actor.speed)) {
        this->actor.speed = 0.0f;
    }
    if (sp30.y < this->actor.world.pos.y) {
        Math_StepToF(&this->actor.gravity, -12.0f, 7.0f);
    } else {
        Math_StepToF(&this->actor.gravity, 5.0f, 4.0f);
    }
    this->actor.velocity.y += this->actor.gravity;
    this->actor.velocity.y *= 0.97f;
    this->actor.world.pos.y += this->actor.velocity.y;
    func_800B9010(&this->actor, NA_SE_EV_UFO_APPEAR - SFX_FLAG);
    if (this->actionTimer > 0) {
        this->actionTimer--;
    } else {
        EnInvadepoh_func_80B49628(this);
    }
}

void EnInvadepoh_func_80B49628(EnInvadepoh* this) {
    this->pulseScaleTarget = 0.2f;
    this->pulseScaleRate = 0.01f;
    this->pulseRate = 0xBB8;
    this->actor.velocity.y *= 0.8f;
    this->actionFunc = EnInvadepoh_func_80B49670;
}

void EnInvadepoh_func_80B49670(EnInvadepoh* this, PlayState* play) {
    s32 pad;
    Vec3f sp30;

    sp30.x = this->actor.home.pos.x;
    sp30.y = this->actor.home.pos.y + 1500.0f;
    sp30.z = this->actor.home.pos.z;
    Math_SmoothStepToS(&this->actor.world.rot.y, Math_Vec3f_Yaw(&this->actor.world.pos, &sp30), 0xA, 0xBB8, 0x64);
    if ((play->gameplayFrames % 0x40) < 14) {
        Math_StepToF(&this->actor.speed, 5.0f, 1.0f);
    } else {
        this->actor.speed *= 0.97f;
    }
    this->actor.gravity = (sp30.y < this->actor.world.pos.y) ? -0.5f : 2.0f;
    this->actor.velocity.y *= 0.97f;
    Actor_MoveWithGravity(&this->actor);
    if (sEventState == ENINVADEPOH_EVENT_CLEAR) {
        EnInvadepoh_func_80B499BC(this);
    }
}

void EnInvadepoh_func_80B497A4(EnInvadepoh* this) {
    this->pulseScaleTarget = 0.2f;
    this->pulseScaleRate = 0.01f;
    this->actor.gravity = -1.5f;
    this->pulseRate = 0xBB8;
    this->actionTimer = 35;
    this->actionFunc = EnInvadepoh_func_80B497EC;
}

void EnInvadepoh_func_80B497EC(EnInvadepoh* this, PlayState* play) {
    s32 pad;
    Vec3f sp30;

    sp30.x = this->actor.home.pos.x + D_80B4E934.x;
    sp30.y = this->actor.home.pos.y + D_80B4E934.y + 400.0f;
    sp30.z = this->actor.home.pos.z + D_80B4E934.z;
    Math_SmoothStepToS(&this->actor.world.rot.y, Math_Vec3f_Yaw(&this->actor.world.pos, &sp30), 4, 0x1F40, (s16)0x64);
    Math_StepToF(&this->actor.speed, 70.0f, 3.0f);
    this->actor.gravity = (sp30.y < this->actor.world.pos.y) ? -2.0f : 2.0f;
    this->actor.velocity.y *= 0.97f;
    Actor_MoveWithGravity(&this->actor);
    if (this->actionTimer > 0) {
        this->actionTimer--;
    } else {
        EnInvadepoh_func_80B49904(this);
    }
}

void EnInvadepoh_func_80B49904(EnInvadepoh* this) {
    this->pulseScaleTarget = 0.2f;
    this->pulseScaleRate = 0.01f;
    this->actor.gravity = 1.0f;
    this->pulseRate = 0xBB8;
    this->actionTimer = 60;
    this->actionFunc = EnInvadepoh_func_80B4994C;
}

void EnInvadepoh_func_80B4994C(EnInvadepoh* this, PlayState* play) {
    Math_StepToF(&this->actor.speed, 150.0f, 4.0f);
    this->actor.velocity.y *= 0.95f;
    Actor_MoveWithGravity(&this->actor);
    if (this->actionTimer > 0) {
        this->actionTimer--;
    } else {
        Actor_Kill(&this->actor);
    }
}

void EnInvadepoh_func_80B499BC(EnInvadepoh* this) {
    this->actionTimer = 40;
    this->pulseScaleTarget = 0.2f;
    this->pulseScaleRate = 0.01f;
    this->actor.speed = 0.0f;
    this->pulseRate = 0xBB8;
    this->actionFunc = EnInvadepoh_func_80B49A00;
}

void EnInvadepoh_func_80B49A00(EnInvadepoh* this, PlayState* play) {
    s32 pad;
    Vec3f sp30;

    sp30.x = this->actor.home.pos.x;
    sp30.y = this->actor.home.pos.y + 800.0f;
    sp30.z = this->actor.home.pos.z;
    Math_SmoothStepToS(&this->actor.world.rot.y, Math_Vec3f_Yaw(&this->actor.world.pos, &sp30), 4, 0x1F40, 0x64);
    Math_StepToF(&this->actor.speed, 30.0f, 3.0f);
    this->actor.velocity.y *= 0.98f;
    this->actor.gravity = (sp30.y < this->actor.world.pos.y) ? -0.5f : 2.0f;
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 0.0f, 0.0f, 0.0f, 4);

    if (this->actionTimer > 0) {
        this->actionTimer--;
    } else {
        EnInvadepoh_func_80B497A4(this);
    }
}

void EnInvadepoh_LightBall_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    f32 temp;

    this->actionFunc(this, play);

    this->pulsePhase += this->pulseRate;
    Math_StepToF(&this->pulseScale, this->pulseScaleTarget, this->pulseScaleRate);

    temp = 1.0f + (Math_SinS(this->pulsePhase) * this->pulseScale);
    Actor_SetScale(&this->actor, 0.27f * temp);
    Math_StepToS(&this->unk_306, 0x258, 8);
    this->actor.world.rot.y += this->unk_306;
    this->unk_304 += 0x258;
}

void EnInvadepoh_func_80B49BD0(EnInvadepoh* this) {
    EnInvadePohUnkStruct_324* temp_v0 = &this->unk_324;

    Animation_MorphToLoop(&this->skelAnime, &gRomaniWalkAnim, -10.0f);
    temp_v0->unk_26.x = 0;
    temp_v0->unk_26.y = 0;
    temp_v0->unk_26.z = 0;
    temp_v0->unk_30 = 0.1f;
    temp_v0->unk_2C = 0x320;
    this->actionFunc = EnInvadepoh_func_80B49C38;
}

void EnInvadepoh_func_80B49C38(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_Night1Romani_SetProgress(this);
    EnInvadepoh_func_80B44C24(this, play);
    EnInvadepoh_func_80B43E6C(this, 6, 0x7D0, 0x64);

    if ((this->currentPoint == 0) || (this->currentPoint + 1 == this->endPoint)) {
        if (this->unk_378 == 0) {
            s32 temp_v0_2 = func_800FE620(play);
            s32 pad;

            if (temp_v0_2 > 0) {
                temp_v0_2 = (gRegEditor->data[0xF] * -16.0f / temp_v0_2) - 0.5f;
                this->unk_378 = EnInvadepoh_func_80B45550(this, play, SQ(80.0f), temp_v0_2);
            }
        }
        this->actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_8);
    } else {
        this->unk_378 = 0;
        this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_8);
    }
    if (CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40) &&
        (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 7.0f))) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_ROMANI_WALK);
    }
    if (this->progress >= 0.9999f) {
        Actor_Kill(&this->actor);
    }
}

void EnInvadepoh_func_80B49DA0(EnInvadepoh* this) {
    this->unk_324.unk_30 = 0.08f;
    this->unk_324.unk_2C = 0x7D0;
    this->unk_370 = 0;
    Animation_MorphToLoop(&this->skelAnime, &gRomaniIdleAnim, -10.0f);
    this->actionFunc = EnInvadepoh_func_80B49DFC;
}

void EnInvadepoh_func_80B49DFC(EnInvadepoh* this, PlayState* play) {
    EnInvadePohUnkStruct_324* temp_s0 = &this->unk_324;
    Player* player = GET_PLAYER(play);
    s16 temp_v1;

    Math_StepToS(&this->unk_370, 0x7D0, 0x1F4);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, this->unk_370, 0x28);
    temp_v1 = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos) * 0.85f;
    temp_s0->unk_26.x = CLAMP((s16)(temp_v1 - this->actor.shape.rot.x), -0xBB8, 0xBB8);

    temp_v1 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
    temp_s0->unk_26.y = CLAMP((s16)(temp_v1 * 0.7f), -0x1F40, 0x1F40);

    if (Actor_TextboxIsClosing(&this->actor, play)) {
        if (this->actor.textId == 0x332D) { // It's almost time, Grasshopper...
            SET_WEEKEVENTREG(WEEKEVENTREG_54_10);
            this->actor.textId = 0x332E; // If you run out of arrows...
        }
        EnInvadepoh_func_80B49BD0(this);
    }
}

void EnInvadepoh_Night1Romani_WaitForObject(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    s32 pad;
    s32 sp38;

    if (Object_IsLoaded(&play->objectCtx, this->bankIndex)) {
        sp38 = gSaveContext.save.time;
        this->actor.objBankIndex = this->bankIndex;
        Actor_SetObjectDependency(play, &this->actor);
        EnInvadepoh_Romani_DesegmentTextures();
        SkelAnime_InitFlex(play, &this->skelAnime, &gRomaniSkel, &gRomaniWalkAnim, this->jointTable, this->morphTable,
                           ROMANI_LIMB_MAX);
        EnInvadepoh_func_80B45C04(&this->unk_324, D_80B4EA90, 1, D_80B4EB00, 1, &gZeroVec3s, 0x64, 0.03f, 0.3f, 0.03f);
        EnInvadepoh_Night1Romani_SetupPath(this, play);
        EnInvadepoh_Night1Romani_SetProgress(this);
        EnInvadepoh_func_80B44C24(this, play);
        EnInvadepoh_SetYawAlongPath(this);
        EnInvadepoh_SnapToFloor(this);
        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_21_20)) {
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_54_10)) {
                this->actor.textId = 0x332E; // If you run out of arrows...
            } else {
                this->actor.textId = 0x332D; // It's almost time, Grasshopper...
            }
        } else {
            this->actor.textId = 0x332C; // ...It's almost time.
        }
        if ((sp38 >= CLOCK_TIME(18, 00)) || (sp38 < CLOCK_TIME(2, 00))) {
            this->actor.update = EnInvadepoh_Night1Romani_WaitForEvent;
            this->actor.draw = NULL;
        } else if ((sp38 < CLOCK_TIME(6, 00)) && (sp38 >= CLOCK_TIME(2, 00)) && (sp38 < CLOCK_TIME(2, 15))) {
            this->actor.update = EnInvadepoh_Night1Romani_Update;
            this->actor.draw = EnInvadepoh_Romani_Draw;
            EnInvadepoh_func_80B49BD0(this);
        } else {
            Actor_Kill(&this->actor);
        }
    }
}

void EnInvadepoh_Night1Romani_WaitForEvent(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if ((gSaveContext.save.time < CLOCK_TIME(6, 00)) && (gSaveContext.save.time >= CLOCK_TIME(2, 00))) {
        this->actor.update = EnInvadepoh_Night1Romani_Update;
        this->actor.draw = EnInvadepoh_Romani_Draw;
        EnInvadepoh_func_80B49BD0(this);
    }
}

void EnInvadepoh_Night1Romani_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    s32 inUncullRange = CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40);
    s32 talkRequested = Actor_ProcessTalkRequest(&this->actor, &play->state);

    if (talkRequested) {
        func_80151BB4(play, 5);
        EnInvadepoh_func_80B49DA0(this);
    }
    this->actionFunc(this, play);
    if (inUncullRange && (this->actor.update != NULL)) {
        SkelAnime_Update(&this->skelAnime);
        EnInvadepoh_func_80B45CE0(&this->unk_324);
        if ((this->actionFunc != EnInvadepoh_func_80B49DFC) && !talkRequested && this->actor.isTargeted) {
            func_800B8614(&this->actor, play, 350.0f);
        }
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    }
}

void EnInvadepoh_func_80B4A2C0(EnInvadepoh* this) {
    EnInvadePohUnkStruct_324* temp_v0 = &this->unk_324;

    Animation_MorphToLoop(&this->skelAnime, &gRomaniIdleAnim, -10.0f);
    temp_v0->unk_26.x = 0;
    temp_v0->unk_26.y = 0;
    temp_v0->unk_26.z = 0;
    temp_v0->unk_30 = 0.1f;
    temp_v0->unk_2C = 0x5DC;

    this->actionTimer = Rand_S16Offset(200, 200);
    this->unk_304 = this->actor.shape.rot.y;
    this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_8);
    this->actionFunc = EnInvadepoh_func_80B4A350;
}

void EnInvadepoh_func_80B4A350(EnInvadepoh* this, PlayState* play) {
    s32 pad;
    EnInvadePohUnkStruct_324* sp30 = &this->unk_324;

    if ((play->gameplayFrames % 0x100) == 0) {
        Vec3f sp44;
        s16 sp42;

        Math_Vec3s_ToVec3f(&sp44, this->pathPoints);
        sp42 = Math_Vec3f_Yaw(&this->actor.world.pos, &sp44);
        this->unk_304 = Rand_S16Offset(-0x1F40, 0x3E80) + sp42;
        this->unk_370 = 0;
    }
    Math_StepToS(&this->unk_370, 0x7D0, 0x28);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->unk_304, 6, this->unk_370, 0x28);
    if (this->actor.xzDistToPlayer < 300.0f) {
        Player* player = GET_PLAYER(play);
        s16 temp_v1;

        temp_v1 = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos) * 0.85f;
        sp30->unk_26.x = CLAMP((s16)(temp_v1 - this->actor.shape.rot.x), -0x9C4, 0x9C4);

        temp_v1 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
        sp30->unk_26.y = CLAMP((s16)(temp_v1 * 0.7f), -0x1F40, 0x1F40);

        if ((play->gameplayFrames % 0x100) == 0) {
            sp30->unk_26.z = Rand_S16Offset(-0x5DC, 0xBB8);
        }
    } else {
        sp30->unk_26.x = 0;
        sp30->unk_26.y = 0;
        sp30->unk_26.z = 0;
    }
    if (this->actionTimer > 0) {
        this->actionTimer--;
    } else {
        EnInvadepoh_func_80B4A570(this);
    }
}

void EnInvadepoh_func_80B4A570(EnInvadepoh* this) {
    EnInvadePohUnkStruct_324* temp_v0 = &this->unk_324;

    Animation_MorphToPlayOnce(&this->skelAnime, &gRomaniLookAroundAnim, -10.0f);
    temp_v0->unk_26.x = 0;
    temp_v0->unk_26.y = 0;
    temp_v0->unk_26.z = 0;
    temp_v0->unk_30 = 0.1f;
    temp_v0->unk_2C = 0x320;
    this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_8);
    this->actionFunc = EnInvadepoh_func_80B4A5E4;
}

void EnInvadepoh_func_80B4A5E4(EnInvadepoh* this, PlayState* play) {
    if (this->finishedAnim) {
        EnInvadepoh_func_80B4A2C0(this);
    }
}

void EnInvadepoh_func_80B4A614(EnInvadepoh* this) {
    EnInvadePohUnkStruct_324* temp_v0 = &this->unk_324;

    Animation_MorphToLoop(&this->skelAnime, &gRomaniWalkAnim, 0.0f);
    temp_v0->unk_26.x = 0;
    temp_v0->unk_26.y = 0;
    temp_v0->unk_26.z = 0;
    temp_v0->unk_30 = 0.1f;
    temp_v0->unk_2C = 0x320;
    this->actionFunc = EnInvadepoh_func_80B4A67C;
}

void EnInvadepoh_func_80B4A67C(EnInvadepoh* this, PlayState* play) {
    s32 pad;

    Math_StepToF(&this->actor.speed, 5.0f, 1.0f);
    if (EnInvadepoh_func_80B44B84(this, play, this->actor.speed, 50.0f) != 0) {
        EnInvadepoh_func_80B44640(this);
        this->unk_370 = 0x5DC;
        this->actor.speed *= 0.5f;
    } else {
        Math_StepToS(&this->unk_370, 0x190, 0x32);
    }
    EnInvadepoh_func_80B43E6C(this, 6, this->unk_370, 0x32);
    if (this->currentPoint == 0) {
        if (this->unk_378 == 0) {
            this->unk_378 = EnInvadepoh_func_80B45550(this, play, SQ(80.0f), -15);
        }
        this->actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_8);
    } else {
        this->unk_378 = 0;
        this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_8);
    }
    if (CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40) &&
        (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 7.0f))) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_ROMANI_WALK);
    }
    if (this->currentPoint == this->endPoint) {
        EnInvadepoh_func_80B4A2C0(this);
    }
}

void EnInvadepoh_func_80B4A7C0(EnInvadepoh* this) {
    this->unk_324.unk_30 = 0.08f;
    this->unk_324.unk_2C = 0x7D0;
    this->unk_370 = 0;
    Animation_MorphToLoop(&this->skelAnime, &gRomaniIdleAnim, 0.0f);
    this->actionFunc = EnInvadepoh_func_80B4A81C;
}

void EnInvadepoh_func_80B4A81C(EnInvadepoh* this, PlayState* play) {
    EnInvadePohUnkStruct_324* temp_s0 = &this->unk_324;
    Player* player = GET_PLAYER(play);
    s16 temp_v1;

    Math_StepToS(&this->unk_370, 0x7D0, 0x1F4);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, this->unk_370, (s16)0x28);
    temp_v1 = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos) * 0.85f;
    temp_s0->unk_26.x = CLAMP((s16)(temp_v1 - this->actor.shape.rot.x), -0xBB8, 0xBB8);

    temp_v1 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
    temp_s0->unk_26.y = CLAMP((s16)(temp_v1 * 0.7f), -0x1F40, 0x1F40);
    if (Actor_TextboxIsClosing(&this->actor, play)) {
        if (this->actor.textId == 0x332D) { // It's almost time, Grasshopper
            SET_WEEKEVENTREG(WEEKEVENTREG_54_10);
            this->actor.textId = 0x332E; // If you run out of arrows...
        }
        if (this->currentPoint == this->endPoint) {
            EnInvadepoh_func_80B4A2C0(this);
        } else {
            EnInvadepoh_func_80B4A614(this);
        }
    }
}

void EnInvadepoh_BarnRomani_WaitForObject(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    s32 pad;

    if (Object_IsLoaded(&play->objectCtx, this->bankIndex)) {
        s32 sp38 = gSaveContext.save.time;

        this->actor.objBankIndex = this->bankIndex;
        Actor_SetObjectDependency(play, &this->actor);
        EnInvadepoh_Romani_DesegmentTextures();
        SkelAnime_InitFlex(play, &this->skelAnime, &gRomaniSkel, &gRomaniWalkAnim, this->jointTable, this->morphTable,
                           ROMANI_LIMB_MAX);
        EnInvadepoh_func_80B45C04(&this->unk_324, D_80B4EA90, 1, D_80B4EB00, 1, &gZeroVec3s, 100, 0.03f, 0.3f, 0.03f);
        EnInvadepoh_BarnRomani_SetupPath(this, play2);
        if ((sp38 < CLOCK_TIME(2, 15)) || (sp38 >= CLOCK_TIME(6, 00))) {
            this->currentPoint = 0;
            this->actor.update = EnInvadepoh_BarnRomani_WaitForEvent;
        } else {
            this->currentPoint = this->endPoint;
            this->actor.update = EnInvadepoh_BarnRomani_Update;
            this->actor.draw = EnInvadepoh_Romani_Draw;
            EnInvadepoh_func_80B4A2C0(this);
        }
        EnInvadepoh_SetPosToPathPoint(this, this->currentPoint);
        EnInvadepoh_SetYawAlongPath(this);
        func_800B4AEC(play, &this->actor, 50.0f);
        EnInvadepoh_SnapToFloor(this);
        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_21_20)) {
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_54_10)) {
                this->actor.textId = 0x332E; // If you run out of arrows...
            } else {
                this->actor.textId = 0x332D; // It's almost time, Grasshopper...
            }
        } else {
            this->actor.textId = 0x332C; // ...It's almost time.
        }
    }
}

void EnInvadepoh_BarnRomani_WaitForEvent(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if ((gSaveContext.save.time < CLOCK_TIME(6, 00)) && (gSaveContext.save.time >= CLOCK_TIME(2, 15))) {
        this->actor.update = EnInvadepoh_BarnRomani_Update;
        this->actor.draw = EnInvadepoh_Romani_Draw;
        EnInvadepoh_func_80B4A614(this);
    }
}

void EnInvadepoh_BarnRomani_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    s32 inUncullRange = CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40);
    s32 talkRequested = Actor_ProcessTalkRequest(&this->actor, &play->state);

    if (talkRequested) {
        func_80151BB4(play, 5);
        EnInvadepoh_func_80B4A7C0(this);
    }
    this->actionFunc(this, play);
    if (inUncullRange) {
        this->finishedAnim = SkelAnime_Update(&this->skelAnime);
        EnInvadepoh_func_80B45CE0(&this->unk_324);
        if ((this->actionFunc != EnInvadepoh_func_80B4A81C) && !talkRequested && this->actor.isTargeted) {
            func_800B8614(&this->actor, play, 100.0f);
        }
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    }
}

void EnInvadepoh_func_80B4ACDC(EnInvadepoh* this) {
    this->actionFunc = EnInvadepoh_func_80B4ACF0;
}

void EnInvadepoh_func_80B4ACF0(EnInvadepoh* this, PlayState* play) {
    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_22_01)) {
        this->actor.draw = EnInvadepoh_Romani_Draw;
        this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_8);
        EnInvadepoh_func_80B4AD3C(this);
    }
}

void EnInvadepoh_func_80B4AD3C(EnInvadepoh* this) {
    this->actor.flags |= ACTOR_FLAG_10000;
    this->actionFunc = EnInvadepoh_func_80B4AD60;
}

void EnInvadepoh_func_80B4AD60(EnInvadepoh* this, PlayState* play) {
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        EnInvadepoh_Romani_SetTextId(this, play, 0x3331); // We did it...We won.
        EnInvadepoh_func_80B4ADB8(this);
    } else {
        func_800B8614(&this->actor, play, 2000.0f);
    }
}

void EnInvadepoh_func_80B4ADB8(EnInvadepoh* this) {
    this->actionFunc = EnInvadepoh_func_80B4ADCC;
}

void EnInvadepoh_func_80B4ADCC(EnInvadepoh* this, PlayState* play) {
    if ((Message_GetState(&play->msgCtx) == 5) && Message_ShouldAdvance(play)) {
        if (this->textId == 0x3331) { // We did it...We won.
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_22_02)) {
                EnInvadepoh_Romani_SetTextId(this, play, 0x3334); // I have to get back to bed...
                func_80151BB4(play, 0x1D);
                func_80151BB4(play, 5);
            } else {
                EnInvadepoh_Romani_SetTextId(this, play, 0x3333); // Here's Romani's thanks
            }
        } else if (this->textId == 0x3333) { // Here's Romani's thanks
            EnInvadepoh_func_80B4AEC0(this);
        } else if (this->textId == 0x3334) { // I have to get back to bed...
            Message_CloseTextbox(play);
            EnInvadepoh_func_80B4B024(this);
        }
    }
}

void EnInvadepoh_func_80B4AEC0(EnInvadepoh* this) {
    this->actionTimer = 2;
    this->actionFunc = EnInvadepoh_func_80B4AEDC;
}

void EnInvadepoh_func_80B4AEDC(EnInvadepoh* this, PlayState* play) {
    if (this->actionTimer > 0) {
        this->actionTimer--;
        if (this->actionTimer == 0) {
            Message_CloseTextbox(play);
        }
    }
    if (Actor_HasParent(&this->actor, play)) {
        this->actor.parent = NULL;
        SET_WEEKEVENTREG(WEEKEVENTREG_22_02);
        EnInvadepoh_func_80B4AF80(this);
    } else {
        Actor_OfferGetItem(&this->actor, play, 0x60, 2000.0f, 2000.0f);
    }
}

void EnInvadepoh_func_80B4AF80(EnInvadepoh* this) {
    this->actionFunc = EnInvadepoh_func_80B4AF94;
}

void EnInvadepoh_func_80B4AF94(EnInvadepoh* this, PlayState* play) {
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        EnInvadepoh_Romani_SetTextId(this, play, 0x3334); // I have to get back to bed..
        func_80151BB4(play, 0x1E);
        func_80151BB4(play, 0x1D);
        func_80151BB4(play, 5);
        EnInvadepoh_func_80B4ADB8(this);
    } else {
        func_800B85E0(&this->actor, play, 2000.0f, PLAYER_IA_MINUS1);
    }
}

void EnInvadepoh_func_80B4B024(EnInvadepoh* this) {
    this->actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_8);
    this->actionFunc = EnInvadepoh_func_80B4B048;
}

void EnInvadepoh_func_80B4B048(EnInvadepoh* this, PlayState* play) {
    if (play->msgCtx.unk120B1 == 0) {
        if (play->msgCtx.msgMode == 0) {
            sRewardFinished = true;
        } else if ((Message_GetState(&play->msgCtx) == TEXT_STATE_DONE) || (Message_GetState(&play->msgCtx) == TEXT_STATE_5)) {
            sRewardFinished = true;
        }
    }
}

void EnInvadepoh_RewardRomani_WaitForObject(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    EnInvadePohUnkStruct_324* temp_s0 = &this->unk_324;

    if (Object_IsLoaded(&play2->objectCtx, this->bankIndex)) {
        this->actor.objBankIndex = this->bankIndex;
        Actor_SetObjectDependency(play, &this->actor);
        EnInvadepoh_Romani_DesegmentTextures();
        this->actor.update = EnInvadepoh_RewardRomani_Update;
        SkelAnime_InitFlex(play, &this->skelAnime, &gRomaniSkel, &gRomaniWalkAnim, this->jointTable, this->morphTable,
                           ROMANI_LIMB_MAX);
        Animation_MorphToLoop(&this->skelAnime, &gRomaniIdleAnim, 0.0f);
        EnInvadepoh_func_80B45C04(&this->unk_324, D_80B4EA90, 1, D_80B4EB00, 3, &gZeroVec3s, 0x7D0, 0.08f, 0.3f, 0.03f);
        temp_s0->unk_30 = 0.08f;
        temp_s0->unk_2C = 0x7D0;
        func_800B4AEC(play, &this->actor, 50.0f);
        EnInvadepoh_SnapToFloor(this);
        EnInvadepoh_func_80B4ACDC(this);
    }
}

void EnInvadepoh_RewardRomani_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    EnInvadePohUnkStruct_324* temp_s0 = &this->unk_324;
    s32 inUncullRange = CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40);

    this->actionFunc(this, play);

    if (inUncullRange && (this->actor.update != NULL)) {
        Player* player;
        s16 temp_v1;

        SkelAnime_Update(&this->skelAnime);
        player = GET_PLAYER(play);
        Math_StepToS(&this->unk_370, 0x7D0, 0x28);
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 6, this->unk_370, 40);
        temp_v1 = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos) * 0.9f;
        temp_s0->unk_26.x = CLAMP((s16)(temp_v1 - this->actor.shape.rot.x), -0xBB8, 0xBB8);

        temp_v1 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
        temp_s0->unk_26.y = CLAMP((s16)(temp_v1 * 0.7f), -0x1F40, 0x1F40);
        EnInvadepoh_func_80B45CE0(&this->unk_324);
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    }
}

void EnInvadepoh_func_80B4B3DC(EnInvadepoh* this) {
    s32 pad;

    if (Animation_OnFrame(&this->skelAnime, 1.0f) || Animation_OnFrame(&this->skelAnime, 7.0f)) {
        Actor_PlaySfx(&this->actor, NA_SE_EV_MONKEY_WALK);
    }
}

void EnInvadepoh_func_80B4B430(EnInvadepoh* this) {
    Animation_MorphToLoop(&this->skelAnime, &gDogWalkAnim, -6.0f);
    this->actionTimer = Rand_S16Offset(50, 80);
    this->actionFunc = EnInvadepoh_func_80B4B484;
}

void EnInvadepoh_func_80B4B484(EnInvadepoh* this, PlayState* play) {
    Math_StepToF(&this->actor.speed, 1.1f, 0.5f);
    if (EnInvadepoh_func_80B44C80(this, play)) {
        EnInvadepoh_func_80B44690(this);
    }
    EnInvadepoh_func_80B4B3DC(this);
    if (this->dogTargetPoint >= 0) {
        this->actionTimer = 0;
    }
    if (this->actionTimer > 0) {
        this->actionTimer--;
    } else {
        EnInvadepoh_func_80B4B510(this);
    }
}

void EnInvadepoh_func_80B4B510(EnInvadepoh* this) {
    Animation_MorphToLoop(&this->skelAnime, &gDogRunAnim, -6.0f);
    this->actionTimer = Rand_S16Offset(50, 200);
    this->actionFunc = EnInvadepoh_func_80B4B564;
}

void EnInvadepoh_func_80B4B564(EnInvadepoh* this, PlayState* play) {
    Math_StepToF(&this->actor.speed, 3.8f, 0.45f);
    if (this->dogTargetPoint >= 0) {
        f32 temp_fv0;
        Vec3f sp28;

        Math_Vec3s_ToVec3f(&sp28, &this->pathPoints[this->dogTargetPoint]);
        temp_fv0 = Math3D_Vec3fDistSq(&this->actor.world.pos, &sp28);
        if (temp_fv0 < SQ(80.0f)) {
            this->actor.speed *= 0.85f;
        } else if (temp_fv0 < SQ(150.0f)) {
            this->actor.speed *= 0.93f;
        } else if (temp_fv0 < SQ(250.0f)) {
            this->actor.speed *= 0.96f;
        }
        if ((this->currentPoint == this->dogTargetPoint) || (temp_fv0 < SQ(50.0f))) {
            this->actionTimer = 0;
        }
    }
    EnInvadepoh_func_80B4B3DC(this);
    if (EnInvadepoh_func_80B44C80(this, play)) {
        EnInvadepoh_func_80B44690(this);
    }
    if (this->actionTimer > 0) {
        this->actionTimer--;
    } else if (this->dogTargetPoint >= 0) {
        if (!sAliensTooClose && (Rand_ZeroOne() < 0.4f)) {
            Actor_PlaySfx(&this->actor, NA_SE_EV_SMALL_DOG_GROAN);
        }
        EnInvadepoh_func_80B4B724(this);
    } else {
        EnInvadepoh_func_80B4B430(this);
    }
}

void EnInvadepoh_func_80B4B724(EnInvadepoh* this) {
    Animation_MorphToPlayOnce(&this->skelAnime, &gDogBarkAnim, -6.0f);
    this->actionFunc = EnInvadepoh_func_80B4B768;
}

void EnInvadepoh_func_80B4B768(EnInvadepoh* this, PlayState* play) {
    s32 pad;

    Math_StepToF(&this->actor.speed, 0.0f, 1.0f);
    Math_SmoothStepToS(&this->actor.world.rot.y, Actor_WorldYawTowardActor(&this->actor, &sClosestAlien->actor), 5, 0x1388,
                       (s16)0x64);
    EnInvadepoh_func_80B44E90(this, play);
    if (Animation_OnFrame(&this->skelAnime, 13.0f) || Animation_OnFrame(&this->skelAnime, 19.0f)) {
        Actor_PlaySfx(&this->actor, NA_SE_EV_SMALL_DOG_ANG_BARK);
    }
    if (this->finishedAnim) {
        EnInvadepoh_func_80B4B510(this);
    }
}

void EnInvadepoh_func_80B4B820(EnInvadepoh* this) {
    Animation_MorphToPlayOnce(&this->skelAnime, &gDogJumpAnim, -6.0f);
    this->actionFunc = EnInvadepoh_func_80B4B864;
}

void EnInvadepoh_func_80B4B864(EnInvadepoh* this, PlayState* play) {
    Math_StepToF(&this->actor.speed, 0.5f, 1.0f);
    EnInvadepoh_func_80B44E90(this, play);
    if (this->finishedAnim) {
        EnInvadepoh_func_80B4B510(this);
    }
}

void EnInvadepoh_Dog_WaitForObject(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if (Object_IsLoaded(&play->objectCtx, this->bankIndex)) {
        if(1) {}
        this->actor.objBankIndex = this->bankIndex;
        Actor_SetObjectDependency(play, &this->actor);
        SkelAnime_InitFlex(play, &this->skelAnime, &gDogSkel, &gDogWalkAnim, this->jointTable, this->morphTable,
                           DOG_LIMB_MAX);
        EnInvadepoh_func_80B45C04(&this->unk_324, NULL, 0, NULL, 0, &gZeroVec3s, 0xBB8, 0.1f, 0.0f, 0.0f);
        EnInvadepoh_Dog_SetupPath(this, play);
        EnInvadepoh_SetPosToPathPoint(this, 0);
        func_800B4AEC(play, &this->actor, 50.0f);
        EnInvadepoh_SnapToFloor(this);
        Math_Vec3f_Copy(&this->unk_314, &this->actor.world.pos);
        if (sEventState == ENINVADEPOH_EVENT_ACTIVE) {
            this->actor.update = EnInvadepoh_Dog_Update;
            this->actor.draw = EnInvadepoh_Dog_Draw;
            this->actor.flags |= ACTOR_FLAG_1;
            EnInvadepoh_func_80B4B430(this);
        } else if (sEventState == ENINVADEPOH_EVENT_WAIT) {
            this->actor.update = EnInvadepoh_Dog_WaitForEvent;
        } else {
            Actor_Kill(&this->actor);
        }
    }
}

void EnInvadepoh_Dog_WaitForEvent(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if (sEventState == ENINVADEPOH_EVENT_ACTIVE) {
        this->actor.update = EnInvadepoh_Dog_Update;
        this->actor.draw = EnInvadepoh_Dog_Draw;
        this->actor.flags |= ACTOR_FLAG_1;
        EnInvadepoh_func_80B4B430(this);
    }
}

void EnInvadepoh_Dog_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    s32 inUncullRange = CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40);

    sClosestAlien = EnInvadepoh_Dog_GetClosestAlien();
    if (sClosestAlien == NULL) {
        s32 hadTarget = (this->dogTargetPoint >= 0);

        this->dogTargetPoint = -1;
        if (hadTarget) {
            EnInvadepoh_func_80B4B820(this);
        }
    } else {
        s32 lastTargetPoint = this->dogTargetPoint;
        s32 pointsToTarget;
        s32 halfwayPoint;

        this->dogTargetPoint = EnInvadepoh_func_80B44234(this, &sClosestAlien->actor.world.pos);
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
    this->finishedAnim = SkelAnime_Update(&this->skelAnime);
    if (inUncullRange && (this->actor.update != NULL)) {
        EnInvadepoh_func_80B45CE0(&this->unk_324);
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    }
}

void EnInvadepoh_func_80B4BBE0(EnInvadepoh* this) {
    EnInvadePohUnkStruct_324* temp_v0 = &this->unk_324;

    Animation_MorphToLoop(&this->skelAnime, &gCremiaWalkAnim, -6.0f);
    temp_v0->unk_26.x = 0;
    temp_v0->unk_26.y = 0;
    temp_v0->unk_26.z = 0;
    temp_v0->unk_30 = 0.1f;
    temp_v0->unk_2C = 0x320;

    this->unk_370 = 0;
    this->actionFunc = EnInvadepoh_func_80B4BC4C;
}

void EnInvadepoh_func_80B4BC4C(EnInvadepoh* this, PlayState* play) {
    EnInvadePohUnkStruct_324* temp_s0 = &this->unk_324;
    EnInvadepoh* romani = sRomani;
    s32 pad;
    s32 sp48;
    s32 pad2;
    s16 sp42;
    s16 sp40;
    s16 temp_v1;

    if (romani != NULL) {
        if (romani->currentPoint == 0) {
            this->unk_2F8 = 40.0f;
            this->unk_304 = -0x8000;
            this->actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_8);
        } else if (romani->currentPoint < (romani->endPoint - 1)) {
            this->unk_2F8 = 40.0f;
            Math_ScaledStepToS(&this->unk_304, -0x4800, 0xC8);
            this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_8);
        } else {
            Math_StepToF(&this->unk_2F8, 5.0f, 3.0f);
            Math_ScaledStepToS(&this->unk_304, -0x8000, 0x12C);
            this->actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_8);
        }
        sp42 = this->unk_304 + romani->actor.world.rot.y;
        this->actor.world.pos.x = (Math_SinS(sp42) * this->unk_2F8) + romani->actor.world.pos.x;
        this->actor.world.pos.y = romani->actor.world.pos.y;
        this->actor.world.pos.z = (Math_CosS(sp42) * this->unk_2F8) + romani->actor.world.pos.z;
        func_800B4AEC(play, &this->actor, 50.0f);
        EnInvadepoh_SnapToFloor(this);
        Math_StepToS(&this->unk_370, 0xBB8, 0x1F5);
        if (Math3D_Vec3fDistSq(&this->actor.prevPos, &this->actor.world.pos) > SQ(0.01f)) {
            Math_SmoothStepToS(&this->actor.shape.rot.y, Math_Vec3f_Yaw(&this->actor.prevPos, &this->actor.world.pos),
                               3, this->unk_370, 0x1F4);
        }
        sp48 = (play->gameplayFrames + 20) % 0x80;
        if (sp48 & 0x40) {
            sp40 = Math_Vec3f_Yaw(&this->actor.world.pos, &romani->actor.world.pos);
            if (sp48 == 0x40) {
                this->unk_370 = 0;
            }
            Math_StepToS(&this->unk_370, 0x7D0, 0x28);
            Math_SmoothStepToS(&this->actor.shape.rot.y, sp40, 6, this->unk_370, 0x28);
            temp_v1 = Math_Vec3f_Pitch(&this->actor.focus.pos, &romani->actor.focus.pos) * 0.85f;
            temp_s0->unk_26.x = CLAMP((s16)(temp_v1 - this->actor.shape.rot.x), -0xBB8, 0xBB8);

            temp_v1 = sp40 - this->actor.shape.rot.y;
            temp_s0->unk_26.y = CLAMP((s16)(temp_v1 * 0.7f), -0x1F40, 0x1F40);
        }
    }

    if (CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40) &&
        (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 12.0f))) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_ROMANI_WALK);
    }
    if (gSaveContext.save.time > CLOCK_TIME(20, 15)) {
        Actor_Kill(&this->actor);
    } else if ((romani != NULL) && (romani->actionFunc == EnInvadepoh_func_80B4CB0C)) {
        EnInvadepoh_func_80B4C1BC(this);
    }
}

void EnInvadepoh_func_80B4BFFC(EnInvadepoh* this) {
    this->unk_324.unk_30 = 0.08f;
    this->unk_324.unk_2C = 0x7D0;
    Animation_MorphToLoop(&this->skelAnime, &gCremiaIdleAnim, -6.0f);
    this->unk_370 = 0;
    this->actionFunc = EnInvadepoh_func_80B4C058;
}

void EnInvadepoh_func_80B4C058(EnInvadepoh* this, PlayState* play) {
    EnInvadePohUnkStruct_324* temp_s0 = &this->unk_324;
    Player* sp28 = GET_PLAYER(play);
    s16 temp_v1;

    Math_StepToS(&this->unk_370, 0x9C4, 0x1C2);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, this->unk_370, 0x28);
    temp_v1 = Math_Vec3f_Pitch(&this->actor.focus.pos, &sp28->actor.focus.pos) * 0.85f;
    temp_s0->unk_26.x = CLAMP((s16)(temp_v1 - this->actor.shape.rot.x), -0xBB8, 0xBB8);

    temp_v1 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
    temp_s0->unk_26.y = CLAMP((s16)(temp_v1 * 0.7f), -0x1F40, 0x1F40);
    if (Actor_TextboxIsClosing(&this->actor, play)) {
        EnInvadepoh_func_80B4BBE0(this);
    }
}

void EnInvadepoh_func_80B4C1BC(EnInvadepoh* this) {
    this->unk_324.unk_30 = 0.08f;
    this->unk_324.unk_2C = 0x7D0;
    Animation_MorphToLoop(&this->skelAnime, &gCremiaIdleAnim, -6.0f);
    this->unk_370 = 0;
    this->actionFunc = EnInvadepoh_func_80B4C218;
}

void EnInvadepoh_func_80B4C218(EnInvadepoh* this, PlayState* play) {
    EnInvadePohUnkStruct_324* temp_s0 = &this->unk_324;
    Player* sp28 = GET_PLAYER(play);
    s16 temp_v1;

    Math_StepToS(&this->unk_370, 0x7D0, 0xC8);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 6, this->unk_370, 0x28);
    temp_v1 = Math_Vec3f_Pitch(&this->actor.focus.pos, &sp28->actor.focus.pos) * 0.85f;
    temp_s0->unk_26.x = CLAMP((s16)(temp_v1 - this->actor.shape.rot.x), -0xBB8, 0xBB8);

    temp_v1 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
    temp_s0->unk_26.y = CLAMP((s16)(temp_v1 * 0.7f), -0x1F40, 0x1F40);
    if (sRomani == NULL) {
        EnInvadepoh_func_80B4BBE0(this);
    } else if ((sRomani != NULL) && (sRomani->actionFunc != EnInvadepoh_func_80B4CB0C)) {
        EnInvadepoh_func_80B4BBE0(this);
    }
}

void EnInvadepoh_Cremia_WaitForObject(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    s32 pad;

    if (Object_IsLoaded(&play2->objectCtx, this->bankIndex)) {
        s32 sp38 = gSaveContext.save.time;

        this->actor.objBankIndex = this->bankIndex;
        Actor_SetObjectDependency(play, &this->actor);
        EnInvadepoh_Cremia_DesegmentTextures();
        SkelAnime_InitFlex(play, &this->skelAnime, &gCremiaSkel, &gCremiaWalkAnim, this->jointTable, this->morphTable,
                           CREMIA_LIMB_MAX);
        EnInvadepoh_func_80B45C04(&this->unk_324, D_80B4EBDC, 1, D_80B4EC08, 0, &gZeroVec3s, 100, 0.03f, 0.3f, 0.03f);
        this->actor.textId = 0x33CD; // Good night... See you...tomorrow...OK?
        if (sp38 < CLOCK_TIME(20, 01) + 30) {
            this->unk_304 = -0x8000;
            this->unk_2F8 = 40.0f;
        } else if (sp38 > CLOCK_TIME(20, 14) + 1) {
            this->unk_304 = -0x4800;
            this->unk_2F8 = 20.0f;
        } else {
            this->unk_304 = -0x8000;
            this->unk_2F8 = 40.0f;
        }
        if ((CLOCK_TIME(6, 00) <= sp38) && (sp38 < CLOCK_TIME(20, 00) + 30)) {
            this->actor.update = EnInvadepoh_Cremia_WaitForEvent;
            this->actor.draw = NULL;
        } else if ((CLOCK_TIME(20, 00) + 30 <= sp38) && (sp38 < CLOCK_TIME(20, 15))) {
            this->actor.update = EnInvadepoh_Cremia_Update;
            this->actor.draw = EnInvadepoh_Cremia_Draw;
            EnInvadepoh_func_80B4BBE0(this);
        } else {
            Actor_Kill(&this->actor);
        }
    }
}

void EnInvadepoh_Cremia_WaitForEvent(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if ((gSaveContext.save.time >= CLOCK_TIME(20, 00) + 30) && (gSaveContext.save.time < CLOCK_TIME(20, 15))) {
        this->actor.update = EnInvadepoh_Cremia_Update;
        this->actor.draw = EnInvadepoh_Cremia_Draw;
        EnInvadepoh_func_80B4BBE0(this);
    }
}

void EnInvadepoh_Cremia_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    s32 inUncullRange = CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40);
    s32 talkRequested = Actor_ProcessTalkRequest(&this->actor, &play->state);

    if (talkRequested) {
        func_80151BB4(play, 6);
        EnInvadepoh_func_80B4BFFC(this);
    }
    this->actionFunc(this, play2);
    if (inUncullRange && (this->actor.update != NULL)) {
        SkelAnime_Update(&this->skelAnime);
        EnInvadepoh_func_80B45CE0(&this->unk_324);
        if ((this->actionFunc != EnInvadepoh_func_80B4C058) && !talkRequested && this->actor.isTargeted) {
            func_800B8614(&this->actor, play, 350.0f);
        }
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    }
}

void EnInvadepoh_func_80B4C6C8(EnInvadepoh* this) {
    EnInvadePohUnkStruct_324* temp_v0 = &this->unk_324;

    Animation_MorphToLoop(&this->skelAnime, &gRomaniWalkAnim, -10.0f);
    temp_v0->unk_26.x = 0;
    temp_v0->unk_26.y = 0;
    temp_v0->unk_26.z = 0;
    temp_v0->unk_30 = 0.1f;
    temp_v0->unk_2C = 0x320;
    this->actionFunc = EnInvadepoh_func_80B4C730;
}

void EnInvadepoh_func_80B4C730(EnInvadepoh* this, PlayState* play) {
    EnInvadePohUnkStruct_324* temp_s0 = &this->unk_324;
    EnInvadepoh* sp68 = sCremia;
    s32 var_a2;
    s32 sp60;
    s32 pad;
    s16 temp_v2;
    Vec3f sp4C;
    Vec3f sp40;

    EnInvadepoh_func_80B44700(this);
    EnInvadepoh_func_80B44EFC(this, play);
    EnInvadepoh_func_80B43E6C(this, 6, 0x7D0, 0x64);

    var_a2 = (this->currentPoint < this->endPoint) ? this->currentPoint : this->endPoint - 1;

    Math_Vec3s_ToVec3f(&sp4C, &this->pathPoints[var_a2]);
    Math_Vec3s_ToVec3f(&sp40, &this->pathPoints[var_a2 + 1]);
    Math_SmoothStepToS(&this->actor.world.rot.y, Math_Vec3f_Yaw(&sp4C, &sp40) + 0, 5, 0x7D0, 100);
    if ((this->currentPoint == 0) || (this->currentPoint + 1 == this->endPoint)) {
        if (this->unk_378 == 0) {
            s32 temp_v0_2 = func_800FE620(play);

            if (temp_v0_2 > 0) {
                temp_v0_2 = (gRegEditor->data[0xF] * -23.0f / temp_v0_2) - 0.5f;
                this->unk_378 = EnInvadepoh_func_80B45550(this, play, SQ(80.0f), temp_v0_2);
            }
        }
        this->actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_8);
    } else {
        this->unk_378 = 0;
        this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_8);
    }
    sp60 = play->gameplayFrames % 0x80;
    if (sp60 & 0x40) {
        s16 sp3A = Math_Vec3f_Yaw(&this->actor.world.pos, &sp68->actor.world.pos);
        s16 temp_v1;

        if (sp60 == 0x40) {
            this->unk_370 = 0;
        }
        Math_StepToS(&this->unk_370, 0x7D0, 0x28);
        Math_SmoothStepToS(&this->actor.shape.rot.y, sp3A, 6, this->unk_370, 40);
        temp_v1 = Math_Vec3f_Pitch(&this->actor.focus.pos, &sp68->actor.focus.pos) * 0.85f;
        temp_s0->unk_26.x = CLAMP((s16)(temp_v1 - this->actor.shape.rot.x), -0xBB8, 0xBB8);

        temp_v1 = sp3A - this->actor.shape.rot.y;
        temp_s0->unk_26.y = CLAMP((s16)(temp_v1 * 0.7f), -0x1F40, 0x1F40);
    }
    if (CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40) &&
        (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 7.0f))) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_ROMANI_WALK);
    }
    if (this->progress >= 0.9999f) {
        Actor_Kill(&this->actor);
    } else if ((sp68 != NULL) && (sp68->actionFunc == EnInvadepoh_func_80B4C058)) {
        EnInvadepoh_func_80B4CC70(this);
    }
}

void EnInvadepoh_func_80B4CAB0(EnInvadepoh* this) {
    this->unk_324.unk_30 = 0.08f;
    this->unk_324.unk_2C = 0xFA0;
    Animation_MorphToLoop(&this->skelAnime, &gRomaniIdleAnim, -10.0f);
    this->unk_370 = 0;
    this->actionFunc = EnInvadepoh_func_80B4CB0C;
}

void EnInvadepoh_func_80B4CB0C(EnInvadepoh* this, PlayState* play) {
    EnInvadePohUnkStruct_324* temp_s0 = &this->unk_324;
    Player* player = GET_PLAYER(play);
    s16 temp_v1;

    Math_StepToS(&this->unk_370, 0xBB8, 0x1F4);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 6, this->unk_370, 40);
    temp_v1 = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos) * 0.85f;
    temp_s0->unk_26.x = CLAMP((s16)(temp_v1 - this->actor.shape.rot.x), -0xBB8, 0xBB8);

    temp_v1 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
    temp_s0->unk_26.y = CLAMP((s16)(temp_v1 * 0.7f), -0x1F40, 0x1F40);
    if (Actor_TextboxIsClosing(&this->actor, play)) {
        EnInvadepoh_func_80B4C6C8(this);
    }
}

void EnInvadepoh_func_80B4CC70(EnInvadepoh* this) {
    this->unk_324.unk_30 = 0.08f;
    this->unk_324.unk_2C = 0x7D0;
    Animation_MorphToLoop(&this->skelAnime, &gRomaniIdleAnim, -10.0f);
    this->unk_370 = 0;
    this->actionFunc = EnInvadepoh_func_80B4CCCC;
}

void EnInvadepoh_func_80B4CCCC(EnInvadepoh* this, PlayState* play) {
    EnInvadePohUnkStruct_324* temp_s0 = &this->unk_324;
    Player* player = GET_PLAYER(play);
    s16 temp_v1;

    Math_StepToS(&this->unk_370, 0x7D0, 0xC8);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 6, this->unk_370, 40);
    temp_v1 = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos) * 0.85f;
    temp_s0->unk_26.x = CLAMP((s16)(temp_v1 - this->actor.shape.rot.x), -0xBB8, 0xBB8);

    temp_v1 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
    temp_s0->unk_26.y = CLAMP((s16)(temp_v1 * 0.7f), -0x1F40, 0x1F40);
    if (sCremia == NULL) {
        EnInvadepoh_func_80B4C6C8(this);
    } else if ((sCremia != NULL) && (sCremia->actionFunc != EnInvadepoh_func_80B4C058)) {
        EnInvadepoh_func_80B4C6C8(this);
    }
}

void EnInvadepoh_Night3Romani_WaitForObject(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    s32 pad;

    if (Object_IsLoaded(&play2->objectCtx, this->bankIndex)) {
        s32 sp38 = gSaveContext.save.time;

        this->actor.objBankIndex = this->bankIndex;
        Actor_SetObjectDependency(play, &this->actor);
        EnInvadepoh_Romani_DesegmentTextures();
        SkelAnime_InitFlex(play, &this->skelAnime, &gRomaniSkel, &gRomaniWalkAnim, this->jointTable, this->morphTable,
                           ROMANI_LIMB_MAX);
        EnInvadepoh_func_80B45C04(&this->unk_324, D_80B4EA90, 1, D_80B4EB00, 3, &gZeroVec3s, 100, 0.03f, 0.3f, 0.03f);
        EnInvadepoh_func_80B446D0(this, play);
        this->actor.world.rot.y = this->actor.shape.rot.y;
        EnInvadepoh_func_80B44700(this);
        EnInvadepoh_func_80B44EFC(this, play);
        EnInvadepoh_SetYawAlongPath(this);
        EnInvadepoh_SnapToFloor(this);
        this->actor.textId = 0x33CE; // See you tomorrow!
        if ((sp38 >= CLOCK_TIME(6, 00)) && (sp38 < CLOCK_TIME(20, 00))) {
            this->actor.update = EnInvadepoh_Night3Romani_WaitForEvent;
            this->actor.draw = NULL;
        } else if ((sp38 >= CLOCK_TIME(20, 00)) && (sp38 < CLOCK_TIME(20, 14) + 15)) {
            this->actor.update = EnInvadepoh_Night3Romani_Update;
            this->actor.draw = EnInvadepoh_Romani_Draw;
            EnInvadepoh_func_80B4C6C8(this);
        } else {
            Actor_Kill(&this->actor);
        }
    }
}

void EnInvadepoh_Night3Romani_WaitForEvent(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if ((gSaveContext.save.time >= CLOCK_TIME(20, 00)) && (gSaveContext.save.time < CLOCK_TIME(20, 14) + 15)) {
        this->actor.update = EnInvadepoh_Night3Romani_Update;
        this->actor.draw = EnInvadepoh_Romani_Draw;
        EnInvadepoh_func_80B4C6C8(this);
    }
}

void EnInvadepoh_Night3Romani_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    s32 inUncullRange = CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40);
    s32 talkRequested = Actor_ProcessTalkRequest(&this->actor, &play->state);

    if (talkRequested) {
        func_80151BB4(play, 5);
        EnInvadepoh_func_80B4CAB0(this);
    }
    this->actionFunc(this, play);
    if (inUncullRange && (this->actor.update != NULL)) {
        SkelAnime_Update(&this->skelAnime);
        EnInvadepoh_func_80B45CE0(&this->unk_324);
        if ((this->actionFunc != EnInvadepoh_func_80B4CB0C) && !talkRequested && this->actor.isTargeted) {
            func_800B8614(&this->actor, play, 350.0f);
        }
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    }
}

void EnInvadepoh_func_80B4D15C(EnInvadepoh* this) {
    static EnInvadepohUnkStruct1 D_80B4EE0C[3] = {
        { 0.08f, 0x2BC, -0xA },
        { 0.09f, 0x12C, -5 },
        { 0.05f, 0x190, 0 },
    };
    s32 pad;
    s32 sp28 = ENINVADEPOH_GET_PARAM_7(&this->actor);
    s32 pad2;

    Animation_PlayLoop(&this->skelAnime, &gAlienHoldingCowAnim);
    this->skelAnime.curFrame = (ENINVADEPOH_GET_PARAM_7(&this->actor)) * this->skelAnime.endFrame * 0.25f;
    this->alpha = 255;
    this->actor.draw = EnInvadepoh_Alien_Draw;
    this->present = true;
    this->drawDeathFlash = false;
    this->eyeBeamAlpha = 255;
    this->unk_300 = D_80B4EE0C[sp28].unk0;
    this->unk_304 = sp28 * 0x5555;
    this->actor.world.pos.x = Math_SinS(this->unk_304) * 80.0f + this->actor.home.pos.x;
    this->actor.world.pos.y = this->actor.home.pos.y;
    this->actor.world.pos.z = Math_CosS(this->unk_304) * 80.0f + this->actor.home.pos.z;
    this->actor.shape.rot.y = this->unk_304 + 0x4000;
    this->unk_370 = D_80B4EE0C[sp28].unk4;
    this->unk_372 = D_80B4EE0C[sp28].unk6;
    this->actionFunc = EnInvadepoh_func_80B4D290;
    this->actor.velocity.y = 0.0f;
}

void EnInvadepoh_func_80B4D290(EnInvadepoh* this, PlayState* play) {
    Actor* sp2C;
    f32 sp28;

    if (sLightBall == NULL) {
        Actor_Kill(&this->actor);
        return;
    }
    Math_StepToF(&this->actor.velocity.y, 15.0f, this->unk_300);
    sp28 = Math_SmoothStepToF(&this->actor.world.pos.y, this->actor.home.pos.y + 850.0f, 0.2f, this->actor.velocity.y,
                              0.01f);
    this->unk_304 += 0x2BC;
    this->actor.world.pos.x = Math_SinS(this->unk_304) * 80.0f + this->actor.home.pos.x;
    this->actor.world.pos.z = Math_CosS(this->unk_304) * 80.0f + this->actor.home.pos.z;
    this->unk_370 += this->unk_372;
    this->actor.shape.rot.y += this->unk_370;

    if (this->actor.child != NULL) {
        sp2C = this->actor.child;
        sp2C->world.pos.x = this->actor.world.pos.x;
        sp2C->world.pos.y = this->actor.world.pos.y - 38.0f;
        sp2C->world.pos.z = this->actor.world.pos.z;
        sp2C->shape.rot.y = this->actor.shape.rot.y;
    }
    if (sp28 < 5.0f) {
        Actor_Kill(&this->actor);
    }
}

void EnInvadepoh_func_80B4D3E4(EnInvadepoh* this) {
    Animation_PlayLoop(&this->skelAnime, &gAlienHoldingCowAnim);
    this->skelAnime.curFrame = (ENINVADEPOH_GET_PARAM_7(&this->actor)) * this->skelAnime.endFrame * 0.25f;
    this->alpha = 255;
    this->actor.draw = NULL;
    this->present = true;
    this->drawDeathFlash = false;
    this->eyeBeamAlpha = 255;
    this->unk_306 = 0x190;
    this->unk_304 = 0;
    this->actionTimer = 200;
    this->actionFunc = EnInvadepoh_func_80B4D480;
    this->actor.velocity.y = 0.0f;
}

void EnInvadepoh_func_80B4D480(EnInvadepoh* this, PlayState* play) {
    s32 pad;
    f32 pad2;
    s32 sp2C = 0;

    if (this->actionTimer > 0) {
        this->actionTimer--;
    }
    if (this->actionTimer > 160) {
        this->actor.draw = NULL;
    } else {
        this->actor.draw = EnInvadepoh_Alien_Draw;
        pad = (sp2C ? 0 : this->actionTimer); //! fake
        if ((105 > pad) && (pad >= 100)) {
            this->actor.gravity = -1.0f;
            Math_SmoothStepToS(&this->actor.shape.rot.x, 0x2000, 8, 0x320, 0x28);
        } else {
            this->actor.gravity = 0.7f;
            Math_SmoothStepToS(&this->actor.shape.rot.x, 0, 8, 0x320, 0x28);
        }

        this->actor.velocity.y += this->actor.gravity;
        this->actor.velocity.y *= 0.92f;
        if (this->actionTimer > 80) {
            this->actor.world.pos.y += this->actor.velocity.y;
        } else {
            f32 pad3 = this->actor.home.pos.y + 850.0f;

            sp2C = Math_StepToF(&this->actor.world.pos.y, pad3, fabsf(this->actor.velocity.y));
        }
        pad2 = (this->unk_304 * -0.06f) + this->unk_306;
        pad2 *= 0.98f;
        this->unk_306 = pad2;
        this->actor.shape.rot.y += this->unk_306;
        if (this->actor.child != NULL) {
            Actor* pad1 = this->actor.child;

            pad1->world.pos.x = this->actor.world.pos.x;
            pad1->world.pos.y = this->actor.world.pos.y - 30.0f;
            pad1->world.pos.z = this->actor.world.pos.z;
            pad1->shape.rot.y = this->actor.shape.rot.y;
        }
    }
    if ((this->actionTimer <= 0) || sp2C) {
        Actor_Kill(&this->actor);
    }
}

void EnInvadepoh_Abuductor_WaitForObject(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    s32 sp34;

    if (Object_IsLoaded(&play->objectCtx, this->bankIndex)) {
        sp34 = ENINVADEPOH_GET_PARAM_7(&this->actor);
        this->actor.objBankIndex = this->bankIndex;
        Actor_SetObjectDependency(play, &this->actor);
        EnInvadepoh_Alien_SetTexAnim();
        this->actor.update = EnInvadepoh_Abductor_Update;
        SkelAnime_InitFlex(play, &this->skelAnime, &gAlienSkel, &gAlienHoldingCowAnim, this->jointTable, this->morphTable,
                           ALIEN_LIMB_MAX);
        if (sp34 < 3) {
            EnInvadepoh_func_80B453F4(this, play, sp34);
            EnInvadepoh_func_80B4D15C(this);
        } else {
            EnInvadepoh_func_80B45460(this, play);
            EnInvadepoh_func_80B4D3E4(this);
        }
    }
}

void EnInvadepoh_Abductor_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    this->actionFunc(this, play);

    if (this->actor.update != NULL) {
        SkelAnime_Update(&this->skelAnime);
        func_800B9010(&this->actor, NA_SE_EN_FOLLOWERS_BEAM_PRE - SFX_FLAG);
    }
}

void EnInvadepoh_Event_DrawWarps(PlayState* play) {
    s32 i;
    EnInvadepohWarpEffect* warpEffect;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C2DC(play->state.gfxCtx);

    for (i = 0, warpEffect = D_80B50350; i < 10; i++, warpEffect++) {
        if (warpEffect->timer > 0) {
            u32 temp_s5 = (play->gameplayFrames + (u8)(i * 0x10)) % 0x80;
            u32 temp_s6 = (play->gameplayFrames * -0xF) % 0x100;

            Matrix_Translate(warpEffect->pos.x, warpEffect->pos.y, warpEffect->pos.z, MTXMODE_NEW);
            Matrix_Scale(0.1f, 0.1f, 0.1f, MTXMODE_APPLY);
            gDPPipeSync(POLY_XLU_DISP++);
            gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 255, 255, 170, warpEffect->alpha);
            gDPSetEnvColor(POLY_XLU_DISP++, 255, 50, 0, 0);
            gSPSegment(POLY_XLU_DISP++, 0x8,
                       Gfx_TwoTexScroll(play->state.gfxCtx, 0, temp_s5, 0, 0x20, 0x40, 1, 0, temp_s6, 0x20, 0x40));
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_02E510);
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void EnInvadepoh_Event_Draw(Actor* thisx, PlayState* play) {
    EnInvadepoh_Event_DrawWarps(play);
}

s32 EnInvadepoh_Alien_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx,
                              Gfx** gfx) {
    return false;
}

void EnInvadepoh_Alien_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* pos, Actor* thisx, Gfx** gfx) {
    static Vec3f sFocusOffset = { 2000.0f, 1000.0f, 0.0f };
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if ((limbIndex == ALIEN_LIMB_LEFT_EYE) && (this->eyeBeamAlpha != 0)) {
        Matrix_Push();
        Matrix_RotateZS(-0x53ED, MTXMODE_APPLY);
        Matrix_RotateYS(-0x3830, MTXMODE_APPLY);
        Matrix_Scale(1.0f, 1.0f, 1.5f, MTXMODE_APPLY);
        Matrix_Get(&sAlienLeftEyeBeam);
        Matrix_Pop();
    } else if ((limbIndex == ALIEN_LIMB_RIGHT_EYE) && (this->eyeBeamAlpha != 0)) {
        Matrix_Push();
        Matrix_RotateZS(-0x53ED, MTXMODE_APPLY);
        Matrix_RotateYS(-0x47D0, MTXMODE_APPLY);
        Matrix_Scale(1.0f, 1.0f, 1.5f, MTXMODE_APPLY);
        Matrix_Get(&sAlienRightEyeBeam);
        Matrix_Pop();
    }
    if (limbIndex == ALIEN_LIMB_HEAD) {
        Matrix_MultVec3f(&sFocusOffset, &this->actor.focus.pos);
    }
}

void EnInvadepoh_Alien_Draw(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C2DC(play->state.gfxCtx);
    Matrix_Push();
    if (this->present) {
        if (this->alpha == 255) {
            func_8012C28C(play->state.gfxCtx);
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

            Matrix_Mult(&sAlienLeftEyeBeam, MTXMODE_NEW);
            gSPMatrix(ptr++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(ptr++, gAlienEyeBeamDL);

            Matrix_Mult(&sAlienRightEyeBeam, MTXMODE_NEW);
            gSPMatrix(ptr++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(ptr++, gAlienEyeBeamDL);

            POLY_XLU_DISP = ptr;
            CLOSE_DISPS(play->state.gfxCtx);
        }
    }
    if (this->drawDeathFlash) {
        Matrix_SetTranslateRotateYXZ(this->actor.world.pos.x, this->actor.world.pos.y + 68.0f, this->actor.world.pos.z,
                                     &this->actor.shape.rot);
        Matrix_Scale(this->deathFlashScale.x, this->deathFlashScale.y, this->deathFlashScale.z, MTXMODE_APPLY);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gAlienDeathFlashDL);
    }
    if (this->present) {
        Gfx* ptr;
        Vec3f sp80;
        Vec3f sp74;
        s32 temp;

        OPEN_DISPS(play->state.gfxCtx);
        ptr = POLY_XLU_DISP;

        ptr = func_8012C868(ptr);

        gDPSetDither(ptr++, G_CD_NOISE);
        gDPSetCombineLERP(ptr++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE,
                          0);

        Matrix_Mult(&play->billboardMtxF, MTXMODE_NEW);
        Matrix_MultVecZ(60.0f, &sp80);

        sp74.x = this->actor.world.pos.x + sp80.x;
        sp74.y = this->actor.world.pos.y + sp80.y + 68.0f;
        sp74.z = this->actor.world.pos.z + sp80.z;

        Matrix_Translate(sp74.x, sp74.y, sp74.z, MTXMODE_NEW);
        Matrix_Scale(0.25f, 0.25f, 0.25f, MTXMODE_APPLY);

        temp = 100.0f / 255.0f * this->alpha;

        gSPDisplayList(ptr++, gameplay_keep_DL_029CB0);
        gDPSetPrimColor(ptr++, 0, 0, 240, 180, 100, temp);
        gSPMatrix(ptr++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(ptr++, gameplay_keep_DL_029CF0);

        POLY_XLU_DISP = ptr;

        if ((this->alpha > 128) && EnInvadepoh_func_80B456A8(play, &sp74)) {
            func_800F9824(play, &play->envCtx, &play->view, play->state.gfxCtx, sp74, 10.0f, 9.0f, 0, 0);
        }

        CLOSE_DISPS(play->state.gfxCtx);
    }
    Matrix_Pop();

    CLOSE_DISPS(play->state.gfxCtx);
}

s32 EnInvadepoh_Cow_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    if (limbIndex == COW_LIMB_NOSE_RING) {
        rot->x -= this->actor.shape.rot.x;
    }
    return false;
}

void EnInvadepoh_Cow_Draw(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    func_8012C5B0(play->state.gfxCtx);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, (s32)this->skelAnime.dListCount,
                          EnInvadepoh_Cow_OverrideLimbDraw, NULL, &this->actor);
}

void EnInvadepoh_CowTail_Draw(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    func_8012C5B0(play->state.gfxCtx);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount, NULL,
                          NULL, &this->actor);
}

s32 EnInvadepoh_Romani_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    if (limbIndex == ROMANI_LIMB_HEAD) {
        EnInvadepoh* this = ((EnInvadepoh*)thisx);

        rot->x += this->unk_324.unk_20.y;
        rot->y += this->unk_324.unk_20.z;
        rot->z += this->unk_324.unk_20.x;
    } else if (limbIndex == ROMANI_LIMB_TORSO) {
        EnInvadepoh* this = ((EnInvadepoh*)thisx);

        rot->x += (s16)(this->unk_324.unk_34 * this->unk_324.unk_20.y);
        rot->z += this->unk_324.unk_40;
    }
    return false;
}

void EnInvadepoh_Romani_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* pos, Actor* thisx) {
    static Vec3f sFocusOffset = { 400.0f, 270.0f, 0.0f };
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if (limbIndex == ROMANI_LIMB_LEFT_HAND) {
        OPEN_DISPS(play->state.gfxCtx);

        gSPDisplayList(POLY_OPA_DISP++, gRomaniBowDL);

        CLOSE_DISPS(play->state.gfxCtx);
    } else if (limbIndex == ROMANI_LIMB_HEAD) {
        Matrix_MultVec3f(&sFocusOffset, &this->actor.focus.pos);
    }
}

void EnInvadepoh_Romani_Draw(Actor* thisx, PlayState* play) {
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x09, sRomaniMouthTextures[this->unk_324.mouthAnim.curIndex]);
    gSPSegment(POLY_OPA_DISP++, 0x08, sRomaniEyeTextures[this->unk_324.eyeAnim.curIndex]);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnInvadepoh_Romani_OverrideLimbDraw, EnInvadepoh_Romani_PostLimbDraw, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}

void EnInvadepoh_LightBall_Draw(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    Vec3f sp5C;

    Matrix_Push();
    Matrix_Mult(&play->billboardMtxF, MTXMODE_NEW);
    Matrix_MultVecZ(200.0f, &sp5C);
    Matrix_Pop();
    sp5C.x += this->actor.world.pos.x;
    sp5C.y += this->actor.world.pos.y;
    sp5C.z += this->actor.world.pos.z;
    EnInvadepoh_func_80B45518(&sp5C);
    Matrix_ReplaceRotation(&play->billboardMtxF);
    Matrix_RotateZS(this->unk_304, MTXMODE_APPLY);

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C2DC(play->state.gfxCtx);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(POLY_XLU_DISP++, 0xFF, 0x80, 255, 255, 0, 180);
    gDPSetEnvColor(POLY_XLU_DISP++, 255, 50, 0, 0);
    gSPDisplayList(POLY_XLU_DISP++, gEffFlash1DL);

    if (EnInvadepoh_func_80B456A8(play, &sp5C)) {
        func_800F9824(play, &play->envCtx, &play->view, play->state.gfxCtx, sp5C, 20.0f, 9.0f, 0, 0);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

s32 EnInvadepoh_Dog_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    if ((limbIndex == DOG_LIMB_HEAD) || (limbIndex == DOG_LIMB_RIGHT_FACE_HAIR) ||
        (limbIndex == DOG_LIMB_LEFT_FACE_HAIR)) {
        EnInvadepoh* this = (EnInvadepoh*)thisx;

        rot->x += this->unk_324.unk_20.x;
        rot->y += this->unk_324.unk_20.y;
        rot->z += this->unk_324.unk_20.z;
    }
    return false;
}

void EnInvadepoh_Dog_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* pos, Actor* thisx) {
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if (limbIndex == DOG_LIMB_HEAD) {
        Matrix_MultVecY(20.0f, &this->actor.focus.pos);
    }
}

void EnInvadepoh_Dog_Draw(Actor* thisx, PlayState* play) {
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);
    gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 200, 0);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnInvadepoh_Dog_OverrideLimbDraw, EnInvadepoh_Dog_PostLimbDraw, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}

s32 EnInvadepoh_Cremia_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    if (limbIndex == CREMIA_LIMB_HEAD) {
        EnInvadepoh* this = (EnInvadepoh*)thisx;

        rot->x += this->unk_324.unk_20.y;
        rot->y += this->unk_324.unk_20.z;
        rot->z += this->unk_324.unk_20.x;
    } else if (limbIndex == CREMIA_LIMB_TORSO) {
        EnInvadepoh* this = (EnInvadepoh*)thisx;

        rot->x += (s16)(this->unk_324.unk_34 * this->unk_324.unk_20.y);
    }
    return false;
}

void EnInvadepoh_Cremia_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* pos, Actor* thisx) {
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if (limbIndex == CREMIA_LIMB_HEAD) {
        Matrix_MultZero(&this->actor.focus.pos);
    }
}

void EnInvadepoh_Cremia_Draw(Actor* thisx, PlayState* play) {
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x09, sCremiaMouthTextures[this->unk_324.mouthAnim.curIndex]);
    gSPSegment(POLY_OPA_DISP++, 0x08, sCremiaEyeTextures[this->unk_324.eyeAnim.curIndex]);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnInvadepoh_Cremia_OverrideLimbDraw, EnInvadepoh_Cremia_PostLimbDraw, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}
