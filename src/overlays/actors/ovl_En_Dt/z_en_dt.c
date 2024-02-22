/*
 * File: z_en_dt.c
 * Overlay: ovl_En_Dt
 * Description: Mayor Dotour
 */

#include "z_en_dt.h"

#include "objects/object_dt/object_dt.h"
#include "overlays/actors/ovl_En_Baisen/z_en_baisen.h"
#include "overlays/actors/ovl_En_Muto/z_en_muto.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY)

#define THIS ((EnDt*)thisx)

void EnDt_Init(Actor* thisx, PlayState* play);
void EnDt_Destroy(Actor* thisx, PlayState* play);
void EnDt_Update(Actor* thisx, PlayState* play);
void EnDt_Draw(Actor* thisx, PlayState* play);

void EnDt_ChangeAnim(EnDt* this, s32 animIndex);
void EnDt_SetupRegularState(EnDt* this, PlayState* play);
void EnDt_SetupCutsceneNpcs(EnDt* this, PlayState* play);
void EnDt_OfferRegularTalk(EnDt* this, PlayState* play);
void EnDt_SetupMeetingCutscene(EnDt* this, PlayState* play);
void EnDt_UpdateMeetingCutscene(EnDt* this, PlayState* play);
void EnDt_FinishMeetingCutscene(EnDt* this, PlayState* play);
void EnDt_OfferMeetingReward(EnDt* this, PlayState* play);
void EnDt_OfferFinalNightTalk(EnDt* this, PlayState* play);
void EnDt_TriggerFinalNightTalkEvent(EnDt* this, PlayState* play);
void EnDt_TriggerMeetingRewardEvent(EnDt* this, PlayState* play);
void EnDt_TriggerMeetingNotebookEvent(EnDt* this, PlayState* play);
void EnDt_SetupFinalNightState(EnDt* this, PlayState* play);
void EnDt_UpdateVisualState(EnDt* this);
void EnDt_StartFinalNightTalk(EnDt* this);
void EnDt_UpdateCutsceneFocusTarget(EnDt* this);

typedef enum {
    /* 0 */ EN_DT_NPC_STATE_DEFAULT,
    /* 1 */ EN_DT_NPC_STATE_IDLE,
    /* 2 */ EN_DT_NPC_STATE_VIEWING_MEETING,
    /* 3 */ EN_DT_NPC_STATE_OFFERED_MEETING_REWARD,
    /* 4 */ EN_DT_NPC_STATE_WAIT_FINAL_NIGHT_TALK,
    /* 5 */ EN_DT_NPC_STATE_DONE_FINAL_NIGHT_TALK
} EnDtNpcState;

typedef enum {
    /* 0 */ EN_DT_CS_STATE_NONE,
    /* 1 */ EN_DT_CS_STATE_WAITING,
    /* 2 */ EN_DT_CS_STATE_PLAYING
} EnDtCutsceneState;

typedef enum {
    /* 0 */ EN_DT_CS_FOCUS_TARGET_MUTO,
    /* 1 */ EN_DT_CS_FOCUS_TARGET_BAISEN,
    /* 2 */ EN_DT_CS_FOCUS_TARGET_MAYOR
} EnDtCutsceneFocusTarget;

typedef enum {
    /* 0 */ EN_DT_ANIMATION_0,
    /* 1 */ EN_DT_ANIMATION_1,
    /* 2 */ EN_DT_ANIMATION_2,
    /* 3 */ EN_DT_ANIMATION_3,
    /* 4 */ EN_DT_ANIMATION_4,
    /* 5 */ EN_DT_ANIMATION_5,
    /* 6 */ EN_DT_ANIMATION_MAX
} EnDtAnimation;

typedef enum {
    /* 0 */ EN_DT_EYE_TEXTURE_SHOCK,
    /* 1 */ EN_DT_EYE_TEXTURE_OPEN,
    /* 2 */ EN_DT_EYE_TEXTURE_CLOSED,
    /* 3 */ EN_DT_EYE_TEXTURE_LOOK_DOWN,
    /* 4 */ EN_DT_EYE_TEXTURE_SQUINT,
    /* 5 */ EN_DT_EYE_TEXTURE_MAX
} EnDtEyeTextures;

typedef enum {
    /* 0 */ EN_DT_BROW_TEXTURE_HIGH,
    /* 1 */ EN_DT_BROW_TEXTURE_MID,
    /* 2 */ EN_DT_BROW_TEXTURE_LOW,
    /* 3 */ EN_DT_BROW_TEXTURE_MAX
} EnDtBrowTextures;

