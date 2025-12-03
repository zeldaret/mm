/*
 * File: z_en_kendo_js.c
 * Overlay: ovl_En_Kendo_Js
 * Description: Swordsman
 */

#include "z_en_kendo_js.h"
#include "overlays/actors/ovl_En_Maruta/z_en_maruta.h"

#define FLAGS                                                                                  \
    (ACTOR_FLAG_ATTENTION_ENABLED | ACTOR_FLAG_FRIENDLY | ACTOR_FLAG_UPDATE_CULLING_DISABLED | \
     ACTOR_FLAG_UPDATE_DURING_OCARINA | ACTOR_FLAG_LOCK_ON_DISABLED)

void EnKendoJs_Init(Actor* thisx, PlayState* play);
void EnKendoJs_Destroy(Actor* thisx, PlayState* play);
void EnKendoJs_Update(Actor* thisx, PlayState* play);
void EnKendoJs_Draw(Actor* thisx, PlayState* play);

void EnKendoJs_SetupAwaitingTalk(EnKendoJs* this);
void EnKendoJs_AwaitTalk(EnKendoJs* this, PlayState* play);
void EnKendoJs_SetupMessageStateHandler(EnKendoJs* this);
void EnKendoJs_HandleMessageState(EnKendoJs* this, PlayState* play);
void EnKendoJs_SetupNoviceCourse(EnKendoJs* this);
void EnKendoJs_MovePlayerToStartNoviceCourse(EnKendoJs* this, PlayState* play);
void EnKendoJs_StartNoviceCourse(EnKendoJs* this);
void EnKendoJs_NoviceCourse(EnKendoJs* this, PlayState* play);
void EnKendoJs_SetupExpertCourse(EnKendoJs* this);
void EnKendoJs_MovePlayerToStartExpertCourse(EnKendoJs* this, PlayState* play);
void EnKendoJs_ExpertCourse(EnKendoJs* this, PlayState* play);
void EnKendoJs_SetupPrize(EnKendoJs* this);
void EnKendoJs_AwardPrize(EnKendoJs* this, PlayState* play);
void EnKendoJs_AfterPrizeAccepted(EnKendoJs* this);
void EnKendoJs_AwaitFinalMessage(EnKendoJs* this, PlayState* play);
void EnKendoJs_SetExpertCourseCamera(EnKendoJs* this, PlayState* play);
s32 EnKendoJs_MovePlayerToPos(PlayState* play, Vec3f targetPos);
void EnKendoJs_SpawnLog(EnKendoJs* this, PlayState* play, s32 position);
void EnKendoJs_RetractLogs(EnKendoJs* this, PlayState* play);

