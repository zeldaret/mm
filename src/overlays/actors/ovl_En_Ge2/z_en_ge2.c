/*
 * File: z_en_ge2.c
 * Overlay: ovl_En_Ge2
 * Description: Purple-clad Gerudo Pirate
 */

#include "z_en_ge2.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_80000000)

#define THIS ((EnGe2*)thisx)

void EnGe2_Init(Actor* thisx, PlayState* play);
void EnGe2_Destroy(Actor* thisx, PlayState* play);
void EnGe2_Update(Actor* thisx, PlayState* play);
void EnGe2_Draw(Actor* thisx, PlayState* play);

s32 func_80B8B6B4(EnGe2* this, PlayState* play);

void func_80B8C45C(EnGe2* this, PlayState* play);
void func_80B8C59C(EnGe2* this, PlayState* play);
void func_80B8C9B8(EnGe2* this, PlayState* play);

s32 EnGe2_ValidatePictograph(PlayState* play, Actor* thisx);

const ActorInit En_Ge2_InitVars = {
    ACTOR_EN_GE2,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_GLA,
    sizeof(EnGe2),
    (ActorFunc)EnGe2_Init,
    (ActorFunc)EnGe2_Destroy,
    (ActorFunc)EnGe2_Update,
    (ActorFunc)EnGe2_Draw,
};

typedef enum {
    /* 0 */ GERUDO_PURPLE_DETECTION_UNDETECTED,
    /* 1 */ GERUDO_PURPLE_DETECTION_HEARD,
    /* 2 */ GERUDO_PURPLE_DETECTION_PROXIMITY // Higher priority
} GerudoPurpleDetection;

#define GERUDO_PURPLE_STATE_PATH_REVERSE (1 << 0) //!< Follow path backwards instead of forwards.
#define GERUDO_PURPLE_STATE_KO (1 << 1)
#define GERUDO_PURPLE_STATE_STUNNED (1 << 2) //!< Specifically by Deku Nuts
#define GERUDO_PURPLE_STATE_DISABLE_MOVEMENT \
    (1 << 3) //!< Disable normal movement to let pathing function control it completely.
#define GERUDO_PURPLE_STATE_CAPTURING (1 << 5) //!< Set but not used

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x038BFBB3, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 30, 60, 0, { 0, 0, 0 } },
};

void EnGe2_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnGe2* this = (EnGe2*)thisx;

    ActorShape_Init(&this->picto.actor.shape, 0.0f, ActorShadow_DrawCircle, 36.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &gGerudoPurpleSkel, NULL, this->jointTable, this->morphTable,
                       GERUDO_PURPLE_LIMB_MAX);
    Animation_PlayLoop(&this->skelAnime, &gGerudoPurpleWalkingAnim);

    Collider_InitAndSetCylinder(play, &this->collider, &this->picto.actor, &sCylinderInit);
    this->picto.actor.colChkInfo.mass = MASS_IMMOVABLE;
    Actor_SetScale(&this->picto.actor, 0.01f);
    this->picto.actor.uncullZoneForward = 1200.0f;

    if (this->picto.actor.world.rot.z == 0) {
        this->verticalDetectRange = 40.0f;
    } else {
        this->verticalDetectRange = fabsf(this->picto.actor.world.rot.z * 20.0f);
    }

    this->picto.actor.world.rot.x = this->picto.actor.shape.rot.x = 0;
    this->picto.actor.world.rot.z = this->picto.actor.shape.rot.z = 0;

    this->picto.actor.targetMode = 6;
    this->stateFlags = 0;
    this->detectedStatus = GERUDO_PURPLE_DETECTION_UNDETECTED;
    this->csAction = -1;

    this->picto.actor.terminalVelocity = -9.0f;
    this->picto.actor.gravity = -1.0f;
    this->picto.actor.speedXZ = 1.5f;

    this->actionFunc = func_80B8C59C;
    this->picto.validationFunc = EnGe2_ValidatePictograph;

    func_80B8B6B4(this, play);

    this->picto.actor.flags |= ACTOR_FLAG_10;
    if (play->actorCtx.unk5 & 2) {
        this->picto.actor.flags |= (ACTOR_FLAG_10 | ACTOR_FLAG_20);
    }

    switch (GERUDO_PURPLE_GET_TYPE(&this->picto.actor)) {
        case GERUDO_PURPLE_TYPE_OUTSIDE_FORTRESS:
            Animation_Change(&this->skelAnime, &gGerudoPurpleLookingAboutAnim, 1.0f, 0.0f,
                             Animation_GetLastFrame(&gGerudoPurpleLookingAboutAnim), 0, 0.0f);
            this->actionFunc = func_80B8C9B8;
            this->picto.actor.speedXZ = 0.0f;
            this->picto.actor.uncullZoneForward = 4000.0f;
            break;

        case GERUDO_PURPLE_TYPE_AVEIL_GUARD:
            if (gSaveContext.save.weekEventReg[83] & 2) { // Knocked the beehive down
                Actor_MarkForDeath(&this->picto.actor);
            }
            break;

        default:
            break;
    }
}

