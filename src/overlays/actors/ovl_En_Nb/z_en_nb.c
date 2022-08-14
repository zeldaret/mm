/*
 * File: z_en_nb.c
 * Overlay: ovl_En_Nb
 * Description: Anju's Grandma
 */

#include "z_en_nb.h"
#include "objects/object_nb/object_nb.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnNb*)thisx)

void EnNb_Init(Actor* thisx, PlayState* play);
void EnNb_Destroy(Actor* thisx, PlayState* play);
void EnNb_Update(Actor* thisx, PlayState* play);
void EnNb_Draw(Actor* thisx, PlayState* play);

void EnNb_FollowSchedule(EnNb* this, PlayState* play);
void func_80BC0EAC(EnNb* this, PlayState* play);

void func_80BC08E0(EnNb* this, PlayState* play);
void func_80BC0978(EnNb* this, PlayState* play);

s32 func_80BC00AC(EnNb* this, PlayState* play);
s32 func_80BC01DC(EnNb* this, PlayState* play);

typedef enum EnNbScheduleResult {
    /* 0 */ EN_NB_SCH_NONE,
    /* 1 */ EN_NB_SCH_1,
    /* 2 */ EN_NB_SCH_2,
    /* 3 */ EN_NB_SCH_3,
    /* 4 */ EN_NB_SCH_4,
} EnNbScheduleResult;

static u8 sScheduleScript[] = {
    /* 0x00 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(3, 0x21 - 0x04),
    /* 0x04 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_YADOYA, 0x12 - 0x08),
    /* 0x08 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S( 6,  0, 18,  0, 0x0F - 0x0E),
    /* 0x0E */ SCHEDULE_CMD_RET_NONE(),
    /* 0x0F */ SCHEDULE_CMD_RET_VAL_L(EN_NB_SCH_3),
    /* 0x12 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_OMOYA, 0x20 - 0x16),
    /* 0x16 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(18,  0,  6,  0, 0x1D - 0x1C),
    /* 0x1C */ SCHEDULE_CMD_RET_NONE(),
    /* 0x1D */ SCHEDULE_CMD_RET_VAL_L(EN_NB_SCH_4),
    /* 0x20 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x21 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_YADOYA, 0x72 - 0x25),
    /* 0x25 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(1, 0x47 - 0x29),
    /* 0x29 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S( 8,  0, 12,  0, 0x44 - 0x2F),
    /* 0x2F */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(12,  0, 12, 15, 0x41 - 0x35),
    /* 0x35 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(12, 15, 18,  0, 0x3E - 0x3B),
    /* 0x3B */ SCHEDULE_CMD_RET_VAL_L(EN_NB_SCH_3),
    /* 0x3E */ SCHEDULE_CMD_RET_VAL_L(EN_NB_SCH_1),
    /* 0x41 */ SCHEDULE_CMD_RET_VAL_L(EN_NB_SCH_2),
    /* 0x44 */ SCHEDULE_CMD_RET_VAL_L(EN_NB_SCH_1),
    /* 0x47 */ SCHEDULE_CMD_CHECK_FLAG_S(0x32, 0x20, 0x57 - 0x4B),
    /* 0x4B */ SCHEDULE_CMD_CHECK_TIME_RANGE_S( 8,  0, 18,  0, 0x54 - 0x51),
    /* 0x51 */ SCHEDULE_CMD_RET_VAL_L(EN_NB_SCH_3),
    /* 0x54 */ SCHEDULE_CMD_RET_VAL_L(EN_NB_SCH_1),
    /* 0x57 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S( 8,  0, 12,  0, 0x70 - 0x5D),
    /* 0x5D */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(12,  0, 12, 15, 0x6E - 0x63),
    /* 0x63 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(12, 15, 18,  0, 0x6C - 0x69),
    /* 0x69 */ SCHEDULE_CMD_RET_VAL_L(EN_NB_SCH_3),
    /* 0x6C */ SCHEDULE_CMD_RET_VAL_S(EN_NB_SCH_1),
    /* 0x6E */ SCHEDULE_CMD_RET_VAL_S(EN_NB_SCH_2),
    /* 0x70 */ SCHEDULE_CMD_RET_VAL_S(EN_NB_SCH_1),
    /* 0x72 */ SCHEDULE_CMD_RET_NONE(),
};

