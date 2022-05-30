/*
 * File: z_en_baba.c
 * Overlay: ovl_En_Baba
 * Description: Bomb Shop Lady
 */

#include "z_en_baba.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnBaba*)thisx)

#define ENBABA_END_CONVERSATION (1 << 0)
#define ENBABA_VISIBLE (1 << 1)
#define ENBABA_KNOCKED_OVER (1 << 2) // Don't track player
#define ENBABA_TYPE_IDLE (1 << 3)    // autotalk and set next entrance
#define ENBABA_GIVE_BLAST_MASK (1 << 5)
#define ENBABA_GAVE_BLAST_MASK (1 << 6)
#define ENBABA_DRAW_SHADOW (1 << 7)

void EnBaba_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBaba_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBaba_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBaba_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnBaba_FinishInit(EnBaba* this, GlobalContext* globalCtx);
void EnBaba_Idle(EnBaba* this, GlobalContext* globalCtx);
void EnBaba_FollowScheduleConverse(EnBaba* this, GlobalContext* globalCtx);
void EnBaba_Converse(EnBaba* this, GlobalContext* globalCtx);
void EnBaba_GiveBlastMask(EnBaba* this, GlobalContext* globalCtx);
void EnBaba_GaveBlastMask(EnBaba* this, GlobalContext* globalCtx);
void EnBaba_FollowSchedule(EnBaba* this, GlobalContext* globalCtx);
void EnBaba_KnockedOver(EnBaba* this, GlobalContext* globalCtx);
void EnBaba_DoNothing(EnBaba* this, GlobalContext* globalCtx);
void EnBaba_Walk(EnBaba* this, GlobalContext* globalCtx);
void EnBaba_FaceForward(EnBaba* this, GlobalContext* globalCtx);

typedef enum {
    /* 0 */ BABA_ANIM_IDLE_HOLDING_BAG,
    /* 1 */ BABA_ANIM_IDLE,
    /* 2 */ BABA_ANIM_WALKING_HOLDING_BAG,
    /* 3 */ BABA_ANIM_KNOCKED_OVER,
    /* 4 */ BABA_ANIM_LYING_DOWN,
    /* 5 */ BABA_ANIM_SWAY
} BabaAnimation;

typedef enum {
    /* 0 */ BABA_SCHEDULE_RESULT_NONE,
    /* 1 */ BABA_SCHEDULE_RESULT_KNOCKED_OVER,
    /* 2 */ BABA_SCHEDULE_RESULT_FOLLOW_TIME_PATH
} BabaScheduleResult;

const ActorInit En_Baba_InitVars = {
    ACTOR_EN_BABA,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BBA,
    sizeof(EnBaba),
    (ActorFunc)EnBaba_Init,
    (ActorFunc)EnBaba_Destroy,
    (ActorFunc)EnBaba_Update,
    (ActorFunc)EnBaba_Draw,
};

