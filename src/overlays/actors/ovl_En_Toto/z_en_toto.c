/*
 * File: z_en_toto.c
 * Overlay: ovl_En_Toto
 * Description: Toto
 */

#include "z_en_toto.h"

#define FLAGS (ACTOR_FLAG_ATTENTION_ENABLED | ACTOR_FLAG_FRIENDLY)

#define ENTOTO_FINISHED_WIND_FISH \
    (CHECK_WEEKEVENTREG(WEEKEVENTREG_HELPED_GORMAN_DAY_1) || CHECK_WEEKEVENTREG(WEEKEVENTREG_HELPED_GORMAN_DAY_2))

void EnToto_Init(Actor* thisx, PlayState* play);
void EnToto_Destroy(Actor* thisx, PlayState* play);
void EnToto_Update(Actor* thisx, PlayState* play);
void EnToto_Draw(Actor* thisx, PlayState* play);

void EnToto_SetupIdle(EnToto* this, PlayState* play);
void EnToto_Idle(EnToto* this, PlayState* play);
void EnToto_SoundCheck(EnToto* this, PlayState* play);
void EnToto_SetupTalk(EnToto* this, PlayState* play);
void EnToto_Talk(EnToto* this, PlayState* play);
void EnToto_SetupSoundCheck(EnToto* this, PlayState* play);
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
s32 EnToto_RunTalkStateSetupFunc(EnToto* this, PlayState* play);
s32 EnToto_RunTalkStateHandlerFunc(EnToto* this, PlayState* play);

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
    /* 0  */ EnToto_SetupIdle,
    /* 1  */ EnToto_SetupTalk,
    /* 2  */ EnToto_SetupSoundCheck,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_U8(attentionRangeType, ATTENTION_RANGE_1, ICHAIN_STOP),
};

typedef enum EnTotoTalkState {
    // 0 - 4: Milk Bar Dialog
    /* 0  */ ENTOTO_TALK_EVENT,
    /* 1  */ ENTOTO_TALK_CLOSING,
    /* 2  */ ENTOTO_TALK_CHOICE,
    /* 3  */ ENTOTO_TALK_AFTER_CHOICE,
    /* 4  */ ENTOTO_TALK_NEXT_MESSAGE, // Also used for declining Sound Check request
                                       // 5 - 15: Sound Check Actions
    /* 5  */ ENTOTO_TALK_START_CUTSCENE,
    /* 6  */ ENTOTO_TALK_MOVE_PLAYER_TO_STAGE,
    /* 7  */ ENTOTO_TALK_SPOTLIGHT_PROMPT,
    /* 8  */ ENTOTO_TALK_WAIT_PLAYER_ENTER_SPOTLIGHT,
    /* 9  */ ENTOTO_TALK_WAIT_ADVANCE_TEXT,
    /* 10 */ ENTOTO_TALK_START_CUTSCENE_ON_STAGE,
    /* 11 */ ENTOTO_TALK_WIND_FISH_OCARINA_STAFF,
    /* 12 */ ENTOTO_TALK_START_CUTSCENE_WIND_FISH,
    /* 13 */ ENTOTO_TALK_WAIT_WIND_FISH_CUTSCENE,
    /* 14 */ ENTOTO_TALK_WAIT_AFTER_WIND_FISH,
    /* 15 */ ENTOTO_TALK_START_GORMAN_CUTSCENE,
    // 16 - 17: Mayor's Residence Dialog
    /* 16 */ ENTOTO_TALK_SET_UP_MAYORS_RESIDENCE,
    /* 17 */ ENTOTO_TALK_RETURN_TRUE // Only in SetupFuncs
} EnTotoTalkState;

