/*
 * File: z_en_sth.c
 * Overlay: ovl_En_Sth
 * Description: Guy looking at moon in South Clock Town,
 *              And the Cured Swamp spiderhouse man who gives you Mask of Truth
 *              And the man who wants to buy Ocean Spiderhouse from you with rupees or Wallet
 */

#include "z_en_sth.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnSth*)thisx)

void EnSth_Init(Actor* thisx, PlayState* play);
void EnSth_Destroy(Actor* thisx, PlayState* play);
void EnSth_WaitForObject(Actor* thisx, PlayState* play);

void EnSth_DispairIdle(EnSth* this, PlayState* play);
void EnSth_HandleOceanSpiderhouseConversation(EnSth* this, PlayState* play);
void EnSth_OceanSpiderhouseIdle(EnSth* this, PlayState* play);
void EnSth_MoonLookingIdle(EnSth* this, PlayState* play);
void EnSth_DefaultIdle(EnSth* this, PlayState* play);
void EnSth_HandleSwampSpiderhouseConversation(EnSth* this, PlayState* play);
void EnSth_SwampSpiderhouseCuredIdle(EnSth* this, PlayState* play);
void EnSth_Update(Actor* thisx, PlayState* play);
void EnSth_Draw(Actor* thisx, PlayState* play);

ActorInit En_Sth_InitVars = {
    ACTOR_EN_STH,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnSth),
    (ActorFunc)EnSth_Init,
    (ActorFunc)EnSth_Destroy,
    (ActorFunc)EnSth_WaitForObject,
    (ActorFunc)NULL,
};

#include "overlays/ovl_En_Sth/ovl_En_Sth.c"

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_ENEMY,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 30, 40, 0, { 0, 0, 0 } },
};

typedef enum {
    /* 0x0 */ STH_ANIM_SIGNALLING,   // default, waving arms at you from telescope, OOT: cured happy animation
    /* 0x1 */ STH_ANIM_BENDING_DOWN, // default of second body
    /* 0x2 */ STH_ANIM_TALKING,
    /* 0x3 */ STH_ANIM_WAITING,
    /* 0x4 */ STH_ANIM_LOOK_UP,        // southclocktown, looking at moon
    /* 0x5 */ STH_ANIM_LOOKING_AROUND, // checking out ocean spiderhouse
    /* 0x6 */ STH_ANIM_BEGGING,        // wants to buy ocean house
    /* 0x7 */ STH_ANIM_DISPAIR,        // after buying ocean house, can be found at bottom of slide
    /* 0x8 */ STH_ANIM_START,          // set in init, not an actual index to the array
} EnSthAnimationIndexes;

static AnimationHeader* sAnimationInfo[] = {
    &gEnSthSignalingAnim, &gEnSthBendingDownAnim,  &gEnSthTalkingWithHandUpAnim,
    &gEnSthWaitingAnim,   &gEnSthLookUpAnim,       &gEnSthLookingAroundRestlesslyAnim,
    &gEnSthBeggingAnim,   &gEnSthPanicShakingAnim,
};

// three slightly different variants of "Only a little time left, oh goddess please save me"
static u16 sSthOceanspiderhouseDispairText[] = { 0x1144, 0x1145, 0x1146 };

static u16 sSthFirstOceanSpiderHouseGreetDialogue2[] = {
    0x1139, // I thought I heard noises... I'm glad I found it early
    0x113E, // I had no idea this place was here, perhaps it can keep me safe
    0x1143  // There's no time we have to hide!
};

static u16 sSthFirstOceanSpiderHouseGreetDialogue1[] = {
    0x1132, // I thought I heard some noise.. is this some sort of underground shelter?
    0x113A, // I had no idea there was a basement here..
    0x113F  // I heard loud noises.. I never thought I'd find a place like this..
};

static Vec3f sFocusOffset = { 700.0f, 400.0f, 0.0f };

// Sth is hardcoded to only use element [1].
static Color_RGB8 sShirtColors[] = {
    { 190, 110, 0 },   // darker orange
    { 0, 180, 110 },   // green
    { 0, 255, 80 },    // lime green
    { 255, 160, 60 },  // brighter orange
    { 190, 230, 250 }, // white
    { 240, 230, 120 }, // pale yellow
};

