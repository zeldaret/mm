/*
 * File: z_en_tk.c
 * Overlay: ovl_En_Tk
 * Description: Dampé
 */

#include "z_en_tk.h"
#include "overlays/actors/ovl_Bg_Danpei_Movebg/z_bg_danpei_movebg.h"
#include "overlays/actors/ovl_En_Door/z_en_door.h"
#include "objects/object_tk/object_tk.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY)

#define THIS ((EnTk*)thisx)

void EnTk_Init(Actor* thisx, PlayState* play);
void EnTk_Destroy(Actor* thisx, PlayState* play);
void EnTk_Update(Actor* thisx, PlayState* play);
void EnTk_Draw(Actor* thisx, PlayState* play);

void func_80AECA3C(EnTk* this, PlayState* play);
void func_80AECA90(EnTk* this, PlayState* play);
void func_80AECB0C(EnTk* this, PlayState* play);
void func_80AECB6C(EnTk* this, PlayState* play);
void func_80AECE0C(EnTk* this, PlayState* play);
s32 func_80AECE60(EnTk* this, PlayState* play);
s32 func_80AED354(EnTk* this, PlayState* play, ScheduleOutput* scheduleOutput);
s32 func_80AED38C(EnTk* this, PlayState* play, ScheduleOutput* scheduleOutput);
void func_80AED4F8(EnTk* this, PlayState* play);
void func_80AED610(EnTk* this, PlayState* play);
void func_80AED898(EnTk* this, PlayState* play);
void func_80AED940(EnTk* this, PlayState* play);
void func_80AEDC4C(EnTk* this, PlayState* play);
void func_80AEDCBC(EnTk* this, PlayState* play);
void func_80AEDD4C(EnTk* this, PlayState* play);
void func_80AEDE10(EnTk* this, PlayState* play);
void func_80AEDF5C(EnTk* this, PlayState* play);
void func_80AEE2A8(EnTk* this, PlayState* play);
void func_80AEE2C0(EnTk* this, PlayState* play);
void func_80AEE374(EnTk* this, PlayState* play);
void func_80AEE414(EnTk* this, PlayState* play);
void func_80AEE478(EnTk* this, PlayState* play);
void func_80AEE4D0(EnTk* this, PlayState* play);
void func_80AEE650(EnTk* this, PlayState* play);
void func_80AEE6B8(EnTk* this, PlayState* play);
void func_80AEE784(EnTk* this, PlayState* play);
void func_80AEE9B0(EnTk* this, PlayState* play);
void func_80AEEAD4(EnTk* this, PlayState* play);
void func_80AEEB88(EnTk* this, PlayState* play);
void func_80AEED38(EnTk* this, PlayState* play);
void func_80AEF048(EnTk* this, PlayState* play);
void func_80AEF094(EnTk* this, PlayState* play);
void func_80AEF15C(EnTk* this, PlayState* play);
void func_80AEF1B4(EnTk* this, PlayState* play);
void func_80AEF1C4(EnTk* this, PlayState* play);
void func_80AEF210(EnTk* this, PlayState* play);
void func_80AEF220(EnTk* this, PlayState* play);
void func_80AEF278(EnTk* this, PlayState* play);
void func_80AEF2C8(Actor* thisx, PlayState* play);
void func_80AEF2D8(Actor* thisx, PlayState* play);
void func_80AEF5F4(Actor* thisx, PlayState* play);

static s32 D_80AF0050;

static u8 D_80AEF800[] = {
    /* 0x0 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(6, 0, 18, 0, 0x8 - 0x7),
    /* 0x7 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x8 */ SCHEDULE_CMD_RET_TIME(6, 0, 18, 0, 1),
    /* 0xE */ SCHEDULE_CMD_RET_NONE(),
};

ActorInit En_Tk_InitVars = {
    ACTOR_EN_TK,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_TK,
    sizeof(EnTk),
    (ActorFunc)EnTk_Init,
    (ActorFunc)EnTk_Destroy,
    (ActorFunc)EnTk_Update,
    (ActorFunc)EnTk_Draw,
};

static ColliderCylinderInit sCylinderInit = {
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
    { 30, 52, 0, { 0, 0, 0 } },
};

// part of the collider??
static u32 D_80AEF85C[] = {
    0x00000000,
    0x00000000,
    0xFF000000,
};

static AnimationSpeedInfo D_80AEF868[] = {
    { &object_tk_Anim_001FA8, 1.0f, ANIMMODE_LOOP, -10.0f }, { &object_tk_Anim_001FA8, 2.0f, ANIMMODE_LOOP, -10.0f },
    { &object_tk_Anim_0030A4, 1.0f, ANIMMODE_LOOP, -10.0f }, { &object_tk_Anim_001144, 1.0f, ANIMMODE_ONCE, -10.0f },
    { &object_tk_Anim_003724, 1.0f, ANIMMODE_ONCE, -10.0f }, { &object_tk_Anim_003FB8, 1.0f, ANIMMODE_LOOP, -10.0f },
    { &object_tk_Anim_0020C8, 1.0f, ANIMMODE_LOOP, -10.0f }, { &object_tk_Anim_003B10, 1.0f, ANIMMODE_LOOP, -10.0f },
};

static s32 D_80AEF8E8[2] = { 0, 0 };

static f32 D_80AEF8F0[] = {
    0.637399971485f, 0.637399971485f, 0.637399971485f, 0.637399971485f, 0.637399971485f, 0.637399971485f,
    0.637399971485f, 0.637399971485f, 0.637399971485f, 0.637399971485f, 0.637399971485f, 0.637399971485f,
    1.88639998436f,  3.44770002365f,  5.29629993439f,  7.39470005035f,  9.60550022125f,  11.9537000656f,
    14.30189991f,    16.6000995636f,  18.8108997345f,  20.8342990875f,  22.6203994751f,  24.1441993713f,
    25.3057994843f,  25.3057994843f,  25.3057994843f,  25.3057994843f,  25.3057994843f,  25.3057994843f,
    25.3057994843f,  25.3057994843f,  25.3057994843f,  25.3057994843f,  25.3057994843f,  25.3057994843f,
    25.3057994843f,  26.5048999786f,  28.0412006378f,  29.9146995544f,  31.9881000519f,  34.2238998413f,
    36.572101593f,   38.932800293f,   41.28099823f,    43.5416984558f,  45.6276016235f,  47.4511985779f,
    49.0f,
};

typedef struct {
    /* 0x0 */ Actor* unk_00;
    /* 0x4 */ f32 unk_04;
} EnTkStruct; // size = 0x8

