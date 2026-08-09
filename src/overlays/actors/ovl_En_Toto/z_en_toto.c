/*
 * File: z_en_toto.c
 * Overlay: ovl_En_Toto
 * Description: Toto
 */

#include "z_en_toto.h"

#define FLAGS (ACTOR_FLAG_ATTENTION_ENABLED | ACTOR_FLAG_FRIENDLY)

#define ENTOTO_FINISHED_WIND_FISH (CHECK_WEEKEVENTREG(WEEKEVENTREG_HELPED_GORMAN_DAY_1) || CHECK_WEEKEVENTREG(WEEKEVENTREG_HELPED_GORMAN_DAY_2))

void EnToto_Init(Actor* thisx, PlayState* play);
void EnToto_Destroy(Actor* thisx, PlayState* play);
void EnToto_Update(Actor* thisx, PlayState* play);
void EnToto_Draw(Actor* thisx, PlayState* play);

void EnToto_SetupAction_Idle(EnToto* this, PlayState* play);
void EnToto_Action_Idle(EnToto* this, PlayState* play);
void EnToto_Action_SoundCheck(EnToto* this, PlayState* play);
void EnToto_SetupAction_Talk(EnToto* this, PlayState* play);
void EnToto_Action_Talk(EnToto* this, PlayState* play);
void EnToto_SetupAction_SoundCheck(EnToto* this, PlayState* play);
s32 EnToto_SetupTalk_ReturnTrue(EnToto* this, PlayState* play);
s32 EnToto_SetupTalk_DoNothing(EnToto* this, PlayState* play);
s32 EnToto_HandleTalk_AfterChoice(EnToto* this, PlayState* play);
s32 EnToto_SetupTalk_NextMessage(EnToto* this, PlayState* play);
s32 EnToto_SetupTalk_SetNextMessageTimer(EnToto* this, PlayState* play);
s32 EnToto_HandleTalk_Wait(EnToto* this, PlayState* play);
s32 EnToto_SetupTalk_StartAdditionalCutscene(EnToto* this, PlayState* play);
s32 EnToto_HandleTalk_StartCutscene(EnToto* this, PlayState* play);
s32 EnToto_HandleTalk_Event(EnToto* this, PlayState* play);
s32 EnToto_HandleTalk_Closing(EnToto* this, PlayState* play);
s32 EnToto_HandleTalk_Choice(EnToto* this, PlayState* play);
s32 EnToto_HandleTalk_SoundCheck_WaitAdvanceText(EnToto* this, PlayState* play);
s32 EnToto_SetupTalk_InitSoundCheck(EnToto* this, PlayState* play);
s32 EnToto_HandleTalk_SoundCheck_MovePlayerToStage(EnToto* this, PlayState* play);
s32 EnToto_HandleTalk_SoundCheck_WaitForPromptTextbox(EnToto* this, PlayState* play);
s32 EnToto_SetupTalk_StopCutsceneAndResetTimer(EnToto* this, PlayState* play);
s32 EnToto_HandleTalk_SoundCheck_WaitForPlayerToEnterSpotlight(EnToto* this, PlayState* play);
s32 EnToto_SetupTalk_InitWindFishOcarinaStaff(EnToto* this, PlayState* play);
s32 EnToto_HandleTalk_SoundCheck_SetPlayedFlags(EnToto* this, PlayState* play);
s32 EnToto_SetupTalk_InitWindFishPlayback(EnToto* this, PlayState* play);
s32 EnToto_SetupTalk_StartWindFishPlayback(EnToto* this, PlayState* play);
s32 EnToto_HandleTalk_SoundCheck_EndWindFishCutscene(EnToto* this, PlayState* play);
s32 EnToto_HandleTalk_SetupMayorsResidence(EnToto* this, PlayState* play);
s32 EnToto_ShouldTriggerCutscene(EnToto* this, PlayState* play);
s32 EnToto_NextTalkStateTriggersCutscene(EnToto* this, PlayState* play);

ActorProfile En_Toto_Profile = {
    /**/ ACTOR_EN_TOTO,
    /**/ ACTORCAT_NPC,
    /**/ FLAGS,
    /**/ OBJECT_ZM,
    /**/ sizeof(EnToto),
    /**/ EnToto_Init,
    /**/ EnToto_Destroy,
    /**/ EnToto_Update,
    /**/ EnToto_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COL_MATERIAL_METAL,
        AT_NONE,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEM_MATERIAL_UNK2,
        { 0x00100000, 0x00, 0x00 },
        { 0x01000202, 0x00, 0x00 },
        ATELEM_NONE | ATELEM_SFX_NORMAL,
        ACELEM_ON | ACELEM_HOOKABLE,
        OCELEM_ON,
    },
    { 20, 60, 0, { 0, 0, 0 } },
};

static EnTotoActionFunc sActionSetupFuncs[] = {
    EnToto_SetupAction_Idle,
    EnToto_SetupAction_Talk,
    EnToto_SetupAction_SoundCheck,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_U8(attentionRangeType, ATTENTION_RANGE_1, ICHAIN_STOP),
};