void EnSth_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnSth* this = THIS;
    s32 objectId;

    // this actor can draw two separate bodies that use different objects
    if (STH_GET_SWAMP_BODY(&this->actor)) {
        objectId = Object_GetIndex(&play->objectCtx, OBJECT_AHG);
    } else {
        objectId = Object_GetIndex(&play->objectCtx, OBJECT_STH);
    }
    this->mainObjectId = objectId;
    this->maskOfTruthObjectId = Object_GetIndex(&play->objectCtx, OBJECT_MASK_TRUTH);

    Actor_SetScale(&this->actor, 0.01f);
    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 36.0f);

    this->sthFlags = STH_FLAG_CLEAR;
    this->curAnimIndex = STH_ANIM_START;
    this->actor.terminalVelocity = -9.0f;
    this->actor.gravity = -1.0f;

    switch (STH_GET_TYPE(&this->actor)) {
        case STH_TYPE_UNUSED_1:
            if (play->actorCtx.flags & ACTORCTX_FLAG_1) {
                this->actor.flags |= (ACTOR_FLAG_10 | ACTOR_FLAG_20);
                this->actionFunc = EnSth_DefaultIdle;
            } else {
                Actor_Kill(&this->actor);
                return;
            }
            break;

        case STH_TYPE_SWAMP_SPIDERHOUSE_CURED:
            if (Inventory_GetSkullTokenCount(play->sceneId) >= STH_SWAMP_SPIDER_TOKENS_REQUIRED) {
                this->actionFunc = EnSth_SwampSpiderhouseCuredIdle;
            } else {
                Actor_Kill(&this->actor);
            }
            this->actor.textId = 0;
            if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_34_40) || !CHECK_WEEKEVENTREG(WEEKEVENTREG_RECEIVED_MASK_OF_TRUTH)) {
                this->sthFlags |= STH_FLAG_DRAW_TRUTH_MASK;
            }
            break;

        case STH_TYPE_MOON_LOOKING: // south clock town
            if ((gSaveContext.save.skullTokenCount & 0xFFFF) >= STH_OCEAN_SPIDER_TOKENS_REQUIRED) {
                Actor_Kill(&this->actor);
                return;
            }

            this->actionFunc = EnSth_MoonLookingIdle;
            this->sthFlags |= STH_FLAG_DISABLE_HEAD_TRACK;
            this->actor.targetMode = 3;
            this->actor.uncullZoneForward = 800.0f;
            break;

        case STH_TYPE_OCEAN_SPIDERHOUSE_GREETING:
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_13_20)) {
                Actor_Kill(&this->actor);
                return;
            }
            this->actor.textId = 0;
            this->actionFunc = EnSth_OceanSpiderhouseIdle;
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_13_80)) {
                this->sthFlags |= STH_FLAG_CURED;
            }
            break;
        case STH_TYPE_OCEAN_SPIDERHOUSE_SUFFERING:
            if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_13_20) ||
                (Inventory_GetSkullTokenCount(play->sceneId) < STH_OCEAN_SPIDER_TOKENS_REQUIRED)) {
                Actor_Kill(&this->actor);
                return;
            }
            this->actionFunc = EnSth_DispairIdle;
            this->actor.textId = 0;
            this->sthFlags |= STH_FLAG_DISABLE_HEAD_TRACK;
            break;

        default:
            this->actionFunc = EnSth_DefaultIdle;
            break;
    }
}

void EnSth_Destroy(Actor* thisx, PlayState* play) {
    EnSth* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

s32 EnSth_DetectSpeakingRange(EnSth* this, PlayState* play) {
    if ((this->actor.xzDistToPlayer < 100.0f) && Player_IsFacingActor(&this->actor, 0x3000, play) &&
        Actor_IsFacingPlayer(&this->actor, 0x2000)) {
        return true;
    } else {
        return false;
    }
}

void EnSth_SwitchAnimation(EnSth* this, s16 animIndex) {
    if ((animIndex >= 0) && (animIndex < ARRAY_COUNT(sAnimationInfo)) && (animIndex != this->curAnimIndex)) {
        Animation_Change(&this->skelAnime, sAnimationInfo[animIndex], 1.0f, 0.0f,
                         Animation_GetLastFrame(sAnimationInfo[animIndex]), ANIMMODE_LOOP, -5.0f);
        this->curAnimIndex = animIndex;
    }
}

void EnSth_GetInitialDispairText(EnSth* this, PlayState* play) {
    s32 day = CURRENT_DAY - 1;
    u16 nextTextId;

    if (day < 0) {
        day = 0;
    }
    nextTextId = sSthOceanspiderhouseDispairText[day];

    Message_StartTextbox(play, nextTextId, &this->actor);
}

void EnSth_HandleDispairConversation(EnSth* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);

    if ((Message_GetState(&play->msgCtx) == TEXT_STATE_5) && Message_ShouldAdvance(play)) {
        this->actionFunc = EnSth_DispairIdle;
        func_801477B4(play);
    }
}

