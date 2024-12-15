/*
 * File: z_en_pm.c
 * Overlay: ovl_En_Pm
 * Description: Postman
 */

#include "z_en_pm.h"
#include "attributes.h"
#include "overlays/actors/ovl_En_Door/z_en_door.h"

#define FLAGS                                                                                  \
    (ACTOR_FLAG_ATTENTION_ENABLED | ACTOR_FLAG_FRIENDLY | ACTOR_FLAG_UPDATE_CULLING_DISABLED | \
     ACTOR_FLAG_DRAW_CULLING_DISABLED)

void EnPm_Init(Actor* thisx, PlayState* play);
void EnPm_Destroy(Actor* thisx, PlayState* play);
void EnPm_Update(Actor* thisx, PlayState* play);
void EnPm_Draw(Actor* thisx, PlayState* play);

void func_80AFA4D0(EnPm* this, PlayState* play);
void func_80AFA5FC(EnPm* this, PlayState* play);

#include "src/overlays/actors/ovl_En_Pm/scheduleScripts.schl.inc"

static s32 D_80AFB430[] = {
    -1, 0, 4, 1,  0,  0, 1, 4,  -1, -1, 15, 5, 0, 3, -1, -1, 1, 2, 11, 3, -1, -1, -1, 0, 0, 0, 0, 0, 1,  12, -1,
    -1, 2, 0, 10, 11, 0, 3, 1,  0,  1,  2,  0, 1, 0, 1,  2,  3, 4, 3,  5, 14, 3,  1,  0, 6, 4, 1, 2, 6,  7,  8,
    2,  1, 0, 6,  7,  9, 8, -1, 0,  1,  10, 3, 1, 0, 11, 12, 8, 2, 2,  3, 0,  1,  1,  0, 6, 9, 1, 2, 12, 13,
};

static MsgScript D_80AFB5A0[] = {
    /* 0x0000 0x05 */ MSCRIPT_CMD_CHECK_WEEK_EVENT_REG(WEEKEVENTREG_LISTENED_ANJU_POSTMAN_CONVERSATION,
                                                       0x004A - 0x0005),
    /* 0x0005 0x03 */ MSCRIPT_CMD_CHECK_CALLBACK(0x0),
    /* 0x0008 0x01 */ MSCRIPT_CMD_FOCUS_TO_CHILD(),
    /* 0x0009 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x28BA),
    /* 0x000C 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x000D 0x03 */ MSCRIPT_CMD_CHECK_CALLBACK(0x0),
    /* 0x0010 0x01 */ MSCRIPT_CMD_FOCUS_TO_SELF(),
    /* 0x0011 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x28BB),
    /* 0x0014 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x0015 0x03 */ MSCRIPT_CMD_CHECK_CALLBACK(0x0),
    /* 0x0018 0x01 */ MSCRIPT_CMD_FOCUS_TO_CHILD(),
    /* 0x0019 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x28BC),
    /* 0x001C 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x001D 0x03 */ MSCRIPT_CMD_CHECK_CALLBACK(0x0),
    /* 0x0020 0x01 */ MSCRIPT_CMD_FOCUS_TO_SELF(),
    /* 0x0021 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x28BD),
    /* 0x0024 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x0025 0x03 */ MSCRIPT_CMD_CHECK_CALLBACK(0x0),
    /* 0x0028 0x01 */ MSCRIPT_CMD_FOCUS_TO_CHILD(),
    /* 0x0029 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x28BE),
    /* 0x002C 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x002D 0x03 */ MSCRIPT_CMD_CHECK_CALLBACK(0x0),
    /* 0x0030 0x01 */ MSCRIPT_CMD_FOCUS_TO_SELF(),
    /* 0x0031 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x28BF),
    /* 0x0034 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x0035 0x03 */ MSCRIPT_CMD_CHECK_CALLBACK(0x0),
    /* 0x0038 0x01 */ MSCRIPT_CMD_FOCUS_TO_CHILD(),
    /* 0x0039 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x28C0),
    /* 0x003C 0x03 */ MSCRIPT_CMD_NOTEBOOK_EVENT(BOMBERS_NOTEBOOK_EVENT_MET_ANJU),
    /* 0x003F 0x03 */ MSCRIPT_CMD_NOTEBOOK_EVENT(BOMBERS_NOTEBOOK_EVENT_MET_POSTMAN),
    /* 0x0042 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x0043 0x03 */ MSCRIPT_CMD_CHECK_CALLBACK(0x0),
    /* 0x0046 0x03 */ MSCRIPT_CMD_SET_WEEK_EVENT_REG(WEEKEVENTREG_LISTENED_ANJU_POSTMAN_CONVERSATION),
    /* 0x0049 0x01 */ MSCRIPT_CMD_DONE(),

    /* 0x004A 0x03 */ MSCRIPT_CMD_CHECK_CALLBACK(0x0),
    /* 0x004D 0x01 */ MSCRIPT_CMD_FOCUS_TO_CHILD(),
    /* 0x004E 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x295C),
    /* 0x0051 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x0052 0x03 */ MSCRIPT_CMD_CHECK_CALLBACK(0x0),
    /* 0x0055 0x01 */ MSCRIPT_CMD_FOCUS_TO_SELF(),
    /* 0x0056 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x295D),
    /* 0x0059 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x005A 0x03 */ MSCRIPT_CMD_CHECK_CALLBACK(0x0),
    /* 0x005D 0x01 */ MSCRIPT_CMD_FOCUS_TO_CHILD(),
    /* 0x005E 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x295E),
    /* 0x0061 0x03 */ MSCRIPT_CMD_NOTEBOOK_EVENT(BOMBERS_NOTEBOOK_EVENT_MET_ANJU),
    /* 0x0064 0x03 */ MSCRIPT_CMD_NOTEBOOK_EVENT(BOMBERS_NOTEBOOK_EVENT_MET_POSTMAN),
    /* 0x0067 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x0068 0x03 */ MSCRIPT_CMD_CHECK_CALLBACK(0x0),
    /* 0x006B 0x01 */ MSCRIPT_CMD_DONE(),
};

static MsgScript D_80AFB60C[] = {
    /* 0x0000 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x2774),
    /* 0x0003 0x03 */ MSCRIPT_CMD_NOTEBOOK_EVENT(BOMBERS_NOTEBOOK_EVENT_MET_POSTMAN),
    /* 0x0006 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x0007 0x01 */ MSCRIPT_CMD_DONE(),
};

static MsgScript D_80AFB614[] = {
    /* 0x0000 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x2775),
    /* 0x0003 0x03 */ MSCRIPT_CMD_NOTEBOOK_EVENT(BOMBERS_NOTEBOOK_EVENT_MET_POSTMAN),
    /* 0x0006 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x0007 0x01 */ MSCRIPT_CMD_DONE(),
};

static MsgScript D_80AFB61C[] = {
    /* 0x0000 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x2777),
    /* 0x0003 0x03 */ MSCRIPT_CMD_NOTEBOOK_EVENT(BOMBERS_NOTEBOOK_EVENT_MET_POSTMAN),
    /* 0x0006 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x0007 0x01 */ MSCRIPT_CMD_DONE(),
};

static MsgScript D_80AFB624[] = {
    /* 0x0000 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x2778),
    /* 0x0003 0x03 */ MSCRIPT_CMD_NOTEBOOK_EVENT(BOMBERS_NOTEBOOK_EVENT_MET_POSTMAN),
    /* 0x0006 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x0007 0x01 */ MSCRIPT_CMD_DONE(),
};

static MsgScript D_80AFB62C[] = {
    /* 0x0000 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x2779),
    /* 0x0003 0x03 */ MSCRIPT_CMD_NOTEBOOK_EVENT(BOMBERS_NOTEBOOK_EVENT_MET_POSTMAN),
    /* 0x0006 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x0007 0x01 */ MSCRIPT_CMD_DONE(),
};

static MsgScript D_80AFB634[] = {
    /* 0x0000 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x2781),
    /* 0x0003 0x03 */ MSCRIPT_CMD_NOTEBOOK_EVENT(BOMBERS_NOTEBOOK_EVENT_MET_POSTMAN),
    /* 0x0006 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x0007 0x01 */ MSCRIPT_CMD_DONE(),
};

static MsgScript D_80AFB63C[] = {
    /* 0x0000 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x277A),
    /* 0x0003 0x03 */ MSCRIPT_CMD_NOTEBOOK_EVENT(BOMBERS_NOTEBOOK_EVENT_MET_POSTMAN),
    /* 0x0006 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x0007 0x01 */ MSCRIPT_CMD_DONE(),
};

static MsgScript D_80AFB644[] = {
    /* 0x0000 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x2782),
    /* 0x0003 0x03 */ MSCRIPT_CMD_NOTEBOOK_EVENT(BOMBERS_NOTEBOOK_EVENT_MET_POSTMAN),
    /* 0x0006 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x0007 0x03 */ MSCRIPT_CMD_SET_WEEK_EVENT_REG(WEEKEVENTREG_88_02),
    /* 0x000A 0x01 */ MSCRIPT_CMD_DONE(),
};

static MsgScript D_80AFB650[] = {
    /* 0x0000 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x2783),
    /* 0x0003 0x03 */ MSCRIPT_CMD_NOTEBOOK_EVENT(BOMBERS_NOTEBOOK_EVENT_MET_POSTMAN),
    /* 0x0006 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x0007 0x01 */ MSCRIPT_CMD_DONE(),
};