static EnTotoSpeakData sSpeakData1[] = {
    { 0, 0, 0x2B21 },               // "Are you going to play for us again?"
    { 3, 2, 0 },                    //                                          (Wait for Sound Check)
    { 0, 0, 0x2B23 },               // "We were scheduled to do a show..."      (Sound Check, first time)
    { 2, 1, 0x2B24 },               // "Could you help me with a performance?"
    { 4, 0, 0x2B25 },               // "Oh, that's too bad."
    { 3, 2, 0 },                    //                                          (Wait for Sound Check)
    { 4, 0, 0x2B25 },               // "Oh, that's too bad."
    { 16, 0, 0x2A94 },              // "Are the fins damp lately?"
    { 0, 0, 0x2A95 },               // "What? Mikau???"                     (Mayor's Residence as Zora, first time)
    { 4, 0, 0x2A96 },               // "You look so much like him..."       (Mayor's Residence as Zora, first time)
    { 4, 0, 0x2A97 },               // "With the ocean the way it is..."    (Mayor's Residence as Zora)
    { 0, 0, 0x2A98 },               // "That's the greeting used among us Zoras."
    { 0, 0, 0x2A99 },               // "I am Toto, manager of the band..."
    { 4, 0, 0x2A9A },               // "The Indigo-Go's is..."
    { 4, 0, 0x2A9B },               // "Canceling the show isn't something I want to do at all..."
    { 0, 0, 0x2AE1 },               // "Are the fins damp lately?"          (Mayor's Residence as Deku)
    { 0, 0, 0x2AE2 },               // Oh. That's the greeting used among us Zora." (          ...Deku)
    { 4, 0, 0x2AE3 },               // "Where's your momma, sonny? Huh?"    (Mayor's Residence as Deku)
    { 4, 0, 0x2AE4 },               // "Once you get older, come see us perform!"   (          ...Deku)
};

typedef enum EnTotoAnimation {
    /* 0 */ ENTOTO_ANIM_TALK_SITTING,
    /* 1 */ ENTOTO_ANIM_MOVE_CANE_BEHIND_HEAD,
    /* 2 */ ENTOTO_ANIM_TAP_HEAD_WITH_CANE,
    /* 3 */ ENTOTO_ANIM_MOVE_CANE_TO_FLOOR,
    /* 4 */ ENTOTO_ANIM_MAX
} EnTotoAnimation;

static AnimationHeader* sTalkSittingAnimations[ENTOTO_ANIM_MAX] = {
    &gTotoTalkSittingAnim, // ENTOTO_ANIM_TALK_SITTING
    &gTotoMoveCaneBehindHeadAnim, // ENTOTO_ANIM_MOVE_CANE_BEHIND_HEAD
    &gTotoTapHeadWithCaneAnim, // ENTOTO_ANIM_TAP_HEAD_WITH_CANE
    &gTotoMoveCaneBackDownAnim, // ENTOTO_ANIM_MOVE_CANE_TO_FLOOR
};

static EnTotoSpeakData sSpeakData2[] = {
    { 5,  0, 0 },  
    { 6, 20, 0 }, 
    { 7,  0, 0 },  
    { 8,  9, 0 },  
    { 9, 10, 0 },
    { 1,  0, 0 },
    { 10, 0, 0 },
    { 11, 0, 0 },
    { 12, 0, 0 }, 
    { 13, 0, 0 }, 
    { 15, 0, 0 }, 
    { 17, 1, 0 },
    { 17, 0, 0 },
    { 5,  0, 0 },
    { 6, 20, 0 }, 
    { 8,  5, 0 },  
    { 12, 0, 0 }, 
    { 13, 0, 0 }, 
    { 14, 20, 0x2B22 },             // "I wanted you, too, to hear Lulu's voice on this stage."
    { 1,  0, 0 },  
    { 17, 0, 0 },
};

/*
    0: Goron
    1: Zora
    2: Deku
    3: Human
*/
static EnTotoSpotlight sSpotlightList[] = {
    { 0x2B2F, 0x2B30, 0x2B31, { 0xFF96, 0x0016, 0xFE16 } },
    { 0x2B26, 0x2B27, 0x2B28, { 0x0072, 0x0016, 0xFE3C } },
    { 0x2B29, 0x2B2A, 0x2B2B, { 0xFF67, 0x0016, 0xFE6E } },
    { 0x2B2C, 0x2B2D, 0x2B2E, { 0xFFF1, 0x0016, 0xFE74 } },
};

static Vec3s sPlayerOverrideInputPosList[] = {
    { -186, -8, -192 },
    { -223, -3, -252 },
    { -156, 22, -386 },
};

static u16 sOcarinaActionWindFishPrompts[] = {
    OCARINA_ACTION_PROMPT_WIND_FISH_HUMAN,
    OCARINA_ACTION_PROMPT_WIND_FISH_GORON,
    OCARINA_ACTION_PROMPT_WIND_FISH_ZORA,
    OCARINA_ACTION_PROMPT_WIND_FISH_DEKU,
};

static u8 D_80BA5128[] = { 8, 4, 2, 1 }; // Spotlight index to form flag