ActorInit En_Dt_InitVars = {
    /**/ ACTOR_EN_DT,
    /**/ ACTORCAT_NPC,
    /**/ FLAGS,
    /**/ OBJECT_DT,
    /**/ sizeof(EnDt),
    /**/ EnDt_Init,
    /**/ EnDt_Destroy,
    /**/ EnDt_Update,
    /**/ EnDt_Draw,
};

static u16 sTextIds[] = { 0x2ABD, 0x2ABE, 0x2ABF, 0x2AC0, 0x2ABE, 0x2AC1, 0x2AC2, 0x2AC3, 0x2AC4, 0x2ABB,
                          0x2ABC, 0x2AC6, 0x2AC7, 0x2AC8, 0x2AC9, 0x2ACA, 0x2ACB, 0x2ACC, 0x2ACD, 0x2ACE,
                          0x2ACF, 0x2AD0, 0x2AD1, 0x2AC5, 0x2AD3, 0x2AD4, 0x2AD2, 0x0000 };

// The code uses EnDt::textIdIndex as an index into this lookup table
static s32 sCutsceneFocusTargetTable[] = {
    /* 00 */ EN_DT_CS_FOCUS_TARGET_BAISEN, /* [2ABD] "Most of the townsfolk already sheltered" */
    /* 01 */ EN_DT_CS_FOCUS_TARGET_MAYOR,  /* [2ABE] "Ahh...hmm...well..." */
    /* 02 */ EN_DT_CS_FOCUS_TARGET_MUTO,   /* [2ABF] "You cowards! The moon won't fall" */
    /* 03 */ EN_DT_CS_FOCUS_TARGET_MUTO,   /* [2AC0] "Isn't that right Mayor?" */
    /* 04 */ EN_DT_CS_FOCUS_TARGET_MAYOR,  /* [2ABE] "Ahh...hmm...well..." */
    /* 05 */ EN_DT_CS_FOCUS_TARGET_BAISEN, /* [2AC1] "You serious Mutoh? Missed the huge rock?" */
    /* 06 */ EN_DT_CS_FOCUS_TARGET_MAYOR,  /* [2AC2] "Mmm...Hmm..." */
    /* 07 */ EN_DT_CS_FOCUS_TARGET_MUTO,   /* [2AC3] "If the soldiers wish to run, then abandon us"   */
    /* 08 */ EN_DT_CS_FOCUS_TARGET_MAYOR,  /* [2AC4] "Let's not bring my wife into this" */

    /* 09 */ EN_DT_CS_FOCUS_TARGET_BAISEN, /* [2ABB] "All must take refuge!!!" */
    /* 10 */ EN_DT_CS_FOCUS_TARGET_MUTO,   /* [2ABC] "On with the carnival!!!" */

    /* 11 */ EN_DT_CS_FOCUS_TARGET_BAISEN, /* [2AC6] "Ah!" */
    /* 12 */ EN_DT_CS_FOCUS_TARGET_MAYOR,  /* [2AC7] "Ah!" */
    /* 13 */ EN_DT_CS_FOCUS_TARGET_MUTO,   /* [2AC8] "Ah!" */
    /* 14 */ EN_DT_CS_FOCUS_TARGET_MAYOR,  /* [2AC9] "The Couple's Mask. Someone got married" */
    /* 15 */ EN_DT_CS_FOCUS_TARGET_MUTO,   /* [2ACA] "I wonder if my wife fled" */
    /* 16 */ EN_DT_CS_FOCUS_TARGET_BAISEN, /* [2ACB] "What did you just say!?" */
    /* 17 */ EN_DT_CS_FOCUS_TARGET_MAYOR,  /* [2ACB] "We're all worried, let's end the meeting" */
    /* 18 */ EN_DT_CS_FOCUS_TARGET_BAISEN, /* [2ACD] "But Mayor!" */
    /* 19 */ EN_DT_CS_FOCUS_TARGET_MAYOR,  /* [2ACE] "Stay or run, that's up to people to decide" */
    /* 20 */ EN_DT_CS_FOCUS_TARGET_MUTO,   /* [2ACF] "..!" */
    /* 21 */ EN_DT_CS_FOCUS_TARGET_MAYOR,  /* [2AD0] "Thanks for helping me end that. Here's your reward" */
    /* 22 */ EN_DT_CS_FOCUS_TARGET_MAYOR,  /* [2AD1] "I'm an unreliable mayor, but I want to protect my family" */

    /* 23 */ EN_DT_CS_FOCUS_TARGET_MAYOR /* [2AC5] "You take refuge, too." */
};