void EnSth_DispairIdle(EnSth* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        EnSth_GetInitialDispairText(this, play);
        this->actionFunc = EnSth_HandleDispairConversation;
    } else if ((this->actor.xzDistToPlayer < 100.0f) && Player_IsFacingActor(&this->actor, 0x3000, play)) {
        func_800B8614(&this->actor, play, 110.0f);
    }
}

void EnSth_GetInitialOceanSpiderhouseText(EnSth* this, PlayState* play) {
    u16 nextTextId;
    s32 day = CURRENT_DAY - 1;

    if (day < 0) {
        day = 0;
    }

    if (this->sthFlags & STH_FLAG_CURED) {
        s32 pad;

        nextTextId = sSthFirstOceanSpiderHouseGreetDialogue2[day];
        if (day == 2) {
            EnSth_SwitchAnimation(this, STH_ANIM_LOOKING_AROUND);
        }
    } else {
        nextTextId = sSthFirstOceanSpiderHouseGreetDialogue1[day];
    }
    Message_StartTextbox(play, nextTextId, &this->actor);
}

void EnSth_PostOceanspiderhouseReward(EnSth* this, PlayState* play) {
    u16 nextTextId;

    SkelAnime_Update(&this->skelAnime);

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->actor.flags &= ~ACTOR_FLAG_10000;
        this->actionFunc = EnSth_HandleOceanSpiderhouseConversation;

        switch (STH_GI_ID(&this->actor)) {
            case GI_WALLET_ADULT:
            case GI_WALLET_GIANT:
                nextTextId = 0x1137; // I'm just glad it was something you needed
                break;

            case GI_RUPEE_SILVER:
                // unused code, as he only gives wallet, purple and red, silver is never assigned to STH_GI_ID
                nextTextId = 0x1138; // That's my life's fortune
                break;

            case GI_RUPEE_PURPLE:
                if (CHECK_WEEKEVENTREG(WEEKEVENTREG_RECEIVED_GIANTS_WALLET)) {
                    nextTextId = 0x113D; // That's my life's savings
                } else {
                    nextTextId = 0x113C; // That's my life's savings (2)
                }
                break;

            default:
                if (CHECK_WEEKEVENTREG(WEEKEVENTREG_RECEIVED_GIANTS_WALLET)) {
                    nextTextId = 0x1142; // Well, thats all I have on me
                } else {
                    nextTextId = 0x1141; // Well, thats all I have on me
                }
                break;
        }
        Message_StartTextbox(play, nextTextId, &this->actor);
    } else {
        func_800B8500(&this->actor, play, 1000.0f, 1000.0f, PLAYER_IA_MINUS1);
    }
}

void EnSth_GiveOceanspiderhouseReward(EnSth* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);

    if (Actor_HasParent(&this->actor, play)) {
        this->actor.parent = NULL;
        this->actionFunc = EnSth_PostOceanspiderhouseReward;
        this->actor.flags |= ACTOR_FLAG_10000;
        func_800B8500(&this->actor, play, 1000.0f, 1000.0f, PLAYER_IA_MINUS1);
        if (CURRENT_DAY == 3) {
            EnSth_SwitchAnimation(this, STH_ANIM_BEGGING);
        } else {
            EnSth_SwitchAnimation(this, STH_ANIM_WAITING);
        }
    } else {
        Actor_PickUp(&this->actor, play, STH_GI_ID(&this->actor), 10000.0f, 500.0f);
    }
}

