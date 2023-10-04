/*
 * File: z_en_test3.c
 * Overlay: ovl_En_Test3
 * Description: Kafei
 */

#include "z_en_test3.h"
#include "objects/object_test3/object_test3.h"
#include "overlays/actors/ovl_En_Door/z_en_door.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "objects/object_mask_ki_tan/object_mask_ki_tan.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_CAN_PRESS_SWITCH)

#define THIS ((EnTest3*)thisx)

typedef struct {
    /* 0x0 */ s8 unk_0;
    /* 0x1 */ s8 unk_1_0 : 4;
    /* 0x1 */ s8 unk_1_4 : 4;
} struct_80A41828; // size = 0x2

typedef s32 (*EnTest3UnkFunc2)(EnTest3* this, PlayState* play, struct_80A41828* arg2, ScheduleOutput* scheduleOutput);
typedef s32 (*EnTest3UnkFunc)(EnTest3* this, PlayState* play);

typedef struct {
    /* 0x0 */ EnTest3UnkFunc2 unk_0;
    /* 0x4 */ EnTest3UnkFunc unk_4;
} struct_80A40678; // size = 0x8

typedef struct {
    /* 0x0 */ EnTest3ActionFunc unk_0; // might not actually be an action function
    /* 0x4 */ EnTest3ActionFunc actionFunc;
} struct_80A4168C; // size = 0x8

// Main functions
void EnTest3_Init(Actor* thisx, PlayState* play2);
void EnTest3_Destroy(Actor* thisx, PlayState* play2);
void EnTest3_Update(Actor* thisx, PlayState* play2);
void EnTest3_Draw(Actor* thisx, PlayState* play2);

// Functions used in D_80A4169C and D_80A416C0. Purpose unclear, but related to Schedule
s32 func_80A3E870(EnTest3* this, PlayState* play);
s32 func_80A3E884(EnTest3* this, PlayState* play);
s32 func_80A3E898(EnTest3* this, PlayState* play);
s32 func_80A3E960(EnTest3* this, PlayState* play);
s32 func_80A3E97C(EnTest3* this, PlayState* play);
s32 func_80A3E9DC(EnTest3* this, PlayState* play);
s32 func_80A3EA30(EnTest3* this, PlayState* play);
s32 func_80A3EAC4(EnTest3* this, PlayState* play);
s32 func_80A3EAF8(EnTest3* this, PlayState* play);
s32 func_80A3EB8C(EnTest3* this, PlayState* play);
s32 func_80A3EBFC(EnTest3* this, PlayState* play);
s32 func_80A3EC30(EnTest3* this, PlayState* play);
s32 func_80A3EC44(EnTest3* this, PlayState* play);

// Functions used in D_80A417E8. Purpose unclear, but related to Schedule
s32 func_80A3F080(EnTest3* this, PlayState* play, struct_80A41828* arg2, ScheduleOutput* scheduleOutput);
s32 func_80A3F09C(EnTest3* this, PlayState* play);
s32 func_80A3F62C(EnTest3* this, PlayState* play, struct_80A41828* arg2, ScheduleOutput* scheduleOutput);
s32 func_80A3F73C(EnTest3* this, PlayState* play);
s32 func_80A3F8D4(EnTest3* this, PlayState* play, struct_80A41828* arg2, ScheduleOutput* scheduleOutput);
s32 func_80A3F9A4(EnTest3* this, PlayState* play);
s32 func_80A3F9E4(EnTest3* this, PlayState* play, struct_80A41828* arg2, ScheduleOutput* scheduleOutput);
s32 func_80A3FA58(EnTest3* this, PlayState* play);
s32 func_80A3FBCC(EnTest3* this, PlayState* play, struct_80A41828* arg2, ScheduleOutput* scheduleOutput);
s32 func_80A3FBE8(EnTest3* this, PlayState* play);
s32 func_80A3FDE4(EnTest3* this, PlayState* play, struct_80A41828* arg2, ScheduleOutput* scheduleOutput);
s32 func_80A3FE20(EnTest3* this, PlayState* play);
s32 func_80A3FF10(EnTest3* this, PlayState* play, struct_80A41828* arg2, ScheduleOutput* scheduleOutput);
s32 func_80A3FFD0(EnTest3* this, PlayState* play2);
s32 func_80A40098(EnTest3* this, PlayState* play, struct_80A41828* arg2, ScheduleOutput* scheduleOutput);
s32 func_80A40230(EnTest3* this, PlayState* play);

// Action functions
void func_80A40678(EnTest3* this, PlayState* play);
void func_80A40824(EnTest3* this, PlayState* play);
void func_80A4084C(EnTest3* this, PlayState* play);
void func_80A40908(EnTest3* this, PlayState* play);
void func_80A40A6C(EnTest3* this, PlayState* play);