void func_80AEC460(EnTk* this) {
    if (DECR(this->unk_2C4) == 0) {
        this->unk_2C2++;
        if (this->unk_2C2 >= 3) {
            this->unk_2C0--;
            if (this->unk_2C0 < 0) {
                this->unk_2C4 = Rand_S16Offset(30, 30);
                this->unk_2C0 = 2;
                if (Rand_ZeroOne() > 0.5f) {
                    this->unk_2C0++;
                }
            }
            this->unk_2C2 = 0;
        }
    }
}

f32 func_80AEC524(f32 arg0) {
    f32 temp_f0;
    f32 ret;
    s32 temp_a0;
    s32 temp_a1;

    while ((arg0 >= ARRAY_COUNT(D_80AEF8F0)) || (arg0 < 0.0f)) {
        if (arg0 >= ARRAY_COUNT(D_80AEF8F0)) {
            arg0 -= ARRAY_COUNT(D_80AEF8F0);
        } else if (arg0 < 0.0f) {
            arg0 += ARRAY_COUNT(D_80AEF8F0);
        }
    }

    // temp_f0 always becomes 0
    temp_a1 = arg0;
    temp_a0 = temp_a1 + 1;
    temp_f0 = arg0 - temp_a1;

    if (arg0 != temp_a1) {
        if (temp_a0 >= ARRAY_COUNT(D_80AEF8F0)) {
            temp_a0 -= ARRAY_COUNT(D_80AEF8F0);
            ret = (((D_80AEF8F0[temp_a0] + D_80AEF8F0[ARRAY_COUNT(D_80AEF8F0) - 1]) - D_80AEF8F0[temp_a1]) * temp_f0) +
                  D_80AEF8F0[temp_a1];
        } else {
            ret = ((D_80AEF8F0[temp_a0] - D_80AEF8F0[temp_a1]) * temp_f0) + D_80AEF8F0[temp_a1];
        }
    } else {
        ret = D_80AEF8F0[temp_a1];
    }
    return ret;
}

void func_80AEC658(SkelAnime* skelAnime, f32 arg1, f32 arg2, f32* arg3, f32* arg4) {
    static f32 D_80AEF9B4[] = { 0.95f, 0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,
                                0.0f,  0.0f,  1.0f,  1.25f, 1.48f, 1.68f, 1.77f, 1.88f, 1.88f, 1.84f,
                                1.77f, 1.62f, 1.43f, 1.22f, 0.93f, 0.0f,  0.0f,  0.0f,  0.0f,  0.0f,
                                0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.96f, 1.23f, 1.5f,
                                1.66f, 1.79f, 1.88f, 1.89f, 1.88f, 1.81f, 1.67f, 1.46f, 1.24f };

    *arg3 = D_80AEF9B4[(s32)skelAnime->curFrame] * 0.5f * skelAnime->playSpeed * arg2;
    *arg4 = (func_80AEC524(skelAnime->curFrame) - func_80AEC524(arg1)) * arg2;

    while (*arg4 < 0.0f) {
        *arg4 += D_80AEF8F0[(s32)skelAnime->animLength - 1] * arg2;
    }
}

void EnTk_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnTk* this = THIS;

    this->unk_2B0 = ENTK_GET_F(&this->actor);
    this->unk_2B1 = ENTK_GET_7F0(&this->actor);
    Collider_InitCylinder(play, &this->collider);

    if (Flags_GetSwitch(play, this->unk_2B1)) {
        if (this->unk_2B0 == 0) {
            Actor_Kill(&this->actor);
            return;
        }
    } else if (this->unk_2B0 == 2) {
        Actor_Kill(&this->actor);
        return;
    }

    if ((this->unk_2B0 == 1) || (this->unk_2B0 == 3)) {
        this->actor.flags &= ~(ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY);
        this->actor.update = func_80AEF2C8;
        this->actor.draw = NULL;
        return;
    }

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 24.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &object_tk_Skel_00B9E8, NULL, this->jointTable, this->morphTable, 18);
    Animation_Change(&this->skelAnime, &object_tk_Anim_0030A4, 1.0f, 0.0f,
                     Animation_GetLastFrame(&object_tk_Anim_0030A4.common), ANIMMODE_LOOP, 0.0f);
    this->unk_318 = 0;
    this->unk_2D4 = -1;
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.targetMode = TARGET_MODE_1;
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;

    if (this->unk_2B0 == 2) {
        this->unk_316 = 0;
        this->actor.update = func_80AEF5F4;
        func_80AECA3C(this, play);
        return;
    }

    Collider_SetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    this->actor.gravity = -1.0f;
    this->actor.shape.rot.y = this->actor.world.rot.y;
    this->actor.flags |= ACTOR_FLAG_10;
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_80AEF868, 0, &this->unk_2D4);
    SubS_FillCutscenesList(&this->actor, this->csIdList, ARRAY_COUNT(this->csIdList));

    switch (this->unk_2B0) {
        case 4:
            if (D_80AF0050 != 0) {
                Actor_Kill(&this->actor);
                return;
            }
            D_80AF0050 = 1;
            this->actor.room = -1;
            this->actor.update = func_80AEF2D8;
            this->unk_2D8 = 0.0f;
            func_80AECB0C(this, play);
            func_80AEF2D8(&this->actor, play);
            break;

        case 0:
            this->unk_2D0 = -1;
            this->unk_310 = 0;
            this->unk_2E4 = 0;
            func_80AED898(this, play);
            break;

        default:
            Actor_Kill(&this->actor);
            return;
    }
}

void EnTk_Destroy(Actor* thisx, PlayState* play) {
    EnTk* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void func_80AECA3C(EnTk* this, PlayState* play) {
    this->unk_316 = 0;
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_80AEF868, 2, &this->unk_2D4);
    this->actionFunc = func_80AECA90;
}

void func_80AECA90(EnTk* this, PlayState* play) {
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        play->msgCtx.msgMode = MSGMODE_NONE;
        play->msgCtx.msgLength = 0;
        func_80AEDE10(this, play);
    } else if (this->actor.xzDistToPlayer < 100.0f) {
        Actor_OfferTalk(&this->actor, play, 100.0f);
    }
}

void func_80AECB0C(EnTk* this, PlayState* play) {
    this->actor.speed = 0.0f;
    this->unk_3CC = 0xFF;
    this->unk_2DC = 0.0f;
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_80AEF868, 0, &this->unk_2D4);
    this->actionFunc = func_80AECB6C;
}