/* 
    Functions called once
*/
static EnTotoTalkFunc sTalkStateSetupFuncs[] = {
    EnToto_SetupTalk_NextMessage, 
    EnToto_SetupTalk_DoNothing, 
    EnToto_SetupTalk_NextMessage, 
    EnToto_SetupTalk_NextMessage, 
    EnToto_SetupTalk_NextMessage, 
    EnToto_SetupTalk_DoNothing,
    EnToto_SetupTalk_InitSoundCheck,
    EnToto_SetupTalk_DoNothing,
    EnToto_SetupTalk_StopCutsceneAndResetTimer,
    EnToto_SetupTalk_SetNextMessageTimer, 
    EnToto_SetupTalk_StartAdditionalCutscene, 
    EnToto_SetupTalk_InitWindFishOcarinaStaff,
    EnToto_SetupTalk_InitWindFishPlayback, 
    EnToto_SetupTalk_StartWindFishPlayback, 
    EnToto_SetupTalk_SetNextMessageTimer, 
    EnToto_SetupTalk_StartAdditionalCutscene, 
    EnToto_SetupTalk_NextMessage, 
    EnToto_SetupTalk_ReturnTrue,
};

/*
    Functions called repeatedly until text pointer changed
    Similar to EnTest3 (Kafei)'s sTalkStateHandlerFuncs
*/
static EnTotoTalkFunc sTalkStateHandlerFuncs[] = {
    EnToto_HandleTalk_Event, 
    EnToto_HandleTalk_Closing, 
    EnToto_HandleTalk_Choice, 
    EnToto_HandleTalk_AfterChoice, 
    EnToto_HandleTalk_AfterChoice, 
    EnToto_HandleTalk_StartCutscene,
    EnToto_HandleTalk_SoundCheck_MovePlayerToStage, 
    EnToto_HandleTalk_SoundCheck_WaitForPromptTextbox,
    EnToto_HandleTalk_SoundCheck_WaitForPlayerToEnterSpotlight, 
    EnToto_HandleTalk_SoundCheck_WaitAdvanceText, 
    EnToto_HandleTalk_StartCutscene, 
    EnToto_HandleTalk_SoundCheck_SetPlayedFlags,
    EnToto_HandleTalk_StartCutscene, 
    EnToto_HandleTalk_SoundCheck_EndWindFishCutscene, 
    EnToto_HandleTalk_Wait, 
    EnToto_HandleTalk_StartCutscene, 
    EnToto_HandleTalk_SetupMayorsResidence,
};

static EnTotoActionFunc sActionHandlerFuncs[] = {
    EnToto_Action_Idle,
    EnToto_Action_Talk,
    EnToto_Action_SoundCheck,
};

/*

*/

void EnToto_SetMainAction(EnToto* this, PlayState* play, s32 index) {
    this->shouldPlaySoundCheckCompleteCutscene = false;
    this->actionFuncIndex = index;
    sActionSetupFuncs[this->actionFuncIndex](this, play);
}

void EnToto_Init(Actor* thisx, PlayState* play) {
    EnToto* this = (EnToto*)thisx;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    if ((play->sceneId == SCENE_MILK_BAR) && (CURRENT_TIME >= CLOCK_TIME(6, 0)) &&
        (CURRENT_TIME < CLOCK_TIME(21, 30))) {
        Actor_Kill(&this->actor);
        return;
    }
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 30.0f);
    this->actor.bgCheckFlags |= BGCHECKFLAG_PLAYER_400;
    SkelAnime_InitFlex(play, &this->skelAnime, &gTotoSkel,
                       ((play->sceneId == SCENE_SONCHONOIE) ? &gTotoIdleSittingAnim : &gTotoIdleStandingAnim),
                       this->jointTable, this->morphTable, OBJECT_ZM_LIMB_MAX);
    EnToto_SetMainAction(this, play, 0);
    this->actor.shape.rot.x = 0;
}

void EnToto_Destroy(Actor* thisx, PlayState* play) {
    EnToto* this = (EnToto*)thisx;

    Collider_DestroyCylinder(play, &this->collider);
}

void EnToto_UpdateAnimation(EnToto* this, PlayState* play) {
    if (SkelAnime_Update(&this->skelAnime) && (this->actionFuncIndex == 1) &&   // If animation is finished and is talking to player
        (this->skelAnime.animation != &gTotoWaveHelloAnim)) {                // And animation is not Greeting Link
        if ((play->msgCtx.currentTextId != 0x2A98) && (play->msgCtx.currentTextId != 0x2A99)) { // First 2 text boxes after Mayor's Residence greeting ("That's the greeting used among us...", "Oh, forgive me...")
            if ((this->animIndex & 1) || (Rand_ZeroOne() > 0.5f)) {
                this->animIndex = (this->animIndex + 1) & 3;        // Tap on head with cane (50% chance)
            }
        }
        Animation_PlayOnce(&this->skelAnime, sTalkSittingAnimations[this->animIndex]);
    }
    FaceChange_UpdateBlinkingNonHuman(&this->faceChange, 20, 80, 3);
}

