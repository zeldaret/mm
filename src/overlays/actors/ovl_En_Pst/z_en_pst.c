/*
 * File: z_en_pst.c
 * Overlay: ovl_En_Pst
 * Description: Postbox
 */

#include "z_en_pst.h"

#define FLAGS (ACTOR_FLAG_1)

#define THIS ((EnPst*)thisx)

void EnPst_Init(Actor* thisx, PlayState* play);
void EnPst_Destroy(Actor* thisx, PlayState* play);
void EnPst_Update(Actor* thisx, PlayState* play);
void EnPst_Draw(Actor* thisx, PlayState* play);

void func_80B2BD98(EnPst* this, PlayState* play);
void func_80B2BE54(EnPst* this, PlayState* play);

typedef enum {
    /* 0 */ POSTBOX_SCH_NONE,
    /* 1 */ POSTBOX_SCH_AVAILABLE
} PostboxScheduleResult;

static u8 D_80B2C200[] = {
    /* 0x0 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(9, 31, 9, 35, 0x9 - 0x6),
    /* 0x6 */ SCHEDULE_CMD_RET_VAL_L(1),
    /* 0x9 */ SCHEDULE_CMD_RET_VAL_L(2),
};

static u8 D_80B2C20C[] = {
    /* 0x0 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(10, 3, 10, 7, 0x9 - 0x6),
    /* 0x6 */ SCHEDULE_CMD_RET_VAL_L(1),
    /* 0x9 */ SCHEDULE_CMD_RET_VAL_L(2),
};

static u8 D_80B2C218[] = {
    /* 0x0 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(10, 35, 10, 39, 0x9 - 0x6),
    /* 0x6 */ SCHEDULE_CMD_RET_VAL_L(1),
    /* 0x9 */ SCHEDULE_CMD_RET_VAL_L(2),
};

static u8 D_80B2C224[] = {
    /* 0x0 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(10, 53, 10, 57, 0x9 - 0x6),
    /* 0x6 */ SCHEDULE_CMD_RET_VAL_L(1),
    /* 0x9 */ SCHEDULE_CMD_RET_VAL_L(2),
};

static u8 D_80B2C230[] = {
    /* 0x0 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 25, 11, 29, 0x9 - 0x6),
    /* 0x6 */ SCHEDULE_CMD_RET_VAL_L(1),
    /* 0x9 */ SCHEDULE_CMD_RET_VAL_L(2),
};

s32 D_80B2C23C[] = { 0x0E27840C, 0x0E00FF2B, 0x00000031, 0x00392800, 0x0A122C27, 0xA40C2F00, 0x000C1012,
                     0x2C27870C, 0x2F00000C, 0x111B022A, 0x002F001B, 0x4000080F, 0x27882D00, 0x180C100F,
                     0x27892D00, 0x180C1012, 0x2C27850C, 0x2FFFD20E, 0x27860C10 };

s32 D_80B2C288[] = { 0x0E27840C, 0x0E00FF2B, 0x00000031, 0x00392800, 0x0A122C27, 0xA40C2F00, 0x000C1012,
                     0x2C27870C, 0x2F00000C, 0x111B042A, 0x002F001B, 0x8000080F, 0x27882D00, 0x180C100F,
                     0x27892D00, 0x180C1012, 0x2C27850C, 0x2FFFD20E, 0x27860C10 };

s32 D_80B2C2D4[] = { 0x0E27840C, 0x0E00FF2B, 0x00000031, 0x00392800, 0x0A122C27, 0xA40C2F00, 0x000C1012,
                     0x2C27870C, 0x2F00000C, 0x111B082A, 0x002F001C, 0x0100080F, 0x27882D00, 0x180C100F,
                     0x27892D00, 0x180C1012, 0x2C27850C, 0x2FFFD20E, 0x27860C10 };