void EnGe2_Destroy(Actor* thisx, PlayState* play) {
}

// Detect Player through hearing or proximity
GerudoPurpleDetection EnGe2_DetectPlayer(PlayState* play, EnGe2* this) {
    if (this->picto.actor.xzDistToPlayer > 250.0f) {
        return GERUDO_PURPLE_DETECTION_UNDETECTED;
    } else if ((Player_GetMask(play) != PLAYER_MASK_STONE) && (this->picto.actor.xzDistToPlayer < 50.0f)) {
        return GERUDO_PURPLE_DETECTION_PROXIMITY;
    } else if (func_800B715C(play)) {
        return GERUDO_PURPLE_DETECTION_HEARD;
    } else {
        return GERUDO_PURPLE_DETECTION_UNDETECTED;
    }
}

/**
 * Spotted Player with line-of-sight
 *
 * @param play PlayState
 * @param thisx Actor to use for range and angle checks
 * @param pos Position to check from
 * @param yaw Center of yaw range to check
 * @param yawRange Spread of angles from `yaw` to check. If 0, do not check yaw
 * @param xzRange Horizontal range to check
 * @param yRange Vertical range to check
 * @return true if Player is visible with these settings
 */
s32 EnGe2_LookForPlayer(PlayState* play, Actor* actor, Vec3f* pos, s16 yaw, s16 yawRange, f32 xzRange, f32 yRange) {
    s16 yawToPlayer;
    Vec3f posResult;
    CollisionPoly* outPoly;
    Player* player = GET_PLAYER(play);

    if (Player_GetMask(play) == PLAYER_MASK_STONE) {
        return false;
    }
    if (actor->xzDistToPlayer > xzRange) {
        return false;
    }
    if (fabsf(actor->playerHeightRel) > yRange) {
        return false;
    }

    yawToPlayer = actor->yawTowardsPlayer - yaw;
    if ((yawRange > 0) && (yawRange < ABS_ALT(yawToPlayer))) {
        return false;
    }

    if (BgCheck_AnyLineTest1(&play->colCtx, pos, &player->bodyPartsPos[7], &posResult, &outPoly, false)) {
        return false;
    } else {
        return true;
    }
}

/* Path functions */

s32 func_80B8B6B4(EnGe2* this, PlayState* play) {
    if (GERUDO_PURPLE_GET_PATH(&this->picto.actor) != GERUDO_PURPLE_PATH_NONE) {
        this->path = &play->setupPathList[GERUDO_PURPLE_GET_PATH(&this->picto.actor)];
        if (this->path != NULL) {
            Path* path = this->path;
            Vec3s* points = Lib_SegmentedToVirtual(path->points);
            f32 diffX = points[0].x - this->picto.actor.world.pos.x;
            f32 diffZ = points[0].z - this->picto.actor.world.pos.z;

            if ((SQ(diffX) + SQ(diffZ)) < 100.0f) {
                this->curPointIndex = 0;
                this->stateFlags &= ~GERUDO_PURPLE_STATE_PATH_REVERSE;
            } else {
                this->curPointIndex = path->count - 1;
                this->stateFlags |= GERUDO_PURPLE_STATE_PATH_REVERSE;
                return true;
            }
        }
    } else {
        this->path = NULL;
        this->curPointIndex = 0;
    }
    return false;
}