typedef struct {
    s16 D_80BEB268[1];
    s16 D_80BEB26A[25];
} CutsceneIndexTable;

static CutsceneIndexTable sCsIndexTable = { { 0x2ABB },
                                            { 0x0000, 0x2ABD, 0x0000, 0x2AC0, 0x0001, 0x2AC1, 0x0002, 0x2AC4, 0x0003,
                                              0x2AC6, 0x0004, 0x2AC7, 0x0005, 0x2AC8, 0x0006, 0x2AC9, 0x0007, 0x2ACC,
                                              0x0008, 0x2ACF, 0x0009, 0x2AD0, 0x000A, 0x0309, 0x0309 } };

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 25, 70, 0, { 0, 0, 0 } },
};

static AnimationHeader* sAnimations[EN_DT_ANIMATION_MAX] = { &object_dt_Anim_00112C, &object_dt_Anim_0005A4,
                                                             &object_dt_Anim_000854, &object_dt_Anim_000DA8,
                                                             &object_dt_Anim_000BE0, &object_dt_Anim_00B500 };

static u8 sAnimationModes[EN_DT_ANIMATION_MAX] = { ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_ONCE,
                                                   ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_ONCE };

// clang-format off
static s32 sVisualStateTable[] = {
    0, EN_DT_ANIMATION_1, EN_DT_EYE_TEXTURE_LOOK_DOWN, true,  
    0, EN_DT_ANIMATION_2, EN_DT_EYE_TEXTURE_LOOK_DOWN, true,
    0, EN_DT_ANIMATION_3, EN_DT_EYE_TEXTURE_LOOK_DOWN, true,  
    0, EN_DT_ANIMATION_3, EN_DT_EYE_TEXTURE_SHOCK,     false,
    0, EN_DT_ANIMATION_5, EN_DT_EYE_TEXTURE_SHOCK,     false, 
    0, EN_DT_ANIMATION_4, EN_DT_EYE_TEXTURE_SHOCK,     false
};
// clang-format on

static TexturePtr sEyeTextures[] = { gDotourEyeShockTex, gDotourEyeOpenTex, gDotourEyeClosedTex, gDotourEyeLookDownTex,
                                     gDotourEyeSquintTex };

static TexturePtr sBrowTextures[] = { gDotourEyebrowHighTex, gDotourEyebrowMidTex, gDotourEyebrowLowTex };

void EnDt_Init(Actor* thisx, PlayState* play) {
    EnDt* this = THIS;

    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 19.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &object_dt_Skel_00B0CC, &object_dt_Anim_00112C, this->jointTable,
                       this->morphTable, OBJECT_DT_LIMB_MAX);

    this->actor.targetMode = TARGET_MODE_6;
    this->npcEnMuto = NULL;
    this->npcEnBaisen = NULL;
    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);

    if ((gSaveContext.save.day == 3) && (gSaveContext.save.isNight)) {
        EnDt_SetupFinalNightState(this, play);
    } else {
        s32 csId = this->actor.csId;
        s32 i = 0;

        // clang-format off
        while (csId != CS_ID_NONE) { this->csIds[i] = csId; csId = CutsceneManager_GetAdditionalCsId(csId); i++; }
        // clang-format on
    }
    this->actionFunc = EnDt_SetupCutsceneNpcs;
}

void EnDt_Destroy(Actor* thisx, PlayState* play) {
    EnDt* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void EnDt_UpdateHeadRotate(EnDt* this) {
    s32 deltaAngle = BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.world.rot.y);
    s32 absDeltaAngle = ABS_ALT(deltaAngle);

    this->headRotTarget.y = 0;
    if (absDeltaAngle < 20000) {
        this->headRotTarget.y = BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.world.rot.y);

        if (this->headRotTarget.y > 10000) {
            this->headRotTarget.y = 10000;
        } else if (this->headRotTarget.y < -10000) {
            this->headRotTarget.y = -10000;
        }
    }
}

void EnDt_ChangeAnim(EnDt* this, s32 animIndex) {
    f32 morphFrames;

    this->animIndex = animIndex;

    morphFrames = -4.0f;
    if (this->animIndex == EN_DT_ANIMATION_2 || this->animIndex == EN_DT_ANIMATION_5) {
        morphFrames = 0.0f;
    }

    this->animEndFrame = Animation_GetLastFrame(sAnimations[this->animIndex]);
    Animation_Change(&this->skelAnime, sAnimations[this->animIndex], 1.0f, 0.0f, this->animEndFrame,
                     sAnimationModes[this->animIndex], morphFrames);
}