static u8 sScheduleScript[] = {
    /* 0x000 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(1, 0x046 - 0x004),
    /* 0x004 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_ALLEY, 0x020 - 0x008),
    /* 0x008 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(6, 50, 7, 20, 0x01A - 0x00E),
    /* 0x00E */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(7, 30, 0x019 - 0x012),
    /* 0x012 */ SCHEDULE_CMD_CHECK_FLAG_S(WEEKEVENTREG_51_04, 0x017 - 0x016),
    /* 0x016 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x017 */ SCHEDULE_CMD_RET_VAL_S(10),
    /* 0x019 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x01A */ SCHEDULE_CMD_RET_TIME(6, 50, 7, 20, 15),
    /* 0x020 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_CLOCKTOWER, 0x045 - 0x024),
    /* 0x024 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(6, 0, 6, 30, 0x03F - 0x02A),
    /* 0x02A */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(6, 30, 6, 35, 0x03D - 0x030),
    /* 0x030 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(6, 35, 6, 50, 0x037 - 0x036),
    /* 0x036 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x037 */ SCHEDULE_CMD_RET_TIME(6, 35, 6, 50, 14),
    /* 0x03D */ SCHEDULE_CMD_RET_VAL_S(1),
    /* 0x03F */ SCHEDULE_CMD_RET_TIME(6, 0, 6, 30, 13),
    /* 0x045 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x046 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(2, 0x09B - 0x04A),
    /* 0x04A */ SCHEDULE_CMD_CHECK_FLAG_S(WEEKEVENTREG_51_02, 0x058 - 0x04E),
    /* 0x04E */ SCHEDULE_CMD_BRANCH_S(0x0),
    /* 0x050 */ SCHEDULE_CMD_CHECK_FLAG_S(WEEKEVENTREG_51_04, 0x055 - 0x054),
    /* 0x054 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x055 */ SCHEDULE_CMD_RET_VAL_L(10),
    /* 0x058 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_ALLEY, 0x081 - 0x05C),
    /* 0x05C */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(13, 0, 0x050 - 0x060),
    /* 0x060 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(15, 5, 15, 25, 0x07B - 0x066),
    /* 0x066 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(15, 25, 15, 40, 0x079 - 0x06C),
    /* 0x06C */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(15, 40, 16, 0, 0x073 - 0x072),
    /* 0x072 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x073 */ SCHEDULE_CMD_RET_TIME(15, 40, 16, 0, 17),
    /* 0x079 */ SCHEDULE_CMD_RET_VAL_S(1),
    /* 0x07B */ SCHEDULE_CMD_RET_TIME(15, 5, 15, 25, 16),
    /* 0x081 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_AYASHIISHOP, 0x09A - 0x085),
    /* 0x085 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(15, 55, 16, 10, 0x094 - 0x08B),
    /* 0x08B */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(16, 10, 22, 10, 0x092 - 0x091),
    /* 0x091 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x092 */ SCHEDULE_CMD_RET_VAL_S(3),
    /* 0x094 */ SCHEDULE_CMD_RET_TIME(15, 55, 16, 10, 12),
    /* 0x09A */ SCHEDULE_CMD_RET_NONE(),
    /* 0x09B */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_L(3, 0x138 - 0x0A0),
    /* 0x0A0 */ SCHEDULE_CMD_CHECK_FLAG_L(WEEKEVENTREG_RECOVERED_STOLEN_BOMB_BAG, 0x12C - 0x0A5),
    /* 0x0A5 */ SCHEDULE_CMD_CHECK_FLAG_L(WEEKEVENTREG_SAKON_DEAD, 0x12C - 0x0AA),
    /* 0x0AA */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_SECOM, 0x0B0 - 0x0AE),
    /* 0x0AE */ SCHEDULE_CMD_RET_VAL_S(7),
    /* 0x0B0 */ SCHEDULE_CMD_CHECK_FLAG_S(WEEKEVENTREG_ESCAPED_SAKONS_HIDEOUT, 0x0DD - 0x0B4),
    /* 0x0B4 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_IKANA, 0x0DC - 0x0B8),
    /* 0x0B8 */ SCHEDULE_CMD_CHECK_FLAG_S(WEEKEVENTREG_51_08, 0x0BE - 0x0BC),
    /* 0x0BC */ SCHEDULE_CMD_RET_VAL_S(5),
    /* 0x0BE */ SCHEDULE_CMD_CHECK_FLAG_S(WEEKEVENTREG_61_08, 0x0DA - 0x0C2),
    /* 0x0C2 */ SCHEDULE_CMD_CHECK_FLAG_S(WEEKEVENTREG_51_10, 0x0CD - 0x0C6),
    /* 0x0C6 */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(19, 0, 0x0CB - 0x0CA),
    /* 0x0CA */ SCHEDULE_CMD_RET_NONE(),
    /* 0x0CB */ SCHEDULE_CMD_RET_VAL_S(5),
    /* 0x0CD */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(19, 0, 19, 10, 0x0D4 - 0x0D3),
    /* 0x0D3 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x0D4 */ SCHEDULE_CMD_RET_TIME(19, 0, 19, 10, 20),
    /* 0x0DA */ SCHEDULE_CMD_RET_VAL_S(5),
    /* 0x0DC */ SCHEDULE_CMD_RET_NONE(),
    /* 0x0DD */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_IKANA, 0x0E8 - 0x0E1),
    /* 0x0E1 */ SCHEDULE_CMD_CHECK_FLAG_S(WEEKEVENTREG_90_02, 0x0E7 - 0x0E5),
    /* 0x0E5 */ SCHEDULE_CMD_RET_VAL_S(9),
    /* 0x0E7 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x0E8 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_TOWN, 0x0F9 - 0x0EC),
    /* 0x0EC */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(4, 0, 4, 10, 0x0F3 - 0x0F2),
    /* 0x0F2 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x0F3 */ SCHEDULE_CMD_RET_TIME(4, 0, 4, 10, 11),
    /* 0x0F9 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_YADOYA, 0x12B - 0x0FD),
    /* 0x0FD */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(4, 10, 4, 30, 0x125 - 0x103),
    /* 0x103 */ SCHEDULE_CMD_CHECK_FLAG_S(WEEKEVENTREG_DELIVERED_PENDANT_OF_MEMORIES, 0x11C - 0x107),
    /* 0x107 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(4, 30, 4, 45, 0x116 - 0x10D),
    /* 0x10D */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(4, 45, 6, 0, 0x114 - 0x113),
    /* 0x113 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x114 */ SCHEDULE_CMD_RET_VAL_S(6),
    /* 0x116 */ SCHEDULE_CMD_RET_TIME(4, 30, 4, 45, 19),
    /* 0x11C */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(4, 30, 6, 0, 0x123 - 0x122),
    /* 0x122 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x123 */ SCHEDULE_CMD_RET_VAL_S(8),
    /* 0x125 */ SCHEDULE_CMD_RET_TIME(4, 10, 4, 30, 18),
    /* 0x12B */ SCHEDULE_CMD_RET_NONE(),
    /* 0x12C */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_AYASHIISHOP, 0x137 - 0x130),
    /* 0x130 */ SCHEDULE_CMD_CHECK_FLAG_S(WEEKEVENTREG_51_08, 0x135 - 0x134),
    /* 0x134 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x135 */ SCHEDULE_CMD_RET_VAL_S(4),
    /* 0x137 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x138 */ SCHEDULE_CMD_RET_NONE(),
};

ActorInit En_Test3_InitVars = {
    ACTOR_EN_TEST3,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_TEST3,
    sizeof(EnTest3),
    (ActorFunc)EnTest3_Init,
    (ActorFunc)EnTest3_Destroy,
    (ActorFunc)EnTest3_Update,
    (ActorFunc)NULL,
};

static struct_80A4168C D_80A4168C[] = {
    { func_80A40A6C, NULL },
    { NULL, NULL },
};

static EnTest3UnkFunc D_80A4169C[] = {
    func_80A3E898, func_80A3E898, func_80A3E884, func_80A3E898, func_80A3E898,
    func_80A3EA30, func_80A3E898, func_80A3E960, func_80A3E870,
};

static EnTest3UnkFunc D_80A416C0[] = {
    func_80A3EAC4, func_80A3EAF8, func_80A3EBFC, func_80A3EC44,
    func_80A3EC30, func_80A3E9DC, func_80A3EB8C, func_80A3E97C,
};

static PlayerAgeProperties sAgeProperties = {
    40.0f,
    60.0f,
    11.0f / 17.0f,
    71.0f,
    50.0f,
    49.0f,
    39.0f,
    27.0f,
    19.0f,
    22.0f,
    32.4f,
    32.0f,
    48.0f,
    11.0f / 17.0f * 70.0f,
    14.0f,
    12.0f,
    55.0f,
    { 0xFFE8, 0x0DED, 0x036C },
    { { 0xFFE8, 0x0D92, 0x035E }, { 0xFFE8, 0x1371, 0x03A9 }, { 0x0008, 0x1256, 0x017C }, { 0x0009, 0x17EA, 0x0167 } },
    { { 0xFFE8, 0x1371, 0x03A9 }, { 0xFFE8, 0x195F, 0x03A9 }, { 0x0009, 0x17EA, 0x0167 }, { 0x0009, 0x1E0D, 0x017C } },
    { { 0x0008, 0x1256, 0x017C }, { 0x0009, 0x17EA, 0x0167 }, { 0xF9C8, 0x1256, 0x017C }, { 0xF9C9, 0x17EA, 0x0167 } },
    0x0020,
    0x0000,
    22.0f,
    29.4343f,
    &gPlayerAnim_clink_demo_Tbox_open,
    &gPlayerAnim_clink_demo_goto_future,
    &gPlayerAnim_clink_demo_return_to_future,
    &gPlayerAnim_clink_normal_climb_startA,
    &gPlayerAnim_clink_normal_climb_startB,
    { &gPlayerAnim_clink_normal_climb_upL, &gPlayerAnim_clink_normal_climb_upR, &gPlayerAnim_link_normal_Fclimb_upL,
      &gPlayerAnim_link_normal_Fclimb_upR },
    { &gPlayerAnim_link_normal_Fclimb_sideL, &gPlayerAnim_link_normal_Fclimb_sideR },
    { &gPlayerAnim_clink_normal_climb_endAL, &gPlayerAnim_clink_normal_climb_endAR },
    { &gPlayerAnim_clink_normal_climb_endBR, &gPlayerAnim_clink_normal_climb_endBL },
};