ActorProfile En_Kendo_Js_Profile = {
    /**/ ACTOR_EN_KENDO_JS,
    /**/ ACTORCAT_NPC,
    /**/ FLAGS,
    /**/ OBJECT_JS,
    /**/ sizeof(EnKendoJs),
    /**/ EnKendoJs_Init,
    /**/ EnKendoJs_Destroy,
    /**/ EnKendoJs_Update,
    /**/ EnKendoJs_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COL_MATERIAL_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEM_MATERIAL_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        ATELEM_NONE | ATELEM_SFX_NORMAL,
        ACELEM_NONE,
        OCELEM_ON,
    },
    { 18, 30, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

typedef enum EnKendoJsAnimation {
    /* 0 */ ENKENDOJS_ANIM_SLAPPING_KNEE, // unused
    /* 1 */ ENKENDOJS_ANIM_DEFAULT,
    /* 2 */ ENKENDOJS_ANIM_FLAILING,
    /* 3 */ ENKENDOJS_ANIM_STOP_FLAILING,
    /* 4 */ ENKENDOJS_ANIM_SCARED,
    /* 5 */ ENKENDOJS_ANIM_MAX
} EnKendoJsAnimation;

static AnimationInfo sAnimationInfo[ENKENDOJS_ANIM_MAX] = {
    { &object_js_Anim_SlappingKnee, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -8.0f }, // unused
    { &object_js_Anim_Default, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -8.0f },
    { &object_js_Anim_Flailing, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -8.0f },
    { &object_js_Anim_StopFlailing, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -8.0f },
    { &object_js_Anim_Scared, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -8.0f },
};

typedef enum EnKendoJsMessage {
    ENKENDOJS_MSG_HUMAN_INTRO_DAY1 = 0x2710,
    ENKENDOJS_MSG_HUMAN_INTRO_SHORT_DAY1 = 0x2711,
    ENKENDOJS_MSG_HUMAN_INTRO_DAY2 = 0x2712,
    ENKENDOJS_MSG_HUMAN_INTRO_SHORT_DAY2 = 0x2713,
    ENKENDOJS_MSG_HUMAN_INTRO_DAY3 = 0x2714,
    ENKENDOJS_MSG_HUMAN_INTRO_SHORT_DAY3 = 0x2715,
    ENKENDOJS_MSG_WHICH_COURSE = 0x2716,
    ENKENDOJS_MSG_CANCEL = 0x2717,
    ENKENDOJS_MSG_NOT_ENOUGH_RUPEES = 0x2718,
    ENKENDOJS_MSG_NOVICE_COURSE_SELECTED = 0x2719,
    ENKENDOJS_MSG_NOVICE_COURSE_START = 0x271A,
    ENKENDOJS_MSG_NOVICE_COURSE_RETRY_ROUND1 = 0x271B,
    ENKENDOJS_MSG_NOVICE_COURSE_PASS_ROUND1 = 0x271C,
    ENKENDOJS_MSG_NOVICE_COURSE_RETRY_ROUND2 = 0x271D,
    ENKENDOJS_MSG_NOVICE_COURSE_PASS_ROUND2 = 0x271E,
    ENKENDOJS_MSG_NOVICE_COURSE_RETRY_ROUND3 = 0x271F,
    ENKENDOJS_MSG_NOVICE_COURSE_PASS_ROUND3 = 0x2720,
    ENKENDOJS_MSG_NOVICE_COURSE_RETRY_ROUND4 = 0x2721,
    ENKENDOJS_MSG_NOVICE_COURSE_PASS_ROUND4 = 0x2722,
    ENKENDOJS_MSG_NOVICE_COURSE_RETRY_ROUND5 = 0x2723,
    ENKENDOJS_MSG_NOVICE_COURSE_PASS_ROUND5 = 0x2724,
    ENKENDOJS_MSG_NOVICE_COURSE_RETRY_ROUND6 = 0x2725,
    ENKENDOJS_MSG_NOVICE_COURSE_PASS_ROUND6 = 0x2726,
    ENKENDOJS_MSG_NOVICE_COURSE_RETRY_ROUND7 = 0x2727,
    ENKENDOJS_MSG_NOVICE_COURSE_PASS_ROUND7 = 0x2728,
    ENKENDOJS_MSG_NOVICE_COURSE_WRONG = 0x2729,
    ENKENDOJS_MSG_NOVICE_COURSE_SHEATH_WEAPON = 0x272A,
    ENKENDOJS_MSG_NOVICE_COURSE_NO_Z_TARGET = 0x272B,
    ENKENDOJS_MSG_NOVICE_COURSE_NO_SWORD = 0x272C,
    ENKENDOJS_MSG_EXPERT_COURSE_PERFECT = 0x272D,
    ENKENDOJS_MSG_EXPERT_COURSE_INSUFFICIENT = 0x272E,
    ENKENDOJS_MSG_EXPERT_COURSE_ACCEPT_HEART_PIECE = 0x272F,
    ENKENDOJS_MSG_EXPERT_COURSE_ACCEPT_RED_RUPEE = 0x2730,
    ENKENDOJS_MSG_DEKU_DAY1 = 0x2731,
    ENKENDOJS_MSG_DEKU_DAY2 = 0x2732,
    ENKENDOJS_MSG_DEKU_DAY3 = 0x2733,
    ENKENDOJS_MSG_GORON_DAY1 = 0x2734,
    ENKENDOJS_MSG_GORON_DAY2 = 0x2735,
    ENKENDOJS_MSG_GORON_DAY3 = 0x2736,
    ENKENDOJS_MSG_ZORA_DAY1 = 0x2737,
    ENKENDOJS_MSG_ZORA_DAY2 = 0x2738,
    ENKENDOJS_MSG_ZORA_DAY3 = 0x2739,
    ENKENDOJS_MSG_EXPERT_COURSE_SELECTED = 0x273A,
    ENKENDOJS_MSG_EXPERT_COURSE_RULES = 0x273B,
    ENKENDOJS_MSG_DONT_WANT_TO_DIE = 0x273C,
} EnKendoJsMessage;

#define ENKENDOJS_MSG_MASK(play) Player_GetMask(play) + 0x273C

#define ENKENDOJS_QUEUE_MSG(thisx, play, textId)       \
    Message_StartTextbox(play, textId, &thisx->actor); \
    thisx->curTextId = textId;

s16 sNonHumanMessages[][3] = {
    { ENKENDOJS_MSG_DEKU_DAY1, ENKENDOJS_MSG_DEKU_DAY2, ENKENDOJS_MSG_DEKU_DAY3 },
    { ENKENDOJS_MSG_GORON_DAY1, ENKENDOJS_MSG_GORON_DAY2, ENKENDOJS_MSG_GORON_DAY3 },
    { ENKENDOJS_MSG_ZORA_DAY1, ENKENDOJS_MSG_ZORA_DAY2, ENKENDOJS_MSG_ZORA_DAY3 },
};

s16 sHumanMessages[][3] = {
    { ENKENDOJS_MSG_HUMAN_INTRO_DAY1, ENKENDOJS_MSG_HUMAN_INTRO_DAY2, ENKENDOJS_MSG_HUMAN_INTRO_DAY3 },
    { ENKENDOJS_MSG_HUMAN_INTRO_SHORT_DAY1, ENKENDOJS_MSG_HUMAN_INTRO_SHORT_DAY2,
      ENKENDOJS_MSG_HUMAN_INTRO_SHORT_DAY3 },
};

s16 sNoviceCourseProgressMessages[] = {
    ENKENDOJS_MSG_NOVICE_COURSE_PASS_ROUND1, ENKENDOJS_MSG_NOVICE_COURSE_PASS_ROUND2,
    ENKENDOJS_MSG_NOVICE_COURSE_PASS_ROUND3, ENKENDOJS_MSG_NOVICE_COURSE_PASS_ROUND4,
    ENKENDOJS_MSG_NOVICE_COURSE_PASS_ROUND5, ENKENDOJS_MSG_NOVICE_COURSE_PASS_ROUND6,
    ENKENDOJS_MSG_NOVICE_COURSE_PASS_ROUND7,
};

s16 sNoviceCourseTryAgainMessages[] = {
    ENKENDOJS_MSG_NOVICE_COURSE_RETRY_ROUND1, ENKENDOJS_MSG_NOVICE_COURSE_RETRY_ROUND2,
    ENKENDOJS_MSG_NOVICE_COURSE_RETRY_ROUND3, ENKENDOJS_MSG_NOVICE_COURSE_RETRY_ROUND4,
    ENKENDOJS_MSG_NOVICE_COURSE_RETRY_ROUND5, ENKENDOJS_MSG_NOVICE_COURSE_RETRY_ROUND6,
    ENKENDOJS_MSG_NOVICE_COURSE_RETRY_ROUND7,
};

typedef enum EnKendoJsCourseState {
    /* 0 */ ENKENDOJS_COURSE_PAUSED,
    /* 1 */ ENKENDOJS_COURSE_ACTIVE,
    /* 2 */ ENKENDOJS_COURSE_RETRY,
} EnKendoJsCourseState;

typedef enum EnKendoJsNoviceCourseLesson {
    /* 0 */ ENKENDOJS_NOVICE_SIDE_JUMP,
    /* 1 */ ENKENDOJS_NOVICE_ROLL,
    /* 2 */ ENKENDOJS_NOVICE_BACKFLIP,
    /* 3 */ ENKENDOJS_NOVICE_SWORD_ATTACK,
    /* 4 */ ENKENDOJS_NOVICE_SWORD_TARGET,
    /* 5 */ ENKENDOJS_NOVICE_SWORD_THRUST,
    /* 6 */ ENKENDOJS_NOVICE_JUMP_ATTACK,
    /* 7 */ ENKENDOJS_NOVICE_FINISHED,
} EnKendoJsNoviceCourseLesson;

typedef enum EnKendoJsNoviceCourseActionResult {
    /* 0 */ ENKENDOJS_RESULT_CORRECT,
    /* 1 */ ENKENDOJS_RESULT_INCORRECT,
    /* 2 */ ENKENDOJS_RESULT_PENDING,
} EnKendoJsNoviceCourseActionResult;

void EnKendoJs_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnKendoJs* this = (EnKendoJs*)thisx;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 36.0f);

    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &sColChkInfoInit);

    SkelAnime_InitFlex(play, &this->skelAnime, &object_js_Skel_006990, &object_js_Anim_Default, this->jointTable,
                       this->morphTable, OBJECT_JS_LIMB_MAX);

    if ((CURRENT_DAY == 3) && ((CURRENT_TIME > CLOCK_TIME(23, 0)) || (CURRENT_TIME < CLOCK_TIME(6, 0)))) {
        if (ENKENDOJS_GET_FF(&this->actor) != ENKENDOJS_FF_1) {
            Actor_Spawn(&play->actorCtx, play, ACTOR_EN_KANBAN, this->actor.home.pos.x, this->actor.home.pos.y,
                        this->actor.home.pos.z - 10.0f, this->actor.home.rot.x, this->actor.home.rot.y,
                        this->actor.home.rot.z, 0x10);
            Actor_Kill(&this->actor);
        } else {
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, ENKENDOJS_ANIM_SCARED);
        }
    } else if (ENKENDOJS_GET_FF(&this->actor) == ENKENDOJS_FF_1) {
        Actor_Kill(&this->actor);
    }

    Actor_UpdateBgCheckInfo(play, &this->actor, 0.0f, 0.0f, 0.0f, UPDBGCHECKINFO_FLAG_4);

    if (ENKENDOJS_GET_FF(&this->actor) != ENKENDOJS_FF_1) {
        Path* path = &play->setupPathList[ENKENDOJS_GET_PATH_INDEX(&this->actor)];

        this->pathPoints = Lib_SegmentedToVirtual(path->points);
    }

    this->actor.flags &= ~ACTOR_FLAG_ATTENTION_ENABLED;
    this->actor.focus.pos = this->actor.world.pos;
    this->actor.focus.pos.y += 30.0f;
    this->actor.child = NULL;
    this->hasSpoken = false;
    this->numLogs = 0;
    this->isSlashingLog = 0;
    this->courseState = ENKENDOJS_COURSE_PAUSED;
    EnKendoJs_SetupAwaitingTalk(this);
}