void EnSth_HandleOceanSpiderhouseConversation(EnSth* this, PlayState* play) {
    s32 day = CURRENT_DAY - 1;

    if (day < 0) {
        day = 0;
    }

    if (this->curAnimIndex == STH_ANIM_BEGGING) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 0x1000, 0x200);
        this->actor.world.rot.y = this->actor.shape.rot.y;
    }

    SkelAnime_Update(&this->skelAnime);

    switch (Message_GetState(&play->msgCtx)) {
        case TEXT_STATE_5:
            if (Message_ShouldAdvance(play)) {
                switch (play->msgCtx.currentTextId) {
                    case 0x1134: // (does not exist)
                        func_80151938(play, play->msgCtx.currentTextId + 1);
                        break;

                    case 0x1132:                     // Heard noise, came in to see
                    case 0x113A:                     // Had no idea there was a basement here
                    case 0x113F:                     // Heard noise... I never thought I'd find a place like this
                        func_80151938(play, 0x1133); // did you find this place?
                        break;

                    case 0x1133:                     // did you find this place?
                        func_80151938(play, 0x1136); // I want to buy this place from you
                        EnSth_SwitchAnimation(this, STH_ANIM_BEGGING);
                        break;

                    case 0x1136: // I want to buy this house from you
                        SET_WEEKEVENTREG(WEEKEVENTREG_13_80);

                        switch (day) {
                            case 0: // first day
                                if (CHECK_WEEKEVENTREG(WEEKEVENTREG_RECEIVED_GIANTS_WALLET)) {
                                    STH_GI_ID(&this->actor) = GI_RUPEE_SILVER;
                                } else {
                                    SET_WEEKEVENTREG(WEEKEVENTREG_RECEIVED_GIANTS_WALLET);
                                    switch (CUR_UPG_VALUE(UPG_WALLET)) {
                                        case 0:
                                            STH_GI_ID(&this->actor) = GI_WALLET_ADULT;
                                            break;

                                        case 1:
                                            STH_GI_ID(&this->actor) = GI_WALLET_GIANT;
                                            break;
                                    }
                                }
                                break;

                            case 1: // second day
                                STH_GI_ID(&this->actor) = GI_RUPEE_PURPLE;
                                break;

                            default: // final day
                                STH_GI_ID(&this->actor) = GI_RUPEE_RED;
                                break;
                        }
                        func_801477B4(play);
                        this->actionFunc = EnSth_GiveOceanspiderhouseReward;
                        EnSth_GiveOceanspiderhouseReward(this, play);
                        break;

                    case 0x113C:                     // (Second day) I am giving you my life savings
                        func_80151938(play, 0x113B); // If only I had gotten here yesterday...
                        break;

                    case 0x1141:                     // (Final day) This is all I have
                        func_80151938(play, 0x1140); // If only I had gotten here two days ago...
                        EnSth_SwitchAnimation(this, STH_ANIM_WAITING);
                        break;

                    default:
                        this->actionFunc = EnSth_OceanSpiderhouseIdle;
                        func_801477B4(play);
                        this->sthFlags |= STH_FLAG_CURED;
                        break;
                }
            }
            break;

        case TEXT_STATE_CLOSING:
            this->actionFunc = EnSth_OceanSpiderhouseIdle;
            this->sthFlags |= STH_FLAG_CURED;
            break;
    }
}

void EnSth_OceanSpiderhouseIdle(EnSth* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        EnSth_GetInitialOceanSpiderhouseText(this, play);
        this->actionFunc = EnSth_HandleOceanSpiderhouseConversation;
    } else if (EnSth_DetectSpeakingRange(this, play)) {
        func_800B8614(&this->actor, play, 110.0f);
    }
}

void EnSth_HandleMoonLookingConversation(EnSth* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);

    if ((Message_GetState(&play->msgCtx) == TEXT_STATE_5) && Message_ShouldAdvance(play)) {
        this->actionFunc = EnSth_MoonLookingIdle;
        func_801477B4(play);
    }
    this->headRot.x = -0x1388;
}

void EnSth_MoonLookingIdle(EnSth* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->actionFunc = EnSth_HandleMoonLookingConversation;
    } else if (EnSth_DetectSpeakingRange(this, play) || this->actor.isTargeted) {
        if ((gSaveContext.save.time >= CLOCK_TIME(6, 0)) && (gSaveContext.save.time <= CLOCK_TIME(18, 0))) {
            this->actor.textId = 0x1130; // Huh? The Moon...
        } else {
            this->actor.textId = 0x1131; // (The Moon) gotten bigger again
        }
        func_800B8614(&this->actor, play, 110.0f);
    }
    this->headRot.x = -0x1388;
}