static EffectBlureInit2 sBlureInit = {
    0, 8, 0, { 255, 255, 255, 255 }, { 255, 255, 255, 64 }, { 255, 255, 255, 0 }, { 255, 255, 255, 0 }, 4,
    0, 2, 0, { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
};

static EffectTireMarkInit sTireMarkInit = {
    0,
    63,
    { 0, 0, 15, 100 },
};

static struct_80A40678 D_80A417E8[] = {
    { func_80A3F080, func_80A3F09C }, { func_80A40098, func_80A40230 }, { func_80A3F62C, func_80A3F73C },
    { func_80A3F8D4, func_80A3F9A4 }, { func_80A3F9E4, func_80A3FA58 }, { func_80A3FBCC, func_80A3FBE8 },
    { func_80A3FDE4, func_80A3FE20 }, { func_80A3FF10, func_80A3FFD0 },
};

static struct_80A41828 D_80A41828[] = {
    { 0, 0, 0 },  { 3, -2, 0 }, { 2, -1, 0 }, { 2, -1, 1 }, { 2, -1, 2 }, { 2, 1, 3 }, { 2, -2, 4 }, { 5, 1, 0 },
    { 7, -1, 0 }, { 6, 2, 0 },  { 4, 4, 0 },  { 1, 1, 0 },  { 1, 1, 0 },  { 1, 2, 0 }, { 1, 1, 0 },  { 1, 1, 0 },
    { 1, 2, 0 },  { 1, 3, 0 },  { 1, 1, 0 },  { 1, 2, 0 },  { 1, 1, 0 },  { 0, 0, 0 },
};

static EnTest3_struct_D78 D_80A41854[] = {
    { 4, 0, 0x2B25 }, { 1, 0, 0x2969 }, { 3, 1, 0x296A },  { 1, 0, 0x296B }, { 5, 1, 0x0000 }, { 8, 0, 0x0000 },
    { 4, 0, 0x2976 }, { 6, 0, 0x2977 }, { 7, 10, 0x2978 }, { 4, 1, 0x0000 }, { 4, 0, 0x2968 }, { 4, 0, 0x297A },
    { 1, 0, 0x145D }, { 1, 0, 0x145E }, { 5, 1, 0x145F },  { 1, 0, 0x145F }, { 5, 0, 0x0000 }, { 4, 0, 0x1460 },
    { 4, 0, 0x145C }, { 4, 0, 0x2913 }, { 4, 0, 0x1465 },
};

s32 D_80A41D20;
s32 D_80A41D24;
Input sEnTest3_Input;
f32 D_80A41D40;
s16 D_80A41D44;
s32 D_80A41D48;
Vec3f D_80A41D50;
s32 D_80A41D5C;
s32 D_80A41D60;
s32 D_80A41D64;
s32 D_80A41D68;
Vec3f* D_80A41D6C;

s32 func_80A3E7E0(EnTest3* this, EnTest3ActionFunc actionFunc) {
    if (actionFunc == this->unk_D94) {
        return false;
    } else {
        this->unk_D94 = actionFunc;
        this->unk_D8A = 0;
        this->unk_D88 = 0;
        return true;
    }
}

s32 func_80A3E80C(EnTest3* this, PlayState* play, s32 arg2) {
    s32 pad;

    D_80A4168C[arg2].unk_0(this, play);
    if (D_80A4168C[arg2].actionFunc == NULL) {
        // D_80A4168C[arg2].actionFunc is always NULL
        return false;
    } else {
        func_80A3E7E0(this, D_80A4168C[arg2].actionFunc);
        return true;
    }
}

s32 func_80A3E870(EnTest3* this, PlayState* play) {
    return true;
}

s32 func_80A3E884(EnTest3* this, PlayState* play) {
    return false;
}

s32 func_80A3E898(EnTest3* this, PlayState* play) {
    u16 textId = this->unk_D78->textId;

    if ((this->unk_D78->unk_0 == 4) && CHECK_WEEKEVENTREG(WEEKEVENTREG_51_08)) {
        Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_KAFEI);
    }
    if (textId == 0xFFFF) {
        Message_CloseTextbox(play);
    } else if (textId) { // != 0
        Message_ContinueTextbox(play, textId);
    }
    if (textId == 0x296B) {
        PlayerAnimation_PlayOnceSetSpeed(play, &this->player.skelAnime, &gPlayerAnim_al_yareyare, 2.0f / 3.0f);
    }
    return false;
}

s32 func_80A3E960(EnTest3* this, PlayState* play) {
    this->unk_D8C = this->unk_D78->unk_1;
    return false;
}

s32 func_80A3E97C(EnTest3* this, PlayState* play) {
    if (DECR(this->unk_D8C) == 0) {
        Message_StartTextbox(play, this->unk_D78->textId, NULL);
        return true;
    }
    return false;
}

s32 func_80A3E9DC(EnTest3* this, PlayState* play) {
    if (CutsceneManager_IsNext(this->csId)) {
        CutsceneManager_StartWithPlayerCs(this->csId, &this->player.actor);
        return true;
    } else {
        CutsceneManager_Queue(this->csId);
        return false;
    }
}

s32 func_80A3EA30(EnTest3* this, PlayState* play) {
    if (this->unk_D78->textId == 0x145F) {
        Actor* hideoutDoor = SubS_FindActor(play, NULL, ACTORCAT_BG, ACTOR_BG_IKNV_OBJ);

        if (hideoutDoor != NULL) {
            this->player.lockOnActor = hideoutDoor;
        }
    }
    if (this->unk_D78->unk_1 != 0) {
        CutsceneManager_Stop(CS_ID_GLOBAL_TALK);
        CutsceneManager_Queue(this->csId);
        play->msgCtx.msgMode = MSGMODE_PAUSED;
    }
    return false;
}

s32 func_80A3EAC4(EnTest3* this, PlayState* play) {
    if (Message_GetState(&play->msgCtx) == TEXT_STATE_DONE) {
        return 1;
    }
    return 0;
}

s32 func_80A3EAF8(EnTest3* this, PlayState* play) {
    if ((Message_GetState(&play->msgCtx) == TEXT_STATE_5) && Message_ShouldAdvance(play)) {
        if (this->unk_D78->textId == 0x145F) {
            CutsceneManager_Stop(this->csId);
            this->csId = CS_ID_GLOBAL_TALK;
            CutsceneManager_Queue(this->csId);
            this->player.lockOnActor = &GET_PLAYER(play)->actor;
        }
        return 1;
    }
    return 0;
}

s32 func_80A3EB8C(EnTest3* this, PlayState* play) {
    if (func_80A3EAF8(this, play)) {
        Actor* hideoutObject = SubS_FindActor(play, NULL, ACTORCAT_ITEMACTION, ACTOR_OBJ_NOZOKI);

        if (hideoutObject != NULL) {
            this->player.lockOnActor = hideoutObject;
        }
        play->msgCtx.msgMode = MSGMODE_PAUSED;
        return 1;
    }
    return 0;
}

s32 func_80A3EBFC(EnTest3* this, PlayState* play) {
    if (Message_GetState(&play->msgCtx) == TEXT_STATE_CLOSING) {
        return 1;
    }
    return 0;
}

s32 func_80A3EC30(EnTest3* this, PlayState* play) {
    return 0;
}

s32 func_80A3EC44(EnTest3* this, PlayState* play) {
    if ((Message_GetState(&play->msgCtx) == TEXT_STATE_CHOICE) && Message_ShouldAdvance(play)) {
        if (play->msgCtx.choiceIndex != 0) {
            Audio_PlaySfx_MessageCancel();
        } else {
            Audio_PlaySfx_MessageDecide();
        }
        if (play->msgCtx.choiceIndex != 0) {
            return 1;
        } else {
            s32 ret = this->unk_D78->unk_1 + 1;

            return ret;
        }
    }
    return 0;
}

s32 func_80A3ECEC(EnTest3* this, PlayState* play) {
    return D_80A4169C[this->unk_D78->unk_0](this, play);
}

s32 func_80A3ED24(EnTest3* this, PlayState* play) {
    s32 temp = D_80A416C0[this->unk_D78->unk_0](this, play);

    if (temp != 0) {
        this->unk_D78 = &this->unk_D78[temp];
        return func_80A3ECEC(this, play);
    }
    return false;
}