static AnimationInfo sAnimations[] = {
    { &gBbaIdleHoldingBagAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
    { &gBbaIdleAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
    { &gBbaWalkingHoldingBagAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
    { &gBbaKnockedOverAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, 0.0f },
    { &gBbaLyingDownAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
    { &gBbaSwayAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
};

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
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 18, 64, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(1, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(1, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x0),
    /* Ice arrow      */ DMG_ENTRY(1, 0x0),
    /* Light arrow    */ DMG_ENTRY(1, 0x0),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, 0x0),
    /* Zora barrier   */ DMG_ENTRY(1, 0x0),
    /* Normal shield  */ DMG_ENTRY(1, 0x0),
    /* Light ray      */ DMG_ENTRY(1, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(1, 0x0),
    /* Normal Roll    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(1, 0x0),
    /* Unblockable    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(1, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};

static u8 sSchedule[] = {
    /* 0x00 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(1, 0x1D - 0x04),
    /* 0x04 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_BACKTOWN, 0x1C - 0x08),
    /* 0x08 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(0, 0, 0, 30, 0x16 - 0x0E),
    /* 0x0E */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(0, 30, 0x15 - 0x12),
    /* 0x12 */ SCHEDULE_CMD_RET_VAL_L(BABA_SCHEDULE_RESULT_KNOCKED_OVER),
    /* 0x15 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x16 */ SCHEDULE_CMD_RET_TIME(0, 0, 0, 30, BABA_SCHEDULE_RESULT_FOLLOW_TIME_PATH),
    /* 0x1C */ SCHEDULE_CMD_RET_NONE(),
    /* 0x1D */ SCHEDULE_CMD_RET_NONE(),
};

static s32 sSearchTimePathLimit[] = { -1, -1, 0 };

static TurnOptionsSet sTurnOptions = {
    { 0xFA0, 4, 1, 3 },
    { 0x1770, 4, 1, 6 },
    { 0xFA0, 4, 1, 3 },
    { 0x1770, 4, 1, 6 },
};

s32 EnBaba_FindBombShopkeeper(EnBaba* this, GlobalContext* globalCtx) {
    // the bomb shopkeeper is an EnSob1, but initalizes itself with id `ACTOR_EN_OSSAN`
    this->bombShopkeeper = SubS_FindActor(globalCtx, this->bombShopkeeper, ACTORCAT_NPC, ACTOR_EN_OSSAN);

    if (this->bombShopkeeper != NULL) {
        return true;
    }
    return false;
}

void EnBaba_HandleConversation(EnBaba* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    switch (this->textId) {
        case 0:
            if (this->flags & ENBABA_TYPE_IDLE) {
                if (gSaveContext.save.weekEventReg[33] & 8) {
                    this->textId = 0x2A34;
                    break;
                }

                if (gSaveContext.save.weekEventReg[79] & 0x40) {
                    this->flags |= ENBABA_END_CONVERSATION;
                    this->textId = 0x2A33;
                    break;
                }

                this->flags |= ENBABA_END_CONVERSATION;
                this->textId = 0x2A32;
                break;
            } else if (player->transformation == PLAYER_FORM_DEKU) {
                if (!(gSaveContext.save.weekEventReg[79] & 0x20)) {
                    gSaveContext.save.weekEventReg[79] |= 0x20;
                    this->flags |= ENBABA_END_CONVERSATION;
                    this->textId = 0x2A37;
                    break;
                } else {
                    this->flags |= ENBABA_END_CONVERSATION;
                    this->textId = 0x2A38;
                }
                break;
            } else if (!(gSaveContext.save.weekEventReg[33] & 8)) {
                if (!(gSaveContext.save.weekEventReg[73] & 1)) {
                    this->textId = 0x660;
                    break;
                }
                this->textId = 0x662;
                break;
            } else {
                if (!(gSaveContext.save.weekEventReg[73] & 2)) {
                    this->textId = 0x65A;
                    break;
                }
                this->textId = 0x65E;
                break;
            }
            break;

        case 0x660:
            Actor_ChangeFocus(&this->actor, globalCtx, this->bombShopkeeper);
            this->textId = 0x661;
            break;

        case 0x661:
            Actor_ChangeFocus(this->bombShopkeeper, globalCtx, &this->actor);
            this->textId = 0x662;
            break;

        case 0x662:
            Actor_ChangeFocus(&this->actor, globalCtx, this->bombShopkeeper);
            this->textId = 0x663;
            gSaveContext.save.weekEventReg[73] |= 1;
            this->flags |= ENBABA_END_CONVERSATION;
            break;

        case 0x65A:
            Actor_ChangeFocus(&this->actor, globalCtx, this->bombShopkeeper);
            this->textId = 0x65B;
            break;

        case 0x65B:
            Actor_ChangeFocus(this->bombShopkeeper, globalCtx, &this->actor);
            this->textId = 0x65C;
            break;

        case 0x65C:
            Actor_ChangeFocus(&this->actor, globalCtx, this->bombShopkeeper);
            this->textId = 0x65D;
            gSaveContext.save.weekEventReg[73] |= 2;
            this->flags |= ENBABA_END_CONVERSATION;
            break;

        case 0x65E:
            Actor_ChangeFocus(&this->actor, globalCtx, this->bombShopkeeper);
            this->textId = 0x65F;
            this->flags |= ENBABA_END_CONVERSATION;
            break;

        case 0x2A34:
            if (INV_CONTENT(ITEM_MASK_BLAST) == ITEM_MASK_BLAST) {
                this->flags |= ENBABA_END_CONVERSATION;
                this->textId = 0x2A36;
                break;
            }
            this->flags |= ENBABA_GIVE_BLAST_MASK;
            this->textId = 0x2A35;
            break;

        case 0x2A35:
            this->flags |= ENBABA_END_CONVERSATION;
            this->textId = 0x2A36;
            break;

        case 0x2A30:
        case 0x2A31:
            this->flags |= ENBABA_END_CONVERSATION;
            break;
    }

    Message_StartTextbox(globalCtx, this->textId, &this->actor);
    if (this->flags & ENBABA_END_CONVERSATION) {
        if (this->flags & ENBABA_GAVE_BLAST_MASK) {
            this->flags &= ~ENBABA_GAVE_BLAST_MASK;
            func_80151BB4(globalCtx, 0x33);
        }
        func_80151BB4(globalCtx, 4);
    }
}

void EnBaba_SetNextEntrance(GlobalContext* globalCtx, u16 nextEntrance) {
    globalCtx->nextEntranceIndex = nextEntrance;
    globalCtx->unk_1887F = 0x40;
    gSaveContext.nextTransition = 0x40;
    globalCtx->sceneLoadFlag = 0x14;
}

void EnBaba_UpdateCollider(EnBaba* this, GlobalContext* globalCtx) {
    this->collider.dim.pos.x = this->actor.world.pos.x + 5.0f;
    this->collider.dim.pos.y = this->actor.world.pos.y;
    this->collider.dim.pos.z = this->actor.world.pos.z + 22.0f;

    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

s32 EnBaba_MoveForward(EnBaba* this, f32 speedTarget) {
    s16 rotStep;
    s32 reachedEnd = false;
    Vec3f point;

    Math_SmoothStepToF(&this->actor.speedXZ, speedTarget, 0.4f, 1000.0f, 0.0f);
    rotStep = this->actor.speedXZ * 400.0f;
    if (SubS_CopyPointFromPath(this->path, this->waypoint, &point) &&
        SubS_MoveActorToPoint(&this->actor, &point, rotStep)) {
        this->waypoint++;
        if (this->waypoint >= this->path->count) {
            reachedEnd = true;
        }
    }
    return reachedEnd;
}

void EnBaba_UpdateModel(EnBaba* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f point;

    SkelAnime_Update(&this->skelAnime);

    if (SubS_AngleDiffLessEqual(this->actor.shape.rot.y, 0x36B0, this->actor.yawTowardsPlayer) &&
        !(this->flags & ENBABA_KNOCKED_OVER)) {
        point.x = player->actor.world.pos.x;
        point.y = player->bodyPartsPos[7].y + 3.0f;
        point.z = player->actor.world.pos.z;

        SubS_TurnToPoint(&point, &this->actor.focus.pos, &this->actor.shape.rot, &this->turnTarget, &this->headRot,
                         &this->torsoRot, &sTurnOptions);
    } else {
        Math_SmoothStepToS(&this->turnTarget.x, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->turnTarget.y, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->headRot.x, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->headRot.y, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->torsoRot.x, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->torsoRot.y, 0, 4, 0x3E8, 1);
    }

    SubS_FillLimbRotTables(globalCtx, this->limbRotTableY, this->limbRotTableZ, ARRAY_COUNT(this->limbRotTableY));

    if (this->flags & ENBABA_VISIBLE) {
        EnBaba_UpdateCollider(this, globalCtx);
    }
}

s32 EnBaba_InitTimePath(EnBaba* this, GlobalContext* globalCtx, ScheduleOutput* scheduleOutput) {
    u16 now = SCHEDULE_TIME_NOW;
    u16 startTime;
    u8 pathIndex = ENBABA_GET_PATH_INDEX(&this->actor);
    u16 numWaypoints;

    if (sSearchTimePathLimit[scheduleOutput->result] >= 0) {
        this->timePath = SubS_GetAdditionalPath(globalCtx, pathIndex, sSearchTimePathLimit[scheduleOutput->result]);
    }

    if (this->timePath == NULL) {
        return false;
    }

    if ((this->scheduleResult != BABA_SCHEDULE_RESULT_NONE) && (this->timePathTimeSpeed >= 0)) {
        startTime = now;
    } else {
        startTime = scheduleOutput->time0;
    }

    if (scheduleOutput->time1 < startTime) {
        this->timePathTotalTime = (startTime - scheduleOutput->time1) + (DAY_LENGTH - 1);
    } else {
        this->timePathTotalTime = scheduleOutput->time1 - startTime;
    }

    this->timePathElapsedTime = now - startTime;

    numWaypoints = startTime = this->timePath->count - (SUBS_TIME_PATHING_ORDER - 1);
    this->timePathWaypointTime = this->timePathTotalTime / numWaypoints;

    this->timePathIsSetup = false;
    this->timePathWaypoint = (this->timePathElapsedTime / this->timePathWaypointTime) + (SUBS_TIME_PATHING_ORDER - 1);
    this->timePathHasReachedEnd = false;

    return true;
}

s32 EnBaba_ProcessScheduleOutput(EnBaba* this, GlobalContext* globalCtx, ScheduleOutput* scheduleOutput) {
    s32 success;

    switch (scheduleOutput->result) {
        default:
            success = false;
            break;

        case BABA_SCHEDULE_RESULT_FOLLOW_TIME_PATH:
            success = EnBaba_InitTimePath(this, globalCtx, scheduleOutput);
            break;

        case BABA_SCHEDULE_RESULT_KNOCKED_OVER:
            success = true;
            break;
    }
    return success;
}

s32 EnBaba_FollowTimePath(EnBaba* this, GlobalContext* globalCtx) {
    f32 weightArray[265];
    Vec3f worldPos;
    Vec3f timePathPointNew; // used to compute yaw after update
    Vec3f timePathPoint;    // used in setup and to store a backup before update
    s32 prevTimePathElapsedTime = 0;
    s32 prevTimePathWaypoint = 0;
    s32 pad;

    SubS_TimePathing_FillWeightArray(weightArray, SUBS_TIME_PATHING_ORDER,
                                     this->timePath->count + SUBS_TIME_PATHING_ORDER);

    if (!this->timePathIsSetup) {
        timePathPoint = gZeroVec3f;

        SubS_TimePathing_Update(this->timePath, &this->timePathProgress, &this->timePathElapsedTime,
                                this->timePathWaypointTime, this->timePathTotalTime, &this->timePathWaypoint,
                                weightArray, &timePathPoint, this->timePathTimeSpeed);
        SubS_TimePathing_ComputeInitialY(globalCtx, this->timePath, this->timePathWaypoint, &timePathPoint);
        this->actor.world.pos.y = timePathPoint.y;
        this->timePathIsSetup = true;
    } else {
        timePathPoint = this->timePathPoint;
    }

    this->actor.world.pos.x = timePathPoint.x;
    this->actor.world.pos.z = timePathPoint.z;

    if (SubS_InCsMode(globalCtx)) {
        prevTimePathElapsedTime = this->timePathElapsedTime;
        prevTimePathWaypoint = this->timePathWaypoint;
        timePathPoint = this->actor.world.pos;
    }

    this->timePathPoint = gZeroVec3f;

    if (SubS_TimePathing_Update(this->timePath, &this->timePathProgress, &this->timePathElapsedTime,
                                this->timePathWaypointTime, this->timePathTotalTime, &this->timePathWaypoint,
                                weightArray, &this->timePathPoint, this->timePathTimeSpeed)) {
        this->timePathHasReachedEnd = true;
    } else {
        worldPos = this->actor.world.pos;
        timePathPointNew = this->timePathPoint;
        this->actor.world.rot.y = Math_Vec3f_Yaw(&worldPos, &timePathPointNew);
    }

    if (SubS_InCsMode(globalCtx)) {
        this->timePathElapsedTime = prevTimePathElapsedTime;
        this->timePathWaypoint = prevTimePathWaypoint;
        this->timePathPoint = timePathPoint;
    }

    return false;
}

void EnBaba_HandleScheduleOutput(EnBaba* this, GlobalContext* globalCtx) {
    switch (this->scheduleResult) {
        case BABA_SCHEDULE_RESULT_FOLLOW_TIME_PATH:
            gSaveContext.save.weekEventReg[58] |= 0x40;
            this->flags |= ENBABA_VISIBLE;
            EnBaba_FollowTimePath(this, globalCtx);
            break;

        case BABA_SCHEDULE_RESULT_KNOCKED_OVER:
            this->animIndex = BABA_ANIM_KNOCKED_OVER;
            this->textId = 0x2A30;
            this->actor.speedXZ = 0.0f;
            Enemy_StartFinishingBlow(globalCtx, &this->actor);
            this->flags |= ENBABA_KNOCKED_OVER;
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, this->animIndex);
            this->actionFunc = EnBaba_KnockedOver;
            break;
    }
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 4, 0x1554);
}

void EnBaba_FinishInit(EnBaba* this, GlobalContext* globalCtx) {
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gBbaSkel, &gBbaWalkingHoldingBagAnim, this->jointTable,
                       this->morphTable, BBA_LIMB_MAX);

    this->actor.draw = EnBaba_Draw;
    this->flags |= ENBABA_DRAW_SHADOW;
    this->actor.flags |= ACTOR_FLAG_1;

    if (globalCtx->sceneNum == SCENE_BOMYA) {
        this->flags |= ENBABA_VISIBLE;
        this->animIndex = BABA_ANIM_IDLE;
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, this->animIndex);
        this->actionFunc = EnBaba_Idle;
    } else if (globalCtx->sceneNum == SCENE_BACKTOWN) {
        if ((ENBABA_GET_TYPE(&this->actor) == ENBABA_TYPE_FOLLOW_SCHEDULE) &&
            (gSaveContext.save.entranceIndex != 0xD670) && (ENBABA_GET_PATH_INDEX(&this->actor) != 0x3F)) {
            if ((gSaveContext.save.weekEventReg[58] & 0x40) ||
                (gSaveContext.save.time >= CLOCK_TIME(0, 20) && (gSaveContext.save.time < CLOCK_TIME(6, 0)))) {
                Actor_MarkForDeath(&this->actor);
                return;
            }

            this->sakonDeadTimer = 50;
            this->animIndex = BABA_ANIM_WALKING_HOLDING_BAG;
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, this->animIndex);
            this->actionFunc = EnBaba_FollowSchedule;
        } else if ((ENBABA_GET_TYPE(&this->actor) == ENBABA_TYPE_IDLE) && (gSaveContext.save.entranceIndex == 0xD670)) {
            if (gSaveContext.save.weekEventReg[81] & 2) {
                Actor_MarkForDeath(&this->actor);
                return;
            }

            this->flags |= ENBABA_VISIBLE;
            if (gSaveContext.save.weekEventReg[33] & 8) {
                this->animIndex = BABA_ANIM_IDLE_HOLDING_BAG;
            } else {
                this->animIndex = BABA_ANIM_IDLE;
            }

            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, this->animIndex);
            this->flags |= ENBABA_TYPE_IDLE;
            this->actionFunc = EnBaba_Idle;
        } else {
            Actor_MarkForDeath(&this->actor);
            return;
        }
    } else {
        this->flags |= ENBABA_VISIBLE;
        if (ENBABA_GET_TYPE(&this->actor) == ENBABA_TYPE_SWAY) {
            this->actor.flags &= ~ACTOR_FLAG_1;
            this->animIndex = BABA_ANIM_SWAY;
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, this->animIndex);
            this->actionFunc = EnBaba_DoNothing;
        } else if (ENBABA_GET_PATH_INDEX(&this->actor) != 0x3F) {
            this->animIndex = BABA_ANIM_WALKING_HOLDING_BAG;
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, this->animIndex);
            this->actionFunc = EnBaba_Walk;
        } else {
            this->animIndex = BABA_ANIM_IDLE_HOLDING_BAG;
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, this->animIndex);
            this->actionFunc = EnBaba_FaceForward;
        }
    }
}