s32 D_80BC1464[] = {
    0x1B040800, 0x6A0A0010, 0x00080010, 0x00080000, 0x00080E29, 0x122D000E, 0x0C100E29, 0x012D000E, 0x0C100E29,
    0x020C0F29, 0x030C0500, 0x00000600, 0x22312D00, 0x0E121030, 0x1C04040E, 0x29040C20, 0x00030004, 0x150900C4,
    0x0900000F, 0x29050C15, 0x0900B930, 0x1D04040E, 0x290B0C20, 0x00030004, 0x150900A8, 0x0900000F, 0x290C0C15,
    0x09009D20, 0x00030017, 0x1B040400, 0x090E2911, 0x2D000E0C, 0x16100E29, 0x0A2D000E, 0x0C16101B, 0x0404003B,
    0x0E290D0C, 0x05000000, 0x0A00000E, 0x29102D00, 0x0E0C1216, 0x100E290E, 0x00320400, 0x590C0F29, 0x0F0C1206,
    0x000C0000, 0x13000C2F, 0x00002E2D, 0x002A2D00, 0x0E113204, 0x0C16100E, 0x29060C05, 0x000A0000, 0x00000E29,
    0x072D000E, 0x0C121610, 0x0E290800, 0x3202001E, 0x0C0F2909, 0x0C120600, 0x0C000013, 0x000C2F00, 0x002E2D00,
    0x292D000E, 0x1132020C, 0x16102D00, 0x0E0C1216, 0x10000000,
};

s32 D_80BC1574[] = {
    0x0900000E, 0x28C70C09, 0x0000170E, 0x28C80C09, 0x0000180E, 0x28C90C09, 0x0000170E,
    0x28CA0C09, 0x0000180E, 0x28CB0C09, 0x0000170E, 0x28CC0C09, 0x0000180E, 0x28CD0C09,
    0x0000170E, 0x28CE0C09, 0x0000180E, 0x28CF2D00, 0x012D000E, 0x0C090000, 0x10000000,
};

s32 D_80BC15C8[] = {
    0x0E23622D,
    0x000E0C10,
};

const ActorInit En_Nb_InitVars = {
    ACTOR_EN_NB,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_NB,
    sizeof(EnNb),
    (ActorFunc)EnNb_Init,
    (ActorFunc)EnNb_Destroy,
    (ActorFunc)EnNb_Update,
    (ActorFunc)EnNb_Draw,
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
    { 10, 68, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

static AnimationInfoS sAnimationInfo[] = {
    { &object_nb_Anim_000990, 1.0f, 0, -1, 0, 0 },   // EN_NB_ANIM_0
    { &object_nb_Anim_000990, 1.0f, 0, -1, 0, -4 }, // EN_NB_ANIM_1
    { &object_nb_Anim_000290, 1.0f, 0, -1, 2, 0 },   // EN_NB_ANIM_2
    { &object_nb_Anim_000290, 1.0f, 0, -1, 0, -4 }, // EN_NB_ANIM_3
    { &object_nb_Anim_00052C, 1.0f, 0, -1, 0, -4 },  // EN_NB_ANIM_4
    { &object_nb_Anim_0006D4, 1.0f, 0, -1, 2, -4 }, // EN_NB_ANIM_5
};

Actor* EnNb_FindActor(EnNb* this, PlayState* play, u8 actorCategory, s16 actorId) {
    Actor* thisx;
    Actor* actor = NULL;

    while (true) {
        actor = SubS_FindActor(play, actor, actorCategory, actorId);
        if (actor == NULL) {
            break;
        }

        thisx = &this->actor;
        if ((actor != thisx) && (actor->update != NULL)) {
            break;
        }

        if (actor->next == NULL) {
            actor = NULL;
            break;
        }

        actor = actor->next;
    }

    return actor;
}

void func_80BBFE60(EnNb* this) {
    this->skelAnime.playSpeed = this->animPlaySpeed;
    SkelAnime_Update(&this->skelAnime);
}

s32 EnNb_ChangeAnim(EnNb* this, EnNbAnimation animIndex) {
    s32 shouldChange = false;
    s32 didAnimationChange = false;

    if ((animIndex == EN_NB_ANIM_0) || (animIndex == EN_NB_ANIM_1)) {
        if ((this->animIndex != EN_NB_ANIM_0) && (this->animIndex != EN_NB_ANIM_1)) {
            shouldChange = true;
        }
    } else if (animIndex != this->animIndex) {
        shouldChange = true;
    }

    if (shouldChange) {
        this->animIndex = animIndex;
        didAnimationChange = SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, animIndex);
        this->animPlaySpeed = this->skelAnime.playSpeed;
    }

    return didAnimationChange;
}

void func_80BBFF24(EnNb* this, PlayState* play) {
    f32 diff;
    s32 pad;

    Collider_UpdateCylinder(&this->actor, &this->collider);

    diff = this->actor.focus.pos.y - this->actor.world.pos.y;
    this->collider.dim.height = diff;
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
}

Actor* func_80BBFF90(EnNb* this, PlayState* play) {
    Actor* actor;

    if (this->schResultValue == EN_NB_SCH_2) {
        actor = EnNb_FindActor(this, play, ACTORCAT_NPC, ACTOR_EN_AN);
    } else {
        actor = &GET_PLAYER(play)->actor;
    }
    return actor;
}

s32 func_80BBFFD4(EnNb* this, s16 arg1) {
    s32 ret = false;

    if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
        ActorCutscene_SetIntentToPlay(arg1);
    } else if (ActorCutscene_GetCanPlayNext(arg1)) {
        ActorCutscene_StartAndSetUnkLinkFields(arg1, &this->actor);
        ret = true;
    } else {
        ActorCutscene_SetIntentToPlay(arg1);
    }

    return ret;
}

