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

void func_80B8BCEC(EnGe2* this, PlayState* play);
void func_80B8BD38(EnGe2* this, PlayState* play);
void func_80B8BE08(EnGe2* this, PlayState* play);
void func_80B8BF04(EnGe2* this, PlayState* play);
void func_80B8C048(EnGe2* this, PlayState* play);
void func_80B8C0B0(EnGe2* this, PlayState* play);
void func_80B8C45C(EnGe2* this, PlayState* play);
void func_80B8C59C(EnGe2* this, PlayState* play);
void func_80B8C644(EnGe2* this, PlayState* play);
void func_80B8C9B8(EnGe2* this, PlayState* play);

s32 func_80B8B6B4(EnGe2* this, PlayState* play);

s32 func_80B8CC0C(PlayState* play, Actor* thisx);

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

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B8CE40 = {
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

// extern ColliderCylinderInit D_80B8CE40;
extern FlexSkeletonHeader D_06008DD8;
extern AnimationHeader D_06001664;
extern AnimationHeader D_060091D0;
extern AnimationHeader D_06009D1C;
extern AnimationHeader D_0600A344;

void EnGe2_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnGe2* this = (EnGe2*)thisx;

    ActorShape_Init(&this->picto.actor.shape, 0.0f, ActorShadow_DrawCircle, 36.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &D_06008DD8, NULL, this->jointTable, this->morphTable, 22);
    Animation_PlayLoop(&this->skelAnime, &D_0600A344);

    Collider_InitAndSetCylinder(play, &this->unk148, &this->picto.actor, &D_80B8CE40);
    this->picto.actor.colChkInfo.mass = MASS_IMMOVABLE;
    Actor_SetScale(&this->picto.actor, 0.01f);

    this->picto.actor.uncullZoneForward = 1200.0f;
    if (this->picto.actor.world.rot.z == 0) {
        this->unk2FC = 40.0f;
    } else {
        this->unk2FC = fabsf(this->picto.actor.world.rot.z * 20.0f);
    }

    this->picto.actor.world.rot.x = this->picto.actor.shape.rot.x = 0;
    this->picto.actor.world.rot.z = this->picto.actor.shape.rot.z = 0;

    this->picto.actor.targetMode = 6;
    this->unk2F8 = 0;
    this->unk301 = 0;
    this->unk302 = -1;

    this->picto.actor.terminalVelocity = -9.0f;
    this->picto.actor.gravity = -1.0f;
    this->picto.actor.speedXZ = 1.5f;

    this->actionFunc = func_80B8C59C;
    this->picto.validationFunc = func_80B8CC0C;

    func_80B8B6B4(this, play);

    this->picto.actor.flags |= 0x10;
    if (play->actorCtx.unk5 & 2) {
        this->picto.actor.flags |= 0x30;
    }

    switch ((this->picto.actor.params & 0xE0) >> 5) {
        case 1:
            Animation_Change(&this->skelAnime, &D_06009D1C, 1.0f, 0.0f, Animation_GetLastFrame(&D_06009D1C), 0, 0.0f);
            this->actionFunc = func_80B8C9B8;
            this->picto.actor.speedXZ = 0.0f;
            this->picto.actor.uncullZoneForward = 4000.0f;
            break;

        case 2:
            if (gSaveContext.save.weekEventReg[83] & 2) {
                Actor_MarkForDeath(&this->picto.actor);
            }
            break;

        default:
            break;
    }
}

void EnGe2_Destroy(Actor* thisx, PlayState* play) {
}

s32 func_80B8B514(PlayState* play, EnGe2* this) {
    if (this->picto.actor.xzDistToPlayer > 250.0f) {
        return 0;
    } else if ((Player_GetMask(play) != PLAYER_MASK_STONE) && (this->picto.actor.xzDistToPlayer < 50.0f)) {
        return 2;
    } else if (func_800B715C(play)) {
        return 1;
    } else {
        return 0;
    }
}