void func_80AECB6C(EnTk* this, PlayState* play) {
    f32 temp_f0;
    s32 temp2;
    s32 temp3;
    f32 sp48;
    f32 sp44;
    ScheduleOutput sp34;
    u8 temp4;

    this->actor.textId = 0;
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        play->msgCtx.msgMode = MSGMODE_NONE;
        play->msgCtx.msgLength = 0;
        func_80AED4F8(this, play);
        return;
    }

    if (R_TIME_SPEED != 0.0f) {
        this->skelAnime.playSpeed = (f32)func_800FE620(play) / R_TIME_SPEED;
    } else {
        this->skelAnime.playSpeed = 0.0f;
    }

    if (this->unk_2CA & 0x10) {
        SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_80AEF868, 5, &this->unk_2D4);
        sp48 = 1.0f;
        sp44 = 22.0f;
    } else {
        func_80AEC658(&this->skelAnime, this->unk_320, 1.0f, &sp48, &sp44);
    }

    temp2 = R_TIME_SPEED * sp44;
    temp_f0 = temp2;

    this->unk_2DC += (R_TIME_SPEED * sp44) - temp2;
    temp3 = this->unk_2DC;
    this->timePathTimeSpeed = temp2 + temp3;
    this->unk_2DC -= temp3;
    this->unk_2E0 += R_TIME_SPEED;

    if (Schedule_RunScript(play, D_80AEF800, &sp34)) {
        if ((this->unk_3CC != sp34.result) && !func_80AED354(this, play, &sp34)) {
            return;
        }
        temp4 = sp34.result;
    } else {
        sp34.result = 0;
        temp4 = sp34.result;
    }

    if (!temp4 && (this->unk_3CC != 0)) {
        this->actor.draw = NULL;
        this->actor.flags &= ~ACTOR_FLAG_TARGETABLE;
    } else if (temp4 && (this->unk_3CC == 0)) {
        this->actor.flags |= ACTOR_FLAG_TARGETABLE;
        this->actor.draw = EnTk_Draw;
    }

    this->unk_3CC = sp34.result;
    func_80AECE0C(this, play);

    if (this->unk_3CE & 8) {
        this->actor.flags &= ~ACTOR_FLAG_TARGETABLE;
        this->actor.draw = NULL;
    }
}

void func_80AECE0C(EnTk* this, PlayState* play) {
    if (this->unk_3CC != 0) {
        if (1) {}
        func_80AECE60(this, play);
    }
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.world.rot.y, 4, 0x1555, 0xB6);
}

s32 func_80AECE60(EnTk* this, PlayState* play) {
    EnDoor* door;
    f32 knots[265];
    Vec3f sp94;
    Vec3f sp88;
    Vec3f timePathTargetPos;
    s32 sp78;
    s32 sp74;
    s32 pad;

    SubS_TimePathing_FillKnots(knots, SUBS_TIME_PATHING_ORDER, this->timePath->count + SUBS_TIME_PATHING_ORDER);
    if (!(this->unk_3CE & 4)) {
        timePathTargetPos = gZeroVec3f;
        SubS_TimePathing_Update(this->timePath, &this->timePathProgress, &this->timePathElapsedTime,
                                this->timePathWaypointTime, this->timePathTotalTime, &this->timePathWaypoint, knots,
                                &timePathTargetPos, this->timePathTimeSpeed);
        SubS_TimePathing_ComputeInitialY(play, this->timePath, this->timePathWaypoint, &timePathTargetPos);
        this->actor.world.pos.y = timePathTargetPos.y;
    } else {
        timePathTargetPos = this->timePathTargetPos;
    }

    this->actor.world.pos.x = timePathTargetPos.x;
    this->actor.world.pos.z = timePathTargetPos.z;

    if (!(this->unk_3CE & 4)) {
        Math_Vec3f_Copy(&this->actor.prevPos, &this->actor.world.pos);
        this->unk_3CE |= 4;
    }

    if ((play->transitionMode != TRANS_MODE_OFF) || (this->timePathTimeSpeed == 0)) {
        sp78 = this->timePathElapsedTime;
        sp74 = this->timePathWaypoint;
        timePathTargetPos = this->actor.world.pos;
    }

    this->timePathTargetPos = gZeroVec3f;

    if (SubS_TimePathing_Update(this->timePath, &this->timePathProgress, &this->timePathElapsedTime,
                                this->timePathWaypointTime, this->timePathTotalTime, &this->timePathWaypoint, knots,
                                &this->timePathTargetPos, this->timePathTimeSpeed)) {
        this->unk_3CE |= 8;
    } else {
        sp94 = this->actor.world.pos;
        sp88 = this->timePathTargetPos;
        this->actor.world.rot.y = Math_Vec3f_Yaw(&sp94, &sp88);
    }

    if ((play->transitionMode != TRANS_MODE_OFF) || (this->timePathTimeSpeed == 0)) {
        this->timePathElapsedTime = sp78;
        this->timePathWaypoint = sp74;
        this->timePathTargetPos = timePathTargetPos;
    }

    door = NULL;
    if (!(this->unk_2CA & 0xC00)) {
        Actor* doorIter = NULL;

        do {
            doorIter = SubS_FindActor(play, doorIter, ACTORCAT_DOOR, ACTOR_EN_DOOR);
            if (doorIter != NULL) {
                if (Actor_WorldDistXZToActor(&this->actor, doorIter) <= 120.0f) {
                    if (ABS(BINANG_SUB(Actor_WorldYawTowardPoint(&this->actor, &doorIter->world.pos),
                                       this->actor.shape.rot.y)) <= 0x2000) {
                        this->unk_2CA |= 0x400;
                        door = (EnDoor*)doorIter;
                        break;
                    }
                }
                doorIter = doorIter->next;
            }
        } while (doorIter != NULL);
    } else {
        Actor* doorIter = NULL;

        do {
            doorIter = SubS_FindActor(play, doorIter, ACTORCAT_DOOR, ACTOR_EN_DOOR);
            if (doorIter != NULL) {
                if (Actor_WorldDistXZToActor(&this->actor, doorIter) <= 160.0f) {
                    door = (EnDoor*)doorIter;
                    break;
                }
                doorIter = doorIter->next;
            }
        } while (doorIter != NULL);
    }

    if ((door != NULL) && (this->unk_2CA & 0x400)) {
        Vec3f sp5C;

        Actor_OffsetOfPointInActorCoords(&this->actor, &sp5C, &door->knobDoor.dyna.actor.world.pos);
        door->unk_1A7 = 2;
        if (sp5C.z < -20.0f) {
            this->unk_2CA &= ~0x400;
            this->unk_2CA |= 0x800;
        }
    }

    if (door != NULL) {
        if ((this->unk_2CA & 0x800) && (door->unk_1A7 == 0)) {
            this->unk_2CA &= ~0x800;
        }
    }

    if (!(this->unk_3CE & 8) && !(this->unk_2CA & 0x10) && (this->actor.xzDistToPlayer < 100.0f)) {
        SubS_OfferTalkExchangeFacing(&this->actor, play, 100.0f, 100.0f, PLAYER_IA_NONE, 0x4000, 0x4000);
    }

    return false;
}