void EnKendoJs_Destroy(Actor* thisx, PlayState* play) {
    EnKendoJs* this = (EnKendoJs*)thisx;

    Collider_DestroyCylinder(play, &this->collider);
    CLEAR_WEEKEVENTREG(WEEKEVENTREG_STARTED_SWORDSMAN_MINIGAME);
}

void EnKendoJs_SetupAwaitingTalk(EnKendoJs* this) {
    this->actionFunc = EnKendoJs_AwaitTalk;
}

void EnKendoJs_AwaitTalk(EnKendoJs* this, PlayState* play) {
    s32 mainIndex;
    s32 dayIndex;

    if (Actor_TalkOfferAccepted(&this->actor, &play->state)) {
        if (CURRENT_DAY != 0) {
            dayIndex = CURRENT_DAY - 1;
        } else {
            dayIndex = 0;
        }

        if (ENKENDOJS_GET_FF(&this->actor) == ENKENDOJS_FF_1) {
            ENKENDOJS_QUEUE_MSG(this, play, ENKENDOJS_MSG_DONT_WANT_TO_DIE);
        } else if (GET_PLAYER_FORM != PLAYER_FORM_HUMAN) {
            switch (GET_PLAYER_FORM) {
                case PLAYER_FORM_DEKU:
                    mainIndex = 0;
                    break;

                case PLAYER_FORM_GORON:
                    mainIndex = 1;
                    break;

                case PLAYER_FORM_ZORA:
                    mainIndex = 2;
                    break;

                default:
                    mainIndex = 0;
                    break;
            }

            ENKENDOJS_QUEUE_MSG(this, play, sNonHumanMessages[mainIndex][dayIndex]);
        } else if ((Player_GetMask(play) != PLAYER_MASK_NONE) && (Player_GetMask(play) < PLAYER_MASK_GIANT)) {
            u16 maskMessage = ENKENDOJS_MSG_MASK(play);

            //! FAKE:
            if (1) {}

            ENKENDOJS_QUEUE_MSG(this, play, maskMessage);
        } else {
            if (!this->hasSpoken) {
                this->hasSpoken = true;
                mainIndex = 0;
            } else {
                mainIndex = 1;
            }
            ENKENDOJS_QUEUE_MSG(this, play, sHumanMessages[mainIndex][dayIndex]);
        }

        EnKendoJs_SetupMessageStateHandler(this);
    } else {
        Actor_OfferTalk(&this->actor, play, 100.0f);
    }
}