s32 D_80B2C320[] = { 0x0E27840C, 0x0E00FF2B, 0x00000031, 0x00392800, 0x0A122C27, 0xA40C2F00, 0x000C1012,
                     0x2C27870C, 0x2F00000C, 0x111B102A, 0x002F001C, 0x0200080F, 0x27882D00, 0x180C100F,
                     0x27892D00, 0x180C1012, 0x2C27850C, 0x2FFFD20E, 0x27860C10 };

s32 D_80B2C36C[] = { 0x0E27840C, 0x0E00FF2B, 0x00000031, 0x00392800, 0x0A122C27, 0xA40C2F00, 0x000C1012,
                     0x2C27870C, 0x2F00000C, 0x111B202A, 0x002F001C, 0x0400080F, 0x27882D00, 0x180C100F,
                     0x27892D00, 0x180C1012, 0x2C27850C, 0x2FFFD20E, 0x27860C10 };

s32 D_80B2C3B8[] = { 0x0E27A10C, 0x0F27A20C, 0x12005108, 0x000F0600, 0x0C000013, 0x000C0C11,
                     0x51080700, 0x0C060001, 0x00001300, 0x010C0700, 0x000E27A3, 0x0C161000 };

s32 D_80B2C3E8[] = { 0x2C27870C, 0x111B022A, 0x002F001B, 0x4000080F, 0x27882D00, 0x180C100F, 0x27892D00, 0x180C1000 };

s32 D_80B2C408[] = { 0x2C27870C, 0x111B042A, 0x002F001B, 0x8000080F, 0x27882D00, 0x180C100F, 0x27892D00, 0x180C1000 };

s32 D_80B2C428[] = { 0x2C27870C, 0x111B082A, 0x002F001C, 0x0100080F, 0x27882D00, 0x180C100F, 0x27892D00, 0x180C1000 };

s32 D_80B2C448[] = { 0x2C27870C, 0x111B102A, 0x002F001C, 0x0200080F, 0x27882D00, 0x180C100F, 0x27892D00, 0x180C1000 };

s32 D_80B2C468[] = { 0x2C27870C, 0x111B202A, 0x002F001C, 0x0400080F, 0x27882D00, 0x180C100F, 0x27892D00, 0x180C1000 };

s32 D_80B2C488[] = { 0x2C27A40C, 0x10000000 };

s32 D_80B2C490[] = { 0x2C27850C, 0x10000000 };