void EnBaba_Idle(EnBaba* this, GlobalContext* globalCtx) {
    if ((this->flags & ENBABA_TYPE_IDLE) || (this->bombShopkeeper != NULL) ||
        EnBaba_FindBombShopkeeper(this, globalCtx)) {
        if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
            EnBaba_HandleConversation(this, globalCtx);
            if (this->flags & ENBABA_TYPE_IDLE) {
                this->actor.flags &= ~ACTOR_FLAG_10000;
            }
            this->actionFunc = EnBaba_Converse;
        } else if (this->actor.xzDistToPlayer < 100.0f) {
            if (this->flags & ENBABA_TYPE_IDLE) {
                this->actor.flags |= ACTOR_FLAG_10000;
            }
            func_800B8614(&this->actor, globalCtx, 100.0f);
        }
    }
}

void EnBaba_FollowScheduleConverse(EnBaba* this, GlobalContext* globalCtx) {
    u8 talkState = Message_GetState(&globalCtx->msgCtx);

    if (((talkState == 5) || (talkState == 6)) && Message_ShouldAdvance(globalCtx)) {
        globalCtx->msgCtx.msgMode = 0x43;
        globalCtx->msgCtx.unk12023 = 4;
        this->actionFunc = EnBaba_FollowSchedule;
    }
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x1000, 0x100);
}