void EnToto_SetupAction_Idle(EnToto* this, PlayState* play) {
    AnimationHeader* anim = &gTotoIdleStandingAnim;

    if (play->sceneId == SCENE_SONCHONOIE) {
        anim = &gTotoIdleSittingAnim;
    }
    Animation_MorphToLoop(&this->skelAnime, anim, -4.0f);
}

s32 EnToto_IsFacingPlayer(EnToto* this, s16 angle) {
    s16 diff;

    diff = this->actor.yawTowardsPlayer - this->actor.home.rot.y;
    if (ABS_ALT(diff) < angle) {
        return 1;
    }
    return 0;
}

/*
    Wait for player to talk
*/
void EnToto_Action_Idle(EnToto* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    EnToto_UpdateAnimation(this, play); // Update animation
    if (Actor_TalkOfferAccepted(&this->actor, &play->state)) {
        EnToto_SetMainAction(this, play, 1);

        if (play->sceneId != SCENE_SONCHONOIE) {
            Flags_SetSwitch(play, ENTOTO_GET_ZORA_SPOKEN_FLAG(&this->actor));
        } else if (player->transformation == PLAYER_FORM_DEKU) {
            Flags_SetSwitch(play, ENTOTO_GET_DEKU_SPOKEN_FLAG(&this->actor));
        }
        this->shouldCancelSoundCheck = 0;
        return;
    }

    // If (in Milk Bar and it is not between 6 AM and 10:13 PM) or (not in Milk Bar and is facing player), offer talk
    if (((play->sceneId == SCENE_MILK_BAR) &&
         !((CURRENT_TIME >= CLOCK_TIME(6, 0)) && (CURRENT_TIME <= (CLOCK_TIME(22, 13) + 7)))) ||    // Toto refuses to talk to you until 10:13 PM + 7 ticks ( = 0xED02)
        ((play->sceneId != SCENE_MILK_BAR) && EnToto_IsFacingPlayer(this, 0x2000))) {

        if (this->shouldCancelSoundCheck != 0) { // If player left stage during last frame
            this->text = &sSpeakData1[6];               // "Oh, that's too bad."
            this->actor.flags |= ACTOR_FLAG_TALK_OFFER_AUTO_ACCEPTED;
            Actor_OfferTalkExchange(&this->actor, play, 9999.9f, 9999.9f, PLAYER_IA_NONE);
        } else {
            this->actor.flags &= ~ACTOR_FLAG_TALK_OFFER_AUTO_ACCEPTED;
            Actor_OfferTalk(&this->actor, play, 50.0f);
            if (play->sceneId == SCENE_SONCHONOIE) {
                if (player->transformation == PLAYER_FORM_DEKU) {
                    if (!Flags_GetSwitch(play, ENTOTO_GET_DEKU_SPOKEN_FLAG(&this->actor))) {
                        this->text = &sSpeakData1[15];
                    } else {
                        this->text = &sSpeakData1[18];
                    }
                } else {
                    this->text = &sSpeakData1[7];
                }
            } else if (ENTOTO_FINISHED_WIND_FISH) {
                this->text = &sSpeakData1[0];
            } else if (!Flags_GetSwitch(play, ENTOTO_GET_ZORA_SPOKEN_FLAG(&this->actor))) {
                this->text = &sSpeakData1[2];
            } else {
                this->text = &sSpeakData1[3];
            }
        }

        this->actor.textId = this->text->textId;
    }
}
/*
    Triggered by player speaking to Toto. Animation handler?
    Triggers notebook event in Milk Bar only
*/
void EnToto_SetupAction_Talk(EnToto* this, PlayState* play) {
    if (play->sceneId == SCENE_SONCHONOIE) {
        Animation_MorphToPlayOnce(&this->skelAnime, &gTotoWaveHelloAnim, -4.0f); // Hold hand up while talking
        this->animIndex = ENTOTO_ANIM_TALK_SITTING;
    } else {
        if (this->text->talkActionIndex == 4) {
            Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_TOTO);
        }
        Animation_MorphToLoop(&this->skelAnime, &gTotoTalkStandingAnim, -4.0f);
    }
}

void EnToto_TurnTowardsPlayer(EnToto* this) {
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 4, 0xFA0, 0x320);
}

void EnToto_Action_Talk(EnToto* this, PlayState* play) {     // Talk?
    EnToto_UpdateAnimation(this, play);
    EnToto_TurnTowardsPlayer(this);
    if (Actor_TextboxIsClosing(&this->actor, play)) {
        EnToto_SetMainAction(this, play, this->text->argument);
    } else {
        EnToto_NextTalkStateTriggersCutscene(this, play);
    }
}

void EnToto_SetupAction_SoundCheck(EnToto* this, PlayState* play) {
    this->csId = this->actor.csId;
    this->text = ENTOTO_FINISHED_WIND_FISH ? &sSpeakData2[13] : &sSpeakData2[0];
    EnToto_ShouldTriggerCutscene(this, play);
    play->actorCtx.flags |= ACTORCTX_FLAG_5;
    this->faceChange.face = 0;
}

