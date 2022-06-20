/*
 * File: z_en_baba.c
 * Overlay: ovl_En_Baba
 * Description: Bomb Shop Lady
 */

#include "z_en_baba.h"
#include "overlays/actors/ovl_En_Ossan/z_en_ossan.h"
#include "objects/object_bba/object_bba.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnBaba*)thisx)

void EnBaba_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBaba_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBaba_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBaba_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BA9480(EnBaba* this, GlobalContext* globalCtx);
void func_80BA9758(EnBaba* this, GlobalContext* globalCtx);
void func_80BA9848(EnBaba* this, GlobalContext* globalCtx);
void func_80BA98EC(EnBaba* this, GlobalContext* globalCtx);
void func_80BA9AB8(EnBaba* this, GlobalContext* globalCtx);
void func_80BA9B24(EnBaba* this, GlobalContext* globalCtx);
void func_80BA9B80(EnBaba* this, GlobalContext* globalCtx);
void func_80BA9CD4(EnBaba* this, GlobalContext* globalCtx);
void func_80BA9E00(EnBaba* this, GlobalContext* globalCtx);
void func_80BA9E10(EnBaba* this, GlobalContext* globalCtx);
void func_80BA9E48(EnBaba* this, GlobalContext* globalCtx);

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
    { &gBbaWalkingAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
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

static u8 D_80BAA488[] = {
    /* 0x00 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(1, 0x1D - 0x04),
    /* 0x04 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_BACKTOWN, 0x1C - 0x08),
    /* 0x08 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(0, 0, 0, 30, 0x16 - 0x0E),
    /* 0x0E */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(0, 30, 0x15 - 0x12),
    /* 0x12 */ SCHEDULE_CMD_RET_VAL_L(1),
    /* 0x15 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x16 */ SCHEDULE_CMD_RET_TIME(0, 0, 0, 30, 2),
    /* 0x1C */ SCHEDULE_CMD_RET_NONE(),
    /* 0x1D */ SCHEDULE_CMD_RET_NONE(),
};

s32 D_80BAA4A8[] = { -1, -1, 0 };

static TrackOptionsSet sTrackOptions = {
    { 0xFA0, 4, 1, 3 },
    { 0x1770, 4, 1, 6 },
    { 0xFA0, 4, 1, 3 },
    { 0x1770, 4, 1, 6 },
};

s32 func_80BA8820(EnBaba* this, GlobalContext* globalCtx) {
    this->unk_144 = (EnOssan*)SubS_FindActor(globalCtx, &this->unk_144->actor, ACTORCAT_NPC, ACTOR_EN_OSSAN);

    if (this->unk_144 != NULL) {
        return true;
    }
    return false;
}

void func_80BA886C(EnBaba* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    switch (this->unk_1E0) {
        case 0:
            if (this->unk_40A & 8) {
                if (gSaveContext.save.weekEventReg[33] & 8) {
                    this->unk_1E0 = 0x2A34;
                    break;
                }

                if (gSaveContext.save.weekEventReg[79] & 0x40) {
                    this->unk_40A |= 1;
                    this->unk_1E0 = 0x2A33;
                    break;
                }

                this->unk_40A |= 1;
                this->unk_1E0 = 0x2A32;
                break;
            } else if (player->transformation == PLAYER_FORM_DEKU) {
                if (!(gSaveContext.save.weekEventReg[79] & 0x20)) {
                    gSaveContext.save.weekEventReg[79] |= 0x20;
                    this->unk_40A |= 1;
                    this->unk_1E0 = 0x2A37;
                    break;
                } else {
                    this->unk_40A |= 1;
                    this->unk_1E0 = 0x2A38;
                }
                break;
            } else if (!(gSaveContext.save.weekEventReg[33] & 8)) {
                if (!(gSaveContext.save.weekEventReg[73] & 1)) {
                    this->unk_1E0 = 0x660;
                    break;
                }
                this->unk_1E0 = 0x662;
                break;
            } else {
                if (!(gSaveContext.save.weekEventReg[73] & 2)) {
                    this->unk_1E0 = 0x65A;
                    break;
                }
                this->unk_1E0 = 0x65E;
                break;
            }
            break;

        case 0x660:
            Actor_ChangeFocus(&this->actor, globalCtx, &this->unk_144->actor);
            this->unk_1E0 = 0x661;
            break;

        case 0x661:
            Actor_ChangeFocus(&this->unk_144->actor, globalCtx, &this->actor);
            this->unk_1E0 = 0x662;
            break;

        case 0x662:
            Actor_ChangeFocus(&this->actor, globalCtx, &this->unk_144->actor);
            this->unk_1E0 = 0x663;
            gSaveContext.save.weekEventReg[73] |= 1;
            this->unk_40A |= 1;
            break;

        case 0x65A:
            Actor_ChangeFocus(&this->actor, globalCtx, &this->unk_144->actor);
            this->unk_1E0 = 0x65B;
            break;

        case 0x65B:
            Actor_ChangeFocus(&this->unk_144->actor, globalCtx, &this->actor);
            this->unk_1E0 = 0x65C;
            break;

        case 0x65C:
            Actor_ChangeFocus(&this->actor, globalCtx, &this->unk_144->actor);
            this->unk_1E0 = 0x65D;
            gSaveContext.save.weekEventReg[73] |= 2;
            this->unk_40A |= 1;
            break;

        case 0x65E:
            Actor_ChangeFocus(&this->actor, globalCtx, &this->unk_144->actor);
            this->unk_1E0 = 0x65F;
            this->unk_40A |= 1;
            break;

        case 0x2A34:
            if (INV_CONTENT(ITEM_MASK_BLAST) == ITEM_MASK_BLAST) {
                this->unk_40A |= 1;
                this->unk_1E0 = 0x2A36;
                break;
            }
            this->unk_40A |= 0x20;
            this->unk_1E0 = 0x2A35;
            break;

        case 0x2A35:
            this->unk_40A |= 1;
            this->unk_1E0 = 0x2A36;
            break;

        case 0x2A30:
        case 0x2A31:
            this->unk_40A |= 1;
            break;
    }

    Message_StartTextbox(globalCtx, this->unk_1E0, &this->actor);
    if (this->unk_40A & 1) {
        if (this->unk_40A & 0x40) {
            this->unk_40A &= ~0x40;
            func_80151BB4(globalCtx, 0x33);
        }
        func_80151BB4(globalCtx, 4);
    }
}

void func_80BA8C4C(GlobalContext* globalCtx, u16 nextEntrance) {
    globalCtx->nextEntranceIndex = nextEntrance;
    globalCtx->unk_1887F = 0x40;
    gSaveContext.nextTransition = 0x40;
    globalCtx->sceneLoadFlag = 0x14;
}

void func_80BA8C90(EnBaba* this, GlobalContext* globalCtx) {
    this->collider.dim.pos.x = this->actor.world.pos.x + 5.0f;
    this->collider.dim.pos.y = this->actor.world.pos.y;
    this->collider.dim.pos.z = this->actor.world.pos.z + 22.0f;

    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

s32 func_80BA8D2C(EnBaba* this, f32 arg1) {
    s16 sp3E;
    s32 ret = false;
    Vec3f sp2C;

    Math_SmoothStepToF(&this->actor.speedXZ, arg1, 0.4f, 1000.0f, 0.0f);
    sp3E = this->actor.speedXZ * 400.0f;
    if (SubS_CopyPointFromPath(this->path, this->unk_1E8, &sp2C) && SubS_MoveActorToPoint(&this->actor, &sp2C, sp3E)) {
        this->unk_1E8++;
        if (this->unk_1E8 >= this->path->count) {
            ret = true;
        }
    }
    return ret;
}

void func_80BA8DF4(EnBaba* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f point;

    SkelAnime_Update(&this->skelAnime);

    if (SubS_AngleDiffLessEqual(this->actor.shape.rot.y, 0x36B0, this->actor.yawTowardsPlayer) &&
        !(this->unk_40A & 4)) {
        point.x = player->actor.world.pos.x;
        point.y = player->bodyPartsPos[7].y + 3.0f;
        point.z = player->actor.world.pos.z;

        SubS_TrackPoint(&point, &this->actor.focus.pos, &this->actor.shape.rot, &this->trackTarget, &this->headRot,
                        &this->torsoRot, &sTrackOptions);
    } else {
        Math_SmoothStepToS(&this->trackTarget.x, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->trackTarget.y, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->headRot.x, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->headRot.y, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->torsoRot.x, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->torsoRot.y, 0, 4, 0x3E8, 1);
    }

    SubS_FillLimbRotTables(globalCtx, this->unk_302, this->unk_326, ARRAY_COUNT(this->unk_302));

    if (this->unk_40A & 2) {
        func_80BA8C90(this, globalCtx);
    }
}

s32 func_80BA8F88(EnBaba* this, GlobalContext* globalCtx, ScheduleResult* arg2) {
    u16 sp26 = SCHEDULE_TIME_NOW;
    u16 temp;
    u8 sp23 = ENBABA_GET_3F00(&this->actor);

    if (D_80BAA4A8[arg2->result] >= 0) {
        this->timePath = SubS_GetAdditionalPath(globalCtx, sp23, D_80BAA4A8[arg2->result]);
    }

    if (this->timePath == NULL) {
        return false;
    }

    if ((this->unk_434 != 0) && (this->timePathTimeSpeed >= 0)) {
        temp = sp26;
    } else {
        temp = arg2->time0;
    }

    if (arg2->time1 < temp) {
        this->timePathTotalTime = (temp - arg2->time1) + 0xFFFF;
    } else {
        this->timePathTotalTime = arg2->time1 - temp;
    }

    this->timePathElapsedTime = sp26 - temp;
    temp = this->timePath->count - (SUBS_TIME_PATHING_ORDER - 1);
    this->timePathWaypointTime = this->timePathTotalTime / temp;
    this->unk_438 = 0;
    this->timePathWaypoint = (this->timePathElapsedTime / this->timePathWaypointTime) + (SUBS_TIME_PATHING_ORDER - 1);
    this->unk_43C = 0;
    return true;
}

s32 func_80BA9110(EnBaba* this, GlobalContext* globalCtx, ScheduleResult* arg2) {
    s32 ret;

    switch (arg2->result) {
        default:
            ret = false;
            break;

        case 2:
            ret = func_80BA8F88(this, globalCtx, arg2);
            break;

        case 1:
            ret = true;
            break;
    }
    return ret;
}

s32 func_80BA9160(EnBaba* this, GlobalContext* globalCtx) {
    f32 knots[265];
    Vec3f sp70;
    Vec3f sp64;
    Vec3f timePathTargetPos;
    s32 sp54 = 0;
    s32 sp50 = 0;
    s32 pad;

    SubS_TimePathing_FillKnots(knots, SUBS_TIME_PATHING_ORDER, this->timePath->count + SUBS_TIME_PATHING_ORDER);

    if (this->unk_438 == 0) {
        timePathTargetPos = gZeroVec3f;

        SubS_TimePathing_Update(this->timePath, &this->timePathProgress, &this->timePathElapsedTime,
                                this->timePathWaypointTime, this->timePathTotalTime, &this->timePathWaypoint, knots,
                                &timePathTargetPos, this->timePathTimeSpeed);
        SubS_TimePathing_ComputeInitialY(globalCtx, this->timePath, this->timePathWaypoint, &timePathTargetPos);
        this->actor.world.pos.y = timePathTargetPos.y;
        this->unk_438 = 1;
    } else {
        timePathTargetPos = this->timePathTargetPos;
    }

    this->actor.world.pos.x = timePathTargetPos.x;
    this->actor.world.pos.z = timePathTargetPos.z;

    if (SubS_InCsMode(globalCtx)) {
        sp54 = this->timePathElapsedTime;
        sp50 = this->timePathWaypoint;
        timePathTargetPos = this->actor.world.pos;
    }

    this->timePathTargetPos = gZeroVec3f;

    if (SubS_TimePathing_Update(this->timePath, &this->timePathProgress, &this->timePathElapsedTime,
                                this->timePathWaypointTime, this->timePathTotalTime, &this->timePathWaypoint, knots,
                                &this->timePathTargetPos, this->timePathTimeSpeed)) {
        this->unk_43C = 1;
    } else {
        sp70 = this->actor.world.pos;
        sp64 = this->timePathTargetPos;
        this->actor.world.rot.y = Math_Vec3f_Yaw(&sp70, &sp64);
    }

    if (SubS_InCsMode(globalCtx)) {
        this->timePathElapsedTime = sp54;
        this->timePathWaypoint = sp50;
        this->timePathTargetPos = timePathTargetPos;
    }

    return false;
}

void func_80BA93AC(EnBaba* this, GlobalContext* globalCtx) {
    if (this->unk_434 != 1) {
        if (this->unk_434 == 2) {
            gSaveContext.save.weekEventReg[58] |= 0x40;
            this->unk_40A |= 2;
            func_80BA9160(this, globalCtx);
        }
    } else {
        this->unk_40C = 3;
        this->unk_1E0 = 10800;
        this->actor.speedXZ = 0.0f;
        Enemy_StartFinishingBlow(globalCtx, &this->actor);
        this->unk_40A |= 4;
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, this->unk_40C);
        this->actionFunc = func_80BA9CD4;
    }
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 4, 0x1554);
}