s32 func_80AED354(EnTk* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    s32 phi_v1 = false;

    if (scheduleOutput->result != 0) {
        phi_v1 = func_80AED38C(this, play, scheduleOutput);
    }
    return phi_v1;
}

s32 func_80AED38C(EnTk* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    u16 sp1E = SCHEDULE_TIME_NOW;
    u8 pathIndex = ENTK_GET_PATH_INDEX(&this->actor);
    u16 phi_a1;
    s32 index = scheduleOutput->result - 1;
    u16 tmp;

    this->timePath = SubS_GetAdditionalPath(play, pathIndex, D_80AEF8E8[index + 1]);
    if (this->timePath == NULL) {
        return false;
    }

    if ((this->unk_3CC <= 0) && (this->unk_3CC != 0) && (this->timePathTimeSpeed >= 0)) {
        phi_a1 = sp1E;
    } else {
        phi_a1 = scheduleOutput->time0;
    }

    this->timePathTotalTime = scheduleOutput->time1 - phi_a1;
    this->timePathElapsedTime = sp1E - phi_a1;
    tmp = phi_a1 = this->timePath->count - (SUBS_TIME_PATHING_ORDER - 1);
    this->timePathWaypointTime = this->timePathTotalTime / tmp;
    this->timePathWaypoint = (this->timePathElapsedTime / this->timePathWaypointTime) + (SUBS_TIME_PATHING_ORDER - 1);
    this->unk_3CE &= ~4;
    this->unk_3CE &= ~8;
    return true;
}

void func_80AED4F8(EnTk* this, PlayState* play) {
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_80AEF868, 2, &this->unk_2D4);
    this->actionFunc = func_80AED610;
}

void func_80AED544(EnTk* this, PlayState* play) {
    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_31_10)) {
        Message_StartTextbox(play, 0x13FE, &this->actor);
        SET_WEEKEVENTREG(WEEKEVENTREG_31_10);
    } else if (gSaveContext.save.time < CLOCK_TIME(9, 0)) {
        Message_StartTextbox(play, 0x13FF, &this->actor);
    } else if (gSaveContext.save.time < CLOCK_TIME(12, 0)) {
        Message_StartTextbox(play, 0x1400, &this->actor);
    } else if (gSaveContext.save.time < CLOCK_TIME(15, 0)) {
        Message_StartTextbox(play, 0x1401, &this->actor);
    } else {
        Message_StartTextbox(play, 0x1402, &this->actor);
    }
}

void func_80AED610(EnTk* this, PlayState* play) {
    if ((this->unk_2D4 == 4) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_80AEF868, 7, &this->unk_2D4);
    }

    switch (Message_GetState(&play->msgCtx)) {
        case TEXT_STATE_NONE:
            if (Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer - 0x1555, 0x71C)) {
                if (Player_GetMask(play) == PLAYER_MASK_CAPTAIN) {
                    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_80AEF868, 4, &this->unk_2D4);
                    Message_StartTextbox(play, 0x13FD, &this->actor);
                } else if (CURRENT_DAY != 2) {
                    func_80AED544(this, play);
                } else if (!Flags_GetSwitch(play, ENTK_GET_7F0(&this->actor))) {
                    Message_StartTextbox(play, 0x1403, &this->actor);
                } else if (CHECK_WEEKEVENTREG(WEEKEVENTREG_60_02)) {
                    func_80AED544(this, play);
                } else {
                    Message_StartTextbox(play, 0x1413, &this->actor);
                }
                break;
            }

        case TEXT_STATE_1:
        case TEXT_STATE_CLOSING:
        case TEXT_STATE_3:
            break;

        case TEXT_STATE_CHOICE:
        case TEXT_STATE_5:
        case TEXT_STATE_DONE:
            if (Message_ShouldAdvance(play)) {
                switch (play->msgCtx.currentTextId) {
                    case 0x13FD:
                        this->unk_2CA |= 0x10;
                        SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_80AEF868, 0, &this->unk_2D4);
                        this->skelAnime.playSpeed = 10.0f;
                        this->actionFunc = func_80AECB6C;
                        break;

                    case 0x13FE:
                        Message_ContinueTextbox(play, 0x13FF);
                        break;

                    case 0x1413:
                        Rupees_ChangeBy(30);
                        SET_WEEKEVENTREG(WEEKEVENTREG_60_02);
                        Message_ContinueTextbox(play, 0x13FF);
                        break;

                    case 0x13FF:
                    case 0x1400:
                    case 0x1401:
                    case 0x1402:
                    case 0x1403:
                    case 0x1404:
                    case 0x1405:
                    case 0x1406:
                    case 0x1407:
                    case 0x1408:
                    case 0x1409:
                    case 0x140A:
                    case 0x140B:
                    case 0x140C:
                    case 0x140D:
                    case 0x140E:
                    case 0x140F:
                    case 0x1410:
                    case 0x1411:
                    case 0x1412:
                    default:
                        SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_80AEF868, 0, &this->unk_2D4);
                        this->actionFunc = func_80AECB6C;
                        break;
                }
            }
            break;
    }
}

void func_80AED898(EnTk* this, PlayState* play) {
    this->unk_316 = 0;
    this->actor.speed = 0.0f;
    if (this->unk_2CA & 0x1000) {
        if ((this->unk_2D4 == 4) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
            SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_80AEF868, 7, &this->unk_2D4);
        }
    } else {
        SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_80AEF868, 2, &this->unk_2D4);
    }
    this->actionFunc = func_80AED940;
}