void EnBaba_Converse(EnBaba* this, GlobalContext* globalCtx) {
    u8 talkState = Message_GetState(&globalCtx->msgCtx);

    if (talkState == 5) {
        if (Message_ShouldAdvance(globalCtx)) {
            if (this->flags & ENBABA_END_CONVERSATION) {
                this->flags &= ~ENBABA_END_CONVERSATION;
                globalCtx->msgCtx.msgMode = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
                if (this->flags & ENBABA_TYPE_IDLE) {
                    if (CHECK_QUEST_ITEM(QUEST_BOMBERS_NOTEBOOK)) {
                        if (globalCtx->msgCtx.unk120B1 == 0) {
                            gSaveContext.save.weekEventReg[81] |= 2;
                            EnBaba_SetNextEntrance(globalCtx, 0xD670);
                            return;
                        }
                    } else {
                        gSaveContext.save.weekEventReg[81] |= 2;
                        EnBaba_SetNextEntrance(globalCtx, 0xD670);
                    }
                } else {
                    this->textId = 0;
                    this->actionFunc = EnBaba_Idle;
                }
            } else if (this->flags & ENBABA_GIVE_BLAST_MASK) {
                this->flags &= ~ENBABA_GIVE_BLAST_MASK;
                globalCtx->msgCtx.msgMode = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
                this->actionFunc = EnBaba_GiveBlastMask;
            } else {
                EnBaba_HandleConversation(this, globalCtx);
            }
        }
    } else if (talkState == 6) {
        if (Message_ShouldAdvance(globalCtx) && (globalCtx->msgCtx.unk120B1 == 0)) {
            gSaveContext.save.weekEventReg[81] |= 2;
            EnBaba_SetNextEntrance(globalCtx, 0xD670);
        }
    }
}