void func_80BA9480(EnBaba* this, GlobalContext* globalCtx) {
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gBbaSkel, &gBbaWalkingHoldingBagAnim, this->jointTable,
                       this->morphTable, 0x12);

    this->actor.draw = EnBaba_Draw;
    this->unk_40A |= 0x80;
    this->actor.flags |= ACTOR_FLAG_1;

    if (globalCtx->sceneNum == SCENE_BOMYA) {
        this->unk_40A |= 2;
        this->unk_40C = 1;
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 1);
        this->actionFunc = func_80BA9758;
    } else if (globalCtx->sceneNum == SCENE_BACKTOWN) {
        if ((ENBABA_GET_C000(&this->actor) == ENBABA_C000_0) && (gSaveContext.save.entranceIndex != 0xD670) &&
            ((ENBABA_GET_3F00(&this->actor)) != ENBABA_3F00_3F)) {
            if ((gSaveContext.save.weekEventReg[58] & 0x40) ||
                (!(gSaveContext.save.time < CLOCK_TIME(0, 20)) && (gSaveContext.save.time < CLOCK_TIME(6, 0)))) {
                Actor_MarkForDeath(&this->actor);
                return;
            }

            this->unk_404 = 50;
            this->unk_40C = 2;
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 2);
            this->actionFunc = func_80BA9B80;
        } else if ((ENBABA_GET_C000(&this->actor) == ENBABA_C000_1) && (gSaveContext.save.entranceIndex == 0xD670)) {
            if (gSaveContext.save.weekEventReg[81] & 2) {
                Actor_MarkForDeath(&this->actor);
                return;
            }

            this->unk_40A |= 2;
            if (gSaveContext.save.weekEventReg[33] & 8) {
                this->unk_40C = 0;
            } else {
                this->unk_40C = 1;
            }

            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, this->unk_40C);
            this->unk_40A |= 8;
            this->actionFunc = func_80BA9758;
        } else {
            Actor_MarkForDeath(&this->actor);
            return;
        }
    } else {
        this->unk_40A |= 2;
        if (ENBABA_GET_C000(&this->actor) == ENBABA_C000_2) {
            this->actor.flags &= ~ACTOR_FLAG_1;
            this->unk_40C = 5;
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 5);
            this->actionFunc = func_80BA9E00;
        } else if ((ENBABA_GET_3F00(&this->actor)) != ENBABA_3F00_3F) {
            this->unk_40C = 2;
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 2);
            this->actionFunc = func_80BA9E10;
        } else {
            this->unk_40C = 0;
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 0);
            this->actionFunc = func_80BA9E48;
        }
    }
}