void EnKendoJs_HandleCourseChoice(EnKendoJs* this, PlayState* play) {
    if (Message_ShouldAdvance(play) && (this->curTextId == ENKENDOJS_MSG_WHICH_COURSE)) {
        switch (play->msgCtx.choiceIndex) {
            case 0:
                if (GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SWORD) == EQUIP_VALUE_SWORD_NONE) {
                    Audio_PlaySfx(NA_SE_SY_ERROR);
                    ENKENDOJS_QUEUE_MSG(this, play, ENKENDOJS_MSG_NOVICE_COURSE_NO_SWORD);
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, ENKENDOJS_ANIM_FLAILING);
                } else if (gSaveContext.save.saveInfo.playerData.rupees < play->msgCtx.unk1206C) {
                    Audio_PlaySfx(NA_SE_SY_ERROR);
                    ENKENDOJS_QUEUE_MSG(this, play, ENKENDOJS_MSG_NOT_ENOUGH_RUPEES);
                } else {
                    Audio_PlaySfx_MessageDecide();
                    Rupees_ChangeBy(-play->msgCtx.unk1206C);
                    ENKENDOJS_QUEUE_MSG(this, play, ENKENDOJS_MSG_NOVICE_COURSE_SELECTED);
                }
                break;

            case 1:
                if (GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SWORD) == EQUIP_VALUE_SWORD_NONE) {
                    Audio_PlaySfx(NA_SE_SY_ERROR);
                    ENKENDOJS_QUEUE_MSG(this, play, ENKENDOJS_MSG_NOVICE_COURSE_NO_SWORD);
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, ENKENDOJS_ANIM_FLAILING);
                } else if (gSaveContext.save.saveInfo.playerData.rupees < play->msgCtx.unk12070) {
                    Audio_PlaySfx(NA_SE_SY_ERROR);
                    ENKENDOJS_QUEUE_MSG(this, play, ENKENDOJS_MSG_NOT_ENOUGH_RUPEES);
                } else {
                    Audio_PlaySfx_MessageDecide();
                    Rupees_ChangeBy(-play->msgCtx.unk12070);
                    ENKENDOJS_QUEUE_MSG(this, play, ENKENDOJS_MSG_EXPERT_COURSE_SELECTED);
                }
                break;

            case 2:
                Audio_PlaySfx_MessageCancel();
                ENKENDOJS_QUEUE_MSG(this, play, ENKENDOJS_MSG_CANCEL);
                break;

            default:
                break;
        }
    }
}

void EnKendoJs_HandleEvents(EnKendoJs* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (!Message_ShouldAdvance(play)) {
        return;
    }

    switch (this->curTextId) {
        case ENKENDOJS_MSG_HUMAN_INTRO_DAY1:
        case ENKENDOJS_MSG_HUMAN_INTRO_SHORT_DAY1:
        case ENKENDOJS_MSG_HUMAN_INTRO_DAY2:
        case ENKENDOJS_MSG_HUMAN_INTRO_SHORT_DAY2:
        case ENKENDOJS_MSG_HUMAN_INTRO_DAY3:
        case ENKENDOJS_MSG_HUMAN_INTRO_SHORT_DAY3:
            ENKENDOJS_QUEUE_MSG(this, play, ENKENDOJS_MSG_WHICH_COURSE);
            break;

        case ENKENDOJS_MSG_NOVICE_COURSE_SELECTED:
            Message_CloseTextbox(play);
            player->stateFlags1 |= PLAYER_STATE1_20;
            EnKendoJs_SetupNoviceCourse(this);
            break;

        case ENKENDOJS_MSG_NOVICE_COURSE_START:
            Message_CloseTextbox(play);
            EnKendoJs_StartNoviceCourse(this);
            break;

        case ENKENDOJS_MSG_EXPERT_COURSE_SELECTED:
            ENKENDOJS_QUEUE_MSG(this, play, ENKENDOJS_MSG_EXPERT_COURSE_RULES);
            break;

        case ENKENDOJS_MSG_EXPERT_COURSE_RULES:
            Message_CloseTextbox(play);
            Interface_InitMinigame(play);
            player->stateFlags1 |= PLAYER_STATE1_20;
            EnKendoJs_SetupExpertCourse(this);
            break;

        case ENKENDOJS_MSG_EXPERT_COURSE_PERFECT:
            Message_CloseTextbox(play);
            gSaveContext.minigameStatus = MINIGAME_STATUS_END;
            EnKendoJs_SetupPrize(this);
            EnKendoJs_AwardPrize(this, play);
            break;

        default:
            break;
    }
}