void EnDt_UpdateVisualState(EnDt* this) {
    s32 index = this->visualState * 4;

    index++;
    EnDt_ChangeAnim(this, sVisualStateTable[index]);

    index++;
    this->eyeTexIndex = sVisualStateTable[index];

    index++;
    this->disableBlinking = sVisualStateTable[index];
}

void EnDt_UpdateCutsceneFocusTarget(EnDt* this) {
    if (this->npcEnMuto != NULL && this->npcEnBaisen != NULL) {
        EnMuto* npcEnMuto = (EnMuto*)this->npcEnMuto;
        EnBaisen* npcEnBaisen = (EnBaisen*)this->npcEnBaisen;

        switch (sCutsceneFocusTargetTable[this->textIdIndex]) {
            case EN_DT_CS_FOCUS_TARGET_MUTO:
                npcEnMuto->targetActor = this->npcEnMuto;
                npcEnBaisen->targetActor = this->npcEnMuto;
                this->targetActor = this->npcEnMuto;
                break;
            case EN_DT_CS_FOCUS_TARGET_BAISEN:
                npcEnMuto->targetActor = this->npcEnBaisen;
                npcEnBaisen->targetActor = this->npcEnBaisen;
                this->targetActor = this->npcEnBaisen;
                break;
            case EN_DT_CS_FOCUS_TARGET_MAYOR:
                npcEnMuto->targetActor = &this->actor;
                npcEnBaisen->targetActor = &this->actor;
                this->targetActor = &this->actor;
                break;
        }
    }
}

void EnDt_SetupCutsceneNpcs(EnDt* this, PlayState* play) {
    Actor* npc = play->actorCtx.actorLists[ACTORCAT_NPC].first;

    while (npc != NULL) {
        if (npc->id == ACTOR_EN_MUTO) {
            this->npcEnMuto = npc;
        } else if (npc->id == ACTOR_EN_BAISEN) {
            this->npcEnBaisen = npc;
        }
        npc = npc->next;
    }

    EnDt_SetupRegularState(this, play);
}

void EnDt_SetupRegularState(EnDt* this, PlayState* play) {
    EnDtActionFunc actionFn;
    u32 textId;

    this->textIdIndex = 0;

    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_60_10)) {
        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_63_80)) {
            this->textIdIndex = 21;
            this->visualState = 5;
            EnDt_UpdateVisualState(this);

            this->actor.textId = sTextIds[this->textIdIndex];
            Message_StartTextbox(play, this->actor.textId, &this->actor);
            Player_SetCsActionWithHaltedActors(play, &this->actor, PLAYER_CSACTION_WAIT);

            actionFn = EnDt_UpdateMeetingCutscene;
            this->npcState = EN_DT_NPC_STATE_IDLE;
            this->actionFunc = actionFn;
            return;
        }
    } else if (CHECK_WEEKEVENTREG(WEEKEVENTREG_63_80)) {
        this->textIdIndex = 23; // "You take refuge too"
        this->visualState = 5;
        this->meetingFinished = true;
        EnDt_UpdateVisualState(this);
        Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_PERSON_MAYOR_DOTOUR);
    }

    if (this->visualState == 0) {
        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_60_08)) {
            this->textIdIndex = 9; // "All must take refuge!!!"
            this->visualState = 2;
        }

        EnDt_UpdateVisualState(this);
        if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_60_08)) {
            this->visualState = 1;
        }
    }

    this->actor.textId = sTextIds[this->textIdIndex];
    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_63_80)) {
        EnDt_UpdateCutsceneFocusTarget(this);
    }

    actionFn = EnDt_OfferRegularTalk;
    this->npcState = EN_DT_NPC_STATE_IDLE;
    this->actionFunc = actionFn;
}

