/*
 * File: z_en_horse.c
 * Overlay: ovl_En_Horse
 * Description: Epona
 */

#include "z_en_horse.h"
#include "objects/object_horse_link_child/object_horse_link_child.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnHorse*)thisx)

void EnHorse_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHorse_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHorse_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHorse_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_8087D540(Actor* thisx, GlobalContext* globalCtx);
void EnHorse_StartMountedIdleResetAnim(EnHorse* this);
void EnHorse_StartMountedIdle(EnHorse* this);
void EnHorse_MountedIdle(EnHorse* this, GlobalContext* globalCtx);
void EnHorse_MountedIdleAnim(EnHorse* this);
void EnHorse_MountedIdleWhinney(EnHorse* this);
void EnHorse_StartTurning(EnHorse* this);
void EnHorse_StartWalkingFromIdle(EnHorse* this);
void EnHorse_StartWalkingInterruptable(EnHorse* this);
void EnHorse_StartWalking(EnHorse* this);
void EnHorse_StartTrotting(EnHorse* this);
void EnHorse_StartGallopingInterruptable(EnHorse* this);
void EnHorse_StartGalloping(EnHorse* this);
void EnHorse_StartBraking(EnHorse* this, GlobalContext* globalCtx);
void EnHorse_StartReversingInterruptable(EnHorse* this);
void EnHorse_StartReversing(EnHorse* this);
void EnHorse_StartLowJump(EnHorse* this, GlobalContext* globalCtx);
void EnHorse_StartHighJump(EnHorse* this, GlobalContext* globalCtx);
void EnHorse_InitInactive(EnHorse* this);
void EnHorse_ChangeIdleAnimation(EnHorse* this, s32 anim, f32 morphFrames);
void EnHorse_ResetIdleAnimation(EnHorse* this);
void EnHorse_StartIdleRidable(EnHorse* this);
void EnHorse_StartMovingAnimation(EnHorse* this, s32 anim, f32 morphFrames, f32 startFrames);
void EnHorse_SetFollowAnimation(EnHorse* this, GlobalContext* globalCtx);
void EnHorse_InitIngoHorse(EnHorse* this);
void EnHorse_UpdateIngoHorseAnim(EnHorse* this);
void func_80881290(EnHorse* this, GlobalContext* globalCtx);
void func_8088159C(EnHorse* this, GlobalContext* globalCtx);
void func_80881634(EnHorse* this);
void func_8088168C(EnHorse* this);
void EnHorse_CsMoveInit(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void EnHorse_CsMoveToPoint(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void EnHorse_CsPlayHighJumpAnim(EnHorse* this, GlobalContext* globalCtx);
void EnHorse_CsJumpInit(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void EnHorse_CsJump(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void EnHorse_CsRearingInit(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void EnHorse_CsRearing(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void EnHorse_WarpMoveInit(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void EnHorse_CsWarpMoveToPoint(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void EnHorse_CsWarpRearingInit(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void EnHorse_CsWarpRearing(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void EnHorse_InitCutscene(EnHorse* this, GlobalContext* globalCtx);
void EnHorse_InitHorsebackArchery(EnHorse* this);
void EnHorse_UpdateHbaAnim(EnHorse* this);
void func_80883BEC(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void func_80883CB0(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void func_80883D64(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void func_80883DE0(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void func_80883E10(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void func_80883EA0(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void func_80883F18(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void func_80883F98(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void func_80884010(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void func_808840C4(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void func_80884194(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void func_8088424C(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void func_80884314(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void func_808843B4(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void func_80884444(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void func_808844E0(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void func_80884564(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void func_80884604(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void func_808846B4(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void func_808846DC(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void func_808846F0(EnHorse* this, GlobalContext* globalCtx);
void func_80884994(EnHorse* this);
void func_80884D04(EnHorse* this, GlobalContext* globalCtx);
void EnHorse_StickDirection(Vec2f* curStick, f32* stickMag, s16* angle);
s32 EnHorse_GetMountSide(EnHorse* this, GlobalContext* globalCtx);

typedef struct {
    s32 csAction;
    s32 csFuncIdx;
} CsActionEntry;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 speed;
    s16 angle;
} RaceWaypoint;

typedef struct {
    s32 numWaypoints;
    RaceWaypoint* waypoints;
} RaceInfo;

static AnimationHeader* sEponaAnimHeaders[] = {
    &object_horse_link_child_Anim_006D44, &object_horse_link_child_Anim_007468, &object_horse_link_child_Anim_005F64,
    &object_horse_link_child_Anim_004DE8, &object_horse_link_child_Anim_007D50, &object_horse_link_child_Anim_0043AC,
    &object_horse_link_child_Anim_002F98, &object_horse_link_child_Anim_0035B0, &object_horse_link_child_Anim_003D38,
};

static AnimationHeader* sHniAnimHeaders[] = {
    &object_ha_Anim_00C850, &object_ha_Anim_00CE70, &object_ha_Anim_00B9C8,
    &object_ha_Anim_00B00C, &object_ha_Anim_00D648, &object_ha_Anim_00A650,
    &object_ha_Anim_009208, &object_ha_Anim_009858, &object_ha_Anim_00A05C,
};

static AnimationHeader** sAnimationHeaders[] = {
    NULL, NULL, sEponaAnimHeaders, sHniAnimHeaders, sHniAnimHeaders,
};

static f32 sPlaybackSpeeds[] = { 2.0f / 3.0f, 2.0f / 3.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f / 3.0f, 2.0f / 3.0f };

static SkeletonHeader* sSkeletonHeaders[] = {
    NULL, NULL, &object_horse_link_child_Skel_00A480, NULL, NULL,
};

const ActorInit En_Horse_InitVars = {
    ACTOR_EN_HORSE,
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnHorse),
    (ActorFunc)EnHorse_Init,
    (ActorFunc)EnHorse_Destroy,
    (ActorFunc)EnHorse_Update,
    (ActorFunc)EnHorse_Draw,
};

static ColliderCylinderInit sCylinderInit1 = {
    {
        COLTYPE_NONE,
        AT_NONE | AT_TYPE_PLAYER,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1 | OC2_UNK1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000004, 0x00, 0x02 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NONE,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 20, 70, 0, { 0, 0, 0 } },
};

static ColliderCylinderInit sCylinderInit2 = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1 | OC2_UNK1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 20, 70, 0, { 0, 0, 0 } },
};

static ColliderJntSphElementInit sJntSphElementsInit[] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0x00013820, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_NO_AT_INFO | BUMP_NO_DAMAGE | BUMP_NO_SWORD_SFX | BUMP_NO_HITMARK,
            OCELEM_ON,
        },
        { 13, { { 0, 0, 0 }, 20 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1 | OC2_UNK1,
        COLSHAPE_JNTSPH,
    },
    1,
    sJntSphElementsInit,
};

static CollisionCheckInfoInit sColChkInfoInit = { 10, 35, 100, MASS_HEAVY };

static s32 sAnimSoundFrames[] = {
    0,
    16,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneScale, 1200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_STOP),
};

static u8 sResetNoInput[] = {
    false, false, false, false, false, false, true,  true,  true,  true,  true,  true,
    true,  true,  true,  false, false, false, false, false, false, false, false, false,
};

static s32 sIdleAnimIds[] = {
    1, 3, 0, 3, 1, 0,
};

static s16 sIngoAnimations[] = { 7, 6, 2, 2, 1, 1, 0, 0, 0, 0 };

static EnHorseCsFunc sCutsceneInitFuncs[] = {
    NULL,
    EnHorse_CsMoveInit,
    EnHorse_CsJumpInit,
    EnHorse_CsRearingInit,
    EnHorse_WarpMoveInit,
    EnHorse_CsWarpRearingInit,
};

static EnHorseCsFunc sCutsceneActionFuncs[] = {
    NULL, EnHorse_CsMoveToPoint, EnHorse_CsJump, EnHorse_CsRearing, EnHorse_CsWarpMoveToPoint, EnHorse_CsWarpRearing,
};

static CsActionEntry sCsActionTable[] = {
    { 36, 1 }, { 37, 2 }, { 38, 3 }, { 64, 4 }, { 65, 5 },
};

static RaceWaypoint sHbaWaypoints[] = {
    { 3600, 1413, -5055, 11, 0x8001 }, { 3360, 1413, -5220, 5, 0xC000 }, { 3100, 1413, -4900, 5, 0x0000 },
    { 3600, 1413, -4100, 11, 0x0000 }, { 3600, 1413, 360, 11, 0x0000 },
};

static RaceInfo sHbaInfo = { 5, sHbaWaypoints };

static EnHorseCsFunc D_808890F0[] = {
    NULL,          func_80883BEC, func_80883D64, func_80883E10, func_80883F18, func_80884010,
    func_80884194, func_80884314, func_80884444, func_80884564, func_808846B4,
};

static EnHorseCsFunc D_8088911C[] = {
    NULL,          func_80883CB0, func_80883DE0, func_80883EA0, func_80883F98, func_808840C4,
    func_8088424C, func_808843B4, func_808844E0, func_80884604, func_808846DC,
};

void EnHorse_RaceWaypointPos(RaceWaypoint* waypoints, s32 idx, Vec3f* pos) {
    pos->x = waypoints[idx].x;
    pos->y = waypoints[idx].y;
    pos->z = waypoints[idx].z;
}

void EnHorse_RotateToPoint(EnHorse* this, GlobalContext* globalCtx, Vec3f* pos, s16 turnAmount) {
    func_800F415C(&this->actor, pos, turnAmount);
}

void func_8087B7C0(EnHorse* this, GlobalContext* globalCtx, Path* path) {
    s32 spA4;
    Vec3s* spA0;
    f32 phi_f12;
    f32 phi_f14;
    Vec3f sp8C;
    Vec3f sp80;
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    s32 i;
    s32 sp68;
    f32 sp64;
    s32 sp60;
    f32 temp_f0;
    Vec3f sp50;

    spA4 = path->count;
    spA0 = Lib_SegmentedToVirtual(path->points);
    Math_Vec3s_ToVec3f(&sp8C, &spA0[this->curRaceWaypoint]);

    if (this->curRaceWaypoint == 0) {
        phi_f12 = spA0[1].x - spA0[0].x;
        phi_f14 = spA0[1].z - spA0[0].z;
    } else if ((this->curRaceWaypoint + 1) == path->count) {
        phi_f12 = spA0[path->count - 1].x - spA0[path->count - 2].x;
        phi_f14 = spA0[path->count - 1].z - spA0[path->count - 2].z;
    } else {
        phi_f12 = spA0[this->curRaceWaypoint + 1].x - spA0[this->curRaceWaypoint - 1].x;
        phi_f14 = spA0[this->curRaceWaypoint + 1].z - spA0[this->curRaceWaypoint - 1].z;
    }

    func_8017B7F8(&sp8C, Math_Atan2S(phi_f12, phi_f14), &sp7C, &sp78, &sp74);

    if (((this->actor.world.pos.x * sp7C) + (sp78 * this->actor.world.pos.z) + sp74) > 0.0f) {
        this->curRaceWaypoint++;
        if (this->curRaceWaypoint >= spA4) {
            this->curRaceWaypoint = spA4 - 1;
        }
        Math_Vec3s_ToVec3f(&sp8C, &spA0[this->curRaceWaypoint]);
    }

    if (this->curRaceWaypoint == 0) {
        Math_Vec3s_ToVec3f(&sp80, &spA0[1]);
    } else {
        Math_Vec3s_ToVec3f(&sp80, &spA0[this->curRaceWaypoint - 1]);
    }

    func_8017D7C0(this->actor.world.pos.x, this->actor.world.pos.z, sp80.x, sp80.z, sp8C.x, sp8C.z, &sp70);

    if ((this->actor.bgCheckFlags & 8) || (this->unk_1EC & 4)) {
        EnHorse_RotateToPoint(this, globalCtx, &sp8C, 0xC80);
        if (this->unk_1EC & 4) {
            this->unk_1EC &= ~4;
        }
    } else {
        EnHorse_RotateToPoint(this, globalCtx, &sp8C, 0x320);
        if (sp70 < SQ(100.0f)) {
            if ((this->actor.xzDistToPlayer < 100.0f) ||
                (this->colliderJntSph.elements[0].info.ocElemFlags & OCELEM_HIT)) {
                s32 pad;

                if (Math_SinS(this->actor.yawTowardsPlayer - this->actor.world.rot.y) > 0.0f) {
                    this->actor.world.rot.y -= 0x1E0;
                } else {
                    this->actor.world.rot.y += 0x1E0;
                }
            } else if (this->actor.xzDistToPlayer < 300.0f) {
                if (Math_SinS(this->actor.yawTowardsPlayer - this->actor.world.rot.y) > 0.0f) {
                    this->actor.world.rot.y += 0x1E0;
                } else {
                    this->actor.world.rot.y -= 0x1E0;
                }
            }
            this->actor.shape.rot.y = this->actor.world.rot.y;
        }
    }

    sp68 = this->curRaceWaypoint - 3;
    if (sp68 < 0) {
        sp68 = 0;
    }

    sp64 = 1.0e+38;
    sp60 = sp68 + 5;
    if (path->count < sp60) {
        sp60 = path->count;
    }

    for (i = sp68; i < sp60; i++) {
        Math_Vec3s_ToVec3f(&sp50, &spA0[i]);
        temp_f0 = Math3D_Distance(&this->actor.world.pos, &sp50);
        if (temp_f0 < sp64) {
            sp64 = temp_f0;
            sp68 = i;
        }
    }

    this->unk_398 = spA0[this->curRaceWaypoint].y * 0.01f;
    if ((this->unk_1EC & 0x100) && !(this->stateFlags & ENHORSE_JUMPING) &&
        ((this->colliderCylinder1.base.acFlags & AC_HIT) || (this->colliderCylinder2.base.acFlags & AC_HIT) ||
         (this->unk_58C > 0))) {
        if (this->unk_58C == 0) {
            this->unk_590 = 0x1F4;
            this->unk_58C = 0x2B;
        }
        this->unk_58C--;
        if (this->actor.speedXZ > 5.0f) {
            this->actor.speedXZ -= 0.5f;
        }
    } else if (this->unk_590 > 0) {
        if (this->unk_590 == 0x1F4) {
            if (this->rider != NULL) {
                Actor_PlaySfxAtPos(&this->rider->actor, NA_SE_VO_IN_CRY_0);
            }
        }
        this->unk_590--;
        if (this->actor.speedXZ < this->unk_398) {
            this->actor.speedXZ += 1.0f;
        } else {
            this->actor.speedXZ -= 0.5f;
        }
    } else if (this->actor.params == ENHORSE_5) {
        s16 sp4A;

        if (sp68 >= this->curRaceWaypoint) {
            if (this->actor.speedXZ < this->unk_398) {
                this->actor.speedXZ += 0.5f;
            } else {
                this->actor.speedXZ -= 0.5f;
            }
            this->unk_394 |= 1;
            return;
        }

        sp4A = Actor_YawBetweenActors(&this->actor, &GET_PLAYER(globalCtx)->actor) - this->actor.world.rot.y;

        if ((fabsf(Math_SinS(sp4A)) < 0.9f) && (Math_CosS(sp4A) > 0.0f)) {
            if (this->actor.speedXZ < this->unk_398) {
                this->actor.speedXZ += 0.5f;
            } else {
                this->actor.speedXZ -= 0.25f;
            }
            this->unk_394 |= 1;
        } else {
            if (this->actor.speedXZ < 13.0f) {
                this->actor.speedXZ += 0.4f;
            } else {
                this->actor.speedXZ -= 0.2f;
            }
            this->unk_394 &= ~1;
        }
    } else if (sp68 >= this->curRaceWaypoint) {
        if (this->actor.speedXZ < this->unk_398) {
            this->actor.speedXZ += 0.5f;
        } else {
            this->actor.speedXZ -= 0.5f;
        }
        this->unk_394 |= 1;
    } else if ((sp68 + 1) == this->curRaceWaypoint) {
        s16 sp48 = Actor_YawBetweenActors(&this->actor, &GET_PLAYER(globalCtx)->actor) - this->actor.world.rot.y;

        if ((fabsf(Math_SinS(sp48)) < 0.9f) && (Math_CosS(sp48) > 0.0f)) {
            if (this->actor.speedXZ < this->unk_398) {
                this->actor.speedXZ += 0.5f;
            } else {
                this->actor.speedXZ -= 0.25f;
            }
            this->unk_394 |= 1;
        } else {
            if (this->actor.speedXZ < 12.0f) {
                this->actor.speedXZ += 0.4f;
            } else {
                this->actor.speedXZ -= 0.2f;
            }
            this->unk_394 &= ~1;
        }
    } else {
        if (this->actor.speedXZ < 13.0f) {
            this->actor.speedXZ += 0.4f;
        } else {
            this->actor.speedXZ -= 0.2f;
        }
        this->unk_394 &= ~1;
    }
}

void EnHorse_PlayWalkingSound(EnHorse* this) {
    if (sAnimSoundFrames[this->soundTimer] < this->curFrame) {
        if ((this->soundTimer == 0) && (sAnimSoundFrames[1] < this->curFrame)) {
            return;
        }

        if (this->type == HORSE_2) {
            Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_WALK);
        } else {
            Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_HORSE_WALK);
        }

        this->soundTimer++;
        if (this->soundTimer > 1) {
            this->soundTimer = 0;
        }
    }
}

void func_8087C178(EnHorse* this) {
    if (this->type == HORSE_2) {
        Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_RUN);
    } else {
        Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_HORSE_RUN);
    }
}

void func_8087C1C0(EnHorse* this) {
    if (this->type == HORSE_2) {
        Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_RUN);
    } else {
        Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_HORSE_RUN);
    }
}

f32 EnHorse_SlopeSpeedMultiplier(EnHorse* this, GlobalContext* globalCtx) {
    f32 multiplier = 1.0f;

    if ((Math_CosS(this->actor.shape.rot.x) < 0.939262f) && (Math_SinS(this->actor.shape.rot.x) < 0.0f)) {
        multiplier = 0.7f;
    }
    return multiplier;
}

void func_8087C288(GlobalContext* globalCtx, Vec3f* arg1, Vec3f* arg2, f32* arg3) {
    SkinMatrix_Vec3fMtxFMultXYZW(&globalCtx->viewProjectionMtxF, arg1, arg2, arg3);
}

s32 func_8087C2B8(GlobalContext* globalCtx, EnHorse* this, Vec3f* arg2, f32 arg3) {
    f32 phi_f14;

    if ((arg2->z > 0.0f) && (arg2->z < (this->actor.uncullZoneForward + this->actor.uncullZoneScale))) {
        if (arg3 < 1.0f) {
            phi_f14 = 1.0f;
        } else {
            phi_f14 = 1.0f / arg3;
        }

        if (((fabsf(arg2->x) * phi_f14) < 1.0f) && (((arg2->y + this->actor.uncullZoneDownward) * phi_f14) > -1.0f) &&
            (((arg2->y - this->actor.uncullZoneScale) * phi_f14) < 1.0f)) {
            return true;
        }
    }
    return false;
}

s32 func_8087C38C(GlobalContext* globalCtx, EnHorse* this, Vec3f* arg2) {
    Vec3f sp24;
    f32 sp20;
    f32 eyeDist;

    func_8087C288(globalCtx, arg2, &sp24, &sp20);

    if (fabsf(sp20) < 0.008f) {
        return false;
    }

    eyeDist = Math3D_Distance(arg2, &globalCtx->view.eye);

    return func_8087C2B8(globalCtx, this, &sp24, sp20) || (eyeDist < 100.0f);
}

void EnHorse_IdleAnimSounds(EnHorse* this, GlobalContext* globalCtx) {
    if ((this->animationIdx == ENHORSE_ANIM_IDLE) &&
        (((this->curFrame > 35.0f) && (this->type == HORSE_EPONA)) ||
         ((this->curFrame > 28.0f) && (this->type == HORSE_HNI)) ||
         ((this->curFrame > 25.0f) && (this->type == HORSE_2))) &&
        !(this->stateFlags & ENHORSE_SANDDUST_SOUND)) {
        this->stateFlags |= ENHORSE_SANDDUST_SOUND;
        if (this->type == HORSE_2) {
            Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_SANDDUST);
        } else {
            Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_SANDDUST);
        }
    } else if ((this->animationIdx == 3) && (this->curFrame > 25.0f) && !(this->stateFlags & ENHORSE_LAND2_SOUND)) {
        this->stateFlags |= ENHORSE_LAND2_SOUND;
        if (this->type == HORSE_2) {
            Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_LAND2);
        } else {
            Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_LAND2);
        }
    }
}

s32 EnHorse_Spawn(EnHorse* this, GlobalContext* globalCtx) {
    s32 i;
    f32 dist;
    Path* path;
    s32 spawn = false;
    f32 minDist = 1.0e+38;
    Player* player = GET_PLAYER(globalCtx);
    Vec3f spawnPos;
    s32 pathIdx = func_800F3940(globalCtx);
    s32 pathCount;
    Vec3s* pathPoints;

    if (pathIdx == -1) {
        return false;
    }

    path = &globalCtx->setupPathList[pathIdx];
    pathCount = path->count;
    pathPoints = Lib_SegmentedToVirtual(path->points);

    for (i = 0; i < pathCount; i++) {
        spawnPos.x = pathPoints[i].x;
        spawnPos.y = pathPoints[i].y;
        spawnPos.z = pathPoints[i].z;
        dist = Math3D_Distance(&player->actor.world.pos, &spawnPos);

        if ((minDist < dist) || func_8087C38C(globalCtx, this, &spawnPos)) {
            continue;
        }

        minDist = dist;
        this->actor.world.pos.x = spawnPos.x;
        this->actor.world.pos.y = spawnPos.y;
        this->actor.world.pos.z = spawnPos.z;
        this->actor.prevPos = this->actor.world.pos;
        this->actor.world.rot.y = 0;
        this->actor.shape.rot.y = Actor_YawBetweenActors(&this->actor, &GET_PLAYER(globalCtx)->actor);
        spawn = true;
        SkinMatrix_Vec3fMtxFMultXYZW(&globalCtx->viewProjectionMtxF, &this->actor.world.pos, &this->actor.projectedPos,
                                     &this->actor.projectedW);
    }

    if (spawn == true) {
        return true;
    }

    for (i = 0; i < pathCount; i++) {
        spawnPos.x = pathPoints[i].x;
        spawnPos.y = pathPoints[i].y;
        spawnPos.z = pathPoints[i].z;
        dist = Math3D_Distance(&player->actor.world.pos, &spawnPos);

        if (minDist < dist) {
            continue;
        }

        minDist = dist;
        this->actor.world.pos.x = spawnPos.x;
        this->actor.world.pos.y = spawnPos.y;
        this->actor.world.pos.z = spawnPos.z;
        this->actor.prevPos = this->actor.world.pos;
        this->actor.world.rot.y = 0;
        this->actor.shape.rot.y = Actor_YawBetweenActors(&this->actor, &GET_PLAYER(globalCtx)->actor);
        spawn = true;
        SkinMatrix_Vec3fMtxFMultXYZW(&globalCtx->viewProjectionMtxF, &this->actor.world.pos, &this->actor.projectedPos,
                                     &this->actor.projectedW);
    }

    return spawn;
}

void EnHorse_ResetCutscene(EnHorse* this, GlobalContext* globalCtx) {
    this->cutsceneAction = -1;
    this->cutsceneFlags = 0;
}

void EnHorse_ResetRace(EnHorse* this, GlobalContext* globalCtx) {
    this->inRace = false;
}

s32 EnHorse_PlayerCanMove(EnHorse* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if ((player->stateFlags1 & 1) || (func_800B7128(GET_PLAYER(globalCtx)) == true) ||
        (player->stateFlags1 & 0x100000) ||
        (((this->stateFlags & ENHORSE_FLAG_19) || (this->stateFlags & ENHORSE_FLAG_29)) && !this->inRace) ||
        (this->action == 19) || (player->actor.flags & ACTOR_FLAG_100) || (globalCtx->csCtx.state != 0) ||
        (ActorCutscene_GetCurrentIndex() != -1) || (player->stateFlags1 & 0x20) || (player->csMode != 0)) {
        return false;
    }
    return true;
}

void EnHorse_ResetHorsebackArchery(EnHorse* this, GlobalContext* globalCtx) {
    this->unk_39C = 0;
    this->hbaStarted = 0;
    this->hbaFlags = 0;
}

void EnHorse_ClearDustFlags(u16* dustFlags) {
    *dustFlags = 0;
}

void func_8087C9F8(EnHorse* this) {
}

void func_8087CA04(EnHorse* this, GlobalContext* globalCtx) {
}

#ifdef NON_MATCHING
void EnHorse_Init(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnHorse* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    EnHorse_ClearDustFlags(&this->dustFlags);
    D_801BDAA4 = 0;
    Skin_Setup(&this->skin);
    this->riderPos = this->actor.world.pos;
    this->unk_52C = 0;
    this->noInputTimer = 0;
    this->riderPos.y += 70.0f;
    this->noInputTimerMax = 0;
    this->unk_1EC = 0;
    this->unk_58C = 0;
    this->unk_590 = 0;
    this->unk_3E8 = 0.0f;
    this->unk_528 = 100.0f;

    if (ENHORSE_GET_8000(&this->actor)) {
        this->type = HORSE_4;
        this->unk_528 = 80.0f;
        this->boostSpeed = 12;
        if ((this->bankIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_HA)) < 0) {
            Actor_MarkForDeath(&this->actor);
            return;
        }
        this->unk_1EC |= 1;
        this->actor.update = func_8087D540;
    } else if (ENHORSE_GET_4000(&this->actor)) {
        this->type = HORSE_2;
        this->unk_528 = 64.8f;
        this->boostSpeed = 15;
        if ((this->bankIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_HORSE_LINK_CHILD)) < 0) {
            this->actor.objBankIndex = Object_Spawn(&globalCtx->objectCtx, OBJECT_HORSE_LINK_CHILD);
            Actor_SetObjectDependency(globalCtx, &this->actor);
            Skin_Init(&globalCtx->state, &this->skin, sSkeletonHeaders[this->type], sAnimationHeaders[this->type][0]);
            Animation_PlayOnce(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx]);
            this->unk_1EC |= 0x200;
        } else {
            this->actor.update = func_8087D540;
        }
    } else if (ENHORSE_GET_2000(&this->actor)) {
        this->type = HORSE_3;
        this->boostSpeed = 12;
        if ((this->bankIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_HA)) < 0) {
            Actor_MarkForDeath(&this->actor);
            return;
        }
        this->unk_1EC |= 1;
        this->actor.update = func_8087D540;
    } else {
        this->type = HORSE_EPONA;
        this->boostSpeed = 15;
        Actor_MarkForDeath(&this->actor);
    }

    this->actor.params &= ~0xE000;
    if (this->actor.params == 0x1FFF) {
        this->actor.params = ENHORSE_1;
    }

    if (this->actor.params == ENHORSE_3) {
        this->stateFlags = ENHORSE_FLAG_19 | ENHORSE_CANT_JUMP | ENHORSE_UNRIDEABLE;
    } else if (this->actor.params == ENHORSE_8) {
        this->stateFlags = ENHORSE_FLAG_19 | ENHORSE_CANT_JUMP;
        if (CHECK_QUEST_ITEM(14)) {
            this->stateFlags &= ~ENHORSE_CANT_JUMP;
            this->stateFlags |= ENHORSE_FLAG_26;
        }
    } else if (this->actor.params == ENHORSE_13) {
        this->stateFlags = ENHORSE_FLAG_29;
        this->unk_1EC |= 0x10;
    } else if (this->actor.params == ENHORSE_4) {
        this->stateFlags = ENHORSE_FLAG_29 | ENHORSE_CANT_JUMP;
        this->actor.flags |= ACTOR_FLAG_80000000;
    } else if (this->actor.params == ENHORSE_5) {
        this->stateFlags = ENHORSE_FLAG_29 | ENHORSE_CANT_JUMP;
        this->actor.flags |= ACTOR_FLAG_80000000;
    } else if (this->actor.params == ENHORSE_15) {
        this->stateFlags = ENHORSE_UNRIDEABLE | ENHORSE_FLAG_7;
    } else if (this->actor.params == ENHORSE_17) {
        this->stateFlags = 0;
        this->unk_1EC |= 8;
    } else if (this->actor.params == ENHORSE_18) {
        this->stateFlags = ENHORSE_FLAG_29 | ENHORSE_CANT_JUMP;
        this->actor.flags |= ACTOR_FLAG_80000000;
    } else if (this->actor.params == ENHORSE_1) {
        this->stateFlags = ENHORSE_FLAG_7;
    } else if ((this->actor.params == ENHORSE_19) || (this->actor.params == ENHORSE_20)) {
        this->stateFlags = ENHORSE_CANT_JUMP | ENHORSE_UNRIDEABLE;
    } else {
        this->stateFlags = 0;
    }

    if (((globalCtx->sceneNum == SCENE_KOEPONARACE) && ((gSaveContext.save.weekEventReg[92] & (1 | 2 | 4)) == 1)) ||
        ((gSaveContext.save.entranceIndex == 0x6400) && Cutscene_GetSceneSetupIndex(globalCtx))) {
        this->stateFlags |= ENHORSE_FLAG_25;
    }

    this->actor.gravity = -3.5f;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawHorse, 20.0f);
    this->action = ENHORSE_ACT_IDLE;
    this->actor.speedXZ = 0.0f;

    if (this->type == HORSE_2) {
        sJntSphInit.elements[0].dim.limb = 13;
    } else if ((this->type == HORSE_3) || (this->type == HORSE_4)) {
        sJntSphInit.elements[0].dim.limb = 10;
    }

    Collider_InitCylinder(globalCtx, &this->colliderCylinder1);
    Collider_SetCylinder(globalCtx, &this->colliderCylinder1, &this->actor, &sCylinderInit1);
    Collider_InitCylinder(globalCtx, &this->colliderCylinder2);
    Collider_SetCylinder(globalCtx, &this->colliderCylinder2, &this->actor, &sCylinderInit2);
    Collider_InitJntSph(globalCtx, &this->colliderJntSph);
    Collider_SetJntSph(globalCtx, &this->colliderJntSph, &this->actor, &sJntSphInit, this->colliderJntSphElements);

    if (this->type == HORSE_2) {
        this->colliderCylinder1.dim.radius = this->colliderCylinder1.dim.radius * 0.8f;
        this->colliderCylinder2.dim.radius = this->colliderCylinder2.dim.radius * 0.8f;
        this->colliderJntSph.elements[0].dim.modelSphere.radius *= 0.6f;
    } else if (this->type == HORSE_4) {
        this->colliderCylinder1.dim.radius = 50;
    }

    CollisionCheck_SetInfo(&this->actor.colChkInfo, NULL, &sColChkInfoInit);

    if (this->type == HORSE_2) {
        Actor_SetScale(&this->actor, 0.00648f);
    } else if (this->type == HORSE_4) {
        Actor_SetScale(&this->actor, 0.008f);
    } else {
        Actor_SetScale(&this->actor, 0.01f);
    }

    this->actor.focus.pos = this->actor.world.pos;
    this->playerControlled = false;
    this->actor.focus.pos.y += 70.0f;

    if (!(this->unk_1EC & 1) && !(this->unk_1EC & 0x200) && (this->actor.update == EnHorse_Update)) {
        Skin_Init(&globalCtx->state, &this->skin, sSkeletonHeaders[this->type], sAnimationHeaders[this->type][0]);
    }

    this->animationIdx = 0;
    this->numBoosts = 6;
    this->boostRegenTime = 0;
    this->postDrawFunc = NULL;
    this->blinkTimer = 0;

    EnHorse_ResetCutscene(this, globalCtx);
    EnHorse_ResetRace(this, globalCtx);
    EnHorse_ResetHorsebackArchery(this, globalCtx);

    if (this->actor.params == ENHORSE_2) {
        this->unk_53C = 0;
        EnHorse_InitInactive(this);
    } else if (this->actor.params == ENHORSE_3) {
        EnHorse_InitIngoHorse(this);
        this->rider = (EnIn*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_IN, this->actor.world.pos.x,
                                         this->actor.world.pos.y, this->actor.world.pos.z, this->actor.shape.rot.x,
                                         this->actor.shape.rot.y, 1, 1);
        this->unk_398 = 14.34f;
    } else if (this->actor.params == ENHORSE_4) {
        func_80881634(this);
        this->unk_398 = 14.34f;
        this->rider = (EnIn*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_IN, this->actor.world.pos.x,
                                         this->actor.world.pos.y, this->actor.world.pos.z, this->actor.shape.rot.x,
                                         this->actor.shape.rot.y, 1, 1);
        this->unk_1EC |= 0x100;
    } else if (this->actor.params == ENHORSE_5) {
        func_80881634(this);
        this->unk_398 = 14.525f;
        this->rider = (EnIn*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_IN, this->actor.world.pos.x,
                                         this->actor.world.pos.y, this->actor.world.pos.z, this->actor.shape.rot.x,
                                         this->actor.shape.rot.y, 1, 2);
        this->unk_1EC |= 0x100;
    } else if (this->actor.params == ENHORSE_9) {
        EnHorse_InitCutscene(this, globalCtx);
    } else if (this->actor.params == ENHORSE_10) {
        EnHorse_InitHorsebackArchery(this);
        func_80112AFC(globalCtx);
    } else if (this->actor.params == ENHORSE_14) {
        func_808846F0(this, globalCtx);
        if ((globalCtx->sceneNum == SCENE_LOST_WOODS) && !Cutscene_IsPlaying(globalCtx)) {
            Actor_MarkForDeath(&this->actor);
        }
    } else if (this->actor.params == ENHORSE_16) {
        func_8087C9F8(this);
    } else if (this->actor.params == ENHORSE_15) {
        EnHorse_ResetIdleAnimation(this);
    } else if (this->actor.params == ENHORSE_18) {
        func_80884994(this);
    } else if (this->actor.params == ENHORSE_19) {
        EnIn* in;

        func_80884D04(this, globalCtx);
        in = (EnIn*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_IN, this->actor.world.pos.x,
                                this->actor.world.pos.y, this->actor.world.pos.z, this->actor.shape.rot.x,
                                this->actor.shape.rot.y, 1, 1);
        this->rider = in;
        in->unk4AC |= (0x20 | 0x4);
    } else if (this->actor.params == ENHORSE_20) {
        EnIn* in;

        func_80884D04(this, globalCtx);
        in = (EnIn*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_IN, this->actor.world.pos.x,
                                this->actor.world.pos.y, this->actor.world.pos.z, this->actor.shape.rot.x,
                                this->actor.shape.rot.y, 1, 1);
        this->rider = in;
        in->unk4AC |= (0x20 | 0x8 | 0x4);
    } else {
        EnHorse_StartIdleRidable(this);
    }

    this->actor.shape.rot.z = 0;
    this->actor.world.rot.z = this->actor.shape.rot.z;
    this->actor.home.rot.z = this->actor.shape.rot.z;
    this->unk_3EC = this->actor.world.rot.y;
    this->unk_538 = 0;

    if (this->unk_1EC & 0x100) {
        this->colliderCylinder1.base.colType = COLTYPE_HIT3;
        this->colliderCylinder1.base.acFlags |= (AC_TYPE_PLAYER | AC_ON);
        this->colliderCylinder1.info.bumperFlags |= BUMP_ON;
        this->colliderCylinder1.info.bumper.dmgFlags = 0x10000 | 0x2000 | 0x1000 | 0x800 | 0x20;
        this->colliderCylinder2.base.colType = COLTYPE_HIT3;
        this->colliderCylinder2.base.acFlags |= (AC_TYPE_PLAYER | AC_ON);
        this->colliderCylinder2.info.bumperFlags |= BUMP_ON;
        this->colliderCylinder2.info.bumper.dmgFlags = 0x10000 | 0x2000 | 0x1000 | 0x800 | 0x20;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/EnHorse_Init.s")
#endif

void func_8087D540(Actor* thisx, GlobalContext* globalCtx) {
    EnHorse* this = THIS;

    if (Object_IsLoaded(&globalCtx->objectCtx, this->bankIndex)) {
        this->actor.objBankIndex = this->bankIndex;
        Actor_SetObjectDependency(globalCtx, &this->actor);
        this->actor.update = EnHorse_Update;
        if (this->unk_1EC & 1) {
            if (this->type == HORSE_3) {
                SkelAnime_InitFlex(globalCtx, &this->skin.skelAnime, &object_ha_Skel_008C68, NULL, this->jointTable,
                                   this->morphTable, OBJECT_HA_1_LIMB_MAX);
            } else {
                SkelAnime_InitFlex(globalCtx, &this->skin.skelAnime, &object_ha_Skel_0150D8, NULL, this->jointTable,
                                   this->morphTable, OBJECT_HA_2_LIMB_MAX);
            }
        } else {
            Skin_Init(&globalCtx->state, &this->skin, sSkeletonHeaders[this->type], sAnimationHeaders[this->type][0]);
        }
        Animation_PlayOnce(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx]);
    }
}

void EnHorse_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnHorse* this = THIS;

    if (this->stateFlags & ENHORSE_DRAW) {
        Audio_StopSfxByPos(&this->unk_218);
    }
    Skin_Free(&globalCtx->state, &this->skin);
    Collider_DestroyCylinder(globalCtx, &this->colliderCylinder1);
    Collider_DestroyCylinder(globalCtx, &this->colliderCylinder2);
    Collider_DestroyJntSph(globalCtx, &this->colliderJntSph);
}

void EnHorse_RotateToPlayer(EnHorse* this, GlobalContext* globalCtx) {
    EnHorse_RotateToPoint(this, globalCtx, &GET_PLAYER(globalCtx)->actor.world.pos, 0x320);
    if (this->stateFlags & ENHORSE_OBSTACLE) {
        this->actor.world.rot.y += 1600;
    }
    this->actor.shape.rot.y = this->actor.world.rot.y;
}

void EnHorse_Freeze(EnHorse* this, GlobalContext* globalCtx) {
    if ((this->action != ENHORSE_ACT_HBA) && (this->action != ENHORSE_ACT_21) &&
        (this->action != ENHORSE_ACT_FLEE_PLAYER)) {
        if (sResetNoInput[this->actor.params] && (this->actor.params != ENHORSE_6)) {
            Player* player = GET_PLAYER(globalCtx);

            this->noInputTimerMax = 0;
            this->noInputTimer = 0;
            player->actor.world.pos = this->actor.world.pos;
            player->actor.world.pos.y += 70.0f;
        }
        this->prevAction = this->action;
        this->action = ENHORSE_ACT_FROZEN;
        this->colliderCylinder1.base.ocFlags1 &= ~OC1_ON;
        this->colliderCylinder2.base.ocFlags1 &= ~OC1_ON;
        this->colliderJntSph.base.ocFlags1 &= ~OC1_ON;
        this->animationIdx = ENHORSE_ANIM_IDLE;
    }
}

void EnHorse_Frozen(EnHorse* this, GlobalContext* globalCtx) {
    this->actor.speedXZ = 0.0f;
    this->noInputTimer--;
    if (this->noInputTimer < 0) {
        this->colliderCylinder1.base.ocFlags1 |= OC1_ON;
        this->colliderCylinder2.base.ocFlags1 |= OC1_ON;
        this->colliderJntSph.base.ocFlags1 |= OC1_ON;
        if (this->playerControlled == true) {
            this->stateFlags &= ~ENHORSE_FLAG_7;
            if (this->actor.params == ENHORSE_6) {
                EnHorse_StartMountedIdleResetAnim(this);
            } else if (this->actor.params == ENHORSE_11) {
                this->actor.params = ENHORSE_7;
                if (globalCtx->csCtx.state != 0) {
                    EnHorse_StartMountedIdle(this);
                } else {
                    this->actor.speedXZ = 8.0f;
                    EnHorse_StartGalloping(this);
                }
            } else if (this->prevAction == ENHORSE_ACT_IDLE) {
                EnHorse_StartMountedIdle(this);
            } else {
                EnHorse_StartMountedIdleResetAnim(this);
            }

            if (this->actor.params != ENHORSE_0) {
                this->actor.params = ENHORSE_0;
            }
        } else if (this->prevAction == ENHORSE_ACT_MOUNTED_TURN) {
            EnHorse_ChangeIdleAnimation(this, 0, 0.0f);
        } else if (this->prevAction == ENHORSE_ACT_MOUNTED_WALK) {
            EnHorse_ChangeIdleAnimation(this, 0, 0.0f);
        } else {
            EnHorse_ChangeIdleAnimation(this, 0, 0.0f);
        }
    }
}

void EnHorse_UpdateSpeed(EnHorse* this, GlobalContext* globalCtx, f32 brakeDecel, f32 brakeAngle, f32 minStickMag,
                         f32 decel, f32 baseSpeed, s16 turnSpeed) {
    f32 phi_f0;
    f32 stickMag;
    s16 stickAngle;
    s16 turn;
    f32 temp_f12;

    if (!EnHorse_PlayerCanMove(this, globalCtx)) {
        if (this->actor.speedXZ > 8.0f) {
            this->actor.speedXZ -= decel;
        } else if (this->actor.speedXZ < 0.0f) {
            this->actor.speedXZ = 0.0f;
        }
        return;
    }

    baseSpeed *= EnHorse_SlopeSpeedMultiplier(this, globalCtx);
    EnHorse_StickDirection(&this->curStick, &stickMag, &stickAngle);

    if (Math_CosS(stickAngle) <= brakeAngle) {
        this->actor.speedXZ -= brakeDecel;
        this->actor.speedXZ = CLAMP_MIN(this->actor.speedXZ, 0.0f);
        return;
    }

    if (stickMag < minStickMag) {
        this->stateFlags &= ~ENHORSE_BOOST;
        this->stateFlags &= ~ENHORSE_BOOST_DECEL;
        this->actor.speedXZ -= decel;
        if (this->actor.speedXZ < 0.0f) {
            this->actor.speedXZ = 0.0f;
        }
        return;
    }

    if (this->stateFlags & ENHORSE_BOOST) {
        if ((16 - this->boostTimer) > 0) {
            this->actor.speedXZ =
                (((EnHorse_SlopeSpeedMultiplier(this, globalCtx) * this->boostSpeed) - this->actor.speedXZ) /
                 (16.0f - this->boostTimer)) +
                this->actor.speedXZ;
        } else {
            this->actor.speedXZ = EnHorse_SlopeSpeedMultiplier(this, globalCtx) * this->boostSpeed;
        }

        if ((EnHorse_SlopeSpeedMultiplier(this, globalCtx) * this->boostSpeed) <= this->actor.speedXZ) {
            this->stateFlags &= ~ENHORSE_BOOST;
            this->stateFlags |= ENHORSE_BOOST_DECEL;
        }
    } else if (this->stateFlags & ENHORSE_BOOST_DECEL) {
        if (this->actor.speedXZ > baseSpeed) {
            this->actor.speedXZ -= 0.06f;
        } else if (this->actor.speedXZ < baseSpeed) {
            this->actor.speedXZ = baseSpeed;
            this->stateFlags &= ~ENHORSE_BOOST_DECEL;
        }
    } else {
        if (this->actor.speedXZ <= (baseSpeed * (1.0f / 54.0f) * stickMag)) {
            phi_f0 = 1.0f;
        } else {
            phi_f0 = -1.0f;
        }

        this->actor.speedXZ += phi_f0 * 50.0f * 0.01f;

        if (this->actor.speedXZ > baseSpeed) {
            this->actor.speedXZ -= decel;
            if (this->actor.speedXZ < baseSpeed) {
                this->actor.speedXZ = baseSpeed;
            }
        }
    }

    temp_f12 = stickAngle * (1 / 32236.f);
    turn = stickAngle * temp_f12 * temp_f12 * (2.2f - (this->actor.speedXZ * (1.0f / this->boostSpeed)));
    turn = CLAMP(turn, -turnSpeed * (2.2f - (1.7f * this->actor.speedXZ * (1.0f / this->boostSpeed))),
                 turnSpeed * (2.2f - (1.7f * this->actor.speedXZ * (1.0f / this->boostSpeed))));
    this->actor.world.rot.y += turn;
    this->actor.shape.rot.y = this->actor.world.rot.y;
}

void EnHorse_StartMountedIdleResetAnim(EnHorse* this) {
    this->skin.skelAnime.curFrame = 0.0f;
    EnHorse_StartMountedIdle(this);
    this->stateFlags &= ~ENHORSE_SANDDUST_SOUND;
}

void EnHorse_StartMountedIdle(EnHorse* this) {
    f32 curFrame;

    this->action = ENHORSE_ACT_MOUNTED_TURN;
    this->animationIdx = ENHORSE_ANIM_IDLE;

    if (((this->curFrame > 35.0f) && (this->type == HORSE_EPONA)) ||
        ((this->curFrame > 28.0f) && (this->type == HORSE_HNI))) {
        if (!(this->stateFlags & ENHORSE_SANDDUST_SOUND)) {
            this->stateFlags |= ENHORSE_SANDDUST_SOUND;
            if (this->type == HORSE_2) {
                Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_SANDDUST);
            } else {
                Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_SANDDUST);
            }
        }
    }
    curFrame = this->skin.skelAnime.curFrame;
    Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.0f, curFrame,
                     Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE, -3.0f);
}

void EnHorse_MountedIdle(EnHorse* this, GlobalContext* globalCtx) {
    f32 mag;
    s16 angle = 0;

    this->actor.speedXZ = 0.0f;
    EnHorse_StickDirection(&this->curStick, &mag, &angle);
    if (mag > 10.0f) {
        if (EnHorse_PlayerCanMove(this, globalCtx) == true) {
            if (Math_CosS(angle) <= -0.5f) {
                EnHorse_StartReversingInterruptable(this);
            } else if (Math_CosS(angle) <= 0.7071f) {
                EnHorse_StartTurning(this);
            } else {
                EnHorse_StartWalkingFromIdle(this);
            }
        } else if (this->unk_3EC != this->actor.world.rot.y) {
            EnHorse_StartTurning(this);
        }
    }

    if (SkelAnime_Update(&this->skin.skelAnime)) {
        EnHorse_MountedIdleAnim(this);
    }
}

void EnHorse_MountedIdleAnim(EnHorse* this) {
    this->skin.skelAnime.curFrame = 0.0f;
    EnHorse_MountedIdleWhinney(this);
}

void EnHorse_MountedIdleWhinney(EnHorse* this) {
    f32 curFrame;

    this->action = ENHORSE_ACT_MOUNTED_WALK;
    this->animationIdx = ENHORSE_ANIM_WHINNEY;
    curFrame = this->skin.skelAnime.curFrame;
    Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.0f, curFrame,
                     Animation_GetLastFrame(sAnimationHeaders[this->type][1]), ANIMMODE_ONCE, -3.0f);
    if (this->stateFlags & ENHORSE_DRAW) {
        if (this->type == HORSE_2) {
            Audio_PlaySfxAtPos(&this->unk_218, NA_SE_EV_KID_HORSE_GROAN);
        } else {
            Audio_PlaySfxAtPos(&this->unk_218, NA_SE_EV_HORSE_GROAN);
        }
    }
}

void EnHorse_MountedIdleWhinneying(EnHorse* this, GlobalContext* globalCtx) {
    f32 stickMag;
    s16 stickAngle = 0;

    this->actor.speedXZ = 0.0f;
    EnHorse_StickDirection(&this->curStick, &stickMag, &stickAngle);
    if (stickMag > 10.0f) {
        if (EnHorse_PlayerCanMove(this, globalCtx) == true) {
            if (Math_CosS(stickAngle) <= -0.5f) {
                EnHorse_StartReversingInterruptable(this);
            } else if (Math_CosS(stickAngle) <= 0.7071f) {
                EnHorse_StartTurning(this);
            } else {
                EnHorse_StartWalkingFromIdle(this);
            }
        } else if (this->unk_3EC != this->actor.world.rot.y) {
            EnHorse_StartTurning(this);
        }
    }

    if (SkelAnime_Update(&this->skin.skelAnime)) {
        EnHorse_StartMountedIdleResetAnim(this);
    }
}

void EnHorse_StartTurning(EnHorse* this) {
    this->action = ENHORSE_ACT_MOUNTED_TROT;
    this->soundTimer = 0;
    this->animationIdx = ENHORSE_ANIM_WALK;
    Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.0f, 0.0f,
                     Animation_GetLastFrame(sAnimationHeaders[this->type][4]), ANIMMODE_ONCE, -3.0f);
}

void EnHorse_MountedTurn(EnHorse* this, GlobalContext* globalCtx) {
    f32 stickMag;
    s16 clampedYaw;
    s16 stickAngle;

    this->actor.speedXZ = 0.0f;
    EnHorse_PlayWalkingSound(this);
    if (EnHorse_PlayerCanMove(this, globalCtx) == true) {
        EnHorse_StickDirection(&this->curStick, &stickMag, &stickAngle);
        if (stickMag > 10.0f) {
            if (!EnHorse_PlayerCanMove(this, globalCtx)) {
                EnHorse_StartMountedIdleResetAnim(this);
            } else if (Math_CosS(stickAngle) <= -0.5f) {
                EnHorse_StartReversingInterruptable(this);
            } else if (Math_CosS(stickAngle) <= 0.7071f) {
                clampedYaw = CLAMP(stickAngle, -1600.0f, 1600.0f);
                this->actor.world.rot.y += clampedYaw;
                this->actor.shape.rot.y = this->actor.world.rot.y;
            } else {
                EnHorse_StartWalkingInterruptable(this);
            }
        }
    }

    if (SkelAnime_Update(&this->skin.skelAnime)) {
        if (EnHorse_PlayerCanMove(this, globalCtx) == true) {
            if (Math_CosS(stickAngle) <= 0.7071f) {
                EnHorse_StartTurning(this);
            } else {
                EnHorse_StartMountedIdleResetAnim(this);
            }
        } else if (this->unk_3EC != this->actor.world.rot.y) {
            EnHorse_StartTurning(this);
        } else {
            EnHorse_StartMountedIdleResetAnim(this);
        }
    }
}

void EnHorse_StartWalkingFromIdle(EnHorse* this) {
    EnHorse_StartWalkingInterruptable(this);
    if (!(this->stateFlags & ENHORSE_FLAG_8) && !(this->stateFlags & ENHORSE_FLAG_9)) {
        this->stateFlags |= ENHORSE_FLAG_9;
        this->waitTimer = 8;
    } else {
        this->waitTimer = 0;
    }
}

void EnHorse_StartWalkingInterruptable(EnHorse* this) {
    this->noInputTimer = 0;
    this->noInputTimerMax = 0;
    EnHorse_StartWalking(this);
}

void EnHorse_StartWalking(EnHorse* this) {
    this->action = ENHORSE_ACT_MOUNTED_GALLOP;
    this->soundTimer = 0;
    this->animationIdx = ENHORSE_ANIM_WALK;
    this->waitTimer = 0;
    Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.0f, 0.0f,
                     Animation_GetLastFrame(sAnimationHeaders[this->type][4]), ANIMMODE_ONCE, -3.0f);
}

void EnHorse_MountedWalkingReset(EnHorse* this) {
    this->action = ENHORSE_ACT_MOUNTED_GALLOP;
    this->soundTimer = 0;
    this->animationIdx = ENHORSE_ANIM_WALK;
    this->waitTimer = 0;
    Animation_PlayOnce(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx]);
}

void EnHorse_MountedWalk(EnHorse* this, GlobalContext* globalCtx) {
    f32 stickMag;
    s16 stickAngle;

    EnHorse_PlayWalkingSound(this);
    EnHorse_StickDirection(&this->curStick, &stickMag, &stickAngle);

    if ((this->noInputTimerMax == 0) ||
        ((this->noInputTimer > 0) && (this->noInputTimer < (this->noInputTimerMax - 20)))) {
        EnHorse_UpdateSpeed(this, globalCtx, 0.3f, -0.5f, 10.0f, 0.06f, 3.0f, 0x320);
    } else {
        this->actor.speedXZ = 3.0f;
    }

    if (this->actor.speedXZ == 0.0f) {
        this->stateFlags &= ~ENHORSE_FLAG_9;
        EnHorse_StartMountedIdleResetAnim(this);
        this->noInputTimer = 0;
        this->noInputTimerMax = 0;
    } else if (this->actor.speedXZ > 3.0f) {
        this->stateFlags &= ~ENHORSE_FLAG_9;
        EnHorse_StartTrotting(this);
        this->noInputTimer = 0;
        this->noInputTimerMax = 0;
    }

    if (this->noInputTimer > 0) {
        this->noInputTimer--;
        if (this->noInputTimer <= 0) {
            this->noInputTimerMax = 0;
        }
    }

    if (this->waitTimer <= 0) {
        this->stateFlags &= ~ENHORSE_FLAG_9;
        this->skin.skelAnime.playSpeed = this->actor.speedXZ * 0.75f;
        if ((SkelAnime_Update(&this->skin.skelAnime) || (this->actor.speedXZ == 0.0f)) && (this->noInputTimer <= 0)) {
            if (this->actor.speedXZ > 3.0f) {
                EnHorse_StartTrotting(this);
                this->noInputTimer = 0;
                this->noInputTimerMax = 0;
            } else if ((stickMag < 10.0f) || (Math_CosS(stickAngle) <= -0.5f)) {
                EnHorse_StartMountedIdleResetAnim(this);
                this->noInputTimer = 0;
                this->noInputTimerMax = 0;
            } else {
                EnHorse_MountedWalkingReset(this);
            }
        }
    } else {
        this->waitTimer--;
        this->actor.speedXZ = 0.0f;
    }
}

void EnHorse_StartTrotting(EnHorse* this) {
    this->action = ENHORSE_ACT_MOUNTED_REARING;
    this->animationIdx = ENHORSE_ANIM_TROT;
    Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.0f, 0.0f,
                     Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE, -3.0f);
}

void EnHorse_MountedTrotReset(EnHorse* this) {
    this->action = ENHORSE_ACT_MOUNTED_REARING;
    this->animationIdx = ENHORSE_ANIM_TROT;
    Animation_PlayOnce(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx]);
}