s16 func_80BC0050(EnNb* this, s32 arg1) {
    s16 cutscene = this->actor.cutscene;
    s32 i;

    for (i = 0; i < arg1; i++) {
        cutscene = ActorCutscene_GetAdditionalCutscene(cutscene);
    }

    return cutscene;
}

s32 func_80BC00AC(EnNb* this, PlayState* play) {
    s32 pad;
    s16 sp2A = func_80BC0050(this, 0);
    s32 phi_v1 = 0;

    switch (this->unk_288) {
        case 0:
            if (func_80BBFFD4(this, sp2A)) {
                case 2:
                case 4:
                case 6:
                case 8:
                    Camera_SetTargetActor(Play_GetCamera(play, ActorCutscene_GetCurrentSubCamId(sp2A)),
                                          &this->actor);
                    this->unk_288++;
                    phi_v1 = 1;
            }
            break;

        case 1:
        case 3:
        case 5:
        case 7:
            if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
                Camera_SetTargetActor(Play_GetCamera(play, ActorCutscene_GetCurrentSubCamId(sp2A)),
                                      this->actor.child);
            }
            this->unk_288++;
            phi_v1 = 1;
            break;

        case 9:
            ActorCutscene_Stop(sp2A);
            this->unk_288++;
            phi_v1 = 1;
            break;
    }

    return phi_v1;
}

s32 func_80BC01DC(EnNb* this, PlayState* play) {
    s32 pad[2];
    s32 sp2C = 0;

    switch (this->unk_288) {
        case 0:
            if (Player_GetMask(play) == PLAYER_MASK_ALL_NIGHT) {
                this->unk_288 = 1;
            } else {
                this->unk_288 = 5;
            }
            break;

        case 1:
            func_8016A268(&play->state, 1, 0, 0, 0, 0);
            this->unk_286 = 40;
            this->unk_288 = (u16)(this->unk_288 + 1);
            break;

        case 2:
            MREG(68) = (s16)(s32)(255.0f - (((f32)ABS_ALT(20 - this->unk_286) / 20.0f) * 255.0f));

            if (this->unk_286 == 20) {
                if (gSaveContext.eventInf[4] & 4) {
                    play->interfaceCtx.unk_31B = 0;
                } else {
                    play->interfaceCtx.unk_31B = 1;
                }
                play->interfaceCtx.unk_31A = 6;
                XREG(91) = 0xFF;
            }

            if (DECR(this->unk_286) == 0) {
                this->unk_288++;
            }
            break;

        case 3:
            play->interfaceCtx.unk_31A = 4;
            this->unk_288++;
            sp2C = 1;
            break;

        case 4:
            play->interfaceCtx.unk_31A = 5;
            this->unk_288++;
            /* fallthrough */

        case 5:
            if (!(gSaveContext.eventInf[4] & 4)) {
                gSaveContext.save.time = CLOCK_TIME(8, 0);
                Sram_IncrementDay();
            } else {
                func_800FE658(120.0f);
            }

            this->unk_288++;
            play->nextEntranceIndex = 0xBC20;
            gSaveContext.nextCutsceneIndex = 0;
            play->transitionTrigger = TRANS_TRIGGER_START;
            play->transitionType = TRANS_TYPE_02;
            gSaveContext.nextTransitionType = TRANS_TYPE_06;
            gSaveContext.eventInf[4] |= 8;
            break;
    }

    return sp2C;
}