void func_80B8B7A8(EnGe2* this, PlayState* play) {
    Path* curPath;
    Path* nextPath;
    Vec3s* points;
    u8 unk1;

    this->curPointIndex = 0;

    if (GERUDO_PURPLE_GET_PATH(&this->picto.actor) != GERUDO_PURPLE_PATH_NONE) {
        curPath = &play->setupPathList[GERUDO_PURPLE_GET_PATH(&this->picto.actor)];
        unk1 = curPath->unk1;
        nextPath = &play->setupPathList[unk1];
        this->path = nextPath;
        points = Lib_SegmentedToVirtual(nextPath->points);
        this->picto.actor.world.pos.x = points[0].x;
        this->picto.actor.world.pos.z = points[0].z;
    } else {
        this->path = NULL;
    }
}

void func_80B8B848(EnGe2* this, PlayState* play) {
    s32 pad;
    Vec3s* points;
    Vec3f nextPoint;

    this->curPointIndex = 0;
    if (GERUDO_PURPLE_GET_PATH(&this->picto.actor) != GERUDO_PURPLE_PATH_NONE) {
        this->path = &play->setupPathList[GERUDO_PURPLE_GET_PATH(&this->picto.actor)];
        if (this->path != NULL) {
            points = Lib_SegmentedToVirtual(this->path->points);
            Math_Vec3s_ToVec3f(&this->picto.actor.world.pos, points);
            this->curPointIndex++;
            points++;
            Math_Vec3s_ToVec3f(&nextPoint, points);

            this->picto.actor.world.rot.y = Math_Vec3f_Yaw(&this->picto.actor.world.pos, &nextPoint);
            this->picto.actor.world.rot.x = Math_Vec3f_Pitch(&this->picto.actor.world.pos, &nextPoint);
            this->picto.actor.speedXZ = 15.0f;
        }
    } else {
        this->path = NULL;
    }
}

typedef enum {
    /* 0 */ GERUDO_PURPLE_PATHSTATUS_0, //! not near waypoint
    /* 1 */ GERUDO_PURPLE_PATHSTATUS_1, //! no path or waypoint changed
    /* 2 */ GERUDO_PURPLE_PATHSTATUS_2  //! reached end of path
} GerudoPurplePathStatus;

GerudoPurplePathStatus func_80B8B90C(EnGe2* this) {
    Path* path = this->path;
    Vec3s* curPoint;
    f32 diffX;
    f32 diffZ;

    if (path == NULL) {
        return GERUDO_PURPLE_PATHSTATUS_1;
    }

    curPoint = (Vec3s*)Lib_SegmentedToVirtual(path->points) + this->curPointIndex;

    diffX = curPoint->x - this->picto.actor.world.pos.x;
    diffZ = curPoint->z - this->picto.actor.world.pos.z;

    this->picto.actor.world.rot.y = Math_Atan2S(diffX, diffZ);
    Math_SmoothStepToS(&this->picto.actor.shape.rot.y, this->picto.actor.world.rot.y, 2, 0x7D0, 0xC8);

    if ((SQ(diffX) + SQ(diffZ)) < 100.0f) {
        if (this->stateFlags & GERUDO_PURPLE_STATE_PATH_REVERSE) {
            this->curPointIndex--;
            if (this->curPointIndex < 0) {
                return GERUDO_PURPLE_PATHSTATUS_2;
            }
        } else {
            this->curPointIndex++;
            if (this->curPointIndex >= path->count) {
                return GERUDO_PURPLE_PATHSTATUS_2;
            }
        }
        return GERUDO_PURPLE_PATHSTATUS_1;
    }
    return GERUDO_PURPLE_PATHSTATUS_0;
}