void EnDt_OfferRegularTalk(EnDt* this, PlayState* play) {
    EnMuto* npcMuto = NULL;
    EnBaisen* npcBaisen = NULL;

    if (Actor_TalkOfferAccepted(&this->actor, &play->state)) {
        EnDt_SetupMeetingCutscene(this, play);
        return;
    }

    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_63_80)) {
        if (this->npcEnMuto != NULL && this->npcEnBaisen) {
            npcMuto = (EnMuto*)this->npcEnMuto;
            npcBaisen = (EnBaisen*)this->npcEnBaisen;
        }

        this->showedCouplesMask = false;
        this->textIdIndex = 0;

        if (Player_GetMask(play) == PLAYER_MASK_COUPLE) {
            this->textIdIndex = 11; // "Ah!"
            this->showedCouplesMask = true;

            if (this->npcEnMuto && this->npcEnBaisen) {
                npcMuto->textIdIndex = 4;   // "Ah!"
                npcBaisen->textIdIndex = 6; // "Ah!"
            }
        } else if (CHECK_WEEKEVENTREG(WEEKEVENTREG_60_08)) {
            this->textIdIndex = 9; // "All must take refuge!!!"
        }
    }

    this->actor.textId = sTextIds[this->textIdIndex];
    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_63_80) && this->npcEnMuto != NULL && this->npcEnBaisen != NULL &&
        (npcMuto->cutsceneState == 1 || npcBaisen->cutsceneState == 1)) {
        EnDt_SetupMeetingCutscene(this, play);
    }

    // After completing Couple's Mask event and wearing Kafeis Mask
    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_63_80) && (Player_GetMask(play) == PLAYER_MASK_KAFEIS_MASK)) {
        this->actor.textId = 0x2368; // "My wife hired you? Go ask the Curiosity Shop"
    }

    Actor_OfferTalk(&this->actor, play, 150.0f);
}

void EnDt_SetupMeetingCutscene(EnDt* this, PlayState* play) {
    EnMuto* npcMuto;
    EnBaisen* npcBaisen;
    s32 index;
    s16* pTextData;

    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_63_80)) {
        if (this->npcEnMuto != NULL && this->npcEnBaisen != NULL) {
            npcMuto = (EnMuto*)this->npcEnMuto;
            npcBaisen = (EnBaisen*)this->npcEnBaisen;
        }

        if ((this->npcEnMuto != NULL) && (this->npcEnBaisen != NULL)) {
            npcMuto->cutsceneState = 1;
            npcBaisen->cutsceneState = 1;
            if (Player_GetMask(play) == PLAYER_MASK_COUPLE) {
                npcMuto->textIdIndex = 4;   // "Ah!"
                npcBaisen->textIdIndex = 6; // "Ah!"
                this->visualState = 5;
                if (CHECK_WEEKEVENTREG(WEEKEVENTREG_60_08)) {
                    this->visualState = 4;
                }
                EnDt_UpdateVisualState(this);
            }
        }
    }

    this->cutsceneState = EN_DT_CS_STATE_NONE;
    for (index = 0; index < 24; index += 2) {
        if ((play->msgCtx.currentTextId == sCsIndexTable.D_80BEB268[index]) ||
            (this->actor.textId == sCsIndexTable.D_80BEB268[index])) {
            this->cutsceneState = EN_DT_CS_STATE_WAITING;
            this->csIdIndex = index;
            break;
        }
    }

    this->npcState = EN_DT_NPC_STATE_VIEWING_MEETING;
    this->actionFunc = EnDt_UpdateMeetingCutscene;
}