void EnToto_Action_SoundCheck(EnToto* this, PlayState* play) {
    Player* player;

    EnToto_UpdateAnimation(this, play);
    if (!this->shouldPlaySoundCheckCompleteCutscene) {
        if (!EnToto_NextTalkStateTriggersCutscene(this, play)) {
            return;
        }
        if ((this->text->argument != 0) && ENTOTO_FINISHED_WIND_FISH) {
            this->shouldPlaySoundCheckCompleteCutscene = true;
            return;
        }
    } else {
        player = GET_PLAYER(play);
        if ((player->stateFlags1 & PLAYER_STATE1_400) && (player->av1.actionVar1 != 0)) {
            Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_RECEIVED_CIRCUS_LEADERS_MASK);
            Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_TOTO);
            Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_GORMAN);
        } else {
            return;
        }
    }

    EnToto_SetMainAction(this, play, 0);
    CutsceneManager_Stop(this->csId);
    play->actorCtx.flags &= ~ACTORCTX_FLAG_5;
}

s32 EnToto_SetupTalk_ReturnTrue(EnToto* this, PlayState* play) {
    return 1;
}

s32 EnToto_SetupTalk_DoNothing(EnToto* this, PlayState* play) {
    return 0;
}

/*
    Sets up Link's "Wait" animation/cutscene if text argument is 2
    Argument is 2 if select "Yes" (should init sound check)
*/
s32 EnToto_HandleTalk_AfterChoice(EnToto* this, PlayState* play) {
    if (this->text->argument == 2) {
        Player_SetCsActionWithHaltedActors(play, NULL, PLAYER_CSACTION_WAIT);
    }
    return 0;
}
/*
    NextMessage should never trigger a cutscene, so always returns false
*/
s32 EnToto_SetupTalk_NextMessage(EnToto* this, PlayState* play) {
    if (this->text->textId != 0) {
        Message_ContinueTextbox(play, this->text->textId);
    } else {
        Message_CloseTextbox(play);
        EnToto_HandleTalk_AfterChoice(this, play);
    }
    if (this->text->talkActionIndex == 4) {
        Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_TOTO);
    }
    return 0;
}

/*
    Sets up timer from EnTotoSpeakData
*/
s32 EnToto_SetupTalk_SetNextMessageTimer(EnToto* this, PlayState* play) {
    this->timer = this->text->argument;
    return 0;
}

s32 EnToto_HandleTalk_Wait(EnToto* this, PlayState* play) {
    if (DECR(this->timer) == 0) {
        Message_StartTextbox(play, this->text->textId, NULL);
        return 1;
    }
    return 0;
}

/*
    Queue next cutscene
*/
s32 EnToto_SetupTalk_StartAdditionalCutscene(EnToto* this, PlayState* play) {
    s16 prevCsId = this->csId;

    this->csId = CutsceneManager_GetAdditionalCsId(this->csId);
    CutsceneManager_Queue(this->csId);
    CutsceneManager_Stop(prevCsId);
    return 0;
}

/*
    Start or queue cutscene

    Flow:
        Repeat:
            cutscene csId is not queued
        EnToto_HandleTalk_SoundCheck_MovePlayerToStage:
            cutscene csId is queued
*/
s32 EnToto_HandleTalk_StartCutscene(EnToto* this, PlayState* play) {
    if (CutsceneManager_IsNext(this->csId)) {
        CutsceneManager_StartWithPlayerCs(this->csId, &GET_PLAYER(play)->actor);
        return 1;
    }

    CutsceneManager_Queue(this->csId);
    return 0;
}

/* 
    

    
    
    
    
    Return true if at end of text sequence (i.e. text_done sound plays)
*/
s32 EnToto_HandleTalk_Event(EnToto* this, PlayState* play) {
    if ((Message_GetState(&play->msgCtx) == TEXT_STATE_EVENT) && Message_ShouldAdvance(play)) {
        return 1;
    }
    return 0;
}

/*
    Wait for player to advance text

    Flow:
        Repeat:
            - Message state is not CLOSING
        EnToto_HandleTalk_Choice:
            - Message state is CLOSING (Called from EnToto_NextTalkStateTriggersCutscene)
        EnToto_HandleTalk_SoundCheck_WaitForPlayerToEnterSpotlight:
            - Message state is CLOSING (Called from EnToto_HandleTalk_SoundCheck_WaitForPromptTextbox)
        
*/
s32 EnToto_HandleTalk_Closing(EnToto* this, PlayState* play) {
    if (Message_GetState(&play->msgCtx) == TEXT_STATE_CLOSING) {
        return 1;
    }
    return 0;
}

/*
    Wait for player to make choice on sound check start prompt

    Flow:
        Repeat:
            - Message state is not CHOICE or message should not advance
            - Player chooses option > 0 ("No", presumably)
        (Depends on argument):
            - Player chooses option 0 ("Yes", presumably)
*/
s32 EnToto_HandleTalk_Choice(EnToto* this, PlayState* play) {
    if ((Message_GetState(&play->msgCtx) == TEXT_STATE_CHOICE) && Message_ShouldAdvance(play)) {
        if (play->msgCtx.choiceIndex != 0) {
            Audio_PlaySfx_MessageCancel();
        } else {
            Audio_PlaySfx_MessageDecide();
        }
        return ((play->msgCtx.choiceIndex != 0) ? 0 : this->text->argument) + 1;
    }
    return 0;
}