void EnHorse_MountedTrot(EnHorse* this, GlobalContext* globalCtx) {
    f32 stickMag;
    s16 stickAngle;

    EnHorse_UpdateSpeed(this, globalCtx, 0.3f, -0.5f, 10.0f, 0.06f, 6.0f, 800);
    EnHorse_StickDirection(&this->curStick, &stickMag, &stickAngle);
    if (this->actor.speedXZ < 3.0f) {
        EnHorse_StartWalkingInterruptable(this);
    }

    this->skin.skelAnime.playSpeed = this->actor.speedXZ * 0.375f;

    if (SkelAnime_Update(&this->skin.skelAnime)) {
        func_8087C178(this);
        func_8013ECE0(0.0f, 60, 8, 255);
        if (this->actor.speedXZ >= 6.0f) {
            EnHorse_StartGallopingInterruptable(this);
        } else if (this->actor.speedXZ < 3.0f) {
            EnHorse_StartWalkingInterruptable(this);
        } else {
            EnHorse_MountedTrotReset(this);
        }
    }
}

void EnHorse_StartGallopingInterruptable(EnHorse* this) {
    this->noInputTimer = 0;
    this->noInputTimerMax = 0;
    EnHorse_StartGalloping(this);
}

void EnHorse_StartGalloping(EnHorse* this) {
    this->action = ENHORSE_ACT_STOPPING;
    this->animationIdx = ENHORSE_ANIM_GALLOP;
    this->unk_230 = 0;
    Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.0f, 0.0f,
                     Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE, -3.0f);
}