// Spotted Player
s32 func_80B8B5AC(PlayState* play, Actor* thisx, Vec3f* pos, s16 yaw, s16 yawRange, f32 xzRange, f32 yRange) {
    s16 yawToPlayer;
    Vec3f posResult;
    CollisionPoly* outPoly;
    Player* player = GET_PLAYER(play);

    if (Player_GetMask(play) == PLAYER_MASK_STONE) {
        return false;
    }
    if (thisx->xzDistToPlayer > xzRange) {
        return false;
    }
    if (fabsf(thisx->playerHeightRel) > yRange) {
        return false;
    }

    yawToPlayer = thisx->yawTowardsPlayer - yaw;
    if ((yawRange > 0) && (yawRange < ABS_ALT(yawToPlayer))) {
        return false;
    }

    if (BgCheck_AnyLineTest1(&play->colCtx, pos, &player->bodyPartsPos[7], &posResult, &outPoly, false)) {
        return false;
    } else {
        return true;
    }
}

#define GERUDO_PURPLE_GET_PATH(thisx) ((((thisx)->params) & 0xFC00) >> 10)

s32 func_80B8B6B4(EnGe2* this, PlayState* play) {
    if (GERUDO_PURPLE_GET_PATH(&this->picto.actor) != 0x3F) {
        this->unk2F0 = &play->setupPathList[GERUDO_PURPLE_GET_PATH(&this->picto.actor)];
        if (this->unk2F0 != NULL) {
            Path* path = this->unk2F0;
            Vec3s* points = Lib_SegmentedToVirtual(path->points);
            f32 diffX = points[0].x - this->picto.actor.world.pos.x;
            f32 diffZ = points[0].z - this->picto.actor.world.pos.z;

            if ((SQ(diffX) + SQ(diffZ)) < 100.0f) {
                this->unk2F4 = 0;
                this->unk2F8 &= ~1;
            } else {
                this->unk2F4 = path->count - 1;
                this->unk2F8 |= 1;
                return 1;
            }
        }
    } else {
        this->unk2F0 = NULL;
        this->unk2F4 = 0;
    }
    return 0;
}

void func_80B8B7A8(EnGe2* this, PlayState* play) {
    Path* firstPath;
    Path* nextPath;
    Vec3s* points;
    u8 unk1;

    this->unk2F4 = 0;

    if (GERUDO_PURPLE_GET_PATH(&this->picto.actor) != 0x3F) {
        firstPath = &play->setupPathList[GERUDO_PURPLE_GET_PATH(&this->picto.actor)];
        unk1 = firstPath->unk1;
        nextPath = &play->setupPathList[unk1];
        this->unk2F0 = nextPath;
        points = Lib_SegmentedToVirtual(nextPath->points);
        this->picto.actor.world.pos.x = points[0].x;
        this->picto.actor.world.pos.z = points[0].z;
    } else {
        this->unk2F0 = NULL;
    }
}

void func_80B8B848(EnGe2* this, PlayState* play) {
    s32 pad;
    Vec3s* points;
    Vec3f nextPoint;

    this->unk2F4 = 0;
    if (GERUDO_PURPLE_GET_PATH(&this->picto.actor) != 0x3F) {
        this->unk2F0 = &play->setupPathList[GERUDO_PURPLE_GET_PATH(&this->picto.actor)];
        if (this->unk2F0 != NULL) {
            points = Lib_SegmentedToVirtual(this->unk2F0->points);
            Math_Vec3s_ToVec3f(&this->picto.actor.world.pos, points);
            this->unk2F4++;
            points++;
            Math_Vec3s_ToVec3f(&nextPoint, points);

            this->picto.actor.world.rot.y = Math_Vec3f_Yaw(&this->picto.actor.world.pos, &nextPoint);
            this->picto.actor.world.rot.x = Math_Vec3f_Pitch(&this->picto.actor.world.pos, &nextPoint);
            this->picto.actor.speedXZ = 15.0f;
        }
    } else {
        this->unk2F0 = NULL;
    }
}