/*
    Set up prompt for target spotlight

    Flow:
        Repeat:
            Timer is not finished counting down
        EnToto_HandleTalk_StartCutscene:
            Timer is finished counting down
*/
s32 EnToto_HandleTalk_SoundCheck_WaitAdvanceText(EnToto* this, PlayState* play) {
    EnTotoSpotlight* targetSpotlight;

    if (DECR(this->timer) == 0) {
        if (!ENTOTO_FINISHED_WIND_FISH) {
            targetSpotlight = &sSpotlightList[gSaveContext.save.playerForm - 1];
            Message_StartTextbox(play, (this->text->talkActionIndex == 6) ? targetSpotlight->promptTextId : targetSpotlight->rightLightTextId, NULL);
        }
        return 1;
    }
    return 0;
}

/*
    Start moving Link to the stairs in front of the stage, and spawn the spotlights.
    Omits points based on initial distance to end point.
*/
s32 EnToto_SetupTalk_InitSoundCheck(EnToto* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    u32 numPoints = 0;
    Vec3s* endPosListPtr = &sPlayerOverrideInputPosList[ARRAY_COUNT(sPlayerOverrideInputPosList)];

    EnToto_SetupTalk_SetNextMessageTimer(this, play);
    Player_SetCsActionWithHaltedActors(play, NULL, PLAYER_CSACTION_END);
    if (player->actor.world.pos.z > -310.0f) {
        if ((player->actor.world.pos.x > -150.0f) || (player->actor.world.pos.z > -172.0f)) {
            numPoints = ARRAY_COUNT(sPlayerOverrideInputPosList);
        } else if (player->actor.world.pos.z > -232.0f) {
            numPoints = ARRAY_COUNT(sPlayerOverrideInputPosList) - 1;
        } else {
            numPoints = ARRAY_COUNT(sPlayerOverrideInputPosList) - 2;
        }
    }
    Player_InitOverrideInput(play, &this->overrideInputEntry, numPoints, endPosListPtr - numPoints);
    this->spotlights = Actor_Spawn(&play->actorCtx, play, ACTOR_DM_CHAR07, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0xF02);
    return 0;
}

/*
    Move player to stage stairs, then wait for cue to advance (player enters right spotlight)
    
    Flow:
        Repeat:
            Player move is not complete
            EnToto_HandleTalk_SoundCheck_WaitAdvanceText returns false
        EnToto_HandleTalk_SoundCheck_WaitForPromptTextbox:
            EnToto_HandleTalk_SoundCheck_WaitAdvanceText returns true
        
*/
s32 EnToto_HandleTalk_SoundCheck_MovePlayerToStage(EnToto* this, PlayState* play) {
    EnToto_TurnTowardsPlayer(this);
    if (Player_UpdateOverrideInput(play, &this->overrideInputEntry, 60.0f)) {
        Player_SetCsActionWithHaltedActors(play, NULL, PLAYER_CSACTION_19);
        return EnToto_HandleTalk_SoundCheck_WaitAdvanceText(this, play);
    }
    return 0;
}

/*
    Flow:
        Repeat:
            EnToto_HandleTalk_Closing returns false
        EnToto_HandleTalk_SoundCheck_WaitForPlayerToEnterSpotlight:
            EnToto_HandleTalk_Closing returns true
*/
s32 EnToto_HandleTalk_SoundCheck_WaitForPromptTextbox(EnToto* this, PlayState* play) {
    if (EnToto_HandleTalk_Closing(this, play)) {
        Player_SetCsActionWithHaltedActors(play, NULL, PLAYER_CSACTION_END);
        return 1;
    }
    return 0;
}

/*
    Stop cutscene and reset timer
*/
s32 EnToto_SetupTalk_StopCutsceneAndResetTimer(EnToto* this, PlayState* play) {
    CutsceneManager_Stop(this->csId);
    this->timer = 0;
    return 0;
}

/*
    Returns true if distance to spotlight point is less than 10 units
*/
s32 EnToto_CheckIfPlayerInSpotlight(EnTotoSpotlight* arg0, Player* player) {
    Vec3f pos;

    Math_Vec3s_ToVec3f(&pos, &arg0->pos);
    if (Math_Vec3f_DistXZ(&player->actor.world.pos, &pos) < 10.0f) {
        return 1;
    }
    return 0;
}