void EnHorse_MountedGallopReset(EnHorse* this) {
    this->noInputTimer = 0;
    this->noInputTimerMax = 0;
    this->action = ENHORSE_ACT_STOPPING;
    this->animationIdx = ENHORSE_ANIM_GALLOP;
    this->unk_230 = 0;
    Animation_PlayOnce(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx]);
}

void EnHorse_JumpLanding(EnHorse* this, GlobalContext* globalCtx) {
    Vec3s* jointTable;
    f32 y;

    this->action = ENHORSE_ACT_STOPPING;
    this->animationIdx = ENHORSE_ANIM_GALLOP;
    Animation_PlayOnce(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx]);
    jointTable = this->skin.skelAnime.jointTable;
    y = jointTable->y;
    this->riderPos.y += y * 0.01f * this->unk_528 * 0.01f;
    this->postDrawFunc = NULL;
}

void EnHorse_MountedGallop(EnHorse* this, GlobalContext* globalCtx) {
    f32 stickMag;
    s16 stickAngle;

    EnHorse_StickDirection(&this->curStick, &stickMag, &stickAngle);

    if (this->noInputTimer <= 0) {
        EnHorse_UpdateSpeed(this, globalCtx, 0.3f, -0.5f, 10.0f, 0.06f, 8.0f, 800);
    } else if (this->noInputTimer > 0) {
        this->noInputTimer--;
        this->actor.speedXZ = 8.0f;
    }

    if (this->actor.speedXZ < 6.0f) {
        EnHorse_StartTrotting(this);
    }

    this->skin.skelAnime.playSpeed = this->actor.speedXZ * 0.3f;

    if (SkelAnime_Update(&this->skin.skelAnime)) {
        func_8087C1C0(this);
        func_8013ECE0(0.0f, 120, 8, 255);
        if (EnHorse_PlayerCanMove(this, globalCtx) == true) {
            if ((stickMag >= 10.0f) && (Math_CosS(stickAngle) <= -0.5f)) {
                EnHorse_StartBraking(this, globalCtx);
            } else if (this->actor.speedXZ < 6.0f) {
                EnHorse_StartTrotting(this);
            } else {
                EnHorse_MountedGallopReset(this);
            }
        } else {
            EnHorse_MountedGallopReset(this);
        }
    }
}

void EnHorse_StartRearing(EnHorse* this) {
    this->action = ENHORSE_ACT_REVERSE;
    this->animationIdx = ENHORSE_ANIM_REARING;

    if (sAnimationHeaders[this->type][this->animationIdx] == NULL) {
        if (Rand_ZeroOne() > 0.5f) {
            if (this->stateFlags & ENHORSE_DRAW) {
                if (this->type == HORSE_2) {
                    Audio_PlaySfxAtPos(&this->unk_218, NA_SE_EV_KID_HORSE_NEIGH);
                } else {
                    Audio_PlaySfxAtPos(&this->unk_218, NA_SE_EV_HORSE_NEIGH);
                }
            }
            func_8013ECE0(0.0f, 180, 20, 100);
            this->stateFlags &= ~ENHORSE_STOPPING_NEIGH_SOUND;
        }
        EnHorse_StartMountedIdleResetAnim(this);
    }

    this->stateFlags &= ~ENHORSE_LAND2_SOUND;
    if (this->stateFlags & ENHORSE_DRAW) {
        if (this->type == HORSE_2) {
            Audio_PlaySfxAtPos(&this->unk_218, NA_SE_EV_KID_HORSE_NEIGH);
        } else {
            Audio_PlaySfxAtPos(&this->unk_218, NA_SE_EV_HORSE_NEIGH);
        }
    }

    func_8013ECE0(0.0f, 180, 20, 100);
    Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.0f, 0.0f,
                     Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE, -3.0f);
}

void EnHorse_MountedRearing(EnHorse* this, GlobalContext* globalCtx) {
    f32 stickMag;
    s16 stickAngle;

    this->actor.speedXZ = 0.0f;
    if (this->curFrame > 25.0f) {
        if (!(this->stateFlags & ENHORSE_LAND2_SOUND)) {
            this->stateFlags |= ENHORSE_LAND2_SOUND;
            if (this->type == HORSE_2) {
                Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_LAND2);
            } else {
                Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_LAND2);
            }
            func_8013ECE0(0.0f, 180, 20, 100);
        }
    }

    EnHorse_StickDirection(&this->curStick, &stickMag, &stickAngle);

    if (SkelAnime_Update(&this->skin.skelAnime)) {
        if (EnHorse_PlayerCanMove(this, globalCtx) == true) {
            if (this->stateFlags & ENHORSE_FORCE_REVERSING) {
                this->noInputTimer = 100;
                this->noInputTimerMax = 100;
                this->stateFlags &= ~ENHORSE_FORCE_REVERSING;
                EnHorse_StartReversing(this);
            } else if (this->stateFlags & ENHORSE_FORCE_WALKING) {
                this->noInputTimer = 100;
                this->noInputTimerMax = 100;
                this->stateFlags &= ~ENHORSE_FORCE_WALKING;
                EnHorse_StartWalking(this);
            } else if (Math_CosS(stickAngle) <= -0.5f) {
                EnHorse_StartReversingInterruptable(this);
            } else {
                EnHorse_StartMountedIdleResetAnim(this);
            }
        } else {
            EnHorse_StartMountedIdleResetAnim(this);
        }
    }
}

void EnHorse_StartBraking(EnHorse* this, GlobalContext* globalCtx) {
    this->action = ENHORSE_ACT_LOW_JUMP;
    this->animationIdx = ENHORSE_ANIM_STOPPING;
    if (sAnimationHeaders[this->type][this->animationIdx] == NULL) {
        if (Rand_ZeroOne() > 0.5f) {
            if (this->stateFlags & ENHORSE_DRAW) {
                if (this->type == HORSE_2) {
                    Audio_PlaySfxAtPos(&this->unk_218, NA_SE_EV_KID_HORSE_NEIGH);
                } else {
                    Audio_PlaySfxAtPos(&this->unk_218, NA_SE_EV_HORSE_NEIGH);
                }
            }
            func_8013ECE0(0.0f, 180, 20, 100);
            this->stateFlags &= ~ENHORSE_STOPPING_NEIGH_SOUND;
        }
        EnHorse_StartMountedIdleResetAnim(this);
    }

    if (this->type == HORSE_2) {
        Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_HORSE_SLIP);
    } else {
        Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_HORSE_SLIP);
    }

    Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.5f, 0.0f,
                     Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE, -3.0f);
    this->stateFlags |= ENHORSE_STOPPING_NEIGH_SOUND;
    this->stateFlags &= ~ENHORSE_BOOST;
}

void EnHorse_Stopping(EnHorse* this, GlobalContext* globalCtx) {
    if (this->actor.speedXZ > 0.0f) {
        this->actor.speedXZ -= 0.6f;
        if (this->actor.speedXZ < 0.0f) {
            this->actor.speedXZ = 0.0f;
        }
    }

    if ((this->stateFlags & ENHORSE_STOPPING_NEIGH_SOUND) && (this->skin.skelAnime.curFrame > 29.0f)) {
        this->actor.speedXZ = 0.0f;
        if ((Rand_ZeroOne() > 0.5f) &&
            ((gSaveContext.save.entranceIndex != 0x6400) || !Cutscene_GetSceneSetupIndex(globalCtx))) {
            if (this->stateFlags & ENHORSE_DRAW) {
                if (this->type == HORSE_2) {
                    Audio_PlaySfxAtPos(&this->unk_218, NA_SE_EV_KID_HORSE_NEIGH);
                } else {
                    Audio_PlaySfxAtPos(&this->unk_218, NA_SE_EV_HORSE_NEIGH);
                }
            }
            func_8013ECE0(0.0f, 180, 20, 100);
            this->stateFlags &= ~ENHORSE_STOPPING_NEIGH_SOUND;
        } else {
            EnHorse_StartMountedIdleResetAnim(this);
        }
    }

    if (this->skin.skelAnime.curFrame > 29.0f) {
        this->actor.speedXZ = 0.0f;
    } else if ((this->actor.speedXZ > 3.0f) && (this->stateFlags & ENHORSE_FORCE_REVERSING)) {
        this->actor.speedXZ = 3.0f;
    }

    if (SkelAnime_Update(&this->skin.skelAnime)) {
        if (this->stateFlags & ENHORSE_FORCE_REVERSING) {
            this->noInputTimer = 100;
            this->noInputTimerMax = 100;
            EnHorse_StartReversing(this);
            this->stateFlags &= ~ENHORSE_FORCE_REVERSING;
        } else {
            EnHorse_StartMountedIdleResetAnim(this);
        }
    }
}

void EnHorse_StartReversingInterruptable(EnHorse* this) {
    this->noInputTimer = 0;
    this->noInputTimerMax = 0;
    EnHorse_StartReversing(this);
}

void EnHorse_StartReversing(EnHorse* this) {
    this->action = ENHORSE_ACT_HIGH_JUMP;
    this->animationIdx = ENHORSE_ANIM_WALK;
    this->soundTimer = 0;
    Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.0f, 0.0f,
                     Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_LOOP, -3.0f);
}

void EnHorse_Reverse(EnHorse* this, GlobalContext* globalCtx) {
    f32 stickMag;
    s16 stickAngle;
    s16 turnAmount;
    Player* player = GET_PLAYER(globalCtx);

    EnHorse_PlayWalkingSound(this);
    EnHorse_StickDirection(&this->curStick, &stickMag, &stickAngle);
    if (EnHorse_PlayerCanMove(this, globalCtx) == true) {
        if ((this->noInputTimerMax == 0) ||
            ((this->noInputTimer > 0) && (this->noInputTimer < (this->noInputTimerMax - 20)))) {
            if ((stickMag < 10.0f) && (this->noInputTimer <= 0)) {
                EnHorse_StartMountedIdleResetAnim(this);
                this->actor.speedXZ = 0.0f;
                return;
            } else if (stickMag < 10.0f) {
                stickAngle = -0x7FFF;
            } else if (Math_CosS(stickAngle) > -0.5f) {
                this->noInputTimerMax = 0;
                EnHorse_StartMountedIdleResetAnim(this);
                this->actor.speedXZ = 0.0f;
                return;
            }
        } else if (stickMag < 10.0f) {
            stickAngle = -0x7FFF;
        }
    } else if ((player->actor.flags & ACTOR_FLAG_100) || (globalCtx->csCtx.state != 0) ||
               (ActorCutscene_GetCurrentIndex() != -1) || (player->stateFlags1 & 0x20)) {
        EnHorse_StartMountedIdleResetAnim(this);
        this->actor.speedXZ = 0.0f;
        return;
    } else {
        stickAngle = -0x7FFF;
    }

    this->actor.speedXZ = -2.0f;
    turnAmount = -0x8000 - stickAngle;
    turnAmount = CLAMP(turnAmount, -2400.0f, 2400.0f);
    this->actor.world.rot.y += turnAmount;
    this->actor.shape.rot.y = this->actor.world.rot.y;

    if (this->noInputTimer > 0) {
        this->noInputTimer--;
        if (this->noInputTimer <= 0) {
            this->noInputTimerMax = 0;
        }
    }

    this->skin.skelAnime.playSpeed = this->actor.speedXZ * 0.5f * 1.5f;

    if (SkelAnime_Update(&this->skin.skelAnime) && (this->noInputTimer <= 0) &&
        (EnHorse_PlayerCanMove(this, globalCtx) == true)) {
        if ((stickMag > 10.0f) && (Math_CosS(stickAngle) <= -0.5f)) {
            this->noInputTimerMax = 0;
            EnHorse_StartReversingInterruptable(this);
        } else if (stickMag < 10.0f) {
            this->noInputTimerMax = 0;
            EnHorse_StartMountedIdleResetAnim(this);
        } else {
            EnHorse_StartReversing(this);
        }
    }
}

void EnHorse_LowJumpInit(EnHorse* this, GlobalContext* globalCtx) {
    this->skin.skelAnime.curFrame = 0.0f;
    EnHorse_StartLowJump(this, globalCtx);
}

void EnHorse_StartLowJump(EnHorse* this, GlobalContext* globalCtx) {
    f32 curFrame;
    Vec3s* jointTable;
    f32 y;

    this->action = ENHORSE_ACT_BRIDGE_JUMP;
    this->animationIdx = ENHORSE_ANIM_LOW_JUMP;
    curFrame = this->skin.skelAnime.curFrame;
    Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.5f, curFrame,
                     Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE, -3.0f);
    this->postDrawFunc = NULL;
    this->jumpStartY = this->actor.world.pos.y;
    this->actor.gravity = 0.0f;
    this->actor.velocity.y = 0.0f;

    jointTable = this->skin.skelAnime.jointTable;
    y = jointTable->y;
    this->riderPos.y -= ((y * 0.01f) * this->unk_528) * 0.01f;

    if (this->type == HORSE_2) {
        Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_HORSE_JUMP);
    } else {
        Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_HORSE_JUMP);
    }
    func_8013ECE0(0.0f, 170, 10, 10);
}

void EnHorse_Stub1(EnHorse* this) {
}

void EnHorse_LowJump(EnHorse* this, GlobalContext* globalCtx) {
    Vec3f pad;
    f32 temp_f0;
    f32 curFrame;
    Vec3s* jointTable;

    this->stateFlags |= ENHORSE_JUMPING;

    if (this->actor.speedXZ < 12.0f) {
        this->actor.speedXZ = 12.0f;
    }

    if (this->actor.floorHeight != BGCHECK_Y_MIN) {
        CollisionPoly* colPoly;
        s32 floorBgId;
        Vec3f pos = this->actor.world.pos;

        pos.y = this->actor.floorHeight - 5.0f;
        temp_f0 =
            BgCheck_EntityRaycastFloor5_2(globalCtx, &globalCtx->colCtx, &colPoly, &floorBgId, &this->actor, &pos);
        if ((this->actor.floorHeight - 120.0f) < temp_f0) {
            this->actor.floorHeight = temp_f0;
            this->actor.floorPoly = colPoly;
            this->actor.floorBgId = floorBgId;
        }
    }

    curFrame = this->skin.skelAnime.curFrame;

    if (curFrame > 17.0f) {
        this->actor.gravity = -3.5f;
        if (this->actor.velocity.y == 0.0f) {
            this->actor.velocity.y = -6.0f;
        }
        if (this->actor.world.pos.y < (this->actor.floorHeight + 90.0f)) {
            this->skin.skelAnime.playSpeed = 1.5f;
        } else {
            this->skin.skelAnime.playSpeed = 0.0f;
        }
    } else {
        jointTable = this->skin.skelAnime.jointTable;
        temp_f0 = jointTable->y;

        this->actor.world.pos.y = this->jumpStartY + (temp_f0 * 0.01f * this->unk_528 * 0.01f);
    }

    if (SkelAnime_Update(&this->skin.skelAnime) ||
        ((curFrame > 17.0f) &&
         (this->actor.world.pos.y < ((this->actor.floorHeight - this->actor.velocity.y) + 80.0f)))) {
        if (this->type == HORSE_2) {
            Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_HORSE_LAND);
        } else {
            Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_HORSE_LAND);
        }
        func_8013ECE0(0.0f, 255, 10, 80);
        this->stateFlags &= ~ENHORSE_JUMPING;
        this->actor.gravity = -3.5f;
        this->actor.world.pos.y = this->actor.floorHeight;
        EnHorse_JumpLanding(this, globalCtx);
    }
}

void EnHorse_HighJumpInit(EnHorse* this, GlobalContext* globalCtx) {
    this->skin.skelAnime.curFrame = 0.0f;
    EnHorse_StartHighJump(this, globalCtx);
}

void EnHorse_StartHighJump(EnHorse* this, GlobalContext* globalCtx) {
    f32 curFrame;
    Vec3s* jointTable;
    f32 y;

    this->action = ENHORSE_ACT_CS_UPDATE;
    this->animationIdx = ENHORSE_ANIM_HIGH_JUMP;
    curFrame = this->skin.skelAnime.curFrame;
    Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.5f, curFrame,
                     Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE, -3.0f);

    this->postDrawFunc = NULL;
    this->jumpStartY = this->actor.world.pos.y;
    this->actor.gravity = 0.0f;
    this->actor.velocity.y = 0.0f;

    jointTable = this->skin.skelAnime.jointTable;
    y = jointTable->y;
    this->riderPos.y -= ((y * 0.01f) * this->unk_528) * 0.01f;

    this->stateFlags |= ENHORSE_CALC_RIDER_POS;
    if (this->type == HORSE_2) {
        Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_HORSE_JUMP);
    } else {
        Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_HORSE_JUMP);
    }
    func_8013ECE0(0.0f, 170, 10, 10);
}

void EnHorse_Stub2(EnHorse* this) {
}