void func_80AED940(EnTk* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    Actor* actor;
    Vec3f sp44;

    if ((this->unk_2D4 != 4) && (this->unk_2D4 != 7)) {
        s16 temp_v0 = (this->actor.shape.rot.y - this->actor.yawTowardsPlayer) + 0x1555;

        if (ABS(temp_v0) < 0x1800) {
            Math_SmoothStepToS(&this->unk_31C, temp_v0, 3, 0x71C, 0);
        } else {
            Math_SmoothStepToS(&this->unk_31C, 0, 3, 0x71C, 0);
        }

        Math_Vec3f_Copy(&sp44, &player->actor.world.pos);
        sp44.y = player->bodyPartsPos[PLAYER_BODYPART_HEAD].y + 3.0f;
        temp_v0 = Math_Vec3f_Pitch(&this->actor.focus.pos, &sp44);
        if (ABS(temp_v0) < 0x800) {
            Math_SmoothStepToS(&this->unk_31A, temp_v0, 3, 0x16C, 0);
        } else {
            Math_SmoothStepToS(&this->unk_31A, 0, 3, 0x16C, 0);
        }
    }

    if ((this->unk_2D4 == 4) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_80AEF868, 7, &this->unk_2D4);
    }

    if (!(this->unk_2CA & 0x40)) {
        actor = NULL;

        do {
            actor = SubS_FindActor(play, actor, ACTORCAT_NPC, ACTOR_EN_TK);
            if (actor != NULL) {
                if (ENTK_GET_F(actor) == 1) {
                    Math_Vec3f_Copy(&this->unk_2EC, &actor->world.pos);
                    Math_Vec3s_Copy(&this->unk_2F8, &actor->world.rot);
                    Actor_Kill(actor);
                    this->unk_2CA |= 0x40;
                    break;
                }
                actor = actor->next;
            }
        } while (actor != NULL);
    }

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->unk_2CA &= ~0x80;
        this->actor.flags &= ~ACTOR_FLAG_10000;
        play->msgCtx.msgMode = MSGMODE_NONE;
        play->msgCtx.msgLength = 0;
        func_80AEDE10(this, play);
    } else if (!(this->unk_2CA & 0x80)) {
        if (this->actor.xzDistToPlayer < 100.0f) {
            SubS_OfferTalkExchangeFacing(&this->actor, play, 100.0f, 100.0f, PLAYER_IA_NONE, 0x4000, 0x4000);
        }
    } else {
        Actor_OfferTalkExchange(&this->actor, play, this->actor.xzDistToPlayer, this->actor.playerHeightRel,
                                PLAYER_IA_NONE);
    }
}

void func_80AEDBEC(EnTk* this, PlayState* play) {
    this->actor.params = -1;
    this->csLength = 0;
    this->actor.speed = 0.0f;
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_80AEF868, 2, &this->unk_2D4);
    this->actionFunc = func_80AEDC4C;
}

void func_80AEDC4C(EnTk* this, PlayState* play) {
    if ((this->actor.params >= 0) &&
        SubS_StartCutscene(&this->actor, this->csIdList[1], this->actor.params, SUBS_CUTSCENE_WITH_PLAYER)) {
        this->csLength = CutsceneManager_GetLength(this->csIdList[1]);
        Message_ContinueTextbox(play, 0x1411);
        func_80AEDCBC(this, play);
    }
}

void func_80AEDCBC(EnTk* this, PlayState* play) {
    this->actor.speed = 10.0f;
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_80AEF868, 5, &this->unk_2D4);
    Math_Vec3f_Copy(&this->actor.world.pos, &this->unk_2EC);
    Math_Vec3f_Copy(&this->actor.prevPos, &this->unk_2EC);
    Math_Vec3s_Copy(&this->actor.world.rot, &this->unk_2F8);
    Math_Vec3s_Copy(&this->actor.shape.rot, &this->unk_2F8);
    this->actionFunc = func_80AEDD4C;
}

void func_80AEDD4C(EnTk* this, PlayState* play) {
    this->csLength--;
    if (this->csLength <= 0) {
        CutsceneManager_Stop(this->csIdList[1]);
        Message_CloseTextbox(play);
        Actor_Kill(&this->actor);
    }
}

void func_80AEDDA0(EnTk* this, PlayState* play) {
    this->actor.speed = 0.0f;
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_80AEF868, 2, &this->unk_2D4);
    this->actor.flags |= ACTOR_FLAG_10000;
    this->unk_2CA |= 0x80;
    this->actionFunc = func_80AED940;
}

void func_80AEDE10(EnTk* this, PlayState* play) {
    switch (this->unk_2B0) {
        case 0:
            if (Player_GetMask(play) == PLAYER_MASK_CAPTAIN) {
                this->unk_2E6 = 0x1404;
                break;
            }

            switch (this->unk_310) {
                case 0:
                    this->unk_2CA &= ~0x1000;
                    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_52_80)) {
                        this->unk_2E6 = 0x1405;
                    } else {
                        this->unk_2E6 = 0x140B;
                    }
                    break;

                case 2:
                    this->unk_2E6 = 0x140D;
                    break;

                case 4:
                    Message_StartTextbox(play, 0x140F, &this->actor);
                    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_80AEF868, 2, &this->unk_2D4);
                    break;

                case 3:
                    Message_StartTextbox(play, 0x1410, &this->actor);
                    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_80AEF868, 2, &this->unk_2D4);
                    break;
            }
            break;

        case 2:
            this->unk_2E6 = 0x1414;
            break;
    }

    this->actionFunc = func_80AEDF5C;
}