s32 EnToto_HandleTalk_SoundCheck_WaitForPlayerToEnterSpotlight(EnToto* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    EnTotoSpotlight* targetSpotlight;
    s32 i;

    EnToto_TurnTowardsPlayer(this);

    // Player leaves the stage area
    if (player->actor.world.pos.z > -270.0f) {
        if (this->spotlights != NULL) {
            Actor_Kill(this->spotlights);
        }
        this->shouldCancelSoundCheck = 1;
        return this->text->argument;        // "Oh, that's too bad."
    }
    if (player->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
        targetSpotlight = &sSpotlightList[gSaveContext.save.playerForm - 1];
        
        // Player is in correct spotlight
        if (EnToto_CheckIfPlayerInSpotlight(targetSpotlight, player)) {
            Math_Vec3s_ToVec3f(&player->actor.world.pos, &targetSpotlight->pos);
            player->actor.shape.rot.y = 0;
            player->yaw = 0;
            return EnToto_HandleTalk_StartCutscene(this, play);       // Return next Wind Fish cutscene ID?
        }
        if (!ENTOTO_FINISHED_WIND_FISH) {
            for (i = 0; i < ARRAY_COUNT(sSpotlightList); i++) {
                
                // Player is in incorrect spotlight
                if (EnToto_CheckIfPlayerInSpotlight(&sSpotlightList[i], player)) {
                    if (this->timer < 10) {
                        this->timer++;
                        if (this->timer >= 10) {
                            Message_StartTextbox(play, sSpotlightList[GET_PLAYER_FORM - 1].wrongLightTextId, NULL);
                        }
                    }
                    return 0;
                }
            }
            this->timer = 0;
        }
    }
    return 0;
}

/*
    Prompt player with Wind Fish staff for their current form
*/
s32 EnToto_SetupTalk_InitWindFishOcarinaStaff(EnToto* this, PlayState* play) {
    Player_SetCsActionWithHaltedActors(play, NULL, PLAYER_CSACTION_68);
    Message_DisplayOcarinaStaff(play, sOcarinaActionWindFishPrompts[CUR_FORM]);
    return 0;
}

s32 EnToto_HandleTalk_SoundCheck_SetPlayedFlags(EnToto* this, PlayState* play) {
    if (play->msgCtx.ocarinaMode == OCARINA_MODE_END) {
        if (GET_PLAYER_FORM == PLAYER_FORM_HUMAN) {
            SET_WEEKEVENTREG(WEEKEVENTREG_PLAYED_WIND_FISH_AS_HUMAN);
        }
        if (GET_PLAYER_FORM == PLAYER_FORM_DEKU) {
            SET_WEEKEVENTREG(WEEKEVENTREG_PLAYED_WIND_FISH_AS_DEKU);
        }
        if (GET_PLAYER_FORM == PLAYER_FORM_ZORA) {
            SET_WEEKEVENTREG(WEEKEVENTREG_PLAYED_WIND_FISH_AS_ZORA);
        }
        if (GET_PLAYER_FORM == PLAYER_FORM_GORON) {
            SET_WEEKEVENTREG(WEEKEVENTREG_PLAYED_WIND_FISH_AS_GORON);
        }
        return 1;
    }
    return 0;
}

s32 EnToto_SetupTalk_InitWindFishPlayback(EnToto* this, PlayState* play) {
    Vec3f spawnPos;
    s32 i;

    this->windFishFormsPlayed = 0;
    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_PLAYED_WIND_FISH_AS_HUMAN)) {
        this->windFishFormsPlayed += 1;
    }
    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_PLAYED_WIND_FISH_AS_DEKU)) {
        this->windFishFormsPlayed += 2;
    }
    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_PLAYED_WIND_FISH_AS_ZORA)) {
        this->windFishFormsPlayed += 4;
    }
    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_PLAYED_WIND_FISH_AS_GORON)) {
        this->windFishFormsPlayed += 8;
    }
    for (i = 0; i < ARRAY_COUNT(sSpotlightList); i++) {
        if ((GET_PLAYER_FORM != (i + 1)) && (D_80BA5128[i] & this->windFishFormsPlayed)) {
            Math_Vec3s_ToVec3f(&spawnPos, &sSpotlightList[i].pos);

            Actor_Spawn(&play->actorCtx, play, ACTOR_PLAYER, spawnPos.x, spawnPos.y, spawnPos.z, i + 2, 0, 0,
                        PLAYER_PARAMS(0xFF, PLAYER_START_MODE_F) | 0xFFFFF000);
        }
    }
    EnToto_SetupTalk_StartAdditionalCutscene(this, play);
    if (ENTOTO_FINISHED_WIND_FISH) {
        EnToto_SetupTalk_StartAdditionalCutscene(this, play);
    }
    return 0;
}

/*
    Play back Ballad of the Wind Fish for all forms played
*/
s32 EnToto_SetupTalk_StartWindFishPlayback(EnToto* this, PlayState* play) {
    Player_SetCsActionWithHaltedActors(play, NULL, PLAYER_CSACTION_68);
    Audio_PlayFanfareWithPlayerIOCustomPort(NA_BGM_BALLAD_OF_THE_WIND_FISH, 4, this->windFishFormsPlayed ^ 0xF);
    this->timer = 4;
    return 0;
}