void func_80BA9758(EnBaba* this, GlobalContext* globalCtx) {
    if ((this->unk_40A & 8) || (this->unk_144 != NULL) || func_80BA8820(this, globalCtx)) {
        if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
            func_80BA886C(this, globalCtx);
            if (this->unk_40A & 8) {
                this->actor.flags &= ~ACTOR_FLAG_10000;
            }
            this->actionFunc = func_80BA98EC;
        } else if (this->actor.xzDistToPlayer < 100.0f) {
            if (this->unk_40A & 8) {
                this->actor.flags |= ACTOR_FLAG_10000;
            }
            func_800B8614(&this->actor, globalCtx, 100.0f);
        }
    }
}

void func_80BA9848(EnBaba* this, GlobalContext* globalCtx) {
    u8 temp_v0 = Message_GetState(&globalCtx->msgCtx);

    if (((temp_v0 == 5) || (temp_v0 == 6)) && Message_ShouldAdvance(globalCtx)) {
        globalCtx->msgCtx.msgMode = 0x43;
        globalCtx->msgCtx.unk12023 = 4;
        this->actionFunc = func_80BA9B80;
    }
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x1000, 0x100);
}

void func_80BA98EC(EnBaba* this, GlobalContext* globalCtx) {
    u8 temp_v0 = Message_GetState(&globalCtx->msgCtx);

    if (temp_v0 == 5) {
        if (Message_ShouldAdvance(globalCtx)) {
            if (this->unk_40A & 1) {
                this->unk_40A &= ~1;
                globalCtx->msgCtx.msgMode = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
                if (this->unk_40A & 8) {
                    if (CHECK_QUEST_ITEM(QUEST_BOMBERS_NOTEBOOK)) {
                        if (globalCtx->msgCtx.unk120B1 == 0) {
                            gSaveContext.save.weekEventReg[81] |= 2;
                            func_80BA8C4C(globalCtx, 0xD670);
                            return;
                        }
                    } else {
                        gSaveContext.save.weekEventReg[81] |= 2;
                        func_80BA8C4C(globalCtx, 0xD670);
                    }
                } else {
                    this->unk_1E0 = 0;
                    this->actionFunc = func_80BA9758;
                }
            } else if (this->unk_40A & 0x20) {
                this->unk_40A &= ~0x20;
                globalCtx->msgCtx.msgMode = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
                this->actionFunc = func_80BA9AB8;
            } else {
                func_80BA886C(this, globalCtx);
            }
        }
    } else if (temp_v0 == 6) {
        if (Message_ShouldAdvance(globalCtx) && (globalCtx->msgCtx.unk120B1 == 0)) {
            gSaveContext.save.weekEventReg[81] |= 2;
            func_80BA8C4C(globalCtx, 0xD670);
        }
    }
}