void EnBaba_GiveBlastMask(EnBaba* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        this->flags |= ENBABA_GAVE_BLAST_MASK;
        this->actionFunc = EnBaba_GaveBlastMask;
    } else {
        Actor_PickUp(&this->actor, globalCtx, GI_MASK_BLAST, 300.0f, 300.0f);
    }
}

void EnBaba_GaveBlastMask(EnBaba* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        EnBaba_HandleConversation(this, globalCtx);
        this->actionFunc = EnBaba_Converse;
    } else {
        func_800B85E0(&this->actor, globalCtx, 400.0f, EXCH_ITEM_MINUS1);
    }
}

void EnBaba_FollowSchedule(EnBaba* this, GlobalContext* globalCtx) {
    ScheduleOutput scheduleOutput;

    this->timePathTimeSpeed = REG(15) + ((void)0, gSaveContext.save.daySpeed);

    if (!Schedule_RunScript(globalCtx, sSchedule, &scheduleOutput) ||
        ((this->scheduleResult != scheduleOutput.result) &&
         !EnBaba_ProcessScheduleOutput(this, globalCtx, &scheduleOutput))) {
        this->flags &= ~ENBABA_DRAW_SHADOW;
        this->actor.flags &= ~ACTOR_FLAG_1;
        scheduleOutput.result = BABA_SCHEDULE_RESULT_NONE;
    } else {
        this->flags |= ENBABA_DRAW_SHADOW;
        this->actor.flags |= ACTOR_FLAG_1;
    }
    this->scheduleResult = scheduleOutput.result;

    EnBaba_HandleScheduleOutput(this, globalCtx);

    if (this->flags & ENBABA_VISIBLE) {
        if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
            Message_StartTextbox(globalCtx, 0x2A39, &this->actor); // "I'm sorry"
            this->actionFunc = EnBaba_FollowScheduleConverse;
        } else if ((this->actor.xzDistToPlayer < 100.0f) || this->actor.isTargeted) {
            func_800B863C(&this->actor, globalCtx);
        }
    }
    Actor_MoveWithGravity(&this->actor);
}