static MsgScript D_80AFB658[] = {
    /* 0x0000 0x05 */ MSCRIPT_CMD_CHECK_ITEM(ITEM_LETTER_MAMA, 0x001F - 0x0005),
    /* 0x0005 0x05 */ MSCRIPT_CMD_CHECK_WEEK_EVENT_REG(WEEKEVENTREG_82_80, 0x0016 - 0x000A),
    /* 0x000A 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x277C),
    /* 0x000D 0x03 */ MSCRIPT_CMD_NOTEBOOK_EVENT(BOMBERS_NOTEBOOK_EVENT_MET_POSTMAN),
    /* 0x0010 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x0011 0x03 */ MSCRIPT_CMD_SET_WEEK_EVENT_REG(WEEKEVENTREG_82_80),
    /* 0x0014 0x01 */ MSCRIPT_CMD_CLOSE_TEXT(),
    /* 0x0015 0x01 */ MSCRIPT_CMD_DONE(),

    /* 0x0016 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x277D),
    /* 0x0019 0x03 */ MSCRIPT_CMD_NOTEBOOK_EVENT(BOMBERS_NOTEBOOK_EVENT_MET_POSTMAN),
    /* 0x001C 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x001D 0x01 */ MSCRIPT_CMD_CLOSE_TEXT(),
    /* 0x001E 0x01 */ MSCRIPT_CMD_DONE(),

    /* 0x001F 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x277C),
    /* 0x0022 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x0023 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x00FF),
    /* 0x0026 0x09 */ MSCRIPT_CMD_CHECK_ITEM_ACTION(PLAYER_IA_LETTER_MAMA, 0x0, 0x0047 - 0x002F, 0x0057 - 0x002F),
    /* 0x002F 0x03 */ MSCRIPT_CMD_PLAYER_TALK(0xFFFF),
    /* 0x0032 0x03 */ MSCRIPT_CMD_CHECK_CALLBACK(0x0),
    /* 0x0035 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x277E),
    /* 0x0038 0x03 */ MSCRIPT_CMD_NOTEBOOK_EVENT(BOMBERS_NOTEBOOK_EVENT_MET_POSTMAN),
    /* 0x003B 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x003C 0x03 */ MSCRIPT_CMD_SET_WEEK_EVENT_REG(WEEKEVENTREG_82_80),
    /* 0x003F 0x03 */ MSCRIPT_CMD_SET_WEEK_EVENT_REG(WEEKEVENTREG_86_01),
    /* 0x0042 0x03 */ MSCRIPT_CMD_DELETE_ITEM(ITEM_LETTER_MAMA),
    /* 0x0045 0x01 */ MSCRIPT_CMD_CLOSE_TEXT(),
    /* 0x0046 0x01 */ MSCRIPT_CMD_DONE(),

    /* 0x0047 0x03 */ MSCRIPT_CMD_PLAYER_TALK(0x277D),
    /* 0x004A 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x004B 0x03 */ MSCRIPT_CMD_JUMP_3(0x0),
    /* 0x004E 0x03 */ MSCRIPT_CMD_NOTEBOOK_EVENT(BOMBERS_NOTEBOOK_EVENT_MET_POSTMAN),
    /* 0x0051 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x0052 0x03 */ MSCRIPT_CMD_SET_WEEK_EVENT_REG(WEEKEVENTREG_82_80),
    /* 0x0055 0x01 */ MSCRIPT_CMD_CLOSE_TEXT(),
    /* 0x0056 0x01 */ MSCRIPT_CMD_DONE(),

    /* 0x0057 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x277D),
    /* 0x005A 0x03 */ MSCRIPT_CMD_NOTEBOOK_EVENT(BOMBERS_NOTEBOOK_EVENT_MET_POSTMAN),
    /* 0x005D 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x005E 0x03 */ MSCRIPT_CMD_SET_WEEK_EVENT_REG(WEEKEVENTREG_82_80),
    /* 0x0061 0x01 */ MSCRIPT_CMD_CLOSE_TEXT(),
    /* 0x0062 0x01 */ MSCRIPT_CMD_DONE(),
};

static MsgScript D_80AFB6BC[] = {
    /* 0x0000 0x03 */ MSCRIPT_CMD_CHECK_CALLBACK(0x0),
    /* 0x0003 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x27A5),
    /* 0x0006 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x0007 0x03 */ MSCRIPT_CMD_CHECK_CALLBACK(0x0),
    /* 0x000A 0x01 */ MSCRIPT_CMD_FOCUS_TO_CHILD(),
    /* 0x000B 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x27A6),
    /* 0x000E 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x000F 0x03 */ MSCRIPT_CMD_CHECK_CALLBACK(0x0),
    /* 0x0012 0x01 */ MSCRIPT_CMD_FOCUS_TO_SELF(),
    /* 0x0013 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x27A7),
    /* 0x0016 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x0017 0x03 */ MSCRIPT_CMD_CHECK_CALLBACK(0x0),
    /* 0x001A 0x01 */ MSCRIPT_CMD_FOCUS_TO_CHILD(),
    /* 0x001B 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x27A8),
    /* 0x001E 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x001F 0x03 */ MSCRIPT_CMD_CHECK_CALLBACK(0x0),
    /* 0x0022 0x01 */ MSCRIPT_CMD_FOCUS_TO_SELF(),
    /* 0x0023 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x27A9),
    /* 0x0026 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x0027 0x03 */ MSCRIPT_CMD_CHECK_CALLBACK(0x0),
    /* 0x002A 0x01 */ MSCRIPT_CMD_FOCUS_TO_CHILD(),
    /* 0x002B 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x27AA),
    /* 0x002E 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x002F 0x03 */ MSCRIPT_CMD_CHECK_CALLBACK(0x0),
    /* 0x0032 0x01 */ MSCRIPT_CMD_FOCUS_TO_SELF(),
    /* 0x0033 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x27AB),
    /* 0x0036 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x0037 0x03 */ MSCRIPT_CMD_CHECK_CALLBACK(0x0),
    /* 0x003A 0x01 */ MSCRIPT_CMD_FOCUS_TO_CHILD(),
    /* 0x003B 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x27AC),
    /* 0x003E 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x003F 0x03 */ MSCRIPT_CMD_CHECK_CALLBACK(0x0),
    /* 0x0042 0x01 */ MSCRIPT_CMD_FOCUS_TO_SELF(),
    /* 0x0043 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x27AD),
    /* 0x0046 0x03 */ MSCRIPT_CMD_NOTEBOOK_EVENT(BOMBERS_NOTEBOOK_EVENT_MET_POSTMAN),
    /* 0x0049 0x03 */ MSCRIPT_CMD_NOTEBOOK_EVENT(BOMBERS_NOTEBOOK_EVENT_MET_MADAME_AROMA),
    /* 0x004C 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x004D 0x03 */ MSCRIPT_CMD_SET_WEEK_EVENT_REG(WEEKEVENTREG_89_08),
    /* 0x0050 0x03 */ MSCRIPT_CMD_CHECK_CALLBACK(0x0),
    /* 0x0053 0x01 */ MSCRIPT_CMD_DONE(),
};

static MsgScript D_80AFB710[] = {
    /* 0x0000 0x05 */ MSCRIPT_CMD_CHECK_ITEM(ITEM_MASK_POSTMAN, 0x0028 - 0x0005),
    /* 0x0005 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x2780),
    /* 0x0008 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x0009 0x03 */ MSCRIPT_CMD_CONTINUE_TEXT(0x27AE),
    /* 0x000C 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x000D 0x01 */ MSCRIPT_CMD_CLOSE_TEXT(),
    /* 0x000E 0x05 */ MSCRIPT_CMD_OFFER_ITEM(GI_MASK_POSTMAN, 0x0),
    /* 0x0013 0x03 */ MSCRIPT_CMD_SET_COLLECTIBLE(0x0084),
    /* 0x0016 0x03 */ MSCRIPT_CMD_SET_WEEK_EVENT_REG(WEEKEVENTREG_90_04),
    /* 0x0019 0x03 */ MSCRIPT_CMD_JUMP_3(0x0),
    /* 0x001C 0x01 */ MSCRIPT_CMD_AWAIT_TEXT_DONE(),
    /* 0x001D 0x03 */ MSCRIPT_CMD_NOTEBOOK_EVENT(BOMBERS_NOTEBOOK_EVENT_MET_POSTMAN),
    /* 0x0020 0x03 */ MSCRIPT_CMD_NOTEBOOK_EVENT(BOMBERS_NOTEBOOK_EVENT_RECEIVED_POSTMANS_HAT),
    /* 0x0023 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x0024 0x03 */ MSCRIPT_CMD_SET_WEEK_EVENT_REG(WEEKEVENTREG_90_01),
    /* 0x0027 0x01 */ MSCRIPT_CMD_DONE(),

    /* 0x0028 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x2780),
    /* 0x002B 0x03 */ MSCRIPT_CMD_NOTEBOOK_EVENT(BOMBERS_NOTEBOOK_EVENT_MET_POSTMAN),
    /* 0x002E 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x002F 0x03 */ MSCRIPT_CMD_SET_WEEK_EVENT_REG(WEEKEVENTREG_90_01),
    /* 0x0032 0x01 */ MSCRIPT_CMD_CLOSE_TEXT(),
    /* 0x0033 0x01 */ MSCRIPT_CMD_DONE(),
};

static MsgScript D_80AFB744[] = {
    /* 0x0000 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x2369),
    /* 0x0003 0x03 */ MSCRIPT_CMD_NOTEBOOK_EVENT(BOMBERS_NOTEBOOK_EVENT_MET_POSTMAN),
    /* 0x0006 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x0007 0x01 */ MSCRIPT_CMD_DONE(),
};