const ActorInit En_Pst_InitVars = {
    ACTOR_EN_PST,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_PST,
    sizeof(EnPst),
    (ActorFunc)EnPst_Init,
    (ActorFunc)EnPst_Destroy,
    (ActorFunc)EnPst_Update,
    (ActorFunc)EnPst_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT1,
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
    { 28, 72, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 1, 0, 0, 0, MASS_IMMOVABLE };

static AnimationInfoS sAnimations[] = { &object_pst_Anim_000018, 1.0f, 0, -1, ANIMMODE_ONCE, 0 };

void EnPst_UpdateCollision(EnPst* this, PlayState* play) {
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
}

s32 func_80B2B874(EnPst* this) {
    switch (this->actor.params) {
        case 0:
            return gSaveContext.save.weekEventReg[0x1B] & 0x2;
        case 1:
            return gSaveContext.save.weekEventReg[0x1B] & 0x4;
        case 2:
            return gSaveContext.save.weekEventReg[0x1B] & 0x8;
        case 3:
            return gSaveContext.save.weekEventReg[0x1B] & 0x10;
        case 4:
            return gSaveContext.save.weekEventReg[0x1B] & 0x20;
        default:
            return false;
    }
}

s32 func_80B2B8F4(EnPst* this) {
    switch (this->actor.params) {
        case 0:
            return gSaveContext.save.weekEventReg[0x1B] & 0x40;
        case 1:
            return gSaveContext.save.weekEventReg[0x1B] & 0x80;
        case 2:
            return gSaveContext.save.weekEventReg[0x1C] & 0x1;
        case 3:
            return gSaveContext.save.weekEventReg[0x1C] & 0x2;
        case 4:
            return gSaveContext.save.weekEventReg[0x1C] & 0x4;
        default:
            return false;
    }
}

s32 func_80B2B974(Actor* thisx, PlayState* play) {
    s32 itemActionParam = 0;
    s32 scriptBranch = 0;
    EnPst* this = THIS;

    switch (this->unk20E) {
        case 0:
            switch (Message_GetState(&play->msgCtx)) {
                case TEXT_STATE_CHOICE:
                case TEXT_STATE_5:
                    if (Message_ShouldAdvance(play)) {
                        case TEXT_STATE_16:
                            itemActionParam = func_80123810(play);
                            scriptBranch = 0;
                            if ((itemActionParam == PLAYER_AP_LETTER_TO_KAFEI) ||
                                (itemActionParam == PLAYER_AP_LETTER_MAMA)) {
                                this->exchangeItemId = itemActionParam;
                                this->unk20E++;
                                scriptBranch = 1;
                            } else if (itemActionParam < PLAYER_AP_NONE) {
                                this->unk20E++;
                                scriptBranch = 3;
                            } else if (itemActionParam != PLAYER_AP_NONE) {
                                this->unk20E++;
                                scriptBranch = 2;
                            }
                    }
                    break;
            }
            break;
        case 1:
            if (this->exchangeItemId == EXCH_ITEM_LETTER_TO_KAFEI) {
                scriptBranch = 1;
            }
            break;
    }
    return scriptBranch;
}

s32* func_80B2BAA4(EnPst* this, PlayState* play) {
    if (Player_GetMask(play) == PLAYER_MASK_POSTMAN) {
        return D_80B2C3B8;
    }

    if (this->stateFlags & 0x10) {
        switch (this->actor.params) {
            case 0:
                return D_80B2C3E8;
            case 1:
                return D_80B2C408;
            case 2:
                return D_80B2C428;
            case 3:
                return D_80B2C448;
            case 4:
                return D_80B2C468;
            default:
                return NULL;
        }

    } else if (this->stateFlags & 0x20) {
        if (this->exchangeItemId == 0x33) {
            return D_80B2C488;
        }
        return D_80B2C490;
    } else {

        this->msgEventCallback = func_80B2B974;
        switch (this->actor.params) {
            case 0:
                return D_80B2C23C;
            case 1:
                return D_80B2C288;
            case 2:
                return D_80B2C2D4;
            case 3:
                return D_80B2C320;
            case 4:
                return D_80B2C36C;
            default:
                return NULL;
        }
    }
}

s32 EnPst_CheckTalk(EnPst* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s32 ret = false;

    if (this->stateFlags & 7) {
        if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
            this->stateFlags &= ~0x30;
            if (player->exchangeItemId == EXCH_ITEM_LETTER_TO_KAFEI) {
                this->stateFlags |= 0x10;
                this->exchangeItemId = player->exchangeItemId;
            } else if (player->exchangeItemId != 0) {
                this->stateFlags |= 0x20;
                this->exchangeItemId = player->exchangeItemId;
            }
            this->unk21C = func_80B2B874(this);
            SubS_UpdateFlags(&this->stateFlags, 0, 7);
            this->unk20E = 0;
            this->msgEventCallback = NULL;
            this->stateFlags |= 0x40;
            this->unk1DC = func_80B2BAA4(this, play);
            this->actionFunc = func_80B2BE54;
            ret = true;
        }
    }
    return ret;
}

s32 EnPst_UpdateFlagsSubs(EnPst* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    SubS_UpdateFlags(&this->stateFlags, 3, 7);
    return true;
}

s32 func_80B2BD30(EnPst* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    s32 ret = false;

    this->stateFlags = 0;

    switch (scheduleOutput->result) {
        case 1:
            ret = EnPst_UpdateFlagsSubs(this, play, scheduleOutput);
            break;
        case 2:
            ret = true;
            break;
    }
    return ret;
}