void func_80AEDF5C(EnTk* this, PlayState* play) {
    if ((this->unk_2D4 == 4) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_80AEF868, 7, &this->unk_2D4);
    }

    switch (Message_GetState(&play->msgCtx)) {
        case TEXT_STATE_NONE:
            switch (this->unk_2E6) {
                case 0x1404:
                case 0x1405:
                case 0x140B:
                case 0x140D:
                    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer - 0x1555, 1, 0x71C, 0);
                    this->actor.world.rot.y = this->actor.shape.rot.y;
                    if (!Math_SmoothStepToS(&this->unk_31A, 0, 3, 0x16C, 10) &&
                        !Math_SmoothStepToS(&this->unk_31C, 0, 3, 0x71C, 10) &&
                        (this->actor.shape.rot.y == (s16)(this->actor.yawTowardsPlayer - 0x1555))) {
                        if (this->unk_2E6 == 0x1404) {
                            SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_80AEF868, 4, &this->unk_2D4);
                        } else {
                            SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_80AEF868, 2, &this->unk_2D4);
                        }
                        Message_StartTextbox(play, this->unk_2E6, &this->actor);
                    }
                    break;

                case 0x1414:
                    Message_StartTextbox(play, this->unk_2E6, &this->actor);
                    break;
            }
            break;

        case TEXT_STATE_1:
        case TEXT_STATE_CLOSING:
        case TEXT_STATE_3:
            break;

        case TEXT_STATE_CHOICE:
        case TEXT_STATE_5:
        case TEXT_STATE_DONE:
            if (Message_ShouldAdvance(play)) {
                switch (play->msgCtx.currentTextId) {
                    case 0x1404:
                        this->unk_2CA |= 0x1000;
                        func_80AED898(this, play);
                        break;

                    case 0x1405:
                        Message_ContinueTextbox(play, 0x1406);
                        break;

                    case 0x1406:
                        Message_ContinueTextbox(play, 0x1407);
                        break;

                    case 0x1407:
                        if (play->msgCtx.choiceIndex == 0) {
                            Audio_PlaySfx_MessageDecide();
                            Message_ContinueTextbox(play, 0x1409);
                        } else {
                            Audio_PlaySfx_MessageCancel();
                            Message_ContinueTextbox(play, 0x1408);
                        }
                        break;

                    case 0x1408:
                        Message_ContinueTextbox(play, 0x1407);
                        break;

                    case 0x1409:
                        Message_ContinueTextbox(play, 0x140A);
                        break;

                    case 0x140A:
                        SET_WEEKEVENTREG(WEEKEVENTREG_52_80);

                    case 0x140B:
                        func_80AEE784(this, play);
                        break;

                    case 0x140D:
                        this->unk_2CA |= 2;
                        if (play->msgCtx.choiceIndex == 0) {
                            Audio_PlaySfx_MessageDecide();
                            play->msgCtx.msgMode = MSGMODE_PAUSED;
                            func_80AEE2A8(this, play);
                        } else {
                            Audio_PlaySfx_MessageCancel();
                            Message_ContinueTextbox(play, 0x140E);
                        }
                        break;

                    case 0x140E:
                    case 0x140F:
                    case 0x1410:
                        func_80AEE784(this, play);
                        break;

                    case 0x1414:
                        func_80AECA3C(this, play);
                        break;
                }
            }
            break;
    }
}

void func_80AEE2A8(EnTk* this, PlayState* play) {
    this->actionFunc = func_80AEE2C0;
}

void func_80AEE2C0(EnTk* this, PlayState* play) {
    if (SubS_StartCutscene(&this->actor, this->csIdList[0], CS_ID_GLOBAL_TALK, SUBS_CUTSCENE_WITH_PLAYER)) {
        func_80AEE374(this, play);
    }
}

s32 func_80AEE300(PlayState* play, Actor* arg1, Actor* arg2, void* _arg3) {
    EnTkStruct* arg3 = (EnTkStruct*)_arg3;
    f32 temp_f0;

    if ((arg2 != arg1) && (ENTK_GET_F(arg2) == 3)) {
        temp_f0 = Actor_WorldDistXYZToActor(arg1, arg2);
        if (temp_f0 < arg3->unk_04) {
            arg3->unk_00 = arg2;
            arg3->unk_04 = temp_f0;
        }
    }
    return false;
}

void func_80AEE374(EnTk* this, PlayState* play) {
    EnTkStruct sp30;

    sp30.unk_00 = NULL;
    sp30.unk_04 = FLT_MAX;

    SubS_FindActorCustom(play, &this->actor, NULL, ACTORCAT_NPC, ACTOR_EN_TK, &sp30, func_80AEE300);
    if (sp30.unk_00 == 0) {
        Actor_Kill(&this->actor);
        return;
    }

    this->unk_2CC = Actor_WorldYawTowardPoint(&this->actor, &sp30.unk_00->world.pos);
    this->actionFunc = func_80AEE414;
}

void func_80AEE414(EnTk* this, PlayState* play) {
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->unk_2CC, 2, 0xE38, 0x5B);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (this->actor.shape.rot.y == this->unk_2CC) {
        func_80AEE478(this, play);
    }
}

void func_80AEE478(EnTk* this, PlayState* play) {
    this->unk_310 = 2;
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_80AEF868, 3, &this->unk_2D4);
    this->actionFunc = func_80AEE4D0;
}

void func_80AEE4D0(EnTk* this, PlayState* play) {
    Actor* bigPoe;

    if ((this->skelAnime.curFrame > 33.0f) && (this->skelAnime.curFrame < 41.0f)) {
        func_800BBFB0(play, &this->unk_2B4, 10.0f, 2, 50, 30, 1);
    }

    if (Animation_OnFrame(&this->skelAnime, 33.0f)) {
        Actor_PlaySfx(&this->actor, NA_SE_EV_DIG_UP);
    }

    if (!(this->unk_2CA & 0x20)) {
        if (Animation_OnFrame(&this->skelAnime, 37.0f)) {
            bigPoe = NULL;
            do {
                bigPoe = SubS_FindActor(play, bigPoe, ACTORCAT_PROP, ACTOR_EN_BIGPO);

                if (bigPoe != NULL) {
                    if ((bigPoe->params == 3) && (Actor_WorldDistXYZToActor(&this->actor, bigPoe) < 80.0f)) {
                        bigPoe->params = 4;
                        this->unk_2CA |= 0x20;
                        this->unk_2E4++;
                    }
                    bigPoe = bigPoe->next;
                }
            } while (bigPoe != NULL);
        }
    }

    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        func_80AEE650(this, play);
    }
}

void func_80AEE650(EnTk* this, PlayState* play) {
    if (this->unk_36C < ARRAY_COUNT(this->unk_324)) {
        Math_Vec3f_Copy(&this->unk_324[this->unk_36C], &this->actor.world.pos);
        this->unk_36C++;
    }
    this->actionFunc = func_80AEE6B8;
}

void func_80AEE6B8(EnTk* this, PlayState* play) {
    if (this->unk_2CA & 0x20) {
        if (this->unk_2E4 >= 3) {
            CutsceneManager_Stop(this->csIdList[0]);
            Message_CloseTextbox(play);
            func_80AEDBEC(this, play);
        } else if (SubS_StartCutscene(&this->actor, CS_ID_GLOBAL_TALK, this->csIdList[0], SUBS_CUTSCENE_WITH_PLAYER)) {
            this->unk_310 = 3;
            func_80AEDE10(this, play);
            this->unk_2CA &= ~0x20;
        }
    } else if (SubS_StartCutscene(&this->actor, CS_ID_GLOBAL_TALK, this->csIdList[0], SUBS_CUTSCENE_WITH_PLAYER)) {
        this->unk_310 = 4;
        func_80AEDE10(this, play);
    }
}

void func_80AEE784(EnTk* this, PlayState* play) {
    this->unk_2D0 = -1;
    this->unk_310 = 1;
    Math_Vec3s_Copy(&this->actor.world.rot, &this->actor.shape.rot);
    func_80AEEAD4(this, play);
    this->actionFunc = func_80AEE9B0;
}