s32 func_80B8B90C(EnGe2* this) {
    Path* path = this->unk2F0;
    Vec3s* curPoint;
    f32 diffX;
    f32 diffZ;

    if (path == NULL) {
        return 1;
    }

    curPoint = (Vec3s*)Lib_SegmentedToVirtual(path->points) + this->unk2F4;

    diffX = curPoint->x - this->picto.actor.world.pos.x;
    diffZ = curPoint->z - this->picto.actor.world.pos.z;

    this->picto.actor.world.rot.y = Math_Atan2S(diffX, diffZ);
    Math_SmoothStepToS(&this->picto.actor.shape.rot.y, this->picto.actor.world.rot.y, 2, 0x7D0, 0xC8);

    if ((SQ(diffX) + SQ(diffZ)) < 100.0f) {
        if (this->unk2F8 & 1) {
            this->unk2F4--;
            if (this->unk2F4 < 0) {
                return 2;
            }
        } else {
            this->unk2F4++;
            if (this->unk2F4 >= path->count) {
                return 2;
            }
        }
        return 1;
    }
    return 0;
}

s32 func_80B8BA40(EnGe2* this) {
    s32 pad;
    Vec3s* points;
    Path* temp_v1;
    Vec3f point;
    s16 yawTarget;
    s16 pitchTarget;

    temp_v1 = this->unk2F0;
    if (this->unk2F0 == NULL) {
        return 1;
    }
    points = Lib_SegmentedToVirtual(temp_v1->points);
    points += this->unk2F4;
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

Vec3f D_80B8CE6C = { 0.0f, -0.05f, 0.0f };
Vec3f D_80B8CE78 = { 0.0f, -0.025f, 0.0f };
Color_RGBA8 D_80B8CE84 = { 255, 255, 255, 0 };
Color_RGBA8 D_80B8CE88 = { 255, 150, 0, 0 };

void func_80B8BB3C(EnGe2* this, PlayState* play) {
    s16 angle;
    Vec3f pos;

    angle = play->state.frames * 0x2800;
    pos.x = (Math_CosS(angle) * 5.0f) + this->picto.actor.focus.pos.x;
    pos.y = this->picto.actor.focus.pos.y + 10.0f;
    pos.z = (Math_SinS(angle) * 5.0f) + this->picto.actor.focus.pos.z;
    EffectSsKirakira_SpawnDispersed(play, &pos, &D_80B8CE6C, &D_80B8CE78, &D_80B8CE84, &D_80B8CE88, 0x3E8, 0x10);
}

void func_80B8BC1C(Actor* thisx) {
    if ((s32)Rand_ZeroFloat(2.0f) == 0) {
        Actor_PlaySfxAtPos(thisx, NA_SE_VO_FPVO00);
    } else {
        Actor_PlaySfxAtPos(thisx, NA_SE_VO_FPVO01);
    }
}

// Set up the captured transition
void func_80B8BC78(EnGe2* this, PlayState* play) {
    if (this->unk300 > 0) {
        this->unk300--;
    } else if (play->nextEntrance != play->setupExitList[this->picto.actor.params & 0x1F]) {
        play->nextEntrance = play->setupExitList[this->picto.actor.params & 0x1F];
        play->transitionTrigger = 0x14;
        play->transitionType = 0x26;
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
    Animation_Change(&this->skelAnime, &D_06009D1C, 1.0f, 0.0f, Animation_GetLastFrame(&D_06009D1C), 0, -8.0f);
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

    if (this->unk300 > 0) {
        this->unk300--;
    } else {
        func_80B8BC78(this, play);
    }

    if (Animation_OnFrame(&this->skelAnime, 2.0f) || Animation_OnFrame(&this->skelAnime, 6.0f)) {
        Actor_PlaySfxAtPos(&this->picto.actor, 0x2971);
    }
}

void func_80B8BF04(EnGe2* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    Math_SmoothStepToS(&this->picto.actor.shape.rot.y, this->picto.actor.yawTowardsPlayer, 2, 0x400, 0x100);
    this->picto.actor.world.rot.y = this->picto.actor.shape.rot.y;

    if (this->picto.actor.shape.rot.y == this->picto.actor.yawTowardsPlayer) {
        Animation_Change(&this->skelAnime, &D_060091D0, 1.0f, 0.0f, Animation_GetLastFrame(&D_060091D0), 0, -8.0f);
        this->unk300 = 50;
        this->actionFunc = func_80B8BE08;
        this->picto.actor.speedXZ = 4.0f;
    }
}

void func_80B8BFC8(EnGe2* this) {
    Animation_Change(&this->skelAnime, &D_06009D1C, 1.0f, 0.0f, Animation_GetLastFrame(&D_06009D1C), 0, -8.0f);
    this->unk300 = 60;
    this->picto.actor.speedXZ = 0.0f;
    this->actionFunc = func_80B8C45C;
}

void func_80B8C048(EnGe2* this, PlayState* play) {
    if (this->picto.actor.colorFilterTimer == 0) {
        func_80B8BFC8(this);
        this->unk301 = 0;
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->unk148.base);
        this->unk2F8 &= ~4;
    }
}

void func_80B8C0B0(EnGe2* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    func_80B8BB3C(this, play);

    if (this->unk300 > 0) {
        this->unk300--;
        return;
    } else {
        func_80B8BFC8(this);
        this->unk301 = 0;
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->unk148.base);
        this->unk2F8 &= ~2;
        this->picto.actor.flags |= 1;
    }
}