s32 EnToto_HandleTalk_SoundCheck_EndWindFishCutscene(EnToto* this, PlayState* play) {
    Actor* actor;

    if (DECR(this->timer) == 0) {
        // If Wind Fish is not done playing, stay in this state
        if (!Audio_IsSequencePlaying(NA_BGM_BALLAD_OF_THE_WIND_FISH)) {
            // Destroy the spotlights and the Links playing them
            actor = &GET_PLAYER(play)->actor;
            actor = actor->next;
            while (actor != NULL) {
                Actor_Kill(actor);
                actor = actor->next;
            }
            if (this->spotlights != NULL) {
                Actor_Kill(this->spotlights);
            }

            Player_SetCsActionWithHaltedActors(play, NULL, PLAYER_CSACTION_69);
            
            if (this->windFishFormsPlayed == 0xF) {
                if (CURRENT_DAY == 1) {
                    SET_WEEKEVENTREG(WEEKEVENTREG_HELPED_GORMAN_DAY_1);
                } else {
                    SET_WEEKEVENTREG(WEEKEVENTREG_HELPED_GORMAN_DAY_2);
                }
            } else {
                EnToto_SetupTalk_StartAdditionalCutscene(this, play);   // "What feels good? That wretched, senseless racket?"
            }
            return 1;
        }
    }
    return 0;
}

s32 EnToto_HandleTalk_SetupMayorsResidence(EnToto* this, PlayState* play) {      // Handle Mayor's Residence talk
    Player* player;

    if (EnToto_HandleTalk_Event(this, play)) {
        player = GET_PLAYER(play);
        Animation_MorphToPlayOnce(&this->skelAnime, &gTotoTalkSittingAnim, -4.0f);
        if (player->transformation == PLAYER_FORM_ZORA) {
            if (!Flags_GetSwitch(play, ENTOTO_GET_ZORA_SPOKEN_FLAG(&this->actor))) {
                Flags_SetSwitch(play, ENTOTO_GET_ZORA_SPOKEN_FLAG(&this->actor));
                return 1;
            } else {
                return 3;
            }
        } else {
            if (!Flags_GetSwitch(play, ENTOTO_GET_OTHER_SPOKEN_FLAG(&this->actor))) {
                Flags_SetSwitch(play, ENTOTO_GET_OTHER_SPOKEN_FLAG(&this->actor));
                return 4;
            } else {
                return 7;
            }
        }
    }
    return 0;
}

/*
    
*/
s32 EnToto_ShouldTriggerCutscene(EnToto* this, PlayState* play) {
    return sTalkStateSetupFuncs[this->text->talkActionIndex](this, play);
}

/*
    Update talkHandler function
    These functions repeat until returning a nonzero value, at which point the talkFunc
    pointer increments to the next one in sTalkStateHandlerFuncs, and also calls a 
    talkFunc from sTalkStateSetupFuncs once
*/
s32 EnToto_NextTalkStateTriggersCutscene(EnToto* this, PlayState* play) {
    s32 nextOffset = sTalkStateHandlerFuncs[this->text->talkActionIndex](this, play);

    if (nextOffset != 0) {
        this->text += nextOffset;
        return EnToto_ShouldTriggerCutscene(this, play);
    }
    return 0;
}

/*
    
*/
void EnToto_HandleGormanCutscene(EnToto* this, PlayState* play) {
    CsCmdActorCue* cue = play->csCtx.actorCues[Cutscene_GetCueChannel(play, CS_CMD_ACTOR_CUE_525)];

    if (this->cueId != cue->id) {
        this->cueId = cue->id;
        if (this->cueId != 4) {
            if (this->cueId == 3) {     /* cueId 3 == "Alright! That feels good!" */
                Animation_MorphToPlayOnce(&this->skelAnime, &gTotoCheerAnim, -4.0f);
            } else {                    /* cueId 2 == Turn to look at Gorman*/
                Animation_PlayOnce(&this->skelAnime,
                                   (this->cueId == 1) ? &gTotoTurnLookAtStageAnim : &gTotoTurnLookAtGormanAnim);
                if ((this->cueId == 2) && (this->windFishFormsPlayed != 0xF)) {
                    Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_TOTO);
                    Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_GORMAN);
                }
            }
        }
    }
    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 0x320);
    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->cueId != 3) {
            Animation_PlayLoop(&this->skelAnime, (this->cueId == 1) ? &gTotoIdleStandingAnim : &gTotoIdleLookAtGormanAnim);
        }
    }
    if ((this->cueId == 4) && !Actor_HasParent(&this->actor, play)) {
        Actor_OfferGetItem(&this->actor, play, GI_MASK_CIRCUS_LEADER, 9999.9f, 9999.9f);
    }
}

void EnToto_Update(Actor* thisx, PlayState* play) {
    EnToto* this = (EnToto*)thisx;
    s32 pad;

    if (Cutscene_IsCueInChannel(play, CS_CMD_ACTOR_CUE_525)) {
        EnToto_HandleGormanCutscene(this, play);          // Update cutscene. Gorman interaction only? Or any?
    } else {
        sActionHandlerFuncs[this->actionFuncIndex](this, play);
    }

    Collider_ResetCylinderAC(play, &this->collider.base);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
    Actor_SetFocus(&this->actor, 40.0f);
}

void EnToto_Draw(Actor* thisx, PlayState* play) {
    TexturePtr eyeTextures[] = { gTotoEyesOpenTex, gTotoEyesHalfTex, gTotoEyesClosedTex };
    EnToto* this = (EnToto*)thisx;
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Opa(play->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(eyeTextures[this->faceChange.face]));
    Scene_SetRenderModeXlu(play, 0, 1);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount, NULL,
                          NULL, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}