void EnKendoJs_SetupMessageStateHandler(EnKendoJs* this) {
    this->actionFunc = EnKendoJs_HandleMessageState;
}

void EnKendoJs_HandleMessageState(EnKendoJs* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    switch (Message_GetState(&play->msgCtx)) {
        case TEXT_STATE_CHOICE:
            EnKendoJs_HandleCourseChoice(this, play);
            break;

        case TEXT_STATE_EVENT:
            EnKendoJs_HandleEvents(this, play);
            break;

        case TEXT_STATE_DONE:
            if (Message_ShouldAdvance(play)) {
                if (this->curTextId == ENKENDOJS_MSG_NOVICE_COURSE_NO_SWORD) {
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, ENKENDOJS_ANIM_STOP_FLAILING);
                }

                if ((this->curTextId == ENKENDOJS_MSG_EXPERT_COURSE_INSUFFICIENT) ||
                    (this->curTextId == ENKENDOJS_MSG_EXPERT_COURSE_ACCEPT_HEART_PIECE) ||
                    (this->curTextId == ENKENDOJS_MSG_EXPERT_COURSE_ACCEPT_RED_RUPEE)) {
                    gSaveContext.minigameStatus = MINIGAME_STATUS_END;
                }

                player->stateFlags1 &= ~PLAYER_STATE1_20;
                EnKendoJs_SetupAwaitingTalk(this);
            }
            break;

        case TEXT_STATE_NONE:
        case TEXT_STATE_NEXT:
        case TEXT_STATE_CLOSING:
        case TEXT_STATE_FADING:
        default:
            break;
    }
}

s32 EnKendoJs_GetNoviceCourseActionResult(EnKendoJs* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    switch (this->minigameRound) {
        case ENKENDOJS_NOVICE_SIDE_JUMP:
            if (Player_IsSideJumping(play)) {
                return ENKENDOJS_RESULT_CORRECT;
            }

            if ((player->meleeWeaponState != PLAYER_MELEE_WEAPON_STATE_0) ||
                (player->stateFlags3 & PLAYER_STATE3_8000000) || (player->stateFlags2 & PLAYER_STATE2_80000)) {
                return ENKENDOJS_RESULT_INCORRECT;
            }
            break;

        case ENKENDOJS_NOVICE_ROLL:
            if ((player->stateFlags3 & PLAYER_STATE3_8000000)) {
                return ENKENDOJS_RESULT_CORRECT;
            }

            if ((player->meleeWeaponState != PLAYER_MELEE_WEAPON_STATE_0) ||
                (player->stateFlags2 & PLAYER_STATE2_80000)) {
                return ENKENDOJS_RESULT_INCORRECT;
            }
            break;

        case ENKENDOJS_NOVICE_BACKFLIP:
            if (Player_IsBackJumping(play)) {
                return ENKENDOJS_RESULT_CORRECT;
            }

            if ((player->meleeWeaponState != PLAYER_MELEE_WEAPON_STATE_0) ||
                (player->stateFlags3 & PLAYER_STATE3_8000000) || (player->stateFlags2 & PLAYER_STATE2_80000)) {
                return ENKENDOJS_RESULT_INCORRECT;
            }
            this->isSlashingLog = 0;
            break;

        case ENKENDOJS_NOVICE_SWORD_ATTACK:
            if ((this->isSlashingLog == 1) && ((player->meleeWeaponAnimation == PLAYER_MWA_RIGHT_SLASH_1H) ||
                                               (player->meleeWeaponAnimation == PLAYER_MWA_RIGHT_COMBO_1H))) {
                this->isSlashingLog = 0;
                return ENKENDOJS_RESULT_CORRECT;
            }

            if ((this->isSlashingLog == 1) || (player->stateFlags3 & PLAYER_STATE3_8000000) ||
                (player->stateFlags2 & PLAYER_STATE2_80000)) {
                this->isSlashingLog = 0;
                return ENKENDOJS_RESULT_INCORRECT;
            }
            break;

        case ENKENDOJS_NOVICE_SWORD_TARGET:
            if ((this->isSlashingLog == 1) && ((player->meleeWeaponAnimation == PLAYER_MWA_FORWARD_SLASH_1H) ||
                                               (player->meleeWeaponAnimation == PLAYER_MWA_FORWARD_COMBO_1H))) {
                this->isSlashingLog = 0;
                return ENKENDOJS_RESULT_CORRECT;
            }

            if ((this->isSlashingLog == 1) || (player->stateFlags3 & PLAYER_STATE3_8000000) ||
                (player->stateFlags2 & PLAYER_STATE2_80000)) {
                this->isSlashingLog = 0;
                return ENKENDOJS_RESULT_INCORRECT;
            }
            break;

        case ENKENDOJS_NOVICE_SWORD_THRUST:
            if ((this->isSlashingLog == 1) && (player->meleeWeaponAnimation == PLAYER_MWA_STAB_1H)) {
                this->isSlashingLog = 0;
                return ENKENDOJS_RESULT_CORRECT;
            }

            if ((this->isSlashingLog == 1) || (player->stateFlags3 & PLAYER_STATE3_8000000) ||
                (player->stateFlags2 & PLAYER_STATE2_80000)) {
                this->isSlashingLog = 0;
                return ENKENDOJS_RESULT_INCORRECT;
            }
            break;

        case ENKENDOJS_NOVICE_JUMP_ATTACK:
            if ((this->isSlashingLog == 1) && ((player->meleeWeaponAnimation == PLAYER_MWA_JUMPSLASH_START) ||
                                               (player->meleeWeaponAnimation == PLAYER_MWA_JUMPSLASH_FINISH))) {
                this->isSlashingLog = 0;
                return ENKENDOJS_RESULT_CORRECT;
            }

            if ((this->isSlashingLog == 1) || (player->stateFlags3 & PLAYER_STATE3_8000000) ||
                (player->stateFlags2 & PLAYER_STATE2_80000)) {
                this->isSlashingLog = 0;
                return ENKENDOJS_RESULT_INCORRECT;
            }
            break;

        default:
            break;
    }
    return ENKENDOJS_RESULT_PENDING;
}