s32 func_80B8BA40(EnGe2* this) {
    s32 pad;
    Vec3s* points;
    Path* path = this->path;
    Vec3f point;
    s16 yawTarget;
    s16 pitchTarget;

    if (this->path == NULL) {
        return true;
    }

    points = Lib_SegmentedToVirtual(path->points);
    points += this->curPointIndex;
    Math_Vec3s_ToVec3f(&point, points);

    yawTarget = Math_Vec3f_Yaw(&this->picto.actor.world.pos, &point);
    pitchTarget = Math_Vec3f_Pitch(&this->picto.actor.world.pos, &point);
    Math_SmoothStepToS(&this->picto.actor.world.rot.y, yawTarget, 0xA, 0x3E8, 0x64);
    Math_SmoothStepToS(&this->picto.actor.world.rot.x, pitchTarget, 6, 0x7D0, 0xC8);
    this->picto.actor.speedXZ = 15.0f;

    Actor_MoveWithoutGravityReverse(&this->picto.actor);

    if (Math_Vec3f_DistXYZ(&this->picto.actor.world.pos, &point) < 40.0f) {
        return true;
    } else {
        return false;
    }
}

void EnGe2_SpawnEffects(EnGe2* this, PlayState* play) {
    static Vec3f effectVelocity = { 0.0f, -0.05f, 0.0f };
    static Vec3f effectAccel = { 0.0f, -0.025f, 0.0f };
    static Color_RGBA8 effectPrimColor = { 255, 255, 255, 0 };
    static Color_RGBA8 effectEnvColor = { 255, 150, 0, 0 };
    s16 effectAngle = play->state.frames * 0x2800;
    Vec3f effectPos;

    effectPos.x = (Math_CosS(effectAngle) * 5.0f) + this->picto.actor.focus.pos.x;
    effectPos.y = this->picto.actor.focus.pos.y + 10.0f;
    effectPos.z = (Math_SinS(effectAngle) * 5.0f) + this->picto.actor.focus.pos.z;
    EffectSsKirakira_SpawnDispersed(play, &effectPos, &effectVelocity, &effectAccel, &effectPrimColor, &effectEnvColor,
                                    1000, 16);
}

void EnGe2_Scream(EnGe2* this) {
    if ((s32)Rand_ZeroFloat(2.0f) == 0) {
        Actor_PlaySfxAtPos(&this->picto.actor, NA_SE_VO_FPVO00);
    } else {
        Actor_PlaySfxAtPos(&this->picto.actor, NA_SE_VO_FPVO01);
    }
}

// Set up the captured transition
void func_80B8BC78(EnGe2* this, PlayState* play) {
    if (this->timer > 0) {
        this->timer--;
    } else if (play->nextEntrance != play->setupExitList[GERUDO_PURPLE_GET_EXIT(&this->picto.actor)]) {
        play->nextEntrance = play->setupExitList[GERUDO_PURPLE_GET_EXIT(&this->picto.actor)];
        play->transitionTrigger = TRANS_TRIGGER_START;
        play->transitionType = TRANS_TYPE_38;
    }
}

void func_80B8BCEC(EnGe2* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    Math_SmoothStepToS(&this->picto.actor.shape.rot.y, this->picto.actor.yawTowardsPlayer, 2, 0x1000, 0x200);
}

void func_80B8BD38(EnGe2* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    Math_SmoothStepToS(&this->picto.actor.shape.rot.y, this->picto.actor.yawTowardsPlayer, 2, 0x400, 0x100);
    func_80B8BC78(this, play);
}

void func_80B8BD90(EnGe2* this) {
    this->picto.actor.speedXZ = 0.0f;
    this->actionFunc = func_80B8BD38;
    Animation_Change(&this->skelAnime, &gGerudoPurpleLookingAboutAnim, 1.0f, 0.0f,
                     Animation_GetLastFrame(&gGerudoPurpleLookingAboutAnim), 0, -8.0f);
}