UNK_PTR func_80BC045C(EnNb* this, PlayState* play) {
    if (gSaveContext.eventInf[4] & 8) {
        this->unk_28C = func_80BC01DC;
        return &D_80BC1464;
    }

    if (this->schResultValue == EN_NB_SCH_2) {
        this->unk_28C = func_80BC00AC;
        return &D_80BC1574;
    }

    if (Player_GetMask(play) == PLAYER_MASK_KAFEIS_MASK) {
        return &D_80BC15C8;
    }

    this->unk_28C = func_80BC01DC;
    return &D_80BC1464;
}

s32 func_80BC04FC(EnNb* this, PlayState* play) {
    s32 ret = false;

    if (this->stateFlags & (EN_NB_FLAG_1 | EN_NB_FLAG_2 | EN_NB_FLAG_4)) {
        if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
            this->stateFlags |= EN_NB_FLAG_20;
            SubS_UpdateFlags(&this->stateFlags, EN_NB_FLAG_NONE, EN_NB_FLAG_1 | EN_NB_FLAG_2 | EN_NB_FLAG_4);
            this->unk_288 = 0;
            this->unk_28C = NULL;
            this->actor.child = this->unk_1E8;
            this->unk_1E0 = func_80BC045C(this, play);
            this->stateFlags |= EN_NB_FLAG_20;
            this->actionFunc = func_80BC0EAC;
            ret = true;
        }
    }
    return ret;
}

void func_80BC05A8(EnNb* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    TextState talkState = Message_GetState(&play->msgCtx);
    u16 textId = play->msgCtx.currentTextId;

    if ((&this->actor == player->targetActor) && ((textId < 0xFF) || (textId > 0x200)) && (talkState == TEXT_STATE_3) &&
        (this->prevTalkState == TEXT_STATE_3)) {
        if ((play->state.frames % 3) == 0) {
            if (this->unk_26C == 120.0f) {
                this->unk_26C = 0.0f;
            } else {
                this->unk_26C = 120.0f;
            }
        }
    } else {
        this->unk_26C = 0.0f;
    }

    Math_SmoothStepToF(&this->unk_270, this->unk_26C, 0.8f, 40.0f, 10.0f);
    Matrix_Translate(this->unk_270, 0.0f, 0.0f, 1);
    this->prevTalkState = talkState;
}

void func_80BC06C4(EnNb* this) {
    s32 pad;
    Vec3f sp40;
    Vec3f sp34;
    Player* player;

    Math_Vec3f_Copy(&sp40, &this->unk_1E8->world.pos);
    Math_Vec3f_Copy(&sp34, &this->actor.world.pos);
    Math_ApproachS(&this->unk_27E, Math_Vec3f_Yaw(&sp34, &sp40) - this->actor.shape.rot.y, 4, 0x2AA8);

    this->unk_27E = CLAMP(this->unk_27E, -0x1FFE, 0x1FFE);

    Math_Vec3f_Copy(&sp34, &this->actor.focus.pos);

    if (this->unk_1E8->id == ACTOR_PLAYER) {
        player = (Player*)this->unk_1E8;

        sp40.y = player->bodyPartsPos[7].y + 3.0f;
    } else {
        Math_Vec3f_Copy(&sp40, &this->unk_1E8->focus.pos);
    }

    Math_ApproachS(&this->headRot, Math_Vec3f_Pitch(&sp34, &sp40), 4, 0x2AA8);

    this->headRot = CLAMP(this->headRot, -0x1554, 0x1554);
}