void EnKendoJs_NoviceCourseProgress(EnKendoJs* this, PlayState* play) {
    ENKENDOJS_QUEUE_MSG(this, play, sNoviceCourseProgressMessages[this->minigameRound]);
    this->minigameRound++;
}

void EnKendoJs_NoviceCourseTryAgain(EnKendoJs* this, PlayState* play) {
    ENKENDOJS_QUEUE_MSG(this, play, sNoviceCourseTryAgainMessages[this->minigameRound]);
}

s32 EnKendoJs_HasMoreAdviceToTryAgain(EnKendoJs* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    switch (this->curTextId) {
        case ENKENDOJS_MSG_NOVICE_COURSE_RETRY_ROUND2:
            if (Player_GetMeleeWeaponHeld(player) != PLAYER_MELEEWEAPON_NONE) {
                ENKENDOJS_QUEUE_MSG(this, play, ENKENDOJS_MSG_NOVICE_COURSE_SHEATH_WEAPON);
                return true;
            }
            break;

        case ENKENDOJS_MSG_NOVICE_COURSE_RETRY_ROUND4:
            if (this->isPlayerLockedOn) {
                ENKENDOJS_QUEUE_MSG(this, play, ENKENDOJS_MSG_NOVICE_COURSE_NO_Z_TARGET);
                return true;
            }
            break;

        default:
            break;
    }
    return false;
}

void EnKendoJs_SetupNoviceCourse(EnKendoJs* this) {
    this->actionFunc = EnKendoJs_MovePlayerToStartNoviceCourse;
}

void EnKendoJs_MovePlayerToStartNoviceCourse(EnKendoJs* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    Vec3f startPos = this->actor.world.pos;

    startPos.z += 200.0f;

    if (EnKendoJs_MovePlayerToPos(play, startPos)) {
        this->actor.flags |= ACTOR_FLAG_TALK_OFFER_AUTO_ACCEPTED;
        if (Actor_TalkOfferAccepted(&this->actor, &play->state)) {
            this->actor.flags &= ~ACTOR_FLAG_TALK_OFFER_AUTO_ACCEPTED;
            player->stateFlags1 &= ~PLAYER_STATE1_20;
            EnKendoJs_SpawnLog(this, play, 0);
            ENKENDOJS_QUEUE_MSG(this, play, ENKENDOJS_MSG_NOVICE_COURSE_START);
            EnKendoJs_SetupMessageStateHandler(this);
        } else {
            Actor_OfferTalk(&this->actor, play, 800.0f);
        }
    }
}

void EnKendoJs_StartNoviceCourse(EnKendoJs* this) {
    SET_WEEKEVENTREG(WEEKEVENTREG_STARTED_SWORDSMAN_MINIGAME);
    this->numLogs = 1;
    this->timer = 0;
    this->minigameRound = ENKENDOJS_NOVICE_SIDE_JUMP;
    this->courseState = ENKENDOJS_COURSE_ACTIVE;
    this->actionFunc = EnKendoJs_NoviceCourse;
}