void EnHorse_HighJump(EnHorse* this, GlobalContext* globalCtx) {
    Vec3f pad;
    f32 temp_f0;
    f32 curFrame;
    Vec3s* jointTable;

    this->stateFlags |= ENHORSE_JUMPING;

    if (this->actor.speedXZ < 13.0f) {
        this->actor.speedXZ = 13.0f;
    }

    if (this->actor.floorHeight != BGCHECK_Y_MIN) {
        CollisionPoly* colPoly;
        s32 floorBgId;
        Vec3f pos = this->actor.world.pos;

        pos.y = this->actor.floorHeight - 5.0f;
        temp_f0 =
            BgCheck_EntityRaycastFloor5_2(globalCtx, &globalCtx->colCtx, &colPoly, &floorBgId, &this->actor, &pos);
        if ((this->actor.floorHeight - 120.0f) < temp_f0) {
            this->actor.floorHeight = temp_f0;
            this->actor.floorPoly = colPoly;
            this->actor.floorBgId = floorBgId;
        }
    }

    curFrame = this->skin.skelAnime.curFrame;

    if (curFrame > 23.0f) {
        this->actor.gravity = -3.5f;
        if (this->actor.velocity.y == 0.0f) {
            this->actor.velocity.y = -10.5f;
        }
        if (this->actor.world.pos.y < (this->actor.floorHeight + 90.0f)) {
            this->skin.skelAnime.playSpeed = 1.5f;
        } else {
            this->skin.skelAnime.playSpeed = 0.0f;
        }
    } else {
        jointTable = this->skin.skelAnime.jointTable;
        temp_f0 = jointTable->y;
        this->actor.world.pos.y = this->jumpStartY + (temp_f0 * 0.01f * this->unk_528 * 0.01f);
    }

    if (SkelAnime_Update(&this->skin.skelAnime) ||
        ((curFrame > 23.0f) &&
         (this->actor.world.pos.y < ((this->actor.floorHeight - this->actor.velocity.y) + 80.0f)))) {
        if (this->type == HORSE_2) {
            Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_HORSE_LAND);
        } else {
            Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_HORSE_LAND);
        }
        func_8013ECE0(0.0f, 255, 10, 80);
        this->stateFlags &= ~ENHORSE_JUMPING;
        this->actor.gravity = -3.5f;
        this->actor.world.pos.y = this->actor.floorHeight;
        func_800B1598(globalCtx, 25.0f, &this->actor.world.pos);
        EnHorse_JumpLanding(this, globalCtx);
    }
}

void EnHorse_InitInactive(EnHorse* this) {
    this->colliderCylinder1.base.ocFlags1 &= ~OC1_ON;
    this->colliderCylinder2.base.ocFlags1 &= ~OC1_ON;
    this->colliderJntSph.base.ocFlags1 &= ~OC1_ON;
    this->action = ENHORSE_ACT_INACTIVE;
    this->animationIdx = ENHORSE_ANIM_WALK;
    this->stateFlags |= ENHORSE_INACTIVE;
    this->followTimer = 0;
}

void EnHorse_Inactive(EnHorse* this, GlobalContext* globalCtx) {
    if ((D_801BDAA4 != 0) && (this->type == HORSE_2)) {
        D_801BDAA4 = 0;
        if (EnHorse_Spawn(this, globalCtx)) {
            if (this->type == HORSE_2) {
                Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_NEIGH);
            }
            this->stateFlags &= ~ENHORSE_INACTIVE;
        }
    }

    if (!(this->stateFlags & ENHORSE_INACTIVE)) {
        this->followTimer = 0;
        EnHorse_SetFollowAnimation(this, globalCtx);
        this->actor.params = ENHORSE_0;
        this->colliderCylinder1.base.ocFlags1 |= OC1_ON;
        this->colliderCylinder2.base.ocFlags1 |= OC1_ON;
        this->colliderJntSph.base.ocFlags1 |= OC1_ON;
    }
}

void EnHorse_PlayIdleAnimation(EnHorse* this, s32 anim, f32 morphFrames, f32 startFrames) {
    this->action = ENHORSE_ACT_IDLE;
    this->actor.speedXZ = 0.0f;

    if ((anim != ENHORSE_ANIM_IDLE) && (anim != ENHORSE_ANIM_WHINNEY) && (anim != ENHORSE_ANIM_REARING)) {
        anim = ENHORSE_ANIM_IDLE;
    }

    if (sAnimationHeaders[this->type][anim] == NULL) {
        anim = ENHORSE_ANIM_IDLE;
    }

    if (anim != this->animationIdx) {
        this->animationIdx = anim;
        if (anim == ENHORSE_ANIM_IDLE) {
            this->stateFlags &= ~ENHORSE_SANDDUST_SOUND;
        } else {
            if (this->animationIdx == ENHORSE_ANIM_WHINNEY) {
                if (this->stateFlags & ENHORSE_DRAW) {
                    if (this->type == HORSE_2) {
                        Audio_PlaySfxAtPos(&this->unk_218, NA_SE_EV_KID_HORSE_GROAN);
                    } else {
                        Audio_PlaySfxAtPos(&this->unk_218, NA_SE_EV_HORSE_GROAN);
                    }
                }
            } else if (this->animationIdx == ENHORSE_ANIM_REARING) {
                if (this->stateFlags & ENHORSE_DRAW) {
                    if (this->type == HORSE_2) {
                        Audio_PlaySfxAtPos(&this->unk_218, NA_SE_EV_KID_HORSE_NEIGH);
                    } else {
                        Audio_PlaySfxAtPos(&this->unk_218, NA_SE_EV_HORSE_NEIGH);
                    }
                }
                this->stateFlags &= ~ENHORSE_LAND2_SOUND;
            }
        }
        Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.0f, startFrames,
                         Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE,
                         morphFrames);
    }
}

void EnHorse_ChangeIdleAnimation(EnHorse* this, s32 anim, f32 morphFrames) {
    EnHorse_PlayIdleAnimation(this, anim, morphFrames, this->curFrame);
}

void EnHorse_ResetIdleAnimation(EnHorse* this) {
    this->animationIdx = ENHORSE_ANIM_WALK;
    EnHorse_PlayIdleAnimation(this, this->animationIdx, 0.0f, 0.0f);
}

void EnHorse_StartIdleRidable(EnHorse* this) {
    EnHorse_ResetIdleAnimation(this);
    this->stateFlags &= ~ENHORSE_UNRIDEABLE;
}

void EnHorse_Idle(EnHorse* this, GlobalContext* globalCtx) {
    this->actor.speedXZ = 0.0f;
    EnHorse_IdleAnimSounds(this, globalCtx);

    if ((D_801BDAA4 != 0) && (this->type == HORSE_2)) {
        D_801BDAA4 = 0;
        if (!func_8087C38C(globalCtx, this, &this->actor.world.pos)) {
            if (EnHorse_Spawn(this, globalCtx)) {
                if (this->type == HORSE_2) {
                    Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_NEIGH);
                } else {
                    Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_HORSE_NEIGH);
                }
                this->followTimer = 0;
                EnHorse_SetFollowAnimation(this, globalCtx);
            }
        } else {
            if (this->type == HORSE_2) {
                Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_NEIGH);
            } else {
                Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_HORSE_NEIGH);
            }
            this->followTimer = 0;
            EnHorse_StartMovingAnimation(this, 6, -3.0f, 0.0f);
        }
    }

    if (SkelAnime_Update(&this->skin.skelAnime)) {
        s32 idleAnimIdx = 0;

        if (this->animationIdx != 0) {
            if (this->animationIdx == 1) {
                idleAnimIdx = 1;
            } else if (this->animationIdx == 3) {
                idleAnimIdx = 2;
            }
        }
        // Play one of the two other idle animations
        EnHorse_PlayIdleAnimation(this, sIdleAnimIds[((Rand_ZeroOne() > 0.5f) ? 0 : 1) + idleAnimIdx * 2], 0.0f, 0.0f);
    }
}

void EnHorse_StartMovingAnimation(EnHorse* this, s32 anim, f32 morphFrames, f32 startFrames) {
    this->action = ENHORSE_ACT_FOLLOW_PLAYER;
    this->stateFlags &= ~ENHORSE_TURNING_TO_PLAYER;

    if ((anim != ENHORSE_ANIM_TROT) && (anim != ENHORSE_ANIM_GALLOP) && (anim != ENHORSE_ANIM_WALK)) {
        anim = ENHORSE_ANIM_WALK;
    }

    if (anim != this->animationIdx) {
        this->animationIdx = anim;
        Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.0f, startFrames,
                         Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE,
                         morphFrames);
    } else {
        Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.0f, startFrames,
                         Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE,
                         0.0f);
    }
}

void EnHorse_SetFollowAnimation(EnHorse* this, GlobalContext* globalCtx) {
    s32 anim = ENHORSE_ANIM_WALK;
    f32 distToPlayer = Actor_XZDistanceBetweenActors(&this->actor, &GET_PLAYER(globalCtx)->actor);

    if (distToPlayer > 400.0f) {
        anim = ENHORSE_ANIM_GALLOP;
    } else if (!(distToPlayer <= 300.0f) && (distToPlayer <= 400.0f)) {
        anim = ENHORSE_ANIM_TROT;
    }

    if (this->animationIdx == ENHORSE_ANIM_GALLOP) {
        if (distToPlayer > 400.0f) {
            anim = ENHORSE_ANIM_GALLOP;
        } else {
            anim = ENHORSE_ANIM_TROT;
        }
    } else if (this->animationIdx == ENHORSE_ANIM_TROT) {
        if (distToPlayer > 400.0f) {
            anim = ENHORSE_ANIM_GALLOP;
        } else if (distToPlayer < 300.0f) {
            anim = ENHORSE_ANIM_WALK;
        } else {
            anim = ENHORSE_ANIM_TROT;
        }
    } else if (this->animationIdx == ENHORSE_ANIM_WALK) {
        if (distToPlayer > 300.0f) {
            anim = ENHORSE_ANIM_TROT;
        } else {
            anim = ENHORSE_ANIM_WALK;
        }
    }

    EnHorse_StartMovingAnimation(this, anim, -3.0f, 0.0f);
}

void EnHorse_FollowPlayer(EnHorse* this, GlobalContext* globalCtx) {
    f32 distToPlayer;

    D_801BDAA4 = 0;
    distToPlayer = Actor_XZDistanceBetweenActors(&this->actor, &GET_PLAYER(globalCtx)->actor);

    if (((this->playerDir == PLAYER_DIR_BACK_R) || (this->playerDir == PLAYER_DIR_BACK_L)) && (distToPlayer > 300.0f) &&
        !(this->stateFlags & ENHORSE_TURNING_TO_PLAYER)) {
        f32 angleDiff;

        this->animationIdx = ENHORSE_ANIM_REARING;
        this->stateFlags |= ENHORSE_TURNING_TO_PLAYER;
        this->angleToPlayer = Actor_YawBetweenActors(&this->actor, &GET_PLAYER(globalCtx)->actor);

        angleDiff = (f32)this->angleToPlayer - this->actor.world.rot.y;
        if (angleDiff > 0x7FFF) {
            angleDiff -= 0x7FFF;
        } else if (angleDiff < -0x7FFF) {
            angleDiff += 0x7FFF;
        }

        this->followPlayerTurnSpeed =
            angleDiff / Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]);

        Animation_PlayOnce(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx]);
        this->skin.skelAnime.playSpeed = 1.0f;
        this->stateFlags &= ~ENHORSE_LAND2_SOUND;
    } else if (this->stateFlags & ENHORSE_TURNING_TO_PLAYER) {
        this->actor.world.rot.y += this->followPlayerTurnSpeed;
        this->actor.shape.rot.y = this->actor.world.rot.y;
        if ((this->curFrame > 25.0f) && !(this->stateFlags & ENHORSE_LAND2_SOUND)) {
            this->stateFlags |= ENHORSE_LAND2_SOUND;
            if (this->type == HORSE_2) {
                Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_LAND2);
            } else {
                Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_LAND2);
            }
        }
    } else {
        EnHorse_RotateToPlayer(this, globalCtx);
    }

    if (this->animationIdx == ENHORSE_ANIM_GALLOP) {
        this->actor.speedXZ = 8.0f;
        this->skin.skelAnime.playSpeed = this->actor.speedXZ * 0.3f;
    } else {
        if (this->animationIdx == ENHORSE_ANIM_TROT) {
            this->actor.speedXZ = 6.0f;
            this->skin.skelAnime.playSpeed = this->actor.speedXZ * 0.375f;
        } else if (this->animationIdx == ENHORSE_ANIM_WALK) {
            this->actor.speedXZ = 3.0f;
            EnHorse_PlayWalkingSound(this);
            this->skin.skelAnime.playSpeed = this->actor.speedXZ * 0.75f;
        } else {
            this->actor.speedXZ = 0.0f;
            this->skin.skelAnime.playSpeed = 1.0f;
        }
    }

    if (!(this->stateFlags & ENHORSE_TURNING_TO_PLAYER)) {
        this->followTimer++;
        if (this->followTimer > 300) {
            EnHorse_StartIdleRidable(this);
            if (this->stateFlags & ENHORSE_DRAW) {
                if (this->type == HORSE_2) {
                    Audio_PlaySfxAtPos(&this->unk_218, NA_SE_EV_KID_HORSE_NEIGH);
                } else {
                    Audio_PlaySfxAtPos(&this->unk_218, NA_SE_EV_HORSE_NEIGH);
                }
            }
        }
    }

    if (SkelAnime_Update(&this->skin.skelAnime)) {
        if (this->animationIdx == ENHORSE_ANIM_GALLOP) {
            func_8087C1C0(this);
        } else if (this->animationIdx == ENHORSE_ANIM_TROT) {
            func_8087C178(this);
        }

        this->stateFlags &= ~ENHORSE_TURNING_TO_PLAYER;

        if (distToPlayer < 100.0f) {
            EnHorse_StartIdleRidable(this);
        } else {
            EnHorse_SetFollowAnimation(this, globalCtx);
        }
    }
}

void EnHorse_InitIngoHorse(EnHorse* this) {
    this->curRaceWaypoint = 0;
    this->soundTimer = 0;
    this->actor.speedXZ = 0.0f;
    EnHorse_UpdateIngoHorseAnim(this);
    if (this->stateFlags & ENHORSE_DRAW) {
        Audio_PlaySfxAtPos(&this->unk_218, NA_SE_IT_INGO_HORSE_NEIGH);
    }
}

void EnHorse_SetIngoAnimation(s32 anim, f32 curFrame, s32 arg2, s16* animIdxOut) {
    *animIdxOut = sIngoAnimations[anim];
    if (arg2 == 1) {
        if (anim == 5) {
            *animIdxOut = 4;
        } else if (anim == 6) {
            *animIdxOut = 3;
        }
    }
}

void EnHorse_UpdateIngoHorseAnim(EnHorse* this) {
    s32 animChanged = false;
    f32 animSpeed;

    this->action = ENHORSE_ACT_INGO_RACE;
    this->stateFlags &= ~ENHORSE_SANDDUST_SOUND;

    if (this->actor.speedXZ == 0.0f) {
        if (this->animationIdx != ENHORSE_ANIM_IDLE) {
            animChanged = true;
        }
        this->animationIdx = ENHORSE_ANIM_IDLE;
    } else if (this->actor.speedXZ <= 3.0f) {
        if (this->animationIdx != ENHORSE_ANIM_WALK) {
            animChanged = true;
        }
        this->animationIdx = ENHORSE_ANIM_WALK;
    } else if (this->actor.speedXZ <= 6.0f) {
        if (this->animationIdx != ENHORSE_ANIM_TROT) {
            animChanged = true;
        }
        this->animationIdx = ENHORSE_ANIM_TROT;
    } else {
        if (this->animationIdx != ENHORSE_ANIM_GALLOP) {
            animChanged = true;
        }
        this->animationIdx = ENHORSE_ANIM_GALLOP;
    }

    if (this->animationIdx == ENHORSE_ANIM_WALK) {
        animSpeed = this->actor.speedXZ * 0.5f;
    } else if (this->animationIdx == ENHORSE_ANIM_TROT) {
        animSpeed = this->actor.speedXZ * 0.25f;
        if (this->type == HORSE_2) {
            Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_RUN);
        } else {
            Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_HORSE_RUN);
        }
    } else if (this->animationIdx == ENHORSE_ANIM_GALLOP) {
        animSpeed = this->actor.speedXZ * 0.2f;
        if (this->type == HORSE_2) {
            Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_RUN);
        } else {
            Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_HORSE_RUN);
        }
    } else {
        animSpeed = 1.0f;
    }

    if (animChanged == true) {
        Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx],
                         sPlaybackSpeeds[this->animationIdx] * animSpeed * 1.5f, 0.0f,
                         Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE,
                         -3.0f);
    } else {
        Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx],
                         sPlaybackSpeeds[this->animationIdx] * animSpeed * 1.5f, 0.0f,
                         Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE,
                         0.0f);
    }
}

void EnHorse_UpdateIngoRace(EnHorse* this, GlobalContext* globalCtx) {
    f32 playSpeed;

    if ((this->animationIdx == ENHORSE_ANIM_IDLE) || (this->animationIdx == ENHORSE_ANIM_WHINNEY)) {
        EnHorse_IdleAnimSounds(this, globalCtx);
    } else if (this->animationIdx == ENHORSE_ANIM_WALK) {
        EnHorse_PlayWalkingSound(this);
    }

    if (!this->inRace) {
        this->actor.speedXZ = 0.0f;
        this->rider->actor.speedXZ = 0.0f;
        if (this->animationIdx != ENHORSE_ANIM_IDLE) {
            EnHorse_UpdateIngoHorseAnim(this);
        }
    }

    if (this->animationIdx == ENHORSE_ANIM_WALK) {
        playSpeed = this->actor.speedXZ * 0.5f;
    } else if (this->animationIdx == 5) {
        playSpeed = this->actor.speedXZ * 0.25f;
    } else if (this->animationIdx == 6) {
        playSpeed = this->actor.speedXZ * 0.2f;
    } else {
        playSpeed = 1.0f;
    }
    this->skin.skelAnime.playSpeed = playSpeed;

    if (SkelAnime_Update(&this->skin.skelAnime) ||
        ((this->animationIdx == ENHORSE_ANIM_IDLE) && (this->actor.speedXZ != 0.0f))) {
        EnHorse_UpdateIngoHorseAnim(this);
    }
}

void func_8088126C(EnHorse* this, GlobalContext* globalCtx) {
    this->skin.skelAnime.curFrame = 0.0f;
    func_80881290(this, globalCtx);
}

void func_80881290(EnHorse* this, GlobalContext* globalCtx) {
    f32 curFrame;

    this->action = ENHORSE_ACT_MOUNTED_IDLE_WHINNEYING;
    this->animationIdx = ENHORSE_ANIM_HIGH_JUMP;
    curFrame = this->skin.skelAnime.curFrame;
    Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.5f, curFrame,
                     Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE, -3.0f);
    this->postDrawFunc = NULL;
    this->actor.gravity = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->jumpStartY = this->actor.world.pos.y;
    if (this->type == HORSE_2) {
        Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_HORSE_JUMP);
    } else {
        Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_HORSE_JUMP);
    }
    func_8013ECE0(0.0f, 170, 10, 10);
}

void func_80881398(EnHorse* this, GlobalContext* globalCtx) {
    Vec3s* jointTable;
    f32 y;
    s32 animeUpdated;
    f32 curFrame;

    this->stateFlags |= ENHORSE_JUMPING;
    if (this->actor.speedXZ < 14.0f) {
        this->actor.speedXZ = 14.0f;
    }

    animeUpdated = SkelAnime_Update(&this->skin.skelAnime);
    curFrame = this->skin.skelAnime.curFrame;

    if (curFrame > 23.0f) {
        this->actor.gravity = -3.5f;
        if (this->actor.velocity.y == 0.0f) {
            this->actor.velocity.y = -10.5f;
        }
        if (this->actor.world.pos.y < (this->actor.floorHeight + 90.0f)) {
            this->skin.skelAnime.playSpeed = 1.5f;
        } else {
            this->skin.skelAnime.playSpeed = 0.0f;
        }
    } else {
        jointTable = this->skin.skelAnime.jointTable;
        y = jointTable->y;
        this->actor.world.pos.y = this->jumpStartY + (y * 0.01f * this->unk_528 * 0.01f);
    }

    if (animeUpdated || ((curFrame > 17.0f) &&
                         (this->actor.world.pos.y < ((this->actor.floorHeight - this->actor.velocity.y) + 80.0f)))) {
        if (this->type == HORSE_2) {
            Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_HORSE_LAND);
        } else {
            Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_HORSE_LAND);
        }
        func_8013ECE0(0.0f, 255, 10, 80);
        this->stateFlags &= ~ENHORSE_JUMPING;
        this->stateFlags &= ~ENHORSE_FLAG_30;
        this->actor.gravity = -3.5f;
        this->actor.world.pos.y = this->actor.floorHeight;
        func_800B1598(globalCtx, 25.0f, &this->actor.world.pos);
        func_8088159C(this, globalCtx);
    }
}

void func_8088159C(EnHorse* this, GlobalContext* globalCtx) {
    Vec3s* jointTable;
    f32 y;

    this->action = ENHORSE_ACT_MOUNTED_IDLE;
    this->animationIdx = ENHORSE_ANIM_GALLOP;
    Animation_PlayOnce(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx]);
    jointTable = this->skin.skelAnime.jointTable;
    y = jointTable->y;
    this->riderPos.y += y * 0.01f * this->unk_528 * 0.01f;
    this->postDrawFunc = NULL;
}

void func_80881634(EnHorse* this) {
    this->curRaceWaypoint = 0;
    this->soundTimer = 0;
    this->actor.speedXZ = 0.0f;
    func_8088168C(this);
    if (this->stateFlags & ENHORSE_DRAW) {
        Audio_PlaySfxAtPos(&this->unk_218, NA_SE_IT_INGO_HORSE_NEIGH);
    }
}

void func_8088168C(EnHorse* this) {
    s32 animChanged = false;
    f32 animSpeed;
    f32 finalAnimSpeed;

    this->action = ENHORSE_ACT_MOUNTED_IDLE;
    this->stateFlags &= ~ENHORSE_SANDDUST_SOUND;

    if (this->actor.speedXZ == 0.0f) {
        if (this->animationIdx != ENHORSE_ANIM_IDLE) {
            animChanged = true;
        }
        this->animationIdx = ENHORSE_ANIM_IDLE;
    } else if (this->actor.speedXZ <= 3.0f) {
        if (this->animationIdx != ENHORSE_ANIM_WALK) {
            animChanged = true;
        }
        this->animationIdx = ENHORSE_ANIM_WALK;
    } else if (this->actor.speedXZ <= 6.0f) {
        if (this->animationIdx != ENHORSE_ANIM_TROT) {
            animChanged = true;
        }
        this->animationIdx = ENHORSE_ANIM_TROT;
    } else {
        if (this->animationIdx != ENHORSE_ANIM_GALLOP) {
            animChanged = true;
        }
        this->animationIdx = ENHORSE_ANIM_GALLOP;
    }

    if (this->animationIdx == ENHORSE_ANIM_WALK) {
        animSpeed = this->actor.speedXZ * 0.5f;
    } else if (this->animationIdx == ENHORSE_ANIM_TROT) {
        animSpeed = this->actor.speedXZ * 0.25f;
        if (this->type == HORSE_2) {
            Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_RUN);
        } else {
            Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_HORSE_RUN);
        }
    } else if (this->animationIdx == ENHORSE_ANIM_GALLOP) {
        animSpeed = this->actor.speedXZ * 0.2f;
        if (this->type == HORSE_2) {
            Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_RUN);
        } else {
            Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_HORSE_RUN);
        }
    } else {
        animSpeed = 1.0f;
    }

    finalAnimSpeed = sPlaybackSpeeds[this->animationIdx] * animSpeed * 1.5f;
    if (finalAnimSpeed < 1.0f) {
        finalAnimSpeed = 1.0f;
    }

    if (animChanged == true) {
        Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], finalAnimSpeed, 0.0f,
                         Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE,
                         -3.0f);
    } else {
        Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], finalAnimSpeed, 0.0f,
                         Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE,
                         0.0f);
    }
}