void func_80B8BE08(EnGe2* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    Math_SmoothStepToS(&this->picto.actor.shape.rot.y, this->picto.actor.yawTowardsPlayer, 2, 0x400, 0x100);
    this->picto.actor.world.rot.y = this->picto.actor.shape.rot.y;

    if (this->picto.actor.xzDistToPlayer < 50.0f) {
        func_80B8BD90(this);
    } else if (!(this->picto.actor.bgCheckFlags & 1)) {
        this->picto.actor.world.pos = this->picto.actor.prevPos;
        func_80B8BD90(this);
    }

    if (this->timer > 0) {
        this->timer--;
    } else {
        func_80B8BC78(this, play);
    }

    if (Animation_OnFrame(&this->skelAnime, 2.0f) || Animation_OnFrame(&this->skelAnime, 6.0f)) {
        Actor_PlaySfxAtPos(&this->picto.actor, NA_SE_EV_PIRATE_WALK);
    }
}

void func_80B8BF04(EnGe2* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    Math_SmoothStepToS(&this->picto.actor.shape.rot.y, this->picto.actor.yawTowardsPlayer, 2, 0x400, 0x100);
    this->picto.actor.world.rot.y = this->picto.actor.shape.rot.y;

    if (this->picto.actor.shape.rot.y == this->picto.actor.yawTowardsPlayer) {
        Animation_Change(&this->skelAnime, &gGerudoPurpleChargingAnim, 1.0f, 0.0f,
                         Animation_GetLastFrame(&gGerudoPurpleChargingAnim), 0, -8.0f);
        this->timer = 50;
        this->actionFunc = func_80B8BE08;
        this->picto.actor.speedXZ = 4.0f;
    }
}

void func_80B8BFC8(EnGe2* this) {
    Animation_Change(&this->skelAnime, &gGerudoPurpleLookingAboutAnim, 1.0f, 0.0f,
                     Animation_GetLastFrame(&gGerudoPurpleLookingAboutAnim), 0, -8.0f);
    this->timer = 60;
    this->picto.actor.speedXZ = 0.0f;
    this->actionFunc = func_80B8C45C;
}

void func_80B8C048(EnGe2* this, PlayState* play) {
    if (this->picto.actor.colorFilterTimer == 0) {
        func_80B8BFC8(this);
        this->detectedStatus = GERUDO_PURPLE_DETECTION_UNDETECTED;
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
        this->stateFlags &= ~GERUDO_PURPLE_STATE_STUNNED;
    }
}

void func_80B8C0B0(EnGe2* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    EnGe2_SpawnEffects(this, play);

    if (this->timer > 0) {
        this->timer--;
        return;
    } else {
        func_80B8BFC8(this);
        this->detectedStatus = GERUDO_PURPLE_DETECTION_UNDETECTED;
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
        this->stateFlags &= ~GERUDO_PURPLE_STATE_KO;
        this->picto.actor.flags |= ACTOR_FLAG_1;
    }
}