void EnTest3_Init(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnTest3* this = THIS;
    Camera* subCam;

    if (D_80A41D24) {
        Actor_Kill(&this->player.actor);
        return;
    }
    D_80A41D24 = true;

    this->player.actor.room = -1;
    this->player.csId = CS_ID_NONE;
    this->player.transformation = PLAYER_FORM_HUMAN;
    this->player.ageProperties = &sAgeProperties;
    this->player.heldItemAction = PLAYER_IA_NONE;
    this->player.heldItemId = ITEM_OCARINA_OF_TIME;

    Player_SetModelGroup(&this->player, 3);
    play->playerInit(&this->player, play, &object_test3_Skel_00F7EC);

    Effect_Add(play, &this->player.meleeWeaponEffectIndex[0], EFFECT_BLURE2, 0, 0, &sBlureInit);
    Effect_Add(play, &this->player.meleeWeaponEffectIndex[1], EFFECT_BLURE2, 0, 0, &sBlureInit);
    Effect_Add(play, &this->player.meleeWeaponEffectIndex[2], EFFECT_TIRE_MARK, 0, 0, &sTireMarkInit);

    this->player.maskObjectSegment = ZeldaArena_Malloc(0x3800);
    play->func_18780(&this->player, play);
    this->unk_D90 = GET_PLAYER(play);
    this->player.giObjectSegment = this->unk_D90->giObjectSegment;
    this->player.tatlActor = this->unk_D90->tatlActor;
    if ((CURRENT_DAY != 3) || CHECK_WEEKEVENTREG(WEEKEVENTREG_RECOVERED_STOLEN_BOMB_BAG) ||
        !CHECK_WEEKEVENTREG(WEEKEVENTREG_51_08)) {
        this->player.currentMask = PLAYER_MASK_KEATON;
    }
    this->player.prevMask = this->player.currentMask;

    if (play->sceneId == SCENE_SECOM) {
        this->subCamId = Play_CreateSubCamera(play);
        subCam = Play_GetCamera(play, this->subCamId);
        Camera_InitFocalActorSettings(subCam, &this->player.actor);
        Camera_SetStateFlag(subCam, CAM_STATE_0 | CAM_STATE_6);
        Play_ChangeCameraStatus(play, this->subCamId, CAM_STATUS_WAIT);
    }

    this->player.actor.colChkInfo.cylRadius = 20;
    this->player.actor.colChkInfo.cylHeight = 60;
    this->player.actor.colChkInfo.health = 255;

    if (KAFEI_GET_PARAM_1E0(&this->player.actor) == 0) {
        func_80A3E7E0(this, func_80A40824);
    } else {
        func_80A3E7E0(this, func_80A40678);
    }
}

void EnTest3_Destroy(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnTest3* this = THIS;

    Effect_Destroy(play, this->player.meleeWeaponEffectIndex[0]);
    Effect_Destroy(play, this->player.meleeWeaponEffectIndex[1]);
    Effect_Destroy(play, this->player.meleeWeaponEffectIndex[2]);
    Collider_DestroyCylinder(play, &this->player.cylinder);
    Collider_DestroyCylinder(play, &this->player.shieldCylinder);
    Collider_DestroyQuad(play, &this->player.meleeWeaponQuads[0]);
    Collider_DestroyQuad(play, &this->player.meleeWeaponQuads[1]);
    Collider_DestroyQuad(play, &this->player.shieldQuad);
    ZeldaArena_Free(this->player.maskObjectSegment);
    Environment_StartTime();
}

s32 func_80A3F080(EnTest3* this, PlayState* play, struct_80A41828* arg2, ScheduleOutput* scheduleOutput) {
    return true;
}

s32 func_80A3F09C(EnTest3* this, PlayState* play) {
    this->player.actor.draw = NULL;
    return true;
}

void func_80A3F0B0(EnTest3* this, PlayState* play) {
    func_800BC154(play, &play->actorCtx, &this->unk_D90->actor, 2);
    func_800BC154(play, &play->actorCtx, &this->player.actor, 4);
    this->unk_D90->stateFlags1 &= ~PLAYER_STATE1_20;
}

void func_80A3F114(EnTest3* this, PlayState* play) {
    if (this->player.csMode != PLAYER_CSMODE_NONE) {
        play->startPlayerCutscene(play, &this->player, PLAYER_CSMODE_END);
    }
}

s32 func_80A3F15C(EnTest3* this, PlayState* play, struct_80A41828* arg2) {
    s32 limit;
    Path* path;
    Vec3s* curPathPoint;
    Vec3s* nextPathPoint;
    Vec3f curPathPos;
    Vec3f nextPathPos;

    limit = ABS_ALT(arg2->unk_1_0) - 1;

    if (limit >= 0) {
        path = SubS_GetAdditionalPath(play, KAFEI_GET_PATH_INDEX(&this->player.actor), limit);

        curPathPoint = Lib_SegmentedToVirtual(path->points);
        if (arg2->unk_1_0 > 0) {
            nextPathPoint = curPathPoint + 1;
        } else {
            curPathPoint += path->count - 1;
            nextPathPoint = curPathPoint - 1;
        }
        Math_Vec3s_ToVec3f(&curPathPos, curPathPoint);
        Math_Vec3s_ToVec3f(&nextPathPos, nextPathPoint);
        if (Math_Vec3f_DistXZ(&this->player.actor.world.pos, &curPathPos) > 10.0f) {
            Math_Vec3f_Copy(&this->player.actor.world.pos, &curPathPos);
            Math_Vec3f_Copy(&this->player.actor.home.pos, &curPathPos);
            Math_Vec3f_Copy(&this->player.actor.prevPos, &curPathPos);
            this->player.currentYaw = Math_Vec3f_Yaw(&this->player.actor.world.pos, &nextPathPos);
            if (arg2->unk_1_0 < 0) {
                this->player.currentYaw += 0x8000;
            }
            this->player.actor.shape.rot.y = this->player.currentYaw;
            return true;
        }
    }
    return false;
}

Actor* func_80A3F2BC(PlayState* play, EnTest3* this, s32 actorId, s32 category, f32 arg4, f32 arg5) {
    Actor* actor = play->actorCtx.actorLists[category].first;

    while (actor != NULL) {
        if (actorId == actor->id) {
            f32 dy = this->player.actor.world.pos.y - actor->world.pos.y;

            if ((fabsf(dy) < arg5) && (Actor_WorldDistXZToActor(&this->player.actor, actor) < arg4)) {
                return actor;
            }
        }
        actor = actor->next;
    }
    return NULL;
}

s32 func_80A3F384(EnTest3* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    EnDoor* door = (EnDoor*)func_80A3F2BC(play, this, ACTOR_EN_DOOR, ACTORCAT_DOOR, 55.0f, 20.0f);
    Vec3f offset;

    if ((door != NULL) && !door->knobDoor.playOpenAnim &&
        ((player->doorType == PLAYER_DOORTYPE_NONE) || (&door->knobDoor.dyna.actor != player->doorActor)) &&
        Actor_ActorAIsFacingActorB(&this->player.actor, &door->knobDoor.dyna.actor, 0x3000)) {
        Actor_OffsetOfPointInActorCoords(&door->knobDoor.dyna.actor, &offset, &this->player.actor.world.pos);
        this->player.doorType = PLAYER_DOORTYPE_HANDLE;
        this->player.doorDirection = (offset.z >= 0.0f) ? 1.0f : -1.0f;
        this->player.doorActor = &door->knobDoor.dyna.actor;
        this->player.csId = CS_ID_NONE;
        return true;
    }
    return false;
}

s32 func_80A3F4A4(PlayState* play) {
    return (Player_GetMask(play) == PLAYER_MASK_NONE) || (Player_GetMask(play) == PLAYER_MASK_BUNNY) ||
           (Player_GetMask(play) == PLAYER_MASK_POSTMAN) || (Player_GetMask(play) == PLAYER_MASK_KEATON) ||
           (Player_GetMask(play) == PLAYER_MASK_KAFEIS_MASK);
}

void func_80A3F534(EnTest3* this, PlayState* play) {
    if (!func_80A3F4A4(play)) {
        this->unk_D78 = &D_80A41854[10];
    } else if (CHECK_WEEKEVENTREG(WEEKEVENTREG_51_08)) {
        this->unk_D78 = &D_80A41854[7];
    } else {
        this->unk_D78 = &D_80A41854[1];
    }
    this->csId = this->player.actor.csId;
}

void func_80A3F5A4(EnTest3* this, PlayState* play) {
    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_51_08) || !func_80A3F4A4(play)) {
        this->unk_D78 = &D_80A41854[18];
        D_80A41D5C = false;
    } else if (D_80A41D5C) {
        this->unk_D78 = &D_80A41854[17];
    } else {
        this->unk_D78 = &D_80A41854[12];
    }
    this->csId = this->player.actor.csId;
}