void func_808819D8(EnHorse* this, GlobalContext* globalCtx) {
    Path* path;
    f32 animSpeed;

    if ((this->animationIdx == ENHORSE_ANIM_IDLE) || (this->animationIdx == ENHORSE_ANIM_WHINNEY)) {
        EnHorse_IdleAnimSounds(this, globalCtx);
    } else if (this->animationIdx == ENHORSE_ANIM_WALK) {
        EnHorse_PlayWalkingSound(this);
    }

    if (!this->inRace) {
        this->actor.speedXZ = 0.0f;
        this->rider->actor.speedXZ = 0.0f;
        if (this->animationIdx != ENHORSE_ANIM_IDLE) {
            EnHorse_UpdateIngoHorseAnim(this);
        }
    }

    if (this->actor.params == ENHORSE_4) {
        path = &globalCtx->setupPathList[0];
        func_8087B7C0(this, globalCtx, path);
    } else if (this->actor.params == ENHORSE_5) {
        path = &globalCtx->setupPathList[1];
        func_8087B7C0(this, globalCtx, path);
    }

    if (!this->inRace) {
        this->actor.speedXZ = 0.0f;
        if (this->animationIdx != ENHORSE_ANIM_IDLE) {
            func_8088168C(this);
        }
    }

    if (this->animationIdx == ENHORSE_ANIM_WALK) {
        animSpeed = this->actor.speedXZ * 0.5f;
    } else if (this->animationIdx == ENHORSE_ANIM_TROT) {
        animSpeed = this->actor.speedXZ * 0.25f;
    } else if (this->animationIdx == ENHORSE_ANIM_GALLOP) {
        animSpeed = this->actor.speedXZ * 0.2f;
    } else {
        animSpeed = 1.0f;
    }
    this->skin.skelAnime.playSpeed = animSpeed;

    if (SkelAnime_Update(&this->skin.skelAnime) ||
        ((this->animationIdx == ENHORSE_ANIM_IDLE) && (this->actor.speedXZ != 0.0f))) {
        func_8088168C(this);
    }

    if ((gSaveContext.save.weekEventReg[92] & (1 | 2 | 4)) == 3) {
        this->rider->unk488 = 7;
    } else {
        EnHorse_SetIngoAnimation(this->animationIdx, this->skin.skelAnime.curFrame, this->unk_394 & 1,
                                 &this->rider->unk488);
    }
}

void EnHorse_CsMoveInit(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    this->animationIdx = ENHORSE_ANIM_GALLOP;
    this->cutsceneAction = 1;
    Animation_PlayOnceSetSpeed(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx],
                               this->actor.speedXZ * 0.2f * 1.5f);
}

void EnHorse_CsMoveToPoint(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    Vec3f endPos;
    s32 pad;

    endPos.x = action->endPos.x;
    endPos.y = action->endPos.y;
    endPos.z = action->endPos.z;

    if (Math3D_Distance(&endPos, &this->actor.world.pos) > 8.0f) {
        EnHorse_RotateToPoint(this, globalCtx, &endPos, 0x320);
        this->actor.speedXZ = 8.0f;
        this->skin.skelAnime.playSpeed = this->actor.speedXZ * 0.3f;
    } else {
        this->actor.world.pos = endPos;
        this->actor.speedXZ = 0.0f;
    }

    if (SkelAnime_Update(&this->skin.skelAnime)) {
        func_8087C1C0(this);
        func_8013ECE0(0.0f, 120, 8, 255);
        Animation_PlayOnceSetSpeed(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx],
                                   this->actor.speedXZ * 0.3f);
    }
}

void EnHorse_CsSetAnimHighJump(EnHorse* this, GlobalContext* globalCtx) {
    this->skin.skelAnime.curFrame = 0.0f;
    EnHorse_CsPlayHighJumpAnim(this, globalCtx);
}

void EnHorse_CsPlayHighJumpAnim(EnHorse* this, GlobalContext* globalCtx) {
    f32 curFrame;
    f32 y;
    Vec3s* jointTable;

    this->animationIdx = ENHORSE_ANIM_HIGH_JUMP;
    curFrame = this->skin.skelAnime.curFrame;
    Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.5f, curFrame,
                     Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE, -3.0f);
    this->postDrawFunc = NULL;
    this->jumpStartY = this->actor.world.pos.y;
    this->actor.gravity = 0.0f;
    this->actor.velocity.y = 0.0f;

    jointTable = this->skin.skelAnime.jointTable;
    y = jointTable->y;
    this->riderPos.y -= y * 0.01f * this->unk_528 * 0.01f;

    this->stateFlags |= ENHORSE_ANIM_HIGH_JUMP;
    if (this->type == HORSE_2) {
        Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_HORSE_JUMP);
    } else {
        Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_HORSE_JUMP);
    }
    func_8013ECE0(0.0f, 170, 10, 10);
}

void EnHorse_CsJumpInit(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    EnHorse_CsSetAnimHighJump(this, globalCtx);
    this->cutsceneAction = 2;
    this->cutsceneFlags &= ~1;
}

void EnHorse_CsJump(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    f32 curFrame;
    f32 y;
    Vec3s* jointTable;
    s32 pad[2];

    if (this->cutsceneFlags & 1) {
        EnHorse_CsMoveToPoint(this, globalCtx, action);
        return;
    }

    curFrame = this->skin.skelAnime.curFrame;
    this->actor.speedXZ = 13.0f;
    this->stateFlags |= ENHORSE_JUMPING;

    if (curFrame > 19.0f) {
        this->actor.gravity = -3.5f;
        if (this->actor.velocity.y == 0.0f) {
            this->actor.velocity.y = -10.5f;
        }
        if (this->actor.world.pos.y < (this->actor.floorHeight + 90.0f)) {
            this->skin.skelAnime.playSpeed = 1.5f;
        } else {
            this->skin.skelAnime.playSpeed = 0.0f;
        }
    } else {
        jointTable = this->skin.skelAnime.jointTable;
        y = jointTable->y;

        this->actor.world.pos.y = this->jumpStartY + (y * 0.01f * this->unk_528 * 0.01f);
    }

    if (SkelAnime_Update(&this->skin.skelAnime) ||
        ((curFrame > 19.0f) &&
         (this->actor.world.pos.y < ((this->actor.floorHeight - this->actor.velocity.y) + 80.0f)))) {
        this->cutsceneFlags |= 1;
        if (this->type == HORSE_2) {
            Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_HORSE_LAND);
        } else {
            Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_HORSE_LAND);
        }
        func_8013ECE0(0.0f, 255, 10, 80);
        this->stateFlags &= ~ENHORSE_JUMPING;
        this->actor.gravity = -3.5f;
        this->actor.velocity.y = 0.0f;
        this->actor.world.pos.y = this->actor.floorHeight;
        func_800B1598(globalCtx, 25.0f, &this->actor.world.pos);
        this->animationIdx = ENHORSE_ANIM_GALLOP;
        Animation_PlayOnceSetSpeed(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx],
                                   sPlaybackSpeeds[6]);

        jointTable = this->skin.skelAnime.jointTable;
        y = jointTable->y;
        this->riderPos.y += y * 0.01f * this->unk_528 * 0.01f;

        this->postDrawFunc = NULL;
    }
}

void EnHorse_CsRearingInit(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    this->animationIdx = ENHORSE_ANIM_REARING;
    this->cutsceneAction = 3;
    this->cutsceneFlags &= ~4;
    this->stateFlags &= ~ENHORSE_LAND2_SOUND;
    if (this->stateFlags & ENHORSE_DRAW) {
        if (this->type == HORSE_2) {
            Audio_PlaySfxAtPos(&this->unk_218, NA_SE_EV_KID_HORSE_NEIGH);
        } else {
            Audio_PlaySfxAtPos(&this->unk_218, NA_SE_EV_HORSE_NEIGH);
        }
    }
    Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.0f, 0.0f,
                     Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE, -3.0f);
}

void EnHorse_CsRearing(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    this->actor.speedXZ = 0.0f;
    if (this->curFrame > 25.0f) {
        if (!(this->stateFlags & ENHORSE_LAND2_SOUND)) {
            this->stateFlags |= ENHORSE_LAND2_SOUND;
            if (this->type == HORSE_2) {
                Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_LAND2);
            } else {
                Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_LAND2);
            }
        }
    }

    if (SkelAnime_Update(&this->skin.skelAnime)) {
        this->animationIdx = ENHORSE_ANIM_IDLE;
        if (!(this->cutsceneFlags & 4)) {
            this->cutsceneFlags |= 4;
            Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.0f, 0.0f,
                             Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE,
                             -3.0f);
        } else {
            Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.0f, 0.0f,
                             Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_LOOP,
                             0.0f);
        }
    }
}

void EnHorse_WarpMoveInit(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    this->actor.world.pos.x = action->startPos.x;
    this->actor.world.pos.y = action->startPos.y;
    this->actor.world.pos.z = action->startPos.z;
    this->actor.prevPos = this->actor.world.pos;

    this->actor.world.rot.y = action->urot.y;
    this->actor.shape.rot = this->actor.world.rot;

    this->animationIdx = ENHORSE_ANIM_GALLOP;
    this->cutsceneAction = 4;
    Animation_PlayOnceSetSpeed(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx],
                               this->actor.speedXZ * 0.3f);
}

void EnHorse_CsWarpMoveToPoint(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    Vec3f endPos;
    s32 pad;

    endPos.x = action->endPos.x;
    endPos.y = action->endPos.y;
    endPos.z = action->endPos.z;

    if (Math3D_Distance(&endPos, &this->actor.world.pos) > 8.0f) {
        EnHorse_RotateToPoint(this, globalCtx, &endPos, 0x320);
        this->actor.speedXZ = 8.0f;
        this->skin.skelAnime.playSpeed = this->actor.speedXZ * 0.3f;
    } else {
        this->actor.world.pos = endPos;
        this->actor.speedXZ = 0.0f;
    }

    if (SkelAnime_Update(&this->skin.skelAnime)) {
        func_8087C1C0(this);
        func_8013ECE0(0.0f, 120, 8, 255);
        Animation_PlayOnceSetSpeed(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx],
                                   this->actor.speedXZ * 0.3f);
    }
}

void EnHorse_CsWarpRearingInit(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    this->actor.world.pos.x = action->startPos.x;
    this->actor.world.pos.y = action->startPos.y;
    this->actor.world.pos.z = action->startPos.z;
    this->actor.prevPos = this->actor.world.pos;

    this->actor.world.rot.y = action->urot.y;
    this->actor.shape.rot = this->actor.world.rot;

    this->animationIdx = ENHORSE_ANIM_REARING;
    this->cutsceneAction = 5;
    this->cutsceneFlags &= ~4;
    this->stateFlags &= ~ENHORSE_LAND2_SOUND;

    if (this->stateFlags & ENHORSE_DRAW) {
        if (this->type == HORSE_2) {
            Audio_PlaySfxAtPos(&this->unk_218, NA_SE_EV_KID_HORSE_NEIGH);
        } else {
            Audio_PlaySfxAtPos(&this->unk_218, NA_SE_EV_HORSE_NEIGH);
        }
    }
    Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.0f, 0.0f,
                     Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE, -3.0f);
}

void EnHorse_CsWarpRearing(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    this->actor.speedXZ = 0.0f;
    if (this->curFrame > 25.0f) {
        if (!(this->stateFlags & ENHORSE_LAND2_SOUND)) {
            this->stateFlags |= ENHORSE_LAND2_SOUND;
            if (this->type == HORSE_2) {
                Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_LAND2);
            } else {
                Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_LAND2);
            }
        }
    }

    if (SkelAnime_Update(&this->skin.skelAnime)) {
        this->animationIdx = ENHORSE_ANIM_IDLE;
        if (!(this->cutsceneFlags & 4)) {
            this->cutsceneFlags |= 4;
            Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.0f, 0.0f,
                             Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE,
                             -3.0f);
        } else {
            Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.0f, 0.0f,
                             Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_LOOP,
                             0.0f);
        }
    }
}

void EnHorse_InitCutscene(EnHorse* this, GlobalContext* globalCtx) {
    this->playerControlled = false;
    this->action = ENHORSE_ACT_HBA;
    this->cutsceneAction = 0;
    this->actor.speedXZ = 0.0f;
}

s32 EnHorse_GetCutsceneFunctionIndex(s32 csAction) {
    s32 numActions = ARRAY_COUNT(sCsActionTable); // prevents unrolling
    s32 i;

    for (i = 0; i < numActions; i++) {
        if (csAction == sCsActionTable[i].csAction) {
            return sCsActionTable[i].csFuncIdx;
        }

        if (csAction < sCsActionTable[i].csAction) {
            return 0;
        }
    }
    return 0;
}

void EnHorse_CutsceneUpdate(EnHorse* this, GlobalContext* globalCtx) {
    s32 csFunctionIdx;
    CsCmdActorAction* playerAction = globalCtx->csCtx.playerAction;

    if (globalCtx->csCtx.state == 3) {
        this->playerControlled = true;
        this->actor.params = ENHORSE_12;
        this->action = ENHORSE_ACT_IDLE;
        EnHorse_Freeze(this, globalCtx);
        return;
    }

    if (playerAction != NULL) {
        csFunctionIdx = EnHorse_GetCutsceneFunctionIndex(playerAction->action);
        if (csFunctionIdx != 0) {
            if (csFunctionIdx != this->cutsceneAction) {
                if (this->cutsceneAction == 0) {
                    this->actor.world.pos.x = playerAction->startPos.x;
                    this->actor.world.pos.y = playerAction->startPos.y;
                    this->actor.world.pos.z = playerAction->startPos.z;

                    this->actor.world.rot.y = playerAction->urot.y;
                    this->actor.shape.rot = this->actor.world.rot;
                    this->actor.prevPos = this->actor.world.pos;
                }
                this->cutsceneAction = csFunctionIdx;
                sCutsceneInitFuncs[csFunctionIdx](this, globalCtx, playerAction);
            }
            sCutsceneActionFuncs[this->cutsceneAction](this, globalCtx, playerAction);
        }
    }
}

s32 EnHorse_UpdateHbaRaceInfo(EnHorse* this, GlobalContext* globalCtx, RaceInfo* raceInfo) {
    Vec3f pos;
    f32 px;
    f32 pz;
    f32 d;

    EnHorse_RaceWaypointPos(raceInfo->waypoints, this->curRaceWaypoint, &pos);
    func_8017B7F8(&pos, raceInfo->waypoints[this->curRaceWaypoint].angle, &px, &pz, &d);

    if ((this->curRaceWaypoint >= (raceInfo->numWaypoints - 1)) &&
        (Math3D_Distance(&pos, &this->actor.world.pos) < DREG(8))) {
        this->hbaFlags |= 2;
    }

    if (((this->actor.world.pos.x * px) + (pz * this->actor.world.pos.z) + d) > 0.0f) {
        this->curRaceWaypoint++;
        if (this->curRaceWaypoint >= raceInfo->numWaypoints) {
            this->hbaFlags |= 1;
            return true;
        }
    }

    if (!(this->hbaFlags & 1)) {
        EnHorse_RotateToPoint(this, globalCtx, &pos, 0x640);
    }

    this->actor.shape.rot.y = this->actor.world.rot.y;
    if ((this->actor.speedXZ < raceInfo->waypoints[this->curRaceWaypoint].speed) && !(this->hbaFlags & 1)) {
        this->actor.speedXZ += 0.4f;
    } else {
        this->actor.speedXZ -= 0.4f;
        if (this->actor.speedXZ < 0.0f) {
            this->actor.speedXZ = 0.0f;
        }
    }
    return false;
}

void EnHorse_InitHorsebackArchery(EnHorse* this) {
    this->hbaStarted = 0;
    this->soundTimer = 0;
    this->curRaceWaypoint = 0;
    this->hbaTimer = 0;
    this->actor.speedXZ = 0.0f;
    EnHorse_UpdateHbaAnim(this);
}

void EnHorse_UpdateHbaAnim(EnHorse* this) {
    s32 animChanged = false;
    f32 animSpeed;

    this->action = ENHORSE_ACT_FLEE_PLAYER;
    if (this->actor.speedXZ == 0.0f) {
        if (this->animationIdx != ENHORSE_ANIM_IDLE) {
            animChanged = true;
        }
        this->animationIdx = ENHORSE_ANIM_IDLE;
    } else if (this->actor.speedXZ <= 3.0f) {
        if (this->animationIdx != ENHORSE_ANIM_WALK) {
            animChanged = true;
        }
        this->animationIdx = ENHORSE_ANIM_WALK;
    } else if (this->actor.speedXZ <= 6.0f) {
        if (this->animationIdx != ENHORSE_ANIM_TROT) {
            animChanged = true;
        }
        this->animationIdx = ENHORSE_ANIM_TROT;
    } else {
        if (this->animationIdx != ENHORSE_ANIM_GALLOP) {
            animChanged = true;
        }
        this->animationIdx = ENHORSE_ANIM_GALLOP;
    }

    if (this->animationIdx == ENHORSE_ANIM_WALK) {
        animSpeed = this->actor.speedXZ * 0.5f;
    } else if (this->animationIdx == ENHORSE_ANIM_TROT) {
        animSpeed = this->actor.speedXZ * 0.25f;
        if (this->type == HORSE_2) {
            Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_RUN);
        } else {
            Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_HORSE_RUN);
        }
        func_8013ECE0(0.0f, 60, 8, 255);
    } else if (this->animationIdx == ENHORSE_ANIM_GALLOP) {
        animSpeed = this->actor.speedXZ * 0.2f;
        if (this->type == HORSE_2) {
            Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_RUN);
        } else {
            Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_HORSE_RUN);
        }
        func_8013ECE0(0.0f, 120, 8, 255);
    } else {
        animSpeed = 1.0f;
    }

    if (animChanged == true) {
        Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx],
                         sPlaybackSpeeds[this->animationIdx] * animSpeed * 1.5f, 0.0f,
                         Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE,
                         -3.0f);
    } else {
        Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx],
                         sPlaybackSpeeds[this->animationIdx] * animSpeed * 1.5f, 0.0f,
                         Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE,
                         0.0f);
    }
}

void EnHorse_UpdateHorsebackArchery(EnHorse* this, GlobalContext* globalCtx) {
    f32 playSpeed;
    s32 sp28;

    if (this->animationIdx == ENHORSE_ANIM_WALK) {
        EnHorse_PlayWalkingSound(this);
    }

    if (globalCtx->interfaceCtx.hbaAmmo == 0) {
        this->hbaTimer++;
    }

    sp28 = Audio_IsSequencePlaying(0x41);
    EnHorse_UpdateHbaRaceInfo(this, globalCtx, &sHbaInfo);

    if (((this->hbaFlags & 1) || (this->hbaTimer > 45)) && (sp28 != 1) && (gSaveContext.minigameState != 3)) {
        gSaveContext.save.cutscene = 0;
        globalCtx->sceneLoadFlag = 0x14;
        globalCtx->unk_1887F = 0x40;
    }

    if (globalCtx->interfaceCtx.hbaAmmo) {}

    if (((globalCtx->interfaceCtx.hbaAmmo == 0) || (this->hbaFlags & 2)) && (this->hbaFlags & 4)) {
        this->hbaFlags &= ~4;
        Audio_QueueSeqCmd(0x8041);
    }

    if (this->hbaStarted == 0) {
        this->actor.speedXZ = 0.0f;
        if (this->animationIdx != ENHORSE_ANIM_IDLE) {
            EnHorse_UpdateHbaAnim(this);
        }
    }

    if (this->animationIdx == ENHORSE_ANIM_WALK) {
        playSpeed = this->actor.speedXZ * 0.5f;
    } else if (this->animationIdx == ENHORSE_ANIM_TROT) {
        playSpeed = this->actor.speedXZ * 0.25f;
    } else if (this->animationIdx == ENHORSE_ANIM_GALLOP) {
        playSpeed = this->actor.speedXZ * 0.2f;
    } else {
        playSpeed = 1.0f;
    }
    this->skin.skelAnime.playSpeed = playSpeed;

    if (SkelAnime_Update(&this->skin.skelAnime) ||
        ((this->animationIdx == ENHORSE_ANIM_IDLE) && (this->actor.speedXZ != 0.0f))) {
        EnHorse_UpdateHbaAnim(this);
    }
}

#ifdef NON_MATCHING
void EnHorse_FleePlayer(EnHorse* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    f32 distToHome;
    f32 playerDistToHome;
    f32 distToPlayer;
    s32 nextAnim;
    s32 animFinished;
    s16 yaw;

    if ((D_801BDAA4 != 0) || (this->type == HORSE_HNI)) {
        EnHorse_StartIdleRidable(this);
        if (this->type == HORSE_2) {
            Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_NEIGH);
        } else {
            Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_HORSE_NEIGH);
        }
    }

    distToHome = Math3D_Distance(&this->actor.home.pos, &this->actor.world.pos);
    playerDistToHome = Math3D_Distance(&player->actor.world.pos, &this->actor.home.pos);
    distToPlayer = Math3D_Distance(&player->actor.world.pos, &this->actor.world.pos);

    if (playerDistToHome > 300.0f) {
        if (distToHome > 150.0f) {
            this->actor.speedXZ += 0.4f;
            if (this->actor.speedXZ > 8.0f) {
                this->actor.speedXZ = 8.0f;
            }
        } else {
            this->actor.speedXZ -= 0.5f;
            if (this->actor.speedXZ < 0.0f) {
                this->actor.speedXZ = 0.0f;
            }
        }
    } else if (distToPlayer < 300.0f) {
        this->actor.speedXZ += 0.4f;
        if (this->actor.speedXZ > 8.0f) {
            this->actor.speedXZ = 8.0f;
        }
    } else {
        this->actor.speedXZ -= 0.5f;
        if (this->actor.speedXZ < 0.0f) {
            this->actor.speedXZ = 0.0f;
        }
    }

    if (this->actor.speedXZ >= 6.0f) {
        this->skin.skelAnime.playSpeed = this->actor.speedXZ * 0.3f;
        nextAnim = ENHORSE_ANIM_GALLOP;
    } else if (this->actor.speedXZ >= 3.0f) {
        this->skin.skelAnime.playSpeed = this->actor.speedXZ * 0.375f;
        nextAnim = ENHORSE_ANIM_TROT;
    } else if (this->actor.speedXZ > 0.1f) {
        this->skin.skelAnime.playSpeed = this->actor.speedXZ * 0.75f;
        nextAnim = ENHORSE_ANIM_WALK;
        EnHorse_PlayWalkingSound(this);
    } else {
        if (Rand_ZeroOne() > 0.5f) {
            nextAnim = ENHORSE_ANIM_WHINNEY;
        } else {
            nextAnim = ENHORSE_ANIM_IDLE;
        }
        EnHorse_IdleAnimSounds(this, globalCtx);
        this->skin.skelAnime.playSpeed = 1.0f;
    }

    if ((nextAnim == ENHORSE_ANIM_GALLOP) || (nextAnim == ENHORSE_ANIM_TROT) || (nextAnim == ENHORSE_ANIM_WALK)) {
        if (playerDistToHome < 300.0f) {
            yaw = player->actor.shape.rot.y;
            yaw += ((Actor_YawBetweenActors(&this->actor, &player->actor) > 0) ? 1 : -1) * 0x3FFF;
        } else {
            yaw = Math_Vec3f_Yaw(&this->actor.world.pos, &this->actor.home.pos) - this->actor.world.rot.y;
        }

        if (yaw > 800.0f) {
            this->actor.world.rot.y += 0x320;
        } else if (yaw < -800.0f) {
            this->actor.world.rot.y += -0x320;
        } else {
            this->actor.world.rot.y += yaw;
        }
        this->actor.shape.rot.y = this->actor.world.rot.y;
    }

    animFinished = SkelAnime_Update(&this->skin.skelAnime);

    if (((this->animationIdx == ENHORSE_ANIM_IDLE) || (this->animationIdx == ENHORSE_ANIM_WHINNEY)) &&
        ((nextAnim == ENHORSE_ANIM_GALLOP) || (nextAnim == ENHORSE_ANIM_TROT) || (nextAnim == ENHORSE_ANIM_WALK))) {
        this->animationIdx = nextAnim;
        Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.0f, 0.0f,
                         Animation_GetLastFrame(sAnimationHeaders[this->type][nextAnim]), ANIMMODE_ONCE, -3.0f);
        if (this->animationIdx == ENHORSE_ANIM_GALLOP) {
            func_8087C1C0(this);
        } else if (this->animationIdx == ENHORSE_ANIM_TROT) {
            func_8087C178(this);
        }
    } else if (animFinished) {
        if (nextAnim == ENHORSE_ANIM_GALLOP) {
            func_8087C1C0(this);
        } else if (nextAnim == ENHORSE_ANIM_TROT) {
            func_8087C178(this);
        }

        if ((this->animationIdx == ENHORSE_ANIM_IDLE) || (this->animationIdx == ENHORSE_ANIM_WHINNEY)) {
            if (nextAnim != this->animationIdx) {
                this->animationIdx = nextAnim;
                Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.0f, 0.0f,
                                 Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]),
                                 ANIMMODE_ONCE, -3.0f);
            } else {
                if (Rand_ZeroOne() > 0.5f) {
                    this->animationIdx = ENHORSE_ANIM_IDLE;
                    this->stateFlags &= ~ENHORSE_SANDDUST_SOUND;
                } else {
                    this->animationIdx = ENHORSE_ANIM_WHINNEY;
                    if (this->stateFlags & ENHORSE_DRAW) {
                        if (this->type == HORSE_2) {
                            Audio_PlaySfxAtPos(&this->unk_218, NA_SE_EV_KID_HORSE_GROAN);
                        } else {
                            Audio_PlaySfxAtPos(&this->unk_218, NA_SE_EV_HORSE_GROAN);
                        }
                    }
                }
                Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.0f, 0.0f,
                                 Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]),
                                 ANIMMODE_ONCE, -3.0f);
            }
        } else if (nextAnim != this->animationIdx) {
            this->animationIdx = nextAnim;
            Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.0f, 0.0f,
                             Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE,
                             -3.0f);
        } else {
            Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.0f, 0.0f,
                             Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE,
                             0.0f);
        }
    } else if ((this->animationIdx == ENHORSE_ANIM_WALK) &&
               ((nextAnim == ENHORSE_ANIM_IDLE) || (nextAnim == ENHORSE_ANIM_WHINNEY))) {
        this->animationIdx = nextAnim;
        Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.0f, 0.0f,
                         Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE,
                         -3.0f);
    }
}
#else
void EnHorse_FleePlayer(EnHorse* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/EnHorse_FleePlayer.s")
#endif

void func_80883B70(EnHorse* this, CsCmdActorAction* action) {
    this->actor.world.pos.x = action->startPos.x;
    this->actor.world.pos.y = action->startPos.y;
    this->actor.world.pos.z = action->startPos.z;

    this->actor.world.rot.y = action->urot.y;
    this->actor.shape.rot = this->actor.world.rot;

    this->actor.prevPos = this->actor.world.pos;
}

void func_80883BEC(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    func_80883B70(this, action);
    this->animationIdx = ENHORSE_ANIM_IDLE;
    this->unk_3E0 = 1;
    this->stateFlags &= ~ENHORSE_SANDDUST_SOUND;
    Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.0f, 0.0f,
                     Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE, 0.0f);
    this->stateFlags |= ENHORSE_SANDDUST_SOUND;
}