void EnBaba_KnockedOver(EnBaba* this, GlobalContext* globalCtx) {
    s16 curFrame = this->skelAnime.curFrame;
    s16 endFrame = Animation_GetLastFrame(sAnimations[this->animIndex].animation);

    this->collider.dim.height = 37;
    this->collider.dim.radius = 23;

    if (this->animIndex == BABA_ANIM_KNOCKED_OVER) {
        if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_VO_BBVO00);
        }

        if (curFrame == endFrame) {
            this->animIndex = BABA_ANIM_LYING_DOWN;
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, this->animIndex);
        }
    } else {
        if ((gSaveContext.save.weekEventReg[79] & 0x40) && (DECR(this->sakonDeadTimer) == 0)) {
            Audio_QueueSeqCmd(0x101400FF);
            EnBaba_SetNextEntrance(globalCtx, 0xD670);
        } else {
            Actor_MoveWithGravity(&this->actor);
        }
    }
}

void EnBaba_DoNothing(EnBaba* this, GlobalContext* globalCtx) {
}

void EnBaba_Walk(EnBaba* this, GlobalContext* globalCtx) {
    if (EnBaba_MoveForward(this, 1.0f)) {
        this->waypoint = 0;
    }
}

void EnBaba_FaceForward(EnBaba* this, GlobalContext* globalCtx) {
    this->actor.shape.rot = this->actor.world.rot;
}