void func_80B2BD88(EnPst* this, PlayState* play) {
}

void func_80B2BD98(EnPst* this, PlayState* play) {
    static u8* sScheduleScript[] = {
        D_80B2C200, D_80B2C20C, D_80B2C218, D_80B2C224, D_80B2C230,
    };
    s16 params = this->actor.params;
    ScheduleOutput scheduleOutput;

    if (!Schedule_RunScript(play, sScheduleScript[params], &scheduleOutput) ||
        ((this->scheduleResult != scheduleOutput.result) && !func_80B2BD30(this, play, &scheduleOutput))) {
        this->actor.shape.shadowDraw = NULL;
        this->actor.flags &= ~ACTOR_FLAG_1;
        scheduleOutput.result = POSTBOX_SCH_NONE;
    } else {
        this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        this->actor.flags |= ACTOR_FLAG_1;
    }
    this->scheduleResult = scheduleOutput.result;
    func_80B2BD88(this, play);
}

void func_80B2BE54(EnPst* this, PlayState* play) {
    if (func_8010BF58(&this->actor, play, this->unk1DC, this->msgEventCallback, &this->msgEventArg4)) {
        if (func_80B2B874(this) != this->unk21C) {
            switch (gSaveContext.save.day) {
                case 1:
                    gSaveContext.save.weekEventReg[0x5B] |= 4;
                    break;

                case 2:
                    if (func_80B2B8F4(this) != 0) {
                        gSaveContext.save.weekEventReg[0x5B] |= 8;
                    } else {
                        gSaveContext.save.weekEventReg[0x5B] |= 4;
                    }
                    break;

                default:
                    gSaveContext.save.weekEventReg[0x5B] |= 8;
                    break;
            }
        }
        SubS_UpdateFlags(&this->stateFlags, 3, 7);
        this->msgEventArg4 = 0;
        this->actionFunc = func_80B2BD98;
    }
}

void EnPst_Init(Actor* thisx, PlayState* play) {
    EnPst* this = THIS;
    s32 pad;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 18.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &gPostboxSkel, NULL, this->jointTable, this->morphTable,
                       POSTBOX_LIMB_MAX);
    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &sColChkInfoInit);
    SubS_UpdateFlags(&this->stateFlags, 3, 7);
    SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimations, 0);
    this->actor.targetMode = 0;
    Actor_SetScale(&this->actor, 0.02f);
    this->actionFunc = func_80B2BD98;
    Actor_UpdateBgCheckInfo(play, &this->actor, 0.0f, 0.0f, 0.0f, 4);
}

void EnPst_Destroy(Actor* thisx, PlayState* play) {
    EnPst* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void EnPst_Update(Actor* thisx, PlayState* play) {
    EnPst* this = THIS;

    EnPst_CheckTalk(this, play);
    this->actionFunc(this, play);
    if (this->scheduleResult != POSTBOX_SCH_NONE) {
        if (Actor_IsFacingPlayer(&this->actor, 0x1FFE)) {
            this->unk214 = 0;
            func_8013C964(&this->actor, play, 60.0f, 20.0f, 0, this->stateFlags & 7);
        }
        Actor_SetFocus(&this->actor, 20.0f);
        EnPst_UpdateCollision(this, play);
    }
}

s32 EnPst_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnPst* this = THIS;
    f32 phi_fa1;

    if (limbIndex == 2) {
        if (this->stateFlags & 0x40) {
            phi_fa1 = -100.0f;
        } else {
            phi_fa1 = 0.0f;
        }
        Matrix_Translate(0.0f, phi_fa1, 0.0f, MTXMODE_APPLY);
    }
    return false;
}

void EnPst_Draw(Actor* thisx, PlayState* play) {
    EnPst* this = THIS;

    if (this->scheduleResult != POSTBOX_SCH_NONE) {
        func_8012C28C(play->state.gfxCtx);
        SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                              EnPst_OverrideLimbDraw, NULL, &this->actor);
    }
}