static MsgScript D_80AFB74C[] = {
    /* 0x0000 0x03 */ MSCRIPT_CMD_PLAYER_TALK(0xFFFF),
    /* 0x0003 0x03 */ MSCRIPT_CMD_CHECK_CALLBACK(0x0),
    /* 0x0006 0x03 */ MSCRIPT_CMD_BEGIN_TEXT(0x277E),
    /* 0x0009 0x03 */ MSCRIPT_CMD_NOTEBOOK_EVENT(BOMBERS_NOTEBOOK_EVENT_MET_POSTMAN),
    /* 0x000C 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x000D 0x03 */ MSCRIPT_CMD_SET_WEEK_EVENT_REG(WEEKEVENTREG_82_80),
    /* 0x0010 0x03 */ MSCRIPT_CMD_SET_WEEK_EVENT_REG(WEEKEVENTREG_86_01),
    /* 0x0013 0x03 */ MSCRIPT_CMD_DELETE_ITEM(ITEM_LETTER_MAMA),
    /* 0x0016 0x01 */ MSCRIPT_CMD_CLOSE_TEXT(),
    /* 0x0017 0x01 */ MSCRIPT_CMD_DONE(),
};

static MsgScript D_80AFB764[] = {
    /* 0x0000 0x03 */ MSCRIPT_CMD_PLAYER_TALK(0x277D),
    /* 0x0003 0x03 */ MSCRIPT_CMD_NOTEBOOK_EVENT(BOMBERS_NOTEBOOK_EVENT_MET_POSTMAN),
    /* 0x0006 0x01 */ MSCRIPT_CMD_AWAIT_TEXT(),
    /* 0x0007 0x03 */ MSCRIPT_CMD_SET_WEEK_EVENT_REG(WEEKEVENTREG_82_80),
    /* 0x000A 0x01 */ MSCRIPT_CMD_CLOSE_TEXT(),
    /* 0x000B 0x01 */ MSCRIPT_CMD_DONE(),
};

ActorProfile En_Pm_Profile = {
    /**/ ACTOR_EN_PM,
    /**/ ACTORCAT_NPC,
    /**/ FLAGS,
    /**/ OBJECT_MM,
    /**/ sizeof(EnPm),
    /**/ EnPm_Init,
    /**/ EnPm_Destroy,
    /**/ EnPm_Update,
    /**/ EnPm_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COL_MATERIAL_HIT1,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEM_MATERIAL_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        ATELEM_NONE | ATELEM_SFX_NORMAL,
        ACELEM_NONE,
        OCELEM_ON,
    },
    { 14, 62, 0, { 0, 0, 0 } },
};

static ColliderSphereInit sSphereInit = {
    {
        COL_MATERIAL_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_SPHERE,
    },
    {
        ELEM_MATERIAL_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        ATELEM_NONE | ATELEM_SFX_NORMAL,
        ACELEM_NONE,
        OCELEM_ON,
    },
    { 0, { { 0, 0, 0 }, 26 }, 100 },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

typedef enum EnPmAnimation {
    /* -1 */ ENPM_ANIM_NONE = -1,
    /*  0 */ ENPM_ANIM_0,
    /*  1 */ ENPM_ANIM_1,
    /*  2 */ ENPM_ANIM_2,
    /*  3 */ ENPM_ANIM_3,
    /*  4 */ ENPM_ANIM_4,
    /*  5 */ ENPM_ANIM_5,
    /*  6 */ ENPM_ANIM_6,
    /*  7 */ ENPM_ANIM_7,
    /*  8 */ ENPM_ANIM_8,
    /*  9 */ ENPM_ANIM_9,
    /* 10 */ ENPM_ANIM_10,
    /* 11 */ ENPM_ANIM_11,
    /* 12 */ ENPM_ANIM_12,
    /* 13 */ ENPM_ANIM_13,
    /* 14 */ ENPM_ANIM_MAX
} EnPmAnimation;

static AnimationInfoS sAnimationInfo[ENPM_ANIM_MAX] = {
    { &object_mm_Anim_002238, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },  // ENPM_ANIM_0
    { &object_mm_Anim_002238, 1.0f, 0, -1, ANIMMODE_LOOP, -4 }, // ENPM_ANIM_1
    { &object_mm_Anim_00A4E0, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },  // ENPM_ANIM_2
    { &object_mm_Anim_00B09C, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },  // ENPM_ANIM_3
    { &object_mm_Anim_00B09C, 1.0f, 0, -1, ANIMMODE_LOOP, -4 }, // ENPM_ANIM_4
    { &object_mm_Anim_00BA78, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },  // ENPM_ANIM_5
    { &object_mm_Anim_00C32C, 1.0f, 0, -1, ANIMMODE_LOOP, -4 }, // ENPM_ANIM_6
    { &object_mm_Anim_0099B4, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },  // ENPM_ANIM_7
    { &object_mm_Anim_000FC4, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },  // ENPM_ANIM_8
    { &object_mm_Anim_00A8D8, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },  // ENPM_ANIM_9
    { &object_mm_Anim_00099C, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },  // ENPM_ANIM_10
    { &object_mm_Anim_001F84, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },  // ENPM_ANIM_11
    { &object_mm_Anim_000468, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },  // ENPM_ANIM_12
    { &object_mm_Anim_00C640, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },  // ENPM_ANIM_13
};

s32 func_80AF7B40(void) {
    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_90_01)) {
        return 4;
    }

    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_89_40)) {
        return 3;
    }

    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_89_08)) {
        return 2;
    }

    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_86_01)) {
        return 1;
    }

    return 0;
}

s32 func_80AF7BAC(EnPm* this) {
    switch (this->unk_38C) {
        case 0:
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_86_01)) {
                D_801F4E78 = CURRENT_TIME;
                this->unk_38C++;
            }
            break;

        case 1:
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_89_08)) {
                D_801F4E78 = CURRENT_TIME;
                this->unk_38C++;
            }
            break;

        case 2:
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_89_40)) {
                D_801F4E78 = CLOCK_TIME(0, 0);
                this->unk_38C++;
            }
            break;

        case 3:
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_90_01)) {
                D_801F4E78 = CURRENT_TIME;
                this->unk_38C++;
            }
            break;
    }

    return true;
}

Actor* EnPm_FindActor(EnPm* this, PlayState* play, u8 actorCategory, s16 actorId) {
    Actor* actorIter = NULL;

    while (true) {
        actorIter = SubS_FindActor(play, actorIter, actorCategory, actorId);

        if (actorIter == NULL) {
            break;
        }

        if ((this != (EnPm*)actorIter) && (actorIter->update != NULL)) {
            break;
        }

        if (actorIter->next == NULL) {
            actorIter = NULL;
            break;
        }

        actorIter = actorIter->next;
    }

    return actorIter;
}

EnDoor* EnPm_FindScheduleDoor(PlayState* play, s32 scheduleOutputResult) {
    EnDoorScheduleType schType;

    switch (scheduleOutputResult) {
        case 1:
        case 2:
        case 32:
        case 33:
            schType = ENDOOR_SCH_TYPE_POST_OFFICE;
            break;

        case 34:
        case 35:
        case 36:
        case 37:
            schType = ENDOOR_SCH_TYPE_MILK_BAR;
            break;

        case 10:
        case 11:
        case 12:
        case 13:
            schType = ENDOOR_SCH_TYPE_INN_MAIN_ENTRANCE;
            break;

        default:
            return NULL;
    }

    return SubS_FindScheduleDoor(play, schType);
}

Actor* func_80AF7DC4(EnPm* this, PlayState* play, s32 arg2) {
    Actor* actorIter = NULL;

    while (true) {
        actorIter = SubS_FindActor(play, actorIter, ACTORCAT_PROP, ACTOR_EN_PST);

        if (actorIter == NULL) {
            break;
        }

        if ((this != (EnPm*)actorIter) && (actorIter->update != NULL) && (actorIter->params == (s16)arg2)) {
            break;
        }

        if (actorIter->next == NULL) {
            actorIter = NULL;
            break;
        }

        actorIter = actorIter->next;
    }

    return actorIter;
}

void EnPm_UpdateSkelAnime(EnPm* this) {
    this->skelAnime.playSpeed = this->animPlaySpeed;
    SkelAnime_Update(&this->skelAnime);
}

s32 EnPm_ChangeAnim(EnPm* this, s32 animIndex) {
    s32 changeAnim = false;
    s32 didAnimChange = false;

    switch (animIndex) {
        case ENPM_ANIM_0:
        case ENPM_ANIM_1:
            if ((this->animIndex != ENPM_ANIM_0) && (this->animIndex != ENPM_ANIM_1)) {
                changeAnim = true;
            }
            break;

        case ENPM_ANIM_3:
        case ENPM_ANIM_4:
            if ((this->animIndex != ENPM_ANIM_3) && (this->animIndex != ENPM_ANIM_4)) {
                changeAnim = true;
            }
            break;

        default:
            if (this->animIndex != animIndex) {
                changeAnim = true;
            }
            break;
    }

    if (changeAnim) {
        this->animIndex = animIndex;
        didAnimChange = SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, animIndex);
        this->animPlaySpeed = this->skelAnime.playSpeed;
    }

    return didAnimChange;
}