void EnDt_UpdateMeetingCutscene(EnDt* this, PlayState* play) {
    EnMuto* muto = NULL;
    EnBaisen* baisen = NULL;
    s32 index = sCsIndexTable.D_80BEB26A[this->csIdIndex];
    s32 csIdIndex = sCsIndexTable.D_80BEB26A[this->csIdIndex];

    if (this->cutsceneState == EN_DT_CS_STATE_WAITING) {
        if (CutsceneManager_GetCurrentCsId() == CS_ID_GLOBAL_TALK) {
            CutsceneManager_Stop(CS_ID_GLOBAL_TALK);
            CutsceneManager_Queue(this->csIds[index]);
            return;
        }

        if (!CutsceneManager_IsNext(this->csIds[index])) {
            CutsceneManager_Queue(this->csIds[index]);
            return;
        }

        CutsceneManager_StartWithPlayerCs(this->csIds[index], this->targetActor);
        Actor_ChangeFocus(&this->actor, play, this->targetActor);
        this->cutsceneState = EN_DT_CS_STATE_PLAYING;
    }

    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_63_80) && (this->npcEnMuto != NULL || this->npcEnBaisen != NULL)) {
        muto = (EnMuto*)this->npcEnMuto;
        baisen = (EnBaisen*)this->npcEnBaisen;
    }

    if (this->timer == 0 && Message_GetState(&play->msgCtx) == TEXT_STATE_EVENT && Message_ShouldAdvance((play))) {
        if (this->textIdIndex == 21) { // "Thanks for helping me end that..."
            Player_SetCsActionWithHaltedActors(play, &this->actor, PLAYER_CSACTION_END);
            if (this->cutsceneState == EN_DT_CS_STATE_PLAYING) {
                CutsceneManager_Stop(this->csIds[index]);
                this->cutsceneState = EN_DT_CS_STATE_NONE;
            }
            EnDt_OfferMeetingReward(this, play);
            return;
        }

        // After Muto and Baisen react to the Couple's Mask,
        // they leave the office and trigger a transition.
        if (this->textIdIndex == 20) { // Muto says "...!" in response to Mayor's final comments
            Message_CloseTextbox(play);
            play->nextEntrance = ENTRANCE(MAYORS_RESIDENCE, 1);
            Scene_SetExitFade(play);
            play->transitionTrigger = TRANS_TRIGGER_START;

            SET_WEEKEVENTREG(WEEKEVENTREG_63_80);
            this->meetingFinished = true;

            if (this->cutsceneState == EN_DT_CS_STATE_PLAYING) {
                CutsceneManager_Stop(this->csIds[index]);
                this->cutsceneState = EN_DT_CS_STATE_NONE;
            }
        } else {
            // At the end of each cutscene dialog, trigger an event flag
            if ((this->textIdIndex == 8) || (this->textIdIndex == 10) || (this->textIdIndex == 22) ||
                (this->textIdIndex == 23)) {
                SET_WEEKEVENTREG(WEEKEVENTREG_60_08);
                Message_CloseTextbox(play);

                // If the meeting is ongoing, reset all of the npc targets
                if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_63_80)) {
                    if ((this->npcEnMuto != NULL) && (this->npcEnBaisen != NULL)) {
                        muto->cutsceneState = 2;
                        baisen->cutsceneState = 2;
                        muto->targetActor = this->npcEnMuto;
                        baisen->targetActor = this->npcEnBaisen;
                    }
                    this->targetActor = &this->actor;
                }

                if (this->cutsceneState == EN_DT_CS_STATE_PLAYING) {
                    CutsceneManager_Stop(this->csIds[index]);
                    this->cutsceneState = EN_DT_CS_STATE_NONE;
                }
                EnDt_SetupRegularState(this, play);
                return;
            }

            this->textIdIndex++;

            // Mayor: "Let's not bring my wife into this..." - end of cutscene
            if (this->textIdIndex == 8) {
                play->msgCtx.msgLength = 0;
                EnDt_UpdateCutsceneFocusTarget(this);
                Actor_ChangeFocus(&this->actor, play, this->targetActor);
                Camera_SetTargetActor(Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(this->csIds[index])),
                                      this->targetActor);

                this->timer = 2;
                this->actionFunc = EnDt_FinishMeetingCutscene;
                return;
            }

            if (this->textIdIndex == 12) { // Mayor - "Ah!"
                if (CHECK_WEEKEVENTREG(WEEKEVENTREG_60_08)) {
                    EnDt_UpdateVisualState(this);
                    this->timer = 25;
                } else {
                    EnDt_ChangeAnim(this, EN_DT_ANIMATION_4);
                    SkelAnime_Update(&this->skelAnime);
                }
            }

            if (this->textIdIndex == 13) { // Muto - "Ah!"
                EnDt_ChangeAnim(this, EN_DT_ANIMATION_4);
                SkelAnime_Update(&this->skelAnime);
            }

            EnDt_UpdateCutsceneFocusTarget(this);
            Actor_ChangeFocus(&this->actor, play, this->targetActor);
            Camera_SetTargetActor(Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(this->csIds[index])),
                                  this->targetActor);

            this->actor.textId = sTextIds[this->textIdIndex];
            Message_CloseTextbox(play);
            Message_StartTextbox(play, this->actor.textId, &this->actor);

            // Sets the cutscene ID index based off the current textId
            for (index = 0; index < 24; index += 2) {
                if (play->msgCtx.currentTextId == sCsIndexTable.D_80BEB268[index] ||
                    this->actor.textId == sCsIndexTable.D_80BEB268[index]) {
                    this->csIdIndex = index;
                    break;
                }
            }

            index = sCsIndexTable.D_80BEB26A[this->csIdIndex];
            if (this->cutsceneState == EN_DT_CS_STATE_PLAYING && (index != csIdIndex)) {
                this->cutsceneState = EN_DT_CS_STATE_WAITING;
                CutsceneManager_Stop(this->csIds[csIdIndex]);
                CutsceneManager_Queue(this->csIds[index]);
            }

            // Mutoh turns his head to focus on the Mayor after saying "Isn't that right Mayor?"
            if (this->textIdIndex == 3 && this->npcEnMuto != NULL && this->npcEnBaisen != NULL) {
                muto->targetActor = &this->actor;
            }
        }
    }
}