static EnTotoSpeakData sDialogSpeakData[] = {
    /* Milk Bar */
    { ENTOTO_TALK_EVENT, 0, 0x2B21 }, // "...play for us again?"
    { ENTOTO_TALK_AFTER_CHOICE, 2, 0 },
    { ENTOTO_TALK_EVENT, 0, 0x2B23 },        // "...scheduled to do a show..."
    { ENTOTO_TALK_CHOICE, 1, 0x2B24 },       // "...help me with a performance?"
    { ENTOTO_TALK_NEXT_MESSAGE, 0, 0x2B25 }, // "Oh, that's too bad."
    { ENTOTO_TALK_AFTER_CHOICE, 2, 0 },
    { ENTOTO_TALK_NEXT_MESSAGE, 0, 0x2B25 }, // "Oh, that's too bad."
    /* Mayor's Residence */
    { ENTOTO_TALK_SET_UP_MAYORS_RESIDENCE, 0, 0x2A94 }, // "Are the fins damp lately?"
    { ENTOTO_TALK_EVENT, 0, 0x2A95 },                   // "What? Mikau???"
    { ENTOTO_TALK_NEXT_MESSAGE, 0, 0x2A96 },            // "You look so much like him..."
    { ENTOTO_TALK_NEXT_MESSAGE, 0, 0x2A97 },            // "With the ocean the way it is..."
    { ENTOTO_TALK_EVENT, 0, 0x2A98 },                   // "That's the greeting..."
    { ENTOTO_TALK_EVENT, 0, 0x2A99 },                   // "I am Toto..."
    { ENTOTO_TALK_NEXT_MESSAGE, 0, 0x2A9A },            // "The Indigo-Go's is..."
    { ENTOTO_TALK_NEXT_MESSAGE, 0, 0x2A9B },            // "Canceling the show..."
    { ENTOTO_TALK_EVENT, 0, 0x2AE1 },                   // "Are the fins damp?"  (Deku)
    { ENTOTO_TALK_EVENT, 0, 0x2AE2 },                   // "That's the greeting" (Deku)
    { ENTOTO_TALK_NEXT_MESSAGE, 0, 0x2AE3 },            // "Where's your momma?"
    { ENTOTO_TALK_NEXT_MESSAGE, 0, 0x2AE4 },            // "Once you get older..."
};

typedef enum EnTotoAnimation {
    /* 0 */ ENTOTO_ANIM_TALK_SITTING,
    /* 1 */ ENTOTO_ANIM_MOVE_CANE_BEHIND_HEAD,
    /* 2 */ ENTOTO_ANIM_TAP_HEAD_WITH_CANE,
    /* 3 */ ENTOTO_ANIM_MOVE_CANE_TO_FLOOR,
    /* 4 */ ENTOTO_ANIM_MAX
} EnTotoAnimation;

static AnimationHeader* sTalkSittingAnimations[ENTOTO_ANIM_MAX] = {
    &gTotoTalkSittingAnim,        // ENTOTO_ANIM_TALK_SITTING
    &gTotoMoveCaneBehindHeadAnim, // ENTOTO_ANIM_MOVE_CANE_BEHIND_HEAD
    &gTotoTapHeadWithCaneAnim,    // ENTOTO_ANIM_TAP_HEAD_WITH_CANE
    &gTotoMoveCaneBackDownAnim,   // ENTOTO_ANIM_MOVE_CANE_TO_FLOOR
};