s32 func_80AEE7E0(Vec3f* arg0, f32 arg1, Vec3f* arg2, s32 arg3) {
    s32 i;
    s32 ret = true;

    for (i = 0; i < arg3; i++) {
        if (Math_Vec3f_DistXZ(arg0, &arg2[i]) < arg1) {
            ret = false;
            break;
        }
    }
    return ret;
}

s32 func_80AEE86C(EnTk* this, PlayState* play) {
    static Vec3f D_80AEFA78 = { 0.0f, 20.0f, 32.0f };
    s32 pad;
    s32 ret = false;
    s32 pad2;
    CollisionPoly* groundPoly;
    s32 bgId;
    Vec3f sp28;

    Lib_Vec3f_TranslateAndRotateY(&this->actor.world.pos, this->actor.shape.rot.y, &D_80AEFA78, &sp28);
    if ((BgCheck_EntityRaycastFloor3(&play->colCtx, &groundPoly, &bgId, &sp28) != BGCHECK_Y_MIN) &&
        (SurfaceType_GetMaterial(&play->colCtx, groundPoly, bgId) == SURFACE_MATERIAL_SAND) && (this->unk_2D0 == 1) &&
        (this->actor.xyzDistToPlayerSq <= SQ(115.0f)) &&
        func_80AEE7E0(&this->actor.world.pos, 100.0f, this->unk_324, this->unk_36C) &&
        (((this->unk_2CA & 2) && (Math_Vec3f_DistXZ(&this->unk_300, &sp28) >= 100.0f)) || !(this->unk_2CA & 2)) &&
        !Play_InCsMode(play)) {
        Math_Vec3f_Copy(&this->unk_300, &sp28);
        ret = true;
    }
    return ret;
}

void func_80AEE9B0(EnTk* this, PlayState* play) {
    this->unk_30C(this, play);

    func_80AEEAD4(this, play);
    if (Math_Vec3f_DistXZ(&this->actor.world.pos, &this->unk_300) >= 100.0f) {
        this->unk_2CA &= ~2;
    }

    if (func_80AEE86C(this, play)) {
        this->unk_310 = 2;
        func_80AEDDA0(this, play);
    }
}

s32 func_80AEEA4C(EnTk* this, PlayState* play) {
    s32 ret;

    if (this->unk_2CA & 1) {
        ret = 3;
    } else if (this->actor.xyzDistToPlayerSq < SQ(60.0f)) {
        ret = 0;
    } else if (this->actor.isLockedOn || (play->actorCtx.targetCtx.arrowPointedActor == &this->actor) ||
               (this->actor.xyzDistToPlayerSq < SQ(80.0f))) {
        ret = 1;
    } else {
        ret = 2;
    }
    return ret;
}

void func_80AEEAD4(EnTk* this, PlayState* play) {
    s32 sp24 = func_80AEEA4C(this, play);

    if (sp24 != this->unk_2D0) {
        switch (sp24) {
            case 0:
                func_80AEF220(this, play);
                break;

            case 1:
                func_80AEF048(this, play);
                break;

            case 2:
                func_80AEEB88(this, play);
                break;

            case 3:
                func_80AEF15C(this, play);
                break;

            case 4:
                func_80AEF1C4(this, play);
                break;
        }
        this->unk_2D0 = sp24;
    }
}

void func_80AEEB88(EnTk* this, PlayState* play) {
    s32 sp74;
    Vec3f sp68;
    s32 i;
    f32 temp;

    for (i = 0; i < 8; i++) {
        sp68.x = Math_SinS(this->actor.world.rot.y + (i * 0x2000)) * 80.0f;
        sp68.z = Math_CosS(this->actor.world.rot.y + (i * 0x2000)) * 80.0f;

        sp68.x += this->actor.world.pos.x;
        sp68.y = this->actor.world.pos.y + 50.0f;
        sp68.z += this->actor.world.pos.z;

        temp =
            BgCheck_EntityRaycastFloor3(&play->colCtx, &this->actor.floorPoly, &sp74, &sp68) - this->actor.world.pos.y;
        if (temp <= -80.0f) {
            break;
        }
    }

    if (i == 8) {
        this->unk_2CC = BINANG_ROT180((Rand_Centered() * 0x8000) + this->actor.yawTowardsPlayer);
    } else {
        this->unk_2CC = this->actor.world.rot.y + (i * 0x2000);
    }

    this->unk_2C6 = 100;
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_80AEF868, 1, &this->unk_2D4);
    this->unk_30C = func_80AEED38;
}

void func_80AEED38(EnTk* this, PlayState* play) {
    f32 sp64;
    Vec3f sp58;
    s16 sp56 = this->actor.shape.rot.y;
    Vec3f sp48;
    Vec3f sp3C;

    Math_Vec3f_Copy(&sp58, &this->actor.world.pos);
    sp58.x += (Math_SinS(sp56) * 20.0f);
    sp58.y += 30.0f;
    sp58.z += Math_CosS(sp56) * 20.0f;

    if (BgCheck_SphVsFirstWall(&play->colCtx, &sp58, 20.0f)) {
        Math_Vec3f_Copy(&sp48, &this->actor.world.pos);
        sp56 = BINANG_ADD(this->actor.shape.rot.y, 0x4000);
        sp48.x += (Math_SinS(sp56) * 20.0f);
        sp48.y += 30.0f;
        sp48.z += Math_CosS(sp56) * 20.0f;

        Math_Vec3f_Copy(&sp3C, &this->actor.world.pos);
        sp56 = BINANG_SUB(this->actor.shape.rot.y, 0x4000);
        sp3C.x += (Math_SinS(sp56) * 20.0f);
        sp3C.y += 30.0f;
        sp3C.z += Math_CosS(sp56) * 20.0f;

        if (BgCheck_SphVsFirstWall(&play->colCtx, &sp48, 20.0f)) {
            if (BgCheck_SphVsFirstWall(&play->colCtx, &sp3C, 20.0f)) {
                this->unk_2CC = this->actor.shape.rot.y - 0x4000;
            } else {
                this->unk_2CC = this->actor.shape.rot.y - 0x4000;
            }
        } else {
            this->unk_2CC = this->actor.shape.rot.y + 0x4000;
        }
    }

    if (this->unk_2CA & 0x200) {
        SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_80AEF868, 2, &this->unk_2D4);
    } else {
        SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_80AEF868, 1, &this->unk_2D4);
        func_80AEC658(&this->skelAnime, this->unk_320, 1.0f, &this->actor.speed, &sp64);
    }

    if (this->actor.speed > 0.5f) {
        Math_SmoothStepToS(&this->actor.world.rot.y, this->unk_2CC, 2, 0xAAA, 1);
        this->actor.shape.rot.y = this->actor.world.rot.y;
    }

    if ((Message_GetState(&play->msgCtx) == TEXT_STATE_NONE) && !Play_InCsMode(play) && (this->unk_2C6-- <= 0)) {
        Message_StartTextbox(play, 0x140C, NULL);
        this->unk_2CA |= 0x4000;
        this->unk_2C6 = 200;
    }
}