void func_80B8C13C(EnGe2* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    f32 visionRange = gSaveContext.save.isNight ? 200.0f : 280.0f;

    if (player->csMode == 0x1A) {
        this->picto.actor.speedXZ = 0.0f;
        this->actionFunc = func_80B8BF04;
        Animation_Change(&this->skelAnime, &D_06009D1C, 1.0f, 0.0f, Animation_GetLastFrame(&D_06009D1C), 0, -8.0f);
        this->unk2F8 |= 0x20;
    } else if (gSaveContext.save.weekEventReg[80] & 8) {
        this->picto.actor.speedXZ = 0.0f;
        this->actionFunc = func_80B8BCEC;
        Animation_Change(&this->skelAnime, &D_06009D1C, 1.0f, 0.0f, Animation_GetLastFrame(&D_06009D1C), 0, -8.0f);
    } else if (func_80B8B5AC(play, &this->picto.actor, &this->picto.actor.focus.pos, this->picto.actor.shape.rot.y,
                             0x1800, visionRange, this->unk2FC)) {
        if (((this->picto.actor.params & 0x1F) != 0x1F) && !Play_InCsMode(play)) {
            this->picto.actor.speedXZ = 0.0f;
            func_800B7298(play, &this->picto.actor, 0x1A);
            func_801000A4(0x482C);
            Message_StartTextbox(play, 0x1194, &this->picto.actor);
            this->actionFunc = func_80B8BF04;
            Animation_Change(&this->skelAnime, &D_06009D1C, 1.0f, 0.0f, Animation_GetLastFrame(&D_06009D1C), 0, -8.0f);
        }
    } else if (this->unk148.base.acFlags & 2) {
        // hitInfo = this->unk148.info.acHitInfo;
        if ((this->unk148.info.acHitInfo != NULL) && (this->unk148.info.acHitInfo->toucher.dmgFlags & 1)) {
            Actor_SetColorFilter(&this->picto.actor, 0, 120, 0, 400);
            this->picto.actor.speedXZ = 0.0f;
            this->actionFunc = func_80B8C048;
            this->unk2F8 |= 4;
        } else {
            Animation_Change(&this->skelAnime, &D_06001664, 1.0f, 0.0f, Animation_GetLastFrame(&D_06001664), 2, -8.0f);
            this->unk300 = 200;
            this->picto.actor.speedXZ = 0.0f;
            this->actionFunc = func_80B8C0B0;
            Actor_PlaySfxAtPos(&this->picto.actor, 0x399A);
            this->picto.actor.flags &= ~1;
            this->unk2F8 |= 2;
        }
    } else if (this->picto.actor.home.rot.x == 0) {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->unk148.base);
    }
}