void func_80AF7F68(EnPm* this, PlayState* play) {
    f32 temp;
    s32 pad;

    switch (this->scheduleResult) {
        case 9:
        case 20:
        case 21:
        case 22:
        case 24:
            temp = this->colliderSphere.dim.modelSphere.radius * this->colliderSphere.dim.scale;
            this->colliderSphere.dim.worldSphere.radius = temp;
            CollisionCheck_SetOC(play, &play->colChkCtx, &this->colliderSphere.base);
            break;

        default:
            Collider_UpdateCylinder(&this->actor, &this->colliderCylinder);
            temp = this->actor.focus.pos.y - this->actor.world.pos.y;
            this->colliderCylinder.dim.height = temp;
            CollisionCheck_SetOC(play, &play->colChkCtx, &this->colliderCylinder.base);
            break;
    }
}

Actor* func_80AF8040(EnPm* this, PlayState* play) {
    Actor* actor;

    switch (this->scheduleResult) {
        case 16:
            actor = EnPm_FindActor(this, play, ACTORCAT_NPC, ACTOR_EN_AN);
            break;

        case 17:
            actor = EnPm_FindActor(this, play, ACTORCAT_NPC, ACTOR_EN_TEST3);
            break;

        case 28:
            actor = EnPm_FindActor(this, play, ACTORCAT_NPC, ACTOR_EN_AL);
            break;

        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            actor = func_80AF7DC4(this, play, this->scheduleResult - 3);
            break;

        case 19:
            actor = func_80AF7DC4(this, play, 4);
            break;

        case 18:
            actor = func_80AF7DC4(this, play, 4);
            break;

        default:
            actor = &GET_PLAYER(play)->actor;
            break;
    }

    return actor;
}

s32 func_80AF80F4(EnPm* this, s16 csId) {
    s32 ret = false;

    if (CutsceneManager_GetCurrentCsId() == CS_ID_GLOBAL_TALK) {
        CutsceneManager_Stop(CS_ID_GLOBAL_TALK);
        CutsceneManager_Queue(csId);
    } else if (CutsceneManager_IsNext(csId)) {
        CutsceneManager_StartWithPlayerCs(csId, &this->actor);
        ret = true;
    } else {
        CutsceneManager_Queue(csId);
    }
    return ret;
}

s16 func_80AF8170(EnPm* this, s32 numCutscenes) {
    s32 i;
    s16 csId = CS_ID_NONE;

    if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
        csId = this->actor.child->csId;

        for (i = 0; i < numCutscenes; i++) {
            csId = CutsceneManager_GetAdditionalCsId(csId);
        }
    }
    return csId;
}

s32 func_80AF81E8(Actor* thisx, PlayState* play) {
    EnPm* this = (EnPm*)thisx;
    s16 csId = func_80AF8170(this, 0);
    s32 ret = false;

    switch (this->unk_378) {
        case 0:
            if (!func_80AF80F4(this, csId)) {
                break;
            }
            FALLTHROUGH;
        case 2:
        case 4:
        case 6:
            if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
                Camera_SetTargetActor(Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(csId)),
                                      this->actor.child);
            }
            this->unk_378++;
            ret = true;
            break;

        case 1:
        case 3:
        case 5:
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_LISTENED_ANJU_POSTMAN_CONVERSATION) && (this->unk_378 == 3)) {
                CutsceneManager_Stop(csId);
            } else {
                Camera_SetTargetActor(Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(csId)), &this->actor);
            }
            this->unk_378++;
            ret = true;
            break;

        case 7:
            CutsceneManager_Stop(csId);
            this->unk_378++;
            ret = true;
            break;
    }
    return ret;
}

s32 func_80AF8348(Actor* thisx, PlayState* play) {
    EnPm* this = (EnPm*)thisx;
    s16 csId = func_80AF8170(this, 0);
    s32 ret = false;

    switch (this->unk_378) {
        case 0:
            if (!func_80AF80F4(this, csId)) {
                break;
            }
            FALLTHROUGH;
        case 2:
        case 4:
        case 6:
        case 8:
            Camera_SetTargetActor(Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(csId)), &this->actor);
            this->unk_378++;
            ret = true;
            break;

        case 1:
        case 3:
        case 5:
        case 7:
            if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
                Camera_SetTargetActor(Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(csId)),
                                      this->actor.child);
            }
            this->unk_378++;
            ret = true;
            break;

        case 9:
            CutsceneManager_Stop(csId);
            this->unk_378++;
            ret = true;
            break;
    }

    return ret;
}

s32 func_80AF8478(Actor* thisx, PlayState* play) {
    EnPm* this = (EnPm*)thisx;
    s32 ret = false;

    switch (this->unk_378) {
        case 0:
            EnPm_ChangeAnim(this, ENPM_ANIM_2);
            this->unk_356 &= ~0x20;
            this->unk_356 |= 0x200;
            this->unk_378++;
            break;

        case 1:
            if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                EnPm_ChangeAnim(this, ENPM_ANIM_4);
                this->unk_356 &= ~0x200;
                this->unk_356 |= 0x20;
                this->unk_378++;
                ret = true;
            }
            break;
    }
    return ret;
}

MsgScript* EnPm_GetMsgScript(EnPm* this, PlayState* play) {
    switch (this->scheduleResult) {
        case 28:
            this->msgScriptCallback = func_80AF8348;
            return D_80AFB6BC;

        case 29:
            return D_80AFB710;

        case 16:
            this->msgScriptCallback = func_80AF81E8;
            return D_80AFB5A0;

        case 17:
            return D_80AFB644;

        case 24:
            if (this->unk_356 & 0x2000) {
                this->msgScriptCallback = func_80AF8478;
                return D_80AFB74C;
            } else if (this->unk_356 & 0x4000) {
                return D_80AFB764;
            } else {
                this->msgScriptCallback = func_80AF8478;
                return D_80AFB658;
            }
            break;

        case 25:
            return D_80AFB650;

        default:
            if (Player_GetMask(play) == PLAYER_MASK_KAFEIS_MASK) {
                return D_80AFB744;
            }

            switch (this->scheduleResult) {
                case 9:
                    return D_80AFB614;

                case 14:
                    return D_80AFB624;

                case 20:
                    return D_80AFB61C;

                case 21:
                    return D_80AFB634;

                case 22:
                    return D_80AFB63C;

                case 18:
                case 74:
                case 75:
                case 76:
                case 77:
                case 78:
                case 79:
                    return D_80AFB62C;

                default:
                    return D_80AFB60C;
            }
            break;
    }
}

s32 func_80AF86F0(EnPm* this, PlayState* play) {
    s32 ret = false;

    if (((this->unk_356 & SUBS_OFFER_MODE_MASK) != SUBS_OFFER_MODE_NONE) &&
        Actor_TalkOfferAccepted(&this->actor, &play->state)) {
        SubS_SetOfferMode(&this->unk_356, SUBS_OFFER_MODE_NONE, SUBS_OFFER_MODE_MASK);
        this->unk_398 = 0;
        this->unk_378 = 0;
        this->msgScriptCallback = NULL;
        this->actor.child = this->unk_268;
        this->msgScript = EnPm_GetMsgScript(this, play);
        if ((this->scheduleResult != 24) && (this->scheduleResult != 9) && (this->scheduleResult != 20) &&
            (this->scheduleResult != 21) && (this->scheduleResult != 22)) {
            this->unk_356 |= 0x20;
        }
        this->actionFunc = func_80AFA5FC;
        ret = true;
    }
    return ret;
}

s32 func_80AF87C4(EnPm* this, PlayState* play) {
    s32 ret = false;

    if ((play->csCtx.state != CS_STATE_IDLE) && (play->sceneId == SCENE_00KEIKOKU) && (gSaveContext.sceneLayer == 9) &&
        (play->curSpawn == 1)) {
        if (!this->unk_380) {
            EnPm_ChangeAnim(this, ENPM_ANIM_0);
            this->scheduleResult = 255;
            this->unk_380 = true;
            this->actor.speed = 4.0f;
            this->actor.gravity = -1.0f;
        }
        ret = true;
    } else if (this->unk_380) {
        this->scheduleResult = 0;
        this->unk_380 = false;
        this->actor.speed = 0.0f;
    }
    return ret;
}

void func_80AF8890(EnPm* this, Gfx** gfx, s32 arg2) {
    Matrix_Push();

    switch (arg2) {
        case 0:
            if (this->unk_356 & 0x800) {
                gSPDisplayList((*gfx)++, object_mm_DL_008348);
            }
            break;

        case 1:
            if (this->unk_356 & 0x1000) {
                gSPDisplayList((*gfx)++, object_mm_DL_0085C8);
            }
            break;

        case 2:
            if (this->unk_356 & 0x1000) {
                gSPDisplayList((*gfx)++, object_mm_DL_0083E0);
            }
            break;
    }

    Matrix_Pop();
}

void func_80AF898C(EnPm* this) {
    s32 pad;
    Vec3f sp40;
    Vec3f sp34;
    s32 pad2;

    Math_Vec3f_Copy(&sp40, &this->unk_268->world.pos);
    Math_Vec3f_Copy(&sp34, &this->actor.world.pos);
    Math_ApproachS(&this->unk_372, Math_Vec3f_Yaw(&sp34, &sp40) - this->actor.shape.rot.y, 4, 0x2AA8);
    this->unk_372 = CLAMP(this->unk_372, -0x1FFE, 0x1FFE);
    Math_Vec3f_Copy(&sp34, &this->actor.focus.pos);
    if (this->unk_268->id == ACTOR_PLAYER) {
        sp40.y = ((Player*)this->unk_268)->bodyPartsPos[PLAYER_BODYPART_HEAD].y + 3.0f;
    } else {
        Math_Vec3f_Copy(&sp40, &this->unk_268->focus.pos);
    }
    Math_ApproachS(&this->unk_370, Math_Vec3f_Pitch(&sp34, &sp40), 4, 0x2AA8);
    this->unk_370 = CLAMP(this->unk_370, -0x1554, 0x1554);
}