void func_80BA9AB8(EnBaba* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        this->unk_40A |= 0x40;
        this->actionFunc = func_80BA9B24;
    } else {
        Actor_PickUp(&this->actor, globalCtx, GI_MASK_BLAST, 300.0f, 300.0f);
    }
}

void func_80BA9B24(EnBaba* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        func_80BA886C(this, globalCtx);
        this->actionFunc = func_80BA98EC;
    } else {
        func_800B85E0(&this->actor, globalCtx, 400.0f, -1);
    }
}

void func_80BA9B80(EnBaba* this, GlobalContext* globalCtx) {
    ScheduleResult sp20;

    this->timePathTimeSpeed = REG(15) + ((void)0, gSaveContext.save.daySpeed);

    if (!Schedule_RunScript(globalCtx, D_80BAA488, &sp20) ||
        ((this->unk_434 != sp20.result) && !func_80BA9110(this, globalCtx, &sp20))) {
        this->unk_40A &= ~0x80;
        this->actor.flags &= ~ACTOR_FLAG_1;
        sp20.result = false;
    } else {
        this->unk_40A |= 0x80;
        this->actor.flags |= ACTOR_FLAG_1;
    }
    this->unk_434 = sp20.result;

    func_80BA93AC(this, globalCtx);

    if (this->unk_40A & 2) {
        if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
            Message_StartTextbox(globalCtx, 0x2A39, &this->actor); // "I'm sorry"
            this->actionFunc = func_80BA9848;
        } else if ((this->actor.xzDistToPlayer < 100.0f) || this->actor.isTargeted) {
            func_800B863C(&this->actor, globalCtx);
        }
    }
    Actor_MoveWithGravity(&this->actor);
}