// used by type: STH_TYPE_UNUSED_1 and undefined types
void EnSth_DefaultIdle(EnSth* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
}

void EnSth_GetInitialSwampSpiderhouseText(EnSth* this, PlayState* play) {
    u16 nextTextId;

    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_34_10)) {
        nextTextId = 0x903; // (does not exist)
        EnSth_SwitchAnimation(this, STH_ANIM_TALKING);
    } else if (CHECK_WEEKEVENTREG(WEEKEVENTREG_34_20)) {
        nextTextId = 0x90F; // (does not exist)
        EnSth_SwitchAnimation(this, STH_ANIM_TALKING);
    } else if (CHECK_WEEKEVENTREG(WEEKEVENTREG_34_40)) {
        if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_RECEIVED_MASK_OF_TRUTH)) {
            nextTextId = 0x91B; // As soon as I calm down, getting rid of it
        } else {
            nextTextId = 0x918; // I've had enough of this, going home
        }
        EnSth_SwitchAnimation(this, STH_ANIM_TALKING);
    } else if (Inventory_GetSkullTokenCount(play->sceneId) >= STH_SWAMP_SPIDER_TOKENS_REQUIRED) {
        if (INV_CONTENT(ITEM_MASK_TRUTH) == ITEM_MASK_TRUTH) {
            this->sthFlags |= STH_FLAG_SAVED;
            nextTextId = 0x919; // I've been saved!
        } else {
            nextTextId = 0x916; // I've been saved! (Duplicate)
        }
    } else if (CHECK_WEEKEVENTREG(WEEKEVENTREG_34_02)) {
        nextTextId = 0x8FF; // (does not exist)
    } else {
        nextTextId = 0x8FC; // (does not exist)
        SET_WEEKEVENTREG(WEEKEVENTREG_34_02);
    }

    Message_StartTextbox(play, nextTextId, &this->actor);
}

void EnSth_PostSwampSpiderhouseGiveMask(EnSth* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->actionFunc = EnSth_HandleSwampSpiderhouseConversation;
        SET_WEEKEVENTREG(WEEKEVENTREG_34_40);
        Message_StartTextbox(play, 0x918, &this->actor); // I've had enough of this, going home
    } else {
        func_800B8500(&this->actor, play, 1000.0f, 1000.0f, PLAYER_IA_MINUS1);
    }
}

void EnSth_SwampSpiderhouseGiveMask(EnSth* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);

    if (Actor_HasParent(&this->actor, play)) {
        this->actor.parent = NULL;
        this->actionFunc = EnSth_PostSwampSpiderhouseGiveMask;
        this->actor.flags |= ACTOR_FLAG_10000;
        func_800B8500(&this->actor, play, 1000.0f, 1000.0f, PLAYER_IA_MINUS1);
    } else {
        this->sthFlags &= ~STH_FLAG_DRAW_TRUTH_MASK;
        SET_WEEKEVENTREG(WEEKEVENTREG_RECEIVED_MASK_OF_TRUTH);
        Actor_PickUp(&this->actor, play, GI_MASK_TRUTH, 10000.0f, 50.0f);
    }
}

void EnSth_HandleSwampSpiderhouseConversation(EnSth* this, PlayState* play) {
    s32 pad;

    SkelAnime_Update(&this->skelAnime);

    if ((Message_GetState(&play->msgCtx) == TEXT_STATE_5) && Message_ShouldAdvance(play)) {
        switch (play->msgCtx.currentTextId) {
            case 0x90C: // (does not exist)
                EnSth_SwitchAnimation(this, STH_ANIM_TALKING);
                func_80151938(play, play->msgCtx.currentTextId + 1);
                break;

            case 0x916: // I have been saved! I thought I was doomed
            case 0x919: // I have been saved! I thought I was doomed (duplicate)
                EnSth_SwitchAnimation(this, STH_ANIM_WAITING);
                func_80151938(play, play->msgCtx.currentTextId + 1);
                break;

            case 0x8FC: // (does not exist)
            case 0x8FD: // (does not exist)
            case 0x900: // (does not exist)
            case 0x90A: // (does not exist)
            case 0x90D: // (does not exist)
                func_80151938(play, play->msgCtx.currentTextId + 1);
                break;

            case 0x901: // (does not exist)
            case 0x90B: // (does not exist)
            case 0x917: // Someone gave me this mask and said it would make me rich, Take it
                func_801477B4(play);
                this->actionFunc = EnSth_SwampSpiderhouseGiveMask;
                EnSth_SwampSpiderhouseGiveMask(this, play);
                break;

            case 0x91A: // Someone gave me this mask and said it would make me rich, getting rid of it
                // why is this two flags? is it some.. started dialogue, ended dialogue thing?
                SET_WEEKEVENTREG(WEEKEVENTREG_34_40);
                CLEAR_WEEKEVENTREG(WEEKEVENTREG_RECEIVED_MASK_OF_TRUTH);

            case 0x902: // (does not exist)
            case 0x903: // (does not exist)
            case 0x90E: // (does not exist)
            case 0x90F: // (does not exist)
            case 0x918: // I have had enough, going home
            case 0x91B: // As soon as I calm down, getting rid of it
                EnSth_SwitchAnimation(this, STH_ANIM_WAITING);

            default:
                this->actor.flags &= ~ACTOR_FLAG_10000;
                func_801477B4(play);
                this->actionFunc = EnSth_SwampSpiderhouseCuredIdle;
                break;
        }
    }
}