s32 func_80A3F62C(EnTest3* this, PlayState* play, struct_80A41828* arg2, ScheduleOutput* scheduleOutput) {
    static EnTest3_struct_D78* D_80A418A8[] = {
        &D_80A41854[0], &D_80A41854[1], &D_80A41854[11], &D_80A41854[12], &D_80A41854[19],
    };

    if (((func_80A3F15C(this, play, arg2) || (this->unk_D88 >= 8)) && ((arg2->unk_1_4 == 1) || (arg2->unk_1_4 == 2))) ||
        (arg2->unk_1_4 == 4)) {
        if (arg2->unk_1_4 == 4) {
            this->player.actor.home.rot.y = 0x7FFF;
        } else {
            this->player.actor.home.rot.y = this->player.actor.shape.rot.y + 0x8000;
        }
        this->player.stateFlags2 |= PLAYER_STATE2_40000;
        play->startPlayerCutscene(play, &this->player, -1);
    }
    this->unk_D78 = D_80A418A8[arg2->unk_1_4];
    return true;
}

s32 func_80A3F73C(EnTest3* this, PlayState* play) {
    if (Actor_ProcessTalkRequest(&this->player.actor, &play->state)) {
        func_80A3E7E0(this, func_80A4084C);
        this->player.lockOnActor = &GET_PLAYER(play)->actor;
        this->player.stateFlags2 &= ~PLAYER_STATE2_40000;
        D_80A41D5C = true;
        if ((this->unk_D78->unk_0 == 4) && CHECK_WEEKEVENTREG(WEEKEVENTREG_51_08)) {
            Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_KAFEI);
        }
    } else {
        if (play->actorCtx.flags & ACTORCTX_FLAG_4) {
            play->actorCtx.flags &= ~ACTORCTX_FLAG_4;
            this->player.stateFlags2 &= ~PLAYER_STATE2_40000;
            this->unk_D90->stateFlags1 |= PLAYER_STATE1_20;
            func_800BC154(play, &play->actorCtx, &this->unk_D90->actor, 4);
            func_800BC154(play, &play->actorCtx, &this->player.actor, 2);
            CutsceneManager_SetReturnCamera(this->subCamId);
            play->startPlayerCutscene(play, &this->player, PLAYER_CSMODE_WAIT);
        }
        Actor_OfferTalkNearColChkInfoCylinder(&this->player.actor, play);
        if (this->unk_D88 == 3) {
            func_80A3F534(this, play);
        } else if (this->unk_D88 == 5) {
            func_80A3F5A4(this, play);
        }
        this->player.actor.textId = this->unk_D78->textId;
        this->player.actor.flags |= (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY);
    }
    return false;
}

s32 func_80A3F8D4(EnTest3* this, PlayState* play, struct_80A41828* arg2, ScheduleOutput* scheduleOutput) {
    Actor* postActor;

    func_80A3F15C(this, play, arg2);
    if (((postActor = func_80A3F2BC(play, this, ACTOR_EN_PST, ACTORCAT_PROP, 100.0f, 20.0f)) != NULL) ||
        ((postActor = func_80A3F2BC(play, this, ACTOR_EN_PM, ACTORCAT_NPC, 100.0f, 20.0f)) != NULL)) {
        this->player.actor.home.rot.y = Actor_WorldYawTowardActor(&this->player.actor, postActor);
    }
    play->startPlayerCutscene(play, &this->player, PLAYER_CSMODE_97);
    return true;
}

s32 func_80A3F9A4(EnTest3* this, PlayState* play) {
    Math_ScaledStepToS(&this->player.actor.shape.rot.y, this->player.actor.home.rot.y, 0x320);
    this->player.currentYaw = this->player.actor.shape.rot.y;
    return false;
}

s32 func_80A3F9E4(EnTest3* this, PlayState* play, struct_80A41828* arg2, ScheduleOutput* scheduleOutput) {
    scheduleOutput->time0 = SCHEDULE_TIME_NOW;
    scheduleOutput->time1 = (u16)(scheduleOutput->time0 + 70);
    func_80A40098(this, play, arg2, scheduleOutput);
    if (this->player.actor.xzDistToPlayer < 300.0f) {
        this->unk_D8A = -1;
    } else {
        this->unk_D8A = 120;
    }
    return true;
}

s32 func_80A3FA58(EnTest3* this, PlayState* play) {
    s32 pad;
    Player* player = GET_PLAYER(play);
    u32 cond;
    struct_80A41828 sp40;
    ScheduleOutput scheduleOutput;

    if (player->stateFlags1 & PLAYER_STATE1_40) {
        return false;
    }
    cond = func_80A40230(this, play);
    if (this->unk_D8A > 0) {
        this->unk_D8A--;
        cond = cond && (this->player.actor.xzDistToPlayer < 200.0f);
        if (cond || this->unk_D8A <= 0) {
            func_80A3F114(this, play);
            sp40.unk_1_0 = 5;
            scheduleOutput.time0 = SCHEDULE_TIME_NOW;
            scheduleOutput.time1 = (u16)(scheduleOutput.time0 + (cond ? 80 : 140));

            func_80A40098(this, play, &sp40, &scheduleOutput);
            this->unk_D8A = -40;
            return false;
        }
        if (this->unk_D8A == 90) {
            play->startPlayerCutscene(play, &this->player, PLAYER_CSMODE_21);
        }
    } else {
        this->unk_D8A++;
        if (this->unk_D8A == 0) {
            CLEAR_WEEKEVENTREG(WEEKEVENTREG_51_04);
            this->unk_D88 = 0;
        }
    }
    return false;
}

s32 func_80A3FBCC(EnTest3* this, PlayState* play, struct_80A41828* arg2, ScheduleOutput* scheduleOutput) {
    return true;
}

s32 func_80A3FBE8(EnTest3* this, PlayState* play) {
    if (D_80A41D20 == 0) {
        if (!Play_InCsMode(play)) {
            D_80A41D20 = 1;
            this->unk_D78 = &D_80A41854[20];
            this->csId = this->player.actor.csId;
            this->player.actor.textId = this->unk_D78->textId;
        }
    } else if (D_80A41D20 == 1) {
        if (this->csId >= 0) {
            if (func_80A3E9DC(this, play)) {
                this->csId = CS_ID_NONE;
                Environment_StopTime();
            }
        } else if ((play->actorCtx.flags & ACTORCTX_FLAG_6) || (play->actorCtx.flags & ACTORCTX_FLAG_5)) {
            this->csId = CutsceneManager_GetAdditionalCsId(this->player.actor.csId);
            SET_WEEKEVENTREG(WEEKEVENTREG_90_02);
            if (play->actorCtx.flags & ACTORCTX_FLAG_5) {
                this->csId = CutsceneManager_GetAdditionalCsId(this->csId);
            }
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM_MAIN, 1);
            D_80A41D20 = 2;
        } else {
            func_80A3F73C(this, play);
        }
    } else if ((D_80A41D20 == 2) && func_80A3E9DC(this, play)) {
        CutsceneManager_SetReturnCamera(CAM_ID_MAIN);
        Environment_StartTime();
        if (((void)0, gSaveContext.save.time) > CLOCK_TIME(6, 0)) {
            func_800FE658(TIME_TO_MINUTES_ALT_F(fabsf((s16) - ((void)0, gSaveContext.save.time))));
        }
        if (play->actorCtx.flags & ACTORCTX_FLAG_6) {
            SET_WEEKEVENTREG(WEEKEVENTREG_ESCAPED_SAKONS_HIDEOUT);
            CLEAR_WEEKEVENTREG(WEEKEVENTREG_90_02);
        }
        D_80A41D20 = 3;
    }
    return false;
}

s32 func_80A3FDE4(EnTest3* this, PlayState* play, struct_80A41828* arg2, ScheduleOutput* scheduleOutput) {
    this->csId = CutsceneManager_GetAdditionalCsId(this->player.actor.csId);
    return true;
}