void func_80BA9CD4(EnBaba* this, GlobalContext* globalCtx) {
    s16 sp2E = this->skelAnime.curFrame;
    s16 sp2C = Animation_GetLastFrame(sAnimations[this->unk_40C].animation);

    this->collider.dim.height = 37;
    this->collider.dim.radius = 23;

    if (this->unk_40C == 3) {
        if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_VO_BBVO00);
        }

        if (sp2E == sp2C) {
            this->unk_40C = 4;
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 4);
        }
    } else {
        if ((gSaveContext.save.weekEventReg[79] & 0x40) && (DECR(this->unk_404) == 0)) {
            Audio_QueueSeqCmd(0x101400FF);
            func_80BA8C4C(globalCtx, 0xD670);
        } else {
            Actor_MoveWithGravity(&this->actor);
        }
    }
}

void func_80BA9E00(EnBaba* this, GlobalContext* globalCtx) {
}

void func_80BA9E10(EnBaba* this, GlobalContext* globalCtx) {
    if (func_80BA8D2C(this, 1.0f)) {
        this->unk_1E8 = 0;
    }
}

void func_80BA9E48(EnBaba* this, GlobalContext* globalCtx) {
    this->actor.shape.rot = this->actor.world.rot;
}

void EnBaba_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnBaba* this = THIS;

    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);

    this->path = SubS_GetPathByIndex(globalCtx, ENBABA_GET_3F00(&this->actor), ENBABA_3F00_3F);

    Actor_SetScale(&this->actor, 0.01f);

    this->actor.targetMode = 0;
    this->actor.gravity = -4.0f;
    this->actionFunc = func_80BA9480;
}