void func_80BC0800(EnNb* this) {
    if (this->stateFlags & EN_NB_FLAG_20) {
        if ((this->unk_1E8 != NULL) && (this->unk_1E8->update != NULL)) {
            if (DECR(this->unk_282) == 0) {
                func_80BC06C4(this);
                this->stateFlags &= ~EN_NB_FLAG_400;
                this->stateFlags |= EN_NB_FLAG_100;
                return;
            }
        }
    }

    if (this->stateFlags & EN_NB_FLAG_100) {
        this->stateFlags &= ~EN_NB_FLAG_100;
        this->headRot = 0;
        this->unk_27E = 0;
        this->unk_282 = 20;
    } else if (DECR(this->unk_282) == 0) {
        this->stateFlags |= EN_NB_FLAG_400;
    }
}

// Related to both stories?
void func_80BC08E0(EnNb* this, PlayState* play) {
    if (this->unk_284 == 0) {
        EnNb_ChangeAnim(this, EN_NB_ANIM_2);
        this->stateFlags |= EN_NB_FLAG_400;
        this->unk_284++;
    } else if ((this->unk_284 == 1) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        EnNb_ChangeAnim(this, EN_NB_ANIM_1);
        this->stateFlags &= ~EN_NB_FLAG_400;
        this->unk_284++;
    }
}

void func_80BC0978(EnNb* this, PlayState* play) {
    if (this->unk_284 == 0) {
        EnNb_ChangeAnim(this, EN_NB_ANIM_5);
        this->stateFlags &= ~EN_NB_FLAG_20;
        this->stateFlags |= EN_NB_FLAG_400;
        this->unk_284++;
    } else if ((this->unk_284 == 1) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        EnNb_ChangeAnim(this, EN_NB_ANIM_3);
        this->stateFlags &= ~EN_NB_FLAG_400;
        this->unk_284++;
    }
}

s32 func_80BC0A18(EnNb* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    u16 currentTextId = play->msgCtx.currentTextId;

    if (player->stateFlags1 & PLAYER_STATE1_40) {
        this->stateFlags |= EN_NB_FLAG_80;

        if (this->textId != currentTextId) {
            switch (currentTextId) {
                case 0x28CF:
                    this->stateFlags |= EN_NB_FLAG_20;
                    EnNb_ChangeAnim(this, EN_NB_ANIM_3);
                    break;

                case 0x2904: // "You want to hear the carnival of time story? ..."
                case 0x290B: // "You want to hear the four giants story? ..."
                    this->unk_18C = func_80BC08E0;
                    this->unk_284 = 0;
                    break;

                case 0x28CD:
                    this->unk_18C = func_80BC0978;
                    this->unk_284 = 0;
                    break;

                case 0x28CB:
                    EnNb_ChangeAnim(this, EN_NB_ANIM_4);
                    break;

                case 0x28C7:
                case 0x2901:
                case 0x2902:
                case 0x2906:
                case 0x290D:
                case 0x2912:
                    EnNb_ChangeAnim(this, EN_NB_ANIM_3);
                    break;
            }
        }

        this->textId = currentTextId;
    } else if (this->stateFlags & EN_NB_FLAG_80) {
        this->unk_18C = NULL;
        this->textId = 0;
        this->stateFlags &= ~EN_NB_FLAG_80;
        EnNb_ChangeAnim(this, EN_NB_ANIM_1);
    }

    if (this->unk_18C != NULL) {
        this->unk_18C(this, play);
    }

    return 0;
}

s32 func_80BC0B98(EnNb* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    s32 success = false;

    if (EnNb_FindActor(this, play, ACTORCAT_NPC, ACTOR_EN_AN) != NULL) {
        SubS_UpdateFlags(&this->stateFlags, EN_NB_FLAG_1 | EN_NB_FLAG_2, EN_NB_FLAG_1 | EN_NB_FLAG_2 | EN_NB_FLAG_4);
        this->stateFlags |= EN_NB_FLAG_20;
        EnNb_ChangeAnim(this, EN_NB_ANIM_0);
        success = true;
    }

    return success;
}