s32 func_80A3FE20(EnTest3* this, PlayState* play) {
    struct_80A41828 sp2C;
    ScheduleOutput scheduleOutput;

    if (D_80A41D64 == 0) {
        if (func_80A3E9DC(this, play)) {
            sp2C.unk_1_0 = 2;
            scheduleOutput.time0 = SCHEDULE_TIME_NOW;
            scheduleOutput.time1 = (u16)(scheduleOutput.time0 + 1000);
            func_80A40098(this, play, &sp2C, &scheduleOutput);
            D_80A41D64 = 1;
            return false;
        }
    } else if (D_80A41D64 == 1) {
        func_80A40230(this, play);
    } else if (D_80A41D64 == 2) {
        CutsceneManager_Stop(this->csId);
        SET_WEEKEVENTREG(WEEKEVENTREG_90_02);
        D_80A41D64 = 3;
    }
    return false;
}

s32 func_80A3FF10(EnTest3* this, PlayState* play, struct_80A41828* arg2, ScheduleOutput* scheduleOutput) {
    static Vec3f D_80A418BC = { -420.0f, 210.0f, -162.0f };

    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_51_40)) {
        D_80A41D68 = 2;
        Math_Vec3f_Copy(&this->player.actor.world.pos, &D_80A418BC);
        Math_Vec3f_Copy(&this->player.actor.home.pos, &D_80A418BC);

        this->player.actor.home.rot.y = -0x2AAB;
        this->player.actor.shape.rot.y = -0x2AAB;
        this->player.currentYaw = -0x2AAB;
        if (1) {} // macro?
        return true;
    } else {
        func_80A3F15C(this, play, arg2);
        this->csId = this->player.actor.csId;
        if (play->roomCtx.curRoom.num == 2) {
            this->csId = CutsceneManager_GetAdditionalCsId(this->csId);
        }
        return true;
    }
}

s32 func_80A3FFD0(EnTest3* this, PlayState* play2) {
    PlayState* play = play2;

    if (D_80A41D68 == 0) {
        if (!Play_InCsMode(play) && (play->roomCtx.curRoom.num == 2)) {
            D_80A41D68 = 1;
        }
    } else if (D_80A41D68 == 1) {
        if (func_80A3E9DC(this, play)) {
            D_80A41D68 = 2;
        }
    } else {
        SET_WEEKEVENTREG(WEEKEVENTREG_51_40);
        play->startPlayerCutscene(play, &this->player, PLAYER_CSMODE_110);
    }
    return false;
}

s32 func_80A40098(EnTest3* this, PlayState* play, struct_80A41828* arg2, ScheduleOutput* scheduleOutput) {
    u16 now = SCHEDULE_TIME_NOW;
    u16 startTime;
    u16 numWaypoints;

    func_80A3F15C(this, play, arg2);
    this->unk_D7C = SubS_GetAdditionalPath(play, KAFEI_GET_PATH_INDEX(&this->player.actor), ABS_ALT(arg2->unk_1_0) - 1);
    if ((this->unk_D88 < 7) && (this->unk_D88 != 0) && (this->unk_D80 >= 0)) {
        startTime = now;
    } else {
        startTime = scheduleOutput->time0;
    }
    if (scheduleOutput->time1 < startTime) {
        this->unk_DA8 = (startTime - scheduleOutput->time1) + (DAY_LENGTH - 1);
    } else {
        this->unk_DA8 = scheduleOutput->time1 - startTime;
    }
    this->unk_DB4 = now - startTime;
    numWaypoints = startTime = this->unk_D7C->count - (SUBS_TIME_PATHING_ORDER - 1);
    this->unk_DAC = this->unk_DA8 / numWaypoints;
    this->unk_DB0 = (this->unk_DB4 / this->unk_DAC) + (SUBS_TIME_PATHING_ORDER - 1);
    this->unk_D89 &= ~1;
    this->unk_D84 = 1.0f;
    return true;
}

s32 func_80A40230(EnTest3* this, PlayState* play) {
    f32 knots[265];
    Vec3f worldPos;
    Vec3f sp7C;
    Vec3f sp70;
    s32 sp6C = 0;
    s32 sp68 = 0;
    s32 pad1;
    f32 dx;
    f32 dy;
    s32 ret = false;

    SubS_TimePathing_FillKnots(knots, 3, this->unk_D7C->count + 3);
    if (!(this->unk_D89 & 1)) {
        sp70 = gZeroVec3f;
        SubS_TimePathing_Update(this->unk_D7C, &this->unk_DA4, &this->unk_DB4, this->unk_DAC, this->unk_DA8,
                                &this->unk_DB0, knots, &sp70, this->unk_D80);
        SubS_TimePathing_ComputeInitialY(play, this->unk_D7C, this->unk_DB0, &sp70);
        Math_Vec3f_Copy(&this->player.actor.home.pos, &sp70);
        Math_Vec3f_Copy(&this->player.actor.prevPos, &sp70);
        this->player.actor.world.pos.y = sp70.y;
        this->unk_D89 |= 1;
    } else {
        sp70 = this->unk_D98;
    }
    this->player.actor.world.pos.x = sp70.x;
    this->player.actor.world.pos.z = sp70.z;
    if (play->transitionMode != TRANS_MODE_OFF) {
        sp6C = this->unk_DB4;
        sp68 = this->unk_DB0;
        sp70 = this->player.actor.world.pos;
    }
    this->unk_D98 = gZeroVec3f;
    if (SubS_TimePathing_Update(this->unk_D7C, &this->unk_DA4, &this->unk_DB4, this->unk_DAC, this->unk_DA8,
                                &this->unk_DB0, knots, &this->unk_D98, this->unk_D80)) {
        if (this->unk_D88 == 0x14) {
            CLEAR_WEEKEVENTREG(WEEKEVENTREG_58_80);
            this->player.actor.draw = NULL;
        } else if (this->unk_D88 == 9) {
            D_80A41D64 = 2;
        }
        ret = true;
    } else {
        worldPos = this->player.actor.world.pos;
        sp7C = this->unk_D98;
        this->player.actor.world.rot.y = Math_Vec3f_Yaw(&worldPos, &sp7C);
    }
    if (play->transitionMode != TRANS_MODE_OFF) {
        this->unk_DB4 = sp6C;
        this->unk_DB0 = sp68;
        this->unk_D98 = sp70;
    }
    dx = this->player.actor.world.pos.x - this->player.actor.prevPos.x;
    dy = this->player.actor.world.pos.z - this->player.actor.prevPos.z;
    if (!Math_StepToF(&this->unk_D84, 1.0f, 0.1f)) {
        this->player.actor.world.pos.x = this->player.actor.prevPos.x + (dx * this->unk_D84);
        this->player.actor.world.pos.z = this->player.actor.prevPos.z + (dy * this->unk_D84);
    }
    Math_Vec3f_Copy(&D_80A41D50, &this->player.actor.world.pos);
    dx = this->player.actor.world.pos.x - this->player.actor.prevPos.x;
    dy = this->player.actor.world.pos.z - this->player.actor.prevPos.z;
    this->player.linearVelocity = sqrtf(SQ(dx) + SQ(dy));
    this->player.linearVelocity *= 1.0f + (1.05f * fabsf(Math_SinS(this->player.floorPitch)));
    D_80A41D40 = (this->player.linearVelocity * 10.0f) + 20.0f;
    D_80A41D40 = CLAMP_MAX(D_80A41D40, 60.0f);
    D_80A41D44 = this->player.actor.world.rot.y;
    this->player.actor.world.pos.x = this->player.actor.prevPos.x;
    this->player.actor.world.pos.z = this->player.actor.prevPos.z;
    if (!func_80A3F384(this, play)) {
        D_80A41D48 = true;
    }
    return ret;
}