static EnTotoSpeakData sSoundCheckSpeakData[] = {
    /* Sound Check Before Completion */
    { ENTOTO_TALK_START_CUTSCENE, 0, 0 },
    { ENTOTO_TALK_MOVE_PLAYER_TO_STAGE, 20, 0 },
    { ENTOTO_TALK_SPOTLIGHT_PROMPT, 0, 0 },
    { ENTOTO_TALK_WAIT_PLAYER_ENTER_SPOTLIGHT, 9, 0 },
    { ENTOTO_TALK_WAIT_ADVANCE_TEXT, 10, 0 },
    { ENTOTO_TALK_CLOSING, 0, 0 },
    { ENTOTO_TALK_START_CUTSCENE_ON_STAGE, 0, 0 },
    { ENTOTO_TALK_WIND_FISH_OCARINA_STAFF, 0, 0 },
    { ENTOTO_TALK_START_CUTSCENE_WIND_FISH, 0, 0 },
    { ENTOTO_TALK_WAIT_WIND_FISH_CUTSCENE, 0, 0 },
    { ENTOTO_TALK_START_GORMAN_CUTSCENE, 0, 0 },
    { ENTOTO_TALK_RETURN_TRUE, 1, 0 },
    { ENTOTO_TALK_RETURN_TRUE, 0, 0 },
    /* Sound Check After Completion */
    { ENTOTO_TALK_START_CUTSCENE, 0, 0 },
    { ENTOTO_TALK_MOVE_PLAYER_TO_STAGE, 20, 0 },
    { ENTOTO_TALK_WAIT_PLAYER_ENTER_SPOTLIGHT, 5, 0 },
    { ENTOTO_TALK_START_CUTSCENE_WIND_FISH, 0, 0 },
    { ENTOTO_TALK_WAIT_WIND_FISH_CUTSCENE, 0, 0 },
    { ENTOTO_TALK_WAIT_AFTER_WIND_FISH, 20, 0x2B22 }, // "I wanted you to hear Lulu's voice"
    { ENTOTO_TALK_CLOSING, 0, 0 },
    { ENTOTO_TALK_RETURN_TRUE, 0, 0 }
};

static EnTotoSpotlight sSpotlightList[] = {
    /* Goron */ { 0x2B2F, 0x2B30, 0x2B31, { 0xFF96, 0x0016, 0xFE16 } },
    /* Zora  */ { 0x2B26, 0x2B27, 0x2B28, { 0x0072, 0x0016, 0xFE3C } },
    /* Deku  */ { 0x2B29, 0x2B2A, 0x2B2B, { 0xFF67, 0x0016, 0xFE6E } },
    /* Human */ { 0x2B2C, 0x2B2D, 0x2B2E, { 0xFFF1, 0x0016, 0xFE74 } },
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

static u8 sSpotlightIndexToForm[] = { 8, 4, 2, 1 }; // Spotlight index to form flag

static EnTotoTalkFunc sTalkStateSetupFuncs[] = {
    /* 0  */ EnToto_SetupTalk_NextMessage,
    /* 1  */ EnToto_SetupTalk_DoNothing,
    /* 2  */ EnToto_SetupTalk_NextMessage,
    /* 3  */ EnToto_SetupTalk_NextMessage,
    /* 4  */ EnToto_SetupTalk_NextMessage,
    /* 5  */ EnToto_SetupTalk_DoNothing,
    /* 6  */ EnToto_SetupTalk_InitSoundCheck,
    /* 7  */ EnToto_SetupTalk_DoNothing,
    /* 8  */ EnToto_SetupTalk_StopCutsceneAndResetTimer,
    /* 9  */ EnToto_SetupTalk_SetNextMessageTimer,
    /* 10 */ EnToto_SetupTalk_StartAdditionalCutscene,
    /* 11 */ EnToto_SetupTalk_InitWindFishOcarinaStaff,
    /* 12 */ EnToto_SetupTalk_InitWindFishPlayback,
    /* 13 */ EnToto_SetupTalk_StartWindFishPlayback,
    /* 14 */ EnToto_SetupTalk_SetNextMessageTimer,
    /* 15 */ EnToto_SetupTalk_StartAdditionalCutscene,
    /* 16 */ EnToto_SetupTalk_NextMessage,
    /* 17 */ EnToto_SetupTalk_ReturnTrue,
};

/**
 * Functions called repeatedly until text pointer changed
 * Similar to EnTest3 (Kafei)'s sTalkStateHandlerFuncs
 */
static EnTotoTalkFunc sTalkStateHandlerFuncs[] = {
    /* 0  */ EnToto_HandleTalk_Event,
    /* 1  */ EnToto_HandleTalk_Closing,
    /* 2  */ EnToto_HandleTalk_Choice,
    /* 3  */ EnToto_HandleTalk_AfterChoice,
    /* 4  */ EnToto_HandleTalk_AfterChoice,
    /* 5  */ EnToto_HandleTalk_StartCutscene,
    /* 6  */ EnToto_HandleTalk_SoundCheck_MovePlayerToStage,
    /* 7  */ EnToto_HandleTalk_SoundCheck_WaitForPromptTextbox,
    /* 8  */ EnToto_HandleTalk_SoundCheck_WaitForPlayerToEnterSpotlight,
    /* 9  */ EnToto_HandleTalk_SoundCheck_WaitAdvanceText,
    /* 10 */ EnToto_HandleTalk_StartCutscene,
    /* 11 */ EnToto_HandleTalk_SoundCheck_SetPlayedFlags,
    /* 12 */ EnToto_HandleTalk_StartCutscene,
    /* 13 */ EnToto_HandleTalk_SoundCheck_EndWindFishCutscene,
    /* 14 */ EnToto_HandleTalk_Wait,
    /* 15 */ EnToto_HandleTalk_StartCutscene,
    /* 16 */ EnToto_HandleTalk_SetupMayorsResidence,
};

static EnTotoActionFunc sActionHandlerFuncs[] = {
    /* 0  */ EnToto_Idle,
    /* 1  */ EnToto_Talk,
    /* 2  */ EnToto_SoundCheck,
};

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
    if (SkelAnime_Update(&this->skelAnime) &&                 // Animation is complete
        (this->actionFuncIndex == 1) &&                       // Is talking to player
        (this->skelAnime.animation != &gTotoWaveHelloAnim)) { // Not currently waving to Link

        if ((play->msgCtx.currentTextId != 0x2A98) &&
            (play->msgCtx.currentTextId != 0x2A99)) { // If not first 2 text boxes after Mayor's Residence greeting
            if ((this->animIndex & 1) || (Rand_ZeroOne() > 0.5f)) { // 50% chance
                this->animIndex = (this->animIndex + 1) & 3;        // Tap on head with cane
            }
        }
        Animation_PlayOnce(&this->skelAnime, sTalkSittingAnimations[this->animIndex]);
    }
    FaceChange_UpdateBlinkingNonHuman(&this->faceChange, 20, 80, 3);
}