s32 func_80BC0C0C(EnNb* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    if (!(gSaveContext.eventInf[4] & 8)) {
        SubS_UpdateFlags(&this->stateFlags, EN_NB_FLAG_1 | EN_NB_FLAG_2, EN_NB_FLAG_1 | EN_NB_FLAG_2 | EN_NB_FLAG_4);
    } else {
        SubS_UpdateFlags(&this->stateFlags, EN_NB_FLAG_4, EN_NB_FLAG_1 | EN_NB_FLAG_2 | EN_NB_FLAG_4);
    }
    EnNb_ChangeAnim(this, EN_NB_ANIM_0);

    return true;
}

s32 EnNb_ProcessScheduleOutput(EnNb* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    s32 success;

    this->actor.flags |= ACTOR_FLAG_1;
    this->actor.targetMode = 0;
    this->stateFlags = EN_NB_FLAG_NONE;
    this->unk_274 = 40.0f;

    switch (scheduleOutput->result) {
        default:
            success = false;
            break;

        case EN_NB_SCH_1:
        case EN_NB_SCH_3:
        case EN_NB_SCH_4:
            success = func_80BC0C0C(this, play, scheduleOutput);
            break;

        case EN_NB_SCH_2:
            success = func_80BC0B98(this, play, scheduleOutput);
            break;
    }
    return success;
}

s32 func_80BC0D08(EnNb* this, PlayState* play) {
    return 0;
}

void EnNb_HandleSchedule(EnNb* this, PlayState* play) {
    if ((this->schResultValue == EN_NB_SCH_1) || (this->schResultValue == EN_NB_SCH_2) || (this->schResultValue == EN_NB_SCH_3) || (this->schResultValue == EN_NB_SCH_4)) {
        func_80BC0D08(this, play);
    }

    Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 3, 0x2AA8);
}

void EnNb_FollowSchedule(EnNb* this, PlayState* play) {
    ScheduleOutput scheduleResult;

    this->timePathTimeSpeed = REG(15) + ((void)0, gSaveContext.save.daySpeed);

    if (gSaveContext.eventInf[4] & 8) {
        scheduleResult.result = EN_NB_SCH_1;
        EnNb_ProcessScheduleOutput(this, play, &scheduleResult);
        this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        this->actor.flags |= ACTOR_FLAG_1;
    } else if ((!Schedule_RunScript(play, sScheduleScript, &scheduleResult)) ||
               ((this->schResultValue != scheduleResult.result) && !EnNb_ProcessScheduleOutput(this, play, &scheduleResult))) {
        this->actor.shape.shadowDraw = NULL;
        this->actor.flags &= ~ACTOR_FLAG_1;
        scheduleResult.result = EN_NB_SCH_NONE;
    } else {
        this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        this->actor.flags |= ACTOR_FLAG_1;
    }

    this->schResultValue = scheduleResult.result;
    this->unk_1E8 = func_80BBFF90(this, play);
    EnNb_HandleSchedule(this, play);
}

void func_80BC0EAC(EnNb* this, PlayState* play) {
    if (func_8010BF58(&this->actor, play, this->unk_1E0, this->unk_28C, &this->unk_1E4) != 0) {
        if (gSaveContext.eventInf[4] & 8) {
            gSaveContext.eventInf[4] &= (u8)~4;
            gSaveContext.eventInf[4] &= (u8)~8;
        }

        SubS_UpdateFlags(&this->stateFlags, EN_NB_FLAG_1 | EN_NB_FLAG_2, EN_NB_FLAG_1 | EN_NB_FLAG_2 | EN_NB_FLAG_4);
        if (this->schResultValue != EN_NB_SCH_2) {
            this->stateFlags &= ~EN_NB_FLAG_20;
        }

        this->actor.child = NULL;
        this->stateFlags |= EN_NB_FLAG_400;
        this->unk_282 = 20;
        this->unk_1E4 = 0;
        this->actionFunc = EnNb_FollowSchedule;
    }
}