void EnDt_FinishMeetingCutscene(EnDt* this, PlayState* play) {
    f32 currFrame = this->skelAnime.curFrame;

    if (this->timer != 0) {
        if (this->timer == 1) {
            if ((this->textIdIndex == 8) || (this->visualState == 4)) {
                EnDt_UpdateVisualState(this);
            }

            this->visualState++;
            if (this->visualState > 5) {
                this->visualState = 5;
            }
        }
    } else if (this->animEndFrame <= currFrame) {
        Camera* pCamera;
        s32 index;
        s32 currTextId = sCsIndexTable.D_80BEB26A[this->csIdIndex];

        EnDt_UpdateVisualState(this);

        Message_CloseTextbox(play);
        this->actor.textId = sTextIds[this->textIdIndex];
        Message_StartTextbox(play, this->actor.textId, &this->actor);

        if (this->textIdIndex == 8) { // "Let's not bring my wife into this"
            Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_PERSON_MAYOR_DOTOUR);
        }

        // Loop through the text id array and set the index if it matches the current text id
        for (index = 0; index < 24; index++) {
            if ((play->msgCtx.currentTextId == sCsIndexTable.D_80BEB268[index]) ||
                (this->actor.textId == sCsIndexTable.D_80BEB268[index])) {
                this->csIdIndex = index;
            }
        }

        index = sCsIndexTable.D_80BEB26A[this->csIdIndex];
        if ((this->cutsceneState == EN_DT_CS_STATE_PLAYING) && (index != currTextId)) {
            this->cutsceneState = EN_DT_CS_STATE_WAITING;
            CutsceneManager_Stop(this->csIds[currTextId]);
            CutsceneManager_Queue(this->csIds[index]);
        }

        EnDt_UpdateCutsceneFocusTarget(this);
        Actor_ChangeFocus(&this->actor, play, this->targetActor);

        pCamera = Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(this->csIds[index]));
        Camera_SetTargetActor(pCamera, this->targetActor);

        this->actionFunc = EnDt_UpdateMeetingCutscene;
    }
}

void EnDt_OfferMeetingReward(EnDt* this, PlayState* play) {
    Actor_OfferGetItem(&this->actor, play, GI_HEART_PIECE, 300.0f, 300.0f);
    this->npcState = EN_DT_NPC_STATE_OFFERED_MEETING_REWARD;
    this->actionFunc = EnDt_TriggerMeetingRewardEvent;
}

void EnDt_TriggerMeetingRewardEvent(EnDt* this, PlayState* play) {
    if (Actor_HasParent(&this->actor, play)) {
        this->textIdIndex = 22;
        this->actor.parent = NULL;
        this->actor.textId = sTextIds[this->textIdIndex];

        Actor_OfferTalkExchange(&this->actor, play, 400.0f, 400.0f, PLAYER_IA_MINUS1);

        SET_WEEKEVENTREG(WEEKEVENTREG_60_10);
        this->actionFunc = EnDt_TriggerMeetingNotebookEvent;
    } else {
        Actor_OfferGetItem(&this->actor, play, GI_HEART_PIECE, 300.0f, 300.0f);
    }
}

void EnDt_TriggerMeetingNotebookEvent(EnDt* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);

    if (Actor_TalkOfferAccepted(&this->actor, &play->state)) {
        Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_RECEIVED_MAYOR_HP);
        Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_PERSON_MAYOR_DOTOUR);
        this->actionFunc = EnDt_UpdateMeetingCutscene;
    } else {
        Actor_OfferTalkExchange(&this->actor, play, 400.0f, 400.0f, PLAYER_IA_MINUS1);
    }
}

void EnDt_SetupFinalNightState(EnDt* this, PlayState* play) {
    EnDt_ChangeAnim(this, EN_DT_ANIMATION_3);

    this->disableBlinking = true;
    this->textIdIndex = 24; // "Unclear which way things will go, cus Mutoh said he would call wife"
    Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_PERSON_MAYOR_DOTOUR);

    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_60_40)) {
        this->textIdIndex = 26; // "Hard to figure out which way things will go"
    }

    this->actor.textId = sTextIds[this->textIdIndex];
    this->eyeTexIndex = EN_DT_EYE_TEXTURE_LOOK_DOWN;
    this->disableBlinking = true;
    this->npcState = EN_DT_NPC_STATE_WAIT_FINAL_NIGHT_TALK;
    this->actionFunc = EnDt_OfferFinalNightTalk;
}