void func_80AF8AC8(EnPm* this) {
    if ((this->unk_356 & 0x20) && (this->unk_268 != NULL) && (this->unk_268->update != NULL)) {
        if (DECR(this->unk_376) == 0) {
            func_80AF898C(this);
            this->unk_356 &= ~0x200;
            this->unk_356 |= 0x80;
            return;
        }
    }

    if (this->unk_356 & 0x80) {
        this->unk_356 &= ~0x80;
        this->unk_370 = 0;
        this->unk_372 = 0;
        this->unk_376 = 20;
    } else if (DECR(this->unk_376) == 0) {
        this->unk_356 |= 0x200;
    }
}

void func_80AF8BA8(s32 arg0) {
    static u16 D_80AFB8D4[] = {
        WEEKEVENTREG_DEPOSITED_LETTER_TO_KAFEI_SOUTH_UPPER_CLOCKTOWN,
        WEEKEVENTREG_DEPOSITED_LETTER_TO_KAFEI_NORTH_CLOCKTOWN,
        WEEKEVENTREG_DEPOSITED_LETTER_TO_KAFEI_EAST_UPPER_CLOCKTOWN,
        WEEKEVENTREG_DEPOSITED_LETTER_TO_KAFEI_EAST_LOWER_CLOCKTOWN,
        WEEKEVENTREG_DEPOSITED_LETTER_TO_KAFEI_SOUTH_LOWER_CLOCKTOWN,
    };
    static u16 D_80AFB8E0[] = {
        WEEKEVENTREG_27_40, WEEKEVENTREG_27_80, WEEKEVENTREG_28_01, WEEKEVENTREG_28_02, WEEKEVENTREG_28_04,
    };

    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_88_02)) {
        if (CHECK_WEEKEVENTREG(D_80AFB8D4[arg0])) {
            switch (gSaveContext.save.day) {
                case 2:
                    SET_WEEKEVENTREG(WEEKEVENTREG_28_08);
                    break;

                case 3:
                    SET_WEEKEVENTREG(WEEKEVENTREG_28_10);
                    break;
            }
            SET_WEEKEVENTREG(WEEKEVENTREG_51_02);
            SET_WEEKEVENTREG(WEEKEVENTREG_90_08);
        }
    }

    SET_WEEKEVENTREG(D_80AFB8E0[arg0]);
}

void func_80AF8C68(EnPm* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s32 talkState = Message_GetState(&play->msgCtx);
    u16 textId = play->msgCtx.currentTextId;

    if ((player->talkActor == &this->actor) && ((textId < 0xFF) || (textId > 0x200)) &&
        (talkState == TEXT_STATE_FADING) && (this->prevTalkState == TEXT_STATE_FADING)) {
        if ((play->state.frames % 3) == 0) {
            if (this->unk_360 == 120.0f) {
                this->unk_360 = 0.0f;
            } else {
                this->unk_360 = 120.0f;
            }
        }
    } else {
        this->unk_360 = 0.0f;
    }
    Math_SmoothStepToF(&this->unk_364, this->unk_360, 0.8f, 40.0f, 10.0f);
    Matrix_Translate(this->unk_364, 0.0f, 0.0f, MTXMODE_APPLY);
    this->prevTalkState = talkState;
}

s32 func_80AF8D84(EnPm* this, PlayState* play) {
    switch (this->animIndex) {
        case ENPM_ANIM_10:
            EnPm_ChangeAnim(this, ENPM_ANIM_9);
            break;

        case ENPM_ANIM_7:
            EnPm_ChangeAnim(this, ENPM_ANIM_0);
            break;

        default:
            break;
    }
    return true;
}

s32 func_80AF8DD4(EnPm* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    u16 textId = play->msgCtx.currentTextId;
    s32 pad;

    if (player->stateFlags1 & (PLAYER_STATE1_TALKING | PLAYER_STATE1_400)) {
        this->unk_356 |= 0x400;
        if (this->unk_358 != textId) {
            if ((this->animIndex == ENPM_ANIM_0) || (this->animIndex == ENPM_ANIM_1)) {
                EnPm_ChangeAnim(this, ENPM_ANIM_7);
            }
            if ((textId == 0x277C) || (textId == 0x277D)) {
                EnPm_ChangeAnim(this, ENPM_ANIM_10);
            }
        }
        this->unk_358 = textId;
    } else {
        if (this->unk_356 & 0x400) {
            this->unk_358 = 0;
            this->unk_356 &= ~0x400;
            func_80AF8D84(this, play);
        }
    }

    if (this->unk_18C != NULL) {
        this->unk_18C(this, play);
    }

    return 0;
}

s32 func_80AF8ED4(EnPm* this, PlayState* play, ScheduleOutput* scheduleOutput, u8 actorCategory, s16 actorId) {
    u8 pathIndex = ENPM_GET_PATH_INDEX(&this->actor);
    Vec3s* sp48;
    Vec3f sp3C;
    Vec3f sp30;
    Actor* sp2C;
    s32 pad;
    s32 ret = false;

    this->timePath = NULL;
    sp2C = EnPm_FindActor(this, play, actorCategory, actorId);
    if (D_80AFB430[scheduleOutput->result] >= 0) {
        this->timePath = SubS_GetAdditionalPath(play, pathIndex, D_80AFB430[scheduleOutput->result]);
    }

    if ((sp2C != NULL) && (sp2C->update != NULL)) {
        if (this->timePath != NULL) {
            sp48 = Lib_SegmentedToVirtual(this->timePath->points);
            Math_Vec3s_ToVec3f(&sp3C, &sp48[this->timePath->count - 2]);
            Math_Vec3s_ToVec3f(&sp30, &sp48[this->timePath->count - 1]);
            this->actor.shape.shadowDraw = NULL;
            this->actor.world.rot.y = Math_Vec3f_Yaw(&sp3C, &sp30);
            Math_Vec3f_Copy(&this->actor.world.pos, &sp30);
            ret = true;
        }
    }

    return ret;
}

s32 func_80AF9008(EnPm* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    u16 sp56 = SCRIPT_TIME_NOW;
    u8 pathIndex = ENPM_GET_PATH_INDEX(&this->actor);
    EnDoor* door;
    Vec3s* sp4C;
    Vec3f sp40;
    Vec3f sp34;
    s16 temp;
    s32 ret = false;

    this->timePath = NULL;
    door = EnPm_FindScheduleDoor(play, scheduleOutput->result);
    if (D_80AFB430[scheduleOutput->result] >= 0) {
        this->timePath = SubS_GetAdditionalPath(play, pathIndex, D_80AFB430[scheduleOutput->result]);
    }

    if ((door != NULL) && (door->knobDoor.dyna.actor.update != NULL)) {
        if (this->timePath != 0) {
            sp4C = Lib_SegmentedToVirtual(this->timePath->points);
            Math_Vec3s_ToVec3f(&sp40, &sp4C[0]);
            Math_Vec3s_ToVec3f(&sp34, &sp4C[1]);
            Math_Vec3f_Copy(&this->unk_26C, &sp40);
            Math_Vec3f_Copy(&this->unk_278, &sp34);
            this->actor.world.rot.y = Math_Vec3f_Yaw(&sp40, &sp34);
            Math_Vec3f_Copy(&this->actor.world.pos, &sp40);
            temp = this->actor.world.rot.y - door->knobDoor.dyna.actor.shape.rot.y;
            if (ABS_ALT(temp) <= 0x4000) {
                this->unk_260 = -0x4B;
            } else {
                this->unk_260 = 0x4B;
            }

            this->unk_36C = scheduleOutput->time1 - scheduleOutput->time0;
            this->unk_36E = sp56 - scheduleOutput->time0;
            this->actor.flags &= ~ACTOR_FLAG_ATTENTION_ENABLED;
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_90_08)) {
                this->unk_356 |= 0x800;
            }
            this->unk_356 |= 0x9000;
            this->unk_356 |= 0x200;
            EnPm_ChangeAnim(this, ENPM_ANIM_0);
            this->actor.gravity = 0.0f;
            ret = true;
        }
    }
    return ret;
}