void EnSth_SwampSpiderhouseCuredIdle(EnSth* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        EnSth_GetInitialSwampSpiderhouseText(this, play);
        this->actionFunc = EnSth_HandleSwampSpiderhouseConversation;
    } else if (EnSth_DetectSpeakingRange(this, play)) {
        this->actor.textId = 0;
        func_800B8614(&this->actor, play, 110.0f);
    }
}

void EnSth_OceanSpiderhouseWaitForTokens(Actor* thisx, PlayState* play) {
    EnSth* this = THIS;

    if (Inventory_GetSkullTokenCount(play->sceneId) >= STH_OCEAN_SPIDER_TOKENS_REQUIRED) {
        this->actor.update = EnSth_Update;
        this->actor.draw = EnSth_Draw;
        this->actor.flags |= ACTOR_FLAG_1;
    }
}

/**
 * Dual object actors have to wait for the object to finish loading,
 * this dev chose to use a temporary update instead of temporary acitonFunc
 */
void EnSth_WaitForObject(Actor* thisx, PlayState* play) {
    s32 pad;
    EnSth* this = THIS;

    if (Object_IsLoaded(&play->objectCtx, this->mainObjectId)) {
        this->actor.objBankIndex = this->mainObjectId;
        Actor_SetObjectDependency(play, &this->actor);

        if (STH_GET_SWAMP_BODY(&this->actor)) {
            // as this version is unused, we don't know what scene they were meant for
            // except: WEEKEVENTREG_34_40 is used in swamp spiderhouse
            SkelAnime_InitFlex(play, &this->skelAnime, &gAhgSkel, &gEnSthBendingDownAnim, this->jointTable,
                               this->morphTable, AHG_LIMB_MAX);
            Animation_PlayLoop(&this->skelAnime, &gEnSthBendingDownAnim);
            this->curAnimIndex = STH_ANIM_BENDING_DOWN;
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_34_10) || CHECK_WEEKEVENTREG(WEEKEVENTREG_34_20) ||
                CHECK_WEEKEVENTREG(WEEKEVENTREG_34_40) ||
                (Inventory_GetSkullTokenCount(play->sceneId) >= STH_SWAMP_SPIDER_TOKENS_REQUIRED)) {
                EnSth_SwitchAnimation(this, STH_ANIM_WAITING);
            }
        } else {
            SkelAnime_InitFlex(play, &this->skelAnime, &gSthSkel, &gEnSthSignalingAnim, this->jointTable,
                               this->morphTable, STH_LIMB_MAX);
            Animation_PlayLoop(&this->skelAnime, &gEnSthSignalingAnim);
        }

        this->actor.update = EnSth_Update;
        this->actor.draw = EnSth_Draw;

        switch (STH_GET_TYPE(&this->actor)) {
            case STH_TYPE_MOON_LOOKING:
                EnSth_SwitchAnimation(this, STH_ANIM_LOOK_UP);
                break;

            case STH_TYPE_OCEAN_SPIDERHOUSE_GREETING:
                if (CHECK_WEEKEVENTREG(WEEKEVENTREG_13_80)) {
                    EnSth_SwitchAnimation(this, STH_ANIM_LOOKING_AROUND);
                } else {
                    EnSth_SwitchAnimation(this, STH_ANIM_LOOKING_AROUND);
                }
                break;

            case STH_TYPE_OCEAN_SPIDERHOUSE_SUFFERING:
                EnSth_SwitchAnimation(this, STH_ANIM_DISPAIR);
                break;
        }

        // not ready to appear yet
        if ((STH_GET_TYPE(&this->actor) == STH_TYPE_OCEAN_SPIDERHOUSE_GREETING) &&
            (Inventory_GetSkullTokenCount(play->sceneId) < STH_OCEAN_SPIDER_TOKENS_REQUIRED)) {
            this->actor.update = EnSth_OceanSpiderhouseWaitForTokens;
            this->actor.draw = NULL;
            this->actor.flags &= ~ACTOR_FLAG_1;
        }
    }
}