void func_80B8C13C(EnGe2* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    f32 visionRange = gSaveContext.save.isNight ? 200.0f : 280.0f;

    if (player->csMode == 0x1A) {
        this->picto.actor.speedXZ = 0.0f;
        this->actionFunc = func_80B8BF04;
        Animation_Change(&this->skelAnime, &gGerudoPurpleLookingAboutAnim, 1.0f, 0.0f,
                         Animation_GetLastFrame(&gGerudoPurpleLookingAboutAnim), 0, -8.0f);
        this->stateFlags |= GERUDO_PURPLE_STATE_CAPTURING;
    } else if (gSaveContext.save.weekEventReg[80] & 8) {
        this->picto.actor.speedXZ = 0.0f;
        this->actionFunc = func_80B8BCEC;
        Animation_Change(&this->skelAnime, &gGerudoPurpleLookingAboutAnim, 1.0f, 0.0f,
                         Animation_GetLastFrame(&gGerudoPurpleLookingAboutAnim), 0, -8.0f);
    } else if (EnGe2_LookForPlayer(play, &this->picto.actor, &this->picto.actor.focus.pos,
                                   this->picto.actor.shape.rot.y, 0x1800, visionRange, this->verticalDetectRange)) {
        if ((GERUDO_PURPLE_GET_EXIT(&this->picto.actor) != GERUDO_PURPLE_EXIT_NONE) && !Play_InCsMode(play)) {
            this->picto.actor.speedXZ = 0.0f;
            func_800B7298(play, &this->picto.actor, 0x1A);
            func_801000A4(NA_SE_SY_FOUND);
            Message_StartTextbox(play, 0x1194, &this->picto.actor);
            this->actionFunc = func_80B8BF04;
            Animation_Change(&this->skelAnime, &gGerudoPurpleLookingAboutAnim, 1.0f, 0.0f,
                             Animation_GetLastFrame(&gGerudoPurpleLookingAboutAnim), 0, -8.0f);
        }
    } else if (this->collider.base.acFlags & AC_HIT) {
        if ((this->collider.info.acHitInfo != NULL) &&
            (this->collider.info.acHitInfo->toucher.dmgFlags & DMG_DEKU_NUT)) {
            Actor_SetColorFilter(&this->picto.actor, 0, 120, 0, 400);
            this->picto.actor.speedXZ = 0.0f;
            this->actionFunc = func_80B8C048;
            this->stateFlags |= GERUDO_PURPLE_STATE_STUNNED;
        } else {
            Animation_Change(&this->skelAnime, &gGerudoPurpleFallingToGroundAnim, 1.0f, 0.0f,
                             Animation_GetLastFrame(&gGerudoPurpleFallingToGroundAnim), 2, -8.0f);
            this->timer = 200;
            this->picto.actor.speedXZ = 0.0f;
            this->actionFunc = func_80B8C0B0;
            Actor_PlaySfxAtPos(&this->picto.actor, NA_SE_EN_PIRATE_DEAD);
            this->picto.actor.flags &= ~ACTOR_FLAG_1;
            this->stateFlags |= GERUDO_PURPLE_STATE_KO;
        }
    } else if (this->picto.actor.home.rot.x == 0) {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
    }
}

void func_80B8C45C(EnGe2* this, PlayState* play) {
    u8 detectedStatus;

    SkelAnime_Update(&this->skelAnime);
    detectedStatus = EnGe2_DetectPlayer(play, this);
    if (detectedStatus != GERUDO_PURPLE_DETECTION_UNDETECTED) {
        this->timer = 100;
        this->yawTarget = this->picto.actor.yawTowardsPlayer;

        if (this->detectedStatus < detectedStatus) {
            this->detectedStatus = detectedStatus;
        }
    }

    if (this->timer > 0) {
        this->timer--;
    } else {
        this->actionFunc = func_80B8C59C;
        Animation_Change(&this->skelAnime, &gGerudoPurpleWalkingAnim, 1.0f, 0.0f,
                         Animation_GetLastFrame(&gGerudoPurpleWalkingAnim), 0, -8.0f);
        this->headRot.y = 0;
        this->detectedStatus = GERUDO_PURPLE_DETECTION_UNDETECTED;
    }

    switch (this->detectedStatus) {
        case GERUDO_PURPLE_DETECTION_HEARD:
            Math_SmoothStepToS(&this->picto.actor.shape.rot.y, this->yawTarget, 2, 0x3E8, 0x1F4);
            break;
        case GERUDO_PURPLE_DETECTION_PROXIMITY:
            Math_SmoothStepToS(&this->picto.actor.shape.rot.y, this->yawTarget, 2, 0xBB8, 0x3E8);
            break;

        default:
            break;
    }

    this->picto.actor.world.rot.y = this->picto.actor.shape.rot.y;
    func_80B8C13C(this, play);
}