void func_80A40678(EnTest3* this, PlayState* play) {
    struct_80A41828* sp3C;
    ScheduleOutput scheduleOutput;

    this->unk_D80 = ((this->unk_D88 == 20) || (this->unk_D88 == 10) || (this->unk_D88 == 9)) ? 3
                    : Play_InCsMode(play)                                                    ? 0
                                          : R_TIME_SPEED + ((void)0, gSaveContext.save.timeSpeedOffset);

    if (Schedule_RunScript(play, sScheduleScript, &scheduleOutput)) {
        if (this->unk_D88 != scheduleOutput.result) {
            sp3C = &D_80A41828[scheduleOutput.result];
            func_80A3F114(this, play);
            if (sp3C->unk_0 != 4) {
                CLEAR_WEEKEVENTREG(WEEKEVENTREG_51_04);
            }
            if (!D_80A417E8[sp3C->unk_0].unk_0(this, play, sp3C, &scheduleOutput)) {
                return;
            }
            if (scheduleOutput.result == 6) {
                this->player.actor.home.rot.y = 0x7FFF;
                this->player.stateFlags2 |= PLAYER_STATE2_40000;
                play->startPlayerCutscene(play, &this->player, -1);
            }
        }
    } else {
        scheduleOutput.result = 0;
    }
    this->unk_D88 = scheduleOutput.result;
    sp3C = &D_80A41828[this->unk_D88];
    D_80A417E8[sp3C->unk_0].unk_4(this, play);
}

void func_80A40824(EnTest3* this, PlayState* play) {
    this->unk_D78 = &D_80A41854[0];
    func_80A3F73C(this, play);
}

void func_80A4084C(EnTest3* this, PlayState* play) {
    if (Actor_TextboxIsClosing(&this->player.actor, play)) {
        if ((this->unk_D78->unk_1 == 0) || !func_80A3E80C(this, play, this->unk_D78->unk_1 - 1)) {
            if (KAFEI_GET_PARAM_1E0(&this->player.actor) == 0) {
                func_80A3E7E0(this, func_80A40824);
            } else {
                func_80A3E7E0(this, func_80A40678);
            }
            this->player.lockOnActor = NULL;
        }
    } else if (func_80A3ED24(this, play)) {
        func_80A3E7E0(this, func_80A40908);
    }
}

void func_80A40908(EnTest3* this, PlayState* play) {
    if (Actor_ProcessTalkRequest(&this->player.actor, &play->state)) {
        func_80A3E7E0(this, func_80A4084C);
        this->player.lockOnActor = &GET_PLAYER(play)->actor;
        SET_WEEKEVENTREG(WEEKEVENTREG_51_08);
        Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_RECEIVED_PENDANT_OF_MEMORIES);
        Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_KAFEI);
    } else {
        Actor_OfferTalkExchange(&this->player.actor, play, 9999.9f, 9999.9f, PLAYER_IA_MINUS1);
        this->unk_D78 = &D_80A41854[6];
        this->player.actor.textId = this->unk_D78->textId;
        this->player.actor.flags |= (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY);
    }
}

void func_80A409D4(EnTest3* this, PlayState* play) {
    if ((play->actorCtx.flags & ACTORCTX_FLAG_5) || (play->actorCtx.flags & ACTORCTX_FLAG_4)) {
        play->actorCtx.flags &= ~ACTORCTX_FLAG_4;
        func_80A3F0B0(this, play);
        CutsceneManager_SetReturnCamera(CAM_ID_MAIN);
    } else {
        sEnTest3_Input = *CONTROLLER1(&play->state);
    }
}

void func_80A40A6C(EnTest3* this, PlayState* play) {
    SET_WEEKEVENTREG(WEEKEVENTREG_64_20);
}

void EnTest3_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnTest3* this = THIS;

    sEnTest3_Input.rel.button = sEnTest3_Input.cur.button;
    sEnTest3_Input.cur.button = 0;
    sEnTest3_Input.rel.stick_x = 0;
    sEnTest3_Input.rel.stick_y = 0;

    play->actorCtx.flags &= ~ACTORCTX_FLAG_7;
    this->player.actor.draw = EnTest3_Draw;
    D_80A41D48 = false;
    this->player.actor.flags &= ~(ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY);
    if (Cutscene_IsCueInChannel(play, CS_CMD_ACTOR_CUE_506) &&
        !((this->player.actor.category == ACTORCAT_PLAYER) &&
          ((play->actorCtx.flags & ACTORCTX_FLAG_5) || (play->actorCtx.flags & ACTORCTX_FLAG_4)))) {
        if (this->player.csMode != PLAYER_CSMODE_5) {
            play->startPlayerCutscene(play, &this->player, PLAYER_CSMODE_5);
        }
        play->actorCtx.flags &= ~ACTORCTX_FLAG_4;
    } else if (this->player.actor.category == ACTORCAT_PLAYER) {
        func_80A409D4(this, play);
    } else if (play->startPlayerCutscene(play, &this->player, PLAYER_CSMODE_NONE)) {
        if (this->unk_D88 >= 7) {
            Vec3f worldPos;

            Math_Vec3f_Copy(&worldPos, &this->player.actor.world.pos);
            this->unk_D80 = 4;
            func_80A40230(this, play);
            Math_Vec3f_Copy(&this->player.actor.world.pos, &worldPos);
            D_80A41D48 = false;
            this->unk_D84 = 0.0f;
        }
    } else {
        D_80A41D40 = 0.0f;
        D_80A41D44 = this->player.actor.shape.rot.y;
        this->unk_D94(this, play);
        sEnTest3_Input.press.button =
            (sEnTest3_Input.rel.button ^ sEnTest3_Input.cur.button) & sEnTest3_Input.cur.button;
        func_800B6F20(play, &sEnTest3_Input, D_80A41D40, D_80A41D44);
    }
    play->playerUpdate(&this->player, play, &sEnTest3_Input);
    if (D_80A41D48) {
        this->player.actor.world.pos.x = D_80A41D50.x;
        this->player.actor.world.pos.z = D_80A41D50.z;
        this->player.linearVelocity = 0.0f;
    }
}

s32 D_80A418C8 = false;

s32 EnTest3_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnTest3* this = THIS;

    if (limbIndex == OBJECT_TEST3_LIMB_01) {
        D_80A41D6C = &this->player.bodyPartsPos[-1];
        if (!(this->player.skelAnime.moveFlags & ANIM_FLAG_4) || (this->player.skelAnime.moveFlags & ANIM_FLAG_1)) {
            pos->x *= this->player.ageProperties->unk_08;
            pos->z *= this->player.ageProperties->unk_08;
        }
        if (!(this->player.skelAnime.moveFlags & ANIM_FLAG_4) ||
            (this->player.skelAnime.moveFlags & ANIM_FLAG_UPDATE_Y)) {
            pos->y *= this->player.ageProperties->unk_08;
        }
        pos->y -= this->player.unk_AB8;
        if (this->player.unk_AAA != 0) {

            Matrix_Translate(pos->x, ((Math_CosS(this->player.unk_AAA) - 1.0f) * 200.0f) + pos->y, pos->z,
                             MTXMODE_APPLY);
            Matrix_RotateXS(this->player.unk_AAA, MTXMODE_APPLY);
            Matrix_RotateZYX(rot->x, rot->y, rot->z, MTXMODE_APPLY);
            func_80125318(pos, rot);
        }
    } else {
        if (*dList != NULL) {
            D_80A41D6C++;
        }
        if (D_80A418C8) {
            *dList = NULL;
        }
        if (limbIndex == OBJECT_TEST3_LIMB_0B) {
            rot->x += this->player.headLimbRot.z;
            rot->y -= this->player.headLimbRot.y;
            rot->z += this->player.headLimbRot.x;
        } else if (limbIndex == OBJECT_TEST3_LIMB_0A) {
            s32 requiredScopeTemp;

            if (this->player.unk_AA8 != 0) {
                Matrix_RotateZS(0x44C, MTXMODE_APPLY);
                Matrix_RotateYS(this->player.unk_AA8, MTXMODE_APPLY);
            }
            if (this->player.upperLimbRot.y != 0) {
                Matrix_RotateYS(this->player.upperLimbRot.y, MTXMODE_APPLY);
            }
            Matrix_RotateXS(this->player.upperLimbRot.x, MTXMODE_APPLY);
            if (this->player.upperLimbRot.z != 0) {
                Matrix_RotateZS(this->player.upperLimbRot.z, MTXMODE_APPLY);
            }
        } else {
            func_80125500(play, &this->player, limbIndex, pos, rot);
        }
    }
    return false;
}