void func_80883CB0(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    EnHorse_IdleAnimSounds(this, globalCtx);
    if (SkelAnime_Update(&this->skin.skelAnime)) {
        this->animationIdx = ENHORSE_ANIM_IDLE;
        Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.0f, 0.0f,
                         Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE,
                         0.0f);
    }
}

void func_80883D64(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    func_80883B70(this, action);
    this->unk_3E0 = 2;
    Animation_Change(&this->skin.skelAnime, &object_horse_link_child_Anim_00A8DC, 0.0f, 0.0f,
                     Animation_GetLastFrame(&object_horse_link_child_Anim_00A8DC), ANIMMODE_ONCE, 0.0f);
}

void func_80883DE0(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    SkelAnime_Update(&this->skin.skelAnime);
}

void func_80883E10(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    func_80883B70(this, action);
    this->unk_3E0 = 3;
    Animation_Change(&this->skin.skelAnime, &object_horse_link_child_Anim_00A8DC, 1.0f, 0.0f,
                     Animation_GetLastFrame(&object_horse_link_child_Anim_00A8DC), ANIMMODE_ONCE, -3.0f);
    Audio_PlaySfxAtPos(&this->unk_218, NA_SE_EV_KID_HORSE_NEIGH);
}

void func_80883EA0(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    if (SkelAnime_Update(&this->skin.skelAnime)) {
        Animation_Change(&this->skin.skelAnime, &object_horse_link_child_Anim_00B3E0, 1.0f, 11.0f,
                         Animation_GetLastFrame(&object_horse_link_child_Anim_00B3E0), ANIMMODE_ONCE, 0.0f);
    }
}

void func_80883F18(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    func_80883B70(this, action);
    this->unk_3E0 = 4;
    Animation_Change(&this->skin.skelAnime, &object_horse_link_child_Anim_00AD08, 1.0f, 0.0f,
                     Animation_GetLastFrame(&object_horse_link_child_Anim_00AD08), ANIMMODE_ONCE, -3.0f);
}

void func_80883F98(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    if (Animation_OnFrame(&this->skin.skelAnime, Animation_GetLastFrame(&object_horse_link_child_Anim_00AD08) - 1.0f)) {
        Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_LAND2);
    }
    SkelAnime_Update(&this->skin.skelAnime);
}

void func_80884010(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    func_80883B70(this, action);
    this->unk_3E0 = 5;
    this->animationIdx = ENHORSE_ANIM_WALK;
    Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.0f, 0.0f,
                     Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE, -3.0f);
}

void func_808840C4(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    EnHorse_PlayWalkingSound(this);
    Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx, this->unk_530);
    if (SkelAnime_Update(&this->skin.skelAnime)) {
        Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.0f, 0.0f,
                         Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE,
                         0.0f);
    }
}

void func_80884194(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    func_80883B70(this, action);
    this->unk_3E0 = 6;
    this->animationIdx = ENHORSE_ANIM_GALLOP;
    Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.0f, 0.0f,
                     Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE, -3.0f);
    func_8087C1C0(this);
}

void func_8088424C(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx, this->unk_530);
    if (SkelAnime_Update(&this->skin.skelAnime)) {
        Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 1.0f, 0.0f,
                         Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE,
                         0.0f);
        func_8087C1C0(this);
    }
}

void func_80884314(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 20.0f);
    func_80883B70(this, action);
    this->unk_3E0 = 7;
    Animation_Change(&this->skin.skelAnime, &object_horse_link_child_Anim_00D178, 1.0f, 0.0f,
                     Animation_GetLastFrame(&object_horse_link_child_Anim_00D178), ANIMMODE_ONCE, 0.0f);
    Audio_PlaySfxAtPos(&this->unk_218, NA_SE_EV_KID_HORSE_NEIGH);
}

void func_808843B4(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    SkelAnime_Update(&this->skin.skelAnime);
    if (this->curFrame > 42.0f) {
        if (((s32)this->curFrame % 11) == 0) {
            func_8087C1C0(this);
        }
        Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx, this->unk_530);
    }
}

void func_80884444(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 20.0f);
    func_80883B70(this, action);
    this->cutsceneAction = 8;
    Animation_Change(&this->skin.skelAnime, &object_horse_link_child_Anim_00D4E8, 1.0f, 0.0f,
                     Animation_GetLastFrame(&object_horse_link_child_Anim_00D4E8), ANIMMODE_ONCE, 0.0f);
    func_8087C1C0(this);
}

void func_808844E0(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx, this->unk_530);
    if (SkelAnime_Update(&this->skin.skelAnime)) {
        Animation_Change(&this->skin.skelAnime, &object_horse_link_child_Anim_00D4E8, 1.0f, 0.0f,
                         Animation_GetLastFrame(&object_horse_link_child_Anim_00D4E8), ANIMMODE_ONCE, 0.0f);
        func_8087C1C0(this);
    }
}

void func_80884564(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 20.0f);
    func_80883B70(this, action);
    this->cutsceneAction = 8;
    Animation_Change(&this->skin.skelAnime, &object_horse_link_child_Anim_00BDE0, 1.0f, 0.0f,
                     Animation_GetLastFrame(&object_horse_link_child_Anim_00BDE0), ANIMMODE_ONCE, -3.0f);
    func_8087C1C0(this);
}

void func_80884604(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx, this->unk_530);
    if (SkelAnime_Update(&this->skin.skelAnime)) {
        Animation_Change(&this->skin.skelAnime, &object_horse_link_child_Anim_00BDE0, 1.0f, 0.0f,
                         Animation_GetLastFrame(&object_horse_link_child_Anim_00BDE0), ANIMMODE_ONCE, 0.0f);
    }

    if (((s32)this->curFrame % 11) == 0) {
        func_8087C1C0(this);
    }
}

void func_808846B4(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    Actor_MarkForDeath(&this->actor);
}

void func_808846DC(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
}

void func_808846F0(EnHorse* this, GlobalContext* globalCtx) {
    this->playerControlled = false;
    this->action = ENHORSE_ACT_21;
    this->unk_3E0 = -1;
    this->actor.speedXZ = 0.0f;
}

void func_80884718(EnHorse* this, GlobalContext* globalCtx) {
    CsCmdActorAction* action;

    if (Cutscene_CheckActorAction(globalCtx, 0x70)) {
        this->unk_530 = Cutscene_GetActorActionIndex(globalCtx, 0x70);
        action = globalCtx->csCtx.actorActions[this->unk_530];

        this->unk_1EC |= 0x20;
        if (this->unk_3E0 != action->action) {
            if (this->unk_3E0 == -1) {
                this->actor.world.pos.x = action->startPos.x;
                this->actor.world.pos.y = action->startPos.y;
                this->actor.world.pos.z = action->startPos.z;

                this->actor.world.rot.y = action->urot.y;
                this->actor.shape.rot = this->actor.world.rot;

                this->actor.prevPos = this->actor.world.pos;
            }

            this->unk_3E0 = action->action;
            if (D_808890F0[this->unk_3E0] != NULL) {
                D_808890F0[this->unk_3E0](this, globalCtx, action);
            }
        }

        if (D_8088911C[this->unk_3E0] != NULL) {
            D_8088911C[this->unk_3E0](this, globalCtx, action);
        }
    }
}

void func_80884868(EnHorse* this) {
    this->action = ENHORSE_ACT_23;
    this->animationIdx = ENHORSE_ANIM_WALK;
    Animation_PlayLoop(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx]);
    this->stateFlags |= ENHORSE_UNRIDEABLE;
}

void func_808848C8(EnHorse* this, GlobalContext* globalCtx) {
    Vec3f sp24 = { -1916.0f, -106.0f, -523.0f };

    EnHorse_PlayWalkingSound(this);
    this->actor.speedXZ = 4.0f;
    func_800F415C(&this->actor, &sp24, 2000);
    this->skin.skelAnime.playSpeed = this->actor.speedXZ * 0.75f;
    SkelAnime_Update(&this->skin.skelAnime);
    if (Math3D_Distance(&sp24, &this->actor.world.pos) < 30.0f) {
        this->stateFlags &= ~ENHORSE_UNRIDEABLE;
        EnHorse_StartIdleRidable(this);
    }
}

void func_80884994(EnHorse* this) {
    this->unk_534 = -1;
    this->animationIdx = ENHORSE_ANIM_TROT;
    this->action = ENHORSE_ACT_24;
    Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 2.0f, 0.0f,
                     Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE, -3.0f);
}

void func_80884A40(EnHorse* this, GlobalContext* globalCtx) {
    s32 sp44[] = { 5, 6, 0 };
    s32 sp40;
    s32 temp_v0;

    if (this->animationIdx == ENHORSE_ANIM_WHINNEY) {
        temp_v0 = 0;
    } else {
        temp_v0 = this->animationIdx;
    }

    sp40 = sp44[this->unk_538] != temp_v0;

    if (SkelAnime_Update(&this->skin.skelAnime) || sp40) {
        this->animationIdx = sp44[this->unk_538];
        if ((this->animationIdx == ENHORSE_ANIM_IDLE) && (Rand_ZeroOne() < 0.5f)) {
            this->animationIdx = ENHORSE_ANIM_WHINNEY;
        }

        if (sp40) {
            if (this->animationIdx == ENHORSE_ANIM_IDLE) {
                Animation_MorphToPlayOnce(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx],
                                          -3.0f);
            } else {
                Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 2.0f, 0.0f,
                                 Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]),
                                 ANIMMODE_ONCE, -3.0f);
            }
        } else if (this->animationIdx == ENHORSE_ANIM_IDLE) {
            Animation_PlayOnce(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx]);
        } else {
            Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx], 2.0f, 0.0f,
                             Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE,
                             0.0f);
        }

        if ((this->unk_538 == 0) || (this->unk_538 == 1)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_HORSE_RUN);
        } else if (this->unk_538 == 2) {
            if (this->animationIdx == ENHORSE_ANIM_IDLE) {
                EnHorse_IdleAnimSounds(this, globalCtx);
            } else if (this->animationIdx == ENHORSE_ANIM_WHINNEY) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_HORSE_GROAN);
            }
        }
    }
}

void func_80884D04(EnHorse* this, GlobalContext* globalCtx) {
    f32 playSpeed;

    this->actor.speedXZ = 10.0f;
    this->action = ENHORSE_ACT_25;
    this->unk_540 = this->actor.world.pos;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_IT_INGO_HORSE_NEIGH);
    this->animationIdx = ENHORSE_ANIM_GALLOP;
    playSpeed = this->actor.speedXZ * 0.2f;
    Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx],
                     sPlaybackSpeeds[this->animationIdx] * playSpeed * 2.5f, 0.0f,
                     Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE, 0.0f);
}

void func_80884E0C(EnHorse* this, GlobalContext* globalCtx) {
    f32 playSpeed = (this->unk_56C * 0.2f * 0.5f) + 1.0f;
    Vec3f pos;
    CollisionPoly* sp3C;

    this->skin.skelAnime.playSpeed = playSpeed;

    if (SkelAnime_Update(&this->skin.skelAnime)) {
        Animation_Change(&this->skin.skelAnime, sAnimationHeaders[this->type][this->animationIdx],
                         sPlaybackSpeeds[this->animationIdx] * playSpeed * 2.5f, 0.0f,
                         Animation_GetLastFrame(sAnimationHeaders[this->type][this->animationIdx]), ANIMMODE_ONCE,
                         0.0f);
        Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_HORSE_RUN);
    }

    this->unk_57C = this->actor.world.pos;
    this->actor.world.pos.x = this->unk_570.x;
    this->actor.world.pos.z = this->unk_570.z;

    this->unk_56C = Math3D_Distance(&this->actor.world.pos, &this->actor.prevPos);
    if (((this->unk_550 == 5) || (this->unk_550 == 7)) && (Player_GetMask(globalCtx) != PLAYER_MASK_CIRCUS_LEADER)) {
        this->rider->unk488 = 7;
    } else {
        EnHorse_SetIngoAnimation(this->animationIdx, this->skin.skelAnime.curFrame, this->unk_394 & 1,
                                 &this->rider->unk488);
    }

    pos = this->actor.world.pos;
    pos.y += 10.0f;

    if (BgCheck_EntityRaycastFloor1(&globalCtx->colCtx, &sp3C, &pos) != BGCHECK_Y_MIN) {
        this->actor.velocity.y += this->actor.gravity;
        if (this->actor.velocity.y < this->actor.terminalVelocity) {
            this->actor.velocity.y = this->actor.terminalVelocity;
        }
        this->actor.world.pos.y += this->actor.velocity.y * 0.5f;
    } else {
        this->actor.world.pos.y = this->unk_570.y;
    }
}

void EnHorse_Vec3fOffset(Vec3f* src, s16 yaw, f32 dist, f32 height, Vec3f* dst) {
    dst->x = (Math_SinS(yaw) * dist) + src->x;
    dst->y = src->y + height;
    dst->z = (Math_CosS(yaw) * dist) + src->z;
}

s32 EnHorse_CalcFloorHeight(EnHorse* this, GlobalContext* globalCtx, Vec3f* pos, CollisionPoly** polyFloor,
                            f32* floorHeight, s32* bgId) {
    f32 waterY;
    WaterBox* waterbox;

    *polyFloor = NULL;
    *floorHeight = BgCheck_EntityRaycastFloor3(&globalCtx->colCtx, polyFloor, bgId, pos);
    if (*floorHeight == BGCHECK_Y_MIN) {
        return 1; // No floor
    }

    if ((WaterBox_GetSurface1_2(globalCtx, &globalCtx->colCtx, pos->x, pos->z, &waterY, &waterbox) == 1) &&
        (*floorHeight < waterY)) {
        return 2; // Water
    }

    if ((COLPOLY_GET_NORMAL((*polyFloor)->normal.y) < 0.81915206f) ||
        SurfaceType_IsHorseBlocked(&globalCtx->colCtx, *polyFloor, *bgId) ||
        (func_800C99D4(&globalCtx->colCtx, *polyFloor, *bgId) == 7)) {
        return 3; // Horse blocked surface
    }

    return 0;
}

/**
 * obstacleType:
 *  1: Water in front
 *  2: Water behind?
 *  3: ?
 *  4: Obstructed in front
 *  5: Obstructed behind
 */
void EnHorse_ObstructMovement(EnHorse* this, GlobalContext* globalCtx, s32 obstacleType, s32 galloping) {
    if (this->action != ENHORSE_ACT_HBA) {
        if ((this->action == ENHORSE_ACT_MOUNTED_IDLE) || (this->action == ENHORSE_ACT_MOUNTED_IDLE_WHINNEYING)) {
            this->actor.world.pos = this->actor.prevPos;
            this->actor.world.rot.y -= 0x640;
            this->actor.speedXZ = 0.0f;
            this->actor.shape.rot.y = this->actor.world.rot.y;
            this->unk_1EC |= 4;
        } else if (this->action == ENHORSE_ACT_25) {
            this->unk_1EC |= 0x80;
            this->actor.world.pos = this->actor.prevPos;
            this->actor.speedXZ = 0.0f;
        } else if ((globalCtx->sceneNum != SCENE_KOEPONARACE) || (this->unk_1EC & 2)) {
            this->unk_1EC &= ~2;
            this->actor.world.pos = this->lastPos;
            this->stateFlags |= ENHORSE_OBSTACLE;
            if (this->playerControlled == 0) {
                if (this->animationIdx != 3) {}
            } else if (this->action != ENHORSE_ACT_REVERSE) {
                if (this->stateFlags & ENHORSE_JUMPING) {
                    this->stateFlags &= ~ENHORSE_JUMPING;
                    this->actor.gravity = -3.5f;
                    this->actor.world.pos.y = this->actor.floorHeight;
                }

                if ((obstacleType == 1) || (obstacleType == 4)) {
                    this->stateFlags |= ENHORSE_FORCE_REVERSING;
                } else if ((obstacleType == 2) || (obstacleType == 5)) {
                    this->stateFlags |= ENHORSE_FORCE_WALKING;
                }

                if (galloping == true) {
                    EnHorse_StartRearing(this);
                }
            }
        }
    }
}

void EnHorse_CheckFloors(EnHorse* this, GlobalContext* globalCtx) {
    s32 pad;
    CollisionPoly* frontFloor;
    CollisionPoly* backFloor;
    s32 bgId;
    s16 floorSlope;
    Vec3f frontPos;
    Vec3f backPos;
    Vec3f pos;
    f32 nx;
    f32 ny;
    f32 nz;
    s32 galloping = this->actor.speedXZ > 8.0f;
    s32 status;
    f32 waterHeight;
    WaterBox* waterbox;
    f32 dist;

    if ((WaterBox_GetSurface1_2(globalCtx, &globalCtx->colCtx, this->actor.world.pos.x, this->actor.world.pos.z,
                                &waterHeight, &waterbox) == true) &&
        (this->actor.floorHeight < waterHeight)) {
        EnHorse_ObstructMovement(this, globalCtx, 1, galloping);
        return;
    }

    if (this->type != HORSE_2) {
        EnHorse_Vec3fOffset(&this->actor.world.pos, this->actor.shape.rot.y, 30.0f, 55.0f, &frontPos);
    } else {
        EnHorse_Vec3fOffset(&this->actor.world.pos, this->actor.shape.rot.y, 15.0f, 30.0f, &frontPos);
    }

    status = EnHorse_CalcFloorHeight(this, globalCtx, &frontPos, &frontFloor, &this->yFront, &this->unk_24C);
    if (status == 1) {
        this->actor.shape.rot.x = 0;
        EnHorse_ObstructMovement(this, globalCtx, 4, galloping);
        return;
    }

    if (status == 3) {
        this->unk_1EC |= 2;
        EnHorse_ObstructMovement(this, globalCtx, 4, galloping);
        return;
    }

    if (this->type != HORSE_2) {
        EnHorse_Vec3fOffset(&this->actor.world.pos, this->actor.shape.rot.y, -30.0f, 55.0f, &backPos);
    } else {
        EnHorse_Vec3fOffset(&this->actor.world.pos, this->actor.shape.rot.y, -15.0f, 30.0f, &backPos);
    }

    status = EnHorse_CalcFloorHeight(this, globalCtx, &backPos, &backFloor, &this->yBack, &bgId);
    if (status == 1) {
        this->actor.shape.rot.x = 0;
        EnHorse_ObstructMovement(this, globalCtx, 5, galloping);
        return;
    }

    if (status == 3) {
        this->unk_1EC |= 2;
        EnHorse_ObstructMovement(this, globalCtx, 5, galloping);
        return;
    }

    floorSlope = Math_Atan2S(this->yBack - this->yFront, 60.0f);
    if (this->actor.floorPoly != NULL) {
        nx = COLPOLY_GET_NORMAL(this->actor.floorPoly->normal.x);
        ny = COLPOLY_GET_NORMAL(this->actor.floorPoly->normal.y);
        nz = COLPOLY_GET_NORMAL(this->actor.floorPoly->normal.z);

        pos = frontPos;
        pos.y = this->yFront;

        dist = Math3D_DistPlaneToPos(nx, ny, nz, this->actor.floorPoly->dist, &pos);
        if ((frontFloor != this->actor.floorPoly) && (this->actor.speedXZ >= 0.0f) &&
            ((!(this->stateFlags & ENHORSE_JUMPING) && (dist < -40.0f)) ||
             ((this->stateFlags & ENHORSE_JUMPING) && (dist < -200.0f)))) {
            EnHorse_ObstructMovement(this, globalCtx, 4, galloping);
            return;
        }

        pos = backPos;
        pos.y = this->yBack;

        dist = Math3D_DistPlaneToPos(nx, ny, nz, this->actor.floorPoly->dist, &pos);
        if ((backFloor != this->actor.floorPoly) && (this->actor.speedXZ <= 0.0f) &&
            ((!(this->stateFlags & ENHORSE_JUMPING) && (dist < -40.0f)) ||
             ((this->stateFlags & ENHORSE_JUMPING) && (dist < -200.0f)))) {
            EnHorse_ObstructMovement(this, globalCtx, 5, galloping);
            return;
        }

        if ((ny < 0.81915206f) ||
            SurfaceType_IsHorseBlocked(&globalCtx->colCtx, this->actor.floorPoly, this->actor.floorBgId) ||
            (func_800C99D4(&globalCtx->colCtx, this->actor.floorPoly, this->actor.floorBgId) == 7)) {
            if (this->actor.speedXZ >= 0.0f) {
                EnHorse_ObstructMovement(this, globalCtx, 4, galloping);
            } else {
                EnHorse_ObstructMovement(this, globalCtx, 5, galloping);
            }
        } else if (this->stateFlags & 4) {
            this->actor.shape.rot.x = 0;
        } else if ((this->actor.floorHeight + 4.0f) < this->actor.world.pos.y) {
            this->actor.shape.rot.x = 0;
        } else if (!(fabsf(floorSlope) > 0x1FFF)) {
            this->actor.shape.rot.x = floorSlope;
            this->actor.shape.yOffset =
                ((this->yFront + (((this->yBack - this->yFront) * 20.0f) / 45.0f)) - this->actor.floorHeight) +
                this->unk_3E8;
        }
    }
}

void EnHorse_MountDismount(EnHorse* this, GlobalContext* globalCtx) {
    s32 mountSide = EnHorse_GetMountSide(this, globalCtx);

    if ((mountSide != 0) && !(this->stateFlags & ENHORSE_UNRIDEABLE)) {
        Actor_SetRideActor(globalCtx, &this->actor, mountSide);
    }

    if ((this->playerControlled == false) && (Actor_HasRider(globalCtx, &this->actor) == true)) {
        this->noInputTimer = 26;
        this->noInputTimerMax = 26;
        this->playerControlled = true;
        EnHorse_Freeze(this, globalCtx);
    } else if ((this->playerControlled == true) && (Actor_HasNoRider(globalCtx, &this->actor) == true)) {
        this->noInputTimer = 35;
        this->noInputTimerMax = 35;
        this->stateFlags &= ~ENHORSE_UNRIDEABLE;
        this->playerControlled = false;
        EnHorse_Freeze(this, globalCtx);
    }
}

void EnHorse_StickDirection(Vec2f* curStick, f32* stickMag, s16* angle) {
    *stickMag = sqrtf(SQ(curStick->x) + SQ(curStick->z));
    *stickMag = CLAMP_MAX(*stickMag, 60.0f);
    *angle = Math_Atan2S(-curStick->x, curStick->z);
}