void EnBaba_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnBaba* this = THIS;

    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);

    this->path = SubS_GetPathByIndex(globalCtx, ENBABA_GET_PATH_INDEX(&this->actor), 0x3F);

    Actor_SetScale(&this->actor, 0.01f);

    this->actor.targetMode = 0;
    this->actor.gravity = -4.0f;
    this->actionFunc = EnBaba_FinishInit;
}

void EnBaba_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnBaba* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnBaba_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnBaba* this = THIS;

    this->actionFunc(this, globalCtx);

    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    EnBaba_UpdateModel(this, globalCtx);
}

s32 EnBaba_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                            Actor* thisx) {
    EnBaba* this = THIS;

    if (limbIndex == BBA_LIMB_NECK) {
        Matrix_Translate(1500.0f, 0.0f, 0.0f, MTXMODE_APPLY);
        Matrix_RotateXS(this->headRot.y, MTXMODE_APPLY);
        Matrix_RotateZS(-this->headRot.x, MTXMODE_APPLY);
        Matrix_Translate(-1500.0f, 0.0f, 0.0f, MTXMODE_APPLY);
    }

    if (limbIndex == BBA_LIMB_UPPER_ROOT) {
        Matrix_RotateXS(-this->torsoRot.y, MTXMODE_APPLY);
        Matrix_RotateZS(-this->torsoRot.x, MTXMODE_APPLY);
    }

    if ((limbIndex == BBA_LIMB_NECK) && (this->inMsgState3 != 0) && ((globalCtx->state.frames % 2) == 0)) {
        Matrix_Translate(40.0f, 0.0f, 0.0f, MTXMODE_APPLY);
    }

    if ((limbIndex == BBA_LIMB_UPPER_ROOT) || (limbIndex == BBA_LIMB_LEFT_UPPER_ARM) ||
        (limbIndex == BBA_LIMB_RIGHT_UPPER_ARM)) {
        rot->y += (s16)(Math_SinS(this->limbRotTableY[limbIndex]) * 200.0f);
        rot->z += (s16)(Math_CosS(this->limbRotTableZ[limbIndex]) * 200.0f);
    }

    if (((this->animIndex == BABA_ANIM_IDLE) || (this->animIndex == BABA_ANIM_KNOCKED_OVER) ||
         (this->animIndex == BABA_ANIM_LYING_DOWN) || (ENBABA_GET_TYPE(&this->actor) == ENBABA_TYPE_SWAY)) &&
        (limbIndex == BBA_LIMB_BAG)) {
        *dList = NULL;
    }
    return false;
}