void func_80B8C45C(EnGe2* this, PlayState* play) {
    u8 temp_v1;

    SkelAnime_Update(&this->skelAnime);
    temp_v1 = func_80B8B514(play, this);
    if (temp_v1 != 0) {
        this->unk300 = 100;
        this->unk2FA = this->picto.actor.yawTowardsPlayer;

        if (this->unk301 < temp_v1) {
            this->unk301 = temp_v1;
        }
    }

    if (this->unk300 > 0) {
        this->unk300--;
    } else {
        this->actionFunc = func_80B8C59C;
        Animation_Change(&this->skelAnime, &D_0600A344, 1.0f, 0.0f, Animation_GetLastFrame(&D_0600A344), 0, -8.0f);
        this->unk2E4.y = 0;
        this->unk301 = 0;
    }

    switch (this->unk301) {
        case 1:
            Math_SmoothStepToS(&this->picto.actor.shape.rot.y, this->unk2FA, 2, 0x3E8, 0x1F4);
            break;
        case 2:
            Math_SmoothStepToS(&this->picto.actor.shape.rot.y, this->unk2FA, 2, 0xBB8, 0x3E8);
            break;
    }

    this->picto.actor.world.rot.y = this->picto.actor.shape.rot.y;
    func_80B8C13C(&this->picto.actor, play);
}

void func_80B8C59C(EnGe2* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    this->picto.actor.speedXZ = 1.5f;

    switch (func_80B8B90C(this)) {
        case 2:
            func_80B8B6B4(this, play);
            break;

        case 1:
            func_80B8BFC8(this);
            this->unk301 = 0;
            break;

        default:
            break;
    }

    this->unk301 = func_80B8B514(play, this);
    if (this->unk301 != 0) {
        func_80B8BFC8(this);
        this->unk2FA = this->picto.actor.yawTowardsPlayer;
    }
    func_80B8C13C(this, play);
}

extern AnimationHeader D_0600030C;
extern AnimationHeader D_06000460;

void func_80B8C644(EnGe2* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    if (Cutscene_CheckActorAction(play, 0x1DC)) {
        s16 temp_v1 = play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 0x1DC)]->action;
        if (this->unk302 != temp_v1) {
            this->unk302 = temp_v1;

            switch (temp_v1) {
                case 1:
                    Animation_Change(&this->skelAnime, &D_06009D1C, 1.0f, 0.0f, Animation_GetLastFrame(&D_06009D1C), 0,
                                     -8.0f);
                    func_80B8B7A8(this, play);
                    break;
                case 2:
                    Animation_Change(&this->skelAnime, &D_0600030C, 1.0f, 0.0f, Animation_GetLastFrame(&D_0600030C), 0,
                                     -5.0f);
                    this->unk306 = (s32)(Rand_ZeroFloat(10.0f) + 20.0f);
                    break;
                case 3:
                    Actor_MarkForDeath(&this->picto.actor);
                    break;
                case 4:
                    Animation_Change(&this->skelAnime, &D_06000460, 0.0f, 0.0f, 0.0f, 2, 0.0f);
                    break;
                case 5:
                    Animation_Change(&this->skelAnime, &D_06000460, 0.0f, 1.0f, 1.0f, 2, 0.0f);
                    func_80B8B848(this, play);
                    this->unk2F8 |= 8;
                    this->unk306 = (s32)(Rand_ZeroFloat(10.0f) + 20.0f);
                    break;
            }
        }
    }

    switch (this->unk302) {
        case 2:
            func_80B8B90C(this);
            this->picto.actor.speedXZ = 5.0f;

            if (Animation_OnFrame(&this->skelAnime, 2.0f) || Animation_OnFrame(&this->skelAnime, 6.0f)) {
                Actor_PlaySfxAtPos(&this->picto.actor, 0x2971);
            }

            if (this->unk306 > 0) {
                this->unk306--;
            } else {
                this->unk306 = (s32)(Rand_ZeroFloat(10.0f) + 20.0f);
                func_80B8BC1C(&this->picto.actor);
            }
            break;

        case 5:
            if ((this->unk2F4 < this->unk2F0->count) && func_80B8BA40(&this->picto.actor)) {
                this->unk2F4++;
            }

            this->picto.actor.shape.rot.x += 0x3E8;
            this->picto.actor.shape.rot.y += 0x7D0;
            this->picto.actor.shape.rot.z += 0x1F4;
            if (this->unk306 > 0) {
                this->unk306--;
            } else {
                this->unk306 = (s32)(Rand_ZeroFloat(10.0f) + 20.0f);
                func_80B8BC1C(&this->picto.actor);
            }
            break;

        default:
            break;
    }
}