void EnBaba_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnBaba* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnBaba_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnBaba* this = THIS;

    this->actionFunc(this, globalCtx);

    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    func_80BA8DF4(this, globalCtx);
}

s32 EnBaba_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                            Actor* thisx) {
    EnBaba* this = THIS;

    if (limbIndex == 6) {
        Matrix_Translate(1500.0f, 0.0f, 0.0f, MTXMODE_APPLY);
        Matrix_RotateXS(this->headRot.y, MTXMODE_APPLY);
        Matrix_RotateZS(-this->headRot.x, MTXMODE_APPLY);
        Matrix_Translate(-1500.0f, 0.0f, 0.0f, MTXMODE_APPLY);
    }

    if (limbIndex == 5) {
        Matrix_RotateXS(-this->torsoRot.y, MTXMODE_APPLY);
        Matrix_RotateZS(-this->torsoRot.x, MTXMODE_APPLY);
    }

    if ((limbIndex == 6) && (this->unk_1E2 != 0) && ((globalCtx->state.frames % 2) == 0)) {
        Matrix_Translate(40.0f, 0.0f, 0.0f, MTXMODE_APPLY);
    }

    if ((limbIndex == 5) || (limbIndex == 10) || (limbIndex == 14)) {
        rot->y += (s16)(Math_SinS(this->unk_302[limbIndex]) * 200.0f);
        rot->z += (s16)(Math_CosS(this->unk_326[limbIndex]) * 200.0f);
    }

    if (((this->unk_40C == 1) || (this->unk_40C == 3) || (this->unk_40C == 4) ||
         (ENBABA_GET_C000(&this->actor) == ENBABA_C000_2)) &&
        (limbIndex == 8)) {
        *dList = NULL;
    }
    return 0;
}

void EnBaba_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnBaba* this = THIS;
    Vec3f sp18 = { 0.0f, 0.0f, 0.0f };

    if (limbIndex == 7) {
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
    Vec3f sp4C;
    Vec3f sp40;

    if (this->unk_40A & 2) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        func_8012C5B0(globalCtx->state.gfxCtx);

        gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(gBbaEyeTex));

        SkelAnime_DrawTransformFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                       this->skelAnime.dListCount, EnBaba_OverrideLimbDraw, EnBaba_PostLimbDraw,
                                       EnBaba_TransformLimbDraw, &this->actor);

        if (this->unk_40A & 0x80) {
            if ((this->unk_40C == 3) || (this->unk_40C == 4)) {
                func_8012C2DC(globalCtx->state.gfxCtx);
                sp4C.x = this->actor.world.pos.x + 20.0f;
                sp4C.y = this->actor.world.pos.y;
                sp4C.z = this->actor.world.pos.z + 20.0f;
            } else {
                sp4C = this->actor.world.pos;
            }

            sp40.x = sp40.y = sp40.z = 0.3f;
            func_800BC620(&sp4C, &sp40, 255, globalCtx);
        }

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