void EnBaba_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnBaba* this = THIS;
    Vec3f sp18 = { 0.0f, 0.0f, 0.0f };

    if (limbIndex == BBA_LIMB_HEAD) {
        this->actor.focus.pos.x = this->actor.world.pos.x;
        this->actor.focus.pos.y = this->actor.world.pos.y;
        this->actor.focus.pos.z = this->actor.world.pos.z;
        Matrix_MultVec3f(&sp18, &this->actor.focus.pos);
    }
}

void EnBaba_TransformLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx) {
}

void EnBaba_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnBaba* this = THIS;
    Vec3f pos;
    Vec3f scale;

    if (this->flags & ENBABA_VISIBLE) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        func_8012C5B0(globalCtx->state.gfxCtx);

        gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(gBbaEyeTex));

        SkelAnime_DrawTransformFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                       this->skelAnime.dListCount, EnBaba_OverrideLimbDraw, EnBaba_PostLimbDraw,
                                       EnBaba_TransformLimbDraw, &this->actor);

        if (this->flags & ENBABA_DRAW_SHADOW) {
            if ((this->animIndex == BABA_ANIM_KNOCKED_OVER) || (this->animIndex == BABA_ANIM_LYING_DOWN)) {
                func_8012C2DC(globalCtx->state.gfxCtx);
                pos.x = this->actor.world.pos.x + 20.0f;
                pos.y = this->actor.world.pos.y;
                pos.z = this->actor.world.pos.z + 20.0f;
            } else {
                pos = this->actor.world.pos;
            }

            scale.x = scale.y = scale.z = 0.3f;
            func_800BC620(&pos, &scale, 255, globalCtx);
        }

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