void EnHorse_UpdateStick(EnHorse* this, GlobalContext* globalCtx) {
    Input* input = &globalCtx->state.input[this->unk_52C];

    this->lastStick = this->curStick;
    this->curStick.x = input->rel.stick_x;
    this->curStick.z = input->rel.stick_y;
}

void EnHorse_ResolveCollision(EnHorse* this, GlobalContext* globalCtx, CollisionPoly* colPoly) {
    f32 dist;
    f32 nx;
    f32 ny;
    f32 nz;
    f32 offset;

    nx = COLPOLY_GET_NORMAL(colPoly->normal.x);
    ny = COLPOLY_GET_NORMAL(colPoly->normal.y);
    nz = COLPOLY_GET_NORMAL(colPoly->normal.z);

    if (!(Math_CosS(BINANG_ROT180(this->actor.world.rot.y - Math_Atan2S(colPoly->normal.x, colPoly->normal.z))) <
          0.7071f)) { // cos(45 degrees)
        dist = Math3D_DistPlaneToPos(nx, ny, nz, colPoly->dist, &this->actor.world.pos);
        offset = (1.0f / sqrtf(SQ(nx) + SQ(nz)));
        offset = (30.0f - dist) * offset;
        this->actor.world.pos.x += offset * nx;
        this->actor.world.pos.z += offset * nz;
    }
}

void EnHorse_BgCheckSlowMoving(EnHorse* this, GlobalContext* globalCtx) {
    f32 yOffset = 40.0f;
    Vec3f start;
    Vec3f end;
    Vec3f intersect;
    CollisionPoly* colPoly;
    s32 bgId;

    Math_Vec3f_Copy(&start, &this->actor.world.pos);
    start.y += yOffset;

    Math_Vec3f_Copy(&end, &start);
    end.x += 30.0f * Math_SinS(this->actor.world.rot.y);
    end.y += 30.0f * Math_SinS(-this->actor.shape.rot.x);
    end.z += 30.0f * Math_CosS(this->actor.world.rot.y);
    if (BgCheck_EntityLineTest1(&globalCtx->colCtx, &start, &end, &intersect, &colPoly, true, false, false, true,
                                &bgId)) {
        EnHorse_ResolveCollision(this, globalCtx, colPoly);
    }
}

void EnHorse_UpdateBgCheckInfo(EnHorse* this, GlobalContext* globalCtx) {
    s32 pad2[2];
    Vec3f startPos;
    Vec3f endPos;
    Vec3f obstaclePos;
    f32 temp_f0;
    f32 intersectDist;
    CollisionPoly* wall = NULL;
    CollisionPoly* obstacleFloor = NULL;
    s32 bgId;
    f32 obstacleHeight;
    f32 behindObstacleHeight;
    DynaPolyActor* horseJump;
    s32 movingFast;
    s16 sp7E = 0;
    DynaPolyActor* horseGameCheck = NULL;
    s32 pad6;
    s32 pad;
    Vec3f intersect;
    Vec3f obstacleTop;
    s32 pad5;
    s32 pad4;

    if ((this->actor.params != ENHORSE_4) && (this->actor.params != ENHORSE_5) && (this->actor.params != ENHORSE_19) &&
        (this->actor.params != ENHORSE_20) && (this->actor.params != ENHORSE_18)) {
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 40.0f, 35.0f, 100.0f, 0x1D);
    } else {
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 40.0f, 35.0f, 100.0f, 0x1C);
    }

    if ((this->actor.bgCheckFlags & 8) && (Math_CosS(this->actor.wallYaw - this->actor.world.rot.y) < -0.3f)) {
        if (this->actor.speedXZ > 4.0f) {
            this->actor.speedXZ -= 1.0f;
            if (this->type == HORSE_2) {
                Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_SANDDUST);
            } else {
                Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_SANDDUST);
            }
        }
    }

    horseJump = DynaPoly_GetActor(&globalCtx->colCtx, this->actor.floorBgId);

    if (!(this->stateFlags & ENHORSE_JUMPING)) {
        if ((horseJump != NULL) && (horseJump->actor.id == ACTOR_EN_HORSE_GAME_CHECK) &&
            ((horseJump->actor.params & 0xFF) == 5)) {
            this->stateFlags |= ENHORSE_FLAG_28;
            this->unk_3E8 += ((-10.0f / this->actor.scale.y) - this->unk_3E8) * 0.5f;
            if (this->actor.speedXZ > 2.0f) {
                this->actor.speedXZ -= 1.0f;
                if (this->type == HORSE_2) {
                    Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_SANDDUST);
                } else {
                    Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_SANDDUST);
                }
            }
        } else {
            this->stateFlags &= ~ENHORSE_FLAG_28;
            this->unk_3E8 *= 0.5f;
        }
    }

    if ((this->stateFlags & ENHORSE_JUMPING) || (this->stateFlags & ENHORSE_FLAG_28) || (this->actor.speedXZ < 0.0f) ||
        (this->action == ENHORSE_ACT_LOW_JUMP) || (this->action == ENHORSE_ACT_REVERSE)) {
        return;
    }

    if (this->actor.speedXZ > 8.0f) {
        if (this->actor.speedXZ < 12.8f) {
            intersectDist = 160.0f;
            movingFast = false;
        } else {
            intersectDist = 230.0f;
            movingFast = true;
        }
    } else {
        EnHorse_BgCheckSlowMoving(this, globalCtx);
        return;
    }

    startPos = this->actor.world.pos;
    startPos.y += 19.0f;

    endPos = startPos;
    endPos.x += intersectDist * Math_SinS(this->actor.world.rot.y);
    endPos.y += intersectDist * Math_SinS(-this->actor.shape.rot.x);
    endPos.z += intersectDist * Math_CosS(this->actor.world.rot.y);

    intersect = endPos;
    wall = NULL;

    if (BgCheck_EntityLineTest1(&globalCtx->colCtx, &startPos, &endPos, &intersect, &wall, true, false, false, true,
                                &bgId) == true) {
        intersectDist = sqrtf(Math3D_Vec3fDistSq(&startPos, &intersect));
        this->stateFlags |= ENHORSE_OBSTACLE;
    }

    if (wall != NULL) {
        if (intersectDist < 30.0f) {
            EnHorse_ResolveCollision(this, globalCtx, wall);
        }

        sp7E = BINANG_ROT180(this->actor.world.rot.y - Math_Atan2S(wall->normal.x, wall->normal.z));

        if ((Math_CosS(sp7E) < 0.5f) || SurfaceType_IsHorseBlocked(&globalCtx->colCtx, wall, bgId)) {
            return;
        }

        if (((movingFast == false) && (intersectDist < 80.0f)) || ((movingFast == true) && (intersectDist < 150.0f))) {
            if ((globalCtx->sceneNum != SCENE_KOEPONARACE) && (Math_CosS(sp7E) < 0.9f) &&
                (this->playerControlled == true)) {
                if (movingFast == false) {
                    this->stateFlags |= ENHORSE_FORCE_REVERSING;
                } else if (movingFast == true) {
                    this->stateFlags |= ENHORSE_FORCE_REVERSING;
                    EnHorse_StartBraking(this, globalCtx);
                }
            }
            return;
        }

        horseJump = DynaPoly_GetActor(&globalCtx->colCtx, bgId);
        if ((this->stateFlags & ENHORSE_FLAG_26) &&
            (((horseJump != NULL) && (horseJump->actor.id != ACTOR_BG_UMAJUMP)) || (horseJump == NULL))) {
            if (this->playerControlled == true) {
                if (movingFast == false) {
                    this->stateFlags |= ENHORSE_FORCE_REVERSING;
                } else if (movingFast == true) {
                    this->stateFlags |= ENHORSE_FORCE_REVERSING;
                    EnHorse_StartBraking(this, globalCtx);
                }
            }
            return;
        }
    }

    intersectDist += 5.0f;
    obstaclePos = startPos;

    obstaclePos.x += intersectDist * Math_SinS(this->actor.world.rot.y);
    obstaclePos.y = this->actor.world.pos.y + 120.0f;
    obstaclePos.z += intersectDist * Math_CosS(this->actor.world.rot.y);

    obstacleTop = obstaclePos;
    obstacleTop.y = BgCheck_EntityRaycastFloor3(&globalCtx->colCtx, &obstacleFloor, &bgId, &obstaclePos);

    if (obstacleTop.y == BGCHECK_Y_MIN) {
        return;
    }

    obstacleHeight = obstacleTop.y - this->actor.world.pos.y;

    if ((this->actor.floorPoly == NULL) || (obstacleFloor == NULL)) {
        return;
    }

    if ((Math3D_DistPlaneToPos(COLPOLY_GET_NORMAL(this->actor.floorPoly->normal.x),
                               COLPOLY_GET_NORMAL(this->actor.floorPoly->normal.y),
                               COLPOLY_GET_NORMAL(this->actor.floorPoly->normal.z), this->actor.floorPoly->dist,
                               &obstacleTop) < -40.0f) &&
        (Math3D_DistPlaneToPos(COLPOLY_GET_NORMAL(obstacleFloor->normal.x), COLPOLY_GET_NORMAL(obstacleFloor->normal.y),
                               COLPOLY_GET_NORMAL(obstacleFloor->normal.z), obstacleFloor->dist,
                               &this->actor.world.pos) > 40.0f)) {
        if ((movingFast == true) && (this->playerControlled == true) && (this->action != ENHORSE_ACT_LOW_JUMP) &&
            (globalCtx->sceneNum != SCENE_KOEPONARACE)) {
            this->stateFlags |= ENHORSE_FORCE_REVERSING;
            EnHorse_StartBraking(this, globalCtx);
        }
        this->stateFlags |= ENHORSE_OBSTACLE;
        return;
    }

    temp_f0 = COLPOLY_GET_NORMAL(obstacleFloor->normal.y);
    if ((temp_f0 < 0.81915206f) || SurfaceType_IsHorseBlocked(&globalCtx->colCtx, obstacleFloor, bgId) ||
        (func_800C99D4(&globalCtx->colCtx, obstacleFloor, bgId) == 7)) {
        if ((Math_CosS(sp7E) < 0.9f) && (movingFast == true) && (this->playerControlled == true) &&
            (this->action != ENHORSE_ACT_LOW_JUMP) && (globalCtx->sceneNum != SCENE_KOEPONARACE)) {
            this->stateFlags |= ENHORSE_FORCE_REVERSING;
            EnHorse_StartBraking(this, globalCtx);
        }
        return;
    }

    if (wall == NULL) {
        horseGameCheck = DynaPoly_GetActor(&globalCtx->colCtx, bgId);
        if ((horseGameCheck == NULL) || (horseGameCheck->actor.id != ACTOR_EN_HORSE_GAME_CHECK) ||
            ((horseGameCheck->actor.params & 0xFF) != 5)) {
            return;
        }
    }

    if (((obstacleTop.y < intersect.y) &&
         ((horseGameCheck == NULL) || (horseGameCheck->actor.id != ACTOR_EN_HORSE_GAME_CHECK) ||
          ((horseGameCheck->actor.params & 0xFF) != 5))) ||
        ((this->stateFlags & ENHORSE_CANT_JUMP) && (this->action != ENHORSE_ACT_MOUNTED_IDLE))) {
        return;
    }

    if ((this->action == ENHORSE_ACT_MOUNTED_IDLE) && !(this->stateFlags & ENHORSE_FLAG_30)) {
        horseGameCheck = DynaPoly_GetActor(&globalCtx->colCtx, bgId);
        if ((horseGameCheck != NULL) && (horseGameCheck->actor.id == ACTOR_EN_HORSE_GAME_CHECK) &&
            ((horseGameCheck->actor.params & 0xFF) == 5)) {
            this->stateFlags |= ENHORSE_FLAG_30;
            this->postDrawFunc = func_8088126C;
        }
    }

    if (this->playerControlled == false) {
        return;
    }

    obstaclePos = startPos;
    obstaclePos.y = this->actor.world.pos.y + 120.0f;

    if (movingFast == false) {
        obstaclePos.x += 276.0f * Math_SinS(this->actor.world.rot.y);
        obstaclePos.z += 276.0f * Math_CosS(this->actor.world.rot.y);
    } else {
        obstaclePos.x += 390.0f * Math_SinS(this->actor.world.rot.y);
        obstaclePos.z += 390.0f * Math_CosS(this->actor.world.rot.y);
    }

    obstacleTop = obstaclePos;
    obstacleTop.y = BgCheck_EntityRaycastFloor3(&globalCtx->colCtx, &obstacleFloor, &bgId, &obstaclePos);

    if (obstacleTop.y == BGCHECK_Y_MIN) {
        return;
    }

    behindObstacleHeight = obstacleTop.y - this->actor.world.pos.y;

    if (obstacleFloor == NULL) {
        return;
    }

    temp_f0 = COLPOLY_GET_NORMAL(obstacleFloor->normal.y);
    if ((temp_f0 < 0.81915206f) || SurfaceType_IsHorseBlocked(&globalCtx->colCtx, obstacleFloor, bgId) ||
        (func_800C99D4(&globalCtx->colCtx, obstacleFloor, bgId) == 7)) {
        if ((movingFast == true) && (this->playerControlled == true) && (this->action != ENHORSE_ACT_LOW_JUMP) &&
            (globalCtx->sceneNum != SCENE_KOEPONARACE)) {
            this->stateFlags |= ENHORSE_FORCE_REVERSING;
            EnHorse_StartBraking(this, globalCtx);
        }
    } else if (behindObstacleHeight < -70.0f) {
        if ((movingFast == true) && (this->playerControlled == true) && (this->action != ENHORSE_ACT_LOW_JUMP) &&
            (globalCtx->sceneNum != SCENE_KOEPONARACE)) {
            this->stateFlags |= ENHORSE_FORCE_REVERSING;
            EnHorse_StartBraking(this, globalCtx);
        }
    } else {
        temp_f0 = (this->actor.scale.y * 100.0f);

        if ((horseGameCheck == NULL) || (horseGameCheck->actor.id != ACTOR_EN_HORSE_GAME_CHECK) ||
            ((horseGameCheck->actor.params & 0xFF) != 5)) {
            if ((movingFast == false) && ((19.0f * temp_f0) < obstacleHeight) &&
                (obstacleHeight <= (40.0f * temp_f0))) {
                EnHorse_Stub1(this);
                this->postDrawFunc = EnHorse_LowJumpInit;
            } else if ((movingFast == true) &&
                       (((this->actor.speedXZ < 13.8f) && ((19.0f * temp_f0) < obstacleHeight) &&
                         (obstacleHeight <= (72.0f * temp_f0))) ||
                        ((this->actor.speedXZ > 13.8f) && (obstacleHeight <= (112.0f * temp_f0))))) {
                EnHorse_Stub2(this);
                this->postDrawFunc = EnHorse_HighJumpInit;
            }
        } else if (movingFast == false) {
            EnHorse_Stub1(this);
            this->postDrawFunc = EnHorse_LowJumpInit;
        } else if (movingFast == true) {
            EnHorse_Stub2(this);
            this->postDrawFunc = EnHorse_HighJumpInit;
        }
    }
}

void func_80886C00(EnHorse* this, GlobalContext* globalCtx) {
    Input* input = &globalCtx->state.input[this->unk_52C];

    if (((this->action == ENHORSE_ACT_MOUNTED_GALLOP) || (this->action == ENHORSE_ACT_MOUNTED_REARING) ||
         (this->action == ENHORSE_ACT_STOPPING)) &&
        (CHECK_BTN_ALL(input->press.button, BTN_A) || (func_801A5100() == 5)) &&
        (globalCtx->interfaceCtx.unk_212 == 8) && !(this->stateFlags & ENHORSE_BOOST) &&
        !(this->stateFlags & ENHORSE_FLAG_8) && !(this->stateFlags & ENHORSE_FLAG_9)) {
        if (this->numBoosts > 0) {
            func_8013ECE0(0.0f, 180, 20, 100);
            this->stateFlags |= ENHORSE_BOOST;
            this->stateFlags |= ENHORSE_FIRST_BOOST_REGEN;
            this->stateFlags |= ENHORSE_FLAG_8;
            this->numBoosts--;
            this->boostTimer = 0;
            if (this->numBoosts == 0) {
                this->boostRegenTime = 140;
            } else if (this->type == HORSE_EPONA) {
                if (this->stateFlags & ENHORSE_FIRST_BOOST_REGEN) {
                    this->boostRegenTime = 60;
                    this->stateFlags &= ~ENHORSE_FIRST_BOOST_REGEN;
                } else {
                    this->boostRegenTime = 8;
                }
            } else {
                this->boostRegenTime = 70;
            }
        } else if ((this->stateFlags & ENHORSE_DRAW) && (Rand_ZeroOne() < 0.1f)) {
            if (this->type == HORSE_2) {
                Audio_PlaySfxAtPos(&this->unk_218, NA_SE_EV_KID_HORSE_NEIGH);
            } else {
                Audio_PlaySfxAtPos(&this->unk_218, NA_SE_EV_HORSE_NEIGH);
            }
        }
    }
}

void EnHorse_RegenBoost(EnHorse* this, GlobalContext* globalCtx) {
    s32 playSfx;

    if ((this->numBoosts < 6) && (this->numBoosts > 0)) {
        this->boostRegenTime--;
        this->boostTimer++;
        if (this->boostRegenTime <= 0) {
            this->numBoosts++;
            if (((this->action == ENHORSE_ACT_MOUNTED_TURN) || (this->action == ENHORSE_ACT_FROZEN) ||
                 (this->action == ENHORSE_ACT_MOUNTED_WALK)) &&
                !(this->stateFlags & ENHORSE_FLAG_19) && !(this->stateFlags & ENHORSE_FLAG_25)) {
                playSfx = true;
            } else {
                playSfx = false;
            }

            if (!playSfx) {
                play_sound(NA_SE_SY_CARROT_RECOVER);
            }

            if (this->numBoosts < 6) {
                this->boostRegenTime = 11;
            }
        }
    } else if (this->numBoosts == 0) {
        this->boostRegenTime--;
        this->boostTimer++;
        if (this->boostRegenTime <= 0) {
            this->boostRegenTime = 0;
            this->numBoosts = 6;
            if (((this->action == ENHORSE_ACT_MOUNTED_TURN) || (this->action == ENHORSE_ACT_FROZEN) ||
                 (this->action == ENHORSE_ACT_MOUNTED_WALK)) &&
                !(this->stateFlags & ENHORSE_FLAG_19) && !(this->stateFlags & ENHORSE_FLAG_25)) {
                playSfx = true;
            } else {
                playSfx = false;
            }

            if (!playSfx) {
                play_sound(NA_SE_SY_CARROT_RECOVER);
            }
        }
    }

    if (this->boostTimer == 8) {
        if ((Rand_ZeroOne() < 0.25f) && (this->stateFlags & ENHORSE_DRAW)) {
            if (this->type == HORSE_2) {
                Audio_PlaySfxAtPos(&this->unk_218, NA_SE_EV_KID_HORSE_NEIGH);
            } else {
                Audio_PlaySfxAtPos(&this->unk_218, NA_SE_EV_HORSE_NEIGH);
            }
        }
    }

    globalCtx->interfaceCtx.numHorseBoosts = this->numBoosts;
}

void EnHorse_UpdatePlayerDir(EnHorse* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 angle = Actor_YawBetweenActors(&this->actor, &player->actor) - this->actor.world.rot.y;
    f32 s = Math_SinS(angle);
    f32 c = Math_CosS(angle);

    if (s > 0.8660254f) { // sin(60 degrees)
        this->playerDir = PLAYER_DIR_SIDE_L;
    } else if (s < -0.8660254f) { // -sin(60 degrees)
        this->playerDir = PLAYER_DIR_SIDE_R;
    } else if (c > 0.0f) {
        if (s > 0.0f) {
            this->playerDir = PLAYER_DIR_FRONT_L;
        } else {
            this->playerDir = PLAYER_DIR_FRONT_R;
        }
    } else if (s > 0.0f) {
        this->playerDir = PLAYER_DIR_BACK_L;
    } else {
        this->playerDir = PLAYER_DIR_BACK_R;
    }
}

void EnHorse_TiltBody(EnHorse* this, GlobalContext* globalCtx) {
    f32 speed;
    f32 rollDiff;
    s32 targetRoll;
    s16 turnVel;

    speed = this->actor.speedXZ / this->boostSpeed;
    turnVel = this->actor.shape.rot.y - this->lastYaw;
    targetRoll = -((s16)((2730.0f * speed) * (turnVel / 960.00006f)));
    rollDiff = targetRoll - this->actor.world.rot.z;

    if (fabsf(targetRoll) < 100.0f) {
        this->actor.world.rot.z = 0;
    } else if (fabsf(rollDiff) < 100.0f) {
        this->actor.world.rot.z = targetRoll;
    } else if (rollDiff > 0.0f) {
        this->actor.world.rot.z += 0x64;
    } else {
        this->actor.world.rot.z -= 0x64;
    }

    this->actor.shape.rot.z = this->actor.world.rot.z;
}

s32 EnHorse_UpdateConveyors(EnHorse* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 conveyorDir;

    if ((this->actor.floorPoly == NULL) || (&this->actor != player->rideActor) ||
        !SurfaceType_GetConveyorSpeed(&globalCtx->colCtx, this->actor.floorPoly, this->actor.floorBgId)) {
        return false;
    }

    conveyorDir = SurfaceType_GetConveyorDirection(&globalCtx->colCtx, this->actor.floorPoly, this->actor.floorBgId);
    conveyorDir = (conveyorDir * 0x400) - this->actor.world.rot.y;
    if (conveyorDir > 0x640) {
        this->actor.world.rot.y += 0x640;
    } else if (conveyorDir < -0x640) {
        this->actor.world.rot.y -= 0x640;
    } else {
        this->actor.world.rot.y += conveyorDir;
    }
    this->actor.shape.rot.y = this->actor.world.rot.y;
    return true;
}

s32 EnHorse_RandInt(f32 arg0) {
    return Rand_ZeroOne() * arg0;
}