s32 func_80AF91E8(EnPm* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    u16 sp2E = SCRIPT_TIME_NOW;
    u16 phi_v1;
    u8 pathIndex = ENPM_GET_PATH_INDEX(&this->actor);
    u16 tmp;
    s16 pad;
    s32 ret = false;

    this->timePath = NULL;

    if (D_80AFB430[scheduleOutput->result] >= 0) {
        this->timePath = SubS_GetAdditionalPath(play, pathIndex, D_80AFB430[scheduleOutput->result]);
    }

    if ((this->timePath != NULL) && (this->timePath->count < 3)) {
        this->timePath = NULL;
    }

    if (this->timePath != 0) {
        if ((this->scheduleResult < 38) && (this->scheduleResult != 0) && (this->timePathTimeSpeed >= 0)) {
            phi_v1 = sp2E;
        } else {
            phi_v1 = scheduleOutput->time0;
        }

        if (scheduleOutput->time1 < phi_v1) {
            this->timePathTotalTime = (phi_v1 - scheduleOutput->time1) + 0xFFFF;
        } else {
            this->timePathTotalTime = scheduleOutput->time1 - phi_v1;
        }

        this->timePathElapsedTime = sp2E - phi_v1;
        tmp = phi_v1 = this->timePath->count - (SUBS_TIME_PATHING_ORDER - 1);
        this->timePathWaypointTime = this->timePathTotalTime / tmp;
        this->timePathWaypoint =
            (this->timePathElapsedTime / this->timePathWaypointTime) + (SUBS_TIME_PATHING_ORDER - 1);
        this->unk_356 &= ~8;
        this->unk_356 &= ~0x10;
        if (this->scheduleResult == 27) {
            Actor_PlaySfx(&this->actor, NA_SE_EV_ROOM_CARTAIN);
            Flags_UnsetSwitch(play, 0);
        }

        switch (scheduleOutput->result) {
            case 83:
            case 84:
            case 85:
            case 86:
            case 87:
            case 88:
            case 89:
            case 90:
                this->unk_356 |= 0x9000;
                this->unk_356 |= 0x200;
                FALLTHROUGH;
            case 82:
                EnPm_ChangeAnim(this, ENPM_ANIM_0);
                break;

            case 91:
                this->unk_356 |= 0x9000;
                EnPm_ChangeAnim(this, ENPM_ANIM_12);
                break;

            default:
                SubS_SetOfferMode(&this->unk_356, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
                EnPm_ChangeAnim(this, ENPM_ANIM_0);
                if (CHECK_WEEKEVENTREG(WEEKEVENTREG_90_08)) {
                    this->unk_356 |= 0x800;
                }
                this->unk_356 |= 0x9000;
                this->unk_356 |= 0x200;
                break;
        }

        this->actor.gravity = -1.0f;
        ret = true;
    }

    return ret;
}

s32 func_80AF94AC(EnPm* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    u8 pathIndex = ENPM_GET_PATH_INDEX(&this->actor);
    Vec3f sp40;
    Vec3f sp34;
    Vec3s* sp30;
    s32 pad;
    s32 ret = false;

    this->timePath = NULL;
    if (D_80AFB430[scheduleOutput->result] >= 0) {
        this->timePath = SubS_GetAdditionalPath(play, pathIndex, D_80AFB430[scheduleOutput->result]);
    }

    if ((this->timePath != 0) && (this->timePath->count >= 2)) {
        sp30 = Lib_SegmentedToVirtual(this->timePath->points);
        Math_Vec3s_ToVec3f(&sp40, &sp30[0]);
        Math_Vec3s_ToVec3f(&sp34, &sp30[1]);
        this->actor.world.rot.y = Math_Vec3f_Yaw(&sp40, &sp34);
        Math_Vec3s_Copy(&this->actor.shape.rot, &this->actor.world.rot);
        Math_Vec3f_Copy(&this->actor.world.pos, &sp40);
        Math_Vec3f_Copy(&this->actor.prevPos, &sp40);
        if (scheduleOutput->result == 24) {
            Flags_UnsetSwitch(play, 0);
            Flags_UnsetSwitch(play, 1);
            this->unk_394 = PLAYER_IA_NONE;
            this->unk_368 = 60.0f;
            EnPm_ChangeAnim(this, ENPM_ANIM_9);
        }
        ret = true;
    }
    return ret;
}

s32 func_80AF95E8(EnPm* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    u8 pathIndex = ENPM_GET_PATH_INDEX(&this->actor);
    Vec3f sp40;
    Vec3f sp34;
    Vec3s* sp30;
    s32 pad;
    s32 ret = false;
    s32 phi_a3 = -1;

    switch (scheduleOutput->result) {
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            phi_a3 = scheduleOutput->result - 3;
            break;

        case 19:
            phi_a3 = 4;
            break;
    }

    if ((phi_a3 >= 0) && !func_80AF7DC4(this, play, phi_a3)) {
        return ret;
    }

    this->timePath = NULL;
    phi_a3 = D_80AFB430[scheduleOutput->result];
    if (phi_a3 >= 0) {
        this->timePath = SubS_GetAdditionalPath(play, pathIndex, phi_a3);
    }

    if ((this->timePath != 0) && (this->timePath->count >= 2)) {
        sp30 = Lib_SegmentedToVirtual(this->timePath->points);
        Math_Vec3s_ToVec3f(&sp40, &sp30[this->timePath->count - 1]);
        Math_Vec3s_ToVec3f(&sp34, &sp30[this->timePath->count - 2]);
        this->actor.world.rot.y = Math_Vec3f_Yaw(&sp34, &sp40);
        Math_Vec3s_Copy(&this->actor.shape.rot, &this->actor.world.rot);
        Math_Vec3f_Copy(&this->actor.world.pos, &sp40);
        Math_Vec3f_Copy(&this->actor.prevPos, &sp40);

        switch (scheduleOutput->result) {
            case 27:
                Actor_PlaySfx(&this->actor, NA_SE_EV_ROOM_CARTAIN);
                Flags_SetSwitch(play, 0);
                this->unk_36C = 20;
                SubS_SetOfferMode(&this->unk_356, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
                EnPm_ChangeAnim(this, ENPM_ANIM_3);
                break;

            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 19:
                this->unk_356 |= 0x9000;
                EnPm_ChangeAnim(this, ENPM_ANIM_11);
                break;

            case 18:
                this->unk_356 |= 0x9000;
                this->unk_356 |= 0x800;
                EnPm_ChangeAnim(this, ENPM_ANIM_5);
                break;

            case 23:
                if (CHECK_WEEKEVENTREG(WEEKEVENTREG_90_08)) {
                    this->unk_356 |= 0x800;
                }
                SET_WEEKEVENTREG(WEEKEVENTREG_60_04);
                FALLTHROUGH;
            default:
                if (scheduleOutput->result == 29) {
                    this->actor.world.rot.y = BINANG_ROT180(this->actor.world.rot.y);
                }
                SubS_SetOfferMode(&this->unk_356, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
                this->unk_356 |= 0x9000;
                EnPm_ChangeAnim(this, ENPM_ANIM_3);
                break;
        }
        ret = true;
    }
    return ret;
}

s32 func_80AF98A0(EnPm* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    s32 ret = false;

    if (Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EN_MM3, 116.0f, 26.0f, -219.0f, 0, -0x3F46, 0,
                           0) != NULL) {
        Actor_Kill(&this->actor);
        ret = true;
    }
    return ret;
}

s32 func_80AF992C(EnPm* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    static Vec3f D_80AFB8EC = { 116.0f, 26.0f, -219.0f };
    static Vec3s D_80AFB8F8 = { 0x0000, 0xC0BA, 0x0000 };
    s32 pad;

    Math_Vec3f_Copy(&this->actor.world.pos, &D_80AFB8EC);
    Math_Vec3s_Copy(&this->actor.world.rot, &D_80AFB8F8);
    Math_Vec3s_Copy(&this->actor.shape.rot, &this->actor.world.rot);
    SubS_SetOfferMode(&this->unk_356, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
    this->actor.attentionRangeType = ATTENTION_RANGE_6;
    this->actor.gravity = -1.0f;
    this->unk_368 = 80.0f;
    if (scheduleOutput->result == 14) {
        this->unk_356 &= ~0x200;
        EnPm_ChangeAnim(this, ENPM_ANIM_13);
    } else {
        this->unk_356 &= ~0x200;
        EnPm_ChangeAnim(this, ENPM_ANIM_8);
    }
    return true;
}

s32 func_80AF9A0C(EnPm* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    s32 ret = false;

    if (func_80AF8ED4(this, play, scheduleOutput, ACTORCAT_NPC, ACTOR_EN_AN)) {
        SubS_SetOfferMode(&this->unk_356, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
        this->unk_356 |= 0x20;
        this->unk_356 |= 0x9000;
        if (this->scheduleResult != 0) {
            this->unk_356 |= 0x800;
            EnPm_ChangeAnim(this, ENPM_ANIM_5);
        } else {
            EnPm_ChangeAnim(this, ENPM_ANIM_3);
        }
        ret = true;
    }
    return ret;
}

s32 func_80AF9AB0(EnPm* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    s32 ret = false;

    if (func_80AF8ED4(this, play, scheduleOutput, ACTORCAT_NPC, ACTOR_EN_TEST3)) {
        SubS_SetOfferMode(&this->unk_356, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
        this->unk_356 |= 0x20;
        this->unk_356 |= 0x9000;
        if (this->scheduleResult != 0) {
            this->unk_356 |= 0x800;
            EnPm_ChangeAnim(this, ENPM_ANIM_5);
        } else {
            EnPm_ChangeAnim(this, ENPM_ANIM_3);
        }
        ret = true;
    }
    return ret;
}

s32 func_80AF9B54(EnPm* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    s32 ret = false;

    if (func_80AF8ED4(this, play, scheduleOutput, ACTORCAT_NPC, ACTOR_EN_AL)) {
        SubS_SetOfferMode(&this->unk_356, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
        this->unk_356 |= 0x9000;
        this->unk_356 |= 0x20;
        if (this->scheduleResult != 0) {
            this->unk_356 |= 0x800;
            EnPm_ChangeAnim(this, ENPM_ANIM_5);
        } else {
            EnPm_ChangeAnim(this, ENPM_ANIM_3);
        }
        ret = true;
    }
    return ret;
}

s32 func_80AF9BF8(EnPm* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    s32 ret;

    this->actor.flags |= ACTOR_FLAG_ATTENTION_ENABLED;
    this->actor.attentionRangeType = ATTENTION_RANGE_0;
    this->unk_394 = PLAYER_IA_NONE;
    this->unk_356 = 0;
    this->unk_368 = 40.0f;

    switch (scheduleOutput->result) {
        case 16:
            ret = func_80AF9A0C(this, play, scheduleOutput);
            break;

        case 17:
            ret = func_80AF9AB0(this, play, scheduleOutput);
            break;

        case 28:
            ret = func_80AF9B54(this, play, scheduleOutput);
            break;

        case 24:
            ret = func_80AF94AC(this, play, scheduleOutput);
            break;

        case 29:
            ret = func_80AF95E8(this, play, scheduleOutput);
            break;

        case 1:
        case 2:
        case 10:
        case 11:
        case 12:
        case 13:
        case 32:
        case 33:
        case 34:
        case 35:
        case 36:
        case 37:
            ret = func_80AF9008(this, play, scheduleOutput);
            break;

        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 18:
        case 19:
        case 23:
        case 25:
        case 27:
            ret = func_80AF95E8(this, play, scheduleOutput);
            break;

        case 8:
            ret = func_80AF98A0(this, play, scheduleOutput);
            break;

        case 9:
        case 14:
        case 20:
        case 21:
        case 22:
            ret = func_80AF992C(this, play, scheduleOutput);
            break;

        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 48:
        case 49:
        case 50:
        case 51:
        case 52:
        case 53:
        case 54:
        case 55:
        case 56:
        case 57:
        case 58:
        case 59:
        case 60:
        case 61:
        case 62:
        case 63:
        case 64:
        case 65:
        case 66:
        case 67:
        case 68:
        case 69:
        case 70:
        case 71:
        case 72:
        case 73:
        case 74:
        case 75:
        case 76:
        case 77:
        case 78:
        case 79:
        case 80:
        case 81:
        case 82:
        case 83:
        case 84:
        case 85:
        case 86:
        case 87:
        case 88:
        case 89:
        case 90:
        case 91:
            ret = func_80AF91E8(this, play, scheduleOutput);
            break;

        default:
            ret = false;
            break;
    }
    return ret;
}

s32 func_80AF9D04(EnPm* this, PlayState* play) {
    EnDoor* door = EnPm_FindScheduleDoor(play, this->scheduleResult);
    Vec3f sp38;
    s32 pad;
    f32 temp;

    if (!SubS_InCsMode(play) && (this->timePathTimeSpeed != 0)) {
        if ((door != NULL) && (door->knobDoor.dyna.actor.update != NULL)) {
            if (((f32)this->unk_36E / this->unk_36C) <= 0.9f) {
                door->openTimer = this->unk_260;
            } else {
                door->openTimer = 0;
            }
        }
        this->unk_36E = CLAMP(this->unk_36E, 0, this->unk_36C);
        temp = Math_Vec3f_DistXZ(&this->unk_26C, &this->unk_278) / this->unk_36C;
        sp38.x = 0.0f;
        sp38.y = 0.0f;
        sp38.z = this->unk_36E * temp;
        Lib_Vec3f_TranslateAndRotateY(&this->unk_26C, this->actor.world.rot.y, &sp38, &this->actor.world.pos);
        this->unk_36E += this->timePathTimeSpeed;
        if (Animation_OnFrame(&this->skelAnime, 3.0f) || Animation_OnFrame(&this->skelAnime, 8.0f)) {
            Actor_PlaySfx(&this->actor, NA_SE_EV_POSTMAN_WALK);
        }
    }
    return false;
}

s32 func_80AF9E7C(EnPm* this, PlayState* play) {
    f32 knots[265];
    Vec3f sp70;
    Vec3f sp64;
    Vec3f timePathTargetPos;
    s32 sp54;
    s32 sp50;

    sp50 = 0;
    sp54 = 0;

    SubS_TimePathing_FillKnots(knots, SUBS_TIME_PATHING_ORDER, this->timePath->count + SUBS_TIME_PATHING_ORDER);
    if (!(this->unk_356 & 8)) {
        timePathTargetPos = gZeroVec3f;
        SubS_TimePathing_Update(this->timePath, &this->timePathProgress, &this->timePathElapsedTime,
                                this->timePathWaypointTime, this->timePathTotalTime, &this->timePathWaypoint, knots,
                                &timePathTargetPos, this->timePathTimeSpeed);
        SubS_TimePathing_ComputeInitialY(play, this->timePath, this->timePathWaypoint, &timePathTargetPos);
        this->actor.world.pos.y = timePathTargetPos.y;
        this->unk_356 |= 8;
    } else {
        timePathTargetPos = this->timePathTargetPos;
    }

    this->actor.world.pos.x = timePathTargetPos.x;
    this->actor.world.pos.z = timePathTargetPos.z;

    if (SubS_InCsMode(play)) {
        sp54 = this->timePathElapsedTime;
        sp50 = this->timePathWaypoint;
        timePathTargetPos = this->actor.world.pos;
    }

    this->timePathTargetPos = gZeroVec3f;

    if (SubS_TimePathing_Update(this->timePath, &this->timePathProgress, &this->timePathElapsedTime,
                                this->timePathWaypointTime, this->timePathTotalTime, &this->timePathWaypoint, knots,
                                &this->timePathTargetPos, this->timePathTimeSpeed)) {
        this->unk_356 |= 0x10;
    } else {
        sp70 = this->actor.world.pos;
        sp64 = this->timePathTargetPos;
        this->actor.world.rot.y = Math_Vec3f_Yaw(&sp70, &sp64);
    }

    if (SubS_InCsMode(play)) {
        this->timePathElapsedTime = sp54;
        this->timePathWaypoint = sp50;
        this->timePathTargetPos = timePathTargetPos;
    } else if ((this->scheduleResult != 91) &&
               (Animation_OnFrame(&this->skelAnime, 3.0f) || Animation_OnFrame(&this->skelAnime, 8.0f))) {
        Actor_PlaySfx(&this->actor, NA_SE_EV_POSTMAN_WALK);
    }

    if ((this->unk_356 & 0x10) && (this->scheduleResult == 90)) {
        //! @bug Uses SET_WEEKEVENTREG instead of CHECK_WEEKEVENTREG
        if (!SET_WEEKEVENTREG(WEEKEVENTREG_89_40)) {
            SET_WEEKEVENTREG(WEEKEVENTREG_89_40);
        }
    }

    return false;
}

s32 func_80AFA170(EnPm* this, PlayState* play) {
    Vec3f sp34;
    Vec3f sp28;

    switch (this->scheduleResult) {
        case 28:
            if (CURRENT_TIME >= CLOCK_TIME(1, 39)) {
                SET_WEEKEVENTREG(WEEKEVENTREG_89_08);
            }
            FALLTHROUGH;
        case 16:
        case 17:
        case 18:
            if ((this->animIndex == ENPM_ANIM_5) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                EnPm_ChangeAnim(this, ENPM_ANIM_6);
                this->unk_36C = 40;
            } else if ((this->animIndex == ENPM_ANIM_6) && (DECR(this->unk_36C) == 0)) {
                this->unk_356 &= ~0x800;
                EnPm_ChangeAnim(this, ENPM_ANIM_4);
            }
            break;

        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 19:
            if ((this->animIndex == ENPM_ANIM_11) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                EnPm_ChangeAnim(this, ENPM_ANIM_4);
            }

            if ((this->animIndex == ENPM_ANIM_11) && Animation_OnFrame(&this->skelAnime, 8.0f)) {
                Actor_PlaySfx(&this->actor, NA_SE_EV_POSTMACHINE_HIT_OPEN);
            }

            if (this->scheduleResult == 19) {
                func_80AF8BA8(4);
            } else {
                func_80AF8BA8(this->scheduleResult - 3);
            }
            break;
    }

    if ((this->unk_268 != NULL) && (this->unk_268->update != NULL)) {
        Math_Vec3f_Copy(&sp34, &this->unk_268->world.pos);
        Math_Vec3f_Copy(&sp28, &this->actor.world.pos);
        this->actor.world.rot.y = Math_Vec3f_Yaw(&sp28, &sp34);
    }

    return true;
}

s32 func_80AFA334(EnPm* this, PlayState* play) {
    s16 temp_v0;

    switch (this->scheduleResult) {
        case 14:
        case 24:
            temp_v0 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
            if (ABS_ALT(temp_v0) < 0x4000) {
                SubS_SetOfferMode(&this->unk_356, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
            } else {
                SubS_SetOfferMode(&this->unk_356, SUBS_OFFER_MODE_NONE, SUBS_OFFER_MODE_MASK);
            }
            break;

        case 27:
            if (DECR(this->unk_36C) == 0) {
                Flags_SetSwitch(play, 1);
            }
            break;

        case 9:
        case 20:
        case 21:
        case 22:
            if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
                Actor_PlaySfx(&this->actor, NA_SE_VO_NP_SLEEP_OUT);
            }
            break;

        case 29:
            break;
    }

    return false;
}

void func_80AFA438(EnPm* this, PlayState* play) {
    switch (this->scheduleResult) {
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 16:
        case 17:
        case 18:
        case 28:
            func_80AFA170(this, play);
            break;

        case 1:
        case 2:
        case 10:
        case 11:
        case 12:
        case 13:
        case 32:
        case 33:
        case 34:
        case 35:
        case 36:
        case 37:
            func_80AF9D04(this, play);
            break;

        case 9:
        case 14:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 27:
        case 29:
            func_80AFA334(this, play);
            break;

        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 48:
        case 49:
        case 50:
        case 51:
        case 52:
        case 53:
        case 54:
        case 55:
        case 56:
        case 57:
        case 58:
        case 59:
        case 60:
        case 61:
        case 62:
        case 63:
        case 64:
        case 65:
        case 66:
        case 67:
        case 68:
        case 69:
        case 70:
        case 71:
        case 72:
        case 73:
        case 74:
        case 75:
        case 76:
        case 77:
        case 78:
        case 79:
        case 80:
        case 81:
        case 82:
        case 83:
        case 84:
        case 85:
        case 86:
        case 87:
        case 88:
        case 89:
        case 90:
        case 91:
            func_80AF9E7C(this, play);
            break;
    }

    Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 3, 0x2AA8);
}

void func_80AFA4D0(EnPm* this, PlayState* play) {
    static ScheduleScript* D_80AFB900[] = {
        D_80AFAD80, D_80AFB30C, D_80AFB3C0, D_80AFB3FC, D_80AFB41C,
    };
    u16 time = CURRENT_TIME;
    u16 sp3C = 0;
    ScheduleOutput scheduleOutput;

    this->timePathTimeSpeed = R_TIME_SPEED + ((void)0, gSaveContext.save.timeSpeedOffset);
    if (this->unk_38C != 0) {
        time = CURRENT_TIME - D_801F4E78;
        sp3C = CURRENT_TIME;
        gSaveContext.save.time = time;
    }

    if (!Schedule_RunScript(play, D_80AFB900[this->unk_38C], &scheduleOutput) ||
        ((this->scheduleResult != scheduleOutput.result) && !func_80AF9BF8(this, play, &scheduleOutput))) {
        this->actor.shape.shadowDraw = NULL;
        this->actor.flags &= ~ACTOR_FLAG_ATTENTION_ENABLED;
        scheduleOutput.result = 0;
    } else {
        this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        this->actor.flags |= ACTOR_FLAG_ATTENTION_ENABLED;
    }

    this->scheduleResult = scheduleOutput.result;
    this->unk_268 = func_80AF8040(this, play);
    func_80AFA438(this, play);
    if (this->unk_38C != 0) {
        gSaveContext.save.time = sp3C;
    }
}

void func_80AFA5FC(EnPm* this, PlayState* play) {
    s16 yaw;
    Vec3f sp38;
    Vec3f sp2C;

    if (MsgEvent_RunScript(&this->actor, play, this->msgScript, this->msgScriptCallback, &this->msgScriptPos)) {
        SubS_SetOfferMode(&this->unk_356, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
        this->unk_356 &= ~0x20;
        this->unk_356 |= 0x200;
        this->actor.child = NULL;
        this->unk_376 = 20;
        this->msgScriptPos = 0;
        this->actionFunc = func_80AFA4D0;
        return;
    }

    if ((this->scheduleResult != 9) && (this->scheduleResult != 14) && (this->scheduleResult != 16) &&
        (this->scheduleResult != 17) && (this->scheduleResult != 20) && (this->scheduleResult != 21) &&
        (this->scheduleResult != 22) && (this->scheduleResult != 24) && (this->scheduleResult != 25)) {
        if ((this->unk_268 != NULL) && (this->unk_268->update != NULL)) {
            Math_Vec3f_Copy(&sp38, &this->unk_268->world.pos);
            Math_Vec3f_Copy(&sp2C, &this->actor.world.pos);
            yaw = Math_Vec3f_Yaw(&sp2C, &sp38);
            Math_ApproachS(&this->actor.shape.rot.y, yaw, 4, 0x2AA8);
        }
    }
}

void func_80AFA724(EnPm* this, PlayState* play) {
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 12.0f, 0.0f, UPDBGCHECKINFO_FLAG_4);
    if (Animation_OnFrame(&this->skelAnime, 3.0f) || Animation_OnFrame(&this->skelAnime, 8.0f)) {
        Actor_PlaySfx(&this->actor, NA_SE_EV_POSTMAN_WALK);
    }
}

void EnPm_Init(Actor* thisx, PlayState* play) {
    EnPm* this = (EnPm*)thisx;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 14.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &object_mm_Skel_0096E8, NULL, this->jointTable, this->morphTable,
                       OBJECT_MM_LIMB_MAX);
    this->animIndex = ENPM_ANIM_NONE;
    EnPm_ChangeAnim(this, ENPM_ANIM_0);
    Collider_InitAndSetCylinder(play, &this->colliderCylinder, &this->actor, &sCylinderInit);
    Collider_InitAndSetSphere(play, &this->colliderSphere, &this->actor, &sSphereInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &sColChkInfoInit);
    Actor_SetScale(&this->actor, 0.01f);
    this->unk_38C = func_80AF7B40();
    this->scheduleResult = 0;
    this->unk_356 = 0;
    this->actionFunc = func_80AFA4D0;
    this->actionFunc(this, play);
}

void EnPm_Destroy(Actor* thisx, PlayState* play) {
    EnPm* this = (EnPm*)thisx;

    Collider_DestroyCylinder(play, &this->colliderCylinder);
    Collider_DestroySphere(play, &this->colliderSphere);
}

void EnPm_Update(Actor* thisx, PlayState* play) {
    EnPm* this = (EnPm*)thisx;

    if (!func_80AF86F0(this, play) && func_80AF87C4(this, play)) {
        func_80AFA724(this, play);
        EnPm_UpdateSkelAnime(this);
        func_80AF8AC8(this);
    } else {
        this->actionFunc(this, play);
        func_80AF7BAC(this);
        if (this->scheduleResult != 0) {
            func_80AF8DD4(this, play);
            EnPm_UpdateSkelAnime(this);
            func_80AF8AC8(this);
            SubS_Offer(&this->actor, play, this->unk_368, 30.0f, this->unk_394, this->unk_356 & SUBS_OFFER_MODE_MASK);
            Actor_MoveWithGravity(&this->actor);
            Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 12.0f, 0.0f, UPDBGCHECKINFO_FLAG_4);
            func_80AF7F68(this, play);
        }
    }
}

s32 EnPm_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx,
                          Gfx** gfx) {
    EnPm* this = (EnPm*)thisx;

    if (limbIndex == OBJECT_MM_LIMB_0F) {
        func_80AF8C68(this, play);
    }
    return false;
}

void EnPm_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    EnPm* this = (EnPm*)thisx;
    s32 pad;
    Vec3f sp2C;

    switch (limbIndex) {
        case OBJECT_MM_LIMB_0F:
            if (CutsceneManager_GetCurrentCsId() == CS_ID_NONE) {
                Matrix_MultVec3f(&gZeroVec3f, &this->actor.focus.pos);
                Math_Vec3s_Copy(&this->actor.focus.rot, &this->actor.world.rot);
            }
            if ((this->unk_356 & 0x8000) && !CHECK_WEEKEVENTREG(WEEKEVENTREG_90_04)) {
                func_80AF8890(this, gfx, 1);
            }
            break;

        case OBJECT_MM_LIMB_0B:
            if (this->unk_356 & 0x800) {
                func_80AF8890(this, gfx, 0);
            }
            break;

        case OBJECT_MM_LIMB_08:
            if ((this->scheduleResult == 9) || (this->scheduleResult == 20) || (this->scheduleResult == 21) ||
                (this->scheduleResult == 22)) {
                Matrix_MultVec3f(&gZeroVec3f, &sp2C);
                Math_Vec3f_ToVec3s(&this->colliderSphere.dim.worldSphere.center, &sp2C);
            } else if (this->scheduleResult == 24) {
                Matrix_MultVec3f(&gZeroVec3f, &sp2C);
                Math_Vec3f_ToVec3s(&this->colliderSphere.dim.worldSphere.center, &sp2C);
            }
            func_80AF8890(this, gfx, 2);
            break;

        default:
            break;
    }
}

void EnPm_TransformLimbDraw(PlayState* play, s32 limbIndex, Actor* thisx, Gfx** gfx) {
    EnPm* this = (EnPm*)thisx;
    s32 stepRot;
    s32 overrideRot;

    if (!(this->unk_356 & 0x200)) {
        if (this->unk_356 & 0x80) {
            overrideRot = true;
        } else {
            overrideRot = false;
        }
        stepRot = true;
    } else {
        overrideRot = false;
        stepRot = false;
    }

    if (limbIndex == OBJECT_MM_LIMB_0F) {
        SubS_UpdateLimb(this->unk_370 + 0x4000, this->unk_372 + this->actor.shape.rot.y + 0x4000, &this->unk_284,
                        &this->unk_290, stepRot, overrideRot);
        Matrix_Pop();
        Matrix_Translate(this->unk_284.x, this->unk_284.y, this->unk_284.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateYS(this->unk_290.y, MTXMODE_APPLY);
        Matrix_RotateXS(this->unk_290.x, MTXMODE_APPLY);
        Matrix_RotateZS(this->unk_290.z, MTXMODE_APPLY);
        Matrix_Push();
    }
}

void EnPm_Draw(Actor* thisx, PlayState* play) {
    static TexturePtr D_80AFB914[] = {
        object_mm_Tex_002950,
        object_mm_Tex_002750,
    };
    EnPm* this = (EnPm*)thisx;
    s32 pad;

    if (this->scheduleResult != 0) {
        Gfx_SetupDL25_Opa(play->state.gfxCtx);

        OPEN_DISPS(play->state.gfxCtx);

        Scene_SetRenderModeXlu(play, 0, 1);

        gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80AFB914[0]));

        POLY_OPA_DISP = SubS_DrawTransformFlex(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                               this->skelAnime.dListCount, EnPm_OverrideLimbDraw, EnPm_PostLimbDraw,
                                               EnPm_TransformLimbDraw, &this->actor, POLY_OPA_DISP);

        CLOSE_DISPS(play->state.gfxCtx);
    }
}