void EnToto_SetupIdle(EnToto* this, PlayState* play) {
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

void EnToto_Idle(EnToto* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    EnToto_UpdateAnimation(this, play);
    if (Actor_TalkOfferAccepted(&this->actor, &play->state)) {
        EnToto_SetMainAction(this, play, 1);

        if (play->sceneId != SCENE_SONCHONOIE) {
            Flags_SetSwitch(play, ENTOTO_GET_ZORA_SPOKEN_FLAG(&this->actor));
        } else if (player->transformation == PLAYER_FORM_DEKU) {
            Flags_SetSwitch(play, ENTOTO_GET_DEKU_SPOKEN_FLAG(&this->actor));
        }
        this->shouldCancelSoundCheck = false;
        return;
    }

    if (((play->sceneId == SCENE_MILK_BAR) &&
         !((CURRENT_TIME >= CLOCK_TIME(6, 0)) && (CURRENT_TIME <= (CLOCK_TIME(22, 13) + 7)))) ||
        ((play->sceneId != SCENE_MILK_BAR) && EnToto_IsFacingPlayer(this, 0x2000))) {

        if (this->shouldCancelSoundCheck) {
            this->text = &sDialogSpeakData[6]; // "Oh, that's too bad."
            this->actor.flags |= ACTOR_FLAG_TALK_OFFER_AUTO_ACCEPTED;
            Actor_OfferTalkExchange(&this->actor, play, 9999.9f, 9999.9f, PLAYER_IA_NONE);
        } else {
            this->actor.flags &= ~ACTOR_FLAG_TALK_OFFER_AUTO_ACCEPTED;
            Actor_OfferTalk(&this->actor, play, 50.0f);
            if (play->sceneId == SCENE_SONCHONOIE) {
                if (player->transformation == PLAYER_FORM_DEKU) {
                    if (!Flags_GetSwitch(play, ENTOTO_GET_DEKU_SPOKEN_FLAG(&this->actor))) {
                        this->text = &sDialogSpeakData[15]; // "Are the fins damp lately?" (as Deku)
                    } else {
                        this->text = &sDialogSpeakData[18]; // "Once you get older, come see us perform!"
                    }
                } else {
                    this->text = &sDialogSpeakData[7]; // "Are the fins damp lately?" (non-Deku)
                }
            } else if (ENTOTO_FINISHED_WIND_FISH) {
                this->text = &sDialogSpeakData[0]; // "Are you going to play for us again?"
            } else if (!Flags_GetSwitch(play, ENTOTO_GET_ZORA_SPOKEN_FLAG(&this->actor))) {
                this->text = &sDialogSpeakData[2]; // "We were scheduled to do a show, but..."
            } else {
                this->text = &sDialogSpeakData[3]; // "Could you help me with a performance?"
            }
        }

        this->actor.textId = this->text->textId;
    }
}

void EnToto_SetupTalk(EnToto* this, PlayState* play) {
    if (play->sceneId == SCENE_SONCHONOIE) {
        Animation_MorphToPlayOnce(&this->skelAnime, &gTotoWaveHelloAnim, -4.0f);
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

void EnToto_Talk(EnToto* this, PlayState* play) {
    EnToto_UpdateAnimation(this, play);
    EnToto_TurnTowardsPlayer(this);
    if (Actor_TextboxIsClosing(&this->actor, play)) {
        EnToto_SetMainAction(this, play, this->text->argument);
    } else {
        EnToto_RunTalkStateHandlerFunc(this, play);
    }
}

void EnToto_SetupSoundCheck(EnToto* this, PlayState* play) {
    this->csId = this->actor.csId;
    this->text = ENTOTO_FINISHED_WIND_FISH ? &sSoundCheckSpeakData[13] : &sSoundCheckSpeakData[0];
    EnToto_RunTalkStateSetupFunc(this, play);
    play->actorCtx.flags |= ACTORCTX_FLAG_5;
    this->faceChange.face = 0;
}

void EnToto_SoundCheck(EnToto* this, PlayState* play) {
    Player* player;

    EnToto_UpdateAnimation(this, play);
    if (!this->shouldPlaySoundCheckCompleteCutscene) {
        if (!EnToto_RunTalkStateHandlerFunc(this, play)) {
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

s32 EnToto_HandleTalk_AfterChoice(EnToto* this, PlayState* play) {
    if (this->text->argument == 2) {
        Player_SetCsActionWithHaltedActors(play, NULL, PLAYER_CSACTION_WAIT);
    }
    return 0;
}

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

s32 EnToto_SetupTalk_StartAdditionalCutscene(EnToto* this, PlayState* play) {
    s16 prevCsId = this->csId;

    this->csId = CutsceneManager_GetAdditionalCsId(this->csId);
    CutsceneManager_Queue(this->csId);
    CutsceneManager_Stop(prevCsId);
    return 0;
}

s32 EnToto_HandleTalk_StartCutscene(EnToto* this, PlayState* play) {
    if (CutsceneManager_IsNext(this->csId)) {
        CutsceneManager_StartWithPlayerCs(this->csId, &GET_PLAYER(play)->actor);
        return 1;
    }

    CutsceneManager_Queue(this->csId);
    return 0;
}

s32 EnToto_HandleTalk_Event(EnToto* this, PlayState* play) {
    if ((Message_GetState(&play->msgCtx) == TEXT_STATE_EVENT) && Message_ShouldAdvance(play)) {
        return 1;
    }
    return 0;
}

s32 EnToto_HandleTalk_Closing(EnToto* this, PlayState* play) {
    if (Message_GetState(&play->msgCtx) == TEXT_STATE_CLOSING) {
        return 1;
    }
    return 0;
}

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

s32 EnToto_HandleTalk_SoundCheck_WaitAdvanceText(EnToto* this, PlayState* play) {
    EnTotoSpotlight* targetSpotlight;

    if (DECR(this->timer) == 0) {
        if (!ENTOTO_FINISHED_WIND_FISH) {
            targetSpotlight = &sSpotlightList[gSaveContext.save.playerForm - 1];
            Message_StartTextbox(play,
                                 (this->text->talkActionIndex == 6) ? targetSpotlight->promptTextId
                                                                    : targetSpotlight->rightLightTextId,
                                 NULL);
        }
        return 1;
    }
    return 0;
}

/**
 *  Start moving Link to the stairs in front of the stage, and spawn the spotlights.
 *  Omits points based on initial distance to end point.
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

s32 EnToto_HandleTalk_SoundCheck_MovePlayerToStage(EnToto* this, PlayState* play) {
    EnToto_TurnTowardsPlayer(this);
    if (Player_UpdateOverrideInput(play, &this->overrideInputEntry, 60.0f)) {
        Player_SetCsActionWithHaltedActors(play, NULL, PLAYER_CSACTION_19);
        return EnToto_HandleTalk_SoundCheck_WaitAdvanceText(this, play);
    }
    return 0;
}

s32 EnToto_HandleTalk_SoundCheck_WaitForPromptTextbox(EnToto* this, PlayState* play) {
    if (EnToto_HandleTalk_Closing(this, play)) {
        Player_SetCsActionWithHaltedActors(play, NULL, PLAYER_CSACTION_END);
        return 1;
    }
    return 0;
}

s32 EnToto_SetupTalk_StopCutsceneAndResetTimer(EnToto* this, PlayState* play) {
    CutsceneManager_Stop(this->csId);
    this->timer = 0;
    return 0;
}

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
        this->shouldCancelSoundCheck = true;
        return this->text->argument;
    }
    if (player->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
        targetSpotlight = &sSpotlightList[gSaveContext.save.playerForm - 1];

        // Player is in correct spotlight
        if (EnToto_CheckIfPlayerInSpotlight(targetSpotlight, player)) {
            Math_Vec3s_ToVec3f(&player->actor.world.pos, &targetSpotlight->pos);
            player->actor.shape.rot.y = 0;
            player->yaw = 0;
            return EnToto_HandleTalk_StartCutscene(this, play);
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
        if ((GET_PLAYER_FORM != (i + 1)) && (sSpotlightIndexToForm[i] & this->windFishFormsPlayed)) {
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
                EnToto_SetupTalk_StartAdditionalCutscene(this, play); // Set up Gorman booing cutscene
            }
            return 1;
        }
    }
    return 0;
}

s32 EnToto_HandleTalk_SetupMayorsResidence(EnToto* this, PlayState* play) {
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

s32 EnToto_RunTalkStateSetupFunc(EnToto* this, PlayState* play) {
    return sTalkStateSetupFuncs[this->text->talkActionIndex](this, play);
}

/**
 *  These functions generally stay in the same state until one of them returns
 *  something nonzero, then it sets up the next one.
 */
s32 EnToto_RunTalkStateHandlerFunc(EnToto* this, PlayState* play) {
    s32 nextOffset = sTalkStateHandlerFuncs[this->text->talkActionIndex](this, play);

    if (nextOffset != 0) {
        this->text += nextOffset;
        return EnToto_RunTalkStateSetupFunc(this, play);
    }
    return 0;
}

void EnToto_HandleGormanCutscene(EnToto* this, PlayState* play) {
    CsCmdActorCue* cue = play->csCtx.actorCues[Cutscene_GetCueChannel(play, CS_CMD_ACTOR_CUE_525)];

    if (this->cueId != cue->id) {
        this->cueId = cue->id;
        if (this->cueId != 4) {
            if (this->cueId == 3) {
                Animation_MorphToPlayOnce(&this->skelAnime, &gTotoCheerAnim, -4.0f);
            } else {
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
            Animation_PlayLoop(&this->skelAnime,
                               (this->cueId == 1) ? &gTotoIdleStandingAnim : &gTotoIdleLookAtGormanAnim);
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
        EnToto_HandleGormanCutscene(this, play);
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