void EnSth_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    EnSth* this = THIS;

    Actor_MoveWithGravity(&this->actor);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    Actor_UpdateBgCheckInfo(play, &this->actor, 0.0f, 0.0f, 0.0f, 4);

    this->actionFunc(this, play);

    if (EnSth_DetectSpeakingRange(this, play) && !(this->sthFlags & STH_FLAG_DISABLE_HEAD_TRACK) &&
        (this->curAnimIndex != STH_ANIM_LOOKING_AROUND)) {
        Vec3s torsoRot;
        torsoRot.x = torsoRot.y = torsoRot.z = 0; // this should block torso rot from working

        Actor_TrackPlayer(play, &this->actor, &this->headRot, &torsoRot, this->actor.focus.pos);
    } else {
        Math_SmoothStepToS(&this->headRot.x, 0, 6, 6200, 100);
        Math_SmoothStepToS(&this->headRot.y, 0, 6, 6200, 100);
    }
}

s32 EnSth_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    s32 pad;
    EnSth* this = THIS;

    if (limbIndex == STH_LIMB_HEAD) {
        rot->x += this->headRot.y;
        rot->z += this->headRot.x;

        // object_sth body has no head by default, forced here from overlay data
        *dList = gEnSthHeadDL;
    }

    if ((limbIndex == STH_LIMB_CHEST) || (limbIndex == STH_LIMB_LEFT_FOREARM) ||
        (limbIndex == STH_LIMB_RIGHT_FOREARM)) {
        rot->y += (s16)(Math_SinS(play->state.frames * ((limbIndex * 50) + 0x814)) * 200.0f);
        rot->z += (s16)(Math_CosS(play->state.frames * ((limbIndex * 50) + 0x940)) * 200.0f);
    }

    return false;
}

void EnSth_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnSth* this = THIS;

    if (limbIndex == STH_LIMB_HEAD) {
        s32 pad;

        Matrix_MultVec3f(&sFocusOffset, &this->actor.focus.pos);

        if (!STH_GET_SWAMP_BODY(&this->actor)) {
            OPEN_DISPS(play->state.gfxCtx);

            gSPDisplayList(POLY_OPA_DISP++, gEnSthExtraHairDL);

            CLOSE_DISPS(play->state.gfxCtx);
        } else {
            OPEN_DISPS(play->state.gfxCtx);

            if (this->sthFlags & STH_FLAG_DRAW_TRUTH_MASK) {
                if (Object_IsLoaded(&play->objectCtx, this->maskOfTruthObjectId)) {
                    Matrix_Push();
                    Matrix_RotateZS(0x3A98, MTXMODE_APPLY);
                    Matrix_Translate(0.0f, 190.0f, 0.0f, MTXMODE_APPLY);

                    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPSegment(POLY_OPA_DISP++, 0x0A, play->objectCtx.status[this->maskOfTruthObjectId].segment);
                    gSPDisplayList(POLY_OPA_DISP++, object_mask_truth_DL_0001A0);

                    Matrix_Pop();
                }
            }

            CLOSE_DISPS(play->state.gfxCtx);
        }
    }
}

void EnSth_Draw(Actor* thisx, PlayState* play) {
    s32 pad;
    EnSth* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08,
               Gfx_EnvColor(play->state.gfxCtx, sShirtColors[1].r, sShirtColors[1].g, sShirtColors[1].b, 255));
    gSPSegment(POLY_OPA_DISP++, 0x09, Gfx_EnvColor(play->state.gfxCtx, 90, 110, 130, 255));

    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnSth_OverrideLimbDraw, EnSth_PostLimbDraw, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}