void func_80B8C59C(EnGe2* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    this->picto.actor.speedXZ = 1.5f;

    switch (func_80B8B90C(this)) {
        case GERUDO_PURPLE_PATHSTATUS_2:
            func_80B8B6B4(this, play);
            break;

        case GERUDO_PURPLE_PATHSTATUS_1:
            func_80B8BFC8(this);
            this->detectedStatus = GERUDO_PURPLE_DETECTION_UNDETECTED;
            break;

        default:
            break;
    }

    this->detectedStatus = EnGe2_DetectPlayer(play, this);
    if (this->detectedStatus != GERUDO_PURPLE_DETECTION_UNDETECTED) {
        func_80B8BFC8(this);
        this->yawTarget = this->picto.actor.yawTowardsPlayer;
    }
    func_80B8C13C(this, play);
}

void EnGe2_PerformCutsceneActions(EnGe2* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    if (Cutscene_CheckActorAction(play, 0x1DC)) {
        s16 csAction = play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 0x1DC)]->action;
        if (this->csAction != csAction) {
            this->csAction = csAction;

            switch (csAction) {
                case 1:
                    Animation_Change(&this->skelAnime, &gGerudoPurpleLookingAboutAnim, 1.0f, 0.0f,
                                     Animation_GetLastFrame(&gGerudoPurpleLookingAboutAnim), 0, -8.0f);
                    func_80B8B7A8(this, play);
                    break;

                case 2:
                    Animation_Change(&this->skelAnime, &gGerudoPurpleRunningAwayCutsceneAnim, 1.0f, 0.0f,
                                     Animation_GetLastFrame(&gGerudoPurpleRunningAwayCutsceneAnim), 0, -5.0f);
                    this->screamTimer = (s32)(Rand_ZeroFloat(10.0f) + 20.0f);
                    break;

                case 3:
                    Actor_MarkForDeath(&this->picto.actor);
                    break;

                case 4:
                    Animation_Change(&this->skelAnime, &gGerudoPurpleGreatBayCutsceneAnim, 0.0f, 0.0f, 0.0f, 2, 0.0f);
                    break;

                case 5:
                    Animation_Change(&this->skelAnime, &gGerudoPurpleGreatBayCutsceneAnim, 0.0f, 1.0f, 1.0f, 2, 0.0f);
                    func_80B8B848(this, play);
                    this->stateFlags |= GERUDO_PURPLE_STATE_DISABLE_MOVEMENT;
                    this->screamTimer = (s32)(Rand_ZeroFloat(10.0f) + 20.0f);
                    break;

                default:
                    break;
            }
        }
    }

    switch (this->csAction) {
        case 2:
            func_80B8B90C(this);
            this->picto.actor.speedXZ = 5.0f;

            if (Animation_OnFrame(&this->skelAnime, 2.0f) || Animation_OnFrame(&this->skelAnime, 6.0f)) {
                Actor_PlaySfxAtPos(&this->picto.actor, NA_SE_EV_PIRATE_WALK);
            }

            if (this->screamTimer > 0) {
                this->screamTimer--;
            } else {
                this->screamTimer = (s32)(Rand_ZeroFloat(10.0f) + 20.0f);
                EnGe2_Scream(this);
            }
            break;

        case 5:
            if ((this->curPointIndex < this->path->count) && func_80B8BA40(this)) {
                this->curPointIndex++;
            }

            this->picto.actor.shape.rot.x += 0x3E8;
            this->picto.actor.shape.rot.y += 0x7D0;
            this->picto.actor.shape.rot.z += 0x1F4;
            if (this->screamTimer > 0) {
                this->screamTimer--;
            } else {
                this->screamTimer = (s32)(Rand_ZeroFloat(10.0f) + 20.0f);
                EnGe2_Scream(this);
            }
            break;

        default:
            break;
    }
}