void EnKendoJs_NoviceCourse(EnKendoJs* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if ((Message_GetState(&play->msgCtx) == TEXT_STATE_EVENT) && Message_ShouldAdvance(play)) {
        if (this->curTextId == ENKENDOJS_MSG_NOVICE_COURSE_WRONG) {
            EnKendoJs_NoviceCourseTryAgain(this, play);
        } else if (!EnKendoJs_HasMoreAdviceToTryAgain(this, play)) {
            if (this->skelAnime.animation == &object_js_Anim_Flailing) {
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, ENKENDOJS_ANIM_STOP_FLAILING);
            }
            this->courseState = ENKENDOJS_COURSE_RETRY;
            Message_CloseTextbox(play);
            player->stateFlags1 &= ~PLAYER_STATE1_20;
        }
    } else if (this->courseState == ENKENDOJS_COURSE_RETRY) {
        this->courseState = ENKENDOJS_COURSE_ACTIVE;
    }

    if (this->courseState == ENKENDOJS_COURSE_ACTIVE) {
        switch (EnKendoJs_GetNoviceCourseActionResult(this, play)) {
            case ENKENDOJS_RESULT_CORRECT:
                this->courseState = ENKENDOJS_COURSE_PAUSED;
                Actor_PlaySfx(&this->actor, NA_SE_SY_TRE_BOX_APPEAR);
                player->stateFlags1 |= PLAYER_STATE1_20;
                EnKendoJs_NoviceCourseProgress(this, play);
                break;

            case ENKENDOJS_RESULT_INCORRECT:
                Actor_PlaySfx(&this->actor, NA_SE_SY_ERROR);
                this->courseState = ENKENDOJS_COURSE_PAUSED;
                player->stateFlags1 |= PLAYER_STATE1_20;
                ENKENDOJS_QUEUE_MSG(this, play, ENKENDOJS_MSG_NOVICE_COURSE_WRONG);
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, ENKENDOJS_ANIM_FLAILING);
                break;

            default:
                if (this->numLogs == 0) {
                    this->timer++;
                    if (this->timer == 30) {
                        this->timer = 0;
                        EnKendoJs_SpawnLog(this, play, 0);
                    }
                }
                break;
        }

        if ((this->skelAnime.animation == &object_js_Anim_StopFlailing) &&
            Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, ENKENDOJS_ANIM_DEFAULT);
        }

        if (this->minigameRound == ENKENDOJS_NOVICE_FINISHED) {
            CLEAR_WEEKEVENTREG(WEEKEVENTREG_STARTED_SWORDSMAN_MINIGAME);
            EnKendoJs_SetupMessageStateHandler(this);
        }
    }
}

void EnKendoJs_SetupExpertCourse(EnKendoJs* this) {
    SET_WEEKEVENTREG(WEEKEVENTREG_STARTED_SWORDSMAN_MINIGAME);
    this->timer = 120;
    this->minigameRound = 0;
    this->courseState = ENKENDOJS_COURSE_ACTIVE;
    this->actionFunc = EnKendoJs_MovePlayerToStartExpertCourse;
}

void EnKendoJs_MovePlayerToStartExpertCourse(EnKendoJs* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    Vec3f startPos = this->actor.world.pos;

    startPos.z += 300.0f;

    if (EnKendoJs_MovePlayerToPos(play, startPos)) {
        this->numLogs = 0;
        player->stateFlags1 &= ~PLAYER_STATE1_20;
        this->actionFunc = EnKendoJs_ExpertCourse;
    }
}

void EnKendoJs_ExpertCourse(EnKendoJs* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (this->timer >= 140) {
        if (this->minigameRound == 5) {
            if (gSaveContext.minigameScore == 30) {
                ENKENDOJS_QUEUE_MSG(this, play, ENKENDOJS_MSG_EXPERT_COURSE_PERFECT);
            } else {
                ENKENDOJS_QUEUE_MSG(this, play, ENKENDOJS_MSG_EXPERT_COURSE_INSUFFICIENT);
            }
            player->stateFlags1 |= PLAYER_STATE1_20;
            CLEAR_WEEKEVENTREG(WEEKEVENTREG_STARTED_SWORDSMAN_MINIGAME);
            EnKendoJs_SetupMessageStateHandler(this);
            return;
        }

        Audio_PlaySfx(NA_SE_SY_FOUND);
        EnKendoJs_SpawnLog(this, play, ((u8)Rand_Next() % 3) + 1);
        EnKendoJs_SpawnLog(this, play, ((u8)Rand_Next() % 3) + 4);
        this->timer = 0;
        this->minigameRound++;
    } else if (this->timer == 120) {
        EnKendoJs_RetractLogs(this, play);
        this->timer++;
    } else {
        this->timer++;
    }

    if (this->isSlashingLog == 1) {
        if ((player->meleeWeaponAnimation == PLAYER_MWA_JUMPSLASH_START) ||
            (player->meleeWeaponAnimation == PLAYER_MWA_JUMPSLASH_FINISH)) {
            play->interfaceCtx.minigamePoints = 3;
            if (gSaveContext.minigameScore >= 27) {
                player->stateFlags1 |= PLAYER_STATE1_20;
            }
        } else if (player->meleeWeaponAnimation == PLAYER_MWA_STAB_1H) {
            play->interfaceCtx.minigamePoints = 2;
        } else {
            play->interfaceCtx.minigamePoints = 1;
        }
        Actor_PlaySfx(&this->actor, NA_SE_SY_TRE_BOX_APPEAR);
        this->isSlashingLog = 0;
    }
    EnKendoJs_SetExpertCourseCamera(this, play);
}

void EnKendoJs_SetupPrize(EnKendoJs* this) {
    this->actionFunc = EnKendoJs_AwardPrize;
}