void func_80AEF048(EnTk* this, PlayState* play) {
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_80AEF868, 1, &this->unk_2D4);
    this->unk_30C = func_80AEF094;
}

void func_80AEF094(EnTk* this, PlayState* play) {
    f32 sp2C;

    if (this->unk_2CA & 0x200) {
        SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_80AEF868, 2, &this->unk_2D4);
    } else {
        SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_80AEF868, 1, &this->unk_2D4);
        func_80AEC658(&this->skelAnime, this->unk_320, 1.0f, &this->actor.speed, &sp2C);
    }

    if (this->actor.speed >= 0.5f) {
        Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 2, 0x38E, 1);
        this->actor.shape.rot.y = this->actor.world.rot.y;
    }
}

void func_80AEF15C(EnTk* this, PlayState* play) {
    this->actor.speed = 0.0f;
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_80AEF868, 2, &this->unk_2D4);
    this->unk_30C = func_80AEF1B4;
}

void func_80AEF1B4(EnTk* this, PlayState* play) {
}

void func_80AEF1C4(EnTk* this, PlayState* play) {
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_80AEF868, 2, &this->unk_2D4);
    this->unk_30C = func_80AEF210;
}

void func_80AEF210(EnTk* this, PlayState* play) {
}

void func_80AEF220(EnTk* this, PlayState* play) {
    this->actor.speed = 0.0f;
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_80AEF868, 2, &this->unk_2D4);
    this->unk_30C = func_80AEF278;
}

void func_80AEF278(EnTk* this, PlayState* play) {
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer - 0x1555, 3, 0x1C7, 0);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

void func_80AEF2C8(Actor* thisx, PlayState* play) {
}

void func_80AEF2D8(Actor* thisx, PlayState* play) {
    s32 pad;
    EnTk* this = THIS;

    if (this->actor.draw != NULL) {
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    }

    this->unk_320 = this->skelAnime.curFrame;
    SkelAnime_Update(&this->skelAnime);

    if ((this->actor.draw != NULL) && ((this->unk_2D4 == 0) || (this->unk_2D4 == 1)) &&
        (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 24.0f))) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_GOLON_WALK);
    }

    this->actionFunc(this, play);

    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 10.0f, 10.0f, 0.0f, UPDBGCHECKINFO_FLAG_4);
    func_80AEC460(this);
}

void EnTk_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    EnTk* this = THIS;

    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    this->unk_320 = this->skelAnime.curFrame;
    SkelAnime_Update(&this->skelAnime);
    func_80AEC460(this);

    if (((this->unk_2D4 == 0) || (this->unk_2D4 == 1)) &&
        (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 24.0f))) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_GOLON_WALK);
    }

    this->unk_2CA &= ~1;

    if (this->actor.floorBgId != BGCHECK_SCENE) {
        BgDanpeiMovebg* platform = (BgDanpeiMovebg*)DynaPoly_GetActor(&play->colCtx, this->actor.floorBgId);

        if (platform != NULL) {
            if (platform->dyna.actor.id == ACTOR_BG_DANPEI_MOVEBG) {
                platform->unk_1CC |= 1;
                if (platform->unk_1CC & 2) {
                    this->unk_2CA |= 1;
                }
            }
        } else {
            Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.home.pos);
            Math_Vec3f_Copy(&this->actor.prevPos, &this->actor.home.pos);
        }
    }

    this->actionFunc(this, play);

    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 10.0f, 10.0f, 0.0f, UPDBGCHECKINFO_FLAG_1 | UPDBGCHECKINFO_FLAG_4);

    if ((this->unk_2B0 == 0) && (SurfaceType_GetFloorProperty(&play->colCtx, this->actor.floorPoly,
                                                              this->actor.floorBgId) == FLOOR_PROPERTY_12)) {
        Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.prevPos);
        this->unk_2CA |= 0x200;
        this->actor.velocity.y = 0.0f;
    } else {
        this->unk_2CA &= ~0x200;
    }

    if (!(this->unk_2CA & 0x200)) {
        if (!(this->actor.bgCheckFlags & BGCHECKFLAG_GROUND)) {
            Actor_PlaySfx_Flagged(&this->actor, NA_SE_EV_HONEYCOMB_FALL - SFX_FLAG);
        } else if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND_TOUCH) {
            Actor_PlaySfx(&this->actor, NA_SE_EV_HUMAN_BOUND);
        }
    }
}

void func_80AEF5F4(Actor* thisx, PlayState* play) {
    EnTk* this = THIS;

    this->unk_316 += 0x46C8;
    this->unk_318 = Math_SinS(this->unk_316) * 900.0f;
    this->actionFunc(this, play);
}

s32 EnTk_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnTk* this = THIS;

    if (limbIndex == 16) {
        rot->z += this->unk_31A;
        rot->y += this->unk_31C;
    }
    return false;
}

void EnTk_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Vec3f D_80AEFA84 = { 0.0f, 0.0f, 4600.0f };
    EnTk* this = THIS;

    if (this->unk_2B0 != 2) {
        switch (limbIndex) {
            case 16:
                Matrix_MultZero(&this->actor.focus.pos);
                break;

            case 14:
                Matrix_MultVec3f(&D_80AEFA84, &this->unk_2B4);

                OPEN_DISPS(play->state.gfxCtx);

                gSPDisplayList(POLY_OPA_DISP++, object_tk_DL_00B530);

                CLOSE_DISPS(play->state.gfxCtx);

                break;
        }
    }
}

void EnTk_Draw(Actor* thisx, PlayState* play) {
    static TexturePtr D_80AEFA90[] = {
        object_tk_Tex_004390,
        object_tk_Tex_004B90,
        object_tk_Tex_005390,
    };
    s32 pad;
    EnTk* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    POLY_OPA_DISP = Gfx_SetupDL(POLY_OPA_DISP, SETUPDL_25);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80AEFA90[this->unk_2C2]));

    Matrix_RotateYS(this->unk_318, MTXMODE_APPLY);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnTk_OverrideLimbDraw, EnTk_PostLimbDraw, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}