void func_80B8C9B8(EnGe2* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    if (EnGe2_LookForPlayer(play, &this->picto.actor, &this->picto.actor.focus.pos, this->picto.actor.shape.rot.y,
                            0x4000, 720.0f, this->verticalDetectRange)) {
        if ((GERUDO_PURPLE_GET_EXIT(&this->picto.actor) != GERUDO_PURPLE_EXIT_NONE) && !Play_InCsMode(play)) {
            func_800B7298(play, &this->picto.actor, 0x1A);
            func_801000A4(NA_SE_SY_FOUND);
            Message_StartTextbox(play, 0x1194, &this->picto.actor);
            this->timer = 50;
            func_80B8BD90(this);
        }
    }

    if (this->picto.actor.playerHeightRel < -150.0f) {
        this->picto.actor.draw = NULL;
    } else {
        this->picto.actor.draw = EnGe2_Draw;
    }
}

void EnGe2_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    EnGe2* this = (EnGe2*)thisx;

    if (!(this->stateFlags & GERUDO_PURPLE_STATE_DISABLE_MOVEMENT)) {
        Actor_MoveWithGravity(&this->picto.actor);
    }
    Actor_UpdateBgCheckInfo(play, &this->picto.actor, 40.0f, 25.0f, 40.0f, 5U);
    Collider_UpdateCylinder(&this->picto.actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    if (Cutscene_CheckActorAction(play, 0x1DC)) {
        this->actionFunc = EnGe2_PerformCutsceneActions;
        this->stateFlags &= ~GERUDO_PURPLE_STATE_KO;
        this->stateFlags &= ~GERUDO_PURPLE_STATE_PATH_REVERSE;
        this->picto.actor.flags |= ACTOR_FLAG_20;
        this->picto.actor.speedXZ = 0.0f;
    }

    this->actionFunc(this, play);

    // Blinking
    if (this->stateFlags & GERUDO_PURPLE_STATE_KO) {
        this->eyeIndex = 2;
    } else if (!(this->stateFlags & GERUDO_PURPLE_STATE_STUNNED)) {
        if (DECR(this->blinkTimer) == 0) {
            this->blinkTimer = Rand_S16Offset(60, 60);
        }
        this->eyeIndex = this->blinkTimer;
        if (this->eyeIndex >= 3) {
            this->eyeIndex = 0;
        }
    }
}

s32 EnGe2_ValidatePictograph(PlayState* play, Actor* thisx) {
    s32 ret = Snap_ValidatePictograph(play, thisx, PICTOGRAPH_PIRATE_GOOD, &thisx->focus.pos, &thisx->shape.rot, 10.0f,
                                      400.0f, -1);

    ret |= Snap_ValidatePictograph(play, thisx, PICTOGRAPH_PIRATE_TOO_FAR, &thisx->focus.pos, &thisx->shape.rot, 10.0f,
                                   1200.0f, -1);
    return ret;
}

s32 EnGe2_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnGe2* this = (EnGe2*)thisx;

    if (limbIndex == 3) {
        rot->x += this->headRot.y;
        rot->z += this->headRot.x;
    }
    return false;
}

void EnGe2_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Vec3f sFocusOffset = { 600.0f, 700.0f, 0.0f };

    if (limbIndex == 6) {
        Matrix_MultVec3f(&sFocusOffset, &thisx->focus.pos);
    }
}

void EnGe2_Draw(Actor* thisx, PlayState* play) {
    static TexturePtr sEyeTextures[] = {
        gGerudoPurpleEyeOpenTex,
        gGerudoPurpleEyeHalfTex,
        gGerudoPurpleEyeClosedTex,
    };
    s32 pad;
    EnGe2* this = (EnGe2*)thisx;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C5B0(play->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(sEyeTextures[this->eyeIndex]));
    func_800B8050(&this->picto.actor, play, 0);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnGe2_OverrideLimbDraw, EnGe2_PostLimbDraw, &this->picto.actor);

    CLOSE_DISPS(play->state.gfxCtx);
}