void EnDt_OfferFinalNightTalk(EnDt* this, PlayState* play) {
    EnDt_UpdateHeadRotate(this);

    if (Actor_TalkOfferAccepted(&this->actor, &play->state)) {
        EnDt_StartFinalNightTalk(this);
        return;
    }

    // After completing Couple's Mask event and wearing Kafeis Mask
    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_63_80) && Player_GetMask(play) == PLAYER_MASK_KAFEIS_MASK) {
        this->actor.textId = 0x2368; // "My wife hired you? Go ask the Curiosity Shop"
    }

    Actor_OfferTalk(&this->actor, play, 150.0f);
}

void EnDt_StartFinalNightTalk(EnDt* this) {
    this->npcState = EN_DT_NPC_STATE_DONE_FINAL_NIGHT_TALK;
    this->actionFunc = EnDt_TriggerFinalNightTalkEvent;
}

void EnDt_TriggerFinalNightTalkEvent(EnDt* this, PlayState* play) {
    EnDt_UpdateHeadRotate(this);

    if (Message_GetState(&play->msgCtx) == TEXT_STATE_EVENT && Message_ShouldAdvance(play)) {
        Message_CloseTextbox(play);
        if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_60_40)) {
            this->textIdIndex = 25; // "The carnival is... on"
            Message_ContinueTextbox(play, sTextIds[this->textIdIndex]);
            SET_WEEKEVENTREG(WEEKEVENTREG_60_40);
        } else {
            EnDt_SetupFinalNightState(this, play);
        }
    }
}

void EnDt_Update(Actor* thisx, PlayState* play) {
    EnDt* this = THIS;
    ColliderCylinder* collider;

    SkelAnime_Update(&this->skelAnime);
    Actor_SetScale(&this->actor, 0.01f);

    if (this->npcState != 4 && this->npcState != 5 && gSaveContext.save.day == 3 && gSaveContext.save.isNight) {
        EnDt_SetupFinalNightState(this, play);
    }

    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_63_80) &&
        (gSaveContext.save.day != 3 || (gSaveContext.save.day == 3 && !gSaveContext.save.isNight))) {
        Audio_PlaySequenceAtPos(SEQ_PLAYER_BGM_SUB, &gSfxDefaultPos, NA_BGM_MAYORS_OFFICE, 1000.0f);
        Actor_PlaySfx(&this->actor, 0x205DU);
    }

    DECR(this->blinkTimer);
    DECR(this->timer);

    if (this->meetingFinished) {
        EnDt_UpdateHeadRotate(this);
    }

    // Blinking update
    if (!this->disableBlinking && this->blinkTimer == 0) {
        this->eyeTexIndex++;
        if (this->eyeTexIndex >= EN_DT_EYE_TEXTURE_LOOK_DOWN) {
            this->eyeTexIndex = EN_DT_EYE_TEXTURE_SHOCK;
            this->blinkTimer = (s32)Rand_ZeroFloat(60.0f) + 20;
        }
    }

    this->actionFunc(this, play);

    this->actor.shape.rot.y = this->actor.world.rot.y;
    Math_SmoothStepToS(&this->headRotValue.y, this->headRotTarget.y, 1, 3000, 0);

    Actor_SetFocus(&this->actor, 60.0f);
    Actor_MoveWithGravity(&this->actor);

    collider = &this->collider;
    Collider_UpdateCylinder(&this->actor, collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &collider->base);
}

s32 EnDt_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnDt* this = THIS;

    if (limbIndex == OBJECT_DT_LIMB_0C) {
        rot->y += -1 * this->headRotValue.y;
    }

    return false;
}

void EnDt_Draw(Actor* thisx, PlayState* play) {
    EnDt* this = THIS;
    s32 eyebrowIndex = 0;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Opa(play->state.gfxCtx);
    Gfx_SetupDL25_Xlu(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sEyeTextures[this->eyeTexIndex]));

    if (this->eyeTexIndex < EN_DT_BROW_TEXTURE_MAX) {
        eyebrowIndex = this->eyeTexIndex;
    }

    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(sBrowTextures[eyebrowIndex]));

    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnDt_OverrideLimbDraw, NULL, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}