#ifdef NON_MATCHING
void EnHorse_Update(Actor* thisx, GlobalContext* globalCtx) {
    static EnHorseActionFunc sActionFuncs[] = {
        EnHorse_Frozen,
        EnHorse_Inactive,
        EnHorse_Idle,
        EnHorse_FollowPlayer,
        EnHorse_UpdateIngoRace,
        func_808819D8,
        func_80881398,
        EnHorse_MountedIdle,
        EnHorse_MountedIdleWhinneying,
        EnHorse_MountedTurn,
        EnHorse_MountedWalk,
        EnHorse_MountedTrot,
        EnHorse_MountedGallop,
        EnHorse_MountedRearing,
        EnHorse_Stopping,
        EnHorse_Reverse,
        EnHorse_LowJump,
        EnHorse_HighJump,
        EnHorse_CutsceneUpdate,
        EnHorse_UpdateHorsebackArchery,
        EnHorse_FleePlayer,
        func_80884718,
        func_8087CA04,
        func_808848C8,
        func_80884A40,
        func_80884E0C,
    };
    s32 pad;
    EnHorse* this = THIS;
    Vec3f dustAcc = { 0.0f, 0.0f, 0.0f };
    Vec3f dustVel = { 0.0f, 1.0f, 0.0f };
    Player* player = GET_PLAYER(globalCtx);

    if (this->type == HORSE_2) {
        Actor_SetScale(&this->actor, 0.00648f);
    } else if (this->type == HORSE_4) {
        Actor_SetScale(&this->actor, 0.008f);
    } else {
        Actor_SetScale(&this->actor, 0.01f);
    }

    this->lastYaw = this->actor.shape.rot.y;
    EnHorse_UpdateStick(this, globalCtx);
    EnHorse_UpdatePlayerDir(this, globalCtx);

    if (!(this->stateFlags & ENHORSE_INACTIVE)) {
        EnHorse_MountDismount(this, globalCtx);
    }

    if (this->stateFlags & ENHORSE_FLAG_19) {
        if ((this->stateFlags & ENHORSE_FLAG_20) && (this->inRace == true)) {
            this->stateFlags &= ~ENHORSE_FLAG_20;
            EnHorse_StartRearing(this);
        } else if (!(this->stateFlags & ENHORSE_FLAG_20) && (this->stateFlags & ENHORSE_FLAG_21) &&
                   (this->action != ENHORSE_ACT_REVERSE) && (this->inRace == true)) {
            this->stateFlags &= ~ENHORSE_FLAG_21;
            EnHorse_StartRearing(this);
        }
    }

    sActionFuncs[this->action](this, globalCtx);

    this->stateFlags &= ~ENHORSE_OBSTACLE;
    this->unk_3EC = this->actor.world.rot.y;
    if ((this->animationIdx == ENHORSE_ANIM_STOPPING) || (this->animationIdx == ENHORSE_ANIM_REARING)) {
        this->skin.skelAnime.jointTable[0].y += 0x154;
    }

    this->curFrame = this->skin.skelAnime.curFrame;
    this->lastPos = this->actor.world.pos;

    if (!(this->stateFlags & ENHORSE_INACTIVE)) {
        if ((this->action == ENHORSE_ACT_STOPPING) || (this->action == ENHORSE_ACT_MOUNTED_REARING) ||
            (this->action == ENHORSE_ACT_MOUNTED_GALLOP)) {
            func_80886C00(this, globalCtx);
        }

        if (this->playerControlled == true) {
            EnHorse_RegenBoost(this, globalCtx);
        }

        if (ActorCutscene_GetCurrentIndex() != -1) {
            this->actor.speedXZ = 0.0f;
        }

        if (this->action != ENHORSE_ACT_25) {
            Actor_MoveWithGravity(&this->actor);
        }

        if (this->rider != NULL) {
            if ((this->action == ENHORSE_ACT_INGO_RACE) || (this->action == ENHORSE_ACT_MOUNTED_IDLE) ||
                (this->action == ENHORSE_ACT_25)) {
                this->rider->actor.world.pos.x = this->actor.world.pos.x;
                this->rider->actor.world.pos.y = this->actor.world.pos.y + 10.0f;
                this->rider->actor.world.pos.z = this->actor.world.pos.z;
                this->rider->actor.shape.rot.x = this->actor.shape.rot.x;
                this->rider->actor.shape.rot.y = this->actor.shape.rot.y;
            } else if (this->action == ENHORSE_ACT_MOUNTED_IDLE_WHINNEYING) {
                EnIn* in = this->rider;
                s16 jnt = in->jointTable[0].y;

                in->actor.world.pos.x = this->riderPos.x;
                in->actor.world.pos.y = this->riderPos.y - (jnt * 0.01f * this->unk_528 * 0.01f);
                in->actor.world.pos.z = this->riderPos.z;
                in->actor.shape.rot.x = this->actor.shape.rot.x;
                in->actor.shape.rot.y = this->actor.shape.rot.y;
            }
        }

        if (this->colliderJntSph.elements->info.ocElemFlags & OCELEM_HIT) {
            if (this->actor.speedXZ > 10.0f) {
                this->actor.speedXZ -= 1.0f;
            }
        }

        if ((this->colliderJntSph.base.acFlags & AC_HIT) && (this->stateFlags & ENHORSE_DRAW)) {
            if (this->type == HORSE_2) {
                Audio_PlaySfxAtPos(&this->unk_218, NA_SE_EV_KID_HORSE_NEIGH);
            } else {
                Audio_PlaySfxAtPos(&this->unk_218, NA_SE_EV_HORSE_NEIGH);
            }
        }

        if ((this->action != ENHORSE_ACT_INGO_RACE) && (this->action != ENHORSE_ACT_MOUNTED_IDLE) &&
            (this->action != ENHORSE_ACT_MOUNTED_IDLE_WHINNEYING)) {
            EnHorse_TiltBody(this, globalCtx);
        }

        if ((this->playerControlled == false) && (this->unk_1EC & 8)) {
            if ((this->colliderJntSph.elements->info.ocElemFlags & OCELEM_HIT) &&
                (this->colliderJntSph.base.oc->id == ACTOR_EN_IN)) {
                func_80884868(this);
            }

            if ((this->colliderCylinder1.base.ocFlags1 & OC1_HIT) &&
                (this->colliderCylinder1.base.oc->id == ACTOR_EN_IN)) {
                func_80884868(this);
            }

            if ((this->colliderCylinder2.base.ocFlags1 & OC1_HIT) &&
                (this->colliderCylinder2.base.oc->id == ACTOR_EN_IN)) {
                func_80884868(this);
            }
        }

        Collider_UpdateCylinder(&this->actor, &this->colliderCylinder1);
        Collider_UpdateCylinder(&this->actor, &this->colliderCylinder2);

        if (this->type == HORSE_2) {
            this->colliderCylinder1.dim.pos.x =
                (s16)(Math_SinS(this->actor.shape.rot.y) * 11.0f) + this->colliderCylinder1.dim.pos.x;
            this->colliderCylinder1.dim.pos.z =
                (s16)(Math_CosS(this->actor.shape.rot.y) * 11.0f) + this->colliderCylinder1.dim.pos.z;
            this->colliderCylinder2.dim.pos.x =
                (s16)(Math_SinS(this->actor.shape.rot.y) * -18.0f) + this->colliderCylinder2.dim.pos.x;
            this->colliderCylinder2.dim.pos.z =
                (s16)(Math_CosS(this->actor.shape.rot.y) * -18.0f) + this->colliderCylinder2.dim.pos.z;
        } else {
            this->colliderCylinder1.dim.pos.x =
                (s16)(Math_SinS(this->actor.shape.rot.y) * 6.6000004f) + this->colliderCylinder1.dim.pos.x;
            this->colliderCylinder1.dim.pos.z =
                (s16)(Math_CosS(this->actor.shape.rot.y) * 6.6000004f) + this->colliderCylinder1.dim.pos.z;
            this->colliderCylinder2.dim.pos.x =
                (s16)(Math_SinS(this->actor.shape.rot.y) * -10.8f) + this->colliderCylinder2.dim.pos.x;
            this->colliderCylinder2.dim.pos.z =
                (s16)(Math_CosS(this->actor.shape.rot.y) * -10.8f) + this->colliderCylinder2.dim.pos.z;
        }

        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->colliderCylinder1.base);
        if (!(this->stateFlags & ENHORSE_JUMPING) && !(this->unk_1EC & 0x20)) {
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderCylinder1.base);
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderCylinder2.base);
        } else {
            this->unk_1EC &= ~0x20;
        }

        if (this->unk_1EC & 0x100) {
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliderCylinder1.base);
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliderCylinder2.base);
        }

        if ((player->stateFlags1 & ENHORSE_BOOST) && (player->rideActor != NULL)) {
            EnHorse_UpdateConveyors(this, globalCtx);
        }

        EnHorse_UpdateBgCheckInfo(this, globalCtx);
        EnHorse_CheckFloors(this, globalCtx);
        if (this->actor.world.pos.y < this->yFront) {
            if (this->actor.world.pos.y < this->yBack) {
                if (this->yBack < this->yFront) {
                    this->actor.world.pos.y = this->yBack;
                } else {
                    this->actor.world.pos.y = this->yFront;
                }
            }
        }

        this->actor.focus.pos = this->actor.world.pos;
        this->actor.focus.pos.y += 70.0f;

        if ((Rand_ZeroOne() < 0.025f) && (this->blinkTimer == 0)) {
            this->blinkTimer++;
        } else if (this->blinkTimer > 0) {
            this->blinkTimer++;
            if (this->blinkTimer > 3) {
                this->blinkTimer = 0;
            }
        }

        if ((this->actor.speedXZ == 0.0f) && !(this->stateFlags & ENHORSE_FLAG_19)) {
            this->actor.colChkInfo.mass = MASS_IMMOVABLE;
        } else {
            this->actor.colChkInfo.mass = MASS_HEAVY;
        }

        if (this->actor.speedXZ >= 5.0f) {
            this->colliderCylinder1.base.atFlags |= AT_ON;
        } else {
            this->colliderCylinder1.base.atFlags &= ~AT_ON;
        }

        if (this->dustFlags & 1) {
            this->dustFlags &= ~1;
            func_800B12F0(globalCtx, &this->frontRightHoof, &dustVel, &dustAcc, EnHorse_RandInt(100.0f) + 200,
                          EnHorse_RandInt(10.0f) + 30, EnHorse_RandInt(20.0f) + 30);
        } else if (this->dustFlags & 2) {
            this->dustFlags &= ~2;
            func_800B12F0(globalCtx, &this->frontLeftHoof, &dustVel, &dustAcc, EnHorse_RandInt(100.0f) + 200,
                          EnHorse_RandInt(10.0f) + 30, EnHorse_RandInt(20.0f) + 30);
        } else if (this->dustFlags & 4) {
            this->dustFlags &= ~4;
            func_800B12F0(globalCtx, &this->backRightHoof, &dustVel, &dustAcc, EnHorse_RandInt(100.0f) + 200,
                          EnHorse_RandInt(10.0f) + 30, EnHorse_RandInt(20.0f) + 30);
        } else if (this->dustFlags & 8) {
            this->dustFlags &= ~8;
            func_800B12F0(globalCtx, &this->backLeftHoof, &dustVel, &dustAcc, EnHorse_RandInt(100.0f) + 200,
                          EnHorse_RandInt(10.0f) + 30, EnHorse_RandInt(20.0f) + 30);
        }
        this->stateFlags &= ~ENHORSE_DRAW;
    }
}
#else
EnHorseActionFunc sActionFuncs[] = {
    EnHorse_Frozen,
    EnHorse_Inactive,
    EnHorse_Idle,
    EnHorse_FollowPlayer,
    EnHorse_UpdateIngoRace,
    func_808819D8,
    func_80881398,
    EnHorse_MountedIdle,
    EnHorse_MountedIdleWhinneying,
    EnHorse_MountedTurn,
    EnHorse_MountedWalk,
    EnHorse_MountedTrot,
    EnHorse_MountedGallop,
    EnHorse_MountedRearing,
    EnHorse_Stopping,
    EnHorse_Reverse,
    EnHorse_LowJump,
    EnHorse_HighJump,
    EnHorse_CutsceneUpdate,
    EnHorse_UpdateHorsebackArchery,
    EnHorse_FleePlayer,
    func_80884718,
    func_8087CA04,
    func_808848C8,
    func_80884A40,
    func_80884E0C,
};
Vec3f D_808891C8 = { 0.0f, 0.0f, 0.0f };
Vec3f D_808891D4 = { 0.0f, 1.0f, 0.0f };
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/EnHorse_Update.s")
#endif

s32 EnHorse_PlayerDirToMountSide(EnHorse* this, GlobalContext* globalCtx, Player* player) {
    if (this->playerDir == PLAYER_DIR_SIDE_L) {
        return -1;
    }

    if (this->playerDir == PLAYER_DIR_SIDE_R) {
        return 1;
    }

    return 0;
}

s32 EnHorse_MountSideCheck(EnHorse* this, GlobalContext* globalCtx, Player* player) {
    s32 mountSide;

    if (Actor_XZDistanceBetweenActors(&this->actor, &player->actor) > 75.0f) {
        return 0;
    }

    if (fabsf(this->actor.world.pos.y - player->actor.world.pos.y) > 30.0f) {
        return 0;
    }

    if (Math_CosS(Actor_YawBetweenActors(&player->actor, &this->actor) - player->actor.world.rot.y) <
        0.17364818f) { // cos(80 degrees)
        return 0;
    }

    mountSide = EnHorse_PlayerDirToMountSide(this, globalCtx, player);
    if (mountSide == -1) {
        return -1;
    }

    if (mountSide == 1) {
        return 1;
    }

    return 0;
}

s32 EnHorse_GetMountSide(EnHorse* this, GlobalContext* globalCtx) {
    if (this->action != ENHORSE_ACT_IDLE) {
        return 0;
    }

    if ((this->animationIdx != ENHORSE_ANIM_IDLE) && (this->animationIdx != ENHORSE_ANIM_WHINNEY)) {
        return 0;
    }

    return EnHorse_MountSideCheck(this, globalCtx, GET_PLAYER(globalCtx));
}

void EnHorse_RandomOffset(Vec3f* src, f32 dist, Vec3f* dst) {
    dst->x = ((Rand_ZeroOne() * (2.0f * dist)) + src->x) - dist;
    dst->y = ((Rand_ZeroOne() * (2.0f * dist)) + src->y) - dist;
    dst->z = ((Rand_ZeroOne() * (2.0f * dist)) + src->z) - dist;
}

void EnHorse_PostDraw(Actor* thisx, GlobalContext* globalCtx, Skin* skin) {
    s32 pad;
    EnHorse* this = THIS;
    Vec3f sp7C = { 0.0f, 0.0f, 0.0f };
    Vec3f hoofOffset = { 5.0f, -4.0f, 5.0f };
    Vec3f sp64;
    f32 curFrame = this->skin.skelAnime.curFrame;
    Vec3f center;
    Vec3f newCenter;
    s32 i;
    Vec3f sp38;
    f32 sp34;

    if (!(this->stateFlags & ENHORSE_CALC_RIDER_POS)) {
        if (this->type == HORSE_2) {
            Skin_GetVertexPos(skin, 5, 120, &this->riderPos);
            this->riderPos.y += 13.0f;
        } else {
            Vec3f riderOffset = { 600.0f, -1670.0f, 0.0f };

            Skin_GetLimbPos(skin, 30, &riderOffset, &this->riderPos);
        }
        this->riderPos.x -= this->actor.world.pos.x;
        this->riderPos.y -= this->actor.world.pos.y;
        this->riderPos.z -= this->actor.world.pos.z;
    } else {
        this->stateFlags &= ~ENHORSE_CALC_RIDER_POS;
    }

    if (this->type == HORSE_2) {
        Skin_GetLimbPos(skin, 13, &sp7C, &sp38);
    } else {
        Skin_GetLimbPos(skin, 13, &sp7C, &sp38);
    }

    SkinMatrix_Vec3fMtxFMultXYZW(&globalCtx->viewProjectionMtxF, &sp38, &this->unk_218, &sp34);

    if ((this->animationIdx == ENHORSE_ANIM_IDLE) && (this->action != ENHORSE_ACT_FROZEN) &&
        (((curFrame > 40.0f) && (curFrame < 45.0f) && (this->type == 0)) ||
         ((curFrame > 28.0f) && (curFrame < 33.0f) && (this->type == 1)))) {
        if (Rand_ZeroOne() < 0.02f) {
            this->dustFlags |= 1;
            Skin_GetLimbPos(skin, 28, &hoofOffset, &this->frontRightHoof);
            this->frontRightHoof.y -= 5.0f;
        }
    } else {
        if (this->action == ENHORSE_ACT_LOW_JUMP) {
            if (((curFrame > 10.0f) && (curFrame < 13.0f)) || ((curFrame > 25.0f) && (curFrame < 33.0f))) {
                if (Rand_ZeroOne() < 0.02f) {
                    this->dustFlags |= 2;
                    if (this->type == HORSE_2) {
                        Skin_GetLimbPos(skin, 20, &hoofOffset, &sp64);
                    } else {
                        Skin_GetLimbPos(skin, 20, &hoofOffset, &sp64);
                    }
                    EnHorse_RandomOffset(&sp64, 10.0f, &this->frontLeftHoof);
                }

                if (Rand_ZeroOne() < 0.02f) {
                    this->dustFlags |= 1;
                    if (this->type == HORSE_2) {
                        Skin_GetLimbPos(skin, 28, &hoofOffset, &sp64);
                    } else {
                        curFrame = curFrame;
                        Skin_GetLimbPos(skin, 28, &hoofOffset, &sp64);
                    }
                    EnHorse_RandomOffset(&sp64, 10.0f, &this->frontRightHoof);
                }
            }

            if (((curFrame > 6.0f) && (curFrame < 10.0f)) || ((curFrame > 23.0f) && (curFrame < 29.0f))) {
                if (Rand_ZeroOne() < 0.02f) {
                    this->dustFlags |= 8;
                    if (this->type == HORSE_2) {
                        Skin_GetLimbPos(skin, 36, &hoofOffset, &sp64);
                    } else {
                        Skin_GetLimbPos(skin, 37, &hoofOffset, &sp64);
                    }
                    EnHorse_RandomOffset(&sp64, 10.0f, &this->backLeftHoof);
                }
            }

            if ((((curFrame > 7.0f) && (curFrame < 14.0f)) || ((curFrame > 26.0f) && (curFrame < 30.0f))) &&
                (Rand_ZeroOne() < 0.02f)) {
                this->dustFlags |= 4;
                if (this->type == HORSE_2) {
                    Skin_GetLimbPos(skin, 44, &hoofOffset, &sp64);
                } else {
                    Skin_GetLimbPos(skin, 45, &hoofOffset, &sp64);
                }
                EnHorse_RandomOffset(&sp64, 10.0f, &this->backRightHoof);
            }
        } else if (this->animationIdx == ENHORSE_ANIM_GALLOP) {
            if ((curFrame > 14.0f) && (curFrame < 16.0f) && (Rand_ZeroOne() < 0.02f)) {
                this->dustFlags |= 1;
                if (this->type == HORSE_2) {
                    Skin_GetLimbPos(skin, 28, &hoofOffset, &sp64);
                } else {
                    Skin_GetLimbPos(skin, 28, &hoofOffset, &sp64);
                }
                EnHorse_RandomOffset(&sp64, 5.0f, &this->frontRightHoof);
            } else if ((curFrame > 8.0f) && (curFrame < 10.0f) && (Rand_ZeroOne() < 0.02f)) {
                this->dustFlags |= 2;
                if (this->type == HORSE_2) {
                    Skin_GetLimbPos(skin, 20, &hoofOffset, &sp64);
                } else {
                    Skin_GetLimbPos(skin, 20, &hoofOffset, &sp64);
                }
                EnHorse_RandomOffset(&sp64, 10.0f, &this->frontLeftHoof);
            } else if ((curFrame > 1.0f) && (curFrame < 3.0f) && (Rand_ZeroOne() < 0.02f)) {
                this->dustFlags |= 4;
                if (this->type == HORSE_2) {
                    Skin_GetLimbPos(skin, 44, &hoofOffset, &sp64);
                } else {
                    Skin_GetLimbPos(skin, 45, &hoofOffset, &sp64);
                }
                EnHorse_RandomOffset(&sp64, 10.0f, &this->backRightHoof);
            } else if ((curFrame > 26.0f) && (curFrame < 28.0f) && (Rand_ZeroOne() < 0.02f)) {
                this->dustFlags |= 8;
                if (this->type == HORSE_2) {
                    Skin_GetLimbPos(skin, 36, &hoofOffset, &sp64);
                } else {
                    Skin_GetLimbPos(skin, 37, &hoofOffset, &sp64);
                }
                EnHorse_RandomOffset(&sp64, 10.0f, &this->backLeftHoof);
            }
        } else if ((this->action == ENHORSE_ACT_BRIDGE_JUMP) && (curFrame > 6.0f) &&
                   (Rand_ZeroOne() < (1.0f - ((curFrame - 6.0f) * (1.0f / 17.0f))))) {
            if (Rand_ZeroOne() < 0.05f) {
                this->dustFlags |= 8;
                if (this->type == HORSE_2) {
                    Skin_GetLimbPos(skin, 36, &hoofOffset, &sp64);
                } else {
                    Skin_GetLimbPos(skin, 37, &hoofOffset, &sp64);
                }
                EnHorse_RandomOffset(&sp64, 10.0f, &this->backLeftHoof);
            }
            if (Rand_ZeroOne() < 0.02f) {
                this->dustFlags |= 4;
                if (this->type == HORSE_2) {
                    Skin_GetLimbPos(skin, 44, &hoofOffset, &sp64);
                } else {
                    Skin_GetLimbPos(skin, 45, &hoofOffset, &sp64);
                }
                EnHorse_RandomOffset(&sp64, 10.0f, &this->backRightHoof);
            }
        } else if ((this->action == ENHORSE_ACT_CS_UPDATE) && (curFrame > 5.0f)) {
            if (Rand_ZeroOne() < (1.0f - ((curFrame - 5.0f) * 0.04f))) {
                if (Rand_ZeroOne() < 0.05f) {
                    this->dustFlags |= 8;
                    if (this->type == HORSE_2) {
                        Skin_GetLimbPos(skin, 36, &hoofOffset, &sp64);
                    } else {
                        Skin_GetLimbPos(skin, 37, &hoofOffset, &sp64);
                    }
                    EnHorse_RandomOffset(&sp64, 10.0f, &this->backLeftHoof);
                }

                if (Rand_ZeroOne() < 0.02f) {
                    this->dustFlags |= 4;
                    if (this->type == HORSE_2) {
                        Skin_GetLimbPos(skin, 44, &hoofOffset, &sp64);
                    } else {
                        Skin_GetLimbPos(skin, 45, &hoofOffset, &sp64);
                    }
                    EnHorse_RandomOffset(&sp64, 10.0f, &this->backRightHoof);
                }
            }
        }
    }

    for (i = 0; i < this->colliderJntSph.count; i++) {
        center.x = this->colliderJntSph.elements[i].dim.modelSphere.center.x;
        center.y = this->colliderJntSph.elements[i].dim.modelSphere.center.y;
        center.z = this->colliderJntSph.elements[i].dim.modelSphere.center.z;

        Skin_GetLimbPos(skin, this->colliderJntSph.elements[i].dim.limb, &center, &newCenter);

        this->colliderJntSph.elements[i].dim.worldSphere.center.x = newCenter.x;
        this->colliderJntSph.elements[i].dim.worldSphere.center.y = newCenter.y;
        this->colliderJntSph.elements[i].dim.worldSphere.center.z = newCenter.z;

        this->colliderJntSph.elements[i].dim.worldSphere.radius =
            this->colliderJntSph.elements[i].dim.modelSphere.radius * this->colliderJntSph.elements[i].dim.scale;
    }

    //! @bug Setting colliders in a draw function allows for duplicate entries to be added to their respective lists
    //! under certain conditions, like when pausing and unpausing the game.
    //! Actors will draw for a couple of frames between the pauses, but some important logic updates will not occur.
    //! In the case of OC, this can cause unwanted effects such as a very large amount of displacement being applied to
    //! a colliding actor.
    if (!(this->stateFlags & ENHORSE_JUMPING)) {
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderJntSph.base);
    }
}

s32 EnHorse_OverrideLimbDraw(Actor* thisx, GlobalContext* globalCtx, s32 limbIndex, Skin* skin) {
    static TexturePtr D_80889204[] = {
        object_horse_link_child_Tex_001D28,
        object_horse_link_child_Tex_001928,
        object_horse_link_child_Tex_001B28,
    };
    static u8 D_80889210[] = { 0, 1, 2, 1 };
    EnHorse* this = THIS;
    s32 drawOriginalLimb = true;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    if ((limbIndex != 13) || (this->type != HORSE_EPONA)) {
        if ((limbIndex == 13) && (this->type == HORSE_2)) {
            u8 idx = D_80889210[this->blinkTimer];

            gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80889204[idx]));
        } else if ((this->type == HORSE_HNI) && (this->stateFlags & ENHORSE_FLAG_18) && (limbIndex == 30)) {
            drawOriginalLimb = false;
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);

    return drawOriginalLimb;
}

s32 func_80888D18(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    Vec3f sp1C = { -98.0f, -1454.0f, 0.0f };
    EnHorse* this = THIS;

    if (limbIndex == 3) {
        Matrix_MultiplyVector3fByState(&sp1C, &this->riderPos);
    }
    return false;
}

void EnHorse_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnHorse* this = THIS;

    if (!(this->stateFlags & ENHORSE_INACTIVE) && (this->actor.update != func_8087D540)) {
        func_8012C28C(globalCtx->state.gfxCtx);
        this->stateFlags |= ENHORSE_DRAW;
        if (!(this->unk_1EC & 1)) {
            if (this->stateFlags & ENHORSE_JUMPING) {
                func_80138258(&this->actor, globalCtx, &this->skin, EnHorse_PostDraw, EnHorse_OverrideLimbDraw, false);
            } else {
                func_80138258(&this->actor, globalCtx, &this->skin, EnHorse_PostDraw, EnHorse_OverrideLimbDraw, true);
            }
        } else {
            if (this->stateFlags & ENHORSE_JUMPING) {
                this->skin.skelAnime.jointTable->x = 0;
                this->skin.skelAnime.jointTable->y = 0;
                this->skin.skelAnime.jointTable->z = 0;
            }
            SkelAnime_DrawFlexOpa(globalCtx, this->skin.skelAnime.skeleton, this->skin.skelAnime.jointTable,
                                  this->skin.skelAnime.dListCount, func_80888D18, NULL, &this->actor);
        }

        if (this->postDrawFunc != NULL) {
            this->postDrawFunc(this, globalCtx);
        }
    }
}