void func_80B8C9B8(EnGe2* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    if ((func_80B8B5AC(play, &this->picto.actor, &this->picto.actor.focus.pos, this->picto.actor.shape.rot.y, 0x4000,
                       720.0f, this->unk2FC)) &&
        ((this->picto.actor.params & 0x1F) != 0x1F) && !Play_InCsMode(play)) {
        func_800B7298(play, &this->picto.actor, 0x1AU);
        func_801000A4(NA_SE_SY_FOUND);
        Message_StartTextbox(play, 0x1194, &this->picto.actor);
        this->unk300 = 50;
        func_80B8BD90(this);
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

    if (!(this->unk2F8 & 8)) {
        Actor_MoveWithGravity(&this->picto.actor);
    }
    Actor_UpdateBgCheckInfo(play, &this->picto.actor, 40.0f, 25.0f, 40.0f, 5U);
    Collider_UpdateCylinder(&this->picto.actor, &this->unk148);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->unk148.base);
    if (Cutscene_CheckActorAction(play, 0x1DC)) {
        this->actionFunc = func_80B8C644;
        this->unk2F8 &= ~2;
        this->unk2F8 &= ~1;
        this->picto.actor.flags |= 0x20;
        this->picto.actor.speedXZ = 0.0f;
    }

    this->actionFunc(this, play);

    if (this->unk2F8 & 2) {
        this->unk2E0 = 2;
    } else if (!(this->unk2F8 & 4)) {
        if (DECR(this->unk2E2) == 0) {
            this->unk2E2 = Rand_S16Offset(60, 60);
        }
        this->unk2E0 = this->unk2E2;
        if (this->unk2E0 >= 3) {
            this->unk2E0 = 0;
        }
    }
}

// EnGe2_ValidatePictograph
s32 func_80B8CC0C(PlayState* play, Actor* thisx) {
    s32 ret = Snap_ValidatePictograph(play, thisx, 9, &thisx->focus.pos, &thisx->shape.rot, 10.0f, 400.0f, -1);

    ret |= Snap_ValidatePictograph(play, thisx, 11, &thisx->focus.pos, &thisx->shape.rot, 10.0f, 1200.0f, -1);
    return ret;
}

// EnGe2_OverrideLimbDraw
s32 func_80B8CCB4(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnGe2* this = (EnGe2*)thisx;

    if (limbIndex == 3) {
        rot->x += this->unk2E4.y;
        rot->z += this->unk2E4.x;
    }
    return false;
}

Vec3f D_80B8CE8C = { 600.0f, 700.0f, 0.0f };

// EnGe2_PostLimbDraw
void func_80B8CCFC(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    if (limbIndex == 6) {
        Matrix_MultVec3f(&D_80B8CE8C, &thisx->focus.pos);
    }
}

TexturePtr D_80B8CE98[] = {
    0x060053E8,
    0x060059E8,
    0x06006068,
};

void EnGe2_Draw(Actor* thisx, PlayState* play) {
    s32 pad;
    EnGe2* this = (EnGe2*)thisx;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C5B0(play->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(D_80B8CE98[this->unk2E0]));
    func_800B8050(&this->picto.actor, play, 0);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          func_80B8CCB4, func_80B8CCFC, &this->picto.actor);

    CLOSE_DISPS(play->state.gfxCtx);
}