void EnTest3_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList1, Gfx** dList2, Vec3s* rot, Actor* thisx) {
    s32 pad;
    EnTest3* this = THIS;

    if (*dList2 != NULL) {
        Matrix_MultZero(D_80A41D6C);
    }
    if (limbIndex == OBJECT_TEST3_LIMB_10) {
        MtxF curMtxF;
        Actor* leftHandActor;

        Math_Vec3f_Copy(&this->player.leftHandWorld.pos, D_80A41D6C);
        if (*dList1 != NULL) {
            func_80128640(play, &this->player, *dList1);
            if (this->player.stateFlags3 & PLAYER_STATE3_20000000) {
                OPEN_DISPS(play->state.gfxCtx);

                gSPDisplayList(POLY_OPA_DISP++, object_test3_DL_00EDD0);

                CLOSE_DISPS(play->state.gfxCtx);
            }
        }
        leftHandActor = this->player.heldActor;
        if ((leftHandActor != NULL) && (this->player.stateFlags1 & PLAYER_STATE1_800)) {
            Vec3s curRot;

            Matrix_Get(&curMtxF);
            Matrix_MtxFToYXZRot(&curMtxF, &curRot, false);
            leftHandActor->world.rot.y = this->player.actor.shape.rot.y + this->player.leftHandWorld.rot.y;
            leftHandActor->shape.rot.y = leftHandActor->world.rot.y;
        } else {
            Matrix_Get(&this->player.leftHandMf);
            Matrix_MtxFToYXZRot(&this->player.leftHandMf, &this->player.leftHandWorld.rot, false);
            func_80126B8C(play, &this->player);
        }

    } else if (limbIndex == OBJECT_TEST3_LIMB_13) {
        Actor* leftHandActor = this->player.heldActor;

        if (leftHandActor != NULL) {
            leftHandActor->world.pos.x =
                (this->player.bodyPartsPos[PLAYER_BODYPART_RIGHT_HAND].x + this->player.leftHandWorld.pos.x) / 2.0f;
            leftHandActor->world.pos.y =
                (this->player.bodyPartsPos[PLAYER_BODYPART_RIGHT_HAND].y + this->player.leftHandWorld.pos.y) / 2.0f;
            leftHandActor->world.pos.z =
                (this->player.bodyPartsPos[PLAYER_BODYPART_RIGHT_HAND].z + this->player.leftHandWorld.pos.z) / 2.0f;
        }
    } else if (limbIndex == OBJECT_TEST3_LIMB_0B) {
        Actor* actor730 = this->player.lockOnActor;

        if ((*dList1 != NULL) && this->player.currentMask && !(this->player.stateFlags2 & PLAYER_STATE2_1000000)) {
            // this->player.currentMask != PLAYER_MASK_NONE
            if ((this->player.skelAnime.animation != &gPlayerAnim_cl_maskoff) &&
                ((this->player.skelAnime.animation != &gPlayerAnim_cl_setmask) ||
                 (this->player.skelAnime.curFrame >= 12.0f))) {
                if (func_80127438(play, &this->player, this->player.currentMask)) {
                    OPEN_DISPS(play->state.gfxCtx);

                    gSPDisplayList(POLY_OPA_DISP++, object_mask_ki_tan_DL_0004A0);

                    CLOSE_DISPS(play->state.gfxCtx);
                }
            }
        }
        if ((actor730 != NULL) && (actor730->id == ACTOR_BG_IKNV_OBJ)) {
            Math_Vec3f_Copy(&this->player.actor.focus.pos, &actor730->focus.pos);
        } else {
            static Vec3f D_80A418CC = { 1100.0f, -700.0f, 0.0f };

            Matrix_MultVec3f(&D_80A418CC, &this->player.actor.focus.pos);
        }
    } else if (limbIndex == OBJECT_TEST3_LIMB_15) {
        if (D_80A41D60 || CHECK_WEEKEVENTREG(WEEKEVENTREG_RECEIVED_PENDANT_OF_MEMORIES) ||
            (INV_CONTENT(ITEM_PENDANT_OF_MEMORIES) == ITEM_PENDANT_OF_MEMORIES) ||
            (this->player.getItemDrawIdPlusOne - 1 == GID_PENDANT_OF_MEMORIES)) {
            D_80A41D60 = true;
        } else {
            OPEN_DISPS(play->state.gfxCtx);

            gSPDisplayList(POLY_OPA_DISP++, object_test3_DL_00CB60);

            CLOSE_DISPS(play->state.gfxCtx);
        }
    } else {
        Player_SetFeetPos(play, &this->player, limbIndex);
    }
}

static TexturePtr sEyeTextures[] = {
    object_test3_Tex_000DC0, object_test3_Tex_003680, object_test3_Tex_003E80, object_test3_Tex_004680,
    object_test3_Tex_004E80, object_test3_Tex_005680, object_test3_Tex_005E80, object_test3_Tex_006680,
};

static TexturePtr sMouthTextures[] = {
    object_test3_Tex_0009C0,
    object_test3_Tex_006E80,
    object_test3_Tex_007280,
    object_test3_Tex_007680,
};

typedef struct {
    /* 0x0 */ u8 eyeIndex;
    /* 0x1 */ u8 mouthIndex;
} KafeiFace; // size = 0x2

static KafeiFace sFaceExpressions[] = {
    { 0, 0 }, { 1, 0 }, { 2, 0 }, { 0, 0 }, { 1, 0 }, { 2, 0 }, { 4, 0 }, { 5, 1 }, { 7, 2 }, { 0, 2 },
    { 3, 0 }, { 4, 0 }, { 2, 2 }, { 1, 1 }, { 0, 2 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
};

void EnTest3_Draw(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnTest3* this = THIS;
    s32 eyeTexIndex = (this->player.skelAnime.jointTable[OBJECT_TEST3_LIMB_MAX].x & 0xF) - 1;
    s32 mouthTexIndex = ((this->player.skelAnime.jointTable[OBJECT_TEST3_LIMB_MAX].x >> 4) & 0xF) - 1;
    Gfx* gfx;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C268(&play->state);
    if (this->player.invincibilityTimer > 0) {
        s32 temp2; // Must exist for stack order. Could hold the result of CLAMP instead.

        this->player.unk_B5F += CLAMP(50 - this->player.invincibilityTimer, 8, 40);
        temp2 = Math_CosS(this->player.unk_B5F * 0x100) * 2000.0f;
        POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 0, 0, 4000 - temp2);
    }
    func_800B8050(&this->player.actor, play, 0);
    D_80A418C8 = false;
    if (this->player.stateFlags1 & PLAYER_STATE1_100000) {
        Vec3f sp4C;

        SkinMatrix_Vec3fMtxFMultXYZ(&play->viewProjectionMtxF, &this->player.actor.focus.pos, &sp4C);
        if (sp4C.z < -4.0f) {
            D_80A418C8 = true;
        }
    }

    gfx = POLY_OPA_DISP;

    if (eyeTexIndex < 0) {
        eyeTexIndex = sFaceExpressions[this->player.actor.shape.face].eyeIndex;
    }
    gSPSegment(&gfx[0], 0x08, Lib_SegmentedToVirtual(sEyeTextures[eyeTexIndex]));
    if (mouthTexIndex < 0) {
        mouthTexIndex = sFaceExpressions[this->player.actor.shape.face].mouthIndex;
    }
    gSPSegment(&gfx[1], 0x09, Lib_SegmentedToVirtual(sMouthTextures[mouthTexIndex]));

    POLY_OPA_DISP = &gfx[2];

    SkelAnime_DrawFlexLod(play, this->player.skelAnime.skeleton, this->player.skelAnime.jointTable,
                          this->player.skelAnime.dListCount, EnTest3_OverrideLimbDraw, EnTest3_PostLimbDraw,
                          &this->player.actor, 0);
    if (this->player.invincibilityTimer > 0) {
        POLY_OPA_DISP = Play_SetFog(play, POLY_OPA_DISP);
    }
    if ((this->player.getItemDrawIdPlusOne - 1) != GID_NONE) {
        Player_DrawGetItem(play, &this->player);
    }
    CLOSE_DISPS(play->state.gfxCtx);
}