void EnNb_Init(Actor* thisx, PlayState* play) {
    EnNb* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &object_nb_Skel_008C40, NULL, this->jointTable, this->morphTable,
                       OBJECT_NB_LIMB_MAX);

    this->animIndex = EN_NB_ANIM_INVALID;
    EnNb_ChangeAnim(this, EN_NB_ANIM_0);

    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &sColChkInfoInit);
    Actor_SetScale(&this->actor, 0.01f);
    this->stateFlags = EN_NB_FLAG_NONE;

    if (gSaveContext.eventInf[4] & 8) {
        SubS_UpdateFlags(&this->stateFlags, EN_NB_FLAG_4, EN_NB_FLAG_1 | EN_NB_FLAG_2 | EN_NB_FLAG_4);
    } else {
        gSaveContext.eventInf[4] &= (u8)~4;
        gSaveContext.eventInf[4] &= (u8)~8;
    }

    this->actionFunc = EnNb_FollowSchedule;
    this->actionFunc(this, play);
}

void EnNb_Destroy(Actor* thisx, PlayState* play) {
    EnNb* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
    play->interfaceCtx.unk_31A = 3;
}

void EnNb_Update(Actor* thisx, PlayState* play) {
    EnNb* this = THIS;

    func_80BC04FC(this, play);
    this->actionFunc(this, play);
    func_80BC0A18(this, play);

    if (this->schResultValue != EN_NB_SCH_NONE) {
        func_80BBFE60(this);
        func_80BC0800(this);
        if (Actor_IsFacingPlayer(&this->actor, 0x38E0)) {
            func_8013C964(&this->actor, play, this->unk_274, 30.0f, ITEM_OCARINA, this->stateFlags & (EN_NB_FLAG_1 | EN_NB_FLAG_2 | EN_NB_FLAG_4));
        }
        func_80BBFF24(this, play);
    }
}

s32 EnNb_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnNb* this = THIS;

    if (limbIndex == OBJECT_NB_LIMB_05) {
        func_80BC05A8(this, play);
    }

    return false;
}

void EnNb_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnNb* this = THIS;
    Vec3f focusTarget;

    if ((ActorCutscene_GetCurrentIndex() == -1) && (limbIndex == OBJECT_NB_LIMB_05)) {
        Matrix_MultVec3f(&gZeroVec3f, &focusTarget);
        Math_ApproachF(&thisx->focus.pos.x, focusTarget.x, 0.6f, 10000.0f);
        Math_ApproachF(&thisx->focus.pos.y, focusTarget.y, 0.6f, 10000.0f);
        Math_ApproachF(&thisx->focus.pos.z, focusTarget.z, 0.6f, 10000.0f);
        Math_Vec3s_Copy(&thisx->focus.rot, &thisx->world.rot);
    }
}

void EnNb_TransformLimbDraw(PlayState* play, s32 limbIndex, Actor* thisx) {
    EnNb* this = THIS;
    s32 stepRot;
    s32 overrideRot;

    if (!(this->stateFlags & EN_NB_FLAG_400)) {
        overrideRot = false;
        if (this->stateFlags & EN_NB_FLAG_100) {
            overrideRot = true;
            stepRot = true;
        } else {
            stepRot = true;
        }
    } else {
        overrideRot = false;
        stepRot = false;
    }

    if (limbIndex == OBJECT_NB_LIMB_05) {
        SubS_UpdateLimb(this->headRot + 0x4000, this->unk_27E + this->actor.shape.rot.y + 0x4000, &this->unk_1F0,
                      &this->unk_1FC, stepRot, overrideRot);
        Matrix_Pop();
        Matrix_Translate(this->unk_1F0.x, this->unk_1F0.y, this->unk_1F0.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateYS(this->unk_1FC.y, MTXMODE_APPLY);
        Matrix_RotateXS(this->unk_1FC.x, MTXMODE_APPLY);
        Matrix_RotateZS(this->unk_1FC.z, MTXMODE_APPLY);
        Matrix_Push();
    }
}

void EnNb_Draw(Actor* thisx, PlayState* play) {
    EnNb* this = THIS;

    if (this->schResultValue != EN_NB_SCH_NONE) {
        func_8012C5B0(play->state.gfxCtx);
        SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                       this->skelAnime.dListCount, EnNb_OverrideLimbDraw, EnNb_PostLimbDraw,
                                       EnNb_TransformLimbDraw, &this->actor);
    }
}