void EnKendoJs_AwardPrize(EnKendoJs* this, PlayState* play) {
    if (Actor_HasParent(&this->actor, play)) {
        this->actor.parent = NULL;
        EnKendoJs_AfterPrizeAccepted(this);
    } else if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_RECEIVED_SWORDSMANS_SCHOOL_HEART_PIECE)) {
        Actor_OfferGetItem(&this->actor, play, GI_HEART_PIECE, 800.0f, 100.0f);
    } else {
        Actor_OfferGetItem(&this->actor, play, GI_RUPEE_RED, 800.0f, 100.0f);
    }
}

void EnKendoJs_AfterPrizeAccepted(EnKendoJs* this) {
    this->actionFunc = EnKendoJs_AwaitFinalMessage;
}

void EnKendoJs_AwaitFinalMessage(EnKendoJs* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (Actor_TalkOfferAccepted(&this->actor, &play->state)) {
        if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_RECEIVED_SWORDSMANS_SCHOOL_HEART_PIECE)) {
            SET_WEEKEVENTREG(WEEKEVENTREG_RECEIVED_SWORDSMANS_SCHOOL_HEART_PIECE);
            ENKENDOJS_QUEUE_MSG(this, play, ENKENDOJS_MSG_EXPERT_COURSE_ACCEPT_HEART_PIECE);
        } else {
            ENKENDOJS_QUEUE_MSG(this, play, ENKENDOJS_MSG_EXPERT_COURSE_ACCEPT_RED_RUPEE);
        }
        EnKendoJs_SetupMessageStateHandler(this);
        player->stateFlags1 &= ~PLAYER_STATE1_20;
    } else {
        Actor_OfferTalkExchangeEquiCylinder(&this->actor, play, 1000.0f, PLAYER_IA_MINUS1);
    }
}

void EnKendoJs_SetExpertCourseCamera(EnKendoJs* this, PlayState* play) {
    if (this->actor.csId != CS_ID_NONE) {
        Camera_ChangeActorCsCamIndex(play->cameraPtrs[CAM_ID_MAIN],
                                     CutsceneManager_GetCutsceneEntry(this->actor.csId)->csCamId);
    }
}

void EnKendoJs_KeepPlayerInTrainingArea(EnKendoJs* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    f32 zClamp = this->actor.world.pos.z + 70.0f;

    if ((ENKENDOJS_GET_FF(&this->actor) != ENKENDOJS_FF_1) && (player->actor.world.pos.z < zClamp)) {
        player->actor.world.pos.z = zClamp;
    }
}

s32 EnKendoJs_MovePlayerToPos(PlayState* play, Vec3f targetPos) {
    Player* player = GET_PLAYER(play);
    f32 distXZ;
    f32 controlStickMagnitude;
    s16 controlStickAngle;

    controlStickAngle = Math_Vec3f_Yaw(&player->actor.world.pos, &targetPos);
    distXZ = Math_Vec3f_DistXZ(&player->actor.world.pos, &targetPos);

    if (distXZ < 20.0f) {
        controlStickMagnitude = 10.0f;
    } else if (distXZ < 40.0f) {
        controlStickMagnitude = 40.0f;
    } else {
        controlStickMagnitude = 80.0f;
    }

    play->actorCtx.isOverrideInputOn = true;
    Actor_SetControlStickData(play, &play->actorCtx.overrideInput, controlStickMagnitude, controlStickAngle);

    if (distXZ < 20.0f) {
        return true;
    }
    return false;
}

void EnKendoJs_UpdateCollider(EnKendoJs* this, PlayState* play) {
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
}

void EnKendoJs_SpawnLog(EnKendoJs* this, PlayState* play, s32 position) {
    f32 x = this->pathPoints[position].x;
    f32 y = this->pathPoints[position].y;
    f32 z = this->pathPoints[position].z;

    Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EN_MARUTA, x, y, z, 0, 0, 0, 0);
    this->numLogs++;
}

void EnKendoJs_RetractLogs(EnKendoJs* this, PlayState* play) {
    Actor* actor = play->actorCtx.actorLists[ACTORCAT_PROP].first;

    while (actor != NULL) {
        if (actor->id == ACTOR_EN_MARUTA) {
            ((EnMaruta*)actor)->isRetracting = 1;
        }
        actor = actor->next;
    }

    this->numLogs = 0;
}

void EnKendoJs_Update(Actor* thisx, PlayState* play) {
    EnKendoJs* this = (EnKendoJs*)thisx;

    this->actionFunc(this, play);

    SkelAnime_Update(&this->skelAnime);
    Actor_TrackPlayer(play, &this->actor, &this->headRot, &this->torsoRot, this->actor.focus.pos);
    EnKendoJs_UpdateCollider(this, play);
    EnKendoJs_KeepPlayerInTrainingArea(this, play);
}

s32 EnKendoJs_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnKendoJs* this = (EnKendoJs*)thisx;

    if (limbIndex == OBJECT_JS_LIMB_0C) {
        rot->y -= this->headRot.y;
    }
    return false;
}

void EnKendoJs_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
}

void EnKendoJs_Draw(Actor* thisx, PlayState* play) {
    EnKendoJs* this = (EnKendoJs*)thisx;

    Gfx_SetupDL25_Opa(play->state.gfxCtx);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnKendoJs_OverrideLimbDraw, EnKendoJs_PostLimbDraw, &this->actor);
}
